/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：FuncAuto_CoreSpike.c 
**
**    功能描述:【机芯+推杆】自动
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
static uint16_t        CoreSpikeAutoTabIndex;
static ActionTabStep_t CoreSpikeAutoTabStep;

static const ActionTabAttr_t   CoreSpikeAutoAttrTab[] =
{
  /*---------------------------------------------------------------*/
  { 
    FA_CORESPIKE_NONE,                                   /*动作ID */
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
    FA_CORESPIKE_TRY,                                    /*动作ID */
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


#define CORESPIKE_AUTO_TAB_NUM    TAB_NUM(CoreSpikeAutoAttrTab)


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : MChair_FuncSwitch_CoreSpikeAuto                                                                                                
* 功能描述 : 按摩椅 功能切换 之  【机芯+推杆】自动                                                      
* 输入参数 : SwitchMode -- 要切换模式
*            pFuncLogic -- 功能逻辑的描述                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_CoreSpikeAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  CoreSpikeAutoTabIndex = MChair_FuncSwitch_CloseForNewFunc(pFuncLogic, CoreSpikeAutoAttrTab, CORESPIKE_AUTO_TAB_NUM, &CoreSpikeAutoTabStep);
}

/*
************************************************************************************************************************
* 函数名称 : MChair_FuncExe_CoreSpikeAuto                                                                                           
* 功能描述 : 按摩椅 功能执行 之  【机芯+推杆】自动                                                       
* 输入参数 : ExePeriod  -- 执行周期
*            pFuncLogic -- 指向自身功能逻辑的指针。                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_CoreSpikeAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  if((0x00                   == CoreSpikeAutoTabIndex) ||   
     (INDEX_NO_MATCH         == CoreSpikeAutoTabIndex) ||
     (CORESPIKE_AUTO_TAB_NUM <= CoreSpikeAutoTabIndex) )
  {
    return;                                                /*表格索引无效，则无功能*/
  }

  pMChair->ComponentFuncState.Bit.Core  = FUNC_TYPE_AUTO;  /*机芯功能状态：自动*/
  pMChair->ComponentFuncState.Bit.Spike = FUNC_TYPE_AUTO;  /*推杆功能状态：自动*/

  if(FALSE == pMChair->StateBodyScan.Bit.Finish)           /*人体扫描未完成*/
  {
    return;
  }


  pMChair->CSFlag.Bit.BackSpikeMannualMoveDisable = TRUE;  /*靠背推杆手动无效*/
  pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable = TRUE;  /*零重力推杆手动无效*/
  pMChair->CSFlag.Bit.FeetSpikeMannualMoveDisable = TRUE;  /*小腿推杆手动无效*/
  pMChair->CSFlag.Bit.LegFlexMannualMoveDisable   = TRUE;  /*小腿伸缩手动无效*/
  MChair_TabHandle_CoreSpikeAuto(ExePeriod, (ActionTabAttr_t *)&CoreSpikeAutoAttrTab[CoreSpikeAutoTabIndex], &CoreSpikeAutoTabStep);

}
