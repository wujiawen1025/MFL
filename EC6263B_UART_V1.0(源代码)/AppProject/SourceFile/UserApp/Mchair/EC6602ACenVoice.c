/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: EC6602ACenVoice.c
**
**    ��������: ���İ���������ͨ��Э��  
**
**    ��    ˾���ɷ�������
**
**    ��Ŀ���ƣ�                                                                                                        
**
**    ƽ̨��Ϣ��                                                                                                        
**
**    ��    �ߣ�                                                                                                     
**
**    ����˵��: ��IO�ھ���ɨ����ơ�                                                                                                     
**
**    �޸ļ�¼:  
**
========================================================================================================================
========================================================================================================================
*/

/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
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
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/
//#define TapMotorIsRunning()			(gbCoreManualFunction.All & 0x787F)
//#define KneadMotorIsRunning()		(gbCoreManualFunction.All & 0x1F80)

/*
========================================================================================================================
*�������������Ͷ��塿                              �������������Ͷ��塿                              �������������Ͷ��塿
========================================================================================================================
*/

/*
************************************************************************************************************************
* ���Ͷ��� :                                                                                                         
************************************************************************************************************************
*/


/*
========================================================================================================================
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
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
  evKeyPower,            	        /*1 ����С��*/
  evKeyPower,            	            /*2 ����*/
  evKeyPower,            	        /*3 �ػ�*/
  evKeyPower,		//evKeyBackRaiseFeetRecline,       /*4 ��������*/  //��ָ������д���,�������ִ��
  evKeyNC,		//evKeyBackReclineFeetRaise,       /*5 ���Ƚ���*/  //��ָ������д���,�������ִ��
  evKeyNC,		//evKeyStrengthSpeedAdd,   /*6 ǿ�ȼ���*/  //��ָ������д���,�������ִ��
  evKeyNC,		//evKeyStrengthSpeedDec, /*7 ǿ�ȼ���*/  //��ָ������д���,�������ִ��
  evKeyNC,                          /*8 �������ӣ��������Լ�����*/
  evKeyNC,                          /*9 �������٣��������Լ�����*/
  evKeyNC,                          /*10 �������,�ڴ������д���*/
  evKeyNC,//evKeyNeckShoulder,                /*11 ����*/
  evKeyNC,//evKeyArmsGas,                     /*12 �ֱ�*/
  evKeyNC,//evKeyBackLumbar,                  /*13 ����*/
  evKeyNC,//evKeyLumbar,                      /*14 ����*/
  evKeyNC,//evKeyButto,                       /*15 �β�*/
  evKeyNC,//evKeyFeetCalvesGas,               /*16 �ȽŲ�*/
  evKeyNC,            	    /*17 ��о�ֶ����� ����*/
  evKeyNC,                     /*18 ��о�ֶ����� ����*/
  evKeyNC,            		    /*19 ��о�ֶ����� �û�*/
  evKeyNC,                        /*20 ��о�ֶ����� ָѹ*/
  evKeyNC,           			    /*21 ����*/
  
  evKeyNC,                          /*22*/
  evKeyNC,                          /*23*/
  evKeyNC,                          /*24*/
  evKeyNC,                          /*25*/
  evKeyNC,                       /*26 ��ͣ*/
  evKeyNC,                       /*27 ȡ����ͣ*/
  evKeyNC,                    /*28 */
  evKeyNC,                  /*29 */
  evKeyNC,                   /*30 */
  evKeyNC,		 /*31 */
  evKeyNC,		 /*32 */
  evKeyNC,		 /*33������1*/
  evKeyNC,		/*34������2*/
  evKeyNC,			/*35 */
  evKeyNC,			/*36 */
  evKeyVoiceSwitch,		/*37 */
  evKeyVoiceSwitch,		/*38 */
  evKeyNC,                          /*39*/
  evKeyNC,                          /*40*/
  evKeyNC,                          /*41*/
  evKeyNC,                          /*42*/
  evKeyNC,                          /*43*/
  evKeyHeating,           		/*44 ��������*/
  evKeyHeating,           		/*45 �رռ���*/
};
static const uint8_t VoiceAutoMassageKeyValTab[] = 
{
  evKeyNC,                          /*0  */
  evKeyMasterCare,            		/*1 ȫ���滺*/
  evKeyOldMan,  				/*2 ����Ԫ��*/
  evKeyShoulderNeck,            	/*3 ����ģʽ*/
  evKeyBackBLumbarMassage,	/*4 ����ģʽ*/
  evKeyThaiMassage,			/*5 �⽳����*/
  evKeyNC,					/*6*/ 
  evKeySleep,		 			/*7 ҡ������*/ 
  evKeyFitness,                      	/*8 ����ģʽ*/
  evKeyWalk,          			/*9 ��֫ģʽ*/
  evKeyDeepMassage,        		/*10  �����ѹ*/
  evKeyJapanese, 				/*11  ��ʽ��Ħ*/
  evKeyNC, 				/*12  */
  evKeyNC, 				/*13  */
  evKeyNC, 				/*14  */
  evKeyNC, 				/*15  */
  evKeyNC, 			/*16  ���κǻ�*/
  evKeyNC, 		/*17  ̩ʽ����*/
  evKeyNC, 			/*18  ҡ������*/
};

