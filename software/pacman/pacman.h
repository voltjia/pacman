/*
 * pacman.h
 *
 *  Created on: 2021��4��30��
 *      Author: user
 */

#ifndef PACMAN_H_
#define PACMAN_H_

#include <stdlib.h>

#define PACMAN_MAP_WIDTH 40
#define PACMAN_MAP_HEIGHT 30

#define SPRITE_INDEX_SHIFT 0
#define SPRITE_TYPE_SHIFT 8
#define SPRITE_PROPERTY_SHIFT 12
#define SPRITE_DIRECTION_SHIFT 16

#define SPRITE_INDEX_MASK 0x000000FF
#define SPRITE_TYPE_MASK 0x00000F00
#define SPRITE_PROPERTY_MASK 0x0000F000
#define SPRITE_DIRECTION_MASK 0x000F0000

#define PACMAN (0 << SPRITE_TYPE_SHIFT)
#define GHOST (1 << SPRITE_TYPE_SHIFT)
#define FOOD (2 << SPRITE_TYPE_SHIFT)
#define WALL (3 << SPRITE_TYPE_SHIFT)
#define SPRITE_TYPE_SIZE 4

#define BACKGROUND -1
#define BLACK (0 << SPRITE_PROPERTY_SHIFT)
#define WHITE (1 << SPRITE_PROPERTY_SHIFT)
#define YELLOW (2 << SPRITE_PROPERTY_SHIFT)
#define RED (3 << SPRITE_PROPERTY_SHIFT)
#define PINK (4 << SPRITE_PROPERTY_SHIFT)
#define CYAN (5 << SPRITE_PROPERTY_SHIFT)
#define TEAL (6 << SPRITE_PROPERTY_SHIFT)
#define BLUE (7 << SPRITE_PROPERTY_SHIFT)
#define EYES_ONLY (13 << SPRITE_PROPERTY_SHIFT)
#define SMALL (14 << SPRITE_PROPERTY_SHIFT)
#define BIG (15 << SPRITE_PROPERTY_SHIFT)
#define SPRITE_PROPERTY_SIZE 16

#define IDLE (0 << SPRITE_DIRECTION_SHIFT)
#define UP (1 << SPRITE_DIRECTION_SHIFT)
#define DOWN (2 << SPRITE_DIRECTION_SHIFT)
#define LEFT (3 << SPRITE_DIRECTION_SHIFT)
#define RIGHT (4 << SPRITE_DIRECTION_SHIFT)
#define SPRITE_DIRECTION_SIZE 5

#define GHOST_PROPERTY_BASE 3
#define PACMAN_BASE 0
#define GHOST_BASE 9
#define BLUE_GHOST 41
#define WHITE_GHOST 43
#define GHOST_EYES_BASE 45
#define FOOD_BASE 49
#define WALL_BASE 51
#define NUMBER_BASE 52
#define ALPHABET_S 62
#define ALPHABET_C 63
#define ALPHABET_O 64
#define ALPHABET_R 65
#define ALPHABET_E 66
#define ALPHABET_COLON 67
#define SPRITE_COUNT 68

void spawn_all_sprites(int *map);
int sprite_index(int sprite);
int sprite_type(int sprite);
int sprite_direction(int sprite);
int sprite_property(int sprite);
int get_pacman(int pacman);
int get_ghost(int ghost);
int get_sprite(int sprite);
int map_get_sprite(int *map, int x, int y);
int map_set_sprite(int *map, int x, int y, int sprite);
int next_sprite(int sprite);
int animate_map(int *map);
int random_sprite();
void random_map(int *map);
void test_map(int *map);
void game_over(int *map);
int can_walk(int *map, int x, int y);
void show_score(int *map, int score);

#endif /* PACMAN_H_ */
