;/**
; * @file       IEC60335_B_CPUregTestBIST_gnu.asm
; * @purpose    IEC60335 Class B CPU register tests library
; * @version    v1.0
; * @date       6-aug-2009
; * @author     nlv15840
;*/
;/*----------------------------------------------------------------------------
; * Software that is described herein is for illustrative purposes only
; * which provides customers with programming information regarding the
; * products. This software is supplied "AS IS" without any warranties.
; * NXP Semiconductors assumes no responsibility or liability for the
; * use of the software, conveys no license or title under any patent,
; * copyright, or mask work right to the product. NXP Semiconductors
; * reserves the right to make changes in the software without
; * notification. NXP Semiconductors also make no representation or
; * warranty that such application will be suitable for the specified
; * use without further testing or modification.
; **********************************************************************/

.text

.syntax unified
.global _CPUregTestLOW
.global _CPUregTestMID
.global _CPUregTestHIGH
.global _CPUregTestSP
.global _CPUregTestSPEC


.type   _CPUregTestLOW, function
.type   _CPUregTestMID, function
.type   _CPUregTestHIGH, function
.type   _CPUregTestSP, function
.type   _CPUregTestSPEC, function

  .equ  testState       , 0
  .equ  testPassed      , 4

.equ pattern1, 0xAAAAAAAA
.equ pattern2, 0xAAAAAAA8
.equ pattern3, 0x55555555
.equ pattern4, 0x55555554
.equ pattern5, 0xA8000000
.equ pattern6, 0x50000000
.equ pattern7, 0x000000A8
.equ pattern8, 0x00000050
;/*.word pattern1, pattern2*/

#endif

;/**************************************/
;/* START of the CPU register test LOW */
;/**************************************/
.thumb
.thumb_func
_CPUregTestLOW:

;   /* Push ALL registers to stack */
    push    {r0-r12,r14}

;/*---- LOW REGISTERS r0-r7 --------------------
; *     First the low registers r0-r7 are tested
; */

;/* r0 register test:
; * Since r0 is the first register to be tested
; * and no other registers may be used, r0 should be tested
; * by only using immediate instructions.
; */
_cpu_low_test:

;	/* Since cmp can only compare with an immediate
;	 * 8-bit value, the bits to be tested needs to
;	 * be shifted to the LSB's.
;	 */
;	/* r0 - stuck at 0 test */
	movw	r0, #0x00AA
;	/* r0 - test r0[7:0] */
	cmp 	r0, #0xAA
	bne		_cpu_low_test_fail
;	/* r0 - test r0[15:8] */
	movw	r0, #0xAA00
	lsr		r0, r0, #8
	cmp 	r0, #0xAA
	bne		_cpu_low_test_fail
;	/* r0 - test r0[23:16] */
	movw	r0, #0x0000
	movt	r0, #0x00AA
	lsr		r0, r0, #16
	cmp 	r0, #0xAA
	bne		_cpu_low_test_fail
;	/* r0 - test r0[31:24] */
	movw	r0, #0x0000
	movt	r0, #0xAA00
	lsr		r0, r0, #24
	cmp 	r0, #0xAA
	bne		_cpu_low_test_fail

;	/* r0 - inverted pattern and
;	 * neighbour stuck test
;	 */
	movw	r0, #0x0055
;	/* r0 - test r0[7:0] */
	cmp 	r0, #0x55
	bne		_cpu_low_test_fail
;	/* r0 - test r0[15:8] */
	movw	r0, #0x5500
	lsr		r0, r0, #8
	cmp 	r0, #0x55
	bne		_cpu_low_test_fail
;	/* r0 - test r0[23:16] */
	movw	r0, #0x0000
	movt	r0, #0x0055
	lsr		r0, r0, #16
	cmp 	r0, #0x55
	bne		_cpu_low_test_fail
