#ifndef __BOARD_INIT_H
#define __BOARD_INIT_H



#include "stm32f4xx.h"



/**********************************************************************
*Function:  void SystemClock_Config(void)
*Describe:  ϵͳʱ�ӳ�ʼ��
*Return  :  ��
**********************************************************************/
void SystemClock_Config(void);

/**********************************************************************
*Function:  void Error_Handler(void)
*Describe:  ��
*Return  :  ��
**********************************************************************/
void Error_Handler(void);

/**********************************************************************
*Function:  void GPIO_init(void)
*Describe:  LED\KEY�ȹܽų�ʼ��
*Return  :  ��
**********************************************************************/
void GPIO_init(void);



#endif


