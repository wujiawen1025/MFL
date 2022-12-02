/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: Spike.h                                                                                                         
**
**    功能描述:	推杆驱动。管理 靠背、小腿、小腿伸缩、零重力 等推杆
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
#ifndef  _SPIKE_H
#define  _SPIKE_H


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "MotorCommon.h"
#include "BackSpike.h"
#include "ZeroSpike.h"
#include "FeetSpike.h"
#include "LegFlexSpike.h"


/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
/*将下层模块常用的宏定义，以更好的命名方式展现给同层和上层模块===========================*/
#define  PBACK_MIN                                  BACKSPIKE_POSITION_MIN
#define  PBACK_MAX                                  BACKSPIKE_POSITION_MAX
#define  PFEET_MIN                                  FEETSPIKE_POSITION_MIN
#define  PFEET_MAX                                  FEETSPIKE_POSITION_MAX
#define  PZERO_MIN                                  ZEROSPIKE_POSITION_MIN
#define  PZERO_MAX                                  ZEROSPIKE_POSITION_MAX
#define  PLEGFLEX_MIN                               LEGFLEXSPIKE_POSITION_MIN
#define  PLEGFLEX_MAX                               LEGFLEXSPIKE_POSITION_MAX
#define  PULEGFLEX_MIN                              ULEGFLEXSPIKE_POSITION_MIN
#define  PULEGFLEX_MAX                              ULEGFLEXSPIKE_POSITION_MAX


/*推杆 按键触发模式 长按 短按==========================================================*/
#define  SPIKE_KEY_MODE_LONG                        0                      /*推杆为长按*/
#define  SPIKE_KEY_MODE_SHORT                       1                      /*推杆为短按*/
#define  SPIKE_KEY_MODE                             SPIKE_KEY_MODE_SHORT


/*推杆 空间位置 相关宏定义==========================================================*/
#define  PBACK_HOME_ANGLE                           PBACK00                /*复位角度*/
#define  PFEET_HOME_ANGLE                           PFEET00                /*复位角度*/

#define  PBACK_USER_ANGLE                           PBACK00                /*开机角度*/
#define  PFEET_USER_ANGLE                           PFEET03                /*开机角度*/
#define  PZERO_USER_ANGLE                           PZERO04                /*开机角度*/

#define  PBACK_EXE_ANGLE                            PBACK09                /*执行程序角度*/
#define  PFEET_EXE_ANGLE                            PFEET12                /*执行程序角度*/
#define  PZERO_EXE_ANGLE                            PZERO04                /*执行程序角度*/

#define  PBACK_ZERO1_ANGLE                          PBACK09                /*零重力1角度*/
#define  PFEET_ZERO1_ANGLE                          PFEET12                /*零重力1角度*/
#define  PZERO_ZERO1_ANGLE                          PKEEP                  /*零重力1角度*/

#define  PBACK_ZERO2_ANGLE                          PBACK15                /*零重力2角度*/
#define  PFEET_ZERO2_ANGLE                          PFEET15                /*零重力2角度*/
#define  PZERO_ZERO2_ANGLE                          PKEEP                  /*零重力2角度*/

#define  PBACK_LEG_LEN_DETECT_ANGLE                 PBACK04                /*启动腿长检测的角度*/
#define  PFEET_LEG_LEN_DETECT_ANGLE                 PFEET04                /*启动腿长检测的角度*/
#define  PZERO_LEG_LEN_DETECT_ANGLE                 PZERO03                /*启动腿长检测的角度*/


#define  PBACK15                                    15
#define  PBACK14                                    14
#define  PBACK13                                    13
#define  PBACK12                                    12
#define  PBACK11                                    11
#define  PBACK10                                    10
#define  PBACK09                                    9
#define  PBACK08                                    8
#define  PBACK07                                    7
#define  PBACK06                                    6
#define  PBACK05                                    5
#define  PBACK04                                    4           
#define  PBACK03                                    3
#define  PBACK02                                    2
#define  PBACK01                                    1
#define  PBACK00                                    0

#define  PFEET15                                    15
#define  PFEET14                                    14
#define  PFEET13                                    13
#define  PFEET12                                    12
#define  PFEET11                                    11
#define  PFEET10                                    10
#define  PFEET09                                    9
#define  PFEET08                                    8
#define  PFEET07                                    7
#define  PFEET06                                    6
#define  PFEET05                                    5
#define  PFEET04                                    4           
#define  PFEET03                                    3
#define  PFEET02                                    2
#define  PFEET01                                    1
#define  PFEET00                                    0

