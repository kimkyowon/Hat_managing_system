/*
 * wigy.c
 *
 *  Created on: Jun 1, 2024
 *      Author: KYO
 */

#include "wigy.h"

// PV _ private value for user
//extern Ptimer_t led_blink;


// static functions prototypes
//static void led_off_all();
static void Ctrl_led(RGB_t _rgb);
static void Ctrl_IR_Led(turn blank);
static void Ctrl_UVA_Led(turn blank);
static void Ctrl_UVC_Led(turn blank);
static void Ctrl_EXTFAN(turn blank);
static void Ctrl_Heater(turn blank);

static void 	WIGY_ResetPressedFlags	(WIGY_t *);
static void 	WIGY_UpdateOutputs		(WIGY_t *);
static State_t 	WIGY_Eval_NextState		(WIGY_t *);
static void 	WIGY_UpdateOutputs		(WIGY_t *);
//static void process_led_blink(Ptimer_t* process,color_t color);

//static void change_system_mode(Sys_mode_t sysmode);
//static void change_led_mode(L_mode_t lmode);

// For initializing struct type wigy
void Init_wigy(WIGY_t *_instance)
{
	// _instance->L 				= SW1;
	// _instance->System 			= SW2;
	// _instance->fan				= 0;
	// _instance->irled			= 0;
	// _instance->rgb_color		= 0;
	// _instance->uvcled 			= 0;
	// _instance->uvled			= 0;
	// _instance->mode.lmode		= 0;
	// _instance->mode.sysmode		= 0;
	_instance->LEDSwPressedFlag 	= false;
	_instance->SystemSwPressedFlag 	= false;
	_instance->state 				= S_L_mode0; //Initial State
	WIGY_UpdateOutputs(_instance);
}

void process(WIGY_t *wigy){ //Process Moore Statemachine
	// is_pushed_L_sw(wigy);
	// is_pushed_System_sw(wigy);
	const bool Sw_LED = wigy->LEDSwPressedFlag;
	const bool Sw_Mode = wigy->SystemSwPressedFlag;

	if (Sw_LED || Sw_Mode) //Implies State Transition
	{
		wigy->state = WIGY_Eval_NextState(wigy);
		WIGY_UpdateOutputs(wigy);

		WIGY_ResetPressedFlags(wigy);
	}
	//read_state(wigy);	//For Debug
}

void WIGY_NotifyLEDSwPressed(WIGY_t *wigy)
{
	wigy->LEDSwPressedFlag = true;
}
void WIGY_NotifySystemSwPressed(WIGY_t *wigy)
{
	wigy->SystemSwPressedFlag = true;
}



// void is_pushed_L_sw(WIGY_t *wigy){
// 	if(wigy->L.push_cnt != wigy->mode.lmode){
// 		wigy->mode.lmode = wigy->L.push_cnt;
// 		change_led_mode(wigy->mode.lmode);
// 	}
// }

// void is_pushed_System_sw(WIGY_t *wigy){
// 	if(wigy->System.push_cnt != wigy->mode.sysmode){
// 		wigy->mode.sysmode = wigy->System.push_cnt;
// 		change_system_mode(wigy->mode.sysmode);
// 	}
// }

//  static void read_state(WIGY_t *wigy){
//  	wigy->irled  = HAL_GPIO_ReadPin(GPIOB,LEDD1012_G_Pin);
//  	wigy->uvled  = HAL_GPIO_ReadPin(GPIOC, UVLED_G_Pin);
//  	wigy->uvcled = HAL_GPIO_ReadPin(GPIOB, LED12_G_Pin);
//  	wigy->fan	 = HAL_GPIO_ReadPin(GPIOA,EXTFAN_G_Pin);
//  }

static void Ctrl_led(RGB_t _rgb){
	//led_off_all();

	HAL_GPIO_WritePin(RGB_Red_G_GPIO_Port	, RGB_Red_G_Pin		, (bool)_rgb.R);
	HAL_GPIO_WritePin(RGB_Green_G_GPIO_Port	, RGB_Green_G_Pin	, (bool)_rgb.G);
	HAL_GPIO_WritePin(RGB_Blue_G_GPIO_Port	, RGB_Blue_G_Pin	, (bool)_rgb.B);

	// }
	// switch(color){
	// case pink:
	// 	HAL_GPIO_WritePin(GPIOA,RGB_Blue_G_Pin,on_off);
	// 	HAL_GPIO_WritePin(GPIOB,RGB_Red_G_Pin,on_off);
	// 	break;
	// case sky:
	// 	HAL_GPIO_WritePin(GPIOA,RGB_Blue_G_Pin,on_off);
	// 	HAL_GPIO_WritePin(GPIOA,RGB_Green_G_Pin,on_off);
	// 	break;
	// case blue:
	// 	HAL_GPIO_WritePin(GPIOA,RGB_Blue_G_Pin,on_off);
	// 	break;
	// case green:
	// 	HAL_GPIO_WritePin(GPIOA,RGB_Green_G_Pin,on_off);
	// 	break;
	// case red:
	// 	HAL_GPIO_WritePin(GPIOB,RGB_Red_G_Pin,on_off);
	// 	break;
	// default:
	// 	break;
	// }
}

