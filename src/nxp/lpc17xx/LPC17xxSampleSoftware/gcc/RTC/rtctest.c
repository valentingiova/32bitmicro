/*****************************************************************************
 *   rtctest.c:  main C entry file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.23  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
/* 
Note: if the version of the head file for 17xx is 1.0(21. Nov. 2008),
	  please modify the head file like below:
	  Modify RESERVED0[3] to RESERVED0[7] in RTC_TypeDef Structure definition.
      Just some mistake of this head file. 
	  George Yan 2009.5.26      
*/
#include <lpc17xx.h>
#include "type.h"
#include "rtc.h"

extern volatile uint32_t alarm_on;
RTCTime local_time, alarm_time, current_time;

/*****************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{
	SystemInit();		    		
  /* Initialize RTC module */
  RTCInit();

  local_time.RTC_Sec = 0;
  local_time.RTC_Min = 0;
  local_time.RTC_Hour = 0;
  local_time.RTC_Mday = 8;
  local_time.RTC_Wday = 3;
  local_time.RTC_Yday = 12;		/* current date 07/12/2006 */
  local_time.RTC_Mon = 7;
  local_time.RTC_Year = 2006;
  RTCSetTime( local_time );		/* Set local time */

  alarm_time.RTC_Sec = 0;
  alarm_time.RTC_Min = 0;
  alarm_time.RTC_Hour = 0;
  alarm_time.RTC_Mday = 1;
  alarm_time.RTC_Wday = 0;
  alarm_time.RTC_Yday = 1;		/* alarm date 01/01/2007 */
  alarm_time.RTC_Mon = 1;
  alarm_time.RTC_Year = 2007;
  RTCSetAlarm( alarm_time );		/* set alarm time */

	NVIC_EnableIRQ(RTC_IRQn);

  /* mask off alarm mask, turn on IMYEAR in the counter increment interrupt
  register */
  RTCSetAlarmMask(AMRSEC|AMRMIN|AMRHOUR|AMRDOM|AMRDOW|AMRDOY|AMRMON|AMRYEAR);
  RTC -> CIIR = IMMIN | IMYEAR;
  /* 2007/01/01/00:00:00 is the alarm on */
    
  RTCStart();

  while (1) 
  {					/* Loop forever */
	current_time = RTCGetTime();
	if ( alarm_on != 0 )
	{
	  alarm_on = 0;
	  /* Get current time when alarm is on */
	  current_time = RTCGetTime();	
	}
  }

}

/******************************************************************************
**                            End Of File
******************************************************************************/
