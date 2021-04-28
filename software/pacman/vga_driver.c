/*
 * vga_driver.c
 *
 *  Created on: 2021Äê4ÔÂ23ÈÕ
 *      Author: user
 */

#include "vga_driver.h"

vga_sender vga_send_pixel_color;
vga_sender vga_send_pixel_position;

int vga_canvas[VGA_WIDTH * VGA_HEIGHT];

void vga_init_canvas()
{
	memset(vga_canvas, 0, VGA_WIDTH * VGA_HEIGHT);
}

int *vga_get_canvas_address()
{
	return vga_canvas;
}

void vga_set_pixel_color_sender(vga_sender sender)
{
	vga_send_pixel_color = sender;
}

void vga_set_pixel_position_sender(vga_sender sender)
{
	vga_send_pixel_position = sender;
}

void vga_set_pixel_rgba(int x, int y, int rgba)
{
	vga_canvas[y * VGA_WIDTH + x] = rgba;
}

void vga_draw()
{
	for (int y = 0; y < VGA_HEIGHT; ++y) {
		for (int x = 0; x < VGA_WIDTH; ++x) {
			int position = y * VGA_WIDTH + x;
			vga_send_pixel_color(vga_canvas[position]);
			vga_send_pixel_position(position);
		}
	}
}
