

// This program sets up SCTimer 0 to produce 2 PWM signals.
// The signals are center aligned.
// The main() function simply configures the timer and does not do anything.

// Modified from NXP Xpresso_SDK, driver_examples simple_pwm
// by Ahmet Onat 2023


#include "pin_mux.h"
#include "fsl_power.h"
#include "fsl_swm.h"
#include "fsl_swm_connections.h"
#include "fsl_sctimer.h"



#define CORE_CLOCK   30000000U  // Set CPU Core clock frequency (Hz)

void clock_init(void);




int main(void) {

  // This struct stores several parameters of SCTimer:
  sctimer_config_t sctimerConfig;

  // This struct stores several parameters of the  PWM signal:
  sctimer_pwm_signal_param_t pwmParam;
  
  bool result;
  uint32_t event;
  uint32_t sctimerClock;
  
  
  CLOCK_EnableClock(kCLOCK_Uart0);    // Enable clock of uart0.
  
  
  InitPins();        // Initialize board pins.
  clock_init();      // Initialize processor clock.
  
  
  CLOCK_EnableClock(kCLOCK_Sct); // Enable clock of SCTimer peripheral


  // What frequency is the SCTimer getting?:
  //sctimerClock = CLOCK_GetFreq(kCLOCK_Irc);
  sctimerClock = CORE_CLOCK;
  
  // SCTimer example to output 2 center-aligned PWM signals.
  // Probe the signal using an oscilloscope.

  // sctimerConfig structure contains the configuration of SCTimer.
  // Set it to a default value. See the library function.
  SCTIMER_GetDefaultConfig(&sctimerConfig);

  SCTIMER_Init(SCT0, &sctimerConfig);  // Initialize SCTimer module:
  
  // Configure first PWM with frequency 24kHz from first output
  pwmParam.output           = kSCTIMER_Out_4; // This is the Blue LED.
  // High duty ratio will produce a higher average signal:
  pwmParam.level            = kSCTIMER_HighTrue;
  // However here 100 is dim, 0 is bright because LED anode is connected to VDD:
  pwmParam.dutyCyclePercent = 98;

  // Configure the timer:
  SCTIMER_SetupPwm(SCT0,                      // Timer is SCT0.
		   &pwmParam,                 // Use the pwmParam struct.
		   kSCTIMER_CenterAlignedPwm, // Generate center aligned PWM
		   24000U,                    // Freq is 24kHz
		   sctimerClock,              // Use the clock from sctimer
		   &event);
  
  
  //Configure the second PWM with a different duty ratio.
  pwmParam.output           = kSCTIMER_Out_2;  // Use this output "pin"
  // High duty ratio will produce a lower average signal:
  pwmParam.level            = kSCTIMER_HighTrue;
  pwmParam.dutyCyclePercent = 25;             // This is the duty ratio.
  
  SCTIMER_SetupPwm(SCT0,              // Use SCT0 timer.
		   &pwmParam,                 // Use the pwmParam struct.
		   kSCTIMER_CenterAlignedPwm, // Generate center aligned PWM
		   24000U,                    // Freq is 24kHz
		   sctimerClock,              // Use the clock from sctimer
		   &event);
  
  
  // Start the 32-bit unified timer
  SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_U);
  
  while (1){
    // Main does nothing.  SCT is producing the PWM signals in hardware.
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
  // It outputs the system clock on Pin 26
  //    so that we can check using an oscilloscope:
  // First activate the clock out function:
  SYSCON->CLKOUTSEL = (uint32_t)3; //set CLKOUT source to main clock.
  SYSCON->CLKOUTUEN = 0UL;
  SYSCON->CLKOUTUEN = 1UL;
  // Divide by a reasonable constant so that it is easy to view on an oscilloscope:
  //SYSCON->CLKOUTDIV = 100;
  SYSCON->CLKOUTDIV = 2000; 

  // Using the switch matrix, connect clock out to Pin 26:
  CLOCK_EnableClock(kCLOCK_Swm);     // Enables clock for switch matrix.
  SWM_SetMovablePinSelect(SWM0, kSWM_CLKOUT, kSWM_PortPin_P0_26);
  CLOCK_DisableClock(kCLOCK_Swm); // Disable clock for switch matrix.

}
