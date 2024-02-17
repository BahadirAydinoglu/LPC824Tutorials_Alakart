



The blink_systick project demonstrates the Systick timer peripheral that is common to all ARM processors.
Systick produces a periodic interrupt at a desired time interval.
The ISR for Systick is on system INT (-1), actually the 16th vector, counting from the begining. ARM gives a negative number to the first 16 INT vectors.

The handler for the Systick INT is defined in the
vector table in the file startup_LPC824.S around line 41 and looks like this:
 .long   SysTick_Handler             /* SysTick Handler    */
This is an assembly file.


In this project, Systick is programmed to create a periodic interrupt at an interval of 1ms. We use the processor support library for configuring the Systick, in the file:
"blink.c"
In line:
 SysTick_Config(SystemCoreClock / 1000U);

See the comments in the file "blink.c" to understand how the program works.