#define  PZERO15                                    15
#define  PZERO14                                    14
#define  PZERO13                                    13
#define  PZERO12                                    12
#define  PZERO11                                    11
#define  PZERO10                                    10
#define  PZERO09                                    9
#define  PZERO08                                    8
#define  PZERO07                                    7
#define  PZERO06                                    6
#define  PZERO05                                    5
#define  PZERO04                                    4           
#define  PZERO03                                    3
#define  PZERO02                                    2
#define  PZERO01                                    1
#define  PZERO00                                    0


/*推杆 各个方向的 调节 运动 ===================================================================*/
#define  SPIKE_MOVE_NONE                            0
#define  SPIKE_MOVE_BACK_UP                         1
#define  SPIKE_MOVE_BACK_DOWN                       2
#define  SPIKE_MOVE_ZERO_UP                         1
#define  SPIKE_MOVE_ZERO_DOWN                       2
#define  SPIKE_MOVE_FEET_UP                         1
#define  SPIKE_MOVE_FEET_DOWN                       2
#define  SPIKE_MOVE_LEG_SHORT                       1
#define  SPIKE_MOVE_LEG_EXTEND                      2


/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  推杆 控制与状态标识                                                                                           
************************************************************************************************************************
*/
typedef  union 
{
  struct
  {
    uint8_t    Pause                          :5;  /*暂停*/

    uint8_t    ReachZeroSafetyAngleLimit      :1;  /*达到零重力安全角度*/

    uint8_t    LegLenDetectPause              :5;  /*暂停*/
    uint8_t    LegLenDetectSw                 :1;  /*腿长检测开关*/
    uint8_t    LegLenDetectFinish             :1;  /*腿长检测完成标识*/
    uint8_t    LegLenDetectRun                :1;  /*腿长检测运行标识*/
    
    uint8_t    LegTouchGroundProtectRun       :1;  /*触地保护*/
  }Bit;
  uint32_t All;
}SpikeCSFlag_t;  /*Control State Flag  控制与状态标识*/


/*
************************************************************************************************************************
* 类型定义 :  推杆动作                                                                                       
************************************************************************************************************************
*/
typedef union
{
  uint16_t All;
  struct
  {
    uint8_t       BackMove           :2;
    uint8_t       FeetMove           :2;
    uint8_t       ZeroMove           :2;
    uint8_t       LegFlexMove        :2;
    uint8_t       ULegFlexMove       :2;
  }Bit;   
}SpikeAction_t; 

/*
************************************************************************************************************************
* 类型定义 :  推杆操作相关数据结构                                                                                      
************************************************************************************************************************
*/
typedef struct
{
  SpikeCSFlag_t            CSFlag;

  SpikeAction_t            ActionCur;
  SpikeAction_t            ActionHis;

  uint8_t                  BackAngleSetVal;                /*角度 设置值*/
  uint8_t                  FeetAngleSetVal;                /*角度 设置值*/ 
  uint8_t                  ZeroAngleSetVal;                /*角度 设置值*/ 
   uint8_t                 LegFlexAngleSetVal;             /*角度 设置值*/ 
   uint8_t                 ULegFlexAngleSetVal;            /*角度 设置值*/ 
 //uint8_t                  BackAngleRealVal;               /*角度 实际值*/
  //uint8_t                  FeetAngleRealVal;               /*角度 实际值*/
  //uint8_t                  ZeroAngleRealVal;               /*角度 实际值*/

  uint8_t                  ZeroSafetyAngleLimitBackAngele; /*零重力安全角度限制 之 背部角度*/  
  uint8_t                  ZeroSafetyAngleLimitZeroAngele; /*零重力安全角度限制 之 零重力角度*/ 

  uint8_t                  LegLenDetectStep;               /*腿长检测步骤*/
  uint8_t                  LegLenDetectExtendMax;          /*腿长检测时，伸长的最大值*/

  /*推杆部件 主要为调试用，实际编码应尽量使用各部件的接口函数-------*/
  BackSpike_t              *pBackSpike;
  FeetSpike_t              *pFeetSpike;
  ZeroSpike_t              *pZeroSpike;
  LegFlexSpike_t           *pLegFlexSpike;

}Spike_t;


