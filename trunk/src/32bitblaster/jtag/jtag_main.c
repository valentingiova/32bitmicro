/**
 * A command line interface to jtag.
 * Wait for a target to be connected to the jtag on the debugger,
 * and allow for various debugging commands.
 *
 * our ARM CPU:
 * chain 0:
 *   selected by default on reset, reserved, not really can be used
 * chain 1:
 *   JTAG <-> CORE interface
 *   33 bits: 32 bits data (MSB first) + 1 bit DBGBREAK
 * chain 2:
 *   JTAG <-> ICE interface
 *   38 bits:
 *     0 - 31: data
 *     32 - 36: ICE register address
 *     37: read/write (0 - read, 1 - write)
 */

#include <stdint.h>
#include <lpc2000/io.h>
#include <stdlib.h>

#define CLOCKS_PCLK 3000000
#include "systick.c"

#define UART0_BAUD_RATE 38400
#include "uart0.c"

#define  print_char(x) uart0SendByte(x)
#include "print.c"

#define print_div_line() \
	print("=====================================================\n")

void next_state(uint32_t tms);

/**
 * Show usage error.
 */
void printUnknownCmd(uint8_t input) {
	print_div_line();
	print("Unknown command: ");
	printNum(input);
	print("\n");
	print_div_line();
}

#include "cmd_jtag.c"
#include "cmd_arm.c"
#include "cmd_ice.c"


/**
 * Main command line interface.
 */
void main_print_menu() {
	print("\nInterpreter (One character at a time):\n");
	print("Main menu (ESC to exit):\n");
	print("  1 -> halt -> show cpu info -> resume\n");
	print("  2 -> goto JTAG menu\n");
	print("  3 -> goto ICE menu\n");
	print("  4 -> goto ARM core menu\n");
}


/**
 * Main command line implementation.
 */
int main(void) {
	uint8_t input;

	/* Needed for terminal communication. */
	uart0Init();
	if (jtag_init()) {
		exit(1);
	}

	/* Main loop. */
	while (1) {
		main_print_menu();
		input = getchar();
		print("\n");

		switch (input) {
		case (48 + 1):
			print_div_line();
		    ice_print_halt_target();
		    core_info();
		    arm_resume_target();
			print_div_line();
			break;
		case (48 + 2):
			jtag_cmd_run();
			break;
		case (48 + 3):
			ice_cmd_run();
			break;
		case (48 + 4):
			core_cmd_run();
			break;
		default:
			printUnknownCmd(input);
			break;
		}
	}

	return 0;
}
