/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: Roller.h                                                                                                         
**
**    功能描述: 滚轮驱动。
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
#ifndef  _ROLLER_H
#define  _ROLLER_H


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
#define  ROLLER_FEET_EN                                    1
#define  ROLLER_CALVES_EN                                  1

#define  FEET_ROLLER_POSITION_MIN                          0           /*推杆位置：最小*/
#define  FEET_ROLLER_POSITION_MAX                          8           /*推杆位置：最大*/

#define  FEET_ROLLER_COUNT_MIN                             0           /*推杆位置计数：最小*/
#define  FEET_ROLLER_COUNT_MAX                             92          /*推杆位置计数：最大*/
#define  FEET_ROLLER_COUNT_PER_SEGMENT                     (FEET_ROLLER_COUNT_MAX/FEET_ROLLER_POSITION_MAX) /*每个位置段的计数大小精度*/


#define  FEET_ROLLER_DIRECTION_BACK                        0            /*脚滚方向：向后*/  
#define  FEET_ROLLER_DIRECTION_FRONT                       1            /*脚滚方向：向前*/

#define  FEETROLLER_DIRECTION_TIME_MS                      (50 * 10)    /*换向时间，公差为50ms*/
#define  FEETROLLER_REVERSE_TIME_MS                        (50 * 20)    /*反转时间，公差为50ms*/

/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  滚轮配合的充气控制                                                                
************************************************************************************************************************
*/
typedef union 
{
  uint8_t    All;
  __packed struct
  {
    uint8_t            FeetSide      :1;     /*脚侧*/
    uint8_t            Ankle         :1;     /*脚踝*/
    uint8_t            Gas3          :1;    
    uint8_t            Gas4          :1;    
    uint8_t            CalvesSide    :1;     /*腿侧*/
    uint8_t            CalvesBot     :1;     /*腿底*/
    uint8_t            Gas7          :1;  
    uint8_t            Pump          :1;     /*气泵*/  
  }Bit;
}RollerGasPart_t;  

/*
************************************************************************************************************************
* 类型定义 :  滚轮动作表格项                                                                            
************************************************************************************************************************
*/
typedef struct
{
  RollerGasPart_t        GasPart;                /*滚轮配合的充气控制*/

  uint8_t                PWM;                    /*强度, 单位百分比*/
  uint8_t                Direction;              /*滚动方向*/
  uint8_t                StartPosition;          /*滚动起始位置*/
  uint8_t                EndPosition;            /*滚动结束位置*/
                                       
  uint16_t               OnTime;                 /*滚动时间 ms*/
  uint16_t               OffTime;                /*停滚时间 ms*/

  uint8_t                Repeat;                 /*重复次数*/
}RollerTabItem_t;


/*
************************************************************************************************************************
* 类型定义 :  滚轮动作   
* 注：每个部位的功能占用3位，即可用值为0~7  
************************************************************************************************************************
*/
typedef union
{
  uint16_t All;
  struct
  {
    uint8_t       Feet         :3;
    uint8_t       Calves       :3;
  }Bit;   
}RollerAction_t; 

/*
************************************************************************************************************************
* 类型定义 :  滚轮 控制与状态标识                                                                         
************************************************************************************************************************
*/
typedef  union 
{
  struct
  {
    uint8_t            FeetWork                   :1;    /*工作中*/
    uint8_t            FeetPause                  :5;    /*暂停*/
    uint8_t            FeetRun                    :1;    /*运行*/
    uint8_t            FeetDirection              :1;    /*方向*/
    uint8_t            FeetInitPositionIO         :1;    /*脚滚初始位置IO检测*/
    uint8_t            KeepAtInitPosition         :1;    /*保持在初始位置*/

    uint8_t            CalvesWork                 :1;    /*工作中*/
    uint8_t            CalvesPause                :5;    /*暂停*/
    uint8_t            CalvesRun                  :1;    /*运行*/
    uint8_t            CalvesDirection            :1;    /*方向*/
  }Bit;

  uint16_t All;
}RollerCSFlag_t;  /*Control State Flag  控制与状态标识*/

/*
************************************************************************************************************************
* 类型定义 :  滚轮操作相关数据结构                                                                        
************************************************************************************************************************
*/
typedef struct
{
  RollerCSFlag_t          CSFlag;                /*控制与状态标识*/

  #if(1==ROLLER_FEET_EN)
  uint8_t                 FeetPositionSetp;      /*脚滚 位置 步骤*/  
  uint8_t                 FeetSetpNum;           /*脚滚 步骤数*/  
  uint16_t                FeetSetpTime;          /*脚滚 步骤时间*/ 
  uint8_t                 FeetSetpRepeat;        /*脚滚 步骤重复次数*/ 
  uint16_t                FeetPWM;               /*脚滚PWM输出值*/
  
  uint16_t                FeetCount;             /*脚滚计数值*/
  uint16_t                FeetPosition;          /*脚滚位置*/
  CDP_DataFormat0x49_t    SetQry0x49;
  #endif

  #if(1==ROLLER_CALVES_EN)
  uint8_t                 CalvesSetpNum;         /*腿滚 步骤数*/  
  uint16_t                CalvesSetpTime;        /*腿滚 步骤时间*/ 
  uint8_t                 CalvesSetpRepeat;      /*腿滚 步骤重复次数*/ 
  uint16_t                CalvesPWM;             /*腿滚PWM输出值*/
  uint16_t                CalvesCount;           /*腿滚计数值*/
  #endif
}Roller_t;


/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
/*初始化--------------------------------------*/
Roller_t*  Roller_Init(void);


/*周期执行--------------------------------------*/
void Roller_Handle(void);


/* 对外的接口， 即 其他模块 可对 该模块执行的 控制操作*/
void Roller_SetFeetRollerWorkState(uint8_t  TureFalse);

void Roller_FeetRollerPauseOn(void);
void Roller_FeetRollerPauseOff(void);
void Roller_FeetRollerResetStep(void);

void Roller_SetCalvesRollerWorkState(uint8_t  TureFalse);

void Roller_CalvesRollerPauseOn(void);
void Roller_CalvesRollerPauseOff(void);
void Roller_CalvesRollerResetStep(void);

RollerCSFlag_t Roller_GetCSFlag(void);
RollerGasPart_t Roller_GetFeetGas(void);
void Roller_SetFeetRollerKeepAtInitPosition(void);
void Roller_ClrFeetRollerKeepAtInitPosition(void);
#endif
