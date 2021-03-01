#include "can.h"
#include "usart.h"
#include "delay.h"
#include "led.h"


CAN_HandleTypeDef   Can_Handle;   //CAN1���
CanTxMsgTypeDef     TxMessage;      //������Ϣ
CanRxMsgTypeDef     RxMessage;      //������Ϣ

extern __IO uint32_t flag ;		 //���ڱ�־�Ƿ���յ����ݣ����жϺ����и�ֵ


static void CAN_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    CAN_TX_GPIO_CLK_ENABLE();
    CAN_RX_GPIO_CLK_ENABLE();

    /* ����CAN�������� */
    GPIO_InitStructure.Pin = CAN_TX_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
    GPIO_InitStructure.Pull  = GPIO_PULLUP;
    GPIO_InitStructure.Alternate =  GPIO_AF9_CAN1;
    HAL_GPIO_Init(CAN_TX_GPIO_PORT, &GPIO_InitStructure);

    /* ����CAN�������� */
    GPIO_InitStructure.Pin = CAN_RX_PIN ;
    HAL_GPIO_Init(CAN_RX_GPIO_PORT, &GPIO_InitStructure);
}


static void CAN_NVIC_Config(void)
{
	  /* ������ռ���ȼ��ķ��� */
	  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_1);
	  /*�ж����ã���ռ���ȼ�0�������ȼ�Ϊ0*/
	  HAL_NVIC_SetPriority(CAN_RX_IRQ, 0 ,0);
	  HAL_NVIC_EnableIRQ(CAN_RX_IRQ);
}


u8 CAN_Mode_Config(void)
{
	/************************CANͨ�Ų�������**********************************/
	/* ʹ��CANʱ�� */
    CAN_CLK_ENABLE();
    
    Can_Handle.Instance = CANx;
    Can_Handle.pTxMsg = &TxMessage;
    Can_Handle.pRxMsg = &RxMessage;
	  /* CAN��Ԫ��ʼ�� */
	  Can_Handle.Init.TTCM=DISABLE;			   //MCR-TTCM  �ر�ʱ�䴥��ͨ��ģʽʹ��
	  Can_Handle.Init.ABOM=ENABLE;			   //MCR-ABOM  �Զ����߹��� 
	  Can_Handle.Init.AWUM=ENABLE;			   //MCR-AWUM  ʹ���Զ�����ģʽ
	  Can_Handle.Init.NART=DISABLE;			   //MCR-NART  ��ֹ�����Զ��ش�	  DISABLE-�Զ��ش�
	  Can_Handle.Init.RFLM=DISABLE;			   //MCR-RFLM  ����FIFO ����ģʽ  DISABLE-���ʱ�±��ĻḲ��ԭ�б���  
	  Can_Handle.Init.TXFP=DISABLE;			   //MCR-TXFP  ����FIFO���ȼ� DISABLE-���ȼ�ȡ���ڱ��ı�ʾ�� 
	  Can_Handle.Init.Mode = CAN_MODE_NORMAL;    //��������ģʽ
	  //Can_Handle.Init.Mode = CAN_MODE_LOOPBACK;    //��������ģʽ
	
	  Can_Handle.Init.SJW=CAN_SJW_1TQ;		   //BTR-SJW ����ͬ����Ծ���� 2��ʱ�䵥Ԫ
	 
	  /* ss=1 bs1=8 bs2=6 λʱ�����Ϊ(1+8+6) �����ʼ�Ϊʱ������tq*(1+8+6)  */
	  Can_Handle.Init.BS1=CAN_BS1_8TQ;		   //BTR-TS1 ʱ���1 ռ����8��ʱ�䵥Ԫ
	  Can_Handle.Init.BS2=CAN_BS2_6TQ;		   //BTR-TS1 ʱ���2 ռ����6��ʱ�䵥Ԫ
	
	  /* CAN Baudrate = 500k Bps (1MBps��Ϊstm32��CAN�������) (CAN ʱ��Ƶ��Ϊ APB1 = 180 / 4 = 45 MHz) */
	  Can_Handle.Init.Prescaler = 6;		     //BTR-BRP �����ʷ�Ƶ��  ������ʱ�䵥Ԫ��ʱ�䳤�� 45/(1+8+6)/6 =500k bps
	  if(HAL_CAN_Init(&Can_Handle) != HAL_OK)
			  return 1;
		else
			  return 0;
}


