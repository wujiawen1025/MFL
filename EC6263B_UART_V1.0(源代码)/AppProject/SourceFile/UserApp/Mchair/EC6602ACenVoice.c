/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: EC6602ACenVoice.c
**
**    功能描述: 中心板与语音板通信协议  
**
**    公    司：蒙发利电子
**
**    项目名称：                                                                                                        
**
**    平台信息：                                                                                                        
**
**    作    者：                                                                                                     
**
**    其他说明: 用IO口矩阵扫描控制。                                                                                                     
**
**    修改记录:  
**
========================================================================================================================
========================================================================================================================
*/

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include <stdlib.h>
#include "IO.h"
#include "Flag.h"
#include "Glob.h"
#include "Clib.h"
#include "EC6602ACenVoice.h"
#include "Bluetooth50.h"
/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/
//#define TapMotorIsRunning()			(gbCoreManualFunction.All & 0x787F)
//#define KneadMotorIsRunning()		(gbCoreManualFunction.All & 0x1F80)

/*
========================================================================================================================
*【本地数据类型定义】                              【本地数据类型定义】                              【本地数据类型定义】
========================================================================================================================
*/

/*
************************************************************************************************************************
* 类型定义 :                                                                                                         
************************************************************************************************************************
*/


/*
========================================================================================================================
*【变量定义 & 各种声明】                          【变量定义 & 各种声明】                          【变量定义 & 各种声明】    
========================================================================================================================
*/
extern void KeyPressEvent(Uchar KeyValue,Uchar	KeyTab[],Uchar device,Uchar TabSize);
extern void IdentifySend(BSP_UART_PortNum_t PortNum);
extern void SpikeAngleSet(Uchar BackSpikeAngle,Uchar FeetSpikeAngle,Uchar ZeroSpikeAngle);
extern void SystemStart(void);
extern void KeyPower(void);
static const uint8_t VoiceKeyValMapTab[] = 
{
  evKeyNC,                          /*0  */
  evKeyPower,            	        /*1 开机小派*/
  evKeyPower,            	            /*2 开机*/
  evKeyPower,            	        /*3 关机*/
  evKeyPower,		//evKeyBackRaiseFeetRecline,       /*4 降腿升背*/  //在指令处理函数中处理,按键表格不执行
  evKeyNC,		//evKeyBackReclineFeetRaise,       /*5 升腿降背*/  //在指令处理函数中处理,按键表格不执行
  evKeyNC,		//evKeyStrengthSpeedAdd,   /*6 强度加重*/  //在指令处理函数中处理,按键表格不执行
  evKeyNC,		//evKeyStrengthSpeedDec, /*7 强度减弱*/  //在指令处理函数中处理,按键表格不执行
  evKeyNC,                          /*8 音量增加，语音板自己控制*/
  evKeyNC,                          /*9 音量减少，语音板自己控制*/
  evKeyNC,                          /*10 随机程序,在处理函数中处理*/
  evKeyNC,//evKeyNeckShoulder,                /*11 劲肩*/
  evKeyNC,//evKeyArmsGas,                     /*12 手臂*/
  evKeyNC,//evKeyBackLumbar,                  /*13 背部*/
  evKeyNC,//evKeyLumbar,                      /*14 腰部*/
  evKeyNC,//evKeyButto,                       /*15 臀部*/
  evKeyNC,//evKeyFeetCalvesGas,               /*16 腿脚部*/
  evKeyNC,            	    /*17 机芯手动程序 揉捏*/
  evKeyNC,                     /*18 机芯手动程序 推拿*/
  evKeyNC,            		    /*19 机芯手动程序 敲击*/
  evKeyNC,                        /*20 机芯手动程序 指压*/
  evKeyNC,           			    /*21 定点*/
  
  evKeyNC,                          /*22*/
  evKeyNC,                          /*23*/
  evKeyNC,                          /*24*/
  evKeyNC,                          /*25*/
  evKeyNC,                       /*26 暂停*/
  evKeyNC,                       /*27 取消暂停*/
  evKeyNC,                    /*28 */
  evKeyNC,                  /*29 */
  evKeyNC,                   /*30 */
  evKeyNC,		 /*31 */
  evKeyNC,		 /*32 */
  evKeyNC,		 /*33零重力1*/
  evKeyNC,		/*34零重力2*/
  evKeyNC,			/*35 */
  evKeyNC,			/*36 */
  evKeyVoiceSwitch,		/*37 */
  evKeyVoiceSwitch,		/*38 */
  evKeyNC,                          /*39*/
  evKeyNC,                          /*40*/
  evKeyNC,                          /*41*/
  evKeyNC,                          /*42*/
  evKeyNC,                          /*43*/
  evKeyHeating,           		/*44 开启加热*/
  evKeyHeating,           		/*45 关闭加热*/
};
static const uint8_t VoiceAutoMassageKeyValTab[] = 
{
  evKeyNC,                          /*0  */
  evKeyMasterCare,            		/*1 全身舒缓*/
  evKeyOldMan,  				/*2 长者元气*/
  evKeyShoulderNeck,            	/*3 颈肩模式*/
  evKeyBackBLumbarMassage,	/*4 腰部模式*/
  evKeyThaiMassage,			/*5 意匠拉伸*/
  evKeyNC,					/*6*/ 
  evKeySleep,		 			/*7 摇摆助眠*/ 
  evKeyFitness,                      	/*8 骨盘模式*/
  evKeyWalk,          			/*9 下肢模式*/
  evKeyDeepMassage,        		/*10  深层舒压*/
  evKeyJapanese, 				/*11  日式按摩*/
  evKeyNC, 				/*12  */
  evKeyNC, 				/*13  */
  evKeyNC, 				/*14  */
  evKeyNC, 				/*15  */
  evKeyNC, 			/*16  腰臀呵护*/
  evKeyNC, 		/*17  泰式拉伸*/
  evKeyNC, 			/*18  摇摆舒眠*/
};

