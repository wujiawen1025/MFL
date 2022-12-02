/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: Vib.c                                                                                                         
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

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "Vib.h"
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
static Vib_t   Vib;
Vib_t   *pVib = &Vib;


static  const  VibTabItem_t VibTab[] = 
{
  /*强度  振动时间  停振时间  重复次数*/
  {20,   0,        500,      1},   /*初始*/
  {25,   6000,     2000,     4},
  {30,   5000,     1000,     3},
  {35,   7000,     3000,     2},
  {30,   5000,     1000,     3},
  {25,   6000,     2000,     4},
  {20,   0,        500,      1}    /*停*/
};
#define  VIB_TAB_NUM  TAB_NUM(VibTab)


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : Vib_SetFeetVibFunc      
* 函数名称 : Vib_SetCalvesVibFunc      
* 函数名称 : Vib_SetSeatVibFunc      
* 函数名称 : Vib_SetLumbarBackVibFunc      
* 功能描述 : 设置振动的工作与不工作                                                                                     
* 输入参数 : TrueFalse -- TRUE  工作
*                         FALSE 不工作                                                                                      
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Vib_SetFeetVibWorkState(uint8_t TrueFalse)
{
  #if(1==VIB_FEET_EN)
  if((TrueFalse != TRUE) && (TrueFalse != FALSE))
  {
    TrueFalse = FALSE;
  }
  pVib->CSFlag.Bit.FeetWork = TrueFalse;
  #endif
}

void Vib_SetCalvesVibWorkState(uint8_t TrueFalse)
{
  #if(1==VIB_CALVES_EN)
  if((TrueFalse != TRUE) && (TrueFalse != FALSE))
  {
    TrueFalse = FALSE;
  }
  pVib->CSFlag.Bit.CalvesWork = TrueFalse;
  #endif
}

void Vib_SetSeatVibWorkState(uint8_t TrueFalse)
{
  #if(1==VIB_SEAT_EN)
  if((TrueFalse != TRUE) && (TrueFalse != FALSE))
  {
    TrueFalse = FALSE;
  }
  pVib->CSFlag.Bit.SeatWork = TrueFalse;
  #endif
}

void Vib_SetLumbarBackVibWorkState(uint8_t TrueFalse)
{
  #if(1==VIB_LUMBARBACK_EN)
  if((TrueFalse != TRUE) && (TrueFalse != FALSE))
  {
    TrueFalse = FALSE;
  }
  pVib->CSFlag.Bit.LumbarBackWork = TrueFalse;
  #endif
}


