################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Events.c \
../Sources/main.c \
../Sources/vmain.c 

OBJS += \
./Sources/Events.o \
./Sources/main.o \
./Sources/vmain.o 

C_DEPS += \
./Sources/Events.d \
./Sources/main.d \
./Sources/vmain.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"E:/PROGRAMOWANIE/KDS_DEV/ecuCAN/Static_Code/System" -I"E:/PROGRAMOWANIE/KDS_DEV/ecuCAN/Static_Code/PDD" -I"E:/PROGRAMOWANIE/KDS_DEV/ecuCAN/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"E:/PROGRAMOWANIE/KDS_DEV/ecuCAN/Sources" -I"E:/PROGRAMOWANIE/KDS_DEV/ecuCAN/Generated_Code" -I"E:\PROGRAMOWANIE\KDS_DEV\ecuCAN\modules" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


