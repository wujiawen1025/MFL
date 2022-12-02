/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：FuncLogic.c 
**
**    功能描述: 按摩功能逻辑管理
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
/***********************************************************************************************************************
 *                   按摩功能逻辑切换表
************************************************************************************************************************/
static const FuncLogic_t FuncLogicTab[] = 
{
  /*属性：   b0~b1 -- 0无功能   1手动  2自动   3手动与自动
             b2    -- 0 分立   1组合
             b3~b5 -- 预留 
             b6~b7 -- 执行优先级  0~3，数值越小，优先级越大 */

  /*主部件：b0--机芯  b1--充气  b2--推杆 */

  /*       当前功能                    历史功能           属性          主部件          功能切换操作函数                   功能执行函数         */
  /*手动 主功能*/
  {&MChair.FuncMannual_Gas.All,    &MChair.FuncHis[0],   B(00000001), B(00000010),  MChair_FuncSwitch_GasMannual,        MChair_FuncExe_GasMannual},
  {&MChair.FuncMannual_Spike.All,  &MChair.FuncHis[1],   B(10000001), B(00000100),  MChair_FuncSwitch_SpikeMannual,      MChair_FuncExe_SpikeMannual},
  {&MChair.FuncMannual_Core.All,   &MChair.FuncHis[2],   B(00000001), B(00000001),  MChair_FuncSwitch_CoreMannual,       MChair_FuncExe_CoreMannual},

  /*自动 主功能 分立*/
  {&MChair.FuncAuto_CoreGasSpike,  &MChair.FuncHis[3],   B(00000010), B(00000111),  MChair_FuncSwitch_CoreGasSpikeAuto,  MChair_FuncExe_CoreGasSpikeAuto},
  {&MChair.FuncAuto_CoreSpike,     &MChair.FuncHis[4],   B(00000010), B(00000101),  MChair_FuncSwitch_CoreSpikeAuto,     MChair_FuncExe_CoreSpikeAuto},
  {&MChair.FuncAuto_CoreGas,       &MChair.FuncHis[5],   B(00000010), B(00000011),  MChair_FuncSwitch_CoreGasAuto,       MChair_FuncExe_CoreGasAuto},
  {&MChair.FuncAuto_GasSpike,      &MChair.FuncHis[6],   B(00000010), B(00000110),  MChair_FuncSwitch_GasSpikeAuto,      MChair_FuncExe_GasSpikeAuto},
  {&MChair.FuncAuto_Spike,         &MChair.FuncHis[7],   B(11000010), B(00000100),  MChair_FuncSwitch_SpikeAuto,         MChair_FuncExe_SpikeAuto},
  {&MChair.FuncAuto_Gas,           &MChair.FuncHis[8],   B(00000010), B(00000010),  MChair_FuncSwitch_GasAuto,           MChair_FuncExe_GasAuto},
  {&MChair.FuncAuto_Core,          &MChair.FuncHis[9],   B(00000010), B(00000001),  MChair_FuncSwitch_CoreAuto,          MChair_FuncExe_CoreAuto},

  {&MChair.FuncAuto_GridCombo,     &MChair.FuncHis[10],  B(00000010), B(00000011),  MChair_FuncSwitch_GridComboAuto,     MChair_FuncExe_GridComboAuto},

  /*手动/自动  伴随功能   可单独作用，也可作为主功能的伴随而存在*/
  {&MChair.FuncMA_Roller.All,      &MChair.FuncHis[11],  B(00000011), B(00000000),  MChair_FuncSwitch_RollerMA,          MChair_FuncExe_RollerMA},
  {&MChair.FuncMA_Heat.All,        &MChair.FuncHis[12],  B(00000011), B(00000000),  MChair_FuncSwitch_HeatMA,            MChair_FuncExe_HeatMA},
  {&MChair.FuncMA_Vib.All,         &MChair.FuncHis[13],  B(00000011), B(00000000),  MChair_FuncSwitch_VibMA,             MChair_FuncExe_VibMA},
  {&MChair.FuncMA_Led.All,         &MChair.FuncHis[14],  B(00000011), B(00000000),  MChair_FuncSwitch_LedMA,             MChair_FuncExe_LedMA}
}; 

