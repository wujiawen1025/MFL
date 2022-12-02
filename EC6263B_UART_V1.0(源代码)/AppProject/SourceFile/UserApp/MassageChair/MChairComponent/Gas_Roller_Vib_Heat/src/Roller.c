/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: Roller.c                                                                                                         
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

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "Roller.h"
#include "ESF.h"


/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/


/*
========================================================================================================================
*【本地数据类型定义】                              【本地数据类型定义】                              【本地数据类型定义】
========================================================================================================================
*/


/*
========================================================================================================================
*【变量定义 & 各种声明】                          【变量定义 & 各种声明】                          【变量定义 & 各种声明】    
========================================================================================================================
*/
static Roller_t   Roller;
Roller_t   *pRoller = &Roller;


#if((1==ROLLER_FEET_EN) || (1==ROLLER_CALVES_EN))

/**************************************************************************************************
* 配合的充气 将通过函数 Roller_GetFeetGas() 提供给上层调用。 上层调用在进行相关充气配合的控制。
* 此种方式充气强度控制不起作用（除非采用气压检测等方式）。
*
*    b0   FeetSide       脚侧
*    b0   Ankle          脚踝
*    b0   Gas3        
*    b0   Gas4          
*    b0   CalvesSide     腿侧
*    b0   CalvesBot      腿底
*    b0   Gas7          
*    b0   Pump           气泵  (预留)
*/
static const RollerTabItem_t FeetRollerTab[] = 
{
 /* 配合的充气   强度              方向              起始位置  结束位置  滚动时间  停滚时间  重复次数*/
  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        0,        0,   5000,    500,      1},
  {B(00000000),  0,    FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,      0,   1000,      1},

  {B(00000000),  100,  FEET_ROLLER_DIRECTION_BACK,   PIGNORE,  PIGNORE,  17000,    500,      1},
  {B(00000000),  90,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   7000,    500,      2},
  {B(00000000),  60,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   7000,    500,      3},

  {B(00000000),  100,  FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,  10000,    500,      1},
  {B(00000000),  60,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   7000,    500,      2},
  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        5,        7,   7000,    500,      3},
  {B(00000000),  90,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   7000,    500,      2},

  {B(00000000),  100,  FEET_ROLLER_DIRECTION_BACK,   PIGNORE,  PIGNORE,  15000,    500,      1},
  {B(00000000),  60,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   7000,    500,      2},
  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        1,        3,   7000,    500,      3},
  {B(00000000),  90,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   7000,    500,      2},
  {B(00000000),  100,  FEET_ROLLER_DIRECTION_BACK,   PIGNORE,  PIGNORE,  15000,    500,      1},

  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        0,        0,   5000,     500,      1},    /*位置复位*/
  {B(00000000),   0,   FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,   5000,     500,      1},    /*休息5s*/
  {B(00000000),  60,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      2},
  {B(00000000),  80,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      2},
  {B(00000000), 100,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      3},
  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        0,        0,   5000,     500,      1},    /*位置复位*/
  {B(00000000),   0,   FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,   5000,     500,      1},    /*休息5s*/
  {B(00000000), 100,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      3},
  {B(00000000),  80,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      2},
  {B(00000000),  60,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      2},

  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        0,        0,   5000,     500,      1},    /*位置复位*/
  {B(00000000),   0,   FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,   5000,     500,      1},    /*休息5s*/
  {B(00000000),  70,   FEET_ROLLER_DIRECTION_BACK,   PIGNORE,  PIGNORE,  15000,     500,      1},
  {B(00000000),  60,   FEET_ROLLER_DIRECTION_FRONT,        5,        7,   7000,     500,      2},
  {B(00000000),  80,   FEET_ROLLER_DIRECTION_FRONT,        5,        7,   7000,     500,      2},
  {B(00000000), 100,   FEET_ROLLER_DIRECTION_FRONT,        5,        7,   7000,     500,      4},

  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        0,        0,   5000,     500,      1},    /*位置复位*/
  {B(00000000),   0,   FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,   5000,     500,      1},    /*休息5s*/
  {B(00000000),  70,   FEET_ROLLER_DIRECTION_BACK,   PIGNORE,  PIGNORE,  15000,     500,      1},
  {B(00000000),  60,   FEET_ROLLER_DIRECTION_FRONT,        1,        3,   7000,     500,      2},
  {B(00000000),  80,   FEET_ROLLER_DIRECTION_FRONT,        1,        3,   7000,     500,      2},
  {B(00000000), 100,   FEET_ROLLER_DIRECTION_FRONT,        1,        3,   7000,     500,      4},

  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        0,        0,   5000,     500,      1},    /*位置复位*/
  {B(00000000),   0,   FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,   5000,     500,      1},    /*休息5s*/
  {B(00000000),  55,   FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,  15000,     500,      1},
  {B(00000000), 100,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      3},
  {B(00000000),  90,   FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,  10000,     500,      1},
  {B(00000000), 100,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      3},
  {B(00000000),  55,   FEET_ROLLER_DIRECTION_BACK,   PIGNORE,  PIGNORE,  15000,     500,      1},
  {B(00000000), 100,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      3},
  {B(00000000),  90,   FEET_ROLLER_DIRECTION_BACK,   PIGNORE,  PIGNORE,  10000,     500,      1},
  {B(00000000), 100,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      3},
  
  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        0,        0,   5000,     500,      1},    /*位置复位*/
  {B(00000000),   0,   FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,   5000,     500,      1},    /*休息5s*/

  //-------------------------------------------------------------------------------------------------
  {B(00000000),  0,    FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,  0,        1000,     1}
};

