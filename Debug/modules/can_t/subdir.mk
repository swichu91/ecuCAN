################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/can_t/can_t.c 

OBJS += \
./modules/can_t/can_t.o 

C_DEPS += \
./modules/can_t/can_t.d 


# Each subdirectory must supply rules for building sources it contributes
modules/can_t/%.o: ../modules/can_t/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"D:/Moje/GIT/ecuCAN/Static_Code/System" -I"D:/Moje/GIT/ecuCAN/Static_Code/PDD" -I"D:/Moje/GIT/ecuCAN/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"D:/Moje/GIT/ecuCAN/Sources" -I"D:/Moje/GIT/ecuCAN/Generated_Code" -I"D:\Moje\GIT\ecuCAN\modules" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


