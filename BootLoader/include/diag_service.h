#ifndef __DIAG_SERVICE_H
#define __DIAG_SERVICE_H

#define RECEIVE_ID                 0x520U               //接收id
#define SEND_ID                    0x521U               //发送id

#define POSITIVE_RESPOND           0x66U                //积极应答
#define NEGATIVE_RESPOND           0x77U                //消极应答

#define NORMAL_FRAME               0x00U                //普通帧
#define REQUEST_FRAME              0x10U                //多帧请求
#define LONGDATA_FRAME             0x20U                //长数据帧
#define REQ_LONG_FRAME             0x30U                //接收应答多帧请求

#define LF_ERROR                   0x89                 //长数据帧序号错误
#define TRANS_DATA_MAX             0xF2                 //一个数据块的大小
#define TEMP_DATA_MAX              0xFFU               //长数据帧存储最大数据

#define SECURITY_PASSWD            0xacb80dU            //验证密钥
#define UP_SER_PASS                0x01U                //升级状态--安全校验通过
#define UP_ERASE_FINISH            0x02U                //升级状态--擦除完成
#define BOOT_START_ADD             0x80000000U          //bootloader_flash起始地址

/************************************************************************************************************
*Service Id 00:   0x18U
*************************************************************************************************************/
#define READ_MASSAGE               0x18U								//数据读取
		#define READ_MCU_VERSION       0x01U                //读MCU版本信息

/************************************************************************************************************
*Service Id 01:   0x19U
*************************************************************************************************************/
#define SECURITY_ACCESS            0x19U                //安全访问
		#define SECURITY_ACCESS_REQ    0x01U                //请求访问
		#define SECURITY_ACCESS_BOOT   0xabbaU              //boot
		#define SECURITY_ACCESS_APP    0xaccaU              //app

		#define SECURITY_ACCESS_KEY    0x02U                //安全访问发送密钥
		#define SECURITY_KEY_RIGHT     0x10U                //密钥正确
		#define SECURITY_KEY_ERROR     0x11U                //密钥错误


/************************************************************************************************************
*Service Id 02:   0x22U
*************************************************************************************************************/
#define ERASE_REQUEST              0x22U                //擦除请求
		#define ERASE_ADD_SEND         0xd11dU              //发送擦除地址
		#define ERASE_SUCCESS          0x20U                //请求成功
		#define ERASE_FAILED           0x21U                //请求失败
		#define ERASE_ADD_ERROR        0x01U                //地址校验错误
		#define ERASE_TIME_OUT         0x02U                //擦除超时

/************************************************************************************************************
*Service Id 03:   0x23U
*************************************************************************************************************/
#define REQ_DOWNLOAD               0x23U                //请求下载
		#define REQ_DOW_ADD            0xe11eU              //发送写入地址、数据大小
		#define REQ_DOW_SUCCESS        0x30U                //请求下载成功
    #define REQ_DOW_FAILED         0x31U                //请求下载失败
		#define REQ_DOW_ADD_ERROE      0x01U                //写入地址错误
		#define REQ_DOW_SIZE_OUT       0x02U                //写入数据过大


/************************************************************************************************************
*Service Id 04:   0x24U
*************************************************************************************************************/
#define DATA_TRANS                 0x24U                //数据传输
		#define TRANS_SUCCESS          0x40U                //写入成功
		#define TRANS_FAILED           0x41U                //写入失败


/************************************************************************************************************
*Service Id 05:   0x25U
*************************************************************************************************************/
#define QUIT_TRANS 	               0x25U                //退出传输
		#define QUIT_SUCCESS 	         0x50U                //推出成功

/************************************************************************************************************
*Service Id 06:   0x26U
*************************************************************************************************************/
#define CHECK_SUM                  0x26U                //和校验
		#define CHECK_SUM_RIGHT        0x60U                //和校验正确
		#define CHECK_SUM_ERROR        0x61U                //和校验错误


/************************************************************************************************************
*Service Id 07:   0x27U
*************************************************************************************************************/
#define WRITE_MASSAGE              0x27U                //信息写入
		#define WRITE_MCU_VERSION      0x01U                //写MCU版本信息  --待添加


/************************************************************************************************************
*Service Id 08:   0x28U
*************************************************************************************************************/
#define MCU_RESET                  0x28U                //重启MCU
		#define RESET_KEY              0xadcdacU            //重启确认



#endif
