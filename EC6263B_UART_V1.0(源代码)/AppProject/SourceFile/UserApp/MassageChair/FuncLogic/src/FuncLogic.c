/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣ�FuncLogic.c 
**
**    ��������: ��Ħ�����߼�����
**
**    ��    ˾���ɷ�������
**
**    ��Ŀ���ƣ�
**
**    ƽ̨��Ϣ��
**
**    ��    �ߣ�Hzy
**
**    ����˵��:
**
**    �޸ļ�¼:  --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/

/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "FuncLogic.h"
#include "MChair.h"


/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/


/*
========================================================================================================================
*�������������Ͷ��塿                              �������������Ͷ��塿                              �������������Ͷ��塿
========================================================================================================================
*/


/*
========================================================================================================================
*���������� & ����������                          ���������� & ����������                         ���������� & ����������    
========================================================================================================================
*/
/***********************************************************************************************************************
 *                   ��Ħ�����߼��л���
************************************************************************************************************************/
static const FuncLogic_t FuncLogicTab[] = 
{
  /*���ԣ�   b0~b1 -- 0�޹���   1�ֶ�  2�Զ�   3�ֶ����Զ�
             b2    -- 0 ����   1���
             b3~b5 -- Ԥ�� 
             b6~b7 -- ִ�����ȼ�  0~3����ֵԽС�����ȼ�Խ�� */

  /*��������b0--��о  b1--����  b2--�Ƹ� */

  /*       ��ǰ����                    ��ʷ����           ����          ������          �����л���������                   ����ִ�к���         */
  /*�ֶ� ������*/
  {&MChair.FuncMannual_Gas.All,    &MChair.FuncHis[0],   B(00000001), B(00000010),  MChair_FuncSwitch_GasMannual,        MChair_FuncExe_GasMannual},
  {&MChair.FuncMannual_Spike.All,  &MChair.FuncHis[1],   B(10000001), B(00000100),  MChair_FuncSwitch_SpikeMannual,      MChair_FuncExe_SpikeMannual},
  {&MChair.FuncMannual_Core.All,   &MChair.FuncHis[2],   B(00000001), B(00000001),  MChair_FuncSwitch_CoreMannual,       MChair_FuncExe_CoreMannual},

  /*�Զ� ������ ����*/
  {&MChair.FuncAuto_CoreGasSpike,  &MChair.FuncHis[3],   B(00000010), B(00000111),  MChair_FuncSwitch_CoreGasSpikeAuto,  MChair_FuncExe_CoreGasSpikeAuto},
  {&MChair.FuncAuto_CoreSpike,     &MChair.FuncHis[4],   B(00000010), B(00000101),  MChair_FuncSwitch_CoreSpikeAuto,     MChair_FuncExe_CoreSpikeAuto},
  {&MChair.FuncAuto_CoreGas,       &MChair.FuncHis[5],   B(00000010), B(00000011),  MChair_FuncSwitch_CoreGasAuto,       MChair_FuncExe_CoreGasAuto},
  {&MChair.FuncAuto_GasSpike,      &MChair.FuncHis[6],   B(00000010), B(00000110),  MChair_FuncSwitch_GasSpikeAuto,      MChair_FuncExe_GasSpikeAuto},
  {&MChair.FuncAuto_Spike,         &MChair.FuncHis[7],   B(11000010), B(00000100),  MChair_FuncSwitch_SpikeAuto,         MChair_FuncExe_SpikeAuto},
  {&MChair.FuncAuto_Gas,           &MChair.FuncHis[8],   B(00000010), B(00000010),  MChair_FuncSwitch_GasAuto,           MChair_FuncExe_GasAuto},
  {&MChair.FuncAuto_Core,          &MChair.FuncHis[9],   B(00000010), B(00000001),  MChair_FuncSwitch_CoreAuto,          MChair_FuncExe_CoreAuto},

  {&MChair.FuncAuto_GridCombo,     &MChair.FuncHis[10],  B(00000010), B(00000011),  MChair_FuncSwitch_GridComboAuto,     MChair_FuncExe_GridComboAuto},

  /*�ֶ�/�Զ�  ���湦��   �ɵ������ã�Ҳ����Ϊ�����ܵİ��������*/
  {&MChair.FuncMA_Roller.All,      &MChair.FuncHis[11],  B(00000011), B(00000000),  MChair_FuncSwitch_RollerMA,          MChair_FuncExe_RollerMA},
  {&MChair.FuncMA_Heat.All,        &MChair.FuncHis[12],  B(00000011), B(00000000),  MChair_FuncSwitch_HeatMA,            MChair_FuncExe_HeatMA},
  {&MChair.FuncMA_Vib.All,         &MChair.FuncHis[13],  B(00000011), B(00000000),  MChair_FuncSwitch_VibMA,             MChair_FuncExe_VibMA},
  {&MChair.FuncMA_Led.All,         &MChair.FuncHis[14],  B(00000011), B(00000000),  MChair_FuncSwitch_LedMA,             MChair_FuncExe_LedMA}
}; 

