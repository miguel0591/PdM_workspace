/*
 * API_delay.c
 *
 *  Created on: Dec 6, 2023
 *      Author: ubuntu22
 */
#include "API_delay.h"


//Funcion de Inicializacion
void delayInit( delay_t* delay, tick_t duration ){
	delay->duration = duration;
	delay->running = false;
	delay->startTime = HAL_GetTick();
};

//Funcion de control
bool_t delayRead( delay_t* delay ){
	uint8_t flag;
	if ((HAL_GetTick() - delay->startTime) <= delay->duration) {
		delay->running = false;
		flag = false;
	}else{
		delay->running = true;
		flag = true;
	}
	return flag;
}

//Funcion de cambio de duracion
void delayWrite( delay_t * delay, tick_t duration ){
	delay->duration = duration;
	delay->running = false;
	delay->startTime = HAL_GetTick();
};
