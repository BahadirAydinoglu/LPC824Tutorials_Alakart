

// This a very simple 'C' language program.
// It blinks a LED in an infinite loop.
// Delay timing is provided by a busy wait.

// (C) Ahmet Onat 2023

#include <stdint.h> // Declarations of uint32_t etc.
#include "lpc824.h" // Declarations of LPC824 register names.


void delay(uint32_t counts); // The busy delay routine.



int main(void) {
  
  SYSCON_SYSAHBCLKCTRL |= 0x400C0; // Enable IOCON, SWM & GPIO clocks.
 
  SYSCON_PRESETCTRL &= ~(0x400);  // Peripheral reset control to gpio/gpio int
  SYSCON_PRESETCTRL |=   0x400;   // AO: Check.
  
  
  //Make Pin 16 an output. On Alakart, Pin #16 is the blue LED:
  GPIO_DIR0 |= (1<<16);

  while (1) { // Blink the LED in an infinite loop:

    GPIO_B16 = 0;    // Set pin low. (LED is ON)
    delay(5000000);  // The dela
    
    GPIO_B16 = 1;    //Set pin high (LED is OFF)
    delay(1000000);
  }

}

// Delay timing is provided by a busy wait:
void delay(uint32_t counts) {

  uint32_t wait;
  for (wait=counts; wait>0; --wait){
  }

}
 