#define  FEET_ROLLER_TAB_NUM  TAB_NUM(FeetRollerTab)




#define CalvesRollerTab  FeetRollerTab
#endif



/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : Roller_SetFeetRollerWorkState                                                                                                         
* 函数名称 : Roller_SetCalvesRollerWorkState                                                                                                         
* 功能描述 : 设置滚轮功能的工作与不工作                                                                                     
* 输入参数 : TureFalse -- TRUE  工作
*                         FALSE 不工作                                                                                      
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Roller_SetFeetRollerWorkState(uint8_t  TureFalse)
{
  #if(1==ROLLER_FEET_EN)
  if((TureFalse != TRUE) && (TureFalse != FALSE))
  {
    TureFalse = FALSE;
  }

  pRoller->CSFlag.Bit.FeetWork = TureFalse;
  #endif
}

void Roller_SetCalvesRollerWorkState(uint8_t  TureFalse)
{
  #if(1==ROLLER_CALVES_EN)
  if((TureFalse != TRUE) && (TureFalse != FALSE))
  {
    TureFalse = FALSE;
  }

  pRoller->CSFlag.Bit.CalvesWork = TureFalse;
  #endif
}

/*
************************************************************************************************************************
* 函数名称 : Roller_FeetRollerPauseOn                                                                                                         
* 函数名称 : Roller_CalvesRollerPauseOn                                                                                                         
* 功能描述 : 暂停滚轮功能                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Roller_FeetRollerPauseOn(void)
{
  #if(1==ROLLER_FEET_EN)
  if(pRoller->CSFlag.Bit.FeetPause < 0x1F)
  {
    pRoller->CSFlag.Bit.FeetPause++;
  }
  #endif
}

void Roller_CalvesRollerPauseOn(void)
{
  #if(1==ROLLER_CALVES_EN)
  if(pRoller->CSFlag.Bit.CalvesPause < 0x1F)
  {
    pRoller->CSFlag.Bit.CalvesPause++;
  }
  #endif
}

/*
************************************************************************************************************************
* 函数名称 : Roller_FeetRollerPauseOff                                                                                                         
* 函数名称 : Roller_CalvesRollerPauseOff                                                                                                         
* 功能描述 : 解除暂停滚轮功能                                                                                    
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Roller_FeetRollerPauseOff(void)
{
  #if(1==ROLLER_FEET_EN)
  if(pRoller->CSFlag.Bit.FeetPause > 0)
  {
    pRoller->CSFlag.Bit.FeetPause--;
  }
  #endif
}

void Roller_CalvesRollerPauseOff(void)
{
  #if(1==ROLLER_CALVES_EN)
  if(pRoller->CSFlag.Bit.CalvesPause > 0)
  {
    pRoller->CSFlag.Bit.CalvesPause--;
  }
  #endif
}

/*
************************************************************************************************************************
* 函数名称 : Roller_FeetRollerResetStep                                                                                                         
* 函数名称 : Roller_CalvesRollerResetStep                                                                                                         
* 功能描述 : 复位步骤                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Roller_FeetRollerResetStep()
{
  #if(1==ROLLER_FEET_EN)
  pRoller->FeetPositionSetp = 0;      /*滚轮 位置 步骤*/  
  pRoller->FeetSetpNum = 0;           /*滚轮 步骤数*/  
  pRoller->FeetSetpTime = 0;          /*滚轮 步骤时间*/ 
  pRoller->FeetSetpRepeat = 0;        /*滚轮 步骤重复次数*/ 
  #endif
}

