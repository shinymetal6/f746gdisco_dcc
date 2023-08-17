################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/BSP/Components/ft5336/ft5336.c 

OBJS += \
./Libraries/BSP/Components/ft5336/ft5336.o 

C_DEPS += \
./Libraries/BSP/Components/ft5336/ft5336.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/BSP/Components/ft5336/%.o Libraries/BSP/Components/ft5336/%.su Libraries/BSP/Components/ft5336/%.cyclo: ../Libraries/BSP/Components/ft5336/%.c Libraries/BSP/Components/ft5336/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Libraries/Application -I../Libraries/BSP/F746Disco -I../Libraries/BSP/Components -I../Libraries/BSP/Common -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-BSP-2f-Components-2f-ft5336

clean-Libraries-2f-BSP-2f-Components-2f-ft5336:
	-$(RM) ./Libraries/BSP/Components/ft5336/ft5336.cyclo ./Libraries/BSP/Components/ft5336/ft5336.d ./Libraries/BSP/Components/ft5336/ft5336.o ./Libraries/BSP/Components/ft5336/ft5336.su

.PHONY: clean-Libraries-2f-BSP-2f-Components-2f-ft5336

