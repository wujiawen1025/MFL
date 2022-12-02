/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: CDP_CenXxx.h                                                                                                         
**
**    功能描述:	通信数据包   之   手控器 机芯板 小腿板 侧板 <--> 中心板。
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
#ifndef  _CDP_CEN_CTRL_H
#define  _CDP_CEN_CTRL_H


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp.h"
#include "ESF.h"
#include "CDP_Common.h"

/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
/*接收状态机*/
#define  CTRL_TO_CEN_RX_STATE_SEARCH_HEAD            0         /*搜索起始码*/
#define  CTRL_TO_CEN_RX_STATE_JUDGE_ADDR             1         /*判断地址码*/
#define  CTRL_TO_CEN_RX_STATE_JUDGE_FUNC             2         /*判断功能码*/
#define  CTRL_TO_CEN_RX_STATE_JUDGE_FRAMELEN         3         /*判断帧长度*/
#define  CTRL_TO_CEN_RX_STATE_RCV_DATA               4         /*接收数据*/
#define  CTRL_TO_CEN_RX_STATE_JUDGE_SUMCHECK         5         /*判断校验码*/ 


/*手控器 --> 中心板*/
#define  CTRL_TO_CEN_HEAD                            0xAA      /*起始码*/
#define  CTRL_TO_CEN_ADDR                            0x01      /*地址码*/
#define  CTRL_TO_CEN_FUNC                            0xA0      /*功能码*/
#define  CTRL_TO_CEN_FRAMELEN                        0x0A      /*帧长度*/
#define  CTRL_TO_CEN_DATALEN                         0x05      /*数据长度*/

#define  CTRL_TO_CEN_ADDR_OFFSET                     1         /*地址在帧中的位置偏移量*/
#define  CTRL_TO_CEN_DATA_OFFSET                     4         /*数据在帧中的位置偏移量*/


/*中心板 --> 手控器 */
#define  CEN_TO_CTRL_HEAD                            0xAA      /*起始码*/
#define  CEN_TO_CTRL_ADDR                            0x08      /*地址码*/
#define  CEN_TO_CTRL_FUNC                            0xB0      /*正常操作下  功能码*/
#define  CEN_TO_CTRL_DATALEN                         40        /*正常操作下  数据长度*/
#define  CEN_TO_CTRL_VENDER_DATALEN                  38        /*厂家检测模式下  数据长度*/


#define  CTRL_KEY_BE_STUCK_TIME_THRESHOLD            45000     /*手控器按键被卡 时间门限*/ 
#define  CTRL_LINK_LOST_COUNT_THRESHOLD              8         /*手控器链接丢失次数 门限*/

#define  CDP_TYPE_NONE                               0x00      /*通信数据包类型：无*/
//#define  CDP_TYPE_CTRL                               0x01      /*通信数据包类型：控制*/  



/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  手控器 <--> 中心板   控制与状态标识                                                                              
************************************************************************************************************************
*/
typedef  union 
{
  uint8_t All;
  struct
  {
    uint8_t    CtrlLinkLostFault          :1;    /*通信链接丢失 故障*/
    uint8_t    CoreLinkLostFault          :1;    /*机芯板通信链接丢失 故障*/
    uint8_t    CalvesFeetLinkLostFault    :1;    /*腿脚板通信链接丢失 故障*/
    uint8_t    SideCtrlLinkLostFault      :1;    /*侧板通信链接丢失   故障*/

  }Bit;

}CDP_CenXxxCSFlag_t;  /*Control State Flag  控制与状态标识*/

