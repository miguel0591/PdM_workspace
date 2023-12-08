#ifndef API_INC_MEF_H_
#define API_INC_MEF_H_

/*Include Necesarios*/
#include "stm32f4xx.h"
#include "LCD_2X16_HD44780.h"
#include "SENSOR_Temp.h"
#include "API_delay.h"
#include "port_gpio.h"
#include "port_usart.h"

/*Umbrales de temperatura*/
#define T1 30
#define T2 90

/*Typedef*/
typedef enum{
	ESTABLE,
	PRECAUCION,
	PELIGRO
} MEF_status;

typedef bool bool_t;

/*Funciones Disponibles*/
void MEF_init(void);
void MEF_update(void);
void MEF_uartUpdate(void);

#endif /* API_MEF_H_ */
