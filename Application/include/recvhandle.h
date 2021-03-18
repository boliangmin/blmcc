#ifndef __RECVHANDLE_H
#define __RECVHANDLE_H


#include "stm32f4xx.h"



#define POSITIVE_RESPONSE 0x0521U
#define NEGATIVE_RESPONSE 0x0721U
#define TEST_RESPONSE 38



/**********************************************************************
*Function:  void CanRecvService(void)
*Describe:  CAN服务处理函数
*Return  :  无
**********************************************************************/
void CanRecvService(void);

/**********************************************************************
*Function:  void SendPositiveResponse(uint16_t buff[])
*Describe:  积极应答
*Return  :  无
**********************************************************************/
void SendPositiveResponse(uint16_t buff[]);

/**********************************************************************
*Function:  void SendNagetiveResponse(uint16_t buff[])
*Describe:  消极应答
*Return  :  无
**********************************************************************/
void SendNagetiveResponse(uint16_t buff[]);



#endif


