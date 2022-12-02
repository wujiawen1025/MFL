/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: LegFlexSpike.h                                                                                                         
**
**    功能描述:小腿缩推杆驱动。
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
#ifndef  _LEGFLEXSPIKE_H
#define  _LEGFLEXSPIKE_H

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp.h"
#include "MotorCommon.h"
#include "CDP.h"


/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
#define  LEGFLEX_UP_EN                                       0
#define  LEGFLEX_DOWN_EN                                     1


#define  LEGFLEXSPIKE_POSITION_MIN                           0            /*下 推杆位置：最小*/
#define  LEGFLEXSPIKE_POSITION_MAX                           6            /*下 推杆位置：最大*/
#define  LEGFLEXSPIKE_COUNT_MIN                              0            /*下 推杆位置计数：最小*/
#define  LEGFLEXSPIKE_COUNT_MAX                              30           /*下 推杆位置计数：最大*/
#define  LEGFLEXSPIKE_COUNT_PER_SEGMENT                      (LEGFLEXSPIKE_COUNT_MAX/LEGFLEXSPIKE_POSITION_MAX) /*每个位置段的计数大小精度*/

#define  ULEGFLEXSPIKE_POSITION_MIN                          0            /*上 推杆位置：最小*/
#define  ULEGFLEXSPIKE_POSITION_MAX                          3            /*上 推杆位置：最大*/
#define  ULEGFLEXSPIKE_COUNT_MIN                             0            /*上 推杆位置计数：最小*/
#define  ULEGFLEXSPIKE_COUNT_MAX                             15           /*上 推杆位置计数：最大*/
#define  ULEGFLEXSPIKE_COUNT_PER_SEGMENT                     (ULEGFLEXSPIKE_COUNT_MAX/ULEGFLEXSPIKE_POSITION_MAX) /*上 每个位置段的计数大小精度*/


#define  LEGFLEXSPIKE_ACTION_STOP                            0            /*推杆动作模式:停*/
#define  LEGFLEXSPIKE_ACTION_SHORTEN                         1            /*推杆动作模式:缩短*/
#define  LEGFLEXSPIKE_ACTION_EXTEND                          2            /*推杆动作模式:伸长*/

#define  LEGFLEXSPIKE_DIRECTION_SHORTEN                      0            /*推杆运行方向*/
#define  LEGFLEXSPIKE_DIRECTION_EXTEND                       1

#define  LEGFLEXSPIKE_POSITION_CODE_ERR_TIME_THRESHOLD       500          /*位置编码错误     门限时间，单位ms*/
#define  LEGFLEXSPIKE_POSITION_SENSOR_LOST_TIME_THRESHOLD    10000        /*位置传感器失联   门限时间，单位ms*/
#define  LEGFLEXSPIKE_COUNT_SENSOR_LOST_TIME_THRESHOLD       5000         /*计数传感器失联   门限时间，单位ms*/

#define  LEGFLEXSPIKE_DIRECTION_TIME_MS                      (50 * 6)     /*推杆换向时间，公差为50ms*/
#define  LEGFLEXSPIKE_REVERSE_TIME_MS                        (50 * 12)    /*推杆反转时间，公差为50ms*/