#define  FUNC_LOGIC_TAB_NUM     TAB_NUM(FuncLogicTab)

/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : MChair_FuncLogic_ClearAllFunc                                                                                                         
* 功能描述 : 清零所有功能，即关闭所有开启的按摩功能。                                                                                             
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                                                               
* 补充说明 : ★ 此函数内不设置推杆角度，清零所有功能一般是在定时到或关机时才调用。                                ★
             ★ 一般手动关机时需要复位推杆角度。其他情况，如定时到或自动关机，是否设置推杆角度根据业务的需求决定。★
             ★ 因此推杆角度根据实际需要另外设置。此函数内不设置。                                                ★                                                           
************************************************************************************************************************
*/
void MChair_FuncLogic_ClearAllFunc(void)
{
  uint8_t i;
  uint8_t tmepbuf[4]={0,0,0,0};

  for(i=0; i<FUNC_LOGIC_TAB_NUM; i++)
  {
    *FuncLogicTab[i].pFuncCur = 0;                                         /*将当前和历史都清零，不用触发切换逻辑的判断*/
    *FuncLogicTab[i].pFuncHis = 0; 
  }                                                                        
  
  GridComboAuto_UpdateComboSelectBit(tmepbuf);                             /*清除宫格的选择位*/

  pMChair->ComponentFuncState.All = FUNC_TYPE_NONE;                        /*功能关闭，将部件的功能状态清除*/

  Core_SetAction(CORE_ACTION_EXE_NONE, XYZ_ACTION_NONE, TCS_ACTION_NONE);  /*关闭机芯动作*/
  Core_SetXYZPosition(PXWIDE, PYTOP, PZBACK);                              /*设置机芯的位置*/ 

  Spike_SetMoveAction(SPIKE_MOVE_NONE);                                    /*推杆 的手动长按释放*/
  /*注：此函数内不设置推杆角度，清零所有功能一般是在定时到或关机时才调用。                              
        手动关机时需要复位推杆角度。其他情况，如定时到或自动关机，是否设置推杆角度根据业务的需求决定。  
        因此推杆角度根据实际需要另外设置。此函数内不设置。    */

  Gas_SetPumpSw(OFF);                                                      /*关气泵与气阀*/
  Gas_AllCtrlEn();                                                         /*所有部位充气控制使能*/                            
  Gas_SetGasPart(0, 0);                              

  MChair_RollerFuncReset_Feet();                                           /*复位脚滚*/
  MChair_RollerFuncReset_Calves();                                         /*复位腿滚*/
  MChair_VibFuncReset_Feet();                                              /*复位振动*/
  MChair_VibFuncReset_Calves();                                            /*复位振动*/
  MChair_VibFuncReset_Seat();                                              /*复位振动*/
  MChair_VibFuncReset_LumbarBack();                                        /*复位振动*/
  MChair_HeatFuncReset_Feet();                                             /*复位加热*/
  MChair_HeatFuncReset_Calves();                                           /*复位加热*/
  MChair_HeatFuncReset_Seat();                                             /*复位加热*/
  MChair_HeatFuncReset_LumbarBack();                                       /*复位加热*/
  MChair_LedFuncReset();                                                   /*复位灯*/  
}


