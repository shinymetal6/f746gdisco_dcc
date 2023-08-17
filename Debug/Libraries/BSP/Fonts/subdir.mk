################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/BSP/Fonts/font12.c \
../Libraries/BSP/Fonts/font16.c \
../Libraries/BSP/Fonts/font20.c \
../Libraries/BSP/Fonts/font24.c \
../Libraries/BSP/Fonts/font8.c 

OBJS += \
./Libraries/BSP/Fonts/font12.o \
./Libraries/BSP/Fonts/font16.o \
./Libraries/BSP/Fonts/font20.o \
./Libraries/BSP/Fonts/font24.o \
./Libraries/BSP/Fonts/font8.o 

C_DEPS += \
./Libraries/BSP/Fonts/font12.d \
./Libraries/BSP/Fonts/font16.d \
./Libraries/BSP/Fonts/font20.d \
./Libraries/BSP/Fonts/font24.d \
./Libraries/BSP/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/BSP/Fonts/%.o Libraries/BSP/Fonts/%.su Libraries/BSP/Fonts/%.cyclo: ../Libraries/BSP/Fonts/%.c Libraries/BSP/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Libraries/Application -I../Libraries/BSP/F746Disco -I../Libraries/BSP/Components -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-BSP-2f-Fonts

clean-Libraries-2f-BSP-2f-Fonts:
	-$(RM) ./Libraries/BSP/Fonts/font12.cyclo ./Libraries/BSP/Fonts/font12.d ./Libraries/BSP/Fonts/font12.o ./Libraries/BSP/Fonts/font12.su ./Libraries/BSP/Fonts/font16.cyclo ./Libraries/BSP/Fonts/font16.d ./Libraries/BSP/Fonts/font16.o ./Libraries/BSP/Fonts/font16.su ./Libraries/BSP/Fonts/font20.cyclo ./Libraries/BSP/Fonts/font20.d ./Libraries/BSP/Fonts/font20.o ./Libraries/BSP/Fonts/font20.su ./Libraries/BSP/Fonts/font24.cyclo ./Libraries/BSP/Fonts/font24.d ./Libraries/BSP/Fonts/font24.o ./Libraries/BSP/Fonts/font24.su ./Libraries/BSP/Fonts/font8.cyclo ./Libraries/BSP/Fonts/font8.d ./Libraries/BSP/Fonts/font8.o ./Libraries/BSP/Fonts/font8.su

.PHONY: clean-Libraries-2f-BSP-2f-Fonts

