/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: BackSpike.h                                                                                                         
**
**    功能描述: 靠背推杆驱动。
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

#ifndef  _BACKSPIKE_H
#define  _BACKSPIKE_H

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp.h"
#include "MotorCommon.h"


/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
#define  BACKSPIKE_POSITION_MIN                           0            /*推杆位置：最小*/
#define  BACKSPIKE_POSITION_MAX                           15           /*推杆位置：最大*/

#define  BACKSPIKE_COUNT_MIN                              0            /*推杆位置计数：最小*/
#define  BACKSPIKE_COUNT_MAX                              970//973     /*推杆位置计数：最大*/
#define  BACKSPIKE_COUNT_PER_SEGMENT                      (BACKSPIKE_COUNT_MAX/BACKSPIKE_POSITION_MAX) /*每个位置段的计数大小精度*/

#define  BACKSPIKE_POSITION_DETECT_BY_COUNT               0            /*推杆位置检测方式：计数*/
#define  BACKSPIKE_POSITION_DETECT_BY_CODE                1            /*推杆位置检测方式：码盘编码*/
#define  BACKSPIKE_POSITION_DETECT_MODE                   BACKSPIKE_POSITION_DETECT_BY_COUNT  

#define  BACKSPIKE_ACTION_STOP                            0            /*推杆动作模式:停*/
#define  BACKSPIKE_ACTION_UP                              1            /*推杆动作模式:升*/
#define  BACKSPIKE_ACTION_DOWN                            2            /*推杆动作模式:降*/

#define  BACKSPIKE_DIRECTION_UP                           BSP_BACKSPIKE_DIRECTION_UP            /*推杆运行方向*/
#define  BACKSPIKE_DIRECTION_DOWN                         BSP_BACKSPIKE_DIRECTION_DOWN

#define  BACKSPIKE_PWM_MIN                                0            /*马达开始转动所需的最小PWM*/
#define  BACKSPIKE_PWM_MAX                                255          /*马达全速转动的最大PWM*/
#define  BACKSPIKE_PWM_FIXED_STEPING_VAL                  30

#define  BACKSPIKE_POSITION_CODE_ERR_TIME_THRESHOLD       500          /*位置编码错误   门限时间，单位ms*/
#define  BACKSPIKE_POSITION_SENSOR_LOST_TIME_THRESHOLD    30000        /*位置传感器失联 门限时间，单位ms*/
#define  BACKSPIKE_COUNT_SENSOR_LOST_TIME_THRESHOLD       1500         /*计数传感器失联 门限时间，单位ms*/
#define  BACKSPIKE_OVER_CURRENT_TIME_THRESHOLD            3000         /*推杆电流锁定   门限时间，单位ms*/
#define  BACKSPIKE_OVER_CURRENT_LEVEL                     0            /*推杆电流锁定电平*/


#define  BACKSPIKE_DIRECTION_TIME_MS                      (50 * 6)     /*推杆换向时间，公差为50ms*/
#define  BACKSPIKE_REVERSE_TIME_MS                        (50 * 12)    /*推杆反转时间，公差为50ms*/



/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  靠背推杆 控制与状态标识                                                                                                   
************************************************************************************************************************
*/
typedef  union 
{
  struct
  {
    uint8_t    Work                   :1;    /*工作中*/
    uint8_t    Pause                  :5;    /*暂停*/
    uint8_t    Run                    :1;    /*运行*/
    uint8_t    Direction              :1;    /*方向*/
    uint8_t    ReachUpLimt            :1;    /*已达上方向限定*/
    uint8_t    ReachDownLimt          :1;    /*已达下方向限定*/

    uint8_t    PositionCodeFault      :1;    /*位置编码故障，出现不应该存在的编码*/
    uint8_t    PositionSensorFault    :1;    /*位置传感器故障*/
    //uint8_t    RPMSensorFault         :1;    /*转速传感器故障*/
    uint8_t    OverCurrentFault       :1;    /*过电流故障*/
    uint8_t    CountFault             :1;    /*计数故障，检测不到计数变化*/
    uint8_t    CountFaultCheckSw      :1;    /*计数故障检测开关*/
    uint8_t    Locked                 :1;    /*被锁，不能再工作*/

    uint8_t    PositionResetOK        :1;    /*位置复位完成*/
  }Bit;

  uint32_t All;
}BackSpikeCSFlag_t;  /*Control State Flag  控制与状态标识*/

/*
************************************************************************************************************************
* 类型定义 :  靠背推杆操作相关数据结构                                                                                           
************************************************************************************************************************
*/
typedef struct
{
  BackSpikeCSFlag_t         CSFlag;                  /*控制与状态标识*/

  uint32_t                  RunTimeMs;               /*推杆运行时间，单位1ms*/
  uint16_t                  UpRunTimeMs;             /*向上运行时间，单位1ms*/
  uint16_t                  DownRunTimeMs;           /*向下运行时间，单位1ms*/
  uint16_t                  OverCurrentTimeMs;       /*过电流锁定时间，单位1ms*/
  uint16_t                  StateCtrlTimeMs;         /*状态控制时间，单位1ms*/

  uint8_t                   Action;                  /*推杆动作*/
  uint8_t                   PositionRealVal;         /*位置 实际值*/
  uint8_t                   PositionSetVal;          /*位置 设置值*/

  int16_t                   PWMFinalSetVal;          /*PWM最终设置值*/

  MotorPositionMonitor_t    PositionMonitor;         /*位置 监测器*/

}BackSpike_t;



/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
/*初始化--------------------------------------*/
BackSpike_t* BackSpike_Init(void);


/*周期执行--------------------------------------*/
void BackSpike_PositionIOCheck(Ticker_t ExePeriod);
void BackSpike_OverCurrentIOCheck(Ticker_t ExePeriod);
void BackSpike_PositionHandle(Ticker_t ExePeriod);
void BackSpike_ActionHandle(Ticker_t ExePeriod);


/* 对外的接口， 即 其他模块 可对 该模块执行的 控制操作*/
void BackSpike_PauseOn(void);
void BackSpike_PauseOff(void);

uint8_t BackSpike_GetPosition(void);
void BackSpike_SetPosition(uint8_t Position);

BackSpikeCSFlag_t BackSpike_GetCSFlag(void);
void BackSpike_ResetPosition(void);
void BackSpike_SetCountFaultCheckSw(uint8_t Sw);

#endif
