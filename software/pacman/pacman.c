/*
 * pacman.c
 *
 *  Created on: 2021��4��30��
 *      Author: user
 */

#include "pacman.h"

void spawn_all_sprites(int *map)
{
	int count = 0;
	for (int y = 0; y < PACMAN_MAP_HEIGHT; ++y) {
		for (int x = 0; x < PACMAN_MAP_WIDTH; ++x) {
			map[y * PACMAN_MAP_WIDTH + x] = (count++) % SPRITE_COUNT;
		}
	}
}

int sprite_index(int sprite)
{
	return SPRITE_INDEX_MASK & sprite;
}

int sprite_type(int sprite)
{
	return SPRITE_TYPE_MASK & sprite;
}

int sprite_direction(int sprite)
{
	return SPRITE_DIRECTION_MASK & sprite;
}

int sprite_property(int sprite)
{
	return SPRITE_PROPERTY_MASK & sprite;
}

int get_pacman(int pacman)
{
	if (sprite_direction(pacman) == IDLE) {
		return 0;
	}
	return PACMAN_BASE + 2 * (sprite_direction(pacman) >> SPRITE_DIRECTION_SHIFT) - 1;
}

int get_ghost(int ghost)
{
	switch (sprite_property(ghost)) {
	case BLUE:
		return BLUE_GHOST;
	case WHITE:
		return WHITE_GHOST;
	case EYES_ONLY:
		return GHOST_EYES_BASE + (sprite_direction(ghost) >> SPRITE_DIRECTION_SHIFT) - 1;
	default:
		return GHOST_BASE
			+ 8 * ((sprite_property(ghost) >> SPRITE_PROPERTY_SHIFT) - GHOST_PROPERTY_BASE)
			+ 2 * ((sprite_direction(ghost) >> SPRITE_DIRECTION_SHIFT) - 1);
	}
}

int get_food(int food)
{
	switch (sprite_property(food)) {
	case SMALL:
		return FOOD_BASE + 1;
	case BIG:
		return FOOD_BASE;
	default:
		return -1;
	}
}

int get_sprite(int sprite)
{
	switch (sprite_type(sprite)) {
	case PACMAN:
		return (sprite & ~SPRITE_INDEX_MASK) | get_pacman(sprite);
	case GHOST:
		return (sprite & ~SPRITE_INDEX_MASK) | get_ghost(sprite);
	case FOOD:
		return (sprite & ~SPRITE_INDEX_MASK) | get_food(sprite);
	case WALL:
		return (sprite & ~SPRITE_INDEX_MASK) | WALL_BASE;
	default:
		return -1;
	}
}

int map_get_sprite(int *map, int x, int y)
{
	return map[y * PACMAN_MAP_WIDTH + x];
}

int map_set_sprite(int *map, int x, int y, int sprite)
{
	map[y * PACMAN_MAP_WIDTH + x] = sprite;
}

int next_pacman(int pacman)
{
	if (sprite_index(pacman) == PACMAN_BASE) {
		return get_sprite(pacman);
	}
	if (pacman % 2 == 1) {
		return pacman + 1;
	} else {
		return (pacman & ~SPRITE_INDEX_MASK);
	}
}

int next_ghost(int ghost)
{
	if (ghost % 2 == 1) {
		return ghost + 1;
	} else {
		return ghost - 1;
	}
}

int next_sprite(int sprite)
{
	switch (sprite_type(sprite)) {
	case PACMAN:
		return next_pacman(sprite);
	case GHOST:
		return next_ghost(sprite);
	case FOOD:
	case WALL:
		return sprite;
	default:
		return -1;
	}
}

int animate_map(int *map)
{
	for (int y = 0; y < PACMAN_MAP_HEIGHT; ++y) {
		for (int x = 0; x < PACMAN_MAP_WIDTH; ++x) {
			map[y * PACMAN_MAP_WIDTH + x] = next_sprite(map[y * PACMAN_MAP_WIDTH + x]);
		}
	}
}

int random_sprite()
{
	return get_sprite(
			(rand() % SPRITE_TYPE_SIZE << SPRITE_TYPE_SHIFT)
		| (rand() % SPRITE_PROPERTY_SIZE << SPRITE_PROPERTY_SHIFT)
		| (rand() % SPRITE_DIRECTION_SIZE << SPRITE_DIRECTION_SHIFT));
}

void random_map(int *map)
{
	for (int y = 0; y < PACMAN_MAP_HEIGHT; ++y) {
		for (int x = 0; x < PACMAN_MAP_WIDTH; ++x) {
			map[y * PACMAN_MAP_WIDTH + x] = get_sprite(random_sprite());
		}
	}
}

