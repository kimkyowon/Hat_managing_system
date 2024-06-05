/*
 * wigy.c
 *
 *  Created on: Jun 1, 2024
 *      Author: KYO
 */

#include "wigy.h"

// static functions declaration
static void led_off_all();
static void Ctrl_IR_Led(turn blank);
static void Ctrl_UVA_Led(turn blank);
static void Ctrl_UVC_Led(turn blank);

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

void lights_up_one(color_t color){
	led_off_all();
	switch(color){
	case pink:
		HAL_GPIO_WritePin(GPIOA,RGB_Blue_G_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,RGB_Red_G_Pin,GPIO_PIN_SET);
		break;
	case sky:
		HAL_GPIO_WritePin(GPIOA,RGB_Blue_G_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,RGB_Green_G_Pin,GPIO_PIN_SET);
		break;
	case blue:
		HAL_GPIO_WritePin(GPIOA,RGB_Blue_G_Pin,GPIO_PIN_SET);
		break;
	case green:
		HAL_GPIO_WritePin(GPIOA,RGB_Green_G_Pin,GPIO_PIN_SET);
		break;
	case red:
		HAL_GPIO_WritePin(GPIOB,RGB_Red_G_Pin,GPIO_PIN_SET);
		break;
	default:
		break;
	}
}

void process(WIGY_t *wigy){

}

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


static void change_system_mode(Sys_mode_t sysmode){
	switch(sysmode){	//Sys_default,Sys_mode1,Sys_mode2,Sys_All_off
	case Sys_default:
		//do nothing
		break;
	case Sys_mode1:
		led_off_all();
		lights_up_one(red);
		Ctrl_IR_Led(on);
		Ctrl_UVA_Led(on);
		Ctrl_UVC_Led(on);

		break;
	case Sys_mode2:
		break;
	case Sys_All_off:
	default:
		break;
	}
}

static void change_led_mode(L_mode_t lmode){

}
