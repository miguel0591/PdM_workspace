#include "MEF.h"


/*******************************************************************************************
 *                              Variables Globales Privadas                                *
 *******************************************************************************************/
static MEF_status MEF;

/*Flag para indicar si se viene de un cambio de estado o se mantiene el mismo, el flag1 es
 * para el estado 1, flag2 para el estado 2 y flag3 para el estado 3*/
static bool_t flag1, flag2, flag3;

// valor de temperatura del sistema
static uint16_t temp;

//Para actualizar temperatura en el LCD - No Bloqueante
static delay_t delayLCDtemp;
static tick_t duracion = 200;


/*******************************************************************************************
 *                             Funciones Privadas Necesarias                               *
 *******************************************************************************************/
/*funciones para imprimir en el LCD*/
static void LCD_printEstable(){
	LDC_2x16_clear();
	LCD_2x16_cursor(1, 1);
	LCD_2x16_string("Estado:  Estable");
	LCD_2x16_cursor(2, 1);
	LCD_2x16_string("Temperatura:");
}

static void LCD_printPrecaucion(){
	LDC_2x16_clear();
	LCD_2x16_cursor(1, 1);
	LCD_2x16_string("Estado: Precauc.");
	LCD_2x16_cursor(2, 1);
	LCD_2x16_string("Temperatura:");

}

static void LCD_printPeligro(){
	LDC_2x16_clear();
	LCD_2x16_cursor(1, 1);
	LCD_2x16_string("Estado: Peligro");
	LCD_2x16_cursor(2, 1);
	LCD_2x16_string("Temperatura:");

}

static void LDC_printTemp(uint16_t temp){
	if(delayRead(&delayLCDtemp)){
		LCD_2x16_cursor(2, 14);
		LCD_2x16_uint16(temp);
		delayWrite(&delayLCDtemp, duracion);
	}
}

/* Manejo de actuadores*/
/*Manejo de FAN - el rele del fan encuentra conectado al GPIO_PIN 13*/
static void MEF_fanOff(){
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, 0);
};
static void MEF_fanOn(){
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, 1);
};

/*Manejo de Alarma*/
/*El contacto que dispara la alamar se en cuentra conectado al GPIO_PIN 14*/
static void MEF_alarmOff(){
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, 0);
};
static void MEF_alarmOn(){
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, 1);
};

/*******************************************************************************************
 *                               Definicion de las funciones                               *
 *******************************************************************************************/
/* Inicializa la MEF*/
void MEF_init(){
	delayInit(&delayLCDtemp, duracion);
	MEF = ESTABLE;
}

/* Actualiza la MEF */
void MEF_update(){
	LDC_printTemp(temp);
	switch(MEF){
		case ESTABLE:
			temp = SENSOR_TEMP_check();
			if (temp <= T1) {
				if(flag1 == 0){
					flag1 = 1;
					LCD_printEstable();
					MEF_fanOff();
					MEF_alarmOff();
				}
			}
			if(temp>T1 && temp<=T2){
				MEF = PRECAUCION;
				flag1 = 0;
				flag2 = 1;
				LCD_printPrecaucion();
				MEF_fanOn();
				MEF_alarmOff();
			}
			if(temp>T2){
				MEF = PELIGRO;
				flag1 = 0;
				flag3 = 1;
				LCD_printPeligro();
				MEF_fanOn();
				MEF_alarmOn();
			}
		break;
		case PRECAUCION:
			temp = SENSOR_TEMP_check();
			if (temp > T1 && temp <= T2) {
				if(flag2 == 0){
					flag2 = 1;
					LCD_printPrecaucion();
					MEF_fanOn();
					MEF_alarmOff();
				}
			}
			if(temp <= T1){
				MEF = ESTABLE;
				flag2 = 0;
				flag1 = 1;
				LCD_printEstable();
				MEF_fanOff();
				MEF_alarmOff();
			}
			if(temp > T2){
				MEF = PELIGRO;
				flag2 = 0;
				flag3 = 1;
				LCD_printPeligro();
				MEF_fanOn();
				MEF_alarmOn();
			}
		break;
		case PELIGRO:
			temp = SENSOR_TEMP_check();
			if (temp > T2) {
				if(flag3 == 0){
					flag3 = 1;
					LCD_printPeligro();
					MEF_fanOn();
					MEF_alarmOn();
				}
			};
			if(temp <= T1){
				MEF = ESTABLE;
				flag3 = 0;
				flag1 = 1;
				LCD_printEstable();
				MEF_fanOff();
				MEF_alarmOff();
			}
			if(temp>T1 && temp<=T2){
				MEF = PRECAUCION;
				flag3 = 0;
				flag2 = 1;
				LCD_printPrecaucion();
				MEF_fanOn();
				MEF_alarmOff();
			}
		break;
	}
}
