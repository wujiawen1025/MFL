/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称SysMode.c 
**
**    功能描述: 系统模式管理
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
#include "SysMode.h"

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


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : Default_Key_Power                                                                                                         
* 功能描述 :                                                                                         
* 输入参数 : pData -- 键值所附带的命令数据                                                                                     
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t Default_Key_Power(uint8_t *pData)
{
//  if(SYS_MODE_STANDBY == pMChair->SysModeCur) 
//  {
//    return SysMode_UserRun_Enter();
//  }
//  else
  {
    return SysMode_Standby_Enter(SYS_MODE_INSPECTAUTO, TRUE);    /*关机，复位推杆角度*/
  }
}


static const SysMode_KeyLogicTabItem_t Default_KeyLogicTab[] = /*默认键值表*/
{
  {KEYVAL_Power,                  B(00000000),    Default_Key_Power},

  /*---------------------------------------------------*/
  {KEYVAL_MAX,                    B(00000000),    NULL}
};

#define DEFAULT_KEY_TAB_NUM  TAB_NUM(Default_KeyLogicTab)

static uint16_t Default_GetKeyValID(uint16_t index)
{
  if(index > (DEFAULT_KEY_TAB_NUM-1))
  {
    return INDEX_NO_MATCH;
  }
  return Default_KeyLogicTab[index].KeyValID;
}

/*
************************************************************************************************************************
* 函数名称 : Default_KeyValAdditonOp                                                                                                         
* 功能描述 : 键值执行前后的附加操作                                                                                    
* 输入参数 : Index       -- 键值在表格里的索引
*            BeforeAfter -- BEFORE：键值执行前执行附加操作
*                           AFTER：键值执行后执行附加操作   
*            CurExeState -- 当前执行状态。 SUCCESS 成功   FAIL 失败 
* 返回参数 : SUCCESS -- 可执行后续键值操作。
*            FAIL    -- 不可执行后续键值操作。                                                            
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t Default_KeyValAdditonOp(uint8_t Index, uint8_t BeforeAfter, uint8_t CurExeState)
{
  uint8_t ret;

  
  ret = SUCCESS;                                                 /*先假设成功*/

  /*键值执行前的附加操作---------------------------------------------------*/
  if(BEFORE == BeforeAfter)                    
  {

  }
  
  /*键值执行后的附加操作---------------------------------------------------*/
  else 
  {
    if((SUCCESS == CurExeState) &&                               /*键值成功执行*/
       (Default_KeyLogicTab[Index].KeyValID != KEYVAL_NoPress))  /*有按键按下*/
    {
      pMChair->PromptToneTLMs = 300;                             /*键值成功执行，则开提示音*/
    }
  }

  return ret;  
}

/*
************************************************************************************************************************
* 函数名称 : SysMode_DefaultKeyValHandle                                                                                                         
* 功能描述 : 系统模式默认的键值处理                                                                             
* 输入参数 : 无                                                                      
* 返回参数 : 无                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_DefaultKeyValHandle(void)
{
  pMChair->KeyValHandle.KeyLogicTab    = Default_KeyLogicTab;            /*按键逻辑表*/
  pMChair->KeyValHandle.KeyLogicTabNum = DEFAULT_KEY_TAB_NUM;            /*按键逻辑表 大小*/
  pMChair->KeyValHandle.pGetMatchID    = Default_GetKeyValID;            /*函数指针，指向的函数作用：返回表格条目 中 的要搜索的数据 所在的索引*/
  pMChair->KeyValHandle.pAddOp         = Default_KeyValAdditonOp;        /*函数指针，指向的函数作用：键值执行前后的附加操作 */
}

 
/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/