//#pragma arm section rwdata = "RAM_KEEP"
//#pragma arm section zidata = "RAM_KEEP"
CDP_CenVoiceFrame_t CDP_AckVoice;
CDP_CenVoiceFrame_t *pCDP_AckVoice = &CDP_AckVoice;
CDP_CenVoice_t CDP_CtrlUnit;
CDP_CenVoice_t *pCDP_CtrlUnit = &CDP_CtrlUnit;
/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
#define AutoMassageSum	12
/*
************************************************************************************************************************
* 函数名称 : SendDataToVoice                                                                                                    
* 功能描述 : 通信数据包   之    中心板 <--> 蓝牙  发送数据处理                                                                              
* 输入参数 : rescmd命令码，resdatabuffer数据区地址，datalen数据长度                                                                 
* 返回参数 : 无                                                             
* 补充说明 : 收到数据立即回复                                                                                        
************************************************************************************************************************
*/
//void	SendDataToVoice(uint8_t rescmd,uint8_t *resdatabuffer,uint8_t datalen)
//{
//	uint8_t checksum;
//	uint8_t i,j;
//	uint8_t TxLen;
//	
//	if(CEN_VOICE_VoiceVal_0xa0 != rescmd && CEN_VOICE_ORDER_0xa1 != rescmd && CEN_VOICE_VER_0xa3 != rescmd
//	&& CEN_VOICE_CLOSE_0xa4 != rescmd && CEN_VOICE_DISCERN_ONOFF_0xa5 != rescmd
//	&& CEN_VOICE_VOLUME_0xa6 != rescmd && CEN_VOICE_WIFIDATA_0xa8 != rescmd)
//	{
//		return;
//	}	
//	
//	TxLen = 0;
//    /*帧头*/
//    CDP_CtrlUnit.TxBuf[TxLen++] = VOICE_CEN_FRAME_HEAD;  
//    /*命令码*/
//    CDP_CtrlUnit.TxBuf[TxLen++] = rescmd;               
//    /*数据长度*/
//    CDP_CtrlUnit.TxBuf[TxLen++] = datalen;              
//    /*数据内容*/
//    if(datalen>0)                                       
//	{
//    	for(j=0;j<datalen;j++)
//    	{
//    	    CDP_CtrlUnit.TxBuf[TxLen++] = *(resdatabuffer+j);
//    	}
//	}
//	
//	//最大发送长度限制
//	if(TxLen>CEN_TO_Voice_TXBUF_SIZE)
//	    TxLen=CEN_TO_Voice_TXBUF_SIZE;
//	    
//	/*校验码计算*/
//	checksum = 0;
//	for(i=0; i<TxLen; i++)
//	{
//		checksum += CDP_CtrlUnit.TxBuf[i];
//	}
//	CDP_CtrlUnit.TxBuf[TxLen++] = checksum;
//	CDP_CtrlUnit.TxLen = TxLen;
//	BSP_UART_TxData(CEN_Voice_UART_PORT, CDP_CtrlUnit.TxBuf, CDP_CtrlUnit.TxLen);	
//}



/*
************************************************************************************************************************
* 函数名称 : SetVoiceStopPlayNetworkAudio                                                                                                    
* 功能描述 : 置起进入串口配网模式标志位                                                                          
* 输入参数 :                                                                 
* 返回参数 : 无                                                             
* 补充说明 : 通过该标志位判断发送配网指令给语音板                                                                                       
************************************************************************************************************************
*/
void SetVoiceStopPlayNetworkAudio(void)
{
	CDP_CtrlUnit.CSFlag.Bit.StopPlayNetworkAudioFlag = TRUE;
}


