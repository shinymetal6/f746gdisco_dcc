################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Application/dcc_main.c \
../Libraries/Application/dcc_parser.c \
../Libraries/Application/dcc_timpwm_functions.c \
../Libraries/Application/lcd.c 

OBJS += \
./Libraries/Application/dcc_main.o \
./Libraries/Application/dcc_parser.o \
./Libraries/Application/dcc_timpwm_functions.o \
./Libraries/Application/lcd.o 

C_DEPS += \
./Libraries/Application/dcc_main.d \
./Libraries/Application/dcc_parser.d \
./Libraries/Application/dcc_timpwm_functions.d \
./Libraries/Application/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Application/%.o Libraries/Application/%.su Libraries/Application/%.cyclo: ../Libraries/Application/%.c Libraries/Application/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Libraries/Application -I../Libraries/BSP/F746Disco -I../Libraries/BSP/Components -I../Libraries/BSP/Common -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-Application

clean-Libraries-2f-Application:
	-$(RM) ./Libraries/Application/dcc_main.cyclo ./Libraries/Application/dcc_main.d ./Libraries/Application/dcc_main.o ./Libraries/Application/dcc_main.su ./Libraries/Application/dcc_parser.cyclo ./Libraries/Application/dcc_parser.d ./Libraries/Application/dcc_parser.o ./Libraries/Application/dcc_parser.su ./Libraries/Application/dcc_timpwm_functions.cyclo ./Libraries/Application/dcc_timpwm_functions.d ./Libraries/Application/dcc_timpwm_functions.o ./Libraries/Application/dcc_timpwm_functions.su ./Libraries/Application/lcd.cyclo ./Libraries/Application/lcd.d ./Libraries/Application/lcd.o ./Libraries/Application/lcd.su

.PHONY: clean-Libraries-2f-Application

