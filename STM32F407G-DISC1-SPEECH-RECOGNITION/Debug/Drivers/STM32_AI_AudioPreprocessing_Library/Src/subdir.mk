################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32_AI_AudioPreprocessing_Library/Src/common_tables.c \
../Drivers/STM32_AI_AudioPreprocessing_Library/Src/dct.c \
../Drivers/STM32_AI_AudioPreprocessing_Library/Src/feature_extraction.c \
../Drivers/STM32_AI_AudioPreprocessing_Library/Src/mel_filterbank.c \
../Drivers/STM32_AI_AudioPreprocessing_Library/Src/window.c 

OBJS += \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/common_tables.o \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/dct.o \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/feature_extraction.o \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/mel_filterbank.o \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/window.o 

C_DEPS += \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/common_tables.d \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/dct.d \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/feature_extraction.d \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/mel_filterbank.d \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/window.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32_AI_AudioPreprocessing_Library/Src/%.o Drivers/STM32_AI_AudioPreprocessing_Library/Src/%.su Drivers/STM32_AI_AudioPreprocessing_Library/Src/%.cyclo: ../Drivers/STM32_AI_AudioPreprocessing_Library/Src/%.c Drivers/STM32_AI_AudioPreprocessing_Library/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -I../Drivers/BSP/Inc -I../AUDIO_PROCESSING_UTILS/Inc -I../Drivers/STM32_AI_AudioPreprocessing_Library/Inc -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-STM32_AI_AudioPreprocessing_Library-2f-Src

clean-Drivers-2f-STM32_AI_AudioPreprocessing_Library-2f-Src:
	-$(RM) ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/common_tables.cyclo ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/common_tables.d ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/common_tables.o ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/common_tables.su ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/dct.cyclo ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/dct.d ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/dct.o ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/dct.su ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/feature_extraction.cyclo ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/feature_extraction.d ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/feature_extraction.o ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/feature_extraction.su ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/mel_filterbank.cyclo ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/mel_filterbank.d ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/mel_filterbank.o ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/mel_filterbank.su ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/window.cyclo ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/window.d ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/window.o ./Drivers/STM32_AI_AudioPreprocessing_Library/Src/window.su

.PHONY: clean-Drivers-2f-STM32_AI_AudioPreprocessing_Library-2f-Src