static void WIGY_ResetPressedFlags(WIGY_t *wigy)
{
	wigy->LEDSwPressedFlag 		= false;
	wigy->SystemSwPressedFlag 	= false;
}

static State_t WIGY_Eval_NextState(WIGY_t *wigy)
{
	State_t next = wigy->state;

	const bool Sw_LED = wigy->LEDSwPressedFlag;
	const bool Sw_Mode = wigy->SystemSwPressedFlag;

	if((Sw_LED || Sw_Mode) == 0) return S_Sys_mode0; //WHAT??

	switch (wigy->state)
	{
	case S_Sys_mode0:
		if(Sw_Mode) next = S_Sys_mode1;
		//if(Sw_LED) ret = ;
		break;
	case S_Sys_mode1:
		if(Sw_Mode) next = S_L_mode0;
		//if(Sw_LED) ret = ;
		break;
	case S_L_mode0:
		if(Sw_Mode) next = S_Sys_mode0;
		if(Sw_LED) next = S_L_mode1;
		break;
	case S_L_mode1:
		if(Sw_Mode) next = S_Sys_mode0;
		if(Sw_LED) next = S_L_mode2;
		break;
	case S_L_mode2:
		if(Sw_Mode) next = S_Sys_mode0;
		if(Sw_LED) next = S_L_mode3;
		break;
	case S_L_mode3:
		if(Sw_Mode) next = S_Sys_mode0;
		if(Sw_LED) next = S_L_mode4;
		break;
	case S_L_mode4:
		if(Sw_Mode) next = S_Sys_mode0;
		if(Sw_LED) next = S_L_mode5;
		break;
	case S_L_mode5:
		if(Sw_Mode) next = S_Sys_mode0;
		if(Sw_LED) next = S_L_mode0;
		break;
	}

	return next;
}



static void WIGY_UpdateOutputs(WIGY_t *wigy)
{
	switch (wigy->state)
	{
	case S_Sys_mode0:
	{
		RGB_t rgb = RGB_RED;
		Ctrl_led(rgb);
	}
		Ctrl_IR_Led(on);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(on);
		Ctrl_EXTFAN(off);
		Ctrl_Heater(on);
		break;
	case S_Sys_mode1:
	{
		RGB_t rgb = RGB_RED;
		Ctrl_led(rgb);
	}
		Ctrl_IR_Led(on);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(on);
		Ctrl_EXTFAN(on);
		Ctrl_Heater(on);
		break;
	case S_L_mode0:
	{
		RGB_t rgb = RGB_BLACK;
		Ctrl_led(rgb);
	}
		Ctrl_IR_Led(off);
		Ctrl_UVA_Led(off);
		Ctrl_UVC_Led(off);
		Ctrl_EXTFAN(off);
		Ctrl_Heater(off);
		break;
	case S_L_mode1:
	{
		RGB_t rgb = RGB_WHITE;
		Ctrl_led(rgb);
	}
		Ctrl_IR_Led(off);
		Ctrl_UVA_Led(off);
		Ctrl_UVC_Led(off);
		Ctrl_EXTFAN(off);
		Ctrl_Heater(off);
		break;
	case S_L_mode2:
	{
		RGB_t rgb = RGB_CYAN;
		Ctrl_led(rgb);
	}
		Ctrl_IR_Led(off);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(off);
		Ctrl_EXTFAN(off);
		Ctrl_Heater(off);
		break;
	case S_L_mode3:
	{
		RGB_t rgb = RGB_BLU;
		Ctrl_led(rgb);
	}
		Ctrl_IR_Led(off);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(on);
		Ctrl_EXTFAN(off);
		Ctrl_Heater(off);
		break;
	case S_L_mode4:
	{
		RGB_t rgb = RGB_GRN;
		Ctrl_led(rgb);
	}
		Ctrl_IR_Led(off);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(on);
		Ctrl_EXTFAN(off);
		Ctrl_Heater(off);
		break;
	case S_L_mode5:
	{
		RGB_t rgb = RGB_MAGENTA;
		Ctrl_led(rgb);
	}
		Ctrl_IR_Led(on);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(on);
		Ctrl_EXTFAN(off);
		Ctrl_Heater(off);
		break;
	}
}

