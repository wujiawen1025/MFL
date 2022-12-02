/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: CoreTCSMotor.h                                                                                                         
**
**    功能描述: 敲击马达驱动。
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
#ifndef  _CORE_TCS_MOTOR_H
#define  _CORE_TCS_MOTOR_H


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
#define  TCSMOTOR_ACTION_STOP                             0            /*马达动作模式*/
#define  TCSMOTOR_ACTION_CLAP1                            1            /*拍打1*/ 
#define  TCSMOTOR_ACTION_CLAP2                            2            /*拍打2*/ 
#define  TCSMOTOR_ACTION_SHIA1                            3            /*指压1*/ 
#define  TCSMOTOR_ACTION_SHIA2                            4            /*指压2*/ 
#define  TCSMOTOR_ACTION_LTAP                             5            /*轻敲击*/ 
#define  TCSMOTOR_ACTION_TAP                              6            /*敲击*/ 
#define  TCSMOTOR_ACTION_NO_FB_LTAP                       7            /*无速度反馈的轻敲击*/      
#define  TCSMOTOR_ACTION_NO_FB_TAP                        8            /*无速度反馈的敲击*/      

#define  TCSMOTOR_SPEEDLEVEL_OFF                          0            /*马达速度 关*/
#define  TCSMOTOR_SPEEDLEVEL_MIN                          1            /*马达速度等级*/
#define  TCSMOTOR_SPEEDLEVEL_MAX                          5

#define  TCSMOTOR_SPEEDLEVEL_DEFAULT                      1            /*默认速度*/
#define  TCSMOTOR_FB_DEFAULT                              1            /*默认反馈 开关*/


#define  TCSMOTOR_PWM_MIN                                 25           /*马达开始转动所需的最小PWM*/
#define  TCSMOTOR_PWM_MAX                                 255          /*马达全速转动的最大PWM*/
#define  TCSMOTOR_PWM_FIXED_STEPING_VAL                   1
#define  TCSMOTOR_PWMSET_MINI_EXE_PERIODE                 7            /*PWM设置最小执行周期*/

#define  TCSMOTOR_RPM_PULSE_NUM                           0x04         /*马达转一圈，转速码盘经过几个脉冲*/
#define  TCSMOTOR_RPM_MEASURE_CYCLE_TIME                  (60000000/TCSMOTOR_RPM_PULSE_NUM)  /*计数RPM时,测周法使用的时间(60000000us/开孔数)*/
#define  TCSMOTOR_RPM_CLEAR_TIME_THRESHOLD                (1000/TCSMOTOR_RPM_PULSE_NUM-100)  /*转速值清零 门限时间，单位ms。实测大负载下，敲击较容易卡停，因此-100以缩短检测到卡停的时间*/

#define  TCSMOTOR_RPM_MAX                                 3450         /*马达最大转速*/

#define  TCSMOTOR_RPM_SENSOR_LOST_TIME_THRESHOLD          9000//4500   /*转速传感器失联 门限时间，单位ms。 注意：松下资料给的是4.5s,但我们手动下伸缩可最强档，在某些位置下比较容易堵，因此将时间改为9s*/
#define  TCSMOTOR_OVER_CURRENT_TIME_THRESHOLD             3000         /*马达电流锁定   门限时间，单位ms*/
#define  TCSMOTOR_OVER_CURRENT_LEVEL                      0            /*马达电流锁定电平*/

#define  TCSMOTOR_DIRECTION_TIME_MS                       100          /*马达换向时间*/


/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  周期性敲击                                                                                 
************************************************************************************************************************
*/
typedef struct
{
  uint8_t      PWM;      
  uint16_t     Time_ms;   /*时间，单位ms*/
  uint8_t      Repeat;    /*重复次数*/
}TCSMotor_PeriodTap_t;

/*
************************************************************************************************************************
* 类型定义 :  敲击马达 控制与状态标识                                                                                 
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

    uint8_t    RPMSensorFault         :1;    /*转速传感器故障*/
    uint8_t    OverCurrentFault       :1;    /*过电流故障*/
    uint8_t    Locked                 :1;    /*被锁，不能再工作*/

    uint8_t    PeriodTCSPWMOn         :1;    /*TCS 的PWM 起作用*/

  }Bit;

  uint32_t All;
}TCSMotorCSFlag_t;  /*Control State Flag  控制与状态标识*/

/*
************************************************************************************************************************
* 类型定义 :  敲击马达操作相关数据结构                                                                              
************************************************************************************************************************
*/
typedef struct
{
  TCSMotorCSFlag_t          CSFlag;                  /*控制与状态标识*/

  uint32_t                  RunTimeMs;               /*马达运行时间，单位1ms*/
  uint16_t                  OverCurrentTimeMs;       /*过电流锁定时间，单位1ms*/
  uint16_t                  StateCtrlTimeMs;         /*状态控制时间，单位1ms*/

  uint8_t                   Action;                  /*马达动作*/
  uint8_t                   ActionStep;              /*动作 步骤*/
  uint8_t                   ActionStepRepeat;        /*动作 步骤重复次数*/
  uint16_t                  ActionStepTime;          /*动作 步骤时间*/

  uint8_t                   SpeedLevel;              /*速度等级*/
  uint16_t                  RPMSetVal;               /*转速 设置值*/
  uint16_t                  RPMRealVal;              /*转速 实际值*/
  uint8_t                   FBWorkState;             /*反馈的工作状态*/
  int16_t                   PWMFinalSetVal;          /*PWM最终设置值*/
  int16_t                   PWMPreSetVal;            /*PWM 预设值*/
  int16_t                   PWMCompensationVal;      /*PWM 补偿值*/

  uint8_t                   LightTapRealSpeedLevel;  /*轻打敲击的实际速度等级*/

  MotorRPMMointor_t         RPMMointor;	             /*转速 监测器*/

}TCSMotor_t;



/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
/*初始化--------------------------------------*/
TCSMotor_t*  TCSMotor_Init(void);


/*周期执行--------------------------------------*/
void TCSMotor_OverCurrentIOCheck(Ticker_t ExePeriod);
void TCSMotor_RPMCheckHandle(Ticker_t ExePeriod);
void TCSMotor_PWMSetValHandle(Ticker_t ExePeriod);
void TCSMotor_ActionHandle(Ticker_t ExePeriod);

void TCSMotor_RPMCheckHandle(Ticker_t ExePeriod);


/* 对外的接口， 即 其他模块 可对 该模块执行的 控制操作*/
void TCSMotor_PauseOn(void);
void TCSMotor_PauseOff(void);

//void TCSMotor_SetAction(uint8_t Action, uint8_t SpeedLevel, uint8_t FBEn);
void TCSMotor_SetAction(uint8_t Action, uint8_t SpeedLevel);

TCSMotorCSFlag_t TCSMotor_GetCSFlag(void);
uint16_t TCSMotor_GetCurRPM(void);

#endif
