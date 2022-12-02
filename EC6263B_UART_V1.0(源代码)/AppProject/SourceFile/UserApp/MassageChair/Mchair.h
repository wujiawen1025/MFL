/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: MChair.h
**
**    ��������: ��Ħ����߲���ļ�
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
#ifndef  _MCHAIR_H
#define  _MCHAIR_H


/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "bsp.h"
#include "ESF.h"

#include "Core.h"
#include "Spike.h"
#include "Gas.h"
#include "Roller.h"
#include "Heat.h"
#include "Vib.h"
#include "LED.h"
#include "SaveData.h"
#include "RealTimeInspect.h"
#include "CDP.h"

#include "BodyScan.h"
#include "FuncLogic.h"
#include "SysMode.h"


/*
========================================================================================================================
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/


/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� : ��Ħ�� ��ֵ�������                                                                                         
************************************************************************************************************************
*/
typedef struct SysMode_KeyLogicTabItem  SysMode_KeyLogicTabItem_t;

typedef  struct 
{
  const SysMode_KeyLogicTabItem_t  *KeyLogicTab;                                /*�����߼���*/
  uint8_t   KeyLogicTabNum;                                                     /*�����߼��� ��С*/
  uint16_t (*pGetMatchID)(uint16_t index);                                      /*����ָ�룬ָ��ĺ������ã����ر����Ŀ �� ��Ҫ���������� ���ڵ�����*/
  uint8_t  (*pAddOp)(uint8_t Index, uint8_t BeforeAfter, uint8_t CurExeState);  /*����ָ�룬ָ��ĺ������ã���ִֵ��ǰ��ĸ��Ӳ��� */

  uint8_t  CtrlBuf[2];                                                          /*�ֿ����ļ�ֵ*/
  uint8_t  SideCtrlBuf[2];                                                      /*���ļ�ֵ*/
  uint8_t  AppBuf[2];                                                           /*App�ļ�ֵ*/
  uint8_t  AppTimeOut;                                                          /*App�ļ�ֵ��ʱ*/

}MChairKeyValHandle_t;  