void test_map(int *map)
{
	for (int y = 0; y < PACMAN_MAP_HEIGHT; ++y) {
		for (int x = 0; x < PACMAN_MAP_WIDTH; ++x) {
			map[y * PACMAN_MAP_WIDTH + x] = get_sprite(SMALL | FOOD);
		}
	}
	for (int x = 0; x < PACMAN_MAP_WIDTH; ++x) {
		map[x] = get_sprite(WALL);
		map[(PACMAN_MAP_HEIGHT - 1) * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	}
	for (int y = 0; y < PACMAN_MAP_HEIGHT; ++y) {
		map[y * PACMAN_MAP_WIDTH] = get_sprite(WALL);
		map[y * PACMAN_MAP_WIDTH + PACMAN_MAP_WIDTH - 1] = get_sprite(WALL);
	}
	for (int x = 17; x <= 22; ++x) {
		map[9 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
		map[12 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	}
	for (int y = 10; y <= 11; ++y) {
		map[y * PACMAN_MAP_WIDTH + 17] = get_sprite(WALL);
		map[y * PACMAN_MAP_WIDTH + 22] = get_sprite(WALL);
	}
	for (int x = 19; x <= 20; ++x)
		map[9 * PACMAN_MAP_WIDTH + x] = get_sprite(BACKGROUND);
	for (int x = 18; x <= 21; ++x) {
		map[10 * PACMAN_MAP_WIDTH + x] = get_sprite(BACKGROUND);
		map[11 * PACMAN_MAP_WIDTH + x] = get_sprite(BACKGROUND);
	}
	for (int y = 1; y <= 3; ++y) {
		map[y * PACMAN_MAP_WIDTH + 4] = get_sprite(WALL);
		map[y * PACMAN_MAP_WIDTH + 35] = get_sprite(WALL);
	}
	for (int x = 5; x <= 7; ++x)
		map[3 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int x = 11; x <= 17; ++x)
		map[3 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int x = 22; x <= 28; ++x)
		map[3 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int x = 32; x <= 34; ++x)
		map[3 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int x = 4; x <= 8; ++x)
		map[6 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int x = 14; x <= 25; ++x)
		map[6 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int x = 31; x <= 35; ++x)
		map[6 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int x = 4; x <= 6; ++x)
		map[7 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int x = 33; x <= 35; ++x)
		map[7 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int x = 4; x <= 5; ++x)
		map[8 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int x = 34; x <= 35; ++x)
		map[8 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int y = 9; y <= 10; ++y) {
		map[y * PACMAN_MAP_WIDTH + 4] = get_sprite(WALL);
		map[y * PACMAN_MAP_WIDTH + 35] = get_sprite(WALL);
	}
	for (int y = 11; y <= 16; ++y) {
		map[y * PACMAN_MAP_WIDTH + 9] = get_sprite(WALL);
		map[y * PACMAN_MAP_WIDTH + 30] = get_sprite(WALL);
	}
	for (int y = 11; y <= 15; ++y) {
		map[y * PACMAN_MAP_WIDTH + 12] = get_sprite(WALL);
		map[y * PACMAN_MAP_WIDTH + 27] = get_sprite(WALL);
	}
	for (int y = 13; y <= 15; ++y) {
		map[y * PACMAN_MAP_WIDTH + 11] = get_sprite(WALL);
		map[y * PACMAN_MAP_WIDTH + 13] = get_sprite(WALL);
		map[y * PACMAN_MAP_WIDTH + 26] = get_sprite(WALL);
		map[y * PACMAN_MAP_WIDTH + 28] = get_sprite(WALL);
	}
	for (int x = 10; x <= 11; ++x) 
		map[11 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int x = 28; x <= 29; ++x) 
		map[11 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int x = 4; x <= 8; ++x) 
		map[16 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int x = 31; x <= 35; ++x) 
		map[16 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int x = 12; x <= 14; ++x) 
		map[16 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int x = 25; x <= 27; ++x) 
		map[16 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int y = 17; y <= 18; ++y) {
		map[y * PACMAN_MAP_WIDTH + 15] = get_sprite(WALL);
		map[y * PACMAN_MAP_WIDTH + 24] = get_sprite(WALL);
	}
	for (int x = 3; x <= 7; ++x) 
		map[21 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int x = 32; x <= 36; ++x) 
		map[21 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	for (int y = 19; y <= 25; ++y) {
		map[y * PACMAN_MAP_WIDTH + 8] = get_sprite(WALL);
		map[y * PACMAN_MAP_WIDTH + 31] = get_sprite(WALL);
	}
	for (int y = 21; y <= 23; ++y) {
		map[y * PACMAN_MAP_WIDTH + 12] = get_sprite(WALL);
		map[y * PACMAN_MAP_WIDTH + 27] = get_sprite(WALL);
	}
	map[23 * PACMAN_MAP_WIDTH + 13] = get_sprite(WALL);
	map[23 * PACMAN_MAP_WIDTH + 26] = get_sprite(WALL);
	for (int y = 19; y <= 23; ++y) {
		map[y * PACMAN_MAP_WIDTH + 19] = get_sprite(WALL);
		map[y * PACMAN_MAP_WIDTH + 20] = get_sprite(WALL);
	}
	for (int x = 12; x <= 27; ++x) 
		map[24 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
	map[24 * PACMAN_MAP_WIDTH + 7] = get_sprite(WALL);
	map[24 * PACMAN_MAP_WIDTH + 32] = get_sprite(WALL);
	map[25 * PACMAN_MAP_WIDTH + 6] = get_sprite(WALL);
	map[25 * PACMAN_MAP_WIDTH + 33] = get_sprite(WALL);
	map[26 * PACMAN_MAP_WIDTH + 5] = get_sprite(WALL);
	map[26 * PACMAN_MAP_WIDTH + 34] = get_sprite(WALL);
	map[27 * PACMAN_MAP_WIDTH + 4] = get_sprite(WALL);
	map[27 * PACMAN_MAP_WIDTH + 35] = get_sprite(WALL);
}
