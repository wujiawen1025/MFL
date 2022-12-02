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

#define CEN_BLUETOOTH_UART_PORT        BSP_UART_Port2                                         /*所用串口*/
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

/////////////////////////////键值定义(拥有附加值)//////////////////////////////////////////
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

////////////////////////////键值定义(无附加值，特殊处理)///////////////////////////////

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
	uint8_t        SysRun					:1;  /*系统开关机状态*/ 
	uint8_t        Pause                        		:1;  /*暂停状态*/ 

  }Byte4;

  struct
  {
  	uint8_t        FullBack            			:1;  /*全背*/  
  	uint8_t        Spot            				:1;  /*定点*/  
	uint8_t        Partial            				:1;  /*区间*/  
	uint8_t        MoveUp           				:1;  /*机芯上行标志*/  
	uint8_t        MoveDown           			:1;  /*机芯下行标志*/  
	uint8_t        BackScanning           		:1;  /*人体肩部检测中标志*/
	uint8_t	    BackHeightAdjust			:1;  /*人体肩部检测高度调节标志*/
	
  }Byte5;

  struct
  {
  	uint8_t        BackScanFinish			:1;  /*人体肩部检测完成标志*/
	uint8_t								:1;
	uint8_t        RollRun					:1;  /*推拿按键运行标志位*/ 
  	uint8_t        Knead1Run				:1;  /*揉捏1按键运行标志位*/ 
	uint8_t        Knead2Run                        	:1;  /*揉捏2按键运行标志位*/ 
	uint8_t        Swedish1Run                        :1;  /*瑞典1按键运行标志位*/ 
	uint8_t        Swedish2Run				:1;  /*瑞典2按键运行标志位*/ 
	uint8_t        Tap1Run					:1;  /*敲击1按键运行标志位*/ 
	
  }Byte6;
  
  struct
  {
	uint8_t        Tap2Run                        		:1;  /*敲击2按键运行标志位*/ 
	uint8_t        Shiatsu1Run					:1;  /*指压1按键运行标志位*/ 
	uint8_t        Shiatsu2Run                        	:1;  /*指压2按键运行标志位*/ 
	uint8_t        Clap1Run					:1;  /*拍打1按键运行标志位*/ 
	uint8_t        Clap2Run                       		:1;  /*拍打2按键运行标志位*/ 
  }Byte7;
  
   struct
  {
	uint8_t        RollState					:1;  /*推拿图标*/ 
  	uint8_t        Knead1State				:1;  /*揉捏1图标*/ 
	uint8_t        Knead2State                        	:1;  /*揉捏2图标*/ 
	uint8_t        Swedish1State                      :1;  /*瑞典1图标*/ 
	uint8_t        Swedish2State				:1;  /*瑞典2图标*/ 
	uint8_t        Tap1State					:1;  /*敲击1图标*/ 
	uint8_t        Tap2State                        	:1;  /*敲击2图标*/ 
	uint8_t        Shiatsu1State				:1;  /*指压1图标*/ 
  }Byte8;
   
  struct
  {
	uint8_t        Shiatsu2State                       :1;  /*指压2图标*/ 
	uint8_t        Clap1State				:1;  /*拍打1图标*/ 
	uint8_t        Clap2State                        	:1;  /*拍打2图标*/ 
       uint8_t        Width            				:3;  /*机芯宽度*/		
	
  }Byte9;

  struct
  {
	 uint8_t        Strength            			:3;  /*机芯揉捏力度*/ 
	
  }Byte10;

  struct
  {
  	uint8_t        Speed               			:3;  /*机芯敲击速度*/
	
  }Byte11;
  
  struct
  {
  	uint8_t        Intensity           			:3;  /*充气强度*/  
	
  }Byte12;

  struct
  {
  	uint8_t        Flex3D           				:3;  /*3D强度*/  
	
  }Byte13;

  struct
  {
  	uint8_t        BackPoint              			:4;  /*机芯点位*/  
	
  }Byte14;

  struct
  {
  	uint8_t       buff                         				:8;  
	
  }Byte15;

  struct
  {  
	uint8_t        FeetSpikeUpRun               	:1;  /*抬腿按键运行标志*/  
	uint8_t        FeetSpikeDownRun             	:1;  /*降腿按键运行标志*/ 
	uint8_t								:1;
	uint8_t								:1;
	uint8_t        BackSpikeDownRun             	:1;  /*倒背按键运行标志*/
	uint8_t        BackSpikeUpRun               	:1;  /*升背按键运行标志*/  

  }Byte16;
   
  struct
  {
  	uint8_t								:1;
  	uint8_t        ClavesGasStateFlag           	:1;  /*膝盖气袋 图标标志位*/  
	uint8_t        FeetGasStateFlag             	:1;  /*脚侧气袋 图标标志位*/  
	uint8_t        ShoulderGasStateFlag         	:1;  /*肩部气袋 图标标志位*/  
	uint8_t        Arms1GasStateFlag             	:1;  /*手部气袋 图标标志位*/  
	uint8_t        Arms2GasStateFlag             	:1;  /*手部气袋 图标标志位*/  
	uint8_t        LumbarGasStateFlag		:1;  /*腰部气袋 图标标志位*/  
	
  }Byte17;

   uint8_t Buff[2];											   
}CenToBlueToothAppStateData1_t;          