void	CenSendDataToVoice(uint8_t rescmd,uint8_t *resdatabuffer,uint8_t datalen)
{
	Uchar i;
	Uchar *wp;
	Uchar CheckSum = 0;
	wp = &CDP_AckVoice.Head;
	*wp++ = VOICE_CEN_FRAME_HEAD;
	*wp++ = rescmd;
	*wp++ = datalen;
	for(i = 0;i<datalen;i++)
	{
		*wp++ = *(resdatabuffer + i);
		CheckSum +=  *(resdatabuffer + i);
	}
	CheckSum += VOICE_CEN_FRAME_HEAD + rescmd +datalen;
	*wp = CheckSum;

	 BSP_UART_TxData(CEN_Voice_UART_PORT,&CDP_AckVoice.Head, (CEN_TO_Voice_TX_BASE_SIZE+datalen));	 
}
/*
************************************************************************************************************************
* 函数名称 : VoiceOrder0xb1RxHandle                                                                                                    
* 功能描述 : 接收0xb1语音指令处理函数                                                                              
* 输入参数 : OrderH指令高字节，OrderL指令低字节                                                                 
* 返回参数 : void                                                            
* 补充说明 :                                                                                                 
************************************************************************************************************************
*/
void VoiceOrder0xb1RxHandle(Uchar OrderH,Uchar OrderL)
{
    static Uchar Server,RandomAutoTemp,WakeUpTemp,CurrentProgramTemp;
    static Uchar temp[2],VoiceValRetryHis[2],AutoMassageTemp;
    Uchar RandomAutoTempHis,RandomAutoTempCount = 0;
    if(!VoiceOnOffFlag)
    {
	if(OrderL != VOICEORDER_0xb1_OpenVoice)
		OrderL = 0x00;
    }
    if(OrderL == 0)
    {
		 temp[0]=0x00;
		  temp[1]=0x00;
    }
    else if(VOICEORDER_0xb1_WakeUpO == OrderL )
    {
        temp[0]=0x00;
        if(VOICEORDER_0xb1_WakeUpO == OrderL)
        {
//            if(CDP_CtrlUnit.CSFlag.Bit.VoiceWakeUpStateFlag == FALSE || !SystemRunFlag)
            {
                temp[1]=VOICEVal_0xa0_WakeUpO;
            }
//            else
//            {
//                WakeUpTemp++;
//                if(WakeUpTemp > 1)
//                {
//                    WakeUpTemp=0;
//                }
//                
//                if(WakeUpTemp==0)
//                {
//                    temp[1]=VOICEVal_0xa0_ImHere;
//                }
//                else if(WakeUpTemp==1)
//                {
//                    temp[1]=VOICEVal_0xa0_Here;
//                }
//                
//            }
            //temp[1]=VOICEVal_0xa0_WakeUpO;
            Server = VOICEORDER_0xb1_WakeUpO;
            
	        CDP_CtrlUnit.CSFlag.Bit.VoiceWakeUpStateFlag = TRUE;

        }
        //if(SystemRunFlag)   //开机情况下，不执行
        //{    
            OrderL = 0x00;  //唤醒指令不开机
        //}
    }
    else if(VOICEORDER_0xb1_PowerOn == OrderL)
    {
        temp[0]=0x00;
        temp[1]=VOICEVal_0xa0_PowerOn;
        
        if(SystemRunFlag)  //开机情况下，不执行
        {    
            OrderL = 0x00;
        }
         else if(!SystemRunFlag && !(CorePositionTopFlag && BackSpikeResetFlag && FeetSpikeResetFlag))  //关机复位过程中不执行
	 {    
	        temp[0]=0x00;
		 temp[1] = VOICEVal_0xa0_ChairRest;
	        OrderL = 0x00;
	  }
	 else
	 {
		KeyPower();
		OrderL = 0x00;
	 }
//	else if(!SystemRunFlag && ChildLockFlag)
//	{
//		temp[0]=0x04;
//		temp[1] = VOICEVal_0xa0_ChildClockOpen;
//	       OrderL = 0x00;
//	}
    }
    else if(VOICEORDER_0xb1_PowerOff == OrderL)
    {
        temp[0]=0x00;
        temp[1]=VOICEVal_0xa0_PowerOff;
        
        if(!SystemRunFlag)  //关机情况下，不执行
        {    
            OrderL = 0x00;
        }
    }
    else if(VOICEORDER_0xb1_Pause == OrderL)
    {
        temp[0]=0x00;
        temp[1]=VOICEVal_0xa0_Pause;
        
        if(PauseFlag)  //暂停情况下，不执行
        {    
            OrderL = 0x00;
        }          
    }
    else if(VOICEORDER_0xb1_PauseResume == OrderL)
    {
        temp[0]=0x00;
        temp[1]=VOICEVal_0xa0_PauseResume;
        
        if(!PauseFlag)  //不是暂停情况下，不执行
        {    
            OrderL = 0x00;
        }          
    } 
//    else if(VOICEORDER_0xb1_VolumeAdd == OrderL||VOICEORDER_0xb1_VolumeDec == OrderL)
//    {
//        temp[0]=0x00;
//        if(VOICEORDER_0xb1_VolumeAdd == OrderL)
//        {    
//            temp[1]=VOICEVal_0xa0_VolumeAdd;
//        }
//        else if(VOICEORDER_0xb1_VolumeDec == OrderL)
//        {
//            temp[1]=VOICEVal_0xa0_VolumeDec; 
//        }
//        OrderL = 0x00;//语音模块自己调整，不执行动作
//    }

 	else if(VOICEORDER_0xb1_OpenVoice == OrderL)
    {
        temp[0]=0x00;
        temp[1]=VOICEVal_0xa0_OpenVoice;
	if(VoiceOnOffFlag)
        	OrderL = 0x00;//自己控制,按键表格不执行
    }
	else if(VOICEORDER_0xb1_CloseVoice == OrderL)
    {
        temp[0]=0x00;
        temp[1]=VOICEVal_0xa0_CloseVoice;
        if(!VoiceOnOffFlag)
        	OrderL = 0x00;//自己控制,按键表格不执行
    }
 
	else if(VOICEORDER_0xb1_BlueToothOn == OrderL)
    { 
        temp[0]=0x00;
        temp[1]=VOICEVal_0xa0_BlueToothOn;
	if(GetBlueToothSendCmdState(BLUETOOTH_SWITCH_STATE))
	{
		OrderL = 0x00;
	}
    }
	else if(VOICEORDER_0xb1_BlueToothOff == OrderL)
    {
        temp[0]=0x00;
        temp[1]=VOICEVal_0xa0_BlueToothOff;
	if(!GetBlueToothSendCmdState(BLUETOOTH_SWITCH_STATE))
	{
		OrderL = 0x00;
	}
    }
  
    else if(VOICEORDER_0xb1_WakeUpEnd == OrderL)
    {
        temp[0]=0x00;
        temp[1]=0x00;
        OrderL = 0x00;//自己控制,按键表格不执行
        CDP_CtrlUnit.CSFlag.Bit.VoiceWakeUpStateFlag = FALSE;//清唤醒标志位
        return;//无回复语音
    }
   
    else if(PauseFlag)  //暂停情况下，不执行以下函数功能。
    {    
        temp[0]=0x00;
	    temp[1] = VOICEVal_0xa0_UnsupportedProgram;
        OrderL = 0x00;
    }

    //以上不管暂停状态，都执行/////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    //以下暂停时不执行/////////////////////////////////////////////////////////////////////////  
    else if(VOICEORDER_0xb1_BackRiseFeetRecline == OrderL||VOICEORDER_0xb1_BackReclineFeetRise == OrderL)
    {
    	temp[0]=0x00;
        if((gbCoreGasSpikeAutoFunction.All>0) ||!BackSpikeResetFlag  || !FeetSpikeResetFlag || PauseFlag)
    	{
            temp[1] = VOICEVal_0xa0_UnsupportedProgram;
    	} 	
    	else if((VOICEORDER_0xb1_BackRiseFeetRecline == OrderL))
    	{
            if(gBackSpikePointCount == B0 && gFeetSpikePointCount == F0)
            {    
                temp[1] = VOICEVal_0xa0_SpikeAdjLimit; 
            }
            else
            {
                SpikeAngleSet(((gBackSpikePointCount >= B0+2)?(gBackSpikePointCount-2): B0),((gFeetSpikePointCount >= F0+2)?(gFeetSpikePointCount-2): F0),KEEP);
                temp[1] = VOICEVal_0xa0_SpikeAdj1; 
            }
    	}
    	else if((VOICEORDER_0xb1_BackReclineFeetRise == OrderL))
    	{
            if(gBackSpikePointCount == B15 && gFeetSpikePointCount == F13)
            {    
                temp[1] = VOICEVal_0xa0_SpikeAdjLimit; 
            }
            else
            {
                SpikeAngleSet(((gBackSpikePointCount+2 >= B15)? B15:(gBackSpikePointCount+2)),((gFeetSpikePointCount+2 >= F13) ? F13:(gFeetSpikePointCount+2)),KEEP);
                temp[1] = VOICEVal_0xa0_SpikeAdj2; 
            }
    	}
        OrderL = 0x00;//自己控制,按键表格不执行
    }

    else if(!SystemRunFlag && !(CorePositionTopFlag && BackSpikeResetFlag && FeetSpikeResetFlag))  //关机复位过程中不执行
    {    
        temp[0]=0x00;
	    temp[1] = VOICEVal_0xa0_ChairRest;
        OrderL = 0x00;
    }
    else if(VOICEORDER_0xb1_FlexAdd == OrderL || VOICEORDER_0xb1_FlexDec == OrderL)
    {
        temp[0]=0x00;
    	if(!SystemRunFlag||PauseFlag||BackScanningFlag)
	{
            temp[1]=VOICEVal_0xa0_UnsupportedProgram;
	}
        else
        {
        
	        if(VOICEORDER_0xb1_FlexAdd == OrderL)
	        {
			if(gbCoreAutoFunction.All > 0||gbCoreGasSpikeAutoFunction.All > 0||gbUserDefinedAutoFunction.All > 0)
			{
				gCurveIncDecLevel += 2;
			
				if(gCurveIncDecLevel > 11)
				{
//					 temp[1]=VOICEVal_0xa0_SpikeAdjLimit;
					 temp[1]=VOICEVal_0xa0_SrtengthDec;
					gCurveIncDecLevel = 1;
				}
				else if(gCurveIncDecLevel == 11)
				{
					 temp[1]=VOICEVal_0xa0_SrtengthAdd;
					gCurveIncDecLevel = 10;
				}
				else
				{
					 temp[1]=VOICEVal_0xa0_SrtengthAdd;
				}
			}
			else
			{
				gFlexLevelSet++;
				if(gFlexLevelSet > 5)
				{
//					 temp[1]=VOICEVal_0xa0_SpikeAdjLimit;
					 temp[1]=VOICEVal_0xa0_SrtengthDec;
					gFlexLevelSet = 0;
					if(Tap1RunFlag || Tap2RunFlag || Clap1RunFlag || Clap2RunFlag ||Shiatsu1RunFlag || Shiatsu2RunFlag ||Swedish1RunFlag || Swedish2RunFlag ||DualAction1RunFlag || DualAction2RunFlag)
					{
						if(gFlexLevelSet < 1)
						{
							gFlexLevelSet = 1;
						}
					}
				}
				else
				{
					 temp[1]=VOICEVal_0xa0_SrtengthAdd;
				}
			}

	        }
//		{
//			if(gbCoreAutoFunction.All > 0||gbCoreGasSpikeAutoFunction.All > 0||gbUserDefinedAutoFunction.All > 0)
//			{
//				gCurveIncDecLevel += 2;
//			
//				if(gCurveIncDecLevel > 10)
//				{
//					 temp[1]=VOICEVal_0xa0_SpikeAdjLimit;
//					gCurveIncDecLevel = 10;
//				}
//				else
//				{
//					 temp[1]=VOICEVal_0xa0_SrtengthAdd;
//				}
//			}
//			else
//			{
//				gFlexLevelSet++;
//				if(gFlexLevelSet > 5)
//				{
//					 temp[1]=VOICEVal_0xa0_SpikeAdjLimit;
//					gFlexLevelSet = 5;
//				}
//				else
//				{
//					 temp[1]=VOICEVal_0xa0_SrtengthAdd;
//				}
//			}

//	        }
	        else if(VOICEORDER_0xb1_FlexDec == OrderL)
	        {    
	    		if(gbCoreAutoFunction.All > 0||gbCoreGasSpikeAutoFunction.All > 0||gbUserDefinedAutoFunction.All > 0)
			{
				//分为10 、9 、7 、5 、3 、1 这6档
				if(gCurveIncDecLevel == 10)
				{
					gCurveIncDecLevel = 9;
				}
				else
				{
					gCurveIncDecLevel -= 2;
				}
				
				if(gCurveIncDecLevel <  1 || gCurveIncDecLevel > 10)
				{
//					 temp[1]=VOICEVal_0xa0_SpikeAdjLimit;
					temp[1]=VOICEVal_0xa0_SrtengthAdd;
					gCurveIncDecLevel = 10;
				}
				else
				{
					 temp[1]=VOICEVal_0xa0_SrtengthDec;
				}
			}
			else
			{
				gFlexLevelSet--;
				if(gFlexLevelSet > 5)
				{
//					 temp[1]=VOICEVal_0xa0_SpikeAdjLimit;
					temp[1]=VOICEVal_0xa0_SrtengthAdd;
					gFlexLevelSet = 5;
				}
				else
				{
					 temp[1]=VOICEVal_0xa0_SrtengthDec;
				}

				if(Tap1RunFlag || Tap2RunFlag || Clap1RunFlag || Clap2RunFlag ||Shiatsu1RunFlag || Shiatsu2RunFlag ||Swedish1RunFlag || Swedish2RunFlag ||DualAction1RunFlag || DualAction2RunFlag)
				{
					if(gFlexLevelSet < 1)
					{
						gFlexLevelSet = 5;
						temp[1]=VOICEVal_0xa0_SrtengthAdd;
					}
				}
			}
	        } 
//		{    
//	    		if(gbCoreAutoFunction.All > 0||gbCoreGasSpikeAutoFunction.All > 0||gbUserDefinedAutoFunction.All > 0)
//			{
//				//分为10 、9 、7 、5 、3 、1 这6档
//				if(gCurveIncDecLevel == 10)
//				{
//					gCurveIncDecLevel = 9;
//				}
//				else
//				{
//					gCurveIncDecLevel -= 2;
//				}
//				
//				if(gCurveIncDecLevel <  1 || gCurveIncDecLevel > 10)
//				{
//					 temp[1]=VOICEVal_0xa0_SpikeAdjLimit;
//					gCurveIncDecLevel = 1;
//				}
//				else
//				{
//					 temp[1]=VOICEVal_0xa0_SrtengthDec;
//				}
//			}
//			else
//			{
//				gFlexLevelSet--;
//				if(gFlexLevelSet > 5)
//				{
//					 temp[1]=VOICEVal_0xa0_SpikeAdjLimit;
//					gFlexLevelSet = 0;
//				}
//				else
//				{
//					 temp[1]=VOICEVal_0xa0_SrtengthDec;
//				}

//				if(Tap1RunFlag || Tap2RunFlag || Clap1RunFlag || Clap2RunFlag ||Shiatsu1RunFlag || Shiatsu2RunFlag ||Swedish1RunFlag || Swedish2RunFlag ||DualAction1RunFlag || DualAction2RunFlag)
//				{
//					if(gFlexLevelSet < 1)
//					{
//						gFlexLevelSet = 1;
//						temp[1]=VOICEVal_0xa0_SpikeAdjLimit;
//					}
//				}
//			}
//	        } 
        
        }
        OrderL = 0x00;//自己控制,按键表格不执行
    }    
    
    CDP_CtrlUnit.TxVoiceVal[0] = temp[0];//保存最新需要重发的数据
    CDP_CtrlUnit.TxVoiceVal[1] = temp[1];
    
    //如果重发的数据发生变化，则原来数据的重发次数清零
    if((VoiceValRetryHis[0] != temp[0]) || (VoiceValRetryHis[1] != temp[1]))
    {
        VoiceValRetryHis[0] = temp[0];
        VoiceValRetryHis[1] = temp[1];
	    CDP_CtrlUnit.RetryDelayTimer = 0;
	    CDP_CtrlUnit.RetryTimes = 0;
    }
   
   	
    CenSendDataToVoice(CEN_VOICE_VoiceVal_0xa0,temp,CEN_VOICE_VoiceVal_0xa0_DataLength);       //播放语音
    CDP_CtrlUnit.CSFlag.Bit.VoiceValNeedResFlag = TRUE;//需要应答
    
    VoiceValRetryTimerMS = 0;
    
	/*收到键值,点亮手控器,以免出现需操作两次的现象*/
    LCDLight_ON();
    
    if( OrderL > 0 )
    {    
    	if(((OrderL >= 0x51) &&(OrderL <= 0x5B)) ||((OrderL >= 0x60) &&(OrderL <= 0x62)))
    	{
    		AutoMassageTemp = OrderL-0x50;
		KeyPressEvent(AutoMassageTemp,(uint8_t*)VoiceAutoMassageKeyValTab,VoiceUse,sizeof(VoiceAutoMassageKeyValTab));	/*键值入队列处理*/
    	}
	else
	{
		//值太大了，特殊处理
		if(OrderL == VOICEORDER_0xb1_OpenVoice  || OrderL == VOICEORDER_0xb1_CloseVoice)
		{
			OrderL = OrderL - 0x5C;
		}
       	KeyPressEvent(OrderL,(uint8_t*)VoiceKeyValMapTab,VoiceUse,sizeof(VoiceKeyValMapTab));	/*键值入队列处理*/
	}
    }
}


