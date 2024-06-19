/*
 * wigy.h
 *
 *  Created on: Jun 1, 2024
 *      Author: KYO
 */

#ifndef INC_WIGY_H_
#define INC_WIGY_H_

#include "main.h"
#include "switch.h"

typedef struct _RGB
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
} RGB_t;

#define RGB(RED, GRN, BLU)  \
    {                       \
        .R = RED,           \
        .G = GRN,           \
        .B = BLU            \
    }

#define RGB_RED 		RGB(255,0,0)
#define RGB_GRN 		RGB(0,255,0)
#define RGB_BLU 		RGB(0,0,255)
#define RGB_CYAN 		RGB(0,255,255)
#define RGB_MAGENTA		RGB(255,0,255)
#define RGB_YELLOW 		RGB(255,255,0)
#define RGB_BLACK 		RGB(0,0,0)
#define RGB_WHITE 		RGB(255,255,255)


// typedef enum {
// 	none,pink,sky,blue,green,red
// }color_t;

typedef enum {
	off,on
}turn;


typedef enum _STATE_T //System is Moore Statemachine
{
	S_Sys_mode0, 	//Initial State
	S_Sys_mode1,	
	S_L_mode0,		//Sys mode 2 = L mode 0, All off
	S_L_mode1,
	S_L_mode2,
	S_L_mode3,
	S_L_mode4,
	S_L_mode5,
} State_t;

// typedef enum L
// {
// 	L_mode0,
// 	L_mode1,
// 	L_mode2,
// 	L_mode3,
// 	L_mode4,
// 	L_mode5,
// 	remove_funcs
// } L_mode_t;


// typedef struct modes
// {
// 	Sys_mode_t sysmode;
// 	L_mode_t lmode;
// } mode_t;
typedef struct MZR_WIGY
{

	// color_t rgb_color;

	// turn irled;
	// turn uvled;
	// turn uvcled;
	// turn fan;

	// SW_t L;		// SW1
	// SW_t System;	// SW2

	bool LEDSwPressedFlag;
	bool SystemSwPressedFlag;

	// mode_t mode;

	State_t state;

} WIGY_t;

void Init_wigy(WIGY_t *instance);
// void is_pushed_L_sw(WIGY_t *wigy);
// void is_pushed_System_sw(WIGY_t *wigy);
void WIGY_NotifyLEDSwPressed(WIGY_t *);	   // When Switch Pressed
void WIGY_NotifySystemSwPressed(WIGY_t *); // When Switch Pressed
//void lights_up_one(color_t color, turn on_off);
void process(WIGY_t *wigy);



#endif /* INC_WIGY_H_ */
