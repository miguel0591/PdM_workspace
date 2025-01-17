/*
 * SENSOR_Temp.c
 *
 *  Created on: Dec 6, 2023
 *      Author: ubuntu22
 */
#include "SENSOR_Temp.h"

/*******************************************************************************************
 *                              Variables Globales Privadas                                *
 *******************************************************************************************/
/*Limites de Sensor Teorico*/
static const uint8_t Tmax = 150;        /*Corresponde a los 4096 de DAC*/
static const uint8_t Tmin =  20;        /*Corresponde a los    0 de DAC*/
static const uint8_t diff = Tmax-Tmin;



/*******************************************************************************************
 *                               Definicion de las funciones                               *
 *******************************************************************************************/
void SENSOR_TEMP_init(void){
	HAL_ADC_Start(&hadc1);
};

uint16_t SENSOR_TEMP_check(void){
	HAL_ADC_PollForConversion(&hadc1, 100);
	uint16_t tempADC = HAL_ADC_GetValue(&hadc1);
	float con = ((float)diff)/4095;
	float te = (con * (float)tempADC);
	uint8_t temp = te + Tmin;
	return temp;
};
