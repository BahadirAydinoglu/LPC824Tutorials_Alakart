

// This is an example program where the timer is used to directly initiate an
// ADC conversion sequence.
// At the end of the sequence, the ADC triggers the
//  "ADC0 Sequence A conversion complete interrupt" and the corresponding ISR
//  prints out the conversion result to the terminal.

// AO 2023

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_adc.h"
#include "fsl_sctimer.h"
#include "fsl_clock.h"
#include "fsl_power.h"

#include <stdbool.h>

#define ADC_CHANNEL 1U  // Channel 1 will be used in this example.

#define ADC_CLOCK_DIVIDER 1U // See Fig 52. ADC clocking in Ref Manual.

// The pointer and flag are global so that ISR can manipulate them:
adc_result_info_t *volatile ADCResultPtr; 
volatile bool ADCConvCompleteFlag;

void ADC_Configuration(adc_result_info_t * ADCResultStruct);
void SCT_Configuration(void);

int main(void) {
  
  uint32_t frequency = 0U;
  adc_result_info_t ADCResultStruct;

  ADCResultPtr = &ADCResultStruct; // The global pointer points to this variable
  
  BOARD_InitPins();
  BOARD_InitBootClocks();
  
  CLOCK_EnableClock(kCLOCK_Uart0);    // Enable UART0 clock
  CLOCK_SetClkDivider(kCLOCK_DivUsartClk, 1U); // Set UART0 clock divider
  BOARD_InitDebugConsole();
  
  PRINTF("ADC interrupt example.\r\n");


  CLOCK_EnableClock(kCLOCK_Sct);      // Enable clock of sct.
  SCT_Configuration();
  
  CLOCK_EnableClock(kCLOCK_Adc);      // Enable ADC clock

  POWER_DisablePD(kPDRUNCFG_PD_ADC0); // Power on ADC0
  
  // Hardware calibration is required after each chip reset.
  // See: Sec. 21.3.4 Hardware self-calibration
  frequency = CLOCK_GetFreq(kCLOCK_Irc);

  if (true == ADC_DoSelfCalibration(ADC0, frequency)) {
    PRINTF("ADC Calibration Done.\r\n");
  } else {
    PRINTF("ADC Calibration Failed.\r\n");
  }
  

  ADC_Configuration(&ADCResultStruct);    // Configure ADC and operation mode.
  
  // Enable the interrupt the for Sequence A Conversion Complete:
  ADC_EnableInterrupts(ADC0, kADC_ConvSeqAInterruptEnable); // Within ADC0
  NVIC_EnableIRQ(ADC0_SEQA_IRQn);                           // Within NVIC
  
  PRINTF("Configuration Done.\r\n\n");

  
    /*
     * The main loop is completely empty.
     * All ADC conversion is handled by the hardware.
     *
     * ADC0 conversion is triggered by the hardware: SCT OUTPUT 3 event
     * When SCT OUTPUT3 changes, the conversion of Sequence A starts.
     *
     * When the conversion is complete,
     *   SEQA_INT (Sequence A conversion complete INT) is triggered.
     * This calls ADC0_SEQA_IRQHandler function which finally prints out
     *  the conversion result to the serial port (and to the terminal screen.)
     *
     * This has two advantages:
     * 1. The main loop is free to do other tasks.
     * 2. The sampling time of the analog channels is precise.
     *
    */
    
  while (1) {
    
  } 

  
} // END: main()



//ISR for ADC conversion sequence A done.
void ADC0_SEQA_IRQHandler(void) {
    if (kADC_ConvSeqAInterruptFlag ==
	(kADC_ConvSeqAInterruptFlag & ADC_GetStatusFlags(ADC0))) {

      ADC_GetChannelConversionResult(ADC0, ADC_CHANNEL, ADCResultPtr);

      ADC_ClearStatusFlags(ADC0, kADC_ConvSeqAInterruptFlag);

      PRINTF("Ch %d result = %d    \r", // See below for PRINTF usage in an ISR.
	     ADCResultPtr->channelNumber,
	     ADCResultPtr->result);
      
      /* ignore this part. It is for demo using SerialPlot:
      PRINTF("%d.\r\n", // See below for PRINTF usage in an ISR.
	     //ADCResultPtr->channelNumber,
	     ADCResultPtr->result);
      */
      
      // ADCConvCompleteFlag is not used in this program.
      //However if any task in the main loop must be informed of the
      //  ADC conversion, that task can check this flag;
      //  when the flag is true,  the task can use the conversion result:
      ADCConvCompleteFlag = true; 
    }
}

