################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Position/Src/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include MEMS/App/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/STM32F4xx_Nucleo/subdir.mk
-include Drivers/BSP/IKS01A3/subdir.mk
-include Drivers/BSP/Components/stts751/subdir.mk
-include Drivers/BSP/Components/lsm6dso/subdir.mk
-include Drivers/BSP/Components/lps22hh/subdir.mk
-include Drivers/BSP/Components/lis2mdl/subdir.mk
-include Drivers/BSP/Components/lis2dw12/subdir.mk
-include Drivers/BSP/Components/hts221/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/dbg/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
APH.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
APH.list \

OBJCOPY_BIN += \
APH.bin \


# All Target
all: APH.elf secondary-outputs

# Tool invocations
APH.elf: $(OBJS) $(USER_OBJS) C:\Users\Hans\Documents\GitHub\APH01\APH\STM32F401RETX_FLASH.ld
	arm-none-eabi-gcc -o "APH.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Hans\Documents\GitHub\APH01\APH\STM32F401RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="APH.map" -Wl,--gc-sections -static -L../Middlewares/ST/STM32_MotionEC_Library/Lib -L../Middlewares/ST/STM32_MotionAC_Library/Lib -L../Middlewares/ST/STM32_MotionGC_Library/Lib -L../Middlewares/ST/STM32_MotionMC_Library/Lib -L../Middlewares/ST/STM32_MotionFX_Library/Lib --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

APH.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "APH.list"
	@echo 'Finished building: $@'
	@echo ' '

APH.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "APH.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
