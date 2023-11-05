#include "API_delay.h"
#include "stm32f4xx_hal.h"

//Funcion de Inicializacion
void delayInit( delay_t* delay, tick_t duration ){
	delay->duration = duration;
	delay->running = false;
	delay->startTime = HAL_GetTick();
};

//Funcion de control
bool_t delayRead( delay_t* delay ){

	if ((HAL_GetTick() - delay->startTime) <= delay->duration) {
		delay->running = false;
	}else{
		delay->running = true;
	}
	return delay->running;
}

//Funcion de cambio de duracion
void delayWrite( delay_t * delay, tick_t duration ){
	delay->duration = duration;
	delay->running = false;
	delay->startTime = HAL_GetTick();
};
