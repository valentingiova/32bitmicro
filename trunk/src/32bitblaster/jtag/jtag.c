/**
 * jtag implementation.
 */

#define TCK BIT4 // p0.4
#define TDO BIT5 // p0.5
#define TDI BIT6 // p0.6
#define TMS BIT28 // p0.28
#define VREF BIT29 // p0.29

#define PIN_DIR_OUT 1
#define PIN_DIR_IN 0

#define ADC_DONE	0x80000000
#define ADC_OVERRUN	0x40000000

#define set_pin_dir(pin, dir) \
	do { \
		IODIR0 = (dir) ? IODIR0 | (pin) : IODIR0 & ~(pin); \
	} while (0)

#define set_pin(pin, val) \
	do { \
		IOPIN0 = (val) ? IOPIN0 | (pin) : IOPIN0 & ~(pin); \
	} while (0)

#define get_pin(pin) (!!(IOPIN0 & (pin)))

/**
 * IDCODE instruction.
 * After this OP updated in IR we can shift out 32 bit id code from DR.
 */
#define JTAG_OP_IDCODE 0xe // (1110)

/**
 * SCAN_N selects scan chain that we are willing to work with.
 * after this OP updated in IR we shift in DR chain number (4 bits).
 */
#define JTAG_OP_SCAN_N 0x2 // (0010)

/* After the chain was selected by the SCAN_N OP this OP is used to
 * perform a test on the registers of the selected chain.
 * after this OP updated in IR we use DR (TDI) to shift in data and TDO to
 * get data out of the registers in the chain.
 */
#define JTAG_OP_INTEST 0xc // (1100) after the chain was selected this cmd puts it into test

/* this OP connects 1 bit register between the TDI and TDO */
#define JTAG_OP_BYPASS 0xf // (1111)

/* used to restart the CPU on exit from debug mode */
#define JTAG_OP_RESTART 0x4 // (0100)


/**
 * Initialize vref.
 */
void config_vref_pin(void) {
	/* set p.029 to AD0.2 function. */
	PINSEL1 &= ~(BIT26 | BIT27);
	PINSEL1 |= BIT26;

	/* power on the ADC0. */
	PCONP |= BIT12;

	/* configure ADC0 channel. */
	AD0CR |= ((0x01 << 2)   // SEL:  channel 1
			|(0x02 << 8)    // main clock / (CLKDIV - 1)
			|(0x01 << 21)); // PDN - converter enabled
}


/**
 * Read vref.
 */
uint32_t read_vref(void) {
	uint32_t adc_val;

	/* start AD conversion. */
	AD0CR |= (0x1 << 24);

	/* wait for the conversion to finish. */
	while (1) {
		/* read the AD data register. */
		adc_val = AD0DR2;

		if (adc_val & ADC_OVERRUN)
			continue;

		if (adc_val & ADC_DONE)
			break;
	}

	/* stop AD conversion. */
	AD0CR &= ~(0x7 << 24);

	/* Shift and mask the data. */
	return (adc_val >> 6) & 0x3ff;
}


/**
 * Wait for a target to be connected to the debugger.
 */
uint32_t jtag_target_sense(void) {
	uint32_t vref_res;

	config_vref_pin();

	while (100000) {
		vref_res = read_vref();
		print("Target sensing report: ");
		printNum(vref_res);
		print("\n");

		/* 512 -> 3.3V/2 | 930 -> 6V/2 */
		if (vref_res > 500 && vref_res < 940) {
			print("target is found ...\n");
			return 0;
		}
	}

	print("no target found, sorry :-(\n");
	return 1;
}


/**
 * Utility to reverse bits in data.
 */
uint32_t bits_reverse(uint32_t data) {
	uint32_t res = 0;
	int i = 0;
	for (i = 0; i < 32; i++)
		res = (res | ((data & (0x1 << i)) ? (0x80000000 >> i) : 0));

	return res;
}


/**
 * Make one jtag clock pulse.
 */
void pulse_clk() {
	set_pin(TCK, 0);
	set_pin(TCK, 1);
}


/**
 * Send and receive one jtag bit.
 */
uint32_t jtag_io(uint32_t tms, uint32_t tdi) {
	set_pin(TMS, tms);
	set_pin(TDI, tdi);

	pulse_clk();

	return get_pin(TDO);
}


/**
 * Send and receive 32 jtag bits.
 */
uint32_t jtag_io_32(uint32_t nof_bits, uint32_t tms_buf, uint32_t tdi_buf) {
	uint32_t tdo_buf = 0;
	int i = 0;

	if (nof_bits <= 0 || nof_bits > 32) {
		print("expected (0 < nof_bits <= 32), but you gave me: ");
		printNum(nof_bits);
		while (1);
	}

	for (i = 0; i < nof_bits; i++) {
		/* set the next bits for tms and tdi input (LSB first) */
		set_pin(TMS, tms_buf & 0x1);
		set_pin(TDI, tdi_buf & 0x1);

		/* get ready for the next cycle */
		tms_buf >>= 0x1;
		tdi_buf >>= 0x1;

		/* on rising edge TMS and TDI are in and on the falling TDO is out */
		pulse_clk();

		/* get the output (LSB first)*/
		tdo_buf |= (get_pin(TDO) << i);
	}

	return tdo_buf;
}


