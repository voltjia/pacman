/*
 * spu.h
 *
 *  Created on: 2021Äê4ÔÂ28ÈÕ
 *      Author: user
 */

#ifndef SPU_H_
#define SPU_H_

#define SPU_MAP_WIDTH 40
#define SPU_MAP_HEIGHT 30

#define PAC_MAN_SPRITE_0              0
#define PAC_MAN_SPRITE_UP_1           1
#define PAC_MAN_SPRITE_UP_2           2
#define PAC_MAN_SPRITE_DOWN_1         3
#define PAC_MAN_SPRITE_DOWN_2         4
#define PAC_MAN_SPRITE_LEFT_1         5
#define PAC_MAN_SPRITE_LEFT_2         6
#define PAC_MAN_SPRITE_RIGHT_1        7
#define PAC_MAN_SPRITE_RIGHT_2        8
#define RED_GHOST_SPRITE_UP_1         9
#define RED_GHOST_SPRITE_UP_2        10
#define RED_GHOST_SPRITE_DOWN_1      11
#define RED_GHOST_SPRITE_DOWN_2      12
#define RED_GHOST_SPRITE_LEFT_1      13
#define RED_GHOST_SPRITE_LEFT_2      14
#define RED_GHOST_SPRITE_RIGHT_1     15
#define RED_GHOST_SPRITE_RIGHT_2     16
#define PINK_GHOST_SPRITE_UP_1       17
#define PINK_GHOST_SPRITE_UP_2       18
#define PINK_GHOST_SPRITE_DOWN_1     19
#define PINK_GHOST_SPRITE_DOWN_2     20
#define PINK_GHOST_SPRITE_LEFT_1     21
#define PINK_GHOST_SPRITE_LEFT_2     22
#define PINK_GHOST_SPRITE_RIGHT_1    23
#define PINK_GHOST_SPRITE_RIGHT_2    24
#define CYAN_GHOST_SPRITE_UP_1       25
#define CYAN_GHOST_SPRITE_UP_2       26
#define CYAN_GHOST_SPRITE_DOWN_1     27
#define CYAN_GHOST_SPRITE_DOWN_2     28
#define CYAN_GHOST_SPRITE_LEFT_1     29
#define CYAN_GHOST_SPRITE_LEFT_2     30
#define CYAN_GHOST_SPRITE_RIGHT_1    31
#define CYAN_GHOST_SPRITE_RIGHT_2    32
#define STEEL_GHOST_SPRITE_UP_1      33
#define STEEL_GHOST_SPRITE_UP_2      34
#define STEEL_GHOST_SPRITE_DOWN_1    35
#define STEEL_GHOST_SPRITE_DOWN_2    36
#define STEEL_GHOST_SPRITE_LEFT_1    37
#define STEEL_GHOST_SPRITE_LEFT_2    38
#define STEEL_GHOST_SPRITE_RIGHT_1   39
#define STEEL_GHOST_SPRITE_RIGHT_2   40
#define BLUE_GHOST_SPRITE_1          41
#define BLUE_GHOST_SPRITE_2          42
#define WHITE_GHOST_SPRITE_1         43
#define WHITE_GHOST_SPRITE_2         44
#define GHOST_EYES_SPRITE_UP         45
#define GHOST_EYES_SPRITE_DOWN       46
#define GHOST_EYES_SPRITE_LEFT       47
#define GHOST_EYES_SPRITE_RIGHT      48
#define BIG_FOOD_SPRITE              49
#define SMALL_FOOD_SPRITE            50
#define HORIZONTAL_WALL_SPRITE       51
#define VERTICAL_WALL_SPRITE         52
#define CROSS_WALL_SPRITE            53
#define T_WALL_SPRITE_UP             54
#define T_WALL_SPRITE_DOWN           55
#define T_WALL_SPRITE_LEFT           56
#define T_WALL_SPRITE_RIGHT          57
#define TOP_LEFT_WALL_SPRITE         58
#define TOP_RIGHT_WALL_SPRITE        59
#define BOTTOM_LEFT_WALL_SPRITE      60
#define BOTTOM_RIGHT_WALL_SPRITE     61
#define PAC_MAN_GAME_SPRITE_COUNT    62

void spu_control(int instruction);
void spu_show_all_sprites();
void spu_show_all_walls();
void spu_set_sprite(int x, int y, int index);
void spu_set_map(int *map);
void spu_animate(int *map);

#endif /* SPU_H_ */
