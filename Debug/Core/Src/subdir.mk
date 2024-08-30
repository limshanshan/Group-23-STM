################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ICM20948.c \
../Core/Src/PIDController.c \
../Core/Src/calAngle.c \
../Core/Src/calDistance.c \
../Core/Src/calc_conversions.c \
../Core/Src/cmds.c \
../Core/Src/display.c \
../Core/Src/kalmanFilter.c \
../Core/Src/leftrightmotor.c \
../Core/Src/magnetometer.c \
../Core/Src/main.c \
../Core/Src/movement.c \
../Core/Src/oled.c \
../Core/Src/sensorstuff.c \
../Core/Src/servomotor.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/ultrasonicsensor.c \
../Core/Src/userbutton.c 

OBJS += \
./Core/Src/ICM20948.o \
./Core/Src/PIDController.o \
./Core/Src/calAngle.o \
./Core/Src/calDistance.o \
./Core/Src/calc_conversions.o \
./Core/Src/cmds.o \
./Core/Src/display.o \
./Core/Src/kalmanFilter.o \
./Core/Src/leftrightmotor.o \
./Core/Src/magnetometer.o \
./Core/Src/main.o \
./Core/Src/movement.o \
./Core/Src/oled.o \
./Core/Src/sensorstuff.o \
./Core/Src/servomotor.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/ultrasonicsensor.o \
./Core/Src/userbutton.o 

C_DEPS += \
./Core/Src/ICM20948.d \
./Core/Src/PIDController.d \
./Core/Src/calAngle.d \
./Core/Src/calDistance.d \
./Core/Src/calc_conversions.d \
./Core/Src/cmds.d \
./Core/Src/display.d \
./Core/Src/kalmanFilter.d \
./Core/Src/leftrightmotor.d \
./Core/Src/magnetometer.d \
./Core/Src/main.d \
./Core/Src/movement.d \
./Core/Src/oled.d \
./Core/Src/sensorstuff.d \
./Core/Src/servomotor.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/ultrasonicsensor.d \
./Core/Src/userbutton.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ICM20948.cyclo ./Core/Src/ICM20948.d ./Core/Src/ICM20948.o ./Core/Src/ICM20948.su ./Core/Src/PIDController.cyclo ./Core/Src/PIDController.d ./Core/Src/PIDController.o ./Core/Src/PIDController.su ./Core/Src/calAngle.cyclo ./Core/Src/calAngle.d ./Core/Src/calAngle.o ./Core/Src/calAngle.su ./Core/Src/calDistance.cyclo ./Core/Src/calDistance.d ./Core/Src/calDistance.o ./Core/Src/calDistance.su ./Core/Src/calc_conversions.cyclo ./Core/Src/calc_conversions.d ./Core/Src/calc_conversions.o ./Core/Src/calc_conversions.su ./Core/Src/cmds.cyclo ./Core/Src/cmds.d ./Core/Src/cmds.o ./Core/Src/cmds.su ./Core/Src/display.cyclo ./Core/Src/display.d ./Core/Src/display.o ./Core/Src/display.su ./Core/Src/kalmanFilter.cyclo ./Core/Src/kalmanFilter.d ./Core/Src/kalmanFilter.o ./Core/Src/kalmanFilter.su ./Core/Src/leftrightmotor.cyclo ./Core/Src/leftrightmotor.d ./Core/Src/leftrightmotor.o ./Core/Src/leftrightmotor.su ./Core/Src/magnetometer.cyclo ./Core/Src/magnetometer.d ./Core/Src/magnetometer.o ./Core/Src/magnetometer.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/movement.cyclo ./Core/Src/movement.d ./Core/Src/movement.o ./Core/Src/movement.su ./Core/Src/oled.cyclo ./Core/Src/oled.d ./Core/Src/oled.o ./Core/Src/oled.su ./Core/Src/sensorstuff.cyclo ./Core/Src/sensorstuff.d ./Core/Src/sensorstuff.o ./Core/Src/sensorstuff.su ./Core/Src/servomotor.cyclo ./Core/Src/servomotor.d ./Core/Src/servomotor.o ./Core/Src/servomotor.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/ultrasonicsensor.cyclo ./Core/Src/ultrasonicsensor.d ./Core/Src/ultrasonicsensor.o ./Core/Src/ultrasonicsensor.su ./Core/Src/userbutton.cyclo ./Core/Src/userbutton.d ./Core/Src/userbutton.o ./Core/Src/userbutton.su

.PHONY: clean-Core-2f-Src

