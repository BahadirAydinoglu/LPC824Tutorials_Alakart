
TARGET = blink_systick
HEX_FILE=$(TARGET).hex
ELF_FILE=$(TARGET).elf
BIN_FILE=$(TARGET).bin


# Build directory
BUILD_DIR = build

#Modify this path to fit your own directory structure:
LIBPATH=/home/onat/work/Ders/KON309E_Microcontroller/NXP284/Xpresso_SDK
LPC824DIR=$(LIBPATH)/devices/LPC824


# C sources
C_SOURCES = blink.c
C_SOURCES += system_LPC824.c
# drivers/
C_SOURCES += fsl_common.c
C_SOURCES += fsl_common_arm.c
C_SOURCES += fsl_gpio.c
C_SOURCES += fsl_power.c
C_SOURCES += fsl_clock.c
C_SOURCES += fsl_reset.c
C_SOURCES += fsl_swm.c

# ASM sources
# gcc/
ASM_SOURCES = startup_LPC824.S


#Tools:
CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc -x assembler-with-cpp
CP = arm-none-eabi-objcopy
LD = arm-none-eabi-ld
SZ = arm-none-eabi-size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S


ASM_DEFINES = -DNDEBUG -D__STARTUP_CLEAR_BSS 

ASM_FLAGS  = $(ASM_DEFINES)
ASM_FLAGS += -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft   
ASM_FLAGS += -Wall
# compile gcc flags


ASM_INCLUDES += -I$(LPC824DIR)/utilities/str
ASM_INCLUDES += -I$(LPC824DIR)/utilities/debug_console_lite
ASM_INCLUDES += -I$(LIBPATH)/components/uart
ASM_INCLUDES += -I$(LPC824DIR)/drivers
ASM_INCLUDES += -I$(LPC824DIR)
ASM_INCLUDES += -I$(LIBPATH)/CMSIS/Core/Include


C_DEFINES  = -DNDEBUG
C_DEFINES += -DCPU_LPC824 -DCPU_LPC824M201JHI33
C_DEFINES += -DMCUXPRESSO_SDK
C_DEFINES += -DSDK_DEBUGCONSOLE=1

C_INCLUDES  = -I.
C_INCLUDES += -I$(LPC824DIR)
C_INCLUDES += -I$(LPC824DIR)/drivers
C_INCLUDES += -I$(LPC824DIR)/utilities/str
C_INCLUDES += -I$(LPC824DIR)/utilities/debug_console_lite
C_INCLUDES += -I$(LIBPATH)/components/uart
C_INCLUDES += -I$(LIBPATH)/CMSIS/Core/Include


C_FLAGS  = -O3 -Os
C_FLAGS += -mcpu=cortex-m0plus
C_FLAGS += -Wall -mthumb -MMD -MP
C_FLAGS += -mapcs
C_FLAGS += -std=gnu99
C_FLAGS += $(C_DEFINES)
C_FLAGS += $(C_INCLUDES) 
CFLAGS += -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst))

# Add assembly listing of each compiled file to the build dir:
##CFLAGS += -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst))
# -Wa: pass options to assembler.
# -alms specifies:
# -a: turn on listings
# -d: omit debugging directives; n: omit forms processing
# -h: include high-level source
# -l: include assembly


# Linker script and linker flags:
LDSCRIPT = LPC824_flash.ld

LDFLAGS  = $(C_FLAGS)
LDFLAGS += --specs=nano.specs --specs=nosys.specs
LDFLAGS += -T$(LDSCRIPT)
LDFLAGS += -static
LDFLAGS += -Wl,--start-group -lm -lc -lgcc -lnosys -Wl,--end-group 


# default action: build all
all: $(BUILD_DIR)/$(ELF_FILE) $(BUILD_DIR)/$(HEX_FILE) $(BUILD_DIR)/$(BIN_FILE)


#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(LPC824DIR)
vpath %.c $(LPC824DIR)/drivers/

# list of ASM program objects
# CAUTION: Take care with 'S' and 's' extension.
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))


# Objects from c sources:
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(C_FLAGS) $< -o $@

# Objects from assembly sources: CAUTION: Check 'S' or 's' extension.
$(BUILD_DIR)/%.o: %.S Makefile #| $(BUILD_DIR)
	$(AS) -c $(C_FLAGS) $< -o $@

$(BUILD_DIR)/$(ELF_FILE): $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS)-o $@
#$(LD) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	

$(BUILD_DIR):
	mkdir $@


21flash: $(BUILD_DIR)/$(HEX_FILE)
	lpc21isp -control $(BUILD_DIR)/$(HEX_FILE) /dev/ttyUSB0 115200 12000

clean:
	rm -f $(OBJECTS) $(OBJECTS:.o=.d) $(OBJECTS:.o=.lst) $(BUILD_DIR)/$(ELF_FILE) $(BUILD_DIR)/$(BIN_FILE) $(BUILD_DIR)/$(TARGET).map

# Dependencies
-include $(wildcard $(BUILD_DIR)/*.d)



