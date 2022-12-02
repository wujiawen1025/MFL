/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: FuncTabHandle.c 
**
**    ��������: ��Ħ���ܶ������Ĵ���
**
**    ��    ˾: �ɷ�������
**
**    ��Ŀ����: 
**
**    ƽ̨��Ϣ: 
**
**    ��    ��: Hzy
**
**    ����˵��: 
**          (1) ���ڡ���о �Զ�����ض�������ڵ� Repeat �� Time��˵��
**              �ɼܹ��еĻ�о�����ַ����������ǵ������ַ�����ȫ����ʱ�������Ʋ���ĵ�����
**              �¼ܹ����������ַ�������ַ�������ʱ�������Ʋ���ĵ�����Ӧ���Զ�����ɵĴ��������ơ�
**              ��ˣ��¼ܹ��ڶ�������м����˱���Repeat�����ƶ�����ִ�д�����  
**              Ŀǰ���¼ܹ�����о������Զ������� ֻ���� Repeat ����ֵΪRIGNORE��
**              ��CoreXYZAction ����Ϊ XYZ_ACTION_NONE ʱ������ʱ�������Ʋ���ĵ�����
**              �����Ķ�����Repeat�����������в���ĵ�������Repeat������ΪRIGNOREʱ��������ʱ����жϡ�
**
**          (2) ���ڲ�������� 
**              �¼ܹ��ԡ���о�����������������Ƹˡ���������������Ϊ�����������Ԫ�ء�
**              ������ 7 ��������ϣ� ����о�����������������Ƹˡ�������о+��������
**                                    ����о+�Ƹˡ���������+�Ƹˡ�������о+����+�Ƹˡ�
**              �����Ĺ��ܲ���(����֡���)���ٲ��붯��������ϣ�������Ϊ���ӵİ��湦�ܶ����ڡ�
**              ���ӵİ��湦�ܼȿ��Ե��������У��������ܿ�����Ҳ�ɵ����Ķ�����п��ز�����
**              �������ɿ���������ϵ�����������������еĲ�������ɼܹ�������������ϡ�
**              ����������������࣬����ж��߼���Խ��Խ���ӡ�
**
**    �޸ļ�¼:  ------------------------------------------------------------------------------------------------------
**               2016.6.16 ---------------------------------------------------------------------------
**               �� ActionTabAttr_t���������������� StartStepNum(���ʼ ������) �� EndStepNum(������ ������)��
**               ���޸���Ӧ�Ĵ��룬ʹ�ö�������ִ�в�������������  StartStepNum  �� EndStepNum֮�䡣               
**
**               2016.6.20 ---------------------------------------------------------------------------
**               �޸� MChair_TabHandle_CoreMixOtherAuto()����������ز����߼���
**                 
**               ԭ��  ��Other������в��롾Other�������ж��߼��ǣ�(����ECP388������ʹ�á�)
**               ����Core������е� XYZAction = XYZ_ACTION_NONE  ��                   
**                                  Time1 = TIGNORE                                 
**               ����������������ʱ����Other����Ϊ������                      
**               ��������£���Other����Ϊ������                                
**
**               ���ڽ� ��Other������в��롾Other�������ж��߼� ��Ϊ��
**               ����Core������е� Repeat = RIGNORE   ��                           
**                                  Time1 = TIGNORE                                 
**               ����������������ʱ����Other����Ϊ������                      
**               ��������£���Other����Ϊ������   
**
**               �������ECP388�����п�����������ʱ��Ӧע���޸���ر�����ݡ�
**
**               2016.12.5 ---------------------------------------------------------------------------
**               ���ӱ��������Թ��ܡ�
**               ͨ����λ���ܹ����ٱ����Զ�������
========================================================================================================================
========================================================================================================================
*/
/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "FuncTabHandle.h"
#include "FuncLogic.h"
#include "MChair.h"
#include "FuncTab.h"
#include "CDP.h"

/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/
/*Ҫ����ı�����ͣ�b0--��о  b1--����  b2--�Ƹ� */
#define  TAB_TRY_TYPE_CORE                            B(00000001)
#define  TAB_TRY_TYPE_GAS                             B(00000010)
#define  TAB_TRY_TYPE_SPIKE                           B(00000100)
#define  TAB_TRY_TYPE_COREGAS                         B(00000011)
#define  TAB_TRY_TYPE_CORESPIKE                       B(00000101)
#define  TAB_TRY_TYPE_GASSPIKE                        B(00000110)
#define  TAB_TRY_TYPE_COREGASSPIKE                    B(00000111)

#define  TABTYPE_CHANNEL_SUM                          2           /*�������ͨ������*/
/*
========================================================================================================================
*�������������Ͷ��塿                              �������������Ͷ��塿                              �������������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� :  ��������ã�������͵����ܵĹ���                                                          
************************************************************************************************************************
*/
typedef struct
{
  uint8_t                         TapType;                           /*�������*/
  uint16_t                        *pFuncCur;                         /*��ǰ����*/
}ActionTabTry_TapTypeToFuncCur_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  ���������ز�������                                                        
************************************************************************************************************************
*/
typedef struct
{
  uint8_t                         ChannelSw;                         /*ͨ������*/
  uint8_t                         SetpHop;                           /*������ʶ*/
  
  CDP_DataFormat0x1A_To_0x1F_t    *pStepDataCur;                     /*��ǰִ�еĲ�������*/
  CDP_DataFormat0x1A_To_0x1F_t    *pStepDataNext;                    /*�������һ��Ҫִ�е�����*/
}ActionTabTry_t;

/*
========================================================================================================================
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
========================================================================================================================
*/
static const ActionTabTry_TapTypeToFuncCur_t TapTypeToFuncCurTab[] =   /*�����빦�ܹ������*/
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

ActionTabTry_t  ActionTabTry[TABTYPE_CHANNEL_SUM];                                                     /*�����������ͨ��*/
uint8_t         TabTryStepDataCur[TABTYPE_CHANNEL_SUM][sizeof(CDP_DataFormat0x1A_To_0x1F_t) + 30];     /*�������ݻ�������*/
uint8_t         TabTryStepDataNext[TABTYPE_CHANNEL_SUM][sizeof(CDP_DataFormat0x1A_To_0x1F_t) + 30];    /*�������ݻ�������*/

