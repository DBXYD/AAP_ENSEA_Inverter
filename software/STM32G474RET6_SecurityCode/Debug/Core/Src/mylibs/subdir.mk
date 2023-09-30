################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/mylibs/TCN75A.c \
../Core/Src/mylibs/break.c \
../Core/Src/mylibs/button.c \
../Core/Src/mylibs/fan.c \
../Core/Src/mylibs/lcd.c \
../Core/Src/mylibs/led.c \
../Core/Src/mylibs/rotary_encoder.c 

OBJS += \
./Core/Src/mylibs/TCN75A.o \
./Core/Src/mylibs/break.o \
./Core/Src/mylibs/button.o \
./Core/Src/mylibs/fan.o \
./Core/Src/mylibs/lcd.o \
./Core/Src/mylibs/led.o \
./Core/Src/mylibs/rotary_encoder.o 

C_DEPS += \
./Core/Src/mylibs/TCN75A.d \
./Core/Src/mylibs/break.d \
./Core/Src/mylibs/button.d \
./Core/Src/mylibs/fan.d \
./Core/Src/mylibs/lcd.d \
./Core/Src/mylibs/led.d \
./Core/Src/mylibs/rotary_encoder.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/mylibs/%.o Core/Src/mylibs/%.su Core/Src/mylibs/%.cyclo: ../Core/Src/mylibs/%.c Core/Src/mylibs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-mylibs

clean-Core-2f-Src-2f-mylibs:
	-$(RM) ./Core/Src/mylibs/TCN75A.cyclo ./Core/Src/mylibs/TCN75A.d ./Core/Src/mylibs/TCN75A.o ./Core/Src/mylibs/TCN75A.su ./Core/Src/mylibs/break.cyclo ./Core/Src/mylibs/break.d ./Core/Src/mylibs/break.o ./Core/Src/mylibs/break.su ./Core/Src/mylibs/button.cyclo ./Core/Src/mylibs/button.d ./Core/Src/mylibs/button.o ./Core/Src/mylibs/button.su ./Core/Src/mylibs/fan.cyclo ./Core/Src/mylibs/fan.d ./Core/Src/mylibs/fan.o ./Core/Src/mylibs/fan.su ./Core/Src/mylibs/lcd.cyclo ./Core/Src/mylibs/lcd.d ./Core/Src/mylibs/lcd.o ./Core/Src/mylibs/lcd.su ./Core/Src/mylibs/led.cyclo ./Core/Src/mylibs/led.d ./Core/Src/mylibs/led.o ./Core/Src/mylibs/led.su ./Core/Src/mylibs/rotary_encoder.cyclo ./Core/Src/mylibs/rotary_encoder.d ./Core/Src/mylibs/rotary_encoder.o ./Core/Src/mylibs/rotary_encoder.su

.PHONY: clean-Core-2f-Src-2f-mylibs

