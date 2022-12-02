/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: EC6602ACenVoice.h                                                                                                       
**
**    ��������: ���İ���������ͨ��Э��                                                                                                      
**
**    ��    ˾��                                                                                                        
**
**    ��Ŀ���ƣ�                                                                                                        
**
**    ƽ̨��Ϣ��                                                                                                        
**
**    ��    �ߣ�                                                                                              
**
**    ����˵��:                                                                                                        
**
**    �޸ļ�¼:  
**
========================================================================================================================
========================================================================================================================
*/
#ifndef  _EC6602ACENVOICE_H_
#define  _EC6602ACENVOICE_H_


/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "bsp.h"


/*
========================================================================================================================
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/
#define  CEN_Voice_UART_PORT                    BSP_UART_Port3           /*���ô���*/

#define  Voice_TO_CEN_RXBUF_SIZE                6                        /*���ջ����С*/ 

#define  CEN_TO_Voice_TX_BASE_SIZE		4

#define  CEN_TO_Voice_TXBUF_SIZE                (Voice_TO_CEN_RXBUF_SIZE+67)  /*���ͻ����С,�����������67�ֽ�*/ 

/*������Ӧ���ָ��Ӧ��200ms���յ�Ӧ�𣬷���Ӧ�ٴη���ָ����ط�2����δ�յ���ЧӦ����ֹͣ����ָ��*/

#define  VOICE_CEN_FRAME_HEAD                           0x7b	/*֡ͷ*/

/*�����룬���ݳ��ȣ��ظ��룬���ݳ�������*/
//�������Ų���ָ����İ�->�����壬û��Ӧ���д����ط�������ط�����
#define  CEN_VOICE_VoiceVal_0xa0                 		0xa0	/*Cen���Ͳ���ָ��*/
#define  CEN_VOICE_VoiceVal_0xa0_DataLength             2      	/*Cen���Ͳ���ָ�����ݳ���*/
#define  VOICE_CEN_VoiceVal_0xb0               	        0xb0    /*������ظ���ֵָ��*/
#define  VOICE_CEN_VoiceVal_0xb0_DataLength             2      	/*������ظ���ֵָ�����ݳ��ȣ��������ݣ��ɹ���0xFFFF���д�0xFFEE*/

//������ʶ��ָ��󣬷������İ�
#define  VOICE_CEN_ORDER_0xb1						    0xb1    /*����ʶ��ָ��֡*/
#define  VOICE_CEN_ORDER_0xb1_DataLength                2       /*����ʶ��ָ�����ݳ���*/
#define  CEN_VOICE_ORDER_0xa1						    0xa1    /*�ظ�����ʶ��ָ��֡*/
#define  CEN_VOICE_ORDER_0xa1_DataLength                2       /*�ظ�����ʶ��ָ���������ݣ���ȷ0xffff������0xffee*/

//��ѯ������汾��ָ�����������
#define  CEN_VOICE_VER_0xa3               		 	    0xa3    /*���İ��ѯ������汾*/
#define  CEN_VOICE_VER_0xa3_DataLength                  0     	/*���ݳ���Ϊ0*/
#define  VOICE_CEN_VER_0xb3               		        0xb3    /*������Ӧ�����İ�*/
#define  VOICE_CEN_VER_0xb3_DataLength                  1       /*�汾�����ݳ���1������0x12��ʾV1.2*/

//�������Źر�ָ�����������
#define  CEN_VOICE_CLOSE_0xa4               		 	0xa4    /*�������Źر�*/
#define  CEN_VOICE_CLOSE_0xa4_DataLength                0     	/*���ݳ���Ϊ0*/
#define  VOICE_CEN_CLOSE_0xb4               		    0xb4    /*������Ӧ�����İ�*/
#define  VOICE_CEN_CLOSE_0xb4_DataLength                1       /*�汾�����ݳ���1�����ݳɹ�:0x88,ʧ��:0xee*/

//����ʶ�����͹ر�ָ�����������
#define  CEN_VOICE_DISCERN_ONOFF_0xa5               	0xa5    /*����ʶ�𿪹�*/
#define  CEN_VOICE_DISCERN_ONOFF_DataLength             1     	/*���ݳ���Ϊ1�����ݹر�:0,����:1*/
#define  VOICE_CEN_DISCERN_ONOFF_0xb5                   0xb5    /*������Ӧ�����İ�*/
#define  VOICE_CEN_DISCERN_ONOFF_0xb5_DataLength        1       /*�汾�����ݳ���1�����ݹرճɹ�:0x88,�ر�ʧ��:0x0e�������ɹ�:0x18,����ʧ��:0x1e*/

