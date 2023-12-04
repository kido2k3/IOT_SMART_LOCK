################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/main.c \
../Core/Src/my_fsm.c \
../Core/Src/my_keypad.c \
../Core/Src/my_lcd.c \
../Core/Src/my_lock.c \
../Core/Src/my_password.c \
../Core/Src/my_scheduler.c \
../Core/Src/my_sensor.c \
../Core/Src/my_system.c \
../Core/Src/my_uart.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/main.o \
./Core/Src/my_fsm.o \
./Core/Src/my_keypad.o \
./Core/Src/my_lcd.o \
./Core/Src/my_lock.o \
./Core/Src/my_password.o \
./Core/Src/my_scheduler.o \
./Core/Src/my_sensor.o \
./Core/Src/my_system.o \
./Core/Src/my_uart.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/main.d \
./Core/Src/my_fsm.d \
./Core/Src/my_keypad.d \
./Core/Src/my_lcd.d \
./Core/Src/my_lock.d \
./Core/Src/my_password.d \
./Core/Src/my_scheduler.d \
./Core/Src/my_sensor.d \
./Core/Src/my_system.d \
./Core/Src/my_uart.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/my_fsm.cyclo ./Core/Src/my_fsm.d ./Core/Src/my_fsm.o ./Core/Src/my_fsm.su ./Core/Src/my_keypad.cyclo ./Core/Src/my_keypad.d ./Core/Src/my_keypad.o ./Core/Src/my_keypad.su ./Core/Src/my_lcd.cyclo ./Core/Src/my_lcd.d ./Core/Src/my_lcd.o ./Core/Src/my_lcd.su ./Core/Src/my_lock.cyclo ./Core/Src/my_lock.d ./Core/Src/my_lock.o ./Core/Src/my_lock.su ./Core/Src/my_password.cyclo ./Core/Src/my_password.d ./Core/Src/my_password.o ./Core/Src/my_password.su ./Core/Src/my_scheduler.cyclo ./Core/Src/my_scheduler.d ./Core/Src/my_scheduler.o ./Core/Src/my_scheduler.su ./Core/Src/my_sensor.cyclo ./Core/Src/my_sensor.d ./Core/Src/my_sensor.o ./Core/Src/my_sensor.su ./Core/Src/my_system.cyclo ./Core/Src/my_system.d ./Core/Src/my_system.o ./Core/Src/my_system.su ./Core/Src/my_uart.cyclo ./Core/Src/my_uart.d ./Core/Src/my_uart.o ./Core/Src/my_uart.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

