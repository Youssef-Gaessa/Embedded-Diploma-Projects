# STOP_WATCH

1. Microcontroller: ATmega32 running at a clock frequency of 1 MHz.

2. Timer Configuration: Utilize Timer1 in CTC (Clear Timer on Compare Match) mode to measure and track the Stopwatch time.

3. Display Setup: Interface six Common Anode 7-segment displays through a 7447 BCD-to-7-segment decoder for time output.

4. External Interrupt INT0 (Reset Functionality):
*Trigger on falling edge.
*A push button with an internal pull-up resistor will reset the Stopwatch timer when activated.

5. External Interrupt INT1 (Pause Functionality):
*Trigger on rising edge.
*A push button connected with an external pull-down resistor will pause the Stopwatch timer when pressed.

6. External Interrupt INT2 (Resume Functionality):
*Trigger on falling edge.
*A push button with an internal pull-up resistor will resume the Stopwatch timer when activated.

This setup allows for precise Stopwatch control, utilizing external interrupts for easy reset, pause, and resume operations.
