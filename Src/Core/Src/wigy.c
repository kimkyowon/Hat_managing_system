/*
 * wigy.c
 *
 *  Created on: Jun 1, 2024
 *      Author: KYO
 */

#include "wigy.h"

// PV _ private value for user
extern Ptimer_t led_blink;


// static functions prototypes
static void led_off_all();
static void Ctrl_IR_Led(turn blank);
static void Ctrl_UVA_Led(turn blank);
static void Ctrl_UVC_Led(turn blank);
static void Ctrl_EXTFAN(turn blank);
static void process_led_blink(Ptimer_t* process,color_t color);

static void change_system_mode(Sys_mode_t sysmode);
static void change_led_mode(L_mode_t lmode);

// For initializing struct type wigy
void Initialize_wigy(WIGY_t *_instance){
	_instance->L.push_cnt 		= 0;
	_instance->System.push_cnt  = 0;
	_instance->fan				= 0;
	_instance->irled			= 0;
	_instance->rgb_color		= 0;
	_instance->uvcled 			= 0;
	_instance->uvled			= 0;
	_instance->mode.lmode		= 0;
	_instance->mode.sysmode		= 0;

}

void is_pushed_L_sw(WIGY_t *wigy){
	if(wigy->L.push_cnt != wigy->mode.lmode){
		wigy->mode.lmode = wigy->L.push_cnt;
		change_led_mode(wigy->mode.lmode);
	}
}

void is_pushed_System_sw(WIGY_t *wigy){
	if(wigy->System.push_cnt != wigy->mode.sysmode){
		wigy->mode.sysmode = wigy->System.push_cnt;
		change_system_mode(wigy->mode.sysmode);
	}
}

static void read_state(WIGY_t *wigy){
	wigy->irled  = HAL_GPIO_ReadPin(GPIOB,LEDD1012_G_Pin);
	wigy->uvled  = HAL_GPIO_ReadPin(GPIOC, UVLED_G_Pin);
	wigy->uvcled = HAL_GPIO_ReadPin(GPIOB, LED12_G_Pin);
	wigy->fan	 = HAL_GPIO_ReadPin(GPIOA,EXTFAN_G_Pin);

}

void Ctrl_led(color_t color, turn on_off){
	led_off_all();
	switch(color){
	case pink:
		HAL_GPIO_WritePin(GPIOA,RGB_Blue_G_Pin,on_off);
		HAL_GPIO_WritePin(GPIOB,RGB_Red_G_Pin,on_off);
		break;
	case sky:
		HAL_GPIO_WritePin(GPIOA,RGB_Blue_G_Pin,on_off);
		HAL_GPIO_WritePin(GPIOA,RGB_Green_G_Pin,on_off);
		break;
	case blue:
		HAL_GPIO_WritePin(GPIOA,RGB_Blue_G_Pin,on_off);
		break;
	case green:
		HAL_GPIO_WritePin(GPIOA,RGB_Green_G_Pin,on_off);
		break;
	case red:
		HAL_GPIO_WritePin(GPIOB,RGB_Red_G_Pin,on_off);
		break;
	default:
		break;
	}
}

void process(WIGY_t *wigy){
	is_pushed_L_sw(wigy);
	is_pushed_System_sw(wigy);
	read_state(wigy);
}


static void change_system_mode(Sys_mode_t sysmode){
	switch(sysmode){	//Sys_default,Sys_mode1,Sys_mode2,Sys_All_off
	case Sys_default:
		//do nothing
		break;
	case Sys_mode1:
		Ctrl_led(red,on);
		Ctrl_IR_Led(on);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(on);
		Ctrl_EXTFAN(off);
		break;
	case Sys_mode2:
		Ctrl_led(red,on);
		Ctrl_IR_Led(on);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(on);
		Ctrl_EXTFAN(on);
		break;
	case Sys_All_off:
		Ctrl_led(none,on);
		Ctrl_IR_Led(off);
		Ctrl_UVA_Led(off);
		Ctrl_UVC_Led(off);
		Ctrl_EXTFAN(off);
	default:
		break;
	}
}
//default_mode,mood,low_salgyun, high_salgyun, mid_salgyun, one_high_salgyun,remove_func
static void change_led_mode(L_mode_t lmode){
	switch(lmode){
	case L_mode1:	//mood
		Ctrl_led(red,on);
		break;

	case L_mode2:	//low_salgyun
		Ctrl_led(sky,on);
		Ctrl_UVA_Led(on);
		break;

	case L_mode3:	//high_salgyun
		Ctrl_led(blue,on);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(on);
		break;

	case L_mode4:	//mid_salgyun
		Ctrl_led(green,on);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(on);
		break;

	case L_mode5:	//one_high_salgyun
		Ctrl_led(pink,on);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(on);
		Ctrl_IR_Led(on);
		break;
	case remove_funcs:	//remove_func
		led_off_all();
		Ctrl_UVA_Led(off);
		Ctrl_UVC_Led(off);
		Ctrl_IR_Led(off);
		process_led_blink(&led_blink, pink);
		break;
	default:
		break;
	}
}
// Ctrl function (GPIO)
static void led_off_all(){	//temporary all gpio
	HAL_GPIO_WritePin(GPIOA, RGB_Green_G_Pin|RGB_Blue_G_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, RGB_Red_G_Pin, GPIO_PIN_RESET);
}
static void Ctrl_IR_Led(turn blank){
	HAL_GPIO_WritePin(GPIOB,LEDD1012_G_Pin, blank);
}

static void Ctrl_UVA_Led(turn blank){
	HAL_GPIO_WritePin(GPIOC, UVLED_G_Pin, blank);
}

static void Ctrl_UVC_Led(turn blank){
	HAL_GPIO_WritePin(GPIOB, LED12_G_Pin, blank);
}

static void Ctrl_EXTFAN(turn blank){
	HAL_GPIO_WritePin(GPIOA,EXTFAN_G_Pin,blank);
}

static void process_led_blink(Ptimer_t* process,color_t color){
	if(process->do_flag == true){
		Ctrl_led(color,process->current_cnt%2);	//set state with current cnt, cause blink has two state (off and on)
		process->do_flag = false;
	}
}




















