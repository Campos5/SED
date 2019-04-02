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
Pr4.hex \

SECONDARY_LIST += \
Pr4.lst \

SECONDARY_SIZE += \
Pr4.siz \


# All Target
all: Pr4.elf secondary-outputs

# Tool invocations
Pr4.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"C:\hlocal\p4Skeleton_int\commonUart\ram_ice.ld" -nostartfiles -L"C:\software\electronica\ARM\EclipseARM\sourcery-g++-lite-arm-2011.03\lib\gcc\arm-none-eabi\4.5.2" -L"C:\software\electronica\ARM\EclipseARM\sourcery-g++-lite-arm-2011.03\arm-none-eabi\lib" -L"C:\hlocal\EclipseARMwspace\Pr4\commonUart" -Wl,-Map,Pr4.map -mcpu=arm7tdmi -g3 -gdwarf-2 -o "Pr4.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Pr4.hex: Pr4.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary Pr4.elf  "Pr4.hex"
	@echo 'Finished building: $@'
	@echo ' '

Pr4.lst: Pr4.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S Pr4.elf > "Pr4.lst"
	@echo 'Finished building: $@'
	@echo ' '

Pr4.siz: Pr4.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley Pr4.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) Pr4.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
