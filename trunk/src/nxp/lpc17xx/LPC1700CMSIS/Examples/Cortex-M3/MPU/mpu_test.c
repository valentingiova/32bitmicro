/***********************************************************************//**
 * @file		dac_speaker.c
 * @purpose		This example used to test DAC peripheral through speaker
 * @version		1.0
 * @date		16. July. 2010
 * @author		NXP MCU SW Application Team
 *---------------------------------------------------------------------
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
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "debug_frmwrk.h"
#include "lpc17xx_gpio.h"

/* Example group ----------------------------------------------------------- */
/** @defgroup Cortex_M3_MPU	MPU
 * @ingroup Cortex_M3_Examples
 * @{
 */
/************************** PRIVATE VARIABLES *************************/
uint8_t menu[]=
	"********************************************************************************\n\r"
	"Hello NXP Semiconductors \n\r"
	"MPU demo \n\r"
	"\t - MCU: LPC17xx \n\r"
	"\t - Core: ARM CORTEX-M3 \n\r"
	"\t - Communicate via: UART0 - 115200 bps \n\r"
	"Set up 6 region memory and try to access memory that don't allow to invoke\n\r"
	"Memory Management Handler\n\r"
	"********************************************************************************\n\r";
Bool Led_State = FALSE;

/************************** PRIVATE FUNCTIONS *************************/
void MemManage_Handler(void);

/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @brief		Memory Management interrupt handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void MemManage_Handler(void)
{
	uint32_t i;
	//Blink LED P1.28
	if(Led_State == FALSE)
	{
		GPIO_SetValue(1,(1<<28));
		Led_State = TRUE;
		for(i = 0;i<0x70000;i++);//delay
	}
	else
	{
		GPIO_ClearValue(1,(1<<28));
		Led_State = FALSE;
		for(i = 0;i<0x70000;i++);//delay
	}
}