//#pragma arm section rwdata = "RAM_KEEP"
//#pragma arm section zidata = "RAM_KEEP"
CDP_CenVoiceFrame_t CDP_AckVoice;
CDP_CenVoiceFrame_t *pCDP_AckVoice = &CDP_AckVoice;
CDP_CenVoice_t CDP_CtrlUnit;
CDP_CenVoice_t *pCDP_CtrlUnit = &CDP_CtrlUnit;
/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
#define AutoMassageSum	12
/*
************************************************************************************************************************
* �������� : SendDataToVoice                                                                                                    
* �������� : ͨ�����ݰ�   ֮    ���İ� <--> ����  �������ݴ���                                                                              
* ������� : rescmd�����룬resdatabuffer��������ַ��datalen���ݳ���                                                                 
* ���ز��� : ��                                                             
* ����˵�� : �յ����������ظ�                                                                                        
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
//    /*֡ͷ*/
//    CDP_CtrlUnit.TxBuf[TxLen++] = VOICE_CEN_FRAME_HEAD;  
//    /*������*/
//    CDP_CtrlUnit.TxBuf[TxLen++] = rescmd;               
//    /*���ݳ���*/
//    CDP_CtrlUnit.TxBuf[TxLen++] = datalen;              
//    /*��������*/
//    if(datalen>0)                                       
//	{
//    	for(j=0;j<datalen;j++)
//    	{
//    	    CDP_CtrlUnit.TxBuf[TxLen++] = *(resdatabuffer+j);
//    	}
//	}
//	
//	//����ͳ�������
//	if(TxLen>CEN_TO_Voice_TXBUF_SIZE)
//	    TxLen=CEN_TO_Voice_TXBUF_SIZE;
//	    
//	/*У�������*/
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
* �������� : SetVoiceStopPlayNetworkAudio                                                                                                    
* �������� : ������봮������ģʽ��־λ                                                                          
* ������� :                                                                 
* ���ز��� : ��                                                             
* ����˵�� : ͨ���ñ�־λ�жϷ�������ָ���������                                                                                       
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
* �������� : VoiceOrder0xb1RxHandle                                                                                                    
* �������� : ����0xb1����ָ�����                                                                              
* ������� : OrderHָ����ֽڣ�OrderLָ����ֽ�                                                                 
* ���ز��� : void                                                            
* ����˵�� :                                                                                                 
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
        //if(SystemRunFlag)   //��������£���ִ��
        //{    
            OrderL = 0x00;  //����ָ�����
        //}
    }
    else if(VOICEORDER_0xb1_PowerOn == OrderL)
    {
        temp[0]=0x00;
        temp[1]=VOICEVal_0xa0_PowerOn;
        
        if(SystemRunFlag)  //��������£���ִ��
        {    
            OrderL = 0x00;
        }
         else if(!SystemRunFlag && !(CorePositionTopFlag && BackSpikeResetFlag && FeetSpikeResetFlag))  //�ػ���λ�����в�ִ��
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
        
        if(!SystemRunFlag)  //�ػ�����£���ִ��
        {    
            OrderL = 0x00;
        }
    }
    else if(VOICEORDER_0xb1_Pause == OrderL)
    {
        temp[0]=0x00;
        temp[1]=VOICEVal_0xa0_Pause;
        
        if(PauseFlag)  //��ͣ����£���ִ��
        {    
            OrderL = 0x00;
        }          
    }
    else if(VOICEORDER_0xb1_PauseResume == OrderL)
    {
        temp[0]=0x00;
        temp[1]=VOICEVal_0xa0_PauseResume;
        
        if(!PauseFlag)  //������ͣ����£���ִ��
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
//        OrderL = 0x00;//����ģ���Լ���������ִ�ж���
//    }

 	else if(VOICEORDER_0xb1_OpenVoice == OrderL)
    {
        temp[0]=0x00;
        temp[1]=VOICEVal_0xa0_OpenVoice;
	if(VoiceOnOffFlag)
        	OrderL = 0x00;//�Լ�����,�������ִ��
    }
	else if(VOICEORDER_0xb1_CloseVoice == OrderL)
    {
        temp[0]=0x00;
        temp[1]=VOICEVal_0xa0_CloseVoice;
        if(!VoiceOnOffFlag)
        	OrderL = 0x00;//�Լ�����,�������ִ��
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
        OrderL = 0x00;//�Լ�����,�������ִ��
        CDP_CtrlUnit.CSFlag.Bit.VoiceWakeUpStateFlag = FALSE;//�廽�ѱ�־λ
        return;//�޻ظ�����
    }
   
    else if(PauseFlag)  //��ͣ����£���ִ�����º������ܡ�
    {    
        temp[0]=0x00;
	    temp[1] = VOICEVal_0xa0_UnsupportedProgram;
        OrderL = 0x00;
    }

    //���ϲ�����ͣ״̬����ִ��/////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    //������ͣʱ��ִ��/////////////////////////////////////////////////////////////////////////  
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
        OrderL = 0x00;//�Լ�����,�������ִ��
    }

    else if(!SystemRunFlag && !(CorePositionTopFlag && BackSpikeResetFlag && FeetSpikeResetFlag))  //�ػ���λ�����в�ִ��
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
				//��Ϊ10 ��9 ��7 ��5 ��3 ��1 ��6��
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
//				//��Ϊ10 ��9 ��7 ��5 ��3 ��1 ��6��
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
        OrderL = 0x00;//�Լ�����,�������ִ��
    }    
    
    CDP_CtrlUnit.TxVoiceVal[0] = temp[0];//����������Ҫ�ط�������
    CDP_CtrlUnit.TxVoiceVal[1] = temp[1];
    
    //����ط������ݷ����仯����ԭ�����ݵ��ط���������
    if((VoiceValRetryHis[0] != temp[0]) || (VoiceValRetryHis[1] != temp[1]))
    {
        VoiceValRetryHis[0] = temp[0];
        VoiceValRetryHis[1] = temp[1];
	    CDP_CtrlUnit.RetryDelayTimer = 0;
	    CDP_CtrlUnit.RetryTimes = 0;
    }
   
   	
    CenSendDataToVoice(CEN_VOICE_VoiceVal_0xa0,temp,CEN_VOICE_VoiceVal_0xa0_DataLength);       //��������
    CDP_CtrlUnit.CSFlag.Bit.VoiceValNeedResFlag = TRUE;//��ҪӦ��
    
    VoiceValRetryTimerMS = 0;
    
	/*�յ���ֵ,�����ֿ���,���������������ε�����*/
    LCDLight_ON();
    
    if( OrderL > 0 )
    {    
    	if(((OrderL >= 0x51) &&(OrderL <= 0x5B)) ||((OrderL >= 0x60) &&(OrderL <= 0x62)))
    	{
    		AutoMassageTemp = OrderL-0x50;
		KeyPressEvent(AutoMassageTemp,(uint8_t*)VoiceAutoMassageKeyValTab,VoiceUse,sizeof(VoiceAutoMassageKeyValTab));	/*��ֵ����д���*/
    	}
	else
	{
		//ֵ̫���ˣ����⴦��
		if(OrderL == VOICEORDER_0xb1_OpenVoice  || OrderL == VOICEORDER_0xb1_CloseVoice)
		{
			OrderL = OrderL - 0x5C;
		}
       	KeyPressEvent(OrderL,(uint8_t*)VoiceKeyValMapTab,VoiceUse,sizeof(VoiceKeyValMapTab));	/*��ֵ����д���*/
	}
    }
}


