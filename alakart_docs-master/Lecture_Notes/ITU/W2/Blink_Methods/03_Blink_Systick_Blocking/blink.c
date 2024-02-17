

// This program demonstrates the use of the "System Tick" simple timer
//  peripheral of the ARM M series processors.
// It provides a simple time base timer which causes an interrupt at
//  fixed intervals.
// The interrupt is used as a precise busy wait time delay function
//  with a resolution of 1ms.

// SysTick_Handler function is the ISR.
// Its is declared as part of the vector table in the file "init.c".


// Ahmet Onat (C) 2023

#include <stdint.h>
#include "lpc824.h"

#define TRUE 1
#define FALSE 0

#define SYSTEM_CORE_CLOCK 30000000UL   //Declare system clock as 30MHz
// (The clock speed has been set in "init.c" file to 30MHz.)

static inline uint32_t SysTickConfig(uint32_t ticks);
void SysTick_Handler(void);  //our systick interrupt handler
void delay_ms(uint32_t ms);//delay (ms)

volatile uint32_t delaytime; // This is decremented by SysTick_Handler.


int main(void) {

  delaytime=0;
  
  //SYSCON_SYSAHBCLKCTRL |= 0x40080; // Enable IOCON & SWM clock signal.
  //SYSCON_SYSAHBCLKCTRL |= 0x40;   // Enable AHB clock to the GPIO peripheral
  SYSCON_SYSAHBCLKCTRL |= 0x400C0; // Enable IOCON, SWM & GPIO clocks.
  
  SYSCON_PRESETCTRL &= ~(0x400);  // Peripheral reset control to gpio/gpio int
  SYSCON_PRESETCTRL |=   0x400;   // AO: Check.
  
  //Make Pin 16 an output. On Alakart, Pin #16 is the blue LED:
  GPIO_DIR0 |= (1<<16);

  SysTickConfig(SYSTEM_CORE_CLOCK/1000);  //setup systick clock interrupt @1ms
  
  
  while (1) { // Blink the LED in an infinite loop:

    GPIO_B16 = 0;    //set pin low. (LED is ON)
    delay_ms(100);
    
    GPIO_B16 = 1;    //set pin high (LED is OFF)
    delay_ms(100);

    GPIO_B16 = 0;    //set pin low (LED is ON)
    delay_ms(100);
    
    GPIO_B16 = 1;    //set pin high (LED is OFF)
    delay_ms(900);

  }

}


 //The interrupt handler for SysTick system time-base timer.
void SysTick_Handler(void) { 
  if (delaytime!=0){ // If delaytime has been set somewhere in the program,
    --delaytime;     //  decrement it every time SysTick event occurs (1ms).
  }
}


void delay_ms(uint32_t ms) {//delay (ms)

  delaytime=ms;        // Set the delay time to the number of millisecs of wait
  while(delaytime!=0){}// Wait here until the delay time expires.

}
 
// System Tick Configuration:
// Initializes the System Timer and its interrupt, and
// Starts the System Tick Timer.
// ticks = Number of ticks between two interrupts.

static inline uint32_t SysTickConfig(uint32_t ticks) {
  if (ticks > 0xFFFFFFUL) // Timer is only 24 bits wide.
    return (1); //Reload value impossible
  
  SYST_RVR = (ticks & 0xFFFFFFUL) - 1;  //Set reload register

  SYST_CVR = 0;   //Load the initial count value.

  SYST_CSR = 0x07;  // Counter ENABLE, INT ENABLE, CLK source=system clock.

  return (0);
}         // AO!: Check OK.