void Roller_CalvesRollerResetStep()
{
  #if(1==ROLLER_CALVES_EN)
  pRoller->CalvesSetpNum = 0;           /*滚轮 步骤数*/  
  pRoller->CalvesSetpTime = 0;          /*滚轮 步骤时间*/ 
  pRoller->CalvesSetpRepeat = 0;        /*滚轮 步骤重复次数*/ 
  #endif
}



/*
************************************************************************************************************************
* 函数名称 : Roller_FeetRollerHandle                                                                                                         
* 函数名称 : Roller_CalvesRollerHandle                                                                                                         
* 功能描述 : 滚轮处理                                                                                     
* 输入参数 : ExePeriod -- 函数的执行周期                                                                                      
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Roller_FeetRollerHandle(Ticker_t ExePeriod)
{
  #if(1==ROLLER_FEET_EN)
  static uint16_t   ProtectTimeMs;                                   
  static uint8_t    DirHis;  
  uint8_t           DirTab;

  do
  {
    /*暂停则停止电机-----------------------------------------*/
    if(pRoller->CSFlag.Bit.FeetPause > 0)
    {
      pRoller->CSFlag.Bit.FeetRun = OFF;
      pRoller->FeetPWM = 0;
      break;
    }

    if(TRUE == pRoller->CSFlag.Bit.KeepAtInitPosition)       /*保持在初始位置*/
    {
      if(pRoller->CSFlag.Bit.FeetInitPositionIO != 0)
      {
        pRoller->CSFlag.Bit.FeetRun = ON;
        pRoller->FeetPWM = 70;
      }
      else
      {
        pRoller->CSFlag.Bit.FeetRun = OFF;
        pRoller->FeetPWM = 0;
      }    
      break;
    }
    
    /*马达驱动--------------------------------------------------*/
    if(TRUE == pRoller->CSFlag.Bit.FeetWork) /*工作*/
    {
      pRoller->CSFlag.Bit.FeetRun = ON;
      DirTab = FeetRollerTab[pRoller->FeetSetpNum].Direction;
      pRoller->FeetSetpTime += ExePeriod;
      
      if((FeetRollerTab[pRoller->FeetSetpNum].EndPosition   != PIGNORE) &&   /*滚动位置有效，即在某段上来回滚动刮痧*/
         (FeetRollerTab[pRoller->FeetSetpNum].StartPosition != PIGNORE) )    /*滚动位置有效，即在某段上来回滚动刮痧*/
      {
        pRoller->FeetPWM = FeetRollerTab[pRoller->FeetSetpNum].PWM;

        switch(pRoller->FeetPositionSetp)
        {
          case 0: 
          {
            if((pRoller->FeetPosition == FeetRollerTab[pRoller->FeetSetpNum].EndPosition) ||    /*位置到*/
               (pRoller->FeetSetpTime >= FeetRollerTab[pRoller->FeetSetpNum].OnTime)      )     /*超时*/
            {
              pRoller->FeetPositionSetp++;
            }  
          }break;
          
          case 1: 
          {
            DirTab = !DirTab;                                                                   /*回滚换向*/ 
            if((pRoller->FeetPosition == FeetRollerTab[pRoller->FeetSetpNum].StartPosition) ||  /*位置到*/
               (pRoller->FeetSetpTime >= FeetRollerTab[pRoller->FeetSetpNum].OnTime)        )   /*超时*/
            {
              pRoller->FeetPositionSetp++;
            }  
          }break;
           
          default: 
          { 
            pRoller->FeetPositionSetp = 0; 
            pRoller->FeetSetpTime = 0;
            pRoller->FeetSetpRepeat++;
          }break;
        }
      }
      else  /*滚动位置无效，即一直前滚或一直后滚*/
      {
        if(pRoller->FeetSetpTime < FeetRollerTab[pRoller->FeetSetpNum].OnTime)
        {
          pRoller->FeetPWM = FeetRollerTab[pRoller->FeetSetpNum].PWM;
        }
        else if(pRoller->FeetSetpTime < (FeetRollerTab[pRoller->FeetSetpNum].OnTime + FeetRollerTab[pRoller->FeetSetpNum].OffTime))
        {
          pRoller->FeetPWM = 0;
        }
        else
        {
          pRoller->FeetSetpTime = 0;
          pRoller->FeetSetpRepeat++;
        }       
      }

      if(pRoller->FeetSetpRepeat >= FeetRollerTab[pRoller->FeetSetpNum].Repeat)
      {
        pRoller->FeetSetpRepeat = 0;
        pRoller->FeetSetpNum++;
        if(pRoller->FeetSetpNum >= FEET_ROLLER_TAB_NUM)
        {
          pRoller->FeetSetpNum = 0;
        }
      }
      
      /*换向保护*/
      if(DirHis != DirTab)
      {
        DirHis = DirTab;
        ProtectTimeMs = 0;
      }
      if(ProtectTimeMs < 1000)
      {
        ProtectTimeMs += ExePeriod;
      }
      if(ProtectTimeMs < 100)                     
      {
        pRoller->FeetPWM = 0;
      } 
      else if(ProtectTimeMs < 200) 
      {
        pRoller->FeetPWM = 0;
        pRoller->CSFlag.Bit.FeetDirection = DirTab;//FeetRollerTab[pRoller->FeetSetpNum].Direction;
      }      
    }
    else  /*不工作*/
    {
      Roller_FeetRollerResetStep();
      
      if(pRoller->CSFlag.Bit.FeetInitPositionIO != 0)
      {
        pRoller->CSFlag.Bit.FeetRun = ON;
        pRoller->FeetPWM = 70;
      }
      else
      {
        pRoller->CSFlag.Bit.FeetRun = OFF;
        pRoller->CSFlag.Bit.FeetDirection = FEET_ROLLER_DIRECTION_FRONT; 
        pRoller->FeetPWM = 0;
      }
    }
  }while(0);

  //BSP_IO_SetOutput_FeetRollerCtrl(pRoller->CSFlag.Bit.FeetRun, pRoller->CSFlag.Bit.FeetDirection,  pRoller->FeetPWM);
  pRoller->SetQry0x49.Byte0.Bit.FeetRollerSw = pRoller->CSFlag.Bit.FeetRun;
  pRoller->SetQry0x49.Byte0.Bit.FeetRollerDirection = pRoller->CSFlag.Bit.FeetDirection;
  pRoller->SetQry0x49.FeetRollerPWM = pRoller->FeetPWM;

  #endif
}

