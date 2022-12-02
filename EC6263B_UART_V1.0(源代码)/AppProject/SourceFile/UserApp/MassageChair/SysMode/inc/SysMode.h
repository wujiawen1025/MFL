/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：SysMode.h 
**
**    功能描述: 系统模式管理
**
**    公    司：蒙发利电子
**
**    项目名称：
**
**    平台信息：
**
**    作    者：Hzy
**
**    其他说明:
**
**    修改记录:  --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/
#ifndef  _SYSMODE_H
#define  _SYSMODE_H

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "MChair.h"


/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
/*0~9 常规模式*/
#define  SYS_MODE_NONE                               0
#define  SYS_MODE_STANDBY                            1       /*系统模式：待机*/
#define  SYS_MODE_USERRUN                            2       /*系统模式：用户运行*/

/*10~19 厂家检测*/
#define  SYS_MODE_INSPECTAUTO                        10      /*系统模式：厂家自检*/
#define  SYS_MODE_INSPECTMANUAL                      11      /*系统模式：厂家手检*/
#define  SYS_MODE_INSPECTOTHER1                      12      /*系统模式：其他厂家检测 1*/
#define  SYS_MODE_INSPECTOTHER2                      13      /*系统模式：其他厂家检测 2*/
#define  SYS_MODE_INSPECTOTHER3                      14      /*系统模式：其他厂家检测 3*/

/*20~29 厂家拷机*/
#define  SYS_MODE_TESTNOTIMER                        20      /*系统模式：厂家考机 之 无定时测试模式, 做温升拷机用*/
#define  SYS_MODE_TESTSPIKE                          21      /*系统模式：厂家考机 之 推杆*/
#define  SYS_MODE_TESTAGE                            22      /*系统模式：厂家考机 之 寿命 动一小时，停15分钟*/
#define  SYS_MODE_TESTOTHER1                         23      /*系统模式：厂家考机 之 其他拷机 1*/
#define  SYS_MODE_TESTOTHER2                         24      /*系统模式：厂家考机 之 其他拷机 2*/
#define  SYS_MODE_TESTOTHER3                         25      /*系统模式：厂家考机 之 其他拷机 3*/

/*30~39 其他模式*/
#define  SYS_MODE_PACKING                            30      /*系统模式：厂家包装*/
#define  SYS_MODE_OTHER1                             31      /*系统模式：其他1*/
#define  SYS_MODE_OTHER2                             32      /*系统模式：其他2*/
#define  SYS_MODE_OTHER3                             33      /*系统模式：其他3*/
#define  SYS_MODE_QUERY_CHAIR_INFO                   34      /*系统模式：查询按摩椅信息（如软件版本号 等信息）*/


/*--------------------------------------------------------------------------------*/
#define  MASSAGETIME_MIN_DEFAULT                     15      /*用户按摩时间默认值 分*/
#define  MASSAGETIME_DELAYON_SEC                     3       /*用户按摩时间延时启动的秒数*/


/*--------------------------------------------------------------------------------*/
#define  ON_OFF_KEY_VALID_LEVEL                      0       /*开关机按键的有效电平*/        


/*--------------------------------------------------------------------------------*/
#define  SYS_PROMPT_TONE_ADDR_DEFAULT                1       /*系统默认提示音地址*/



