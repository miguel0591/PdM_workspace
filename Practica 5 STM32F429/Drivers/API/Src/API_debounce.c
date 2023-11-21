//include Necesarios
#include "stm32f4xx_hal.h"        // Se incluyo para poder usar las funciones de la HAL
#include "API_debounce.h"         // Se incluyo por las deficiones que necesita el punto c
#include "API_delay.h"            // Permite usar la funciones de retardo

#define DEBOUNCED_DELAY 40


//VARIABLES GLOBALES PRIVADAS: corresponde a la variables necesarias para lo retardos
// pero no interesa que sean visibles solo dentro del archivo.
static debounceState_t MEF;
static delay_t retardo;         //estructura del retardo duracion = 40;    //Retardo de 40ms
static bool_t flag = 0;

//Prototipo de funciones
void debounceFSM_init(){
	MEF = BUTTON_UP;
	delayInit(&retardo, DEBOUNCED_DELAY);
};  // Inicializar la maquina de etado


void debounceFSM_update(){
	switch(MEF){

	case BUTTON_UP:
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1) {
			MEF = BUTTON_FALLING;
		}else{
			MEF = BUTTON_UP;
		}
	break;

	case BUTTON_FALLING:
		if(delayRead(&retardo) == 1){
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1){
				MEF = BUTTON_DOWN;
				buttonPressed();
			}
			else{
				MEF = BUTTON_UP;
			}
		}
	break;

	case BUTTON_DOWN:
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0){
			MEF = BUTTON_RAISING;
			delayInit(&retardo, DEBOUNCED_DELAY);
		}else{
			MEF = BUTTON_DOWN;
		}
	break;

	case BUTTON_RAISING:
		if(delayRead(&retardo) == 1){
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0){
				MEF = BUTTON_UP;
			}else{
				MEF = BUTTON_DOWN;
			}
		}
	break;
	};
}; //Actuliza la maquina de estado


void buttonPressed(){
	flag = 1;
};    //Da la salida de boton precionado (enciende el led)


void buttonReleased(){
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
};   //Da la salida de boton NO precionado (Apaga el led)


bool_t readKey(void){

	if(flag){
		flag = 0;
		return 1;
	}
	if(flag == 0){
		return 0;
	}
	return 0;
}
