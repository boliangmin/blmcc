#ifndef __IR_NEC_H
#define __IR_NEC_H
#include "sys.h"



#define NEC_PIN                 GPIO_PIN_4
#define NEC_GPIO_PORT           GPIOD
#define NEC_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOD_CLK_ENABLE()

void NEC_GPIO_Config(void);
void TiMer_Init(void);



#endif