void Roller_CalvesRollerHandle(Ticker_t ExePeriod)
{
  #if(1==ROLLER_CALVES_EN)
  static uint16_t   ProtectTimeMs;                                   
  static uint8_t    DirHis;  
  uint8_t           DirTab;

  do
  {
    /*暂停则停止电机-----------------------------------------*/
    if(pRoller->CSFlag.Bit.CalvesPause > 0)
    {
      pRoller->CSFlag.Bit.CalvesRun = OFF;
      pRoller->CalvesPWM = 0;
      break;
    }

    /*马达驱动--------------------------------------------------*/
    if(TRUE == pRoller->CSFlag.Bit.CalvesWork) /*工作*/
    {
      pRoller->CSFlag.Bit.CalvesRun = ON;
      DirTab = CalvesRollerTab[pRoller->CalvesSetpNum].Direction;
      pRoller->CalvesSetpTime += ExePeriod;
      if(pRoller->CalvesSetpTime < CalvesRollerTab[pRoller->CalvesSetpNum].OnTime)
      {
        pRoller->CalvesPWM = CalvesRollerTab[pRoller->CalvesSetpNum].PWM;
      }
      else if(pRoller->CalvesSetpTime < (CalvesRollerTab[pRoller->CalvesSetpNum].OnTime + CalvesRollerTab[pRoller->CalvesSetpNum].OffTime))
      {
        pRoller->CalvesPWM = 0;
      }
      else
      {
        pRoller->CalvesSetpTime = 0;
        pRoller->CalvesSetpRepeat++;
      }       

      if(pRoller->CalvesSetpRepeat >= CalvesRollerTab[pRoller->CalvesSetpNum].Repeat)
      {
        pRoller->CalvesSetpRepeat = 0;
        pRoller->CalvesSetpNum++;
        if(pRoller->CalvesSetpNum >= FEET_ROLLER_TAB_NUM)
        {
          pRoller->CalvesSetpNum = 0;
        }
      }
      
      /*换向保护*/
      if(DirHis != DirTab)
      {
        DirHis = DirTab;
        ProtectTimeMs = 0;
      }
      if(ProtectTimeMs < 1000)
      {
        ProtectTimeMs += ExePeriod;
      }
      if(ProtectTimeMs < 200)                     
      {
        pRoller->CSFlag.Bit.CalvesRun = OFF;
      } 
      else if(ProtectTimeMs < 400) 
      {
        pRoller->CSFlag.Bit.CalvesRun = OFF;
        pRoller->CSFlag.Bit.CalvesDirection = CalvesRollerTab[pRoller->CalvesSetpNum].Direction;
      }      
    }
    else  /*不工作*/
    {
      Roller_CalvesRollerResetStep();
      pRoller->CSFlag.Bit.CalvesRun = OFF;
      pRoller->CalvesPWM = 0;
    }
  }while(0);
  
  pRoller->SetQry0x49.Byte2.Bit.CalvesRollerSw = pRoller->CSFlag.Bit.CalvesRun;
  pRoller->SetQry0x49.Byte2.Bit.CalvesRollerDirection = pRoller->CSFlag.Bit.CalvesDirection;
  
  #endif
}