//���������������ã�����������
#define  CEN_VOICE_VOLUME_0xa6                 			0xa6    /*����������������*/
#define  CEN_VOICE_VOLUME_0xa6_DataLength               1       /*����1������:0~10,0������С*/
#define  VOICE_CEN_VOLUME_0xb6               		    0xb6    /*��������������Ӧ��֡*/
#define  VOICE_CEN_VOLUME_0xb6_DataLength               1       /*����1������,�ɹ�:0x88,ʧ��:0xee*/

//��������������30�뷢��һ�������������İ壬�����Ӧ
#define  VOICE_CEN_HEARTBEAT_0xb7              		   	0xb7    /*������������ָ��*/
#define  VOICE_CEN_HEARTBEAT_0xb7_DataLength			0     	/*���İ������Ӧ*/

//������wifi�������ݣ�����������
#define  CEN_VOICE_WIFIDATA_0xa8                 		0xa8    /*����WIFI������������*/
//#define  CEN_VOICE_WIFIDATA_0xa8_DataLengthx               1       /*�ɱ䳤*/
#define  VOICE_CEN_WIFIDATA_0xb8               		    0xb8    /*����WIFI������������Ӧ��֡*/
#define  VOICE_CEN_WIFIDATA_0xb8_DataLength             2       /*����WIFI������������Ӧ�����ݣ�����2���������ݣ��ɹ���0xffff���д�0xffee*/


#define  VOICE_CEN_CMD_OFFSET                           1       /*������֡�е�λ��ƫ����*/
#define  VOICE_CEN_DATALEN_OFFSET                       2       /*���ݳ�����֡�е�λ��ƫ����*/
#define  VOICE_CEN_DATA_OFFSET                          3       /*������֡�е�λ��ƫ����*/
#define  VOICE_CEN_DATA_OFFSET1                         4       /*����1��֡�е�λ��ƫ����*/





/*=====VOICE_CEN_ORDER_0xb1����������ָ��=============================================================================*/
#define  VOICEORDER_0xb1_WakeUpO                        	0x01    /*���� ��������(��������1��С��)*/

#define  VOICEORDER_0xb1_PowerOn                        		0x56    /*����*/
#define  VOICEORDER_0xb1_PowerOff                       		0x04    /*�ػ�(��λ)*/

#define  VOICEORDER_0xb1_BackRiseFeetRecline            0x05    /*��������*/
#define  VOICEORDER_0xb1_BackReclineFeetRise            0x07    /*̧�ȵ���*/

//#define  VOICEORDER_0xb1_SrtengthAdd                    	0x06    /*ǿ�ȼ���*/
//#define  VOICEORDER_0xb1_SrtengthDec                    	0x07    /*ǿ�ȼ���*/

#define  VOICEORDER_0xb1_FlexAdd                    		0x09    /*ǿ�ȼ���*/
#define  VOICEORDER_0xb1_FlexDec                    		0x0A    /*ǿ�ȼ���*/

#define  VOICEORDER_0xb1_IntensityAdd                    	0x06    /*ǿ�ȼ���*/
#define  VOICEORDER_0xb1_IntensityDec                    	0x08    /*ǿ�ȼ���*/

//#define  VOICEORDER_0xb1_Neck                   			0x08    /*������Ħ*/

//#define  VOICEORDER_0xb1_RandomAuto                     	0x0A    /*�Զ��ƽ鰴Ħ*/
#define  VOICEORDER_0xb1_SwitchManual                     	0x1D    /*�Զ��ƽ鰴Ħ*/

#define  VOICEORDER_0xb1_Shoulder                   		0x0B    /*�粿��Ħ*/
#define  VOICEORDER_0xb1_Arms                           		0x0C    /*�ֱ۰�Ħ*/
#define  VOICEORDER_0xb1_Back                          		0x0D    /*������Ħ*/
#define  VOICEORDER_0xb1_Lumbar                         		0x0E    /*������Ħ*/
#define  VOICEORDER_0xb1_Hip                           		0x0F    /*�β���Ħ*/
#define  VOICEORDER_0xb1_CalvesFeet                     	0x10    /*�ȽŰ�Ħ*/

