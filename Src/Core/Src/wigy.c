/*
 * wigy.c
 *
 *  Created on: Jun 1, 2024
 *      Author: KYO
 */

#include "wigy.h"

// static functions declaration
static void led_off_all();

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

void update_mode(WIGY_t *wigy){
	if()
	wigy->mode
}

void lights_up_one(color_t color){
	led_off_all();
	switch(color){
	case pink:
		HAL_GPIO_WritePin(GPIOB,LEDD1012_G_Pin,GPIO_PIN_SET);
		break;
	case sky:
		HAL_GPIO_WritePin(GPIOB,LED12_G_Pin,GPIO_PIN_SET);
		break;
	case blue:
		HAL_GPIO_WritePin(GPIOA,RGB_BLUE_G_Pin,GPIO_PIN_SET);
		break;
	case green:
		HAL_GPIO_WritePin(GPIOA,LEDD1012_G_Pin,GPIO_PIN_SET);
		break;
	case red:
		HAL_GPIO_WritePin(GPIOA,LEDD1012_G_Pin,GPIO_PIN_SET);
		break;
	default:
		break;
	}
}




void process(WIGY_t *wigy){


	swtich(wigy->mode){
		case:
			break;
		case:
			break;
		case:
			break;
		case:
			break;
		case:
			break;
		default:
			break;
	}
}

static void led_off_all(){
	HAL_GPIO_WritePin(GPIOA, USBLED_Pin|RGB_BLUE_G_Pin|RGB_RED_G_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LEDD1012_G_Pin|LED12_G_Pin, GPIO_PIN_RESET);
}



