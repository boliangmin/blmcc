#include "dev_can.h"
#include "delay.h"



CAN_HandleTypeDef   Can_Handle;       //CAN1句柄
CanTxMsgTypeDef     TxMessage;        //发送消息
CanRxMsgTypeDef     RxMessage;        //接收消息
extern __IO uint32_t can_rx_flag ;    //用于标志是否接收到数据，在中断函数中赋值



/**********************************************************************
*Function:  static void CAN_GPIO_Config(void)
*Describe:  初始化CAN通道管脚
*Return  :  无
**********************************************************************/
static void CAN_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	CAN_TX_GPIO_CLK_ENABLE();
	CAN_RX_GPIO_CLK_ENABLE();

	/* 配置CAN发送引脚 */
	GPIO_InitStructure.Pin = CAN_TX_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	GPIO_InitStructure.Pull  = GPIO_PULLUP;
	GPIO_InitStructure.Alternate =  GPIO_AF9_CAN1;
	HAL_GPIO_Init(CAN_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置CAN接收引脚 */
	GPIO_InitStructure.Pin = CAN_RX_PIN ;
	HAL_GPIO_Init(CAN_RX_GPIO_PORT, &GPIO_InitStructure);
}

/**********************************************************************
*Function:  static void CAN_NVIC_Config(void)
*Describe:  配置CAN中断优先级
*Return  :  无
**********************************************************************/
static void CAN_NVIC_Config(void)
{
	/* 配置抢占优先级的分组 */
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_1);
	/*中断设置，抢占优先级0，子优先级为0*/
	HAL_NVIC_SetPriority(CAN_RX_IRQ, 0 ,0);
	HAL_NVIC_EnableIRQ(CAN_RX_IRQ);
}

