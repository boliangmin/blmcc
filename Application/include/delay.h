#ifndef _DELAY_H
#define _DELAY_H  



#include "stm32f4xx.h"



/**********************************************************************
*Function:  void delay_init(uint8_t SYSCLK)
*Describe:  ��ʼ���ӳٺ���
*           SYSTICK��ʱ�ӹ̶�ΪAHBʱ��
*           SYSCLK:ϵͳʱ��Ƶ��
*Return  :  ��
**********************************************************************/
void delay_init(uint8_t SYSCLK);

/**********************************************************************
*Function:  void delay_us(uint32_t nus)
*Describe:  ��ʱnus
*           nusΪҪ��ʱ��us��.
*           nus:0~190887435(���ֵ��2^32/fac_us@fac_us=22.5)
*Return  :  ��
**********************************************************************/
void delay_ms(uint16_t nms);

/**********************************************************************
*Function:  void delay_ms(uint16_t nms)
*Describe:  ��ʱnms
*           nms:Ҫ��ʱ��ms��
*Return  :  ��
**********************************************************************/
void delay_us(uint32_t nus);



#endif


