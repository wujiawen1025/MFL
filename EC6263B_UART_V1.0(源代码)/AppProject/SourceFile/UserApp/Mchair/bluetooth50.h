/*
*********************************************
* File Name		: bluetooth50.c                                                                                                   
* Description 	: BlueTooth5.0 Program                                                                         
* Author 		: Faceless  
* Date			: 2021/5/14
*********************************************
*/
#ifndef	_BLUETOOTH5P0_h_
#define	_BLUETOOTH5P0_h_
#include "config.h"

#define CEN_BLUETOOTH_UART_PORT        BSP_UART_Port2                                         /*���ô���*/
#define BlueToothUse					  	0xc1

#define BLUETOOTH_A2DP_CONNECTED_STATE			1
#define BLUETOOTH_BLE_CONNECTED_STATE			2
#define BLUETOOTH_BLE_SWITCH_STATE				3
#define BLUETOOTH_SWITCH_STATE					4

#define BLUETOOTH_ON								7
#define BLUETOOTH_OFF								8
#define BLUETOOTH_INQUIRE_STATE					9
#define BLUETOOTH_BLE_OPEN						10
#define BLUETOOTH_BLE_CLOSE						11
#define BLUETOOTH_CONNECTED_STATE				12
#define BLUETOOTH_CONNECTED_LASTDEV				16

#define BLUETOOTH_SOUNDSOURCE_SELECT			17
#define BLUETOOTH_PLAY_MUSIC						18
#define BLUETOOTH_MUSIC_MODE						19
#define BLUETOOTH_MUSIC_VOL						20
#define BLUETOOTH_FUN_OFF							21

#define BLUETOOTH_CONNECTED_INIT		'0'
#define BLUETOOTH_CONNECTED_WAIT		'1'
#define BLUETOOTH_CONNECTED_BACK		'2'
#define BLUETOOTH_CONNECTED_ALREADY		'3'
#define BLUETOOTH_CONNECTED_TELEPHONE	'4'
#define BLUETOOTH_CONNECTED_MUSIC		'5'

#define BLUETOOTH_LOSELINK_TIME			10
#define CEN_TO_BLUETOOTH_TX_SIZE		30
#define CEN_TO_BLUETOOTH_RX_SIZE		30

/////////////////////////////��ֵ����(ӵ�и���ֵ)//////////////////////////////////////////
#define BlueTooth_SetTimer_KeyVal				3

#define BlueTooth_AutoMassage_KeyVal			8
#define BlueTooth_PartMassage_KeyVal			9
#define BlueTooth_Intelligent_KeyVal				10

#define BlueTooth_SetStrength_KeyVal				31
#define BlueTooth_SetSpeed_KeyVal				32
#define BlueTooth_SetIntensity_KeyVal			33
#define BlueTooth_SetCoreFlex_KeyVal			34

#define BlueTooth_SetCoreWidth_KeyVal			55

#define BlueTooth_ManualUpDown_KeyVal			59

////////////////////////////��ֵ����(�޸���ֵ�����⴦��)///////////////////////////////

//#define BlueTooth_PartShoulderMassage_KeyVal 	20	
//#define BlueTooth_PartArmMassage_KeyVal 		22	
//#define BlueTooth_PartLumbarMassage_KeyVal 	23	
//#define BlueTooth_PartButtonMassage_KeyVal 		24	
//#define BlueTooth_PartCalvesMassage_KeyVal 		25	

/////////////////////////////////////////////////////////////////////////////////////////////////////
enum
{
	ENUM_BLUETOOTH_SOUNDSOURCE = 0,
	ENUM_BLUETOOTH_MUSICNUM,
	ENUM_BLUETOOTH_MUSICMODE,
	ENUM_BLUETOOTH_MUSICVOL,
};


