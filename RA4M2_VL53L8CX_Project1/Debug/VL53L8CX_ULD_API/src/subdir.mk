################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../VL53L8CX_ULD_API/src/vl53l8cx_api.c \
../VL53L8CX_ULD_API/src/vl53l8cx_plugin_detection_thresholds.c \
../VL53L8CX_ULD_API/src/vl53l8cx_plugin_motion_indicator.c \
../VL53L8CX_ULD_API/src/vl53l8cx_plugin_xtalk.c 

C_DEPS += \
./VL53L8CX_ULD_API/src/vl53l8cx_api.d \
./VL53L8CX_ULD_API/src/vl53l8cx_plugin_detection_thresholds.d \
./VL53L8CX_ULD_API/src/vl53l8cx_plugin_motion_indicator.d \
./VL53L8CX_ULD_API/src/vl53l8cx_plugin_xtalk.d 

OBJS += \
./VL53L8CX_ULD_API/src/vl53l8cx_api.o \
./VL53L8CX_ULD_API/src/vl53l8cx_plugin_detection_thresholds.o \
./VL53L8CX_ULD_API/src/vl53l8cx_plugin_motion_indicator.o \
./VL53L8CX_ULD_API/src/vl53l8cx_plugin_xtalk.o 

SREC += \
RA4M2_VL53L8CX_Project1.srec 

MAP += \
RA4M2_VL53L8CX_Project1.map 


# Each subdirectory must supply rules for building sources it contributes
VL53L8CX_ULD_API/src/%.o: ../VL53L8CX_ULD_API/src/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM33 -D_RA_ORDINAL=1 -I"C:/Users/a8456/e2_studio/workspace_5.8/RA4M2_VL53L8CX_Project1/src" -I"." -I"C:/Users/a8456/e2_studio/workspace_5.8/RA4M2_VL53L8CX_Project1/ra/fsp/inc" -I"C:/Users/a8456/e2_studio/workspace_5.8/RA4M2_VL53L8CX_Project1/ra/fsp/inc/api" -I"C:/Users/a8456/e2_studio/workspace_5.8/RA4M2_VL53L8CX_Project1/ra/fsp/inc/instances" -I"C:/Users/a8456/e2_studio/workspace_5.8/RA4M2_VL53L8CX_Project1/ra/arm/CMSIS_6/CMSIS/Core/Include" -I"C:/Users/a8456/e2_studio/workspace_5.8/RA4M2_VL53L8CX_Project1/ra_gen" -I"C:/Users/a8456/e2_studio/workspace_5.8/RA4M2_VL53L8CX_Project1/ra_cfg/fsp_cfg/bsp" -I"C:/Users/a8456/e2_studio/workspace_5.8/RA4M2_VL53L8CX_Project1/ra_cfg/fsp_cfg" -I"C:/Users/a8456/e2_studio/workspace_5.8/RA4M2_VL53L8CX_Project1/Platform" -I"C:/Users/a8456/e2_studio/workspace_5.8/RA4M2_VL53L8CX_Project1/VL53L8CX_ULD_API/inc" -std=c99 -Wno-stringop-overflow -Wno-format-truncation --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

