/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: FuncTabHandle.c 
**
**    功能描述: 按摩功能动作表格的处理
**
**    公    司: 蒙发利电子
**
**    项目名称: 
**
**    平台信息: 
**
**    作    者: Hzy
**
**    其他说明: 
**          (1) 关于【机芯 自动】相关动作表格内的 Repeat 与 Time的说明
**              旧架构中的机芯动作手法，几乎都是单独的手法。可全部用时间来控制步骤的迭代。
**              新架构有许多组合手法，组合手法很难用时间来控制步骤的迭代，应该以动作完成的次数来控制。
**              因此，新架构在动作表格中加入了变量Repeat来控制动作的执行次数。  
**              目前，新架构【机芯】相关自动程序中 只有在 Repeat 次数值为RIGNORE，
**              或CoreXYZAction 动作为 XYZ_ACTION_NONE 时，才用时间来控制步骤的迭代。
**              其他的都用且Repeat来次数来进行步骤的迭代。且Repeat次数不为RIGNORE时，将忽略时间的判断。
**
**          (2) 关于部件的组合 
**              新架构以【机芯】、【充气】、【推杆】这三个主部件作为动作表格的组合元素。
**              可生成 7 种排列组合： 【机芯】、【充气】、【推杆】、【机芯+充气】、
**                                    【机芯+推杆】、【充气+推杆】、【机芯+充气+推杆】
**              其他的功能部件(如滚轮、振动)不再参与动作表格的组合，而是作为附加的伴随功能而存在。
**              附加的伴随功能既可以单独的运行，在主功能开启后，也可单独的对其进行开关操作。
**              这样做可控制排列组合的数量，否则如果所有的部件都像旧架构那样都可以组合。
**              随着组合数量的增多，相关判断逻辑将越来越复杂。
**
**    修改记录:  ------------------------------------------------------------------------------------------------------
**               2016.6.16 ---------------------------------------------------------------------------
**               给 ActionTabAttr_t类型增加两个变量 StartStepNum(表格开始 步骤数) 和 EndStepNum(表格结束 步骤数)。
**               并修改相应的代码，使得动作表格的执行步骤数量限制在  StartStepNum  和 EndStepNum之间。               
**
**               2016.6.20 ---------------------------------------------------------------------------
**               修改 MChair_TabHandle_CoreMixOtherAuto()函数及其相关部分逻辑。
**                 
**               原来  【Other】表格中插入【Other】表格的判断逻辑是：(★在ECP388机型上使用★)
**               当【Core】表格中的 XYZAction = XYZ_ACTION_NONE  且                   
**                                  Time1 = TIGNORE                                 
**               这两个条件都满足时，【Other】作为插入表格。                      
**               其他情况下，【Other】作为伴随表格。                                
**
**               现在将 【Other】表格中插入【Other】表格的判断逻辑 改为：
**               当【Core】表格中的 Repeat = RIGNORE   且                           
**                                  Time1 = TIGNORE                                 
**               这两个条件都满足时，【Other】作为插入表格。                      
**               其他情况下，【Other】作为伴随表格。   
**
**               ★★：如果从ECP388程序中拷贝表格过来用时，应注意修改相关表格内容。
**
**               2016.12.5 ---------------------------------------------------------------------------
**               增加表格体验调试功能。
**               通过上位机能够快速编排自动程序表格。
========================================================================================================================
========================================================================================================================
*/
/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "FuncTabHandle.h"
#include "FuncLogic.h"
#include "MChair.h"
#include "FuncTab.h"
#include "CDP.h"

/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/
/*要体验的表格类型：b0--机芯  b1--充气  b2--推杆 */
#define  TAB_TRY_TYPE_CORE                            B(00000001)
#define  TAB_TRY_TYPE_GAS                             B(00000010)
#define  TAB_TRY_TYPE_SPIKE                           B(00000100)
#define  TAB_TRY_TYPE_COREGAS                         B(00000011)
#define  TAB_TRY_TYPE_CORESPIKE                       B(00000101)
#define  TAB_TRY_TYPE_GASSPIKE                        B(00000110)
#define  TAB_TRY_TYPE_COREGASSPIKE                    B(00000111)

#define  TABTYPE_CHANNEL_SUM                          2           /*表格体验通道数量*/
/*
========================================================================================================================
*【本地数据类型定义】                              【本地数据类型定义】                              【本地数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  表格体验用，表格类型到功能的关联                                                          
************************************************************************************************************************
*/
typedef struct
{
  uint8_t                         TapType;                           /*表格类型*/
  uint16_t                        *pFuncCur;                         /*当前功能*/
}ActionTabTry_TapTypeToFuncCur_t;

/*
************************************************************************************************************************
* 类型定义 :  表格体验相关操作数据                                                        
************************************************************************************************************************
*/
typedef struct
{
  uint8_t                         ChannelSw;                         /*通道开关*/
  uint8_t                         SetpHop;                           /*跳步标识*/
  
  CDP_DataFormat0x1A_To_0x1F_t    *pStepDataCur;                     /*当前执行的步骤数据*/
  CDP_DataFormat0x1A_To_0x1F_t    *pStepDataNext;                    /*缓存的下一步要执行的数据*/
}ActionTabTry_t;

/*
========================================================================================================================
*【变量定义 & 各种声明】                          【变量定义 & 各种声明】                          【变量定义 & 各种声明】    
========================================================================================================================
*/
static const ActionTabTry_TapTypeToFuncCur_t TapTypeToFuncCurTab[] =   /*类型与功能关联表格*/
{
  {TAB_TRY_TYPE_CORE,            &MChair.FuncAuto_Core},
  {TAB_TRY_TYPE_GAS,             &MChair.FuncAuto_Gas},
  {TAB_TRY_TYPE_SPIKE,           &MChair.FuncAuto_Spike},
  {TAB_TRY_TYPE_COREGAS,         &MChair.FuncAuto_CoreGas},
  {TAB_TRY_TYPE_CORESPIKE,       &MChair.FuncAuto_CoreSpike},
  {TAB_TRY_TYPE_GASSPIKE,        &MChair.FuncAuto_GasSpike},
  {TAB_TRY_TYPE_COREGASSPIKE,    &MChair.FuncAuto_CoreGasSpike}
};
#define  TABTYPE_TO_FUNCCUR_TAB_ISUM     TAB_ISUM(TapTypeToFuncCurTab)

ActionTabTry_t  ActionTabTry[TABTYPE_CHANNEL_SUM];                                                     /*动作表格体验通道*/
uint8_t         TabTryStepDataCur[TABTYPE_CHANNEL_SUM][sizeof(CDP_DataFormat0x1A_To_0x1F_t) + 30];     /*步骤数据缓存数组*/
uint8_t         TabTryStepDataNext[TABTYPE_CHANNEL_SUM][sizeof(CDP_DataFormat0x1A_To_0x1F_t) + 30];    /*步骤数据缓存数组*/

