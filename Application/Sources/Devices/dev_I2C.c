#include "dev_I2C.h"
#include "delay.h"


/**********************************************************************
*Function:  void IIC_SDA_W(GPIO_PinState sta)
*Describe:  SDA�ܽ�д����
*Return  :  ��
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
*Describe:  SDA�ܽŶ�����
*Return  :  0\1--SDA����������
**********************************************************************/
GPIO_PinState IIC_SDA_R(void)
{
	return HAL_GPIO_ReadPin(IIC_SDA_PORT, IIC_SDA_PIN);
}

/**********************************************************************
*Function:  void IIC_SCL_W(GPIO_PinState sta)
*Describe:  SDA�ܽ�д����
*Return  :  ��
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
*Describe:  ��ʼ��IIC�ܽ�
*Return  :  ��
**********************************************************************/
void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

	//ʱ�ӳ�ʼ��
    IIC_GPIO_CLK_ENABLE();

    //SDA�ܽų�ʼ��
    GPIO_Initure.Pin = IIC_SDA_PIN;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;      //�������
    GPIO_Initure.Pull = GPIO_PULLUP;              //����
    GPIO_Initure.Speed = GPIO_SPEED_FAST;         //����
    HAL_GPIO_Init(IIC_SDA_PORT,&GPIO_Initure);

	//SCL�ܽų�ʼ��
	GPIO_Initure.Pin = IIC_SCL_PIN;
	HAL_GPIO_Init(IIC_SCL_PORT,&GPIO_Initure);

	IIC_SDA_W(1);
	IIC_SCL_W(1);
}

/**********************************************************************
*Function:  void IIC_Start(void)
*Describe:  ����IIC��ʼ�ź�
*Return  :  ��
**********************************************************************/
void IIC_Start(void)
{
	SDA_OUT(); 			//SDA���ģʽ
	IIC_SDA_W(1);
	IIC_SCL_W(1);
	delay_us(4);
 	IIC_SDA_W(0);       //START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_W(0);       //ǯסI2C���ߣ�׼�����ͻ�������� 
}

/**********************************************************************
*Function:  void IIC_Stop(void)
*Describe:  ����IICֹͣ�ź�
*Return  :  ��
**********************************************************************/
void IIC_Stop(void)
{
	SDA_OUT();            //sda�����
	IIC_SCL_W(0);
	IIC_SDA_W(0);         //STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_W(1); 
	delay_us(4);			
	IIC_SDA_W(1);         //����I2C���߽����ź�				   	
}

/**********************************************************************
*Function:  uint8_t IIC_Wait_Ack(void)
*Describe:  �ȴ�Ӧ���źŵ���
*Return  :  1������Ӧ��ʧ��
*           0������Ӧ��ɹ�
**********************************************************************/
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();                    //SDA����Ϊ����  
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
	IIC_SCL_W(0);//ʱ�����0 	   
	return 0;  
}

/**********************************************************************
*Function:  void IIC_Ack(void)
*Describe:  ����ACKӦ��
*Return  :  ��
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
*Describe:  ������ACKӦ��
*Return  :  ��
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
*Describe:  IIC����һ���ֽ�
*Return  :  ��
**********************************************************************/		  
void IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
	SDA_OUT();
    IIC_SCL_W(0);                    //����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
		IIC_SDA_W((txd & 0x80)>>7);
		txd <<= 1;
		delay_us(2);                 //��TEA5767��������ʱ���Ǳ����
		IIC_SCL_W(1);
		delay_us(2);
		IIC_SCL_W(0);
		delay_us(2);
    }
}

/**********************************************************************
*Function:  uint8_t IIC_Read_Byte(unsigned char ack)
*Describe:  ��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
*Return  :  IIC�������ֽ�
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
		IIC_NAck();       //����nACK
	else
		IIC_Ack();        //����ACK
	return receive;
}


