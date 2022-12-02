/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: CoreBackSacn.h                                                                                                         
**
**    功能描述: 机芯背部扫描
**
**    公    司：蒙发利电子
**
**    项目名称：
**
**    平台信息：
**
**    作    者：Hzy
**
**    其他说明: 人体背部位置点逻辑划分：
**              最高点PY00  (哑门穴附近)
**              肩部  PY04
**              腰底  PY24  (腰阳关穴附近)，将从哑门穴附近到腰底位置等分24段(PY00 ~ PY24)
**              剩下的根据导轨的长度不同而不同。
**
**    修改记录:  --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/
#ifndef  _CORE_BACKSCAN_H
#define  _CORE_BACKSCAN_H


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "MotorCommon.h"
#include "CoreXaxisMotor.h"
#include "CoreYaxisMotor.h"
#include "CoreZaxisMotor.h"
#include "CoreTCSMotor.h"


/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/                                      
#define  SHOULDER_ADJUST_NONE              0                            /*肩部无调节*/
#define  SHOULDER_ADJUST_DOWN              1                            /*肩部向下调节*/
#define  SHOULDER_ADJUST_UP                2                            /*肩部向上调节*/
#define  SHOULDER_ADJUST_FINISH            3                            /*肩部调节完成*/

#define  SHOULDER_ADJUST_KEY_L             0                            /*肩部调节 按键 长按*/
#define  SHOULDER_ADJUST_KEY_S             1                            /*肩部调节 按键 短按*/
#define  SHOULDER_ADJUST_KEY_LSMODE        SHOULDER_ADJUST_KEY_L        /*肩部调节 按键 长短按模式*/


#define  SHOULDER_LIMIT_NONE               0                            /*肩部处于可调节范围*/
#define  SHOULDER_LIMIT_UP                 1                            /*肩部处于上极限，不可向上调节*/
#define  SHOULDER_LIMIT_DOWN               2                            /*肩部处于下极限，不可向下调节*/


#define  PZCURVE                           0xC0                         /*跟随曲线*/
#define  PZDEC1                            (PZCURVE - 1)                /*在曲线的基础上 回缩1档*/
#define  PZDEC2                            (PZCURVE - 2)
#define  PZDEC3                            (PZCURVE - 3)
#define  PZDEC4                            (PZCURVE - 4)
#define  PZDEC5                            (PZCURVE - 5)
#define  PZDEC6                            (PZCURVE - 6)
#define  PZDEC7                            (PZCURVE - 7)
#define  PZDEC8                            (PZCURVE - 8)
#define  PZDEC9                            (PZCURVE - 9)
#define  PZDEC10                           (PZCURVE - 10)
#define  PZDEC11                           (PZCURVE - 11)
#define  PZDEC12                           (PZCURVE - 12)
#define  PZDEC13                           (PZCURVE - 13)
#define  PZDEC14                           (PZCURVE - 14)
#define  PZDEC15                           (PZCURVE - 15)
#define  PZADD1                            (PZCURVE + 1)                /*在曲线的基础上 伸出1档*/
#define  PZADD2                            (PZCURVE + 2)
#define  PZADD3                            (PZCURVE + 3)
#define  PZADD4                            (PZCURVE + 4)
#define  PZADD5                            (PZCURVE + 5)
#define  PZADD6                            (PZCURVE + 6)
#define  PZADD7                            (PZCURVE + 7)
#define  PZADD8                            (PZCURVE + 8)
#define  PZADD9                            (PZCURVE + 9)
#define  PZADD10                           (PZCURVE + 10)
#define  PZADD11                           (PZCURVE + 11)
#define  PZADD12                           (PZCURVE + 12)
#define  PZADD13                           (PZCURVE + 13)
#define  PZADD14                           (PZCURVE + 14)
#define  PZADD15                           (PZCURVE + 15)


#define  CURVE_NUM_MAX                      50