/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
/*查询/设置推杆位置------------------------------------------------*/
#define  Spike_GetBackAngle()              BackSpike_GetPosition()
#define  Spike_GetZeroAngle()              ZeroSpike_GetPosition()
#define  Spike_GetFeetAngle()              FeetSpike_GetPosition()
#define  Spike_GetLegFlexAngle()           LegFlexSpike_GetPosition()

uint8_t Spike_SetBackAngle(uint8_t BackAngle);
uint8_t Spike_SetZeroAngle(uint8_t ZeroAngle);
uint8_t Spike_SetFeetAngle(uint8_t FeetAngle);
uint8_t Spike_SetLegFlexAngle(uint8_t LegFlexAngle);
uint8_t Spike_SetULegFlexAngle(uint8_t LegFlexAngle);
void Spike_SetAngle(uint8_t BackAngle, uint8_t FeetAngle, uint8_t ZeroAngle);

#define  Spike_ResetBackAngle()            BackSpike_ResetPosition()  /*复位到初始位置*/        
#define  Spike_ResetZeroAngle()            ZeroSpike_ResetPosition()  /*复位到初始位置*/        
#define  Spike_ResetFeetAngle()            FeetSpike_ResetPosition()  /*复位到初始位置*/        

/*查询/设置推杆动作-----------------------------------------------------*/
uint8_t Spike_GetBackMove(void);
uint8_t Spike_GetZeroMove(void);
uint8_t Spike_GetFeetMove(void);
uint8_t Spike_GetLegFlexMove(void);
uint8_t Spike_GetULegFlexMove(void);

void Spike_SetBackMove(uint8_t Move);
void Spike_SetZeroMove(uint8_t Move);
void Spike_SetFeetMove(uint8_t Move);
void Spike_SetLegFlexMove(uint8_t Move);
void Spike_SetULegFlexMove(uint8_t Move);
void Spike_SetMoveAction(uint16_t SpikeMoveAction);

#define  Spike_BackMoveUp()                BackSpike_SetPosition(PBACK_MIN)
#define  Spike_BackMoveDown()              BackSpike_SetPosition(PBACK_MAX)
#define  Spike_BackMoveStop()              BackSpike_SetPosition(PKEEP)

#define  Spike_ZeroMoveUp()                ZeroSpike_SetPosition(PZERO_MAX)
#define  Spike_ZeroMoveDown()              ZeroSpike_SetPosition(PZERO_MIN)
#define  Spike_ZeroMoveStop()              ZeroSpike_SetPosition(PKEEP)

#define  Spike_FeetMoveUp()                FeetSpike_SetPosition(PFEET_MAX)
#define  Spike_FeetMoveDown()              FeetSpike_SetPosition(PFEET_MIN)
#define  Spike_FeetMoveStop()              FeetSpike_SetPosition(PKEEP)

#define  Spike_LegFlexMoveShorten()        LegFlexSpike_SetPosition(PLEGFLEX_MIN)
#define  Spike_LegFlexMoveExtend()         LegFlexSpike_SetPosition(PLEGFLEX_MAX)
#define  Spike_LegFlexMoveStop()           LegFlexSpike_SetPosition(PKEEP)

#define  Spike_ULegFlexMoveShorten()       LegFlexSpike_SetULegPosition(PULEGFLEX_MIN)
#define  Spike_ULegFlexMoveExtend()        LegFlexSpike_SetULegPosition(PULEGFLEX_MAX)
#define  Spike_ULegFlexMoveStop()          LegFlexSpike_SetULegPosition(PKEEP)

/*零重力安全限定角度相关--------------------------------------------*/
void Spike_SetZeroSafetyAngleLimitRef(uint8_t RefBack, uint8_t RefZero);

void Spike_SetLegLenDetectSw(uint8_t Sw);
void Spike_LegLenDetectRedo(void);
void Spike_SetLegLenDetectExtendMax(uint8_t MaxLen);
void Spike_LegLenDetectPauseOn(void);
void Spike_LegLenDetectPauseOff(void);


/*推杆 初始化 与 处理函数-------------------------------------------*/
Spike_t* Spike_Init(void);
void Spike_Handle(void);

SpikeCSFlag_t Spike_GetCSFlag(void);

#endif
