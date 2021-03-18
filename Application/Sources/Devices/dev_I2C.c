#include "dev_I2C.h"
#include "delay.h"


/**********************************************************************
*Function:  void IIC_SDA_W(GPIO_PinState sta)
*Describe:  SDA管脚写函数
*Return  :  无
**********************************************************************/
void IIC_SDA_W(uint8_t sta)
{
	switch(sta)
	{
		case 0:
			HAL_GPIO_WritePin(IIC_SDA_PORT,IIC_SDA_PIN,GPIO_PIN_RESET);
		break;

		case 1:
			HAL_GPIO_WritePin(IIC_SDA_PORT,IIC_SDA_PIN,GPIO_PIN_SET);
		break;

		default:
			//ERROR
		break;
	}
}

/**********************************************************************
*Function:  GPIO_PinState IIC_SDA_R(void)
*Describe:  SDA管脚读函数
*Return  :  0\1--SDA读到的数据
**********************************************************************/
GPIO_PinState IIC_SDA_R(void)
{
	return HAL_GPIO_ReadPin(IIC_SDA_PORT, IIC_SDA_PIN);
}

/**********************************************************************
*Function:  void IIC_SCL_W(GPIO_PinState sta)
*Describe:  SDA管脚写函数
*Return  :  无
**********************************************************************/
void IIC_SCL_W(uint8_t sta)
{
	switch(sta)
	{
		case 0:
			HAL_GPIO_WritePin(IIC_SCL_PORT,IIC_SCL_PIN,GPIO_PIN_RESET);
		break;

		case 1:
			HAL_GPIO_WritePin(IIC_SCL_PORT,IIC_SCL_PIN,GPIO_PIN_SET);
		break;

		default:
			//ERROR
		break;
	}
}

/**********************************************************************
*Function:  void IIC_Init(void)
*Describe:  初始化IIC管脚
*Return  :  无
**********************************************************************/
void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

	//时钟初始化
    IIC_GPIO_CLK_ENABLE();

    //SDA管脚初始化
    GPIO_Initure.Pin = IIC_SDA_PIN;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;      //推挽输出
    GPIO_Initure.Pull = GPIO_PULLUP;              //上拉
    GPIO_Initure.Speed = GPIO_SPEED_FAST;         //快速
    HAL_GPIO_Init(IIC_SDA_PORT,&GPIO_Initure);

	//SCL管脚初始化
	GPIO_Initure.Pin = IIC_SCL_PIN;
	HAL_GPIO_Init(IIC_SCL_PORT,&GPIO_Initure);

	IIC_SDA_W(1);
	IIC_SCL_W(1);
}

/**********************************************************************
*Function:  void IIC_Start(void)
*Describe:  产生IIC起始信号
*Return  :  无
**********************************************************************/
void IIC_Start(void)
{
	SDA_OUT(); 			//SDA输出模式
	IIC_SDA_W(1);
	IIC_SCL_W(1);
	delay_us(4);
 	IIC_SDA_W(0);       //START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_W(0);       //钳住I2C总线，准备发送或接收数据 
}

/**********************************************************************
*Function:  void IIC_Stop(void)
*Describe:  产生IIC停止信号
*Return  :  无
**********************************************************************/
void IIC_Stop(void)
{
	SDA_OUT();            //sda线输出
	IIC_SCL_W(0);
	IIC_SDA_W(0);         //STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_W(1); 
	delay_us(4);			
	IIC_SDA_W(1);         //发送I2C总线结束信号				   	
}

/**********************************************************************
*Function:  uint8_t IIC_Wait_Ack(void)
*Describe:  等待应答信号到来
*Return  :  1，接收应答失败
*           0，接收应答成功
**********************************************************************/
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();                    //SDA设置为输入  
	IIC_SDA_W(1);
	delay_us(1);	   
	IIC_SCL_W(1);
	delay_us(1);	 
	while(IIC_SDA_R())
	{
		ucErrTime++;
		if(ucErrTime > 250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_W(0);//时钟输出0 	   
	return 0;  
}

/**********************************************************************
*Function:  void IIC_Ack(void)
*Describe:  产生ACK应答
*Return  :  无
**********************************************************************/
void IIC_Ack(void)
{
	IIC_SCL_W(0);
	SDA_OUT();
	IIC_SDA_W(0);
	delay_us(2);
	IIC_SCL_W(1);
	delay_us(2);
	IIC_SCL_W(0);
}

/**********************************************************************
*Function:  void IIC_NAck(void)
*Describe:  不产生ACK应答
*Return  :  无
**********************************************************************/	    
void IIC_NAck(void)
{
	IIC_SCL_W(0);
	SDA_OUT();
	IIC_SDA_W(1);
	delay_us(2);
	IIC_SCL_W(1);
	delay_us(2);
	IIC_SCL_W(0);
}

/**********************************************************************
*Function:  void IIC_Send_Byte(uint8_t txd)
*Describe:  IIC发送一个字节
*Return  :  无
**********************************************************************/		  
void IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
	SDA_OUT();
    IIC_SCL_W(0);                    //拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
		IIC_SDA_W((txd & 0x80)>>7);
		txd <<= 1;
		delay_us(2);                 //对TEA5767这三个延时都是必须的
		IIC_SCL_W(1);
		delay_us(2);
		IIC_SCL_W(0);
		delay_us(2);
    }
}

/**********************************************************************
*Function:  uint8_t IIC_Read_Byte(unsigned char ack)
*Describe:  读1个字节，ack=1时，发送ACK，ack=0，发送nACK
*Return  :  IIC读到的字节
**********************************************************************/	
uint8_t IIC_Read_Byte(uint8_t ack)
{
	uint8_t i,receive=0;
	SDA_IN();
	for(i=0;i<8;i++ )
	{
		IIC_SCL_W(0);
		delay_us(2);
		IIC_SCL_W(1);
		receive <<= 1;
		if(IIC_SDA_R())
			receive++;   
		delay_us(1); 
	}
	if (!ack)
		IIC_NAck();       //发送nACK
	else
		IIC_Ack();        //发送ACK
	return receive;
}


