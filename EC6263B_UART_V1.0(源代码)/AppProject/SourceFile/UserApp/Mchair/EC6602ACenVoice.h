/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: EC6602ACenVoice.h                                                                                                       
**
**    功能描述: 中心板与语音板通信协议                                                                                                      
**
**    公    司：                                                                                                        
**
**    项目名称：                                                                                                        
**
**    平台信息：                                                                                                        
**
**    作    者：                                                                                              
**
**    其他说明:                                                                                                        
**
**    修改记录:  
**
========================================================================================================================
========================================================================================================================
*/
#ifndef  _EC6602ACENVOICE_H_
#define  _EC6602ACENVOICE_H_


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp.h"


/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
#define  CEN_Voice_UART_PORT                    BSP_UART_Port3           /*所用串口*/

#define  Voice_TO_CEN_RXBUF_SIZE                6                        /*接收缓存大小*/ 

#define  CEN_TO_Voice_TX_BASE_SIZE		4

#define  CEN_TO_Voice_TXBUF_SIZE                (Voice_TO_CEN_RXBUF_SIZE+67)  /*发送缓存大小,配网数据最大67字节*/ 

/*所有需应答的指令应在200ms内收到应答，否则应再次发送指令，若重发2次仍未收到有效应答则停止发送指令*/

#define  VOICE_CEN_FRAME_HEAD                           0x7b	/*帧头*/

/*命令码，数据长度，回复码，数据长度整理*/
//语音播放操作指令，中心板->语音板，没回应或有错需重发，最多重发三次
#define  CEN_VOICE_VoiceVal_0xa0                 		0xa0	/*Cen发送播放指令*/
#define  CEN_VOICE_VoiceVal_0xa0_DataLength             2      	/*Cen发送播放指令数据长度*/
#define  VOICE_CEN_VoiceVal_0xb0               	        0xb0    /*语音板回复键值指令*/
#define  VOICE_CEN_VoiceVal_0xb0_DataLength             2      	/*语音板回复键值指令数据长度，数据内容，成功：0xFFFF，有错：0xFFEE*/

//语音板识别到指令后，发给中心板
#define  VOICE_CEN_ORDER_0xb1						    0xb1    /*语音识别指令帧*/
#define  VOICE_CEN_ORDER_0xb1_DataLength                2       /*语音识别指令数据长度*/
#define  CEN_VOICE_ORDER_0xa1						    0xa1    /*回复语音识别指令帧*/
#define  CEN_VOICE_ORDER_0xa1_DataLength                2       /*回复语音识别指令数据内容，正确0xffff，错误0xffee*/

//查询语音板版本号指令，发给语音板
#define  CEN_VOICE_VER_0xa3               		 	    0xa3    /*中心板查询语音板版本*/
#define  CEN_VOICE_VER_0xa3_DataLength                  0     	/*数据长度为0*/
#define  VOICE_CEN_VER_0xb3               		        0xb3    /*语音板应答中心板*/
#define  VOICE_CEN_VER_0xb3_DataLength                  1       /*版本号数据长度1，内容0x12表示V1.2*/

//语音播放关闭指令，发给语音板
#define  CEN_VOICE_CLOSE_0xa4               		 	0xa4    /*语音播放关闭*/
#define  CEN_VOICE_CLOSE_0xa4_DataLength                0     	/*数据长度为0*/
#define  VOICE_CEN_CLOSE_0xb4               		    0xb4    /*语音板应答中心板*/
#define  VOICE_CEN_CLOSE_0xb4_DataLength                1       /*版本号数据长度1，内容成功:0x88,失败:0xee*/

//语音识别开启和关闭指令，发给语音板
#define  CEN_VOICE_DISCERN_ONOFF_0xa5               	0xa5    /*语音识别开关*/
#define  CEN_VOICE_DISCERN_ONOFF_DataLength             1     	/*数据长度为1，内容关闭:0,开启:1*/
#define  VOICE_CEN_DISCERN_ONOFF_0xb5                   0xb5    /*语音板应答中心板*/
#define  VOICE_CEN_DISCERN_ONOFF_0xb5_DataLength        1       /*版本号数据长度1，内容关闭成功:0x88,关闭失败:0x0e，开启成功:0x18,开启失败:0x1e*/