/*
************************************************************************************************************************
* 函数名称 : ERPPower_OnHandle                                                                                                         
* 功能描述 : ERP电源 开启的处理                                                                                        
* 输入参数 : ExePeriod -- 函数执行周期                                                                                       
* 返回参数 : 无                                                                
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void ERPPower_OnHandle(Ticker_t ExePeriod)
{
  pMChair->ERPPowerSw = ON;    
  pMChair->ERPPowerOffWaitTimeMs = 0;
  if((pMChair->ERPPowerOnTimeMs < 10000) && 
     (ON == pMChair->ERPPowerSw)         )
  {
    pMChair->ERPPowerOnTimeMs += ExePeriod;
  }
}

/*
************************************************************************************************************************
* 函数名称 : ERPPower_OffHandle                                                                                                         
* 功能描述 : ERP电源 关闭的处理                                                                                        
* 输入参数 : ExePeriod -- 函数执行周期                                                                                       
* 返回参数 : 无                                                                
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void ERPPower_OffHandle(Ticker_t ExePeriod)
{
  if((pMChair->ERPPowerOnTimeMs < 10000) && 
     (ON == pMChair->ERPPowerSw)         )
  {
    pMChair->ERPPowerOnTimeMs += ExePeriod;
  }

  if(pMChair->ERPPowerOffWaitTimeMs < 65000)
  {
    pMChair->ERPPowerOffWaitTimeMs += ExePeriod;
  }

  /*推杆和机芯还在工作，则暂缓关闭*/
  if((TRUE == pMChair->StateBackSpike.Bit.Work)     ||  
     (TRUE == pMChair->StateZeroSpike.Bit.Work)     ||
     (TRUE == pMChair->StateFeetSpike.Bit.Work)     ||
     (TRUE == pMChair->StateLegFlexSpike.Bit.Work) ||   
     (TRUE == pMChair->StateXMotor.Bit.Work)        ||
     (TRUE == pMChair->StateYMotor.Bit.Work)        ||
     (TRUE == pMChair->StateZMotor.Bit.Work)        ||
     (TRUE == pMChair->StateCDPCSFlag.Bit.RepeaterWork))/*中心板处于数据包转发状态，其他模块必须保证供电中*/ 
  {
    pMChair->ERPPowerSw = ON;               /*开启主电源*/
    pMChair->ERPPowerOffWaitTimeMs = 0;
  }
  /*机芯与推杆无任何动作，超过5s，关闭主电源*/
  else if(pMChair->ERPPowerOffWaitTimeMs > 5000) 
  {
    pMChair->ERPPowerSw = OFF;              /*关闭主电源*/
    pMChair->ERPPowerOnTimeMs = 0;
    //BSP_IO_Init();
  }
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_ERPHandle                                                                                                         
* 功能描述 : ERP功耗控制                                                                                        
* 输入参数 : ExePeriod -- 函数执行周期                                                                                       
* 返回参数 : 无                                                                
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_ERPPowerHandle(Ticker_t ExePeriod)
{
  switch(pMChair->SysModeCur)
  {
    case SYS_MODE_STANDBY:
    {
      ERPPower_OffHandle(ExePeriod);
    }break;

    case SYS_MODE_USERRUN:
    {
      ERPPower_OnHandle(ExePeriod);
    }break;

    /*所有工程模式不关ERP电源*/
    default: 
    {
      ERPPower_OnHandle(ExePeriod);
    }break;
  }

  BSP_IO_SetOutput_ERPPowerSw(pMChair->ERPPowerSw);
}

