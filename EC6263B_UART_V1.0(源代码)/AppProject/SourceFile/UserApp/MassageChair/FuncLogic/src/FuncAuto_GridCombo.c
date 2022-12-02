/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：FuncAuto_GridCombo.c 
**
**    功能描述:【宫格组合】自动。小型短时【机芯】自动程序的组合执行。
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
static const void*  GridComboActionTab[] = /* 组成宫格的动作表格，目前最多4*8=32 */
{
  /*颈肩----------------------------------*/
  (void*)GridComboTab_NeckShoulder_1,
  (void*)GridComboTab_NeckShoulder_2,
  (void*)GridComboTab_NeckShoulder_3,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,

  /*背部----------------------------------*/
  (void*)GridComboTab_Back_1,
  (void*)GridComboTab_Back_2,
  (void*)GridComboTab_Back_3,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,

  /*腰部----------------------------------*/
  (void*)GridComboTab_Lumbar_1,
  (void*)GridComboTab_Lumbar_2,
  (void*)GridComboTab_Lumbar_3,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,

  /*臀部----------------------------------*/
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL
};
#define  GRIDCOMBO_ACTION_TAB_NUM    TAB_NUM(GridComboActionTab)


static uint8_t    GridComboSelectBit[4];          /*【宫格组合】选择位*/    
#define  GRIDCOMBO_SELECT_BYTE_NUM    TAB_NUM(GridComboSelectBit)

static uint16_t   GridComboAutoRunTabIndex;       /*【宫格组合】运行表格索引*/  

static ActionTabStep_t   GridComboAutoTabStep;

static ActionTabAttr_t   GridAutoDynAttr;          /*【宫格组合】动态属性*/


static const ActionTabAttr_t   GridAutoAttrTab[] =
{
  /* 【宫格组合】 与 其他的自动功能处理不太一样。
   * 【宫格组合】 没有伴随功能，所有的伴随功能都是独立操作来叠加的。*/

  /*---------------------------------------------------------------*/
  { 
    FA_GRIDCOMBO_NONE,                                   /*动作ID */
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

  /*---------------------------------------------------------------*/
  { 
    FA_GRIDCOMBO_ON,                                     /*动作ID */
    (void*)NULL,                                         /*动作表格*/
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
  }
};

#define GRID_AUTO_TAB_NUM    TAB_NUM(GridAutoAttrTab)


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : GridComboAuto_UpdateComboSelectBit                                                                                                
* 功能描述 : 更新【宫格组合】程序的选择位                                                      
* 输入参数 : pBit -- 指向功能位
* 返回参数 : 无                                                                                              
* 补充说明 : SUCCESS -- 更新成功   
*            FAIL    -- 没发生变化，不需要更新                                                           
************************************************************************************************************************
*/
uint8_t GridComboAuto_UpdateComboSelectBit(uint8_t  *pBit)
{
  uint8_t i;
  uint8_t TBit;
  uint8_t Change;


  /*判断选择位是否发生变化--------------------------------*/
  Change = FALSE;
  for(i=0; i<GRIDCOMBO_SELECT_BYTE_NUM; i++)
  {
    if(GridComboSelectBit[i] != pBit[i])
    {
      Change = TRUE;
      break;
    }
  }
  if(FALSE == Change)
  {
    return FAIL;
  }

  /*选择位发生变化才更新----------------------------------*/
  pMChair->FuncAuto_GridCombo = FA_GRIDCOMBO_NONE;            /*先假设 【宫格组合】程序无效*/
  GridComboAutoRunTabIndex = 0;
  memset(&GridComboAutoTabStep, 0, sizeof(ActionTabStep_t));

  for(i=0; i<GRIDCOMBO_SELECT_BYTE_NUM; i++)
  {
    GridComboSelectBit[i] = pBit[i];

    if((GridComboSelectBit[i] > 0)                           &&  /*有相应的程序被开启*/
       (FA_GRIDCOMBO_NONE == pMChair->FuncAuto_GridCombo) )   /*【宫格组合】程序尚未开启*/
    {
      for(TBit=0; TBit<8; TBit++)
      {
        if(GridComboSelectBit[i] & (1<<TBit))
        {
          GridComboAutoRunTabIndex = (i<<3) + TBit;              /*计算出第一个宫格程序的索引*/
          break;
        }
      }

      pMChair->FuncAuto_GridCombo = FA_GRIDCOMBO_ON;          /*【宫格组合】程序开启*/
    }
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : GridComboAuto_CalNextRunTabIndex                                                                                           
* 功能描述 : 计算【宫格组合】下一个将要执行的动作表格的索引                                                       
* 输入参数 : 无                                                                                     
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void GridComboAuto_CalNextRunTabIndex(void)
{
  uint8_t i;
  uint8_t TByte, TBit;

  if(FA_GRIDCOMBO_NONE == pMChair->FuncAuto_GridCombo)
  {
    return;
  }

  memset(&GridComboAutoTabStep, 0, sizeof(ActionTabStep_t));

  for(i=0; i<GRIDCOMBO_ACTION_TAB_NUM; i++)
  {
    GridComboAutoRunTabIndex++;
    if(GridComboAutoRunTabIndex >= GRIDCOMBO_ACTION_TAB_NUM)
    {
      GridComboAutoRunTabIndex = 0;
    }
    TByte = GridComboAutoRunTabIndex >> 3;
    TBit  = GridComboAutoRunTabIndex & 0x07;
    if(GridComboSelectBit[TByte] & (1<<TBit))
    {
      break;
    }
  }
}

/*
************************************************************************************************************************
* 函数名称 : GridComboAuto_GetNeckShoulderSelectBit                                                                                            
* 功能描述 : 获取当前【宫格组合】颈肩的选择位                                                       
* 输入参数 : 无                                                                             
* 返回参数 : 颈肩的选择位                                                                                                         
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
uint8_t GridComboAuto_GetNeckShoulderSelectBit(void)
{
  return GridComboSelectBit[0];
}

/*
************************************************************************************************************************
* 函数名称 : GridComboAuto_GetBacSelectkBit                                                                                           
* 功能描述 : 获取当前【宫格组合】背部的选择位                                                       
* 输入参数 : 无                                                                                
* 返回参数 : 背部的选择位                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
uint8_t GridComboAuto_GetBackSelectBit(void)
{
  return GridComboSelectBit[1];
}

/*
************************************************************************************************************************
* 函数名称 : GridComboAuto_GetLumbarSelectBit                                                                                           
* 功能描述 : 获取当前【宫格组合】腰部的选择位                                                       
* 输入参数 : 无                                                                                 
* 返回参数 : 腰部的选择位                                                                                               
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
uint8_t GridComboAuto_GetLumbarSelectBit(void)
{
  return GridComboSelectBit[2];
}

/*
************************************************************************************************************************
* 函数名称 : GridComboAuto_GetButtocksSelectBit                                                                                           
* 功能描述 : 获取当前【宫格组合】臀部的选择位                                                       
* 输入参数 : 无                                                                                  
* 返回参数 : 臀部的选择位                                                                                               
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
uint8_t GridComboAuto_GetButtocksSelectBit(void)
{
  return GridComboSelectBit[3];
}

/*
************************************************************************************************************************
* 函数名称 : GridComboAuto_GetCurRunTabIndex                                                                                           
* 功能描述 : 获取当前【宫格组合】运行表格的索引                                                      
* 输入参数 : 无                                                                                  
* 返回参数 :     0 -- 无效的索引，即【宫格组合】未开启。
*            大于0 -- 当前正在执行的宫格表格索引（下标从1开始）。                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
uint8_t GridComboAuto_GetCurRunTabIndex(void)
{
  if(FA_GRIDCOMBO_NONE == pMChair->FuncAuto_GridCombo)
  {
    return 0;
  }
  else
  {
    /*EC-P388A 为9宫格，因此这里根据9宫格返回索引值*/
    if(GridComboAutoRunTabIndex <= 2)
    {
      return GridComboAutoRunTabIndex + 1;
    }
    else if((GridComboAutoRunTabIndex >= 8) && (GridComboAutoRunTabIndex <= (8+2)))
    {
      return GridComboAutoRunTabIndex + 1 - 8 + 3;
    }
    else if((GridComboAutoRunTabIndex >= 16) && (GridComboAutoRunTabIndex <= (16+2)))
    {
      return GridComboAutoRunTabIndex + 1 - 16 + 6;
    }
    else
    {
      return 0;
    }
  }
}

/*
************************************************************************************************************************
* 函数名称 : MChair_FuncSwitch_GridComboAuto                                                                                           
* 功能描述 : 按摩椅 功能切换 之  【宫格组合】自动                                                       
* 输入参数 : SwitchMode -- 要切换模式
*            pFuncLogic -- 功能逻辑的描述                                                                          
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_GridComboAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  if(CLOSE == SwitchMode)
  {
    pMChair->FuncAuto_GridCombo = FA_GRIDCOMBO_NONE;   /*【宫格组合】程序无效*/
    GridComboAutoRunTabIndex = 0;
    memset(GridComboSelectBit, 0, GRIDCOMBO_SELECT_BYTE_NUM);
  }

  MChair_FuncSwitch_CloseForNewFunc(pFuncLogic, GridAutoAttrTab, GRID_AUTO_TAB_NUM, &GridComboAutoTabStep);
}

