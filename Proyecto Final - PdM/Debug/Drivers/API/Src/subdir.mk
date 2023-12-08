################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/API_delay.c \
../Drivers/API/Src/LCD_2X16_HD44780.c \
../Drivers/API/Src/MEF.c \
../Drivers/API/Src/SENSOR_Temp.c \
../Drivers/API/Src/port_i2c.c 

OBJS += \
./Drivers/API/Src/API_delay.o \
./Drivers/API/Src/LCD_2X16_HD44780.o \
./Drivers/API/Src/MEF.o \
./Drivers/API/Src/SENSOR_Temp.o \
./Drivers/API/Src/port_i2c.o 

C_DEPS += \
./Drivers/API/Src/API_delay.d \
./Drivers/API/Src/LCD_2X16_HD44780.d \
./Drivers/API/Src/MEF.d \
./Drivers/API/Src/SENSOR_Temp.d \
./Drivers/API/Src/port_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/%.o Drivers/API/Src/%.su Drivers/API/Src/%.cyclo: ../Drivers/API/Src/%.c Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ubuntu22/CESE/001ProgDeMicro/PdM_workspace/Proyecto Final - PdM/Drivers/API/Inc" -I"/home/ubuntu22/CESE/001ProgDeMicro/PdM_workspace/Proyecto Final - PdM/Drivers/API/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src

clean-Drivers-2f-API-2f-Src:
	-$(RM) ./Drivers/API/Src/API_delay.cyclo ./Drivers/API/Src/API_delay.d ./Drivers/API/Src/API_delay.o ./Drivers/API/Src/API_delay.su ./Drivers/API/Src/LCD_2X16_HD44780.cyclo ./Drivers/API/Src/LCD_2X16_HD44780.d ./Drivers/API/Src/LCD_2X16_HD44780.o ./Drivers/API/Src/LCD_2X16_HD44780.su ./Drivers/API/Src/MEF.cyclo ./Drivers/API/Src/MEF.d ./Drivers/API/Src/MEF.o ./Drivers/API/Src/MEF.su ./Drivers/API/Src/SENSOR_Temp.cyclo ./Drivers/API/Src/SENSOR_Temp.d ./Drivers/API/Src/SENSOR_Temp.o ./Drivers/API/Src/SENSOR_Temp.su ./Drivers/API/Src/port_i2c.cyclo ./Drivers/API/Src/port_i2c.d ./Drivers/API/Src/port_i2c.o ./Drivers/API/Src/port_i2c.su

.PHONY: clean-Drivers-2f-API-2f-Src