/*-------------------------MAIN FUNCTION------------------------------*/
/*********************************************************************//**
 * @brief		c_entry: Main MPU program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int c_entry(void)
{
	uint32_t test;
	/* Initialize debug via UART0
	 * – 115200bps
	 * – 8 data bit
	 * – No parity
	 * – 1 stop bit
	 * – No flow control
	 */
	debug_frmwrk_init();
	_DBG(menu);

	//Turn off all LEDs
	GPIO_SetDir(1,(1<<28)|(1<<29)|(1<<31),1);
	GPIO_SetDir(2,(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6),1);

	/* Set up MPU:
	 * - Region 0: 0x00000000 - 0x0007FFFF --- on-chip non-volatile memory
	 * 		+ Size: 512kB
	 * 		+ XN=0: enable instruction fetch
	 * 		+ AP=b011: full access
	 * 		+ TEX=0, S=1, C=1, B=1
	 * - Region 1: 0x10000000 - 0x10007FFF --- on-chip SRAM
	 * 		+ Size: 32kB
	 * 		+ XN=0: enable instruction fetch
	 * 		+ AP=b011: full access
	 * 		+ TEX=0, S=1, C=1, B=1
	 * - Region 2:	0x40000000 - 0x400FFFFF --- APB peripheral
	 * 		+ Size: 1MB
	 * 		+ XN=0: enable instruction fetch
	 * 		+ AP=b011: full access
	 * 		+ TEX=0, S=1, C=0, B=1
	 * - Region 3: 0x50000000 - 0x501FFFFF --- AHB peripheral
	 * 		+ Size: 2MB
	 * 		+ XN=0: enable instruction fetch
	 * 		+ AP=b011: full access
	 * 		+ TEX=0, S=1, C=0, B=1
	 * - Region 4: 0xE0000000 - 0xE00FFFFF --- System control
	 * 	 	+ Size: 1MB
	 * 		+ XN=0: enable instruction fetch
	 * 		+ AP=b011: full access
	 * 		+ TEX=0, S=1, C=0, B=1
	 * - Region 5:0x2009C000 - 0x2009FFFF --- GPIO peripheral
	 * 	 	+ Size: 16kB
	 * 		+ XN=0: enable instruction fetch
	 * 		+ AP=b011: full access
	 * 		+ TEX=0, S=1, C=0, B=1
	 * - Region 6: 0x20080000 - 0x20083FFF --- on chip SRAM
	 * 		+ Size: 16kB
	 * 		+ XN=0: enable instruction fetch
	 * 		+ AP=b000: no access
	 * 		+ TEX=0, S=1, C=1, B=1
	 */

	MPU->RNR = 0;//indicate MPU region 0
	MPU->RBAR = 0x00000000; // update the base address for the region 0
	MPU->RASR = 0x03070025;
	MPU->RNR = 1;
	MPU->RBAR = 0x10000000; // update the base address for the region 1
	MPU->RASR = 0x0307001D;
	MPU->RNR = 2;
	MPU->RBAR = 0x40000000; // update the base address for the region 2
	MPU->RASR = 0x03050027;
	MPU->RNR = 3;
	MPU->RBAR = 0x50000000; // update the base address for the region 3
	MPU->RASR = 0x03050029;
	MPU->RNR = 4;
	MPU->RBAR = 0xE0000000; // update the base address for the region 4
	MPU->RASR = 0x03070027;
	MPU->RNR = 5;
	MPU->RBAR = 0x2009C000; // update the base address for the region 5
	MPU->RASR = 0x0307001B;
	MPU->RNR = 6;
	MPU->RBAR = 0x20080000; // update the base address for the region 6
	MPU->RASR = 0x0007001B;

	_DBG_("Setup MPU: \n\r"
		  "This provide 7 regions: \n\r"
		  "Region 0 - Privileged code: 0x00000000 - 0x0007FFFF(512kB)\n\r"
		  "Region 1 - Privileged data: 0x10000000 - 0x10007FFF(32kB)\n\r"
		  "Region 2 - APB Peripheral:  0x40000000 - 0x400FFFFF(1MB)\n\r"
		  "Region 3 - AHB peripheral:  0x50000000 - 0x501FFFFF(2MB)\n\r"
		  "Region 4 - System control:  0xE0000000 - 0xE00FFFFF(1MB)\n\r"
		  "Region 5 - GPIO peripheral: 0x2009C000 - 0x2009FFFF(16kB)\n\r"
		  "Region 6 - Private SRAM:    0x20080000 - 0x20083FFF(16kB)\n\r"
		  "Region 6 can not access (just used for testing)");

	SCB->SHCSR |=(1<<16); //Enable Memory management fault
	MPU->CTRL =(1<<0); //Enable the MPU
	_DBG_("Enable MPU!");

	//try to access to this memory range
	_DBG_("Press '1' to try to read memory from region 1");
	while(_DG !='1');
	test = (*(unsigned int *)0x10000000);
	_DBG_("Read successful!!!");

	_DBG_("Press '2' to try to read memory from region 5\n\r"
		  "Read memory at this region is not allow, LED p1.28 will blink...");
	while(_DG !='2');
	test = (*(unsigned int *)0x20080000);

	while(1);
	return 1;
}

/* With ARM and GHS toolsets, the entry point is main() - this will
   allow the linker to generate wrapper code to setup stacks, allocate
   heap area, and initialize and copy code and data segments. For GNU
   toolsets, the entry point is through __start() in the crt0_gnu.asm
   file, and that startup code will setup stacks and data */
int main(void)
{
    return c_entry();
}

#ifdef  DEBUG
/*******************************************************************************
* @brief		Reports the name of the source file and the source line number
* 				where the CHECK_PARAM error has occurred.
* @param[in]	file Pointer to the source file name
* @param[in]    line assert_param error line source number
* @return		None
*******************************************************************************/
void check_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while(1);
}
#endif

/*
 * @}
 */