/*
************************************************************************************************************************
* ���Ͷ��� : ��Ħ�� ����״̬                                                                                         
************************************************************************************************************************
*/
typedef  struct 
{
  union 
  {
    struct
    {
      /*Ϊ�������ʱ���鿴�����룬���Ӵ˽ṹλ���壬λ���Ƶ����ּ����������*/
      uint8_t    F01                   :1;    
      uint8_t    F02                   :1;    
      uint8_t    F03                   :1;    
      uint8_t    F04                   :1;    
      uint8_t    F05                   :1;    
      uint8_t    F06                   :1;    
      uint8_t    F07                   :1; 
      uint8_t    F08                   :1;    
      uint8_t    F09                   :1;  
      uint8_t    F10                   :1;    
      uint8_t    F11                   :1;    
      uint8_t    F12                   :1;    
      uint8_t    F13                   :1;    
      uint8_t    F14                   :1;    
      uint8_t    F15                   :1; 
      uint8_t    F16                   :1;    
      uint8_t    F17                   :1;    
      uint8_t    F18                   :1;    
      uint8_t    F19                   :1;    
      uint8_t    F20                   :1;    
      uint8_t    F21                   :1;    
      uint8_t    F22                   :1;    
      uint8_t    F23                   :1;    
      uint8_t    F24                   :1;    
      uint8_t    F25                   :1; 
      uint8_t    F26                   :1;    
      uint8_t    F27                   :1;    
      uint8_t    F28                   :1;    
      uint8_t    F29                   :1;    
      uint8_t    F30                   :1;    
      uint8_t    F31                   :1;    
      uint8_t    F32                   :1;    
      uint8_t    F33                   :1;    
      uint8_t    F34                   :1;    
      uint8_t    F35                   :1; 
      uint8_t    F36                   :1;    
      uint8_t    F37                   :1;    
      uint8_t    F38                   :1;    
      uint8_t    F39                   :1;    
      uint8_t    F40                   :1;    
      uint8_t    F41                   :1;    
      uint8_t    F42                   :1;    
      uint8_t    F43                   :1;    
      uint8_t    F44                   :1;    
      uint8_t    F45                   :1; 
      uint8_t    F46                   :1;    
      uint8_t    F47                   :1;    
      uint8_t    F48                   :1;    
      uint8_t    F49                   :1;    
      uint8_t    F50                   :1;    
      uint8_t    F51                   :1;    
      uint8_t    F52                   :1;    
      uint8_t    F53                   :1;    
      uint8_t    F54                   :1;    
      uint8_t    F55                   :1; 
      uint8_t    F56                   :1;    
      uint8_t    F57                   :1;    
      uint8_t    F58                   :1;    
      uint8_t    F59                   :1;    
      uint8_t    F60                   :1;    
      uint8_t    F61                   :1;    
      uint8_t    F62                   :1;    
      uint8_t    F63                   :1;    
      uint8_t    F64                   :1;    
      uint8_t    F65                   :1; 
      uint8_t    F66                   :1;    
      uint8_t    F67                   :1;    
      uint8_t    F68                   :1;    
      uint8_t    F69                   :1;    
      uint8_t    F70                   :1;    
      uint8_t    F71                   :1;    
      uint8_t    F72                   :1;    
      uint8_t    F73                   :1;    
      uint8_t    F74                   :1;    
      uint8_t    F75                   :1; 
      uint8_t    F76                   :1;    
      uint8_t    F77                   :1;    
      uint8_t    F78                   :1;    
      uint8_t    F79                   :1;    
      uint8_t    F80                   :1;    
    }Bit;

    uint8_t      All[10];
  }ReportFlag;                     /*�ϱ���ʶ*/

  uint8_t   DisplayFaultID;        /*Ҫ��ʾ�Ĺ���ID*/
  uint16_t  DisplayTLMsPerFault;   /*ÿ��������ʾ��ʱ�䳤��*/
 
  uint16_t  ReportTLMs;            /*����ʱ������λMS*/

}MChairFault_t;  


/*
************************************************************************************************************************
* ���Ͷ��� :  ��Ħ�� ���Ҽ��                                                                                        
************************************************************************************************************************
*/
typedef struct
{
  uint8_t                  CoreKneadStep;                        /*��о�����ⲽ��*/
  uint8_t                  CoreRollStep;                         /*��о����(����)��ⲽ��*/
  uint8_t                  CoreFlexStep;                         /*��о������ⲽ��*/
  uint8_t                  BackSpikeStep;                        /*�����Ƹ˼�ⲽ��*/
  uint8_t                  FeetSpikeStep;                        /*С���Ƹ˼�ⲽ��*/
  uint8_t                  ZeroSpikeStep;                        /*�������Ƹ˼�ⲽ��*/

  uint16_t                 CoreKneadTimeMs;                      /*��о������ʱ��*/
  uint16_t                 CoreRollTimeMs;                       /*��о����(����)���ʱ��*/
  uint16_t                 CoreFlexTimeMs;                       /*��о�������ʱ��*/
  uint16_t                 BackSpikeTimeMs;                      /*�����Ƹ˼��ʱ��*/
  uint16_t                 FeetSpikeTimeMs;                      /*С���Ƹ˼��ʱ��*/
  uint16_t                 ZeroSpikeTimeMs;                      /*�������Ƹ˼��ʱ��*/

  union
  {
    struct
    {
      uint8_t    XPositionSensorFault          :1;    /*X λ�ô���������*/   
      uint8_t    YPositionSensorFault          :1;    /*Y λ�ô���������*/    
      uint8_t    ZPositionSensorFault          :1;    /*Z λ�ô���������*/    
      uint8_t    BackPositionSensorFault       :1;    /*���� λ�ô���������*/    
      uint8_t    FeetPositionSensorFault       :1;    /*С�� λ�ô���������*/    
      uint8_t    ZeroPositionSensorFault       :1;    /*������ λ�ô���������*/  
    }Bit;

    uint16_t All;
    
  }Result; /*�����*/

}MChairVenderInspect_t; 