void RetryProcess(void)
{//100ms
    //static Uchar RetryTimesAssistFlag,RetryTimesAssist1Flag;
	if(TRUE == CDP_CtrlUnit.CSFlag.Bit.VoiceWIFIDataNeedResFlag)
	{//需要应答标志位
        CDP_CtrlUnit.SendWifiDataRetryDelayTimer++;
        if(CDP_CtrlUnit.SendWifiDataRetryDelayTimer >= 10)  //1S未收到应答，则重发
        {
            CDP_CtrlUnit.SendWifiDataRetryDelayTimer = 0;
            CDP_CtrlUnit.CSFlag.Bit.RetrySendWIFIDataFlag = TRUE;
            
            VoiceValRetryTimeMSBuffer[CDP_CtrlUnit.SendWifiDataRetryTimes] = VoiceValRetryTimerMS;
            VoiceValRetryTimerMS = 0;
            
            CDP_CtrlUnit.SendWifiDataRetryTimes++;
        }

    	if(CDP_CtrlUnit.SendWifiDataRetryTimes >= 3)//最多重发三次
    	{
    	    CDP_CtrlUnit.CSFlag.Bit.VoiceWIFIDataNeedResFlag = FALSE;
    	}

        /*
	    //if(gTime100MS%2 == 0)
	    if(gTime1MS >= 50)//RetryProcess 50ms更新计时一次，首次重发延时1000ms中，可能会有25ms的误差
	    {
            if(RetryTimesAssist1Flag == 0)
            {
    	        RetryTimesAssist1Flag = 1;
    	        
    	        CDP_CtrlUnit.SendWifiDataRetryDelayTimer++;
    	        if(CDP_CtrlUnit.SendWifiDataRetryDelayTimer >= 10)  //1S未收到应答，则重发
    	        {
                    CDP_CtrlUnit.SendWifiDataRetryDelayTimer = 0;
    	            CDP_CtrlUnit.CSFlag.Bit.RetrySendWIFIDataFlag = TRUE;
    	            
    	            VoiceValRetryTimeMSBuffer[CDP_CtrlUnit.SendWifiDataRetryTimes] = VoiceValRetryTimerMS;
    	            VoiceValRetryTimerMS = 0;
    	            
    	            CDP_CtrlUnit.SendWifiDataRetryTimes++;
    	        }
	        }
	    }
	    else
	    {
	        RetryTimesAssist1Flag = 0;
	    }
        */   
	}
	else
	{
	    CDP_CtrlUnit.SendWifiDataRetryDelayTimer = 0;
	    CDP_CtrlUnit.SendWifiDataRetryTimes = 0;
	}
	

/////////////////////////////////////////////////////////////////////
	if(TRUE == CDP_CtrlUnit.CSFlag.Bit.VoiceValNeedResFlag)
	{//需要应答标志位
        CDP_CtrlUnit.RetryDelayTimer++;
        if(CDP_CtrlUnit.RetryDelayTimer >= 10)  //1S未收到应答，则重发
        {
            CDP_CtrlUnit.RetryDelayTimer = 0;
            CDP_CtrlUnit.CSFlag.Bit.RetrySendVoiceValFlag = TRUE;
            
            VoiceValRetryTimeMSBuffer[CDP_CtrlUnit.RetryTimes] = VoiceValRetryTimerMS;
            VoiceValRetryTimerMS = 0;
            
            CDP_CtrlUnit.RetryTimes++;
        }

    	if(CDP_CtrlUnit.RetryTimes >= 3)//最多重发三次
    	{
    	    CDP_CtrlUnit.CSFlag.Bit.VoiceValNeedResFlag = FALSE;
    	}

        /*
	    //if(gTime100MS%2 == 0)
	    if(gTime1MS >= 50)//RetryProcess 50ms更新计时一次，首次重发延时1000ms中，可能会有25ms的误差
	    {
            if(RetryTimesAssistFlag == 0)
            {
    	        RetryTimesAssistFlag = 1;
    	        
    	        CDP_CtrlUnit.RetryDelayTimer++;
    	        if(CDP_CtrlUnit.RetryDelayTimer >= 10)  //1S未收到应答，则重发
    	        {
                    CDP_CtrlUnit.RetryDelayTimer = 0;
    	            CDP_CtrlUnit.CSFlag.Bit.RetrySendVoiceValFlag = TRUE;
    	            
    	            VoiceValRetryTimeMSBuffer[CDP_CtrlUnit.RetryTimes] = VoiceValRetryTimerMS;
    	            VoiceValRetryTimerMS = 0;
    	            
    	            CDP_CtrlUnit.RetryTimes++;
    	        }
	        }
	    }
	    else
	    {
	        RetryTimesAssistFlag = 0;
	    }
        */    
	}
	else
	{
	    CDP_CtrlUnit.RetryDelayTimer = 0;
	    CDP_CtrlUnit.RetryTimes = 0;
	}
	
}



