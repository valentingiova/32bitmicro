/**
 * ice jtag command line interface.
 */

#include "ice.c"


/**
 * Show info on watchpoint 0 registers.
 */
void ice_print_watchpoint0_regs() {
	print("Watch Point 0 regs:\n");

	print("ADDRESS:        ");
	printHex(ice_read(ICE_WATCH_0_ADDRESS), 8);
	print("\nADDRESS MASK: ");
	printHex(ice_read(ICE_WATCH_0_ADDRESS_MASK), 8);
	print("\n");

	print("DATA:           ");
	printHex(ice_read(ICE_WATCH_0_DATA), 8);
	print("\nDATA MASK:    ");
	printHex(ice_read(ICE_WATCH_0_DATA_MASK), 8);
	print("\n");

	print("CONTROL:        ");
	printHex(ice_read(ICE_WATCH_0_CONTROL), 8);
	print("\nCONTROL MASK: ");
	printHex(ice_read(ICE_WATCH_0_CONTROL_MASK), 8);
	print("\n");

	print("\n");
}


/**
 * Show info on watchpoint 1 registers.
 */
void ice_print_watchpoint1_regs() {
	print("Watch Point 1 regs:\n");

	print("ADDRESS:        ");
	printHex(ice_read(ICE_WATCH_1_ADDRESS), 8);
	print("\nADDRESS MASK: ");
	printHex(ice_read(ICE_WATCH_1_ADDRESS_MASK), 8);
	print("\n");

	print("DATA:           ");
	printHex(ice_read(ICE_WATCH_1_DATA), 8);
	print("\nDATA MASK:    ");
	printHex(ice_read(ICE_WATCH_1_DATA_MASK), 8);
	print("\n");

	print("CONTROL:        ");
	printHex(ice_read(ICE_WATCH_1_CONTROL), 8);
	print("\nCONTROL MASK: ");
	printHex(ice_read(ICE_WATCH_1_CONTROL_MASK), 8);
	print("\n");

	print("\n");
}


/**
 * Halt the target and save the context.
 */
void ice_print_halt_target() {
	print("Stopping target\n");
	ice_halt();
	print("saving context\n");
	arm_save_context();
	print("done.\n\n");
}


/**
 * Show debug status register.
 */
void ice_print_dbg_status_reg() {
	print("ICE STATUS REG: ");
	printHex(ice_read(ICE_DBG_STATUS_REG), 8);
	print("\n");
}


/**
 * Show dbg control register.
 */
void ice_print_dbg_control_reg() {
	print("ICE CONTROL REG: ");
	printHex(ice_read(ICE_DBG_CTL_REG), 8);
	print("\n");
}


/**
 * Show ice command line menu.
 */
void ice_print_menu() {
	print("\nICE commands ('0' to go up; ESC to exit):\n");
	print("  1 -> halt target\n");
	print("  2 -> print status reg\n");
	print("  3 -> print control reg\n");
	print("  4 -> print watch point 0 regs\n");
	print("  5 -> print watch point 1 regs\n");
}


/**
 * Implementation of the ice command line menu.
 */
void ice_cmd_run() {
	uint8_t input;

	while (1) {
		ice_print_menu();
		input = getchar();
		print("\n");

		switch (input) {
		case (48 + 0):
			return;
		case (48 + 1):
			print_div_line();
			ice_print_halt_target();
			print_div_line();
			break;
		case (48 + 2):
			print_div_line();
			ice_print_dbg_status_reg();
			print_div_line();
			break;
		case (48 + 3):
			print_div_line();
			ice_print_dbg_control_reg();
			print_div_line();
			break;
		case (48 + 4):
			print_div_line();
			ice_print_watchpoint0_regs();
			print_div_line();
			break;
		case (48 + 5):
			print_div_line();
			ice_print_watchpoint1_regs();
			print_div_line();
			break;
		default:
			printUnknownCmd(input);
			break;
		}
	}
}
