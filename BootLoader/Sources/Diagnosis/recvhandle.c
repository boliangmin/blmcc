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
u8 Update_state = 0;

/*********************************************************************************************************
** Function name:       u8 key_check(u8 *key)
** Descriptions:        ��ȫ������ԿУ��
** input parameters:    3λ�ֽ���Կ
** output parameters:   ��
** Returned value:      1--��֤ͨ����0--��֤ʧ��
*********************************************************************************************************/
u8 key_check(u8 *key)
{
    u8 paswd = ( (key[0] <<16) | (key[1] << 8) | key[2] );
    if(paswd == (u8)SECURITY_PASSWD)
        return 1;
    else
        return 0;
}

/*********************************************************************************************************
** Function name:       u8 erase_add_check(u8 *add)
** Descriptions:        ������ַУ��
** input parameters:    4λ������ַ
** output parameters:   ��
** Returned value:      1--������ַ��ȷ��0--������ַ����
*********************************************************************************************************/
u8 erase_add_check(u8 *add)
{
    u8 temp_add = ( (add[1] << 24) | (add[2] << 16) | (add[3] << 8) | add[4] );
    if(temp_add == (u8)BOOT_START_ADD)
        return 1;
    else
        return 0;
}

/*********************************************************************************************************
** Function name:       void DiagService(u8 *DiagData)
** Descriptions:        ��Ӧ����Ϸ�����
** input parameters:    �����������
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
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
                if(key_check(&DiagData[2]) == 1)
                {
                    Update_state = UP_SER_PASS;

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
                else
                {
                    tempData[0] = 0x04U;
                    tempData[1] = SECURITY_ACCESS;
                    tempData[2] = SECURITY_ACCESS_KEY;
                    tempData[3] = NEGATIVE_RESPOND;
                    tempData[4] = SECURITY_KEY_ERROR;
                    tempData[5] = 0xff;
                    tempData[6] = 0xff;
                    tempData[7] = 0xff;
                    SendNagetiveResponse(tempData);
                }
            }
        break;
        case ERASE_REQUEST:
            if( (DiagData[1] == ((ERASE_ADD_SEND >> 8) & 0xff)) && (DiagData[2] == (ERASE_ADD_SEND & 0xff)) )
            {
                if( (erase_add_check(&DiagData[4]) == 1) && (Update_state == UP_SER_PASS) )
                {
                    //78����
                    //FLASH_Erase();         //����flash����

                    if(0)                //�����ɹ�
                    {
                        Update_state = UP_ERASE_FINISH;

                        tempData[0] = 0x05U;
                        tempData[1] = ERASE_REQUEST;
                        tempData[2] = (ERASE_ADD_SEND >> 8) & 0xff;
                        tempData[3] = ERASE_ADD_SEND & 0xff;
                        tempData[4] = POSITIVE_RESPOND;
                        tempData[5] = ERASE_SUCCESS;
                        tempData[6] = 0xff;
                        tempData[7] = 0xff;
                        SendPositiveResponse(tempData);
                    }
                    else
                    {
                        Update_state = 0;

                        tempData[0] = 0x06U;
                        tempData[1] = ERASE_REQUEST;
                        tempData[2] = (ERASE_ADD_SEND >> 8) & 0xff;
                        tempData[3] = ERASE_ADD_SEND & 0xff;
                        tempData[4] = NEGATIVE_RESPOND;
                        tempData[5] = ERASE_FAILED;
                        tempData[6] = ERASE_TIME_OUT;
                        tempData[7] = 0xff;
                        SendNagetiveResponse(tempData);
                    }
                }
                else
                {
                    tempData[0] = 0x06U;
                    tempData[1] = ERASE_REQUEST;
                    tempData[2] = (ERASE_ADD_SEND >> 8) & 0xff;
                    tempData[3] = ERASE_ADD_SEND & 0xff;
                    tempData[4] = NEGATIVE_RESPOND;
                    tempData[5] = ERASE_FAILED;
                    tempData[6] = ERASE_ADD_ERROR;
                    tempData[7] = 0xff;
                    SendNagetiveResponse(tempData);
                }
            }
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

/*********************************************************************************************************
** Function name:       void CAN_Frame_prase(u8 *ReqData)
** Descriptions:        CAN���Ľ���
** input parameters:    ���յ���can����
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void CAN_Frame_prase(u8 *ReqData)
{
    u16 ReqDataIdx = 0;
    //u16 tempIdx = 0;
    u16 i = 0;
    //u8 	RespData[8] = {0};
	
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
            DiagDataLen = 0;               //���������±�����ݳ������㣬Ϊ�´ν�����׼��
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

/*********************************************************************************************************
** Function name:       void CanRecvService(void)
** Descriptions:        �жϴ��������յ�can���ĺ󣬵��ñ��Ľ���
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void CanRecvService(void)
{
    if(flag ==1)
    {
        CAN_Frame_prase(Can_Handle.pRxMsg->Data);
        flag = 0;
    }
}

/*********************************************************************************************************
** Function name:       void SendPositiveResponse(u8 *buff)
** Descriptions:        ��Ϸ������Ӧ��
** input parameters:    �����͵Ļ���Ӧ������
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void SendPositiveResponse(u8 *buff)
{
    CAN_SetMsg(SEND_ID,buff);
    HAL_CAN_Transmit_IT(&Can_Handle);
    HAL_Delay(100);
}

/*********************************************************************************************************
** Function name:       void SendNagetiveResponse(u8 buff[])
** Descriptions:        ��Ϸ�������Ӧ��
** input parameters:    �����͵�����Ӧ������
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void SendNagetiveResponse(u8 buff[])
{
    CAN_SetMsg(SEND_ID,buff);
    HAL_CAN_Transmit_IT(&Can_Handle);
    HAL_Delay(100);
}