uint8_t MChair_TabHandle_CDPDataObjRx_0x1F(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
void* MChair_TabTry_GetStepData(uint8_t TabType, ActionTabStep_t *pStep);
void  MChair_TabTry_UpdateStepHopState(uint8_t TabType, ActionTabStep_t *pStep);

/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : MChair_TabTry_ChInit                                                                                   
* 功能描述 : 表格体验 之 通道初始化
* 输入参数 : 无  
* 返回参数 : 无                                                                                      
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void MChair_TabTry_ChInit(uint8_t ch)
{
  memset(&ActionTabTry[ch], 0, sizeof(ActionTabTry_t));    
  memset(&TabTryStepDataCur[ch][0],  0, sizeof(CDP_DataFormat0x1A_To_0x1F_t) + 30);    
  memset(&TabTryStepDataNext[ch][0], 0, sizeof(CDP_DataFormat0x1A_To_0x1F_t) + 30);    
  ActionTabTry[ch].pStepDataCur  = (CDP_DataFormat0x1A_To_0x1F_t*)&TabTryStepDataCur[ch][0];
  ActionTabTry[ch].pStepDataNext = (CDP_DataFormat0x1A_To_0x1F_t*)&TabTryStepDataNext[ch][0];
}

/*
************************************************************************************************************************
* 函数名称 : MChair_TabTry_CDPDataObjRx_0x1A_To_0x1F                                                                                   
* 功能描述 : 表格体验 之 接收数据 (通道0(0x1A)~通道5(0x1F))。   
*            0x1F 表格调试（上位机 <-->中心板）：用于辅助编排按摩动作表格                                                                                   
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 上位机开启表格体验功能时，会先发第0步的数据，后续则根据收到的应答数据中的步骤号，
*            发送“收到的步骤号+1”步骤号的数据，以让中心板能够提前缓存下一步的数据，
*            这样可避免步骤迭代时，由于通信延迟带来的动作切换延迟。
************************************************************************************************************************
*/
uint8_t MChair_TabTry_CDPDataObjRx_0x1A_To_0x1F(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  uint8_t Index, j;
  uint8_t ChNum;
  CDP_DataFormat0x1A_To_0x1F_t  *pRxData0x1A1F;
  CDP_DataFormat0x1A_To_0x1F_t  *pAckData0x1A1F;

  SysMode_UserRun_Enter();               /*表格体验时，自动开机*/              
  pMChair->CSFlag.Bit.TabTryRun = TRUE;  /*表格体验进行中，关机才会清除*/
  
  memcpy(&pAckDU[CDP_DU_OFFSET_LEN], &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  pAckData0x1A1F = (CDP_DataFormat0x1A_To_0x1F_t *)&pAckDU[CDP_DU_OFFSET_LEN];
  pRxData0x1A1F  = (CDP_DataFormat0x1A_To_0x1F_t *)&pRxDU[CDP_DU_OFFSET_LEN];
  ChNum = pRxData0x1A1F->DataID - 0x1A;
  
  do
  {
    if(ChNum >= TABTYPE_CHANNEL_SUM)
    {
      pAckData0x1A1F->Byte2.Bit.ChannelNoSupport = TRUE;                                        /*通道号不支持*/
      break;
    }
  
    /*体验通道开关是否改变-----------------------------------------------------------------------*/
    if(ActionTabTry[ChNum].ChannelSw != pRxData0x1A1F->Byte0.Bit.ChannelSw)
    {
      for(Index=0; Index<TABTYPE_TO_FUNCCUR_TAB_ISUM; Index++)
      {
        if(TapTypeToFuncCurTab[Index].TapType == pRxData0x1A1F->TabType)                        /*遍历查找，看是否有匹配的表格类型*/
        {
          break;
        }
      }
      if(Index >= TABTYPE_TO_FUNCCUR_TAB_ISUM) 
      {
        pAckData0x1A1F->Byte2.Bit.TapTypeNoSupport = TRUE;                                      /*表格类型不支持*/
        break;
      }
      
      if(ON == pRxData0x1A1F->Byte0.Bit.ChannelSw)                                              /*通道打开，则查看表格类型中资源是否冲突*/
      {
        for(j=0; j<TABTYPE_CHANNEL_SUM; j++)                                                    /*遍历所有通道，看资源是否冲突*/
        {
          if(j == ChNum)
          {
            continue;                                                                           /*跳过与自身的比较*/
          }
            
          if(ON == ActionTabTry[j].ChannelSw)                                                   /*只比较打开的通道*/
          {
            if((ActionTabTry[j].pStepDataCur->TabType & pRxData0x1A1F->TabType) != 0)
            {
              pAckData0x1A1F->Byte2.Bit.ResourceConflict = TRUE;                                /*表格类型中资源冲突*/
              pAckData0x1A1F->Byte2.Bit.ConflictChnanelNum = j;                                 /*冲突的通道号*/
              break;                                                                            /*跳出，资源冲突比较的for循环*/
            }
          }
        }
        if(TRUE == pAckData0x1A1F->Byte2.Bit.ResourceConflict)
        {
          break;                                                                                /*资源冲突，则跳出while(0)*/
        }      
      }      
      
      MChair_TabTry_ChInit(ChNum);                                                              /*通道开关改变，则重新初始化通道*/
      ActionTabTry[ChNum].ChannelSw = pRxData0x1A1F->Byte0.Bit.ChannelSw;  
      memcpy(ActionTabTry[ChNum].pStepDataCur, pRxData0x1A1F, pRxData0x1A1F->DataLen);          /*通道开关改变时，直接更新当前要执行的步骤数据*/
      if(ON == pRxData0x1A1F->Byte0.Bit.ChannelSw)
      {
        *TapTypeToFuncCurTab[Index].pFuncCur = FA_TAB_TRY;                                      /*开启体验功能*/
      }
      else
      {
        *TapTypeToFuncCurTab[Index].pFuncCur = FUNC_NONE;                                       /*关闭功能*/
      }
    }
    
    /*体验通道开关打开时才接收步骤数据-----------------------------------------------------------*/
    if(ON == pRxData0x1A1F->Byte0.Bit.ChannelSw)
    {
      if(pRxData0x1A1F->Byte0.Bit.StepHop != STEP_HOP_NONE)                                     /*发生了跳步操作，则要清零之前收到的步骤数据*/
      {
        ActionTabTry[ChNum].SetpHop =  pRxData0x1A1F->Byte0.Bit.StepHop;
        memcpy(ActionTabTry[ChNum].pStepDataCur, pRxData0x1A1F, pRxData0x1A1F->DataLen);        /*将当前执行的步骤数据更新为要跳步的数据*/
      }
      
      memcpy(ActionTabTry[ChNum].pStepDataNext, pRxData0x1A1F, pRxData0x1A1F->DataLen);         /*存储下一步要执行的数据*/
      memcpy(pAckData0x1A1F, ActionTabTry[ChNum].pStepDataCur, ActionTabTry[ChNum].pStepDataCur->DataLen);  /*一切正常，则返回当前的步骤数据给上位机*/
    }  
  }while(0);
  
  return pAckDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* 函数名称 : MChair_TabTry_GetExeStepData                                                                                   
* 功能描述 : 表格体验 之 获取要执行的步骤数据 
* 输入参数 : TabType -- 表格类型
*            pStep   -- 步骤
* 返回参数 : 指向步骤数据的指针                                                                                                        
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void* MChair_TabTry_GetExeStepData(uint8_t TabType, ActionTabStep_t *pStep)
{
  uint8_t ChNum;
  
  if(NULL == pStep)
  {
    return NULL;
  }
  
  for(ChNum=0; ChNum<TABTYPE_CHANNEL_SUM; ChNum++)                                                    
  {
    if((ON      == ActionTabTry[ChNum].ChannelSw)            &&   /*通道打开*/
       (TabType == ActionTabTry[ChNum].pStepDataCur->TabType))    /*类型匹配*/   
    {
      if(ActionTabTry[ChNum].SetpHop != STEP_HOP_NONE)  
      {
        /*收到跳步数据时，MChair_TabHandle_CDPDataObjRx_0x1F()函数内已经将跳步数据更新到当前要执行的步骤数据。
         *这里不能再更新了，否则执行的是跳步的再下一步数据。通过MChair_TabTry_UpdateStepHopState()函数获取跳步标识后，
         *ActionTabStep_IterateHandle()函数才能执行步骤迭代(跳步)时的相关数据变量操更新作。然后在这里才将跳步标识清零。*/
        ActionTabTry[ChNum].SetpHop = STEP_HOP_NONE;
      }
      else if(pStep->AdditonOp.Bit.OccurIterate)  
      { 
        /*除了跳步外，正常的步骤迭代时，则将下一步数据更新到当前要执行的步骤数据*/
        memcpy(ActionTabTry[ChNum].pStepDataCur, ActionTabTry[ChNum].pStepDataNext, ActionTabTry[ChNum].pStepDataNext->DataLen);
      }
      
      return  &ActionTabTry[ChNum].pStepDataCur->StepData[0];  
    }
  }
  
  return NULL;
}

/*
************************************************************************************************************************
* 函数名称 : MChair_TabTry_UpdateStepHopState                                                                                   
* 功能描述 : 表格体验 之 更新步骤的跳步状态
* 输入参数 : TabType -- 表格类型
*            pStep   -- 步骤
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void MChair_TabTry_UpdateStepHopState(uint8_t TabType, ActionTabStep_t *pStep)
{
  uint8_t ChNum;

  if(NULL == pStep)
  {
    return;
  }
  
  for(ChNum=0; ChNum<TABTYPE_CHANNEL_SUM; ChNum++)                                                    
  {
    if((ON      == ActionTabTry[ChNum].ChannelSw)            &&   /*通道打开*/
       (TabType == ActionTabTry[ChNum].pStepDataCur->TabType))    /*类型匹配*/   
    {
      pStep->AdditonOp.Bit.StepHop = ActionTabTry[ChNum].SetpHop;
      return;
    }
  }
}

