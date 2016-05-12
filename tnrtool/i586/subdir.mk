################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tnrtool.cpp 

OBJS += \
./tnrtool.o 

CPP_DEPS += \
./tnrtool.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	i686-w64-mingw32-g++ -I/home/andy/development/boost_1_55_0 -I"/home/andy/development/TNR/libTNR" -I/home/andy/development/rapidjson/include -I/home/andy/development/tclap-1.2.1/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


