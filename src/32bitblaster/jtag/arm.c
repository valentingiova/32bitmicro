/**
 * arm jtag implementation.
 */

/* global variables to save/restore the execution context */
uint32_t saved_regs[16];

#define PC 15

#define SPEED_SYS 1
#define SPEED_DBG 0

#define NOP 0xE1A00000 // MOV R0,R0


/**
 * Read register reg_num.
 * Returns the content of the register.
 */
uint32_t arm_read_reg(uint32_t reg_num) {
	/* Change chain to arm chain. */
	jtag_change_chain(0x1);
	ir_scan(4, JTAG_OP_INTEST);

	/* we start with 0xE58E0000, which is STR [R0], [R14] */
	uint32_t instr = 0xE58E0000;

	/* bits 12-15 are holding the register of interest number */
	instr |= ((reg_num << 12) & 0x0000f000);

	/* push STR R[reg_num], R14 into fetch stage of the pipeline */
	dr_scan_chain_1(instr, SPEED_DBG);
	/* pushing STR op into decode stage */
	dr_scan_chain_1(NOP, SPEED_DBG);
	/* pushing STR op into execute stage */
	dr_scan_chain_1(NOP, SPEED_DBG);

	/* make the execution happen, and read the data */
	return dr_scan_chain_1(NOP, SPEED_DBG);
}


/**
 * Write data into register reg_num.
 */
void arm_write_reg(uint32_t reg_num, uint32_t data) {
	/* Change chain to arm chain. */
	jtag_change_chain(0x1);
	ir_scan(4, JTAG_OP_INTEST);

	/* we start with 0xE58E0000, which is LDR [R0], [R14] */
	uint32_t instr = 0xE59E0000;

	/* bits 12-15 are holding the register of interest number */
	instr |= ((reg_num << 12) & 0x0000f000);

	/* push LDR R[reg_num], R14 into fetch stage of the pipeline */
	dr_scan_chain_1(instr, SPEED_DBG);
	/* pushing STR op into decode stage */
	dr_scan_chain_1(NOP, SPEED_DBG);
	/* pushing STR op into execute stage */
	dr_scan_chain_1(NOP, SPEED_DBG);
	/* put our data on the bus */
	dr_scan_chain_1(data, SPEED_DBG);
	/* make the execution happen, after this one the data should be written */
	dr_scan_chain_1(NOP, SPEED_DBG);

	/* In case the register we are writing into is PC we need additional 2 NOPs */
	if (reg_num == PC) {
		dr_scan_chain_1(NOP, SPEED_DBG);
		dr_scan_chain_1(NOP, SPEED_DBG);
	}
}


uint32_t ice_wait_for_dbg_ack();
void ice_set_breakpoint();
void ice_clear_breakpoint();

/**
 * Read the memory from address addr.
 * Returns the memory content at address addr.
 */
uint32_t arm_read_mem(uint32_t addr) {
	/* write the address into R0 */
	arm_write_reg(0, addr - 0xA0);

	/* Change chain to arm chain. */
	jtag_change_chain(0x1);
	ir_scan(4, JTAG_OP_INTEST);

	/* Next op will be executed at system speed */
	dr_scan_chain_1(NOP, SPEED_SYS);

	/* LDMIA R0, {R1-R7} (load multiple memory) */
	dr_scan_chain_1(0xE8B000FE, SPEED_DBG);

	/* NOP to advance the LDMIA in the pipeline */
	dr_scan_chain_1(NOP, SPEED_DBG);

	/* Make it happen */
	jtag_send_restart();

	/* Stop the core */
	ice_set_breakpoint();

	/* Wait for the cpu to return to debug mode */
	ice_wait_for_dbg_ack();

	/* Remove the breakpoints */
	ice_clear_breakpoint();

	return arm_read_reg(5);
}


/**
 * Save the content of the registers, to restore them later.
 */
void arm_save_context() {
	int i = 0;
	/* save the PC. A read instruction is needed also. */
	arm_read_reg(0);
	saved_regs[PC] = arm_read_reg(PC);

	/* it takes 4 instructions to read the register, each instruction is 4 byte */
	/* in addition the PC is 2 instructions away from the instruction been executed */
	saved_regs[PC] -= (0xA << 2);

	/* save all the other registers */
	for (i = 0; i < PC; i++) {
		saved_regs[i] = arm_read_reg(i);
	}
}


/**
 * Restore the content of the registers.
 */
void arm_restore_context() {
	int i = 0;
	/* load all the registers except the PC */
	for (i = 0; i < PC; i++) {
		arm_write_reg(i, saved_regs[i]);
	}

	/* load PC */
	arm_write_reg(PC, saved_regs[PC]);
}


/**
 * Restore the context and go back to the old PC.
 */
void arm_resume_target() {
	arm_restore_context();

	/* Change chain to arm chain. */
	jtag_change_chain(0x1);
	ir_scan(4, JTAG_OP_INTEST);

	/* The next instruction will be executed at system speed. */
	dr_scan_chain_1(NOP, SPEED_SYS);

	/* push branch to the old PC */
	uint32_t instr = 0xEA000000 | (-11 & 0x00ffffff);

	dr_scan_chain_1(instr, SPEED_DBG);

	/* Advance the instruction in the pipeline. */
	dr_scan_chain_1(NOP, SPEED_DBG);

	/* Make this happen. */
	jtag_send_restart();
}


/**
 * Read spsr or cpsr according the the flag spsr.
 * Returns the content of spsr or cpsr.
 */
uint32_t arm_read_xpsr(uint32_t spsr) {
	/* Save r0 to restore it later */
	uint32_t saved_r0 = arm_read_reg(0);

	/* Change chain to arm chain. */
	jtag_change_chain(0x1);
	ir_scan(4, JTAG_OP_INTEST);

	if (spsr)
		dr_scan_chain_1(0xe1200000, SPEED_DBG); // MRS R0, SPSR
	else
		dr_scan_chain_1(0xe1000000, SPEED_DBG); // MRS R0, CPSR

	/* Advance the instruction in the pipeline until execution. */
	dr_scan_chain_1(NOP, SPEED_DBG);
	dr_scan_chain_1(NOP, SPEED_DBG);

	/* Get the result of the instruction. */
	uint32_t ret = arm_read_reg(0);

	/* Restore register 0. */
	arm_write_reg(0, saved_r0);

	return ret;
}