/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
/*
************************************************************************************************************************
* 函数名称 : ActionObjHandle_CoreAuto                                                                                   
* 功能描述 : 动作对象处理 之 机芯自动                                                                                   
* 输入参数 : pCoreAutoActionObj -- 机芯自动动作对象  
*            pStep              -- 步骤
*            ActionRepeat       -- 表格里机芯动作次数                                                                   
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void ActionObjHandle_CoreAuto(CoreAutoActionObj_t *pCoreAutoActionObj, ActionTabStep_t *pStep, uint8_t ActionRepeat)
{
  uint8_t  ZSet;                                                              /*3D强度设置值*/
  uint8_t  ZAjust;
  
  
  /*执行条件判断-----------------------------------------------*/
  if((NULL == pCoreAutoActionObj) || 
     (NULL == pStep)              )
  {
    return;
  }

  if((0xAA == pCoreAutoActionObj->XPosition) &&
     (0xAA == pCoreAutoActionObj->YPosition) &&
     (0xAA == pCoreAutoActionObj->ZPosition) )
  {
    pStep->Num = ACTION_TAB_STEP_NUM_END;                                     /*表格结束*/
  }

  if(pStep->Num > ACTION_TAB_STEP_NUM_MAX)
  {
    return;
  }

  /*设置机芯位置-----------------------------------------------------*/
  Core_SetXPosition(pCoreAutoActionObj->XPosition);
  Core_SetYPosition(pCoreAutoActionObj->YPosition);

  /*设置伸缩度 = 表格中的值 + pMChair->AutoCoreFlexLevelAdjust(自动程序下，用户额外的调节量)*/
  ZSet = pCoreAutoActionObj->ZPosition;                                       /*默认3D调节强度下的Z设置值*/
  pMChair->AutoCoreFlexLevelAdjust = (pMChair->AutoCoreFlexLevelAdjust<1) ? 1 : pMChair->AutoCoreFlexLevelAdjust;
  if(pMChair->AutoCoreFlexLevelAdjust > CORE_AUTO_PZLEVEL_REF)                /*3D调节强度变强*/
  {
    ZAjust = pMChair->AutoCoreFlexLevelAdjust - CORE_AUTO_PZLEVEL_REF;
    ZSet += ZAjust;
    if((PZDEC15 <= pCoreAutoActionObj->ZPosition) && 
       (pCoreAutoActionObj->ZPosition <= PZADD15))                            /*跟随曲线*/
    {
      ZSet = (ZSet > PZADD15) ? (PZADD15) : (ZSet);
    }
    else
    {
      ZSet = (ZSet > PZ_MAX) ? (PZ_MAX) : (ZSet);
    }
  }
  else if(pMChair->AutoCoreFlexLevelAdjust < CORE_AUTO_PZLEVEL_REF)           /*3D调节强度变弱*/
  {
    ZAjust = CORE_AUTO_PZLEVEL_REF - pMChair->AutoCoreFlexLevelAdjust;
    if((PZDEC15 <= pCoreAutoActionObj->ZPosition) && 
       (pCoreAutoActionObj->ZPosition <= PZADD15))                            /*跟随曲线*/
    {
      ZSet -= ZAjust;
      ZSet = (ZSet < PZDEC15) ? (PZDEC15) : (ZSet);
    }
    else
    {
      ZSet = (ZSet >= ZAjust) ? (ZSet - ZAjust) : PZ_MIN;
    }
  }             
  
  Core_SetZPosition(ZSet);

  /*设置机芯速度---以后将以组合动作为主，不允许用户调节速度，只能调节3D强度(伸缩度)---------*/
  Core_SetXYZActionSpeed(pCoreAutoActionObj->XYZActionSpeed); 
  Core_SetTCSActionSpeed(pCoreAutoActionObj->TCSActionSpeed); 

  /*设置机芯按摩手法动作---------------------------------------------*/
  Core_SetXYZAction(CORE_ACTION_EXE_AUTO, pCoreAutoActionObj->XYZAction); 
  Core_SetTCSAction(CORE_ACTION_EXE_AUTO, pCoreAutoActionObj->TCSAction); 
  
  /*查询机芯XYZ动作完成次数------------------------------------------*/
  if((pCoreAutoActionObj->XYZAction != XYZ_ACTION_NONE) &&                    /*xyz 动作有效*/
     (ActionRepeat                  != RIGNORE)         )                     /*次数不忽略*/  
  {
    pStep->IncJudgeCondition.Bit.CoreXYZActionRepeat = TRUE;                  /*机芯XYZ动作重复次数  作为步骤增加的判断条件*/  
    pStep->Repeat = Core_GetXYZActionCompleteRepeat();                        /*获取当前动作的完成次数*/
    if(pStep->Repeat >= ActionRepeat)
    {
      pStep->IncConditionState.Bit.CoreXYZActionRepeat = TRUE;                /*步骤增加条件状态：机芯XYZ动作重复次数*/
    }
  }
}

/*
************************************************************************************************************************
* 函数名称 : ActionObjHandle_SpikeAuto                                                                                   
* 功能描述 : 动作对象处理 之 推杆自动                                                                            
* 输入参数 : pSpkeAutoActionObj -- 推杆自动动作对象  
*            pStep              -- 步骤                                                           
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void ActionObjHandle_SpikeAuto(SpikeAutoActionObj_t *pSpkeAutoActionObj, ActionTabStep_t *pStep)
{
  uint8_t         SpikeOkState;
  uint8_t         SpikeOkJudge;

  /*执行条件判断-----------------------------------------------*/
  if((NULL == pSpkeAutoActionObj) || 
     (NULL == pStep)              )
  {
    return;
  }

  if((0xAA == pSpkeAutoActionObj->BackPosition) &&
     (0xAA == pSpkeAutoActionObj->ZeroPosition) &&
     (0xAA == pSpkeAutoActionObj->FeetPosition) )
  {
    pStep->Num = ACTION_TAB_STEP_NUM_END;                                 /*表格结束*/
  }

  if(pStep->Num > ACTION_TAB_STEP_NUM_MAX)
  {
    return;
  }

  /*设置推杆位置------------------------------------------------*/
  if(pSpkeAutoActionObj->BackPosition != PIGNORE)
  {
    Spike_SetBackAngle(pSpkeAutoActionObj->BackPosition);
  }
  if(pSpkeAutoActionObj->ZeroPosition != PIGNORE)
  {
    Spike_SetZeroAngle(pSpkeAutoActionObj->ZeroPosition);
  }
  if(pSpkeAutoActionObj->FeetPosition != PIGNORE)
  {
    Spike_SetFeetAngle(pSpkeAutoActionObj->FeetPosition);
  }

  /*查询推杆位置------------------------------------------------*/
  SpikeOkJudge = 0;                                                       /*默认不判断推杆位置*/
  SpikeOkState = 0;                                                       /*默认推杆位置未到位*/

  if((pSpkeAutoActionObj->BackPosition != PKEEP)   &&
     (pSpkeAutoActionObj->BackPosition != PIGNORE) )
  {
    SpikeOkJudge |= 0x01;                                                 /*要判断背部推杆位置*/
    if(Spike_GetBackAngle() == pSpkeAutoActionObj->BackPosition)
    {
      SpikeOkState |= 0x01;                                               /*背部推杆到位*/
    }
  }

  if((pSpkeAutoActionObj->ZeroPosition != PKEEP)   &&
     (pSpkeAutoActionObj->ZeroPosition != PIGNORE) )
  {
    SpikeOkJudge |= 0x02;                                                 /*要判断零重力推杆位置*/
    if(Spike_GetZeroAngle() == pSpkeAutoActionObj->ZeroPosition)
    {
      SpikeOkState |= 0x02;                                               /*零重力推杆到位*/
    }
  }

  if((pSpkeAutoActionObj->FeetPosition != PKEEP)   &&
     (pSpkeAutoActionObj->FeetPosition != PIGNORE) )
  {
    SpikeOkJudge |= 0x04;                                                 /*要判断腿部推杆位置*/
    if(Spike_GetFeetAngle() == pSpkeAutoActionObj->FeetPosition)
    {
      SpikeOkState |= 0x04;                                               /*腿部推杆到位*/
    }
  }

  if(SpikeOkJudge > 0)                                                    /*需要判断推杆位置*/
  {
    pStep->IncJudgeCondition.Bit.SpikeAngleOk = TRUE;                     /*推杆位置  作为步骤增加的判断条件*/  
    if(SpikeOkJudge == SpikeOkState)
    {
      pStep->IncConditionState.Bit.SpikeAngleOk = TRUE;                   /*步骤增加条件状态：推杆位置*/
    }
  }

  /*小腿伸缩控制------------------------------------------------*/
  if(TRUE == pSpkeAutoActionObj->LegFlexCtrl.Bit.Extend)  
  {
    pStep->IncJudgeCondition.Bit.LegFlexOk = TRUE;                       /*小腿伸缩推杆  作为步骤增加的判断条件*/  

    if((TRUE == pSpkeAutoActionObj->LegFlexCtrl.Bit.CheckTouchGround) && /*要执行触地检测*/
       (TRUE == pMChair->StateLegFlexSpike.Bit.TouchGround)             )  /*已触地*/ 
    {
      pStep->IncConditionState.Bit.LegFlexOk = TRUE;                     /*步骤增加条件状态：小腿伸缩推杆 */
      Spike_SetLegFlexMove(SPIKE_MOVE_NONE);  
    }
    else if(TRUE == pMChair->StateLegFlexSpike.Bit.ReachExtendLimt)      /*伸到极限*/
    {
      pStep->IncConditionState.Bit.LegFlexOk = TRUE;                     /*步骤增加条件状态：小腿伸缩推杆 */
      Spike_SetLegFlexMove(SPIKE_MOVE_NONE);  
    }
    else
    {
      Spike_SetLegFlexMove(SPIKE_MOVE_LEG_EXTEND);  
    }
  }
  else if(TRUE == pSpkeAutoActionObj->LegFlexCtrl.Bit.Shorten)
  {
    pStep->IncJudgeCondition.Bit.LegFlexOk = TRUE;                       /*小腿伸缩推杆  作为步骤增加的判断条件*/  

    if((TRUE == pSpkeAutoActionObj->LegFlexCtrl.Bit.CheckTouchFeet) &&   /*要执行触脚检测*/
       (TRUE == pMChair->StateLegFlexSpike.Bit.TouchFeet)           )    /*已触脚*/ 
    {
      pStep->IncConditionState.Bit.LegFlexOk = TRUE;                     /*步骤增加条件状态：小腿伸缩推杆 */
      Spike_SetLegFlexMove(SPIKE_MOVE_NONE);  
    }
    else if(TRUE == pMChair->StateLegFlexSpike.Bit.ReachShortenLimt)     /*缩到极限*/
    {
      pStep->IncConditionState.Bit.LegFlexOk = TRUE;  
      Spike_SetLegFlexMove(SPIKE_MOVE_NONE);  
    }
    else
    {
      Spike_SetLegFlexMove(SPIKE_MOVE_LEG_SHORT);  
    }
  }
  else
  {
    Spike_SetLegFlexMove(SPIKE_MOVE_NONE);  
  }
  
  if(TRUE == pSpkeAutoActionObj->LegFlexCtrl.Bit.UpExtend)  
  {
    pStep->IncJudgeCondition.Bit.ULegFlexOk = TRUE;                      /*上小腿伸缩推杆  作为步骤增加的判断条件*/  
    if(TRUE == pMChair->StateLegFlexSpike.Bit.ULegReachExtendLimt)       /*伸到极限*/
    {
      pStep->IncConditionState.Bit.ULegFlexOk = TRUE;                    /*步骤增加条件状态：上小腿伸缩推杆 */
      Spike_SetULegFlexMove(SPIKE_MOVE_NONE);  
    }
    else
    {
      Spike_SetULegFlexMove(SPIKE_MOVE_LEG_EXTEND);  
    }
  }
  else if(TRUE == pSpkeAutoActionObj->LegFlexCtrl.Bit.UpShorten)
  {
    pStep->IncJudgeCondition.Bit.ULegFlexOk = TRUE;                      /*上小腿伸缩推杆  作为步骤增加的判断条件*/  
    if(TRUE == pMChair->StateLegFlexSpike.Bit.ULegReachShortenLimt)      /*缩到极限*/
    {
      pStep->IncConditionState.Bit.ULegFlexOk = TRUE;                    /*步骤增加条件状态：上小腿伸缩推杆 */
      Spike_SetULegFlexMove(SPIKE_MOVE_NONE);  
    }
    else
    {
      Spike_SetULegFlexMove(SPIKE_MOVE_LEG_SHORT);  
    }
  }
  else
  {
    Spike_SetULegFlexMove(SPIKE_MOVE_NONE);  
  }
}