//语音播放音量设置，发给语音板
#define  CEN_VOICE_VOLUME_0xa6                 			0xa6    /*语音播放音量设置*/
#define  CEN_VOICE_VOLUME_0xa6_DataLength               1       /*长度1，内容:0~10,0音量最小*/
#define  VOICE_CEN_VOLUME_0xb6               		    0xb6    /*语音板音量设置应答帧*/
#define  VOICE_CEN_VOLUME_0xb6_DataLength               1       /*长度1，内容,成功:0x88,失败:0xee*/

//语音板心跳包，30秒发送一次心跳包给中心板，无需回应
#define  VOICE_CEN_HEARTBEAT_0xb7              		   	0xb7    /*语音板心跳包指令*/
#define  VOICE_CEN_HEARTBEAT_0xb7_DataLength			0     	/*中心板无需回应*/

//语音板wifi配网数据，发给语音板
#define  CEN_VOICE_WIFIDATA_0xa8                 		0xa8    /*语音WIFI配网数据设置*/
//#define  CEN_VOICE_WIFIDATA_0xa8_DataLengthx               1       /*可变长*/
#define  VOICE_CEN_WIFIDATA_0xb8               		    0xb8    /*语音WIFI配网数据设置应答帧*/
#define  VOICE_CEN_WIFIDATA_0xb8_DataLength             2       /*语音WIFI配网数据设置应答数据，长度2，数据内容，成功：0xffff，有错：0xffee*/


#define  VOICE_CEN_CMD_OFFSET                           1       /*命令在帧中的位置偏移量*/
#define  VOICE_CEN_DATALEN_OFFSET                       2       /*数据长度在帧中的位置偏移量*/
#define  VOICE_CEN_DATA_OFFSET                          3       /*数据在帧中的位置偏移量*/
#define  VOICE_CEN_DATA_OFFSET1                         4       /*数据1在帧中的位置偏移量*/





/*=====VOICE_CEN_ORDER_0xb1接收语音板指令=============================================================================*/
#define  VOICEORDER_0xb1_WakeUpO                        	0x01    /*开机 待机唤醒(启动语音1，小奥)*/

#define  VOICEORDER_0xb1_PowerOn                        		0x56    /*开机*/
#define  VOICEORDER_0xb1_PowerOff                       		0x04    /*关机(复位)*/

#define  VOICEORDER_0xb1_BackRiseFeetRecline            0x05    /*升背降腿*/
#define  VOICEORDER_0xb1_BackReclineFeetRise            0x07    /*抬腿倒背*/

//#define  VOICEORDER_0xb1_SrtengthAdd                    	0x06    /*强度加重*/
//#define  VOICEORDER_0xb1_SrtengthDec                    	0x07    /*强度减弱*/

#define  VOICEORDER_0xb1_FlexAdd                    		0x09    /*强度加重*/
#define  VOICEORDER_0xb1_FlexDec                    		0x0A    /*强度减弱*/

#define  VOICEORDER_0xb1_IntensityAdd                    	0x06    /*强度加重*/
#define  VOICEORDER_0xb1_IntensityDec                    	0x08    /*强度减弱*/

//#define  VOICEORDER_0xb1_Neck                   			0x08    /*颈部按摩*/

//#define  VOICEORDER_0xb1_RandomAuto                     	0x0A    /*自动推介按摩*/
#define  VOICEORDER_0xb1_SwitchManual                     	0x1D    /*自动推介按摩*/

#define  VOICEORDER_0xb1_Shoulder                   		0x0B    /*肩部按摩*/
#define  VOICEORDER_0xb1_Arms                           		0x0C    /*手臂按摩*/
#define  VOICEORDER_0xb1_Back                          		0x0D    /*背部按摩*/
#define  VOICEORDER_0xb1_Lumbar                         		0x0E    /*腰部按摩*/
#define  VOICEORDER_0xb1_Hip                           		0x0F    /*臀部按摩*/
#define  VOICEORDER_0xb1_CalvesFeet                     	0x10    /*腿脚按摩*/

#define  VOICEORDER_0xb1_Knead                          		0x11    /*揉捏*/
#define  VOICEORDER_0xb1_Roll                          		0x12    /*推拿*/
#define  VOICEORDER_0xb1_Clap                           		0x13    /*拍打*/
#define  VOICEORDER_0xb1_Shia                           		0x14    /*指压*/