#define  VOICEORDER_0xb1_Knead                          		0x11    /*����*/
#define  VOICEORDER_0xb1_Roll                          		0x12    /*����*/
#define  VOICEORDER_0xb1_Clap                           		0x13    /*�Ĵ�*/
#define  VOICEORDER_0xb1_Shia                           		0x14    /*ָѹ*/

#define  VOICEORDER_0xb1_Spot                           		0x15    /*����*/

#define  VOICEORDER_0xb1_ServiceDescription             	0x16    /*�����������ݽ���*/

#define  VOICEORDER_0xb1_Swedish                     		0x17    /*���ʽ*/
#define  VOICEORDER_0xb1_Tap                            		0x18    /*�û�*/

#define  VOICEORDER_0xb1_CurrentProgram                 	0x19    /*��ǰ��Ħ����*/

#define  VOICEORDER_0xb1_Pause                          		0x1A    /*��ͣ*/
#define  VOICEORDER_0xb1_PauseResume                    	0x1B    /*ȡ����ͣ*/

#define  VOICEORDER_0xb1_CloseHeat                     		0x2D    /*�ر��Ȳ�����*/
#define  VOICEORDER_0xb1_Heat                     			0x2C    /*�����Ȳ�����*/
#define  VOICEORDER_0xb1_CloseLumberHeat                 	0x1E    /*�ر���������*/
#define  VOICEORDER_0xb1_LumberHeat                     	0x1F    /*�ر���������*/

#define  VOICEORDER_0xb1_NetConnectOk                   	0x20    /*����������*/

#define  VOICEORDER_0xb1_ZeroGravity1                   	0x21    /*������1*/
#define  VOICEORDER_0xb1_ZeroGravity2               	   	0x22    /*������2*/

#define  VOICEORDER_0xb1_BlueToothOn               	   	0x23    /*������*/
#define  VOICEORDER_0xb1_BlueToothOff              	   	0x24    /*�ر�����*/

#define  VOICEORDER_0xb1_WakeUpEnd                      	0x39    /*���ѽ������*/

#define  VOICEORDER_0xb1_AutoMassage1                     	0x51  /*�Ƹ�����*/
#define  VOICEORDER_0xb1_AutoMassage2                     	0x52  /*��ʿ����*/
#define  VOICEORDER_0xb1_AutoMassage3                    	0x53  /*Ů������*/
#define  VOICEORDER_0xb1_AutoMassage4                     	0x54  /*��������*/
#define  VOICEORDER_0xb1_AutoMassage5                    	0x55  /*�����칫*/
#define  VOICEORDER_0xb1_AutoMassage6                    	0x56  /*׷�����*/
#define  VOICEORDER_0xb1_AutoMassage7                    	0x57  /*�˶�����*/
#define  VOICEORDER_0xb1_AutoMassage8                     	0x58  /*��ֳ���*/
#define  VOICEORDER_0xb1_AutoMassage9                     	0x59  /*�羱�ص�*/
#define  VOICEORDER_0xb1_AutoMassage10                 	0x5A  /*���κǻ�*/
#define  VOICEORDER_0xb1_AutoMassage11                 	0x5B  /*̩ʽ����*/
#define  VOICEORDER_0xb1_AutoMassage12                  	0x62  /*ҡ������*/

#define VOICEORDER_0xb1_OpenVoice					0x81 	/*��������*/
#define VOICEORDER_0xb1_CloseVoice					0x82 	/*�ر�����*/

//#define  VOICEORDER_0xb1_Help                           		0x17    /*����*/
//#define  VOICEORDER_0xb1_UnClear                        		0x18    /*û����*/
//#define  VOICEORDER_0xb1_NetConnectFault                0x1F    /*��������ʧ��*/

/*=====CEN_VOICE_VoiceVal_0xa0����������ָ��=============================================================================*/
#define  VOICEVal_0xa0_WakeUpO                          	0x01    /*���� ��������(��������1,С��)*/
#define  VOICEVal_0xa0_PowerOff                         	0x42    /*�ػ�(��λ)*/

#define  VOICEVal_0xa0_SpikeAdj1                        	0x05    /*����Ϊ�����*/
#define  VOICEVal_0xa0_SpikeAdj2                        	0x07    /*����������*/
#define  VOICEVal_0xa0_SpikeAdjLimit                    	0x30    /*�ѴＫ��λ��*/

