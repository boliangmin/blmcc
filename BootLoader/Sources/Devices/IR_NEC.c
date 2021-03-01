#include "IR_NEC.h"

unsigned char itflag = 1;
unsigned int cnt = 0;

TIM_HandleTypeDef TIM2_Handler;
TIM_HandleTypeDef TIM3_Handler;

void NEC_GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_Initure;
	
		NEC_GPIO_CLK_ENABLE();
    GPIO_Initure.Pin   = NEC_PIN | GPIO_PIN_6;                 //PD4
    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;     //推挽输出
    GPIO_Initure.Pull  = GPIO_PULLUP;             //上拉
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;         //高速
    HAL_GPIO_Init(NEC_GPIO_PORT,&GPIO_Initure);

		
	  HAL_GPIO_WritePin(NEC_GPIO_PORT, NEC_PIN, GPIO_PIN_SET);      //初始输出为0
		HAL_GPIO_WritePin(NEC_GPIO_PORT, GPIO_PIN_6, GPIO_PIN_RESET);
}

void TiMer_Init(void)
{
		__HAL_RCC_TIM2_CLK_ENABLE();
		__HAL_RCC_TIM3_CLK_ENABLE();

		HAL_NVIC_SetPriority(TIM2_IRQn,0,3);
		HAL_NVIC_EnableIRQ(TIM2_IRQn);
		HAL_NVIC_SetPriority(TIM3_IRQn,1,3);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);

		TIM2_Handler.Instance = TIM2;                                     //通用定时器2,使用时钟APB1,时钟频率为45MHz
    TIM2_Handler.Init.Prescaler = 45 - 1;                             //45 / 45 / 1000 = 1KHz
    TIM2_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM2_Handler.Init.Period = 560 - 1;                                //自动装载值
    TIM2_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;         //时钟分频因子
    HAL_TIM_Base_Init(&TIM2_Handler);
	
    TIM3_Handler.Instance = TIM3;                                     //通用定时器3,使用时钟APB1,时钟频率为45MHz
		TIM3_Handler.Channel = HAL_TIM_ACTIVE_CHANNEL_1;
    TIM3_Handler.Init.Prescaler = 5 - 1;                             //45 / 20 / 60 = 38KHz
    TIM3_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM3_Handler.Init.Period = 9 - 1;                                //自动装载值
    TIM3_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;         //时钟分频因子
    HAL_TIM_Base_Init(&TIM3_Handler);
		
//		HAL_TIM_Base_Start_IT(&TIM2_Handler);                             //使能定时器2和定时器2更新中断：TIM_IT_UPDATE   
    HAL_TIM_Base_Start_IT(&TIM3_Handler);                             //使能定时器3和定时器3更新中断：TIM_IT_UPDATE   
}

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM2_Handler);
}

void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM3_Handler);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&TIM2_Handler))
    {
        itflag = !itflag;
				HAL_GPIO_TogglePin(NEC_GPIO_PORT, GPIO_PIN_6);
				if(itflag == 0)
				{
						HAL_NVIC_EnableIRQ(TIM3_IRQn);
						HAL_GPIO_WritePin(NEC_GPIO_PORT, NEC_PIN, GPIO_PIN_SET);
						HAL_TIM_Base_Start_IT(&TIM3_Handler);
				}
				if(itflag == 1)
				{
						__HAL_TIM_CLEAR_IT(&TIM3_Handler, TIM_IT_UPDATE | TIM_IT_CC1);  //TIM_IT_UPDATE | TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_TRIGGER | TIM_IT_BREAK
						__HAL_TIM_CLEAR_FLAG(&TIM3_Handler, TIM_FLAG_UPDATE);
						HAL_NVIC_DisableIRQ(TIM3_IRQn);		
						HAL_TIM_Base_Stop_IT(&TIM3_Handler);
					  HAL_GPIO_WritePin(NEC_GPIO_PORT, NEC_PIN, GPIO_PIN_RESET);
				}
    }
    if(htim==(&TIM3_Handler))
    {
				cnt++;
				if(cnt == 6)
				{
						HAL_GPIO_WritePin(NEC_GPIO_PORT, NEC_PIN, GPIO_PIN_RESET);
				}
				if(cnt == 16)
				{
						HAL_GPIO_WritePin(NEC_GPIO_PORT, NEC_PIN, GPIO_PIN_SET);
						cnt = 0;
				}
//        HAL_GPIO_TogglePin(NEC_GPIO_PORT, NEC_PIN);
    }
}



