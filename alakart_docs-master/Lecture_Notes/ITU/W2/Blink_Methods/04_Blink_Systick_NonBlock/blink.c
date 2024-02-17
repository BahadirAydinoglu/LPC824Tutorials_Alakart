

// This program demonstrates the use of the "System Tick" simple timer
//  peripheral of the ARM M series processors.
// It provides a simple time base timer which causes an interrupt at
//  fixed intervals.
// The interrupt is used as a precise time base with a resolution of 1ms.

// Lhe LED blinks by a background task. the Main function is free to do other things. 

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


// Define how long the LED should flash:
#define LED_ON_TIME 100        //LED on for this many ms.
#define LED_PERIOD 1000     //LED blink rate this many ms.

volatile uint16_t MS_count;

int main(void) {

  //SYSCON_SYSAHBCLKCTRL |= 0x40080; // Enable IOCON & SWM clock signal.
  //SYSCON_SYSAHBCLKCTRL |= 0x40;   // Enable AHB clock to the GPIO peripheral
  SYSCON_SYSAHBCLKCTRL |= 0x400C0; // Enable IOCON, SWM & GPIO clocks.
  
  SYSCON_PRESETCTRL &= ~(0x400);  // Peripheral reset control to gpio/gpio int
  SYSCON_PRESETCTRL |=   0x400;   // AO: Check.
  
  //Make Pin 16 an output. On Alakart, Pin #16 is the blue LED:
  GPIO_DIR0 |= (1<<16);

  SysTickConfig(SYSTEM_CORE_CLOCK/1000);  //setup systick clock interrupt @1ms
  
  
  while (1) { // Do nothing in the main loop.
    // LED is flashed in a backgroud process in SysTick_Handler.
  }

}


 //The interrupt handler for SysTick system time-base timer.
void SysTick_Handler(void) { 

  ++MS_count;

  if (MS_count<LED_ON_TIME){
    GPIO_B16 = 0;    //set pin low (LED is ON)
  }else if (MS_count<LED_PERIOD){
    GPIO_B16 = 1;    //set pin high (LED is OFF)
  } else {
    MS_count=0;
  }
  
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


