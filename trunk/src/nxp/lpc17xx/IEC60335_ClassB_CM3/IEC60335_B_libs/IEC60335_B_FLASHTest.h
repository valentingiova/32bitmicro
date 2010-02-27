/**
 * @file	IEC60335_B_FLASHtest.h
 * @purpose
 * @brief
 * @version	1.0
 * @date	10-sep-2009
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

#ifndef IEC60335_B_FLASHTEST_H_
#define IEC60335_B_FLASHTEST_H_

#define SIZE32K			0x00007FFF
#define SIZE64K			0x0000FFFF
#define SIZE128K		0x0001FFFF
#define SIZE256K		0x0003FFFF
#define SIZE512K		0x0007FFFF

#define	FLASH_HARD_SIGN 1
#define FLASH_SOFT_SIGN	2

#define MISR_START	(1<<17)
#define EOM			(0x01<<2)	/* Signature Generation */


typedef struct IEC60335_FlashSign_struct {
	UINT32 word0;
	UINT32 word1;
	UINT32 word2;
	UINT32 word3;
} FlashSign_t;//, *pFlashSign_t;

/**
 *
 */
void StartHardSignatureGen (UINT32 startAddr, UINT32 length, FlashSign_t *ResultSign);

/**
 *
 */
void StartSoftSignatureGen (UINT32 startAddr, UINT32 length, FlashSign_t *pResultSign);

/**
 *
 */
type_testResult IEC60335_FLASHtest_BIST (UINT32 startAddr,
										 UINT32 length,
										 FlashSign_t *TestSign,
										 UINT8 	selectHS);

/**
 *
 */
type_testResult IEC60335_FLASHtest_POST (UINT32 size);

/**
 *
 */
type_testResult IEC60335_testSignatures (FlashSign_t *sign1, FlashSign_t *sign2);

#endif /* IEC60335_B_FLASHTEST_H_ */