#define  FUNC_LOGIC_TAB_NUM     TAB_NUM(FuncLogicTab)

/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : MChair_FuncLogic_ClearAllFunc                                                                                                         
* �������� : �������й��ܣ����ر����п����İ�Ħ���ܡ�                                                                                             
* ������� : ��                                                                                      
* ���ز��� : ��                                                                                               
* ����˵�� : �� �˺����ڲ������Ƹ˽Ƕȣ��������й���һ�����ڶ�ʱ����ػ�ʱ�ŵ��á�                                ��
             �� һ���ֶ��ػ�ʱ��Ҫ��λ�Ƹ˽Ƕȡ�����������綨ʱ�����Զ��ػ����Ƿ������Ƹ˽Ƕȸ���ҵ��������������
             �� ����Ƹ˽Ƕȸ���ʵ����Ҫ�������á��˺����ڲ����á�                                                ��                                                           
************************************************************************************************************************
*/
void MChair_FuncLogic_ClearAllFunc(void)
{
  uint8_t i;
  uint8_t tmepbuf[4]={0,0,0,0};

  for(i=0; i<FUNC_LOGIC_TAB_NUM; i++)
  {
    *FuncLogicTab[i].pFuncCur = 0;                                         /*����ǰ����ʷ�����㣬���ô����л��߼����ж�*/
    *FuncLogicTab[i].pFuncHis = 0; 
  }                                                                        
  
  GridComboAuto_UpdateComboSelectBit(tmepbuf);                             /*��������ѡ��λ*/

  pMChair->ComponentFuncState.All = FUNC_TYPE_NONE;                        /*���ܹرգ��������Ĺ���״̬���*/

  Core_SetAction(CORE_ACTION_EXE_NONE, XYZ_ACTION_NONE, TCS_ACTION_NONE);  /*�رջ�о����*/
  Core_SetXYZPosition(PXWIDE, PYTOP, PZBACK);                              /*���û�о��λ��*/ 

  Spike_SetMoveAction(SPIKE_MOVE_NONE);                                    /*�Ƹ� ���ֶ������ͷ�*/
  /*ע���˺����ڲ������Ƹ˽Ƕȣ��������й���һ�����ڶ�ʱ����ػ�ʱ�ŵ��á�                              
        �ֶ��ػ�ʱ��Ҫ��λ�Ƹ˽Ƕȡ�����������綨ʱ�����Զ��ػ����Ƿ������Ƹ˽Ƕȸ���ҵ������������  
        ����Ƹ˽Ƕȸ���ʵ����Ҫ�������á��˺����ڲ����á�    */

  Gas_SetPumpSw(OFF);                                                      /*������������*/
  Gas_AllCtrlEn();                                                         /*���в�λ��������ʹ��*/                            
  Gas_SetGasPart(0, 0);                              

  MChair_RollerFuncReset_Feet();                                           /*��λ�Ź�*/
  MChair_RollerFuncReset_Calves();                                         /*��λ�ȹ�*/
  MChair_VibFuncReset_Feet();                                              /*��λ��*/
  MChair_VibFuncReset_Calves();                                            /*��λ��*/
  MChair_VibFuncReset_Seat();                                              /*��λ��*/
  MChair_VibFuncReset_LumbarBack();                                        /*��λ��*/
  MChair_HeatFuncReset_Feet();                                             /*��λ����*/
  MChair_HeatFuncReset_Calves();                                           /*��λ����*/
  MChair_HeatFuncReset_Seat();                                             /*��λ����*/
  MChair_HeatFuncReset_LumbarBack();                                       /*��λ����*/
  MChair_LedFuncReset();                                                   /*��λ��*/  
}


