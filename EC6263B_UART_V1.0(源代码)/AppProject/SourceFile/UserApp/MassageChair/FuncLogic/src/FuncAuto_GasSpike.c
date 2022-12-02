/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：FuncAuto_GasSpike.c 
**
**    功能描述:【充气+推杆】自动
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
#include "FuncLogic.h"
#include "FuncTab.h"
#include "MChair.h"


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
*【变量定义 & 各种声明】                          【变量定义 & 各种声明】                         【变量定义 & 各种声明】    
========================================================================================================================
*/
static uint16_t        GasSpikeAutoTabIndex;
static ActionTabStep_t GasSpikeAutoTabStep;

static const ActionTabAttr_t   GasSpikeAutoAttrTab[] =
{
  /*---------------------------------------------------------------*/
  { 
    FA_GASSPIKE_NONE,                                    /*动作ID */
    (void*)0,                                            /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_ROLLER_NONE,                                     /*脚滚 伴随模式*/
    FMA_ROLLER_NONE,                                     /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },

  /*表格体验调试--------表格体验调试--------表格体验调试--------表格体验调试*/
  { 
    FA_GASSPIKE_TRY,                                     /*动作ID */
    (void*)0,                                            /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_FEET_VIB_ByActionTab,                            /*脚振 伴随模式*/
    FMA_CALVES_VIB_ByActionTab,                          /*腿振 伴随模式*/
    FMA_SEAT_VIB_ByActionTab,                            /*座振 伴随模式*/
    FMA_LUMBARBACK_VIB_ByActionTab,                      /*腰背振 伴随模式*/
    FMA_FEET_ROLLER_ByActionTab,                         /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByActionTab,                       /*腿滚 伴随模式*/
    FMA_FEET_HEAT_ByActionTab,                           /*脚热 伴随模式*/
    FMA_CALVES_HEAT_ByActionTab,                         /*腿热 伴随模式*/
    FMA_SEAT_HEAT_ByActionTab,                           /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByActionTab,                     /*腰背热 伴随模式*/
    FMA_LED_ByActionTab                                  /*灯   伴随模式*/
  }
};

#define GASSPIKE_AUTO_TAB_NUM    TAB_NUM(GasSpikeAutoAttrTab)


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : MChair_FuncSwitch_GasSpikeAuto                                                                                                
* 功能描述 : 按摩椅 功能切换 之  【充气+推杆】自动                                                      
* 输入参数 : SwitchMode -- 要切换模式
*            pFuncLogic -- 功能逻辑的描述                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_GasSpikeAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  GasSpikeAutoTabIndex = MChair_FuncSwitch_CloseForNewFunc(pFuncLogic, GasSpikeAutoAttrTab, GASSPIKE_AUTO_TAB_NUM, &GasSpikeAutoTabStep);
}

/*
************************************************************************************************************************
* 函数名称 : MChair_FuncExe_GasSpikeAuto                                                                                           
* 功能描述 : 按摩椅 功能执行 之  【充气+推杆】自动                                                       
* 输入参数 : ExePeriod  -- 执行周期
*            pFuncLogic -- 指向自身功能逻辑的指针。                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_GasSpikeAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  if((0x00                  == GasSpikeAutoTabIndex) ||   
     (INDEX_NO_MATCH        == GasSpikeAutoTabIndex) ||
     (GASSPIKE_AUTO_TAB_NUM <= GasSpikeAutoTabIndex) )
  {
    return;                                                /*表格索引无效，则无功能*/
  }

  pMChair->ComponentFuncState.Bit.Gas   = FUNC_TYPE_AUTO;  /*充气功能状态：自动*/
  pMChair->ComponentFuncState.Bit.Spike = FUNC_TYPE_AUTO;  /*推杆功能状态：自动*/

  pMChair->CSFlag.Bit.BackSpikeMannualMoveDisable = TRUE;  /*靠背推杆手动无效*/
  pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable = TRUE;  /*零重力推杆手动无效*/
  pMChair->CSFlag.Bit.FeetSpikeMannualMoveDisable = TRUE;  /*小腿推杆手动无效*/
  pMChair->CSFlag.Bit.LegFlexMannualMoveDisable   = TRUE;  /*小腿伸缩手动无效*/
  pMChair->CSFlag.Bit.GasCooperateSpikeRun        = TRUE;  /*有充气配合推杆的动作*/

  Gas_AllCtrlEn();                                         /*所有部位充气控制使能*/ 
  MChair_TabHandle_GasSpikeAuto(ExePeriod, (ActionTabAttr_t *)&GasSpikeAutoAttrTab[GasSpikeAutoTabIndex], &GasSpikeAutoTabStep);
}
