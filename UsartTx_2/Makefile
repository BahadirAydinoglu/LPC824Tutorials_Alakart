
TARGET = UsartTx2
HEX_FILE=$(TARGET).hex
ELF_FILE=$(TARGET).elf
BIN_FILE=$(TARGET).bin


# Build directory
BUILD_DIR = build

USER_SOURCE = src
USER_INCLUDE = inc

LIBPATH=/home/bahadira/MCULIBS/LPC824_SDK_215
LPC824DIR=$(LIBPATH)/devices/LPC824
SRCDIR=$(LIBPATH)/devices/LPC824/gcc/

# C sources
C_SOURCES = main.c
C_SOURCES += pin_mux.c
C_SOURCES += board.c
C_SOURCES += clock_config.c
# /
C_SOURCES += system_LPC824.c
# drivers/
C_SOURCES += fsl_common.c
C_SOURCES += fsl_common_arm.c
C_SOURCES += fsl_gpio.c
C_SOURCES += fsl_power.c
C_SOURCES += fsl_clock.c
C_SOURCES += fsl_reset.c
C_SOURCES += fsl_swm.c
C_SOURCES += fsl_syscon.c
C_SOURCES += fsl_usart.c
# components/uart/fsl_adapter_miniusart.c
C_SOURCES += fsl_adapter_miniusart.c
# utilities/debug_console_lite/fsl_assert.c
C_SOURCES += fsl_assert.c
C_SOURCES += fsl_debug_console.c
# utilities/fsl_sbrk.c
C_SOURCES += fsl_sbrk.c
# utilities/str/fsl_str.c
C_SOURCES += fsl_str.c
#C_SOURCES +=

# ASM sources
# gcc/
ASM_SOURCES = startup_LPC824.S


#Tools:
CC = /home/bahadira/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gcc
AS = /home/bahadira/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gcc -x assembler-with-cpp
CP = /home/bahadira/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-objcopy
LD = /home/bahadira/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-ld
SZ = /home/bahadira/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S


ASM_DEFINES = -DNDEBUG -D__STARTUP_CLEAR_BSS 

ASM_FLAGS  = $(ASM_DEFINES)
ASM_FLAGS += -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft   
ASM_FLAGS += -Wall
# compile gcc flags
#ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ASM_INCLUDES  = -I.
ASM_INCLUDES += -I$(USER_SOURCE)/
ASM_INCLUDES += -I$(USER_INCLUDE)/
ASM_INCLUDES += -I$(SRCDIR)/
ASM_INCLUDES += -I$(LPC824DIR)/utilities/str
ASM_INCLUDES += -I$(LPC824DIR)/utilities/debug_console_lite
ASM_INCLUDES += -I$(LIBPATH)/components/uart/
ASM_INCLUDES += -I$(LPC824DIR)/drivers/
ASM_INCLUDES += -I$(LPC824DIR)/
ASM_INCLUDES += -I$(LIBPATH)/CMSIS/Core/Include/

# AS includes
# AS_INCLUDES = 


C_DEFINES  = -DNDEBUG
C_DEFINES += -DCPU_LPC824 -DCPU_LPC824M201JHI33
C_DEFINES += -DMCUXPRESSO_SDK
C_DEFINES += -DSDK_DEBUGCONSOLE=1

C_INCLUDES  = -I.
C_INCLUDES += -I$(USER_SOURCE)
C_INCLUDES += -I$(USER_INCLUDE)
C_INCLUDES += -I$(SRCDIR)/
C_INCLUDES += -I$(LPC824DIR)/
C_INCLUDES += -I$(LPC824DIR)/drivers/
C_INCLUDES += -I$(LPC824DIR)/utilities/str/
C_INCLUDES += -I$(LPC824DIR)/utilities/debug_console_lite/
C_INCLUDES += -I$(LIBPATH)/components/uart/
C_INCLUDES += -I$(LIBPATH)/CMSIS/Core/Include/



C_FLAGS  = -O3 -Os
C_FLAGS += -mcpu=cortex-m0plus
C_FLAGS += -Wall -mthumb -MMD -MP
C_FLAGS += -fno-common -ffunction-sections -fdata-sections
C_FLAGS += -ffreestanding
C_FLAGS += -fno-builtin
C_FLAGS += -mapcs
C_FLAGS += -std=gnu99
C_FLAGS += -mfloat-abi=soft
C_FLAGS += -Wall
C_FLAGS += $(C_DEFINES)
C_FLAGS += $(C_INCLUDES) 
CFLAGS += -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst))
## Dependency info:
#CFLAGS += -MMD -MP  -MF"$(@:%.o=%.d)" 