void Roller_AllPartsHandle(Ticker_t ExePeriod)                                                                                                         
{
  Roller_FeetRollerHandle(ExePeriod);
  Roller_CalvesRollerHandle(ExePeriod);  
}


/*
========================================================================================================================
*         滚轮功能函数表                           滚轮功能函数表                           滚轮功能函数表
========================================================================================================================
*/
#define  ROLLER_TICK_COUNT_BUF_NUM   1
static Ticker_t Roller_TickCount[ROLLER_TICK_COUNT_BUF_NUM];

static const ESF_TmrExeFunc_t  Roller_TmrExeFuncTab[] = 
{
  /*   执行函数              执行周期(ms)    时间计数变量*/
  {Roller_AllPartsHandle,        101,      &Roller_TickCount[0]}

};

#define  ROLLER_TMR_EXE_FUNC_TAB_NUM     TAB_NUM(Roller_TmrExeFuncTab)


/*
************************************************************************************************************************
* 函数名称 : Roller_Init                                                                                                         
* 功能描述 : 滚轮初始化                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 返回 可操作滚轮功能 的结构体 的指针                                                                
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
Roller_t*  Roller_Init(void)
{
  /*初始化相关数据------------------------------------------*/
  memset(pRoller, 0, sizeof(Roller_t)); /*清零所有数据*/

  /*检测 Roller_TmrExeFuncTab 功能函数表排列是否正确------------------------*/
  ESF_TmrExeFuncTabCheck(Roller_TmrExeFuncTab, ROLLER_TMR_EXE_FUNC_TAB_NUM, ROLLER_TICK_COUNT_BUF_NUM);

  return pRoller;
}

