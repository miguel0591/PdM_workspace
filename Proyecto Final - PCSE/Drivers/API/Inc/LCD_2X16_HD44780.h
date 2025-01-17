#ifndef API_INC_LCD_2X16_HD44780_H_
#define API_INC_LCD_2X16_HD44780_H_

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#define  SLAVE_ADDRESS_LCD 0x4E              //Direccion de la pantalla

typedef enum {OK, NO_OK} LCD_Status_t;       //



////////////////////////////////////////////////////////////////////////////////////////
//                     Configuracion para compilacion condicionada                     /
////////////////////////////////////////////////////////////////////////////////////////
/*	Se debe elegir una de las tres opciones disponibles abajo según le modo de trabajo//
 * que se quiera utilizar, dejar comentada las dos lineas no utilizadas               */
#define MOD_4BIT_I2C                                                                  //
//#define MOD_4BIT                                                                    //
//#define MOD_8BIT                                                                    //
////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////
//                                     MOD_4BIT_I2C                                    /
////////////////////////////////////////////////////////////////////////////////////////
/* En este modo estamos utilizado un expansor de 8-Bit I2C PCF8574 para enviar la     //
 * información, en grupos de 4-Bits, el conexionado físico corresponde al siguiente:  //
 * MOD LCD --> DB7 / DB6 / DB5 / DB4 /  BL / EN  / R/W /  RS                          //
 * PCF8574 --> PB7 / PB6 / PB5 / PB4 / PB3 / PB2 / PB1 / PB0                          //
 * Dato (0x30)                                                                        //
 * Dato1    -->  0     0     1     1      1    1      0    0   --> 0x3C               //
 * Dato2    -->  0     0     1     1      1    0      0    0   --> 0x38               //
 * Dato3    -->  0     0     0     0      1    1      0    0   --> 0x0C               //
 * Dato3    -->  0     0     0     0      1    0      0    0   --> 0x08               //
 *//////////////////////////////////////////////////////////////////////////////////////
#ifdef MOD_4BIT_I2C
#include "port_i2c.h"

//Desplazamiento de los bits menos significavos de conversos I2C
#define BL_ON (1 << 3)
#define EN_ON (1 << 2)
#define RW_ON (1 << 1)
#define RS_ON  1


//intrucciones en su formato de 8Bits
#define DISPLAY_CLEAR          0x01    //Limpia el contenido del display
#define DISPLAY_OFF            0x08    //D=0 Display off // C = 0 Cursor off // B = 0 Blinking off
#define DISPLAY_0N             0x0C    //D=1 Display on  // C = 0 Cursor off // B = 0 Blinking off
#define DISPLAY_CURSOR_BLINK   0x0D    //D=1 Display on  // C = 0 Cursor on  // B = 1 Blinking on
#define DISPLAY_CURSOR_NOBLINK 0x0E    //D=1 Display on  // C = 1 Cursor on  // B = 0 Blinking on
#define FUNCTION_SET           0x28    //DL= 0 4bit // N = 1 (2lineas) // F = 0 (caracter 5x8)
#define ENTRY_MODE_SET         0x06    //I/D=1 Increment S=0 (no shitf)
#define RETURN_HOME            0x02    //Retorna el display a la direccion 0x80 de la DDRAM


//Posidicones de la DDRAM
#define L1_COL1 0x80
#define L2_COL1 0xC0

//Funciones Publicas
LCD_Status_t LCD_2x16_init(void);                                 //Inicializa el LCD
LCD_Status_t LCD_2x16_cursor(uint8_t linea, uint8_t pos);         //Poscisiona el cursor
LCD_Status_t LCD_2x16_string(char * str);                         //Imprime un string en el LCD
LCD_Status_t LDC_2x16_clear(void);                                //Borra el LCD
LCD_Status_t LCD_2x16_cursorBlink(void);                          //Blink Cursor
LCD_Status_t LCD_2x16_uint16(uint16_t valor);                     //Imprime un uint16 en el LCD


//Funciones Privadas
//LCD_Status_t LCD_2x16_delay(uint8_t delay);                //Delay Internos necesarios
//LCD_Status_t LCD_2x16_command(uint8_t cmd);                //Envia instrucciones
//LCD_Status_t LCD_2x16_char(char letra);                    //Envia una letra

#endif




////////////////////////////////////////////////////////////////////////////////////////
//                                       MOD_4BIT                                      /
////////////////////////////////////////////////////////////////////////////////////////
/* En este modo usamos el LCD en modo de 4-Bit haciendo uso director de los gpio
 *
 *
 */

#ifdef MOD_4BIT
#include "port_gpio.h"

#endif


////////////////////////////////////////////////////////////////////////////////////////
//                                       MOD_8BIT                                      /
////////////////////////////////////////////////////////////////////////////////////////
/* En este modo usamos el LCD en modo de 8-Bit haciendo uso director de los gpio
 *
 *
 */
#ifdef MOD_8BIT
#include "port_gpio.h"

#endif

#endif /* API_LCD_2X16_HD44780_H_ */
