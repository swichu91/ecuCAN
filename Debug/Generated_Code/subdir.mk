################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/BitIoLdd2.c \
../Generated_Code/BlueLED.c \
../Generated_Code/CAN1.c \
../Generated_Code/Cpu.c \
../Generated_Code/GreenLED.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/Pins1.c \
../Generated_Code/TU1.c 

OBJS += \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/BitIoLdd2.o \
./Generated_Code/BlueLED.o \
./Generated_Code/CAN1.o \
./Generated_Code/Cpu.o \
./Generated_Code/GreenLED.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Pins1.o \
./Generated_Code/TU1.o 

C_DEPS += \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/BitIoLdd2.d \
./Generated_Code/BlueLED.d \
./Generated_Code/CAN1.d \
./Generated_Code/Cpu.d \
./Generated_Code/GreenLED.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/Pins1.d \
./Generated_Code/TU1.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"E:/PROGRAMOWANIE/KDS_DEV/CAN_FreeRTOS/Static_Code/System" -I"E:/PROGRAMOWANIE/KDS_DEV/CAN_FreeRTOS/Static_Code/PDD" -I"E:/PROGRAMOWANIE/KDS_DEV/CAN_FreeRTOS/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"E:/PROGRAMOWANIE/KDS_DEV/CAN_FreeRTOS/Sources" -I"E:/PROGRAMOWANIE/KDS_DEV/CAN_FreeRTOS/Generated_Code" -I"E:\PROGRAMOWANIE\KDS_DEV\CAN_FreeRTOS\modules" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


