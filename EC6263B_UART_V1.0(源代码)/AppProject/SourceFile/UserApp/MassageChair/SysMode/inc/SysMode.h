/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣ�SysMode.h 
**
**    ��������: ϵͳģʽ����
**
**    ��    ˾���ɷ�������
**
**    ��Ŀ���ƣ�
**
**    ƽ̨��Ϣ��
**
**    ��    �ߣ�Hzy
**
**    ����˵��:
**
**    �޸ļ�¼:  --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/
#ifndef  _SYSMODE_H
#define  _SYSMODE_H

/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "MChair.h"


/*
========================================================================================================================
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/
/*0~9 ����ģʽ*/
#define  SYS_MODE_NONE                               0
#define  SYS_MODE_STANDBY                            1       /*ϵͳģʽ������*/
#define  SYS_MODE_USERRUN                            2       /*ϵͳģʽ���û�����*/

/*10~19 ���Ҽ��*/
#define  SYS_MODE_INSPECTAUTO                        10      /*ϵͳģʽ�������Լ�*/
#define  SYS_MODE_INSPECTMANUAL                      11      /*ϵͳģʽ�������ּ�*/
#define  SYS_MODE_INSPECTOTHER1                      12      /*ϵͳģʽ���������Ҽ�� 1*/
#define  SYS_MODE_INSPECTOTHER2                      13      /*ϵͳģʽ���������Ҽ�� 2*/
#define  SYS_MODE_INSPECTOTHER3                      14      /*ϵͳģʽ���������Ҽ�� 3*/

/*20~29 ���ҿ���*/
#define  SYS_MODE_TESTNOTIMER                        20      /*ϵͳģʽ�����ҿ��� ֮ �޶�ʱ����ģʽ, ������������*/
#define  SYS_MODE_TESTSPIKE                          21      /*ϵͳģʽ�����ҿ��� ֮ �Ƹ�*/
#define  SYS_MODE_TESTAGE                            22      /*ϵͳģʽ�����ҿ��� ֮ ���� ��һСʱ��ͣ15����*/
#define  SYS_MODE_TESTOTHER1                         23      /*ϵͳģʽ�����ҿ��� ֮ �������� 1*/
#define  SYS_MODE_TESTOTHER2                         24      /*ϵͳģʽ�����ҿ��� ֮ �������� 2*/
#define  SYS_MODE_TESTOTHER3                         25      /*ϵͳģʽ�����ҿ��� ֮ �������� 3*/

/*30~39 ����ģʽ*/
#define  SYS_MODE_PACKING                            30      /*ϵͳģʽ�����Ұ�װ*/
#define  SYS_MODE_OTHER1                             31      /*ϵͳģʽ������1*/
#define  SYS_MODE_OTHER2                             32      /*ϵͳģʽ������2*/
#define  SYS_MODE_OTHER3                             33      /*ϵͳģʽ������3*/
#define  SYS_MODE_QUERY_CHAIR_INFO                   34      /*ϵͳģʽ����ѯ��Ħ����Ϣ��������汾�� ����Ϣ��*/


/*--------------------------------------------------------------------------------*/
#define  MASSAGETIME_MIN_DEFAULT                     15      /*�û���Ħʱ��Ĭ��ֵ ��*/
#define  MASSAGETIME_DELAYON_SEC                     3       /*�û���Ħʱ����ʱ����������*/


/*--------------------------------------------------------------------------------*/
#define  ON_OFF_KEY_VALID_LEVEL                      0       /*���ػ���������Ч��ƽ*/        


/*--------------------------------------------------------------------------------*/
#define  SYS_PROMPT_TONE_ADDR_DEFAULT                1       /*ϵͳĬ����ʾ����ַ*/



