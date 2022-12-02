/*
*********************************************
* File Name		: bluetooth50.c                                                                                                   
* Description 	: BlueTooth5.0 Program                                                                         
* Author 		: Faceless  
* Date			: 2021/5/14
*********************************************
*/
#include "bluetooth50.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Flag.h"
#include "Glob.h"
#include "IO.h"
#include "SysRun.h"

#define 	BLUETOOTHAPP						0


extern uint8_t KeyTimerAdj(uint8_t  settime);
extern void KeyPressEvent(Uchar KeyValue,Uchar	KeyTab[],Uchar device,Uchar TabSize);
extern uint8_t KeyStrength(uint8_t KneadStrenth);
extern uint8_t KeySpeed(uint8_t TCSSpeed);
extern uint8_t KeyIntensity(uint8_t AirIntensity);
extern Uchar KeyManual3D(Uchar CoreIntensity);
extern Uchar KeyWidth(Uchar WidthLevel);
extern Uchar 	WifiKeyCoreMoveUp(void);
extern Uchar 	WifiKeyCoreMoveDown(void);

typedef __packed union 
{
  uint32_t All;
  __packed struct								//˳���ܱ��
  {
	uint8_t	BlueToothA2DPConnectedState			:1;		/*����A2DP������״̬*/
	uint8_t	BlueToothBLEConnectedState				:1;		/*����BLE������״̬*/
	uint8_t	BlueToothBLESwitchState					:1;		/*����BLE����״̬*/
	uint8_t	BlueToothSwitchState					:1;		/*��������״̬*/

	
	uint8_t	BlueToothRxOkFlag						:1;		/*�������ճɹ���ʶ*/
	uint8_t 	BlueToothLoseLinkFlag					:1;		/*����ͨ�Ŷ�ʧ��ʶ*/
	
	uint8_t	BlueToothSendOnFlag					:1;		/*�������Ϳ���ָ���ʶ*/
	uint8_t	BlueToothSendOffFlag					:1;		/*�������͹ر�ָ���ʶ*/
	uint8_t	BlueToothSendSearchFlag				:1;		/*�������Ͳ�ѯָ���ʶ*/
	uint8_t	BlueToothSendBLEOnFlag					:1;		/*��������BLE����ָ���ʶ*/
	uint8_t	BlueToothSendBLEOffFlag					:1;		/*��������BLE�ر�ָ���ʶ*/
	uint8_t	BlueToothSendSearchConnectedFlag		:1;		/*����������������״̬��ѯָ���ʶ*/
	uint8_t											:3;
	uint8_t	BlueToothSendConnectedLastDevFlag		:1;		/*��������������һ�豸ָ���ʶ*/
	//-------------------------16

	uint8_t	BlueToothSendSoundSourceSelectFlag		:1;		/*����������Դ���ָ���ʶ*/
	uint8_t	BlueToothSendPlayMusicFlag				:1;		/*�������Ͳ���ָ������ָ���ʶ*/
	uint8_t	BlueToothSendMusicModeFlag				:1;		/*������������ģʽָ���ʶ*/
	uint8_t	BlueToothSendMusicVolumeSetFlag		:1;		/*����������������ָ���ʶ*/
	uint8_t	BlueToothSendfFunOFFFlag				:1;		/*��������FUN����ָ���ʶ*/
  }Bit;
}BlueToothCSFlag_t;  		

typedef __packed struct
{
	BlueToothCSFlag_t CSFlag;							
	uint8_t RxNothingTimer;								/*��ʱ�ؽ���*/
	uint8_t RxLoseLink1sTimer;							/*���ն�ʧͨ��ʱ��*/
	uint8_t TxBuf[CEN_TO_BLUETOOTH_TX_SIZE];			/*���ͻ�����*/
	uint8_t TxLen;										/*���ͳ���*/
	uint8_t RxBuf[CEN_TO_BLUETOOTH_RX_SIZE];			/*���ջ�����*/
	uint8_t RxLen;										/*���ճ���*/
}BlueTooth_t;

static BlueTooth_t gBlueTooth;
BlueTooth_t *pBlueTooth = &gBlueTooth;
Uchar gCurrentSendCmdValue;

Uchar gBlueToothMusicBuff[4];


#if BLUETOOTHAPP

typedef __packed union 
{
  uint8_t All;
  __packed struct
  {
	uint8_t	BlueToothAPPRxOkFlag						:1;		/*����APP���ݽ��ճɹ���ʶ*/
	uint8_t 	BlueToothAPPLoseLinkFlag					:1;		/*����APPͨ�Ŷ�ʧ��ʶ*/
	uint8_t 	BlueToothAPPSendIDFlag						:1;		/*����APP����ID���ʶ*/
	uint8_t 	BlueToothAPPSendBackDataFlag				:1;		/*����APP���ͼ�ֵ�ش����ݱ�ʶ*/
	uint8_t    BlueToothAPPSendDIYPackageNumFlag		:1;		/*����APP����DIY���Żش����ݱ�ʶ*/
  }Bit;	
}BlueToothAPPCSFlag_t;



typedef __packed struct
{
	BlueToothAPPCSFlag_t CSFlag;							
	uint8_t RxNothingTimer;								/*��ʱ�ؽ���*/
	uint8_t RxLoseLink1sTimer;							/*���ն�ʧͨ��ʱ��*/
	uint8_t CheckSum;									/*����У���*/
	uint8_t RxStep;										/*���ճ���*/
	uint8_t TxBuf[CEN_TO_BLUETOOTH_TX_SIZE];			/*���ͻ�����*/
	uint8_t TxLen;										/*���ͳ���*/
	uint8_t RxBuf[CEN_TO_BLUETOOTH_RX_SIZE];			/*���ջ�����*/
	uint8_t RxLen;										/*���ճ���*/
}BlueToothAPP_t;


static BlueToothAPP_t gBlueToothAPP;
BlueToothAPP_t *pBlueToothAPP = &gBlueToothAPP;

CenToBlueToothAppStateData1_t gSendChairState1ToBlueToothApp;

CenToBlueToothAppStateData2_t gSendChairState2ToBlueToothApp;

CenToBlueToothAppStateData3_t gSendChairState3ToBlueToothApp;
	
uint8_t gBlueToothAPPData[CEN_TO_BLUETOOTH_RX_SIZE];

static uint8_t BlueToothKeyValTab []=
{
	evKeyNC,				
	evKeyPower,				/* 1 ����*/
	evKeyPause,				/* 2 ������ͣ*/
	evKeyNC,				/* 3 ��ʱ*/
	evKeyPower,				/* 4 �ػ�*/
	evKeyPause,				/* 5 ȡ����ͣ*/
	evKeyNC,				
	evKeyNC,
	evKeyNC,				/* 8 �Զ�����*/
	evKeyAdvancedAuto,		/* 9 ����Ħ*/
	
	evKeyNC,
	evKeySoundPulse,
	evKeyNC,
	evKeyNC,
	evKeyNC,
	evKeyNC,
	evKeyNC,	
	evKeyNC,
	evKeyNC,
	evKeyNC,
	
	evKeyNC,
	evKeyNC,
	evKeyNC,
	evKeyNC,
	evKeyNC,
	evKeyNC,
	evKeyNC,
	evKeyNC,
	evKeyNC,
	evKeyNC,
	
	evKeyNC,
	evKeyNC,
	evKeyNC,
	evKeyNC,
	evKeyNC,
	evKeyNC,
	evKeyNC,
	evKeyNC,        				
	evKeyNC,
	evKeyNC,
	
	evWifiKneading,			/*40 ����1*/
	evWifiKneading2,  			/*41 ����2*/
	evWifiTapping,                 	/*42 �û�1*/ 		
	evWifiTapping2,         		/*43 �û�2*/ 	
	evWifiSwedish,			/*44 ���ʽ1*/
	evWifiSwedish2,  			/*45 ���ʽ2*/
	evWifiShiatsu,                 	/*46 ָѹ1*/		
	evWifiShiatsu2,         		/*47 ָѹ2*/	
	evWifiClapping,			/*48 �Ĵ�1*/
	evWifiClapping2,			/*49 �Ĵ�2*/
	
	evWifiRolling,       			/*50 ����*/ 
	evKeyNC,          		
	evKeyNC,            		
	evKeyNC, 			  
	evKeyNC,          		 
	evKeyNC,            			/*55 ��о���*/
	evKeyFullBack,            		/*56 ��оλ��:ȫ��*/
	evKeyPartial,            		/*57 ��оλ��:����*/
	evKeySpot,         			/*58 ��оλ��:����*/
	evKeyNC,     				/*59 ��о������*/
	
	evKeyNC,      				
	evKeyNC,             				
	evKeyNC,            					  
	evKeyNC,           			
	evKeyBackReclineClick,     		/*64 ����*/
	evKeyBackRaiseClick,        		/*65 ����*/
	evKeyNC,         			/*66 ̧��*/
	evKeyNC,       			/*67 ����*/
	evKeyNC,        			/*68 */
	evKeyNC,        			/*69 */
	
	evKeyNC,                   		/*70 */
	evKeyNC,         			/*71 */
	evKeyHome, 	       		/*72 �Ƕ�1(����)*/       
	evKeyZeroGravity1,    		/*73 �Ƕ�2(������1)*/  
	evKeyZeroGravity2,    		/*74 �Ƕ�3(������2)*/  
	evKeyNC,				/*75 �Ƕ�4(չ��)*/
	evKeyNC,             			/*76 */
	evKeyNC,            			/*77 */
	evKeyNC,            			/*78 */
	evKeyNC,             			/*79 */
	
	evKeyNC,                  		/*80 */
	evKeyNC,                  		/*81 */
	evKeyNC,                 		/*82 */
	evKeyNC,                  		/*83 */
	evKeyAutoGas,               	/*84 ȫ�����*/
	evKeyShoulderGas,       	/*85 �粿����*/
	evKeyArmsGas,            	/*86 �ֲ�����*/
	evKeyNC,            		 	/*87 */
	evKeyFeetCalvesGas,   		/*88 �Ȳ�����*/
	evKeyNC,                 		/*89 �Ų�����*/
	
	evKeyNC,                 		/*90 */
	evKeyNC,                 		/*91 */
	evKeyLumbarHeat,            	/*92 ��������*/
	evKeyNC,              		/*93 �Ȳ�����*/
	evKeyNC,                 		/*94 */
	evKeyNC,                 		/*95 */
	evKeyRoller,                 	/*96 �ŵ׹���*/
	evKeyNC,                 		/*97 */
	evKeyNC,                 		/*98 */
	evKeyNC,                 		/*99 ��������*/
	evKeyBackScanOK,		/*100 �����粿������*/
//	evKeyChildLock,			/*101 ��ͯ��*/
};
static uint8_t BlueToothAutoMassageKeyValTab []=
{
    evKeyNC,
    evKeyBallGame,			/* 1 ����*/  
    evKeyGolf,           		/* 2 �߶���*/
    evKeySwimming,            	/* 3 ��Ӿ*/
    evKeyWalk,           	    	/* 4 ����*/
    evKeyRiding,            		/* 5 ����*/  
    evKeyFitness,            	/* 6 ����*/
    evKeyRunning,                	/* 7 �ܲ�*/
    evKeyMasterCare,           	/* 8 ��ʦ��ѡ*/
    evKeyThaiMassage,        	/* 9 ̩ʽ����*/  
    evKeyJointCare,     		/* 10 �ؽںǻ�*/   
    evKeyRelax,             	/* 11 �澭����*/ 
    evKeyChildren, 			/* 12 Ԫ������*/ 
    evKeyBalance,			/* 13 ƽ������*/
    evKeyDeepMassage,		/* 14 ��㰴Ħ*/
    evKeyMoringSev,		/* 15 �峿����*/
    evKeyEnergy,			/* 16 ��������*/
    evKeySleep,			/* 17 ̫������*/
    evKeyFemale,			/* 18 Ů������*/
    evKeyMiddleMan,		/* 19 ��ʿ����*/
    evKeyOldMan,			/* 20 ���걣��*/
    evKeyJapanese,			/* 21 �ձ�ʽ*/
    evKeyIndian,			/* 22 ӡ��ʽ*/
    evKeyBalinese,			/* 23 ����ʽ*/
    evKeyChinese,			/* 24 ��ʽ*/
    evKeySkiing,			/* 25 ��ѩ*/
    evKeyMahjong,			/* 26 �齫*/
    evKeyOffice,			/* 27 �칫��*/
    evKeyPhubber,			/* 28 ��ͷ��*/
    evKeyDriver,			/* 29 �ݳ���*/
    evKeyHighHeel,			/* 30 �߸���*/
    evKeyJiuYangShenGong,	/* 31 ������*/
    evKeyXiangLongMoZhang,	/* 32 ����ħ��*/
    evKeyLiuMaiShenJian,	/* 33 ������*/
    evKeyYiYangZhi,		/* 34 һ��ָ*/
    evKeyTaiJiQuan,			/* 35 ̫��ȭ*/
    evKeyQianKunNuoYi,		/* 36 Ǭ��Ų��*/
    
};

