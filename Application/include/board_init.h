#ifndef __BOARD_INIT_H
#define __BOARD_INIT_H



#include "stm32f4xx.h"



/**********************************************************************
*Function:  void SystemClock_Config(void)
*Describe:  系统时钟初始化
*Return  :  无
**********************************************************************/
void SystemClock_Config(void);

/**********************************************************************
*Function:  void Error_Handler(void)
*Describe:  无
*Return  :  无
**********************************************************************/
void Error_Handler(void);

/**********************************************************************
*Function:  void GPIO_init(void)
*Describe:  LED\KEY等管脚初始化
*Return  :  无
**********************************************************************/
void GPIO_init(void);



#endif


