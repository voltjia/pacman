#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pacman.h"
#include "spu.h"
#include "system.h"
#include "altera_avalon_spi.h"
#include "altera_avalon_spi_regs.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include "usb_kb/GenericMacros.h"
#include "usb_kb/GenericTypeDefs.h"
#include "usb_kb/HID.h"
#include "usb_kb/MAX3421E.h"
#include "usb_kb/transfer.h"
#include "usb_kb/usb_ch9.h"
#include "usb_kb/USB.h"

#define ARROW_UP 0x52
#define ARROW_DOWN 0x51
#define ARROW_LEFT 0x50
#define ARROW_RIGHT 0x4f
#define KEY_W 0x1a
#define KEY_A 0x04
#define KEY_S 0x16
#define KEY_D 0x07

#define NUM_THREADS 5

void spu_control(int instruction)
{
	IOWR_ALTERA_AVALON_PIO_DATA(CONTROL_BASE, instruction);
}

extern HID_DEVICE hid_device;

static BYTE addr = 1; 				//hard-wired USB address
const char* const devclasses[] = { " Uninitialized", " HID Keyboard", " HID Mouse", " Mass storage" };

BOOT_KBD_REPORT kbdbuf;
BYTE key = 0;

int map[1200];

int pacman_x = 19;
int pacman_y = 28;
int red_ghost_x = 19;
int red_ghost_y = 9;
int pink_ghost_x = 19;
int pink_ghost_y = 12;
int cyan_ghost_x = 18;
int cyan_ghost_y = 12;
int teal_ghost_x = 20;
int teal_ghost_y = 12;

BYTE GetDriverandReport()
{
	BYTE i;
	BYTE rcode;
	BYTE device = 0xFF;
	BYTE tmpbyte;

	DEV_RECORD* tpl_ptr;
	printf("Reached USB_STATE_RUNNING (0x40)\n");
	for (i = 1; i < USB_NUMDEVICES; i++) {
		tpl_ptr = GetDevtable(i);
		if (tpl_ptr->epinfo != NULL) {
			printf("Device: %d", i);
			printf("%s \n", devclasses[tpl_ptr->devclass]);
			device = tpl_ptr->devclass;
		}
	}
	//Query rate and protocol
	rcode = XferGetIdle(addr, 0, hid_device.interface, 0, &tmpbyte);
	if (rcode) {   //error handling
		printf("GetIdle Error. Error code: ");
		printf("%x \n", rcode);
	} else {
		printf("Update rate: ");
		printf("%x \n", tmpbyte);
	}
	printf("Protocol: ");
	rcode = XferGetProto(addr, 0, hid_device.interface, &tmpbyte);
	if (rcode) {   //error handling
		printf("GetProto Error. Error code ");
		printf("%x \n", rcode);
	} else {
		printf("%d \n", tmpbyte);
	}
	return device;
}

void setLED(int LED)
{
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_PIO_BASE,
			(IORD_ALTERA_AVALON_PIO_DATA(LEDS_PIO_BASE) | (0x001 << LED)));
}

void clearLED(int LED)
{
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_PIO_BASE,
			(IORD_ALTERA_AVALON_PIO_DATA(LEDS_PIO_BASE) & ~(0x001 << LED)));

}

void printSignedHex0(signed char value)
{
	BYTE tens = 0;
	BYTE ones = 0;
	WORD pio_val = IORD_ALTERA_AVALON_PIO_DATA(HEX_DIGITS_PIO_BASE);
	if (value < 0) {
		setLED(11);
		value = -value;
	} else {
		clearLED(11);
	}
	//handled hundreds
	if (value / 100)
		setLED(13);
	else
		clearLED(13);

	value = value % 100;
	tens = value / 10;
	ones = value % 10;

	pio_val &= 0x00FF;
	pio_val |= (tens << 12);
	pio_val |= (ones << 8);

	IOWR_ALTERA_AVALON_PIO_DATA(HEX_DIGITS_PIO_BASE, pio_val);
}

void printSignedHex1(signed char value)
{
	BYTE tens = 0;
	BYTE ones = 0;
	DWORD pio_val = IORD_ALTERA_AVALON_PIO_DATA(HEX_DIGITS_PIO_BASE);
	if (value < 0) {
		setLED(10);
		value = -value;
	} else {
		clearLED(10);
	}
	//handled hundreds
	if (value / 100)
		setLED(12);
	else
		clearLED(12);

	value = value % 100;
	tens = value / 10;
	ones = value % 10;
	tens = value / 10;
	ones = value % 10;

	pio_val &= 0xFF00;
	pio_val |= (tens << 4);
	pio_val |= (ones << 0);

	IOWR_ALTERA_AVALON_PIO_DATA(HEX_DIGITS_PIO_BASE, pio_val);
}

void setKeycode(WORD keycode)
{
	IOWR_ALTERA_AVALON_PIO_DATA(KEYCODE_BASE, keycode);
}

int can_walk(int *map, int x, int y)
{
	if (x == -1 || y == -1 || x == PACMAN_MAP_WIDTH || y == PACMAN_MAP_HEIGHT) {
		return 0;
	}
	int dest_sprite = map_get_sprite(map, x, y);
	int dest_type = sprite_type(dest_sprite);
	return dest_type != GHOST && dest_type != WALL;
}