/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  枚举键值                                                                                
************************************************************************************************************************
*/
typedef enum
{
  /* 开关机、暂停、调时间 等基本键值-------------------*/
  KEYVAL_NoPress = 0,
  KEYVAL_Power,
  KEYVAL_Pause,
  KEYVAL_TimerAdd,
  KEYVAL_TimerDec,
  KEYVAL_Timer,
  KEYVAL_BodyCheckOk,                             /*人体检测完成确认*/
  KEYVAL_BodyReCheck,                             /*重新进行人体检测*/

  KEYVAL_BluetoothSwitch = 11,
  
  /*推杆相关-------------------------------------------*/
  KEYVAL_SpikeBackUp = 20,
  KEYVAL_SpikeBackDown,
  KEYVAL_SpikeFeetUp,
  KEYVAL_SpikeFeetDown,
  KEYVAL_SpikeBackUpFeetDown,
  KEYVAL_SpikeBackDownFeetUp,
  KEYVAL_SpikeLegExtend,
  KEYVAL_SpikeLegShorten,
  KEYVAL_SpikeZeroGravity1,
  KEYVAL_SpikeZeroGravity2,
  KEYVAL_SpikeZeroGravity,
  KEYVAL_SpikeHomeReset,                          /*推杆复位*/
  KEYVAL_SpikeULegExtend,
  KEYVAL_SpikeULegShorten,


  /*机芯手动 及其辅助变量  相关 -----------------------*/
  KEYVAL_CoreXYZSpeedAdd = 40,
  KEYVAL_CoreXYZSpeedDec,
  KEYVAL_CoreXYZSpeed,
  KEYVAL_CoreTCSSpeedAdd,
  KEYVAL_CoreTCSSpeedDec,
  KEYVAL_CoreTCSSpeed,
  KEYVAL_CoreWidthAdd,
  KEYVAL_CoreWidthDec,
  KEYVAL_CoreWidth,
  KEYVAL_CoreMannualUp,
  KEYVAL_CoreMannualDown,
  KEYVAL_CoreMannualFront,
  KEYVAL_CoreMannualBack,
  KEYVAL_CoreFlexLevel,
  KEYVAL_CoreSpot,
  KEYVAL_CorePart,
  KEYVAL_CoreWhole,
  KEYVAL_CoreSpotPartWhole,
  KEYVAL_CoreRoll,                                /*旧架构里的机芯手动手法*/
  KEYVAL_CoreKnead,                
  KEYVAL_CoreTap,
  KEYVAL_CoreClap,
  KEYVAL_CoreShiatsu,
  KEYVAL_CoreMannualAction,
  KEYVAL_CoreMannualMode,
  KEYVAL_CoreMannualSpeed,

  KEYVAL_XYZAction = 68,                          /*机芯XYZ动作*/
  KEYVAL_TCSAction,                               /*机芯TCS动作*/


  /*充气 及 辅助变量  相关-------------------------*/
  KEYVAL_GasIntensityAdd = 70,
  KEYVAL_GasIntensityDec,
  KEYVAL_GasIntensity,
  KEYVAL_GasHead,
  KEYVAL_GasShoulder,
  KEYVAL_GasArms,
  KEYVAL_GasLumbar,
  KEYVAL_GasSeat,
  KEYVAL_GasLumbarSeat,
  KEYVAL_GasCalves,
  KEYVAL_GasFeet,
  KEYVAL_GasCalvesFeet,
  KEYVAL_AutoFullGas,
  KEYVAL_GasPartSelcet,                           /*气压部位选择*/
  KEYVAL_AutoQuickGas,


  /*滚轮、加热 、振动、灯 等其他功能相关 --------------*/
  KEYVAL_VibLevelAdd = 90,
  KEYVAL_VibLevelDec,
  KEYVAL_VibLevel,
  KEYVAL_VibLumbarBack ,
  KEYVAL_VibSeat,
  KEYVAL_VibCalves,
  KEYVAL_VibFeet,

  KEYVAL_HeatLevelAdd = 100,
  KEYVAL_HeatLevelDec,
  KEYVAL_HeatLevel,
  KEYVAL_HeatLumbarBack,
  KEYVAL_HeatSeat,
  KEYVAL_HeatCalves,
  KEYVAL_HeatFeet,
  
  KEYVAL_RollerCalves = 110,
  KEYVAL_RollerFeet,
  
  KEYVAL_SleepLed = 115,


  /*自动程序相关 --------------------------------------*/
  KEYVAL_AutoQuick = 120,                         /*快速按摩*/
  KEYVAL_AutoRelax,                               /*舒缓放松*/
  KEYVAL_AutoMoveSleep,                           /*摇动舒眠*/
  KEYVAL_AutoStretch,                             /*伸展拉伸*/
  KEYVAL_AutoScraping,                            /*刮痧推拿*/
  KEYVAL_AutoShiatsu,                             /*深度指压*/
  KEYVAL_AutoLady,                                /*女士专属*/
  KEYVAL_AutoMan,                                 /*男士专属*/
  KEYVAL_AutoShoulderRelax,                       /*颈肩放松*/
  KEYVAL_AutoShoulderRecovery,                    /*颈肩疲劳恢复*/
  KEYVAL_AutoShoulderTuina,                       /*颈肩推拿*/
  KEYVAL_AutoShoulderShiatsu,                     /*颈肩深度指压*/
  KEYVAL_AutoLumbarButtockRelax,                  /*腰臀放松*/
  KEYVAL_AutoLumbarButtockRecovery,               /*腰臀疲劳恢复*/
  KEYVAL_AutoLumbarButtockPress,                  /*腰臀经络按压*/
  KEYVAL_AutoLumbarKidneyCare,                    /*腰肾保健*/

  KEYVAL_AutoGridCombo,                           /*【宫格组合】*/
  
  /*工程模式相关 --------------------------------------*/
  /*类平板可做相应的工程模式界面，和下发相应的键值*/
  /*常规的按键类手控器使用，此类手控器只能靠按键的组合来触发下发相应的键值。
    由于之前的组合按键数量有限(只有2到3个)，不够使用。因此中心板端重新做处理：
    收到键值0xEF，则进入工程模式选择，此选择模式将等待5s，5s内再通过单个按键触发选择需要的工程模式。 
    至于0xEF则通过对手控器的0xE0、0xE1等的旧键值转换得来    */
  KEYVAL_InspectAuto = 0xE0,                      /*系统模式：厂家自检*/
  KEYVAL_InspectManual,                           /*系统模式：厂家手检*/
  KEYVAL_PackingAngle,                            /*系统模式：厂家包装*/
  KEYVAL_InspectOther1,                           /*系统模式：其他厂家检测1*/
  KEYVAL_InspectOther2,                           /*系统模式：其他厂家检测2*/
  KEYVAL_InspectOther3,                           /*系统模式：其他厂家检测3*/
  KEYVAL_TestNoTimer,                             /*系统模式：厂家考机 之 无定时测试模式*/
  KEYVAL_TestSpike,                               /*系统模式：厂家考机 之 推杆*/
  KEYVAL_TestAge,                                 /*系统模式：厂家考机 之 寿命 动一小时，停15分钟*/
  KEYVAL_TestOther1,                              /*系统模式：其他厂家考机1*/
  KEYVAL_TestOther2,                              /*系统模式：其他厂家考机2*/
  KEYVAL_TestOther3,                              /*系统模式：其他厂家考机3*/
  KEYVAL_QueryChairInfo,                          /*查询椅子信息*/
  KEYVAL_Other1,                                  /*其他1*/
  KEYVAL_Other2,                                  /*其他2*/
  KEYVAL_EngiModeSelect = 0xEF,                   /*工程模式选择*/

  /*---------------------------------------------------*/
  KEYVAL_MAX = 0xFF

}SysMode_KeyVal_t;


