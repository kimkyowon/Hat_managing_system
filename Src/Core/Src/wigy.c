/*
 * wigy.c
 *
 *  Created on: Jun 1, 2024
 *      Author: KYO
 */

#include "wigy.h"

// PV _ private value for user



// static functions prototypes
static void led_off_all();
static void Ctrl_IR_Led(turn blank);
static void Ctrl_UVA_Led(turn blank);
static void Ctrl_UVC_Led(turn blank);
static void Ctrl_EXTFAN(turn blank);

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

void lights_up_one(color_t color, turn on_off){
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

void led_blink(color_t color, uint32_t blink_period,uint32_t blink_time){
	lights_up_one(color, on);

}

void process(WIGY_t *wigy){

}


static void change_system_mode(Sys_mode_t sysmode){
	switch(sysmode){	//Sys_default,Sys_mode1,Sys_mode2,Sys_All_off
	case Sys_default:
		//do nothing
		break;
	case Sys_mode1:
		lights_up_one(red,on);
		Ctrl_IR_Led(on);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(on);
		Ctrl_EXTFAN(off);
		break;
	case Sys_mode2:
		lights_up_one(red,on);
		Ctrl_IR_Led(on);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(on);
		Ctrl_EXTFAN(on);
		break;
	case Sys_All_off:
		lights_up_one(none,on);
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
		lights_up_one(red,on);
		break;

	case L_mode2:	//low_salgyun
		lights_up_one(sky,on);
		Ctrl_UVA_Led(on);
		break;

	case L_mode3:	//high_salgyun
		lights_up_one(blue,on);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(on);
		break;

	case L_mode4:	//mid_salgyun
		lights_up_one(green,on);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(on);
		break;

	case L_mode5:	//one_high_salgyun
		lights_up_one(pink,on);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(on);
		Ctrl_IR_Led(on);
		break;
	case default_mode:	//remove_func

		break;
	}
}
// Ctrl function (GPIO)
static void led_off_all(){	//temporary all gpio
	HAL_GPIO_WritePin(GPIOA, USBLED_Pin|EXTFAN_G_Pin|RGB_Green_G_Pin|RGB_Blue_G_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LEDD1012_G_Pin|RGB_Red_G_Pin|LED12_G_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, Heater_G_Pin|UVLED_G_Pin, GPIO_PIN_RESET);
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




