// static void change_system_mode(Sys_mode_t sysmode){
// 	switch(sysmode){	//Sys_default,Sys_mode1,Sys_mode2,Sys_All_off
// 	case Sys_default:
// 		//do nothing
// 		break;
// 	case Sys_mode1:
// 		Ctrl_led(red,on);
// 		Ctrl_IR_Led(on);
// 		Ctrl_UVA_Led(on);
// 		Ctrl_UVC_Led(on);
// 		Ctrl_EXTFAN(off);
// 		break;
// 	case Sys_mode2:
// 		Ctrl_led(red,on);
// 		Ctrl_IR_Led(on);
// 		Ctrl_UVA_Led(on);
// 		Ctrl_UVC_Led(on);
// 		Ctrl_EXTFAN(on);
// 		Ctrl_Heater(on);
// 		break;
// 	case Sys_All_off:
// 		Ctrl_led(none,on);
// 		Ctrl_IR_Led(off);
// 		Ctrl_UVA_Led(off);
// 		Ctrl_UVC_Led(off);
// 		Ctrl_EXTFAN(off);
// 		Ctrl_Heater(off);
// 	default:
// 		break;
// 	}
// }
// //default_mode,mood,low_salgyun, high_salgyun, mid_salgyun, one_high_salgyun,remove_func
// static void change_led_mode(L_mode_t lmode){
// 	switch(lmode){
// 	case L_mode1:	//mood
// 		Ctrl_led(red,on);
// 		break;

// 	case L_mode2:	//low_salgyun
// 		Ctrl_led(sky,on);
// 		Ctrl_UVA_Led(on);
// 		break;

// 	case L_mode3:	//high_salgyun
// 		Ctrl_led(blue,on);
// 		Ctrl_UVA_Led(on);
// 		Ctrl_UVC_Led(on);
// 		break;

// 	case L_mode4:	//mid_salgyun
// 		Ctrl_led(green,on);
// 		Ctrl_UVA_Led(on);
// 		Ctrl_UVC_Led(on);
// 		break;

// 	case L_mode5:	//one_high_salgyun
// 		Ctrl_led(pink,on);
// 		Ctrl_UVA_Led(on);
// 		Ctrl_UVC_Led(on);
// 		Ctrl_IR_Led(on);
// 		break;
// 	case remove_funcs:	//remove_func
// 		led_off_all();
// 		Ctrl_UVA_Led(off);
// 		Ctrl_UVC_Led(off);
// 		Ctrl_IR_Led(off);
// 		//process_led_blink(&led_blink, pink);
// 		break;
// 	default:
// 		break;
// 	}
// }
// Ctrl function (GPIO)
// static void led_off_all(){	//temporary all gpio
// 	HAL_GPIO_WritePin(GPIOA, RGB_Green_G_Pin|RGB_Blue_G_Pin, GPIO_PIN_RESET);
// 	HAL_GPIO_WritePin(GPIOB, RGB_Red_G_Pin, GPIO_PIN_RESET);
// }
static void Ctrl_IR_Led(turn blank){
	HAL_GPIO_WritePin(GPIOB,LEDD1012_G_Pin, blank);
}

static void Ctrl_UVA_Led(turn blank)
{
	HAL_GPIO_WritePin(GPIOB, LED12_G_Pin, blank);
}

static void Ctrl_UVC_Led(turn blank)
{
	HAL_GPIO_WritePin(GPIOC, UVLED_G_Pin, blank);
}

static void Ctrl_EXTFAN(turn blank){
	HAL_GPIO_WritePin(GPIOA, EXTFAN_G_Pin, blank);
}

static void Ctrl_Heater(turn blank){
	HAL_GPIO_WritePin(GPIOC, Heater_G_Pin, blank);
}

/*
static void process_led_blink(Ptimer_t* process,color_t color){
	if(process->do_flag == true){
		Ctrl_led(color,process->current_cnt%2);	//set state with current cnt, cause blink has two state (off and on)
		process->do_flag = false;
	}
}

*/


