/*
************************************************************************************************************************
* 函数名称 : MChair_FuncLogic_Switch                                                                                                         
* 功能描述 : 功能逻辑的切换                                                                                              
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                                                               
* 补充说明 : 使用表格对所有功能的逻辑切换操作进行统一管理。
*            这里的FuncLogicTab是主表格，
*            在每个具体的功能里还有一个子表格（结构体ActionTabAttr_t来定义）。                                                                                                        
************************************************************************************************************************
*/
void MChair_FuncLogic_Switch(void)
{
  uint8_t i;
  uint8_t j;


  for(i=0; i<FUNC_LOGIC_TAB_NUM; i++)
  {
    /*无功能切换------------------------------------------------------------------------*/
    if(*FuncLogicTab[i].pFuncHis == *FuncLogicTab[i].pFuncCur) 
    {
      continue;
    }

    /*切换，关闭功能--------------------------------------------------------------------*/
    if(0 == *FuncLogicTab[i].pFuncCur) 
    {
      if(FuncLogicTab[i].pFuncSwitch != NULL)
      {
        /*切换函数内，将会使用 pFuncCur 和 pFuncHis来做一些相关操作，因此必须保证 pFuncCur 的实时性，
          在进入切换前，务必将pFuncCur更新到最新值，在切换结束后，再将pFuncHis更新到与pFuncCur同步。*/
        FuncLogicTab[i].pFuncSwitch(CLOSE, (FuncLogic_t*)&FuncLogicTab[i]);              /*关闭操作*/
      }
      *FuncLogicTab[i].pFuncHis = *FuncLogicTab[i].pFuncCur;
    }

    /*切换，打开新功能------------------------------------------------------------------*/
    else 
    {
      for(j=0; j<FUNC_LOGIC_TAB_NUM; j++)                                                /*遍历数组，关闭冲突的功能，或被高优先级的冲突方关闭*/
      {
        if(j == i)
        {
          continue;                                                                      /*跳过与自身的比较*/
        }
         
        if((FuncLogicTab[j].MainComponent.All & FuncLogicTab[i].MainComponent.All) &&    /*主部件 冲突*/
           (*FuncLogicTab[j].pFuncHis) > 0)                                              /*且 冲突方 有功能在执行中*/
        {
          /* 比较冲突双方的执行优先级，优先级低的被关闭。
           *【推杆】手动 和【推杆】自动 的优先级都比其他的功能低。
           * 属性Attr里的 b6~b7 -- 执行优先级 0~3，数值越小，优先级越大 */
          if(FuncLogicTab[i].Attr.Bit.Priority <= FuncLogicTab[j].Attr.Bit.Priority)
          {
            *FuncLogicTab[j].pFuncCur = 0;                                               /*更新到最新值*/
            if(FuncLogicTab[j].pFuncSwitch != NULL)
            {
              FuncLogicTab[j].pFuncSwitch(CLOSE, (FuncLogic_t*)&FuncLogicTab[j]);        /*关闭操作*/
            }
            *FuncLogicTab[j].pFuncHis = *FuncLogicTab[j].pFuncCur;
          }
          else
          {
            *FuncLogicTab[i].pFuncCur = 0;                                               /*更新到最新值*/
            if(FuncLogicTab[i].pFuncSwitch != NULL)
            {
              FuncLogicTab[i].pFuncSwitch(CLOSE, (FuncLogic_t*)&FuncLogicTab[i]);        /*关闭操作*/
            }
            *FuncLogicTab[i].pFuncHis = *FuncLogicTab[i].pFuncCur;
            break;                                                                       /*被高优先级的关闭了，没必要再比较了，跳出循环*/
          }
        }
      }

      if((FuncLogicTab[i].pFuncSwitch != NULL) &&                                        /*函数有效*/
         (FuncLogicTab[i].pFuncCur    != 0)    )                                         /*没被高优先级的冲突方关闭*/
      {
        FuncLogicTab[i].pFuncSwitch(OPEN, (FuncLogic_t*)&FuncLogicTab[i]);               /*打开操作*/
        *FuncLogicTab[i].pFuncHis = *FuncLogicTab[i].pFuncCur;
      }
    }
  }
}

