################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BaseBinaryArchiveReadWrite.cpp \
../BasicJSONParser.cpp \
../FormattedTextReadWriteIf.cpp \
../ObjectMap.cpp \
../SimpleTextReadWriteIf.cpp \
../StreamReadWriteIf.cpp \
../TextLogWriteIf.cpp \
../tnr.cpp 

OBJS += \
./BaseBinaryArchiveReadWrite.o \
./BasicJSONParser.o \
./FormattedTextReadWriteIf.o \
./ObjectMap.o \
./SimpleTextReadWriteIf.o \
./StreamReadWriteIf.o \
./TextLogWriteIf.o \
./tnr.o 

CPP_DEPS += \
./BaseBinaryArchiveReadWrite.d \
./BasicJSONParser.d \
./FormattedTextReadWriteIf.d \
./ObjectMap.d \
./SimpleTextReadWriteIf.d \
./StreamReadWriteIf.d \
./TextLogWriteIf.d \
./tnr.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/andy/development/boost_1_55_0/boost -I/home/andy/development/rapidjson/include -I/home/andy/development/boost_1_55_0 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