/*
************************************************************************************************************************
* 函数名称 : Vib_FeetVibPauseOn                                                                                                         
* 函数名称 : Vib_CalvesVibPauseOn                                                                                                         
* 函数名称 : Vib_SeatVibPauseOn                                                                                                         
* 函数名称 : Vib_LumbarBackVibPauseOn                                                                                                         
* 功能描述 : 暂停振动功能                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Vib_FeetVibPauseOn(void)
{
  #if(1==VIB_FEET_EN)
  if(pVib->CSFlag.Bit.FeetPause < 0x1F)
  {
    pVib->CSFlag.Bit.FeetPause++;
  }
  #endif
}

void Vib_CalvesVibPauseOn(void)
{
  #if(1==VIB_CALVES_EN)
  if(pVib->CSFlag.Bit.CalvesPause < 0x1F)
  {
    pVib->CSFlag.Bit.CalvesPause++;
  }
  #endif
}

void Vib_SeatVibPauseOn(void)
{
  #if(1==VIB_SEAT_EN)
  if(pVib->CSFlag.Bit.SeatPause < 0x1F)
  {
    pVib->CSFlag.Bit.SeatPause++;
  }
  #endif
}

void Vib_LumbarBackVibPauseOn(void)
{
  #if(1==VIB_LUMBARBACK_EN)
  if(pVib->CSFlag.Bit.LumbarBackPause < 0x1F)
  {
    pVib->CSFlag.Bit.LumbarBackPause++;
  }
  #endif
}

/*
************************************************************************************************************************
* 函数名称 : Vib_FeetVibPauseOff                                                                                                         
* 函数名称 : Vib_CalvesVibPauseOff                                                                                                         
* 函数名称 : Vib_SeatVibPauseOff                                                                                                         
* 函数名称 : Vib_LumbarBackVibPauseOff                                                                                                         
* 功能描述 : 解除暂停振动功能                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Vib_FeetVibPauseOff(void)
{
  #if(1==VIB_FEET_EN)
  if(pVib->CSFlag.Bit.FeetPause > 0)
  {
    pVib->CSFlag.Bit.FeetPause--;
  }
  #endif
}

void Vib_CalvesVibPauseOff(void)
{
  #if(1==VIB_CALVES_EN)
  if(pVib->CSFlag.Bit.CalvesPause > 0)
  {
    pVib->CSFlag.Bit.CalvesPause--;
  }
  #endif
}

void Vib_SeatVibPauseOff(void)
{
  #if(1==VIB_SEAT_EN)
  if(pVib->CSFlag.Bit.SeatPause > 0)
  {
    pVib->CSFlag.Bit.SeatPause--;
  }
  #endif
}

void Vib_LumbarBackVibPauseOff(void)
{
  #if(1==VIB_LUMBARBACK_EN)
  if(pVib->CSFlag.Bit.LumbarBackPause > 0)
  {
    pVib->CSFlag.Bit.LumbarBackPause--;
  }
  #endif
}

/*
************************************************************************************************************************
* 函数名称 : Vib_FeetVibResetStep                                                                                                         
* 函数名称 : Vib_CalvesVibResetStep                                                                                                         
* 函数名称 : Vib_SeatVibResetStep                                                                                                         
* 函数名称 : Vib_LumbarBackVibResetStep                                                                                                         
* 功能描述 : 复位步骤                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Vib_FeetVibResetStep(void)
{
  #if(1==VIB_FEET_EN)
  pVib->FeetSetpNum = 0;           
  pVib->FeetSetpTime = 0;        
  pVib->FeetSetpRepeat = 0;      
  #endif
}

void Vib_CalvesVibResetStep(void)
{
  #if(1==VIB_CALVES_EN)
  pVib->CalvesSetpNum = 0;           
  pVib->CalvesSetpTime = 0;        
  pVib->CalvesSetpRepeat = 0;      
  #endif
}

void Vib_SeatVibResetStep(void)
{
  #if(1==VIB_SEAT_EN)
  pVib->SeatSetpNum = 0;           
  pVib->SeatSetpTime = 0;        
  pVib->SeatSetpRepeat = 0;      
  #endif
}

void Vib_LumbarBackVibResetStep(void)
{
  #if(1==VIB_LUMBARBACK_EN)
  pVib->LumbarBackSetpNum = 0;           
  pVib->LumbarBackSetpTime = 0;        
  pVib->LumbarBackSetpRepeat = 0;      
  #endif
}

/*
************************************************************************************************************************
* 函数名称 : Vib_FeetVibHandle                                                                                                         
* 函数名称 : Vib_CalvesVibHandle                                                                                                         
* 函数名称 : Vib_SeatVibHandle                                                                                                         
* 函数名称 : Vib_LumbarBackVibHandle                                                                                                         
* 函数名称 : Vib_AllPartsHandle                                                                                                         
* 功能描述 : 各部位振动振动处理                                                                                     
* 输入参数 : ExePeriod -- 函数的执行周期                                                                                    
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Vib_FeetVibHandle(Ticker_t ExePeriod)
{
  #if(1==VIB_FEET_EN)
  do
  {
    if(pVib->CSFlag.Bit.FeetPause > 0)
    {
      pVib->CSFlag.Bit.FeetRun = OFF;
      break;
    }

    if(TRUE == pVib->CSFlag.Bit.FeetWork) /*工作*/
    {
      pVib->FeetSetpTime += ExePeriod;
      if(pVib->FeetSetpTime < VibTab[pVib->FeetSetpNum].OnTime)
      {
        pVib->CSFlag.Bit.FeetRun = ON;
      }
      else if(pVib->FeetSetpTime < (VibTab[pVib->FeetSetpNum].OnTime + VibTab[pVib->FeetSetpNum].OffTime))
      {
        pVib->CSFlag.Bit.FeetRun = OFF;
      }
      else
      {
        pVib->FeetSetpTime = 0;
        pVib->FeetSetpRepeat++;
        if(pVib->FeetSetpRepeat >= VibTab[pVib->FeetSetpNum].Repeat)
        {
          pVib->FeetSetpRepeat = 0;
          pVib->FeetSetpNum++;
          if(pVib->FeetSetpNum >= VIB_TAB_NUM)
          {
            pVib->FeetSetpNum = 0;
          }
        }
      } 
    }
    else  /*不使能*/
    {
      Vib_FeetVibResetStep();
      pVib->CSFlag.Bit.FeetRun = OFF;
    }

  }while(0);

  //BSP_IO_SetOutput_FeetVibCtrl(pVib->CSFlag.Bit.FeetRun, 0, VibTab[pVib->FeetSetpNum].PWM);
  pVib->SetQry0x4A.Byte0.Bit.FeetVibSw = pVib->CSFlag.Bit.FeetRun;
  pVib->SetQry0x4A.Byte0.Bit.FeetVibDirection = 1;
  
  #endif
}

