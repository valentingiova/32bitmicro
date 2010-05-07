/**
 * arm jtag command line interface.
 */

#include "arm.c"


/**
 * Dump the registers content and the instructions in the PC area.
 */
void core_info() {
	int i = 0;
	/* Dump PC */
	print("PC: "); printHex(saved_regs[PC], 8); print("\n\n");

	/* Dump all other registers. */
	uint32_t val;
	for (i = 0; i < 16; i++) {
		val = arm_read_reg(i);
		print("R"); printNum(i); print(": ");
		printHex(val, 8); print("\n");
	}

	/* Dump the instruction near the PC (and includes). */
	print("\nCODE: ");
	arm_read_mem(saved_regs[PC]);
	for (i = -3; i < 4; i++) {
		if (i) {
			printHex(arm_read_mem(saved_regs[PC] + (i * 4)), 8); print(" ");
		} else {
			print("<"); printHex(arm_read_mem(saved_regs[PC] + (i * 4)), 8); print("> ");
		}
	}
	print("\n");
}


/**
 * Write magic number to r0 and read it back.
 */
void core_print_test_write_register() {
	print("Writing 0xdeadbeef into R0\n");
	print("R0 old val: ");
	printHex(arm_read_reg(0), 8); print("\n");
	arm_write_reg(0, 0xdeadbeef);
	print("R0 new val: ");
	printHex(arm_read_reg(0), 8); print("\n");
}


/**
 * Resume the target.
 */
void core_print_resume_target() {
	print("Resuming target using PC: ");
	printHex(saved_regs[PC], 8); print("\n");

	arm_resume_target();
	print("done.\n");
}


/**
 * Print the saved registers (as they were when we stopped the core).
 */
void core_print_saved_registers() {
	int i = 0;
	print("Saved registers:\n");
	for (i = 0; i < 16; i++) {
		print("R"); printNum(i); print(": ");
		printHex(saved_regs[i], 8); print("\n");
	}
}


/**
 * Print cpsr.
 */
void core_print_cpsr() {
	uint32_t cpsr = arm_read_xpsr(0);
	print("CPSR: "); printHex(cpsr, 8); print("\n");

	print("Condition flags: [NZCV]\n");
	if (cpsr & 0x80000000)
		print("  [N] Neg. or Less than\n");
	if (cpsr & 0x40000000)
		print("  [Z] Zero\n");
	if (cpsr & 0x20000000)
		print("  [C] Carry or Borrow or Extend\n");
	if (cpsr & 0x10000000)
		print("  [V] Overflow\n");

	print("IRQ: "); (cpsr & 0x80) ? print("disabled\n"): print("enabled\n");
	print("FIQ: "); (cpsr & 0x40) ? print("disabled\n"): print("enabled\n");
	print("State: "); (cpsr & 0x20) ? print("Thumb\n") : print("ARM\n");

	print("Mode: ");
	switch (cpsr & 0x1f) {
	case 0x10:
		print("User\n");
		break;
	case 0x11:
		print("FIQ\n");
		break;
	case 0x12:
		print("IRQ\n");
		break;
	case 0x13:
		print("Supervisor\n");
		break;
	case 0x17:
		print("Abort\n");
		break;
	case 0x1b:
		print("Undefined\n");
		break;
	case 0x1f:
		print("System\n");
		break;
	default:
		print("Illegal - unrecoverable state\n");
	}
}


/**
 * The arm command line menu.
 */
void core_print_menu() {
	print("\nARM CORE commands ('0' to go up; ESC to exit):\n");
	print("  1 -> core info\n");
	print("  2 -> test write register\n");
	print("  3 -> resume target\n");
	print("  4 -> show saved registers\n");
	print("  5 -> print CPSR\n");
}


/**
 * Implementation of the arm command line menu.
 */
void core_cmd_run() {
	uint8_t input;

	while (1) {
		core_print_menu();
		input = getchar();
		print("\n");

		switch (input) {
		case (48 + 0):
			return;
		case (48 + 1):
			print_div_line();
			core_info();
			print_div_line();
			break;
		case (48 + 2):
			print_div_line();
			core_print_test_write_register();
			print_div_line();
			break;
		case (48 + 3):
			print_div_line();
			core_print_resume_target();
			print_div_line();
			break;
		case (48 + 4):
			print_div_line();
			core_print_saved_registers();
			print_div_line();
			break;
		case (48 + 5):
			print_div_line();
			core_print_cpsr();
			print_div_line();
			break;
		default:
			printUnknownCmd(input);
			break;
		}
	}
}