uint8_t MChair_TabHandle_CDPDataObjRx_0x1F(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
void* MChair_TabTry_GetStepData(uint8_t TabType, ActionTabStep_t *pStep);
void  MChair_TabTry_UpdateStepHopState(uint8_t TabType, ActionTabStep_t *pStep);

/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : MChair_TabTry_ChInit                                                                                   
* �������� : ������� ֮ ͨ����ʼ��
* ������� : ��  
* ���ز��� : ��                                                                                      
* ����˵�� : ��                                                                                                         
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
* �������� : MChair_TabTry_CDPDataObjRx_0x1A_To_0x1F                                                                                   
* �������� : ������� ֮ �������� (ͨ��0(0x1A)~ͨ��5(0x1F))��   
*            0x1F �����ԣ���λ�� <-->���İ壩�����ڸ������Ű�Ħ�������                                                                                   
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ���ĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��λ������������鹦��ʱ�����ȷ���0�������ݣ�����������յ���Ӧ�������еĲ���ţ�
*            ���͡��յ��Ĳ����+1������ŵ����ݣ��������İ��ܹ���ǰ������һ�������ݣ�
*            �����ɱ��ⲽ�����ʱ������ͨ���ӳٴ����Ķ����л��ӳ١�
************************************************************************************************************************
*/
uint8_t MChair_TabTry_CDPDataObjRx_0x1A_To_0x1F(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  uint8_t Index, j;
  uint8_t ChNum;
  CDP_DataFormat0x1A_To_0x1F_t  *pRxData0x1A1F;
  CDP_DataFormat0x1A_To_0x1F_t  *pAckData0x1A1F;

  SysMode_UserRun_Enter();               /*�������ʱ���Զ�����*/              
  pMChair->CSFlag.Bit.TabTryRun = TRUE;  /*�����������У��ػ��Ż����*/
  
  memcpy(&pAckDU[CDP_DU_OFFSET_LEN], &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  pAckData0x1A1F = (CDP_DataFormat0x1A_To_0x1F_t *)&pAckDU[CDP_DU_OFFSET_LEN];
  pRxData0x1A1F  = (CDP_DataFormat0x1A_To_0x1F_t *)&pRxDU[CDP_DU_OFFSET_LEN];
  ChNum = pRxData0x1A1F->DataID - 0x1A;
  
  do
  {
    if(ChNum >= TABTYPE_CHANNEL_SUM)
    {
      pAckData0x1A1F->Byte2.Bit.ChannelNoSupport = TRUE;                                        /*ͨ���Ų�֧��*/
      break;
    }
  
    /*����ͨ�������Ƿ�ı�-----------------------------------------------------------------------*/
    if(ActionTabTry[ChNum].ChannelSw != pRxData0x1A1F->Byte0.Bit.ChannelSw)
    {
      for(Index=0; Index<TABTYPE_TO_FUNCCUR_TAB_ISUM; Index++)
      {
        if(TapTypeToFuncCurTab[Index].TapType == pRxData0x1A1F->TabType)                        /*�������ң����Ƿ���ƥ��ı������*/
        {
          break;
        }
      }
      if(Index >= TABTYPE_TO_FUNCCUR_TAB_ISUM) 
      {
        pAckData0x1A1F->Byte2.Bit.TapTypeNoSupport = TRUE;                                      /*������Ͳ�֧��*/
        break;
      }
      
      if(ON == pRxData0x1A1F->Byte0.Bit.ChannelSw)                                              /*ͨ���򿪣���鿴�����������Դ�Ƿ��ͻ*/
      {
        for(j=0; j<TABTYPE_CHANNEL_SUM; j++)                                                    /*��������ͨ��������Դ�Ƿ��ͻ*/
        {
          if(j == ChNum)
          {
            continue;                                                                           /*����������ıȽ�*/
          }
            
          if(ON == ActionTabTry[j].ChannelSw)                                                   /*ֻ�Ƚϴ򿪵�ͨ��*/
          {
            if((ActionTabTry[j].pStepDataCur->TabType & pRxData0x1A1F->TabType) != 0)
            {
              pAckData0x1A1F->Byte2.Bit.ResourceConflict = TRUE;                                /*�����������Դ��ͻ*/
              pAckData0x1A1F->Byte2.Bit.ConflictChnanelNum = j;                                 /*��ͻ��ͨ����*/
              break;                                                                            /*��������Դ��ͻ�Ƚϵ�forѭ��*/
            }
          }
        }
        if(TRUE == pAckData0x1A1F->Byte2.Bit.ResourceConflict)
        {
          break;                                                                                /*��Դ��ͻ��������while(0)*/
        }      
      }      
      
      MChair_TabTry_ChInit(ChNum);                                                              /*ͨ�����ظı䣬�����³�ʼ��ͨ��*/
      ActionTabTry[ChNum].ChannelSw = pRxData0x1A1F->Byte0.Bit.ChannelSw;  
      memcpy(ActionTabTry[ChNum].pStepDataCur, pRxData0x1A1F, pRxData0x1A1F->DataLen);          /*ͨ�����ظı�ʱ��ֱ�Ӹ��µ�ǰҪִ�еĲ�������*/
      if(ON == pRxData0x1A1F->Byte0.Bit.ChannelSw)
      {
        *TapTypeToFuncCurTab[Index].pFuncCur = FA_TAB_TRY;                                      /*�������鹦��*/
      }
      else
      {
        *TapTypeToFuncCurTab[Index].pFuncCur = FUNC_NONE;                                       /*�رչ���*/
      }
    }
    
    /*����ͨ�����ش�ʱ�Ž��ղ�������-----------------------------------------------------------*/
    if(ON == pRxData0x1A1F->Byte0.Bit.ChannelSw)
    {
      if(pRxData0x1A1F->Byte0.Bit.StepHop != STEP_HOP_NONE)                                     /*������������������Ҫ����֮ǰ�յ��Ĳ�������*/
      {
        ActionTabTry[ChNum].SetpHop =  pRxData0x1A1F->Byte0.Bit.StepHop;
        memcpy(ActionTabTry[ChNum].pStepDataCur, pRxData0x1A1F, pRxData0x1A1F->DataLen);        /*����ǰִ�еĲ������ݸ���ΪҪ����������*/
      }
      
      memcpy(ActionTabTry[ChNum].pStepDataNext, pRxData0x1A1F, pRxData0x1A1F->DataLen);         /*�洢��һ��Ҫִ�е�����*/
      memcpy(pAckData0x1A1F, ActionTabTry[ChNum].pStepDataCur, ActionTabTry[ChNum].pStepDataCur->DataLen);  /*һ���������򷵻ص�ǰ�Ĳ������ݸ���λ��*/
    }  
  }while(0);
  
  return pAckDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* �������� : MChair_TabTry_GetExeStepData                                                                                   
* �������� : ������� ֮ ��ȡҪִ�еĲ������� 
* ������� : TabType -- �������
*            pStep   -- ����
* ���ز��� : ָ�������ݵ�ָ��                                                                                                        
* ����˵�� : ��                                                                                                         
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
    if((ON      == ActionTabTry[ChNum].ChannelSw)            &&   /*ͨ����*/
       (TabType == ActionTabTry[ChNum].pStepDataCur->TabType))    /*����ƥ��*/   
    {
      if(ActionTabTry[ChNum].SetpHop != STEP_HOP_NONE)  
      {
        /*�յ���������ʱ��MChair_TabHandle_CDPDataObjRx_0x1F()�������Ѿ����������ݸ��µ���ǰҪִ�еĲ������ݡ�
         *���ﲻ���ٸ����ˣ�����ִ�е�������������һ�����ݡ�ͨ��MChair_TabTry_UpdateStepHopState()������ȡ������ʶ��
         *ActionTabStep_IterateHandle()��������ִ�в������(����)ʱ��������ݱ����ٸ�������Ȼ��������Ž�������ʶ���㡣*/
        ActionTabTry[ChNum].SetpHop = STEP_HOP_NONE;
      }
      else if(pStep->AdditonOp.Bit.OccurIterate)  
      { 
        /*���������⣬�����Ĳ������ʱ������һ�����ݸ��µ���ǰҪִ�еĲ�������*/
        memcpy(ActionTabTry[ChNum].pStepDataCur, ActionTabTry[ChNum].pStepDataNext, ActionTabTry[ChNum].pStepDataNext->DataLen);
      }
      
      return  &ActionTabTry[ChNum].pStepDataCur->StepData[0];  
    }
  }
  
  return NULL;
}

/*
************************************************************************************************************************
* �������� : MChair_TabTry_UpdateStepHopState                                                                                   
* �������� : ������� ֮ ���²��������״̬
* ������� : TabType -- �������
*            pStep   -- ����
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
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
    if((ON      == ActionTabTry[ChNum].ChannelSw)            &&   /*ͨ����*/
       (TabType == ActionTabTry[ChNum].pStepDataCur->TabType))    /*����ƥ��*/   
    {
      pStep->AdditonOp.Bit.StepHop = ActionTabTry[ChNum].SetpHop;
      return;
    }
  }
}