void Vib_CalvesVibHandle(Ticker_t ExePeriod)
{
  #if(1==VIB_CALVES_EN)
  do
  {
    if(pVib->CSFlag.Bit.CalvesPause > 0)
    {
      pVib->CSFlag.Bit.CalvesRun = OFF;
      break;
    }

    if(TRUE == pVib->CSFlag.Bit.CalvesWork) /*工作*/
    {
      pVib->CalvesSetpTime += ExePeriod;
      if(pVib->CalvesSetpTime < VibTab[pVib->CalvesSetpNum].OnTime)
      {
        pVib->CSFlag.Bit.CalvesRun = ON;
      }
      else if(pVib->CalvesSetpTime < (VibTab[pVib->CalvesSetpNum].OnTime + VibTab[pVib->CalvesSetpNum].OffTime))
      {
        pVib->CSFlag.Bit.CalvesRun = OFF;
      }
      else
      {
        pVib->CalvesSetpTime = 0;
        pVib->CalvesSetpRepeat++;
        if(pVib->CalvesSetpRepeat >= VibTab[pVib->CalvesSetpNum].Repeat)
        {
          pVib->CalvesSetpRepeat = 0;
          pVib->CalvesSetpNum++;
          if(pVib->CalvesSetpNum >= VIB_TAB_NUM)
          {
            pVib->CalvesSetpNum = 0;
          }
        }
      } 
    }
    else  /*不使能*/
    {
      Vib_CalvesVibResetStep();
      pVib->CSFlag.Bit.CalvesRun = OFF;
    }

  }while(0);

  //BSP_IO_SetOutput_CalvesVibCtrl(pVib->CSFlag.Bit.CalvesRun, 0, VibTab[pVib->CalvesSetpNum].PWM);
  #endif
}

void Vib_SeatVibHandle(Ticker_t ExePeriod)
{
  #if(1==VIB_SEAT_EN)
  do
  {
    if(pVib->CSFlag.Bit.SeatPause > 0)
    {
      pVib->CSFlag.Bit.SeatRun = OFF;
      break;
    }

    if(TRUE == pVib->CSFlag.Bit.SeatWork) /*工作*/
    {
      pVib->SeatSetpTime += ExePeriod;
      if(pVib->SeatSetpTime < VibTab[pVib->SeatSetpNum].OnTime)
      {
        pVib->CSFlag.Bit.SeatRun = ON;
      }
      else if(pVib->SeatSetpTime < (VibTab[pVib->SeatSetpNum].OnTime + VibTab[pVib->SeatSetpNum].OffTime))
      {
        pVib->CSFlag.Bit.SeatRun = OFF;
      }
      else
      {
        pVib->SeatSetpTime = 0;
        pVib->SeatSetpRepeat++;
        if(pVib->SeatSetpRepeat >= VibTab[pVib->SeatSetpNum].Repeat)
        {
          pVib->SeatSetpRepeat = 0;
          pVib->SeatSetpNum++;
          if(pVib->SeatSetpNum >= VIB_TAB_NUM)
          {
            pVib->SeatSetpNum = 0;
          }
        }
      } 
    }
    else  /*不使能*/
    {
      Vib_SeatVibResetStep();
      pVib->CSFlag.Bit.SeatRun = OFF;
    }

  }while(0);

  //BSP_IO_SetOutput_SeatVibCtrl(pVib->CSFlag.Bit.SeatRun, 0, VibTab[pVib->SeatSetpNum].PWM);

  #endif
}

