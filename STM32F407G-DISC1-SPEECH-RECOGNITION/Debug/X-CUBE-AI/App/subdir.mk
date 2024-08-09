################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../X-CUBE-AI/App/audio_classifier.c \
../X-CUBE-AI/App/audio_classifier_data.c \
../X-CUBE-AI/App/audio_classifier_data_params.c 

OBJS += \
./X-CUBE-AI/App/audio_classifier.o \
./X-CUBE-AI/App/audio_classifier_data.o \
./X-CUBE-AI/App/audio_classifier_data_params.o 

C_DEPS += \
./X-CUBE-AI/App/audio_classifier.d \
./X-CUBE-AI/App/audio_classifier_data.d \
./X-CUBE-AI/App/audio_classifier_data_params.d 


# Each subdirectory must supply rules for building sources it contributes
X-CUBE-AI/App/%.o X-CUBE-AI/App/%.su X-CUBE-AI/App/%.cyclo: ../X-CUBE-AI/App/%.c X-CUBE-AI/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -I../Drivers/BSP/Inc -I../AUDIO_PROCESSING_UTILS/Inc -I../Drivers/STM32_AI_AudioPreprocessing_Library/Inc -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-X-2d-CUBE-2d-AI-2f-App

clean-X-2d-CUBE-2d-AI-2f-App:
	-$(RM) ./X-CUBE-AI/App/audio_classifier.cyclo ./X-CUBE-AI/App/audio_classifier.d ./X-CUBE-AI/App/audio_classifier.o ./X-CUBE-AI/App/audio_classifier.su ./X-CUBE-AI/App/audio_classifier_data.cyclo ./X-CUBE-AI/App/audio_classifier_data.d ./X-CUBE-AI/App/audio_classifier_data.o ./X-CUBE-AI/App/audio_classifier_data.su ./X-CUBE-AI/App/audio_classifier_data_params.cyclo ./X-CUBE-AI/App/audio_classifier_data_params.d ./X-CUBE-AI/App/audio_classifier_data_params.o ./X-CUBE-AI/App/audio_classifier_data_params.su

.PHONY: clean-X-2d-CUBE-2d-AI-2f-App

