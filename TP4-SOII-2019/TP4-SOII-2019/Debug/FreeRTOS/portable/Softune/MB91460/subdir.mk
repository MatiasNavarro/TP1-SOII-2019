################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/portable/Softune/MB91460/__STD_LIB_sbrk.c \
../FreeRTOS/portable/Softune/MB91460/port.c 

OBJS += \
./FreeRTOS/portable/Softune/MB91460/__STD_LIB_sbrk.o \
./FreeRTOS/portable/Softune/MB91460/port.o 

C_DEPS += \
./FreeRTOS/portable/Softune/MB91460/__STD_LIB_sbrk.d \
./FreeRTOS/portable/Softune/MB91460/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/Softune/MB91460/%.o: ../FreeRTOS/portable/Softune/MB91460/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"E:\Workspace2\SimpleDemo" -I"E:\Workspace2\CMSISv1p30_LPC17xx\inc" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