/*
************************************************************************************************************************
* 函数名称 : MChair_FuncSwitch_CloseForNewFunc                                                                                                         
* 功能描述 : 功能切换  为新功能的开启 关闭占用的资源
*            注：关闭功能（无功能）也是新功能，同样要切换，同样要关闭占用资源。                                                                                               
* 输入参数 : pFuncLogic           -- 功能逻辑的描述
*            ActionTabAttrTab     -- 包含 动作表格属性 的表格
*            ActionTabAttrTabNum  -- 包含 动作表格属性 的表格 的条目数量
*            pTabStep             -- 表格使用的动作步骤                                                                                      
* 返回参数 : 新功能动作表格属性 的索引，
*            特殊值INDEX_NO_MATCH -- 无匹配的索引    
*
* 补充说明 : 1、进入一个新按摩功能时，需要将旧功能占用的部件资源关闭。
*               pFuncLogic 参数里的Component 描述了功能使用的主部件资源（机芯、充气、推杆）。
*               ActionTabAttrTab 表格里的表格项的参数 RollerVibAccompanyBit 和 
*               LedHeatAccompanyBit 描述了功能使用的伴随部件资源（滚轮、振动、加热、灯光）。 
*
*            2、该函数主要在 自动程序 的切换函数内调用。
*               手动程序一般在各种的切换函数内会有单独的特殊操作。
************************************************************************************************************************
*/
uint16_t MChair_FuncSwitch_CloseForNewFunc(FuncLogic_t *pFuncLogic, const ActionTabAttr_t ActionTabAttrTab[], uint8_t ActionTabAttrTabNum, ActionTabStep_t *pTabStep)
{
  uint16_t Index;
  uint8_t  i, j;
  const ActionTabAttr_t  *pActionTabAttrHis;                      /*旧动作的 动作表格属性*/
  const ActionTabAttr_t  *pActionTabAttrCur;                      /*新动作的 动作表格属性*/


  /*关闭主部件(机芯 充气 推杆)-----------------------------------------------*/
  if(pFuncLogic->MainComponent.Bit.Core)                          /*要关闭机芯功能*/
  {
    MChair_TabHandle_ResetMixOtherTabStep(TRUE);                  /*复位机芯混合其他表格的处理步骤*/
    Core_SetAction(CORE_ACTION_EXE_NONE, XYZ_ACTION_NONE, TCS_ACTION_NONE); 
    Core_SetXYZPosition(PXWIDE, PYTOP, PZBACK); 
    pMChair->CSFlag.Bit.FuncExeAngleNeedSet = TRUE;               /*需要设置功能执行角度*/
    Core_ResetXYZActionStep();                                    /*自动程序切换时将动作完成次数清零*/
  }

  if(pFuncLogic->MainComponent.Bit.Gas)                           /*关闭充气功能*/
  {
    Gas_SetPumpSw(OFF);
    Gas_AllCtrlEn();                                              /*所有部位充气控制使能*/ 
    Gas_SetGasPart(0, 0);
    pMChair->GasIntensity = 3;                                    /*充气强度*/
  }

  /*Hzy-20171227:开机角度-->用户按自动程序时，会倒执行角度-->用户关闭或切换程序，若倒执行角度还为完成，则应停止*/
  if((pFuncLogic->MainComponent.Bit.Spike)                   ||   /*关闭推杆功能*/
     (FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Core))    /*机芯功能状态：自动  Hzy-20171227*/
  {
    Spike_SetLegFlexAngle(PLEGFLEX_MIN);                          /*伸缩推杆缩到最短*/
    Spike_SetULegFlexAngle(PULEGFLEX_MAX);                        /*上小腿伸到最长*/
    if(FUNC_TYPE_AUTO == pFuncLogic->Attr.Bit.FuncType)           /*要关闭的功能，推杆工作在自动*/
    {
      Spike_SetAngle(PKEEP, PKEEP, PKEEP);                        /*停止推杆*/
    }
  }

  /*给新功能的伴随功能赋值（滚轮、振动、加热、灯光）-------------------------------------------------*/
  Index = INDEX_NO_MATCH;                                         /*先假设没有匹配的动作表格属性的索引*/

  if(ActionTabAttrTab != NULL)                                    /*有具体的动作表格属性*/
  {
    pActionTabAttrHis = NULL;                                     /*旧动作的 动作表格属性*/
    pActionTabAttrCur = NULL;                                     /*新动作的 动作表格属性*/
    
    /*在一款按摩椅中不可能同时存在太多的表格，因此这里使用遍历查找。有两个查找量，避免两次for循环，使用双向查找。*/
    for(i=0,j=(ActionTabAttrTabNum-1); i<ActionTabAttrTabNum; i++,j--)
    {
      if(*pFuncLogic->pFuncHis == ActionTabAttrTab[i].FuncID)
      {
        pActionTabAttrHis = &ActionTabAttrTab[i];
      }
      if(*pFuncLogic->pFuncCur == ActionTabAttrTab[j].FuncID)
      {
        pActionTabAttrCur = &ActionTabAttrTab[j];
        Index = j;                                                /*记录新动作表格属性的索引*/
      }
      
      if((pActionTabAttrHis != NULL) && (pActionTabAttrCur != NULL) )
      {
        break;                                                    /*新动作和旧动作的表格都查找完毕，跳出循环*/
      }
    }
  }

  if((pActionTabAttrHis != NULL) && (pActionTabAttrCur != NULL))  /*新动作和旧动作的表格属性都存在*/
  {
    /*如果都为NONE，则不赋值，否则用新功能Cur的伴随模式赋值*/
    if((pActionTabAttrHis->FeetRollerMode != FUNC_NONE) ||        /*脚滚*/
       (pActionTabAttrCur->FeetRollerMode != FUNC_NONE) )
    {
      MChair_RollerFuncReset_Feet();
      pMChair->FuncMA_Roller.Bit.Feet = pActionTabAttrCur->FeetRollerMode;  
    }
    if((pActionTabAttrHis->CalvesRollerMode != FUNC_NONE) ||      /*腿滚*/
       (pActionTabAttrCur->CalvesRollerMode != FUNC_NONE) )
    {
      MChair_RollerFuncReset_Calves();
      pMChair->FuncMA_Roller.Bit.Calves = pActionTabAttrCur->CalvesRollerMode;  
    }

    if((pActionTabAttrHis->FeetVibMode != FUNC_NONE) ||           /*脚部振动*/
       (pActionTabAttrCur->FeetVibMode != FUNC_NONE) )
    {
      MChair_VibFuncReset_Feet();
      pMChair->FuncMA_Vib.Bit.Feet = pActionTabAttrCur->FeetVibMode;           
    }
    if((pActionTabAttrHis->CalvesVibMode != FUNC_NONE) ||         /*腿部振动*/
       (pActionTabAttrCur->CalvesVibMode != FUNC_NONE) )
    {
      MChair_VibFuncReset_Calves();
      pMChair->FuncMA_Vib.Bit.Calves = pActionTabAttrCur->CalvesVibMode;           
    }
    if((pActionTabAttrHis->SeatVibMode != FUNC_NONE) ||           /*座部振动*/
       (pActionTabAttrCur->SeatVibMode != FUNC_NONE) )
    {
      MChair_VibFuncReset_Seat();
      pMChair->FuncMA_Vib.Bit.Seat = pActionTabAttrCur->SeatVibMode;           
    }
    if((pActionTabAttrHis->LumbarBackVibMode != FUNC_NONE) ||     /*腰背振动*/
       (pActionTabAttrCur->LumbarBackVibMode != FUNC_NONE) )
    {
      MChair_VibFuncReset_LumbarBack();
      pMChair->FuncMA_Vib.Bit.LumbarBack = pActionTabAttrCur->LumbarBackVibMode;           
    }
    
    if((pActionTabAttrHis->FeetHeatMode != FUNC_NONE) ||          /*脚部加热*/
       (pActionTabAttrCur->FeetHeatMode != FUNC_NONE) )
    {
      MChair_HeatFuncReset_Feet();
      pMChair->FuncMA_Heat.Bit.Feet = pActionTabAttrCur->FeetHeatMode ;       
    }
    
    if((pActionTabAttrHis->CalvesHeatMode != FUNC_NONE) ||        /*腿部加热*/
       (pActionTabAttrCur->CalvesHeatMode != FUNC_NONE) )
    {
      MChair_HeatFuncReset_Calves();
      pMChair->FuncMA_Heat.Bit.Calves = pActionTabAttrCur->CalvesHeatMode ;       
    }
    if((pActionTabAttrHis->SeatHeatMode != FUNC_NONE) ||          /*座部加热*/
       (pActionTabAttrCur->SeatHeatMode != FUNC_NONE) )
    {
      MChair_HeatFuncReset_Seat();
      pMChair->FuncMA_Heat.Bit.Seat = pActionTabAttrCur->SeatHeatMode ;       
    }
    if((pActionTabAttrHis->LumbarBackHeatMode != FUNC_NONE) ||    /*腰背加热*/
       (pActionTabAttrCur->LumbarBackHeatMode != FUNC_NONE) )
    {
      MChair_HeatFuncReset_LumbarBack();
      pMChair->FuncMA_Heat.Bit.LumbarBack = pActionTabAttrCur->LumbarBackHeatMode;        
    }
    
    if((pActionTabAttrHis->LedMode != FUNC_NONE) ||               /*呼吸灯*/
       (pActionTabAttrCur->LedMode != FUNC_NONE) )
    {
      pMChair->FuncMA_Led.Bit.Led = pActionTabAttrCur->LedMode;             
    }
  }
  
  /*复位表格步骤-----------------------------------------------------------*/
  memset(pTabStep, 0, sizeof(ActionTabStep_t));
  if(pActionTabAttrCur != NULL)
  {
    pTabStep->Num = pActionTabAttrCur->StartStepNum;              /*将相应的执行步骤更新为表格的开始步骤*/
  }

  /*操作结束，返回新动作表格属性的索引-------------------------------------*/
  return Index;
}


