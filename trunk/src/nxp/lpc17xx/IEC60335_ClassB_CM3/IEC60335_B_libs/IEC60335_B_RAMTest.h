/**
 * @file	IEC60335_B_RAMTest.h
 * @purpose
 * @brief
 * @version	1.0
 * @date	31-aug-2009
 * @author	nlv15840
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

#ifndef IEC60335_B_RAMTEST_H_
#define IEC60335_B_RAMTEST_H_


#define IEC60335_RAM_START 	(0x10000000UL)
#define IEC60335_RAM_SIZE   0x1000
#define	PATTERN				0x55555555

/**
 *
 */
extern type_testResult IEC60335_RAMtest (UINT32 startAddrs, UINT32 length);

/**
 *
 */
extern type_testResult IEC60335_RAMtest_POST(void);

/**
 *
 */
extern type_testResult IEC60335_RAMtest_BIST (UINT32 startAddrs, UINT32 length);


#endif /* IEC60335_B_RAMTEST_H_ */
