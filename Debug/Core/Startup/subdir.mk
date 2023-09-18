################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32g070rbtx.s 

OBJS += \
./Core/Startup/startup_stm32g070rbtx.o 

S_DEPS += \
./Core/Startup/startup_stm32g070rbtx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -I"/home/vinhtran/Documents/C-Project/heralink/utils" -I"/home/vinhtran/Documents/C-Project/heralink/libs" -I"/home/vinhtran/Documents/C-Project/heralink/drvs" -I"/home/vinhtran/Documents/C-Project/heralink/app" -I"/home/vinhtran/Documents/C-Project/heralink/utils/inc" -I"/home/vinhtran/Documents/C-Project/heralink/libs/inc" -I"/home/vinhtran/Documents/C-Project/heralink/drvs/inc" -I"/home/vinhtran/Documents/C-Project/heralink/app/inc" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32g070rbtx.d ./Core/Startup/startup_stm32g070rbtx.o

.PHONY: clean-Core-2f-Startup