/**
 * Move to next jtag state.
 */
void inline next_state(uint32_t tms) {
	jtag_io(tms, 0);
}


/**
 * Reset jtag state.
 */
void jtag_reset() {
	/* TMS=1 for 5 clocks (brings the transition diagram to test logic reset) */
	jtag_io_32(5, 0x1f, 0);
  
	/* TMS=0 for 1 clock (brings the transition diagram to run test / idle) */
	next_state(0);
}


/**
 * Wait for a target and initialize jtag.
 */
uint32_t jtag_init() {
	/* before we drive the pins we want to sense target's VREF */
	if (jtag_target_sense()) {
		print("init failed!\n");
		return 1;
	}

	/* we use GPIO pins, so need to configure them correctly. */
	set_pin_dir(TCK, PIN_DIR_OUT);
	set_pin_dir(TMS, PIN_DIR_OUT);
	set_pin_dir(TDI, PIN_DIR_OUT);
	set_pin_dir(TDO, PIN_DIR_IN);

	/* Set all outputs. */
	set_pin(TCK, 1);
	set_pin(TMS, 0);
	set_pin(TDI, 0);

	/* reset transition states. */
	jtag_reset();

	return 0;
}


/**
 * Shift jtag instruction.
 */
uint32_t ir_scan(uint32_t nof_bits, uint32_t tdi_buf) {
	/* goto shift-IR state. */
	next_state(1); // goto select-DR-scan
	next_state(1); // goto select-IR-scan
	next_state(0); // goto capture-IR
	next_state(0); // goto shift-IR

	/* shift the data in. */
	/* on the last bit we traverse to the exit1_ir state. */
	jtag_io_32(nof_bits, 0x1 << (nof_bits - 1), tdi_buf);

	next_state(1); // goto update-IR
	next_state(0); // goto run_test/idle

	return 0;
}


/**
 * Shift jtag data register.
 */
uint32_t dr_scan(uint32_t nof_bits, uint32_t tdi_buf) {
	/* goto shift-DR state. */
	next_state(1); // goto select-DR-scan
	next_state(0); // goto capture_DR
	next_state(0); // goto shift-DR

	/* on the last bit we traverse to the exit1_ir state. */
	uint32_t res = jtag_io_32(nof_bits, 0x1 << (nof_bits - 1), tdi_buf);

	next_state(1); // goto update-DR
	next_state(0); // goto run_test/idle

	return res;
}


/**
 * Shift data on chain 1.
 */
uint32_t dr_scan_chain_1(uint32_t data, uint32_t dbg_break) {
	/* goto shift-DR state. */
	next_state(1); // goto select-DR-scan
	next_state(0); // goto capture_DR
	next_state(0); // goto shift-DR

	jtag_io(0, dbg_break);

	/* on the last bit we traverse to the exit1_ir state. */
	uint32_t res = jtag_io_32(32, 0x80000000, bits_reverse(data));

	next_state(1); // goto update-DR
	next_state(0); // goto run_test/idle

	return bits_reverse(res);
}


/**
 * Shift data on chain 2.
 */
void dr_scan_chain_2(uint32_t data, uint32_t reg_addr, uint32_t write) {
	/* goto shift-DR state. */
	next_state(1); // goto select-DR-scan
	next_state(0); // goto capture_DR
	next_state(0); // goto shift-DR

	if (write) {
		/* Shift the data in. */
		jtag_io_32(32, 0, data);
	}

	/* ICE reg address. */
	jtag_io_32(5, 0, reg_addr);

	/* read/write flag. */
	jtag_io(1, write);

	next_state(1); // goto update-DR
	next_state(0); // goto run_test/idle
}


/**
 * Get the target's idcode.
 */
uint32_t jtag_getIdCode(void) {
	ir_scan(4, JTAG_OP_IDCODE);
	return dr_scan(32, 0x0);
}


/**
 * Test jtag bypass.
 */
uint32_t jtag_test_bypass(void) {
	ir_scan(4, JTAG_OP_BYPASS);
	return dr_scan(32, 0xdeadbeef);
}


/**
 * Change jtag chain to chain.
 */
uint32_t jtag_change_chain(uint32_t chain) {
	ir_scan(4, JTAG_OP_SCAN_N);
	return dr_scan(4, chain);
}


/**
 * Restart jtag.
 */
uint32_t jtag_send_restart() {
	ir_scan(4, JTAG_OP_RESTART);
	return dr_scan(32, 0xbabecafe);
}
