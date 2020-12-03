#include "IR_NEC.h"

TIM_HandleTypeDef TIM3_Handler;

void NEC_GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_Initure;
	
		NEC_GPIO_CLK_ENABLE();
    GPIO_Initure.Pin   = NEC_PIN;                 //PD4
    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;     //推挽输出
    GPIO_Initure.Pull  = GPIO_PULLUP;             //上拉
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;         //高速
    HAL_GPIO_Init(NEC_GPIO_PORT,&GPIO_Initure);
		
	  HAL_GPIO_WritePin(NEC_GPIO_PORT, NEC_PIN, GPIO_PIN_RESET);      //初始输出为0
}


void TiMer_Init(void)
{
		__HAL_RCC_TIM3_CLK_ENABLE();

		HAL_NVIC_SetPriority(TIM3_IRQn,0,3);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);

    TIM3_Handler.Instance = TIM3;                                     //通用定时器3,使用时钟APB1,时钟频率为45MHz
    TIM3_Handler.Init.Prescaler = 20 - 1;                             //45 / 20 / 60 = 38KHz
    TIM3_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM3_Handler.Init.Period = 60 - 1;                                //自动装载值
    TIM3_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;         //时钟分频因子
    HAL_TIM_Base_Init(&TIM3_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM3_Handler);                             //使能定时器3和定时器3更新中断：TIM_IT_UPDATE   
}


void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM3_Handler);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&TIM3_Handler))
    {
        HAL_GPIO_TogglePin(NEC_GPIO_PORT, NEC_PIN);
    }
}