/*
************************************************************************************************************************
* 函数名称 : ActionObjHandle_Gas                                                                                   
* 功能描述 : 动作对象处理 之 【充气】                                                                    
* 输入参数 : pGasActionObj -- 充气动作对象  
*            pStep         -- 步骤
*            TimeTab[]     -- 时间表格                                            
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void ActionObjHandle_Gas(GasActionObj_t *pGasActionObj, ActionTabStep_t *pStep, __packed TabItemTime_t TimeTab[])
{
  /*执行条件判断-----------------------------------------------*/
  if((NULL == pGasActionObj) || 
     (NULL == pStep)         ||
     (NULL == TimeTab)       )
  {
    return;
  }

  if((0xAAAA == TimeTab[0]) &&
     (0xAAAA == TimeTab[1]) &&
     (0xAAAA == TimeTab[2]) &&
     (0xAAAA == TimeTab[3]) &&
     (0xAAAA == TimeTab[4]) )
  {
    pStep->Num = ACTION_TAB_STEP_NUM_END;                  /*表格结束*/
  }

  if(pStep->Num > ACTION_TAB_STEP_NUM_MAX)
  {
    return;
  }

  /*充气控制------------------------------------------------*/
  Gas_SetPumpSw(ON);
  Gas_SetGasPart(pGasActionObj->GasPart1.All, pGasActionObj->GasPart2.All);
}

/*
************************************************************************************************************************
* 函数名称 : ActionObjHandle_AccompanyFunc                                                                                   
* 功能描述 : 动作对象处理 之 伴随功能                                                                
* 输入参数 : pActionTabAttr -- 表格属性
*            pStep          -- 步骤
*            pLedHeatCtrl   -- 灯光 加热 伴随控制
*            pRollerVibCtrl -- 滚轮 振动 伴随控制                                     
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void ActionObjHandle_AccompanyFunc(ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep, LedHeatCtrl_t *pLedHeatCtrl, RollerVibCtrl_t *pRollerVibCtrl)
{
  /*执行条件判断-----------------------------------------------*/
  if((NULL == pActionTabAttr) || 
     (NULL == pStep)          ||
     (NULL == pLedHeatCtrl)   || 
     (NULL == pRollerVibCtrl) )
  {
    return;
  }

  if(pStep->Num > ACTION_TAB_STEP_NUM_MAX)
  {
    return;
  }

  /*在功能切换时，将使用动作表格属性pActionTabAttr里的伴随模式对伴随功能赋值。
    当 动作表格属性pActionTabAttr里的伴随模式 为 ByActionTab时，
    伴随功能受动作表格里的控制位LedHeatBit 和 RollerVibBit 控制。
    用户操作手控器可单独开关伴随功能，此时伴随功能的的模式不再为ByActionTab，而是变为Mannual 或 NONE。*/

  /*伴随执行 之 灯光 加热-------------------------------------------------------------*/
  if((FMA_FEET_HEAT_ByActionTab == pActionTabAttr->FeetHeatMode)     &&              /*表格属性里的伴随模式为 ByActionTab*/
     (FMA_FEET_HEAT_ByActionTab == pMChair->FuncMA_Heat.Bit.Feet))                   /*且 当前的模式也为 ByActionTab，即没被用户操作手控器改变*/
  {
    pMChair->FeetHeatCtrlSw = pLedHeatCtrl->Bit.FeetHeat;                            /*脚部加热*/
  }
  if((FMA_CALVES_HEAT_ByActionTab == pActionTabAttr->CalvesHeatMode)     &&          /*表格属性里的伴随模式为 ByActionTab*/
     (FMA_CALVES_HEAT_ByActionTab == pMChair->FuncMA_Heat.Bit.Calves))               /*且 当前的模式也为 ByActionTab，即没被用户操作手控器改变*/
  {
    pMChair->CalvesHeatCtrlSw = pLedHeatCtrl->Bit.CalvesHeat;                        /*腿部加热*/
  }
  if((FMA_SEAT_HEAT_ByActionTab == pActionTabAttr->SeatHeatMode)     &&              /*表格属性里的伴随模式为 ByActionTab*/
     (FMA_SEAT_HEAT_ByActionTab == pMChair->FuncMA_Heat.Bit.Seat))                   /*且 当前的模式也为 ByActionTab，即没被用户操作手控器改变*/
  {
    pMChair->SeatHeatCtrlSw = pLedHeatCtrl->Bit.SeatHeat;                            /*座部加热*/
  }
  if((FMA_LUMBARBACK_HEAT_ByActionTab == pActionTabAttr->LumbarBackHeatMode)     &&  /*表格属性里的伴随模式为 ByActionTab*/
     (FMA_LUMBARBACK_HEAT_ByActionTab == pMChair->FuncMA_Heat.Bit.LumbarBack))       /*且 当前的模式也为 ByActionTab，即没被用户操作手控器改变*/
  {
    pMChair->LumbarBackHeatCtrlSw = pLedHeatCtrl->Bit.LumbarBackHeat;                /*腰背加热*/
  }

  /*伴随执行 之 滚轮 振动-------------------------------------------------------------*/
  if((FMA_FEET_ROLLER_ByActionTab == pActionTabAttr->FeetRollerMode)       &&        /*表格属性里的伴随模式为 ByActionTab*/
     (FMA_FEET_ROLLER_ByActionTab == pMChair->FuncMA_Roller.Bit.Feet))               /*且 当前的模式也为 ByActionTab，即没被用户操作手控器改变*/
  {
    pMChair->FeetRollerCtrlSw = pRollerVibCtrl->Bit.FeetRoller;                      /*脚滚*/
  }
  if((FMA_CALVES_ROLLER_ByActionTab == pActionTabAttr->CalvesRollerMode)       &&    /*表格属性里的伴随模式为 ByActionTab*/
     (FMA_CALVES_ROLLER_ByActionTab == pMChair->FuncMA_Roller.Bit.Calves))           /*且 当前的模式也为 ByActionTab，即没被用户操作手控器改变*/
  {
    pMChair->CalvesRollerCtrlSw = pRollerVibCtrl->Bit.CalvesRoller;                  /*腿滚*/
  }
  
  if((FMA_FEET_VIB_ByActionTab == pActionTabAttr->FeetVibMode)    &&                 /*表格属性里的伴随模式为 ByActionTab*/
     (FMA_FEET_VIB_ByActionTab == pMChair->FuncMA_Vib.Bit.Feet))                     /*且 当前的模式也为 ByActionTab，即没被用户操作手控器改变*/
  {
    pMChair->FeetVibCtrlSw = pRollerVibCtrl->Bit.FeetVib;                            /*脚部振动*/
  }
  if((FMA_CALVES_VIB_ByActionTab == pActionTabAttr->CalvesVibMode)    &&             /*表格属性里的伴随模式为 ByActionTab*/
     (FMA_CALVES_VIB_ByActionTab == pMChair->FuncMA_Vib.Bit.Calves))                 /*且 当前的模式也为 ByActionTab，即没被用户操作手控器改变*/
  {
    pMChair->CalvesVibCtrlSw = pRollerVibCtrl->Bit.CalvesVib;                        /*腿部振动*/
  }
  if((FMA_SEAT_VIB_ByActionTab == pActionTabAttr->SeatVibMode)    &&                 /*表格属性里的伴随模式为 ByActionTab*/
     (FMA_SEAT_VIB_ByActionTab == pMChair->FuncMA_Vib.Bit.Seat))                     /*且 当前的模式也为 ByActionTab，即没被用户操作手控器改变*/
  {
    pMChair->SeatVibCtrlSw = pRollerVibCtrl->Bit.SeatVib;                            /*坐部振动*/
  }
  if((FMA_LUMBARBACK_VIB_ByActionTab == pActionTabAttr->LumbarBackVibMode)    &&     /*表格属性里的伴随模式为 ByActionTab*/
     (FMA_LUMBARBACK_VIB_ByActionTab == pMChair->FuncMA_Vib.Bit.LumbarBack))         /*且 当前的模式也为 ByActionTab，即没被用户操作手控器改变*/
  {
    pMChair->LumbarBackVibCtrlSw = pRollerVibCtrl->Bit.LumbarBackVib;                /*腰背振动*/
  }
}