static const Uchar	AutoFunNum[32]=
{
	8,10,11,15,16,		//5

	17,18,19,20,21, 	//10

	22,23,24,27,28,		//15
	
	29,30,1,2,3,		//20
	
	4,5,6,7,25,	//25
	
	26,12,0,0,14,		//30
	
	13,0				
};

static const Uchar	AutoFunNum1[32]=
{
	31,32,33,34,35,		//5

	36,0,0,0,0, 	//10

	0,0,0,0,0,		//15
	
	0,0,0,0,0,		//20
	
	0,0,0,0,0,		//25
	
	0,0,0,0,0,		//30
	
	0,0				
};
#endif 
/*************************�����ش�ָ�******************************/
const char *pBlueToothCmd_OK 					= "OK";
const char *pBlueToothCmd_ENALBE 				= "SCAN ENABLE";
const char *pBlueToothCmd_DISENALBE 			= "SCAN DISENABLE";
const char *pBlueToothCmd_A_CONNECTED 			= "A_CONNECTED";
const char *pBlueToothCmd_A_DISCONNECTED 		= "A_DISCONNECTED";
const char *pBlueToothCmd_LE_CONNECTED 		= "LE_CONNECTED";
const char *pBlueToothCmd_LE_DISCONNECTED 		= "LE_DISCONNECTED";
const char *pBlueToothCmd_CONNECTED_STATE		= "BTS:";
const char *pBlueToothCmd_LE_OPEN				= "LE=EN";
const char *pBlueToothCmd_LE_CLOSE				= "LE=DIS";
const char *pBlueToothCmd_BREDR_CLOSE			= "BREDR=DIS";
/*
******************************************************************
*	Function Name				:	SetBlueToothSendCmd
*	Decription					:	Set BlueTooth Send Cmd Flag
*	Input Parameter				:	mCmd
									BLUETOOTH_CONNECTED_STATE		4
									BLUETOOTH_CONNECTED_LASTDEV		5
									BLUETOOTH_ON					6
									BLUETOOTH_OFF					7
									BLUETOOTH_INQUIRE_STATE			8
*	Return Parameter			:	void
*	Supplementary Instruction	:	None
******************************************************************
*/
void SetBlueToothSendCmd(uint8_t mCmd)
{
	pBlueTooth->CSFlag.All |= (1 << (mCmd - 1));
}
/*
******************************************************************
*	Function Name				:	GetBlueToothSendCmdState
*	Decription					:	Acquire BlueTooth Send Cmd State Flag
*	Input Parameter				:	mState
									BLUETOOTH_CONNECTED_STATE		4
									BLUETOOTH_CONNECTED_LASTDEV		5
									BLUETOOTH_ON					6
									BLUETOOTH_OFF					7
									BLUETOOTH_INQUIRE_STATE			8
*	Return Parameter			:	TRUE or FALSE
*	Supplementary Instruction	:	None
******************************************************************
*/
uint8_t GetBlueToothSendCmdState(uint8_t mState)
{
	return ((pBlueTooth->CSFlag.All >> (mState-1))&0x01);
}

#if BLUETOOTHAPP
/*
************************************************************************************************************************
* �������� : CDP_CenBluetooth_ByteRx                                                                                                    
* �������� : ͨ�����ݰ�   ֮   ���İ� <--> ��̨������  ���İ��ֽڽ������ݻص�������                                                                              
* ������� : void                                                                 
* ���ز��� : ��                                                             
* ����˵�� : �����ݸ���֡ͷ֡βΪ����������������ۼӺ��ж���ȷ�󣬸���������                                                                                                
************************************************************************************************************************
*/
void BluetoothAPPReceiveRestart()
{
	pBlueToothAPP->CheckSum = 0;
	pBlueToothAPP->RxLen = 0;
	pBlueToothAPP->RxStep = 0;
}
void	CDP_CenBlueAPP_ByteRx(uint8_t RxByte)
{//�����жϵ��ú���
	if(pBlueToothAPP->RxNothingTimer > 10)//����10msû�н�������
	{                                                         /*�������ݽ���*/
		BluetoothAPPReceiveRestart();
	}
	pBlueToothAPP->RxNothingTimer = 0;
	if(pBlueToothAPP->RxStep == 0){
		if((RxByte == 0x7b)){
				pBlueToothAPP->RxBuf[pBlueToothAPP->RxLen++] = RxByte;
				pBlueToothAPP->CheckSum += RxByte;
				pBlueToothAPP->RxStep++;
		}else{
				BluetoothAPPReceiveRestart();
		}
		
	}else if(pBlueToothAPP->RxStep == 1){

		if(RxByte >= 0xa0 && RxByte <= 0xaf){
			pBlueToothAPP->RxBuf[pBlueToothAPP->RxLen++] = RxByte;
			pBlueToothAPP->CheckSum += RxByte;
			pBlueToothAPP->RxStep++;
		}else{
			BluetoothAPPReceiveRestart();
		}
		
	}else if(pBlueToothAPP->RxStep == 2){
		if(RxByte > CEN_TO_BLUETOOTH_RX_SIZE - 3){
			BluetoothAPPReceiveRestart();
		}else{
			pBlueToothAPP->RxBuf[pBlueToothAPP->RxLen++] = RxByte;
			pBlueToothAPP->CheckSum += RxByte;
			pBlueToothAPP->RxStep++;
		}
		
	}else if(pBlueToothAPP->RxStep == 3){
		if(pBlueToothAPP->RxLen == pBlueToothAPP->RxBuf[2]+ 4 -1){
			if(pBlueToothAPP->CheckSum == RxByte){
				pBlueToothAPP->RxBuf[pBlueToothAPP->RxLen++] = RxByte;
				memcpy(gBlueToothAPPData,pBlueToothAPP->RxBuf,pBlueToothAPP->RxLen);
				pBlueToothAPP->CSFlag.Bit.BlueToothAPPRxOkFlag = TRUE;
			}
			BluetoothAPPReceiveRestart();
		}else{
			pBlueToothAPP->RxBuf[pBlueToothAPP->RxLen++] = RxByte;
			pBlueToothAPP->CheckSum += RxByte;
		}
		
	}else{
		BluetoothAPPReceiveRestart();
	}
	
}

#endif