/*
************************************************************************************************************************
* 函数名称 : SysMode_OnOffKeyCheck                                                                                                         
* 功能描述 : 开关机按键检测                                                                                        
* 输入参数 : ExePeriod -- 函数执行周期                                                                                       
* 返回参数 : 无                                                                
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_OnOffKeyCheck(Ticker_t ExePeriod)
{
  static  uint16_t  ValidTimeMs;


  if(ON_OFF_KEY_VALID_LEVEL == BSP_IO_ReadInput_PowerKeyState())
  { 
    if(ValidTimeMs < 10000)
    ValidTimeMs += ExePeriod;
  }
  else
  {
    ValidTimeMs = 0;                                    /*按键释放*/
  }

  if((ValidTimeMs > 200) && (ValidTimeMs != 0xFFFF))
  {
    if(pMChair->SysModeCur != SYS_MODE_STANDBY) 
    {
      SysMode_Standby_Enter(SYS_MODE_USERRUN, TRUE);    /*关机，复位推杆角度*/  
      ValidTimeMs = 0xFFFF;                             /*防止按键还未释放，就一直重复切换系统模式*/
    }
    else
    {
      if(SUCCESS == SysMode_UserRun_Enter())
      {
        ValidTimeMs = 0xFFFF;                           /*防止按键还未释放，就一直重复切换系统模式*/
      }
    }
  }
}


/*
************************************************************************************************************************
* 函数名称 : SysMode_PauseHandle                                                                                                         
* 功能描述 : 暂停处理                                                                                        
* 输入参数 : ExePeriod -- 函数执行周期                                                                                       
* 返回参数 : 无                                                                
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_PauseHandle(Ticker_t ExePeriod)
{
  static uint8_t CoreGasSpikePauseOnOff = OFF;
  static uint8_t Other1PauseOnOff = OFF;
  static uint8_t Other2PauseOnOff = OFF;
  
  if(TRUE == pMChair->CSFlag.Bit.Pause)/*暂停所有部件的功能*/
  {
    PAUSE_ON(&CoreGasSpikePauseOnOff, 0, Core_PauseOn);
    PAUSE_ON(&CoreGasSpikePauseOnOff, 1, Gas_PauseOn);
    PAUSE_ON(&CoreGasSpikePauseOnOff, 2, BackSpike_PauseOn);
    PAUSE_ON(&CoreGasSpikePauseOnOff, 3, ZeroSpike_PauseOn);
    PAUSE_ON(&CoreGasSpikePauseOnOff, 4, FeetSpike_PauseOn);
    if(pMChair->CSFlag.Bit.LegFlexTestSw != TRUE)
    {
      PAUSE_ON(&CoreGasSpikePauseOnOff, 5, LegFlexSpike_PauseOn);
    }
    PAUSE_ON(&CoreGasSpikePauseOnOff, 6, BodyScan_PauseOn);

    PAUSE_ON(&Other1PauseOnOff,       0, Vib_FeetVibPauseOn);
    PAUSE_ON(&Other1PauseOnOff,       1, Vib_CalvesVibPauseOn);
    PAUSE_ON(&Other1PauseOnOff,       2, Vib_SeatVibPauseOn);
    PAUSE_ON(&Other1PauseOnOff,       3, Vib_LumbarBackVibPauseOn);
    PAUSE_ON(&Other1PauseOnOff,       4, Roller_FeetRollerPauseOn);
    PAUSE_ON(&Other1PauseOnOff,       5, Roller_CalvesRollerPauseOn);
    
    PAUSE_ON(&Other2PauseOnOff,       0, Heat_FeetHeatPauseOn);
    PAUSE_ON(&Other2PauseOnOff,       1, Heat_CalvesHeatPauseOn);
    PAUSE_ON(&Other2PauseOnOff,       2, Heat_SeatHeatPauseOn);
    PAUSE_ON(&Other2PauseOnOff,       3, Heat_LumbarBackHeatPauseOn);
    PAUSE_ON(&Other2PauseOnOff,       4, Led_PauseOn);
  }
  else
  {
    PAUSE_OFF(&CoreGasSpikePauseOnOff, 0, Core_PauseOff);
    PAUSE_OFF(&CoreGasSpikePauseOnOff, 1, Gas_PauseOff);
    PAUSE_OFF(&CoreGasSpikePauseOnOff, 2, BackSpike_PauseOff);
    PAUSE_OFF(&CoreGasSpikePauseOnOff, 3, ZeroSpike_PauseOff);
    PAUSE_OFF(&CoreGasSpikePauseOnOff, 4, FeetSpike_PauseOff);
    if(pMChair->CSFlag.Bit.LegFlexTestSw != TRUE)
    {
      PAUSE_OFF(&CoreGasSpikePauseOnOff, 5, LegFlexSpike_PauseOff);
    }
    PAUSE_OFF(&CoreGasSpikePauseOnOff, 6, BodyScan_PauseOff);
    
    PAUSE_OFF(&Other1PauseOnOff,       0, Vib_FeetVibPauseOff);
    PAUSE_OFF(&Other1PauseOnOff,       1, Vib_CalvesVibPauseOff);
    PAUSE_OFF(&Other1PauseOnOff,       2, Vib_SeatVibPauseOff);
    PAUSE_OFF(&Other1PauseOnOff,       3, Vib_LumbarBackVibPauseOff);
    PAUSE_OFF(&Other1PauseOnOff,       4, Roller_FeetRollerPauseOff);
    PAUSE_OFF(&Other1PauseOnOff,       5, Roller_CalvesRollerPauseOff);
    
    PAUSE_OFF(&Other2PauseOnOff,       0, Heat_FeetHeatPauseOff);
    PAUSE_OFF(&Other2PauseOnOff,       1, Heat_CalvesHeatPauseOff);
    PAUSE_OFF(&Other2PauseOnOff,       2, Heat_SeatHeatPauseOff);
    PAUSE_OFF(&Other2PauseOnOff,       3, Heat_LumbarBackHeatPauseOff);
    PAUSE_OFF(&Other2PauseOnOff,       4, Led_PauseOff);
  }
}

