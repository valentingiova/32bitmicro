/**
 * @file	IEC60335.h
 * @purpose
 * @brief
 * @version 1.0
 * @date	10-sep-2009
 * @author	applhi
*/
/*----------------------------------------------------------------------------
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **********************************************************************/

#ifndef __IEC60335_
#define __IEC60335_

typedef enum tag_testResult
{
	IEC60335_testFailed = 0,
	IEC60335_testPassed = 1
} type_testResult;

#include "IEC60335_typedefs.h"

#include "IEC60335_B_SecureDataStorage.h"
#include "IEC60335_B_Interrupts.h"
#include "IEC60335_B_ProgramCounterTest.h"
#include "IEC60335_B_RAMTest.h"
#include "IEC60335_B_FLASHTest.h"
#include "IEC60335_B_ClockTest.h"
#include "IEC60335_B_CPUregTests.h"
/* added for coverage tests with TESSY */
#ifdef TESSY
	#include "Tessy.h"
#endif

/*	User configuration	*/

#define CPU_CLK				4000000
#define FLASH_SIZE 			0x0007FFFF

#define FLASH_CRC_ADDR		(FLASH_SIZE-0xF)
#define	ENTRY_FLASH_CRC		{0x63B29505,0x4584156C,0x6C35D996,0x59921E02}

/*	End of user configuration */

#endif