/*
************************************************************************************************************************
* �������� : MChair_FuncLogic_Switch                                                                                                         
* �������� : �����߼����л�                                                                                              
* ������� : ��                                                                                      
* ���ز��� : ��                                                                                               
* ����˵�� : ʹ�ñ������й��ܵ��߼��л���������ͳһ����
*            �����FuncLogicTab�������
*            ��ÿ������Ĺ����ﻹ��һ���ӱ�񣨽ṹ��ActionTabAttr_t�����壩��                                                                                                        
************************************************************************************************************************
*/
void MChair_FuncLogic_Switch(void)
{
  uint8_t i;
  uint8_t j;


  for(i=0; i<FUNC_LOGIC_TAB_NUM; i++)
  {
    /*�޹����л�------------------------------------------------------------------------*/
    if(*FuncLogicTab[i].pFuncHis == *FuncLogicTab[i].pFuncCur) 
    {
      continue;
    }

    /*�л����رչ���--------------------------------------------------------------------*/
    if(0 == *FuncLogicTab[i].pFuncCur) 
    {
      if(FuncLogicTab[i].pFuncSwitch != NULL)
      {
        /*�л������ڣ�����ʹ�� pFuncCur �� pFuncHis����һЩ��ز�������˱��뱣֤ pFuncCur ��ʵʱ�ԣ�
          �ڽ����л�ǰ����ؽ�pFuncCur���µ�����ֵ�����л��������ٽ�pFuncHis���µ���pFuncCurͬ����*/
        FuncLogicTab[i].pFuncSwitch(CLOSE, (FuncLogic_t*)&FuncLogicTab[i]);              /*�رղ���*/
      }
      *FuncLogicTab[i].pFuncHis = *FuncLogicTab[i].pFuncCur;
    }

    /*�л������¹���------------------------------------------------------------------*/
    else 
    {
      for(j=0; j<FUNC_LOGIC_TAB_NUM; j++)                                                /*�������飬�رճ�ͻ�Ĺ��ܣ��򱻸����ȼ��ĳ�ͻ���ر�*/
      {
        if(j == i)
        {
          continue;                                                                      /*����������ıȽ�*/
        }
         
        if((FuncLogicTab[j].MainComponent.All & FuncLogicTab[i].MainComponent.All) &&    /*������ ��ͻ*/
           (*FuncLogicTab[j].pFuncHis) > 0)                                              /*�� ��ͻ�� �й�����ִ����*/
        {
          /* �Ƚϳ�ͻ˫����ִ�����ȼ������ȼ��͵ı��رա�
           *���Ƹˡ��ֶ� �͡��Ƹˡ��Զ� �����ȼ����������Ĺ��ܵ͡�
           * ����Attr��� b6~b7 -- ִ�����ȼ� 0~3����ֵԽС�����ȼ�Խ�� */
          if(FuncLogicTab[i].Attr.Bit.Priority <= FuncLogicTab[j].Attr.Bit.Priority)
          {
            *FuncLogicTab[j].pFuncCur = 0;                                               /*���µ�����ֵ*/
            if(FuncLogicTab[j].pFuncSwitch != NULL)
            {
              FuncLogicTab[j].pFuncSwitch(CLOSE, (FuncLogic_t*)&FuncLogicTab[j]);        /*�رղ���*/
            }
            *FuncLogicTab[j].pFuncHis = *FuncLogicTab[j].pFuncCur;
          }
          else
          {
            *FuncLogicTab[i].pFuncCur = 0;                                               /*���µ�����ֵ*/
            if(FuncLogicTab[i].pFuncSwitch != NULL)
            {
              FuncLogicTab[i].pFuncSwitch(CLOSE, (FuncLogic_t*)&FuncLogicTab[i]);        /*�رղ���*/
            }
            *FuncLogicTab[i].pFuncHis = *FuncLogicTab[i].pFuncCur;
            break;                                                                       /*�������ȼ��Ĺر��ˣ�û��Ҫ�ٱȽ��ˣ�����ѭ��*/
          }
        }
      }

      if((FuncLogicTab[i].pFuncSwitch != NULL) &&                                        /*������Ч*/
         (FuncLogicTab[i].pFuncCur    != 0)    )                                         /*û�������ȼ��ĳ�ͻ���ر�*/
      {
        FuncLogicTab[i].pFuncSwitch(OPEN, (FuncLogic_t*)&FuncLogicTab[i]);               /*�򿪲���*/
        *FuncLogicTab[i].pFuncHis = *FuncLogicTab[i].pFuncCur;
      }
    }
  }
}

