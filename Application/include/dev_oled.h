#ifndef __DEV_OLED_H
#define __DEV_OLED_H



#include "stm32f4xx.h"
#include "dev_I2C.h"



/**********************************************************************
*Function:  void OLED_HW_Init(void)
*Describe:  ��ʼ��IIC
*Return  :  ��
**********************************************************************/
void OLED_HW_Init(void);

/**********************************************************************
*Function:  void WriteCmd(uint8_t command)
*Describe:  ��OLEDд������
*Return  :  ��
**********************************************************************/
void WriteCmd(uint8_t command);

/**********************************************************************
*Function:  void WriteDat(uint8_t data)
*Describe:  ��OLEDд������
*Return  :  ��
**********************************************************************/
void WriteDat(uint8_t data);

/**********************************************************************
*Function:  void OLED_Init(void)
*Describe:  ��ʼ��OLED��ʹ�ܸ�������
*Return  :  ��
**********************************************************************/
void OLED_Init(void);

/**********************************************************************
*Function:  void OLED_ON(void)
*Describe:  OLED�ϵ绽��
*Return  :  ��
**********************************************************************/
void OLED_ON(void);

/**********************************************************************
*Function:  void OLED_SetPos(uint8_t x, uint8_t y)
*Describe:  ������ʼ������
*Return  :  ��
**********************************************************************/
void OLED_SetPos(uint8_t x, uint8_t y);

/**********************************************************************
*Function:  void OLED_Fill(uint8_t fill_Data)
*Describe:  ȫ����亯��
*Return  :  ��
**********************************************************************/
void OLED_Fill(uint8_t fill_Data);

/**********************************************************************
*Function:  void OLED_CLS(void)
*Describe:  ��������
*Return  :  ��
**********************************************************************/
void OLED_CLS(void);

/**********************************************************************
*Function:  void OLED_ShowStr(uint8_t x, uint8_t y, uint8_t ch[], uint8_t TextSize)
*Describe:  �ַ�����ӡ����
*Return  :  ��
**********************************************************************/
void OLED_ShowStr(uint8_t x, uint8_t y, uint8_t ch[], uint8_t TextSize);



#endif


