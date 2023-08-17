################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/F746Disco/stm32746g_discovery.c \
../Drivers/BSP/F746Disco/stm32746g_discovery_audio.c \
../Drivers/BSP/F746Disco/stm32746g_discovery_camera.c \
../Drivers/BSP/F746Disco/stm32746g_discovery_eeprom.c \
../Drivers/BSP/F746Disco/stm32746g_discovery_lcd.c \
../Drivers/BSP/F746Disco/stm32746g_discovery_qspi.c \
../Drivers/BSP/F746Disco/stm32746g_discovery_sd.c \
../Drivers/BSP/F746Disco/stm32746g_discovery_sdram.c \
../Drivers/BSP/F746Disco/stm32746g_discovery_ts.c 

OBJS += \
./Drivers/BSP/F746Disco/stm32746g_discovery.o \
./Drivers/BSP/F746Disco/stm32746g_discovery_audio.o \
./Drivers/BSP/F746Disco/stm32746g_discovery_camera.o \
./Drivers/BSP/F746Disco/stm32746g_discovery_eeprom.o \
./Drivers/BSP/F746Disco/stm32746g_discovery_lcd.o \
./Drivers/BSP/F746Disco/stm32746g_discovery_qspi.o \
./Drivers/BSP/F746Disco/stm32746g_discovery_sd.o \
./Drivers/BSP/F746Disco/stm32746g_discovery_sdram.o \
./Drivers/BSP/F746Disco/stm32746g_discovery_ts.o 

C_DEPS += \
./Drivers/BSP/F746Disco/stm32746g_discovery.d \
./Drivers/BSP/F746Disco/stm32746g_discovery_audio.d \
./Drivers/BSP/F746Disco/stm32746g_discovery_camera.d \
./Drivers/BSP/F746Disco/stm32746g_discovery_eeprom.d \
./Drivers/BSP/F746Disco/stm32746g_discovery_lcd.d \
./Drivers/BSP/F746Disco/stm32746g_discovery_qspi.d \
./Drivers/BSP/F746Disco/stm32746g_discovery_sd.d \
./Drivers/BSP/F746Disco/stm32746g_discovery_sdram.d \
./Drivers/BSP/F746Disco/stm32746g_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/F746Disco/%.o Drivers/BSP/F746Disco/%.su Drivers/BSP/F746Disco/%.cyclo: ../Drivers/BSP/F746Disco/%.c Drivers/BSP/F746Disco/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Libraries/Application -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components -I../Drivers/BSP/F746Disco -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-F746Disco

clean-Drivers-2f-BSP-2f-F746Disco:
	-$(RM) ./Drivers/BSP/F746Disco/stm32746g_discovery.cyclo ./Drivers/BSP/F746Disco/stm32746g_discovery.d ./Drivers/BSP/F746Disco/stm32746g_discovery.o ./Drivers/BSP/F746Disco/stm32746g_discovery.su ./Drivers/BSP/F746Disco/stm32746g_discovery_audio.cyclo ./Drivers/BSP/F746Disco/stm32746g_discovery_audio.d ./Drivers/BSP/F746Disco/stm32746g_discovery_audio.o ./Drivers/BSP/F746Disco/stm32746g_discovery_audio.su ./Drivers/BSP/F746Disco/stm32746g_discovery_camera.cyclo ./Drivers/BSP/F746Disco/stm32746g_discovery_camera.d ./Drivers/BSP/F746Disco/stm32746g_discovery_camera.o ./Drivers/BSP/F746Disco/stm32746g_discovery_camera.su ./Drivers/BSP/F746Disco/stm32746g_discovery_eeprom.cyclo ./Drivers/BSP/F746Disco/stm32746g_discovery_eeprom.d ./Drivers/BSP/F746Disco/stm32746g_discovery_eeprom.o ./Drivers/BSP/F746Disco/stm32746g_discovery_eeprom.su ./Drivers/BSP/F746Disco/stm32746g_discovery_lcd.cyclo ./Drivers/BSP/F746Disco/stm32746g_discovery_lcd.d ./Drivers/BSP/F746Disco/stm32746g_discovery_lcd.o ./Drivers/BSP/F746Disco/stm32746g_discovery_lcd.su ./Drivers/BSP/F746Disco/stm32746g_discovery_qspi.cyclo ./Drivers/BSP/F746Disco/stm32746g_discovery_qspi.d ./Drivers/BSP/F746Disco/stm32746g_discovery_qspi.o ./Drivers/BSP/F746Disco/stm32746g_discovery_qspi.su ./Drivers/BSP/F746Disco/stm32746g_discovery_sd.cyclo ./Drivers/BSP/F746Disco/stm32746g_discovery_sd.d ./Drivers/BSP/F746Disco/stm32746g_discovery_sd.o ./Drivers/BSP/F746Disco/stm32746g_discovery_sd.su ./Drivers/BSP/F746Disco/stm32746g_discovery_sdram.cyclo ./Drivers/BSP/F746Disco/stm32746g_discovery_sdram.d ./Drivers/BSP/F746Disco/stm32746g_discovery_sdram.o ./Drivers/BSP/F746Disco/stm32746g_discovery_sdram.su ./Drivers/BSP/F746Disco/stm32746g_discovery_ts.cyclo ./Drivers/BSP/F746Disco/stm32746g_discovery_ts.d ./Drivers/BSP/F746Disco/stm32746g_discovery_ts.o ./Drivers/BSP/F746Disco/stm32746g_discovery_ts.su

.PHONY: clean-Drivers-2f-BSP-2f-F746Disco