void pacman_task()
{
	int pacman = map_get_sprite(map, pacman_x, pacman_y);
	int pacman_direction = sprite_direction(pacman);

	printf("key: %x\n", key);
	printf("direction: %x\n", pacman_direction >> SPRITE_DIRECTION_SHIFT);

	if (key == ARROW_UP && pacman_direction != UP) {
		map_set_sprite(map, pacman_x, pacman_y, get_sprite(PACMAN | UP));
	} else if (key == ARROW_DOWN && pacman_direction != DOWN) {
		map_set_sprite(map, pacman_x, pacman_y, get_sprite(PACMAN | DOWN));
	} else if (key == ARROW_LEFT && pacman_direction != LEFT) {
		map_set_sprite(map, pacman_x, pacman_y, get_sprite(PACMAN | LEFT));
	} else if (key == ARROW_RIGHT && pacman_direction != RIGHT) {
		map_set_sprite(map, pacman_x, pacman_y, get_sprite(PACMAN | RIGHT));
	}

	pacman = map_get_sprite(map, pacman_x, pacman_y);
	pacman_direction = sprite_direction(pacman);

	switch (pacman_direction) {
	case UP:
		if (can_walk(map, pacman_x, pacman_y - 1)) {
			map_set_sprite(map, pacman_x, pacman_y, BACKGROUND);
			map_set_sprite(map, pacman_x, --pacman_y, pacman);
		}
		break;
	case DOWN:
		if (can_walk(map, pacman_x, pacman_y + 1)) {
			map_set_sprite(map, pacman_x, pacman_y, BACKGROUND);
			map_set_sprite(map, pacman_x, ++pacman_y, pacman);
		}
		break;
	case LEFT:
		if (can_walk(map, pacman_x - 1, pacman_y)) {
			map_set_sprite(map, pacman_x, pacman_y, BACKGROUND);
			map_set_sprite(map, --pacman_x, pacman_y, pacman);
		}
		break;
	case RIGHT:
		if (can_walk(map, pacman_x + 1, pacman_y)) {
			map_set_sprite(map, pacman_x, pacman_y, BACKGROUND);
			map_set_sprite(map, ++pacman_x, pacman_y, pacman);
		}
		break;
	}

	animate_map(map);
	spu_set_map(map);
}

int main()
{
	srand (time(NULL));

	BYTE rcode;
	BOOT_MOUSE_REPORT buf;		//USB mouse report
	BOOT_KBD_REPORT kbdbuf;

	BYTE runningdebugflag = 0;//flag to dump out a bunch of information when we first get to USB_STATE_RUNNING
	BYTE errorflag = 0; //flag once we get an error device so we don't keep dumping out state info
	BYTE device;
	WORD keycode;

	MAX3421E_init();
	USB_init();

	printf("PacPac\n");
	test_map(map);
	map_set_sprite(map, pacman_x, pacman_y, get_sprite(PACMAN));
	map_set_sprite(map, red_ghost_x, red_ghost_y, get_sprite(RED | GHOST | LEFT));
	map_set_sprite(map, pink_ghost_x, pink_ghost_y, get_sprite(PINK | GHOST | UP));
	map_set_sprite(map, cyan_ghost_x, cyan_ghost_y, get_sprite(CYAN | GHOST | UP));
	map_set_sprite(map, teal_ghost_x, teal_ghost_y, get_sprite(TEAL | GHOST | UP));
	spu_set_map(map);

	for (int i = 0; ; ++i) {
		MAX3421E_Task();
		USB_Task();
		pacman_task();
		//usleep (500000);
		if (GetUsbTaskState() == USB_STATE_RUNNING) {
			if (!runningdebugflag) {
				runningdebugflag = 1;
				setLED(9);
				device = GetDriverandReport();
			} else if (device == 1) {
				//run keyboard debug polling
				rcode = kbdPoll(&kbdbuf);
				if (rcode == hrNAK) {
					continue; //NAK means no new data
				} else if (rcode) {
					printf("Rcode: ");
					printf("%x \n", rcode);
					continue;
				}
				printf("keycodes: ");
				for (int n = 0; n < 6; n++) {
					printf("%x ", kbdbuf.keycode[n]);
				}
				BYTE temp = kbdbuf.keycode[0];
				if (temp == 0x52 || temp == 0x51 || temp == 0x50 || temp == 0x4f)
					key = temp;
//				setKeycode(kbdbuf.keycode[0]);
//				printSignedHex0(kbdbuf.keycode[0]);
//				printSignedHex1(kbdbuf.keycode[1]);
				printf("\n");
			}

			else if (device == 2) {
				rcode = mousePoll(&buf);
				if (rcode == hrNAK) {
					//NAK means no new data
					continue;
				} else if (rcode) {
					printf("Rcode: ");
					printf("%x \n", rcode);
					continue;
				}
				printf("X displacement: ");
				printf("%d ", (signed char) buf.Xdispl);
				printSignedHex0((signed char) buf.Xdispl);
				printf("Y displacement: ");
				printf("%d ", (signed char) buf.Ydispl);
				printSignedHex1((signed char) buf.Ydispl);
				printf("Buttons: ");
				printf("%x\n", buf.button);
				if (buf.button & 0x04)
					setLED(2);
				else
					clearLED(2);
				if (buf.button & 0x02)
					setLED(1);
				else
					clearLED(1);
				if (buf.button & 0x01)
					setLED(0);
				else
					clearLED(0);
			}
		} else if (GetUsbTaskState() == USB_STATE_ERROR) {
			if (!errorflag) {
				errorflag = 1;
				clearLED(9);
				printf("USB Error State\n");
				//print out string descriptor here
			}
		} else { //not in USB running state
			printf("USB task state: ");
			printf("%x\n", GetUsbTaskState());
			if (runningdebugflag) {	//previously running, reset USB hardware just to clear out any funky state, HS/FS etc
				runningdebugflag = 0;
				MAX3421E_init();
				USB_init();
			}
			errorflag = 0;
			clearLED(9);
		}
	}

	return 0;
}