/*
************************************************************************************************************************
* �������� : MChair_FuncSwitch_CloseForNewFunc                                                                                                         
* �������� : �����л�  Ϊ�¹��ܵĿ��� �ر�ռ�õ���Դ
*            ע���رչ��ܣ��޹��ܣ�Ҳ���¹��ܣ�ͬ��Ҫ�л���ͬ��Ҫ�ر�ռ����Դ��                                                                                               
* ������� : pFuncLogic           -- �����߼�������
*            ActionTabAttrTab     -- ���� ����������� �ı��
*            ActionTabAttrTabNum  -- ���� ����������� �ı�� ����Ŀ����
*            pTabStep             -- ���ʹ�õĶ�������                                                                                      
* ���ز��� : �¹��ܶ���������� ��������
*            ����ֵINDEX_NO_MATCH -- ��ƥ�������    
*
* ����˵�� : 1������һ���°�Ħ����ʱ����Ҫ���ɹ���ռ�õĲ�����Դ�رա�
*               pFuncLogic �������Component �����˹���ʹ�õ���������Դ����о���������Ƹˣ���
*               ActionTabAttrTab �����ı����Ĳ��� RollerVibAccompanyBit �� 
*               LedHeatAccompanyBit �����˹���ʹ�õİ��沿����Դ�����֡��񶯡����ȡ��ƹ⣩�� 
*
*            2���ú�����Ҫ�� �Զ����� ���л������ڵ��á�
*               �ֶ�����һ���ڸ��ֵ��л������ڻ��е��������������
************************************************************************************************************************
*/
uint16_t MChair_FuncSwitch_CloseForNewFunc(FuncLogic_t *pFuncLogic, const ActionTabAttr_t ActionTabAttrTab[], uint8_t ActionTabAttrTabNum, ActionTabStep_t *pTabStep)
{
  uint16_t Index;
  uint8_t  i, j;
  const ActionTabAttr_t  *pActionTabAttrHis;                      /*�ɶ����� �����������*/
  const ActionTabAttr_t  *pActionTabAttrCur;                      /*�¶����� �����������*/


  /*�ر�������(��о ���� �Ƹ�)-----------------------------------------------*/
  if(pFuncLogic->MainComponent.Bit.Core)                          /*Ҫ�رջ�о����*/
  {
    MChair_TabHandle_ResetMixOtherTabStep(TRUE);                  /*��λ��о����������Ĵ�����*/
    Core_SetAction(CORE_ACTION_EXE_NONE, XYZ_ACTION_NONE, TCS_ACTION_NONE); 
    Core_SetXYZPosition(PXWIDE, PYTOP, PZBACK); 
    pMChair->CSFlag.Bit.FuncExeAngleNeedSet = TRUE;               /*��Ҫ���ù���ִ�нǶ�*/
    Core_ResetXYZActionStep();                                    /*�Զ������л�ʱ��������ɴ�������*/
  }

  if(pFuncLogic->MainComponent.Bit.Gas)                           /*�رճ�������*/
  {
    Gas_SetPumpSw(OFF);
    Gas_AllCtrlEn();                                              /*���в�λ��������ʹ��*/ 
    Gas_SetGasPart(0, 0);
    pMChair->GasIntensity = 3;                                    /*����ǿ��*/
  }

  /*Hzy-20171227:�����Ƕ�-->�û����Զ�����ʱ���ᵹִ�нǶ�-->�û��رջ��л���������ִ�нǶȻ�Ϊ��ɣ���Ӧֹͣ*/
  if((pFuncLogic->MainComponent.Bit.Spike)                   ||   /*�ر��Ƹ˹���*/
     (FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Core))    /*��о����״̬���Զ�  Hzy-20171227*/
  {
    Spike_SetLegFlexAngle(PLEGFLEX_MIN);                          /*�����Ƹ��������*/
    Spike_SetULegFlexAngle(PULEGFLEX_MAX);                        /*��С���쵽�*/
    if(FUNC_TYPE_AUTO == pFuncLogic->Attr.Bit.FuncType)           /*Ҫ�رյĹ��ܣ��Ƹ˹������Զ�*/
    {
      Spike_SetAngle(PKEEP, PKEEP, PKEEP);                        /*ֹͣ�Ƹ�*/
    }
  }

  /*���¹��ܵİ��湦�ܸ�ֵ�����֡��񶯡����ȡ��ƹ⣩-------------------------------------------------*/
  Index = INDEX_NO_MATCH;                                         /*�ȼ���û��ƥ��Ķ���������Ե�����*/

  if(ActionTabAttrTab != NULL)                                    /*�о���Ķ����������*/
  {
    pActionTabAttrHis = NULL;                                     /*�ɶ����� �����������*/
    pActionTabAttrCur = NULL;                                     /*�¶����� �����������*/
    
    /*��һ�Ħ���в�����ͬʱ����̫��ı���������ʹ�ñ������ҡ�����������������������forѭ����ʹ��˫����ҡ�*/
    for(i=0,j=(ActionTabAttrTabNum-1); i<ActionTabAttrTabNum; i++,j--)
    {
      if(*pFuncLogic->pFuncHis == ActionTabAttrTab[i].FuncID)
      {
        pActionTabAttrHis = &ActionTabAttrTab[i];
      }
      if(*pFuncLogic->pFuncCur == ActionTabAttrTab[j].FuncID)
      {
        pActionTabAttrCur = &ActionTabAttrTab[j];
        Index = j;                                                /*��¼�¶���������Ե�����*/
      }
      
      if((pActionTabAttrHis != NULL) && (pActionTabAttrCur != NULL) )
      {
        break;                                                    /*�¶����;ɶ����ı�񶼲�����ϣ�����ѭ��*/
      }
    }
  }

  if((pActionTabAttrHis != NULL) && (pActionTabAttrCur != NULL))  /*�¶����;ɶ����ı�����Զ�����*/
  {
    /*�����ΪNONE���򲻸�ֵ���������¹���Cur�İ���ģʽ��ֵ*/
    if((pActionTabAttrHis->FeetRollerMode != FUNC_NONE) ||        /*�Ź�*/
       (pActionTabAttrCur->FeetRollerMode != FUNC_NONE) )
    {
      MChair_RollerFuncReset_Feet();
      pMChair->FuncMA_Roller.Bit.Feet = pActionTabAttrCur->FeetRollerMode;  
    }
    if((pActionTabAttrHis->CalvesRollerMode != FUNC_NONE) ||      /*�ȹ�*/
       (pActionTabAttrCur->CalvesRollerMode != FUNC_NONE) )
    {
      MChair_RollerFuncReset_Calves();
      pMChair->FuncMA_Roller.Bit.Calves = pActionTabAttrCur->CalvesRollerMode;  
    }

    if((pActionTabAttrHis->FeetVibMode != FUNC_NONE) ||           /*�Ų���*/
       (pActionTabAttrCur->FeetVibMode != FUNC_NONE) )
    {
      MChair_VibFuncReset_Feet();
      pMChair->FuncMA_Vib.Bit.Feet = pActionTabAttrCur->FeetVibMode;           
    }
    if((pActionTabAttrHis->CalvesVibMode != FUNC_NONE) ||         /*�Ȳ���*/
       (pActionTabAttrCur->CalvesVibMode != FUNC_NONE) )
    {
      MChair_VibFuncReset_Calves();
      pMChair->FuncMA_Vib.Bit.Calves = pActionTabAttrCur->CalvesVibMode;           
    }
    if((pActionTabAttrHis->SeatVibMode != FUNC_NONE) ||           /*������*/
       (pActionTabAttrCur->SeatVibMode != FUNC_NONE) )
    {
      MChair_VibFuncReset_Seat();
      pMChair->FuncMA_Vib.Bit.Seat = pActionTabAttrCur->SeatVibMode;           
    }
    if((pActionTabAttrHis->LumbarBackVibMode != FUNC_NONE) ||     /*������*/
       (pActionTabAttrCur->LumbarBackVibMode != FUNC_NONE) )
    {
      MChair_VibFuncReset_LumbarBack();
      pMChair->FuncMA_Vib.Bit.LumbarBack = pActionTabAttrCur->LumbarBackVibMode;           
    }
    
    if((pActionTabAttrHis->FeetHeatMode != FUNC_NONE) ||          /*�Ų�����*/
       (pActionTabAttrCur->FeetHeatMode != FUNC_NONE) )
    {
      MChair_HeatFuncReset_Feet();
      pMChair->FuncMA_Heat.Bit.Feet = pActionTabAttrCur->FeetHeatMode ;       
    }
    
    if((pActionTabAttrHis->CalvesHeatMode != FUNC_NONE) ||        /*�Ȳ�����*/
       (pActionTabAttrCur->CalvesHeatMode != FUNC_NONE) )
    {
      MChair_HeatFuncReset_Calves();
      pMChair->FuncMA_Heat.Bit.Calves = pActionTabAttrCur->CalvesHeatMode ;       
    }
    if((pActionTabAttrHis->SeatHeatMode != FUNC_NONE) ||          /*��������*/
       (pActionTabAttrCur->SeatHeatMode != FUNC_NONE) )
    {
      MChair_HeatFuncReset_Seat();
      pMChair->FuncMA_Heat.Bit.Seat = pActionTabAttrCur->SeatHeatMode ;       
    }
    if((pActionTabAttrHis->LumbarBackHeatMode != FUNC_NONE) ||    /*��������*/
       (pActionTabAttrCur->LumbarBackHeatMode != FUNC_NONE) )
    {
      MChair_HeatFuncReset_LumbarBack();
      pMChair->FuncMA_Heat.Bit.LumbarBack = pActionTabAttrCur->LumbarBackHeatMode;        
    }
    
    if((pActionTabAttrHis->LedMode != FUNC_NONE) ||               /*������*/
       (pActionTabAttrCur->LedMode != FUNC_NONE) )
    {
      pMChair->FuncMA_Led.Bit.Led = pActionTabAttrCur->LedMode;             
    }
  }
  
  /*��λ�����-----------------------------------------------------------*/
  memset(pTabStep, 0, sizeof(ActionTabStep_t));
  if(pActionTabAttrCur != NULL)
  {
    pTabStep->Num = pActionTabAttrCur->StartStepNum;              /*����Ӧ��ִ�в������Ϊ���Ŀ�ʼ����*/
  }

  /*���������������¶���������Ե�����-------------------------------------*/
  return Index;
}


