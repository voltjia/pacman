/*
 * spu.c
 *
 *  Created on: 2021Äê4ÔÂ28ÈÕ
 *      Author: user
 */

#include "spu.h"

void spu_show_all_sprites()
{
	int map[1200] = {0};
	int count = 0;
	for (int y = 0; y < SPU_MAP_HEIGHT; ++y) {
		for (int x = 0; x < SPU_MAP_WIDTH; ++x) {
			map[y * SPU_MAP_WIDTH + x] = (count++) % PAC_MAN_GAME_SPRITE_COUNT;
		}
	}
}

void spu_show_all_walls()
{
	for (int x = 0; x < SPU_MAP_WIDTH; ++x) {
		spu_set_sprite(x, 0, HORIZONTAL_WALL_SPRITE);
		spu_set_sprite(x, SPU_MAP_HEIGHT / 2, HORIZONTAL_WALL_SPRITE);
		spu_set_sprite(x, SPU_MAP_HEIGHT - 1, HORIZONTAL_WALL_SPRITE);
	}
	for (int y = 0; y < SPU_MAP_WIDTH; ++y) {
		spu_set_sprite(0, y, VERTICAL_WALL_SPRITE);
		spu_set_sprite(SPU_MAP_WIDTH / 2, y, VERTICAL_WALL_SPRITE);
		spu_set_sprite(SPU_MAP_WIDTH - 1, y, VERTICAL_WALL_SPRITE);
	}
	spu_set_sprite(SPU_MAP_WIDTH / 2, SPU_MAP_HEIGHT / 2, CROSS_WALL_SPRITE);
	spu_set_sprite(SPU_MAP_WIDTH / 2, 0, T_WALL_SPRITE_DOWN);
	spu_set_sprite(SPU_MAP_WIDTH / 2, SPU_MAP_HEIGHT - 1, T_WALL_SPRITE_UP);
	spu_set_sprite(0, SPU_MAP_HEIGHT / 2, T_WALL_SPRITE_RIGHT);
	spu_set_sprite(SPU_MAP_WIDTH - 1, SPU_MAP_HEIGHT / 2, T_WALL_SPRITE_LEFT);
	spu_set_sprite(0, 0, TOP_LEFT_WALL_SPRITE);
	spu_set_sprite(SPU_MAP_WIDTH - 1, 0, TOP_RIGHT_WALL_SPRITE);
	spu_set_sprite(0, SPU_MAP_HEIGHT - 1, BOTTOM_LEFT_WALL_SPRITE);
	spu_set_sprite(SPU_MAP_WIDTH - 1, SPU_MAP_HEIGHT - 1, BOTTOM_RIGHT_WALL_SPRITE);
}

void spu_set_sprite(int x, int y, int index)
{
	spu_control((x << 14) | (y << 8) | (0x00FF & index));
}

void spu_set_map(int *map)
{
	for (int y = 0; y < SPU_MAP_HEIGHT; ++y) {
		for (int x = 0; x < SPU_MAP_WIDTH; ++x) {
			spu_set_sprite(x, y, map[y * SPU_MAP_WIDTH + x]);
		}
	}
}

void spu_animate(int *map)
{
	for (int i = 0; i < SPU_MAP_WIDTH * SPU_MAP_HEIGHT; ++i) {
		switch (0x00FF & map[i]) {
		case PAC_MAN_SPRITE_0:
			map[i] >>= 8;
			break;
		case PAC_MAN_SPRITE_UP_1:
			map[i] = PAC_MAN_SPRITE_UP_2;
			break;
		case PAC_MAN_SPRITE_UP_2:
			map[i] = (PAC_MAN_SPRITE_UP_1 << 8) | PAC_MAN_SPRITE_0;
			break;
		case PAC_MAN_SPRITE_DOWN_1:
			map[i] = PAC_MAN_SPRITE_DOWN_2;
			break;
		case PAC_MAN_SPRITE_DOWN_2:
			map[i] = (PAC_MAN_SPRITE_DOWN_1 << 8) | PAC_MAN_SPRITE_0;
			break;
		case PAC_MAN_SPRITE_LEFT_1:
			map[i] = PAC_MAN_SPRITE_LEFT_2;
			break;
		case PAC_MAN_SPRITE_LEFT_2:
			map[i] = (PAC_MAN_SPRITE_LEFT_1 << 8) | PAC_MAN_SPRITE_0;
			break;
		case PAC_MAN_SPRITE_RIGHT_1:
			map[i] = PAC_MAN_SPRITE_RIGHT_2;
			break;
		case PAC_MAN_SPRITE_RIGHT_2:
			map[i] = (PAC_MAN_SPRITE_RIGHT_1 << 8) | PAC_MAN_SPRITE_0;
			break;
		case RED_GHOST_SPRITE_UP_1:
		case PINK_GHOST_SPRITE_UP_1:
		case CYAN_GHOST_SPRITE_UP_1:
		case STEEL_GHOST_SPRITE_UP_1:
		case RED_GHOST_SPRITE_DOWN_1:
		case PINK_GHOST_SPRITE_DOWN_1:
		case CYAN_GHOST_SPRITE_DOWN_1:
		case STEEL_GHOST_SPRITE_DOWN_1:
		case RED_GHOST_SPRITE_LEFT_1:
		case PINK_GHOST_SPRITE_LEFT_1:
		case CYAN_GHOST_SPRITE_LEFT_1:
		case STEEL_GHOST_SPRITE_LEFT_1:
		case RED_GHOST_SPRITE_RIGHT_1:
		case PINK_GHOST_SPRITE_RIGHT_1:
		case CYAN_GHOST_SPRITE_RIGHT_1:
		case STEEL_GHOST_SPRITE_RIGHT_1:
		case BLUE_GHOST_SPRITE_1:
		case WHITE_GHOST_SPRITE_1:
			++map[i];
			break;
		case RED_GHOST_SPRITE_UP_2:
		case PINK_GHOST_SPRITE_UP_2:
		case CYAN_GHOST_SPRITE_UP_2:
		case STEEL_GHOST_SPRITE_UP_2:
		case BLUE_GHOST_SPRITE_2:
		case WHITE_GHOST_SPRITE_2:
		case RED_GHOST_SPRITE_DOWN_2:
		case PINK_GHOST_SPRITE_DOWN_2:
		case CYAN_GHOST_SPRITE_DOWN_2:
		case STEEL_GHOST_SPRITE_DOWN_2:
		case RED_GHOST_SPRITE_LEFT_2:
		case PINK_GHOST_SPRITE_LEFT_2:
		case CYAN_GHOST_SPRITE_LEFT_2:
		case STEEL_GHOST_SPRITE_LEFT_2:
		case RED_GHOST_SPRITE_RIGHT_2:
		case PINK_GHOST_SPRITE_RIGHT_2:
		case CYAN_GHOST_SPRITE_RIGHT_2:
		case STEEL_GHOST_SPRITE_RIGHT_2:
			--map[i];
			break;
		default:
			break;
		}
	}
}
