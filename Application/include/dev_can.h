#ifndef __DEV_CAN_H
#define __DEV_CAN_H



#include "stm32f4xx.h"



extern CAN_HandleTypeDef Can_Handle;

/*CAN通道管脚定义*/
#define CAN_RX_PIN                 GPIO_PIN_11
#define CAN_TX_PIN                 GPIO_PIN_12
#define CAN_TX_GPIO_PORT           GPIOA
#define CAN_RX_GPIO_PORT           GPIOA
#define CAN_TX_GPIO_CLK_ENABLE()   __GPIOA_CLK_ENABLE()
#define CAN_RX_GPIO_CLK_ENABLE()   __GPIOA_CLK_ENABLE()
#define CAN_AF_PORT                GPIO_AF9_CAN1 
/*CAN通道时钟、中断定义*/
#define CANx                       CAN1
#define CAN_CLK_ENABLE()           __CAN1_CLK_ENABLE()
#define CAN_RX_IRQ				   CAN1_RX0_IRQn
#define CAN_RX_IRQHandler		   CAN1_RX0_IRQHandler



/**********************************************************************
*Function:  static void CAN_GPIO_Config(void)
*Describe:  初始化CAN通道管脚
*Return  :  无
**********************************************************************/
static void CAN_GPIO_Config(void);

/**********************************************************************
*Function:  static void CAN_NVIC_Config(void)
*Describe:  配置CAN中断优先级
*Return  :  无
**********************************************************************/
static void CAN_NVIC_Config(void);

/**********************************************************************
*Function:  static uint8_t CAN_Mode_Config(void)
*Describe:  CAN通信参数配置
*Return  :  0--初始化成功
*			1--初始化失败
**********************************************************************/
static uint8_t CAN_Mode_Config(void);

/**********************************************************************
*Function:  static void CAN_Filter_Config(void)
*Describe:  CAN筛选器配置
*Return  :  无
**********************************************************************/
static void CAN_Filter_Config(void);

/**********************************************************************
*Function:  void CAN_Config(void)
*Describe:  CAN初始化
*Return  :  无
**********************************************************************/
void CAN_Config(void);

/**********************************************************************
*Function:  void Init_RxMes(void)
*Describe:  初始化CAN接收数据结构体
*Return  :  无
**********************************************************************/
void CAN_SetMsg(uint16_t stdId,uint16_t buff[8]);

/**********************************************************************
*Function:  void CAN_SetMsg(uint16_t stdId,uint16_t buff[8])
*Describe:  发送一帧CAN数据
*Return  :  无
**********************************************************************/
void Init_RxMes(void);

/**********************************************************************
*Function:  void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
*Describe:  CAN接收中断回调函数
*Return  :  无
**********************************************************************/
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan);

/**********************************************************************
*Function:  void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
*Describe:  CAN接收错误回调函数
*Return  :  无
**********************************************************************/
void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan);



#endif