/*
************************************************************************************************************************
* ���Ͷ��� : ��Ħ�� ������״̬��ʶ                                                                                         
************************************************************************************************************************
*/
typedef  union 
{
  uint32_t All;

  struct
  {
    uint8_t    SysRun                            :1;    /*ϵͳ���У����Ǵ���ģʽ*/
    uint8_t    Pause                             :1;    /*��ͣ*/

    uint8_t    ZeroGravityAngleRun               :1;    /*�������ڽǶ���*/

    uint8_t    BackSpikeMannualMoveDisable       :1;    /*�����Ƹ��ֶ���Ч*/
    uint8_t    ZeroSpikeMannualMoveDisable       :1;    /*�������Ƹ��ֶ���Ч*/
    uint8_t    FeetSpikeMannualMoveDisable       :1;    /*С���Ƹ��ֶ���Ч*/
    uint8_t    LegFlexMannualMoveDisable         :1;    /*С�������ֶ���Ч*/
    uint8_t    ULegFlexMannualMoveDisable        :1;    /*��С�������ֶ���Ч*/

    uint8_t    FeetHeatMannualOpDisable          :1;    /*�Ų������ֶ���Ч*/
    uint8_t    CalvesHeatMannualOpDisable        :1;    /*�Ȳ������ֶ���Ч*/
    uint8_t    SeatHeatMannualOpDisable          :1;    /*���������ֶ���Ч*/
    uint8_t    LumbarBackHeatMannualOpDisable    :1;    /*���������ֶ���Ч*/

    uint8_t    GasCooperateSpikeRun              :1;    /*��������Ƹ� ����*/

    uint8_t    UserMassageTimeOut                :1;    /*�û���Ħʱ�� ��ʱ*/
    uint8_t    UserMassageTimeRun                :1;    /*�û���Ħʱ�� ����*/

    uint8_t    KeyValExeResult                   :1;    /*��ִֵ�н��*/

    uint8_t    IDCodeOpRun                       :1;    /*ID����ز���ִ����*/

    uint8_t    OccurNoStartUpFault               :1;    /*�������������� �Ĺ���*/

    uint8_t    UserSpikeAngleSetd                :1;    /*�û��������һ��ִ���κΰ�Ħ����ʱ��Ҫ�ȵ����̶��Ƕ�*/

    uint8_t    VenderOpFinish                    :1;    /*���Ҳ�������*/
    
    uint8_t    BluetoothSwitch                   :1;    /*��������*/

    uint8_t    SpikeHomeResetRun                 :1;    /*�Ƹ˳�ʼ�Ƕȸ�λ*/

    uint8_t    TabTryRun                         :1;    /*����������� ���б�ʶ*/
    
    uint8_t    FuncExeAngleNeedSet               :1;    /*����ִ�нǶ���Ҫ����*/

    uint8_t    LegFlexTestSw                     :1;    /*С�������������Կ���*/
    
    uint8_t    MChairReported                    :1;    /*״̬�ϱ���־λ*/
  }Bit;

}MChairCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/


/*
************************************************************************************************************************
* ���Ͷ��� : ��Ħ�β�������״̬                                                                                         
************************************************************************************************************************
*/
typedef  union 
{
  uint32_t All;
  struct
  {
    /*#define  FUNC_TYPE_NONE           0     �������� ��
      #define  FUNC_TYPE_MANNUAL        1     �������� �ֶ�
      #define  FUNC_TYPE_AUTO           2     �������� �Զ�
      #define  FUNC_TYPE_MANNUALAUTO    3     �������� �ֶ��Զ�*/

    uint8_t    Core              :2;    /*��о ����״̬*/
    uint8_t    Gas               :2;    /*���� ����״̬*/
    uint8_t    Spike             :2;    /*�Ƹ� ����״̬*/
    
    uint8_t    FeetRoller        :2;    /*�Ź� ����״̬*/
    uint8_t    CalvesRoller      :2;    /*�Ź� ����״̬*/
    
    uint8_t    LumbarBackVib     :2;    /*������ ����״̬*/
    uint8_t    SeatVib           :2;    /*����   ����״̬*/
    uint8_t    CalvesVib         :2;    /*����   ����״̬*/
    uint8_t    FeetVib           :2;    /*����   ����״̬*/
    
    uint8_t    LumbarBackHeat    :2;    /*������ ����״̬*/
    uint8_t    SeatHeat          :2;    /*����   ����״̬*/
    uint8_t    CalvesHeat        :2;    /*����   ����״̬*/
    uint8_t    FeetHeat          :2;    /*����   ����״̬*/
    
    uint8_t    Led               :2;    /*�ƹ� ����״̬*/
  }Bit;

}ComponentFuncState_t; 


