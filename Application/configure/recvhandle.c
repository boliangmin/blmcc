#include "recvhandle.h"
#include "can.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"

extern __IO uint32_t flag ;
extern CAN_HandleTypeDef Can_Handle;

void CanRecvService(void)
{
	  u16 i;
	  u16 tempdData[8] = {0};
	  if(flag==1)
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

			  flag=0;
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


void SendPositiveResponse(u16 buff[])
{
    CAN_SetMsg(POSITIVE_RESPONSE,buff);
	  HAL_CAN_Transmit_IT(&Can_Handle);
	  HAL_Delay(100);
}

void SendNagetiveResponse(u16 buff[])
{
	  CAN_SetMsg(NEGATIVE_RESPONSE,buff);
	  HAL_CAN_Transmit_IT(&Can_Handle);
	  HAL_Delay(100);
}