void RetryProcess(void)
{//100ms
    //static Uchar RetryTimesAssistFlag,RetryTimesAssist1Flag;
	if(TRUE == CDP_CtrlUnit.CSFlag.Bit.VoiceWIFIDataNeedResFlag)
	{//��ҪӦ���־λ
        CDP_CtrlUnit.SendWifiDataRetryDelayTimer++;
        if(CDP_CtrlUnit.SendWifiDataRetryDelayTimer >= 10)  //1Sδ�յ�Ӧ�����ط�
        {
            CDP_CtrlUnit.SendWifiDataRetryDelayTimer = 0;
            CDP_CtrlUnit.CSFlag.Bit.RetrySendWIFIDataFlag = TRUE;
            
            VoiceValRetryTimeMSBuffer[CDP_CtrlUnit.SendWifiDataRetryTimes] = VoiceValRetryTimerMS;
            VoiceValRetryTimerMS = 0;
            
            CDP_CtrlUnit.SendWifiDataRetryTimes++;
        }

    	if(CDP_CtrlUnit.SendWifiDataRetryTimes >= 3)//����ط�����
    	{
    	    CDP_CtrlUnit.CSFlag.Bit.VoiceWIFIDataNeedResFlag = FALSE;
    	}

        /*
	    //if(gTime100MS%2 == 0)
	    if(gTime1MS >= 50)//RetryProcess 50ms���¼�ʱһ�Σ��״��ط���ʱ1000ms�У����ܻ���25ms�����
	    {
            if(RetryTimesAssist1Flag == 0)
            {
    	        RetryTimesAssist1Flag = 1;
    	        
    	        CDP_CtrlUnit.SendWifiDataRetryDelayTimer++;
    	        if(CDP_CtrlUnit.SendWifiDataRetryDelayTimer >= 10)  //1Sδ�յ�Ӧ�����ط�
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
	{//��ҪӦ���־λ
        CDP_CtrlUnit.RetryDelayTimer++;
        if(CDP_CtrlUnit.RetryDelayTimer >= 10)  //1Sδ�յ�Ӧ�����ط�
        {
            CDP_CtrlUnit.RetryDelayTimer = 0;
            CDP_CtrlUnit.CSFlag.Bit.RetrySendVoiceValFlag = TRUE;
            
            VoiceValRetryTimeMSBuffer[CDP_CtrlUnit.RetryTimes] = VoiceValRetryTimerMS;
            VoiceValRetryTimerMS = 0;
            
            CDP_CtrlUnit.RetryTimes++;
        }

    	if(CDP_CtrlUnit.RetryTimes >= 3)//����ط�����
    	{
    	    CDP_CtrlUnit.CSFlag.Bit.VoiceValNeedResFlag = FALSE;
    	}

        /*
	    //if(gTime100MS%2 == 0)
	    if(gTime1MS >= 50)//RetryProcess 50ms���¼�ʱһ�Σ��״��ط���ʱ1000ms�У����ܻ���25ms�����
	    {
            if(RetryTimesAssistFlag == 0)
            {
    	        RetryTimesAssistFlag = 1;
    	        
    	        CDP_CtrlUnit.RetryDelayTimer++;
    	        if(CDP_CtrlUnit.RetryDelayTimer >= 10)  //1Sδ�յ�Ӧ�����ط�
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
* �������� : ReceiveDataFromVoice100ms                                                                                                    
* �������� : ͨ�����ݰ� ֮  ���İ� �������������ݴ���                                                                              
* ������� : void                                                                 
* ���ز��� : ��                                                             
* ����˵�� :                                                                                                 
************************************************************************************************************************
*/
//7506����Ҫ�󲻳���"С��"��"����"������۵���������

void	ReceiveDataFromVoice100ms(void)
{
    static Uchar temp[2],SendWifiDataToVoiceDelayTimer; 
    RetryProcess();  
    
    if(SendWifiDataToVoiceDelayTimer<255)
        SendWifiDataToVoiceDelayTimer++;
        
    if(TRUE == CDP_CtrlUnit.CSFlag.Bit.SetUARTConnectNetFlag)
    {//�����´�����������ִ��
		CDP_CtrlUnit.CSFlag.Bit.SetUARTConnectNetFlag = FALSE;
		temp[0]=0x00;
		temp[1]=VOICEVal_0xa0_UARTNetConnect;
        CenSendDataToVoice(CEN_VOICE_VoiceVal_0xa0,temp,CEN_VOICE_VoiceVal_0xa0_DataLength);       //��������	
        SendWifiDataToVoiceDelayTimer = 0;
    }
    else if(TRUE == CDP_CtrlUnit.CSFlag.Bit.SendWifiDataToVoiceFlag && SendWifiDataToVoiceDelayTimer >= 40)//�����������ָ��󣬸�4s������������
    {//�������ݷ��ͺ�ʱ������
		CDP_CtrlUnit.CSFlag.Bit.SendWifiDataToVoiceFlag = FALSE;
		CenSendDataToVoice(CEN_VOICE_WIFIDATA_0xa8,CDP_CtrlUnit.TxVoiceVal+2,CDP_CtrlUnit.TxVoiceValLen);
        CDP_CtrlUnit.CSFlag.Bit.VoiceWIFIDataNeedResFlag = TRUE;
        CDP_CtrlUnit.CSFlag.Bit.VoiceWakeUpStateFlag = TRUE;//��������ģʽ��Ĭ���ǻ���״̬
    }
//    else if(TRUE == CDP_CtrlUnit.CSFlag.Bit.SetAPPConnectNetFlag)
//    {//��������������ִ��
//		CDP_CtrlUnit.CSFlag.Bit.SetAPPConnectNetFlag = FALSE;
//		temp[0]=0x00;
//		temp[1]=VOICEVal_0xa0_APPNetConnect;
//        CenSendDataToVoice(CEN_VOICE_VoiceVal_0xa0,temp,CEN_VOICE_VoiceVal_0xa0_DataLength);       //��������	
//        CDP_CtrlUnit.CSFlag.Bit.VoiceWakeUpStateFlag = TRUE;//��������ģʽ��Ĭ���ǻ���״̬
//    }
//    else if(TRUE == CDP_CtrlUnit.CSFlag.Bit.StopPlayNetworkAudioFlag)
//    {//ֹͣ����������Ƶ
//		CDP_CtrlUnit.CSFlag.Bit.StopPlayNetworkAudioFlag = FALSE;
//		temp[0]=0x00;
//		temp[1]=VOICEVal_0xa0_StopPlayNetworkAudio;
//        CenSendDataToVoice(CEN_VOICE_VoiceVal_0xa0,temp,CEN_VOICE_VoiceVal_0xa0_DataLength);       //��������	
//    }
    else if(TRUE == CDP_CtrlUnit.CSFlag.Bit.RxOrder0xb1OKFlag)
    {//�ɹ���������ָ����ȷ���Ӧ������
        if(BSP_UART_TxState_Idle == BSP_UART_GetTxState(CEN_Voice_UART_PORT))
        {    
            CDP_CtrlUnit.CSFlag.Bit.RxOrder0xb1OKFlag = FALSE;  
    		VoiceOrder0xb1RxHandle(CDP_CtrlUnit.Rx0xb1Order[0],CDP_CtrlUnit.Rx0xb1Order[1]);		    
        }
    }    
	else if(TRUE == CDP_CtrlUnit.CSFlag.Bit.RxVoiceDataOKFlag)
	{//�ɹ��������ݣ���������ָ�����״̬���ݺ�Ӧ�����ݵ�
		CDP_CtrlUnit.CSFlag.Bit.RxVoiceDataOKFlag = FALSE;
		
		gVoiceLoseLinkTime = 0;
		switch(CDP_CtrlUnit.RxBuf[VOICE_CEN_CMD_OFFSET])
		{
			case VOICE_CEN_VoiceVal_0xb0://�յ�������Ӧ���룬û��Ӧ���д����ط����ط�����
			    if((0xff == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET]) && (0xff == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET1]))
			    {
		            CDP_CtrlUnit.CSFlag.Bit.VoiceValNeedResFlag = FALSE;//Ӧ��ɹ��������ط�
			    }
			    else
			    {//Ӧ�����Ҫ���·���
			        CDP_CtrlUnit.CSFlag.Bit.VoiceValNeedResFlag = TRUE;//���մ���Ҫ���·���			    
			    }
				break;
				
			case VOICE_CEN_ORDER_0xb1://�յ�����ָ�� 
				CDP_CtrlUnit.Rx0xb1Order[0]= CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET];
				CDP_CtrlUnit.Rx0xb1Order[1]= CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET+1];
				//if(!(CDP_CtrlUnit.Rx0xb1Order[0] == 0x00 && (CDP_CtrlUnit.Rx0xb1Order[1] ==VOICEORDER_0xb1_NetConnectOk || CDP_CtrlUnit.Rx0xb1Order[1] ==VOICEORDER_0xb1_NetConnectFault )))
				//{
				    /*�ظ�ָ����ճɹ�*/
    				temp[0]=0xff;
    				temp[1]=0xff;
    				CenSendDataToVoice(CEN_VOICE_ORDER_0xa1,temp,CEN_VOICE_ORDER_0xa1_DataLength);
    				
                    if( CDP_CtrlUnit.Rx0xb1Order[0] == 0x00 && CDP_CtrlUnit.Rx0xb1Order[1] ==VOICEORDER_0xb1_PowerOff)
                    {//�ػ�ͬʱ�ر�������Ƶ����Ҫ�ڲ��Źػ�����֮ǰ���͡�Ȼ���ٷ��Ͳ��Źػ�ָ������
                        SetVoiceStopPlayNetworkAudio();//�ػ�ͬʱ�ر�������Ƶ
                    }

                    CDP_CtrlUnit.CSFlag.Bit.RxOrder0xb1OKFlag = TRUE; 
                //}
				/*ָ�����*/
				//VoiceOrder0xb1RxHandle(CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET],CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET+1]);		    

				break;
				
			case VOICE_CEN_VER_0xb3:    //��ѯ�����汾��,����Ҫ�ط�
				
				break;
				
			case VOICE_CEN_CLOSE_0xb4:  //�ر��������Źر�
			    if(0x88 == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET])       //�رճɹ�
				{
				
				}
			    else if(0xee == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET])  //�ر�ʧ��
			    {
			    
			    }
				break;
				
			case VOICE_CEN_DISCERN_ONOFF_0xb5: //������ر�����ʶ��Ӧ�𣬿���ֱ��ʶ�𣬹ر��軽�Ѳ���ʶ��
			    if(0x08 == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET])       //�رճɹ�
				{
				
				}
			    else if(0x0e == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET])  //�ر�ʧ��
			    {
			    
			    }
			    
			    if(0x18 == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET])       //�����ɹ�
				{
				
				}
			    else if(0x1e == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET])  //����ʧ��
			    {
			    
			    }
				break;
				
			case VOICE_CEN_VOLUME_0xb6:     //������������Ӧ��
			    if(0x88 == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET])   //�������ڳɹ�
                {
                
                }
				break;
				
			case VOICE_CEN_HEARTBEAT_0xb7:  /*�����巢��������������ظ�*/
				
				break;
				
			case VOICE_CEN_WIFIDATA_0xb8:  //�յ�������Ӧ���룬û��Ӧ���д����ط����ط�����
			    if((0xff == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET]) && (0xff == CDP_CtrlUnit.RxBuf[VOICE_CEN_DATA_OFFSET1]))
			    {//Ӧ��ɹ��������ط�
		            CDP_CtrlUnit.CSFlag.Bit.VoiceWIFIDataNeedResFlag = FALSE;//Ӧ��ɹ��������ط�
			    }
			    else
			    {//Ӧ�����Ҫ���·���
			        CDP_CtrlUnit.CSFlag.Bit.VoiceWIFIDataNeedResFlag = TRUE;//���մ���Ҫ���·���			    
			    }
				break;

			default :
				break;
		}
	}
    else if(TRUE == CDP_CtrlUnit.CSFlag.Bit.RetrySendVoiceValFlag)
    {//�ط�������������
		CDP_CtrlUnit.CSFlag.Bit.RetrySendVoiceValFlag = FALSE;
        CenSendDataToVoice(CEN_VOICE_VoiceVal_0xa0,CDP_CtrlUnit.TxVoiceVal,CEN_VOICE_VoiceVal_0xa0_DataLength);       //��������	
    }
    else if(TRUE == CDP_CtrlUnit.CSFlag.Bit.RetrySendWIFIDataFlag)
    {//�ط���������
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
* �������� : CDP_CenBlue_ByteRx                                                                                                    
* �������� : ͨ�����ݰ�   ֮    ���İ� <--> ������  �ֽڽ��մ���                                                                              
* ������� : RxByte -- �յ����ֽ�����                                                                    
* ���ز��� : ��                                                             
* ����˵�� : �ú�������ͨ��BSP_UART_RegRxByteCB()ע���BSP�㣬�Ա��ڴ��ڽ����ֽ��ж��е��á�                                                                                                  
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
			    CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_JUDGE_DATALEN;   /*ȥ�ж����ݳ���*/
			}
			else
			{
			    CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_SEARCH_HEAD;     /*�����������������ͷ*/
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
			    CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_RCV_DATA;         /*���ȶԣ�ȥ��������*/
			    if(CDP_CtrlUnit.RxBuf[VOICE_CEN_DATALEN_OFFSET] == 0)
			    {
			        CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_JUDGE_SUMCHECK;  /*���ռ�ֵ��ɣ�ȥ�ж��ۼӺ�*/ 
			    }
			    CDP_CtrlUnit.RxDataLen = 0;
			}
			else
			{
			    CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_SEARCH_HEAD;      /*���ȴ�������������ͷ*/
			}  
			break;
			
		case VoiceCen_RX_STEP_RCV_DATA:
			CDP_CtrlUnit.RxBuf[CDP_CtrlUnit.RxLen++] = RxByte;
			CDP_CtrlUnit.RxDataLen++;
			if(CDP_CtrlUnit.RxDataLen >= CDP_CtrlUnit.RxBuf[VOICE_CEN_DATALEN_OFFSET])
			{
			    CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_JUDGE_SUMCHECK;  	 /*���ռ�ֵ��ɣ�ȥ�ж��ۼӺ�*/
			}
			else
			{
			    CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_RCV_DATA;         /*���ȶԣ�ȥ��������*/
			}
			break;
		
		case VoiceCen_RX_STEP_JUDGE_SUMCHECK:
			checksum = 0;
			for(i=0; i<CDP_CtrlUnit.RxLen; i++)
			{
			    checksum += CDP_CtrlUnit.RxBuf[i];
			}
			if(checksum == RxByte) /*֡���ճɹ�==========================================================*/
			{
			    CDP_CtrlUnit.RxBuf[CDP_CtrlUnit.RxLen++] = RxByte;
			    //CDP_CtrlUnit.LinkLostTimeMs = 0;                              /*�����Ӷ�ʧʱ��*/ 
			    CDP_CtrlUnit.CSFlag.Bit.RxVoiceDataOKFlag = TRUE;     
			}
			CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_SEARCH_HEAD;     
			break;
		
		default:
			CDP_CtrlUnit.RxStep = VoiceCen_RX_STEP_SEARCH_HEAD;
			break;
	}
			
}