typedef struct
{
  struct
  {
	uint8_t        SysRun					:1;  /*ϵͳ���ػ�״̬*/ 
	uint8_t        Pause                        		:1;  /*��ͣ״̬*/ 

  }Byte4;

  struct
  {
  	uint8_t        FullBack            			:1;  /*ȫ��*/  
  	uint8_t        Spot            				:1;  /*����*/  
	uint8_t        Partial            				:1;  /*����*/  
	uint8_t        MoveUp           				:1;  /*��о���б�־*/  
	uint8_t        MoveDown           			:1;  /*��о���б�־*/  
	uint8_t        BackScanning           		:1;  /*����粿����б�־*/
	uint8_t	    BackHeightAdjust			:1;  /*����粿���߶ȵ��ڱ�־*/
	
  }Byte5;

  struct
  {
  	uint8_t        BackScanFinish			:1;  /*����粿�����ɱ�־*/
	uint8_t								:1;
	uint8_t        RollRun					:1;  /*���ð������б�־λ*/ 
  	uint8_t        Knead1Run				:1;  /*����1�������б�־λ*/ 
	uint8_t        Knead2Run                        	:1;  /*����2�������б�־λ*/ 
	uint8_t        Swedish1Run                        :1;  /*���1�������б�־λ*/ 
	uint8_t        Swedish2Run				:1;  /*���2�������б�־λ*/ 
	uint8_t        Tap1Run					:1;  /*�û�1�������б�־λ*/ 
	
  }Byte6;
  
  struct
  {
	uint8_t        Tap2Run                        		:1;  /*�û�2�������б�־λ*/ 
	uint8_t        Shiatsu1Run					:1;  /*ָѹ1�������б�־λ*/ 
	uint8_t        Shiatsu2Run                        	:1;  /*ָѹ2�������б�־λ*/ 
	uint8_t        Clap1Run					:1;  /*�Ĵ�1�������б�־λ*/ 
	uint8_t        Clap2Run                       		:1;  /*�Ĵ�2�������б�־λ*/ 
  }Byte7;
  
   struct
  {
	uint8_t        RollState					:1;  /*����ͼ��*/ 
  	uint8_t        Knead1State				:1;  /*����1ͼ��*/ 
	uint8_t        Knead2State                        	:1;  /*����2ͼ��*/ 
	uint8_t        Swedish1State                      :1;  /*���1ͼ��*/ 
	uint8_t        Swedish2State				:1;  /*���2ͼ��*/ 
	uint8_t        Tap1State					:1;  /*�û�1ͼ��*/ 
	uint8_t        Tap2State                        	:1;  /*�û�2ͼ��*/ 
	uint8_t        Shiatsu1State				:1;  /*ָѹ1ͼ��*/ 
  }Byte8;
   
  struct
  {
	uint8_t        Shiatsu2State                       :1;  /*ָѹ2ͼ��*/ 
	uint8_t        Clap1State				:1;  /*�Ĵ�1ͼ��*/ 
	uint8_t        Clap2State                        	:1;  /*�Ĵ�2ͼ��*/ 
       uint8_t        Width            				:3;  /*��о���*/		
	
  }Byte9;

  struct
  {
	 uint8_t        Strength            			:3;  /*��о��������*/ 
	
  }Byte10;

  struct
  {
  	uint8_t        Speed               			:3;  /*��о�û��ٶ�*/
	
  }Byte11;
  
  struct
  {
  	uint8_t        Intensity           			:3;  /*����ǿ��*/  
	
  }Byte12;

  struct
  {
  	uint8_t        Flex3D           				:3;  /*3Dǿ��*/  
	
  }Byte13;

  struct
  {
  	uint8_t        BackPoint              			:4;  /*��о��λ*/  
	
  }Byte14;

  struct
  {
  	uint8_t       buff                         				:8;  
	
  }Byte15;

  struct
  {  
	uint8_t        FeetSpikeUpRun               	:1;  /*̧�Ȱ������б�־*/  
	uint8_t        FeetSpikeDownRun             	:1;  /*���Ȱ������б�־*/ 
	uint8_t								:1;
	uint8_t								:1;
	uint8_t        BackSpikeDownRun             	:1;  /*�����������б�־*/
	uint8_t        BackSpikeUpRun               	:1;  /*�����������б�־*/  

  }Byte16;
   
  struct
  {
  	uint8_t								:1;
  	uint8_t        ClavesGasStateFlag           	:1;  /*ϥ������ ͼ���־λ*/  
	uint8_t        FeetGasStateFlag             	:1;  /*�Ų����� ͼ���־λ*/  
	uint8_t        ShoulderGasStateFlag         	:1;  /*�粿���� ͼ���־λ*/  
	uint8_t        Arms1GasStateFlag             	:1;  /*�ֲ����� ͼ���־λ*/  
	uint8_t        Arms2GasStateFlag             	:1;  /*�ֲ����� ͼ���־λ*/  
	uint8_t        LumbarGasStateFlag		:1;  /*�������� ͼ���־λ*/  
	
  }Byte17;

   uint8_t Buff[2];											   
}CenToBlueToothAppStateData1_t;          