void	CDP_CenBlueTooth_ByteRx(uint8_t RxByte)
{//�����жϵ��ú���
	static uint8_t ByteRxLen;
	
#if BLUETOOTHAPP
	CDP_CenBlueAPP_ByteRx(RxByte);
#endif
	if(pBlueTooth->RxNothingTimer > 10)//����10msû�н�������
	{                                                         /*�������ݽ���*/
		ByteRxLen = 0;
	}
	pBlueTooth->RxNothingTimer = 0;
	pBlueTooth->RxBuf[ByteRxLen++] = RxByte;
	if(RxByte == 0x0A){							//�����س�����ֹͣ����
		pBlueTooth->CSFlag.Bit.BlueToothRxOkFlag = TRUE;
		pBlueTooth->RxBuf[ByteRxLen] = '\0';	//ת���ַ���
		pBlueTooth->RxLen = ByteRxLen;
		ByteRxLen = 0;
	}
	if(ByteRxLen >= CEN_TO_BLUETOOTH_RX_SIZE)
	{
		ByteRxLen = 0;

	}
}
/*
************************************************************************************************************************
* �������� : SendDataToBlueTooth                                                                                                         
* �������� : ���ݰ�����                                                                                        
* ������� : cmd	ѡ�õ�ATָ�                                                                                 
* ���ز��� :                                                                  
* ����˵�� : ÿ�η��Ͷ���Ҫ���֮ǰ������                                                                                                
************************************************************************************************************************
*/
static Uchar  HexToAsciiDec(Uchar Hex , char *Ascii, Uchar n)
{
	Uchar temp;
	Uchar i;
	if(n > 3 || n < 1)
		return FALSE;
	temp = Hex % ((Uint16)pow(10,n));
	for(i = n;i > 0;i--)
	{
		Ascii[i-1] = temp % 10 + 0x30;
		temp = temp / 10;
	}
	return TRUE;
}

void	SendDataToBlueTooth(uint8_t cmd)
{

	char *CmdStr = (char *)malloc(sizeof(char)*CEN_TO_BLUETOOTH_TX_SIZE);
	memset(CmdStr, 0x00, CEN_TO_BLUETOOTH_TX_SIZE);
	memset(pBlueTooth->TxBuf, 0x00, CEN_TO_BLUETOOTH_TX_SIZE);
	memset(pBlueTooth->RxBuf, 0x00, CEN_TO_BLUETOOTH_RX_SIZE);
	gCurrentSendCmdValue = cmd;
	switch(cmd)
	{
		case BLUETOOTH_ON:
			//CmdStr = "AT+ENBT\r\n";
			strcpy(CmdStr, "AT+ENBT");
			break;
		case BLUETOOTH_OFF:
			//CmdStr = "AT+DISENBT\r\n";
			strcpy(CmdStr, "AT+DISENBT");
			break;
		case BLUETOOTH_FUN_OFF:
			//CmdStr = "AT+DISENBT\r\n";
			strcpy(CmdStr, "AT+FUN=BREDR=DIS");
			break;
		case BLUETOOTH_INQUIRE_STATE:
			//CmdStr = "AT+GETBT\r\n";
			strcpy(CmdStr, "AT+GETBT");
			break;
		case BLUETOOTH_BLE_OPEN:
			//CmdStr = "AT+ENBT\r\n";
			strcpy(CmdStr, "AT+FUN=LE=EN");
			break;
		case BLUETOOTH_BLE_CLOSE:
			//CmdStr = "AT+ENBT\r\n";
			strcpy(CmdStr, "AT+FUN=LE=DIS");
			break;
		case BLUETOOTH_CONNECTED_STATE:
			//CmdStr = "AT+MO\r\n";
			strcpy(CmdStr, "AT+MO");
			break;
		//-------------------------------��������������
		case BLUETOOTH_SOUNDSOURCE_SELECT:
			strcpy(CmdStr, "AT+AS=");
			*(CmdStr + strlen(CmdStr)) = gBlueToothMusicBuff[ENUM_BLUETOOTH_SOUNDSOURCE] + 0x30;
			break;
		case BLUETOOTH_PLAY_MUSIC:
			strcpy(CmdStr, "AT+SEL_NAM=");
			*(CmdStr + strlen(CmdStr)) = '/';
			HexToAsciiDec(gBlueToothMusicBuff[ENUM_BLUETOOTH_MUSICNUM],(CmdStr + strlen(CmdStr)),2);
			*(CmdStr + strlen(CmdStr)) = '*';
			*(CmdStr + strlen(CmdStr)) = '.';
			*(CmdStr + strlen(CmdStr)) = 'm';
			*(CmdStr + strlen(CmdStr)) = 'p';
			*(CmdStr + strlen(CmdStr)) = '3';
			break;
		case BLUETOOTH_MUSIC_MODE:
			strcpy(CmdStr, "AT+REP=");
			*(CmdStr + strlen(CmdStr)) = gBlueToothMusicBuff[ENUM_BLUETOOTH_MUSICMODE] + 0x30;
			break;
		case BLUETOOTH_MUSIC_VOL:
			strcpy(CmdStr, "AT+MVOL=");
			HexToAsciiDec(gBlueToothMusicBuff[ENUM_BLUETOOTH_MUSICVOL],(CmdStr + strlen(CmdStr)),2);
			break;
		//------------------------------------------------------------------------------------------------
		/*************Ԥ��***************/
		case BLUETOOTH_CONNECTED_LASTDEV:
			//CmdStr = "AT+CC\r\n";
			strcpy(CmdStr, "AT+CC");
			break;
		default:
			free(CmdStr);
			return;
	}
	strcpy((CmdStr + strlen(CmdStr)),"\r\n");
	pBlueTooth->TxLen = strlen(CmdStr);
	memcpy(pBlueTooth->TxBuf, CmdStr, pBlueTooth->TxLen);
	BSP_UART_TxData(CEN_BLUETOOTH_UART_PORT, pBlueTooth->TxBuf, pBlueTooth->TxLen);
	free(CmdStr);
}

#if BLUETOOTHAPP
/*
************************************************************************************************************************
* �������� : ChairState1Refresh                                                                                                         
* �������� : APP��Ħ��״̬1ˢ��                                                                                        
* ������� :                                                                             
* ���ز��� :                                                                  
* ����˵�� :                                                                                                 
************************************************************************************************************************
*/
void ChairState1Refresh(void)
{
	gSendChairState1ToBlueToothApp.Byte4.SysRun = SystemRunFlag;
	gSendChairState1ToBlueToothApp.Byte4.Pause = PauseFlag;

	gSendChairState1ToBlueToothApp.Byte5.FullBack =((gbCoreManualFunction.All || gbCoreKneadFunction.All) && DiyprocessFlag)&&(!(SpotRunFlag||PartialRunFlag));
	gSendChairState1ToBlueToothApp.Byte5.Spot = ((gbCoreManualFunction.All || gbCoreKneadFunction.All) && DiyprocessFlag)&&(SpotRunFlag);
	gSendChairState1ToBlueToothApp.Byte5.Partial = ((gbCoreManualFunction.All || gbCoreKneadFunction.All) && DiyprocessFlag)&&(PartialRunFlag);
	gSendChairState1ToBlueToothApp.Byte5.MoveUp = MoveUpFlag;
	gSendChairState1ToBlueToothApp.Byte5.MoveDown = MoveDownFlag;
	gSendChairState1ToBlueToothApp.Byte5.BackScanning = BackScanningFlag;
//	gSendChairState1ToBlueToothApp.Byte5.BackHeightAdjust = BackHeightAdjustFlag;

	gSendChairState1ToBlueToothApp.Byte6.BackScanFinish = BackScanFinishFlag;
	gSendChairState1ToBlueToothApp.Byte6.RollRun = (RollRunFlag&&DiyprocessFlag);
	gSendChairState1ToBlueToothApp.Byte6.Knead1Run = ((KneadWaveOn1RunFlag || Knead1RunFlag || KneadOn1RunFlag || KneadOn3RunFlag || DualAction1RunFlag)&&DiyprocessFlag);
	gSendChairState1ToBlueToothApp.Byte6.Knead2Run = ((KneadWaveOn2RunFlag || Knead2RunFlag || KneadOn2RunFlag || KneadOn4RunFlag || DualAction2RunFlag)&&DiyprocessFlag);
	gSendChairState1ToBlueToothApp.Byte6.Swedish1Run = (Swedish1RunFlag&&DiyprocessFlag);
	gSendChairState1ToBlueToothApp.Byte6.Swedish2Run = (Swedish2RunFlag&&DiyprocessFlag);
	gSendChairState1ToBlueToothApp.Byte6.Tap1Run = ((Tap1RunFlag ||DualAction1RunFlag)&&DiyprocessFlag);

	gSendChairState1ToBlueToothApp.Byte7.Tap2Run = ((Tap2RunFlag ||DualAction2RunFlag)&&DiyprocessFlag);
	gSendChairState1ToBlueToothApp.Byte7.Shiatsu1Run = (Shiatsu1RunFlag&&DiyprocessFlag);
	gSendChairState1ToBlueToothApp.Byte7.Shiatsu2Run = (Shiatsu2RunFlag&&DiyprocessFlag);
	gSendChairState1ToBlueToothApp.Byte7.Clap1Run = (Clap1RunFlag&&DiyprocessFlag);
	gSendChairState1ToBlueToothApp.Byte7.Clap2Run = (Clap2RunFlag&&DiyprocessFlag);

	gSendChairState1ToBlueToothApp.Byte8.RollState = RollRunFlag;
	gSendChairState1ToBlueToothApp.Byte8.Knead1State = (KneadWaveOn1RunFlag || Knead1RunFlag || KneadOn1RunFlag || KneadOn3RunFlag || DualAction1RunFlag);
	gSendChairState1ToBlueToothApp.Byte8.Knead2State = (KneadWaveOn2RunFlag || Knead2RunFlag || KneadOn2RunFlag || KneadOn4RunFlag || DualAction2RunFlag);
	gSendChairState1ToBlueToothApp.Byte8.Swedish1State = Swedish1RunFlag;
	gSendChairState1ToBlueToothApp.Byte8.Swedish2State = Swedish2RunFlag;
	gSendChairState1ToBlueToothApp.Byte8.Tap1State = Tap1RunFlag || DualAction1RunFlag;
	gSendChairState1ToBlueToothApp.Byte8.Tap2State = Tap2RunFlag || DualAction2RunFlag;
	gSendChairState1ToBlueToothApp.Byte8.Shiatsu1State = Shiatsu1RunFlag;
	
	gSendChairState1ToBlueToothApp.Byte9.Shiatsu2State = Shiatsu2RunFlag;
	gSendChairState1ToBlueToothApp.Byte9.Clap1State = Clap1RunFlag;
	gSendChairState1ToBlueToothApp.Byte9.Clap2State = Clap2RunFlag;
	gSendChairState1ToBlueToothApp.Byte9.Width = GetLcdWidthLevel();
	
	gSendChairState1ToBlueToothApp.Byte10.Strength = GetLcdStrengthLevel();
	
	gSendChairState1ToBlueToothApp.Byte11.Speed = GetLcdSpeedLevel();

	gSendChairState1ToBlueToothApp.Byte12.Intensity = GetLcdIntensityLevel();

	gSendChairState1ToBlueToothApp.Byte13.Flex3D = GetLcdFlexLevel();

	gSendChairState1ToBlueToothApp.Byte14.BackPoint = gBackPointDisplay;

	gSendChairState1ToBlueToothApp.Byte16.FeetSpikeUpRun = (FeetSpikeUpRunFlag);
	gSendChairState1ToBlueToothApp.Byte16.FeetSpikeDownRun = (FeetSpikeDownRunFlag);
	gSendChairState1ToBlueToothApp.Byte16.BackSpikeDownRun = (BackSpikeDownRunFlag);
	gSendChairState1ToBlueToothApp.Byte16.BackSpikeUpRun = (BackSpikeUpRunFlag);
	
	gSendChairState1ToBlueToothApp.Byte17.ClavesGasStateFlag = CalvesGas1_IO;
	gSendChairState1ToBlueToothApp.Byte17.FeetGasStateFlag = FeetGas1_IO;
	gSendChairState1ToBlueToothApp.Byte17.ShoulderGasStateFlag = ShoulderGas1_IO;
	gSendChairState1ToBlueToothApp.Byte17.Arms1GasStateFlag = ArmsGas1_IO;
	gSendChairState1ToBlueToothApp.Byte17.Arms2GasStateFlag = ArmsGas2_IO;
//	gSendChairState1ToBlueToothApp.Byte17.LumbarGasStateFlag = SeatGas1_IO;

}