void Vib_LumbarBackVibHandle(Ticker_t ExePeriod)
{
  #if(1==VIB_LUMBARBACK_EN)
  do
  {
    if(pVib->CSFlag.Bit.LumbarBackPause > 0)
    {
      pVib->CSFlag.Bit.LumbarBackRun = OFF;
      break;
    }

    if(TRUE == pVib->CSFlag.Bit.LumbarBackWork) /*工作*/
    {
      pVib->LumbarBackSetpTime += ExePeriod;
      if(pVib->LumbarBackSetpTime < VibTab[pVib->LumbarBackSetpNum].OnTime)
      {
        pVib->CSFlag.Bit.LumbarBackRun = ON;
      }
      else if(pVib->LumbarBackSetpTime < (VibTab[pVib->LumbarBackSetpNum].OnTime + VibTab[pVib->LumbarBackSetpNum].OffTime))
      {
        pVib->CSFlag.Bit.LumbarBackRun = OFF;
      }
      else
      {
        pVib->LumbarBackSetpTime = 0;
        pVib->LumbarBackSetpRepeat++;
        if(pVib->LumbarBackSetpRepeat >= VibTab[pVib->LumbarBackSetpNum].Repeat)
        {
          pVib->LumbarBackSetpRepeat = 0;
          pVib->LumbarBackSetpNum++;
          if(pVib->LumbarBackSetpNum >= VIB_TAB_NUM)
          {
            pVib->LumbarBackSetpNum = 0;
          }
        }
      } 
    }
    else  /*不使能*/
    {
      Vib_LumbarBackVibResetStep();
      pVib->CSFlag.Bit.LumbarBackRun = OFF;
    }

  }while(0);

  //BSP_IO_SetOutput_LumbarBackVibCtrl(pVib->CSFlag.Bit.LumbarBackRun, 0, VibTab[pVib->LumbarBackSetpNum].PWM);

  #endif
}


void Vib_AllPartsHandle(Ticker_t ExePeriod)                                                                                                         
{
  Vib_FeetVibHandle(ExePeriod);
  Vib_CalvesVibHandle(ExePeriod);  
  Vib_SeatVibHandle(ExePeriod);
  Vib_LumbarBackVibHandle(ExePeriod);
}


/*
========================================================================================================================
*         振动功能函数表                           振动功能函数表                           振动功能函数表
========================================================================================================================
*/
#define  VIB_TICK_COUNT_BUF_NUM   2
static Ticker_t Vib_TickCount[VIB_TICK_COUNT_BUF_NUM];

static const ESF_TmrExeFunc_t  Vib_TmrExeFuncTab[] = 
{
  /*   执行函数             执行周期(ms)        时间计数变量*/
  {Vib_AllPartsHandle,        100,            &Vib_TickCount[0]}

};

#define  VIB_TMR_EXE_FUNC_TAB_NUM     TAB_NUM(Vib_TmrExeFuncTab)


/*
************************************************************************************************************************
* 函数名称 : Vib_Handle                                                                                                         
* 功能描述 : 振动处理                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Vib_Handle(void)
{
  /*调度功能函数表------------------------------------------------*/
  ESF_TmrExeFuncScheduling(Vib_TmrExeFuncTab, VIB_TMR_EXE_FUNC_TAB_NUM);
}

/*
************************************************************************************************************************
* 函数名称 : Vib_Init                                                                                                         
* 功能描述 : 振动初始化                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 返回 可操作振动功能 的结构体 的指针                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
Vib_t*  Vib_Init(void)
{
  /*初始化相关数据------------------------------------------------------*/
  memset(pVib, 0, sizeof(Vib_t)); /*清零所有数据*/

  /*检测 Vib_TmrExeFuncTab 功能函数表排列是否正确-----------------------*/
  ESF_TmrExeFuncTabCheck(Vib_TmrExeFuncTab, VIB_TMR_EXE_FUNC_TAB_NUM, VIB_TICK_COUNT_BUF_NUM);

  return pVib;
}

/*
************************************************************************************************************************
* 函数名称 : Vib_GetCSFlag                                                                                                        
* 功能描述 : 获得 控制 与 状态 标识                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 控制与状态标识 的结构体                                                                
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
VibCSFlag_t Vib_GetCSFlag(void)
{
  return pVib->CSFlag;
}


/*
************************************************************************************************************************
* 函数名称 : Vib_CDPDataObjRx_0x4A                                                                                      
* 功能描述 : 0x4A 腿脚振动控制(中心板<-->腿脚控制板）
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象中数据的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t Vib_CDPDataObjRx_0x4A(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  /*更新数据到中心板-------------------------------------------------------------*/
  memcpy((uint8_t *)&pVib->SetQry0x4A, &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* 函数名称 : Vib_CDPDataObjTx_0x4A                                                                                      
* 功能描述 : 0x4A 腿脚振动控制(中心板<-->腿脚控制板）
* 输入参数 : 无
* 返回参数 : 成功则返回要发送的数据的内存首地址，失败返回NULL空指针
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t* Vib_CDPDataObjTx_0x4A(void)
{
  pVib->SetQry0x4A.DataLen = sizeof(pVib->SetQry0x4A);  
  pVib->SetQry0x4A.DataID = 0x4A;  

  return (uint8_t *)&pVib->SetQry0x4A;
}

