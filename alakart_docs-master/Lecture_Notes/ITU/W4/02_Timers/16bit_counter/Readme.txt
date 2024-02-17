
This project demonstrates the SDK SCTimer using the SCTimer counter as two 16-bit counters. The example toggles an output when the couter value matches the compare value.

It uses the Processor Support Library functions.

In this example, The SCTimer module generates two PWM signals.

The example will initialize clock, pin mux configuration, then configures the SCTimer module.
The example schedules a match event for Counter L every 0.1 seconds and
another match event for Counter H every 0.2 seconds.
SCTimer output 2 is toggled when Counter L event occurs.
SCTimer output 4 is toggled when Counter H event occurs.
Output 2 is connected to PIO0_27 (Green LED on Alakart)
Output 4 is connected to PIO0_16 ( Blue LED on Alakart)


Open a serial terminal in PC(for example PUTTY) with the following settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control

