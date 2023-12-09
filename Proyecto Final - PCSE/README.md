# PROYECTO FINAL - Protocolos de comunicacion en Sistemas Embebidos.

## Objetivo
Consiste en un sistema de control de temperatura, la misma debe mostrarse sobre una pantalla LCD, según su valor el sistema puede encontrarse en tres estados (Estable, Precaución y Peligro), dicho estado debe por visualizar junto con la temperatura. Los valores que son visualizados en la pantalla LCD tambien son reportados cada determinado tiempo por el puerto UART1 por lo que pueden verse lo mismos a traves de un puerto serie en la computadora.

El sistema debe actuar en consecuencia al estado en que se encuentra:
Estable: Debe presentar la temp en el display, FAN OFF y ALARM OFF
Precaución: Debe presentar la temp en el display, FAN ON y ALARM OFF
Peligro: Debe presentar la temp en el display, FAN ON y ALARM ON

## Funcionamiento
El sistema se encuentra constantemente midiendo la temperatura a través de un sensor de temperatura analógico, cuando la temperatura es menor a un valor de umbral T1, podemos decir que se encuentra en un estado ESTABLE. Cuando la temperatura empieza a ascender y sobre pasa este primer umbral T1, pero se mantiene por debajo de un segundo umbral T2, el sistema entra en estado de PRECAUCIÓN, en este estado se trata de descender la temperatura por medio de un FAN comandado por un GPIO. Si la temperatura sigue aumento y supera el umbral T2, entonces el sistema entra en un estado de PELIGRO, en este estado no solo el FAN se encuentra encendido, sino que también se dispara una ALARMA que debe informar a algún centro de supervisión operativo del problema, esta alarma se trata de un GPIO conectado a algún contacto de alarma.

## Implementación del Hardware
Para la implementación se utilizaron lo siguiente elementos de hardware:
1) Placa Nucleo STM32F429ZI-DISC: microcontrolador
2) FAN: el actuador que conecta el FAN sera simulado por el LED verde de la placa STM.
3) ALARMA: el contacto que disparar la alarma sera simulado con el LED rojo de placa STM
4) SENSOR DE TEMPERARA ANALOG: Sera simulado por medio del uso de un potenciómetro.
5) PANTALLA LDC 2X16 + PCF8574 – I2C: Para visualizar los datos.

## Maquina de estado finito del Sistema
En la imagen de abajo se ve la maquina de estado del sistema, con sus respectivos estados, entradas y salidas.
![](/img/004.png)

## Estructura de Archivos del Desarrollo
Por cada periférico utilizado se creo un archivo port_”periférico”, con el fin de abstraernos del software estos archivos contendrán las funciones de la hal de ST. Por ejemplo la pantalla LCD tiene su desarrollado de funciones para su uso, pero al usar el periférico I2C,  las llamadas a la hal se hacen a través del archivo port_ic2.
En la imagen podemos ver la estructura completa de los archivos.
![](/img/005.png)