/*
************************************************************************************************************************
* 类型定义 :  系统模式处理项                                                                                   
************************************************************************************************************************
*/
typedef struct
{
  uint8_t Mode;
  void  (*pHandle)(void);

}SysModeHandleItem_t;


/*
************************************************************************************************************************
* 类型定义 :  按键处理逻辑                                                                                   
************************************************************************************************************************
*/
typedef struct SysMode_KeyLogicTabItem
{
  SysMode_KeyVal_t    KeyValID;                          /*键值*/

  uint8_t             AdditonOp;                         /*附加操作*/

  uint8_t             (*pKeyValHandle)(uint8_t *pData);  /*键值对应的操作处理*/

}SysMode_KeyLogicTabItem_t; 


/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
void SysMode_DefaultKeyValHandle(void);
void SysMode_KeyValHandle(const SysMode_KeyLogicTabItem_t KeyLogicTab[], uint8_t KeyLogicTabNum, uint16_t (*pGetMatchID)(uint16_t index), uint8_t (*pAddOp)(uint8_t Index, uint8_t BeforeAfter));
void SysMode_Init(void);
void SysMode_Handle(void);

/*==================================================================*/
void SysMode_StandBy_EngiModeSelcetTLHandle(Ticker_t ExePeriod);
void SysMode_Standby_Init(void);
void SysMode_Standby_Handle(void);
uint8_t SysMode_Standby_Enter(uint8_t CurSysMode, uint8_t ResetSpikeAngle);

/*==================================================================*/
void SysMode_UserRun_Timer(Ticker_t ExePeriod);
void SysMode_UserRun_Init(void);
void SysMode_UserRun_Handle(void);
uint8_t SysMode_UserRun_Enter(void);

/*==================================================================*/
void SysMode_InspectAuto_Timer(Ticker_t ExePeriod);
void SysMode_InspectAuto_Init(void);
void SysMode_InspectAuto_Handle(void);

/*==================================================================*/
void SysMode_InspectManual_Timer(Ticker_t ExePeriod);
void SysMode_InspectManual_Init(void);
void SysMode_InspectManual_Handle(void);

/*==================================================================*/
void SysMode_TestSpike_Timer(Ticker_t ExePeriod);
void SysMode_TestSpike_Init(void);
void SysMode_TestSpike_Handle(void);

/*==================================================================*/
void SysMode_Packing_Handle(void);

/*==================================================================*/
void SysMode_InspectOther1_Timer(Ticker_t ExePeriod);
void SysMode_InspectOther1_Init(void);
void SysMode_InspectOther1_Handle(void);

/*==================================================================*/
void SysMode_InspectOther2_Timer(Ticker_t ExePeriod);
void SysMode_InspectOther2_Init(void);
void SysMode_InspectOther2_Handle(void);

/*==================================================================*/
void SysMode_TestOther1_Timer(Ticker_t ExePeriod);
void SysMode_TestOther1_Init(void);
void SysMode_TestOther1_Handle(void);

#endif
