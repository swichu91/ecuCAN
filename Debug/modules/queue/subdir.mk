################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/queue/fifo.c \
../modules/queue/queue.c 

OBJS += \
./modules/queue/fifo.o \
./modules/queue/queue.o 

C_DEPS += \
./modules/queue/fifo.d \
./modules/queue/queue.d 


# Each subdirectory must supply rules for building sources it contributes
modules/queue/%.o: ../modules/queue/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"E:/PROGRAMOWANIE/KDS_DEV/CAN_FreeRTOS/Static_Code/System" -I"E:/PROGRAMOWANIE/KDS_DEV/CAN_FreeRTOS/Static_Code/PDD" -I"E:/PROGRAMOWANIE/KDS_DEV/CAN_FreeRTOS/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"E:/PROGRAMOWANIE/KDS_DEV/CAN_FreeRTOS/Sources" -I"E:/PROGRAMOWANIE/KDS_DEV/CAN_FreeRTOS/Generated_Code" -I"E:\PROGRAMOWANIE\KDS_DEV\CAN_FreeRTOS\modules" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


