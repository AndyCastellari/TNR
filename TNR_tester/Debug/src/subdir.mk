################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/JSONTester.cpp \
../src/PODTester.cpp \
../src/TNR_tester.cpp 

OBJS += \
./src/JSONTester.o \
./src/PODTester.o \
./src/TNR_tester.o 

CPP_DEPS += \
./src/JSONTester.d \
./src/PODTester.d \
./src/TNR_tester.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/andy/development/boost_1_55_0 -I/home/andy/development/rapidjson/include -I/home/andy/development/TNR/libTNR -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


