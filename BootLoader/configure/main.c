#include "sys.h"
#include "configure.h"
#include "delay.h"
#include "can.h"

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
	  BoardInit();
	  CAN_Config();
	  printf("\r\n CAN test demo ,start!�\r\n");
	  printf("\r\n CAN test demo ,start!�\r\n");
	  while(1)
		{
			  printf("\r\n test %d :  \r\n",++i);
			  CAN_SetMsg();
			  HAL_CAN_Transmit_IT(&Can_Handle);
			  delay_ms(1000);
			  printf("\r\n��ʹ��CAN�������ݰ���\r\n");
		}
}

