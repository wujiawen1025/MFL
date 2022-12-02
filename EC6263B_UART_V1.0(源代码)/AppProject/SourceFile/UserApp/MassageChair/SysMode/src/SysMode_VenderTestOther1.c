/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: SysMode_VenderTestOther.c 
**
**    功能描述: 系统模式 之  其他拷机 1
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
* 函数名称 : TestOther1_Key_Power                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t TestOther1_Key_Power(uint8_t *pData)
{
  return SysMode_Standby_Enter(SYS_MODE_INSPECTAUTO, TRUE);
}

/*
************************************************************************************************************************
* 函数名称 : TestOther1_Key_SpikeFeetUp                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                 
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t TestOther1_Key_SpikeFeetUp(uint8_t *pData)
{
  Spike_SetFeetAngle(Spike_GetFeetAngle() + 1);
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : TestOther1_Key_SpikeFeetDown                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                 
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t TestOther1_Key_SpikeFeetDown(uint8_t *pData)
{
  if(Spike_GetFeetAngle() > 0)
  {
    Spike_SetFeetAngle(Spike_GetFeetAngle() - 1);
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : TestOther1_Key_SpikeBackUpFeetDown                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                 
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t TestOther1_Key_SpikeBackUpFeetDown(uint8_t *pData)
{
  if(Spike_GetBackAngle() > 0)
  {
    Spike_SetBackAngle(Spike_GetBackAngle() - 1);
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : TestOther1_Key_SpikeBackDownFeetUp                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                 
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t TestOther1_Key_SpikeBackDownFeetUp(uint8_t *pData)
{
  Spike_SetBackAngle(Spike_GetBackAngle() + 1);
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : TestOther1_Key_CoreWidth                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t TestOther1_Key_CoreWidth(uint8_t *pData)
{
  pMChair->MannualCoreWidth++;
  if(pMChair->MannualCoreWidth > PX_MAX)
  {
    pMChair->MannualCoreWidth = PX_MIN;
  }
  Core_SetXPosition(pMChair->MannualCoreWidth); 
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : TestOther1_Key_CoreMannualUp                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t TestOther1_Key_CoreMannualUp(uint8_t *pData)
{
  if(Core_GetYPosition() > PY_MIN)
  {
    Core_SetYPosition(Core_GetYPosition()-1); 
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : TestOther1_Key_CoreMannualDown                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t TestOther1_Key_CoreMannualDown(uint8_t *pData)
{
  Core_SetYPosition(Core_GetYPosition()+1); 
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : TestOther1_Key_CoreMannualFront                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t TestOther1_Key_CoreMannualFront(uint8_t *pData)
{
  if(pMChair->MannualCoreFlexLevel < PZ_MAX)
  {
    pMChair->MannualCoreFlexLevel++;
  }
  Core_SetZPosition(pMChair->MannualCoreFlexLevel); 
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : TestOther1_Key_CoreMannualBack                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t TestOther1_Key_CoreMannualBack(uint8_t *pData)
{
  if(pMChair->MannualCoreFlexLevel > PZ_MIN)
  {
    pMChair->MannualCoreFlexLevel--;
  }
  Core_SetZPosition(pMChair->MannualCoreFlexLevel); 
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : TestOther1_Key_CoreFlexLevel                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t TestOther1_Key_CoreFlexLevel(uint8_t *pData)
{
  pMChair->MannualCoreFlexLevel++;
  if(pMChair->MannualCoreFlexLevel > PZ_MAX)
  {
    pMChair->MannualCoreFlexLevel = PZ_MIN;
  }
  Core_SetZPosition(pMChair->MannualCoreFlexLevel); 
  return SUCCESS;
}

/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
static const SysMode_KeyLogicTabItem_t TestOther1_KeyLogicTab[] = /*键值表*/
{
  /*附加操作：

    键值执行前：bit7 -- 1：ERP主电源关闭，则键值执行前，要重新开启。    
                        0：ERP主电源关闭，则键值执行前，不需要重新开启。    

    键值执行后：                                                   */

  {KEYVAL_Power,                    B(00000000),    TestOther1_Key_Power},

  {KEYVAL_SpikeFeetUp,              B(10000000),    TestOther1_Key_SpikeFeetUp},
  {KEYVAL_SpikeFeetDown,            B(10000000),    TestOther1_Key_SpikeFeetDown},
  {KEYVAL_SpikeBackUpFeetDown,      B(10000000),    TestOther1_Key_SpikeBackUpFeetDown},
  {KEYVAL_SpikeBackDownFeetUp,      B(10000000),    TestOther1_Key_SpikeBackDownFeetUp},

  {KEYVAL_CoreWidth,                B(00000000),    TestOther1_Key_CoreWidth},
  {KEYVAL_CoreMannualUp,            B(00000000),    TestOther1_Key_CoreMannualUp},
  {KEYVAL_CoreMannualDown,          B(00000000),    TestOther1_Key_CoreMannualDown},
  {KEYVAL_CoreMannualFront,         B(00000000),    TestOther1_Key_CoreMannualFront},
  {KEYVAL_CoreMannualBack,          B(00000000),    TestOther1_Key_CoreMannualBack},
  {KEYVAL_CoreFlexLevel,            B(00000000),    TestOther1_Key_CoreFlexLevel},

  /*---------------------------------------------------*/
  {KEYVAL_MAX,                      B(00000000),    NULL}
};