// Usage of long functions in an ISR:
// Note that in general an ISR must be written to complete and exit
// as quickly as possible.
// PRINTF is a function that may take a long time to execute.
// So it is not advisable to use PRINTF in an ISR.
// However, PRINTF is used in an ISR here to
//  emphasize that the main loop is not doing anything.




// Configure and initialize the ADC
void ADC_Configuration(adc_result_info_t * ADCResultStruct) {

  adc_config_t adcConfigStruct;
  adc_conv_seq_config_t adcConvSeqConfigStruct;
  
  adcConfigStruct.clockDividerNumber = ADC_CLOCK_DIVIDER; // Defined above.
  adcConfigStruct.enableLowPowerMode = false;
  // See Sec. 21.6.11 A/D trim register (voltage mode):
  adcConfigStruct.voltageRange = kADC_HighVoltageRange;
  
  ADC_Init(ADC0, &adcConfigStruct); // Initialize ADC0 with this structure.
  
  // Insert this channel in Sequence A, and set conversion properties:
  // See Sec: 21.6.2 A/D Conversion Sequence A Control Register
  adcConvSeqConfigStruct.channelMask = (1U << ADC_CHANNEL); 

  // Triggered by SCT OUT3 event. See Table 277. "ADC hardware trigger inputs":
  adcConvSeqConfigStruct.triggerMask      = 3U;
  
  adcConvSeqConfigStruct.triggerPolarity  = kADC_TriggerPolarityPositiveEdge;
  adcConvSeqConfigStruct.enableSingleStep = false;
  adcConvSeqConfigStruct.enableSyncBypass = false;
  adcConvSeqConfigStruct.interruptMode    = kADC_InterruptForEachSequence;
  
  // Initialize the ADC0 with the sequence defined above:
  ADC_SetConvSeqAConfig(ADC0, &adcConvSeqConfigStruct);
  
  ADC_EnableConvSeqA(ADC0, true); // Enable the conversion sequence A.
  
  // Make the first ADC conversion so that
  //  the result register has a sensible initial value.
  ADC_DoSoftwareTriggerConvSeqA(ADC0);
  
  while (!ADC_GetChannelConversionResult(ADC0, ADC_CHANNEL, ADCResultStruct))
    { }
  
  ADC_GetConvSeqAGlobalConversionResult(ADC0, ADCResultStruct);
}




void SCT_Configuration(void){

  
  sctimer_config_t sctimerConfig;
  uint32_t eventCounterL;
  uint16_t matchValueL;
  
  
  SCTIMER_GetDefaultConfig(&sctimerConfig);
  
  // Set the configuration struct for the timer:
  // For more information, see:  Xpresso_SDK/devices/LPC824/drivers/fsl_sctimer.h
  sctimerConfig.enableCounterUnify = false; // Use as two 16 bit timers.
  
  sctimerConfig.clockMode = kSCTIMER_System_ClockMode; // Use system clock as SCT input


  matchValueL= 5000; // This is in: 16.6.20 SCT match registers 0 to 7
  sctimerConfig.enableBidirection_l= false; // Use as single directional register.
  // Prescaler is 8 bit, in: CTRL. See: 16.6.3 SCT control register
  sctimerConfig.prescale_l = 249; // Thi value +1 is used.

  
  SCTIMER_Init(SCT0, &sctimerConfig);    // Initialize SCTimer module
  

  // Configure the low side counter.
  // Schedule a match event for the 16-bit low counter:
  SCTIMER_CreateAndScheduleEvent(SCT0,
				 kSCTIMER_MatchEventOnly,
				 matchValueL,
				 0,    // Not used for "Match Only"
				 kSCTIMER_Counter_L,
				 &eventCounterL);

  // TODO: Rather than toggle, it should set the output:
  // Toggle output_3 when the 16-bit low counter event occurs:
  SCTIMER_SetupOutputToggleAction(SCT0, kSCTIMER_Out_3, eventCounterL);
  
  // Reset Counter L when the 16-bit low counter event occurs
  SCTIMER_SetupCounterLimitAction(SCT0, kSCTIMER_Counter_L, eventCounterL);
  
  // Setup the 16-bit low counter event active direction
  //  See fsl_sctimer.h
  SCTIMER_SetupEventActiveDirection(SCT0,
				    kSCTIMER_ActiveIndependent,
				    eventCounterL);
  
  
  // Start the 16-bit low counter
  SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);
}
