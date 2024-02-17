

// This program sets up SCTimer 0 to produce 2 PWM signals.
// The signals are center aligned.
// The main() function simply configures the timer and does not do anything.

// Modified from NXP Xpresso_SDK, driver_examples simple_pwm
// by Ahmet Onat 2023


#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_sctimer.h"

#include <stdbool.h>

#define DEMO_FIRST_SCTIMER_OUT  kSCTIMER_Out_4
#define DEMO_SECOND_SCTIMER_OUT kSCTIMER_Out_2

int main(void) {

  // This struct stores several parameters of SCTimer:
  sctimer_config_t sctimerConfig;

  // This struct stores several parameters of the  PWM signal:
  sctimer_pwm_signal_param_t pwmParam;
  
  bool result;
  uint32_t event;
  uint32_t sctimerClock;
  
  
  CLOCK_EnableClock(kCLOCK_Uart0);    // Enable clock of uart0.
  
  // This sets the clock speed of UART. The baud rate is defined in board.c :
  CLOCK_SetClkDivider(kCLOCK_DivUsartClk, 1U);
  
  BOARD_InitBootPins();        // Initialize board pins.
  BOARD_InitBootClocks();      // Initialize clock signals.
  BOARD_InitDebugConsole();    // Initialize serial port for printout.
  
  CLOCK_EnableClock(kCLOCK_Sct); // Enable clock of SCTimer peripheral

  // What frequency is the SCTimer getting?:
  sctimerClock = CLOCK_GetFreq(kCLOCK_Irc);
  
  // Print a note to terminal:
  PRINTF("\r\nSCTimer example to output 2 center-aligned PWM signals\r\n");
  PRINTF("\r\nProbe the signal using an oscilloscope.\r\n");

  // sctimerConfig structure contains the configuration of SCTimer.
  // Set it to a default value. See the library function.
  SCTIMER_GetDefaultConfig(&sctimerConfig);
  
  SCTIMER_Init(SCT0, &sctimerConfig);  // Initialize SCTimer module:
  
  // Configure first PWM with frequency 24kHz from first output
  pwmParam.output           = kSCTIMER_Out_4; // This is the Blue LED.
  // High duty ratio will produce a higher average signal:
  pwmParam.level            = kSCTIMER_HighTrue;
  // However here 100 is dim, 0 is bright because LED anode is connected to VDD:
  pwmParam.dutyCyclePercent = 95;

  // Configure the timer with this function:
  //if (SCTIMER_SetupPwm(SCT0,                      // Use SCT0 timer.
  result=SCTIMER_SetupPwm(SCT0,                      // Use SCT0 timer.
		  &pwmParam,                 // Use the pwmParam struct.
		  kSCTIMER_CenterAlignedPwm, // Generate center aligned PWM
		  24000U,                    // Freq is 24kHz
		  sctimerClock,              // Use the clock from sctimer
		  &event);

  // Check if the operation was successful:
  if (result== kStatus_Fail){  //If it did not succeed: 
    PRINTF("Cannot set required parameters for PWM1.\n\r");
    return -1;
  }else{
    PRINTF("SCT PWM1 was set successfully.\n\r");
  }
  
  //Configure the second PWM with a different duty ratio.
  pwmParam.output           = kSCTIMER_Out_2;  // Use this output "pin"
  // High duty ratio will produce a lower average signal:
  pwmParam.level            = kSCTIMER_LowTrue;
  pwmParam.dutyCyclePercent = 25;             // This is the duty ratio.
  
  result=SCTIMER_SetupPwm(SCT0,              // Use SCT0 timer.
		  &pwmParam,                 // Use the pwmParam struct.
		  kSCTIMER_CenterAlignedPwm, // Generate center aligned PWM
		  24000U,                    // Freq is 24kHz
		  sctimerClock,              // Use the clock from sctimer
		  &event);

  // Check if the operation was successful:
  if (result== kStatus_Fail){  //If it did not succeed: 
    PRINTF("Cannot set required parameters for PWM2.\n\r");
    return -1;
  }else{
    PRINTF("SCT PWM2 was set successfully.\n\r");
  }
  
  // Start the 32-bit unified timer
  SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_U);
  PRINTF("Starting SCT0.\n\r");
  
  while (1){
    // Main does nothing.  SCT is producing the PWM signals in hardware.
  }
}