/*������������������������������������������������������������������������������������������������������������������������*/
/*������������������������������������������������������������������������������������������������������������������������*/
/*
************************************************************************************************************************
* �������� : ActionObjHandle_CoreAuto                                                                                   
* �������� : ���������� ֮ ��о�Զ�                                                                                   
* ������� : pCoreAutoActionObj -- ��о�Զ���������  
*            pStep              -- ����
*            ActionRepeat       -- ������о��������                                                                   
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void ActionObjHandle_CoreAuto(CoreAutoActionObj_t *pCoreAutoActionObj, ActionTabStep_t *pStep, uint8_t ActionRepeat)
{
  uint8_t  ZSet;                                                              /*3Dǿ������ֵ*/
  uint8_t  ZAjust;
  
  
  /*ִ�������ж�-----------------------------------------------*/
  if((NULL == pCoreAutoActionObj) || 
     (NULL == pStep)              )
  {
    return;
  }

  if((0xAA == pCoreAutoActionObj->XPosition) &&
     (0xAA == pCoreAutoActionObj->YPosition) &&
     (0xAA == pCoreAutoActionObj->ZPosition) )
  {
    pStep->Num = ACTION_TAB_STEP_NUM_END;                                     /*������*/
  }

  if(pStep->Num > ACTION_TAB_STEP_NUM_MAX)
  {
    return;
  }

  /*���û�оλ��-----------------------------------------------------*/
  Core_SetXPosition(pCoreAutoActionObj->XPosition);
  Core_SetYPosition(pCoreAutoActionObj->YPosition);

  /*���������� = ����е�ֵ + pMChair->AutoCoreFlexLevelAdjust(�Զ������£��û�����ĵ�����)*/
  ZSet = pCoreAutoActionObj->ZPosition;                                       /*Ĭ��3D����ǿ���µ�Z����ֵ*/
  pMChair->AutoCoreFlexLevelAdjust = (pMChair->AutoCoreFlexLevelAdjust<1) ? 1 : pMChair->AutoCoreFlexLevelAdjust;
  if(pMChair->AutoCoreFlexLevelAdjust > CORE_AUTO_PZLEVEL_REF)                /*3D����ǿ�ȱ�ǿ*/
  {
    ZAjust = pMChair->AutoCoreFlexLevelAdjust - CORE_AUTO_PZLEVEL_REF;
    ZSet += ZAjust;
    if((PZDEC15 <= pCoreAutoActionObj->ZPosition) && 
       (pCoreAutoActionObj->ZPosition <= PZADD15))                            /*��������*/
    {
      ZSet = (ZSet > PZADD15) ? (PZADD15) : (ZSet);
    }
    else
    {
      ZSet = (ZSet > PZ_MAX) ? (PZ_MAX) : (ZSet);
    }
  }
  else if(pMChair->AutoCoreFlexLevelAdjust < CORE_AUTO_PZLEVEL_REF)           /*3D����ǿ�ȱ���*/
  {
    ZAjust = CORE_AUTO_PZLEVEL_REF - pMChair->AutoCoreFlexLevelAdjust;
    if((PZDEC15 <= pCoreAutoActionObj->ZPosition) && 
       (pCoreAutoActionObj->ZPosition <= PZADD15))                            /*��������*/
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

  /*���û�о�ٶ�---�Ժ�����϶���Ϊ�����������û������ٶȣ�ֻ�ܵ���3Dǿ��(������)---------*/
  Core_SetXYZActionSpeed(pCoreAutoActionObj->XYZActionSpeed); 
  Core_SetTCSActionSpeed(pCoreAutoActionObj->TCSActionSpeed); 

  /*���û�о��Ħ�ַ�����---------------------------------------------*/
  Core_SetXYZAction(CORE_ACTION_EXE_AUTO, pCoreAutoActionObj->XYZAction); 
  Core_SetTCSAction(CORE_ACTION_EXE_AUTO, pCoreAutoActionObj->TCSAction); 
  
  /*��ѯ��оXYZ������ɴ���------------------------------------------*/
  if((pCoreAutoActionObj->XYZAction != XYZ_ACTION_NONE) &&                    /*xyz ������Ч*/
     (ActionRepeat                  != RIGNORE)         )                     /*����������*/  
  {
    pStep->IncJudgeCondition.Bit.CoreXYZActionRepeat = TRUE;                  /*��оXYZ�����ظ�����  ��Ϊ�������ӵ��ж�����*/  
    pStep->Repeat = Core_GetXYZActionCompleteRepeat();                        /*��ȡ��ǰ��������ɴ���*/
    if(pStep->Repeat >= ActionRepeat)
    {
      pStep->IncConditionState.Bit.CoreXYZActionRepeat = TRUE;                /*������������״̬����оXYZ�����ظ�����*/
    }
  }
}

