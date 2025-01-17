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

//Delay para transmitir informacion por la Uart;
static delay_t delayUARTtemp;
static tick_t duracion1 = 2000;

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


/*funciones para Reportar Informacion por UART*/
static void UART_printEstable(uint16_t temp){
	uint8_t text1[27] = "\n\r**********************\n\r";
	uint8_t text2[27] = "Estado: Estable\n\r";
	uint8_t text3[27] = "Temperatura:   ";
	UART_transmit(text1);
	UART_transmit(text2);
	UART_transmit(text3);
	UART_transmit_uint16(temp);
	delayWrite(&delayUARTtemp, duracion1);
}

static void UART_printPrecaucion(uint16_t temp){
	uint8_t text1[27] = "\n\r**********************\n\r";
	uint8_t text2[27] = "Estado: Precaucion\n\r";
	uint8_t text3[27] = "Temperatura:   ";
	UART_transmit(text1);
	UART_transmit(text2);
	UART_transmit(text3);
	UART_transmit_uint16(temp);
	delayWrite(&delayUARTtemp, duracion1);
}

static void UART_printPeligro(uint16_t temp){
	uint8_t text1[27] = "\n\r**********************\n\r";
	uint8_t text2[27] = "Estado: Peligro\n\r";
	uint8_t text3[27] = "Temperatura:   ";
	UART_transmit(text1);
	UART_transmit(text2);
	UART_transmit(text3);
	UART_transmit_uint16(temp);
	delayWrite(&delayUARTtemp, duracion1);
}

/*******************************************************************************************
 *                               Definicion de las funciones                               *
 *******************************************************************************************/
/* Inicializa la MEF*/
void MEF_init(){
	delayInit(&delayLCDtemp, duracion);
	delayInit(&delayUARTtemp, duracion1);
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

void MEF_uartUpdate(){
	if(delayRead(&delayUARTtemp)){
		switch(MEF){
		case ESTABLE:
			UART_printEstable(temp);
		break;

		case PRECAUCION:
			UART_printPrecaucion(temp);
		break;

		case PELIGRO:
			UART_printPeligro(temp);
		break;
		}
	}
}
