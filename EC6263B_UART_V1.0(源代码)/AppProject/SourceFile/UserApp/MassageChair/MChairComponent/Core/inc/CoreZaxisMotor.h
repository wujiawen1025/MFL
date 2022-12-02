/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: CoreZaxisMotor.h                                                                                                         
**
**    功能描述: Z轴马达(伸缩(强弱)马达)驱动。
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
#ifndef  _CORE_ZAXIS_MOTOR_H
#define  _CORE_ZAXIS_MOTOR_H


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "MotorCommon.h"


/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
#define  ZMOTOR_BACK_LIMIT_CODE                           B(01)        /*Z轴后极限位置编码*/
#define  ZMOTOR_FRONT_LIMIT_CODE                          B(10)        /*Z轴前极限位置编码*/

#define  ZMOTOR_POSITION_MIN                              0            /*Z坐标最小值*/
#define  ZMOTOR_POSITION_MAX                              7            /*Z坐标最大值*/

#define  ZMOTOR_COUNT_MIN                                 0            /*位置计数：最小*/
#define  ZMOTOR_COUNT_MAX                                 91           /*位置计数：最大*/
#define  ZMOTOR_COUNT_PER_SEGMENT                         ((ZMOTOR_COUNT_MAX/ZMOTOR_POSITION_MAX)+1) /*每个位置段的计数大小精度*/

#define  ZMOTOR_ACTION_STOP                               0            /*马达动作模式*/
#define  ZMOTOR_ACTION_FRONT                              1           
#define  ZMOTOR_ACTION_BACK                               2 

#define  ZMOTOR_DIRECTION_BACK                            BSP_ZMOTOR_DIRECTION_BACK
#define  ZMOTOR_DIRECTION_FRONT                           BSP_ZMOTOR_DIRECTION_FRONT           

#define  ZMOTOR_SPEEDLEVEL_OFF                            0            /*马达速度 关*/
#define  ZMOTOR_SPEEDLEVEL_MIN                            1            /*马达速度等级*/
#define  ZMOTOR_SPEEDLEVEL_MAX                            5

#define  ZMOTOR_SPEEDLEVEL_DEFAULT                        2            /*默认速度*/
#define  ZMOTOR_FB_DEFAULT                                1            /*默认反馈 开关*/

#define  ZMOTOR_PWM_MIN                                   20           /*马达开始转动所需的最小PWM*/
#define  ZMOTOR_PWM_MAX                                   255          /*马达全速转动的最大PWM*/
#define  ZMOTOR_PWM_FIXED_STEPING_VAL                     1            /*PWM增加固定步进值*/
#define  ZMOTOR_PWMSET_MINI_EXE_PERIODE                   8            /*PWM设置最小执行周期*/

#define  ZMOTOR_RPM_PULSE_NUM                             0x01         /*马达转一圈，转速码盘经过几个脉冲*/
#define  ZMOTOR_RPM_MEASURE_CYCLE_TIME                    (60000000/ZMOTOR_RPM_PULSE_NUM)  /*计数RPM时,测周法使用的时间(60000000us/开孔数)*/
#define  ZMOTOR_RPM_CLEAR_TIME_THRESHOLD                  (1000/ZMOTOR_RPM_PULSE_NUM)      /*转速值清零 门限时间，单位ms*/

#define  ZMOTOR_RPM_MAX                                   3450         /*马达最大转速*/


#define  ZMOTOR_POSITION_CODE_ERR_TIME_THRESHOLD          200          /*位置编码错误     门限时间，单位ms*/
#define  ZMOTOR_POSITION_SENSOR_LOST_TIME_THRESHOLD       8000         /*位置传感器失联   门限时间，单位ms。(注：松下给的资料是8s，由于拷机时发现伸缩经常自动保护，因此这里改为10s)*/
#define  ZMOTOR_RPM_SENSOR_LOST_TIME_THRESHOLD            5000         /*转速传感器失联   门限时间，单位ms*/
#define  ZMOTOR_OVER_CURRENT_TIME_THRESHOLD               3000         /*马达过电流锁定   门限时间，单位ms*/
#define  ZMOTOR_OVER_CURRENT_LEVEL                        0            /*马达过电流锁定电平*/
/*位置计数传感器失联(与转速检测使用同一个传感器，因此故障保护时间必须相同)   门限时间，单位ms*/
#define  ZMOTOR_COUNT_SENSOR_LOST_TIME_THRESHOLD          ZMOTOR_RPM_SENSOR_LOST_TIME_THRESHOLD  

#define  ZMOTOR_DIRECTION_TIME_MS                         4000     /*马达换向时间*/
#define  ZMOTOR_REVERSE_TIME_MS                           4100     /*马达反转时间*/

