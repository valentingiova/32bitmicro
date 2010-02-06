/**
  ******************************************************************************
  * @file    stm32f10x_conf.h 
  * @author  32bitmicro.com
  * @version V3.1.2
  * @date    02/01/2010
  * @brief   Library configuration file.
  ******************************************************************************
  * @copy
  *
  *
  * <h2><center>&copy; COPYRIGHT 2010 32bitmicro.com</center></h2>
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_CONF_H
#define __STM32F10x_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Uncomment the line below to enable peripheral header file inclusion */
#ifdef TARGET_STM32F_USE_ADC
#include "stm32f10x_adc.h"
#endif
#ifdef TARGET_STM32F_USE_BKP
#include "stm32f10x_bkp.h"
#endif
#ifdef TARGET_STM32F_USE_CAN
#include "stm32f10x_can.h"
#endif
#ifdef TARGET_STM32F_USE_CRC
#include "stm32f10x_crc.h"
#endif
#ifdef TARGET_STM32F_USE_DAC
#include "stm32f10x_dac.h"
#endif
#ifdef TARGET_STM32F_USE_DBGMCU
#include "stm32f10x_dbgmcu.h"
#endif
#ifdef TARGET_STM32F_USE_DMA
#include "stm32f10x_dma.h"
#endif
#ifdef TARGET_STM32F_USE_EXTI
#include "stm32f10x_exti.h"
#endif
#ifdef TARGET_STM32F_USE_FLASH
#include "stm32f10x_flash.h"
#endif
#ifdef TARGET_STM32F_USE_FSMC
#include "stm32f10x_fsmc.h"
#endif
#ifdef TARGET_STM32F_USE_GPIO
#include "stm32f10x_gpio.h"
#endif
#ifdef TARGET_STM32F_USE_I2C
#include "stm32f10x_i2c.h"
#endif
#ifdef TARGET_STM32F_USE_IWDG
#include "stm32f10x_iwdg.h"
#endif
#ifdef TARGET_STM32F_USE_PWR
#include "stm32f10x_pwr.h"
#endif
#ifdef TARGET_STM32F_USE_RCC
#include "stm32f10x_rcc.h"
#endif
#ifdef TARGET_STM32F_USE_RTC
#include "stm32f10x_rtc.h"
#endif
#ifdef TARGET_STM32F_USE_SDIO
#include "stm32f10x_sdio.h"
#endif
#ifdef TARGET_STM32F_USE_SPI
#include "stm32f10x_spi.h"
#endif
#ifdef TARGET_STM32F_USE_TIM
#include "stm32f10x_tim.h"
#endif
#ifdef TARGET_STM32F_USE_USART
#include "stm32f10x_usart.h"
#endif
#ifdef TARGET_STM32F_USE_WWDG
#include "stm32f10x_wwdg.h"
#endif
#ifdef TARGET_STM32F_USE_MISC
#include "misc.h"   /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */
#endif
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line below to expanse the "assert_param" macro in the 
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1 */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *   which reports the name of the source file and the source
  *   line number of the call that failed. 
  *   If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __STM32F10x_CONF_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
