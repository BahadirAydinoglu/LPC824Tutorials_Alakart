//Copyright (c) 2016, Freescale Semiconductor, Inc.
// Copyright 2016-2019 NXP
// All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

// Modified heavily from 
// Xpresso_SDK/boards/lpcxpresso824max/driver_examples/adc/lpc_adc_interrupt
// AO 2023

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_adc.h"
#include "fsl_clock.h"
#include "fsl_power.h"

#include <stdbool.h>

#define ADC_CHANNEL 1U  // Channel 1 will be used in this example.

#define ADC_CLOCK_DIVIDER 1U // See Fig 52. ADC clocking in Ref Manual.

// The pointer and flag are global so that ISR can manipulate them:
adc_result_info_t *volatile ADCResultPtr; 
volatile bool ADCConvCompleteFlag;

void ADC_Configuration(adc_result_info_t * ADCResultStruct);


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

  
  while (1) {
    GETCHAR();  //Wait for an ADC conversion request from the user terminal.
    ADCConvCompleteFlag = false;
    ADC_DoSoftwareTriggerConvSeqA(ADC0); // Start conversion.

    // Wait until the "conversion complete flag" is set to true by the ISR
    while (ADCConvCompleteFlag == false) { } 
    
    PRINTF("Ch %d result = %d\r\n\n",
	   ADCResultStruct.channelNumber,
	   ADCResultStruct.result);

  }  // END: while(1)

} // END: main()



//ISR for ADC conversion sequence A done.
void ADC0_SEQA_IRQHandler(void) {
    if (kADC_ConvSeqAInterruptFlag ==
	(kADC_ConvSeqAInterruptFlag & ADC_GetStatusFlags(ADC0))) {

      ADC_GetChannelConversionResult(ADC0, ADC_CHANNEL, ADCResultPtr);

      ADC_ClearStatusFlags(ADC0, kADC_ConvSeqAInterruptFlag);

      ADCConvCompleteFlag = true;
    }
    
    //    SDK_ISR_EXIT_BARRIER;
}

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

  adcConvSeqConfigStruct.triggerMask      = 0U;
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
