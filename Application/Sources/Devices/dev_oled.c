#include "dev_oled.h"
#include "delay.h"
#include "dev_I2C.h"
#include "ASCII.h"

/**********************************************************************
*Function:  void OLED_HW_Init(void)
*Describe:  初始化IIC
*Return  :  无
**********************************************************************/
void OLED_HW_Init(void)
{
	IIC_Init();    //IIC初始化
}

/**********************************************************************
*Function:  void WriteCmd(uint8_t command)
*Describe:  向OLED写入命令
*Return  :  无
**********************************************************************/
void WriteCmd(uint8_t command)
{
    IIC_Start();
    IIC_Send_Byte(0x78);    //OLED地址
    IIC_Wait_Ack();
    IIC_Send_Byte(0x00);    //寄存器地址
    IIC_Wait_Ack();
    IIC_Send_Byte(command);
    IIC_Wait_Ack();
    IIC_Stop();
}

/**********************************************************************
*Function:  void WriteDat(uint8_t data)
*Describe:  向OLED写入数据
*Return  :  无
**********************************************************************/
void WriteDat(uint8_t data)
{
    IIC_Start();
    IIC_Send_Byte(0x78);    //OLED地址
    IIC_Wait_Ack();
    IIC_Send_Byte(0x40);    //寄存器地址
    IIC_Wait_Ack();
    IIC_Send_Byte(data);
    IIC_Wait_Ack();
    IIC_Stop();
}

/**********************************************************************
*Function:  void OLED_Init(void)
*Describe:  初始化OLED，使能各种配置
*Return  :  无
**********************************************************************/
void OLED_Init(void)
{
	OLED_HW_Init();

    delay_ms(100);    //这里的延时很重要

    WriteCmd(0xAE);     //display off
    WriteCmd(0x20);     //Set Memory Addressing Mode    
    WriteCmd(0x10);     //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    WriteCmd(0xb0);     //Set Page Start Address for Page Addressing Mode,0-7
    WriteCmd(0xc8); 	//Set COM Output Scan Direction
    WriteCmd(0x00); 	//---set low column address
    WriteCmd(0x10); 	//---set high column address
    WriteCmd(0x40); 	//--set start line address
    WriteCmd(0x81); 	//--set contrast control register
    WriteCmd(0xff); 	//亮度调节 0x00~0xff
    WriteCmd(0xa1); 	//--set segment re-map 0 to 127
    WriteCmd(0xa6); 	//--set normal display
    WriteCmd(0xa8); 	//--set multiplex ratio(1 to 64)
    WriteCmd(0x3F); 	//
    WriteCmd(0xa4); 	//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    WriteCmd(0xd3); 	//-set display offset
    WriteCmd(0x00); 	//-not offset
    WriteCmd(0xd5); 	//--set display clock divide ratio/oscillator frequency
    WriteCmd(0xf0); 	//--set divide ratio
    WriteCmd(0xd9); 	//--set pre-charge period
    WriteCmd(0x22); 	//
    WriteCmd(0xda); 	//--set com pins hardware configuration
    WriteCmd(0x12);
    WriteCmd(0xdb); 	//--set vcomh
    WriteCmd(0x20); 	//0x20,0.77xVcc
    WriteCmd(0x8d); 	//--set DC-DC enable
    WriteCmd(0x14); 	//
    WriteCmd(0xaf); 	//--turn on oled panel
}

/**********************************************************************
*Function:  void OLED_ON(void)
*Describe:  OLED上电唤醒
*Return  :  无
**********************************************************************/
void OLED_ON(void)
{
    WriteCmd(0X8D);  	//设置电荷泵
    WriteCmd(0X14);  	//开启电荷泵
    WriteCmd(0XAF);  	//OLED唤醒
}

/**********************************************************************
*Function:  void OLED_SetPos(uint8_t x, uint8_t y)
*Describe:  设置起始点坐标
*Return  :  无
**********************************************************************/
void OLED_SetPos(uint8_t x, uint8_t y)
{
    WriteCmd(0xb0+y);
    WriteCmd(((x&0xf0)>>4)|0x10);
    WriteCmd((x&0x0f)|0x01);
}


/**********************************************************************
*Function:  void OLED_Fill(uint8_t fill_Data)
*Describe:  全屏填充函数
*Return  :  无
**********************************************************************/
void OLED_Fill(uint8_t fill_Data)
{
    uint8_t m,n;
    for(m=0;m<8;m++)
    {
        WriteCmd(0xb0+m);       //page0-page1
        WriteCmd(0x00);         //low column start address
        WriteCmd(0x10);     	//high column start address
        for(n=0;n<128;n++)
		{
			WriteDat(fill_Data);
		}
    }
}

/**********************************************************************
*Function:  void OLED_CLS(void)
*Describe:  清屏函数
*Return  :  无
**********************************************************************/
void OLED_CLS(void)
{
    OLED_Fill(0x00);
}

/**********************************************************************
*Function:  void OLED_ShowStr(uint8_t x, uint8_t y, uint8_t ch[], uint8_t TextSize)
*Describe:  字符串打印函数
*Return  :  无
**********************************************************************/
void OLED_ShowStr(uint8_t x, uint8_t y, uint8_t ch[], uint8_t TextSize)
{
    uint8_t c = 0,i = 0,j = 0;
    switch(TextSize)
    {
		case 1:
        {
			while(ch[j] != '\0')
            {
                c = ch[j] - 32;
                if(x > 126)
                {
                    x = 0;
                    y++;
                }
                OLED_SetPos(x,y);
                for(i=0;i<6;i++)
					WriteDat(F6x8[c][i]);
                x += 6;
                j++;
            }
        }
		break;
        case 2:
        {
            while(ch[j] != '\0')
            {
                c = ch[j] - 32;
                if(x > 120)
                {
                    x = 0;
                    y++;
                }
                OLED_SetPos(x,y);
                for(i=0;i<8;i++)
                    WriteDat(F8X16[c*16+i]);
                OLED_SetPos(x,y+1);
                for(i=0;i<8;i++)
                    WriteDat(F8X16[c*16+i+8]);
                x += 8;
                j++;
            }
        }
		break;
    }
}


