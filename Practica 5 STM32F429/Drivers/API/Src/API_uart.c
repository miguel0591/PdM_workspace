#include "API_uart.h"
#include "string.h"

//variables privadas
static const char msg[] = "Puerto Serie Iniciaizado correctamente\n\r";
static const char esp[] = "USART1\n\rBaudR 115200\n\rWORDLENGTH_8B\n\rSTOPBITS_1\n\rPARITY_NONE\n\r";
static const char espacios[] = "\n\r\n\r\n\r";

UART_HandleTypeDef huart1;

bool_t uartInit(){

	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	  if (HAL_UART_Init(&huart1) != HAL_OK)
	  {
		  return 0;
	  }
	  HAL_UART_Transmit(&huart1, msg, strlen(msg), HAL_MAX_DELAY);
	  HAL_UART_Transmit(&huart1, esp, strlen(esp), HAL_MAX_DELAY);
	  HAL_UART_Transmit(&huart1, espacios, strlen(espacios), HAL_MAX_DELAY);
	  return 1;
}



void uartSendString(uint8_t * pstring){
	HAL_UART_Transmit(&huart1, pstring, strlen(pstring), HAL_MAX_DELAY);
};
void uartSendStringSize(uint8_t * pstring, uint16_t size){
	HAL_UART_Transmit(&huart1, pstring, size, HAL_MAX_DELAY);
};
void uartReceiveStringSize(uint8_t * pstring, uint16_t size){};
