/********************************************************************
;
;  modified LPC2000 sample code
;
; RC5 format:
;
;      | S | F | C |   5 sytem bits    |    6 command bits     |
;      | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 1 | 1 | 1 | 1 |
;
;   -----+ +-+   +-+ +-+ +-+ +-+ +---+ +-+   +---+ +-+ +-+ +-+ +----
;        | | |   | | | | | | | | |   | | |   |   | | | | | | | |
;        +-+ +---+ +-+ +-+ +-+ +-+   +-+ +---+   +-+ +-+ +-+ +-+
;
********************************************************************/

#include "LPC13xx.h"			/* LPC13xx Peripheral Registers */

#define RC5_INPUT_PIN      (1<< 0x01)

#define MIN_HALF_BIT       640             // 640 us
#define HALF_BIT_TIME      889             // 889 us
#define MAX_HALF_BIT       1140            // 1140 us
#define MIN_FULL_BIT       1340            // 1340 us
#define FULL_BIT_TIME      1778            // 1778 us
#define MAX_FULL_BIT       2220            // 2220 us

unsigned char RC5_System;                  // Format 1 E/N t  s4 s3 s3 s1 s0
unsigned char RC5_Command;                 // Format 0  0  c5 c4 c3 c2 c1 c0
unsigned char RC5_flag;

static signed int    low_time;
static signed int    high_time;
static unsigned char half_bit;
static unsigned char sys;                  // system byte
static unsigned char cmd;                  // Command byte

void RC5_Init(void)
{
//GPIO setup
  //assign input for IR sensor
  LPC_GPIO0->DIR &= ~(RC5_INPUT_PIN);
  LPC_IOCON->PIO0_1 |= (1<<5);          //turn on hysteresis
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);  //enable GPIO clock
  NVIC_EnableIRQ(EINT0_IRQn);

//timer16 0 setup
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);
  LPC_TMR16B0->PR  = 48;       // prescaler 48, timer runs at 48 MHz / 48 = 1 MHz
  LPC_TMR16B0->MR0 = 12000;         //load match register 0
  LPC_TMR16B0->MCR = 3;		  // Interrupt and Reset on MR0
  NVIC_EnableIRQ(TIMER_16_0_IRQn);

  LPC_GPIO0->IS &= ~(0x1<<0x01);  //interrupt sense - 0 = edge sensitive
  LPC_GPIO0->IBE |= 0x1<<0x01; //interrupt both edges - 1 = both edges
  LPC_GPIO0->IE |= ( 0x1 << 0x01);    //interrupt enable

  LPC_TMR16B0->TCR = 1;             //Start timer
}

static void RC5_Shift_Bit(char val)
{
    if (sys & 0x80)
    {
        if (cmd & 0x80)                    // command full ?
        {
            sys = 0;                       // yes, ERROR
            cmd = 0;
        }
        else
            cmd = (cmd << 1) | val;        // shift command
    }
    else
        sys = (sys << 1) | val;            // shift system
}

/************************************************************************
; RC5_Decode (we only take action at a rising edge)
;
; Half(prev) Bit   Low Time        High Time      Action     New Half Bit
; -------------------------------------------------------------------
;     0               0               0          Shift 0         0
;     0               0               1          Shift 1         1
;     0               1               0          -ERROR-         *
;     0               1               1          Shift 1,0       0
;     1               0               0          Shift 1         1
;     1               0               1          -ERROR-         *
;     1               1               0          Shift 1,0       0
;     1               1               1          -ERROR-         *
;
***********************************************************************/
static void RC5_Decode(void)
{
  unsigned char action;

    action = half_bit << 2;

// Check High Time
    if ((high_time > MIN_FULL_BIT) && (high_time < MAX_FULL_BIT))
        action = action | 1;               // high_time = long
    else if (!((high_time > MIN_HALF_BIT) && (high_time < MAX_HALF_BIT)))
    {
        sys = 0;                           // RC5 ERROR
        cmd = 0;
        return;
    }

// Check Low Time

    if ((low_time > MIN_FULL_BIT) && (low_time < MAX_FULL_BIT))
        action = action | 2;               // low_time = long
    else if (!((low_time > MIN_HALF_BIT) && (low_time < MAX_HALF_BIT)))
    {
        sys = 0;                           // RC5 ERROR
        cmd = 0;
        return;
    }

    switch (action)
    {
      case 0:  RC5_Shift_Bit(0);           // short low, short high, shift 0
               break;
      case 1:  RC5_Shift_Bit(1);           // short low, long high, shift 1
               half_bit = 1;               // new half bit is true
               break;
      case 2:  sys = 0;                    // long low, short high, ERROR
               cmd = 0;
      case 3:  RC5_Shift_Bit(1);           // long low, long high, shift 1,0
               RC5_Shift_Bit(0);
               break;
      case 4:  RC5_Shift_Bit(1);           // short low, short high, shift 1
               break;
      case 5:  sys = 0;                    // short low, long high, ERROR
               cmd = 0;
               break;
      case 6:  RC5_Shift_Bit(1);           // long low, short high, shift 1,0
               RC5_Shift_Bit(0);
               half_bit = 0;               // new half bit is false
               break;
      case 7:  sys = 0;                    // long low, long high, ERROR
               cmd = 0;
      default: break;                      // invalid
    }
}

void PIOINT0_IRQHandler(void)
{
  uint32_t regVal;

  LPC_TMR16B0->TCR = 0;                     //disable timer

  regVal =  LPC_GPIO0->MIS & (0x1<<0x01);  //get interrupt status
  if ( regVal )
  {

        if( (LPC_GPIO0->DATA & RC5_INPUT_PIN) == RC5_INPUT_PIN)         // check rising or falling edge
        {
            if (sys == 0)                  // First pulse ?
            {
                low_time  = HALF_BIT_TIME; // assume short low time
                high_time = HALF_BIT_TIME; // assume short high time
                half_bit  = 1;             // assume half bit is true
                cmd = 0x02;                // = 00000010, prepare command byte
            }
            else
                low_time = LPC_TMR16B0->TC;          // rising, so capture low time

            RC5_Decode();
        }
        else
            high_time = LPC_TMR16B0->TC;             // falling, so capture high time
    
  }		
  LPC_TMR16B0->TCR = 1;             //enable timer
  LPC_TMR16B0->TCR = 2;             //reset timer
  LPC_GPIO0->IC |= ( 0x1 << 0x01);  //clear interrupt
  LPC_TMR16B0->TCR = 1;             //enable timer
}

void TIMER16_0_IRQHandler(void)
{  
  if ( LPC_TMR16B0->IR & 0x1 )
  {
    //timeout has occured.
    if (cmd & 0x80)                    // command full ?
    {
      RC5_Command = cmd & 0x7F;      // OK ! Save command byte
      RC5_System = sys;              // save system byte
      RC5_flag = 1;                  // set event to application
    }
    sys = 0;
    cmd = 0;
  }
  LPC_TMR16B0->IR = 1;			// clear interrupt flag
}