#define  VOICEVal_0xa0_SrtengthAdd                      	0x09    /*ǿ�ȼ���*/
//#define  VOICEVal_0xa0_SrtengthMax                      	0x08    /*ǿ�����*/
#define  VOICEVal_0xa0_SrtengthDec                      	0x0A    /*ǿ�ȼ���*/
//#define  VOICEVal_0xa0_SrtengthMin                      	0x0A    /*ǿ����С*/

#define  VOICEVal_0xa0_IntensityAdd                      	0x06   /*ǿ�ȼ���*/
#define  VOICEVal_0xa0_IntensityDec                      	0x08    /*ǿ�ȼ���*/
//�Զ����򲥱�
	#define  VOICEVal_0xa0_RandomAuto1                	0x51  /*ȫ���滺*/
	#define  VOICEVal_0xa0_RandomAuto2              		0x52  /*����Ԫ��*/
	#define  VOICEVal_0xa0_RandomAuto3                     	0x53  /*����ģʽ*/
	#define  VOICEVal_0xa0_RandomAuto4                   	0x54  /*����ģʽ*/
	#define  VOICEVal_0xa0_RandomAuto5                    	0x55  /*�⽳����*/
	
	#define  VOICEVal_0xa0_RandomAuto6                     	0x06  /*�ϰ���*/
	
	#define  VOICEVal_0xa0_RandomAuto7                     	0x57  /*ҡ������*/
	#define  VOICEVal_0xa0_RandomAuto8                    	0x58  /*����ģʽ*/
	#define  VOICEVal_0xa0_RandomAuto9                     	0x59  /*��֫ģʽ*/
	#define  VOICEVal_0xa0_RandomAuto10                  	0x5A  /*�����ѹ*/
	#define  VOICEVal_0xa0_RandomAuto11               	0x5B  /*��ʽ��Ħ*/
	
	#define  VOICEVal_0xa0_RandomAuto12                   	0x0C  /*����ģʽ*/
	#define  VOICEVal_0xa0_RandomAuto13                   	0x0D  /*Ů������*/
	#define  VOICEVal_0xa0_RandomAuto14                  	0x0E  /*��ʿ����*/
	#define  VOICEVal_0xa0_RandomAuto15                   	0x0F  /*����ģʽ*/
	#define  VOICEVal_0xa0_RandomAuto16                   	0x10  /*�ٰ�����*/
	#define  VOICEVal_0xa0_RandomAuto17                 	0x11  /*��ȷ���*/
	#define  VOICEVal_0xa0_RandomAuto18             	0x12  /*������ѹ*/
	#define  VOICEVal_0xa0_RandomAuto19                   	0x13  /*ȫ����չ*/
	#define  VOICEVal_0xa0_RandomAuto20                   	0x14  /*�˶��ָ�*/
	#define  VOICEVal_0xa0_RandomAuto21                  	0x15  /*̩ʽ����*/

#define  VOICEVal_0xa0_Neck                        		0x0D    /*������Ħ*/
#define  VOICEVal_0xa0_Shoulder                     		0x10    /*�粿��Ħ*/
#define  VOICEVal_0xa0_Arms                             	0x11    /*�ֱ۰�Ħ*/
#define  VOICEVal_0xa0_Back                             		0x12    /*������Ħ*/
#define  VOICEVal_0xa0_Lumbar                           	0x13    /*������Ħ*/
#define  VOICEVal_0xa0_Hip                              		0x14    /*�β���Ħ*/
#define  VOICEVal_0xa0_CalvesFeet                       	0x15    /*�ȽŰ�Ħ*/

#define  VOICEVal_0xa0_Knead                            	0x16    /*����*/
#define  VOICEVal_0xa0_Roll                             		0x17    /*����*/
#define  VOICEVal_0xa0_Clap                             		0x18    /*�Ĵ�*/
#define  VOICEVal_0xa0_Shia                             		0x19    /*ָѹ*/
#define  VOICEVal_0xa0_Spot                             		0x1A    /*����*/

#define  VOICEVal_0xa0_ServiceDescriptionO           	0x1B    /*�����������ݽ��ܣ�С��*/

#define  VOICEVal_0xa0_Swedish                             	0x1C    /*���ʽ*/

#define  VOICEVal_0xa0_Help                             		0x1D    /*����*/
#define  VOICEVal_0xa0_SwitchManual                     	0x1D    /*�����ַ�*/

