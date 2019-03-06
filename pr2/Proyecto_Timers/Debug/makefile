################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include commonEclipse/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Proyecto_Timers.hex \

SECONDARY_LIST += \
Proyecto_Timers.lst \

SECONDARY_SIZE += \
Proyecto_Timers.siz \


# All Target
all: Proyecto_Timers.elf secondary-outputs

# Tool invocations
Proyecto_Timers.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"C:\Users\Campos\Desktop\SED\SED\pr2\Proyecto_Timers\commonEclipse\ram_ice.ld" -nostartfiles -Wl,-Map,Proyecto_Timers.map -mcpu=arm7tdmi -g3 -gdwarf-2 -o "Proyecto_Timers.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Proyecto_Timers.hex: Proyecto_Timers.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary Proyecto_Timers.elf  "Proyecto_Timers.hex"
	@echo 'Finished building: $@'
	@echo ' '

Proyecto_Timers.lst: Proyecto_Timers.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S Proyecto_Timers.elf > "Proyecto_Timers.lst"
	@echo 'Finished building: $@'
	@echo ' '

Proyecto_Timers.siz: Proyecto_Timers.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley Proyecto_Timers.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) Proyecto_Timers.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
