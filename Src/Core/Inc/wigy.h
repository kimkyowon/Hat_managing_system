/*
 * wigy.h
 *
 *  Created on: Jun 1, 2024
 *      Author: KYO
 */

#ifndef INC_WIGY_H_
#define INC_WIGY_H_

#include "main.h"


typedef enum {
	none,pink,sky,blue,green,red
}color_t;

typedef enum {
	off,on
}turn;

typedef enum L{
	default_mode, L_mode1, L_mode2, L_mode3, L_mode4, L_mode5
}L_mode_t;

typedef enum System{
	Sys_default,Sys_mode1,Sys_mode2,Sys_All_off
}Sys_mode_t;

typedef struct Switch{
	int push_cnt;
}SW_t;

typedef struct modes{
	Sys_mode_t sysmode;
	L_mode_t lmode;
}mode_t;
typedef struct MZR_WIGY{

	color_t rgb_color;

	turn irled;
	turn uvled;
	turn uvcled;
	turn fan;

	SW_t L;			// SW1
	SW_t System;	// SW2

	mode_t mode;

}WIGY_t;

void Initialize_wigy(WIGY_t *instance);
void is_pushed_L_sw(WIGY_t *wigy);
void is_pushed_System_sw(WIGY_t *wigy);
void lights_up_one(color_t color, turn on_off);
void process(WIGY_t *wigy);



#endif /* INC_WIGY_H_ */
