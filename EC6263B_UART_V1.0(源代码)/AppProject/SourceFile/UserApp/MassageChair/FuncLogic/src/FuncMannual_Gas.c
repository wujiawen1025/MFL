/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：FuncMannual_Gas.c 
**
**    功能描述:【充气】手动
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
//static ActionTabStep_t GasFeetStep;
static ActionTabStep_t GasCalvesStep;
//static ActionTabStep_t GasCalvesFeetStep;

//static ActionTabStep_t GasSeatStep;
//static ActionTabStep_t GasLumbarStep;
static ActionTabStep_t GasLumbarSeatStep;

static ActionTabStep_t GasArmsStep;

static ActionTabStep_t GasShoulderStep;

//static ActionTabStep_t GasHeadStep;


static const ActionTabAttr_t   GasMannualAttrTab[] =
{
  /*【充气】手动 忽略动作ID*/

  /*0---------------------------------------------------------------*/
  { 
    0,                                                   /*动作ID */
    (void*)GasTab_Calves,                                /*动作表格*/
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

  /*1---------------------------------------------------------------*/
  { 
    0,                                                   /*动作ID */
    (void*)GasTab_LumbarSeat,                            /*动作表格*/
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
  
  /*2---------------------------------------------------------------*/
  { 
    0,                                                   /*动作ID */
    (void*)GasTab_Arms,                                  /*动作表格*/
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
  
  /*3---------------------------------------------------------------*/
  { 
    0,                                                   /*动作ID */
    (void*)GasTab_Shoulder,                              /*动作表格*/
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


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : MChair_FuncSwitch_GasMannual                                                                                               
* 功能描述 : 按摩椅 功能切换 之  【充气】手动                                                                              
* 输入参数 : SwitchMode -- 要切换模式
*            pFuncLogic -- 功能逻辑的描述                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_GasMannual(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  GasAction_t  GasHis; 
  GasAction_t  GasCur; 


  GasHis.All = *pFuncLogic->pFuncHis;
  GasCur.All = *pFuncLogic->pFuncCur;

  if(OPEN == SwitchMode)                   /*打开操作，各顾各的*/
  {
    if(GasHis.Bit.Calves != GasCur.Bit.Calves)
    {
      Gas_CalvesCtrlEnOnly();              /*腿充气控制使能，其他部位控制关闭*/     
      Gas_SetGasPart(0, 0);
      memset(&GasCalvesStep, 0, sizeof(ActionTabStep_t));
    }

    if(GasHis.Bit.LumbarSeat != GasCur.Bit.LumbarSeat)
    {
      Gas_LumbarSeatCtrlEnOnly();          /*背座充气控制使能，其他部位控制关闭*/       
      Gas_SetGasPart(0, 0);
      memset(&GasLumbarSeatStep, 0, sizeof(ActionTabStep_t));
    }

    if(GasHis.Bit.Arms != GasCur.Bit.Arms)
    {
      Gas_ArmsCtrlEnOnly();                /*手臂充气控制使能，其他部位控制关闭*/        
      Gas_SetGasPart(0, 0);
      memset(&GasArmsStep, 0, sizeof(ActionTabStep_t));
    }

    if(GasHis.Bit.Shoulder != GasCur.Bit.Shoulder)
    {
      Gas_ShoulderCtrlEnOnly();            /*肩部充气控制使能，其他部位控制关闭*/      
      Gas_SetGasPart(0, 0);
      memset(&GasShoulderStep, 0, sizeof(ActionTabStep_t));
    }
  }
  else// if(CLOSE == SwitchMode)           /*关闭操作，关全部。*/
  {
    Gas_SetPumpSw(OFF);
    Gas_AllCtrlEn();                       /*所有部位充气控制使能*/ 
    Gas_SetGasPart(0, 0);
    
    if(pMChair->FuncMA_Roller.Bit.Calves != FMA_CALVES_ROLLER_Mannual)   /*无充气 且 小腿夹揉非手动 则恢复默认强度*/
    {
      pMChair->GasIntensity = 3;             /*充气强度*/
    }
  }
}

/*
************************************************************************************************************************
* 函数名称 : MChair_FuncExe_GasMannual                                                                                               
* 功能描述 : 按摩椅 功能执行 之  【充气】手动                                                                              
* 输入参数 : ExePeriod  -- 执行周期
*            pFuncLogic -- 指向自身功能逻辑的指针。                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_GasMannual(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  GasAction_t  GasCur; 

  pMChair->ComponentFuncState.Bit.Gas = FUNC_TYPE_MANNUAL;   /*充气功能状态：手动*/


  if((ON == pMChair->StateBodyScan.Bit.Run)    ||            /*人体扫描进行中*/
     (TRUE == pMChair->StateZeroSpike.Bit.Work))             /*零重力升降中*/
  {
    Gas_AllCtrlEn();                                         /*所有部位充气控制使能*/ 
    Gas_SetGasPart(0, 0);
    return;
  }


  GasCur.All = *pFuncLogic->pFuncCur;

  if(GasCur.Bit.Calves)
  {
    Gas_CalvesCtrlEnOnly();                              /*腿脚充气控制使能，其他部位控制关闭*/     
    MChair_TabHandle_GasAuto(ExePeriod, (ActionTabAttr_t *)&GasMannualAttrTab[0], &GasCalvesStep);
  }

  if(GasCur.Bit.LumbarSeat)
  {
    Gas_LumbarSeatCtrlEnOnly();                              /*腰座充气控制使能，其他部位控制关闭*/       
    MChair_TabHandle_GasAuto(ExePeriod, (ActionTabAttr_t *)&GasMannualAttrTab[1], &GasLumbarSeatStep);
  }

  if(GasCur.Bit.Arms)
  {
    Gas_ArmsCtrlEnOnly();                                    /*手臂充气控制使能，其他部位控制关闭*/       
    MChair_TabHandle_GasAuto(ExePeriod, (ActionTabAttr_t *)&GasMannualAttrTab[2], &GasArmsStep);
  }

  if(GasCur.Bit.Shoulder)
  {
    Gas_ShoulderCtrlEnOnly();                                /*肩部充气控制使能，其他部位控制关闭*/        
    MChair_TabHandle_GasAuto(ExePeriod, (ActionTabAttr_t *)&GasMannualAttrTab[3], &GasShoulderStep);
  }
}
