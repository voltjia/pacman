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
	default:
		return sprite;
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

void connect_walls(int *walls, int src, int dst)
{
	for (int y = 0; y < PACMAN_MAP_HEIGHT; ++y) {
		for (int x = 0; x < PACMAN_MAP_WIDTH; ++x) {
			if (walls[y * PACMAN_MAP_WIDTH + x] == src) {
				walls[y * PACMAN_MAP_WIDTH + x] = dst;
			}
		}
	}
}

void random_walls(int *map)
{
	int walls[1200] = {0};
	int index = 1;
	for (int i = 0; i < 1024; ++i) {
		int connected[1200] = {0};
		int x = rand() % (PACMAN_MAP_WIDTH - 2) + 2;
		int y = rand() % (PACMAN_MAP_HEIGHT - 2) + 2;
		if (walls[y * PACMAN_MAP_WIDTH + x] != 0) {
			continue;
		}
		int is_closed = 0;
		int count = 0;
		int connected_indices[8] = {0};
		for (int j = y - 1; j < y + 2; ++j) {
			for (int i = x - 1; i < x + 2; ++i) {
				if (walls[j * PACMAN_MAP_WIDTH + i] != 0) {
					if (connected[walls[j * PACMAN_MAP_WIDTH + i]]) {
						is_closed = 1;
						break;
					}
					connected[walls[j * PACMAN_MAP_WIDTH + i]] = 1;
					connected_indices[count++] = walls[j * PACMAN_MAP_WIDTH + i];
				}
			}
			if (is_closed) {
				break;
			}
		}
		if (count == 0) {
			walls[y * PACMAN_MAP_WIDTH + x] = index++;
			continue;
		}
		if (is_closed) {
			continue;
		}
		for (int i = 1; i < count; ++i) {
			connect_walls(walls, connected_indices[i], connected_indices[0]);
		}
	}

	for (int y = 0; y < PACMAN_MAP_HEIGHT; ++y) {
		for (int x = 0; x < PACMAN_MAP_WIDTH; ++x) {
			if (walls[y * PACMAN_MAP_WIDTH + x])
				map_set_sprite(map, x, y, get_sprite(WALL));
		}
	}
}

void random_map(int *map)
{
	for (int y = 0; y < PACMAN_MAP_HEIGHT; ++y) {
		for (int x = 0; x < PACMAN_MAP_WIDTH; ++x) {
			map[y * PACMAN_MAP_WIDTH + x] = get_sprite(random_sprite());
		}
	}
}

void main_map(int *map)
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
	map[PACMAN_MAP_WIDTH + 14] = get_sprite(WALL);
	map[PACMAN_MAP_WIDTH + 25] = get_sprite(WALL);
	for (int x = 14; x <= 25; ++x)
		map[2 * PACMAN_MAP_WIDTH + x] = get_sprite(WALL);
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
	map[14 * PACMAN_MAP_WIDTH + 12] = get_sprite(BACKGROUND);
	map[14 * PACMAN_MAP_WIDTH + 27] = get_sprite(BACKGROUND);
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

