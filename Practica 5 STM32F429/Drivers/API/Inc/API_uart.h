//Inludes
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"


//typedef
typedef bool bool_t;

//Declaracion de las funiciones publicas
bool_t uartInit();                       // inicializa la UART1 de Forma Asincronica
void uartSendString(uint8_t * pstring);  // envia un String por la UART - Requiere string
void uartSendStringSize(uint8_t * pstring, uint16_t size); //envia un String por la UART - Requiere string y tamaño
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);