/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  Z马达 控制与状态标识                                                                                  
************************************************************************************************************************
*/
typedef  union 
{
  struct
  {
    /*Work表示马达逻辑上有在工作(即有相应的动作需求，且不管Pause是否有效)，
      而Run表示物理上的工作，Pause有效时，马达不Run，Pause无效时，有相应的动作需求的话，马达Run*/
    uint8_t    Work                   :1;    /*工作中*/
    uint8_t    Pause                  :5;    /*暂停*/
    uint8_t    FeedBackEn             :1;    /*反馈功能使能*/
    uint8_t    Run                    :1;    /*运行*/
    uint8_t    Direction              :1;    /*方向*/
    uint8_t    ReachFrontLimt         :1;    /*已达前方向限定*/
    uint8_t    ReachBackLimt          :1;    /*已达后方向限定*/

    uint8_t    PositionCodeFault      :1;    /*位置编码故障，出现不应该存在的编码*/
    uint8_t    PositionSensorFault    :1;    /*位置传感器故障*/
    uint8_t    RPMSensorFault         :1;    /*转速传感器故障*/
    uint8_t    OverCurrentFault       :1;    /*过电流故障*/
    uint8_t    CountFault             :1;    /*计数故障，检测不到计数变化*/
    uint8_t    Locked                 :1;    /*被锁，不能再工作*/
    uint8_t    OvershootSpeedLimitCur :1;    /*过冲速度限制保护 当前*/
    uint8_t    OvershootSpeedLimitHis :1;    /*过冲速度限制保护 历史*/

    uint8_t    PositionResetOK        :1;    /*位置复位完成*/
  }Bit;

  uint32_t All;
}ZMotorCSFlag_t;  /*Control State Flag  控制与状态标识*/

/*
************************************************************************************************************************
* 类型定义 :  Z马达操作相关数据结构                                                                    
************************************************************************************************************************
*/
typedef struct
{
  ZMotorCSFlag_t            CSFlag;                  /*控制与状态标识*/

  uint8_t                   PositionRealVal;         /*位置 实际值*/
  uint8_t                   PositionSetVal;          /*位置 设置值*/

  uint16_t                  FrontRunTimeMs;          /*向下运行时间，单位1ms*/
  uint16_t                  BackRunTimeMs;           /*向上运行时间，单位1ms*/
  uint32_t                  RunTimeMs;               /*马达运行时间，单位1ms*/
  uint16_t                  OverCurrentTimeMs;       /*过电流锁定时间，单位1ms*/
  uint16_t                  StateCtrlTimeMs;         /*状态控制时间，单位1ms*/
  uint16_t                  RollbackTimeMs;          /*回退时间，单位1ms*/

  uint8_t                   Action;                  /*马达动作*/
  uint8_t                   SpeedLevel;              /*速度等级*/
  uint16_t                  RPMSetVal;               /*转速 设置值*/
  uint16_t                  RPMRealVal;              /*转速 实际值*/
  uint8_t                   FBWorkState;             /*反馈的工作状态*/
  uint8_t                   NOFBWorkState;           /*无反馈的工作状态*/
  int16_t                   PWMFinalSetVal;          /*PWM最终设置值*/
  int16_t                   PWMPreSetVal;            /*PWM 预设值*/
  int16_t                   PWMCompensationVal;      /*PWM 补偿值*/

  MotorRPMMointor_t         RPMMointor;	             /*转速 监测器*/
  MotorPositionMonitor_t    PositionMonitor;         /*位置 监测器*/

}ZMotor_t;


/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
/*初始化--------------------------------------*/
ZMotor_t*  ZMotor_Init(void);


/*周期执行--------------------------------------*/
void ZMotor_PositionIOCheck(Ticker_t ExePeriod);
void ZMotor_OverCurrentIOCheck(Ticker_t ExePeriod);
void ZMotor_RPMCheckHandle(Ticker_t ExePeriod);
void ZMotor_PWMSetValHandle(Ticker_t ExePeriod);
void ZMotor_PositionHandle(Ticker_t ExePeriod);
void ZMotor_ActionHandle(Ticker_t ExePeriod);


/* 对外的接口， 即 其他模块 可对 该模块执行的 控制操作-----------------------------
 * 注意：X、Y、Z 三个马达 只提供 有限的几个接口API。
 *       X马达比较特殊，所以单独开放揉捏动作的设置函数。
 */
void ZMotor_PauseOn(void);
void ZMotor_PauseOff(void);

uint8_t ZMotor_GetPosition(void);
void ZMotor_SetPosition(uint8_t Position, uint8_t SpeedLevel, uint8_t FBEn);/*设置坐标轴位置*/

ZMotorCSFlag_t ZMotor_GetCSFlag(void);
void ZMotor_ResetPosition(void);

#endif

