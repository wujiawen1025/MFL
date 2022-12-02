/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：MotorCommon.h 
**
**    功能描述:
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

#ifndef  _COREMOTOR_H
#define  _COREMOTOR_H

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp.h"
#include "ESF.h"


/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
#define  PIGNORE                              255            /*位置忽略*/
#define  PKEEP                                (PIGNORE-1)    /*位置保持*/


#define  FB_WORKSTATE_PREPARE                 0              /*反馈工作状态：准备工作*/
#define  FB_WORKSTATE_BEFORE_SENSOR           1              /*反馈工作状态：检出旋转sensor信号之前的一段时间*/
#define  FB_WORKSTATE_AFTER_SENSOR            2              /*反馈工作状态：检出旋转sensor信号之后*/
#define  FB_WORKSTATE_SENSOR_INTERRUPT        3              /*反馈工作状态：旋转sensor信号中断*/

#define  NOFB_WORKSTATE_PREPARE               0              /*无反馈工作状态：准备工作*/
#define  NOFB_WORKSTATE_ADJUST_PWM            1              /*无反馈工作状态：调节PWM*/


#define  POSITION_COUNT_INC                   0              /*位置计数增加*/
#define  POSITION_COUNT_DEC                   1              /*位置计数减少*/

/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  电机FB转速统计                                                                                                       
* 说   明  ： RPM 每分钟转速。采用测周法。
*             该结构体用来辅助分析恒速的补偿效果。
************************************************************************************************************************
*/
typedef struct
{
  uint8_t  ReStart;
  uint16_t Count;
  int16_t  Diff;
  
  uint16_t In50;
  uint16_t In100;
  uint16_t Out100;
  
  /* 使用实例
  #if(XMOTOR_FB_STAT_EN)
  MotorFBRPMStat_t  XMotorFBRPMStat;
  #endif

  #if(XMOTOR_FB_STAT_EN)
  if(XMotorFBRPMStat.ReStart)
  {
    XMotorFBRPMStat.ReStart = 0;
    XMotorFBRPMStat.Count = 0;
    XMotorFBRPMStat.Diff = 0;
    XMotorFBRPMStat.In50 = 0;
    XMotorFBRPMStat.In100 = 0;
    XMotorFBRPMStat.Out100 = 0;
  }
  
  if(XMotorFBRPMStat.Count < 200)
  {
    XMotorFBRPMStat.Count++;
    XMotorFBRPMStat.Diff = pXMotor->RPMMointor.RPMRealVal-pXMotor->RPMSetVal;
    
    if(XMotorFBRPMStat.Diff < 0)
    {
      XMotorFBRPMStat.Diff = 0 - XMotorFBRPMStat.Diff;
    }
    
    if(XMotorFBRPMStat.Diff < 50)
    {
      XMotorFBRPMStat.In50++;
    }
    else if(XMotorFBRPMStat.Diff < 100)
    {
      XMotorFBRPMStat.In100++;
    }
    else
    {
      XMotorFBRPMStat.Out100++;
    }
  }
  #endif
  */ 
}MotorFBRPMStat_t; 


/*
************************************************************************************************************************
* 类型定义 :  电机转速检测器                                                                                                         
* 说   明  ： RPM 每分钟转速。采用测周法。
************************************************************************************************************************
*/
typedef struct
{
  Ticker_t                MsStamp;                           /*ms时间戳*/                     
  uint16_t                UsStamp;                           /*us时间戳*/                       
 
//  uint8_t                 PulseCount;                        /*脉冲统计*/
  uint16_t                RPMRealVal;                        /*转速实际值*/

  uint16_t                SensorLostTimeMs;                  /*电机启动后，监测不到传感器变化的时间*/

}MotorRPMMointor_t; 


/*
************************************************************************************************************************
* 类型定义 :  电机位置检测器                                                                                                
************************************************************************************************************************
*/
typedef struct
{
  /*使用码盘, 一般使用二进制的编码，可得到起始、结束 和中间过程的位置编码*/
  uint8_t                 PositionCode;                      /*位置编码*/
  
  /*使用 脉冲 和 限位IO检测，起始和结束可使用限位IO，中间位置使用脉冲计数来计算*/
  uint8_t                 StartLimitIOState;                 /*开始位置限位 IO 状态*/
  uint16_t                PositionCountHis;                  /*位置脉冲计数值 历史*/ 
  uint16_t                PositionCountCur;                  /*位置脉冲计数值 当前*/ 
  uint8_t                 CountDirection;                    /*位置脉冲计数方向*/ 
  uint8_t                 EndLimitIOState;                   /*结束位置限位 IO 状态*/

  uint16_t                SensorLostTimeMs;                  /*电机启动后，监测不到传感器变化的时间*/
  uint16_t                PositionCodeErrTimeMs;             /*位置编码错误持续时间*/

}MotorPositionMonitor_t; 


/*
************************************************************************************************************************
* 类型定义 :  位置编码映射                                                                                         
************************************************************************************************************************
*/
typedef struct
{
  uint8_t                 HopCode1;                          /*跳变编码1*/
  uint8_t                 HopCode2;                          /*跳变编码2*/
  uint8_t                 Positon;                           /*映射后的位置*/
}PositionCodeMap_t;



/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
void MotorCountUpdata(uint16_t *pCountCur,  uint8_t IncDec, uint16_t CountMax, uint16_t CountMin);
uint8_t PositionIOStableStat(uint8_t BSPIOCode,  uint8_t *pStableIOCode, uint8_t *pStableStat);

#endif