/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  背部扫描控制与状态标识                                                             
************************************************************************************************************************
*/
typedef union
{
    uint16_t All;
    struct
    {
      uint8_t    Pause                     :5;          /*暂停*/
      uint8_t    Run                       :1;          /*运行*/
      uint8_t    Finish                    :1;          /*完成*/
      uint8_t    ReScanCheck               :1;          /*标识重新检测中*/
      uint8_t    ShoulderAdjustEn          :1;          /*肩部调节使能*/
      uint8_t    ShoulderAdjustOp          :2;          /*肩部调节操作*/
      uint8_t    ShoulderLimitState        :2;          /*肩部位置所处极限状态*/
      uint8_t    UserAdjusting             :1;          /*标识用户在调节肩部位置*/
      uint8_t    NoHumanOnSeat             :1;          /*无人入座*/
      uint8_t    CurveReceived             :1;          /*人体曲线已接收标识*/
    }Bit;
}CoreBackScanCSFlag_t;                                

/*
************************************************************************************************************************
* 类型定义 :  背部扫描相关操作数据结构                                                                        
************************************************************************************************************************
*/
typedef struct
{
  CoreBackScanCSFlag_t      CSFlag;                     /*控制与状态标识*/

  int8_t                    YMFollowZMVal;              /*Y轴更随Z轴的变化补偿值*/

  uint16_t                  MTopPositionCount;          /*按摩最顶位置的物理(映射)计数值*/
  uint16_t                  MShoulderPositionCount;     /*人体检测时检测到的肩部位置的物理(映射)计数值*/
  uint8_t                   MShoulderPosition;          /*人体检测时检测到的肩部位置的物理(映射)*/
  uint8_t                   MShoulderPositionLowest;    /*最低物理肩部位置*/

  uint8_t                   PositionMax;                /*Y轴逻辑总位置最大值(背部点位分段)*/
  uint8_t                   ShoulderAboveCountPerSeg;   /*肩以上每个逻辑分段包含的位置计数值*/
  uint8_t                   ShoulderBelowCountPerSeg;   /*肩以下每个逻辑分段包含的位置计数值*/

  uint8_t                   MPositionMax;               /*Y轴物理(映射)总位置最大值*/
  uint16_t                  MPositionCountMax;          /*Y轴物理(映射)总行程计数最大值*/
  uint8_t                   MCountPerSeg;               /*Y轴物理(映射)每个分段包含的位置计数值*/
  
  uint8_t                   PWMStatCountNoLoad;         /*空载时 PWM统计次数 */
  uint16_t                  PWMSumNoLoad;               /*空载时 PWM总值 */
  uint16_t                  ShoulderPWMThreshold;       /*肩部位置PWM门限值*/
  uint8_t                   ReachShoulderThPWMCount;    /*达到肩位置的PWM输出阀值次数*/

  uint8_t                   ScanStep;                   /*扫描步骤*/
  uint16_t                  ShoudlerAdjustValidTime;    /*肩部位置调节可用时间*/
  uint32_t                  ScanStepTimeMs;             /*扫描步骤时间*/
  
  uint8_t                   CurveTab[CURVE_NUM_MAX];    /*人体曲线表*/
  
}CoreBackScan_t;


/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
void Core_BackScanSetPositionCtrPara(uint16_t MPositionCountMax, uint8_t MPositionMax, uint8_t PositionMax);
void Core_BackScanSetRunSw(uint8_t Sw);
void Core_BackScanSetReScanCheckSw(uint8_t Sw);
uint8_t Core_BackScanSetShoulderAdjustOp(uint8_t Op, uint8_t KeyLS);
void Core_BackScanSetCurveCheckSw(uint8_t Sw);
void Core_BackScanPauseOn(void);
void Core_BackScanPauseOff(void);
CoreBackScanCSFlag_t Core_BackScanGetCSFlag(void);
void Core_BackScanHandle(Ticker_t ExePeriod);
uint8_t Core_BackScanYMDynFollowZM(uint8_t ZPosition);
uint8_t Core_BackScanYMapToYM(uint8_t YPosition);
uint8_t Core_BackScanYMMapToY(uint8_t YMPosition);
uint8_t Core_BackScanZMapToZM(uint8_t ZPosition, uint8_t YPosition);
uint8_t Core_BackScanZMMapToZ(uint8_t ZMPosition);

uint16_t Core_BackScanGetYCount(void);
#endif
