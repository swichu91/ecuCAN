################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/terminal/terminal.c 

OBJS += \
./modules/terminal/terminal.o 

C_DEPS += \
./modules/terminal/terminal.d 


# Each subdirectory must supply rules for building sources it contributes
modules/terminal/%.o: ../modules/terminal/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"D:/Moje/GIT/ecuCAN/Static_Code/System" -I"D:/Moje/GIT/ecuCAN/Static_Code/PDD" -I"D:/Moje/GIT/ecuCAN/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"D:/Moje/GIT/ecuCAN/Sources" -I"D:/Moje/GIT/ecuCAN/Generated_Code" -I"D:\Moje\GIT\ecuCAN\modules" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