/*
************************************************************************************************************************
* 函数名称 : ReceiveDataFromVoice100ms                                                                                                    
* 功能描述 : 通信数据包 之  中心板 接收语音板数据处理                                                                              
* 输入参数 : void                                                                 
* 返回参数 : 无                                                             
* 补充说明 :                                                                                                 
************************************************************************************************************************
*/
//7506机型要求不出现"小慧"及"康美"相关字眼的语音播放

void	ReceiveDataFromVoice100ms(void)
{
    static Uchar temp[2],SendWifiDataToVoiceDelayTimer; 
    RetryProcess();  
    
    if(SendWifiDataToVoiceDelayTimer<255)
        SendWifiDataToVoiceDelayTimer++;
        
    if(TRUE == CDP_CtrlUnit.CSFlag.Bit.SetUARTConnectNetFlag)
    {//有重新串口配网首先执行
		CDP_CtrlUnit.CSFlag.Bit.SetUARTConnectNetFlag = FALSE;
		temp[0]=0x00;
		temp[1]=VOICEVal_0xa0_UARTNetConnect;
        CenSendDataToVoice(CEN_VOICE_VoiceVal_0xa0,temp,CEN_VOICE_VoiceVal_0xa0_DataLength);       //播放语音	
        SendWifiDataToVoiceDelayTimer = 0;
    }
    else if(TRUE == CDP_CtrlUnit.CSFlag.Bit.SendWifiDataToVoiceFlag && SendWifiDataToVoiceDelayTimer >= 40)//播完进入配网指令后，隔4s后发送配网数据
    {//网络数据发送后时间间隔。
		CDP_CtrlUnit.CSFlag.Bit.SendWifiDataToVoiceFlag = FALSE;
		CenSendDataToVoice(CEN_VOICE_WIFIDATA_0xa8,CDP_CtrlUnit.TxVoiceVal+2,CDP_CtrlUnit.TxVoiceValLen);
        CDP_CtrlUnit.CSFlag.Bit.VoiceWIFIDataNeedResFlag = TRUE;
        CDP_CtrlUnit.CSFlag.Bit.VoiceWakeUpStateFlag = TRUE;//进入配网模式后，默认是唤醒状态
    }
//    else if(TRUE == CDP_CtrlUnit.CSFlag.Bit.SetAPPConnectNetFlag)
//    {//有重新配网首先执行
//		CDP_CtrlUnit.CSFlag.Bit.SetAPPConnectNetFlag = FALSE;
//		temp[0]=0x00;
//		temp[1]=VOICEVal_0xa0_APPNetConnect;
//        CenSendDataToVoice(CEN_VOICE_VoiceVal_0xa0,temp,CEN_VOICE_VoiceVal_0xa0_DataLength);       //播放语音	
//        CDP_CtrlUnit.CSFlag.Bit.VoiceWakeUpStateFlag = TRUE;//进入配网模式后，默认是唤醒状态
//    }
//    else if(TRUE == CDP_CtrlUnit.CSFlag.Bit.StopPlayNetworkAudioFlag)
//    {//停止播放网络音频
//		CDP_CtrlUnit.CSFlag.Bit.StopPlayNetworkAudioFlag = FALSE;
//		temp[0]=0x00;
//		temp[1]=VOICEVal_0xa0_StopPlayNetworkAudio;
//        CenSendDataToVoice(CEN_VOICE_VoiceVal_0xa0,temp,CEN_VOICE_VoiceVal_0xa0_DataLength);       //播放语音	
//    }
    else if(TRUE == CDP_CtrlUnit.CSFlag.Bit.RxOrder0xb1OKFlag)
    {//成功接收语音指令，则先发送应答数据
        if(BSP_UART_TxState_Idle == BSP_UART_GetTxState(CEN_Voice_UART_PORT))
        {    
            CDP_CtrlUnit.CSFlag.Bit.RxOrder0xb1OKFlag = FALSE;  
    		VoiceOrder0xb1RxHandle(CDP_CtrlUnit.Rx0xb1Order[0],CDP_CtrlUnit.Rx0xb1Order[1]);		    
        }
    }    
	else if(TRUE == CDP_CtrlUnit.CSFlag.Bit.RxVoiceDataOKFlag)
	{//成功接收数据，包括语音指令、各种状态数据和应答数据等
		CDP_CtrlUnit.CSFlag.Bit.RxVoiceDataOKFlag = FALSE;
		
		gVoiceLoseLinkTime = 0;
		switch(CDP_CtrlUnit.RxBuf[VOICE_CEN_CMD_OFFSET])
		{
			case VOICE_CEN_VoiceVal_0xb0://收到语音板应答码，没回应或有错需重发，重发三次
			    if((0xff == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET]) && (0xff == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET1]))
			    {
		            CDP_CtrlUnit.CSFlag.Bit.VoiceValNeedResFlag = FALSE;//应答成功，无需重发
			    }
			    else
			    {//应答出错，要重新发送
			        CDP_CtrlUnit.CSFlag.Bit.VoiceValNeedResFlag = TRUE;//接收错误，要重新发送			    
			    }
				break;
				
			case VOICE_CEN_ORDER_0xb1://收到语音指令 
				CDP_CtrlUnit.Rx0xb1Order[0]= CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET];
				CDP_CtrlUnit.Rx0xb1Order[1]= CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET+1];
				//if(!(CDP_CtrlUnit.Rx0xb1Order[0] == 0x00 && (CDP_CtrlUnit.Rx0xb1Order[1] ==VOICEORDER_0xb1_NetConnectOk || CDP_CtrlUnit.Rx0xb1Order[1] ==VOICEORDER_0xb1_NetConnectFault )))
				//{
				    /*回复指令接收成功*/
    				temp[0]=0xff;
    				temp[1]=0xff;
    				CenSendDataToVoice(CEN_VOICE_ORDER_0xa1,temp,CEN_VOICE_ORDER_0xa1_DataLength);
    				
                    if( CDP_CtrlUnit.Rx0xb1Order[0] == 0x00 && CDP_CtrlUnit.Rx0xb1Order[1] ==VOICEORDER_0xb1_PowerOff)
                    {//关机同时关闭网络音频，需要在播放关机语音之前发送。然后再发送播放关机指令语音
                        SetVoiceStopPlayNetworkAudio();//关机同时关闭网络音频
                    }

                    CDP_CtrlUnit.CSFlag.Bit.RxOrder0xb1OKFlag = TRUE; 
                //}
				/*指令处理函数*/
				//VoiceOrder0xb1RxHandle(CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET],CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET+1]);		    

				break;
				
			case VOICE_CEN_VER_0xb3:    //查询语音版本号,不需要重发
				
				break;
				
			case VOICE_CEN_CLOSE_0xb4:  //关闭语音播放关闭
			    if(0x88 == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET])       //关闭成功
				{
				
				}
			    else if(0xee == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET])  //关闭失败
			    {
			    
			    }
				break;
				
			case VOICE_CEN_DISCERN_ONOFF_0xb5: //开启或关闭语音识别应答，开启直接识别，关闭需唤醒才能识别
			    if(0x08 == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET])       //关闭成功
				{
				
				}
			    else if(0x0e == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET])  //关闭失败
			    {
			    
			    }
			    
			    if(0x18 == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET])       //开启成功
				{
				
				}
			    else if(0x1e == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET])  //开启失败
			    {
			    
			    }
				break;
				
			case VOICE_CEN_VOLUME_0xb6:     //语音音量调节应答
			    if(0x88 == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET])   //音量调节成功
                {
                
                }
				break;
				
			case VOICE_CEN_HEARTBEAT_0xb7:  /*语音板发送心跳包，无需回复*/
				
				break;
				
			case VOICE_CEN_WIFIDATA_0xb8:  //收到语音板应答码，没回应或有错需重发，重发三次
			    if((0xff == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET]) && (0xff == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET1]))
			    {//应答成功，无需重发
		            CDP_CtrlUnit.CSFlag.Bit.VoiceWIFIDataNeedResFlag = FALSE;//应答成功，无需重发
			    }
			    else
			    {//应答出错，要重新发送
			        CDP_CtrlUnit.CSFlag.Bit.VoiceWIFIDataNeedResFlag = TRUE;//接收错误，要重新发送			    
			    }
				break;

			default :
				break;
		}
	}
    else if(TRUE == CDP_CtrlUnit.CSFlag.Bit.RetrySendVoiceValFlag)
    {//重发语音播报数据
		CDP_CtrlUnit.CSFlag.Bit.RetrySendVoiceValFlag = FALSE;
        CenSendDataToVoice(CEN_VOICE_VoiceVal_0xa0,CDP_CtrlUnit.TxVoiceVal,CEN_VOICE_VoiceVal_0xa0_DataLength);       //播放语音	
    }
    else if(TRUE == CDP_CtrlUnit.CSFlag.Bit.RetrySendWIFIDataFlag)
    {//重发配网数据
		CDP_CtrlUnit.CSFlag.Bit.RetrySendWIFIDataFlag = FALSE;
		CenSendDataToVoice(CEN_VOICE_WIFIDATA_0xa8,CDP_CtrlUnit.TxVoiceVal+2,CDP_CtrlUnit.TxVoiceValLen);
    }

}