/*
************************************************************************************************************************
* 函数名称 : MChair_FuncExeAngleHandle                                                                                                         
* 功能描述 : 按摩功能执行角度处理                                                                                          
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                                                               
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void MChair_FuncExeAngleHandle(Ticker_t ExePeriod)
{
  if(FALSE == pMChair->CSFlag.Bit.FuncExeAngleNeedSet)   /*无需设置功能执行角度*/
  {
    return;
  }
  
  if(FALSE == pMChair->StateBodyScan.Bit.Finish)          /*人体扫描未完成*/
  {
    return;
  }

  /*设置程序执行初始角度--------------------------------------------------------------------*/
  if(pMChair->FuncAuto_CoreGas)
  {
    pMChair->FuncAuto_Spike = FA_SPIKE_NONE;
    if((pMChair->FuncAuto_CoreGas == FA_COREGAS_Shiatsu)           ||
       (pMChair->FuncAuto_CoreGas == FA_COREGAS_Man)               ||
       (pMChair->FuncAuto_CoreGas == FA_COREGAS_ShoulderShiatsu)   ||
       (pMChair->FuncAuto_CoreGas == FA_COREGAS_LumbarButtockPress))
    {
      Spike_SetAngle(PBACK_ZERO2_ANGLE, PFEET_ZERO2_ANGLE, PZERO_EXE_ANGLE);  /*执行角度*/
    }
    else if(pMChair->FuncAuto_CoreGas == FA_COREGAS_Relax)        
    {
      Spike_SetAngle(PBACK_EXE_ANGLE, PFEET_ZERO2_ANGLE, PZERO_EXE_ANGLE);    /*执行角度*/
    }
    else
    {
      Spike_SetAngle(PBACK_EXE_ANGLE, PFEET_EXE_ANGLE, PZERO_EXE_ANGLE);  /*执行角度*/
    }
    Spike_LegLenDetectRedo();                                           /*推杆角度可能未变，强制腿长重新检测*/
  }
  
  pMChair->CSFlag.Bit.FuncExeAngleNeedSet = FALSE;
}