/*
************************************************************************************************************************
* ���Ͷ��� : ��Ħ�� ��ز������ݽṹ
*            ��Ħ�� ��߲�� �ṹ�壬 �ں�������Ħ�ι��ɲ���                                                                                         
************************************************************************************************************************
*/
typedef struct
{
  MChairCSFlag_t             CSFlag;                               /*������״̬��ʶ*/

  uint8_t                    PromptToneAddr;                       /*��ʾ����ַ*/
  uint16_t                   PromptToneTLMs;                       /*��ʾ��ʱ��*/
  uint16_t                   LcdBackLightTLMs;                     /*Lcd����ʱ��*/

  MChairKeyValHandle_t       KeyValHandle;                         /*��ֵ����*/

  /*ϵͳģʽ���-----------------------------------------------------------------------------------*/
  /*ע��������ƽ�忿���İ幩�磬ERP�رպ���ƽ����޷������ˡ�
        ����޷��ڴ���ģʽ�²�����ƽ����볧��ģʽ��ֻ���ڿ����������ƽ����볧��ģʽ��
        ����SysModeVender�����������¼Ҫ����ĳ���ģʽ������״̬�£�������Ӧ�ĳ���ģʽ������
        ���Ƚ������ģʽ��Ȼ�����ģʽ�Ĵ��뽫����SysModeVender������ֵ����ת�뵽��Ӧ�ĳ���ģʽ��*/
  uint8_t                    SysModeVender;                        /*ϵͳģʽ ����*/

  uint8_t                    SysModeHis;                           /*ϵͳģʽ ��ǰ*/
  uint8_t                    SysModeCur;                           /*ϵͳģʽ ��ʷ*/

  uint8_t                    UserMassageTimeMin;                   /*�û���Ħʱ�� ��*/
  uint8_t                    UserMassageTimeSec;                   /*�û���Ħʱ�� ��*/
  uint8_t                    UserMassageTimeDelayOnSec;            /*�û���Ħʱ����ʱ����������*/

  uint8_t                    UserMassageIdleTimeSec;               /*�û���Ħ����ʱ�� �룬�����κΰ�Ħ����*/

  uint8_t                    ERPPowerSw;                           /*ERP��Դ����*/
  uint16_t                   ERPPowerOffWaitTimeMs;                /*ERP��Դ�ر�ǰ�ĵȴ�ʱ��*/
  uint16_t                   ERPPowerOnTimeMs;                     /*ERP��Դ�����˶೤ʱ��*/

  uint16_t                   CommonStep;                           /*����ģʽ������Ҫ����ʹ�õĲ���*/
  uint16_t                   CommonTimeSec;                        /*����ģʽ������Ҫ����ʹ�õ�ʱ�䣬��λ��*/
  uint16_t                   CommonTimeSec1;                       /*����ģʽ������Ҫ����ʹ�õ�ʱ�䣬��λ��*/

  MChairVenderInspect_t      VenderInspect;                        /*���Ҽ��*/


  /*��Ħ��ع��� ���丨������------------------------------------------------------------------------
   * FuncMannual���ֶ�     FuncAuto���Զ�     FuncMA���ֶ� �� �Զ�  */
  ComponentFuncState_t       ComponentFuncState;                   /*��������״̬*/

  uint16_t                   FuncHis[18];                          /*��¼��ʷ����*/

  RollerAction_t             FuncMA_Roller;                        /*�����֡��ֶ� �� �Զ�*/
  HeatAction_t               FuncMA_Heat;                          /*�����ȡ��ֶ� �� �Զ�*/
  VibAction_t                FuncMA_Vib;                           /*���񶯡��ֶ� �� �Զ�*/
  LedAction_t                FuncMA_Led;                           /*���ƹ⡿�ֶ� �� �Զ�*/
  CoreAction_t               FuncMannual_Core;                     /*����о���ֶ�*/
  GasAction_t                FuncMannual_Gas;                      /*���������ֶ�*/
  SpikeAction_t              FuncMannual_Spike;                    /*���Ƹˡ��ֶ�*/
  uint16_t                   FuncAuto_Core;                        /*����о���Զ�*/
  uint16_t                   FuncAuto_Gas;                         /*���������Զ�*/
  uint16_t                   FuncAuto_Spike;                       /*���Ƹˡ��Զ�*/
  uint16_t                   FuncAuto_CoreGas;                     /*����о+�������Զ�*/
  uint16_t                   FuncAuto_CoreSpike;                   /*����о+�Ƹˡ��Զ�*/
  uint16_t                   FuncAuto_GasSpike;                    /*������+�Ƹˡ��Զ�*/
  uint16_t                   FuncAuto_CoreGasSpike;                /*����о+����+�Ƹˡ��Զ�*/
  uint16_t                   FuncAuto_GridCombo;                   /*��������ϡ��Զ�*/

  /*ע���ֶ������£���о��ʵ���ٶ� = �ֶ��µ������ٶ�*/
  uint8_t                    GasIntensity;                         /*����ǿ��*/
  uint8_t                    AutoCoreFlexLevelAdjust;              /*�Զ�������  ��о������ ����ֵ*/
  uint8_t                    MannualCoreTCSActionSpeed;            /*�ֶ�������  TCS�����ַ��ٶ�*/
  uint8_t                    MannualCoreXYZActionSpeed;            /*�ֶ�������  XYZ�����ַ��ٶ�*/
  uint8_t                    MannualCoreWidth;                     /*�ֶ�������  ��о���*/
  uint8_t                    MannualCoreFlexLevel;                 /*�ֶ�������  ��о������*/

  /*�� ���� ���� �ƹ� �ȿ��Ƶĸ�������*/
  uint8_t                    FeetVibCtrlSw;                        /*�Ų��񶯿��ƿ���*/
  uint8_t                    CalvesVibCtrlSw;                      /*�Ȳ��񶯿��ƿ���*/
  uint8_t                    SeatVibCtrlSw;                        /*�����񶯿��ƿ���*/
  uint8_t                    LumbarBackVibCtrlSw;                  /*�����񶯿��ƿ���*/
  uint32_t                   FeetVibCtrlOnOffTime;                 /*�Ų��񶯿��ƿ���ʱ��*/
  uint32_t                   CalvesVibCtrlOnOffTime;               /*�Ȳ��񶯿��ƿ���ʱ��*/
  uint32_t                   SeatVibCtrlOnOffTime;                 /*�����񶯿��ƿ���ʱ��*/
  uint32_t                   LumbarBackVibCtrlOnOffTime;           /*�����񶯿��ƿ���ʱ��*/

  uint8_t                    FeetHeatCtrlSw;                       /*�Ų����ȿ��ƿ���*/
  uint8_t                    CalvesHeatCtrlSw;                     /*�Ȳ����ȿ��ƿ���*/
  uint8_t                    SeatHeatCtrlSw;                       /*�������ȿ��ƿ���*/
  uint8_t                    LumbarBackHeatCtrlSw;                 /*�������ȿ��ƿ���*/
  uint32_t                   FeetHeatCtrlOnOffTime;                /*�Ų����ȿ��ƿ���ʱ��*/
  uint32_t                   CalvesHeatCtrlOnOffTime;              /*�Ȳ����ȿ��ƿ���ʱ��*/
  uint32_t                   SeatHeatCtrlOnOffTime;                /*�������ȿ��ƿ���ʱ��*/
  uint32_t                   LumbarBackHeatCtrlOnOffTime;          /*�������ȿ��ƿ���ʱ��*/

  uint32_t                   FeetRollerCtrlOnOffTime;              /*�Ź����ƿ���ʱ��*/
  uint32_t                   CalvesRollerCtrlOnOffTime;            /*�ȹ����ƿ���ʱ��*/
  uint8_t                    FeetRollerCtrlSw;                     /*�Ź����ƿ���*/
  uint8_t                    CalvesRollerCtrlSw;                   /*�ȹ����ƿ���*/

  uint32_t                   LedCtrlOnOffTime;                     /*�ƹ���ƿ���ʱ��*/

  /*��Ħ�β���״̬���������Ӳ�����״ֵ̬�����ϲ�ֱ�ӿ���-------------------------------------------*/
  BodyScanCSFlag_t           StateBodyScan;                        /*����״̬  ������*/
  CoreCSFlag_t               StateCore;                            /*����״̬  ��о*/
  CoreActionRunFlag_t        StateCoreAction;                      /*�����ַ�״̬  ��о*/
  XMotorCSFlag_t             StateXMotor;                          /*����״̬  X���*/
  YMotorCSFlag_t             StateYMotor;                          /*����״̬  Y���*/
  ZMotorCSFlag_t             StateZMotor;                          /*����״̬  Z���*/
  TCSMotorCSFlag_t           StateTCSMotor;                        /*����״̬  �������*/
  SpikeCSFlag_t              StateSpike;                           /*����״̬  �Ƹ�*/
  BackSpikeCSFlag_t          StateBackSpike;                       /*����״̬  �����Ƹ�*/
  ZeroSpikeCSFlag_t          StateZeroSpike;                       /*����״̬  �������Ƹ�*/
  FeetSpikeCSFlag_t          StateFeetSpike;                       /*����״̬  С�������Ƹ�*/
  LegFlexSpikeCSFlag_t      StateLegFlexSpike;                     /*����״̬  С�������Ƹ�*/
  GasCSFlag_t                StateGas;                             /*����״̬  ����*/
  GasPart1_t                 StateGasPart1;                        /*������λ1 ״̬*/ 
  GasPart2_t                 StateGasPart2;                        /*������λ2 ״̬*/ 
  RollerCSFlag_t             StateRoller;                          /*����״̬  ����*/
  VibCSFlag_t                StateVib;                             /*����״̬  ��*/
  HeatCSFlag_t               StateHeat;                            /*����״̬  ����*/
  LedCSFlag_t                StateLed;                             /*����״̬  �ƹ�*/
  CDPCSFlag_t                StateCDPCSFlag;                       /*���ݰ�״̬*/
  CDP_CenXxxCSFlag_t         StateCDPCenXxxCSFlag;                 /*���ݰ�״̬�����İ�<-->Xxx*/


  /*����-------------------------------------------------------------------------------------------*/
  MChairFault_t              Fault;


  /*��Ħ�β��� ��ҪΪ��������ã�ʵ�ʱ���Ӧ����ʹ�ø������Ľӿں���--------------------------------*/
  BodyScan_t                 *pBodyScan;                           /*������*/
  Core_t                     *pCore;                               /*��о*/
  Spike_t                    *pSpike;                              /*�Ƹ�*/
  Gas_t                      *pGas;                                /*����*/
  Heat_t                     *pHeat;                               /*����*/
  Roller_t                   *pRoller;                             /*����*/
  Vib_t                      *pVib;                                /*��*/
  Led_t                      *pLed;                                /*�ƹ�*/
  CDP_t                      *pCDP;                                /*ͨ�����ݰ�*/
  SaveData_t                 *pSaveData;                           /*���������*/

}MassageChair_t;



/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/
extern  MassageChair_t  MChair;    /*������ ���Ÿ���������ģ��*/
extern  MassageChair_t  *pMChair;  /*������ ���Ÿ���������ģ��*/


void MChair_Init(void);
void MChair_Handle(void);

#endif
