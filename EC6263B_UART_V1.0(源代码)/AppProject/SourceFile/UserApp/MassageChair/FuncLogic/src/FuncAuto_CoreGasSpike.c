/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：FuncAuto_CoreGasSpike.c 
**
**    功能描述:【机芯+充气+推杆】自动
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
static uint16_t        CoreGasSpikeAutoTabIndex;
static ActionTabStep_t CoreGasSpikeAutoTabStep;

static const ActionTabAttr_t   CoreGasSpikeAutoAttrTab[] =
{
  /*RollerVibAccompanyBit 滚&振伴随有无 ： b0 坐部振动  b1 腰背振动   b4 脚滚 */
  /*LedHeatAccompanyBit   灯&热伴随有无 ： b0 腰背加热  b1 脚部加热 */

  /*---------------------------------------------------------------*/
  { 
    FA_COREGASSPIKE_NONE,                                /*动作ID */
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
  
//  /*----------------------------------------------------------------------------------------------------------*/
//  { 
//    FA_COREGASSPIKE_Thai,                                /*动作ID */
//    (void*)CoreGasSpikeAutoTab_Thai,                     /*动作表格*/
//    0,                                                   /*开始步骤*/
//    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
//    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
//    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
//    FMA_VIB_NONE,                                        /*座振 伴随模式*/
//    FMA_LUMBARBACK_VIB_ByActionTab,                      /*腰背振 伴随模式*/
//    FMA_FEET_ROLLER_ByTime_On150s_Off120s,               /*脚滚 伴随模式*/
//    FMA_CALVES_ROLLER_ByTime_On90s_Off120s,              /*腿滚 伴随模式*/
//    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
//    FMA_CALVES_HEAT_ByTime_On120s_Off180s,               /*腿热 伴随模式*/
//    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
//    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
//    FMA_LED_NONE                                         /*灯   伴随模式*/
//  },
  
  /*表格体验调试--------表格体验调试--------表格体验调试--------表格体验调试*/
  { 
    FA_COREGASSPIKE_TRY,                                 /*动作ID */
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


#define COREGASSPIKE_AUTO_TAB_NUM    TAB_NUM(CoreGasSpikeAutoAttrTab)


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : MChair_FuncSwitch_CoreGasSpikeAuto                                                                                                
* 功能描述 : 按摩椅 功能切换 之  【机芯+充气+推杆】自动                                                      
* 输入参数 : SwitchMode -- 要切换模式
*            pFuncLogic -- 功能逻辑的描述                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_CoreGasSpikeAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  CoreGasSpikeAutoTabIndex = MChair_FuncSwitch_CloseForNewFunc(pFuncLogic, CoreGasSpikeAutoAttrTab, COREGASSPIKE_AUTO_TAB_NUM, &CoreGasSpikeAutoTabStep);
  if(CLOSE == SwitchMode)
  {
    Spike_SetAngle(PBACK_USER_ANGLE, PFEET_USER_ANGLE, PZERO_USER_ANGLE);  /*开机角度*/
  }
}

/*
************************************************************************************************************************
* 函数名称 : MChair_FuncExe_CoreGasSpikeAuto                                                                                           
* 功能描述 : 按摩椅 功能执行 之  【机芯+充气+推杆】自动                                                       
* 输入参数 : ExePeriod  -- 执行周期
*            pFuncLogic -- 指向自身功能逻辑的指针。                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_CoreGasSpikeAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  if((0x00                      == CoreGasSpikeAutoTabIndex) ||   
     (INDEX_NO_MATCH            == CoreGasSpikeAutoTabIndex) ||
     (COREGASSPIKE_AUTO_TAB_NUM <= CoreGasSpikeAutoTabIndex) )
  {
    return;                                                /*表格索引无效，则无功能*/
  }

  pMChair->ComponentFuncState.Bit.Core  = FUNC_TYPE_AUTO;  /*机芯功能状态：自动*/
  pMChair->ComponentFuncState.Bit.Gas   = FUNC_TYPE_AUTO;  /*充气功能状态：自动*/
  pMChair->ComponentFuncState.Bit.Spike = FUNC_TYPE_AUTO;  /*推杆功能状态：自动*/

  if(FALSE == pMChair->StateBodyScan.Bit.Finish)           /*人体扫描未完成*/
  {
    return;
  }

  pMChair->CSFlag.Bit.BackSpikeMannualMoveDisable = TRUE;  /*靠背推杆手动无效*/
  pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable = TRUE;  /*零重力推杆手动无效*/
  pMChair->CSFlag.Bit.FeetSpikeMannualMoveDisable = TRUE;  /*小腿推杆手动无效*/
  pMChair->CSFlag.Bit.LegFlexMannualMoveDisable   = TRUE;  /*小腿伸缩手动无效*/
  pMChair->CSFlag.Bit.GasCooperateSpikeRun        = TRUE;  /*有充气配合推杆的动作*/

  Gas_AllCtrlEn();                                         /*控制所有部位的充气*/
  MChair_TabHandle_CoreGasSpikeAuto(ExePeriod, (ActionTabAttr_t *)&CoreGasSpikeAutoAttrTab[CoreGasSpikeAutoTabIndex], &CoreGasSpikeAutoTabStep);
}
