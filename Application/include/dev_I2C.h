#ifndef _DEV_I2C_H
#define _DEV_I2C_H



#include "stm32f4xx.h"



//SDA�ܽŶ���
#define	 IIC_SDA_PORT  GPIOH
#define  IIC_SDA_PIN   GPIO_PIN_5

//SCL�ܽŶ���
#define	 IIC_SCL_PORT  GPIOH
#define  IIC_SCL_PIN   GPIO_PIN_4

//IIC�ܽ�ʱ��ʹ��
#define  IIC_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOH_CLK_ENABLE()

//SDA�������ģʽ�л�
#define SDA_IN()  {GPIOH->MODER &= ~(3<<(5*2));GPIOH->MODER |= 0<<5*2;}	  //PH5����ģʽ
#define SDA_OUT() {GPIOH->MODER &= ~(3<<(5*2));GPIOH->MODER |= 1<<5*2;}   //PH5���ģʽ



/**********************************************************************
*Function:  void IIC_SDA_W(GPIO_PinState sta)
*Describe:  SDA�ܽ�д����
*Return  :  ��
**********************************************************************/
void IIC_SDA_W(uint8_t sta);

/**********************************************************************
*Function:  GPIO_PinState IIC_SDA_R(void)
*Describe:  SDA�ܽŶ�����
*Return  :  0\1--SDA����������
**********************************************************************/
GPIO_PinState IIC_SDA_R(void);

/**********************************************************************
*Function:  void IIC_SDA_W(GPIO_PinState sta)
*Describe:  SDA�ܽ�д����
*Return  :  ��
**********************************************************************/
void IIC_SCL_W(uint8_t sta);

/**********************************************************************
*Function:  void IIC_Init(void)
*Describe:  ��ʼ��IIC�ܽ�
*Return  :  ��
**********************************************************************/
void IIC_Init(void);

/**********************************************************************
*Function:  void IIC_Start(void)
*Describe:  ����IIC��ʼ�ź�
*Return  :  ��
**********************************************************************/
void IIC_Start(void);

/**********************************************************************
*Function:  void IIC_Stop(void)
*Describe:  ����IICֹͣ�ź�
*Return  :  ��
**********************************************************************/
void IIC_Stop(void);

/**********************************************************************
*Function:  uint8_t IIC_Wait_Ack(void)
*Describe:  �ȴ�Ӧ���źŵ���
*Return  :  1������Ӧ��ʧ��
*           0������Ӧ��ɹ�
**********************************************************************/
uint8_t IIC_Wait_Ack(void);

/**********************************************************************
*Function:  void IIC_Ack(void)
*Describe:  ����ACKӦ��
*Return  :  ��
**********************************************************************/
void IIC_Ack(void);

/**********************************************************************
*Function:  void IIC_NAck(void)
*Describe:  ������ACKӦ��
*Return  :  ��
**********************************************************************/	    
void IIC_NAck(void);

/**********************************************************************
*Function:  void IIC_Send_Byte(uint8_t txd)
*Describe:  IIC����һ���ֽ�
*Return  :  ��
**********************************************************************/		  
void IIC_Send_Byte(uint8_t txd);

/**********************************************************************
*Function:  uint8_t IIC_Read_Byte(unsigned char ack)
*Describe:  ��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
*Return  :  IIC�������ֽ�
**********************************************************************/	
uint8_t IIC_Read_Byte(uint8_t ack);



#endif