/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� :  ö�ټ�ֵ                                                                                
************************************************************************************************************************
*/
typedef enum
{
  /* ���ػ�����ͣ����ʱ�� �Ȼ�����ֵ-------------------*/
  KEYVAL_NoPress = 0,
  KEYVAL_Power,
  KEYVAL_Pause,
  KEYVAL_TimerAdd,
  KEYVAL_TimerDec,
  KEYVAL_Timer,
  KEYVAL_BodyCheckOk,                             /*���������ȷ��*/
  KEYVAL_BodyReCheck,                             /*���½���������*/

  KEYVAL_BluetoothSwitch = 11,
  
  /*�Ƹ����-------------------------------------------*/
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
  KEYVAL_SpikeHomeReset,                          /*�Ƹ˸�λ*/
  KEYVAL_SpikeULegExtend,
  KEYVAL_SpikeULegShorten,


  /*��о�ֶ� ���丨������  ��� -----------------------*/
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
  KEYVAL_CoreRoll,                                /*�ɼܹ���Ļ�о�ֶ��ַ�*/
  KEYVAL_CoreKnead,                
  KEYVAL_CoreTap,
  KEYVAL_CoreClap,
  KEYVAL_CoreShiatsu,
  KEYVAL_CoreMannualAction,
  KEYVAL_CoreMannualMode,
  KEYVAL_CoreMannualSpeed,

  KEYVAL_XYZAction = 68,                          /*��оXYZ����*/
  KEYVAL_TCSAction,                               /*��оTCS����*/


  /*���� �� ��������  ���-------------------------*/
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
  KEYVAL_GasPartSelcet,                           /*��ѹ��λѡ��*/
  KEYVAL_AutoQuickGas,


  /*���֡����� ���񶯡��� ������������� --------------*/
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


  /*�Զ�������� --------------------------------------*/
  KEYVAL_AutoQuick = 120,                         /*���ٰ�Ħ*/
  KEYVAL_AutoRelax,                               /*�滺����*/
  KEYVAL_AutoMoveSleep,                           /*ҡ������*/
  KEYVAL_AutoStretch,                             /*��չ����*/
  KEYVAL_AutoScraping,                            /*��������*/
  KEYVAL_AutoShiatsu,                             /*���ָѹ*/
  KEYVAL_AutoLady,                                /*Ůʿר��*/
  KEYVAL_AutoMan,                                 /*��ʿר��*/
  KEYVAL_AutoShoulderRelax,                       /*�������*/
  KEYVAL_AutoShoulderRecovery,                    /*����ƣ�ͻָ�*/
  KEYVAL_AutoShoulderTuina,                       /*��������*/
  KEYVAL_AutoShoulderShiatsu,                     /*�������ָѹ*/
  KEYVAL_AutoLumbarButtockRelax,                  /*���η���*/
  KEYVAL_AutoLumbarButtockRecovery,               /*����ƣ�ͻָ�*/
  KEYVAL_AutoLumbarButtockPress,                  /*���ξ��簴ѹ*/
  KEYVAL_AutoLumbarKidneyCare,                    /*��������*/

  KEYVAL_AutoGridCombo,                           /*��������ϡ�*/
  
  /*����ģʽ��� --------------------------------------*/
  /*��ƽ�������Ӧ�Ĺ���ģʽ���棬���·���Ӧ�ļ�ֵ*/
  /*����İ������ֿ���ʹ�ã������ֿ���ֻ�ܿ�����������������·���Ӧ�ļ�ֵ��
    ����֮ǰ����ϰ�����������(ֻ��2��3��)������ʹ�á�������İ������������
    �յ���ֵ0xEF������빤��ģʽѡ�񣬴�ѡ��ģʽ���ȴ�5s��5s����ͨ��������������ѡ����Ҫ�Ĺ���ģʽ�� 
    ����0xEF��ͨ�����ֿ�����0xE0��0xE1�ȵľɼ�ֵת������    */
  KEYVAL_InspectAuto = 0xE0,                      /*ϵͳģʽ�������Լ�*/
  KEYVAL_InspectManual,                           /*ϵͳģʽ�������ּ�*/
  KEYVAL_PackingAngle,                            /*ϵͳģʽ�����Ұ�װ*/
  KEYVAL_InspectOther1,                           /*ϵͳģʽ���������Ҽ��1*/
  KEYVAL_InspectOther2,                           /*ϵͳģʽ���������Ҽ��2*/
  KEYVAL_InspectOther3,                           /*ϵͳģʽ���������Ҽ��3*/
  KEYVAL_TestNoTimer,                             /*ϵͳģʽ�����ҿ��� ֮ �޶�ʱ����ģʽ*/
  KEYVAL_TestSpike,                               /*ϵͳģʽ�����ҿ��� ֮ �Ƹ�*/
  KEYVAL_TestAge,                                 /*ϵͳģʽ�����ҿ��� ֮ ���� ��һСʱ��ͣ15����*/
  KEYVAL_TestOther1,                              /*ϵͳģʽ���������ҿ���1*/
  KEYVAL_TestOther2,                              /*ϵͳģʽ���������ҿ���2*/
  KEYVAL_TestOther3,                              /*ϵͳģʽ���������ҿ���3*/
  KEYVAL_QueryChairInfo,                          /*��ѯ������Ϣ*/
  KEYVAL_Other1,                                  /*����1*/
  KEYVAL_Other2,                                  /*����2*/
  KEYVAL_EngiModeSelect = 0xEF,                   /*����ģʽѡ��*/

  /*---------------------------------------------------*/
  KEYVAL_MAX = 0xFF

}SysMode_KeyVal_t;


/*
************************************************************************************************************************
* ���Ͷ��� :  ϵͳģʽ������                                                                                   
************************************************************************************************************************
*/
typedef struct
{
  uint8_t Mode;
  void  (*pHandle)(void);

}SysModeHandleItem_t;


/*
************************************************************************************************************************
* ���Ͷ��� :  ���������߼�                                                                                   
************************************************************************************************************************
*/
typedef struct SysMode_KeyLogicTabItem
{
  SysMode_KeyVal_t    KeyValID;                          /*��ֵ*/

  uint8_t             AdditonOp;                         /*���Ӳ���*/

  uint8_t             (*pKeyValHandle)(uint8_t *pData);  /*��ֵ��Ӧ�Ĳ�������*/

}SysMode_KeyLogicTabItem_t; 


/*
========================================================================================================================
*������������                                          ������������                                          ������������
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
