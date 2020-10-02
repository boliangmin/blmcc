#include "sys.h"
#include "configure.h"
#include "delay.h"
#include "can.h"
#include "eeprom.h"

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
	
	
//	  //CAN通信测试
//	  u16 i = 0;
//	  BoardInit();
//	  CAN_Config();
//	  printf("\r\n CAN test demo ,start!r\n");
//	  printf("\r\n CAN test demo ,start!r\n");
//	  while(1)
//		{
//			  printf("\r\n test %d :  \r\n",++i);
//			  CAN_SetMsg();
//			  HAL_CAN_Transmit_IT(&Can_Handle);
//			  delay_ms(1000);
//			  printf("\r\n已使用CAN发送数据包！\r\n");
//		}
		
		//EEPROM读写测试
		#define SIZE sizeof(TEXT_Buffer)
		const u8 TEXT_Buffer[]={"blmcc eeprom test"};
		u16 i;
		u8 datatemp[SIZE];
		
	  BoardInit();
		AT24CXX_Init();
		
		while(AT24CXX_Check())    //检测不到24c02
	  {
		    delay_ms(500);
		    printf("can't find 24c02,Please Check!      ");
		    delay_ms(500);
	  }
		
		while(1)
	  {

			printf("write start!\r\n");
			AT24CXX_Write(0,(u8*)TEXT_Buffer,SIZE);
			printf("write finish\r\n\r\n");
			
			printf("read start!\r\n");
			AT24CXX_Read(0,datatemp,SIZE);
			printf("read finish!\r\n\r\n");
			
			for(i=0;i<30;i++)
			{
				printf("%c",datatemp[i]);
			}
			printf("\r\n---------------------\r\n");
		}
}

