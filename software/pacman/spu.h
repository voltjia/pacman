/*
 * spu.h
 *
 *  Created on: 2021Äê4ÔÂ28ÈÕ
 *      Author: user
 */

#ifndef SPU_H_
#define SPU_H_

#define SPU_SET_PALLETE 0x10000000
#define SPU_SET_SPRITE 0x20000000
#define SPU_SET_MAP 0x30000000

void spu_control(int instruction);
void spu_set_sprite(int index, int *sprite);
void spu_set_map(int x, int y, int index);

#endif /* SPU_H_ */