/*
************************************************************************************************************************
* 函数名称 : MChair_FuncExe                                                                                                         
* 功能描述 : 按摩功能的执行                                                                                             
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                                                               
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void MChair_FuncExe(Ticker_t ExePeriod)
{
  uint8_t i;
  static uint8_t CorePauseOnOff = OFF;
  static uint8_t OtherPauseOnOff = OFF;

  
  /*人体检测的处理---------------------------------------------------*/
  BodyScan_Handle(ExePeriod);

  /*是否可执行本函数判断-------------------------------------------------*/
  if((pMChair->SysModeCur != SYS_MODE_STANDBY)     &&               /*注：待机下，可执行推杆调节功能*/
     (pMChair->SysModeCur != SYS_MODE_USERRUN)     &&               /*这三个模式差别不大，*/ 
     (pMChair->SysModeCur != SYS_MODE_TESTNOTIMER) &&               /*差别在 SysMode_UserRun_Timer()函数中处理*/
     (pMChair->SysModeCur != SYS_MODE_TESTAGE)     )
  {
    return;
  }

  if(TRUE == pMChair->CSFlag.Bit.Pause)
  {
    return;                                                         /*暂停时，不执行按摩功能*/
  }

  /*执行前，先进行逻辑切换处理-------------------------------------------*/
  MChair_FuncLogic_Switch();                                        /*功能逻辑切换*/

  /*各个功能的执行-------------------------------------------------------*/
  /*功能执行前，将部件的功能状态清除，每个执行函数内部将根据实际情况赋值*/
  pMChair->ComponentFuncState.All = FUNC_TYPE_NONE;

  /*功能执行前先清除一些标识，执行函数内将根据实际情况赋值*/
  pMChair->CSFlag.Bit.ZeroGravityAngleRun            = FALSE;       /*零重力摆角度运行标识*/
  pMChair->CSFlag.Bit.GasCooperateSpikeRun           = FALSE;       /*充气配合推杆运行标识*/
  pMChair->CSFlag.Bit.BackSpikeMannualMoveDisable    = FALSE;       /*靠背推杆手动*/
  pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable    = FALSE;       /*零重力推杆手动*/
  pMChair->CSFlag.Bit.FeetSpikeMannualMoveDisable    = FALSE;       /*小腿推杆手动*/
  pMChair->CSFlag.Bit.LegFlexMannualMoveDisable      = FALSE;       /*小腿伸缩手动*/
  pMChair->CSFlag.Bit.ULegFlexMannualMoveDisable     = FALSE;       /*上小腿伸缩手动*/
  pMChair->CSFlag.Bit.FeetHeatMannualOpDisable       = FALSE;       /*脚部加热手动*/
  pMChair->CSFlag.Bit.CalvesHeatMannualOpDisable     = FALSE;       /*腿部加热手动*/
  pMChair->CSFlag.Bit.SeatHeatMannualOpDisable       = FALSE;       /*座部加热手动*/
  pMChair->CSFlag.Bit.LumbarBackHeatMannualOpDisable = FALSE;       /*靠背加热手动*/
  
  MChair_FuncExeAngleHandle(ExePeriod);                             /*按摩程序执行时的角度处理 */

  for(i=0; i<FUNC_LOGIC_TAB_NUM; i++)
  {
    if(*FuncLogicTab[i].pFuncCur > 0)                               /*有功能被打开的才执行*/
    {
      if(FuncLogicTab[i].pFuncExe != NULL)
      {
        FuncLogicTab[i].pFuncExe(ExePeriod, (FuncLogic_t*)&FuncLogicTab[i]);
      }
    }
  }

  /*=====================通用的补充处理==============================*/
  /* 暂停关系处理-----------------------------------------------------
   * 注意：旧架构中，对机芯的四个马达是分别暂停的。
   *       由于旧架构机芯动作手法，马达之间几乎没什么关联，这样做不会有什么问题。
   *       新架构中的机芯组合动作手法，马达之间存在位置等的关联。所以不能像旧架构那样分别暂停。必须一起暂停。
   *       因此这里直接暂停机芯（将会暂停x、y、z、tap四个马达）。而不是选择性的暂停某些马达。*/

  if(TRUE == pMChair->StateZeroSpike.Bit.Work)                      /*零重力升降中*/
  {
    PAUSE_ON(&CorePauseOnOff, 0, Core_PauseOn);
  }
  else
  {
    PAUSE_OFF(&CorePauseOnOff, 0, Core_PauseOff);
  }
  
