#ifndef __DEV_CAN_H
#define __DEV_CAN_H



#include "stm32f4xx.h"



extern CAN_HandleTypeDef Can_Handle;

/*CANͨ���ܽŶ���*/
#define CAN_RX_PIN                 GPIO_PIN_11
#define CAN_TX_PIN                 GPIO_PIN_12
#define CAN_TX_GPIO_PORT           GPIOA
#define CAN_RX_GPIO_PORT           GPIOA
#define CAN_TX_GPIO_CLK_ENABLE()   __GPIOA_CLK_ENABLE()
#define CAN_RX_GPIO_CLK_ENABLE()   __GPIOA_CLK_ENABLE()
#define CAN_AF_PORT                GPIO_AF9_CAN1 
/*CANͨ��ʱ�ӡ��ж϶���*/
#define CANx                       CAN1
#define CAN_CLK_ENABLE()           __CAN1_CLK_ENABLE()
#define CAN_RX_IRQ				   CAN1_RX0_IRQn
#define CAN_RX_IRQHandler		   CAN1_RX0_IRQHandler



/**********************************************************************
*Function:  static void CAN_GPIO_Config(void)
*Describe:  ��ʼ��CANͨ���ܽ�
*Return  :  ��
**********************************************************************/
static void CAN_GPIO_Config(void);

/**********************************************************************
*Function:  static void CAN_NVIC_Config(void)
*Describe:  ����CAN�ж����ȼ�
*Return  :  ��
**********************************************************************/
static void CAN_NVIC_Config(void);

/**********************************************************************
*Function:  static uint8_t CAN_Mode_Config(void)
*Describe:  CANͨ�Ų�������
*Return  :  0--��ʼ���ɹ�
*			1--��ʼ��ʧ��
**********************************************************************/
static uint8_t CAN_Mode_Config(void);

/**********************************************************************
*Function:  static void CAN_Filter_Config(void)
*Describe:  CANɸѡ������
*Return  :  ��
**********************************************************************/
static void CAN_Filter_Config(void);

/**********************************************************************
*Function:  void CAN_Config(void)
*Describe:  CAN��ʼ��
*Return  :  ��
**********************************************************************/
void CAN_Config(void);

/**********************************************************************
*Function:  void Init_RxMes(void)
*Describe:  ��ʼ��CAN�������ݽṹ��
*Return  :  ��
**********************************************************************/
void CAN_SetMsg(uint16_t stdId,uint16_t buff[8]);

/**********************************************************************
*Function:  void CAN_SetMsg(uint16_t stdId,uint16_t buff[8])
*Describe:  ����һ֡CAN����
*Return  :  ��
**********************************************************************/
void Init_RxMes(void);

/**********************************************************************
*Function:  void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
*Describe:  CAN�����жϻص�����
*Return  :  ��
**********************************************************************/
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan);

/**********************************************************************
*Function:  void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
*Describe:  CAN���մ���ص�����
*Return  :  ��
**********************************************************************/
void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan);



#endif


