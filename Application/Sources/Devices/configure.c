#include "sys.h"
#include "can.h"
#include "delay.h"
#include "usart.h"
#include "rtc.h"

//void CanInit()
//{
//	  CAN1_Mode_Init(CAN_SJW_1TQ,CAN_BS2_6TQ,CAN_BS1_8TQ,6,CAN_MODE_LOOPBACK);
//}


void BoardInit()
{
	HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,7);   //����ʱ��,25 / 25 * 360 / 2 = 180Mhz
    delay_init(180);                //��ʼ����ʱ����
    uart_init(115200);              //��ʼ��USART
}

void Sys_Enter_Standby(void)
{
    __HAL_RCC_AHB1_FORCE_RESET();       //��λ����IO�� 
   
	__HAL_RCC_PWR_CLK_ENABLE();         //ʹ��PWRʱ��
    __HAL_RCC_BACKUPRESET_FORCE();      //��λ��������
    HAL_PWR_EnableBkUpAccess();         //���������ʹ��  
	
	//STM32F4,��������RTC����жϺ�,�����ȹر�RTC�ж�,�����жϱ�־λ,Ȼ����������
	//RTC�ж�,�ٽ������ģʽ�ſ�����������,�����������.	
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
    __HAL_RTC_WRITEPROTECTION_DISABLE(&RTC_Handler);//�ر�RTCд����
    
    //�ر�RTC����жϣ�������RTCʵ�����
    __HAL_RTC_WAKEUPTIMER_DISABLE_IT(&RTC_Handler,RTC_IT_WUT);
    __HAL_RTC_TIMESTAMP_DISABLE_IT(&RTC_Handler,RTC_IT_TS);
    __HAL_RTC_ALARM_DISABLE_IT(&RTC_Handler,RTC_IT_ALRA|RTC_IT_ALRB);
    
    //���RTC����жϱ�־λ
    __HAL_RTC_ALARM_CLEAR_FLAG(&RTC_Handler,RTC_FLAG_ALRAF|RTC_FLAG_ALRBF);
    __HAL_RTC_TIMESTAMP_CLEAR_FLAG(&RTC_Handler,RTC_FLAG_TSF); 
    __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&RTC_Handler,RTC_FLAG_WUTF);
    
    __HAL_RCC_BACKUPRESET_RELEASE();                    //��������λ����
    __HAL_RTC_WRITEPROTECTION_ENABLE(&RTC_Handler);     //ʹ��RTCд����
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);                  //���Wake_UP��־
	
		
    HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);           //����WKUP���ڻ���
    HAL_PWR_EnterSTANDBYMode();                         //�������ģʽ     
}
