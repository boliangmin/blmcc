#include "sys.h"
#include "configure.h"
#include "delay.h"
#include "can.h"
#include "eeprom.h"
#include "recvhandle.h"
#include "IR_NEC.h"
#include "led.h"

__IO uint32_t flag = 0;		 //���ڱ�־�Ƿ���յ����ݣ����жϺ����и�ֵ
unsigned char wake_flag = 0;


void WKUP_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_GPIOH_CLK_ENABLE();			  //����GPIOAʱ��
	
	GPIO_Initure.Pin = GPIO_PIN_2;             //PA0
	GPIO_Initure.Mode = GPIO_MODE_IT_FALLING;  //�ж�,������
	GPIO_Initure.Pull = GPIO_PULLUP;           //����
	HAL_GPIO_Init(GPIOH,&GPIO_Initure);
	
	HAL_NVIC_SetPriority(EXTI2_IRQn,2,0);
	HAL_NVIC_EnableIRQ(EXTI2_IRQn);
}

void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);//�����жϴ����ú���
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(100);      //����
	
	if(GPIO_PIN_2)
	{
		wake_flag = !wake_flag;
	}
}


int main(void)
{
//	  //����ͨѶ���Դ���
//	  u16 i= 0;
//	  BoardInit();
//	
//	  while(1)
//	  {
//			  printf("hhhhhhh%d\r\n",i++);
//				delay_ms(50);
//	  }


//	  //CANͨ�Ų���
//	  BoardInit();
//	  CAN_Config();
//	  while(1)
//		{
//			  CanRecvService();
//		}


//			//NEC���Ͳ���
			BoardInit();
//			NEC_GPIO_Config();	
//			TiMer_Init();
//			while(1)
//			{
//					
//			}


//		//EEPROM��д����
//		#define SIZE sizeof(TEXT_Buffer)
//		const u8 TEXT_Buffer[]={"blmcc eeprom test"};
//		u16 i;
//		u8 datatemp[SIZE];
//		
//	  BoardInit();
//		AT24CXX_Init();
//		
//		while(AT24CXX_Check())    //��ⲻ��24c02
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
    WKUP_Init();	                //�������ѳ�ʼ��

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
		delay_ms(500);              //��ʱ250ms
	}
}