/*
========================================================================================================================
*      系统模式 功能函数 管理表                 系统模式 功能函数 管理表                  系统模式 功能函数 管理表
========================================================================================================================
*/
#define  SYSMODE_TICK_COUNT_BUF_NUM   13
static Ticker_t SysMode_TickCount[SYSMODE_TICK_COUNT_BUF_NUM];

static const ESF_TmrExeFunc_t  SysMode_TmrExeFuncTab[] = 
{
  /*   执行函数                  执行周期(ms)  时间计数变量*/

  {SysMode_PauseHandle,                       13,        &SysMode_TickCount[0]},  /*暂停处理*/
  {SysMode_ERPPowerHandle,                    19,        &SysMode_TickCount[1]},  /*ERP电源功耗控制*/

  {SysMode_UserRun_Timer,                     1000,      &SysMode_TickCount[2]},  /*按摩定时器处理*/
  {SysMode_InspectAuto_Timer,                 1000,      &SysMode_TickCount[3]},  /*自检*/
  {SysMode_InspectManual_Timer,               1000,      &SysMode_TickCount[4]},  /*手检*/
  {SysMode_TestSpike_Timer,                   1000,      &SysMode_TickCount[5]},  /*拷机推杆*/
  {SysMode_InspectOther1_Timer,               1000,      &SysMode_TickCount[6]},  /*其他厂家检测 1*/
  {SysMode_InspectOther2_Timer,               1000,      &SysMode_TickCount[7]},  /*其他厂家检测 2*/

  {SysMode_OnOffKeyCheck,                     111,       &SysMode_TickCount[10]},  /*开关机按键检测*/
  {MChair_FuncExe,                            20,        &SysMode_TickCount[11]},  /*按摩功能的执行*/
  
  {SysMode_StandBy_EngiModeSelcetTLHandle,    1011,      &SysMode_TickCount[12]}   /*工程模式选择时间长度处理 */
}; 

#define  SYSMODE_TMR_EXE_FUNC_TAB_NUM     TAB_NUM(SysMode_TmrExeFuncTab)