;	/* r0 - test r0[31:24] */
	movw	r0, #0x0000
	movt	r0, #0x5500
	lsr		r0, r0, #24
	cmp 	r0, #0x55
	bne		_cpu_low_test_fail

;   /*!! NOW r0 is known good !!*/

_cpu_r0_test_pass:
    b       _cpu_r1_r7_test

_cpu_r0_test_fail:
    b       _cpu_low_test_fail


;/* Register r1-r7 test:
; * The registers under test will be written with
; * pattern1 = 0xAAAA.AAAA. Each register will be individually
; * compared to r0 for a pass/fail for the test.
; * The second part of the test will write the inverted pattern
; * in the register under test and pass/fail with a cmp
; */
_cpu_r1_r7_test:

;	/* Load pattern1 in r0 */
	ldr		r0,=pattern1

;	/* Put patter1 in r1-r7 */
	mov		r1,r0
	cmp		r1,r0
	bne		_cpu_low_test_fail

	mov		r2,r0
	cmp		r2,r0
	bne		_cpu_low_test_fail

    mov		r3,r0
    cmp		r3,r0
    bne		_cpu_low_test_fail

	mov		r4,r0
	cmp		r4,r0
	bne		_cpu_low_test_fail

	mov		r5,r0
	cmp		r5,r0
	bne		_cpu_low_test_fail

	mov		r6,r0
	cmp		r6,r0
	bne		_cpu_low_test_fail

	mov		r7,r0
	cmp		r7,r0
	bne		_cpu_low_test_fail

;   /* Load pattern3 in r0 */
    ldr     r0,=pattern3

;   /* Put patter3 in r1-r7 */
    mov     r1,r0
    cmp     r1,r0
    bne     _cpu_low_test_fail

    mov     r2,r0
    cmp     r2,r0
    bne     _cpu_low_test_fail

    mov     r3,r0
    cmp     r3,r0
    bne     _cpu_low_test_fail

    mov     r4,r0
    cmp     r4,r0
    bne     _cpu_low_test_fail

    mov     r5,r0
    cmp     r5,r0
    bne     _cpu_low_test_fail

    mov     r6,r0
    cmp     r6,r0
    bne     _cpu_low_test_fail

    mov     r7,r0
    cmp     r7,r0
    bne     _cpu_low_test_fail

_cpu_low_test_pass:

;   /* Indicate in the CPUregTestBIST_struct
;    * that r0-r7 tests passed.
;    */
    ldr     r1, =CPUregTestBIST_struct