/*
************************************************************************************************************************
* �������� : MChair_FuncExeAngleHandle                                                                                                         
* �������� : ��Ħ����ִ�нǶȴ���                                                                                          
* ������� : ��                                                                                      
* ���ز��� : ��                                                                                               
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void MChair_FuncExeAngleHandle(Ticker_t ExePeriod)
{
  if(FALSE == pMChair->CSFlag.Bit.FuncExeAngleNeedSet)   /*�������ù���ִ�нǶ�*/
  {
    return;
  }
  
  if(FALSE == pMChair->StateBodyScan.Bit.Finish)          /*����ɨ��δ���*/
  {
    return;
  }

  /*���ó���ִ�г�ʼ�Ƕ�--------------------------------------------------------------------*/
  if(pMChair->FuncAuto_CoreGas)
  {
    pMChair->FuncAuto_Spike = FA_SPIKE_NONE;
    if((pMChair->FuncAuto_CoreGas == FA_COREGAS_Shiatsu)           ||
       (pMChair->FuncAuto_CoreGas == FA_COREGAS_Man)               ||
       (pMChair->FuncAuto_CoreGas == FA_COREGAS_ShoulderShiatsu)   ||
       (pMChair->FuncAuto_CoreGas == FA_COREGAS_LumbarButtockPress))
    {
      Spike_SetAngle(PBACK_ZERO2_ANGLE, PFEET_ZERO2_ANGLE, PZERO_EXE_ANGLE);  /*ִ�нǶ�*/
    }
    else if(pMChair->FuncAuto_CoreGas == FA_COREGAS_Relax)        
    {
      Spike_SetAngle(PBACK_EXE_ANGLE, PFEET_ZERO2_ANGLE, PZERO_EXE_ANGLE);    /*ִ�нǶ�*/
    }
    else
    {
      Spike_SetAngle(PBACK_EXE_ANGLE, PFEET_EXE_ANGLE, PZERO_EXE_ANGLE);  /*ִ�нǶ�*/
    }
    Spike_LegLenDetectRedo();                                           /*�Ƹ˽Ƕȿ���δ�䣬ǿ���ȳ����¼��*/
  }
  
  pMChair->CSFlag.Bit.FuncExeAngleNeedSet = FALSE;
}