/*
************************************************************************************************************************
* 函数名称 : SysMode_Init                                                                                                         
* 功能描述 : 系统模式  初始化                                                                                        
* 输入参数 : 无                                                                                     
* 返回参数 : 无                                                                
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_Init(void)
{
  SysMode_Standby_Init();
  SysMode_UserRun_Init();
  SysMode_InspectAuto_Init();
  SysMode_InspectManual_Init();
  SysMode_TestSpike_Init();
  SysMode_InspectOther1_Init();
  SysMode_InspectOther2_Init();
  SysMode_Standby_Enter(SYS_MODE_NONE, TRUE);    /*上电初始时 进入待机模式*/

  /*检测 SysMode_TmrExeFuncTab 功能函数表排列是否正确------------------------*/
  ESF_TmrExeFuncTabCheck(SysMode_TmrExeFuncTab, SYSMODE_TMR_EXE_FUNC_TAB_NUM, SYSMODE_TICK_COUNT_BUF_NUM);
}

/*
************************************************************************************************************************
* 函数名称 : SysMode_Pause_Handle                                                                                                         
* 功能描述 : 系统模式 处理                                                                                        
* 输入参数 : 无                                                                                     
* 返回参数 : 无                                                                
* 补充说明 : 上电默认进入 SYS_MODE_STANDBY 待机模式（关机模式）                                                                                                         
************************************************************************************************************************
*/
static const SysModeHandleItem_t SysModeHandleTab[] = 
{
  {SYS_MODE_STANDBY,            SysMode_Standby_Handle},         /*待机*/

  /*这三个差别不大，共用SysMode_UserRun_Handle，差别在 SysMode_UserRun_Timer()函数中处理*/
  {SYS_MODE_USERRUN,            SysMode_UserRun_Handle},         /*用户运行*/
  {SYS_MODE_TESTNOTIMER,        SysMode_UserRun_Handle},         /*厂家考机 之 无定时测试模式, 做温升拷机用*/
  {SYS_MODE_TESTAGE,            SysMode_UserRun_Handle},         /*厂家考机 之 寿命， 动一小时，停15分钟*/

  {SYS_MODE_INSPECTAUTO,        SysMode_InspectAuto_Handle},     /*厂家自检*/
  {SYS_MODE_INSPECTMANUAL,      SysMode_InspectManual_Handle},   /*厂家手检*/
  {SYS_MODE_TESTSPIKE,          SysMode_TestSpike_Handle},       /*厂家考机 之 推杆*/
  {SYS_MODE_PACKING,            SysMode_Packing_Handle},         /*厂家包装*/
  {SYS_MODE_INSPECTOTHER1,      SysMode_InspectOther1_Handle},   /*其他厂家检测 1*/
  {SYS_MODE_INSPECTOTHER2,      SysMode_InspectOther2_Handle}    /*其他厂家检测 2*/
};

#define  SYSMODE_HANDLE_TAB_NUM    TAB_NUM(SysModeHandleTab)

void SysMode_Handle(void)
{
  uint8_t i;

  /*系统模式处理-------------------------------------------------*/
  for(i=0; i<SYSMODE_HANDLE_TAB_NUM; i++)
  {
    if(pMChair->SysModeCur == SysModeHandleTab[i].Mode)
    {
      if(SysModeHandleTab[i].pHandle != NULL)
      {
        SysModeHandleTab[i].pHandle();        /*进入到各个具体的模式处理函数*/
      }
      break;
    }
  }

  if(i >= SYSMODE_HANDLE_TAB_NUM)             /*SysModeCur值错误，则修正到待机模式*/
  {
    pMChair->SysModeCur = SYS_MODE_STANDBY;
  }

  if(SYS_MODE_STANDBY == pMChair->SysModeCur) 
  {
    pMChair->CSFlag.Bit.SysRun = FALSE;       /*待机模式*/
  }
  else
  {
    pMChair->CSFlag.Bit.SysRun = TRUE;        /*系统运行，非 待机模式*/
  }

  /*调度功能函数表------------------------------------------------*/
  ESF_TmrExeFuncScheduling(SysMode_TmrExeFuncTab, SYSMODE_TMR_EXE_FUNC_TAB_NUM);
}
