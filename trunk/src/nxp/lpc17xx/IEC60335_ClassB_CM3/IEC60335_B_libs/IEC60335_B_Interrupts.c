/**
 * @file	IEC60335_B_Interrupts.c
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

#include "IEC60335_B_Interrupts.h"

/*! 
	The interrupt check has to be called in fixed equidistant times. You must estimate how many times the 
	interrupt will occur within this known time slice.

	\param *pIRQ Pointer to the interrupt test structure.
	\param lowerBound Estimated minimum count of occured interrupts. (Don't take respect to the individualValue).
	\param upperBound Estimated maximum count of occured interrupts. (Don't take respect to the individualValue).
	\param individualValue The internally used individual up-counting value.

	\attention Ensure to place the function call #IEC60335_InterruptOcurred into the corresponding 
	interrupt service handler!
*/
void IEC60335_InitInterruptTest(type_InterruptTest *pIRQ, UINT32 lowerBound, UINT32 upperBound, UINT32 individualValue)
{
	if(pIRQ != 0)
	{
		pIRQ->Count = 0;
	
		pIRQ->lower = lowerBound;
		pIRQ->upper = upperBound;
	
		pIRQ->individualValue = individualValue;

		pIRQ->CountOverflow = FALSE;
	}
}

/*!
	This function must be called from any interrupt service handler which has to be tested.

	\param *pIRQ Pointer to the interrupt test structure.
*/
void IEC60335_InterruptOcurred(type_InterruptTest *pIRQ)
{
	if(pIRQ != 0)
	{
		UINT32 cnt = pIRQ->Count;

		pIRQ->Count = pIRQ->Count + pIRQ->individualValue;

		if(cnt > pIRQ->Count)
			pIRQ->CountOverflow = TRUE;
	}
}

/*!
	The interrupt check routine must be called once in known equidistant times.

	\attention	Prevent this function to be disturbed by interrupts. You can either call it insde of an interrupt service handler,
	or disable interrupts globally, but this is not recommended.

	\param *pIRQ Pointer to the interrupt test structure.
	\return Tells if passed or failed. See \link #tag_testResult type_testResult \endlink.
*/
type_testResult IEC60335_InterruptCheck(type_InterruptTest *pIRQ)
{
	type_testResult Result = IEC60335_testFailed;

	if(pIRQ != 0)
	{
		Result = ifIsInRange(pIRQ->lower*pIRQ->individualValue,pIRQ->Count,pIRQ->upper*pIRQ->individualValue) ? 
						(IEC60335_testPassed) :
						(IEC60335_testFailed);

		if(pIRQ->CountOverflow == TRUE)
		{
			pIRQ->CountOverflow = FALSE;
			Result = IEC60335_testFailed;
		}

		pIRQ->Count = 0;
	}

	return Result;
}
