################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../FreeRTOS/portable/RVDS/ARM7_LPC21xx/portASM.s 

C_SRCS += \
../FreeRTOS/portable/RVDS/ARM7_LPC21xx/port.c 

OBJS += \
./FreeRTOS/portable/RVDS/ARM7_LPC21xx/port.o \
./FreeRTOS/portable/RVDS/ARM7_LPC21xx/portASM.o 

C_DEPS += \
./FreeRTOS/portable/RVDS/ARM7_LPC21xx/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/RVDS/ARM7_LPC21xx/%.o: ../FreeRTOS/portable/RVDS/ARM7_LPC21xx/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"E:\Workspace2\SimpleDemo" -I"E:\Workspace2\CMSISv1p30_LPC17xx\inc" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/portable/RVDS/ARM7_LPC21xx/%.o: ../FreeRTOS/portable/RVDS/ARM7_LPC21xx/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -DDEBUG -D__CODE_RED -D__REDLIB__ -g3 -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