/*
************************************************************************************************************************
* �������� : MChair_FuncExe                                                                                                         
* �������� : ��Ħ���ܵ�ִ��                                                                                             
* ������� : ��                                                                                      
* ���ز��� : ��                                                                                               
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void MChair_FuncExe(Ticker_t ExePeriod)
{
  uint8_t i;
  static uint8_t CorePauseOnOff = OFF;
  static uint8_t OtherPauseOnOff = OFF;

  
  /*������Ĵ���---------------------------------------------------*/
  BodyScan_Handle(ExePeriod);

  /*�Ƿ��ִ�б������ж�-------------------------------------------------*/
  if((pMChair->SysModeCur != SYS_MODE_STANDBY)     &&               /*ע�������£���ִ���Ƹ˵��ڹ���*/
     (pMChair->SysModeCur != SYS_MODE_USERRUN)     &&               /*������ģʽ��𲻴�*/ 
     (pMChair->SysModeCur != SYS_MODE_TESTNOTIMER) &&               /*����� SysMode_UserRun_Timer()�����д���*/
     (pMChair->SysModeCur != SYS_MODE_TESTAGE)     )
  {
    return;
  }

  if(TRUE == pMChair->CSFlag.Bit.Pause)
  {
    return;                                                         /*��ͣʱ����ִ�а�Ħ����*/
  }

  /*ִ��ǰ���Ƚ����߼��л�����-------------------------------------------*/
  MChair_FuncLogic_Switch();                                        /*�����߼��л�*/

  /*�������ܵ�ִ��-------------------------------------------------------*/
  /*����ִ��ǰ���������Ĺ���״̬�����ÿ��ִ�к����ڲ�������ʵ�������ֵ*/
  pMChair->ComponentFuncState.All = FUNC_TYPE_NONE;

  /*����ִ��ǰ�����һЩ��ʶ��ִ�к����ڽ�����ʵ�������ֵ*/
  pMChair->CSFlag.Bit.ZeroGravityAngleRun            = FALSE;       /*�������ڽǶ����б�ʶ*/
  pMChair->CSFlag.Bit.GasCooperateSpikeRun           = FALSE;       /*��������Ƹ����б�ʶ*/
  pMChair->CSFlag.Bit.BackSpikeMannualMoveDisable    = FALSE;       /*�����Ƹ��ֶ�*/
  pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable    = FALSE;       /*�������Ƹ��ֶ�*/
  pMChair->CSFlag.Bit.FeetSpikeMannualMoveDisable    = FALSE;       /*С���Ƹ��ֶ�*/
  pMChair->CSFlag.Bit.LegFlexMannualMoveDisable      = FALSE;       /*С�������ֶ�*/
  pMChair->CSFlag.Bit.ULegFlexMannualMoveDisable     = FALSE;       /*��С�������ֶ�*/
  pMChair->CSFlag.Bit.FeetHeatMannualOpDisable       = FALSE;       /*�Ų������ֶ�*/
  pMChair->CSFlag.Bit.CalvesHeatMannualOpDisable     = FALSE;       /*�Ȳ������ֶ�*/
  pMChair->CSFlag.Bit.SeatHeatMannualOpDisable       = FALSE;       /*���������ֶ�*/
  pMChair->CSFlag.Bit.LumbarBackHeatMannualOpDisable = FALSE;       /*���������ֶ�*/
  
  MChair_FuncExeAngleHandle(ExePeriod);                             /*��Ħ����ִ��ʱ�ĽǶȴ��� */

  for(i=0; i<FUNC_LOGIC_TAB_NUM; i++)
  {
    if(*FuncLogicTab[i].pFuncCur > 0)                               /*�й��ܱ��򿪵Ĳ�ִ��*/
    {
      if(FuncLogicTab[i].pFuncExe != NULL)
      {
        FuncLogicTab[i].pFuncExe(ExePeriod, (FuncLogic_t*)&FuncLogicTab[i]);
      }
    }
  }

  /*=====================ͨ�õĲ��䴦��==============================*/
  /* ��ͣ��ϵ����-----------------------------------------------------
   * ע�⣺�ɼܹ��У��Ի�о���ĸ�����Ƿֱ���ͣ�ġ�
   *       ���ھɼܹ���о�����ַ������֮�伸��ûʲô������������������ʲô���⡣
   *       �¼ܹ��еĻ�о��϶����ַ������֮�����λ�õȵĹ��������Բ�����ɼܹ������ֱ���ͣ������һ����ͣ��
   *       �������ֱ����ͣ��о��������ͣx��y��z��tap�ĸ�����������ѡ���Ե���ͣĳЩ��*/

  if(TRUE == pMChair->StateZeroSpike.Bit.Work)                      /*������������*/
  {
    PAUSE_ON(&CorePauseOnOff, 0, Core_PauseOn);
  }
  else
  {
    PAUSE_OFF(&CorePauseOnOff, 0, Core_PauseOff);
  }
  