/*
************************************************************************************************************************
* �������� : ChairState2Refresh                                                                                                         
* �������� : APP��Ħ��״̬2ˢ��                                                                                     
* ������� :                                                                             
* ���ز��� :                                                                  
* ����˵�� :                                                                                                 
************************************************************************************************************************
*/
void ChairState2Refresh(void)
{
	
	gSendChairState2ToBlueToothApp.Byte4.BackHeatState = LumbarHeatRunFlag;
//	gSendChairState2ToBlueToothApp.Byte4.ClavesHeatState = FeetHeatRunFlag;
	gSendChairState2ToBlueToothApp.Byte4.RollerState = RollerRunFlag;
	
	gSendChairState2ToBlueToothApp.Byte5.HomeRun = HomeRunFlag;
	gSendChairState2ToBlueToothApp.Byte5.ZeroGravity1Run = (ZeroGravityRunFlag &&  (gZeroGravityMode == 1));
	gSendChairState2ToBlueToothApp.Byte5.ZeroGravity2Run = (ZeroGravityRunFlag &&  (gZeroGravityMode == 2));
//	gSendChairState2ToBlueToothApp.Byte5.ZeroGravity3Run = (ZeroGravityRunFlag &&  (gZeroGravityMode == 3));

	gSendChairState2ToBlueToothApp.AutoMassageNum_Byte6 = GetAutoProcessFunNum();

	gSendChairState2ToBlueToothApp.Byte7.AutoMassageType = GetAutoMassageType();
	
	gSendChairState2ToBlueToothApp.Byte8.ShoulderGasRun = ShoulderGasRunFlag;
	gSendChairState2ToBlueToothApp.Byte8.ArmsGasRun = ArmsGasRunFlag;
	gSendChairState2ToBlueToothApp.Byte8.ClavesGasRun = FeetCalvesGasRunFlag || CalvesGasRunFlag;
//	gSendChairState2ToBlueToothApp.Byte8.FeetGasRun = FeetCalvesGasRunFlag || FeetGasRunFlag;
	gSendChairState2ToBlueToothApp.Byte8.AutoGasRun = AutoGasRunFlag;

	gSendChairState2ToBlueToothApp.Byte9.BackHeatRun = LumbarHeatRunFlag;
//	gSendChairState2ToBlueToothApp.Byte9.ClavesHeatRun = LumbarHeatRunFlag;
	gSendChairState2ToBlueToothApp.Byte9.RollerRun = RollerRunFlag ||RollerFeetCalvesGasRunFlag;
	
	gSendChairState2ToBlueToothApp.Byte10.SoundPulseRun = TapWaveRunFlag;

	if(APPUserDefineAirRunFlag || APPUserDefineCoreAutoRunFlag ){
		gSendChairState2ToBlueToothApp.Byte12.Bit.PartMassageShoulder = (gUserDefineInfo & 0x01) ? 1:0;
		gSendChairState2ToBlueToothApp.Byte12.Bit.PartMassageArm = (gUserDefineInfo & 0x02) ? 1:0;
		gSendChairState2ToBlueToothApp.Byte12.Bit.PartMassageButton = (gUserDefineInfo & 0x04) ? 1:0;
		gSendChairState2ToBlueToothApp.Byte12.Bit.PartMassageCalves = (gUserDefineInfo & 0x08) ? 1:0;
		gSendChairState2ToBlueToothApp.Byte12.Bit.PartMassageLumbar = (gUserDefineInfo & 0x10) ? 1:0;
	}else{
		gSendChairState2ToBlueToothApp.Byte12.All = 0;
	}

	gSendChairState2ToBlueToothApp.Byte13.All = gbUserDefinedAutoFunction.All;

	if(gbUserDefinedAutoFunction.All > 0)
		gSendChairState2ToBlueToothApp.Byte14.DIYRunTime = gMassageRunTimeMinDIY-gMassageRunTimeMin + 1;
	else
		gSendChairState2ToBlueToothApp.Byte14.DIYRunTime = 0;
	
//	gSendChairState2ToBlueToothApp.Byte15.StartAcheScan = HriPalusRunFlag || AcheAutoFlag;
//	gSendChairState2ToBlueToothApp.Byte15.AcheScanning = HriPalusRunFlag && !HriPalusScanFinishFlag;
//	gSendChairState2ToBlueToothApp.Byte15.AcheScanFinish = HriPalusScanFinishFlag;

//	gSendChairState2ToBlueToothApp.Byte16.AcheShoulderNeckData = AcheNeckShoulderData;
//	gSendChairState2ToBlueToothApp.Byte16.AcheBackData = AcheBackData;
//	gSendChairState2ToBlueToothApp.Byte16.AcheLumbarButtoData = AcheLumbarButtonData;
	
	gSendChairState2ToBlueToothApp.MassageRunTimeMin_Byte18 = gMassageRunTimeMin;

	gSendChairState2ToBlueToothApp.MassageRunTimeSec_Byte19 = gMassageRunTimeSec;

}