#define  VOICEORDER_0xb1_Spot                           		0x15    /*定点*/

#define  VOICEORDER_0xb1_ServiceDescription             	0x16    /*语音服务内容介绍*/

#define  VOICEORDER_0xb1_Swedish                     		0x17    /*瑞典式*/
#define  VOICEORDER_0xb1_Tap                            		0x18    /*敲击*/

#define  VOICEORDER_0xb1_CurrentProgram                 	0x19    /*当前按摩程序*/

#define  VOICEORDER_0xb1_Pause                          		0x1A    /*暂停*/
#define  VOICEORDER_0xb1_PauseResume                    	0x1B    /*取消暂停*/

#define  VOICEORDER_0xb1_CloseHeat                     		0x2D    /*关闭腿部加热*/
#define  VOICEORDER_0xb1_Heat                     			0x2C    /*开启腿部加热*/
#define  VOICEORDER_0xb1_CloseLumberHeat                 	0x1E    /*关闭腰部加热*/
#define  VOICEORDER_0xb1_LumberHeat                     	0x1F    /*关闭腰部加热*/

#define  VOICEORDER_0xb1_NetConnectOk                   	0x20    /*网络已连接*/

#define  VOICEORDER_0xb1_ZeroGravity1                   	0x21    /*零重力1*/
#define  VOICEORDER_0xb1_ZeroGravity2               	   	0x22    /*零重力2*/

#define  VOICEORDER_0xb1_BlueToothOn               	   	0x23    /*打开蓝牙*/
#define  VOICEORDER_0xb1_BlueToothOff              	   	0x24    /*关闭蓝牙*/

#define  VOICEORDER_0xb1_WakeUpEnd                      	0x39    /*唤醒结束侦测*/

#define  VOICEORDER_0xb1_AutoMassage1                     	0x51  /*云浮漫步*/
#define  VOICEORDER_0xb1_AutoMassage2                     	0x52  /*男士健体*/
#define  VOICEORDER_0xb1_AutoMassage3                    	0x53  /*女王美体*/
#define  VOICEORDER_0xb1_AutoMassage4                     	0x54  /*老年养生*/
#define  VOICEORDER_0xb1_AutoMassage5                    	0x55  /*久坐办公*/
#define  VOICEORDER_0xb1_AutoMassage6                    	0x56  /*追剧放松*/
#define  VOICEORDER_0xb1_AutoMassage7                    	0x57  /*运动达人*/
#define  VOICEORDER_0xb1_AutoMassage8                     	0x58  /*逛街出游*/
#define  VOICEORDER_0xb1_AutoMassage9                     	0x59  /*肩颈重点*/
#define  VOICEORDER_0xb1_AutoMassage10                 	0x5A  /*腰臀呵护*/
#define  VOICEORDER_0xb1_AutoMassage11                 	0x5B  /*泰式拉伸*/
#define  VOICEORDER_0xb1_AutoMassage12                  	0x62  /*摇摆舒眠*/

#define VOICEORDER_0xb1_OpenVoice					0x81 	/*开启语音*/
#define VOICEORDER_0xb1_CloseVoice					0x82 	/*关闭语音*/

//#define  VOICEORDER_0xb1_Help                           		0x17    /*帮助*/
//#define  VOICEORDER_0xb1_UnClear                        		0x18    /*没听清*/
//#define  VOICEORDER_0xb1_NetConnectFault                0x1F    /*网络连接失败*/

/*=====CEN_VOICE_VoiceVal_0xa0控制语音板指令=============================================================================*/
#define  VOICEVal_0xa0_WakeUpO                          	0x01    /*开机 待机唤醒(启动语音1,小奥)*/
#define  VOICEVal_0xa0_PowerOff                         	0x42    /*关机(复位)*/

#define  VOICEVal_0xa0_SpikeAdj1                        	0x05    /*马上为你调整*/
#define  VOICEVal_0xa0_SpikeAdj2                        	0x07    /*这样可以吗*/
#define  VOICEVal_0xa0_SpikeAdjLimit                    	0x30    /*已达极限位置*/

