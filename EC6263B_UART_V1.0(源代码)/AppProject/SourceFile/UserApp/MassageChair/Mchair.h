/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: MChair.h
**
**    功能描述: 按摩椅最高层次文件
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
#ifndef  _MCHAIR_H
#define  _MCHAIR_H


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
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
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/


/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 : 按摩椅 键值处理相关                                                                                         
************************************************************************************************************************
*/
typedef struct SysMode_KeyLogicTabItem  SysMode_KeyLogicTabItem_t;

typedef  struct 
{
  const SysMode_KeyLogicTabItem_t  *KeyLogicTab;                                /*按键逻辑表*/
  uint8_t   KeyLogicTabNum;                                                     /*按键逻辑表 大小*/
  uint16_t (*pGetMatchID)(uint16_t index);                                      /*函数指针，指向的函数作用：返回表格条目 中 的要搜索的数据 所在的索引*/
  uint8_t  (*pAddOp)(uint8_t Index, uint8_t BeforeAfter, uint8_t CurExeState);  /*函数指针，指向的函数作用：键值执行前后的附加操作 */

  uint8_t  CtrlBuf[2];                                                          /*手控器的键值*/
  uint8_t  SideCtrlBuf[2];                                                      /*侧板的键值*/
  uint8_t  AppBuf[2];                                                           /*App的键值*/
  uint8_t  AppTimeOut;                                                          /*App的键值超时*/

}MChairKeyValHandle_t;  


