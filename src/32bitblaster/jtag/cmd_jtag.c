/**
 * underlying jtag command line interface.
 */

#include "jtag.c"


/**
 * Print the target's idcode.
 */
void jtag_print_idcode() {
	uint32_t idcode = jtag_getIdCode();
	print("the target's idcode is: ");
	printHex(idcode, 8);
	print("\n");
}


/**
 * Test the jtag bypass.
 * We send a magic number and expect to see it in the bus,
 * shifted 1 to the left because of the bypass delay of 1 clock.
 */
void jtag_print_test_bypass() {
	print("bypass should introduce 1 clock delay\n"
		  "we send: 0xdeadbeef and expect: ");
	printHex(0xdeadbeef << 1, 8);
	print("\n");
	print("bypass came back with: ");
	printHex(jtag_test_bypass(), 8);
	print("\n");
}


/**
 * Change the jtag chain to chain.
 */
void jtag_print_change_chain(uint32_t chain) {
	jtag_change_chain(chain);
	print("changing chain to: ");
	printNum(chain);
	print("\n");
}


/**
 * Print the last jtag command's output.
 */
void jtag_print_dr32(void) {
	uint32_t ret = dr_scan(32, 0x0);
	print("DR 32 bit: ");
	printHex(ret, 8);
	print("\n");
}


/**
 * Send a jtag restart command.
 */
void jtag_print_send_restart() {
	print("sending RESTART ... \n");
	jtag_send_restart();
	print("done.\n");
}


/**
 * The jtag command line interface.
 */
void jtag_print_menu(void) {
	print("\nJTAG commands ('0' to go up; ESC to exit):\n");
	print("  1 -> print IDCODE\n");
	print("  2 -> test bypass\n");
	print("  3 -> change to chain 1\n");
	print("  4 -> change to chain 2\n");
	print("  5 -> read 32 bits from DR\n");
	print("  6 -> send RESTART\n");
}


/**
 * Implementation of the jtag command line interface.
 */
void jtag_cmd_run(void) {
	uint8_t input;

	while (1) {
		jtag_print_menu();
		input = getchar();
		print("\n");

		switch (input) {
		case (48 + 0):
			return;
		case (48 + 1):
			print_div_line();
			jtag_print_idcode();
			print_div_line();
			break;
		case (48 + 2):
			print_div_line();
			jtag_print_test_bypass();
			print_div_line();
			break;
		case (48 + 3):
			print_div_line();
			jtag_print_change_chain(0x1);
			print_div_line();
			break;
		case (48 + 4):
			print_div_line();
			jtag_print_change_chain(0x2);
			print_div_line();
			break;
		case (48 + 5):
			print_div_line();
			jtag_print_dr32();
			print_div_line();
			break;
		case (48 + 6):
			print_div_line();
			jtag_print_send_restart();
			print_div_line();
			break;
		default:
			printUnknownCmd(input);
			break;
		}
	}
}