static void CAN_Filter_Config(void)
{
	  CAN_FilterConfTypeDef  CAN_FilterInitStructure;

	  /*CANɸѡ����ʼ��*/
	  CAN_FilterInitStructure.FilterNumber = 0;						//ɸѡ����0
	  CAN_FilterInitStructure.FilterMode = CAN_FILTERMODE_IDMASK;	//����������ģʽ
	  CAN_FilterInitStructure.FilterScale = CAN_FILTERSCALE_32BIT;	//ɸѡ��λ��Ϊ����32λ��
	  /* ʹ��ɸѡ�������ձ�־�����ݽ��бȶ�ɸѡ����չID�������µľ����������ǵĻ��������FIFO0�� */
    //��׼֡����ʼλ���ǵ�22λ����Ҫ����21λ

	  CAN_FilterInitStructure.FilterIdHigh = ((((uint32_t)0x520<<21) | CAN_ID_STD | CAN_RTR_DATA)&0xFFFF0000)>>16;		//Ҫɸѡ��ID��λ 
	  CAN_FilterInitStructure.FilterIdLow = (((uint32_t)0x520<<21) | CAN_ID_STD | CAN_RTR_DATA)&0xFFFF;              //Ҫɸѡ��ID��λ 
	  CAN_FilterInitStructure.FilterMaskIdHigh = 0xFFFF;			//ɸѡ����16λÿλ����ƥ��
	  CAN_FilterInitStructure.FilterMaskIdLow = 0xFFFF;			//ɸѡ����16λÿλ����ƥ��
	  CAN_FilterInitStructure.FilterFIFOAssignment = CAN_FILTER_FIFO0 ;	//ɸѡ����������FIFO0
	  CAN_FilterInitStructure.FilterActivation = ENABLE;			//ʹ��ɸѡ��
	  HAL_CAN_ConfigFilter(&Can_Handle,&CAN_FilterInitStructure);
}


void CAN_Config(void)
{
    CAN_GPIO_Config();
    CAN_NVIC_Config();
    CAN_Mode_Config();
    CAN_Filter_Config();
    Init_RxMes(); 
    HAL_CAN_Receive_IT(&Can_Handle, CAN_FIFO0); 	
}


void Init_RxMes(void)
{
    uint8_t ubCounter = 0;

    /*�ѽ��սṹ������*/
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


void CAN_SetMsg(u16 stdId,u8 *buff)
{
	  u16 i;
    Can_Handle.pTxMsg->StdId = stdId;						 
    Can_Handle.pTxMsg->ExtId = 0x00;					     //ʹ�õ���չID
    Can_Handle.pTxMsg->IDE = CAN_ID_STD;				   //��չģʽ
    Can_Handle.pTxMsg->RTR = CAN_RTR_DATA;				 //���͵�������
    Can_Handle.pTxMsg->DLC = 8;							       //���ݳ���Ϊ8�ֽ�
	
    /*����Ҫ���͵�����0-7*/
    for (i = 0; i < 8; i++)
    {
        Can_Handle.pTxMsg->Data[i] = buff[i];
    }
}


void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
{
	  /* �Ƚ�ID�Ƿ�Ϊ0x520 */ 
	  if((hcan->pRxMsg->StdId == 0x520) && (hcan->pRxMsg->IDE == CAN_ID_STD) && (hcan->pRxMsg->DLC==8) )
	  {
		    flag = 1; //���ճɹ�  
	  }
	  else
	  {
		    flag = 0; //����ʧ��
	  }
	  /* ׼���жϽ��� */
	  HAL_CAN_Receive_IT(&Can_Handle, CAN_FIFO0);
}



void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
{
	  printf("\r\nCAN����\r\n");
}