/*
************************************************************************************************************************
* 类型定义 :  手控器 <--> 中心板  相关操作数据结构                                                                            
************************************************************************************************************************
*/
typedef struct
{
  CDP_CenXxxCSFlag_t         CSFlag;
  CDP_FrameRx_t              FrameRx;
  
  uint16_t                   CtrlLinkLostTimeMs;                /*通信链接丢失时间*/
  uint16_t                   CoreLinkLostTimeMs;                /*通信链接丢失时间*/
  uint16_t                   CalvesFeetLinkLostTimeMs;          /*通信链接丢失时间*/
  uint16_t                   SideCtrlLinkLostTimeMs;            /*通信链接丢失时间*/
  
  uint8_t                    CurCDPType;                        /*当前 通信数据包类型*/

  //---------------------------------------------------------------------------
  uint8_t                    ORxBuf[CTRL_TO_CEN_FRAMELEN+2];     /*接收缓存*/
  uint8_t                    ORxLen;                             /*接收长度*/

  uint8_t                    ORxDataLen;                         /*接收到的数据长度*/
  uint8_t                    ORxState;                           /*接收状态*/
  uint8_t                    OKeyValRx;                          /*接收键值*/
  uint8_t                    OKeyValMap;                         /*映射后的键值*/
  uint8_t                    OKeyValAssist;                      /*键值辅助*/

/*正常操作下 发给手控器的数据--------------------------------------*/
  struct
  {
    uint8_t          Head;                               /*起始码*/
    uint8_t          Addr;                               /*地址码*/
    uint8_t          FuncCode;                           /*功能码*/
    uint8_t          DataLen;                            /*数据包长度*/

    struct
    {
      uint8_t        SysRun                         :1;  /*系统开关机状态*/ 
      uint8_t        Pause                          :1;  /*暂停状态*/    
      uint8_t        MassageTimeOut                 :1;  /*按摩定时到状态*/ 
      uint8_t        PromptToneRun                  :1;  /*按键提示音*/ 
      uint8_t        VenderOpFinish                 :1;  /*厂家操作完成*/ 
      uint8_t        BluetoothSwitch                :1;  /*蓝牙开关*/

    }Byte5;

    struct
    {
      uint8_t        CoreXYZKneadInRun              :1;  /*向内揉捏手法 运行中*/ 
      uint8_t        CoreXYZKneadOutRun             :1;  /*向外揉捏手法 运行中*/ 
      uint8_t        CoreXYZRollRun                 :1;  /*推拿(滚动)手法 运行中*/ 
      uint8_t        CoreXYZKneadRun                :1;  /*揉捏手法 运行中*/ 
      uint8_t        CoreXYZKneadStrokeRun          :1;  /*揉抚手法 运行中*/ 
      uint8_t        CoreXYZKneadPressRun           :1;  /*揉按手法 运行中*/ 
      uint8_t        CoreXYZShiaRun                 :1;  /*指压手法 运行中*/ 
      uint8_t        CoreXYZStretchRun              :1;  /*伸展手法 运行中*/ 
    }Byte6;

    struct
    {
      uint8_t        CoreTCSClap1Run                :1;  /*拍打1手法 运行中*/ 
      uint8_t        CoreTCSClap2Run                :1;  /*拍打2手法 运行中*/ 
      uint8_t        CoreTCSShia1Run                :1;  /*指压1手法 运行中*/ 
      uint8_t        CoreTCSShia2Run                :1;  /*指压2手法 运行中*/ 
      uint8_t        CoreTCSLTapRun                 :1;  /*轻敲击手法 运行中*/ 
      uint8_t        CoreTCSTapRun                  :1;  /*敲击手法 运行中*/ 
    }Byte7;

    struct
    {
      uint8_t        GasShoulderRun                 :1;  /*肩部充气IO状态*/  
      uint8_t        GasArmLeftRun                  :1;  /*手臂左充气IO状态*/  
      uint8_t        GasArmRightRun                 :1;  /*手臂右充气IO状态*/  
      uint8_t        GasLumbarRun                   :1;  /*腰部充气IO状态*/  
      uint8_t        GasSeatRun                     :1;  /*座部充气IO状态*/  
      uint8_t        GasCalvesRun                   :1;  /*腿部充气IO状态*/  
    }Byte8;

    struct
    {
      uint8_t        BackHeatRun                    :1;  /*背部加热IO状态*/  
      uint8_t                                       :1; 
      uint8_t        CoreSpotState                  :1;  /*机芯手动程序 定点状态*/  
      uint8_t        CorePartState                  :1;  /*机芯手动程序 区间状态*/  
      uint8_t        CalvesRollerRunState           :1;  /*搓腿 执行中*/  
      uint8_t        FeetRollerRunState             :1;  /*揉脚 执行中*/  
      uint8_t        KeyCalvesRoller                :1;  /*按键 搓腿*/  
      uint8_t        KeyFeetRoller                  :1;  /*按键 揉脚*/  
    }Byte9;

    struct
    {
      uint8_t        GasIntensity                   :4;  /*充气强度*/  
      uint8_t        MassageIntensity               :4;  /*按摩强度*/  
    }Byte10;

    struct
    {
      uint8_t        TapSpeed                       :4;  /*敲击速度*/  
      uint8_t        XYZSpeed                       :4;  /*XYZ手法速度*/  
    }Byte11;

    struct
    {
      uint8_t        BackScanRun                    :1;  /*人体检测中*/  
      uint8_t        BackScanFinish                 :1;  /*人体检测完成*/  
      uint8_t        ShoulderAdjustEn               :1;  /*允许肩部位置手动微调使能*/ 
    }Byte12;

    struct
    {
      uint8_t        KeyBackHeat                    :1;  /*按键 背部加热*/  
      uint8_t                                       :1; 
      uint8_t        KeyGasShoulder                 :1;  /*按键 肩部充气*/  
      uint8_t        KeyGasLumbarSeat               :1;  /*按键 腰座充气*/  
      uint8_t        KeyGasArm                      :1;  /*按键 手部充气*/  
      uint8_t        KeyGasCalves                   :1;  /*按键 腿部充气*/  
      uint8_t        KeyGasFull                     :1;  /*按键 全身充气*/    
      uint8_t        KeyGasQuick                    :1;  /*按键 快速充气*/    
    }Byte13;

    struct
    {
      uint8_t        KeyXYZAction                   :8;  /*按键 XYZ手动程序*/  
    }Byte14;

    struct
    {
      uint8_t        KeyTCSAction                   :8;  /*按键 TCS手动程序*/  
    }Byte15;

    struct
    {
      uint8_t        KeyAuto                        :8;  /*按键 自动程序*/  
    }Byte16;

    struct
    {
      uint8_t        keep                           :8; 
    }Byte17;

    struct
    {
      uint8_t        CoreXPosition                  :4;  /*机芯X轴坐标(0-2)*/  
      uint8_t        CoreZPosition                  :4;  /*机芯Z轴坐标(0-7)*/  
    }Byte18;

    struct
    {
      uint8_t        KeyBackUpFeetDown              :1;  /*按键 靠背 升*/  
      uint8_t        KeyBackDownFeetUp              :1;  /*按键 靠背 降*/  
      uint8_t        KeyFeetUp                      :1;  /*按键 小腿 升*/  
      uint8_t        KeyFeetDown                    :1;  /*按键 小腿 降*/  
      uint8_t        KeyLegExtend                   :1;  /*按键 伸腿*/  
      uint8_t        KeyLegShorten                  :1;  /*按键 缩腿*/  
      uint8_t        KeyZero1                       :1;  /*零重力1*/  
      uint8_t        KeyZero2                       :1;  /*零重力2*/ 
    }Byte19;


    struct
    {
      uint8_t        KeyCoreMannualUp               :1;  /*按键 机芯 上行*/  
      uint8_t        KeyCoreMannualDown             :1;  /*按键 机芯 下行*/  
      uint8_t        KeyCoreWidthDec                :1;  /*按键 机芯 调窄*/  
      uint8_t        KeyCoreWidthAdd                :1;  /*按键 机芯 调宽*/ 
      
      uint8_t        LedLogoRun                     :1;  /*Logo灯IO状态*/  
      uint8_t        LedProjectionRun               :1;  /*迎宾灯IO状态*/  
      uint8_t        KeyLed                         :1;  /*LED灯按键状态*/  
      
    }Byte20;


    struct
    {
      uint8_t        CoreYPosition                  :8;  /*机芯Y轴坐标(0-36)*/  
    }Byte21;

    int8_t           CoreLeftTemp;                       /*左按摩头温度*/
    int8_t           CoreRightTemp;                      /*右按摩头温度*/

    uint8_t          MassageTimeSec;                     /*按摩剩余时间*/
    uint8_t          MassageTimeMin;                     /*按摩剩余时间*/
    uint8_t          PromptToneAddr;                     /*提示音地址*/ 
    uint8_t          FaultCodeBit[10];                   /*故障位*/

    struct
    {
      uint8_t        KeyInspectOneself              :1;  /*按键 厂家自动检测*/  
      uint8_t        KeyInspectManual               :1;  /*按键 厂家手动检测*/  
      uint8_t        KeyInspectOther1               :1;  /*按键 其他厂家检测 1*/  
      uint8_t        KeyInspectOther2               :1;  /*按键 其他厂家检测 2*/  
      uint8_t        KeyInspectOther3               :1;  /*按键 其他厂家检测 3*/  
      uint8_t        KeyTestNoTimer                 :1;  /*按键 无定时拷机程序*/  
      uint8_t        KeyTestSpike                   :1;  /*按键 推杆拷机程序*/  
      uint8_t        KeyTestAge                     :1;  /*按键 寿命拷机程序*/  
    }Byte37;

    struct
    {
      uint8_t        KeyTestOther1                  :1;  /*按键 其他拷机 1*/  
      uint8_t        KeyTestOther2                  :1;  /*按键 其他拷机 2*/  
      uint8_t        KeyTestOther3                  :1;  /*按键 其他拷机 3*/  
      uint8_t        Packing                        :1;  /*按键 包装程序*/ 
      uint8_t        KeyOther1                      :1;  /*按键 其他1*/  
      uint8_t        KeyOther2                      :1;  /*按键 其他2*/  
      uint8_t        KeyOther3                      :1;  /*按键 其他3*/  
      uint8_t        KeyQueryChairInfo              :1;  /*按键 查询按摩椅信息（如软件版本号 等信息）*/  
    }Byte38;

    uint8_t         KeyValAck;                           /*按键应答*/
    uint8_t         SumCode;                             /*校验码*/

  }TxBuf; /*正常操作下 发给手控器的数据*/


  /*厂家检测模式下 发给手控器的数据-------------------------------*/
  struct
  {
    uint8_t          Head;                               /*起始码*/
    uint8_t          Addr;                               /*地址码*/
    uint8_t          FuncCode;                           /*功能码*/
    uint8_t          DataLen;                            /*数据包长度*/

    struct
    {
      uint8_t        SysRun                         :1;  /*系统开关机状态*/ 
      uint8_t        Pause                          :1;  /*暂停状态*/    
      uint8_t        MassageTimeOut                 :1;  /*按摩定时到状态*/ 
      uint8_t        PromptToneRun                  :1;  /*提示音*/ 
      uint8_t        VenderOpFinish                 :1;  /*厂家操作完成*/ 
   
    }Byte5;

    uint8_t          Edition;                            /*版本号*/
    uint16_t         SysRunTimeHour;                     /*系统运行时间*/
    uint16_t         XMotorRunTimeHour;                  /*X马达运行时间*/
    uint16_t         YMotorRunTimeHour;                  /*Y马达运行时间*/
    uint16_t         ZMotorRunTimeHour;                  /*Z马达运行时间*/
    uint16_t         TCSMotorRunTimeHour;                /*敲击马达运行时间*/
    uint16_t         BackSpikeMotorRunTimeHour;          /*靠背推杆马达运行时间*/
    uint16_t         FeetSpikeMotorRunTimeHour;          /*小腿推杆马达运行时间*/
    int8_t           CoreLeftTemp;                       /*左按摩头温度*/
    int8_t           CoreRightTemp;                      /*右按摩头温度*/
    int8_t           FeetTemp;                           /*脚部温度*/
    uint8_t          PromptToneAddr;                     /*提示音地址*/ 
    uint8_t          FaultCodeBit[10];                   /*故障位*/

    struct
    {
      uint8_t        KeyInspectOneself              :1;  /*按键 厂家自动检测*/  
      uint8_t        KeyInspectManual               :1;  /*按键 厂家手动检测*/  
      uint8_t        KeyInspectOther1               :1;  /*按键 其他厂家检测 1*/  
      uint8_t        KeyInspectOther2               :1;  /*按键 其他厂家检测 2*/  
      uint8_t        KeyInspectOther3               :1;  /*按键 其他厂家检测 3*/  
      uint8_t        KeyTestNoTimer                 :1;  /*按键 无定时拷机程序*/  
      uint8_t        KeyTestSpike                   :1;  /*按键 推杆拷机程序*/  
      uint8_t        KeyTestAge                     :1;  /*按键 寿命拷机程序*/  
    }Byte35;

    struct
    {
      uint8_t        KeyTestOther1                  :1;  /*按键 其他拷机 1*/  
      uint8_t        KeyTestOther2                  :1;  /*按键 其他拷机 2*/  
      uint8_t        KeyTestOther3                  :1;  /*按键 其他拷机 3*/  
      uint8_t        Packing                        :1;  /*按键 包装程序*/ 
      uint8_t        KeyOther1                      :1;  /*按键 其他1*/  
      uint8_t        KeyOther2                      :1;  /*按键 其他2*/  
      uint8_t        KeyOther3                      :1;  /*按键 其他3*/  
      uint8_t        KeyQueryChairInfo              :1;  /*按键 查询按摩椅信息（如软件版本号 等信息）*/  
    }Byte36;

    uint8_t         KeyValAck;                           /*按键应答*/
    uint8_t         SumCode;                             /*校验码*/

  }VenderTxBuf; /*厂家检测模式下 发给手控器的数据*/

}CDP_CenXxx_t;

/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
void CDP_CenStateTmrToCtrl_DataTx(Ticker_t ExePeriod);
void CDP_CenXxx_FaultCheck(Ticker_t ExePeriod);
uint8_t CDP_CenXxx_DataTx(ESF_Evt_t *pEvt);
CDP_CenXxx_t* CDP_CenXxx_Init(void);
CDP_CenXxxCSFlag_t CDP_CenXxx_GetCSFlag(void);

#endif
