


This is a very simple assembly language program.
Assembly programs traditionally have the extension '.s' or '.S'


It does the following things:

* To the minium amount of initialization
  (It Preares the RESET vector)

* Initialize the GPIO port
  - Set PIN12 as an output.
  - RED LED is connected to PIN12.

* It then repeats the following indefinitely:

  1. Write '0' to GPIO port PIN12.
  2. Delay
  3. Write '1' to GPIO port PIN12.
  4. Delay
  5. Repeat

The part which causes the delay is implemented as a "subroutine", a primitive function.

To run the program on your Alakart, do the following (ou must have installed and tested Gnu Compiler Collection GCC beforehand):

1. Open a terminal

2. In the terminal type the following command. This creates the object file from the assembly source:
arm-none-eabi-as -mcpu=cortex-m0 -mthumb -g   main.s -o main.obj

3. Link the object file with the linker so that an executable (.elf) is prepared. Type:
arm-none-eabi-ld -T lpc824_linker_script.ld -o main.elf main.obj

4. Convert the executable (.elf) to a format (.hex) that the programming software requires:
arm-none-eabi-objcopy -O ihex main.elf main.hex

5. Program the .hex file on the processor. Connect the processor board to your PC and if on Linux, type:
lpc21isp -control main.hex /dev/ttyUSB0 115200 12000

If on Microsoft Windows or Apple MacOS computer, you should use Flash Magic program.


The LED on the board should start to blink.