/*
************************************************************************************************************************
* 函数名称 : FuncTabStepTimeHandle                                                                                   
* 功能描述 : 动作表格的步骤时间处理                                                         
* 输入参数 : ExePeriod -- 函数执行时间
*            pStep     -- 步骤
*            TimeTab[] -- 时间表格
*            IfWithGas -- 标识动作表格是否带充气                                
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void ActionTabStep_TimeHandle(Ticker_t ExePeriod, ActionTabStep_t *pStep, __packed TabItemTime_t TimeTab[], uint8_t IfWithGas)
{
  TabItemTime_t  MaxRunTime;

  /*执行条件判断----------------------------------------------------------*/
  if((NULL == pStep)   || 
     (NULL == TimeTab) )
  {
    return;
  }

  if(pStep->Num > ACTION_TAB_STEP_NUM_MAX)
  {
    return;
  }

  /*----------------------------------------------------------------------*/
  if(TRUE == IfWithGas)                                                  /*带有充气，则时间依据充气强度*/
  {
    pMChair->GasIntensity = (pMChair->GasIntensity<1) ? 1:pMChair->GasIntensity;
    pMChair->GasIntensity = (pMChair->GasIntensity>5) ? 5:pMChair->GasIntensity;
    MaxRunTime = TimeTab[pMChair->GasIntensity - 1];
  }
  else                                                                   /*没充气，则只有一个时间项*/
  {
    MaxRunTime = TimeTab[0];
  }

  pStep->RunTimeMs += ExePeriod;
  if(pStep->RunTimeMs >= 100)
  {
    pStep->RunTimeMs = 0;
    pStep->RunTimeMs100++;
    pStep->TabRunTimeMs100++;
  }

  /*★机芯XYZ动作重复次数判断  的 优先级 大于 时间★*/ 
  if((FALSE == pStep->IncJudgeCondition.Bit.CoreXYZActionRepeat) &&      /*机芯XYZ动作重复次数  不作为步骤增加的判断条件*/  
     (MaxRunTime != TIGNORE)                                     )       /*时间不忽略*/  
  {
    pStep->IncJudgeCondition.Bit.TimeOut = TRUE;                         /*超时  作为步骤增加的判断条件*/  
    if(pStep->RunTimeMs100 > MaxRunTime)
    {
      pStep->IncConditionState.Bit.TimeOut = TRUE;                       /*步骤增加条件状态：超时 */
    }
  }
}

/*
************************************************************************************************************************
* 函数名称 : ActionTabStep_IterateHandle                                                                                   
* 功能描述 : 动作表格步骤迭代处理                                                   
* 输入参数 : pActionTabAttr -- 表格属性  
*            pStep          -- 步骤对象                          
* 返回参数 : FALSE -- 步骤没变
*            TRUE  -- 步骤发生迭代改变
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t ActionTabStep_IterateHandle(ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  if((NULL == pActionTabAttr) || 
     (NULL == pStep)          )
  {
    return FALSE;
  }

  pStep->AdditonOp.Bit.OccurIterate = FALSE;                                /*先默认步骤不允许迭代*/

  /*★★注：与旧架构不同，步骤增加条件优先级：        ★★
    ★★    机芯动作次数 > 时间 > 推杆位置 > 小腿伸缩 ★★*/
  if((TRUE == pStep->IncJudgeCondition.Bit.CoreXYZActionRepeat) &&          /*机芯XYZ动作次数*/
     (TRUE == pStep->IncConditionState.Bit.CoreXYZActionRepeat) )
  {
    pStep->AdditonOp.Bit.OccurIterate = TRUE;
  }
  else if((TRUE == pStep->IncJudgeCondition.Bit.TimeOut) &&                 /*超时*/
          (TRUE == pStep->IncConditionState.Bit.TimeOut) )
  {
    pStep->AdditonOp.Bit.OccurIterate = TRUE;
  }
  else if((TRUE == pStep->IncJudgeCondition.Bit.SpikeAngleOk) &&            /*推杆*/
          (TRUE == pStep->IncConditionState.Bit.SpikeAngleOk) )
  {
    pStep->AdditonOp.Bit.OccurIterate = TRUE;
  }
//  else if((TRUE == pStep->IncJudgeCondition.Bit.LegFlexOk) &&              /*小腿伸缩 */
//          (TRUE == pStep->IncConditionState.Bit.LegFlexOk) )
//  {
//    pStep->AdditonOp.Bit.OccurIterate = TRUE;
//  }
  else if(TRUE == pStep->IncJudgeCondition.Bit.LegFlexOk) 
  {
    if(TRUE == pStep->IncJudgeCondition.Bit.ULegFlexOk)                    
    {
      if((TRUE == pStep->IncConditionState.Bit.ULegFlexOk) &&               /*上下小腿伸缩都要判断*/
         (TRUE == pStep->IncConditionState.Bit.LegFlexOk)  )
      {
        pStep->AdditonOp.Bit.OccurIterate = TRUE;
      }
    }
    else                                                                    
    {
      if(TRUE == pStep->IncConditionState.Bit.LegFlexOk)                    /*只需要判断下小腿伸缩*/
      {
        pStep->AdditonOp.Bit.OccurIterate = TRUE;
      }
    }
  }
  else if(TRUE == pStep->IncJudgeCondition.Bit.ULegFlexOk)                  /*只需判断上小腿伸缩*/
  {
    if(TRUE == pStep->IncConditionState.Bit.ULegFlexOk)
    {
      pStep->AdditonOp.Bit.OccurIterate = TRUE;
    }
  }
  else if((STEP_HOP_NEXT == pStep->AdditonOp.Bit.StepHop) ||                /*发生跳步*/
          (STEP_HOP_LAST == pStep->AdditonOp.Bit.StepHop) )
  {
    pStep->AdditonOp.Bit.OccurIterate = TRUE;
  }
  else if(pStep->Num > ACTION_TAB_STEP_NUM_MAX)
  {
    pStep->AdditonOp.Bit.OccurIterate = TRUE;
  }

  /*步骤迭代操作--------------------------------------------------*/
  if(TRUE == pStep->AdditonOp.Bit.OccurIterate)
  {
    //if(TRUE == pStep->IncJudgeCondition.Bit.CoreXYZActionRepeat)            /*有机芯XYZ动作*/
    if(TRUE == pStep->AdditonOp.Bit.IsWithCore)            /*带【机芯】*/
    {
      Core_ResetXYZActionStep();                                            /*步骤迭代时复位机芯XYZ联动手法步骤*/
    }
    
    if(STEP_HOP_LAST == pStep->AdditonOp.Bit.StepHop)                       /*跳往上一步，则向后迭代*/
    {
      if(pStep->Num > pActionTabAttr->StartStepNum)
      {
        pStep->Num--;
      }
      else
      {
        pStep->Num = pActionTabAttr->EndStepNum;
      }
    }
    else                                                                    /*向前迭代*/
    {
      if(pStep->Num < pActionTabAttr->EndStepNum)
      {
        pStep->Num++;
      }
      else
      {
        pStep->Num = pActionTabAttr->StartStepNum;                          /*从表格的开始步骤数开始执行*/
        pStep->TabRepeat++;                                                 /*执行完一次表格*/
      }
    }
    pStep->AdditonOp.Bit.StepHop = STEP_HOP_NONE;                           /*迭代时，清除跳步标识 */
    pStep->Repeat = 0;
    pStep->RunTimeMs100 = 0;
  }
  
  return pStep->AdditonOp.Bit.OccurIterate;
}

/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
/*
************************************************************************************************************************
* 宏定义   : MChair_TabHandle_PreProcess                                                                                   
* 补充说明 : 表格执行前的的预处理。                                                                                                         
************************************************************************************************************************
*/
#define MChair_TabHandle_PreProcess()                                                                                  \
{                                                                                                                      \
  if((NULL == pActionTabAttr) ||                                                                                       \
     (NULL == pStep)          )                                                                                        \
  {                                                                                                                    \
    return;                                                                                                            \
  }                                                                                                                    \
  ActionTabStep_IterateHandle(pActionTabAttr, pStep);  /*执行前，先步骤迭代*/                                          \
  if(TRUE == pStep->AdditonOp.Bit.SingleExe)                                                                           \
  {                                                                                                                    \
    if(pStep->TabRepeat > 0)                           /*单次执行的，则表格执行完一遍后，不再执行*/                    \
    {                                                                                                                  \
      return;                                                                                                          \
    }                                                                                                                  \
  }                                                                                                                    \
  pStep->IncConditionState.All = 0;                    /*执行前，将步骤增加条件的状态清零，相关函数内会根据情况置位*/  \
  pStep->IncJudgeCondition.All = 0;                    /*执行前，将步骤增加判断条件清零，相关函数内会据情况置置位*/    \
}

/*
************************************************************************************************************************
* 函数名称 : MChair_TabHandle_CoreAuto                                                                                   
* 功能描述 : 动作表格处理 之 【机芯】自动                                              
* 输入参数 : ExePeriod      -- 函数执行周期
*            pActionTabAttr -- 表格属性
*            pStep          -- 步骤对象                  
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_CoreAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  CoreMixOtherTabItem_t  *pCoreMixOtherTab;                                         /*动作表格*/
  CoreAutoTabItem_t      *pActionTab;                                               /*动作表格*/ 
  CoreAutoTabItem_t      *pExeStepData;                                             /*要执行的步骤数据*/ 

  pStep->AdditonOp.Bit.IsWithCore = TRUE;                                           /*带【机芯】*/
  MChair_TabTry_UpdateStepHopState(TAB_TRY_TYPE_CORE, pStep);                       /*表格体验 之 更新步骤的跳步状态。体验没开启时，是不会更新的*/
  MChair_TabHandle_PreProcess();                                                    /*表格执行前的的预处理*/
  pActionTab = pActionTabAttr->pActionTab;                                          /*先默认从表格属性里取出动作表格*/
  pExeStepData = &pActionTab[pStep->Num];                                           /*先从默认的表格里取出要执行的步骤数据*/
  if(TRUE == pStep->AdditonOp.Bit.IsCoreMixOther)                                   /*是【机芯】混合【其他】表格*/
  {
    pCoreMixOtherTab = pActionTabAttr->pActionTab;                                  /*从表格属性里取出动作表格*/
    pExeStepData = &pCoreMixOtherTab[pStep->Num].CoreAutoTabItem;                   /*从表格里取出要执行的步骤数据*/
  }
  if(FA_TAB_TRY == pActionTabAttr->FuncID)                                          /*如果表格体验开启，则再去取要体验的步骤数据*/
  {
    pExeStepData = MChair_TabTry_GetExeStepData(TAB_TRY_TYPE_CORE, pStep);          /*取出要体验的步骤数据*/
  }
  ActionObjHandle_CoreAuto(&pExeStepData->CoreAutoAction, pStep, pExeStepData->Repeat); 
  ActionObjHandle_AccompanyFunc(pActionTabAttr, pStep, &pExeStepData->LedHeatBit, &pExeStepData->RollerVibBit);
  ActionTabStep_TimeHandle(ExePeriod, pStep, &pExeStepData->Time1, FALSE);    
}

