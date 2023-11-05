# Repositorio Git Practicas PdM - CESE -FIUBA

## Indice:
+ Placa de Desarrollo
+ LEDs, Botones y Sensores para el uso del usuario
+ Descripcion de los Ejercicios
    * PRACTICA 1: Uso de Retardos Bloqueantes
    * PRACTICA 2: Uso de Retardos NO Bloqueantes
	* PRACTICA 3: Modularizacion.

## Placa de Desarrollo Utilizada:
STM32F429I-DISC1 Discovery Development Kit
![](https://market.samm.com/stm32f429i-disc1-discovery-development-kit-en-stm-discovery-stmicroelectronics-6892-64-B.jpg)

## LEDs y Boton para el uso del usuario:
+ LEDs
    + 1 Ubicado en PG13 (MACRO #define LD3_Pin)
    + 1 Ubicado en PG14 (MACRO #define LD4_Pin))
+ Boton
    * Boton en PA0 (resistencia pull-donw)


## Practica 1 - Ejercicio 1: 
Como la placa de desarrollo solo tiene 2 leds, se los hace parpadear a 200ms, y los leds no se prenden simultaneamente.

Definicion de Variables Globales:
```
uint16_t Leds[ ] = {LD3_Pin, LD4_Pin};         //Arreglo de LEDs se usan macros para cada uno
uint8_t Pos = 0;                                            //Variable para la posicion del array
uint32_t Flicker = 200;                                 // valor del parpadeo
```

Rutina del super loop:
```
  while (1)
  {
	  if (Pos < (sizeof(Leds)/2)) {
		  HAL_GPIO_WritePin(GPIOG, Leds[Pos], GPIO_PIN_SET);
		  HAL_Delay(Flicker);
		  HAL_GPIO_WritePin(GPIOG, Leds[Pos], GPIO_PIN_RESET);
		  Pos++;
	} else {
		  Pos = 0;
	}
  }
```
## Practica 1 - Ejercicio 2: 
Usamos una interrupcion internar para alternar el led que debe parpadear, usamos el pulsado en el puerto PA0 que tiene una resistencia de pull-down, cada vez que precionamos el boton se llama la interrupcion que incrementa o vuelve a cero el valor de Pos del led seleccionado.

Definicion de Variables Globales:
```
uint16_t Leds[ ] = {LD3_Pin, LD4_Pin};         //Arreglo de LEDs se usan macros para cada uno
uint8_t Pos = 0;                                            //Variable para la posicion del array
uint32_t Flicker = 200;                                 // valor del parpadeo
```
Rutina del super loop: se encargar de cambiar el estado de led que este seleccionado
```
  while (1)
  {
	  HAL_GPIO_TogglePin(GPIOG, Leds[Pos]); 
	  HAL_Delay(Flicker);
  }
```
Rutina de Interrupcion:
```
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//apagamos todos los led antes de cambiar la posicion
	for (int var = 0; var < (sizeof(Leds)/2); ++var) {
		HAL_GPIO_WritePin(GPIOG, Leds[var], GPIO_PIN_RESET);
	}

	//cambiamos la poscicion (la aumentamos o volvemos a 0)
	if (Pos<((sizeof(Leds)/2)-1)) {
		++Pos;
	} else {
		Pos = 0;
	}
}
```
## Practica 2 - Ejercicio 1 , 2 y 3: 
Consitia en generar funciones para trabajar con delays no bloqueantes, en la parte de aplicarlas para hacer parpadear un led y en la ultima parte poder usar un array para tener valorios delays disponibles.

En el archivo main.c se definio lo necesario para implemetar todo pasando por Includes, Typedef, Macros y Variables Privadas.
```
//Includes Privados
#include <stdint.h>
#include <stdbool.h>

//Typedef Privados
typedef uint32_t tick_t;
typedef bool bool_t;
typedef struct {
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

Macros Privados
#define ciclosdeseados 10              //5 de encendido y 5 de apagado.

//Variables Privadas
delay_t retardo;                                    //estructura del delay
tick_t duracion[] = {1000, 200, 100};    // diferentes duraciones en un array
uint8_t posd = 0;                               // indice del vector de arriba
uint8_t ciclo = 0;                              // candidad de encendidos + apagado realizados
```

Los prototipos de funciones se escribieron:
```
//Inicializa el contador con los parametros pasados
void delayInit( delay_t* delay, tick_t duration ){
	delay->duration = duration;
	delay->running = false;
	delay->startTime = HAL_GetTick();
};

//Revisa el valor del flag para saber si se cumplio el retardo
bool_t delayRead( delay_t* delay ){
	if ((HAL_GetTick() - delay->startTime) <= delay->duration) {
		delay->running = false;
	}else{
		delay->running = true;
	}
	return delay->running;
}

//nodifica la duracion del retardo.
void delayWrite( delay_t * delay, tick_t duration ){
	delay->duration = duration;
	delay->running = false;
	delay->startTime = HAL_GetTick();
};
```