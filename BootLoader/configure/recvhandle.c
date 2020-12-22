#include "recvhandle.h"
#include "can.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "diag_service.h"

extern __IO uint32_t flag ;
extern CAN_HandleTypeDef Can_Handle;

u8 	DiagData[TEMP_DATA_MAX] = {0};
u16 DiagDataLen = 0;


void DiagService(u8 *DiagData)
{
		u8 tempData[8] = {0};
    switch(DiagData[0])
		{
			case READ_MASSAGE:
					break;
			case SECURITY_ACCESS:
					if(DiagData[1] == SECURITY_ACCESS_REQ)
					{
							tempData[0] = 0x05U;
							tempData[1] = SECURITY_ACCESS;
							tempData[2] = SECURITY_ACCESS_REQ;
							tempData[3] = POSITIVE_RESPOND;
							tempData[4] = (SECURITY_ACCESS_BOOT >> 8) & 0xff;
							tempData[5] = SECURITY_ACCESS_BOOT & 0xff;
							tempData[6] = 0xff;
							tempData[7] = 0xff;
							SendPositiveResponse(tempData);
					}
					else if(DiagData[1] == SECURITY_ACCESS_KEY)
					{
							tempData[0] = 0x04U;
							tempData[1] = SECURITY_ACCESS;
							tempData[2] = SECURITY_ACCESS_KEY;
							tempData[3] = POSITIVE_RESPOND;
							tempData[4] = SECURITY_KEY_RIGHT;
							tempData[5] = 0xff;
							tempData[6] = 0xff;
							tempData[7] = 0xff;
							SendPositiveResponse(tempData);
					}
					break;
			case ERASE_REQUEST:
					break;
			case REQ_DOWNLOAD:
					break;
			case DATA_TRANS:
					break;
			case QUIT_TRANS:
					break;
			case CHECK_SUM:
					break;
			case WRITE_MASSAGE:
					break;
			case MCU_RESET:
					break;
		}
}



void CAN_Frame_prase(u8 *ReqData)
{
    u16 ReqDataIdx = 0;
//    u16 tempIdx = 0;
	  u16 i = 0;
//    u8 	RespData[8] = {0};
	
    switch(ReqData[0] & 0xf0)
    {
        case NORMAL_FRAME:
            DiagDataLen = ReqData[0] & 0x0f;
						for(i=0;i<DiagDataLen;i++)
						{
						    DiagData[ReqDataIdx] = ReqData[i+1];
								ReqDataIdx++;
						}
						DiagService(DiagData);
						DiagDataLen = 0;               //请求数据下标和数据长度清零，为下次接收做准备
						ReqDataIdx = 0;
						break;
        case REQUEST_FRAME:
						break;
        case LONGDATA_FRAME:
						break;
        case REQ_LONG_FRAME:
						break;
    }
}


void CanRecvService(void)
{
		if(flag ==1)
		{
				CAN_Frame_prase(Can_Handle.pRxMsg->Data);
				flag = 0;
		}
}


void SendPositiveResponse(u8 *buff)
{
    CAN_SetMsg(SEND_ID,buff);
	  HAL_CAN_Transmit_IT(&Can_Handle);
	  HAL_Delay(100);
}

void SendNagetiveResponse(u8 buff[])
{
	  CAN_SetMsg(SEND_ID,buff);
	  HAL_CAN_Transmit_IT(&Can_Handle);
	  HAL_Delay(100);
}
