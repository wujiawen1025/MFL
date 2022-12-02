/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: CoreXaxisMotor.h                                                                                                         
**
**    功能描述: X轴马达(调宽(揉捏)马达)驱动。
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
#ifndef  _CORE_XAXIS_MOTOR_H
#define  _CORE_XAXIS_MOTOR_H


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
#define  XMOTOR_POSITION_MIN                               0           /*位置最小值*/
#define  XMOTOR_POSITION_MAX                               2           /*位置最大值*/

#define  XMOTOR_ACTION_STOP                                0           /*马达动作模式:停*/
#define  XMOTOR_ACTION_KNEAD_INWARD                        1           /*马达动作模式:内揉*/
#define  XMOTOR_ACTION_KNEAD_OUTWARD                       2           /*马达动作模式:外柔*/
#define  XMOTOR_ACTION_LEFT                                3           /*马达动作模式:左运行*/
#define  XMOTOR_ACTION_RIGHT                               4           /*马达动作模式:右运行*/

#define  XMOTOR_DIRECTION_LEFT                             BSP_XMOTOR_DIRECTION_LEFT          
#define  XMOTOR_DIRECTION_RIGHT                            BSP_XMOTOR_DIRECTION_RIGHT
#define  XDL                                               XMOTOR_DIRECTION_LEFT     /*X马达运行方向 左*/
#define  XDR                                               XMOTOR_DIRECTION_RIGHT    /*X马达运行方向 右*/  

#define  XMOTOR_SPEEDLEVEL_OFF                             0           /*马达速度 关*/
#define  XMOTOR_SPEEDLEVEL_MIN                             1           /*马达速度等级*/
#define  XMOTOR_SPEEDLEVEL_MAX                             5

#define  XMOTOR_SPEEDLEVEL_DEFAULT                         3           /*默认速度*/
#define  XMOTOR_FB_DEFAULT                                 1           /*默认反馈 开关*/


#define  XMOTOR_PWM_MIN                                    20          /*马达开始转动所需的最小PWM*/
#define  XMOTOR_PWM_MAX                                    255         /*马达全速转动的最大PWM*/
#define  XMOTOR_PWM_FIXED_STEPING_VAL                      1
#define  XMOTOR_PWMSET_MINI_EXE_PERIODE                    7           /*PWM设置最小执行周期*/

#define  XMOTOR_RPM_PULSE_NUM                              1           /*马达转一圈，转速码盘经过几个脉冲*/
#define  XMOTOR_RPM_MEASURE_CYCLE_TIME                     (60000000/XMOTOR_RPM_PULSE_NUM)  /*计数RPM时,测周法使用的时间(60000000us/开孔数)*/
#define  XMOTOR_RPM_CLEAR_TIME_THRESHOLD                   (1000/XMOTOR_RPM_PULSE_NUM)      /*转速值清零 门限时间，单位ms*/

#define  XMOTOR_RPM_MAX                                    2700        /*马达最大转速*/


#define  XMOTOR_POSITION_CODE_ERR_TIME_THRESHOLD           300         /*位置编码错误     门限时间，单位ms*/
#define  XMOTOR_POSITION_SENSOR_LOST_TIME_THRESHOLD        8000        /*位置传感器失联   门限时间，单位ms*/
#define  XMOTOR_RPM_SENSOR_LOST_TIME_THRESHOLD             5000        /*转速传感器失联   门限时间，单位ms*/
#define  XMOTOR_OVER_CURRENT_TIME_THRESHOLD                3000        /*马达过电流锁定   门限时间，单位ms*/
#define  XMOTOR_OVER_CURRENT_LEVEL                         0           /*马达过电流锁定电平*/


#define  XMOTOR_DIRECTION_TIME_MS                          4000         /*马达换向时间*/
#define  XMOTOR_REVERSE_TIME_MS                            4100         /*马达反转时间*/


