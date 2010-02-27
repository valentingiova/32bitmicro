/******************************************************************************
 * @file:    IEC60335_B_CPUregs.c
 * @purpose: IEC60335 Class B CPU register tests, both POST and BIST
 * @version: 1.00
 * @date:    22. May 2009
 *----------------------------------------------------------------------------
 *
 ******************************************************************************/

#include <stdint.h>
#include "IEC60335_B_CPUregTests.h"


IEC60335_CPUreg_struct CPUregTestPOST_struct;
IEC60335_CPUreg_struct CPUregTestBIST_struct;

type_testResult IEC60335_CPUregTest_POST (void)
{
	_CPUregTestPOST();
	if (CPUregTestPOST_struct.testPassed != IEC60335_testPassed) return (IEC60335_testFailed);

	return IEC60335_testPassed;
}

type_testResult IEC60335_CPUregTest_BIST (void)
{

	/* Clear the current test states */
	CPUregTestBIST_struct.testState = 0;
	CPUregTestBIST_struct.testPassed = 0;

	/* Test the low registers r0-r7 */
	 _CPUregTestLOW(); 
	 if (CPUregTestBIST_struct.testPassed != IEC60335_testPassed) return (IEC60335_testFailed); 

	/* Clear the PASS bit */
	CPUregTestBIST_struct.testPassed = 0;

	/* Test the mid registers r4-r10 */
	_CPUregTestMID();
	if (CPUregTestBIST_struct.testPassed != IEC60335_testPassed) return (IEC60335_testFailed);

	/* Clear the PASS bit */
	CPUregTestBIST_struct.testPassed = 0;

	/* Test the high registers r8-r12 */
	_CPUregTestHIGH();
	if (CPUregTestBIST_struct.testPassed != IEC60335_testPassed) return (IEC60335_testFailed);

	/* Clear the PASS bit */
	CPUregTestBIST_struct.testPassed = 0;

	/* Test the stack pointer registers
	 * NOTE: DISABLES ALL INTERRUPTS!
	 */
	_CPUregTestSP();
	if (CPUregTestBIST_struct.testPassed != IEC60335_testPassed) return (IEC60335_testFailed);

	/* Clear the PASS bit */
	CPUregTestBIST_struct.testPassed = 0;

	/* Test the Special registers */
	_CPUregTestSPEC();
	if (CPUregTestBIST_struct.testPassed != IEC60335_testPassed) return (IEC60335_testFailed);

	/* Indicate all tests passed */
	CPUregTestBIST_struct.testPassed = 0x01;

	return (IEC60335_testPassed);
}


