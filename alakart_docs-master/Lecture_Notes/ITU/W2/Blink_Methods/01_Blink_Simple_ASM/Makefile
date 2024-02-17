PROJECT=main

SRC_FILE=main.s

OBJ_FILE=$(PROJECT).obj
HEX_FILE=$(PROJECT).hex
ELF_FILE=$(PROJECT).elf
DISAS_FILE=$(PROJECT).list

# Change the following to your compiler directory:
COMPILER_DIR=/opt/st/stm32cubeide_1.10.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.10.3-2021.10.linux64_1.0.0.202111181127/tools/bin/

CC=$(COMPILER_DIR)arm-none-eabi-gcc
AS=$(COMPILER_DIR)arm-none-eabi-as
LD=$(COMPILER_DIR)arm-none-eabi-ld
OC=$(COMPILER_DIR)arm-none-eabi-objcopy
OD=$(COMPILER_DIR)arm-none-eabi-objdump

ASFLAGS=-mcpu=cortex-m0 -mthumb -g  

LDFLAGS=  -T lpc824_linker_script.ld

OBJCOPYFLAGS= -O ihex

OBJDUMPFLAGS= -D -marmv6t2  -M force-thumb 

all:$(DISAS_FILE)

$(DISAS_FILE):$(HEX_FILE)
	$(OD) $(OBJDUMPFLAGS) $(HEX_FILE) > $(DISAS_FILE)

$(HEX_FILE): $(ELF_FILE)
	$(OC) $(OBJCOPYFLAGS) $(ELF_FILE) $(HEX_FILE)

$(ELF_FILE) : $(OBJ_FILE)
	$(LD) $(LDFLAGS) -o $(ELF_FILE) $(OBJ_FILE)

$(OBJ_FILE): $(SRC_FILE)
	$(AS) $(ASFLAGS) $(SRC_FILE) -o $(OBJ_FILE)

21flash:$(HEX_FILE)
	lpc21isp -control $(HEX_FILE) /dev/ttyUSB0 115200 12000
#	lpc21isp -control -controlswap $(HEX_FILE) /dev/ttyUSB0 115200 12000

clean: 
	rm -f $(OBJ_FILE)  $(ELF_FILE) $(HEX_FILE)  $(DISAS_FILE) 
