#include <stdio.h>
#include "sprite_sheet.h"
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

void spu_control(int instruction)
{
	IOWR_ALTERA_AVALON_PIO_DATA(CONTROL_BASE, instruction);
}

int main()
{
	printf("PacPac\n");
	spu_set_sprite(0, yellow_pacman_sprite);
	spu_set_sprite(1, red_ghost_sprite);
	for (int y = 0; y < 30; ++y) {
		for (int x = 0; x < 40; ++x) {
			spu_set_map(x, y, 0);
		}
	}
	for (int i = 0; i < 16; ++i) {
		if (i != 0) {
			spu_set_map(i - 1, 19, 0);
		}
		spu_set_map(i, 19, 1);
		for (int j = 0; j < 65536; ++j) {}
	}
	return 0;
}