//  if((TRUE == pMChair->StateBodyScan.Bit.Run)  &&                 /*扫描时 调节靠背位置*/
//     (TRUE == pMChair->StateBackSpike.Bit.Work))
//  {
//    PAUSE_ON(&CorePauseOnOff, 1, Core_PauseOn);
//  }
//  else
//  {
//    PAUSE_OFF(&CorePauseOnOff, 1, Core_PauseOff);
//  }

  /*腿长检测开关--------------------------------------------------------*/
  if(pMChair->ComponentFuncState.Bit.Spike != FUNC_TYPE_AUTO)       /*推杆功能状态：非自动*/
  {
    Spike_SetLegLenDetectSw(ON);                                    
    if(TRUE == pMChair->StateSpike.Bit.LegLenDetectRun)             /*腿长检测运行中*/
    {
      pMChair->CSFlag.Bit.LegFlexMannualMoveDisable  = TRUE;        /*小腿伸缩手动无效*/
    }
  }
  else
  {
    Spike_SetLegLenDetectSw(OFF);                                   /*推杆自动程序，不进行腿长自动检测*/
  }
  
  /*对腿脚充气的特殊处理--------------------------------------------*/
  if(FALSE == pMChair->CSFlag.Bit.GasCooperateSpikeRun)             /*无充气配合推杆的动作*/
  {
    if((TRUE == pMChair->StateZeroSpike.Bit.Work)        ||         /*零重力升降中*/
       //(TRUE == pMChair->StateBackSpike.Bit.Work)        ||         /*靠背升降中*/
       (TRUE == pMChair->StateFeetSpike.Bit.Work)        ||         /*小腿升降中*/
       (TRUE == pMChair->StateLegFlexSpike.Bit.ULegWork) ||         /*小腿伸缩中*/
       (TRUE == pMChair->StateBodyScan.Bit.Run)          ||         /*人体检测中*/
       (TRUE == pMChair->StateLegFlexSpike.Bit.Work)     )          /*小腿伸缩中*/
    {
      Gas_CalvesFeetCtrlEnOnly();                                   /*腿脚充气控制使能*/    
      Gas_SetGasPart(0, 0);                                         /*关腿脚充气*/
    }
  }

  /*小腿伸缩中，停止脚滚腿滚运动*/
  if((TRUE == pMChair->StateFeetSpike.Bit.Work)   ||                /*小腿升降中*/
     (TRUE == pMChair->StateLegFlexSpike.Bit.Work))                 /*小腿伸缩中*/
  {
    Roller_SetFeetRollerKeepAtInitPosition();
    PAUSE_ON(&OtherPauseOnOff, 1, Roller_CalvesRollerPauseOn);
  }
  else
  {
    Roller_ClrFeetRollerKeepAtInitPosition();
    PAUSE_OFF(&OtherPauseOnOff, 1, Roller_CalvesRollerPauseOff);
  }

  if(FALSE == pMChair->StateBodyScan.Bit.Finish)          /*人体扫描未完成*/
  {
    PAUSE_ON(&OtherPauseOnOff, 2, Spike_LegLenDetectPauseOn);
  }
  else
  {
    PAUSE_OFF(&OtherPauseOnOff, 2, Spike_LegLenDetectPauseOff);
  }

  /*机芯到肩部时不充气*/
  if((Core_GetYPosition() > PY02) && (Core_GetYPosition() < PY15))
  {
    if(FALSE == pMChair->CSFlag.Bit.GasCooperateSpikeRun)           /*无充气配合推杆的动作*/
    {
      Gas_ShoulderCtrlEnOnly();                                     /*肩部充气控制使能，其他部位控制关闭*/      
      Gas_SetGasPart(0, 0);
    }
  }
  
  Gas_SetCalvesPressureThreshold(pMChair->GasIntensity);

  /*伴随功能 的强制关闭---------------------------------------------*/
//  if(FUNC_TYPE_NONE == pMChair->ComponentFuncState.Bit.Core)
//  {
//    pMChair->FuncMA_Heat.Bit.LumbarBack = FMA_HEAT_NONE;            /*机芯无功能，则关闭按摩头加热功能*/
//    pMChair->CSFlag.Bit.LumbarBackHeatMannualOpDisable = TRUE;      /*靠背加热手动无效*/
//  }

//  if((FUNC_TYPE_NONE == pMChair->ComponentFuncState.Bit.Core) &&
//     (FUNC_TYPE_NONE == pMChair->ComponentFuncState.Bit.Gas)  )
//  {
//    pMChair->FuncMA_Heat.Bit.Feet = FMA_HEAT_NONE;                  /*机芯和充气都无功能，则关闭脚部加热功能*/
//    pMChair->CSFlag.Bit.FeetHeatMannualOpDisable = TRUE;            /*脚部加热手动无效*/
//    pMChair->FuncMA_Heat.Bit.Calves = FMA_HEAT_NONE;                /*机芯和充气都无功能，则关闭腿部加热功能*/
//    pMChair->CSFlag.Bit.CalvesHeatMannualOpDisable = TRUE;          /*腿部部加热手动无效*/
//  }
}
