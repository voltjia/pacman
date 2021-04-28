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

void read_rgbas_from_file(char *file_name, int *rgbas)
{
	FILE *file = fopen(file_name, "r");
	for (int i = 0; i < 256; ++i) {
		fscanf(file, "%x", rgbas + i);
		printf("%x\n", rgbas[i]);
	}
	fclose(file);
}

void read_rgbas_from_stdin(int *rgbas)
{
	for (int i = 0; i < 256; ++i) {
		scanf("%x", rgbas + i);
		printf("%x\n", rgbas[i]);
	}
}

int rgba_to_rgb(int rgba)
{
	int rgb = ((rgba & 0xF0000000) >> 20) | ((rgba & 0x00F00000) >> 16) | ((rgba & 0x0000F000) >> 12);
	return rgb;
}

int main()
{
	printf("PacPac\n");
	int illini_blue = 0x13294BFF;
	int illini_orange = 0xE84A27FF;
	int pacman[256] = {0};
	printf("Please enter pacman:\n");
	read_rgbas_from_stdin(pacman);
	int control = 0;
	control = 0x10100000;
	for (int y = 0; y < 16; ++y) {
		for (int x = 0; x < 16; ++x) {
			int actual_control = control | (y << 12) | (x << 16) | rgba_to_rgb(pacman[y * 16 + x]);
			IOWR_ALTERA_AVALON_PIO_DATA(CONTROL_BASE, actual_control);
			printf("%x\n", actual_control);
		}
	}
	return 0;
}
