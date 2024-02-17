
	// This is a simple program in assembly language
	// It initializes the processor and starts to blink a LED.
	// Written By Ayhan Bozkurt, 2023
	
	// Assembly directives are here.
	// Any command that starts with a '.' does not get compiled;
	//   it is a message to the assembler.
	// Specify the processor type:
	.syntax unified
	.arch armv6-m   // Processor architecture.
	.thumb          // Instruction set declaration.


	// The processor starts executing the code from address 0x0000,0000
	// First is the stack pointer (to be described in class)
	// The second is the "Reset Handler". This points to the address
	//  that the processor should go to after starting up.
	//  It is the first line of code in our program that the processor
	//  must execute.
	.section .vectors,"ax",%progbits
	.word 0x10002000
	.word _start+1  // The program will start running the code with the label "_start". 
	.text
	.global _start  // Make it known to all programs.

	
_start:  // This is where the program starts from.

	// Initialize the GPIO port:
	ldr  r2, DIR0
	ldr  r3, PINS
	str  r3, [r2]

	// Prepare for the main loop:
	ldr  r2, GPIO
	movs r3, #0
	movs r4, #1
main:
	strb r3, [r2, 12] // Reset (r3=0) bit 12 of GPIO (stored in r2)
	                  // This will turn on the RED LED on Pin 12.

	bl   delay        // Branch into subroutine called "delay"
	strb r4, [r2, 12] // Set (r4=1) bit 12 of GPIO (stored in r2)
	                  // This will turn off the RED LED on Pin 12.

	bl   delay        // Branch into subroutine called "delay"
	b main            // Branch into subroutine called "main"


	// These are some constants used in the program.
	.align 2
GPIO:	.word 0xA0000000	// GPIO port base value
DIR0:	.word 0xA0002000	// IOCON base address value
PINS:	.word 0x00001000	// bit 12 OUTPUT value.	


delay:    // This is a subroutine (a primitive function)
	ldr  r7, DELAY
delayloop:
	nop
	nop
	subs r7, r7, #1
	bne  delayloop
	mov  pc, lr		/* return to caller */

	// This is a constant, showing the delay count.
	.align 2
DELAY:	.word 500000
	.end
