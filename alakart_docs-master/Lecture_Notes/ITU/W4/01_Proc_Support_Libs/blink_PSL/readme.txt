

This example shows how the processor support libraries (PSL, or SDK) can be used to start a LED blinking. 

Using the PSL gives a less tedious alternative to programming the processor by manipulating the register bits (as we have been doing until now).

The disadvantages are:

* The libraries contain a lot of extra functions. They also get compiled and therefore the code size is much larger.

* The library may contain errors or ambiguities.

Therefore, it is better to use the libraries when using complex peripheral devices such as communication interfaces, and to use direct register bit manipulation when using simple peripheral devices such as GPIO.


///////////////////////////////////////////////////////////////////////////////
///////////////////////////// IMPORTANT! //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

This project is built using the Makefile, and it requires source files from the libraries directory. You must edit the Makefile and change the part that sets the processor support library:

# Main source directories (Insert your own installation directory):
LIBPATH=/home/onat/work/Ders/KON309E_Microcontroller/NXP284/Xpresso_SDK/

Set it to the path of the processor support library folder in your computer (whereever you have extracted it).