/*
************************************************************************************************************************
* �������� : ActionObjHandle_SpikeAuto                                                                                   
* �������� : ���������� ֮ �Ƹ��Զ�                                                                            
* ������� : pSpkeAutoActionObj -- �Ƹ��Զ���������  
*            pStep              -- ����                                                           
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void ActionObjHandle_SpikeAuto(SpikeAutoActionObj_t *pSpkeAutoActionObj, ActionTabStep_t *pStep)
{
  uint8_t         SpikeOkState;
  uint8_t         SpikeOkJudge;

  /*ִ�������ж�-----------------------------------------------*/
  if((NULL == pSpkeAutoActionObj) || 
     (NULL == pStep)              )
  {
    return;
  }

  if((0xAA == pSpkeAutoActionObj->BackPosition) &&
     (0xAA == pSpkeAutoActionObj->ZeroPosition) &&
     (0xAA == pSpkeAutoActionObj->FeetPosition) )
  {
    pStep->Num = ACTION_TAB_STEP_NUM_END;                                 /*������*/
  }

  if(pStep->Num > ACTION_TAB_STEP_NUM_MAX)
  {
    return;
  }

  /*�����Ƹ�λ��------------------------------------------------*/
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

  /*��ѯ�Ƹ�λ��------------------------------------------------*/
  SpikeOkJudge = 0;                                                       /*Ĭ�ϲ��ж��Ƹ�λ��*/
  SpikeOkState = 0;                                                       /*Ĭ���Ƹ�λ��δ��λ*/

  if((pSpkeAutoActionObj->BackPosition != PKEEP)   &&
     (pSpkeAutoActionObj->BackPosition != PIGNORE) )
  {
    SpikeOkJudge |= 0x01;                                                 /*Ҫ�жϱ����Ƹ�λ��*/
    if(Spike_GetBackAngle() == pSpkeAutoActionObj->BackPosition)
    {
      SpikeOkState |= 0x01;                                               /*�����Ƹ˵�λ*/
    }
  }

  if((pSpkeAutoActionObj->ZeroPosition != PKEEP)   &&
     (pSpkeAutoActionObj->ZeroPosition != PIGNORE) )
  {
    SpikeOkJudge |= 0x02;                                                 /*Ҫ�ж��������Ƹ�λ��*/
    if(Spike_GetZeroAngle() == pSpkeAutoActionObj->ZeroPosition)
    {
      SpikeOkState |= 0x02;                                               /*�������Ƹ˵�λ*/
    }
  }

  if((pSpkeAutoActionObj->FeetPosition != PKEEP)   &&
     (pSpkeAutoActionObj->FeetPosition != PIGNORE) )
  {
    SpikeOkJudge |= 0x04;                                                 /*Ҫ�ж��Ȳ��Ƹ�λ��*/
    if(Spike_GetFeetAngle() == pSpkeAutoActionObj->FeetPosition)
    {
      SpikeOkState |= 0x04;                                               /*�Ȳ��Ƹ˵�λ*/
    }
  }

  if(SpikeOkJudge > 0)                                                    /*��Ҫ�ж��Ƹ�λ��*/
  {
    pStep->IncJudgeCondition.Bit.SpikeAngleOk = TRUE;                     /*�Ƹ�λ��  ��Ϊ�������ӵ��ж�����*/  
    if(SpikeOkJudge == SpikeOkState)
    {
      pStep->IncConditionState.Bit.SpikeAngleOk = TRUE;                   /*������������״̬���Ƹ�λ��*/
    }
  }

  /*С����������------------------------------------------------*/
  if(TRUE == pSpkeAutoActionObj->LegFlexCtrl.Bit.Extend)  
  {
    pStep->IncJudgeCondition.Bit.LegFlexOk = TRUE;                       /*С�������Ƹ�  ��Ϊ�������ӵ��ж�����*/  

    if((TRUE == pSpkeAutoActionObj->LegFlexCtrl.Bit.CheckTouchGround) && /*Ҫִ�д��ؼ��*/
       (TRUE == pMChair->StateLegFlexSpike.Bit.TouchGround)             )  /*�Ѵ���*/ 
    {
      pStep->IncConditionState.Bit.LegFlexOk = TRUE;                     /*������������״̬��С�������Ƹ� */
      Spike_SetLegFlexMove(SPIKE_MOVE_NONE);  
    }
    else if(TRUE == pMChair->StateLegFlexSpike.Bit.ReachExtendLimt)      /*�쵽����*/
    {
      pStep->IncConditionState.Bit.LegFlexOk = TRUE;                     /*������������״̬��С�������Ƹ� */
      Spike_SetLegFlexMove(SPIKE_MOVE_NONE);  
    }
    else
    {
      Spike_SetLegFlexMove(SPIKE_MOVE_LEG_EXTEND);  
    }
  }
  else if(TRUE == pSpkeAutoActionObj->LegFlexCtrl.Bit.Shorten)
  {
    pStep->IncJudgeCondition.Bit.LegFlexOk = TRUE;                       /*С�������Ƹ�  ��Ϊ�������ӵ��ж�����*/  

    if((TRUE == pSpkeAutoActionObj->LegFlexCtrl.Bit.CheckTouchFeet) &&   /*Ҫִ�д��ż��*/
       (TRUE == pMChair->StateLegFlexSpike.Bit.TouchFeet)           )    /*�Ѵ���*/ 
    {
      pStep->IncConditionState.Bit.LegFlexOk = TRUE;                     /*������������״̬��С�������Ƹ� */
      Spike_SetLegFlexMove(SPIKE_MOVE_NONE);  
    }
    else if(TRUE == pMChair->StateLegFlexSpike.Bit.ReachShortenLimt)     /*��������*/
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
    pStep->IncJudgeCondition.Bit.ULegFlexOk = TRUE;                      /*��С�������Ƹ�  ��Ϊ�������ӵ��ж�����*/  
    if(TRUE == pMChair->StateLegFlexSpike.Bit.ULegReachExtendLimt)       /*�쵽����*/
    {
      pStep->IncConditionState.Bit.ULegFlexOk = TRUE;                    /*������������״̬����С�������Ƹ� */
      Spike_SetULegFlexMove(SPIKE_MOVE_NONE);  
    }
    else
    {
      Spike_SetULegFlexMove(SPIKE_MOVE_LEG_EXTEND);  
    }
  }
  else if(TRUE == pSpkeAutoActionObj->LegFlexCtrl.Bit.UpShorten)
  {
    pStep->IncJudgeCondition.Bit.ULegFlexOk = TRUE;                      /*��С�������Ƹ�  ��Ϊ�������ӵ��ж�����*/  
    if(TRUE == pMChair->StateLegFlexSpike.Bit.ULegReachShortenLimt)      /*��������*/
    {
      pStep->IncConditionState.Bit.ULegFlexOk = TRUE;                    /*������������״̬����С�������Ƹ� */
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
* �������� : ActionObjHandle_Gas                                                                                   
* �������� : ���������� ֮ ��������                                                                    
* ������� : pGasActionObj -- ������������  
*            pStep         -- ����
*            TimeTab[]     -- ʱ����                                            
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void ActionObjHandle_Gas(GasActionObj_t *pGasActionObj, ActionTabStep_t *pStep, __packed TabItemTime_t TimeTab[])
{
  /*ִ�������ж�-----------------------------------------------*/
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
    pStep->Num = ACTION_TAB_STEP_NUM_END;                  /*������*/
  }

  if(pStep->Num > ACTION_TAB_STEP_NUM_MAX)
  {
    return;
  }

  /*��������------------------------------------------------*/
  Gas_SetPumpSw(ON);
  Gas_SetGasPart(pGasActionObj->GasPart1.All, pGasActionObj->GasPart2.All);
}

/*
************************************************************************************************************************
* �������� : ActionObjHandle_AccompanyFunc                                                                                   
* �������� : ���������� ֮ ���湦��                                                                
* ������� : pActionTabAttr -- �������
*            pStep          -- ����
*            pLedHeatCtrl   -- �ƹ� ���� �������
*            pRollerVibCtrl -- ���� �� �������                                     
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void ActionObjHandle_AccompanyFunc(ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep, LedHeatCtrl_t *pLedHeatCtrl, RollerVibCtrl_t *pRollerVibCtrl)
{
  /*ִ�������ж�-----------------------------------------------*/
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

  /*�ڹ����л�ʱ����ʹ�ö����������pActionTabAttr��İ���ģʽ�԰��湦�ܸ�ֵ��
    �� �����������pActionTabAttr��İ���ģʽ Ϊ ByActionTabʱ��
    ���湦���ܶ��������Ŀ���λLedHeatBit �� RollerVibBit ���ơ�
    �û������ֿ����ɵ������ذ��湦�ܣ���ʱ���湦�ܵĵ�ģʽ����ΪByActionTab�����Ǳ�ΪMannual �� NONE��*/

  /*����ִ�� ֮ �ƹ� ����-------------------------------------------------------------*/
  if((FMA_FEET_HEAT_ByActionTab == pActionTabAttr->FeetHeatMode)     &&              /*���������İ���ģʽΪ ByActionTab*/
     (FMA_FEET_HEAT_ByActionTab == pMChair->FuncMA_Heat.Bit.Feet))                   /*�� ��ǰ��ģʽҲΪ ByActionTab����û���û������ֿ����ı�*/
  {
    pMChair->FeetHeatCtrlSw = pLedHeatCtrl->Bit.FeetHeat;                            /*�Ų�����*/
  }
  if((FMA_CALVES_HEAT_ByActionTab == pActionTabAttr->CalvesHeatMode)     &&          /*���������İ���ģʽΪ ByActionTab*/
     (FMA_CALVES_HEAT_ByActionTab == pMChair->FuncMA_Heat.Bit.Calves))               /*�� ��ǰ��ģʽҲΪ ByActionTab����û���û������ֿ����ı�*/
  {
    pMChair->CalvesHeatCtrlSw = pLedHeatCtrl->Bit.CalvesHeat;                        /*�Ȳ�����*/
  }
  if((FMA_SEAT_HEAT_ByActionTab == pActionTabAttr->SeatHeatMode)     &&              /*���������İ���ģʽΪ ByActionTab*/
     (FMA_SEAT_HEAT_ByActionTab == pMChair->FuncMA_Heat.Bit.Seat))                   /*�� ��ǰ��ģʽҲΪ ByActionTab����û���û������ֿ����ı�*/
  {
    pMChair->SeatHeatCtrlSw = pLedHeatCtrl->Bit.SeatHeat;                            /*��������*/
  }
  if((FMA_LUMBARBACK_HEAT_ByActionTab == pActionTabAttr->LumbarBackHeatMode)     &&  /*���������İ���ģʽΪ ByActionTab*/
     (FMA_LUMBARBACK_HEAT_ByActionTab == pMChair->FuncMA_Heat.Bit.LumbarBack))       /*�� ��ǰ��ģʽҲΪ ByActionTab����û���û������ֿ����ı�*/
  {
    pMChair->LumbarBackHeatCtrlSw = pLedHeatCtrl->Bit.LumbarBackHeat;                /*��������*/
  }

  /*����ִ�� ֮ ���� ��-------------------------------------------------------------*/
  if((FMA_FEET_ROLLER_ByActionTab == pActionTabAttr->FeetRollerMode)       &&        /*���������İ���ģʽΪ ByActionTab*/
     (FMA_FEET_ROLLER_ByActionTab == pMChair->FuncMA_Roller.Bit.Feet))               /*�� ��ǰ��ģʽҲΪ ByActionTab����û���û������ֿ����ı�*/
  {
    pMChair->FeetRollerCtrlSw = pRollerVibCtrl->Bit.FeetRoller;                      /*�Ź�*/
  }
  if((FMA_CALVES_ROLLER_ByActionTab == pActionTabAttr->CalvesRollerMode)       &&    /*���������İ���ģʽΪ ByActionTab*/
     (FMA_CALVES_ROLLER_ByActionTab == pMChair->FuncMA_Roller.Bit.Calves))           /*�� ��ǰ��ģʽҲΪ ByActionTab����û���û������ֿ����ı�*/
  {
    pMChair->CalvesRollerCtrlSw = pRollerVibCtrl->Bit.CalvesRoller;                  /*�ȹ�*/
  }
  
  if((FMA_FEET_VIB_ByActionTab == pActionTabAttr->FeetVibMode)    &&                 /*���������İ���ģʽΪ ByActionTab*/
     (FMA_FEET_VIB_ByActionTab == pMChair->FuncMA_Vib.Bit.Feet))                     /*�� ��ǰ��ģʽҲΪ ByActionTab����û���û������ֿ����ı�*/
  {
    pMChair->FeetVibCtrlSw = pRollerVibCtrl->Bit.FeetVib;                            /*�Ų���*/
  }
  if((FMA_CALVES_VIB_ByActionTab == pActionTabAttr->CalvesVibMode)    &&             /*���������İ���ģʽΪ ByActionTab*/
     (FMA_CALVES_VIB_ByActionTab == pMChair->FuncMA_Vib.Bit.Calves))                 /*�� ��ǰ��ģʽҲΪ ByActionTab����û���û������ֿ����ı�*/
  {
    pMChair->CalvesVibCtrlSw = pRollerVibCtrl->Bit.CalvesVib;                        /*�Ȳ���*/
  }
  if((FMA_SEAT_VIB_ByActionTab == pActionTabAttr->SeatVibMode)    &&                 /*���������İ���ģʽΪ ByActionTab*/
     (FMA_SEAT_VIB_ByActionTab == pMChair->FuncMA_Vib.Bit.Seat))                     /*�� ��ǰ��ģʽҲΪ ByActionTab����û���û������ֿ����ı�*/
  {
    pMChair->SeatVibCtrlSw = pRollerVibCtrl->Bit.SeatVib;                            /*������*/
  }
  if((FMA_LUMBARBACK_VIB_ByActionTab == pActionTabAttr->LumbarBackVibMode)    &&     /*���������İ���ģʽΪ ByActionTab*/
     (FMA_LUMBARBACK_VIB_ByActionTab == pMChair->FuncMA_Vib.Bit.LumbarBack))         /*�� ��ǰ��ģʽҲΪ ByActionTab����û���û������ֿ����ı�*/
  {
    pMChair->LumbarBackVibCtrlSw = pRollerVibCtrl->Bit.LumbarBackVib;                /*������*/
  }
}