typedef struct
{
  struct
  {
	uint8_t        BackHeatState               	:1;  /*背部加热 图标状态*/
	uint8_t        ClavesHeatState               	:1;  /*腿部加热 图标状态*/
	uint8_t								:1;
	uint8_t								:1;
	uint8_t	    RollerState				:1; /*脚底滚轮图标状态*/

  }Byte4;

  struct
  {
  	uint8_t        HomeRun            			:1;  /*复位按键运行标志位*/  
  	uint8_t        ZeroGravity1Run			:1;  /*零重力1按键运行标志位*/  
	uint8_t        ZeroGravity2Run            	:1;  /*零重力2按键运行标志位*/  
	uint8_t        ZeroGravity3Run            	:1;  /*展开按键运行标志位*/
	
  }Byte5;

  uint8_t	AutoMassageNum_Byte6;
  
  struct
  {
	uint8_t       AutoMassageType                 :8;  
	
  }Byte7;
  
   struct
  {
  	uint8_t        ShoulderGasRun         		:1;  /*肩部气袋 按键运行标志位*/  
	uint8_t        ArmsGasRun             		:1;  /*手部气袋 按键运行标志位*/  
	uint8_t        							:1;  
	uint8_t        ClavesGasRun           		:1;  /*膝盖气袋 按键运行标志位*/  
	uint8_t        FeetGasRun             		:1;  /*脚侧气袋 按键运行标志位*/  
	uint8_t        							:1;
	uint8_t        							:1;
	uint8_t        AutoGasRun             		:1;  /* 全身充气按键运行标志位*/
	
  }Byte8;
   
  struct
  {
	uint8_t        BackHeatRun               		:1;  /*背部加热按键运行标志位*/
	uint8_t        ClavesHeatRun               	:1;  /*腿部加热按键运行标志位*/	
	uint8_t								:1;
	uint8_t								:1;
	uint8_t	    RollerRun					:1;  /*脚底滚轮按键运行标志位*/
	
  }Byte9;


  struct
  {
  	uint8_t       SoundPulseRun				:1;  /*音波律动按键运行标志位*/
	
  }Byte10;

  struct
  {
	uint8_t       BlueToothRun                         :1;  /*蓝牙开关按键运行标志位*/
	
  }Byte11;

union
{
	  struct
	  {
	  	uint8_t       PartMassageShoulder           :1; /*区域按摩:肩颈运行标志位*/
		uint8_t       PartMassageArm           		:1; /*区域按摩:肩颈运行标志位*/
		uint8_t       PartMassageButton          	:1; /*区域按摩:肩颈运行标志位*/
		uint8_t       PartMassageCalves         	:1; /*区域按摩:肩颈运行标志位*/
		uint8_t       PartMassageLumbar             :1; /*区域按摩:腰部按键运行标志位*/

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
	uint8_t        StartAcheScan             		:1;  /*酸痛按摩标志位*/
	uint8_t        AcheScanning             		:1;  /*酸痛检测中*/
	uint8_t        AcheScanFinish             	:1;  /*酸痛检测完成*/
	
  }Byte15;

  struct
  {  
	uint8_t         AcheShoulderNeckData              	:2;  /*颈肩酸痛程度*/  
	uint8_t         AcheBackData              			:2;  /*背部酸痛程度*/
	uint8_t         AcheLumbarButtoData              		:2;  /*腰臀酸痛程度*/
	
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
		uint8_t         ChairResetState              	:1;  /*椅子复位状态*/  
		uint8_t         ChildLockRun              		:1;  /*童锁状态*/
		
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

