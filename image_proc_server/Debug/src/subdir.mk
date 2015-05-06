################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/raminta/workspace/Digital-broadcasting/pbm_rw/pbm_rw/main.c \
/home/raminta/workspace/Digital-broadcasting/pbm_rw/pbm_rw/pbm.c 

OBJS += \
./src/main.o \
./src/pbm.o 

C_DEPS += \
./src/main.d \
./src/pbm.d 


# Each subdirectory must supply rules for building sources it contributes
src/main.o: /home/raminta/workspace/Digital-broadcasting/pbm_rw/pbm_rw/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/pbm.o: /home/raminta/workspace/Digital-broadcasting/pbm_rw/pbm_rw/pbm.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


