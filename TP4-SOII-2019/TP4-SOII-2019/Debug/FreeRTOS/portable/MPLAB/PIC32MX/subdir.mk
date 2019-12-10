################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/portable/MPLAB/PIC32MX/port.c 

S_UPPER_SRCS += \
../FreeRTOS/portable/MPLAB/PIC32MX/port_asm.S 

OBJS += \
./FreeRTOS/portable/MPLAB/PIC32MX/port.o \
./FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o 

C_DEPS += \
./FreeRTOS/portable/MPLAB/PIC32MX/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/MPLAB/PIC32MX/%.o: ../FreeRTOS/portable/MPLAB/PIC32MX/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"E:\Workspace2\SimpleDemo" -I"E:\Workspace2\CMSISv1p30_LPC17xx\inc" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/portable/MPLAB/PIC32MX/%.o: ../FreeRTOS/portable/MPLAB/PIC32MX/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -DDEBUG -D__CODE_RED -D__REDLIB__ -g3 -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


