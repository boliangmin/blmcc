#include "recvhandle.h"
#include "dev_can.h"
#include "delay.h"
//#include "usart.h"



extern __IO uint32_t can_rx_flag ;
extern CAN_HandleTypeDef Can_Handle;



/**********************************************************************
*Function:  void CanRecvService(void)
*Describe:  CAN服务处理函数
*Return  :  无
**********************************************************************/
void CanRecvService(void)
{
	uint16_t i;
	uint16_t tempdData[8] = {0};
	if(1 == can_rx_flag)
	{
		printf("CAN接收到数据：\r\n");
		for(i=0;i<8;i++)
		{
			printf("%d\t",Can_Handle.pRxMsg->Data[i]);
		}
		printf("\r\n");

		tempdData[0] = 0x03U;
		tempdData[1] = TEST_RESPONSE;
		tempdData[2] = 0x55U;
		tempdData[3] = 0x55U;
		tempdData[4] = 0x55U;
		tempdData[5] = 0x55U;
		tempdData[6] = 0x55U;
		tempdData[7] = 0x55U;
		SendPositiveResponse(tempdData);

		can_rx_flag = 0;
		tempdData[0] = 0x01U;
		tempdData[1] = TEST_RESPONSE;
		tempdData[2] = 0x55U;
		tempdData[3] = 0x55U;
		tempdData[4] = 0x55U;
		tempdData[5] = 0x55U;
		tempdData[6] = 0x55U;
		tempdData[7] = 0x55U;
		SendNagetiveResponse(tempdData);
		HAL_Delay(100);
	}
	else
	{
		printf("CAN发送信息:\r\n\r\n");
		tempdData[0] = 0x00U;
		tempdData[1] = 0x01U;
		tempdData[2] = 0x02U;
		tempdData[3] = 0x03U;
		tempdData[4] = 0x04U;
		tempdData[5] = 0x05U;
		tempdData[6] = 0x06U;
		tempdData[7] = 0x07U;
		CAN_SetMsg(0x315,tempdData);
		HAL_CAN_Transmit_IT(&Can_Handle);
		HAL_Delay(1000);
	}
}

/**********************************************************************
*Function:  void SendPositiveResponse(uint16_t buff[])
*Describe:  积极应答
*Return  :  无
**********************************************************************/
void SendPositiveResponse(uint16_t buff[])
{
	CAN_SetMsg(POSITIVE_RESPONSE,buff);
	HAL_CAN_Transmit_IT(&Can_Handle);
	HAL_Delay(100);
}

/**********************************************************************
*Function:  void SendNagetiveResponse(uint16_t buff[])
*Describe:  消极应答
*Return  :  无
**********************************************************************/
void SendNagetiveResponse(uint16_t buff[])
{
	CAN_SetMsg(NEGATIVE_RESPONSE,buff);
	HAL_CAN_Transmit_IT(&Can_Handle);
	HAL_Delay(100);
}


