################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drvs/adc_driver.c \
../drvs/max1538_driver.c \
../drvs/spi_driver.c 

OBJS += \
./drvs/adc_driver.o \
./drvs/max1538_driver.o \
./drvs/spi_driver.o 

C_DEPS += \
./drvs/adc_driver.d \
./drvs/max1538_driver.d \
./drvs/spi_driver.d 


# Each subdirectory must supply rules for building sources it contributes
drvs/%.o drvs/%.su drvs/%.cyclo: ../drvs/%.c drvs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G070xx -DSTM32_THREAD_SAFE_STRATEGY=4 '-DCMSIS_device_header=<stm32g0xx.h>' -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"/home/vinhtran/Documents/C-Project/heralink/utils" -I"/home/vinhtran/Documents/C-Project/heralink/libs" -I"/home/vinhtran/Documents/C-Project/heralink/drvs" -I"/home/vinhtran/Documents/C-Project/heralink/app" -I"/home/vinhtran/Documents/C-Project/heralink/utils/inc" -I"/home/vinhtran/Documents/C-Project/heralink/libs/inc" -I"/home/vinhtran/Documents/C-Project/heralink/drvs/inc" -I"/home/vinhtran/Documents/C-Project/heralink/app/inc" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../Core/ThreadSafe -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-drvs

clean-drvs:
	-$(RM) ./drvs/adc_driver.cyclo ./drvs/adc_driver.d ./drvs/adc_driver.o ./drvs/adc_driver.su ./drvs/max1538_driver.cyclo ./drvs/max1538_driver.d ./drvs/max1538_driver.o ./drvs/max1538_driver.su ./drvs/spi_driver.cyclo ./drvs/spi_driver.d ./drvs/spi_driver.o ./drvs/spi_driver.su

.PHONY: clean-drvs