/*
************************************************************************************************************************
* �������� : FuncTabStepTimeHandle                                                                                   
* �������� : �������Ĳ���ʱ�䴦��                                                         
* ������� : ExePeriod -- ����ִ��ʱ��
*            pStep     -- ����
*            TimeTab[] -- ʱ����
*            IfWithGas -- ��ʶ��������Ƿ������                                
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void ActionTabStep_TimeHandle(Ticker_t ExePeriod, ActionTabStep_t *pStep, __packed TabItemTime_t TimeTab[], uint8_t IfWithGas)
{
  TabItemTime_t  MaxRunTime;

  /*ִ�������ж�----------------------------------------------------------*/
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
  if(TRUE == IfWithGas)                                                  /*���г�������ʱ�����ݳ���ǿ��*/
  {
    pMChair->GasIntensity = (pMChair->GasIntensity<1) ? 1:pMChair->GasIntensity;
    pMChair->GasIntensity = (pMChair->GasIntensity>5) ? 5:pMChair->GasIntensity;
    MaxRunTime = TimeTab[pMChair->GasIntensity - 1];
  }
  else                                                                   /*û��������ֻ��һ��ʱ����*/
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

  /*���оXYZ�����ظ������ж�  �� ���ȼ� ���� ʱ���*/ 
  if((FALSE == pStep->IncJudgeCondition.Bit.CoreXYZActionRepeat) &&      /*��оXYZ�����ظ�����  ����Ϊ�������ӵ��ж�����*/  
     (MaxRunTime != TIGNORE)                                     )       /*ʱ�䲻����*/  
  {
    pStep->IncJudgeCondition.Bit.TimeOut = TRUE;                         /*��ʱ  ��Ϊ�������ӵ��ж�����*/  
    if(pStep->RunTimeMs100 > MaxRunTime)
    {
      pStep->IncConditionState.Bit.TimeOut = TRUE;                       /*������������״̬����ʱ */
    }
  }
}

/*
************************************************************************************************************************
* �������� : ActionTabStep_IterateHandle                                                                                   
* �������� : ����������������                                                   
* ������� : pActionTabAttr -- �������  
*            pStep          -- �������                          
* ���ز��� : FALSE -- ����û��
*            TRUE  -- ���跢�������ı�
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t ActionTabStep_IterateHandle(ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  if((NULL == pActionTabAttr) || 
     (NULL == pStep)          )
  {
    return FALSE;
  }

  pStep->AdditonOp.Bit.OccurIterate = FALSE;                                /*��Ĭ�ϲ��費�������*/

  /*���ע����ɼܹ���ͬ�����������������ȼ���        ���
    ���    ��о�������� > ʱ�� > �Ƹ�λ�� > С������ ���*/
  if((TRUE == pStep->IncJudgeCondition.Bit.CoreXYZActionRepeat) &&          /*��оXYZ��������*/
     (TRUE == pStep->IncConditionState.Bit.CoreXYZActionRepeat) )
  {
    pStep->AdditonOp.Bit.OccurIterate = TRUE;
  }
  else if((TRUE == pStep->IncJudgeCondition.Bit.TimeOut) &&                 /*��ʱ*/
          (TRUE == pStep->IncConditionState.Bit.TimeOut) )
  {
    pStep->AdditonOp.Bit.OccurIterate = TRUE;
  }
  else if((TRUE == pStep->IncJudgeCondition.Bit.SpikeAngleOk) &&            /*�Ƹ�*/
          (TRUE == pStep->IncConditionState.Bit.SpikeAngleOk) )
  {
    pStep->AdditonOp.Bit.OccurIterate = TRUE;
  }
//  else if((TRUE == pStep->IncJudgeCondition.Bit.LegFlexOk) &&              /*С������ */
//          (TRUE == pStep->IncConditionState.Bit.LegFlexOk) )
//  {
//    pStep->AdditonOp.Bit.OccurIterate = TRUE;
//  }
  else if(TRUE == pStep->IncJudgeCondition.Bit.LegFlexOk) 
  {
    if(TRUE == pStep->IncJudgeCondition.Bit.ULegFlexOk)                    
    {
      if((TRUE == pStep->IncConditionState.Bit.ULegFlexOk) &&               /*����С��������Ҫ�ж�*/
         (TRUE == pStep->IncConditionState.Bit.LegFlexOk)  )
      {
        pStep->AdditonOp.Bit.OccurIterate = TRUE;
      }
    }
    else                                                                    
    {
      if(TRUE == pStep->IncConditionState.Bit.LegFlexOk)                    /*ֻ��Ҫ�ж���С������*/
      {
        pStep->AdditonOp.Bit.OccurIterate = TRUE;
      }
    }
  }
  else if(TRUE == pStep->IncJudgeCondition.Bit.ULegFlexOk)                  /*ֻ���ж���С������*/
  {
    if(TRUE == pStep->IncConditionState.Bit.ULegFlexOk)
    {
      pStep->AdditonOp.Bit.OccurIterate = TRUE;
    }
  }
  else if((STEP_HOP_NEXT == pStep->AdditonOp.Bit.StepHop) ||                /*��������*/
          (STEP_HOP_LAST == pStep->AdditonOp.Bit.StepHop) )
  {
    pStep->AdditonOp.Bit.OccurIterate = TRUE;
  }
  else if(pStep->Num > ACTION_TAB_STEP_NUM_MAX)
  {
    pStep->AdditonOp.Bit.OccurIterate = TRUE;
  }

  /*�����������--------------------------------------------------*/
  if(TRUE == pStep->AdditonOp.Bit.OccurIterate)
  {
    //if(TRUE == pStep->IncJudgeCondition.Bit.CoreXYZActionRepeat)            /*�л�оXYZ����*/
    if(TRUE == pStep->AdditonOp.Bit.IsWithCore)            /*������о��*/
    {
      Core_ResetXYZActionStep();                                            /*�������ʱ��λ��оXYZ�����ַ�����*/
    }
    
    if(STEP_HOP_LAST == pStep->AdditonOp.Bit.StepHop)                       /*������һ������������*/
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
    else                                                                    /*��ǰ����*/
    {
      if(pStep->Num < pActionTabAttr->EndStepNum)
      {
        pStep->Num++;
      }
      else
      {
        pStep->Num = pActionTabAttr->StartStepNum;                          /*�ӱ��Ŀ�ʼ��������ʼִ��*/
        pStep->TabRepeat++;                                                 /*ִ����һ�α��*/
      }
    }
    pStep->AdditonOp.Bit.StepHop = STEP_HOP_NONE;                           /*����ʱ�����������ʶ */
    pStep->Repeat = 0;
    pStep->RunTimeMs100 = 0;
  }
  
  return pStep->AdditonOp.Bit.OccurIterate;
}

/*������������������������������������������������������������������������������������������������������������������������*/
/*������������������������������������������������������������������������������������������������������������������������*/
/*
************************************************************************************************************************
* �궨��   : MChair_TabHandle_PreProcess                                                                                   
* ����˵�� : ���ִ��ǰ�ĵ�Ԥ����                                                                                                         
************************************************************************************************************************
*/
#define MChair_TabHandle_PreProcess()                                                                                  \
{                                                                                                                      \
  if((NULL == pActionTabAttr) ||                                                                                       \
     (NULL == pStep)          )                                                                                        \
  {                                                                                                                    \
    return;                                                                                                            \
  }                                                                                                                    \
  ActionTabStep_IterateHandle(pActionTabAttr, pStep);  /*ִ��ǰ���Ȳ������*/                                          \
  if(TRUE == pStep->AdditonOp.Bit.SingleExe)                                                                           \
  {                                                                                                                    \
    if(pStep->TabRepeat > 0)                           /*����ִ�еģ�����ִ����һ��󣬲���ִ��*/                    \
    {                                                                                                                  \
      return;                                                                                                          \
    }                                                                                                                  \
  }                                                                                                                    \
  pStep->IncConditionState.All = 0;                    /*ִ��ǰ������������������״̬���㣬��غ����ڻ���������λ*/  \
  pStep->IncJudgeCondition.All = 0;                    /*ִ��ǰ�������������ж��������㣬��غ����ڻ���������λ*/    \
}

