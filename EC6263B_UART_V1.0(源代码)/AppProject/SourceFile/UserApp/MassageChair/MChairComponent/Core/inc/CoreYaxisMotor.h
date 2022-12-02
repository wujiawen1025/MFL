/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: CoreYaxisMotor.h                                                                                                         
**
**    功能描述: Y轴马达(推拿(滚动)马达)驱动。
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
#ifndef  _CORE_YAXIS_MOTOR_H
#define  _CORE_YAXIS_MOTOR_H


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
#define  YMOTOR_POSITION_PARA_BY_MACRO                    1            /*位置参数由宏定义决定*/

#define  YMOTOR_TOP_LIMIT_CODE                            B(01)        /*Y轴上极限位置编码*/
#define  YMOTOR_BOT_LIMIT_CODE                            B(10)        /*Y轴下极限位置编码*/

#define  YMOTOR_POSITION_MIN                              0            /*位置最小值*/
#define  YMOTOR_POSITION_MAX                              73//78//75           /*位置最大值*/

#define  YMOTOR_POSITION_RESET_AT_UNKNOW                  0            /*未知*/
#define  YMOTOR_POSITION_RESET_AT_MIN                     1            /*马达位置复位处：最小处*/
#define  YMOTOR_POSITION_RESET_AT_MAX                     2            /*马达位置复位处：最大处*/
#define  YMOTOR_POSITION_RESET_AT_TOP                     YMOTOR_POSITION_RESET_AT_MIN         
#define  YMOTOR_POSITION_RESET_AT_BOT                     YMOTOR_POSITION_RESET_AT_MAX         
#define  YMOTOR_POSITION_RESET_AT                         YMOTOR_POSITION_RESET_AT_TOP   /*马达位置复位处*/    

#define  YMOTOR_COUNT_MIN                                 0            /*位置计数：最小*/
#define  YMOTOR_COUNT_MAX                                 730//780//740//750          /*位置计数：最大*/
#define  YMOTOR_COUNT_PER_SEGMENT                         (YMOTOR_COUNT_MAX/YMOTOR_POSITION_MAX) /*每个位置段的计数大小精度*/

#define  YMOTOR_ACTION_STOP                               0            /*马达动作模式*/
#define  YMOTOR_ACTION_UP                                 1      
#define  YMOTOR_ACTION_DOWN                               2

#define  YMOTOR_DIRECTION_UP                              BSP_YMOTOR_DIRECTION_UP
#define  YMOTOR_DIRECTION_DOWN                            BSP_YMOTOR_DIRECTION_DOWN

#define  YMOTOR_MOVE_NONE                                 0            /*没在运动*/ 
#define  YMOTOR_MOVE_UP                                   1            /*正在向上运动*/
#define  YMOTOR_MOVE_DOWN                                 2            /*正在向下运动*/

#define  YMOTOR_SPEEDLEVEL_OFF                            0            /*马达速度 关*/
#define  YMOTOR_SPEEDLEVEL_MIN                            1            /*马达速度等级*/
#define  YMOTOR_SPEEDLEVEL_MAX                            7

#define  YMOTOR_SPEEDLEVEL_DEFAULT                        4            /*默认速度*/
#define  YMOTOR_FB_DEFAULT                                1            /*默认反馈 开关*/


#define  YMOTOR_PWM_MIN                                   20           /*马达开始转动所需的最小PWM*/
#define  YMOTOR_PWM_MAX                                   255          /*马达全速转动的最大PWM*/
#define  YMOTOR_PWM_FIXED_STEPING_VAL                     1            /*PWM增加固定步进值*/
#define  YMOTOR_PWMSET_MINI_EXE_PERIODE                   7            /*PWM设置最小执行周期*/

#define  YMOTOR_RPM_PULSE_NUM                             0x01         /*马达转一圈，转速码盘经过几个脉冲*/
#define  YMOTOR_RPM_MEASURE_CYCLE_TIME                    (60000000/YMOTOR_RPM_PULSE_NUM)  /*计数RPM时,测周法使用的时间(60000000us/开孔数)*/
#define  YMOTOR_RPM_CLEAR_TIME_THRESHOLD                  (1000/YMOTOR_RPM_PULSE_NUM)      /*转速值清零 门限时间，单位ms*/

#define  YMOTOR_RPM_MAX                                   3450         /*马达最大转速*/

      
#define  YMOTOR_POSITION_CODE_ERR_TIME_THRESHOLD          300          /*位置编码错误     门限时间，单位ms*/
#define  YMOTOR_POSITION_SENSOR_LOST_TIME_THRESHOLD       10000        /*位置传感器失联   门限时间，单位ms*/
#define  YMOTOR_RPM_SENSOR_LOST_TIME_THRESHOLD            6000         /*转速传感器失联   门限时间，单位ms*/
#define  YMOTOR_OVER_CURRENT_TIME_THRESHOLD               3000         /*马达过电流锁定   门限时间，单位ms*/
#define  YMOTOR_OVER_CURRENT_LEVEL                        0            /*马达过电流锁定电平*/
/*位置计数传感器失联(与转速检测使用同一个传感器，因此故障保护时间必须相同)   门限时间，单位ms*/
#define  YMOTOR_COUNT_SENSOR_LOST_TIME_THRESHOLD          YMOTOR_RPM_SENSOR_LOST_TIME_THRESHOLD  


#define  YMOTOR_DIRECTION_TIME_MS                         4000          /*马达换向时间*/
#define  YMOTOR_REVERSE_TIME_MS                           4150          /*马达反转时间*/


