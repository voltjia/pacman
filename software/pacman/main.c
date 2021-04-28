#include <stdio.h>
#include "vga_driver.h"
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

void control_menu()
{
	printf("Control Menu\n");
	printf("\t1. Fill in Illini orange (E84A27FF);\n");
	printf("\t2. Fill in Illini blue (13294BFF).\n");
	for (;;) {
		printf("Please enter one of the above options: ");
		int option = 0;
		scanf("%d", &option);
		if (option == 1) {
			int control = 0x10000E42;
			for (int y = 0; y < 16; ++y) {
				for (int x = 0; x < 16; ++x) {
					IOWR_ALTERA_AVALON_PIO_DATA(CONTROL_BASE, control | (y << 12) | (x << 16));
					printf("%x\n", control | (y << 12) | (x << 16));
				}
			}
		} else if (option == 2) {
			int control = 0x10000124;
			for (int y = 0; y < 16; ++y) {
				for (int x = 0; x < 16; ++x) {
					IOWR_ALTERA_AVALON_PIO_DATA(CONTROL_BASE, control | (y << 12) | (x << 16));
					printf("%x\n", control | (y << 12) | (x << 16));
				}
			}
		} else {
			printf("Command not found.\n");
		}
	}
}

int main()
{
	printf("PacPac\n");
	int illini_blue = 0x13294BFF;
	int illini_orange = 0xE84A27FF;
	int control = 0;
	control = 0x10000124;
	for (int y = 0; y < 16; ++y) {
		for (int x = 0; x < 16; ++x) {
			IOWR_ALTERA_AVALON_PIO_DATA(CONTROL_BASE, control | (y << 12) | (x << 16));
			printf("%x\n", control | (y << 12) | (x << 16));
		}
	}
	control = 0x10100E42;
	for (int y = 0; y < 16; ++y) {
		for (int x = 0; x < 16; ++x) {
			IOWR_ALTERA_AVALON_PIO_DATA(CONTROL_BASE, control | (y << 12) | (x << 16));
			printf("%x\n", control | (y << 12) | (x << 16));
		}
	}
	control = 0x20000001;
	for (int y = 0; y < 30; ++y) {
		for (int x = 0; x < 40; ++x) {
			IOWR_ALTERA_AVALON_PIO_DATA(CONTROL_BASE, control | (y << 16) | (x << 22));
			printf("%x\n", control | (y << 16) | (x << 22));
		}
	}
	// 0x29dd0000
	// 0010 1001 1101 1101 0000 0000 0000 0000
	control = 0x20000000;
	IOWR_ALTERA_AVALON_PIO_DATA(CONTROL_BASE, control | (16 << 16) | (16 << 22));
	// 0010 0000 0100 0001 0000 0000 0000 0001
	printf("%x\n", control | (2 << 16) | (2 << 22));
	// IOWR_ALTERA_AVALON_PIO_DATA(CONTROL_BASE, control | (1 << 16) | (1 << 22));
	/*
	for (int y = 1; y < 2; ++y) {
		for (int x = 1; x < 2; ++x) {
			IOWR_ALTERA_AVALON_PIO_DATA(CONTROL_BASE, control | (y << 16) | (x << 22));
			printf("%x\n", control | (y << 12) | (x << 16));
		}
	}
	*/
	return 0;
}