#define  VOICEVal_0xa0_SrtengthAdd                      	0x09    /*强度加重*/
//#define  VOICEVal_0xa0_SrtengthMax                      	0x08    /*强度最大*/
#define  VOICEVal_0xa0_SrtengthDec                      	0x0A    /*强度减弱*/
//#define  VOICEVal_0xa0_SrtengthMin                      	0x0A    /*强度最小*/

#define  VOICEVal_0xa0_IntensityAdd                      	0x06   /*强度加重*/
#define  VOICEVal_0xa0_IntensityDec                      	0x08    /*强度减弱*/
//自动程序播报
	#define  VOICEVal_0xa0_RandomAuto1                	0x51  /*全身舒缓*/
	#define  VOICEVal_0xa0_RandomAuto2              		0x52  /*长者元气*/
	#define  VOICEVal_0xa0_RandomAuto3                     	0x53  /*颈肩模式*/
	#define  VOICEVal_0xa0_RandomAuto4                   	0x54  /*腰部模式*/
	#define  VOICEVal_0xa0_RandomAuto5                    	0x55  /*意匠拉伸*/
	
	#define  VOICEVal_0xa0_RandomAuto6                     	0x06  /*上班族*/
	
	#define  VOICEVal_0xa0_RandomAuto7                     	0x57  /*摇摆助眠*/
	#define  VOICEVal_0xa0_RandomAuto8                    	0x58  /*骨盘模式*/
	#define  VOICEVal_0xa0_RandomAuto9                     	0x59  /*下肢模式*/
	#define  VOICEVal_0xa0_RandomAuto10                  	0x5A  /*深层舒压*/
	#define  VOICEVal_0xa0_RandomAuto11               	0x5B  /*日式按摩*/
	
	#define  VOICEVal_0xa0_RandomAuto12                   	0x0C  /*舒眠模式*/
	#define  VOICEVal_0xa0_RandomAuto13                   	0x0D  /*女王美体*/
	#define  VOICEVal_0xa0_RandomAuto14                  	0x0E  /*男士健体*/
	#define  VOICEVal_0xa0_RandomAuto15                   	0x0F  /*老年模式*/
	#define  VOICEVal_0xa0_RandomAuto16                   	0x10  /*速按放松*/
	#define  VOICEVal_0xa0_RandomAuto17                 	0x11  /*深度放松*/
	#define  VOICEVal_0xa0_RandomAuto18             	0x12  /*久坐释压*/
	#define  VOICEVal_0xa0_RandomAuto19                   	0x13  /*全身舒展*/
	#define  VOICEVal_0xa0_RandomAuto20                   	0x14  /*运动恢复*/
	#define  VOICEVal_0xa0_RandomAuto21                  	0x15  /*泰式拉筋*/

#define  VOICEVal_0xa0_Neck                        		0x0D    /*颈部按摩*/
#define  VOICEVal_0xa0_Shoulder                     		0x10    /*肩部按摩*/
#define  VOICEVal_0xa0_Arms                             	0x11    /*手臂按摩*/
#define  VOICEVal_0xa0_Back                             		0x12    /*背部按摩*/
#define  VOICEVal_0xa0_Lumbar                           	0x13    /*腰部按摩*/
#define  VOICEVal_0xa0_Hip                              		0x14    /*臀部按摩*/
#define  VOICEVal_0xa0_CalvesFeet                       	0x15    /*腿脚按摩*/

#define  VOICEVal_0xa0_Knead                            	0x16    /*揉捏*/
#define  VOICEVal_0xa0_Roll                             		0x17    /*推拿*/
#define  VOICEVal_0xa0_Clap                             		0x18    /*拍打*/
#define  VOICEVal_0xa0_Shia                             		0x19    /*指压*/
#define  VOICEVal_0xa0_Spot                             		0x1A    /*定点*/

#define  VOICEVal_0xa0_ServiceDescriptionO           	0x1B    /*语音服务内容介绍，小奥*/

#define  VOICEVal_0xa0_Swedish                             	0x1C    /*瑞典式*/

#define  VOICEVal_0xa0_Help                             		0x1D    /*帮助*/
#define  VOICEVal_0xa0_SwitchManual                     	0x1D    /*换种手法*/

