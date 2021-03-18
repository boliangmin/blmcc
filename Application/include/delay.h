#ifndef _DELAY_H
#define _DELAY_H  



#include "stm32f4xx.h"



/**********************************************************************
*Function:  void delay_init(uint8_t SYSCLK)
*Describe:  初始化延迟函数
*           SYSTICK的时钟固定为AHB时钟
*           SYSCLK:系统时钟频率
*Return  :  无
**********************************************************************/
void delay_init(uint8_t SYSCLK);

/**********************************************************************
*Function:  void delay_us(uint32_t nus)
*Describe:  延时nus
*           nus为要延时的us数.
*           nus:0~190887435(最大值即2^32/fac_us@fac_us=22.5)
*Return  :  无
**********************************************************************/
void delay_ms(uint16_t nms);

/**********************************************************************
*Function:  void delay_ms(uint16_t nms)
*Describe:  延时nms
*           nms:要延时的ms数
*Return  :  无
**********************************************************************/
void delay_us(uint32_t nus);



#endif