//  if((TRUE == pMChair->StateBodyScan.Bit.Run)  &&                 /*ɨ��ʱ ���ڿ���λ��*/
//     (TRUE == pMChair->StateBackSpike.Bit.Work))
//  {
//    PAUSE_ON(&CorePauseOnOff, 1, Core_PauseOn);
//  }
//  else
//  {
//    PAUSE_OFF(&CorePauseOnOff, 1, Core_PauseOff);
//  }

  /*�ȳ���⿪��--------------------------------------------------------*/
  if(pMChair->ComponentFuncState.Bit.Spike != FUNC_TYPE_AUTO)       /*�Ƹ˹���״̬�����Զ�*/
  {
    Spike_SetLegLenDetectSw(ON);                                    
    if(TRUE == pMChair->StateSpike.Bit.LegLenDetectRun)             /*�ȳ����������*/
    {
      pMChair->CSFlag.Bit.LegFlexMannualMoveDisable  = TRUE;        /*С�������ֶ���Ч*/
    }
  }
  else
  {
    Spike_SetLegLenDetectSw(OFF);                                   /*�Ƹ��Զ����򣬲������ȳ��Զ����*/
  }
  
  /*���Ƚų��������⴦��--------------------------------------------*/
  if(FALSE == pMChair->CSFlag.Bit.GasCooperateSpikeRun)             /*�޳�������Ƹ˵Ķ���*/
  {
    if((TRUE == pMChair->StateZeroSpike.Bit.Work)        ||         /*������������*/
       //(TRUE == pMChair->StateBackSpike.Bit.Work)        ||         /*����������*/
       (TRUE == pMChair->StateFeetSpike.Bit.Work)        ||         /*С��������*/
       (TRUE == pMChair->StateLegFlexSpike.Bit.ULegWork) ||         /*С��������*/
       (TRUE == pMChair->StateBodyScan.Bit.Run)          ||         /*��������*/
       (TRUE == pMChair->StateLegFlexSpike.Bit.Work)     )          /*С��������*/
    {
      Gas_CalvesFeetCtrlEnOnly();                                   /*�Ƚų�������ʹ��*/    
      Gas_SetGasPart(0, 0);                                         /*���Ƚų���*/
    }
  }

  /*С�������У�ֹͣ�Ź��ȹ��˶�*/
  if((TRUE == pMChair->StateFeetSpike.Bit.Work)   ||                /*С��������*/
     (TRUE == pMChair->StateLegFlexSpike.Bit.Work))                 /*С��������*/
  {
    Roller_SetFeetRollerKeepAtInitPosition();
    PAUSE_ON(&OtherPauseOnOff, 1, Roller_CalvesRollerPauseOn);
  }
  else
  {
    Roller_ClrFeetRollerKeepAtInitPosition();
    PAUSE_OFF(&OtherPauseOnOff, 1, Roller_CalvesRollerPauseOff);
  }

  if(FALSE == pMChair->StateBodyScan.Bit.Finish)          /*����ɨ��δ���*/
  {
    PAUSE_ON(&OtherPauseOnOff, 2, Spike_LegLenDetectPauseOn);
  }
  else
  {
    PAUSE_OFF(&OtherPauseOnOff, 2, Spike_LegLenDetectPauseOff);
  }

  /*��о���粿ʱ������*/
  if((Core_GetYPosition() > PY02) && (Core_GetYPosition() < PY15))
  {
    if(FALSE == pMChair->CSFlag.Bit.GasCooperateSpikeRun)           /*�޳�������Ƹ˵Ķ���*/
    {
      Gas_ShoulderCtrlEnOnly();                                     /*�粿��������ʹ�ܣ�������λ���ƹر�*/      
      Gas_SetGasPart(0, 0);
    }
  }
  
  Gas_SetCalvesPressureThreshold(pMChair->GasIntensity);

  /*���湦�� ��ǿ�ƹر�---------------------------------------------*/
