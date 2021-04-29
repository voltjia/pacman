/*
 * spu.c
 *
 *  Created on: 2021Äê4ÔÂ28ÈÕ
 *      Author: user
 */

#include "spu.h"

int rgba_to_rgb(int rgba)
{
	int rgb = ((rgba & 0xF0000000) >> 20) | ((rgba & 0x00F00000) >> 16) | ((rgba & 0x0000F000) >> 12);
	return rgb;
}

void spu_set_sprite(int index, int *sprite)
{
	for (int y = 0; y < 16; ++y) {
		for (int x = 0; x < 16; ++x) {
			spu_control(SPU_SET_SPRITE
					| (index << 20)
					| (x << 16)
					| (y << 12)
					| rgba_to_rgb(sprite[y * 16 + x]));
		}
	}
}

void spu_set_map(int x, int y, int index)
{
	spu_control(SPU_SET_MAP
			| (x << 22)
			| (y << 16)
			| index);
}
