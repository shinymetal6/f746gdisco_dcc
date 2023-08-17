################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Fonts/font12.c \
../Drivers/BSP/Fonts/font16.c \
../Drivers/BSP/Fonts/font20.c \
../Drivers/BSP/Fonts/font24.c \
../Drivers/BSP/Fonts/font8.c 

OBJS += \
./Drivers/BSP/Fonts/font12.o \
./Drivers/BSP/Fonts/font16.o \
./Drivers/BSP/Fonts/font20.o \
./Drivers/BSP/Fonts/font24.o \
./Drivers/BSP/Fonts/font8.o 

C_DEPS += \
./Drivers/BSP/Fonts/font12.d \
./Drivers/BSP/Fonts/font16.d \
./Drivers/BSP/Fonts/font20.d \
./Drivers/BSP/Fonts/font24.d \
./Drivers/BSP/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Fonts/%.o Drivers/BSP/Fonts/%.su Drivers/BSP/Fonts/%.cyclo: ../Drivers/BSP/Fonts/%.c Drivers/BSP/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Libraries/Application -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components -I../Drivers/BSP/F746Disco -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Fonts

clean-Drivers-2f-BSP-2f-Fonts:
	-$(RM) ./Drivers/BSP/Fonts/font12.cyclo ./Drivers/BSP/Fonts/font12.d ./Drivers/BSP/Fonts/font12.o ./Drivers/BSP/Fonts/font12.su ./Drivers/BSP/Fonts/font16.cyclo ./Drivers/BSP/Fonts/font16.d ./Drivers/BSP/Fonts/font16.o ./Drivers/BSP/Fonts/font16.su ./Drivers/BSP/Fonts/font20.cyclo ./Drivers/BSP/Fonts/font20.d ./Drivers/BSP/Fonts/font20.o ./Drivers/BSP/Fonts/font20.su ./Drivers/BSP/Fonts/font24.cyclo ./Drivers/BSP/Fonts/font24.d ./Drivers/BSP/Fonts/font24.o ./Drivers/BSP/Fonts/font24.su ./Drivers/BSP/Fonts/font8.cyclo ./Drivers/BSP/Fonts/font8.d ./Drivers/BSP/Fonts/font8.o ./Drivers/BSP/Fonts/font8.su

.PHONY: clean-Drivers-2f-BSP-2f-Fonts