/*
************************************************************************************************************************
* �������� : MChair_TabHandle_CoreAuto                                                                                   
* �������� : ��������� ֮ ����о���Զ�                                              
* ������� : ExePeriod      -- ����ִ������
*            pActionTabAttr -- �������
*            pStep          -- �������                  
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_CoreAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  CoreMixOtherTabItem_t  *pCoreMixOtherTab;                                         /*�������*/
  CoreAutoTabItem_t      *pActionTab;                                               /*�������*/ 
  CoreAutoTabItem_t      *pExeStepData;                                             /*Ҫִ�еĲ�������*/ 

  pStep->AdditonOp.Bit.IsWithCore = TRUE;                                           /*������о��*/
  MChair_TabTry_UpdateStepHopState(TAB_TRY_TYPE_CORE, pStep);                       /*������� ֮ ���²��������״̬������û����ʱ���ǲ�����µ�*/
  MChair_TabHandle_PreProcess();                                                    /*���ִ��ǰ�ĵ�Ԥ����*/
  pActionTab = pActionTabAttr->pActionTab;                                          /*��Ĭ�ϴӱ��������ȡ���������*/
  pExeStepData = &pActionTab[pStep->Num];                                           /*�ȴ�Ĭ�ϵı����ȡ��Ҫִ�еĲ�������*/
  if(TRUE == pStep->AdditonOp.Bit.IsCoreMixOther)                                   /*�ǡ���о����ϡ����������*/
  {
    pCoreMixOtherTab = pActionTabAttr->pActionTab;                                  /*�ӱ��������ȡ���������*/
    pExeStepData = &pCoreMixOtherTab[pStep->Num].CoreAutoTabItem;                   /*�ӱ����ȡ��Ҫִ�еĲ�������*/
  }
  if(FA_TAB_TRY == pActionTabAttr->FuncID)                                          /*���������鿪��������ȥȡҪ����Ĳ�������*/
  {
    pExeStepData = MChair_TabTry_GetExeStepData(TAB_TRY_TYPE_CORE, pStep);          /*ȡ��Ҫ����Ĳ�������*/
  }
  ActionObjHandle_CoreAuto(&pExeStepData->CoreAutoAction, pStep, pExeStepData->Repeat); 
  ActionObjHandle_AccompanyFunc(pActionTabAttr, pStep, &pExeStepData->LedHeatBit, &pExeStepData->RollerVibBit);
  ActionTabStep_TimeHandle(ExePeriod, pStep, &pExeStepData->Time1, FALSE);    
}

/*
************************************************************************************************************************
* �������� : MChair_TabHandle_GasAuto                                                                                   
* �������� : ��������� ֮ ���������Զ�                                           
* ������� : ExePeriod      -- ����ִ������
*            pActionTabAttr -- �������
*            pStep          -- �������                  
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_GasAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  GasAutoTabItem_t  *pActionTab;                                                    /*�������*/ 
  GasAutoTabItem_t  *pExeStepData;                                                  /*Ҫִ�еĲ�������*/ 

  MChair_TabTry_UpdateStepHopState(TAB_TRY_TYPE_GAS, pStep);                        /*������� ֮ ���²��������״̬������û����ʱ���ǲ�����µ�*/
  MChair_TabHandle_PreProcess();                                                    /*���ִ��ǰ�ĵ�Ԥ����*/
  pActionTab = pActionTabAttr->pActionTab;                                          /*��Ĭ�ϴӱ��������ȡ���������*/
  pExeStepData = &pActionTab[pStep->Num];                                           /*�ȴ�Ĭ�ϵı����ȡ��Ҫִ�еĲ�������*/
  if(FA_TAB_TRY == pActionTabAttr->FuncID)                                          /*���������鿪��������ȥȡҪ����Ĳ�������*/
  {
    pExeStepData = MChair_TabTry_GetExeStepData(TAB_TRY_TYPE_GAS, pStep);           /*ȡ��Ҫ����Ĳ�������*/
  }
  ActionObjHandle_Gas(&pExeStepData->GasAutoAction, pStep, &pExeStepData->Time1); 
  ActionObjHandle_AccompanyFunc(pActionTabAttr, pStep, &pExeStepData->LedHeatBit, &pExeStepData->RollerVibBit);
  ActionTabStep_TimeHandle(ExePeriod, pStep, &pExeStepData->Time1, TRUE);    
}

/*
************************************************************************************************************************
* �������� : MChair_TabHandle_SpikeAuto                                                                                   
* �������� : ��������� ֮ ���Ƹˡ��Զ�                                         
* ������� : ExePeriod      -- ����ִ������
*            pActionTabAttr -- �������
*            pStep          -- �������                  
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_SpikeAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  SpikeAutoTabItem_t  *pActionTab;                                                  /*�������*/ 
  SpikeAutoTabItem_t  *pExeStepData;                                                /*Ҫִ�еĲ�������*/ 

  MChair_TabTry_UpdateStepHopState(TAB_TRY_TYPE_SPIKE, pStep);                      /*������� ֮ ���²��������״̬������û����ʱ���ǲ�����µ�*/
  MChair_TabHandle_PreProcess();                                                    /*���ִ��ǰ�ĵ�Ԥ����*/
  pActionTab = pActionTabAttr->pActionTab;                                          /*��Ĭ�ϴӱ��������ȡ���������*/
  pExeStepData = &pActionTab[pStep->Num];                                           /*�ȴ�Ĭ�ϵı����ȡ��Ҫִ�еĲ�������*/
  if(FA_TAB_TRY == pActionTabAttr->FuncID)                                          /*���������鿪��������ȥȡҪ����Ĳ�������*/
  {
    pExeStepData = MChair_TabTry_GetExeStepData(TAB_TRY_TYPE_SPIKE, pStep);         /*ȡ��Ҫ����Ĳ�������*/
  }
  ActionObjHandle_SpikeAuto(&pExeStepData->SpikeAutoAction, pStep); 
  ActionTabStep_TimeHandle(ExePeriod, pStep, &pExeStepData->Time1, FALSE);    
}

/*
************************************************************************************************************************
* �������� : MChair_TabHandle_CoreGasAuto                                                                                   
* �������� : ��������� ֮ ����о+�������Զ�                          
* ������� : ExePeriod      -- ����ִ������
*            pActionTabAttr -- �������
*            pStep          -- �������                  
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_CoreGasAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  CoreGasAutoTabItem_t  *pActionTab;                                                /*�������*/ 
  CoreGasAutoTabItem_t  *pExeStepData;                                              /*Ҫִ�еĲ�������*/ 

  pStep->AdditonOp.Bit.IsWithCore = TRUE;                                           /*������о��*/
  MChair_TabTry_UpdateStepHopState(TAB_TRY_TYPE_COREGAS, pStep);                    /*������� ֮ ���²��������״̬������û����ʱ���ǲ�����µ�*/
  MChair_TabHandle_PreProcess();                                                    /*���ִ��ǰ�ĵ�Ԥ����*/
  pActionTab = pActionTabAttr->pActionTab;                                          /*��Ĭ�ϴӱ��������ȡ���������*/
  pExeStepData = &pActionTab[pStep->Num];                                           /*�ȴ�Ĭ�ϵı����ȡ��Ҫִ�еĲ�������*/
  if(FA_TAB_TRY == pActionTabAttr->FuncID)                                          /*���������鿪��������ȥȡҪ����Ĳ�������*/
  {
    pExeStepData = MChair_TabTry_GetExeStepData(TAB_TRY_TYPE_COREGAS, pStep);       /*ȡ��Ҫ����Ĳ�������*/
  }
  ActionObjHandle_CoreAuto(&pExeStepData->CoreAutoAction, pStep, pExeStepData->Repeat); 
  ActionObjHandle_Gas(&pExeStepData->GasAutoAction, pStep, &pExeStepData->Time1); 
  ActionObjHandle_AccompanyFunc(pActionTabAttr, pStep, &pExeStepData->LedHeatBit, &pExeStepData->RollerVibBit);
  ActionTabStep_TimeHandle(ExePeriod, pStep, &pExeStepData->Time1, TRUE);    
}

