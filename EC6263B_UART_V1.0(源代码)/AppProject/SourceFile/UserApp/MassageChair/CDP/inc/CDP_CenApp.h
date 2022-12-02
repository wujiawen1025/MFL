/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: CDP_CenApp.h                                                                                                         
**
**    功能描述:	通信数据包   之   蓝牙APP <--> 中心板。
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
#ifndef  _CDP_CEN_APP_H
#define  _CDP_CEN_APP_H


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp.h"
#include "ESF.h"
#include "CDP_Common.h"
//#include "CDP_CenXxx.h"

/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
#define  APP_CDP_OFFSET_HEAD                     0                    /*协议数据单元内的 起始码 偏移*/
#define  APP_CDP_OFFSET_FUNC                     1                    /*协议数据单元内的 功能码 偏移*/
#define  APP_CDP_OFFSET_LEN                      2                    /*协议数据单元内的 数据长度 偏移*/
#define  APP_CDP_OFFSET_DATA                     3                    /*协议数据单元内的 数据 偏移*/


/*APP --> 中心板*/
#define  APP_TO_CEN_HEAD                            0x7B      /*起始码*/
#define  APP_TO_CEN_FUNC                            0xA0      /*功能码*/
#define  APP_TO_CEN_DATALEN                         0x02      /*数据长度*/

/*中心板 --> APP */
#define  CEN_TO_APP_HEAD                            0x7B      /*起始码*/
#define  CEN_TO_APP_FUNC                            0xB0      /*正常操作下  功能码*/


/*
************************************************************************************************************************
* 类型定义 :  通信数据包 数据对象管理表项                                                                        
************************************************************************************************************************
*/
typedef struct
{
  uint8_t    Cmd;                   /*数据的ID识别码*/
  void     (*pDataHandle)(void);    /*数据处理函数*/

}AppDataObjManageTabItem_t;

/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*接收状态机*/
#define  APP_TO_CEN_RX_STATE_SEARCH_HEAD            0         /*搜索起始码*/
#define  APP_TO_CEN_RX_STATE_JUDGE_FUNC             1         /*判断功能码*/
#define  APP_TO_CEN_RX_STATE_JUDGE_FRAMELEN         2         /*判断帧长度*/
#define  APP_TO_CEN_RX_STATE_RCV_DATA               3         /*接收数据*/
#define  APP_TO_CEN_RX_STATE_JUDGE_SUMCHECK         4         /*判断校验码*/ 

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
    uint8_t    LinkLostFault                  :1;    /*通信链接丢失 故障*/
    uint8_t    NeedAck                        :1;
//    uint8_t    GetIDCode                      :1;
//    uint8_t    CfgNetwork                     :1;
//    uint8_t    GetSoftVersion                 :1;

  }Bit;

}CDP_CenAppCSFlag_t;  /*Control State Flag  控制与状态标识*/


/*
************************************************************************************************************************
* 类型定义 :  手控器 <--> 中心板  相关操作数据结构                                                                            
************************************************************************************************************************
*/
typedef struct
{
  CDP_CenAppCSFlag_t         CSFlag;
  uint8_t                    *pRxBuf;                  /*接收缓存*/               
  uint16_t                   LinkLostTimeMs;           /*通信链接丢失时间*/
  
  uint8_t                    CurCDPType;                        /*当前 通信数据包类型*/

  CDP_FrameRx_t              FrameRx;
  //---------------------------------------------------------------------------
  uint8_t                    RxBuf[20];                        /*接收缓存*/
  uint8_t                    AckBuf[20];
  uint8_t                    RxLen;                            /*接收长度*/

  uint8_t                    RxDataLen;                         /*接收到的数据长度*/
  uint8_t                    RxState;                           /*接收状态*/
  uint8_t                    KeyValRx;                          /*接收键值*/
  uint8_t                    KeyValMap;                         /*映射后的键值*/
  uint8_t                    KeyValAssist;                      /*键值辅助*/

/*正常操作下 发给手控器的数据--------------------------------------*/
  struct
  {
    uint8_t          Head;                               /*起始码*/
    uint8_t          FuncCode;                           /*功能码*/
    uint8_t          DataLen;                            /*数据包长度*/

    struct
    {
      uint8_t        SysRun                         :1;  /*系统开关机状态*/ 
      uint8_t        Pause                          :1;  /*暂停状态*/    
      uint8_t        MassageTimeOut                 :1;  /*按摩定时到状态*/ 
      uint8_t        PromptToneRun                  :1;  /*按键提示音*/ 
      uint8_t        VenderOpFinish                 :1;  /*厂家操作完成*/ 

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
      uint8_t        keep                           :7;  
      uint8_t        KeyHomeReset                   :1;  /*复位状态*/  
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
    
    struct
    {
      uint8_t                                       :1;  
      uint8_t        WIFINetCfgOK                   :1;  /*WIFI配网完成*/  
      uint8_t                                       :6;  
    }Byte27;
    
    uint8_t          FaultCodeBit[10];                   /*故障位*/

    uint8_t         SumCode;                             /*校验码*/

  }TxBuf; /*正常操作下 发给手控器的数据*/

}CDP_CenApp_t;

/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/

void CDP_CenTmrToApp_DataTx(Ticker_t ExePeriod);
void CDP_CenApp_FaultCheck(Ticker_t ExePeriod);
uint8_t CDP_CenApp_DataTx(ESF_Evt_t *pEvt);
CDP_CenApp_t* CDP_CenApp_Init(void);
CDP_CenAppCSFlag_t CDP_CenApp_GetCSFlag(void);
#endif