/*
************************************************************************************************************************
* 函数名称 : MChair_FuncExe_GridComboAuto                                                                                           
* 功能描述 : 按摩椅 功能执行 之  【宫格组合】自动                                                       
* 输入参数 : ExePeriod  -- 执行周期
*            pFuncLogic -- 指向自身功能逻辑的指针。                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_GridComboAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  if(pMChair->FuncAuto_GridCombo != FA_GRIDCOMBO_ON)  /*宫格程序未开启*/
  {
    return;
  }

  pMChair->ComponentFuncState.Bit.Core = FUNC_TYPE_AUTO;    /*机芯功能状态：自动*/
  if(FALSE == pMChair->StateBodyScan.Bit.Finish)            /*人体扫描未完成*/
  {
    return;
  }

  /*【宫格组合】 的动作表格是用户随机选择的，因此这里用动态属性，动态地更新动作表格属性*/
  memcpy(&GridAutoDynAttr, (ActionTabAttr_t *)&GridAutoAttrTab[1], sizeof(ActionTabAttr_t));
  GridAutoDynAttr.pActionTab = (void*)GridComboActionTab[GridComboAutoRunTabIndex]; /*获取动作表格*/
  if(NULL == GridAutoDynAttr.pActionTab) 
  {
    GridComboAuto_CalNextRunTabIndex();                  /*动作表格无效，则查找下一个执行表格的索引*/
    return;
  }

  MChair_TabHandle_CoreMixOtherAuto(ExePeriod, &GridAutoDynAttr, &GridComboAutoTabStep);

  if(GridComboAutoTabStep.TabRepeat > 0) 
  {
    GridComboAuto_CalNextRunTabIndex();                  /*表格执行完一遍，则查找下一个执行表格的索引*/
  }
}