/**********************************************************************
*Function:  static uint8_t CAN_Mode_Config(void)
*Describe:  CAN通信参数配置
*Return  :  0--初始化成功
*			1--初始化失败
**********************************************************************/
static uint8_t CAN_Mode_Config(void)
{
	/************************CAN通信参数设置**********************************/
	/* 使能CAN时钟 */
	CAN_CLK_ENABLE();

	Can_Handle.Instance = CANx;
	Can_Handle.pTxMsg = &TxMessage;
	Can_Handle.pRxMsg = &RxMessage;
	/* CAN单元初始化 */
	Can_Handle.Init.TTCM=DISABLE;			     //MCR-TTCM  关闭时间触发通信模式使能
	Can_Handle.Init.ABOM=ENABLE;			     //MCR-ABOM  自动离线管理 
	Can_Handle.Init.AWUM=ENABLE;			     //MCR-AWUM  使用自动唤醒模式
	Can_Handle.Init.NART=DISABLE;			     //MCR-NART  禁止报文自动重传	  DISABLE-自动重传
	Can_Handle.Init.RFLM=DISABLE;			     //MCR-RFLM  接收FIFO 锁定模式  DISABLE-溢出时新报文会覆盖原有报文  
	Can_Handle.Init.TXFP=DISABLE;			     //MCR-TXFP  发送FIFO优先级 DISABLE-优先级取决于报文标示符 
	//Can_Handle.Init.Mode = CAN_MODE_NORMAL;    //正常工作模式
	Can_Handle.Init.Mode = CAN_MODE_LOOPBACK;    //正常工作模式

	Can_Handle.Init.SJW=CAN_SJW_1TQ;		     //BTR-SJW 重新同步跳跃宽度 2个时间单元

	/* ss=1 bs1=8 bs2=6 位时间宽度为(1+8+6) 波特率即为时钟周期tq*(1+8+6)  */
	Can_Handle.Init.BS1=CAN_BS1_8TQ;		     //BTR-TS1 时间段1 占用了8个时间单元
	Can_Handle.Init.BS2=CAN_BS2_6TQ;		     //BTR-TS1 时间段2 占用了6个时间单元	

	/* CAN Baudrate = 500k Bps (1MBps已为stm32的CAN最高速率) (CAN 时钟频率为 APB1 = 180 / 4 = 45 MHz) */
	Can_Handle.Init.Prescaler = 6;		         //BTR-BRP 波特率分频器  定义了时间单元的时间长度 45/(1+8+6)/6 =500k bps
	if(HAL_CAN_Init(&Can_Handle) != HAL_OK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**********************************************************************
*Function:  static void CAN_Filter_Config(void)
*Describe:  CAN筛选器配置
*Return  :  无
**********************************************************************/
static void CAN_Filter_Config(void)
{
	CAN_FilterConfTypeDef  CAN_FilterInitStructure;

	/*CAN筛选器初始化*/
	CAN_FilterInitStructure.FilterNumber = 0;							//筛选器组0
	CAN_FilterInitStructure.FilterMode = CAN_FILTERMODE_IDMASK;	    	//工作在掩码模式
	CAN_FilterInitStructure.FilterScale = CAN_FILTERSCALE_32BIT;		//筛选器位宽为单个32位。
	/* 使能筛选器，按照标志的内容进行比对筛选，扩展ID不是如下的就抛弃掉，是的话，会存入FIFO0。 */
	/*标准帧的起始位置是第22位，需要左移21位*/
	/*要筛选的ID高位 */
	CAN_FilterInitStructure.FilterIdHigh = ((((uint32_t)0x520<<21) | CAN_ID_STD | CAN_RTR_DATA)&0xFFFF0000)>>16;
	/*要筛选的ID低位 */
	CAN_FilterInitStructure.FilterIdLow = (((uint32_t)0x520<<21) | CAN_ID_STD | CAN_RTR_DATA)&0xFFFF;
	CAN_FilterInitStructure.FilterMaskIdHigh = 0xFFFF;			        //筛选器高16位每位必须匹配
	CAN_FilterInitStructure.FilterMaskIdLow = 0xFFFF;			        //筛选器低16位每位必须匹配
	CAN_FilterInitStructure.FilterFIFOAssignment = CAN_FILTER_FIFO0 ;	//筛选器被关联到FIFO0
	CAN_FilterInitStructure.FilterActivation = ENABLE;			        //使能筛选器
	HAL_CAN_ConfigFilter(&Can_Handle,&CAN_FilterInitStructure);
}

/**********************************************************************
*Function:  void CAN_Config(void)
*Describe:  CAN初始化
*Return  :  无
**********************************************************************/
void CAN_Config(void)
{
	CAN_GPIO_Config();
	CAN_NVIC_Config();
	CAN_Mode_Config();
	CAN_Filter_Config();
	Init_RxMes(); 
	HAL_CAN_Receive_IT(&Can_Handle, CAN_FIFO0); 	
}

/**********************************************************************
*Function:  void Init_RxMes(void)
*Describe:  初始化CAN接收数据结构体
*Return  :  无
**********************************************************************/
void Init_RxMes(void)
{
	uint8_t ubCounter = 0;

	/*把接收结构体清零*/
	Can_Handle.pRxMsg->StdId = 0x00;
	Can_Handle.pRxMsg->ExtId = 0x00;
	Can_Handle.pRxMsg->IDE = CAN_ID_STD;
	Can_Handle.pRxMsg->DLC = 0;
	Can_Handle.pRxMsg->FMI = 0;
	for (ubCounter = 0; ubCounter < 8; ubCounter++)
	{
		Can_Handle.pRxMsg->Data[ubCounter] = 0x00;
	}
}

/**********************************************************************
*Function:  void CAN_SetMsg(uint16_t stdId,uint16_t buff[8])
*Describe:  发送一帧CAN数据
*Return  :  无
**********************************************************************/
void CAN_SetMsg(uint16_t stdId,uint16_t buff[8])
{
	uint16_t i;
	Can_Handle.pTxMsg->StdId = stdId;						 
	Can_Handle.pTxMsg->ExtId = 0x00;					 //使用的扩展ID
	Can_Handle.pTxMsg->IDE = CAN_ID_STD;				 //扩展模式
	Can_Handle.pTxMsg->RTR = CAN_RTR_DATA;				 //发送的是数据
	Can_Handle.pTxMsg->DLC = 8;							 //数据长度为8字节

	/*设置要发送的数据0-7*/
	for (i = 0; i < 8; i++)
	{
		Can_Handle.pTxMsg->Data[i] = buff[i];
	}
}

/**********************************************************************
*Function:  void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
*Describe:  CAN接收中断回调函数
*Return  :  无
**********************************************************************/
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
{
	/* 比较ID是否为0x520 */ 
	if((hcan->pRxMsg->StdId == 0x520) && (hcan->pRxMsg->IDE == CAN_ID_STD) && (hcan->pRxMsg->DLC==8) )
	{
		can_rx_flag = 1;     //接收成功  
	}
	else
	{
		can_rx_flag = 0;     //接收失败
	}
	/* 准备中断接收 */
	HAL_CAN_Receive_IT(&Can_Handle, CAN_FIFO0);
}

/**********************************************************************
*Function:  void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
*Describe:  CAN接收错误回调函数
*Return  :  无
**********************************************************************/
void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
{
	//printf("\r\nCAN出错\r\n");
}


