################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/portable/GCC/ARM_CM0/port.c 

OBJS += \
./FreeRTOS/portable/GCC/ARM_CM0/port.o 

C_DEPS += \
./FreeRTOS/portable/GCC/ARM_CM0/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/GCC/ARM_CM0/%.o: ../FreeRTOS/portable/GCC/ARM_CM0/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"E:/PROGRAMOWANIE/KDS_DEV/CAN_FreeRTOS/Static_Code/System" -I"E:/PROGRAMOWANIE/KDS_DEV/CAN_FreeRTOS/Static_Code/PDD" -I"E:/PROGRAMOWANIE/KDS_DEV/CAN_FreeRTOS/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"E:/PROGRAMOWANIE/KDS_DEV/CAN_FreeRTOS/Sources" -I"E:/PROGRAMOWANIE/KDS_DEV/CAN_FreeRTOS/Generated_Code" -I"E:\PROGRAMOWANIE\KDS_DEV\CAN_FreeRTOS\FreeRTOS" -I"E:\PROGRAMOWANIE\KDS_DEV\CAN_FreeRTOS\FreeRTOS\include" -I"E:\PROGRAMOWANIE\KDS_DEV\CAN_FreeRTOS\FreeRTOS\portable" -I"E:\PROGRAMOWANIE\KDS_DEV\CAN_FreeRTOS\FreeRTOS\portable\MemMang" -I"E:\PROGRAMOWANIE\KDS_DEV\CAN_FreeRTOS\FreeRTOS\portable\GCC\ARM_CM0" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


