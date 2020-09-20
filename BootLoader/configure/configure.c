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
	  HAL_Init();                     //初始化HAL库   
    Stm32_Clock_Init(360,25,2,7);   //设置时钟,180Mhz
    delay_init(180);                //初始化延时函数
    uart_init(115200);              //初始化USART
}
