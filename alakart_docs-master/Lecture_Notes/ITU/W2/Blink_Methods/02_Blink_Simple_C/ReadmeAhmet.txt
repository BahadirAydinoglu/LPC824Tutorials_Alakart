

Compile blink.c to blink.o:
arm-none-eabi-gcc -c -mcpu=cortex-m0 -mthumb -g  blink.c -o blink.o

arm-none-eabi-gcc -c -mcpu=cortex-m0 -mthumb -g  init.c -o init.o

arm-none-eabi-ld blink.o init.o -T lpc824_linker_script.ld --cref -Map blink.map -o blink.elf


~/elektronik/ARM/LPC/lpcpatchelf/lpcpatchelf -f blink.elf

arm-none-eabi-objcopy -O ihex  blink.elf blink.hex

lpc21isp -control -controlswap blink.hex /dev/ttyUSB0 115200 12000



Red LED is on Pin 12
Blue LED is on Pin 16
Green LED is on Pin 27

Open drain MOSFET gate is on Pin 21.


Note that in init.c, for SysTick INT, Default_Handler must be replaced by SysTick_Handler.


The blink was running faster than anticipated. The
//#define SYSTEM_CORE_CLOCK 12000000UL   //12MHz
#define SYSTEM_CORE_CLOCK 60000000UL   //30MHz

was set to 12MHz in error. It was corrected to 30MHz (as the default RC clock.)
However, it still ran 2x too fast.
When SYSTEM_CORE_CLOCK 60000000UL was set, blink speed was as expected.
TODO: Investigate. Why should it be so high?