/*
************************************************************************************************************************
* 类型定义 : 按摩椅 故障状态                                                                                         
************************************************************************************************************************
*/
typedef  struct 
{
  union 
  {
    struct
    {
      /*为方便调试时，查看故障码，增加此结构位定义，位名称的数字即代表故障码*/
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
  }ReportFlag;                     /*上报标识*/

  uint8_t   DisplayFaultID;        /*要显示的故障ID*/
  uint16_t  DisplayTLMsPerFault;   /*每个故障显示的时间长度*/
 
  uint16_t  ReportTLMs;            /*报警时长，单位MS*/

}MChairFault_t;  


/*
************************************************************************************************************************
* 类型定义 :  按摩椅 厂家检测                                                                                        
************************************************************************************************************************
*/
typedef struct
{
  uint8_t                  CoreKneadStep;                        /*机芯揉捏检测步骤*/
  uint8_t                  CoreRollStep;                         /*机芯推拿(滚动)检测步骤*/
  uint8_t                  CoreFlexStep;                         /*机芯伸缩检测步骤*/
  uint8_t                  BackSpikeStep;                        /*靠背推杆检测步骤*/
  uint8_t                  FeetSpikeStep;                        /*小腿推杆检测步骤*/
  uint8_t                  ZeroSpikeStep;                        /*零重力推杆检测步骤*/

  uint16_t                 CoreKneadTimeMs;                      /*机芯揉捏检测时间*/
  uint16_t                 CoreRollTimeMs;                       /*机芯推拿(滚动)检测时间*/
  uint16_t                 CoreFlexTimeMs;                       /*机芯伸缩检测时间*/
  uint16_t                 BackSpikeTimeMs;                      /*靠背推杆检测时间*/
  uint16_t                 FeetSpikeTimeMs;                      /*小腿推杆检测时间*/
  uint16_t                 ZeroSpikeTimeMs;                      /*零重力推杆检测时间*/

  union
  {
    struct
    {
      uint8_t    XPositionSensorFault          :1;    /*X 位置传感器故障*/   
      uint8_t    YPositionSensorFault          :1;    /*Y 位置传感器故障*/    
      uint8_t    ZPositionSensorFault          :1;    /*Z 位置传感器故障*/    
      uint8_t    BackPositionSensorFault       :1;    /*靠背 位置传感器故障*/    
      uint8_t    FeetPositionSensorFault       :1;    /*小腿 位置传感器故障*/    
      uint8_t    ZeroPositionSensorFault       :1;    /*零重力 位置传感器故障*/  
    }Bit;

    uint16_t All;
    
  }Result; /*检测结果*/

}MChairVenderInspect_t; 


/*
************************************************************************************************************************
* 类型定义 : 按摩椅 控制与状态标识                                                                                         
************************************************************************************************************************
*/
typedef  union 
{
  uint32_t All;

  struct
  {
    uint8_t    SysRun                            :1;    /*系统运行，即非待机模式*/
    uint8_t    Pause                             :1;    /*暂停*/

    uint8_t    ZeroGravityAngleRun               :1;    /*零重力摆角度中*/

    uint8_t    BackSpikeMannualMoveDisable       :1;    /*靠背推杆手动无效*/
    uint8_t    ZeroSpikeMannualMoveDisable       :1;    /*零重力推杆手动无效*/
    uint8_t    FeetSpikeMannualMoveDisable       :1;    /*小腿推杆手动无效*/
    uint8_t    LegFlexMannualMoveDisable         :1;    /*小腿伸缩手动无效*/
    uint8_t    ULegFlexMannualMoveDisable        :1;    /*上小腿伸缩手动无效*/

    uint8_t    FeetHeatMannualOpDisable          :1;    /*脚部加热手动无效*/
    uint8_t    CalvesHeatMannualOpDisable        :1;    /*腿部加热手动无效*/
    uint8_t    SeatHeatMannualOpDisable          :1;    /*座部加热手动无效*/
    uint8_t    LumbarBackHeatMannualOpDisable    :1;    /*腰背加热手动无效*/

    uint8_t    GasCooperateSpikeRun              :1;    /*充气配合推杆 运行*/

    uint8_t    UserMassageTimeOut                :1;    /*用户按摩时间 超时*/
    uint8_t    UserMassageTimeRun                :1;    /*用户按摩时间 运行*/

    uint8_t    KeyValExeResult                   :1;    /*键值执行结果*/

    uint8_t    IDCodeOpRun                       :1;    /*ID码相关操作执行中*/

    uint8_t    OccurNoStartUpFault               :1;    /*发生不允许启动 的故障*/

    uint8_t    UserSpikeAngleSetd                :1;    /*用户开机后第一次执行任何按摩功能时，要先倒到固定角度*/

    uint8_t    VenderOpFinish                    :1;    /*厂家操作结束*/
    
    uint8_t    BluetoothSwitch                   :1;    /*蓝牙开关*/

    uint8_t    SpikeHomeResetRun                 :1;    /*推杆初始角度复位*/

    uint8_t    TabTryRun                         :1;    /*动作表格体验 运行标识*/
    
    uint8_t    FuncExeAngleNeedSet               :1;    /*功能执行角度需要设置*/

    uint8_t    LegFlexTestSw                     :1;    /*小腿伸缩拷机测试开关*/
    
    uint8_t    MChairReported                    :1;    /*状态上报标志位*/
  }Bit;

}MChairCSFlag_t;  /*Control State Flag  控制与状态标识*/


/*
************************************************************************************************************************
* 类型定义 : 按摩椅部件功能状态                                                                                         
************************************************************************************************************************
*/
typedef  union 
{
  uint32_t All;
  struct
  {
    /*#define  FUNC_TYPE_NONE           0     功能类型 无
      #define  FUNC_TYPE_MANNUAL        1     功能类型 手动
      #define  FUNC_TYPE_AUTO           2     功能类型 自动
      #define  FUNC_TYPE_MANNUALAUTO    3     功能类型 手动自动*/

    uint8_t    Core              :2;    /*机芯 功能状态*/
    uint8_t    Gas               :2;    /*充气 功能状态*/
    uint8_t    Spike             :2;    /*推杆 功能状态*/
    
    uint8_t    FeetRoller        :2;    /*脚滚 功能状态*/
    uint8_t    CalvesRoller      :2;    /*脚滚 功能状态*/
    
    uint8_t    LumbarBackVib     :2;    /*腰背振 功能状态*/
    uint8_t    SeatVib           :2;    /*座振   功能状态*/
    uint8_t    CalvesVib         :2;    /*腿振   功能状态*/
    uint8_t    FeetVib           :2;    /*脚振   功能状态*/
    
    uint8_t    LumbarBackHeat    :2;    /*腰背热 功能状态*/
    uint8_t    SeatHeat          :2;    /*座热   功能状态*/
    uint8_t    CalvesHeat        :2;    /*腿热   功能状态*/
    uint8_t    FeetHeat          :2;    /*脚热   功能状态*/
    
    uint8_t    Led               :2;    /*灯光 功能状态*/
  }Bit;

}ComponentFuncState_t; 


/*
************************************************************************************************************************
* 类型定义 : 按摩椅 相关操作数据结构
*            按摩椅 最高层次 结构体， 内含各个按摩椅构成部件                                                                                         
************************************************************************************************************************
*/
typedef struct
{
  MChairCSFlag_t             CSFlag;                               /*控制与状态标识*/

  uint8_t                    PromptToneAddr;                       /*提示音地址*/
  uint16_t                   PromptToneTLMs;                       /*提示音时长*/
  uint16_t                   LcdBackLightTLMs;                     /*Lcd背光时长*/

  MChairKeyValHandle_t       KeyValHandle;                         /*键值处理*/

  /*系统模式相关-----------------------------------------------------------------------------------*/
  /*注：由于类平板靠中心板供电，ERP关闭后，类平板就无法操作了。
        因此无法在待机模式下操作类平板进入厂家模式，只能在开机后操作类平板进入厂家模式。
        增加SysModeVender这个变量，记录要进入的厂家模式。开机状态下，按下相应的厂家模式按键，
        将先进入待机模式，然后待机模式的代码将根据SysModeVender变量的值，再转入到相应的厂家模式。*/
  uint8_t                    SysModeVender;                        /*系统模式 厂家*/

  uint8_t                    SysModeHis;                           /*系统模式 当前*/
  uint8_t                    SysModeCur;                           /*系统模式 历史*/

  uint8_t                    UserMassageTimeMin;                   /*用户按摩时间 分*/
  uint8_t                    UserMassageTimeSec;                   /*用户按摩时间 秒*/
  uint8_t                    UserMassageTimeDelayOnSec;            /*用户按摩时间延时启动的秒数*/

  uint8_t                    UserMassageIdleTimeSec;               /*用户按摩空闲时间 秒，即无任何按摩动作*/

  uint8_t                    ERPPowerSw;                           /*ERP电源开关*/
  uint16_t                   ERPPowerOffWaitTimeMs;                /*ERP电源关闭前的等待时间*/
  uint16_t                   ERPPowerOnTimeMs;                     /*ERP电源开启了多长时间*/

  uint16_t                   CommonStep;                           /*各个模式根据需要都可使用的步骤*/
  uint16_t                   CommonTimeSec;                        /*各个模式根据需要都可使用的时间，单位秒*/
  uint16_t                   CommonTimeSec1;                       /*各个模式根据需要都可使用的时间，单位秒*/

  MChairVenderInspect_t      VenderInspect;                        /*厂家检测*/


  /*按摩相关功能 及其辅助变量------------------------------------------------------------------------
   * FuncMannual：手动     FuncAuto：自动     FuncMA：手动 与 自动  */
  ComponentFuncState_t       ComponentFuncState;                   /*部件功能状态*/

  uint16_t                   FuncHis[18];                          /*记录历史功能*/

  RollerAction_t             FuncMA_Roller;                        /*【滚轮】手动 与 自动*/
  HeatAction_t               FuncMA_Heat;                          /*【加热】手动 与 自动*/
  VibAction_t                FuncMA_Vib;                           /*【振动】手动 与 自动*/
  LedAction_t                FuncMA_Led;                           /*【灯光】手动 与 自动*/
  CoreAction_t               FuncMannual_Core;                     /*【机芯】手动*/
  GasAction_t                FuncMannual_Gas;                      /*【充气】手动*/
  SpikeAction_t              FuncMannual_Spike;                    /*【推杆】手动*/
  uint16_t                   FuncAuto_Core;                        /*【机芯】自动*/
  uint16_t                   FuncAuto_Gas;                         /*【充气】自动*/
  uint16_t                   FuncAuto_Spike;                       /*【推杆】自动*/
  uint16_t                   FuncAuto_CoreGas;                     /*【机芯+充气】自动*/
  uint16_t                   FuncAuto_CoreSpike;                   /*【机芯+推杆】自动*/
  uint16_t                   FuncAuto_GasSpike;                    /*【充气+推杆】自动*/
  uint16_t                   FuncAuto_CoreGasSpike;                /*【机芯+充气+推杆】自动*/
  uint16_t                   FuncAuto_GridCombo;                   /*【宫格组合】自动*/

  /*注：手动程序下，机芯的实际速度 = 手动下的设置速度*/
  uint8_t                    GasIntensity;                         /*充气强度*/
  uint8_t                    AutoCoreFlexLevelAdjust;              /*自动程序下  机芯伸缩度 调节值*/
  uint8_t                    MannualCoreTCSActionSpeed;            /*手动程序下  TCS动作手法速度*/
  uint8_t                    MannualCoreXYZActionSpeed;            /*手动程序下  XYZ动作手法速度*/
  uint8_t                    MannualCoreWidth;                     /*手动程序下  机芯宽度*/
  uint8_t                    MannualCoreFlexLevel;                 /*手动程序下  机芯伸缩度*/

  /*振动 滚轮 加热 灯光 等控制的辅助变量*/
  uint8_t                    FeetVibCtrlSw;                        /*脚部振动控制开关*/
  uint8_t                    CalvesVibCtrlSw;                      /*腿部振动控制开关*/
  uint8_t                    SeatVibCtrlSw;                        /*坐部振动控制开关*/
  uint8_t                    LumbarBackVibCtrlSw;                  /*腰背振动控制开关*/
  uint32_t                   FeetVibCtrlOnOffTime;                 /*脚部振动控制开关时间*/
  uint32_t                   CalvesVibCtrlOnOffTime;               /*腿部振动控制开关时间*/
  uint32_t                   SeatVibCtrlOnOffTime;                 /*坐部振动控制开关时间*/
  uint32_t                   LumbarBackVibCtrlOnOffTime;           /*腰背振动控制开关时间*/

  uint8_t                    FeetHeatCtrlSw;                       /*脚部加热控制开关*/
  uint8_t                    CalvesHeatCtrlSw;                     /*腿部加热控制开关*/
  uint8_t                    SeatHeatCtrlSw;                       /*坐部加热控制开关*/
  uint8_t                    LumbarBackHeatCtrlSw;                 /*腰背加热控制开关*/
  uint32_t                   FeetHeatCtrlOnOffTime;                /*脚部加热控制开关时间*/
  uint32_t                   CalvesHeatCtrlOnOffTime;              /*腿部加热控制开关时间*/
  uint32_t                   SeatHeatCtrlOnOffTime;                /*坐部加热控制开关时间*/
  uint32_t                   LumbarBackHeatCtrlOnOffTime;          /*腰背加热控制开关时间*/

  uint32_t                   FeetRollerCtrlOnOffTime;              /*脚滚控制开关时间*/
  uint32_t                   CalvesRollerCtrlOnOffTime;            /*腿滚控制开关时间*/
  uint8_t                    FeetRollerCtrlSw;                     /*脚滚控制开关*/
  uint8_t                    CalvesRollerCtrlSw;                   /*腿滚控制开关*/

  uint32_t                   LedCtrlOnOffTime;                     /*灯光控制开关时间*/

  /*按摩椅部件状态，将各个子部件的状态值让最上层直接可用-------------------------------------------*/
  BodyScanCSFlag_t           StateBodyScan;                        /*部件状态  人体检测*/
  CoreCSFlag_t               StateCore;                            /*部件状态  机芯*/
  CoreActionRunFlag_t        StateCoreAction;                      /*动作手法状态  机芯*/
  XMotorCSFlag_t             StateXMotor;                          /*部件状态  X马达*/
  YMotorCSFlag_t             StateYMotor;                          /*部件状态  Y马达*/
  ZMotorCSFlag_t             StateZMotor;                          /*部件状态  Z马达*/
  TCSMotorCSFlag_t           StateTCSMotor;                        /*部件状态  敲拍马达*/
  SpikeCSFlag_t              StateSpike;                           /*部件状态  推杆*/
  BackSpikeCSFlag_t          StateBackSpike;                       /*部件状态  靠背推杆*/
  ZeroSpikeCSFlag_t          StateZeroSpike;                       /*部件状态  零重力推杆*/
  FeetSpikeCSFlag_t          StateFeetSpike;                       /*部件状态  小腿升降推杆*/
  LegFlexSpikeCSFlag_t      StateLegFlexSpike;                     /*部件状态  小腿伸缩推杆*/
  GasCSFlag_t                StateGas;                             /*部件状态  充气*/
  GasPart1_t                 StateGasPart1;                        /*充气部位1 状态*/ 
  GasPart2_t                 StateGasPart2;                        /*充气部位2 状态*/ 
  RollerCSFlag_t             StateRoller;                          /*部件状态  滚轮*/
  VibCSFlag_t                StateVib;                             /*部件状态  振动*/
  HeatCSFlag_t               StateHeat;                            /*部件状态  加热*/
  LedCSFlag_t                StateLed;                             /*部件状态  灯光*/
  CDPCSFlag_t                StateCDPCSFlag;                       /*数据包状态*/
  CDP_CenXxxCSFlag_t         StateCDPCenXxxCSFlag;                 /*数据包状态：中心板<-->Xxx*/


  /*故障-------------------------------------------------------------------------------------------*/
  MChairFault_t              Fault;


  /*按摩椅部件 主要为方便调试用，实际编码应尽量使用各部件的接口函数--------------------------------*/
  BodyScan_t                 *pBodyScan;                           /*人体检测*/
  Core_t                     *pCore;                               /*机芯*/
  Spike_t                    *pSpike;                              /*推杆*/
  Gas_t                      *pGas;                                /*充气*/
  Heat_t                     *pHeat;                               /*加热*/
  Roller_t                   *pRoller;                             /*滚轮*/
  Vib_t                      *pVib;                                /*振动*/
  Led_t                      *pLed;                                /*灯光*/
  CDP_t                      *pCDP;                                /*通信数据包*/
  SaveData_t                 *pSaveData;                           /*保存的数据*/

}MassageChair_t;



/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
extern  MassageChair_t  MChair;    /*将变量 开放给其他功能模块*/
extern  MassageChair_t  *pMChair;  /*将变量 开放给其他功能模块*/


void MChair_Init(void);
void MChair_Handle(void);

#endif