/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  Y马达 控制与状态标识                                                                                  
************************************************************************************************************************
*/
typedef  union 
{
  uint32_t All;
  struct
  {
    /*Work表示马达逻辑上有在工作(即有相应的动作需求，且不管Pause是否有效)，
      而Run表示物理上的工作，Pause有效时，马达不Run，Pause无效时，有相应的动作需求的话，马达Run*/
    uint8_t    Work                   :1;    /*工作中*/
    uint8_t    Pause                  :5;    /*暂停*/
    uint8_t    FeedBackEn             :1;    /*反馈功能使能*/
    uint8_t    Run                    :1;    /*运行*/
    uint8_t    Direction              :1;    /*方向*/
    uint8_t    ReachUpLimt            :1;    /*已达上方向限定*/
    uint8_t    ReachDownLimt          :1;    /*已达下方向限定*/

    uint8_t    PositionCodeFault      :1;    /*位置编码故障，出现不应该存在的编码*/
    uint8_t    PositionSensorFault    :1;    /*位置传感器故障*/
    uint8_t    RPMSensorFault         :1;    /*转速传感器故障*/
    uint8_t    OverCurrentFault       :1;    /*过电流故障*/
    uint8_t    CountFault             :1;    /*计数故障，检测不到计数变化*/
    uint8_t    Locked                 :1;    /*被锁，不能再工作*/

    uint8_t    PositionResetAt        :2;    /*位置复位模式，上复位或下复位*/
    uint8_t    PositionResetOK        :1;    /*位置复位完成*/
    uint8_t    CountNocalibrationSw   :1;    /*极限位置不校正计数开关*/
  }Bit;

}YMotorCSFlag_t;  /*Control State Flag  控制与状态标识*/

/*
************************************************************************************************************************
* 类型定义 :  Y马达操作相关数据结构                                                                               
************************************************************************************************************************
*/
typedef struct
{

  YMotorCSFlag_t            CSFlag;                  /*控制与状态标识*/

  uint8_t                   PositionRealVal;         /*位置 实际值*/
  uint8_t                   PositionSetVal;          /*位置 设置值*/

  uint16_t                  DownRunTimeMs;           /*向下运行时间，单位1ms*/
  uint16_t                  UpRunTimeMs;             /*向上运行时间，单位1ms*/
  uint32_t                  RunTimeMs;               /*马达运行时间，单位1ms*/
  uint16_t                  OverCurrentTimeMs;       /*过电流锁定时间，单位1ms*/
  uint16_t                  StateCtrlTimeMs;         /*状态控制时间，单位1ms*/

  uint8_t                   Action;                  /*马达动作*/
  uint8_t                   SpeedLevel;              /*速度等级*/
  uint16_t                  RPMSetVal;               /*转速 设置值*/
  uint16_t                  RPMRealVal;              /*转速 实际值*/
  uint8_t                   FBWorkState;             /*反馈的工作状态*/
  int16_t                   PWMFinalSetVal;          /*PWM最终设置值*/
  int16_t                   PWMPreSetVal;            /*PWM 预设值*/
  int16_t                   PWMCompensationVal;      /*PWM 补偿值*/

  MotorRPMMointor_t         RPMMointor;              /*转速 监测器*/
  MotorPositionMonitor_t    PositionMonitor;         /*位置 监测器*/

  uint8_t                   TOPLimtCode;             /*Y轴上极限位置编码*/
  uint8_t                   BOTLimtCode;             /*Y轴下极限位置编码*/
  uint8_t                   PositionMax;             /*Y轴总位置最大值*/
  uint8_t                   CountPerSeg;             /*每个分段包含的位置计数值*/
  uint16_t                  PositionCountMax;        /*Y轴总行程计数最大值*/
  
}YMotor_t;


/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
/*初始化--------------------------------------*/
YMotor_t * YMotor_Init(void);


/*周期执行--------------------------------------*/
void YMotor_PositionIOCheck(Ticker_t ExePeriod);
void YMotor_OverCurrentIOCheck(Ticker_t ExePeriod);
void YMotor_RPMCheckHandle(Ticker_t ExePeriod);
void YMotor_PWMSetValHandle(Ticker_t ExePeriod);
void YMotor_PositionHandle(Ticker_t ExePeriod);
void YMotor_ActionHandle(Ticker_t ExePeriod);


/* 对外的接口， 即 其他模块 可对 该模块执行的 控制操作-----------------------------
 * 注意：X、Y、Z 三个马达 只提供 有限的几个接口API。
 *       X马达比较特殊，所以单独开放揉捏动作的设置函数。
 */
void YMotor_PauseOn(void);
void YMotor_PauseOff(void);

uint8_t YMotor_GetPosition(void);
void YMotor_SetPosition(uint8_t Position, uint8_t SpeedLevel, uint8_t FBEn); /*设置坐标轴位置*/
uint8_t YMotor_GetPWMOutPutVal(void);
YMotorCSFlag_t YMotor_GetCSFlag(void);
uint8_t YMotor_GetMoveState(void);
void YMotor_ResetPosition(void);
void YMotor_SetPositionCtrPara(uint8_t LimtCode, uint8_t PositionMax, uint16_t PositionCountMax, uint8_t ResetAt);
void YMotor_SetCountNocalibrationSw(uint8_t Sw);
uint16_t YMotor_GetPositionCount(void);

uint8_t YMotor_IfRunTooSlow(void);
void YMotor_ReCheckRunTooSlow(void);

#endif