#define  VOICEVal_0xa0_UnClear                          	0x1E    /*û����*/

#define  VOICEVal_0xa0_ImHere                           	0x20    /*����*/
#define  VOICEVal_0xa0_Here                             		0x21    /*��*/

#define  VOICEVal_0xa0_Tap                              		0x22    /*�û�*/

#define  VOICEVal_0xa0_CloseHeat                        	0x2D    /*�ر��Ȳ�����*/
#define  VOICEVal_0xa0_Heat                       		0x2C    /*�Ȳ�����*/
#define  VOICEVal_0xa0_CloseLumberHeat             	0x25    /*�ر���������*/
#define  VOICEVal_0xa0_LumberHeat                       	0x26    /*��������*/

#define  VOICEVal_0xa0_BlueToothOn                      	0x28    /**/
#define  VOICEVal_0xa0_BlueToothOff                     	0x29    /**/

#define  VOICEVal_0xa0_DefaultMode                   	0x2E    /*ģ������ϵ�Ĭ�Ϲ���״̬*/
#define  VOICEVal_0xa0_SleepMode                      	0x2F    /*ģ���������״̬*/

#define  VOICEVal_0xa0_UnsupportedProgram        	0x3E    /*�˹��ܲ�����������ģʽ*/
#define  VOICEVal_0xa0_ShoulderScanning        	0x31    /*�粿����У������ĵȴ�*/
#define  VOICEVal_0xa0_ShoulderScanFinish        	0x32    /*����������ʼΪ����Ħ*/


#define  VOICEVal_0xa0_UARTNetConnect               	0x39    /*������������ģʽ����������APP����ģʽ */
#define  VOICEVal_0xa0_NetConnectOK                  	0x3a    /*���ţ�����������*/
#define  VOICEVal_0xa0_NetConnectFalse              	0x3B    /*���ţ�����δ���ӣ�����������*/

#define  VOICEVal_0xa0_PowerOn                        	0x3D    /*����*/

#define  VOICEVal_0xa0_ChairRest                 		0x3E    /*���ţ����Ӹ�λ�����Ժ�����*/

#define  VOICEVal_0xa0_Pause                            	0x40    /*��ͣ*/
#define  VOICEVal_0xa0_PauseResume                     	0x41    /*ȡ����ͣ*/

#define VOICEVal_0xa0_OpenVoice					0x81 	/*��������*/
#define VOICEVal_0xa0_CloseVoice				0x82 	/*�ر�����*/

//#define  VOICEVal_0xa0_WakeUpH                          	0x02    /*���� ��������(��������2,С��)*/
//#define  VOICEVal_0xa0_ServiceDescriptionH           	0x1C    /*�����������ݽ��ܣ�С��*/
//#define  VOICEVal_0xa0_APPNetConnect                  	0x31    /*����APP����ģʽ ������*/
//#define  VOICEVal_0xa0_StopPlayNetworkAudio      	0x32    /*ֹͣ���źϳɷ����������֡����¡����ŵȸ������ڲ��ŵ���Ƶ*/

//    04
#define VOICEVal_0xa0_ChildClockOpen			0x15	/*�¼ѻ������ػ�����Ϊ��������ͯ��*/
#define VOICEVal_0xa0_ChildClockClose			0x16	/*�¼ѻ������ػ�����Ϊ���رն�ͯ��*/

/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� :                                                                                                    
************************************************************************************************************************
*/

/*
************************************************************************************************************************
* ���Ͷ��� :  ���İ� <--> ������  ����֡�ṹ                                                                              
************************************************************************************************************************
*/
typedef struct
{
	uint8_t Head;
	uint8_t Cmd;
	uint8_t DataLength;
	uint8_t Data[2];
	uint8_t CheckSum;  
}CDP_CenVoiceFrame_t;/*ͨ������֡*/

/*
************************************************************************************************************************
* ���Ͷ��� :  ���İ� <--> ������  ���İ�������ݲ���                                                                             
************************************************************************************************************************
*/
typedef enum
{                   
	VoiceCen_RX_STEP_SEARCH_HEAD=0,             	/*֡ͷ*/
	VoiceCen_RX_STEP_JUDGE_CMD,                 	/*������*/
	VoiceCen_RX_STEP_JUDGE_DATALEN,             	/*���ݳ���*/
	VoiceCen_RX_STEP_RCV_DATA,					    /*����*/
	VoiceCen_RX_STEP_JUDGE_SUMCHECK			        /*�ۼӺ�У����*/
}CDP_VoiceCenStep_e; /*����״̬��*/  

