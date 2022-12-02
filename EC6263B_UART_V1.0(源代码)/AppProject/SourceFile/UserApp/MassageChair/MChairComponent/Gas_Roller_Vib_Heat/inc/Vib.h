/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: Vib.h                                                                                                         
**
**    功能描述: 振动驱动。
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
#ifndef  _VIB_H
#define  _VIB_H

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp.h"
#include "CDP.h"



/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/

#define  VIB_FEET_EN                  1
#define  VIB_CALVES_EN                0
#define  VIB_SEAT_EN                  0
#define  VIB_LUMBARBACK_EN            0

 

/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  振动动作表格项                                                                                 
************************************************************************************************************************
*/
typedef struct
{
  uint8_t                SpeedLevel;   /*振动强度*/
  uint16_t               OnTime;       /*振动时间 ms*/
  uint16_t               OffTime;      /*停振时间 ms*/
  uint8_t                Repeat;       /*重复次数*/
}VibTabItem_t;


/*
************************************************************************************************************************
* 类型定义 :  振动动作                                                                        
************************************************************************************************************************
*/
typedef union
{
  uint16_t All;
  struct
  {
    uint8_t       Feet            :3;    /*脚部*/
    uint8_t       Calves          :3;    /*腿部*/
    uint8_t       Seat            :3;    /*座部*/
    uint8_t       LumbarBack      :3;    /*腰背*/
    
  }Bit;   
}VibAction_t; 

/*
************************************************************************************************************************
* 类型定义 :  振动 控制与状态标识                                                                         
************************************************************************************************************************
*/
typedef  union 
{
  uint32_t All;
  struct
  {
    #if(1==VIB_FEET_EN)
    uint8_t            FeetWork                   :1;    /*工作中*/
    uint8_t            FeetPause                  :5;    /*暂停*/
    uint8_t            FeetRun                    :1;    /*运行*/
    #endif
    
    #if(1==VIB_CALVES_EN)
    uint8_t            CalvesWork                 :1;    /*工作中*/
    uint8_t            CalvesPause                :5;    /*暂停*/
    uint8_t            CalvesRun                  :1;    /*运行*/
    #endif
    
    #if(1==VIB_SEAT_EN)
    uint8_t            SeatWork                   :1;    /*工作中*/
    uint8_t            SeatPause                  :5;    /*暂停*/
    uint8_t            SeatRun                    :1;    /*运行*/
    #endif

    #if(1==VIB_LUMBARBACK_EN)
    uint8_t            LumbarBackWork             :1;    /*工作中*/
    uint8_t            LumbarBackPause            :5;    /*暂停*/
    uint8_t            LumbarBackRun              :1;    /*运行*/
    uint8_t            LumbarBackRPMSensorFault   :1;    /*转速(或计数)传感器故障*/
    uint8_t            LumbarBackTestAge          :1;    /*振动电机的拷机寿命测试*/
    #endif
    
    #if ((0==VIB_FEET_EN) && (0==VIB_CALVES_EN) && (0==VIB_SEAT_EN) && (0==VIB_LUMBARBACK_EN))
    uint8_t            Keep                       :1;    /*如果都没定义任何功能，则定义一个变量，防止告警*/
    #endif
  }Bit;
}VibCSFlag_t;  /*Control State Flag  控制与状态标识*/

/*
************************************************************************************************************************
* 类型定义 :  振动操作相关数据结构                                                                             
************************************************************************************************************************
*/
typedef struct
{
  VibCSFlag_t             CSFlag;                      /*控制与状态标识*/

  #if(1==VIB_FEET_EN)
  uint8_t                 FeetSetpNum;                 /*步骤数*/  
  uint8_t                 FeetSetpRepeat;              /*步骤重复次数*/ 
  uint16_t                FeetSetpTime;                /*步骤时间*/ 
  CDP_DataFormat0x4A_t    SetQry0x4A;
  #endif
  
  #if(1==VIB_CALVES_EN)
  uint8_t                 CalvesSetpNum;               /*步骤数*/  
  uint8_t                 CalvesSetpRepeat;            /*步骤重复次数*/ 
  uint16_t                CalvesSetpTime;              /*步骤时间*/ 
  #endif
  
  #if(1==VIB_SEAT_EN)
  uint8_t                 SeatSetpNum;                 /*步骤数*/  
  uint8_t                 SeatSetpRepeat;              /*步骤重复次数*/ 
  uint16_t                SeatSetpTime;                /*步骤时间*/ 
  #endif
  
  #if(1==VIB_LUMBARBACK_EN)
  uint8_t                 LumbarBackSetpNum;           /*步骤数*/  
  uint8_t                 LumbarBackSetpRepeat;        /*步骤重复次数*/ 
  uint16_t                LumbarBackSetpTime;          /*步骤时间*/ 
  #endif

}Vib_t;


/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
/*初始化--------------------------------------*/
Vib_t*  Vib_Init(void);


/*周期执行--------------------------------------*/
void Vib_Handle(void);


/* 对外的接口， 即 其他模块 可对 该模块执行的 控制操作*/
void Vib_SetLumbarBackVibTestAge(uint8_t OnOff);

void Vib_FeetVibPauseOn(void);
void Vib_FeetVibPauseOff(void);
void Vib_SetFeetVibWorkState(uint8_t  TrueFalse);
void Vib_FeetVibResetStep(void);

void Vib_CalvesVibPauseOn(void);
void Vib_CalvesVibPauseOff(void);
void Vib_SetCalvesVibWorkState(uint8_t  TrueFalse);
void Vib_CalvesVibResetStep(void);

void Vib_SeatVibPauseOn(void);
void Vib_SeatVibPauseOff(void);
void Vib_SetSeatVibWorkState(uint8_t  TrueFalse);
void Vib_SeatVibResetStep(void);

void Vib_LumbarBackVibPauseOn(void);
void Vib_LumbarBackVibPauseOff(void);
void Vib_SetLumbarBackVibWorkState(uint8_t  TrueFalse);
void Vib_LumbarBackVibResetStep(void);

VibCSFlag_t Vib_GetCSFlag(void);

#endif