/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  小腿伸缩推杆 控制与状态标识                                                                                                 
************************************************************************************************************************
*/
typedef  union 
{
  struct
  {
    uint8_t    Work                            :1;    /*工作中*/
    uint8_t    Pause                           :4;    /*暂停*/
    uint8_t    Run                             :1;    /*运行*/
    uint8_t    Direction                       :1;    /*方向*/
    uint8_t    ReachExtendLimt                 :1;    /*已达最长限定*/
    uint8_t    ReachShortenLimt                :1;    /*已达最短限定*/
    uint8_t    TouchGround                     :1;    /*触地*/
    uint8_t    TouchFeet                       :1;    /*触脚*/
    uint8_t    PositionCodeFault               :1;    /*位置编码故障，出现不应该存在的编码*/
    uint8_t    ExtendPositionSensorFault       :1;    /*最长限位传感器故障*/
    uint8_t    ShortPositionSensorFault        :1;    /*最短限位传感器故障*/
    uint8_t    CountFault                      :1;    /*计数故障，检测不到计数变化*/
    uint8_t    Locked                          :1;    /*被锁，不能再工作*/
    uint8_t    PositionResetOK                 :1;    /*位置复位完成*/
    
    uint8_t    ULegWork                        :1;    /*工作中*/
    uint8_t    ULegPause                       :4;    /*暂停*/
    uint8_t    ULegRun                         :1;    /*运行*/
    uint8_t    ULegDirection                   :1;    /*方向*/
    uint8_t    ULegReachExtendLimt             :1;    /*已达最长限定*/
    uint8_t    ULegReachShortenLimt            :1;    /*已达最短限定*/
    uint8_t    ULegPositionCodeFault           :1;    /*位置编码故障，出现不应该存在的编码*/
    uint8_t    ULegExtendPositionSensorFault   :1;    /*最长限位传感器故障*/
    uint8_t    ULegShortPositionSensorFault    :1;    /*最短限位传感器故障*/
    uint8_t    ULegCountFault                  :1;    /*计数故障，检测不到计数变化*/
    uint8_t    ULegLocked                      :1;    /*被锁，不能再工作*/
    uint8_t    ULegPositionResetOK             :1;    /*位置复位完成*/
  }Bit;

  uint32_t All;
}LegFlexSpikeCSFlag_t;  /*Control State Flag  控制与状态标识*/

/*
************************************************************************************************************************
* 类型定义 :  小腿伸缩推杆操作相关数据结构                                                                                              
************************************************************************************************************************
*/
typedef struct
{
  LegFlexSpikeCSFlag_t      CSFlag;                   /*控制与状态标识*/

  uint32_t                  RunTimeMs;                /*推杆运行时间，单位1ms*/
  uint16_t                  StateCtrlTimeMs;          /*状态控制时间，单位1ms*/
  uint8_t                   Action;                   /*推杆动作*/
  uint8_t                   PositionRealVal;          /*位置 实际值*/
  uint8_t                   PositionSetVal;           /*位置 设置值*/
  MotorPositionMonitor_t    PositionMonitor;          /*位置 监测器*/
  
  uint32_t                  ULegRunTimeMs;            /*推杆运行时间，单位1ms*/
  uint16_t                  ULegStateCtrlTimeMs;      /*状态控制时间，单位1ms*/
  uint8_t                   ULegAction;               /*推杆动作*/
  uint8_t                   ULegPositionRealVal;      /*位置 实际值*/
  uint8_t                   ULegPositionSetVal;       /*位置 设置值*/
  MotorPositionMonitor_t    ULegPositionMonitor;      /*位置 监测器*/
  
  CDP_DataFormat0x4B_t    SetQry0x4B;
  
}LegFlexSpike_t;


/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/

/*初始化--------------------------------------*/
LegFlexSpike_t* LegFlexSpike_Init(void);


/*周期执行--------------------------------------*/
void LegFlexSpike_IOCheck(Ticker_t ExePeriod);
void LegFlexSpike_ActionHandle(Ticker_t ExePeriod);


/* 对外的接口， 即 其他模块 可对 该模块执行的 控制操作*/
void LegFlexSpike_PauseOn(void);
void LegFlexSpike_PauseOff(void);

uint8_t LegFlexSpike_GetPosition(void);
void LegFlexSpike_SetPosition(uint8_t Position);

void LegFlexSpike_PositionHandle(Ticker_t ExePeriod);
void LegFlexSpike_SetAction(uint8_t Action);

LegFlexSpikeCSFlag_t LegFlexSpike_GetCSFlag(void);


//==========================================================
void LegFlexSpike_SetULegAction(uint8_t Action);
uint8_t LegFlexSpike_GetULegPosition(void);
void LegFlexSpike_SetULegPosition(uint8_t Position);

#endif
