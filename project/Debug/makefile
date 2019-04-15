################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include commonUart/subdir.mk
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
proyect.hex \

SECONDARY_LIST += \
proyect.lst \

SECONDARY_SIZE += \
proyect.siz \


# All Target
all: proyect.elf secondary-outputs

# Tool invocations
proyect.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"C:\hlocal\EclipseARMwspace\proyect\commonUart\ram_ice.ld" -nostartfiles -L"C:\software\electronica\ARM\EclipseARM\sourcery-g++-lite-arm-2011.03\arm-none-eabi\lib" -L"C:\software\electronica\ARM\EclipseARM\sourcery-g++-lite-arm-2011.03\lib\gcc\arm-none-eabi\4.5.2" -Wl,-Map,proyect.map -mcpu=arm7tdmi -g3 -gdwarf-2 -o "proyect.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

proyect.hex: proyect.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary proyect.elf  "proyect.hex"
	@echo 'Finished building: $@'
	@echo ' '

proyect.lst: proyect.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S proyect.elf > "proyect.lst"
	@echo 'Finished building: $@'
	@echo ' '

proyect.siz: proyect.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley proyect.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) proyect.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