/*
************************************************************************************************************************
* 函数名称 : MChair_TabHandle_GasAuto                                                                                   
* 功能描述 : 动作表格处理 之 【充气】自动                                           
* 输入参数 : ExePeriod      -- 函数执行周期
*            pActionTabAttr -- 表格属性
*            pStep          -- 步骤对象                  
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_GasAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  GasAutoTabItem_t  *pActionTab;                                                    /*动作表格*/ 
  GasAutoTabItem_t  *pExeStepData;                                                  /*要执行的步骤数据*/ 

  MChair_TabTry_UpdateStepHopState(TAB_TRY_TYPE_GAS, pStep);                        /*表格体验 之 更新步骤的跳步状态。体验没开启时，是不会更新的*/
  MChair_TabHandle_PreProcess();                                                    /*表格执行前的的预处理*/
  pActionTab = pActionTabAttr->pActionTab;                                          /*先默认从表格属性里取出动作表格*/
  pExeStepData = &pActionTab[pStep->Num];                                           /*先从默认的表格里取出要执行的步骤数据*/
  if(FA_TAB_TRY == pActionTabAttr->FuncID)                                          /*如果表格体验开启，则再去取要体验的步骤数据*/
  {
    pExeStepData = MChair_TabTry_GetExeStepData(TAB_TRY_TYPE_GAS, pStep);           /*取出要体验的步骤数据*/
  }
  ActionObjHandle_Gas(&pExeStepData->GasAutoAction, pStep, &pExeStepData->Time1); 
  ActionObjHandle_AccompanyFunc(pActionTabAttr, pStep, &pExeStepData->LedHeatBit, &pExeStepData->RollerVibBit);
  ActionTabStep_TimeHandle(ExePeriod, pStep, &pExeStepData->Time1, TRUE);    
}

/*
************************************************************************************************************************
* 函数名称 : MChair_TabHandle_SpikeAuto                                                                                   
* 功能描述 : 动作表格处理 之 【推杆】自动                                         
* 输入参数 : ExePeriod      -- 函数执行周期
*            pActionTabAttr -- 表格属性
*            pStep          -- 步骤对象                  
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_SpikeAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  SpikeAutoTabItem_t  *pActionTab;                                                  /*动作表格*/ 
  SpikeAutoTabItem_t  *pExeStepData;                                                /*要执行的步骤数据*/ 

  MChair_TabTry_UpdateStepHopState(TAB_TRY_TYPE_SPIKE, pStep);                      /*表格体验 之 更新步骤的跳步状态。体验没开启时，是不会更新的*/
  MChair_TabHandle_PreProcess();                                                    /*表格执行前的的预处理*/
  pActionTab = pActionTabAttr->pActionTab;                                          /*先默认从表格属性里取出动作表格*/
  pExeStepData = &pActionTab[pStep->Num];                                           /*先从默认的表格里取出要执行的步骤数据*/
  if(FA_TAB_TRY == pActionTabAttr->FuncID)                                          /*如果表格体验开启，则再去取要体验的步骤数据*/
  {
    pExeStepData = MChair_TabTry_GetExeStepData(TAB_TRY_TYPE_SPIKE, pStep);         /*取出要体验的步骤数据*/
  }
  ActionObjHandle_SpikeAuto(&pExeStepData->SpikeAutoAction, pStep); 
  ActionTabStep_TimeHandle(ExePeriod, pStep, &pExeStepData->Time1, FALSE);    
}

/*
************************************************************************************************************************
* 函数名称 : MChair_TabHandle_CoreGasAuto                                                                                   
* 功能描述 : 动作表格处理 之 【机芯+充气】自动                          
* 输入参数 : ExePeriod      -- 函数执行周期
*            pActionTabAttr -- 表格属性
*            pStep          -- 步骤对象                  
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_CoreGasAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  CoreGasAutoTabItem_t  *pActionTab;                                                /*动作表格*/ 
  CoreGasAutoTabItem_t  *pExeStepData;                                              /*要执行的步骤数据*/ 

  pStep->AdditonOp.Bit.IsWithCore = TRUE;                                           /*带【机芯】*/
  MChair_TabTry_UpdateStepHopState(TAB_TRY_TYPE_COREGAS, pStep);                    /*表格体验 之 更新步骤的跳步状态。体验没开启时，是不会更新的*/
  MChair_TabHandle_PreProcess();                                                    /*表格执行前的的预处理*/
  pActionTab = pActionTabAttr->pActionTab;                                          /*先默认从表格属性里取出动作表格*/
  pExeStepData = &pActionTab[pStep->Num];                                           /*先从默认的表格里取出要执行的步骤数据*/
  if(FA_TAB_TRY == pActionTabAttr->FuncID)                                          /*如果表格体验开启，则再去取要体验的步骤数据*/
  {
    pExeStepData = MChair_TabTry_GetExeStepData(TAB_TRY_TYPE_COREGAS, pStep);       /*取出要体验的步骤数据*/
  }
  ActionObjHandle_CoreAuto(&pExeStepData->CoreAutoAction, pStep, pExeStepData->Repeat); 
  ActionObjHandle_Gas(&pExeStepData->GasAutoAction, pStep, &pExeStepData->Time1); 
  ActionObjHandle_AccompanyFunc(pActionTabAttr, pStep, &pExeStepData->LedHeatBit, &pExeStepData->RollerVibBit);
  ActionTabStep_TimeHandle(ExePeriod, pStep, &pExeStepData->Time1, TRUE);    
}

/*
************************************************************************************************************************
* 函数名称 : MChair_TabHandle_CoreSpikeAuto                                                                                   
* 功能描述 : 动作表格处理 之 【机芯+推杆】自动                                    
* 输入参数 : ExePeriod      -- 函数执行周期
*            pActionTabAttr -- 表格属性
*            pStep          -- 步骤对象                  
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_CoreSpikeAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  CoreSpikeAutoTabItem_t  *pActionTab;                                              /*动作表格*/ 
  CoreSpikeAutoTabItem_t  *pExeStepData;                                            /*要执行的步骤数据*/ 

  pStep->AdditonOp.Bit.IsWithCore = TRUE;                                           /*带【机芯】*/
  MChair_TabTry_UpdateStepHopState(TAB_TRY_TYPE_CORESPIKE, pStep);                  /*表格体验 之 更新步骤的跳步状态。体验没开启时，是不会更新的*/
  MChair_TabHandle_PreProcess();                                                    /*表格执行前的的预处理*/
  pActionTab = pActionTabAttr->pActionTab;                                          /*先默认从表格属性里取出动作表格*/
  pExeStepData = &pActionTab[pStep->Num];                                           /*先从默认的表格里取出要执行的步骤数据*/
  if(FA_TAB_TRY == pActionTabAttr->FuncID)                                          /*如果表格体验开启，则再去取要体验的步骤数据*/
  {
    pExeStepData = MChair_TabTry_GetExeStepData(TAB_TRY_TYPE_CORESPIKE, pStep);     /*取出要体验的步骤数据*/
  }
  ActionObjHandle_CoreAuto(&pExeStepData->CoreAutoAction, pStep, pExeStepData->Repeat); 
  ActionObjHandle_SpikeAuto(&pExeStepData->SpikeAutoAction, pStep); 
  ActionObjHandle_AccompanyFunc(pActionTabAttr, pStep, &pExeStepData->LedHeatBit, &pExeStepData->RollerVibBit);
  ActionTabStep_TimeHandle(ExePeriod, pStep, &pExeStepData->Time1, FALSE);    
}

/*
************************************************************************************************************************
* 函数名称 : MChair_TabHandle_GasSpikeAuto                                                                                   
* 功能描述 : 动作表格处理 之 【充气+推杆】自动                                         
* 输入参数 : ExePeriod      -- 函数执行周期
*            pActionTabAttr -- 表格属性
*            pStep          -- 步骤对象                  
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_GasSpikeAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  GasSpikeAutoTabItem_t  *pActionTab;                                               /*动作表格*/ 
  GasSpikeAutoTabItem_t  *pExeStepData;                                             /*要执行的步骤数据*/ 

  MChair_TabTry_UpdateStepHopState(TAB_TRY_TYPE_GASSPIKE, pStep);                   /*表格体验 之 更新步骤的跳步状态。体验没开启时，是不会更新的*/
  MChair_TabHandle_PreProcess();                                                    /*表格执行前的的预处理*/
  pActionTab = pActionTabAttr->pActionTab;                                          /*先默认从表格属性里取出动作表格*/
  pExeStepData = &pActionTab[pStep->Num];                                           /*先从默认的表格里取出要执行的步骤数据*/
  if(FA_TAB_TRY == pActionTabAttr->FuncID)                                          /*如果表格体验开启，则再去取要体验的步骤数据*/
  {
    pExeStepData = MChair_TabTry_GetExeStepData(TAB_TRY_TYPE_GASSPIKE, pStep);      /*取出要体验的步骤数据*/
  }
  ActionObjHandle_Gas(&pExeStepData->GasAutoAction, pStep, &pExeStepData->Time1); 
  ActionObjHandle_SpikeAuto(&pExeStepData->SpikeAutoAction, pStep); 
  ActionObjHandle_AccompanyFunc(pActionTabAttr, pStep, &pExeStepData->LedHeatBit, &pExeStepData->RollerVibBit);
  ActionTabStep_TimeHandle(ExePeriod, pStep, &pExeStepData->Time1, TRUE);    
}

