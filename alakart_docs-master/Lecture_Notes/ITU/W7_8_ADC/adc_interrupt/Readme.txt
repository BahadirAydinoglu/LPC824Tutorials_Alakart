

The "adc_interrupt" project demonstrates the use of the "conversion complete" interrupt of the ADC peripheral. It functions similarly to the "adc_basic" project, except that the end of conversion is signalled through a flag that is set by the ADC interrupt.

Refer to the "adc_basic" project for the setup and function of the program.

The difference is in three places:

1. After the ADC configuration, the Sequence A Conversion Complete interrupt is enabled in the ADC and NVIC:

  // Enable the interrupt the for Sequence A Conversion Complete:
  ADC_EnableInterrupts(ADC0, kADC_ConvSeqAInterruptEnable); // Within ADC0
  NVIC_EnableIRQ(ADC0_SEQA_IRQn);                           // Within NVIC

2. An ISR is written for servicing the ADC conversion complete interrupt which
   - Gets the conversion result
   - Writes it into the correct position in a structure
   - Sets a global flag "ADCConvCompleteFlag" to signal the main loop that the ISR has ran:
   
   void ADC0_SEQA_IRQHandler(void) 

3. Within the main loop, the polling is not on directly checking the ADC registers, but the flag "ADCConvCompleteFlag" to test if the interrupt has completed.

    // Wait until the "conversion complete flag" is set to true by the ISR
    while (ADCConvCompleteFlag == false) { } 





