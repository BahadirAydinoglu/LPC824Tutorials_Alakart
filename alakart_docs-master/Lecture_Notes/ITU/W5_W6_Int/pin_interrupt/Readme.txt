

This example shows the PIN INT feature.

It was modified from the SDK eaxmple file:
Xpresso_SDK/boards/lpcxpresso824max/driver_examples/pint/pin_interrupt


See the file pint_pin_interrupt.c
The following is performed:
  Open the file pint_pin_interrupt.c and
  start comparing the following lines with the main() function:

* Initialize the processor
  -   InitPins();
      Initialize the pins.
    = Connect UART transmit and receive pins to PIO0_0 as RX, PIO0_4 as TX
    = Initialize PIO0_12 as input (on Alakart, PIO0_12 is SW2)

  -   clock_init();
      Initialize the processor clock for 30MHz frequency.

  -   uart_init();
      Initialize the UART for serial communications
    = Serial communication speed is 115200 Baud, 8 bits, 1 stop, no parity.

* SYSCON_AttachSignal(SYSCON, kPINT_PinInt1, kSYSCON_GpioPort0Pin12ToPintsel);
  Internally connect PIO0_12 source to Pin INT 1.

* PINT_Init(PINT);
  Initialize PINT; the pin interrupts.

* PINT_PinInterruptConfig(...
  Configure the pin interrupts for PINT1
  - trigger by the falling edge.
  - Set the callback function name.

* PINT_EnableCallbackByIndex(...
  Enable the the callback for PINT (all PINTs that have been configured).

* while (1) {
    __WFI();
  Finally, within the main loop, do nothing.
  The processor sleeps until an interrupt comes.


The PINT callback functon is: 
void pint_intr_callback(pint_pin_int_t pintr, uint32_t pmatch_status)

It prints out a message on a terminal when a pin INT has occurred.
The ISR for PINT0 is in the file:
Xpresso_SDK/devices/LPC824/drivers/fsl_pint.c
as the function:
void SEC_GPIO_INT0_IRQ0_DriverIRQHandler(void)

The callback itself is called from within that function.