# Add assembly listing of each compiled file to the build dir:
##CFLAGS += -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst))
# -Wa: pass options to assembler.
# -alms specifies:
# -a: turn on listings
# -d: omit debugging directives; n: omit forms processing
# -h: include high-level source
# -l: include assembly


# LD flags, linker script:
LDSCRIPT = $(SRCDIR)/LPC824_flash.ld

LIBSPEC=-L /home/onat/elektronik/ARM/Compiler/gcc-arm-none-eabi-4_9-2015q2//lib/gcc/arm-none-eabi/4.9.3/

LDFLAGS  = $(C_FLAGS)
LDFLAGS += --specs=nano.specs --specs=nosys.specs
LDFLAGS += -T$(LDSCRIPT)
LDFLAGS += -static
LDFLAGS += -Wl,--start-group -lm -lc -lgcc -lnosys -Wl,--end-group 


# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
#LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections
# AO!: LDFLAGS += -u _printf_float  # sprintf did not print floats without this.

#LDFLAGS  = -g -mcpu=cortex-m0plus  -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding -fno-builtin
#LDFLAGS += -mthumb -mapcs -Xlinker --gc-sections -Xlinker -static -Xlinker -z -Xlinker muldefs -Xlinker -Map=output.map
#LDFLAGS += -mfloat-abi=soft ${SPECS} -T$(LDSCRIPT) -static
##LDFLAGS += -Wl
#LDFLAGS = $(LIBSPEC) -lgcc -T$(LDSCRIPT) --cref -Map output.map -nostartfiles

# default action: build all
all: $(BUILD_DIR)/$(ELF_FILE) $(BUILD_DIR)/$(HEX_FILE) $(BUILD_DIR)/$(BIN_FILE)

# LPC *requires* a checksum inserted into the binary. This does it:
CHECKSUM=/home/onat/elektronik/ARM/LPC/lpcpatchelf/lpcpatchelf
CHECKSUM_FLAG=-f

#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(USER_SOURCE)
vpath %.c $(USER_INCLUDE)
vpath %.c $(LPC824DIR)
vpath %.c $(LPC824DIR)/drivers/
vpath %.c $(LIBPATH)/components/uart/
vpath %.c $(LPC824DIR)/utilities/
vpath %.c $(LPC824DIR)/utilities/str/
vpath %.c $(LPC824DIR)/utilities/debug_console_lite/


# list of ASM program objects
# CAUTION: Take care with 'S' and 's' extension.
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
#vpath %.s $(sort $(dir $(ASM_SOURCES)))

# Objects from c sources:
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(C_FLAGS) $< -o $@
#$(CC) -c $(C_FLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

# Objects from assembly sources: CAUTION: Make sure 'S' and 's' extension.
$(BUILD_DIR)/%.o: %.S Makefile #| $(BUILD_DIR)
	$(AS) -c $(C_FLAGS) $< -o $@

$(BUILD_DIR)/$(ELF_FILE): $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS)-o $@
#$(LD) $(OBJECTS) $(LDFLAGS) -o $@
#$(CHECKSUM) $(CHECKSUM_FLAG)  $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	

$(BUILD_DIR):
	mkdir $@

sflash: $(BUILD_DIR)/$(ELF_FILE)
	@echo Make sure the device is in Boot 0 mode \(Press SW2/ISP switch while coming out of reset.\)
	lpcprog -d /dev/ttyUSB0 -c flash $(BUILD_DIR)/$(BIN_FILE)

install: $(BUILD_DIR)/$(ELF_FILE)
	lpc21isp -control $(BUILD_DIR)/$(HEX_FILE) /dev/ttyUSB0 115200 12000

clean:
	@rm -f $(BUILD_DIR)/$(OBJECTS) $(BUILD_DIR)/$(OBJECTS:.o=.d) $(OBJECTS:.o=.lst) $(BUILD_DIR)/$(ELF_FILE) $(BUILD_DIR)/$(HEX_FILE) $(BUILD_DIR)/$(BIN_FILE)  $(BUILD_DIR)/$(TARGET).map

# Dependencies
-include $(wildcard $(BUILD_DIR)/*.d)




