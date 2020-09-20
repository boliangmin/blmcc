#include "sys.h"
#include "configure.h"
#include "delay.h"
#include "can.h"

__IO uint32_t flag = 0;		 //用于标志是否接收到数据，在中断函数中赋值

int main(void)
{
//	  //串口通讯测试代码
//	  u16 i= 0;
//	  BoardInit();
//	
//	  while(1)
//	  {
//			  printf("hhhhhhh%d\r\n",i++);
//				delay_ms(50);
//	  }
	
	
	  //CAN通信测试
	  u16 i = 0;
	  BoardInit();
	  CAN_Config();
	  printf("\r\n CAN test demo ,start!r\n");
	  printf("\r\n CAN test demo ,start!r\n");
	  while(1)
		{
			  printf("\r\n test %d :  \r\n",++i);
			  CAN_SetMsg();
			  HAL_CAN_Transmit_IT(&Can_Handle);
			  delay_ms(1000);
			  printf("\r\n已使用CAN发送数据包！\r\n");
		}
}