/*
************************************************************************************************************************
* �������� : ChairState3Refresh                                                                                                         
* �������� : APP��Ħ��״̬3ˢ��                                                                                     
* ������� :                                                                             
* ���ز��� :                                                                  
* ����˵�� :                                                                                                 
************************************************************************************************************************
*/
void ChairState3Refresh(void)
{
	gSendChairState3ToBlueToothApp.ChairIDCode[0] = 0X36;//"6"
	gSendChairState3ToBlueToothApp.ChairIDCode[1] = 0X32;//"2"
	gSendChairState3ToBlueToothApp.ChairIDCode[2] = 0X36;//"6"
	gSendChairState3ToBlueToothApp.ChairIDCode[3] = 0X32;//"2"
	gSendChairState3ToBlueToothApp.Byte5.ChairResetState = (CorePositionTopFlag && BackSpikeResetFlag /*&& FeetSpikeResetFlag*/);
//	gSendChairState3ToBlueToothApp.Byte5.ChildLockRun = ChildLockFlag;
}
/*
************************************************************************************************************************
* �������� : SendAPPDataToBlueTooth                                                                                                         
* �������� : APP���ݰ�����                                                                                        
* ������� :                                                                             
* ���ز��� :                                                                  
* ����˵�� :                                                                                                
************************************************************************************************************************
*/
uint8_t SendAPPDataToBlueTooth(void)
{
	static uint8_t sSendOption,sSendOption1,sSendOptionCount;
	uint8_t UartSendFlag,CheckSum,i;

	UartSendFlag = 0;
	sSendOptionCount++;
	memset(pBlueToothAPP->TxBuf, 0x00, CEN_TO_BLUETOOTH_TX_SIZE);
	pBlueToothAPP->TxBuf[0] = 0x7b;
	if(pBlueToothAPP->CSFlag.Bit.BlueToothAPPSendBackDataFlag){
		pBlueToothAPP->CSFlag.Bit.BlueToothAPPSendBackDataFlag = FALSE;
		pBlueToothAPP->TxBuf[1] = 0xb0;
		pBlueToothAPP->TxBuf[2] = 1;
		pBlueToothAPP->TxBuf[3] = gBlueToothAPPData[3];
		UartSendFlag = 1;
	}else if(pBlueToothAPP->CSFlag.Bit.BlueToothAPPSendIDFlag){
		pBlueToothAPP->CSFlag.Bit.BlueToothAPPSendIDFlag = FALSE;
		pBlueToothAPP->TxBuf[1] = 0xb6;
//		pBlueToothAPP->TxBuf[2] = 17;
//		memcpy((uint8_t *)&pBlueToothAPP->TxBuf[3],(uint8_t *)&gStorageData.IDCode[2],17);
		pBlueToothAPP->TxBuf[2] = 16;
		memcpy((uint8_t *)&pBlueToothAPP->TxBuf[3],(uint8_t *)&gStorageData.IDCode[2],13);
		memcpy((uint8_t *)&pBlueToothAPP->TxBuf[16],(uint8_t *)&gStorageData.IDCode[16],3);
		UartSendFlag = 1;
	}else if(pBlueToothAPP->CSFlag.Bit.BlueToothAPPSendDIYPackageNumFlag){
		pBlueToothAPP->CSFlag.Bit.BlueToothAPPSendDIYPackageNumFlag = FALSE;
		pBlueToothAPP->TxBuf[1] = 0xbd;
		pBlueToothAPP->TxBuf[2] = 2;
		pBlueToothAPP->TxBuf[3] = gBlueToothAPPData[3];
		pBlueToothAPP->TxBuf[4] = (gBlueToothAPPData[4] & 0x0f) | 0xf0 ;
		UartSendFlag = 1;
	}else{
			if(sSendOptionCount >= 10){//250ms
				if(SystemRunFlag){
					if(sSendOption == 0){
						pBlueToothAPP->TxBuf[1] = 0xb1;
						pBlueToothAPP->TxBuf[2] = 16;
						ChairState1Refresh();
						memcpy((uint8_t *)&pBlueToothAPP->TxBuf[3],(uint8_t *)&gSendChairState1ToBlueToothApp.Byte4,pBlueToothAPP->TxBuf[2]);
						UartSendFlag = 1;
						sSendOption = 1;
					}else if(sSendOption == 1){
						pBlueToothAPP->TxBuf[1] = 0xb2;
						pBlueToothAPP->TxBuf[2] = 16;
						ChairState2Refresh();
						memcpy((uint8_t *)&pBlueToothAPP->TxBuf[3],(uint8_t *)&gSendChairState2ToBlueToothApp.Byte4,pBlueToothAPP->TxBuf[2]);
						UartSendFlag = 1;
						if(glErrorNo > 0)
							sSendOption = 2;
						else
							sSendOption = 0;
					
					}else{
						if(glErrorNo > 0){
							pBlueToothAPP->TxBuf[1] = 0xb8;
							pBlueToothAPP->TxBuf[2] = 4;
							pBlueToothAPP->TxBuf[3] = (Uchar)((glErrorNo>>1));
							pBlueToothAPP->TxBuf[4] = (Uchar)((glErrorNo>>9));
							pBlueToothAPP->TxBuf[5] = (Uchar)((glErrorNo>>17));
							pBlueToothAPP->TxBuf[6] = (Uchar)((glErrorNo>>25));
						}
						UartSendFlag = 1;
						sSendOption = 0;
					}
					sSendOption1 = 0;
				}else{
					if(sSendOption1 == 0){
						pBlueToothAPP->TxBuf[1] = 0xb3;
						pBlueToothAPP->TxBuf[2] = 5;//4
						ChairState3Refresh();
						memcpy((uint8_t *)&pBlueToothAPP->TxBuf[3],(uint8_t *)&gSendChairState3ToBlueToothApp.ChairIDCode[0],pBlueToothAPP->TxBuf[2]);
						UartSendFlag = 1;
						if(glErrorNo > 0)
							sSendOption1 = 1;
						else
							sSendOption1 = 0;
					}else{
						if(glErrorNo > 0){
							pBlueToothAPP->TxBuf[1] = 0xb8;
							pBlueToothAPP->TxBuf[2] = 4;
							pBlueToothAPP->TxBuf[3] = (Uchar)((glErrorNo>>1));
							pBlueToothAPP->TxBuf[4] = (Uchar)((glErrorNo>>9));
							pBlueToothAPP->TxBuf[5] = (Uchar)((glErrorNo>>17));
							pBlueToothAPP->TxBuf[6] = (Uchar)((glErrorNo>>25));
						}
						UartSendFlag = 1;
						sSendOption1 = 0;
					}
					sSendOption = 0;	
				}
				sSendOptionCount = 0;
			}
	}

	if(UartSendFlag)
	{
		pBlueToothAPP->TxLen = pBlueToothAPP->TxBuf[2] + 4; //����֡ͷ�������룬���ȣ�У����
		CheckSum = 0;
		for(i=0 ; i<(pBlueToothAPP->TxLen-1) ; i++)
		{
			CheckSum += pBlueToothAPP->TxBuf[i];
		}
		pBlueToothAPP->TxBuf[pBlueToothAPP->TxLen-1] = CheckSum;
		BSP_UART_TxData(CEN_BLUETOOTH_UART_PORT, pBlueToothAPP->TxBuf, pBlueToothAPP->TxLen);
	}
	return UartSendFlag;
}

Uchar DIYDataProcess(Uchar *SourceData)
{
	static  Uchar NumHis;
	static  Uchar RecvDIYData[DIYDefineDataNum][DIYDefineDataLength] = {0};
	Uchar Num;
	Uchar SearchDefineNum,SearchDefineLength;
	Uchar BrkFlag,MassageRunTimeMinTemp;
	
	if(SourceData == NULL)
		return FAIL;
	
	Num = *(SourceData + 1) & 0x0f;
	if(NumHis == Num || Num == 0 || (NumHis == 0 && Num != 1))	//��������F1��Ӱ��
		return FAIL;
	else
		NumHis = Num;
	if(Num == 1)	//��һ��������
	{
		memset((Uchar *)&RecvDIYData[0][0],0x00,DIYDefineDataLength*DIYDefineDataNum);
	}
	memcpy((Uchar *)&RecvDIYData[Num-1][0],(SourceData+2),DIYDefineDataLength);
	if(Num == DIYDefineDataNum ||(*(SourceData+1) & 0xf0))
	{
		if(!SystemRunFlag || PauseFlag)	
			return FAIL;

		memcpy((Uchar *)&DIYDefineProgram[0][0],(Uchar *)&RecvDIYData[0][0],DIYDefineDataLength*DIYDefineDataNum);
		NumHis = 0;		//��������F1��Ӱ��
		BrkFlag = 0;
		MassageRunTimeMinTemp = 15; //����15min
		UserDefinedCoreNeedBackscanRunFlag = 0;
		for(SearchDefineNum = DIYDefineDataNum;SearchDefineNum>0;SearchDefineNum--)
		{//����ʵ������ʱ�䣬�Ӻ���ǰ��ѯ�����������˳�ѭ��
			for(SearchDefineLength = DIYDefineDataLength;SearchDefineLength>0;SearchDefineLength--)
			{
				if(DIYDefineProgram[SearchDefineNum-1][SearchDefineLength-1]>0) //14~0
				{
					BrkFlag = 1;	//�Ӻ�����ǰ��ѯ������ֵ��������ǰѭ��
					break;
				}
				
			}
			
			if(BrkFlag) //��⵽����ֵ���˳���ǰѭ��
			{
				break;
			}
			else
			{
				if(MassageRunTimeMinTemp>0)		//û����ֵ��ʱ��ݼ�
					MassageRunTimeMinTemp--;
			}		
		}
		if(MassageRunTimeMinTemp>0)
		{    	
			gMassageRunTimeMin = MassageRunTimeMinTemp - 1;	//��59�뿪ʼ ����ֹ����14 -15����
			gMassageRunTimeSec = 59;
			gMassageRunTimeMinDIY = gMassageRunTimeMin; //DIY����ʱ��(ʹ�ô�0��ʼ)(��gMassageRunTimeMin�����ļ��㷽ʽ�й�)
			switch(*(SourceData))
			{
				case 1:
					GasAndCoreFunctionClose();
					UserDefinedAutoRunFlag = 1;
					break;
				case 2:
					GasAndCoreFunctionClose();
					UserDefinedAuto1RunFlag = 1;
					break;
				case 3:
					GasAndCoreFunctionClose();
					UserDefinedAuto2RunFlag = 1;
					break;
				default:
					return FAIL;

			}
			for(SearchDefineNum = 0;SearchDefineNum < MassageRunTimeMinTemp;SearchDefineNum++)		//�ж��Ƿ���Ҫ���м粿���
			{
				if(DIYDefineProgram[SearchDefineNum][0]>0 && DIYDefineProgram[SearchDefineNum][1]>0)
				{
					UserDefinedCoreNeedBackscanRunFlag = 1;
					break;
				}			
			}
		}
		else
		{
			if(UserDefinedAutoRunFlag || UserDefinedAuto1RunFlag ||UserDefinedAuto2RunFlag)
			{//������Զ���������
				GasAndCoreFunctionClose();
			}
		}
		BuzzerOn(2);	
	}	
	return SUCCESS;
}

#endif

