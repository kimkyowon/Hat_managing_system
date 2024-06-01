/*
 * wigy.c
 *
 *  Created on: Jun 1, 2024
 *      Author: KYO
 */

#include "wigy.h"

// For initializing struct type wigy
void Initialize_wigy(WIGY_t *_instance){
	_instance->L.push_cnt 		= 0;
	_instance->System.push_cnt  = 0;
	_instance->fan				= 0;
	_instance->irled			= 0;
	_instance->rgb_color		= 0;
	_instance->uvcled 			= 0;
	_instance->uvled			= 0;
	_instance->mode				= 0;
}

void update_mode(WIGY_t *wigy){
	if()
	wigy->mode
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
