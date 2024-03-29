#ifndef _DEV_USART_H
#define _DEV_USART_H



#include "stm32f4xx.h"
#include "stdio.h"	



#define USART_REC_LEN  	 200  	  //定义最大接收字节数 200
#define RXBUFFERSIZE     1        //缓存大小
#define EN_USART1_RX 	 1		  //使能（1）/禁止（0）串口1接收

extern uint8_t  USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern uint16_t USART_RX_STA;         		     //接收状态标记	
extern UART_HandleTypeDef UART1_Handler;         //UART句柄
extern uint8_t aRxBuffer[RXBUFFERSIZE];          //HAL库USART接收Buffer


//如果想串口中断接收，请不要注释以下宏定义
void uart_init(uint32_t bound);



#endif