;   /* Indicate LOW test has passed */
    mov     r0, #0xFF
    ldr     r2, [r1]
    orr     r0, r0, r2
    str     r0, [r1,#testState]

;   /* Indicate the test has passed */
    mov     r0, #0x01
    str     r0, [r1,#testPassed]

_cpu_low_test_fail:
;   /* Pop the stack back */
    pop     {r0-r12,r14}
;   /* Branch back */
    bx      lr

;/**************************************/
;/* END of the CPU register test LOW   */
;/**************************************/

;/**************************************/
;/* START of the CPU register test MID */
;/**************************************/
.thumb_func
;/*--- HIGH REGISTERS r4-r10 ---*/
_CPUregTestMID:

;   /* Push ALL registers to stack */
    push    {r0-r12,r14}

;   /* Clear r0 */
    mov r0, #0x00

;   /* Load pattern1 in r0 */
    ldr     r0,=pattern1

;   /* Put patter1 in r4-r10 */
    mov     r4,r0
    cmp     r4,r0
    bne     _cpu_mid_test_fail

    mov     r5,r0
    cmp     r5,r0
    bne     _cpu_mid_test_fail

    mov     r6,r0
    cmp     r6,r0
    bne     _cpu_mid_test_fail

    mov     r7,r0
    cmp     r7,r0
    bne     _cpu_mid_test_fail

    mov     r8,r0
    cmp     r8,r0
    bne     _cpu_mid_test_fail

    mov     r9,r0
    cmp     r9,r0
    bne     _cpu_mid_test_fail

    mov     r10,r0
    cmp     r10,r0
    bne     _cpu_mid_test_fail

;   /* Load pattern3 in r0 */
    ldr     r0,=pattern3

;   /* Put patter1 in r4-r10 */
    mov     r4,r0
    cmp     r4,r0
    bne     _cpu_mid_test_fail

    mov     r5,r0
    cmp     r5,r0
    bne     _cpu_mid_test_fail

    mov     r6,r0
    cmp     r6,r0
    bne     _cpu_mid_test_fail

    mov     r7,r0
    cmp     r7,r0
    bne     _cpu_mid_test_fail

    mov     r8,r0
    cmp     r8,r0
    bne     _cpu_mid_test_fail

    mov     r9,r0
    cmp     r9,r0
    bne     _cpu_mid_test_fail

    mov     r10,r0
    cmp     r10,r0
    bne     _cpu_mid_test_fail

_cpu_mid_test_pass:

;   /* Indicate in the CPUregTestBIST_struct
;    * that r4-r10 tests passed.
;    */
    ldr     r1, =CPUregTestBIST_struct

;   /* Indicate MID test has passed */
    movw    r0, #0x7F0
    ldr     r2, [r1]
    orr     r0, r0, r2

    str     r0, [r1,#testState]

;   /* Indicate the test has passed */
    mov     r0, #0x01
    str     r0, [r1,#testPassed]

_cpu_mid_test_fail:
;   /* Pop the stack back */
    pop     {r0-r12,r14}
    bx      lr

;/**************************************/
;/* END of the CPU register test MID   */
;/**************************************/

;/**************************************/
;/* START of the CPU register test HIGH*/
;/**************************************/
.thumb_func
;/*--- HIGH REGISTERS r8-r12 ---*/
_CPUregTestHIGH:

;   /* Push ALL registers to stack */
    push    {r0-r12,r14}

;   /* Clear r0 */
    mov r0, #0x00

;   /* Load pattern1 in r0 */
    ldr     r0,=pattern1

;   /* Put patter1 in r8-r12 */
    mov     r8,r0
    cmp     r8,r0
    bne     _cpu_high_test_fail

    mov     r9,r0
    cmp     r9,r0
    bne     _cpu_high_test_fail

    mov     r10,r0
    cmp     r10,r0
    bne     _cpu_high_test_fail

    mov     r11,r0
    cmp     r11,r0
    bne     _cpu_high_test_fail

    mov     r12,r0
    cmp     r12,r0
    bne     _cpu_high_test_fail

;   /* Load pattern3 in r0 */
    ldr     r0,=pattern3

;   /* Put patter1 in r8-r12 */
    mov     r8,r0
    cmp     r8,r0
    bne     _cpu_high_test_fail

    mov     r9,r0
    cmp     r9,r0
    bne     _cpu_high_test_fail

    mov     r10,r0
    cmp     r10,r0
    bne     _cpu_high_test_fail

    mov     r11,r0
    cmp     r11,r0
    bne     _cpu_high_test_fail

    mov     r12,r0
    cmp     r12,r0
    bne     _cpu_high_test_fail

_cpu_high_test_pass:

;   /* Indicate in the CPUregTestBIST_struct
;    * that r0-r12 tests passed.
;    */
    ldr     r1, =CPUregTestBIST_struct

;   /* Indicate LOW test has passed */
    movw    r0, #0x1F00
    ldr     r2, [r1]
    orr     r0, r0, r2
    str     r0, [r1,#testState]

;   /* Indicate the test has passed */
    mov     r0, #0x01
    str     r0, [r1,#testPassed]

_cpu_high_test_fail:
;   /* Pop the stack back */
    pop     {r0-r12,r14}
;   /* Branch back */
    bx      lr

;/**************************************/
;/* END of the CPU register test HIGH  */
;/**************************************/

;/**************************************/
;/* START of the CPU register test SP  */
;/**************************************/
;/* MSP register tests:
; * The MSP consists of two tests, the first test the register
; * through reading/writing r13 using the normal instructions.
; * The second test test the register by using the MSR and MRS
; * special register read/write instructions.
; * For the MSP a different pattern is used because MSP[1:0] are
; * always zero.
; */
.thumb_func
_CPUregTestSP:

;   /* Disable all interrupts */
    mov     r0, #1
    msr     PRIMASK, r0

;   /* Push ALL registers to stack */
    push    {r0-r12,r14}

;   /* Store the current CONTROL value */
    mrs     r3, CONTROL

;   /* Select default stack (MSP) */
    mov     r6, #0x0
    msr     CONTROL, r6
    mrs     r4, CONTROL

;   /* Store the current MSP */
    mov     r4, r13

;   /* Check whether MSP is really selected */
    mrs     r5, MSP
    cmp     r4, r5
    bne     _cpu_MSP_test_fail

;   /* Load pattern1 in r0 */
    ldr     r0,=pattern2

;   /* Move pattern1 in the MSP */
    mov     r13, r0

;   /* Compare the pattern with the input pattern */
    cmp     r13, r0
    bne     _cpu_MSP_test_fail

;   /* Load pattern1 in r0 */
    ldr     r0,=pattern4

;   /* Move pattern1 in the MSP */
    mov     r13, r0

;   /* Compare the pattern with the input pattern */
    cmp     r13, r0
    bne     _cpu_MSP_test_fail

;   /* Load pattern1 in r0 */
    ldr     r0,=pattern2

;   /* Move pattern1 in the MSP */
    msr     MSP, r0

;   /* Copy MSP to r1, since MSP can't be directly cmp'ed */
    mrs     r1, MSP

;   /* Compare the pattern with the input pattern */
    cmp     r1, r0
    bne     _cpu_MSP_test_fail

;   /* Load pattern1 in r0 */
    ldr     r0,=pattern4

;   /* Move pattern1 in the MSP */
    msr     MSP, r0

;   /* Copy MSP to r1, since MSP can't be directly cmp'ed */
    mrs     r1, MSP

;   /* Compare the pattern with the input pattern */
    cmp     r1, r0
    bne     _cpu_MSP_test_fail

_cpu_MSP_test_pass:
;   /* Restore the MSP and CONTROL */
    mov     r13, r4
    msr     CONTROL, r6
;   /* Indicate in the CPUregTestBIST_struct
;    * that MSP tests passed.
;    */
    ldr     r1, =CPUregTestBIST_struct

;   /* Indicate LOW test has passed */
    movw    r0, #0x2000
    ldr     r2, [r1]
    orr     r0, r0, r2
    str     r0, [r1,#testState]

;   /* Indicate the test has passed */
    mov     r0, #0x01
    str     r0, [r1,#testPassed]

_cpu_MSP_test_fail:
;   /* Restore the MSP and CONTROL */
    mov     r13, r4
    msr     CONTROL, r6

;   /* Enable all interrupts */
    mov     r0, #0
    msr     PRIMASK, r0

;   /* Pop the stack back */
    pop     {r0-r12,r14}

;   /* Branch back */
    bx      lr
;/**************************************/
;/* END of the CPU register test SP    */
;/**************************************/

;/**************************************/
;/* START of the CPU register test SPEC*/
;/**************************************/
;/* LR register test:
; * The link register will be written with pattern1,
; * then compared for a pass/fail. Secondly the inverse
; * of the pattern will be tested.
; */
.thumb_func
_CPUregTestSPEC:

;   /* Push ALL registers to stack */
    push    {r0-r12,r14}

;   /* Store the current link register */
    mov     r3, r14

;   /* Load pattern1 in r0 */
    ldr     r0,=pattern1

;   /* Move pattern1 in the MSP */
    mov     r14, r0

;   /* Compare the pattern with the input pattern */
    cmp     r14, r0
    bne     _cpu_LR_test_fail

;   /* Load pattern1 in r0 */
    ldr     r0,=pattern3

;   /* Move pattern1 in the MSP */
    mov     r14, r0

;   /* Compare the pattern with the input pattern */
    cmp     r14, r0
    bne     _cpu_LR_test_fail

_cpu_LR_test_pass:
;   /* Restore the LR */
    mov     r14, r3

;   /* Indicate in the CPUregTestBIST_struct
;      LR test has passed
;    */
    movw    r0, #0x8000
    ldr     r1, =CPUregTestBIST_struct+testState
    ldr     r2, [r1]
    orr     r0, r0, r2
    str     r0, [r1]
    b       _cpu_APSR_test

_cpu_LR_test_fail:
;   /* Restore the LR */
    mov     r14, r3
    b       _cpu_APSR_test_fail

;/* APSR register tests:
; * Only the APSR register can be test, the other PSR registers,
; * IPSR and EPSR are read-only.
; * The APSR register will be written with pattern5, because only APSR[31:27]
; * are readable and writeable,
; * then compared for a pass/fail. Secondly the inverse
; * of the pattern will be tested.
; */
_cpu_APSR_test:

;   /* Store the current link register */
    mrs     r3, APSR

;   /* Load pattern1 in r0 */
    ldr     r0,=pattern5

;   /* Move pattern1 in the APSR */
    msr     APSR, r0

;   /* Read pattern1 from the APSR */
    mrs     r1, APSR

;   /* Compare the pattern with the input pattern */
    cmp     r1, r0
    bne     _cpu_APSR_test_fail

;   /* Load pattern1 in r0 */
    ldr     r0,=pattern6

;   /* Move pattern1 in the APSR */
    msr     APSR, r0

;   /* Read pattern1 from the APSR */
    mrs     r1, APSR

;   /* Compare the pattern with the input pattern */
    cmp     r1, r0
    bne     _cpu_APSR_test_fail

_cpu_APSR_test_pass:
;   /* Restore the APSR */
    msr     APSR, r3
;   /* Indicate in the CPUregTestBIST_struct
;      APSR test has passed
;    */
    movw    r0, #0x0000
    movt    r0, #0x0001
    ldr     r1, =CPUregTestBIST_struct+testState
    ldr     r2, [r1]
    orr     r0, r0, r2
    str     r0, [r1]
    b       _cpu_PRIMASK_test

_cpu_APSR_test_fail:
;   /* Restore the APSR */
    msr     APSR, r3
    b       _cpu_PRIMASK_test_fail


;/* PRIMASK register tests:
; * The PRIMASK bit will be tested to 0 and 1.
; */
_cpu_PRIMASK_test:

;   /* Store the current link register */
    mrs     r3, PRIMASK

;   /* Load pattern1 in r0 */
    mov     r0, #0

;   /* Move pattern1 in the PRIMASK */
    msr     PRIMASK, r0

;   /* Read pattern1 from the PRIMASK */
    mrs     r1, PRIMASK

;   /* Compare the pattern with the input pattern */
    cmp     r1, r0
    bne     _cpu_PRIMASK_test_fail

;   /* Load pattern1 in r0 */
    mov     r0, #1

;   /* Move pattern1 in the PRIMASK */
    msr     PRIMASK, r0

;   /* Read pattern1 from the PRIMASK */
    mrs     r1, PRIMASK

;   /* Compare the pattern with the input pattern */
    cmp     r1, r0
    bne     _cpu_PRIMASK_test_fail

_cpu_PRIMASK_test_pass:
;   /* Restore the PRIMASK */
    msr     PRIMASK, r3
;   /* Indicate in the CPUregTestBIST_struct
;      PRIMASK test has passed
;    */
    movw    r0, #0x0000
    movt    r0, #0x0002
    ldr     r1, =CPUregTestBIST_struct+testState
    ldr     r2, [r1]
    orr     r0, r0, r2
    str     r0, [r1]
    b       _cpu_FAULTMASK_test

_cpu_PRIMASK_test_fail:
;   /* Restore the PRIMASK */
    msr     PRIMASK, r3
    b       _cpu_FAULTMASK_test_fail

;/* FAULTMASK register tests:
; * The FAULTMASK bit will be tested to 0 and 1.
; */
_cpu_FAULTMASK_test:

;   /* Store the current link register */
    mrs     r3, FAULTMASK

;   /* Load pattern in r0 */
    mov     r0, #0

;   /* Move pattern in the FAULTMASK */
    msr     FAULTMASK, r0

;   /* Read pattern from the FAULTMASK */
    mrs     r1, FAULTMASK

;   /* Compare the pattern with the input pattern */
    cmp     r1, r0
    bne     _cpu_FAULTMASK_test_fail

;   /* Load pattern in r0 */
    mov     r0, #1

;   /* Move pattern in the FAULTMASK */
    msr     FAULTMASK, r0

;   /* Read pattern from the FAULTMASK */
    mrs     r1, FAULTMASK

;   /* Compare the pattern with the input pattern */
    cmp     r1, r0
    bne     _cpu_FAULTMASK_test_fail

_cpu_FAULTMASK_test_pass:
;   /* Restore the FAULTMASK */
    msr     FAULTMASK, r3

;   /* Indicate in the CPUregTestBIST_struct
;      FAULTMASK test has passed
;    */
    movw    r0, #0x0000
    movt    r0, #0x0004
    ldr     r1, =CPUregTestBIST_struct+testState
    ldr     r2, [r1]
    orr     r0, r0, r2
    str     r0, [r1]
    b       _cpu_BASEPRI_test

_cpu_FAULTMASK_test_fail:
;   /* Restore the FAULTMASK */
    msr     FAULTMASK, r3
    b       _cpu_BASEPRI_test_fail

;/* BASEPRI register tests:
; * The BASEPRI bit will be tested to 0 and 1.
; */
_cpu_BASEPRI_test:

;   /* Store the current link register */
    mrs     r3, BASEPRI

;   /* Load pattern1 in r0 */
    ldr     r0, =pattern7

;   /* Move pattern1 in the BASEPRI */
    msr     BASEPRI, r0

;   /* Read pattern1 from the BASEPRI */
    mrs     r1, BASEPRI

;   /* Compare the pattern with the input pattern */
    cmp     r1, r0
    bne     _cpu_BASEPRI_test_fail

;   /* Load pattern1 in r0 */
    ldr     r0, =pattern8

;   /* Move pattern1 in the BASEPRI */
    msr     BASEPRI, r0

;   /* Read pattern1 from the BASEPRI */
    mrs     r1, BASEPRI

;   /* Compare the pattern with the input pattern */
    cmp     r1, r0
    bne     _cpu_BASEPRI_test_fail

_cpu_BASEPRI_test_pass:
;   /* Restore the BASEPRI */
    msr     BASEPRI, r3

;   /* Indicate in the CPUregTestBIST_struct
;      BASEPRI test has passed
;    */
    movw    r0, #0x0000
    movt    r0, #0x0008
    ldr     r1, =CPUregTestBIST_struct+testState
    ldr     r2, [r1]
    orr     r0, r0, r2
    str     r0, [r1]

;   /* Indicate the test has passed */
    mov     r0, #0x01
    str     r0, [r1,testPassed]


_cpu_BASEPRI_test_fail:
;   /* Restore the BASEPRI */
    msr     BASEPRI, r3

;   /* Pop the stack back */
    pop     {r0-r12,r14}

;   /* Branch back */
    bx      lr
;/**************************************/
;/* END of the CPU register test SPEC  */
;/**************************************/
.end