/*
************************************************************************************************************************
* �������� : MChair_TabHandle_CoreSpikeAuto                                                                                   
* �������� : ��������� ֮ ����о+�Ƹˡ��Զ�                                    
* ������� : ExePeriod      -- ����ִ������
*            pActionTabAttr -- �������
*            pStep          -- �������                  
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_CoreSpikeAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  CoreSpikeAutoTabItem_t  *pActionTab;                                              /*�������*/ 
  CoreSpikeAutoTabItem_t  *pExeStepData;                                            /*Ҫִ�еĲ�������*/ 

  pStep->AdditonOp.Bit.IsWithCore = TRUE;                                           /*������о��*/
  MChair_TabTry_UpdateStepHopState(TAB_TRY_TYPE_CORESPIKE, pStep);                  /*������� ֮ ���²��������״̬������û����ʱ���ǲ�����µ�*/
  MChair_TabHandle_PreProcess();                                                    /*���ִ��ǰ�ĵ�Ԥ����*/
  pActionTab = pActionTabAttr->pActionTab;                                          /*��Ĭ�ϴӱ��������ȡ���������*/
  pExeStepData = &pActionTab[pStep->Num];                                           /*�ȴ�Ĭ�ϵı����ȡ��Ҫִ�еĲ�������*/
  if(FA_TAB_TRY == pActionTabAttr->FuncID)                                          /*���������鿪��������ȥȡҪ����Ĳ�������*/
  {
    pExeStepData = MChair_TabTry_GetExeStepData(TAB_TRY_TYPE_CORESPIKE, pStep);     /*ȡ��Ҫ����Ĳ�������*/
  }
  ActionObjHandle_CoreAuto(&pExeStepData->CoreAutoAction, pStep, pExeStepData->Repeat); 
  ActionObjHandle_SpikeAuto(&pExeStepData->SpikeAutoAction, pStep); 
  ActionObjHandle_AccompanyFunc(pActionTabAttr, pStep, &pExeStepData->LedHeatBit, &pExeStepData->RollerVibBit);
  ActionTabStep_TimeHandle(ExePeriod, pStep, &pExeStepData->Time1, FALSE);    
}

/*
************************************************************************************************************************
* �������� : MChair_TabHandle_GasSpikeAuto                                                                                   
* �������� : ��������� ֮ ������+�Ƹˡ��Զ�                                         
* ������� : ExePeriod      -- ����ִ������
*            pActionTabAttr -- �������
*            pStep          -- �������                  
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_GasSpikeAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  GasSpikeAutoTabItem_t  *pActionTab;                                               /*�������*/ 
  GasSpikeAutoTabItem_t  *pExeStepData;                                             /*Ҫִ�еĲ�������*/ 

  MChair_TabTry_UpdateStepHopState(TAB_TRY_TYPE_GASSPIKE, pStep);                   /*������� ֮ ���²��������״̬������û����ʱ���ǲ�����µ�*/
  MChair_TabHandle_PreProcess();                                                    /*���ִ��ǰ�ĵ�Ԥ����*/
  pActionTab = pActionTabAttr->pActionTab;                                          /*��Ĭ�ϴӱ��������ȡ���������*/
  pExeStepData = &pActionTab[pStep->Num];                                           /*�ȴ�Ĭ�ϵı����ȡ��Ҫִ�еĲ�������*/
  if(FA_TAB_TRY == pActionTabAttr->FuncID)                                          /*���������鿪��������ȥȡҪ����Ĳ�������*/
  {
    pExeStepData = MChair_TabTry_GetExeStepData(TAB_TRY_TYPE_GASSPIKE, pStep);      /*ȡ��Ҫ����Ĳ�������*/
  }
  ActionObjHandle_Gas(&pExeStepData->GasAutoAction, pStep, &pExeStepData->Time1); 
  ActionObjHandle_SpikeAuto(&pExeStepData->SpikeAutoAction, pStep); 
  ActionObjHandle_AccompanyFunc(pActionTabAttr, pStep, &pExeStepData->LedHeatBit, &pExeStepData->RollerVibBit);
  ActionTabStep_TimeHandle(ExePeriod, pStep, &pExeStepData->Time1, TRUE);    
}

/*
************************************************************************************************************************
* �������� : MChair_TabHandle_CoreGasSpikeAuto                                                                                   
* �������� : ��������� ֮ ����о+����+�Ƹˡ��Զ�                          
* ������� : ExePeriod      -- ����ִ������
*            pActionTabAttr -- �������
*            pStep          -- �������                  
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_CoreGasSpikeAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  CoreGasSpikeAutoTabItem_t  *pActionTab;                                           /*�������*/ 
  CoreGasSpikeAutoTabItem_t  *pExeStepData;                                         /*Ҫִ�еĲ�������*/ 

  pStep->AdditonOp.Bit.IsWithCore = TRUE;                                           /*������о��*/
  MChair_TabTry_UpdateStepHopState(TAB_TRY_TYPE_COREGASSPIKE, pStep);               /*������� ֮ ���²��������״̬������û����ʱ���ǲ�����µ�*/
  MChair_TabHandle_PreProcess();                                                    /*���ִ��ǰ�ĵ�Ԥ����*/
  pActionTab = pActionTabAttr->pActionTab;                                          /*��Ĭ�ϴӱ��������ȡ���������*/
  pExeStepData = &pActionTab[pStep->Num];                                           /*�ȴ�Ĭ�ϵı����ȡ��Ҫִ�еĲ�������*/
  if(FA_TAB_TRY == pActionTabAttr->FuncID)                                          /*���������鿪��������ȥȡҪ����Ĳ�������*/
  {
    pExeStepData = MChair_TabTry_GetExeStepData(TAB_TRY_TYPE_COREGASSPIKE, pStep);  /*ȡ��Ҫ����Ĳ�������*/
  }
  ActionObjHandle_CoreAuto(&pExeStepData->CoreAutoAction, pStep, pExeStepData->Repeat); 
  ActionObjHandle_Gas(&pExeStepData->GasAutoAction, pStep, &pExeStepData->Time1); 
  ActionObjHandle_SpikeAuto(&pExeStepData->SpikeAutoAction, pStep); 
  ActionObjHandle_AccompanyFunc(pActionTabAttr, pStep, &pExeStepData->LedHeatBit, &pExeStepData->RollerVibBit);
  ActionTabStep_TimeHandle(ExePeriod, pStep, &pExeStepData->Time1, TRUE);    
}


/*������������������������������������������������������������������������������������������������������������������������*/
/*========================================================================================================================
*����о��񡿻�ϡ��������                  ����о��񡿻�ϡ��������                  ����о��񡿻�ϡ��������
* ģ�����°�Ħ�ο��ڻ�о��������������л�����ĳ�������         ģ�����°�Ħ�ο��ڻ�о��������������л�����ĳ�������
* ģ�����°�Ħ�ο��ڻ�о��������������л�����ĳ�������         ģ�����°�Ħ�ο��ڻ�о��������������л�����ĳ�������
========================================================================================================================*/

static const MixOtherActionTabAttr_t  MixOtherTabAttr[] = 
{
  /*      ��ϵı��                         ���ܲ�������      ������λ����        �Ƹ˿�������
                                               �� �� ��    ͷ �� �� �� �� �� ��    �� �� С  ��  ����
                                               о �� ��    �� �� �� �� �� �� ��    �� �� �� ���� ���� */  
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

static  ActionTabStep_t  OtherTabStep;         /*�����������Ĳ���*/
static  void             *pOtherAutoTab;       /* ָ�����������*/
static  uint8_t          OtherTabIndex;        /*�������������MixOtherActionTab[]�е�����*/
static  ActionTabAttr_t  OtherAutoTabDynAttr;  /*�����������Ķ�̬����*/

/*
************************************************************************************************************************
* �������� : MChair_TabHandle_ResetMixOtherTabStep                                                                            
* �������� : ���������  ֮ ��λ���������� �Ĳ���                  
* ������� : SpikeStop �Ƿ�ֹͣ�Ƹ�  TRUE--ֹͣ   FALSE--��ֹͣ                 
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_ResetMixOtherTabStep(uint8_t SpikeStop)
{
  pOtherAutoTab = NULL;
  memset(&OtherTabStep, 0, sizeof(ActionTabStep_t));            /*��λ�������������*/

  if(MixOtherTabAttr[OtherTabIndex].ComponentAttr.Bit.Gas)      /*��ϵı�������*/
  {
    if((FUNC_TYPE_NONE == MChair.FuncAuto_Gas)        &&
       (FUNC_TYPE_NONE == MChair.FuncMannual_Gas.All) )
    {
      Gas_SetPumpSw(OFF);                                       /*�޳������ܿ������������*/
    }
    Gas_AllCtrlEn();                                            /*���в�λ��������ʹ��*/ 
    Gas_SetGasPart(0, 0);
  }
 
  if(MixOtherTabAttr[OtherTabIndex].ComponentAttr.Bit.Spike)    /*��ϵı����Ƹ�*/
  {
    if(SpikeStop)
    {
      Spike_SetLegFlexAngle(PKEEP);                             /*ֹͣ�����Ƹ�*/
      Spike_SetULegFlexAngle(PKEEP);                            /*ֹͣ�����Ƹ�*/
      Spike_SetAngle(PKEEP, PKEEP, PKEEP);                      /*ֹͣ�Ƹ�*/
    }
  }

  OtherTabIndex = 0;
}

