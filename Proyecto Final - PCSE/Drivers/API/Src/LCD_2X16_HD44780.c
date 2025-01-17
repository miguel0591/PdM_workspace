#include "LCD_2X16_HD44780.h"


#ifdef MOD_4BIT_I2C

/*******************************************************************************************
 *                             Funciones Privadas Necesarias                               *
 *******************************************************************************************/
static LCD_Status_t LCD_2x16_command(uint8_t cmd){
	uint8_t cmd_h, cmd_l;
	uint8_t data[4];
	cmd_h = (cmd) & 0xF0;
	cmd_l = ((cmd) & 0x0F) << 4;
	data[0] = (cmd_h | EN_ON) | BL_ON;
	data[1] = (data[0]) & ~EN_ON;
	data[2] = cmd_l | EN_ON | BL_ON;
	data[3] = (data[2]) & ~EN_ON;
	LCD_2x16_Send_I2C(data);
	return OK;
}
static LCD_Status_t LCD_2x16_char(char letra){
	char letra_h, letra_l;
	uint8_t data[4];
	letra_h = (letra) & 0xF0;
	letra_l = ((letra) & 0x0F) << 4;
	data[0] = ((letra_h | EN_ON) | BL_ON) | RS_ON;
	data[1] = (data[0]) & ~EN_ON;
	data[2] = letra_l | EN_ON | BL_ON |RS_ON;
	data[3] = (data[2]) & ~EN_ON;
	LCD_2x16_Send_I2C(data);
	return OK;
}
static LCD_Status_t LCD_2x16_delay(uint8_t delay){
	HAL_Delay(delay);
	return OK;
}


/*******************************************************************************************
 *                                    Funciones Publicas                                   *
 *******************************************************************************************/
LCD_Status_t LCD_2x16_init(void){
	LCD_2x16_delay(50);                //Tiempo de espera necesario desde el encendio >40ms
	LCD_Send_RawData(0x3C);
	LCD_2x16_delay(5);
	LCD_Send_RawData(0x3C);
	LCD_2x16_delay(1);
	LCD_Send_RawData(0x3C);
	LCD_2x16_delay(1);
	LCD_Send_RawData(0x2C);    // desde aqui funciona en 4 bits.
	LCD_2x16_delay(1);

	LCD_2x16_command(FUNCTION_SET);
	LCD_2x16_delay(1);
	LCD_2x16_command(DISPLAY_OFF);
	LCD_2x16_delay(1);
	LCD_2x16_command(DISPLAY_CLEAR);
	LCD_2x16_delay(2);
	LCD_2x16_command(ENTRY_MODE_SET);
	LCD_2x16_delay(1);
	LCD_2x16_command(DISPLAY_0N);
	LCD_2x16_delay(1);
	return OK;
}

LCD_Status_t LCD_2x16_cursor(uint8_t linea, uint8_t pos){
	if(linea <= 0 && linea > 2){
		return NO_OK;
	}
	if(pos <= 0 && pos > 16){
		return NO_OK;
	}

	char dir_h, dir_l;
	uint8_t dir, data[4];
	if(linea == 1){
		dir = L1_COL1 + (pos - 1);
		dir_h = (dir)& 0xF0;
		dir_l = ((dir)& 0x0F) << 4;
		data[0] = ((dir_h | EN_ON) | BL_ON);
		data[1] = (data[0]) & ~EN_ON;
		data[2] = dir_l | EN_ON | BL_ON;
		data[3] = (data[2]) & ~EN_ON;
		LCD_2x16_Send_I2C(data);
	}
	if (linea == 2){
		dir = L2_COL1 + (pos - 1);
		dir_h = (dir)& 0xF0;
		dir_l = ((dir)& 0x0F) << 4;
		data[0] = ((dir_h | EN_ON) | BL_ON);
		data[1] = (data[0]) & ~EN_ON;
		data[2] = dir_l | EN_ON | BL_ON;
		data[3] = (data[2]) & ~EN_ON;
		LCD_2x16_Send_I2C(data);
	}
	return OK;
}
LCD_Status_t LCD_2x16_string(char * str){
	while (*str){
		LCD_2x16_char(*str++);
	}
	return OK;
}
LCD_Status_t LDC_2x16_clear(void){
	LCD_2x16_cursor(1, 1);
	LCD_2x16_string("                ");
	LCD_2x16_cursor(2, 1);
	LCD_2x16_string("                ");
	return OK;
}
LCD_Status_t LCD_2x16_cursorBlink(){
	LCD_2x16_command(DISPLAY_CURSOR_BLINK);
	return OK;
}
LCD_Status_t LCD_2x16_uint16(uint16_t valor){
	if(valor<0 || valor>65536){
		return NO_OK;
	}
	char valor2[3];
	sprintf(valor2, "%d",valor);
	LCD_2x16_string(valor2);
	return OK;
}

#endif






#ifdef MOD_4BIT


#endif

#ifdef MOD_8BIT


#endif