#define TESTOTHER1_KEY_TAB_NUM  TAB_NUM(TestOther1_KeyLogicTab)

static uint16_t TestOther1_GetKeyValID(uint16_t index)
{
  if(index > (TESTOTHER1_KEY_TAB_NUM-1))
  {
    return INDEX_NO_MATCH;
  }
  return TestOther1_KeyLogicTab[index].KeyValID;
}


/*
************************************************************************************************************************
* 函数名称 : SysMode_TestOther1_Timer                                                                                                         
* 功能描述 : 其他拷机 1 定时器 处理                                                                                     
* 输入参数 : ExePeriod -- 执行周期                                                                    
* 返回参数 : 无                                                           
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_TestOther1_Timer(Ticker_t ExePeriod)
{
  static  Ticker_t  SysPeriod;
  static  Ticker_t  Period;
  uint8_t zmax;
  static  uint8_t PauseOnOff = OFF;
  
  Heat_SetLumbarBackHeatWorkState(TRUE);
  
  SysPeriod++;
  if(SysPeriod > (3600+900)) 
  {
    SysPeriod = 0;             /*1h+15min 后重新计时*/
    PAUSE_OFF(&PauseOnOff, 0, Heat_LumbarBackHeatPauseOff);
    PAUSE_OFF(&PauseOnOff, 1, Core_PauseOff);
  }
  else if(SysPeriod > 3600)
  {
    PAUSE_ON(&PauseOnOff, 0, Heat_LumbarBackHeatPauseOn);
    PAUSE_ON(&PauseOnOff, 1, Core_PauseOn);
  }
  
  
  Core_SetAction(CORE_ACTION_EXE_MANNNUAL, KNIN, NO_FB_TAP);  
  Core_SetXYZActionSpeed(7);
  Core_SetTCSActionSpeed(5);

  if(Core_GetYPosition() <= 9)
  {
    zmax  = 4 ;
  }
  else if(Core_GetYPosition() <= 22)
  {
    zmax  = 3 ;
  }
  else 
  {
    zmax  = 2 ;
  }  
  
  Period += ExePeriod;
  if(Period < 5000)
  {
    Core_SetZPosition(0);
  }
  else if(Period < 10000)
  {
    Core_SetZPosition(zmax);
  }
  else
  {
    Period = 0;
  }
}

/*
************************************************************************************************************************
* 函数名称 : SysMode_TestOther1_Init                                                                                                         
* 功能描述 : 系统模式 之 其他拷机 1 初始化                                                                                     
* 输入参数 : 无                                                                               
* 返回参数 : 无                                                           
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_TestOther1_Init(void)
{

}


/*
************************************************************************************************************************
* 函数名称 : SysMode_TestOther1_Handle                                                                                                         
* 功能描述 : 系统模式 之 其他拷机 1 处理                                                                                     
* 输入参数 : 无                                                                              
* 返回参数 : 无                                                               
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_TestOther1_Handle(void)
{
  /*发生模式切换操作-----------------------------------------------------*/
  if(pMChair->SysModeHis != pMChair->SysModeCur)      
  {
    pMChair->SysModeHis = pMChair->SysModeCur; 
  }

  /*根据各个模式的不同，对键值处理相关变量赋值---------------------------*/
  pMChair->KeyValHandle.KeyLogicTab    = TestOther1_KeyLogicTab;      /*按键逻辑表*/
  pMChair->KeyValHandle.KeyLogicTabNum = TESTOTHER1_KEY_TAB_NUM;      /*按键逻辑表 大小*/
  pMChair->KeyValHandle.pGetMatchID    = TestOther1_GetKeyValID;      /*函数指针，指向的函数作用：返回表格条目 中 的要搜索的数据 所在的索引*/
  pMChair->KeyValHandle.pAddOp         = NULL;                        /*函数指针，指向的函数作用：键值执行前后的附加操作 */
}