/*
************************************************************************************************************************
* �������� : MChair_TabHandle_UpdateMixOtherTabAttr                                                                            
* �������� : ���������  ֮ ���»��������� ������  
* ������� : ��                 
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void MChair_TabHandle_UpdateMixOtherTabAttr(void)
{
  /*��������----------------------------------------------------------------------------*/
  pMChair->ComponentFuncState.Bit.Core  = (MixOtherTabAttr[OtherTabIndex].ComponentAttr.Bit.Core)  ? (FUNC_TYPE_AUTO) : (pMChair->ComponentFuncState.Bit.Core);
  pMChair->ComponentFuncState.Bit.Gas   = (MixOtherTabAttr[OtherTabIndex].ComponentAttr.Bit.Gas)   ? (FUNC_TYPE_AUTO) : (pMChair->ComponentFuncState.Bit.Gas);
  pMChair->ComponentFuncState.Bit.Spike = (MixOtherTabAttr[OtherTabIndex].ComponentAttr.Bit.Spike) ? (FUNC_TYPE_AUTO) : (pMChair->ComponentFuncState.Bit.Spike);
  if((TRUE == MixOtherTabAttr[OtherTabIndex].ComponentAttr.Bit.Gas)   &&
     (TRUE == MixOtherTabAttr[OtherTabIndex].ComponentAttr.Bit.Spike) )
  {
    pMChair->CSFlag.Bit.GasCooperateSpikeRun = TRUE;        /*�г�������Ƹ˵Ķ���*/
  }
  
  /*�Ƹ�����----------------------------------------------------------------------------*/
  pMChair->CSFlag.Bit.BackSpikeMannualMoveDisable = MixOtherTabAttr[OtherTabIndex].SpikeAttr.Bit.BackMannualDis; 
  pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable = MixOtherTabAttr[OtherTabIndex].SpikeAttr.Bit.ZeroMannualDis; 
  pMChair->CSFlag.Bit.FeetSpikeMannualMoveDisable = MixOtherTabAttr[OtherTabIndex].SpikeAttr.Bit.FeetMannualDis; 
  pMChair->CSFlag.Bit.LegFlexMannualMoveDisable   = MixOtherTabAttr[OtherTabIndex].SpikeAttr.Bit.LegFlexMannualDis; 
  pMChair->CSFlag.Bit.ULegFlexMannualMoveDisable  = MixOtherTabAttr[OtherTabIndex].SpikeAttr.Bit.ULegFlexMannualDis; 

  /*��������----------------------------------------------------------------------------*/
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
* �������� : MChair_TabHandle_CoreMixOtherAuto                                                                          
* �������� : ��������� ֮ ����о ��� ��������Զ�                  
* ������� : ExePeriod      -- ����ִ������
*            pActionTabAttr -- �������
*            pStep          -- �������                  
* ���ز��� : ��                                                                                                         
* ����˵�� : �Other�� Mix ��Other���ķ�ʽ�������ϸ�����ʽ�Ķ������         ��
             �Other������Mix��ʽ�����֣����� �� ���档                        ��
*            ��                                                                    ��
*            �� ���뷽ʽ�� ����Other�����ִ����һ�飬��Core���Ĳ���ŵ�����       ��
*            ��                                                                    ��
*            �� ���淽ʽ�� �ԡ�Core������е� �������� �� ʱ�� ��Ϊ�����������������
*            ��            ����Ӧ�����о�����ų���������                          ��
*            ��                                                                    ��
*            �� ����Core������е� Repeat = RIGNORE   ��                           ��
*            ��                    Time1 = TIGNORE                                 ��
*            �� ����������������ʱ����Other����Ϊ������                        ��
*            �� ��������£���Other����Ϊ������                                ��                                   
************************************************************************************************************************
*/
void MChair_TabHandle_CoreMixOtherAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep)
{
  CoreMixOtherTabItem_t  *pCoreMixOtherTab;                                  /*�������*/
  uint8_t  MixMode;                                                          /*���ģʽ*/
  uint8_t  i;

  /*����о���Զ� ����------------------------------------------------------------------------*/
  pStep->AdditonOp.Bit.IsCoreMixOther = TRUE;                                /*�ǡ���о����ϡ����������*/
  MChair_TabHandle_CoreAuto(ExePeriod, pActionTabAttr, pStep);  
  
  /*��ϵġ���������� ����------------------------------------------------------------------*/
  pCoreMixOtherTab = pActionTabAttr->pActionTab;
  MixMode = MIX_MODE_ACCOMPANY;                                              /*�ȼ���  �����������Ϊ������*/
  if((RIGNORE == pCoreMixOtherTab[pStep->Num].CoreAutoTabItem.Repeat) &&
     (TIGNORE == pCoreMixOtherTab[pStep->Num].CoreAutoTabItem.Time1)  )
  {
    MixMode = MIX_MODE_INSERT;                                               /*�����������Ϊ������*/
  }

  if(pOtherAutoTab != pCoreMixOtherTab[pStep->Num].pOtherTab)                /*��������������仯*/
  {
    MChair_TabHandle_ResetMixOtherTabStep(FALSE);                            /*��λ���������� �Ĳ��� */
    pOtherAutoTab = pCoreMixOtherTab[pStep->Num].pOtherTab;
    for(i=0; i<MIX_OTHER_ACTION_TAB_NUM; i++)                                /*ȷ���仯��ı����FuncActionTab�е�����*/ 
    {
      if(pOtherAutoTab == MixOtherTabAttr[i].pTab)
      {
        OtherTabIndex = i;
        break;
      }
    }
  }

  if((NULL == pOtherAutoTab) ||                                              /*�������������Ч*/
     (0    == OtherTabIndex) )                                               /*���������Ч*/
  {
    if(MIX_MODE_INSERT == MixMode) 
    {
      pStep->Num++;                                                          /*����ı����Ч����ǿ�Ƶ�������о������*/
    }
    pOtherAutoTab = NULL;
    OtherTabIndex = 0;
    return;                                                                  /*�������������Ч����ִ��*/
  }

  if(MIX_MODE_INSERT == MixMode) 
  {
    OtherTabStep.AdditonOp.Bit.SingleExe = TRUE;                             /*����ı�񣬵���ִ��*/
    if(OtherTabStep.TabRepeat > 0)
    {
      pStep->Num++;                                                          /*����ı��ִ����һ�飬��ǿ�Ƶ�������о������*/
      pOtherAutoTab = NULL;
      OtherTabIndex = 0;
      return;                                                                /*����ִ�д˲����񣬽�����һ�����ִ��*/
    }
  }
  
  MChair_TabHandle_UpdateMixOtherTabAttr();                                  /*������ص�����*/
  memcpy(&OtherAutoTabDynAttr, pActionTabAttr, sizeof(ActionTabAttr_t));     /*��Ҫ�ı�����Ը�����о��һ��*/
  OtherAutoTabDynAttr.pActionTab   = pOtherAutoTab;                          /*�������*/
  OtherAutoTabDynAttr.StartStepNum = 0;                                      /*��ʼ����*/
  OtherAutoTabDynAttr.EndStepNum   = ACTION_TAB_STEP_NUM_MAX;                /*��������*/
  switch(MixOtherTabAttr[OtherTabIndex].ComponentAttr.All & B(00000111))     /*���ԣ�b0--��о  b1--����  b2--�Ƹ� */
  { 
    case B(001): MChair_TabHandle_CoreAuto(ExePeriod,         &OtherAutoTabDynAttr, &OtherTabStep);  break;  /*��о*/
    case B(010): MChair_TabHandle_GasAuto(ExePeriod,          &OtherAutoTabDynAttr, &OtherTabStep);  break;  /*����*/
    case B(100): MChair_TabHandle_SpikeAuto(ExePeriod,        &OtherAutoTabDynAttr, &OtherTabStep);  break;  /*�Ƹ�*/ 
    case B(011): MChair_TabHandle_CoreGasAuto(ExePeriod,      &OtherAutoTabDynAttr, &OtherTabStep);  break;  /*��о+����*/ 
    case B(101): MChair_TabHandle_CoreSpikeAuto(ExePeriod,    &OtherAutoTabDynAttr, &OtherTabStep);  break;  /*��о+�Ƹ�*/ 
    case B(110): MChair_TabHandle_GasSpikeAuto(ExePeriod,     &OtherAutoTabDynAttr, &OtherTabStep);  break;  /*����+�Ƹ�*/ 
    case B(111): MChair_TabHandle_CoreGasSpikeAuto(ExePeriod, &OtherAutoTabDynAttr, &OtherTabStep);  break;  /*��о+����+�Ƹ�*/ 
    default: break;
  }
}
