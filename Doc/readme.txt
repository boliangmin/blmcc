This is designing for my smart control system
I will try my best to complete it
When i finished it ,i will leave byd and find a new job
And i hope i can find some one that time
Be brave and confident

2020-09-12


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
2020-09-15
	串口调试助手不能接收到数据。
	1.串口调试工具的问题，傻逼工具打开后不能关闭，导致串口占用，使得不能接收数据。
	2.开发板flash下载之后，需要重新上电再次打开串口才能接收到数据。
	
	问题遗留：
	1.按理说，使用ST_LINK下载程序之后，不需要重新上电程序也能正常跑起来，但现在似乎不符合常理。
	2.代码设置为先printf("hhhh"),之后while(1)间隔半秒输出hhhhi++,上电之后，按理说,程序已经开始跑起来了，在点击调试助手打开串口通道的过程中，log应该进入i++阶段的输出了，但每次都是打开串口通道，才开始输出 hhhh\hhhh0\hhhh1...
	3.这里使用的是串口中断输出，每次收发是否都要触发中断，对于系统的影响如何，除此之外，是否可以采用DMA等其他方式输出串口log.
	
	参考资料：
	https://blog.csdn.net/heda3/article/details/80602287

	version:
	20200915_001
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
2020-09-15
	上传github:
	1.添加ssh,创建github代码仓
	2.git remote add origin git@github.com:michaelliao/learngit.git
	3.git branch -M master
	4.git push -u origin master(第一次上传）
	5.git push origin master(修改上传）
	
	参考资料：
	https://www.liaoxuefeng.com/wiki/896043488029600/898732864121440

	version:
	20200915_002
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
2020-09-21
	添加CAN通信，可以通过周立功USBCAN_II接收到CAN数据。
	
	待解决问题：
	1.stm32的系统时钟配置问题,野火和正点使用的时钟频率不相同，需进一步学习。
	2.can_test接收到的数据与系统发送的数据不相同，按照程序设定，应该是间隔一秒发送一次Id为1314的扩展帧，但接收到的数据毫无规律可言，而且接收到的数据极快，并没有一秒发送一次的效果。
	
	version:
	20200921_003
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
2020-10-03
	添加了EEPROM的读取代码。
	
	待解决问题：
	1.正点原子使用的是软件GPIO模拟IIC，而野火使用的是硬件IIC，不能直接将其代码修改移植，同时应当分析一下二者之间各自的优势与缺点。
	2.正点原子还采用了一种FLASH模拟EEPROM的方式，应分析一下二者之间各自的特点以及运用场景。
	
	version:
	20201003_004
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
2020-10-07
	解决CAN报文发送失败的问题。
	1.在正点原子的代码上移植了野火的代码，在对CAN管脚初始化的时候没有使能管脚时钟--CAN_TX_GPIO_CLK_ENABLE()，而是沿用了--__HAL_RCC_CAN1_CLK_ENABLE()，可能导致管脚没有初始化无用。
	2.系统时钟的设置，正点使用的系统时钟为180MHz，而野火注释标注的是216MHz，实际使用的依然还是180MHz，在对波特率的计算的时候造成了偏差，CAN时钟APB1等于系统时钟除以APB1分频系数，野火CAN时钟应为45Mhz，而不是标注的54MHz。
    3.将上述问题修正之后，进行CAN报文发送，串口数据显示，前三帧数据发送正常，从第四帧开始提示发送错误，修正Can_Handle.Init.NART=ENABLE，使能禁止报文自动重传功能，应该是发送的报文每一帧都是一样的，导致CAN的三个mailbox一致，再次发
送相同的报文时禁止自动重传，导致发送失败。

	CAN时钟以及波特率的计算：
	bitrate = APB1 / (1 + BS1 + BS2) / Prescaler;
	APB1 = SYSCLK / APB1CLKDivider;
	SYSCLK = PLLCLK = 外部时钟 / PLLM * PLLN / PLLP = 25 / 25 * 360 / 2 = 180MHz;

	version:
	20201007_005
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
2020-10-07
	解决CAN报文接收失败、系统卡死的问题,替换掉正点老旧sdk。
	1.Can_Handle.Init.NART=ENABLE 与报文发送失败无关，将其修改为DISABLE之后发送依然成功，还需继续学习相关寄存器的使用。
	2.系统卡死的原因是 can接收中断没有配置正确。CAN_RX_IRQ 在 stm32f4xx_it.c中应该有定义 void CAN_RX_IRQHandler(void)，正点原子的代码比较老旧，并没有找到相应的内容，将其替换为野火的代码后测试可以通过。
	3.在参考手册之中有这么一段话：要注意如果设置了接收报文中断，必须要在中断内调用HAL_CAN_Receive_IT 函数读取接收FIFO 的内容，因为只有这样才能清除该FIFO 的接收中断标志，如果不在中断内调用它清除标志的话，一旦接收到报文，STM32 会不
断进入中断服务函数，导致程序卡死。

	待解决问题：
	1.CAN通信中各种寄存器的使用。
	2.形如 stm32f4xx_it.c 之类的文件的使用。
	
	version:
	20201007-006
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
2020-12-03
	解决机器无法生成38KHz PWM红外载波的问题。
	出现的情况：
		波形不是相同时长的正负交替波形，而是无规律的或长或短的不规律波形周期性出现。----添加输出初始为0仍然不行。
		波形出现周期性上升下降沿，高电平仅维持几微秒。----将触发条件设置为电平触发仍不行
	在无数次检查代码以及设置分频系数、自动重载值仍然不能得到规律的pwm波形之后，尝试着检查逻辑分析仪的使用，将阈值电压设置为2.7V之后，得到了波形输出。

	待解决问题：
	1.红外编码下的波形输出
	2.使用DMA的方式输出PWM波，从而减少CPU资源占用。
	
	version:
	20201201-007
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
2020-12-06
	添加定时器控制38khz红外载波发射以实现遥控控制。
	出现的情况：
		使用TIMER2控制TIMER3输出载波，TIM2每隔500ms中断一次，itflag翻转，itflag == 0时发送
			HAL_GPIO_WritePin(NEC_GPIO_PORT, NEC_PIN, GPIO_PIN_SET);
			HAL_TIM_Base_Start_IT(&TIM3_Handler);
		itflag == 1时不发送
			__HAL_TIM_CLEAR_IT(&TIM3_Handler, TIM_IT_UPDATE | TIM_IT_CC1);
			__HAL_TIM_CLEAR_FLAG(&TIM3_Handler, TIM_FLAG_UPDATE);
			HAL_NVIC_DisableIRQ(TIM3_IRQn);		
			HAL_TIM_Base_Stop_IT(&TIM3_Handler);
			HAL_GPIO_WritePin(NEC_GPIO_PORT, NEC_PIN, GPIO_PIN_RESET);
		发送先置一的原因：再TIME2的控制下，如果不先将输出置为一，则需要在TIM2执行完一次中断之后才会进行载波发送，与实际不符合。
		发送后置零的原因：TIMER3关闭时，有可能输出正处于高位，如不置零，将会一直保持，因此需要将其置为零。
		这样才不会出现TIM2跳变之后，载波发送错误电压以及时序错误的情况。
	待解决问题：
	1.实际载波使用的38.46khz载波是10us高电平，16秒低电平，而使用定时器控制管脚开关无论如何变化重载值和分频值，都不能得到1us跳变一次的pwm波，最低只能达到1.67us，这样得到的载波频率不能达到38khz，后续需要使用定时器pwm模式。
	2.itflag == 1时，如此CLEAR的原因，经测试，只有这样的组合才不会出现载波电平在关闭TIM3后仍然为一的情况。
	3.__HAL_TIM_CLEAR_IT()如果不加，会出现2中所述现象，但只要加上八种clear类型中的任意一个就能解决问题，还需进一步研究原因。
	version:
	20201206-008
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
2020-12-22
	添加诊断协议宏定义，添加APP部分代码模板。
	添加了常用的诊断服务id,测试了相关的19服务子功能。
	version:
	20201222-009
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
2021-03-01
	重置工程目录框架
	添加了休眠唤醒功能。
	待解决问题：
	了解常见的三种休眠方式----待机，stop，低功耗。
	version:
	20210301-010
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
2021-03-18
	删除正点原子sys.h文件在工程中的配置，重写、编排代码结构，优化代码结构，提高可读性和理解性。
	涉及dev_can、dev_oled，dev_IIC,delay等。
	version:
	20210318-011
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------






