/*
************************************************************************************************************************
* 函数名称 : MChair_TabHandle_CoreGasSpikeAuto                                                                                   
* 功能描述 : 动作表格处理 之 【机芯+充气+推杆】自动                          
* 输入参数 : ExePeriod      -- 函数执行周期
*            pActionTabAttr -- 表格属性
*            pStep          -- 步骤对象                  
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_CoreGasSpikeAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  CoreGasSpikeAutoTabItem_t  *pActionTab;                                           /*动作表格*/ 
  CoreGasSpikeAutoTabItem_t  *pExeStepData;                                         /*要执行的步骤数据*/ 

  pStep->AdditonOp.Bit.IsWithCore = TRUE;                                           /*带【机芯】*/
  MChair_TabTry_UpdateStepHopState(TAB_TRY_TYPE_COREGASSPIKE, pStep);               /*表格体验 之 更新步骤的跳步状态。体验没开启时，是不会更新的*/
  MChair_TabHandle_PreProcess();                                                    /*表格执行前的的预处理*/
  pActionTab = pActionTabAttr->pActionTab;                                          /*先默认从表格属性里取出动作表格*/
  pExeStepData = &pActionTab[pStep->Num];                                           /*先从默认的表格里取出要执行的步骤数据*/
  if(FA_TAB_TRY == pActionTabAttr->FuncID)                                          /*如果表格体验开启，则再去取要体验的步骤数据*/
  {
    pExeStepData = MChair_TabTry_GetExeStepData(TAB_TRY_TYPE_COREGASSPIKE, pStep);  /*取出要体验的步骤数据*/
  }
  ActionObjHandle_CoreAuto(&pExeStepData->CoreAutoAction, pStep, pExeStepData->Repeat); 
  ActionObjHandle_Gas(&pExeStepData->GasAutoAction, pStep, &pExeStepData->Time1); 
  ActionObjHandle_SpikeAuto(&pExeStepData->SpikeAutoAction, pStep); 
  ActionObjHandle_AccompanyFunc(pActionTabAttr, pStep, &pExeStepData->LedHeatBit, &pExeStepData->RollerVibBit);
  ActionTabStep_TimeHandle(ExePeriod, pStep, &pExeStepData->Time1, TRUE);    
}


/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
/*========================================================================================================================
*【机芯表格】混合【其他表格】                  【机芯表格】混合【其他表格】                  【机芯表格】混合【其他表格】
* 模仿松下按摩椅可在机芯步骤迭代中随意切换伴随的充气程序。         模仿松下按摩椅可在机芯步骤迭代中随意切换伴随的充气程序。
* 模仿松下按摩椅可在机芯步骤迭代中随意切换伴随的充气程序。         模仿松下按摩椅可在机芯步骤迭代中随意切换伴随的充气程序。
========================================================================================================================*/

static const MixOtherActionTabAttr_t  MixOtherTabAttr[] = 
{
  /*      混合的表格                         功能部件属性      充气部位属性        推杆控制属性
                                               机 充 推    头 肩 手 腰 坐 腿 脚    靠 零 小  腿  上腿
                                               芯 气 杆    部 部 部 部 部 部 部    背 重 腿 伸缩 伸缩 */  
  {(void*)NULL,                               {0, 0, 0},  {0, 0, 0, 0, 0, 0, 0},  {0, 0, 0, 0,   0}},
  /*---------------------------------------------------------------------------------------------*/
  {(void*)GasTab_Shoulder,                    {0, 1, 0},  {0, 1, 0, 0, 0, 0, 0},  {0, 0, 0, 0,   0}},
  {(void*)GasTab_Arms,                        {0, 1, 0},  {0, 0, 1, 0, 0, 0, 0},  {0, 0, 0, 0,   0}},
  {(void*)GasTab_LumbarSeat,                  {0, 1, 0},  {0, 0, 0, 1, 1, 0, 0},  {0, 0, 0, 0,   0}},
  {(void*)GasTab_Calves,                      {0, 1, 0},  {0, 0, 0, 0, 0, 1, 1},  {0, 0, 0, 0,   0}},
  {(void*)GasTab_FullGas,                     {0, 1, 0},  {1, 1, 1, 1, 1, 1, 1},  {0, 0, 0, 0,   0}},
  {(void*)GasTab_RelaxGas,                    {0, 1, 0},  {1, 1, 1, 1, 1, 1, 1},  {0, 0, 0, 0,   0}},
  {(void*)GasTab_QuickGas,                    {0, 1, 0},  {1, 1, 1, 1, 1, 1, 1},  {0, 0, 0, 0,   0}},

  {(void*)SpikeAutoTab_ZeroGravity1,          {0, 0, 1},  {0, 0, 0, 0, 0, 0, 0},  {1, 1, 1, 1,   0}},
  {(void*)SpikeAutoTab_ZeroGravity2,          {0, 0, 1},  {0, 0, 0, 0, 0, 0, 0},  {1, 1, 1, 1,   0}},
  {(void*)SpikeAutoTab_Rocking,               {0, 0, 1},  {0, 0, 0, 0, 0, 0, 0},  {1, 1, 1, 1,   0}},

  {(void*)CoreGasSpikeAutoTab_Shoulder,       {1, 1, 1},  {0, 1, 0, 0, 0, 0, 0},  {1, 1, 1, 1,   0}},
  {(void*)CoreGasSpikeAutoTab_ShoulderTCS,    {1, 1, 1},  {0, 1, 0, 0, 0, 0, 0},  {1, 1, 1, 1,   0}},
  {(void*)CoreGasSpikeAutoTab_Lumbar,         {1, 1, 1},  {0, 1, 1, 1, 1, 1, 1},  {1, 1, 1, 1,   0}},
  {(void*)CoreGasSpikeAutoTab_BackFeet,       {1, 1, 1},  {0, 1, 1, 1, 1, 1, 1},  {1, 1, 1, 1,   0}},
  {(void*)CoreGasSpikeAutoTab_FeetUpDown,     {1, 1, 1},  {0, 1, 1, 1, 1, 1, 1},  {1, 1, 1, 1,   0}},

  /*---------------------------------------------------------------------------------------------*/
  {(void*)NULL,                               {0, 0, 0},  {0, 0, 0, 0, 0, 0, 0},  {0, 0, 0, 0,   0}}
};
#define  MIX_OTHER_ACTION_TAB_NUM  TAB_NUM(MixOtherTabAttr)

static  ActionTabStep_t  OtherTabStep;         /*【其他】表格的步骤*/
static  void             *pOtherAutoTab;       /* 指向【其他】表格*/
static  uint8_t          OtherTabIndex;        /*【其他】表格在MixOtherActionTab[]中的索引*/
static  ActionTabAttr_t  OtherAutoTabDynAttr;  /*【其他】表格的动态属性*/

/*
************************************************************************************************************************
* 函数名称 : MChair_TabHandle_ResetMixOtherTabStep                                                                            
* 功能描述 : 动作表格处理  之 复位混合其他表格 的步骤                  
* 输入参数 : SpikeStop 是否停止推杆  TRUE--停止   FALSE--不停止                 
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_ResetMixOtherTabStep(uint8_t SpikeStop)
{
  pOtherAutoTab = NULL;
  memset(&OtherTabStep, 0, sizeof(ActionTabStep_t));            /*复位【其他】表格步骤*/

  if(MixOtherTabAttr[OtherTabIndex].ComponentAttr.Bit.Gas)      /*混合的表格带充气*/
  {
    if((FUNC_TYPE_NONE == MChair.FuncAuto_Gas)        &&
       (FUNC_TYPE_NONE == MChair.FuncMannual_Gas.All) )
    {
      Gas_SetPumpSw(OFF);                                       /*无充气功能开启，则关气泵*/
    }
    Gas_AllCtrlEn();                                            /*所有部位充气控制使能*/ 
    Gas_SetGasPart(0, 0);
  }
 
  if(MixOtherTabAttr[OtherTabIndex].ComponentAttr.Bit.Spike)    /*混合的表格带推杆*/
  {
    if(SpikeStop)
    {
      Spike_SetLegFlexAngle(PKEEP);                             /*停止伸缩推杆*/
      Spike_SetULegFlexAngle(PKEEP);                            /*停止伸缩推杆*/
      Spike_SetAngle(PKEEP, PKEEP, PKEEP);                      /*停止推杆*/
    }
  }

  OtherTabIndex = 0;
}