#define  VOICEVal_0xa0_UnClear                          	0x1E    /*没听清*/

#define  VOICEVal_0xa0_ImHere                           	0x20    /*我在*/
#define  VOICEVal_0xa0_Here                             		0x21    /*在*/

#define  VOICEVal_0xa0_Tap                              		0x22    /*敲击*/

#define  VOICEVal_0xa0_CloseHeat                        	0x2D    /*关闭腿部加热*/
#define  VOICEVal_0xa0_Heat                       		0x2C    /*腿部加热*/
#define  VOICEVal_0xa0_CloseLumberHeat             	0x25    /*关闭腰部加热*/
#define  VOICEVal_0xa0_LumberHeat                       	0x26    /*腰部加热*/

#define  VOICEVal_0xa0_BlueToothOn                      	0x28    /**/
#define  VOICEVal_0xa0_BlueToothOff                     	0x29    /**/

#define  VOICEVal_0xa0_DefaultMode                   	0x2E    /*模块进入上电默认工作状态*/
#define  VOICEVal_0xa0_SleepMode                      	0x2F    /*模块进入休眠状态*/

#define  VOICEVal_0xa0_UnsupportedProgram        	0x3E    /*此功能不适用于现在模式*/
#define  VOICEVal_0xa0_ShoulderScanning        	0x31    /*肩部检测中，请耐心等待*/
#define  VOICEVal_0xa0_ShoulderScanFinish        	0x32    /*检测结束，开始为您按摩*/


#define  VOICEVal_0xa0_UARTNetConnect               	0x39    /*开启串口配网模式，播报开启APP配网模式 */
#define  VOICEVal_0xa0_NetConnectOK                  	0x3a    /*播放：网络已连接*/
#define  VOICEVal_0xa0_NetConnectFalse              	0x3B    /*播放：网络未连接，请连接网络*/

#define  VOICEVal_0xa0_PowerOn                        	0x3D    /*开机*/

#define  VOICEVal_0xa0_ChairRest                 		0x3E    /*播放：椅子复位中请稍后再试*/

#define  VOICEVal_0xa0_Pause                            	0x40    /*暂停*/
#define  VOICEVal_0xa0_PauseResume                     	0x41    /*取消暂停*/

#define VOICEVal_0xa0_OpenVoice					0x81 	/*开启语音*/
#define VOICEVal_0xa0_CloseVoice				0x82 	/*关闭语音*/

//#define  VOICEVal_0xa0_WakeUpH                          	0x02    /*开机 待机唤醒(启动语音2,小慧)*/
//#define  VOICEVal_0xa0_ServiceDescriptionH           	0x1C    /*语音服务内容介绍，小慧*/
//#define  VOICEVal_0xa0_APPNetConnect                  	0x31    /*开启APP配网模式 不播报*/
//#define  VOICEVal_0xa0_StopPlayNetworkAudio      	0x32    /*停止播放合成反馈音及音乐、故事、新闻等各种正在播放的音频*/

//    04
#define VOICEVal_0xa0_ChildClockOpen			0x15	/*奥佳华贴心守护，已为您开启儿童锁*/
#define VOICEVal_0xa0_ChildClockClose			0x16	/*奥佳华贴心守护，已为您关闭儿童锁*/

/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :                                                                                                    
************************************************************************************************************************
*/

/*
************************************************************************************************************************
* 类型定义 :  中心板 <--> 语音板  数据帧结构                                                                              
************************************************************************************************************************
*/
typedef struct
{
	uint8_t Head;
	uint8_t Cmd;
	uint8_t DataLength;
	uint8_t Data[2];
	uint8_t CheckSum;  
}CDP_CenVoiceFrame_t;/*通信数据帧*/

/*
************************************************************************************************************************
* 类型定义 :  中心板 <--> 语音板  中心板接收数据步骤                                                                             
************************************************************************************************************************
*/
typedef enum
{                   
	VoiceCen_RX_STEP_SEARCH_HEAD=0,             	/*帧头*/
	VoiceCen_RX_STEP_JUDGE_CMD,                 	/*命令码*/
	VoiceCen_RX_STEP_JUDGE_DATALEN,             	/*数据长度*/
	VoiceCen_RX_STEP_RCV_DATA,					    /*数据*/
	VoiceCen_RX_STEP_JUDGE_SUMCHECK			        /*累加和校验码*/
}CDP_VoiceCenStep_e; /*接收状态机*/  