typedef enum
{                   
	CenVoice_TX_STEP_SEARCH_HEAD=0,             	/*֡ͷ*/
	CenVoice_TX_STEP_JUDGE_CMD,                 	/*������*/
	CenVoice_TX_STEP_JUDGE_DATALEN,             	/*���ݳ���*/
	CenVoice_TX_STEP_RCV_DATA,					    /*����*/
	CenVoice_TX_STEP_JUDGE_SUMCHECK				    /*У����*/
}CDP_CenVoiceStep_e; /*����״̬��*/  
/*
************************************************************************************************************************
* ���Ͷ��� :  ���İ� <--> ������  ������״̬��ʶ                                                                              
************************************************************************************************************************
*/
typedef  union 
{
  uint16_t All;
  struct
  {
    uint8_t    SetAPPConnectNetFlag    	    :1;    /*����������־λ*/
    uint8_t    SetUARTConnectNetFlag    	:1;    /*���봮��������־λ*/
    uint8_t    RetrySendVoiceValFlag        :1;    /*���������ط���־*/
    uint8_t    RxVoiceDataOKFlag            :1;    /*����������ͨ�����ݰ��ɹ�*/
    uint8_t    RxOrder0xb1OKFlag            :1;    /*����ָ����ճɹ�*/
    uint8_t    VoiceValNeedResFlag          :1;    /*����ָ����Ҫ�ظ���־λ*/
    uint8_t    StopPlayNetworkAudioFlag     :1;    /*ֹͣ���źϳɷ����������֡����¡����ŵȸ������ڲ��ŵ���Ƶ*/
    
    uint8_t    SendWifiDataToVoiceFlag      :1;    /*������WIFI������Ҫ�ظ���־λ*/
    uint8_t    VoiceWIFIDataNeedResFlag     :1;    /*������WIFI������Ҫ�ظ���־λ*/
    uint8_t    RetrySendWIFIDataFlag        :1;    /*���������ط���־*/
    
    uint8_t    VoiceCloseOKFlag    	        :1;    /*�����رճɹ���־λ*/
    uint8_t    VoiceDiscernCloseOKFlag    	:1;    /*����ʶ��رճɹ���־λ*/
    uint8_t    VoiceDiscernOpenOKFlag    	:1;    /*����ʶ�����ɹ���־λ*/
    uint8_t    VoiceWakeUpStateFlag    	    :1;    /*����ʶ����״̬��־λ*/
    
  }Bit;

}CDP_CenVoiceCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/

/*
************************************************************************************************************************
* ���Ͷ��� :  ���İ� <--> ������  ��ز������ݽṹ                                                                            
************************************************************************************************************************
*/
typedef struct
{
	uint8_t TxVoiceVal[2+67];                      	/*���ͻ�����*/
	uint8_t TxVoiceValLen;                      	/*���ͻ�����*/
	CDP_CenVoiceCSFlag_t CSFlag;
    uint8_t	RxStep;                           		/*���ղ���*/
	uint8_t RxLen;								    						/*�������ݳ���*/
	uint8_t RxBuf[Voice_TO_CEN_RXBUF_SIZE];       /*���ջ�����*/
	uint8_t RxDataLen;
	
	uint8_t Rx0xb1Order[2];
 	uint8_t TxBuf[CEN_TO_Voice_TXBUF_SIZE];       /*���ͻ�����*/
	uint8_t TxLen;																/*�������ݳ���*/

	uint8_t RetryTimes;
	uint8_t RetryDelayTimer;

	uint8_t SendWifiDataRetryTimes;
	uint8_t SendWifiDataRetryDelayTimer;

	uint8_t VoiceNothingReceiveTimerMS;

}CDP_CenVoice_t;	/*ͨ����ؿ��Ʊ���*/



/*
========================================================================================================================
*��ȫ��������                                          ��ȫ��������                                          ��ȫ��������
========================================================================================================================
*/

 void ReceiveDataFromVoice100ms(void);
 void VoiceOrder0xb1RxHandle(Uchar OrderH,Uchar OrderL);
 void CDP_CenVoice_ByteRx(uint8_t RxByte);
 void VoiceVariableRefresh1ms(void);
#endif  


