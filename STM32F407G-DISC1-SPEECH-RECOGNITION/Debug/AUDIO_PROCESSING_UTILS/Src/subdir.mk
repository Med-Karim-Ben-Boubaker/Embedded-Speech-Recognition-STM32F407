################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AUDIO_PROCESSING_UTILS/Src/audio_utils.c 

OBJS += \
./AUDIO_PROCESSING_UTILS/Src/audio_utils.o 

C_DEPS += \
./AUDIO_PROCESSING_UTILS/Src/audio_utils.d 


# Each subdirectory must supply rules for building sources it contributes
AUDIO_PROCESSING_UTILS/Src/%.o AUDIO_PROCESSING_UTILS/Src/%.su AUDIO_PROCESSING_UTILS/Src/%.cyclo: ../AUDIO_PROCESSING_UTILS/Src/%.c AUDIO_PROCESSING_UTILS/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -I../Drivers/BSP/Inc -I../AUDIO_PROCESSING_UTILS/Inc -I../Drivers/STM32_AI_AudioPreprocessing_Library/Inc -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-AUDIO_PROCESSING_UTILS-2f-Src

clean-AUDIO_PROCESSING_UTILS-2f-Src:
	-$(RM) ./AUDIO_PROCESSING_UTILS/Src/audio_utils.cyclo ./AUDIO_PROCESSING_UTILS/Src/audio_utils.d ./AUDIO_PROCESSING_UTILS/Src/audio_utils.o ./AUDIO_PROCESSING_UTILS/Src/audio_utils.su

.PHONY: clean-AUDIO_PROCESSING_UTILS-2f-Src

