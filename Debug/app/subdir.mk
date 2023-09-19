################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/adc_convert.c \
../app/battery_controller.c \
../app/heralink.c \
../app/max1538.c \
../app/spi_slave.c 

OBJS += \
./app/adc_convert.o \
./app/battery_controller.o \
./app/heralink.o \
./app/max1538.o \
./app/spi_slave.o 

C_DEPS += \
./app/adc_convert.d \
./app/battery_controller.d \
./app/heralink.d \
./app/max1538.d \
./app/spi_slave.d 


# Each subdirectory must supply rules for building sources it contributes
app/%.o app/%.su app/%.cyclo: ../app/%.c app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G070xx -DSTM32_THREAD_SAFE_STRATEGY=4 '-DCMSIS_device_header=<stm32g0xx.h>' -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/Desktop/VinhTran/heralink/drvs" -I"C:/Users/Admin/Desktop/VinhTran/heralink/app" -I"C:/Users/Admin/Desktop/VinhTran/heralink/drvs/inc" -I"C:/Users/Admin/Desktop/VinhTran/heralink/app/inc" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../Core/ThreadSafe -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-app

clean-app:
	-$(RM) ./app/adc_convert.cyclo ./app/adc_convert.d ./app/adc_convert.o ./app/adc_convert.su ./app/battery_controller.cyclo ./app/battery_controller.d ./app/battery_controller.o ./app/battery_controller.su ./app/heralink.cyclo ./app/heralink.d ./app/heralink.o ./app/heralink.su ./app/max1538.cyclo ./app/max1538.d ./app/max1538.o ./app/max1538.su ./app/spi_slave.cyclo ./app/spi_slave.d ./app/spi_slave.o ./app/spi_slave.su

.PHONY: clean-app