/*
************************************************************************************************************************
* �������� : ReceiveDataFromBlueTooth                                                                                                    
* �������� : �����������ݴ���                                                                          
* ������� : void                                                                 
* ���ز��� : ��                                                             
* ����˵�� : ʵʱ��ѯ����״̬                                                                                                
************************************************************************************************************************
*/
void ReceiveDataFromBlueTooth(void)
{
	uint8_t KeyAddVal; 
	if(TRUE == pBlueTooth->CSFlag.Bit.BlueToothRxOkFlag){
	
		pBlueTooth->CSFlag.Bit.BlueToothRxOkFlag = FALSE;
		pBlueTooth->CSFlag.Bit.BlueToothLoseLinkFlag = FALSE;
		pBlueTooth->RxLoseLink1sTimer = 0;

//--------------------�ظ�OKָ��--------------------------------	
//���־λ���ȼ�����뷢�����ȼ���ͬ
		if(pBlueTooth->CSFlag.Bit.BlueToothSendOnFlag){
			if((strstr(pBlueTooth->RxBuf, pBlueToothCmd_OK)) && (gCurrentSendCmdValue == BLUETOOTH_ON )){
				pBlueTooth->CSFlag.Bit.BlueToothSwitchState = TRUE;
				pBlueTooth->CSFlag.Bit.BlueToothSendOnFlag = FALSE;
			}
		}
		else if(pBlueTooth->CSFlag.Bit.BlueToothSendOffFlag){
			if((strstr(pBlueTooth->RxBuf, pBlueToothCmd_OK)) && (gCurrentSendCmdValue == BLUETOOTH_OFF )){
				pBlueTooth->CSFlag.Bit.BlueToothSwitchState = FALSE;
				pBlueTooth->CSFlag.Bit.BlueToothSendOffFlag = FALSE;
			}
		}
		else if(pBlueTooth->CSFlag.Bit.BlueToothSendSoundSourceSelectFlag){
			if((strstr(pBlueTooth->RxBuf, pBlueToothCmd_OK)) && (gCurrentSendCmdValue == BLUETOOTH_SOUNDSOURCE_SELECT )){
				pBlueTooth->CSFlag.Bit.BlueToothSendSoundSourceSelectFlag = FALSE;
				if(!GetBlueToothSendCmdState(BLUETOOTH_SWITCH_STATE)){
//					SetBlueToothSendCmd(BLUETOOTH_FUN_OFF);
					BlueToothSetFlag = 1;
				}
			}
		}
		else if(pBlueTooth->CSFlag.Bit.BlueToothSendPlayMusicFlag){
			if((strstr(pBlueTooth->RxBuf, pBlueToothCmd_OK))  && (gCurrentSendCmdValue == BLUETOOTH_PLAY_MUSIC )){
				pBlueTooth->CSFlag.Bit.BlueToothSendPlayMusicFlag = FALSE;
			}
		}
		else if(pBlueTooth->CSFlag.Bit.BlueToothSendMusicModeFlag){
			if((strstr(pBlueTooth->RxBuf, pBlueToothCmd_OK))  && (gCurrentSendCmdValue == BLUETOOTH_MUSIC_MODE )){
				pBlueTooth->CSFlag.Bit.BlueToothSendMusicModeFlag = FALSE;
			}
		}
		else if(pBlueTooth->CSFlag.Bit.BlueToothSendMusicVolumeSetFlag){
			if((strstr(pBlueTooth->RxBuf, pBlueToothCmd_OK)) && (gCurrentSendCmdValue == BLUETOOTH_MUSIC_VOL )){
				pBlueTooth->CSFlag.Bit.BlueToothSendMusicVolumeSetFlag = FALSE;
			}
		}
/////////////////////////////////////////////////////////////////////////////////////////////		
		if(pBlueTooth->CSFlag.Bit.BlueToothSendSearchFlag){
			if(strstr(pBlueTooth->RxBuf, pBlueToothCmd_ENALBE)){
				pBlueTooth->CSFlag.Bit.BlueToothSwitchState = TRUE;
				pBlueTooth->CSFlag.Bit.BlueToothSendSearchFlag = FALSE;
			}else if(strstr(pBlueTooth->RxBuf, pBlueToothCmd_DISENALBE)){
				pBlueTooth->CSFlag.Bit.BlueToothSwitchState = FALSE;
				pBlueTooth->CSFlag.Bit.BlueToothSendSearchFlag = FALSE;
			}
		}

		if(pBlueTooth->CSFlag.Bit.BlueToothSendfFunOFFFlag){
			if((strstr(pBlueTooth->RxBuf, pBlueToothCmd_BREDR_CLOSE)) && (gCurrentSendCmdValue == BLUETOOTH_FUN_OFF )){
				pBlueTooth->CSFlag.Bit.BlueToothSendfFunOFFFlag = FALSE;
				BlueToothSetFlag = 0;
			}
		}
		
		if(pBlueTooth->CSFlag.Bit.BlueToothSendBLEOnFlag){
			if(strstr(pBlueTooth->RxBuf, pBlueToothCmd_LE_OPEN)){
				pBlueTooth->CSFlag.Bit.BlueToothBLESwitchState = TRUE;
				pBlueTooth->CSFlag.Bit.BlueToothSendBLEOnFlag = FALSE;
			}
		}
		
		if(pBlueTooth->CSFlag.Bit.BlueToothSendBLEOffFlag){
			if(strstr(pBlueTooth->RxBuf, pBlueToothCmd_LE_CLOSE)){
				pBlueTooth->CSFlag.Bit.BlueToothBLESwitchState = FALSE;
				pBlueTooth->CSFlag.Bit.BlueToothSendBLEOffFlag = FALSE;
			}
		}
		/********************Ԥ�� ���������豸״̬��ѯ********************/
		if(strstr(pBlueTooth->RxBuf, pBlueToothCmd_A_CONNECTED))
			pBlueTooth->CSFlag.Bit.BlueToothA2DPConnectedState = TRUE;
		else if(strstr(pBlueTooth->RxBuf, pBlueToothCmd_A_DISCONNECTED))
			pBlueTooth->CSFlag.Bit.BlueToothA2DPConnectedState = FALSE;
		else if(strstr(pBlueTooth->RxBuf, pBlueToothCmd_LE_CONNECTED))
			pBlueTooth->CSFlag.Bit.BlueToothBLEConnectedState = TRUE;
		else if(strstr(pBlueTooth->RxBuf, pBlueToothCmd_LE_DISCONNECTED))
			pBlueTooth->CSFlag.Bit.BlueToothBLEConnectedState = FALSE;
		/*
		*********************************************************************
		*	BLUETOOTH_CONNECTED_INIT 		BTS:0	---->   ��ʼ��                                                                                            
		*	BLUETOOTH_CONNECTED_WAIT		BTS:1	---->	�ȴ�����                                                                      
		*	BLUETOOTH_CONNECTED_BACK		BTS:2	---->	���ڻ���                                                                    
		*	BLUETOOTH_CONNECTED_ALREADY		BTS:3	---->	������                                                         
		*	BLUETOOTH_CONNECTED_TELEPHONE	BTS:4	---->	ͨ��״̬
		*	BLUETOOTH_CONNECTED_MUSIC		BTS:5	---->	����״̬
		*********************************************************************
		*/
		if(pBlueTooth->CSFlag.Bit.BlueToothSendSearchConnectedFlag){
			if(strstr(pBlueTooth->RxBuf, pBlueToothCmd_CONNECTED_STATE)){
				pBlueTooth->CSFlag.Bit.BlueToothSendSearchConnectedFlag = FALSE;
				switch(pBlueTooth->RxBuf[sizeof(pBlueToothCmd_CONNECTED_STATE)])
				{
					case BLUETOOTH_CONNECTED_INIT:
						pBlueTooth->CSFlag.Bit.BlueToothA2DPConnectedState = FALSE;
						break;
					case BLUETOOTH_CONNECTED_WAIT:
						pBlueTooth->CSFlag.Bit.BlueToothA2DPConnectedState = FALSE;
						break;
					case BLUETOOTH_CONNECTED_BACK:
						break;
					case BLUETOOTH_CONNECTED_ALREADY:
						pBlueTooth->CSFlag.Bit.BlueToothA2DPConnectedState = TRUE;
						break;
					case BLUETOOTH_CONNECTED_TELEPHONE:
						pBlueTooth->CSFlag.Bit.BlueToothA2DPConnectedState = TRUE;
						break;
					case BLUETOOTH_CONNECTED_MUSIC:
						pBlueTooth->CSFlag.Bit.BlueToothA2DPConnectedState = TRUE;
						break;
				}
			}
		}
	}

#if BLUETOOTHAPP
	if(TRUE == pBlueToothAPP->CSFlag.Bit.BlueToothAPPRxOkFlag){

		pBlueToothAPP->CSFlag.Bit.BlueToothAPPRxOkFlag = FALSE;
		pBlueToothAPP->CSFlag.Bit.BlueToothAPPLoseLinkFlag = FALSE;
		pBlueToothAPP->RxLoseLink1sTimer = 0;
		
		if(gBlueToothAPPData[1] == 0xa0){

			LCDLight_ON();
			KeyAddVal = gBlueToothAPPData[4];
			pBlueToothAPP->CSFlag.Bit.BlueToothAPPSendBackDataFlag = TRUE;

			if((ChildLockFlag && !SystemRunFlag) && !(gBlueToothAPPData[3] == 0x02 || gBlueToothAPPData[3] == 0x05 || gBlueToothAPPData[3] == 0x00 /*|| gBlueToothAPPData[3] == 101*/))
			{
			}
			else
			{
				if(gBlueToothAPPData[3] == BlueTooth_SetTimer_KeyVal){
					KeyTimerAdj(KeyAddVal);	
				}else if(gBlueToothAPPData[3] == BlueTooth_AutoMassage_KeyVal ||gBlueToothAPPData[3] == BlueTooth_Intelligent_KeyVal){
					AutoRecommendNum = 0;
					if(gBlueToothAPPData[3] == BlueTooth_Intelligent_KeyVal){
						AutoRecommendNum = KeyAddVal;
						if(GetAutoProcessFunNum()!= AutoRecommendNum){//�����Ƽ�ͬһ�����򣬲���Ӧ��һ��
							KeyPressEvent(KeyAddVal,(uint8_t*)BlueToothAutoMassageKeyValTab,BlueToothUse,sizeof(BlueToothAutoMassageKeyValTab));	/*��ֵ����д���*/	
						}else{
							BuzzerOn(2);
						}
					}else{
						KeyPressEvent(KeyAddVal,(uint8_t*)BlueToothAutoMassageKeyValTab,BlueToothUse,sizeof(BlueToothAutoMassageKeyValTab));	/*��ֵ����д���*/
					}
				}else if(gBlueToothAPPData[3] == BlueTooth_SetStrength_KeyVal){
					KeyStrength(KeyAddVal);
				}else if(gBlueToothAPPData[3] == BlueTooth_SetSpeed_KeyVal){
					KeySpeed(KeyAddVal);
				}else if(gBlueToothAPPData[3] == BlueTooth_SetIntensity_KeyVal){
					KeyIntensity(KeyAddVal);
				}else if(gBlueToothAPPData[3] == BlueTooth_SetCoreFlex_KeyVal){
					KeyManual3D(KeyAddVal);
				}else if(gBlueToothAPPData[3] == BlueTooth_SetCoreWidth_KeyVal){
					KeyWidth(KeyAddVal);
				}else if(gBlueToothAPPData[3] == BlueTooth_ManualUpDown_KeyVal){
					switch(KeyAddVal)
				  	{
				  		case 0:
				  			APPManualUpDownFlag = 0;
				  			break;
				  		case 1:
				  			WifiKeyCoreMoveUp();
				  			break;
				  		case 2:
							WifiKeyCoreMoveDown();
				  			break;
				  		default:
				  			break;
				  	}
				}else{
//					if(gBlueToothAPPData[3] == BlueTooth_PartShoulderMassage_KeyVal){//�羱
//						if(APPUserDefineCoreAutoRunFlag && (gUserDefineInfo & 0x01))
//						{
//							gUserDefineInfo &= ~0x01;
//						}
//						else
//						{
//							if(APPUserDefineAirRunFlag || APPUserDefineCoreAutoRunFlag)
//								gUserDefineInfo |= 0x01;
//							else
//								gUserDefineInfo = 0x01;
//						}
//					}else if(gBlueToothAPPData[3] == BlueTooth_PartArmMassage_KeyVal){	//�ֲ�
//						if(APPUserDefineAirRunFlag && (gUserDefineInfo & 0x02))
//						{
//							gUserDefineInfo &= ~0x02;
//						}
//						else
//						{
//							if(APPUserDefineAirRunFlag || APPUserDefineCoreAutoRunFlag)
//								gUserDefineInfo |= 0x02;
//							else
//								gUserDefineInfo = 0x02;
//						}
//					}else if(gBlueToothAPPData[3] == BlueTooth_PartLumbarMassage_KeyVal){	//����
//						if(APPUserDefineCoreAutoRunFlag && (gUserDefineInfo & 0x20))
//						{
//							gUserDefineInfo &= ~0x20;
//						}
//						else
//						{
//							if(APPUserDefineAirRunFlag || APPUserDefineCoreAutoRunFlag)
//								gUserDefineInfo |= 0x20;
//							else
//								gUserDefineInfo = 0x20;
//						}
//					}else if(gBlueToothAPPData[3] == BlueTooth_PartButtonMassage_KeyVal){	//�β�
//						if(APPUserDefineCoreAutoRunFlag && (gUserDefineInfo & 0x04))
//						{
//							gUserDefineInfo &= ~0x04;
//						}
//						else
//						{
//							if(APPUserDefineAirRunFlag || APPUserDefineCoreAutoRunFlag)
//								gUserDefineInfo |= 0x04;
//							else
//								gUserDefineInfo = 0x04;
//						}
//					}else if(gBlueToothAPPData[3] == BlueTooth_PartCalvesMassage_KeyVal){	//�Ȳ�
//						if(APPUserDefineAirRunFlag && (gUserDefineInfo & 0x08))
//						{
//							gUserDefineInfo &= ~0x08;
//						}
//						else
//						{
//							if(APPUserDefineAirRunFlag || APPUserDefineCoreAutoRunFlag)
//								gUserDefineInfo |= 0x08;
//							else
//								gUserDefineInfo = 0x08;
//						}
//					}
					
					if(gBlueToothAPPData[3] == BlueTooth_PartMassage_KeyVal){
						gUserDefineInfo = KeyAddVal;
					}
					
					
					if(gBlueToothAPPData[3] == 1 && SystemRunFlag){
					}else if(gBlueToothAPPData[3] == 4 && !SystemRunFlag){
					}else{
						KeyPressEvent(gBlueToothAPPData[3],(uint8_t*)BlueToothKeyValTab,BlueToothUse,sizeof(BlueToothKeyValTab));
					}
				}
			}
			
		}else if(gBlueToothAPPData[1] == 0xa3){
			KeyPressEvent(0,(uint8_t*)BlueToothKeyValTab,BlueToothUse,sizeof(BlueToothKeyValTab));
		}else if(gBlueToothAPPData[1] == 0xa6){
			pBlueToothAPP->CSFlag.Bit.BlueToothAPPSendIDFlag = TRUE;
		}else if(gBlueToothAPPData[1] == 0xad){
			DIYDataProcess((Uchar *)&gBlueToothAPPData[3]);
			pBlueToothAPP->CSFlag.Bit.BlueToothAPPSendDIYPackageNumFlag = TRUE;
		}
	}
#endif
}
/*
************************************************************************************************************************
* �������� : GetBlueToothState                                                                                                    
* �������� : ��ȡ����BLE����״̬                                                                             
* ������� : void                                                                 
* ���ز��� : uint8_t                                                            
* ����˵�� : ��                                                                                           
************************************************************************************************************************
*/
//uint8_t GetBLEState(void)
//{
//	return pBlueTooth->CSFlag.Bit.BlueToothA2DPConnectedState;
//}
/*
************************************************************************************************************************
* �������� : GetBlueToothState                                                                                                    
* �������� : ��ȡ��������״̬                                                                             
* ������� : void                                                                 
* ���ز��� : uint8_t                                                            
* ����˵�� : ��                                                                                           
************************************************************************************************************************
*/
//uint8_t GetBlueToothState(void)
//{
//	return pBlueTooth->CSFlag.Bit.BlueToothSwitchState;
//}
/*
************************************************************************************************************************
* �������� : GetBlueToothLoseLinkState                                                                                                    
* �������� : ��ȡ����ͨ��״̬                                                                             
* ������� : void                                                                 
* ���ز��� : uint8_t                                                            
* ����˵�� : ��                                                                                           
************************************************************************************************************************
*/
//uint8_t GetBlueToothLoseLinkState(void)
//{
//	return pBlueTooth->CSFlag.Bit.BlueToothLoseLinkFlag;
//}
#if BLUETOOTHAPP
/*
************************************************************************************************************************
* �������� : GetBlueToothAPPLoseLinkState                                                                                                    
* �������� : ��ȡ������APPͨ��״̬                                                                             
* ������� : void                                                                 
* ���ز��� : uint8_t                                                            
* ����˵�� : ��                                                                                           
************************************************************************************************************************
*/
uint8_t GetBlueToothAPPLoseLinkState(void)
{
	return pBlueToothAPP->CSFlag.Bit.BlueToothAPPLoseLinkFlag;
}
#endif
/*
************************************************************************************************************************
* �������� : BlueToothValue1MsProcess                                                                                                    
* �������� : 1ms��ʱʱ��仯                                                                           
* ������� : void                                                                 
* ���ز��� : ��                                                          
* ����˵�� : ��                                                                                          
************************************************************************************************************************
*/
void	BlueToothValue1MsProcess(void)
{
	if(pBlueTooth->RxNothingTimer < 255)
		pBlueTooth->RxNothingTimer++;

#if BLUETOOTHAPP
	if(pBlueToothAPP->RxNothingTimer < 255)
		pBlueToothAPP->RxNothingTimer++;
#endif
}
/*
******************************************************************
*	Function Name				:	BlueTooth25Ms_Handle
*	Decription					:	Use to Do25MsEvent
*	Input Parameter				:	void
*	Return Parameter			:	void
*	Supplementary Instruction	:	None
******************************************************************
*/
void BlueTooth25Ms_Handle(void)
{
#if BLUETOOTHAPP
	uint8_t APPSendFlag;
	APPSendFlag = SendAPPDataToBlueTooth();
	if(!APPSendFlag)
#endif 
	{
		if((GetBlueToothSendCmdState(BLUETOOTH_ON) && (!GetBlueToothSendCmdState(BLUETOOTH_SWITCH_STATE) || PowerOnBlueToothSetFlag ))){
			SendDataToBlueTooth(BLUETOOTH_ON);
		}else if(GetBlueToothSendCmdState(BLUETOOTH_OFF) && (GetBlueToothSendCmdState(BLUETOOTH_SWITCH_STATE) || PowerOnBlueToothSetFlag)){
			SendDataToBlueTooth(BLUETOOTH_OFF);
		}else if(GetBlueToothSendCmdState(BLUETOOTH_BLE_OPEN)&& (!GetBlueToothSendCmdState(BLUETOOTH_BLE_SWITCH_STATE) || PowerOnBLESetFlag)){
			SendDataToBlueTooth(BLUETOOTH_BLE_OPEN);
		}else if(GetBlueToothSendCmdState(BLUETOOTH_BLE_CLOSE)&& (GetBlueToothSendCmdState(BLUETOOTH_BLE_SWITCH_STATE) || PowerOnBLESetFlag)){
			SendDataToBlueTooth(BLUETOOTH_BLE_CLOSE);
		}else if(GetBlueToothSendCmdState(BLUETOOTH_SOUNDSOURCE_SELECT)){
			SendDataToBlueTooth(BLUETOOTH_SOUNDSOURCE_SELECT);
		}else if(GetBlueToothSendCmdState(BLUETOOTH_PLAY_MUSIC)){
			SendDataToBlueTooth(BLUETOOTH_PLAY_MUSIC);
		}else if(GetBlueToothSendCmdState(BLUETOOTH_MUSIC_MODE)){
			SendDataToBlueTooth(BLUETOOTH_MUSIC_MODE);
		}else if(GetBlueToothSendCmdState(BLUETOOTH_MUSIC_VOL)){
			SendDataToBlueTooth(BLUETOOTH_MUSIC_VOL);
		}else if(GetBlueToothSendCmdState(BLUETOOTH_INQUIRE_STATE)){
			SendDataToBlueTooth(BLUETOOTH_INQUIRE_STATE);
		}else if(GetBlueToothSendCmdState(BLUETOOTH_CONNECTED_STATE)){
			SendDataToBlueTooth(BLUETOOTH_CONNECTED_STATE);
		}else if(GetBlueToothSendCmdState(BLUETOOTH_FUN_OFF)){
			SendDataToBlueTooth(BLUETOOTH_FUN_OFF);
		}
	}
}
/*
************************************************************************************************************************
* �������� : BlueTooth1SHandle                                                                                                    
* �������� : ���������ء�����״̬���в�ѯ��ͨ���쳣����                                                                           
* ������� : void                                                                 
* ���ز��� : ��                                                          
* ����˵�� : ���ʱ�䶼Ϊ1S                                                                                           
************************************************************************************************************************
*/
void BlueTooth1S_Handle(void)
{
	static uint8_t sSendSelect,sSendSelect1;
	
/********************����ʱ�������Ϳ�������ָ��Ͳ����в�ѯ**********************/
	if(!(TRUE == GetBlueToothSendCmdState(BLUETOOTH_ON) || TRUE == GetBlueToothSendCmdState(BLUETOOTH_OFF))){
		sSendSelect++;
		if(sSendSelect == 1)
			SetBlueToothSendCmd(BLUETOOTH_INQUIRE_STATE);
		else if(sSendSelect == 2){
			SetBlueToothSendCmd(BLUETOOTH_CONNECTED_STATE);
			sSendSelect = 0;
		}
	}

	
/********************����ʱ�����������ݵ�û�н��յ���ȷ����********************/
	if(pBlueTooth->RxLoseLink1sTimer < 255)
		pBlueTooth->RxLoseLink1sTimer++;
	if(pBlueTooth->RxLoseLink1sTimer > BLUETOOTH_LOSELINK_TIME){
		pBlueTooth->CSFlag.All &= ~0x03;					//��ʧͨ����Ҫ������״̬λ���
		pBlueTooth->CSFlag.Bit.BlueToothLoseLinkFlag = TRUE;
	}
	else{
		pBlueTooth->CSFlag.Bit.BlueToothLoseLinkFlag = FALSE;
	}
	
#if BLUETOOTHAPP
	if(pBlueToothAPP->RxLoseLink1sTimer < 255)
		pBlueToothAPP->RxLoseLink1sTimer++;
	if(pBlueToothAPP->RxLoseLink1sTimer > BLUETOOTH_LOSELINK_TIME){
		pBlueToothAPP->CSFlag.Bit.BlueToothAPPLoseLinkFlag = TRUE;
	}
	else{
		pBlueToothAPP->CSFlag.Bit.BlueToothAPPLoseLinkFlag = FALSE;
	}
#endif 

	sSendSelect1++;
	if(sSendSelect1 == 2){
		if(PowerOnBLESetFlag){
			if(GetBlueToothSendCmdState(BLUETOOTH_BLE_SWITCH_STATE) == gStorageData.BlueToothBLEState){
				PowerOnBLESetFlag = 0;
			}else{
				if(gStorageData.BlueToothBLEState){
					SetBlueToothSendCmd(BLUETOOTH_BLE_OPEN);
				}else{
					SetBlueToothSendCmd(BLUETOOTH_BLE_CLOSE);
				}
			}
		}
	}else if(sSendSelect1 == 5){
		sSendSelect1 = 0;
		if(PowerOnBlueToothSetFlag){
			if(GetBlueToothSendCmdState(BLUETOOTH_SWITCH_STATE) == gStorageData.BlueToothState){
				PowerOnBlueToothSetFlag = 0;
			}else{
				if(gStorageData.BlueToothState){
					SetBlueToothSendCmd(BLUETOOTH_ON);
				}else{
					SetBlueToothSendCmd(BLUETOOTH_OFF);
				}
			}
		}
	}
}
#if BLUETOOTHAPP
Uchar	GetAutoProcessFunNum(void)
{
	Uint32 	AutoFunTemp = 0,AutoFunTemp1 = 0;
 	if(ThaiMassageRunFlag) 
 		return 9;
 	else
	{
		Uchar	AutoFunNumTemp = 0,AutoFunNumTemp1 = 0;
		AutoFunTemp = gbCoreAutoFunction.All;
		AutoFunTemp1 = gbCoreAutoFunction1.All;
		while(!TestBit32(AutoFunTemp,AutoFunNumTemp) && AutoFunNumTemp < 32)
		{
			AutoFunNumTemp++;
		}
		while(!TestBit32(AutoFunTemp1,AutoFunNumTemp1) && AutoFunNumTemp1 < 32)
		{
			AutoFunNumTemp1++;
		}
		
		if(AutoFunNumTemp > 31)
		{
			if(AutoFunNumTemp1 > 31)
				return 0;	
			else 
				return	AutoFunNum1[AutoFunNumTemp1];  //ע�����鲻ҪԽ��	
		}
		else 
			return	AutoFunNum[AutoFunNumTemp];  //ע�����鲻ҪԽ��

		
	}
}

