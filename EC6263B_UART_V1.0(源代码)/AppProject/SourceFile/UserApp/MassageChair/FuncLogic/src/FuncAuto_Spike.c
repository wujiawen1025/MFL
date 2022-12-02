/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：FuncAuto_Spike.c 
**
**    功能描述:【推杆】自动
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
static  uint8_t SpikeAutoNeedCloseAngle;    
static uint16_t        SpikeAutoTabIndex;
static ActionTabStep_t SpikeAutoStep;

static const ActionTabAttr_t   SpikeAutoAttrTab[] =
{
  /* 单纯的推杆自动 与 其他的自动功能处理不太一样。
   * 单纯的推杆自动 没有伴随功能，而且只是单纯的调节推杆角度而已(零重力)*/

  /*---------------------------------------------------------------*/
  { 
    FA_SPIKE_NONE,                                       /*动作ID */
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
  
//  /*---------------------------------------------------------------*/
//  { 
//    FA_SPIKE_UserRun,                                    /*动作ID */
//    (void*)SpikeAutoTab_UserRun,                         /*动作表格*/
//    0,                                                   /*开始步骤*/
//    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
//    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
//    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
//    FMA_VIB_NONE,                                        /*座振 伴随模式*/
//    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
//    FMA_ROLLER_NONE,                                     /*脚滚 伴随模式*/
//    FMA_ROLLER_NONE,                                     /*腿滚 伴随模式*/
//    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
//    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
//    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
//    FMA_HEAT_NONE,                                       /*腰背热 伴随模式*/
//    FMA_LED_NONE                                         /*灯   伴随模式*/
//  },
//  
//  /*---------------------------------------------------------------*/
//  { 
//    FA_SPIKE_ExeMassage,                                 /*动作ID */
//    (void*)SpikeAutoTab_ExeMassage,                      /*动作表格*/
//    0,                                                   /*开始步骤*/
//    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
//    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
//    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
//    FMA_VIB_NONE,                                        /*座振 伴随模式*/
//    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
//    FMA_ROLLER_NONE,                                     /*脚滚 伴随模式*/
//    FMA_ROLLER_NONE,                                     /*腿滚 伴随模式*/
//    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
//    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
//    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
//    FMA_HEAT_NONE,                                       /*腰背热 伴随模式*/
//    FMA_LED_NONE                                         /*灯   伴随模式*/
//  },
 
  /*---------------------------------------------------------------*/
  { 
    FA_SPIKE_ZeroGravity1,                               /*动作ID */
    (void*)SpikeAutoTab_ZeroGravity1,                    /*动作表格*/
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
  
  /*---------------------------------------------------------------*/
  { 
    FA_SPIKE_ZeroGravity2,                               /*动作ID */
    (void*)SpikeAutoTab_ZeroGravity2,                    /*动作表格*/
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
  
  /*---------------------------------------------------------------*/
  { 
    FA_SPIKE_Home,                                       /*动作ID */
    (void*)SpikeAutoTab_Home,                            /*动作表格*/
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
    FA_SPIKE_TRY,                                        /*动作ID */
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

#define SPIKE_AUTO_TAB_NUM    TAB_NUM(SpikeAutoAttrTab)


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : MChair_SetFuncAutoSpike                                                                                               
* 功能描述 : 按摩椅 设置推杆自动的功能                                                   
* 输入参数 : FuncAutoSpike  --  要设置的功能
*            NeedCloseAngle --  是否需要关闭角度。该变量只在 FuncAutoSpike 为FA_SPIKE_NONE时，才有效。
*                               取值：TRUE  -- 需要关闭角度。
*                                     FALSE -- 无需关闭角度
* 返回参数 : 无                                                                                              
* 补充说明 : 无
************************************************************************************************************************
*/
void MChair_SetFuncAutoSpike(uint16_t FuncAutoSpike, uint8_t NeedCloseAngle)
{
  pMChair->FuncAuto_Spike = FuncAutoSpike;
  SpikeAutoNeedCloseAngle = NeedCloseAngle;
  if(pMChair->FuncAuto_Spike != FA_SPIKE_NONE)
  {
    SpikeAutoNeedCloseAngle = FALSE;
  }
  
  if(SpikeAutoNeedCloseAngle == TRUE)  /*此时零重力表格可能已经执行完，不会执行切换函数中的 执行角度，这里强制执行一次*/
  {
    Spike_SetAngle(PBACK_EXE_ANGLE, PFEET_EXE_ANGLE, PZERO_EXE_ANGLE);  /*执行角度*/
  }
}


/*
************************************************************************************************************************
* 函数名称 : MChair_FuncSwitch_SpikeAuto                                                                                               
* 功能描述 : 按摩椅 功能切换 之  【推杆】自动                                                              
* 输入参数 : SwitchMode -- 要切换模式
*            pFuncLogic -- 功能逻辑的描述                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 :【推杆】自动 一般都用于调节零重力角度调节等。当有【机芯+推杆】、【充气+推杆】、【机芯+充气+推杆】等程序运行时，
*            是不可以被【推杆】自动切换掉电。因此在零重力开启的键值处理函数内应该做相关的逻辑判断。
*            在 FuncLogic.c 文件中的 FuncLogicTab 表格内对 MChair.FuncAuto_Spike 也分配了较低的优先级，防止其切掉其他程序。
************************************************************************************************************************
*/
void MChair_FuncSwitch_SpikeAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  SpikeAutoTabIndex = MChair_FuncSwitch_CloseForNewFunc(pFuncLogic, SpikeAutoAttrTab, SPIKE_AUTO_TAB_NUM, &SpikeAutoStep);

  if(SpikeAutoNeedCloseAngle == TRUE)
  {
    Spike_SetAngle(PBACK_EXE_ANGLE, PFEET_EXE_ANGLE, PZERO_EXE_ANGLE);  /*执行角度*/
    SpikeAutoNeedCloseAngle = FALSE;
  }
}


/*
************************************************************************************************************************
* 函数名称 : MChair_FuncExe_SpikeAuto                                                                                               
* 功能描述 : 按摩椅 功能执行 之  【推杆】自动                                                           
* 输入参数 : ExePeriod  -- 执行周期
*            pFuncLogic -- 指向自身功能逻辑的指针。                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_SpikeAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  if((0x00               == SpikeAutoTabIndex) ||   
     (INDEX_NO_MATCH     == SpikeAutoTabIndex) ||
     (SPIKE_AUTO_TAB_NUM <= SpikeAutoTabIndex) )
  {
    return;                                                  /*表格索引无效，则无功能*/
  }
  
  SpikeAutoStep.AdditonOp.Bit.SingleExe = TRUE;              /*【推杆】自动只执行一次表格*/
  if(0 == SpikeAutoStep.TabRepeat)                           /*【推杆】自动只执行一次表格*/
  {
    pMChair->ComponentFuncState.Bit.Spike = FUNC_TYPE_AUTO;  /*推杆功能状态：自动*/

    pMChair->CSFlag.Bit.ZeroGravityAngleRun = TRUE;          /*零重力摆角度中*/
    pMChair->CSFlag.Bit.BackSpikeMannualMoveDisable = TRUE;  /*靠背推杆手动无效*/
    //pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable = TRUE;  /*零重力推杆手动无效*/
    pMChair->CSFlag.Bit.FeetSpikeMannualMoveDisable = TRUE;  /*小腿推杆手动无效*/
    pMChair->CSFlag.Bit.LegFlexMannualMoveDisable   = TRUE;  /*小腿伸缩手动无效*/

    Spike_SetZeroSafetyAngleLimitRef(PBACK15, PZERO15); 
    //Spike_SetZeroSafetyAngleLimitRef(PBACK09, PZERO10);

    MChair_TabHandle_SpikeAuto(ExePeriod, (ActionTabAttr_t *)&SpikeAutoAttrTab[SpikeAutoTabIndex], &SpikeAutoStep);
  }
  else
  {
//    if(pMChair->FuncAuto_Spike == FA_SPIKE_ZeroGravity1)
//    {
//      if((Spike_GetBackAngle() != PBACK_ZERO1_ANGLE) || (Spike_GetFeetAngle() != PFEET_ZERO1_ANGLE)) 
//      {
//        pMChair->FuncAuto_Spike = FA_SPIKE_NONE;
//      }
//    }
//    else if(pMChair->FuncAuto_Spike == FA_SPIKE_ZeroGravity2)
//    {
//      if((Spike_GetBackAngle() != PBACK_ZERO2_ANGLE) || (Spike_GetFeetAngle() != PFEET_ZERO2_ANGLE)) 
//      {
//        pMChair->FuncAuto_Spike = FA_SPIKE_NONE;
//      }
//    }
    pMChair->FuncAuto_Spike = FA_SPIKE_NONE;
    /*在函数MChair_FuncExe()中，执行各个功能前已经先清零，这里不要清了，注释掉。*/
    //pMChair->ComponentFuncState.Bit.Spike = FUNC_TYPE_NONE; /*推杆功能状态：无*/
  }  
}

