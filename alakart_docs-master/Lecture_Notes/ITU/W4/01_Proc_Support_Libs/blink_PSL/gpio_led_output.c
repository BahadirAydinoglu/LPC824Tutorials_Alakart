

#include "fsl_gpio.h"
#include "fsl_power.h"
#include "fsl_clock.h"
#include "fsl_swm_connections.h"

#include <stdint.h>

#define GRN_LED_PORT 0
#define GRN_LED_PIN  16

#define CORE_CLOCK   30000000U  // Set CPU Core clock frequency (Hz)

void delay(uint32_t counts); // The busy delay routine.
void clock_init(void);


int main(void) {

  gpio_pin_config_t led_config = {    // struct for the LED pin
				  kGPIO_DigitalOutput,
				  0,
  };

  clock_init();        // Initialize the processor main clock.

  // Initialize GPIO port that LED is connected:
  // (Hint: There is only port 0 in this processor)
  GPIO_PortInit(GPIO, GRN_LED_PORT);     
  
  // Initialize the GPIO pin that the LED is connected:
  GPIO_PinInit(GPIO, GRN_LED_PORT, GRN_LED_PIN, &led_config);


  // Write the desired value. Remember that '0' turns LED ON:
  GPIO_PinWrite(GPIO, GRN_LED_PORT, GRN_LED_PIN, 0);



  
  /*
  // This is the standard way of starting the SysTick interrupt:
  if (SysTick_Config(SystemCoreClock / 1000U)) {
    while (1) { }
  }
  */
  
  while (1) {                  // The main loop.
    
    GPIO_PinWrite(GPIO, GRN_LED_PORT, GRN_LED_PIN, 0);  // Turn LED ON
    delay(500000);
    
    GPIO_PinWrite(GPIO, GRN_LED_PORT, GRN_LED_PIN, 1);  // Turn LED OFF
    delay(500000);
    
    
  }
}


// Delay timing is provided by a busy wait:
void delay(uint32_t counts) {

  uint32_t wait;
  for (wait=counts; wait>0; --wait){
  }

}

void clock_init(void) {    // Set up the clock source

  // Set up IRC
  POWER_DisablePD(kPDRUNCFG_PD_IRC_OUT);        // Turn ON IRC OUT
  POWER_DisablePD(kPDRUNCFG_PD_IRC);            // Turn ON IRC
  //POWER_DisablePD(kPDRUNCFG_PD_SYSOSC);       // In Alakart SYSOSC is not used.
  CLOCK_Select(kSYSPLL_From_Irc);               // Connect IRC to PLL input.
  clock_sys_pll_t config;
  config.src = kCLOCK_SysPllSrcIrc;             // Select PLL source as IRC. 
  config.targetFreq = CORE_CLOCK*2;             // set pll target freq
  CLOCK_InitSystemPll(&config);                 // set parameters
  //CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcIrc);  // Select IRC as main clock source.
  CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcSysPll); // Select PLL as main clock source.
  CLOCK_Select(kCLKOUT_From_Irc);               // select IRC for CLKOUT
  CLOCK_SetCoreSysClkDiv(1U);
  //CLOCK_UpdateClkOUTsrc();
  // Set SystemCoreClock variable.
  //    SystemCoreClock = CORE_CLOCK;

  // Check processor registers and calculate the
  // Actual clock speed. This is stored in the
  // global variable SystemCoreClock
  SystemCoreClockUpdate ();

  // The following is for convenience and not necessary. AO.
  // It outputs the system clock on Pin 27
  //    so that we can check using an oscilloscope:
  // First activate the clock out function:
  SYSCON->CLKOUTSEL = (uint32_t)3; //set CLKOUT source to main clock.
  SYSCON->CLKOUTUEN = 0UL;
  SYSCON->CLKOUTUEN = 1UL;
  // Divide by a reasonable constant so that it is easy to view on an oscilloscope:
  //SYSCON->CLKOUTDIV = 100;
  SYSCON->CLKOUTDIV = 2000; 

  // Using the switch matrix, connect clock out to Pin 27:
  CLOCK_EnableClock(kCLOCK_Swm);     // Enables clock for switch matrix.
  SWM_SetMovablePinSelect(SWM0, kSWM_CLKOUT, kSWM_PortPin_P0_27);
  CLOCK_DisableClock(kCLOCK_Swm); // Disable clock for switch matrix.

}
