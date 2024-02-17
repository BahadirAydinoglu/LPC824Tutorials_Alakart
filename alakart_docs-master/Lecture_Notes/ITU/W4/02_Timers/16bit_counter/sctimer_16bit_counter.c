
// This program sets up SCTimer 0 to produce two counters.
// The counters are set to count at different periods (speeds).
//  See the description at the initial printout.
// The main() function only configures the timer and does not do anything else.

// Heavily modified from NXP Xpresso_SDK, driver_examples 16bit_counter


#include "pin_mux.h"
#include "fsl_sctimer.h"
#include "fsl_swm.h"
#include "fsl_swm_connections.h"
#include "fsl_power.h"



void clock_init(void);

#define CORE_CLOCK   30000000U  // Set CPU Core clock frequency (Hz)


int main(void) {
  
  
  sctimer_config_t sctimerConfig;
  uint32_t eventCounterL, eventCounterH;
  uint16_t matchValueL, matchValueH;
  // sctimer_event_active_direction_t activeDirL, activeDirH;
  
  
  InitPins();                           // Init board pins.
  clock_init();                         // Initialize processor clock.
  
  CLOCK_EnableClock(kCLOCK_Sct);        // Enable clock of sct.
  
  
  // SCTimer in 16-bit mode.
  // Both 16-bit counters run
  // and periodicaly toggle an output.
  // Counter 'L' runs at 0.1ms period and is connected to OUT2
  // OUT2 is connected to PIO0_27 using the SWM.
  // On Alakart, PIO0_27 is the Green LED.
  // Counter 'H' runs at 0.2ms period and is connected to OUT4
  // OUT4 is configured to connect to PIO0_16 using the SWM.
  // On Alakart, PIO0_16 is the Blue LED.
  
  
  
  SCTIMER_GetDefaultConfig(&sctimerConfig);
  

  // Set the configuration struct for the timer:
// For more information, see:  Xpresso_SDK/devices/LPC824/drivers/fsl_sctimer.h
  sctimerConfig.enableCounterUnify = false; // Use as two 16 bit timers.
  
  sctimerConfig.clockMode = kSCTIMER_System_ClockMode; // Use system clock as SCT input
  
  sctimerConfig.enableBidirection_l= false; // Use as single directional register.
  sctimerConfig.enableBidirection_h= false; // Use as single directional register.
  
  // Prescaler is 8 bit, in: CTRL. See: 16.6.3 SCT control register
  sctimerConfig.prescale_l = 249; // Thi value +1 is used.
  sctimerConfig.prescale_h = 249; // Becomes 250.
  
  matchValueL= 60000; // This is in: 16.6.20 SCT match registers 0 to 7
  matchValueH= 30000; // They are 16 bit values (for an 16 bit counter)
  
  
  
  
  SCTIMER_Init(SCT0, &sctimerConfig);    // Initialize SCTimer module
  

  // Configure the low side counter.
  
  // Schedule a match event for the 16-bit low counter:
  SCTIMER_CreateAndScheduleEvent(SCT0,
				 kSCTIMER_MatchEventOnly,
				 matchValueL,
				 0,    // Not used for "Match Only"
				 kSCTIMER_Counter_L,
				 &eventCounterL);
  
  // Toggle output_2 when the 16-bit low counter event occurs:
  SCTIMER_SetupOutputToggleAction(SCT0, kSCTIMER_Out_2, eventCounterL);
  
  // Reset Counter L when the 16-bit low counter event occurs
  SCTIMER_SetupCounterLimitAction(SCT0, kSCTIMER_Counter_L, eventCounterL);
  
  // Setup the 16-bit low counter event active direction
  //  See fsl_sctimer.h
  SCTIMER_SetupEventActiveDirection(SCT0,
				    kSCTIMER_ActiveIndependent,
				    eventCounterL);
  
  
  // Configure the high side counter.
  
  // Schedule a match event for the 16-bit high counter every 0.2 seconds
  SCTIMER_CreateAndScheduleEvent(SCT0,
				 kSCTIMER_MatchEventOnly,
				 matchValueH,
				 0,    // Not used for "Match Only"
				 kSCTIMER_Counter_H,
				 &eventCounterH);
  
  // Setup the 16-bit high counter event active direction
  SCTIMER_SetupEventActiveDirection(SCT0,
				    kSCTIMER_ActiveIndependent,
				    eventCounterH);
  
  // Toggle second output when the 16-bit high counter event occurs
  SCTIMER_SetupOutputToggleAction(SCT0, kSCTIMER_Out_4, eventCounterH);
  
  // Reset Counter H when the 16-bit high counter event occurs
  SCTIMER_SetupCounterLimitAction(SCT0, kSCTIMER_Counter_H, eventCounterH);
  
  // Start the 16-bit low and high counter
  SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L | kSCTIMER_Counter_H);
  
  while (1) {
    // SC Timer is doing all the work.
    // main() can simply do nothing.
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
