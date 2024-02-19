

// This program demonstrates the switch matrix peripheral of LPC824.
// It is possible to connect the input or outputs of many peripheral devices
//  to any physical pin of the processor chip.
// In this example, serial port transmit pin is connected to
//  physical pin PIO0_4.
// On Alakart, PIO0_4 is connected to the USB serial converter to the PC.
// This is a minimal program and does not use any library functions.

// 2023 Ahmet Onat


#include <stdint.h> // Declarations of uint32_t etc.
#include "lpc824.h" // Declarations of LPC824 register names.


void delay(uint32_t counts); // The busy delay routine.
void config_uart0 (void);
void print (uint8_t * message);

int main(void) {

  uint32_t reg; // Dummy variable.
  uint8_t * message="Hello world!\n\r\0";

 
  SYSCON_SYSAHBCLKCTRL |= 0x400C0; // Enable clocks for IOCON, SWM & GPIO.

  
  SYSCON_PRESETCTRL &= ~(0x400);  // Assert  Reset of GPIO peripheral.
  SYSCON_PRESETCTRL |=   0x400;   // Release Reset of GPIO peripheral.
  // See 5.6.2 Peripheral reset control register in User Manual.

  
  //Make Pin PIO0_16 an output. On Alakart, PIO0_16 is the blue LED:
  GPIO_DIR0 |= (1<<16);

  
  // This is the configuration of SWM:
  // Set PINASSIGN0 for UART0 TXD. See 7.3.1 of User Manual
  reg = SWM_PINASSIGN0 & (~(0xff));
  SWM_PINASSIGN0= reg | 4;   // Set the lower 7 bits of PINASSIGN0 to 4: PIO0_4

  

  config_uart0();  // Configure UART0 for correct speed and byte format.
  
  while (1) { // Blink the LED in an infinite loop:
    
    GPIO_B16 = 0;    // Set pin low. (LED is ON)
    print (message);
    delay(1000000);

    GPIO_B16 = 1;    //Set pin high (LED is OFF)
    delay(1000000);
  }

}


// Delay timing is provided by a busy wait:
void delay(uint32_t counts) {

  uint32_t wait;
  for (wait=counts; wait>0; --wait){
  }

}



void print (uint8_t * message){

  uint8_t i;
  i=0;
  
  while(message[i]!='\0'){
    USART0_TXDAT=message[i];
    // Check if transmission has ended. See: 13.6.3 USART Status register:
    while ((USART0_STAT& 0b0100)==0);
    ++i;
  }
  

}


void config_uart0 (void){


  // The following steps set up the serial port USART0:
   // See User Manual
  // 13.3 Basic Configuration (USART)

  // 1. Turn the peripheral on:
  SYSCON_SYSAHBCLKCTRL |= 0x4000; // Enable clock for USART0.

  // 2. Set speed (baud rate) to 115200bps:
  // See Sec. 13.7.1.1 and 13.6.9 in User Manual.
  // Obtain a preliminary clock by first dividing the processor main clock
  // Processor main clock is 60MHz. (60000000)
  // Divide by 8 to obtain 7,500,000 Hz. intermediate clock.
  SYSCON_UARTCLKDIV=8; // USART clock div register.
 
  // Baud rate generator value is calculated from:
  // Intermediate clock /16 (always divided) = 468750Hz
  // To obtain 115200 baud transmission speed, we must divide further:
  // 468750/115200=4.069 ~= 4
  // Baud rate generator should be set to one less than this value.
  USART0_BRG=3;  //(4-1)  Baud rate generator register value.

  // 3. Enable USART & configure byte format for 8 bit, no parity, 1 stop bit:
  // (See 13.6.1 USART Configuration register)
  // (Bit 0) Enable USART 
  // (Bit 1) not used.
  // (Bit 2:3) Data Length 00 => 8 bits.
  // (Bit 4:5) Parity 00 => No parity (default)
  // (Bit 6) Stop bit  0 => 1:  (default)
  // (Bit 7) Reserved
  // The remaining bits are left at default values.
  USART0_CFG=0b00000101;

}
