#ifndef __CAN_H
#define __CAN_H
#include "sys.h"


extern CAN_HandleTypeDef Can_Handle;

#define CANx                       CAN1
#define CAN_CLK_ENABLE()           __CAN1_CLK_ENABLE()
#define CAN_RX_IRQ				         CAN1_RX0_IRQn
#define CAN_RX_IRQHandler		       CAN1_RX0_IRQHandler

#define CAN_RX_PIN                 GPIO_PIN_11
#define CAN_TX_PIN                 GPIO_PIN_12
#define CAN_TX_GPIO_PORT           GPIOA
#define CAN_RX_GPIO_PORT           GPIOA
#define CAN_TX_GPIO_CLK_ENABLE()   __GPIOA_CLK_ENABLE()
#define CAN_RX_GPIO_CLK_ENABLE()   __GPIOA_CLK_ENABLE()
#define CAN_AF_PORT                GPIO_AF9_CAN1 


static void CAN_GPIO_Config(void);
static void CAN_NVIC_Config(void);
static void CAN_Mode_Config(void);
static void CAN_Filter_Config(void);
void CAN_Config(void);

void CAN_SetMsg(void);
void Init_RxMes(void);

#endif
