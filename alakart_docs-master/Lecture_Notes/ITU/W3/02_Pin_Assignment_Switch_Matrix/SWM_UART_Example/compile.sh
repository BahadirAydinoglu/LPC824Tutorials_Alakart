#!/bin/bash
arm-none-eabi-as -mcpu=cortex-m0 -mthumb -g   main.s -o main.obj
arm-none-eabi-ld -T lpc824_linker_script.ld -o main.elf main.obj
arm-none-eabi-objcopy -O ihex main.elf main.hex
lpc21isp -control main.hex /dev/ttyUSB0 115200 12000
