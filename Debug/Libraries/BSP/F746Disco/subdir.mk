################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/BSP/F746Disco/stm32746g_discovery.c \
../Libraries/BSP/F746Disco/stm32746g_discovery_audio.c \
../Libraries/BSP/F746Disco/stm32746g_discovery_camera.c \
../Libraries/BSP/F746Disco/stm32746g_discovery_eeprom.c \
../Libraries/BSP/F746Disco/stm32746g_discovery_lcd.c \
../Libraries/BSP/F746Disco/stm32746g_discovery_qspi.c \
../Libraries/BSP/F746Disco/stm32746g_discovery_sd.c \
../Libraries/BSP/F746Disco/stm32746g_discovery_sdram.c \
../Libraries/BSP/F746Disco/stm32746g_discovery_ts.c 

OBJS += \
./Libraries/BSP/F746Disco/stm32746g_discovery.o \
./Libraries/BSP/F746Disco/stm32746g_discovery_audio.o \
./Libraries/BSP/F746Disco/stm32746g_discovery_camera.o \
./Libraries/BSP/F746Disco/stm32746g_discovery_eeprom.o \
./Libraries/BSP/F746Disco/stm32746g_discovery_lcd.o \
./Libraries/BSP/F746Disco/stm32746g_discovery_qspi.o \
./Libraries/BSP/F746Disco/stm32746g_discovery_sd.o \
./Libraries/BSP/F746Disco/stm32746g_discovery_sdram.o \
./Libraries/BSP/F746Disco/stm32746g_discovery_ts.o 

C_DEPS += \
./Libraries/BSP/F746Disco/stm32746g_discovery.d \
./Libraries/BSP/F746Disco/stm32746g_discovery_audio.d \
./Libraries/BSP/F746Disco/stm32746g_discovery_camera.d \
./Libraries/BSP/F746Disco/stm32746g_discovery_eeprom.d \
./Libraries/BSP/F746Disco/stm32746g_discovery_lcd.d \
./Libraries/BSP/F746Disco/stm32746g_discovery_qspi.d \
./Libraries/BSP/F746Disco/stm32746g_discovery_sd.d \
./Libraries/BSP/F746Disco/stm32746g_discovery_sdram.d \
./Libraries/BSP/F746Disco/stm32746g_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/BSP/F746Disco/%.o Libraries/BSP/F746Disco/%.su Libraries/BSP/F746Disco/%.cyclo: ../Libraries/BSP/F746Disco/%.c Libraries/BSP/F746Disco/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Libraries/Application -I../Libraries/BSP/F746Disco -I../Libraries/BSP/Components -I../Libraries/BSP/Common -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-BSP-2f-F746Disco

clean-Libraries-2f-BSP-2f-F746Disco:
	-$(RM) ./Libraries/BSP/F746Disco/stm32746g_discovery.cyclo ./Libraries/BSP/F746Disco/stm32746g_discovery.d ./Libraries/BSP/F746Disco/stm32746g_discovery.o ./Libraries/BSP/F746Disco/stm32746g_discovery.su ./Libraries/BSP/F746Disco/stm32746g_discovery_audio.cyclo ./Libraries/BSP/F746Disco/stm32746g_discovery_audio.d ./Libraries/BSP/F746Disco/stm32746g_discovery_audio.o ./Libraries/BSP/F746Disco/stm32746g_discovery_audio.su ./Libraries/BSP/F746Disco/stm32746g_discovery_camera.cyclo ./Libraries/BSP/F746Disco/stm32746g_discovery_camera.d ./Libraries/BSP/F746Disco/stm32746g_discovery_camera.o ./Libraries/BSP/F746Disco/stm32746g_discovery_camera.su ./Libraries/BSP/F746Disco/stm32746g_discovery_eeprom.cyclo ./Libraries/BSP/F746Disco/stm32746g_discovery_eeprom.d ./Libraries/BSP/F746Disco/stm32746g_discovery_eeprom.o ./Libraries/BSP/F746Disco/stm32746g_discovery_eeprom.su ./Libraries/BSP/F746Disco/stm32746g_discovery_lcd.cyclo ./Libraries/BSP/F746Disco/stm32746g_discovery_lcd.d ./Libraries/BSP/F746Disco/stm32746g_discovery_lcd.o ./Libraries/BSP/F746Disco/stm32746g_discovery_lcd.su ./Libraries/BSP/F746Disco/stm32746g_discovery_qspi.cyclo ./Libraries/BSP/F746Disco/stm32746g_discovery_qspi.d ./Libraries/BSP/F746Disco/stm32746g_discovery_qspi.o ./Libraries/BSP/F746Disco/stm32746g_discovery_qspi.su ./Libraries/BSP/F746Disco/stm32746g_discovery_sd.cyclo ./Libraries/BSP/F746Disco/stm32746g_discovery_sd.d ./Libraries/BSP/F746Disco/stm32746g_discovery_sd.o ./Libraries/BSP/F746Disco/stm32746g_discovery_sd.su ./Libraries/BSP/F746Disco/stm32746g_discovery_sdram.cyclo ./Libraries/BSP/F746Disco/stm32746g_discovery_sdram.d ./Libraries/BSP/F746Disco/stm32746g_discovery_sdram.o ./Libraries/BSP/F746Disco/stm32746g_discovery_sdram.su ./Libraries/BSP/F746Disco/stm32746g_discovery_ts.cyclo ./Libraries/BSP/F746Disco/stm32746g_discovery_ts.d ./Libraries/BSP/F746Disco/stm32746g_discovery_ts.o ./Libraries/BSP/F746Disco/stm32746g_discovery_ts.su

.PHONY: clean-Libraries-2f-BSP-2f-F746Disco

