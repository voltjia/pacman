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

void spu_control(int instruction);
void spu_set_sprite(int x, int y, int index);
void spu_set_map(int *map);

#endif /* SPU_H_ */