//  if(FUNC_TYPE_NONE == pMChair->ComponentFuncState.Bit.Core)
//  {
//    pMChair->FuncMA_Heat.Bit.LumbarBack = FMA_HEAT_NONE;            /*��о�޹��ܣ���رհ�Ħͷ���ȹ���*/
//    pMChair->CSFlag.Bit.LumbarBackHeatMannualOpDisable = TRUE;      /*���������ֶ���Ч*/
//  }

//  if((FUNC_TYPE_NONE == pMChair->ComponentFuncState.Bit.Core) &&
//     (FUNC_TYPE_NONE == pMChair->ComponentFuncState.Bit.Gas)  )
//  {
//    pMChair->FuncMA_Heat.Bit.Feet = FMA_HEAT_NONE;                  /*��о�ͳ������޹��ܣ���رսŲ����ȹ���*/
//    pMChair->CSFlag.Bit.FeetHeatMannualOpDisable = TRUE;            /*�Ų������ֶ���Ч*/
//    pMChair->FuncMA_Heat.Bit.Calves = FMA_HEAT_NONE;                /*��о�ͳ������޹��ܣ���ر��Ȳ����ȹ���*/
//    pMChair->CSFlag.Bit.CalvesHeatMannualOpDisable = TRUE;          /*�Ȳ��������ֶ���Ч*/
//  }
}