/*
************************************************************************************************************************
* 函数名称 : MChair_TabHandle_UpdateMixOtherTabAttr                                                                            
* 功能描述 : 动作表格处理  之 更新混合其他表格 的属性  
* 输入参数 : 无                 
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_UpdateMixOtherTabAttr(void)
{
  /*部件属性----------------------------------------------------------------------------*/
  pMChair->ComponentFuncState.Bit.Core  = (MixOtherTabAttr[OtherTabIndex].ComponentAttr.Bit.Core)  ? (FUNC_TYPE_AUTO) : (pMChair->ComponentFuncState.Bit.Core);
  pMChair->ComponentFuncState.Bit.Gas   = (MixOtherTabAttr[OtherTabIndex].ComponentAttr.Bit.Gas)   ? (FUNC_TYPE_AUTO) : (pMChair->ComponentFuncState.Bit.Gas);
  pMChair->ComponentFuncState.Bit.Spike = (MixOtherTabAttr[OtherTabIndex].ComponentAttr.Bit.Spike) ? (FUNC_TYPE_AUTO) : (pMChair->ComponentFuncState.Bit.Spike);
  if((TRUE == MixOtherTabAttr[OtherTabIndex].ComponentAttr.Bit.Gas)   &&
     (TRUE == MixOtherTabAttr[OtherTabIndex].ComponentAttr.Bit.Spike) )
  {
    pMChair->CSFlag.Bit.GasCooperateSpikeRun = TRUE;        /*有充气配合推杆的动作*/
  }
  
  /*推杆属性----------------------------------------------------------------------------*/
  pMChair->CSFlag.Bit.BackSpikeMannualMoveDisable = MixOtherTabAttr[OtherTabIndex].SpikeAttr.Bit.BackMannualDis; 
  pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable = MixOtherTabAttr[OtherTabIndex].SpikeAttr.Bit.ZeroMannualDis; 
  pMChair->CSFlag.Bit.FeetSpikeMannualMoveDisable = MixOtherTabAttr[OtherTabIndex].SpikeAttr.Bit.FeetMannualDis; 
  pMChair->CSFlag.Bit.LegFlexMannualMoveDisable   = MixOtherTabAttr[OtherTabIndex].SpikeAttr.Bit.LegFlexMannualDis; 
  pMChair->CSFlag.Bit.ULegFlexMannualMoveDisable  = MixOtherTabAttr[OtherTabIndex].SpikeAttr.Bit.ULegFlexMannualDis; 

  /*充气属性----------------------------------------------------------------------------*/
  (MixOtherTabAttr[OtherTabIndex].GasAttr.Bit.Head)     ? (Gas_HeadCtrlEnAdd())     : ((void)0);
  (MixOtherTabAttr[OtherTabIndex].GasAttr.Bit.Shoulder) ? (Gas_ShoulderCtrlEnAdd()) : ((void)0);
  (MixOtherTabAttr[OtherTabIndex].GasAttr.Bit.Arms)     ? (Gas_ArmsCtrlEnAdd())     : ((void)0);
  (MixOtherTabAttr[OtherTabIndex].GasAttr.Bit.Lumbar)   ? (Gas_LumbarCtrlEnAdd())   : ((void)0);
  (MixOtherTabAttr[OtherTabIndex].GasAttr.Bit.Seat)     ? (Gas_SeatCtrlEnAdd())     : ((void)0);
  (MixOtherTabAttr[OtherTabIndex].GasAttr.Bit.Calves)   ? (Gas_CalvesCtrlEnAdd())   : ((void)0);
  (MixOtherTabAttr[OtherTabIndex].GasAttr.Bit.Feet)     ? (Gas_FeetCtrlEnAdd())     : ((void)0);
}

/*
************************************************************************************************************************
* 函数名称 : MChair_TabHandle_CoreMixOtherAuto                                                                          
* 功能描述 : 动作表格处理 之 【机芯 混合 其他表格】自动                  
* 输入参数 : ExePeriod      -- 函数执行周期
*            pActionTabAttr -- 表格属性
*            pStep          -- 步骤对象                  
* 返回参数 : 无                                                                                                         
* 补充说明 : ★【Other】 Mix 【Other】的方式可灵活组合各种形式的动作表格。         ★
             ★【Other】表格的Mix方式有两种：插入 和 伴随。                        ★
*            ★                                                                    ★
*            ★ 插入方式： 当【Other】表格执行完一遍，【Core】的步骤才迭代。       ★
*            ★                                                                    ★
*            ★ 伴随方式： 以【Core】表格中的 动作次数 或 时间 作为步骤迭代的条件。★
*            ★            典型应用如机芯伴随着充气动作。                          ★
*            ★                                                                    ★
*            ★ 当【Core】表格中的 Repeat = RIGNORE   且                           ★
*            ★                    Time1 = TIGNORE                                 ★
*            ★ 这两个条件都满足时，【Other】作为插入表格。                        ★
*            ★ 其他情况下，【Other】作为伴随表格。                                ★                                   
************************************************************************************************************************
*/
void MChair_TabHandle_CoreMixOtherAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  CoreMixOtherTabItem_t  *pCoreMixOtherTab;                                  /*动作表格*/
  uint8_t  MixMode;                                                          /*混合模式*/
  uint8_t  i;

  /*【机芯】自动 处理------------------------------------------------------------------------*/
  pStep->AdditonOp.Bit.IsCoreMixOther = TRUE;                                /*是【机芯】混合【其他】表格*/
  MChair_TabHandle_CoreAuto(ExePeriod, pActionTabAttr, pStep);  
  
  /*混合的【其他】表格 处理------------------------------------------------------------------*/
  pCoreMixOtherTab = pActionTabAttr->pActionTab;
  MixMode = MIX_MODE_ACCOMPANY;                                              /*先假设  【其他表格】作为伴随表格*/
  if((RIGNORE == pCoreMixOtherTab[pStep->Num].CoreAutoTabItem.Repeat) &&
     (TIGNORE == pCoreMixOtherTab[pStep->Num].CoreAutoTabItem.Time1)  )
  {
    MixMode = MIX_MODE_INSERT;                                               /*【其他表格】作为插入表格*/
  }

  if(pOtherAutoTab != pCoreMixOtherTab[pStep->Num].pOtherTab)                /*【其他】表格发生变化*/
  {
    MChair_TabHandle_ResetMixOtherTabStep(FALSE);                            /*复位混合其他表格 的步骤 */
    pOtherAutoTab = pCoreMixOtherTab[pStep->Num].pOtherTab;
    for(i=0; i<MIX_OTHER_ACTION_TAB_NUM; i++)                                /*确定变化后的表格在FuncActionTab中的索引*/ 
    {
      if(pOtherAutoTab == MixOtherTabAttr[i].pTab)
      {
        OtherTabIndex = i;
        break;
      }
    }
  }

  if((NULL == pOtherAutoTab) ||                                              /*【其他】表格无效*/
     (0    == OtherTabIndex) )                                               /*表格索引无效*/
  {
    if(MIX_MODE_INSERT == MixMode) 
    {
      pStep->Num++;                                                          /*插入的表格无效，则强制迭代【机芯】步骤*/
    }
    pOtherAutoTab = NULL;
    OtherTabIndex = 0;
    return;                                                                  /*【其他】表格无效，则不执行*/
  }

  if(MIX_MODE_INSERT == MixMode) 
  {
    OtherTabStep.AdditonOp.Bit.SingleExe = TRUE;                             /*插入的表格，单次执行*/
    if(OtherTabStep.TabRepeat > 0)
    {
      pStep->Num++;                                                          /*插入的表格执行完一遍，则强制迭代【机芯】步骤*/
      pOtherAutoTab = NULL;
      OtherTabIndex = 0;
      return;                                                                /*不再执行此插入表格，进行下一步骤的执行*/
    }
  }
  
  MChair_TabHandle_UpdateMixOtherTabAttr();                                  /*更新相关的属性*/
  memcpy(&OtherAutoTabDynAttr, pActionTabAttr, sizeof(ActionTabAttr_t));     /*主要的表格属性跟【机芯】一样*/
  OtherAutoTabDynAttr.pActionTab   = pOtherAutoTab;                          /*动作表格*/
  OtherAutoTabDynAttr.StartStepNum = 0;                                      /*开始步骤*/
  OtherAutoTabDynAttr.EndStepNum   = ACTION_TAB_STEP_NUM_MAX;                /*结束步骤*/
  switch(MixOtherTabAttr[OtherTabIndex].ComponentAttr.All & B(00000111))     /*属性：b0--机芯  b1--充气  b2--推杆 */
  { 
    case B(001): MChair_TabHandle_CoreAuto(ExePeriod,         &OtherAutoTabDynAttr, &OtherTabStep);  break;  /*机芯*/
    case B(010): MChair_TabHandle_GasAuto(ExePeriod,          &OtherAutoTabDynAttr, &OtherTabStep);  break;  /*充气*/
    case B(100): MChair_TabHandle_SpikeAuto(ExePeriod,        &OtherAutoTabDynAttr, &OtherTabStep);  break;  /*推杆*/ 
    case B(011): MChair_TabHandle_CoreGasAuto(ExePeriod,      &OtherAutoTabDynAttr, &OtherTabStep);  break;  /*机芯+充气*/ 
    case B(101): MChair_TabHandle_CoreSpikeAuto(ExePeriod,    &OtherAutoTabDynAttr, &OtherTabStep);  break;  /*机芯+推杆*/ 
    case B(110): MChair_TabHandle_GasSpikeAuto(ExePeriod,     &OtherAutoTabDynAttr, &OtherTabStep);  break;  /*充气+推杆*/ 
    case B(111): MChair_TabHandle_CoreGasSpikeAuto(ExePeriod, &OtherAutoTabDynAttr, &OtherTabStep);  break;  /*机芯+充气+推杆*/ 
    default: break;
  }
}
