

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
#include "xprintf.h" // For simple printout of numbers.

void delay(uint32_t counts); // The busy delay routine.
void config_uart0 (void);

void uart_putch (uint8_t character);

uint8_t uart_getch (void); // Dummy function.
void print (uint8_t * message);

#define BLU_LED_ON  GPIO_B16 = 0
#define BLU_LED_OFF  GPIO_B16 = 1

#define SYSTEM_CORE_CLOCK 30000000UL   //Declare system clock as 30MHz
// (The clock speed has been set in "init.c" file to 30MHz.)

static inline uint32_t SysTickConfig(uint32_t ticks);
void SysTick_Handler(void);  //our systick interrupt handler
void delay_ms(uint32_t ms);//delay (ms)

volatile uint32_t delaytime; // This is decremented by SysTick_Handler.


int main(void) {

  uint32_t reg; // Dummy variable.
  uint8_t * message="Hello world!\n\r\0";

  //  xdev_in(uart_getch);
  
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

  SysTickConfig(SYSTEM_CORE_CLOCK/1000);  //setup systick clock interrupt @1ms

  config_uart0();  // Configure UART0 for correct speed and byte format.

  xdev_out(uart_putch);

  
  xprintf("Test xprintf\r\n");
  //  uart_putch('A');

#define  ROM_DRIVER_TABLE_BASE  *((uint32_t*) (0x1FFF1FF8))
#define  SERIAL_ROM_API_BASE  *((uint32_t*) (0x1FFF1FF8)+9)
  // Serial is Base+0x24 = Base+36 -> Base+ (9*4) words.
#define  SPI_ROM_API_BASE  *((uint32_t*) (0x1FFF1FF8)+7)
  // SPI is Base+0x1C = Base+28 -> Base+ (7*4) words.


  BLU_LED_OFF;
  xprintf("Rom Driver Table: %X\n\r", ROM_DRIVER_TABLE_BASE);

  uint32_t * serial_ptr = SERIAL_ROM_API_BASE;

  xprintf("Serial Routines are at: %X\n\r",  serial_ptr);

  uint32_t * spi_ptr= SPI_ROM_API_BASE;

  xprintf("SPI Routines are at: %X\n\r", spi_ptr);
  
  
  
  while (1) { // Blink the LED in an infinite loop:
    
    BLU_LED_ON;
    //GPIO_B16 = 0;    // Set pin low. (LED is ON)
    delay_ms(200);

    BLU_LED_OFF;
    //GPIO_B16 = 1;    //Set pin high (LED is OFF)
    delay_ms(200);
  }

}


// Delay timing is provided by a busy wait:
void delay(uint32_t counts) {

  uint32_t wait;
  for (wait=counts; wait>0; --wait){
  }

}


void uart_putch (uint8_t character){
  // Check if transmission has ended. See: 13.6.3 USART Status register:
  while ((USART0_STAT& 0b0100)==0);
  USART0_TXDAT=character;

}


uint8_t uart_getch (void){ // Dummy function.

  return 65;
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


 //The interrupt handler for SysTick system time-base timer.
void SysTick_Handler(void) { 
  if (delaytime!=0){ // If delaytime has been set somewhere in the program,
    --delaytime;     //  decrement it every time SysTick event occurs (1ms).
  }
}


void delay_ms(uint32_t ms) {//delay (ms)

  delaytime=ms;        // Set the delay time to the number of millisecs of wait
  while(delaytime!=0){}// Wait here until the delay time expires.

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



