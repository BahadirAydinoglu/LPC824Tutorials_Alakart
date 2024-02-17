
#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_swm.h"
#include "pin_mux.h"

void BOARD_InitBootPins(void) {
    BOARD_InitPins();
}


void BOARD_InitPins(void) {
  
  uint32_t IOCON_PIO_config; // This is the struct for keeping the GPIO pin conf
                   // See: User Manual Section 8.4.1 Pin Configuration & Fig.10
  
  CLOCK_EnableClock(kCLOCK_Iocon);   // Enable clock for IOCON block.
  CLOCK_EnableClock(kCLOCK_Swm);     // Enables clock for switch matrix.

  // In this processor, outputs of some peripheral devices
  //  can be connected to any GPIO pin by configuring a "Pin multiplexer".
  // (This is only possible for peripherals with "moveable pins"
  //
  //This code does the configuration.


  /////////////// SCT OUT4 Configuration /////////////////////////////////

  // Configure PIO_16, (Alakart label: P16)  as : SCT OUT4
  // This is the Blue LED
  // IC package physical pin is: 10,
  // GPIO pin name: PIO16_0
  // Peripheral: SCT, signal: OUT4,
  
  // First configure the GPIO pin characteristics:
  IOCON_PIO_config = (IOCON_PIO_MODE_PULLUP |  // Select pull-up function
		      IOCON_PIO_HYS_EN |       // Enable hysteresis
		      IOCON_PIO_INV_DI |       // Do not invert input
		      IOCON_PIO_OD_DI |        // Disable open-drain function
		      IOCON_PIO_SMODE_BYPASS | // Bypass the input filter
		      IOCON_PIO_CLKDIV0);      // IOCONCLKDIV = 0
  
  IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_16, IOCON_PIO_config);
  
  // Second, connect SCT_OUT4 to P0_16 using the multiplexer:
  // SCT_OUT4 is a moveable pin.
  // Connect it to Port 0, Pin 16: PIO0_16
  // PIO0_16 is pin #10  on the 32 pin IC package
  SWM_SetMovablePinSelect(SWM0, kSWM_SCT_OUT4, kSWM_PortPin_P0_16);


  /////////////////////////////////// SCT OUT2 Configuration /////////////////////////////////

  // Configure PIO_27, (Alakart label: P27) This is the Green LED
  // as : SCT OUT2
  // IC package physical pin is: 11,
  // GPIO pin name: PIO27_0
  // Peripheral: SCT, signal: OUT2
  
  // First configure the GPIO pin characteristics:
  IOCON_PIO_config =(IOCON_PIO_MODE_PULLUP |  // Select pull-up function
		     IOCON_PIO_HYS_EN |       // Enable hysteresis
		     IOCON_PIO_INV_DI |       // Do not invert input
		     IOCON_PIO_OD_DI |        // Disable open-drain function
		     IOCON_PIO_SMODE_BYPASS | // Bypass the input filter
		     IOCON_PIO_CLKDIV0);      // IOCONCLKDIV = 0
  IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_27, IOCON_PIO_config);

  // Second, connect SCT_OUT2 to P0_27 using the multiplexer:
  // SCT_OUT2 is a moveable pin.
  // Connect it to Port 0, Pin 27: PIO0_27
  // PIO0_27 is pin #11  on the 32 pin IC package
  SWM_SetMovablePinSelect(SWM0, kSWM_SCT_OUT2, kSWM_PortPin_P0_27);
  
  
  /////////////////////////////////// USART RXD Configuration /////////////////////////////////

  // Configure PIO0, PIN0 (Physical pin no: 24) as USART0, RXD:
  // IC package physical pin: 24,
  // GPIO pin name: PIO0_0/ACMP_I1/TDO,
  // Peripheral: USART0, signal: RXD,
  
  // First configure the GPIO pin characteristics:
  IOCON_PIO_config = (IOCON_PIO_MODE_PULLUP |  // Select pull-up function
		      IOCON_PIO_HYS_EN |       // Enable hysteresis
		      IOCON_PIO_INV_DI |       // Do not invert input
		      IOCON_PIO_OD_DI |        // Disable open-drain function
		      IOCON_PIO_SMODE_BYPASS | // Bypass the input filter
		      IOCON_PIO_CLKDIV0);      // IOCONCLKDIV = 0
  
  IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_0, IOCON_PIO_config);
  
  // Second, connect USART0_RXD to P0_0 using the multiplexer:
  // USART RXD is a moveable pin.
  // Connect it to Port 0, Pin 0: PIO0_0
  // PIO0_0 is pin #24  on the 32 pin IC package 
  SWM_SetMovablePinSelect(SWM0, kSWM_USART0_RXD, kSWM_PortPin_P0_0);
  
  
  /////////////////////////////////// USART TXD Configuration /////////////////////////////////

  // Configure PIO0, PIN4 (Physical pin no: 4) as USART0, TXD.
  // IC package physical pin: '4',
  // GPIO pin name: PIO0_4/ADC11/!TRST
  // Peripheral: USART0, signal: TXD,   
  
  // First configure the GPIO pin characteristics:
  IOCON_PIO_config = (IOCON_PIO_MODE_PULLUP |  // Select pull-up function
		      IOCON_PIO_HYS_EN |       // Enable hysteresis
		      IOCON_PIO_INV_DI |       // Do not invert input
		      IOCON_PIO_OD_DI |        // Disable open-drain function
		      IOCON_PIO_SMODE_BYPASS | // Bypass the input filter
		      IOCON_PIO_CLKDIV0);      // IOCONCLKDIV = 0
  IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_4, IOCON_PIO_config);
  
  // Second, connect USART0_TXD to P0_4 using the multiplexer:
  // USART TXD is a moveable pin.
  // Connect it to Port 0, Pin 4: PIO0_4
  // PIO0_4 is pin #4  on the 32 pin IC package 
  SWM_SetMovablePinSelect(SWM0, kSWM_USART0_TXD, kSWM_PortPin_P0_4);
  
  
  CLOCK_DisableClock(kCLOCK_Swm); // Disable clock for switch matrix.
}

