# lightfly_vm_avr
Lightweight register-based virtual machine runner for AVR architecture

For VM specifications look [here](https://github.com/roman901/lightfly_vm/SPEC.md)

## Hardware default target
**ATMega16**

**1KB** RAM

**32KB** ROM

**PinBoard II** development board

This code uses first LED for display execution status:
* Blinking fast - **malloc** problems, check available RAM, stack, etc
* Blinking at medium speed - error when parsing program header
* Blinking at slow speed - exception while execution was occured

Third led blinks when next opcode is executed