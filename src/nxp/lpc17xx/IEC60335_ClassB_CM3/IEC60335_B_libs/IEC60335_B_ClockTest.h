/**
 * @file	IEC60335_B_ClockTest.h
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

#ifndef __cb_clk_
#define __cb_clk_

#include "IEC60335.h"

void IEC60335_initClockTest(UINT32 timerOccThreshold, UINT32 rtcOccThreshold, UINT32 timerLowerBound, UINT32 timerUpperBound);
/*! \brief  */
type_testResult IEC60335_Clocktest_MainLoopHandler(void);
/*! \brief  */
void IEC60335_Clocktest_TimerIntHandler(void);
/*! \brief  */
void IEC60335_Clocktest_RTCHandler(void);

#endif
