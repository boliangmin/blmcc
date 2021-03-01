#include "sys.h"
#include "configure.h"
#include "delay.h"
#include "can.h"
#include "eeprom.h"
#include "recvhandle.h"
#include "IR_NEC.h"
#include "led.h"

__IO uint32_t flag = 0;		 //用于标志是否接收到数据，在中断函数中赋值
unsigned char wake_flag = 0;


void WKUP_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_GPIOH_CLK_ENABLE();			  //开启GPIOA时钟
	
	GPIO_Initure.Pin = GPIO_PIN_2;             //PA0
	GPIO_Initure.Mode = GPIO_MODE_IT_FALLING;  //中断,上升沿
	GPIO_Initure.Pull = GPIO_PULLUP;           //下拉
	HAL_GPIO_Init(GPIOH,&GPIO_Initure);
	
	HAL_NVIC_SetPriority(EXTI2_IRQn,2,0);
	HAL_NVIC_EnableIRQ(EXTI2_IRQn);
}

void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);//调用中断处理公用函数
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(100);      //消抖
	
	if(GPIO_PIN_2)
	{
		wake_flag = !wake_flag;
	}
}


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
//	  BoardInit();
//	  CAN_Config();
//	  while(1)
//		{
//			  CanRecvService();
//		}


//			//NEC发送测试
			BoardInit();
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

	LED_Init();
    WKUP_Init();	                //待机唤醒初始化

	while(1)
	{
		if(wake_flag == 1)
		{
			delay_ms(2000);
			if(wake_flag == 1)
			{
				Sys_Enter_Standby();
			}
		}
		LED0 = !LED0;
		delay_ms(500);              //延时250ms
	}
}


