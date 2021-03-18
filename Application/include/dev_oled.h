#ifndef __DEV_OLED_H
#define __DEV_OLED_H



#include "stm32f4xx.h"
#include "dev_I2C.h"



/**********************************************************************
*Function:  void OLED_HW_Init(void)
*Describe:  初始化IIC
*Return  :  无
**********************************************************************/
void OLED_HW_Init(void);

/**********************************************************************
*Function:  void WriteCmd(uint8_t command)
*Describe:  向OLED写入命令
*Return  :  无
**********************************************************************/
void WriteCmd(uint8_t command);

/**********************************************************************
*Function:  void WriteDat(uint8_t data)
*Describe:  向OLED写入数据
*Return  :  无
**********************************************************************/
void WriteDat(uint8_t data);

/**********************************************************************
*Function:  void OLED_Init(void)
*Describe:  初始化OLED，使能各种配置
*Return  :  无
**********************************************************************/
void OLED_Init(void);

/**********************************************************************
*Function:  void OLED_ON(void)
*Describe:  OLED上电唤醒
*Return  :  无
**********************************************************************/
void OLED_ON(void);

/**********************************************************************
*Function:  void OLED_SetPos(uint8_t x, uint8_t y)
*Describe:  设置起始点坐标
*Return  :  无
**********************************************************************/
void OLED_SetPos(uint8_t x, uint8_t y);

/**********************************************************************
*Function:  void OLED_Fill(uint8_t fill_Data)
*Describe:  全屏填充函数
*Return  :  无
**********************************************************************/
void OLED_Fill(uint8_t fill_Data);

/**********************************************************************
*Function:  void OLED_CLS(void)
*Describe:  清屏函数
*Return  :  无
**********************************************************************/
void OLED_CLS(void);

/**********************************************************************
*Function:  void OLED_ShowStr(uint8_t x, uint8_t y, uint8_t ch[], uint8_t TextSize)
*Describe:  字符串打印函数
*Return  :  无
**********************************************************************/
void OLED_ShowStr(uint8_t x, uint8_t y, uint8_t ch[], uint8_t TextSize);



#endif