Uchar GetAutoMassageType(void)
{
	if(!SystemRunFlag)
	{
		return 0;
	}
	if((AutoRecommendNum == GetAutoProcessFunNum()) && (AutoRecommendNum != 0))
	{
		return 2;					//�����Ƽ�
	}
	else if(BallGameRunFlag ||GolfRunFlag ||SwimmingRunFlag || WalkRunFlag || RidingRunFlag || FitnessRunFlag
		||RunningRunFlag || BackBLumbarMassageRunFlag || NeckShoulderRunFlag)
	{
		AutoRecommendNum = 0;
		return 4;					//��������
	}
	else if(GetAutoProcessFunNum())
	{
		AutoRecommendNum = 0;
		return 1;					//�Զ�����
	}
	else
	{
		AutoRecommendNum = 0;
		return 0;
	}
}
#endif

void BlueToothMusicSetting(Uchar MusicNum)
{
	Uchar MusicNumTemp;
	MusicNumTemp = MusicNum;
	if(MusicNumTemp == 0xFF || MusicNumTemp == 0)
	{
		gBlueToothMusicBuff[ENUM_BLUETOOTH_MUSICNUM] = 0;
		gBlueToothMusicBuff[ENUM_BLUETOOTH_SOUNDSOURCE] = 0;
		SetBlueToothSendCmd(BLUETOOTH_SOUNDSOURCE_SELECT);	//��Դ�л�Ϊ����
	}
	else if(MusicNumTemp != gBlueToothMusicBuff[ENUM_BLUETOOTH_MUSICNUM])
	{
		if(gBlueToothMusicBuff[ENUM_BLUETOOTH_MUSICNUM] == 0)
		{
			if(gBlueToothMusicBuff[ENUM_BLUETOOTH_MUSICVOL] == 0)
				gBlueToothMusicBuff[ENUM_BLUETOOTH_MUSICVOL] = 18;	//Ĭ�����������30���ػ�������
			SetBlueToothSendCmd(BLUETOOTH_MUSIC_VOL);
		}
		
		gBlueToothMusicBuff[ENUM_BLUETOOTH_MUSICNUM] = MusicNumTemp;
		SetBlueToothSendCmd(BLUETOOTH_PLAY_MUSIC);

		gBlueToothMusicBuff[ENUM_BLUETOOTH_SOUNDSOURCE] = 2;	//��Դ�л�ΪSD��
		SetBlueToothSendCmd(BLUETOOTH_SOUNDSOURCE_SELECT);

		gBlueToothMusicBuff[ENUM_BLUETOOTH_MUSICMODE] = 1;		//����ѭ��
		SetBlueToothSendCmd(BLUETOOTH_MUSIC_MODE);
		BuzzerOn(OK);
	}
	else
	{
		gBlueToothMusicBuff[ENUM_BLUETOOTH_MUSICNUM] = 0;
		gBlueToothMusicBuff[ENUM_BLUETOOTH_SOUNDSOURCE] = 0;
		SetBlueToothSendCmd(BLUETOOTH_SOUNDSOURCE_SELECT);	//��Դ�л�Ϊ����
		BuzzerOn(OK);
	}	
}

void BlueToothMusicVolumeSetting(Uchar MusicVolume)
{
	if(gBlueToothMusicBuff[ENUM_BLUETOOTH_MUSICNUM] == 0)
		return;
	if(MusicVolume == 0)
		MusicVolume =1;
	gBlueToothMusicBuff[ENUM_BLUETOOTH_MUSICVOL] = MusicVolume;	
	SetBlueToothSendCmd(BLUETOOTH_MUSIC_VOL);
	BuzzerOn(OK);	
}