typedef enum
{                   
	CenVoice_TX_STEP_SEARCH_HEAD=0,             	/*帧头*/
	CenVoice_TX_STEP_JUDGE_CMD,                 	/*命令码*/
	CenVoice_TX_STEP_JUDGE_DATALEN,             	/*数据长度*/
	CenVoice_TX_STEP_RCV_DATA,					    /*数据*/
	CenVoice_TX_STEP_JUDGE_SUMCHECK				    /*校验码*/
}CDP_CenVoiceStep_e; /*发送状态机*/  
/*
************************************************************************************************************************
* 类型定义 :  中心板 <--> 语音板  控制与状态标识                                                                              
************************************************************************************************************************
*/
typedef  union 
{
  uint16_t All;
  struct
  {
    uint8_t    SetAPPConnectNetFlag    	    :1;    /*进入配网标志位*/
    uint8_t    SetUARTConnectNetFlag    	:1;    /*进入串口配网标志位*/
    uint8_t    RetrySendVoiceValFlag        :1;    /*语音播报重发标志*/
    uint8_t    RxVoiceDataOKFlag            :1;    /*接收语音板通信数据包成功*/
    uint8_t    RxOrder0xb1OKFlag            :1;    /*语音指令接收成功*/
    uint8_t    VoiceValNeedResFlag          :1;    /*语音指令需要回复标志位*/
    uint8_t    StopPlayNetworkAudioFlag     :1;    /*停止播放合成反馈音及音乐、故事、新闻等各种正在播放的音频*/
    
    uint8_t    SendWifiDataToVoiceFlag      :1;    /*语音板WIFI数据需要回复标志位*/
    uint8_t    VoiceWIFIDataNeedResFlag     :1;    /*语音板WIFI数据需要回复标志位*/
    uint8_t    RetrySendWIFIDataFlag        :1;    /*语音播报重发标志*/
    
    uint8_t    VoiceCloseOKFlag    	        :1;    /*语音关闭成功标志位*/
    uint8_t    VoiceDiscernCloseOKFlag    	:1;    /*语音识别关闭成功标志位*/
    uint8_t    VoiceDiscernOpenOKFlag    	:1;    /*语音识别开启成功标志位*/
    uint8_t    VoiceWakeUpStateFlag    	    :1;    /*语音识别唤醒状态标志位*/
    
  }Bit;

}CDP_CenVoiceCSFlag_t;  /*Control State Flag  控制与状态标识*/

/*
************************************************************************************************************************
* 类型定义 :  中心板 <--> 语音板  相关操作数据结构                                                                            
************************************************************************************************************************
*/
typedef struct
{
	uint8_t TxVoiceVal[2+67];                      	/*发送缓存区*/
	uint8_t TxVoiceValLen;                      	/*发送缓存区*/
	CDP_CenVoiceCSFlag_t CSFlag;
    uint8_t	RxStep;                           		/*接收步骤*/
	uint8_t RxLen;								    						/*接收数据长度*/
	uint8_t RxBuf[Voice_TO_CEN_RXBUF_SIZE];       /*接收缓存区*/
	uint8_t RxDataLen;
	
	uint8_t Rx0xb1Order[2];
 	uint8_t TxBuf[CEN_TO_Voice_TXBUF_SIZE];       /*发送缓存区*/
	uint8_t TxLen;																/*发送数据长度*/

	uint8_t RetryTimes;
	uint8_t RetryDelayTimer;

	uint8_t SendWifiDataRetryTimes;
	uint8_t SendWifiDataRetryDelayTimer;

	uint8_t VoiceNothingReceiveTimerMS;

}CDP_CenVoice_t;	/*通信相关控制变量*/



/*
========================================================================================================================
*【全局声明】                                          【全局声明】                                          【全局声明】
========================================================================================================================
*/

 void ReceiveDataFromVoice100ms(void);
 void VoiceOrder0xb1RxHandle(Uchar OrderH,Uchar OrderL);
 void CDP_CenVoice_ByteRx(uint8_t RxByte);
 void VoiceVariableRefresh1ms(void);
#endif  


