/*
 * vga_driver.h
 *
 *  Created on: 2021Äê4ÔÂ23ÈÕ
 *      Author: user
 */

#ifndef VGA_DRIVER_H_
#define VGA_DRIVER_H_

#include <stdlib.h>
#include <string.h>

#define VGA_WIDTH 640
#define VGA_HEIGHT 480

typedef void (*vga_sender)(int);

void vga_init_canvas();
int *vga_get_canvas_address();
void vga_send_canvas_address();
void vga_set_pixel_color_sender(vga_sender sender);
void vga_set_pixel_position_sender(vga_sender sender);
void vga_set_pixel_rgba(int x, int y, int rgba);
void vga_draw();

#endif /* VGA_DRIVER_H_ */
