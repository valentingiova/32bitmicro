/**
 * ice jtag implementation.
 */

#define ICE_DBG_CTL_REG 0x00
#define ICE_DBG_STATUS_REG 0x01

#define ICE_WATCH_0_ADDRESS 0x08
#define ICE_WATCH_0_ADDRESS_MASK 0x09
#define ICE_WATCH_0_DATA 0x0a
#define ICE_WATCH_0_DATA_MASK 0x0b
#define ICE_WATCH_0_CONTROL 0x0c
#define ICE_WATCH_0_CONTROL_MASK 0x0d

#define ICE_WATCH_1_ADDRESS 0x10
#define ICE_WATCH_1_ADDRESS_MASK 0x11
#define ICE_WATCH_1_DATA 0x12
#define ICE_WATCH_1_DATA_MASK 0x13
#define ICE_WATCH_1_CONTROL 0x14
#define ICE_WATCH_1_CONTROL_MASK 0x15

#define ICE_DBGACK BIT0
#define ICE_MEM_READY BIT3
#define ICE_DBGRQ BIT1
#define ICE_INTDIS BIT2


/**
 * Write data to the ice register reg_addr.
 */
void ice_write(uint32_t data, uint32_t reg_addr) {
	/* Change jtag chain to ice. */
	jtag_change_chain(0x2);
	ir_scan(4, JTAG_OP_INTEST);

	/* Send reg_addr and data to the jtag bus. */
	dr_scan_chain_2(data, reg_addr, 1);
}


/*
 * Read and return the content of the ice register reg_addr.
 */
uint32_t ice_read(uint32_t reg_addr) {
	/* Change jtag chain to ice. */
	jtag_change_chain(0x2);
	ir_scan(4, JTAG_OP_INTEST);

	/* Send reg_addr to the jtag bus. */
	dr_scan_chain_2(0x0, reg_addr, 0);

	/* Shift out the data. */
	return dr_scan(32, 0x0);
}


/**
 * Wait for the core to enter to debug state.
 */
uint32_t ice_wait_for_dbg_ack() {
	int i = 0;
	/* Wait for the ice debug status register to signal ack. */
	for (i = 0; i < 1000; i++) {
		if ((ice_read(ICE_DBG_STATUS_REG) & (ICE_DBGACK)) == (ICE_DBGACK)) {
			return 0;
		}
		busywait(1000);
	}

	/* In case of time out, show the ice debug status register content. */
	print("WARNING: DBG ACK timeout is reached\n");
	print("ICE STATUS REG: "); printHex(ice_read(ICE_DBG_STATUS_REG), 8); print("\n");
	return 1;
}


/**
 * Set breakpoints on all instructions and data transaction.
 */
void ice_set_breakpoint() {
	ice_write(0x000000F0, ICE_WATCH_0_CONTROL);

	ice_write(0x0, ICE_WATCH_0_ADDRESS);
	ice_write(0xffffffff, ICE_WATCH_0_ADDRESS_MASK);
	ice_write(0x0, ICE_WATCH_0_DATA);
	ice_write(0xffffffff, ICE_WATCH_0_DATA_MASK);
	ice_write(0x000001F0, ICE_WATCH_0_CONTROL);
	ice_write(0xfffffff7, ICE_WATCH_0_CONTROL_MASK);
}


/**
 * Clear all breakpoints.
 */
void ice_clear_breakpoint() {
	ice_write(0x000000F0, ICE_WATCH_0_CONTROL);
}


/**
 * Halt the core.
 */
void ice_halt() {
	ice_set_breakpoint();

	ice_wait_for_dbg_ack();

	ice_clear_breakpoint();

	jtag_reset();
}
