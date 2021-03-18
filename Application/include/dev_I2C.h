#ifndef _DEV_I2C_H
#define _DEV_I2C_H



#include "stm32f4xx.h"



//SDA管脚定义
#define	 IIC_SDA_PORT  GPIOH
#define  IIC_SDA_PIN   GPIO_PIN_5

//SCL管脚定义
#define	 IIC_SCL_PORT  GPIOH
#define  IIC_SCL_PIN   GPIO_PIN_4

//IIC管脚时钟使能
#define  IIC_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOH_CLK_ENABLE()

//SDA输入输出模式切换
#define SDA_IN()  {GPIOH->MODER &= ~(3<<(5*2));GPIOH->MODER |= 0<<5*2;}	  //PH5输入模式
#define SDA_OUT() {GPIOH->MODER &= ~(3<<(5*2));GPIOH->MODER |= 1<<5*2;}   //PH5输出模式



/**********************************************************************
*Function:  void IIC_SDA_W(GPIO_PinState sta)
*Describe:  SDA管脚写函数
*Return  :  无
**********************************************************************/
void IIC_SDA_W(uint8_t sta);

/**********************************************************************
*Function:  GPIO_PinState IIC_SDA_R(void)
*Describe:  SDA管脚读函数
*Return  :  0\1--SDA读到的数据
**********************************************************************/
GPIO_PinState IIC_SDA_R(void);

/**********************************************************************
*Function:  void IIC_SDA_W(GPIO_PinState sta)
*Describe:  SDA管脚写函数
*Return  :  无
**********************************************************************/
void IIC_SCL_W(uint8_t sta);

/**********************************************************************
*Function:  void IIC_Init(void)
*Describe:  初始化IIC管脚
*Return  :  无
**********************************************************************/
void IIC_Init(void);

/**********************************************************************
*Function:  void IIC_Start(void)
*Describe:  产生IIC起始信号
*Return  :  无
**********************************************************************/
void IIC_Start(void);

/**********************************************************************
*Function:  void IIC_Stop(void)
*Describe:  产生IIC停止信号
*Return  :  无
**********************************************************************/
void IIC_Stop(void);

/**********************************************************************
*Function:  uint8_t IIC_Wait_Ack(void)
*Describe:  等待应答信号到来
*Return  :  1，接收应答失败
*           0，接收应答成功
**********************************************************************/
uint8_t IIC_Wait_Ack(void);

/**********************************************************************
*Function:  void IIC_Ack(void)
*Describe:  产生ACK应答
*Return  :  无
**********************************************************************/
void IIC_Ack(void);

/**********************************************************************
*Function:  void IIC_NAck(void)
*Describe:  不产生ACK应答
*Return  :  无
**********************************************************************/	    
void IIC_NAck(void);

/**********************************************************************
*Function:  void IIC_Send_Byte(uint8_t txd)
*Describe:  IIC发送一个字节
*Return  :  无
**********************************************************************/		  
void IIC_Send_Byte(uint8_t txd);

/**********************************************************************
*Function:  uint8_t IIC_Read_Byte(unsigned char ack)
*Describe:  读1个字节，ack=1时，发送ACK，ack=0，发送nACK
*Return  :  IIC读到的字节
**********************************************************************/	
uint8_t IIC_Read_Byte(uint8_t ack);



#endif


