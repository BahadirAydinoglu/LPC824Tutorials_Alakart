// Copyright 2019 NXP
// All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause


#include "fsl_clock.h"
#include "fsl_power.h"
#include "fsl_gpio.h"
#include "fsl_swm.h"



#define BOARD_LED_PORT 0U
#define BOARD_LED_PIN  16U

#define LED_ON 0U // LED will be ON when GPIO output is '0' (LED anode is connected to supply)
#define LED_OFF 1U


#define CORE_CLOCK   30000000U  // Set CPU Core clock frequency (Hz)


void clock_init(void);
void SysTick_Handler(void);
void SysTick_DelayTicks(uint32_t n);


// This variable is manipulated by the ISR so that its value is changed
//  outside of the normal program flow. 
volatile uint32_t g_systickCounter;



int main(void) {
  
  gpio_pin_config_t gpio_config={    // struct for the LED pin
    kGPIO_DigitalOutput,
      0U,
      };

  clock_init();

  CLOCK_EnableClock(kCLOCK_Gpio0);             // Enable the clock for GPIO0 
  
  GPIO_PinInit(GPIO, 0U, BOARD_LED_PIN, &gpio_config); // Initialize GPIO pin 


  // Set systick reload value to generate 1ms interrupt (1000U times/second)
  //  This line configures the INT and starts it.
  SysTick_Config(SystemCoreClock / 1000U);
  
  
  
  while (1) {
    GPIO_PinWrite(GPIO, 0U, BOARD_LED_PIN, LED_ON);
    SysTick_DelayTicks(500U);  // Delay 500 ms
    GPIO_PinWrite(GPIO, 0U, BOARD_LED_PIN, LED_OFF);
    SysTick_DelayTicks(500U);  // Delay 500 ms
  }
} // END main()



// This is the ISR for the Systick INT.
// It has been defined in the file
//  startup_LPC824.S in the vector table around line 41:
//  .long   SysTick_Handler       /* SysTick Handler    */

// SysTick_Handler is configured to be called every millisecond. 
// See the function call: SysTick_Config(...) above.

void SysTick_Handler(void) {
    if (g_systickCounter != 0U) {
        g_systickCounter--;
    }
}



// This program sets and monitors the global variable g_systickCounter.
// This variable is decremented by SysTickHandler ISR each time it is called.

void SysTick_DelayTicks(uint32_t n){
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {}
}








// Setup clock source: Internal RC clock with the PLL set to 30MHz frequency:
void clock_init(void) {

  // Set up using Internal RC clock (IRC) oscillator:
  POWER_DisablePD(kPDRUNCFG_PD_IRC_OUT);        // Turn ON IRC OUT
  POWER_DisablePD(kPDRUNCFG_PD_IRC);            // Turn ON IRC

  CLOCK_Select(kSYSPLL_From_Irc);               // Connect IRC to PLL input.

  clock_sys_pll_t config;
  config.src = kCLOCK_SysPllSrcIrc;             // Select PLL source as IRC. 
  config.targetFreq = CORE_CLOCK*2;             // set pll target freq

  CLOCK_InitSystemPll(&config);                 // set parameters

  CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcSysPll); // Select PLL as main clock source.
  CLOCK_Select(kCLKOUT_From_Irc);               // select IRC for CLKOUT
  CLOCK_SetCoreSysClkDiv(1U);

  // Check processor registers and calculate the
  // Actual clock speed. This is stored in the
  // global variable SystemCoreClock
  SystemCoreClockUpdate ();

  /*
  // The following is for convenience and not necessary. AO.
  // It outputs the system clock on Pin 27
  //    so that we can check using an oscilloscope:


  // First activate the clock out function:
  SYSCON->CLKOUTSEL = (uint32_t)3; //set CLKOUT source to main clock.
  SYSCON->CLKOUTUEN = 0UL;
  SYSCON->CLKOUTUEN = 1UL;
  // Divide by a reasonable constant so that it is easy to view on an oscilloscope:
  //SYSCON->CLKOUTDIV = 100;
  SYSCON->CLKOUTDIV = 1000; 

  // Using the switch matrix, connect clock out to Pin 27:
  CLOCK_EnableClock(kCLOCK_Swm);     // Enables clock for switch matrix.
  SWM_SetMovablePinSelect(SWM0, kSWM_CLKOUT, kSWM_PortPin_P0_26);
  CLOCK_DisableClock(kCLOCK_Swm); // Disable clock for switch matrix.
*/  
}