void VoiceVariableRefresh1ms(void)
{
	//static Uint16 sBTNothingReceiveTimerMS;
	if(CDP_CtrlUnit.VoiceNothingReceiveTimerMS<255)
	{
		CDP_CtrlUnit.VoiceNothingReceiveTimerMS++;
	}

}

/*
************************************************************************************************************************
* 函数名称 : CDP_CenBlue_ByteRx                                                                                                    
* 功能描述 : 通信数据包   之    中心板 <--> 语音板  字节接收处理                                                                              
* 输入参数 : RxByte -- 收到的字节数据                                                                    
* 返回参数 : 无                                                             
* 补充说明 : 该函数必须通过BSP_UART_RegRxByteCB()注册给BSP层，以便在串口接收字节中断中调用。                                                                                                  
************************************************************************************************************************
*/
void CDP_CenVoice_ByteRx(uint8_t RxByte)
{
    uint8_t i;
    uint8_t checksum;
    	if(CDP_CtrlUnit.VoiceNothingReceiveTimerMS > 10)
	{
		CDP_CtrlUnit.RxStep = 0;
		CDP_CtrlUnit.RxLen = 0;
	}
	CDP_CtrlUnit.VoiceNothingReceiveTimerMS = 0;
	
	switch(CDP_CtrlUnit.RxStep)
	{
		case VoiceCen_RX_STEP_SEARCH_HEAD: 
			CDP_CtrlUnit.RxLen = 0;
			if(VOICE_CEN_FRAME_HEAD == RxByte)
			{
				CDP_CtrlUnit.RxBuf[CDP_CtrlUnit.RxLen++] = RxByte;
				CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_JUDGE_CMD;
			}
			break;
		case VoiceCen_RX_STEP_JUDGE_CMD:
			if((VOICE_CEN_VoiceVal_0xb0 == RxByte)||(VOICE_CEN_ORDER_0xb1 == RxByte)
			||(VOICE_CEN_VER_0xb3 == RxByte)||(VOICE_CEN_CLOSE_0xb4 == RxByte)
			||(VOICE_CEN_DISCERN_ONOFF_0xb5 == RxByte)||(VOICE_CEN_VOLUME_0xb6 == RxByte)
			||(VOICE_CEN_HEARTBEAT_0xb7 == RxByte)||(VOICE_CEN_WIFIDATA_0xb8 == RxByte))
			{
			    CDP_CtrlUnit.RxBuf[CDP_CtrlUnit.RxLen++] = RxByte;
			    CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_JUDGE_DATALEN;   /*去判断数据长度*/
			}
			else
			{
			    CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_SEARCH_HEAD;     /*命令错，重新搜索命令头*/
			}  
			break;
		case VoiceCen_RX_STEP_JUDGE_DATALEN:
			if(((VOICE_CEN_VoiceVal_0xb0 == CDP_CtrlUnit.RxBuf[VOICE_CEN_CMD_OFFSET])&&(VOICE_CEN_VoiceVal_0xb0_DataLength == RxByte))
			 ||((VOICE_CEN_ORDER_0xb1 == CDP_CtrlUnit.RxBuf[VOICE_CEN_CMD_OFFSET])&&(VOICE_CEN_ORDER_0xb1_DataLength == RxByte)) 
			 ||((VOICE_CEN_VER_0xb3 == CDP_CtrlUnit.RxBuf[VOICE_CEN_CMD_OFFSET])&&(VOICE_CEN_VER_0xb3_DataLength == RxByte)) 
			 ||((VOICE_CEN_CLOSE_0xb4 == CDP_CtrlUnit.RxBuf[VOICE_CEN_CMD_OFFSET])&&(VOICE_CEN_CLOSE_0xb4_DataLength == RxByte)) 
			 ||((VOICE_CEN_DISCERN_ONOFF_0xb5 == CDP_CtrlUnit.RxBuf[VOICE_CEN_CMD_OFFSET])&&(VOICE_CEN_DISCERN_ONOFF_0xb5_DataLength == RxByte)) 
			 ||((VOICE_CEN_VOLUME_0xb6 == CDP_CtrlUnit.RxBuf[VOICE_CEN_CMD_OFFSET])&&(VOICE_CEN_VOLUME_0xb6_DataLength == RxByte)) 
			 ||((VOICE_CEN_HEARTBEAT_0xb7 == CDP_CtrlUnit.RxBuf[VOICE_CEN_CMD_OFFSET])&&(VOICE_CEN_HEARTBEAT_0xb7_DataLength == RxByte))
			 ||((VOICE_CEN_WIFIDATA_0xb8 == CDP_CtrlUnit.RxBuf[VOICE_CEN_CMD_OFFSET])&&(VOICE_CEN_WIFIDATA_0xb8_DataLength == RxByte))
			 )
			{
			    CDP_CtrlUnit.RxBuf[CDP_CtrlUnit.RxLen++] = RxByte;
			    CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_RCV_DATA;         /*长度对，去接收数据*/
			    if(CDP_CtrlUnit.RxBuf[VOICE_CEN_DATALEN_OFFSET] == 0)
			    {
			        CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_JUDGE_SUMCHECK;  /*接收键值完成，去判断累加和*/ 
			    }
			    CDP_CtrlUnit.RxDataLen = 0;
			}
			else
			{
			    CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_SEARCH_HEAD;      /*长度错，重新搜索命令头*/
			}  
			break;
			
		case VoiceCen_RX_STEP_RCV_DATA:
			CDP_CtrlUnit.RxBuf[CDP_CtrlUnit.RxLen++] = RxByte;
			CDP_CtrlUnit.RxDataLen++;
			if(CDP_CtrlUnit.RxDataLen >= CDP_CtrlUnit.RxBuf[VOICE_CEN_DATALEN_OFFSET])
			{
			    CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_JUDGE_SUMCHECK;  	 /*接收键值完成，去判断累加和*/
			}
			else
			{
			    CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_RCV_DATA;         /*长度对，去接收数据*/
			}
			break;
		
		case VoiceCen_RX_STEP_JUDGE_SUMCHECK:
			checksum = 0;
			for(i=0; i<CDP_CtrlUnit.RxLen; i++)
			{
			    checksum += CDP_CtrlUnit.RxBuf[i];
			}
			if(checksum == RxByte) /*帧接收成功==========================================================*/
			{
			    CDP_CtrlUnit.RxBuf[CDP_CtrlUnit.RxLen++] = RxByte;
			    //CDP_CtrlUnit.LinkLostTimeMs = 0;                              /*清链接丢失时间*/ 
			    CDP_CtrlUnit.CSFlag.Bit.RxVoiceDataOKFlag = TRUE;     
			}
			CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_SEARCH_HEAD;     
			break;
		
		default:
			CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_SEARCH_HEAD;
			break;
	}
			
}