void game_over(int *map)
{
	for (int y = 0; y < PACMAN_MAP_HEIGHT; ++y) {
		for (int x = 0; x < PACMAN_MAP_WIDTH; ++x) {
			map[y * PACMAN_MAP_WIDTH + x] = get_sprite(BACKGROUND);
		}
	}
	for (int x = 4; x <= 6; ++x)
		map[4 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
	map[4 * PACMAN_MAP_WIDTH + 14] = get_sprite(PACMAN);
	for (int x = 32; x <= 36; ++x) {
		map[4 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
		map[8 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
		map[12 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
	}
	map[5 * PACMAN_MAP_WIDTH + 3] = get_sprite(PACMAN);
	for (int y = 5; y <= 6; ++y) {
		map[y * PACMAN_MAP_WIDTH + 7] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 13] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 15] = get_sprite(PACMAN);
	}
	for (int y = 6; y <= 10; ++y)
		map[y * PACMAN_MAP_WIDTH + 2] = get_sprite(PACMAN);
	for (int y = 4; y <= 12; ++y) {
		map[y * PACMAN_MAP_WIDTH + 20] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 27] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 31] = get_sprite(PACMAN);
	}
	map[6 * PACMAN_MAP_WIDTH + 21] = get_sprite(PACMAN);
	map[6 * PACMAN_MAP_WIDTH + 26] = get_sprite(PACMAN);
	for (int y = 7; y <= 9; ++y) {
		map[y * PACMAN_MAP_WIDTH + 12] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 16] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 22] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 25] = get_sprite(PACMAN);
	}
	for (int x = 6; x <= 8; ++x)
		map[9 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
	for (int x = 13; x <= 15; ++x)
		map[9 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
	for (int y = 10; y <= 11; ++y) {
		map[y * PACMAN_MAP_WIDTH + 7] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 23] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 24] = get_sprite(PACMAN);
	}
	for (int y = 10; y <= 12; ++y) {
		map[y * PACMAN_MAP_WIDTH + 11] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 17] = get_sprite(PACMAN);
	}
	map[11 * PACMAN_MAP_WIDTH + 3] = get_sprite(PACMAN);
	for (int x = 4; x <= 6; ++x)
		map[12 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
	for (int x = 4; x <= 6; ++x)
		map[18 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
	for (int x = 22; x <= 26; ++x) {
		map[18 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
		map[22 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
		map[26 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
	}
	for (int x = 31; x <= 34; ++x)
		map[18 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
	for (int x = 31; x <= 35; ++x)
		map[22 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
	for (int y = 18; y <= 26; ++y)
		map[y * PACMAN_MAP_WIDTH + 21] = get_sprite(PACMAN);
	for (int y = 18; y <= 27; ++y)
		map[y * PACMAN_MAP_WIDTH + 30] = get_sprite(PACMAN);
	for (int y = 18; y <= 20; ++y) {
		map[y * PACMAN_MAP_WIDTH + 11] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 17] = get_sprite(PACMAN);
	}
	for (int y = 21; y <= 23; ++y) {
		map[y * PACMAN_MAP_WIDTH + 12] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 16] = get_sprite(PACMAN);
	}
	for (int y = 24; y <= 25; ++y) {
		map[y * PACMAN_MAP_WIDTH + 13] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 15] = get_sprite(PACMAN);
	}
	map[26 * PACMAN_MAP_WIDTH + 14] = get_sprite(PACMAN);
	map[19 * PACMAN_MAP_WIDTH + 3] = get_sprite(PACMAN);
	map[19 * PACMAN_MAP_WIDTH + 7] = get_sprite(PACMAN);
	map[19 * PACMAN_MAP_WIDTH + 35] = get_sprite(PACMAN);
	for (int y = 20; y <= 21; ++y)
		map[y * PACMAN_MAP_WIDTH + 36] = get_sprite(PACMAN);
	for (int y = 20; y <= 24; ++y) {
		map[y * PACMAN_MAP_WIDTH + 2] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 8] = get_sprite(PACMAN);
	}
	map[25 * PACMAN_MAP_WIDTH + 3] = get_sprite(PACMAN);
	map[25 * PACMAN_MAP_WIDTH + 7] = get_sprite(PACMAN);
	for (int x = 4; x <= 6; ++x)
		map[26 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
	map[23 * PACMAN_MAP_WIDTH + 32] = get_sprite(PACMAN);
	map[24 * PACMAN_MAP_WIDTH + 33] = get_sprite(PACMAN);
	map[25 * PACMAN_MAP_WIDTH + 34] = get_sprite(PACMAN);
	map[26 * PACMAN_MAP_WIDTH + 35] = get_sprite(PACMAN);
	map[27 * PACMAN_MAP_WIDTH + 36] = get_sprite(PACMAN);
}

void you_win(int *map) {
	for (int y = 0; y < PACMAN_MAP_HEIGHT; ++y) {
		for (int x = 0; x < PACMAN_MAP_WIDTH; ++x) {
			map[y * PACMAN_MAP_WIDTH + x] = get_sprite(BACKGROUND);
		}
	}
	map[5 * PACMAN_MAP_WIDTH + 4] = get_sprite(PACMAN);
	map[6 * PACMAN_MAP_WIDTH + 5] = get_sprite(PACMAN);
	map[7 * PACMAN_MAP_WIDTH + 6] = get_sprite(PACMAN);
	map[5 * PACMAN_MAP_WIDTH + 12] = get_sprite(PACMAN);
	map[6 * PACMAN_MAP_WIDTH + 11] = get_sprite(PACMAN);
	map[7 * PACMAN_MAP_WIDTH + 10] = get_sprite(PACMAN);
	for (int x = 7; x <= 9; ++x)
		map[8 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
	for (int y = 9; y <= 13; ++y)
		map[y * PACMAN_MAP_WIDTH + 8] = get_sprite(PACMAN);
	for (int x = 18; x <= 20; ++x) {
		map[5 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
		map[13 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
	}
	for (int y = 5; y <= 11; ++y) {
		map[y * PACMAN_MAP_WIDTH + 26] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 33] = get_sprite(PACMAN);
	}
	for (int y = 7; y <= 11; ++y) {
		map[y * PACMAN_MAP_WIDTH + 16] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 22] = get_sprite(PACMAN);
	}
	map[6 * PACMAN_MAP_WIDTH + 17] = get_sprite(PACMAN);
	map[6 * PACMAN_MAP_WIDTH + 21] = get_sprite(PACMAN);
	map[12 * PACMAN_MAP_WIDTH + 17] = get_sprite(PACMAN);
	map[12 * PACMAN_MAP_WIDTH + 21] = get_sprite(PACMAN);
	for (int y = 11; y <= 12; ++y) {
		map[y * PACMAN_MAP_WIDTH + 27] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 32] = get_sprite(PACMAN);
	}
	for (int y = 12; y <= 13; ++y) {
		map[y * PACMAN_MAP_WIDTH + 28] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 31] = get_sprite(PACMAN);
	}
	for (int x = 29; x <= 30; ++x)
		map[13 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
	for (int y = 17; y <= 18; ++y) {
		map[y * PACMAN_MAP_WIDTH + 3] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 13] = get_sprite(PACMAN);
	}
	for (int y = 19; y <= 21; ++y) {
		map[y * PACMAN_MAP_WIDTH + 4] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 8] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 12] = get_sprite(PACMAN);
	}
	for (int y = 22; y <= 24; ++y) {
		map[y * PACMAN_MAP_WIDTH + 5] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 7] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 9] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 11] = get_sprite(PACMAN);
	}
	map[25 * PACMAN_MAP_WIDTH + 6] = get_sprite(PACMAN);
	map[25 * PACMAN_MAP_WIDTH + 10] = get_sprite(PACMAN);
	for (int x = 16; x <= 22; ++x) {
		map[17 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
		map[25 * PACMAN_MAP_WIDTH + x] = get_sprite(PACMAN);
	}
	for (int y = 18; y <= 24; ++y)
		map[y * PACMAN_MAP_WIDTH + 19] = get_sprite(PACMAN);
	for (int y = 17; y <= 25; ++y) {
		map[y * PACMAN_MAP_WIDTH + 27] = get_sprite(PACMAN);
		map[y * PACMAN_MAP_WIDTH + 34] = get_sprite(PACMAN);
	}
	map[18 * PACMAN_MAP_WIDTH + 28] = get_sprite(PACMAN);
	map[19 * PACMAN_MAP_WIDTH + 29] = get_sprite(PACMAN);
	map[20 * PACMAN_MAP_WIDTH + 29] = get_sprite(PACMAN);
	map[21 * PACMAN_MAP_WIDTH + 30] = get_sprite(PACMAN);
	map[21 * PACMAN_MAP_WIDTH + 31] = get_sprite(PACMAN);
	map[22 * PACMAN_MAP_WIDTH + 32] = get_sprite(PACMAN);
	map[23 * PACMAN_MAP_WIDTH + 32] = get_sprite(PACMAN);
	map[24 * PACMAN_MAP_WIDTH + 33] = get_sprite(PACMAN);
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

void show_score(int *map, int score)
{
	for (int i = 0; i < 6; ++i) {
		map[PACMAN_MAP_WIDTH + 15 + i] = 62 + i;
	}
	map[PACMAN_MAP_WIDTH + 15 + 6] = NUMBER_BASE + score / 1000;
	map[PACMAN_MAP_WIDTH + 15 + 7] = NUMBER_BASE + (score / 100) % 10;
	map[PACMAN_MAP_WIDTH + 15 + 8] = NUMBER_BASE + (score / 10) % 10;
	map[PACMAN_MAP_WIDTH + 15 + 9] = NUMBER_BASE + score % 10;
}