typedef struct
{
  struct
  {
	uint8_t        BackHeatState               	:1;  /*�������� ͼ��״̬*/
	uint8_t        ClavesHeatState               	:1;  /*�Ȳ����� ͼ��״̬*/
	uint8_t								:1;
	uint8_t								:1;
	uint8_t	    RollerState				:1; /*�ŵ׹���ͼ��״̬*/

  }Byte4;

  struct
  {
  	uint8_t        HomeRun            			:1;  /*��λ�������б�־λ*/  
  	uint8_t        ZeroGravity1Run			:1;  /*������1�������б�־λ*/  
	uint8_t        ZeroGravity2Run            	:1;  /*������2�������б�־λ*/  
	uint8_t        ZeroGravity3Run            	:1;  /*չ���������б�־λ*/
	
  }Byte5;

  uint8_t	AutoMassageNum_Byte6;
  
  struct
  {
	uint8_t       AutoMassageType                 :8;  
	
  }Byte7;
  
   struct
  {
  	uint8_t        ShoulderGasRun         		:1;  /*�粿���� �������б�־λ*/  
	uint8_t        ArmsGasRun             		:1;  /*�ֲ����� �������б�־λ*/  
	uint8_t        							:1;  
	uint8_t        ClavesGasRun           		:1;  /*ϥ������ �������б�־λ*/  
	uint8_t        FeetGasRun             		:1;  /*�Ų����� �������б�־λ*/  
	uint8_t        							:1;
	uint8_t        							:1;
	uint8_t        AutoGasRun             		:1;  /* ȫ������������б�־λ*/
	
  }Byte8;
   
  struct
  {
	uint8_t        BackHeatRun               		:1;  /*�������Ȱ������б�־λ*/
	uint8_t        ClavesHeatRun               	:1;  /*�Ȳ����Ȱ������б�־λ*/	
	uint8_t								:1;
	uint8_t								:1;
	uint8_t	    RollerRun					:1;  /*�ŵ׹��ְ������б�־λ*/
	
  }Byte9;


  struct
  {
  	uint8_t       SoundPulseRun				:1;  /*�����ɶ��������б�־λ*/
	
  }Byte10;

  struct
  {
	uint8_t       BlueToothRun                         :1;  /*�������ذ������б�־λ*/
	
  }Byte11;

union
{
	  struct
	  {
	  	uint8_t       PartMassageShoulder           :1; /*����Ħ:�羱���б�־λ*/
		uint8_t       PartMassageArm           		:1; /*����Ħ:�羱���б�־λ*/
		uint8_t       PartMassageButton          	:1; /*����Ħ:�羱���б�־λ*/
		uint8_t       PartMassageCalves         	:1; /*����Ħ:�羱���б�־λ*/
		uint8_t       PartMassageLumbar             :1; /*����Ħ:�����������б�־λ*/

	  }Bit;
	  uint8_t All;
  }Byte12;
 
  union
  {
  	struct
	{
	  	uint8_t       DIYKeyState1                         :1; 
		uint8_t       DIYKeyState2                         :1;
		uint8_t       DIYKeyState3                         :1;
	 }Bit;
	  uint8_t All;
  }Byte13;

  struct
  {
  	uint8_t       DIYRunTime                         	:6;  
	
  }Byte14;

  struct
  {
  	uint8_t                                				:5;  
	uint8_t        StartAcheScan             		:1;  /*��ʹ��Ħ��־λ*/
	uint8_t        AcheScanning             		:1;  /*��ʹ�����*/
	uint8_t        AcheScanFinish             	:1;  /*��ʹ������*/
	
  }Byte15;

  struct
  {  
	uint8_t         AcheShoulderNeckData              	:2;  /*������ʹ�̶�*/  
	uint8_t         AcheBackData              			:2;  /*������ʹ�̶�*/
	uint8_t         AcheLumbarButtoData              		:2;  /*������ʹ�̶�*/
	
  }Byte16;
   
  struct
  {
  	uint8_t        buff               :8;  
	
  }Byte17;

	uint8_t	    MassageRunTimeMin_Byte18;
	uint8_t	    MassageRunTimeSec_Byte19;
}CenToBlueToothAppStateData2_t;

typedef struct
{
	uint8_t ChairIDCode[4];
	struct
	{  
		uint8_t         ChairResetState              	:1;  /*���Ӹ�λ״̬*/  
		uint8_t         ChildLockRun              		:1;  /*ͯ��״̬*/
		
	}Byte5;
}CenToBlueToothAppStateData3_t;

extern Uchar gBlueToothMusicBuff[];

void 	BlueTooth25Ms_Handle(void);
void 	SetBlueToothSendCmd(uint8_t mCmd);
void	BlueToothValue1MsProcess(void);
void	CDP_CenBlueTooth_ByteRx(uint8_t RxByte);
void	SendDataToBlueTooth(uint8_t cmd);
void	ReceiveDataFromBlueTooth(void);
//uint8_t GetBlueToothLoseLinkState(void);
//uint8_t GetBlueToothState(void);
void 	BlueTooth1S_Handle(void);
uint8_t GetBlueToothSendCmdState(uint8_t mState);
uint8_t GetBlueToothAPPLoseLinkState(void);
uint8_t	GetAutoProcessFunNum(void);
Uchar GetAutoMassageType(void);
void BlueToothMusicSetting(Uchar MusicNum);
void BlueToothMusicVolumeSetting(Uchar MusicVolume);
#endif

