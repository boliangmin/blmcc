#include "board_init.h"
#include "dev_oled.h"
#include "delay.h"

__IO uint32_t can_rx_flag = 0;		 //用于标志是否接收到数据，在中断函数中赋值
//unsigned char wake_flag = 0;




int main(void)
{
	SystemClock_Config();
	delay_init(180);

	OLED_Init();
	OLED_CLS();

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
//	  BoardInit();
//	  CAN_Config();
//	  while(1)
//		{
//			  CanRecvService();
//		}


//			//NEC发送测试
//			BoardInit();
//			NEC_GPIO_Config();	
//			TiMer_Init();
//			while(1)
//			{
//					
//			}


//		//EEPROM读写测试
//		#define SIZE sizeof(TEXT_Buffer)
//		const u8 TEXT_Buffer[]={"blmcc eeprom test"};
//		u16 i;
//		u8 datatemp[SIZE];
//		
//	  BoardInit();
//		AT24CXX_Init();
//		
//		while(AT24CXX_Check())    //检测不到24c02
//	  {
//		    delay_ms(500);
//		    printf("can't find 24c02,Please Check!      ");
//		    delay_ms(500);
//	  }
//		
//		while(1)
//	  {

//			printf("write start!\r\n");
//			AT24CXX_Write(0,(u8*)TEXT_Buffer,SIZE);
//			printf("write finish\r\n\r\n");
//			
//			printf("read start!\r\n");
//			AT24CXX_Read(0,datatemp,SIZE);
//			printf("read finish!\r\n\r\n");
//			
//			for(i=0;i<30;i++)
//			{
//				printf("%c",datatemp[i]);
//			}
//			printf("\r\n---------------------\r\n");
//		}

//	LED_Init();
//    WKUP_Init();	                //待机唤醒初始化

	while(1)
	{
		OLED_ShowStr(0,0,"blm",1);
		OLED_ShowStr(0,1,"0123456789",1);
		OLED_ShowStr(0,2,"come on!",1);
		delay_ms(10000);
		OLED_CLS();
		delay_ms(1000);
		
//		if(wake_flag == 1)
//		{
//			delay_ms(2000);
//			if(wake_flag == 1)
//			{
//				Sys_Enter_Standby();
//			}
//		}
//		LED0 = !LED0;
//		delay_ms(500);              //延时250ms
	}
}