/*
************************************************************************************************************************
* 函数名称 : Roller_Handle                                                                                                         
* 功能描述 : 滚轮处理                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Roller_Handle(void)
{
  /*调度功能函数表------------------------------------------------*/
  ESF_TmrExeFuncScheduling(Roller_TmrExeFuncTab, ROLLER_TMR_EXE_FUNC_TAB_NUM);
}


/*
************************************************************************************************************************
* 函数名称 : Roller_GetCSFlag                                                                                                          
* 功能描述 : 获得 控制 与 状态 标识                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 控制与状态标识 的结构体                                                                
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
RollerCSFlag_t Roller_GetCSFlag(void)
{
  return pRoller->CSFlag;
}

/*
************************************************************************************************************************
* 函数名称 : Roller_GetFeetGas                                                                                                         
* 功能描述 : 获得 脚滚配合的充气                                                                             
* 输入参数 : 无                                                                                      
* 返回参数 : 脚滚配合的充气                                                                   
* 补充说明 : 提供给上层调用，上层调用在进行相关充气配合的控制                                                                                                        
************************************************************************************************************************
*/
RollerGasPart_t Roller_GetFeetGas(void)
{
  return FeetRollerTab[pRoller->FeetSetpNum].GasPart;
}

/*
************************************************************************************************************************
* 函数名称 : Roller_SetFeetRollerKeepAtInitPosition                                                                                                          
* 功能描述 : 让脚滚保持在初始位置                                                                               
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                     
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Roller_SetFeetRollerKeepAtInitPosition(void)
{
  pRoller->CSFlag.Bit.KeepAtInitPosition = TRUE;      /*保持在初始位置*/
}

/*
************************************************************************************************************************
* 函数名称 : Roller_ClrFeetRollerKeepAtInitPosition                                                                                                          
* 功能描述 : 清除让脚滚保持在初始位置                                                                               
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                     
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Roller_ClrFeetRollerKeepAtInitPosition(void)
{
  pRoller->CSFlag.Bit.KeepAtInitPosition = FALSE;      /*保持在初始位置*/
}

/*
************************************************************************************************************************
* 函数名称 : Roller_CDPDataObjRx_0x49                                                                                      
* 功能描述 : 0x49 腿脚滚轮控制(中心板<-->腿脚控制板）
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象中数据的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t Roller_CDPDataObjRx_0x49(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  /*更新数据到中心板-------------------------------------------------------------*/
  memcpy((uint8_t *)&pRoller->SetQry0x49, &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  pRoller->FeetCount = pRoller->SetQry0x49.FeetRollerCount;

  if(FEET_ROLLER_DIRECTION_FRONT == pRoller->CSFlag.Bit.FeetDirection)
  {
    pRoller->FeetPosition = pRoller->FeetCount/FEET_ROLLER_COUNT_PER_SEGMENT;
  }
  else
  {
    pRoller->FeetPosition = pRoller->FeetCount/FEET_ROLLER_COUNT_PER_SEGMENT + 1;
  }
  
  pRoller->CSFlag.Bit.FeetInitPositionIO = pRoller->SetQry0x49.Byte0.Bit.FeetRollerInitPositionIO;

  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* 函数名称 : Roller_CDPDataObjTx_0x49                                                                                      
* 功能描述 : 0x49 腿脚滚轮控制(中心板<-->腿脚控制板）
* 输入参数 : 无
* 返回参数 : 成功则返回要发送的数据的内存首地址，失败返回NULL空指针
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t* Roller_CDPDataObjTx_0x49(void)
{
  pRoller->SetQry0x49.DataLen = sizeof(pRoller->SetQry0x49);  
  pRoller->SetQry0x49.DataID = 0x49;  

  return (uint8_t *)&pRoller->SetQry0x49;
}
