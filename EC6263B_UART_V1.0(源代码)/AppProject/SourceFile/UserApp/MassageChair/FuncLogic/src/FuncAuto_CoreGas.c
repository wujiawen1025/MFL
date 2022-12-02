/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：FuncAuto_CoreGas.c 
**
**    功能描述:【机芯+充气】自动
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
static uint16_t  CoreGasAutoTabIndex;
ActionTabStep_t  CoreGasAutoTabStep;

static const ActionTabAttr_t   CoreGasAutoArrtTab[] =
{
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_NONE,                                     /*动作ID */
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
  
  /*============================ 0x01~0x2F   【机芯】 表格 + 【充气】表格=====================================*/
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_Quick,                                    /*动作ID */
    (void*)CoreMixOtherTab_Quick,                        /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_FEET_ROLLER_ByTime_On90s_Off90s,                 /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByTime_On90s_Off90s,               /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_Relax,                                    /*动作ID */
    (void*)CoreMixOtherTab_Relax,                        /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_FEET_ROLLER_ByTime_On90s_Off90s,                 /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByTime_On90s_Off90s,               /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_MoveSleep,                                /*动作ID */
    (void*)CoreMixOtherTab_MoveSleep,                    /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_ROLLER_NONE,                                     /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByTime_On90s_Off90s,               /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_Stretch,                                  /*动作ID */
    (void*)CoreMixOtherTab_Stretch,                      /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_FEET_ROLLER_ByActionTab,                         /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByActionTab,                       /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_Scraping,                                 /*动作ID */
    (void*)CoreMixOtherTab_Scraping,                     /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_FEET_ROLLER_ByTime_On120s_Off120s,               /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByTime_On120s_Off120s,             /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_Shiatsu,                                  /*动作ID */
    (void*)CoreMixOtherTab_Shiatsu,                      /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_FEET_ROLLER_ByTime_On150s_Off120s,               /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByTime_On120s_Off120s,             /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_Lady,                                     /*动作ID */
    (void*)CoreMixOtherTab_Lady,                         /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_FEET_ROLLER_ByTime_On90s_Off90s,                 /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByTime_On90s_Off90s,               /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_Man,                                      /*动作ID */
    (void*)CoreMixOtherTab_Man,                          /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_FEET_ROLLER_ByTime_On90s_Off90s,                 /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByTime_On90s_Off90s,               /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_ShoulderRelax,                            /*动作ID */
    (void*)CoreMixOtherTab_ShoulderRelax,                /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_FEET_ROLLER_ByTime_On90s_Off90s,                 /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByTime_On90s_Off90s,               /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_ShoulderRecovery,                         /*动作ID */
    (void*)CoreMixOtherTab_ShoulderRecovery,             /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_FEET_ROLLER_ByTime_On150s_Off120s,               /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByTime_On150s_Off120s,             /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_ShoulderTuina,                            /*动作ID */
    (void*)CoreMixOtherTab_ShoulderTuina,                /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_FEET_ROLLER_ByTime_On120s_Off120s,               /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByTime_On150s_Off120s,             /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_ShoulderShiatsu,                          /*动作ID */
    (void*)CoreMixOtherTab_ShoulderShiatsu,              /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_FEET_ROLLER_ByTime_On150s_Off120s,               /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByTime_On150s_Off120s,             /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_LumbarButtockRelax,                       /*动作ID */
    (void*)CoreMixOtherTab_LumbarButtockRelax,           /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_FEET_ROLLER_ByTime_On90s_Off90s,                 /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByTime_On90s_Off90s,               /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_LumbarButtockRecovery,                    /*动作ID */
    (void*)CoreMixOtherTab_LumbarButtockRecovery,        /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_FEET_ROLLER_ByTime_On150s_Off120s,               /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByTime_On150s_Off120s,             /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_LumbarButtockPress,                       /*动作ID */
    (void*)CoreMixOtherTab_LumbarButtockPress,           /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_FEET_ROLLER_ByTime_On150s_Off120s,               /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByTime_On150s_Off120s,             /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_LumbarKidneyCare,                         /*动作ID */
    (void*)CoreMixOtherTab_LumbarKidneyCare,             /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_FEET_ROLLER_ByTime_On150s_Off120s,               /*脚滚 伴随模式*/
    FMA_CALVES_ROLLER_ByTime_On150s_Off120s,             /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  /*============================ 0x30~0x05F   【机芯+充气 】表格 =============================================*/

  /*表格体验调试--------表格体验调试--------表格体验调试--------表格体验调试*/
  { 
    FA_COREGAS_TRY,                                      /*动作ID */
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


#define COREGAS_AUTO_TAB_NUM    TAB_NUM(CoreGasAutoArrtTab)


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : MChair_FuncSwitch_CoreGasAuto                                                                                                
* 功能描述 : 按摩椅 功能切换 之  【机芯+充气】自动                                                      
* 输入参数 : SwitchMode -- 要切换模式
*            pFuncLogic -- 功能逻辑的描述                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_CoreGasAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  CoreGasAutoTabIndex = MChair_FuncSwitch_CloseForNewFunc(pFuncLogic, CoreGasAutoArrtTab, COREGAS_AUTO_TAB_NUM, &CoreGasAutoTabStep);
}

/*
************************************************************************************************************************
* 函数名称 : MChair_FuncExe_CoreGasAuto                                                                                           
* 功能描述 : 按摩椅 功能执行 之  【机芯+充气】自动                                                       
* 输入参数 : ExePeriod  -- 执行周期
*            pFuncLogic -- 指向自身功能逻辑的指针。                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_CoreGasAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  if((0x00                 == CoreGasAutoTabIndex) ||   
     (INDEX_NO_MATCH       == CoreGasAutoTabIndex) ||
     (COREGAS_AUTO_TAB_NUM <= CoreGasAutoTabIndex) )
  {
    return;                                               /*表格索引无效，则无功能*/
  }

  pMChair->ComponentFuncState.Bit.Core = FUNC_TYPE_AUTO;  /*机芯功能状态：自动*/
  pMChair->ComponentFuncState.Bit.Gas = FUNC_TYPE_AUTO;   /*充气功能状态：自动*/

  if(FALSE == pMChair->StateBodyScan.Bit.Finish)          /*人体扫描未完成*/
  {
    return;
  }
  
  Gas_AllCtrlEn();                                        /*控制所有部位的充气*/

  if(pMChair->FuncAuto_CoreGas < 0x30)                    /*0x01~0x2F   【机芯】 表格 + 【充气】表格*/
  {
    MChair_TabHandle_CoreMixOtherAuto(ExePeriod, (ActionTabAttr_t *)&CoreGasAutoArrtTab[CoreGasAutoTabIndex], &CoreGasAutoTabStep);
  }
  else                                                    /*0x30~0x05F   【机芯+充气 】表格*/
  {
    MChair_TabHandle_CoreGasAuto(ExePeriod, (ActionTabAttr_t *)&CoreGasAutoArrtTab[CoreGasAutoTabIndex], &CoreGasAutoTabStep);
  }
}

