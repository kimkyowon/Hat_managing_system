/*
 * wigy.h
 *
 *  Created on: Jun 1, 2024
 *      Author: KYO
 */

#ifndef INC_WIGY_H_
#define INC_WIGY_H_

typedef enum {
	none,red,green,blue,sky,pink
}color;

typedef enum {
	off,on
}turn;

typedef enum System{
	L_default,L_mode1,L_mode2,L_All_off
}Sys_mode_t;

typedef enum L{
	default_mode,mood,low_salgyun, high_salgyun, mid_salgyun, one_high_salgyun,remove_func
}L_mode_t;

typedef struct Switch{
	int push_cnt;
}SW_t;

typdef struct modes{
	Sys_mode_t sysmode;
	L_mode_t lmode;
}mode_t;
typedef struct MZR_WIGY{

	color rgb_color;

	turn irled;
	turn uvled;
	turn uvcled;
	turn fan;

	SW_t System;
	SW_t L;

	mode_t mode;
}WIGY_t;

void Initialize_wigy(WIGY_t *instance);
void update_mode(WIGY_t *wigy);
void process(WIGY_t *wigy);


#endif /* INC_WIGY_H_ */