/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  X马达 控制与状态标识                                                                                      
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
    uint8_t    ReachLeftLimt          :1;    /*已达左方向限定*/
    uint8_t    ReachRightLimt         :1;    /*已达右方向限定*/

    uint8_t    MoveDirectionCtrl      :1;    /*位置运动的方向控制，默认向右*/

    uint8_t    PositionCodeFault      :1;    /*位置编码故障，出现不应该存在的编码*/
    uint8_t    PositionSensorFault    :1;    /*位置传感器故障*/
    uint8_t    RPMSensorFault         :1;    /*转速传感器故障*/
    uint8_t    OverCurrentFault       :1;    /*过电流故障*/
    uint8_t    Locked                 :1;    /*被锁，不能再工作*/

    uint8_t    PositionResetOK        :1;    /*位置复位完成*/

  }Bit;

  uint32_t All;
}XMotorCSFlag_t;  /*Control State Flag  控制与状态标识*/


/*
************************************************************************************************************************
* 类型定义 :  X马达操作相关数据结构                                                                                   
************************************************************************************************************************
*/
typedef struct
{
  XMotorCSFlag_t            CSFlag;                  /*控制与状态标识*/

  uint8_t                   PositionRealVal;         /*位置 实际值*/
  uint8_t                   PositionSetVal;          /*位置 设置值*/

  uint16_t                  LeftRunTimeMs;           /*向左运行时间，单位1ms*/
  uint16_t                  RightRunTimeMs;          /*向右运行时间，单位1ms*/
  uint32_t                  RunTimeMs;               /*马达运行时间，单位1ms*/
  uint16_t                  OverCurrentTimeMs;       /*过电流锁定时间，单位1ms*/
  uint16_t                  StateCtrlTimeMs;         /*状态控制时间，单位1ms*/

  uint8_t                   Action;                  /*马达动作*/
  uint8_t                   SpeedLevel;              /*速度等级*/
  uint16_t                  RPMSetVal;               /*转速 设置值*/
  uint8_t                   FBWorkState;             /*反馈的工作状态*/
  int16_t                   PWMFinalSetVal;          /*PWM最终设置值*/
  int16_t                   PWMPreSetVal;            /*PWM 预设值*/
  int16_t                   PWMCompensationVal;      /*PWM 补偿值*/

  MotorRPMMointor_t         RPMMointor;              /*转速 监测器*/
  MotorPositionMonitor_t    PositionMonitor;         /*位置 监测器*/

}XMotor_t;



/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
/*初始化--------------------------------------*/
XMotor_t* XMotor_Init(void);


/*周期执行--------------------------------------*/
void XMotor_PositionIOCheck(Ticker_t ExePeriod);
void XMotor_OverCurrentIOCheck(Ticker_t ExePeriod);
void XMotor_RPMCheckHandle(Ticker_t ExePeriod);
void XMotor_PWMSetValHandle(Ticker_t ExePeriod);
void XMotor_PositionHandle(Ticker_t ExePeriod);
void XMotor_ActionHandle(Ticker_t ExePeriod);


/* 对外的接口， 即 其他模块 可对 该模块执行的 控制操作-----------------------------
 * 注意：X、Y、Z 三个马达 只提供 有限的几个接口API。
 *       X马达比较特殊，所以单独开放揉捏动作的设置函数。
 */
void XMotor_PauseOn(void);         /*暂停*/
void XMotor_PauseOff(void);        /*解除暂停*/

uint8_t XMotor_GetPosition(void);  /*获取位置*/
void XMotor_SetPosition(uint8_t Position, uint8_t SpeedLevel, uint8_t FBEn); /*设置位置*/

void XMotor_SetKneadAction(uint8_t Action, uint8_t SpeedLevel, uint8_t FBEn);

void XMotor_SetPositionMoveDirectionCtrl(uint8_t Direction);

XMotorCSFlag_t XMotor_GetCSFlag(void);
void XMotor_ResetPosition(void);

#endif
