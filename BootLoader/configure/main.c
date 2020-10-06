#include "sys.h"
#include "configure.h"
#include "delay.h"
#include "can.h"
#include "eeprom.h"

__IO uint32_t flag = 0;		 //���ڱ�־�Ƿ���յ����ݣ����жϺ����и�ֵ

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
	
	
	  //CANͨ�Ų���
	  u16 i = 0;
	  u16 res;
	  BoardInit();
	  CAN_Config();
	  printf("CAN test demo ,start!�\\r\n");
	  while(1)
		{
			  printf("test %d :  \r\n",++i);
			  CAN_SetMsg();
			  res = HAL_CAN_Transmit_IT(&Can_Handle);
			  printf("send result: %d \r\n",res);
			  delay_ms(1000);
			  printf("��ʹ��CAN�������ݰ���\r\n\r\n");
				if(flag==1)
		    {
    	      printf("\r\nCAN���յ����ݣ�\r\n");
					  for(i=0;i<8;i++)
					  {
							  printf("%c",Can_Handle.pRxMsg->Data[i]);
					  }
						printf("\r\n\r\n");
			      flag=0;
			      HAL_Delay(100);
		    }
		}

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
}

