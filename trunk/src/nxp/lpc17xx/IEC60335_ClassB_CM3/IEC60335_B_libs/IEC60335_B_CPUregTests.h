/*
 * IEC60335_B_CPUregTests.h
 *
 *  Created on: 27-jul-2009
 *      Author: nlv15840
 */

#ifndef IEC60335_B_CPUREGS_H_
#define IEC60335_B_CPUREGS_H_

#include "IEC60335.h"

#if defined ( __CC_ARM   )
  #define __ASM            __asm                                      /*!< asm keyword for ARM Compiler          */
  #define __INLINE         __inline                                   /*!< inline keyword for ARM Compiler       */

#elif defined ( __ICCARM__ )
  #define __ASM           __asm                                       /*!< asm keyword for IAR Compiler           */
  #define __INLINE        inline                                      /*!< inline keyword for IAR Compiler. Only avaiable in High optimization mode! */

#elif defined   (  __GNUC__  )
  #define __ASM            __asm                                      /*!< asm keyword for GNU Compiler          */
  #define __INLINE         inline                                     /*!< inline keyword for GNU Compiler       */

#endif


typedef struct {
  /* base 0 */
  unsigned int testState;       /*!< CPU register POST tests passed */
  /* base 4 */
  unsigned int testPassed;      /*!< CPU register POST test status (PASS/FAIL) */
}IEC60335_CPUreg_struct;

/*!
 * @brief IEC607335 CPU register test POST (Pre Operation Self Test)
 */
extern void _CPUregTestPOST (void);

/*!
 * @brief IEC607335 CPU register test BIST (Build in Self Test)
 *          Low-range registers tests r0-r7
 */
extern void _CPUregTestLOW (void);

/*!
 * @brief IEC607335 CPU register test BIST (Build in Self Test)
 *          Mid-range registers tests r4-r10
 */
extern void _CPUregTestMID (void);

/*!
 * @brief IEC607335 CPU register test BIST (Build in Self Test)
 *          Mid-range registers tests r8-r12
 */
extern void _CPUregTestHIGH (void);

/*!
 * @brief IEC607335 CPU register test BIST (Build in Self Test)
 *          Stack pointer registers tests MSP,PSP
 */
extern void _CPUregTestSP (void);

/*!
 * @brief IEC607335 CPU register test BIST (Build in Self Test)
 *          Other special register tests
 */
extern void _CPUregTestSPEC (void);

type_testResult IEC60335_CPUregTest_BIST(void);
type_testResult IEC60335_CPUregTest_POST(void);



#endif /* IEC60335_B_CPUREGS_H_ */
