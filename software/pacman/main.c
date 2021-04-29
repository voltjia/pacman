#include <stdio.h>
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

void spu_control(int instruction)
{
	IOWR_ALTERA_AVALON_PIO_DATA(CONTROL_BASE, instruction);
}

int main()
{
	printf("PacPac\n");
	int map[1200] = {0};
	int count = 0;
	for (int y = 0; y < SPU_MAP_HEIGHT; ++y) {
		for (int x = 0; x < SPU_MAP_WIDTH; ++x) {
			map[y * SPU_MAP_WIDTH + x] = (count++) % 49;
		}
	}
	spu_set_map(map);
	return 0;
}
