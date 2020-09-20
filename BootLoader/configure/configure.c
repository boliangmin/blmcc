#include "sys.h"
#include "can.h"
#include "delay.h"
#include "usart.h"

//void CanInit()
//{
//	  CAN1_Mode_Init(CAN_SJW_1TQ,CAN_BS2_6TQ,CAN_BS1_8TQ,6,CAN_MODE_LOOPBACK);
//}


void BoardInit()
{
	  HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,7);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
    uart_init(115200);              //��ʼ��USART
}
