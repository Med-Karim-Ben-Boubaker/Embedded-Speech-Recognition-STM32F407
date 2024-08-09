################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Src/FIR_Filter_Coef.c \
../Drivers/BSP/Src/MP45DT02-MEMS-Microphone.c 

OBJS += \
./Drivers/BSP/Src/FIR_Filter_Coef.o \
./Drivers/BSP/Src/MP45DT02-MEMS-Microphone.o 

C_DEPS += \
./Drivers/BSP/Src/FIR_Filter_Coef.d \
./Drivers/BSP/Src/MP45DT02-MEMS-Microphone.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Src/%.o Drivers/BSP/Src/%.su Drivers/BSP/Src/%.cyclo: ../Drivers/BSP/Src/%.c Drivers/BSP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -I../Drivers/BSP/Inc -I../AUDIO_PROCESSING_UTILS/Inc -I../Drivers/STM32_AI_AudioPreprocessing_Library/Inc -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Src

clean-Drivers-2f-BSP-2f-Src:
	-$(RM) ./Drivers/BSP/Src/FIR_Filter_Coef.cyclo ./Drivers/BSP/Src/FIR_Filter_Coef.d ./Drivers/BSP/Src/FIR_Filter_Coef.o ./Drivers/BSP/Src/FIR_Filter_Coef.su ./Drivers/BSP/Src/MP45DT02-MEMS-Microphone.cyclo ./Drivers/BSP/Src/MP45DT02-MEMS-Microphone.d ./Drivers/BSP/Src/MP45DT02-MEMS-Microphone.o ./Drivers/BSP/Src/MP45DT02-MEMS-Microphone.su

.PHONY: clean-Drivers-2f-BSP-2f-Src

