/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣ�FuncMA_Heat.c 
**
**    ��������:�����ȡ��ֶ��Զ�
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
#include "FuncTab.h"
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
static const uint16_t   HeatCtrlOnOffTimeTab[][2] = 
{
  {100,  0},    /*����*/

  {180,  60},
  {120,  180},
  {300,  60},

  {0,    100}   /*����*/
};

/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : MChair_HeatFuncReset_Feet                                                                                               
* �������� : MChair_HeatFuncReset_Calves                                                                                               
* �������� : MChair_HeatFuncReset_Seat                                                                                               
* �������� : MChair_HeatFuncReset_LumbarBack                                                                                               
* �������� : ��Ħ�� ���ȹ��� ��λ                                                               
* ������� : ��                                                                                
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_HeatFuncReset_Feet(void)
{
  pMChair->FeetHeatCtrlOnOffTime = 0;
  pMChair->FeetHeatCtrlSw = OFF;
  Heat_SetFeetHeatWorkState(FALSE);  
}

void MChair_HeatFuncReset_Calves(void)
{
  pMChair->CalvesHeatCtrlOnOffTime = 0;
  pMChair->CalvesHeatCtrlSw = OFF;
  Heat_SetCalvesHeatWorkState(FALSE);  
}

void MChair_HeatFuncReset_Seat(void)
{
  pMChair->SeatHeatCtrlOnOffTime = 0;
  pMChair->SeatHeatCtrlSw = OFF;
  Heat_SetSeatHeatWorkState(FALSE);  
}

void MChair_HeatFuncReset_LumbarBack(void)
{
  pMChair->LumbarBackHeatCtrlOnOffTime = 0;
  pMChair->LumbarBackHeatCtrlSw = OFF;
  Heat_SetLumbarBackHeatWorkState(FALSE);  
}

/*
************************************************************************************************************************
* �������� : MChair_FuncSwitch_HeatMA                                                                                               
* �������� : ��Ħ�� �����л� ֮  �����ȡ��ֶ��Զ�                                                                   
* ������� : SwitchMode -- Ҫ�л�ģʽ
*            pFuncLogic -- �����߼�������                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_HeatMA(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  HeatAction_t   HeatActionCur;
  HeatAction_t   HeatActionHis;

  HeatActionCur.All = *pFuncLogic->pFuncCur;
  HeatActionHis.All = *pFuncLogic->pFuncHis;
  
  if((HeatActionCur.Bit.Feet != HeatActionHis.Bit.Feet) || (CLOSE == SwitchMode)) 
  {
    MChair_HeatFuncReset_Feet();
  }
  
  if((HeatActionCur.Bit.Calves != HeatActionHis.Bit.Calves) || (CLOSE == SwitchMode)) 
  {
    MChair_HeatFuncReset_Calves();
  }
  
  if((HeatActionCur.Bit.Seat != HeatActionHis.Bit.Seat) || (CLOSE == SwitchMode)) 
  {
    MChair_HeatFuncReset_Seat();
  }

  if((HeatActionCur.Bit.LumbarBack != HeatActionHis.Bit.LumbarBack) || (CLOSE == SwitchMode))
  {
    MChair_HeatFuncReset_LumbarBack();
  }
}
/*
************************************************************************************************************************
* �������� : MChair_FuncExe_HeatMA                                                                                               
* �������� : ��Ħ�� ����ִ�� ֮  �����ȡ��ֶ��Զ�                                                                   
* ������� : ExePeriod  -- ִ������
*            pFuncLogic -- ָ���������߼���ָ�롣                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_HeatMA(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  uint16_t OnTime;
  uint16_t OffTime;


  switch(pMChair->FuncMA_Heat.Bit.Calves)
  {
    case FMA_HEAT_NONE:
    {
      pMChair->CalvesHeatCtrlSw = OFF;
    }break;

    case FMA_CALVES_HEAT_Mannual:         /*�ֶ����򳣿�*/
    {
      pMChair->ComponentFuncState.Bit.CalvesHeat = FUNC_TYPE_MANNUALAUTO; /*����״̬���ֶ��Զ�*/

      pMChair->CalvesHeatCtrlSw = ON;
    }break;

    case FMA_CALVES_HEAT_ByActionTab:    /*�ɱ���ڵ�ֵ�����ƣ���ActionObjHandle_AccompanyFunc()����*/
    {
      pMChair->ComponentFuncState.Bit.CalvesHeat = FUNC_TYPE_MANNUALAUTO; /*����״̬���ֶ��Զ�*/
    }break;

    case FMA_CALVES_HEAT_ByTime_OnAlways:    /*��ʱ�����*/
    case FMA_CALVES_HEAT_ByTime_On180s_Off60s:
    case FMA_CALVES_HEAT_ByTime_On120s_Off180s:
    case FMA_CALVES_HEAT_ByTime_On300s_Off60s:
    {
      pMChair->ComponentFuncState.Bit.CalvesHeat = FUNC_TYPE_MANNUALAUTO; /*����״̬���ֶ��Զ�*/

      pMChair->CalvesHeatCtrlOnOffTime += ExePeriod;
      OnTime  = HeatCtrlOnOffTimeTab[pMChair->FuncMA_Heat.Bit.Calves - FMA_CALVES_HEAT_ByTime_OnAlways][0];
      OffTime = OnTime + HeatCtrlOnOffTimeTab[pMChair->FuncMA_Heat.Bit.Calves - FMA_CALVES_HEAT_ByTime_OnAlways][1];
      if(pMChair->CalvesHeatCtrlOnOffTime/1000 < OnTime) 
      {
        pMChair->CalvesHeatCtrlSw = ON;
      }
      else if(pMChair->CalvesHeatCtrlOnOffTime/1000 < OffTime)
      {
        pMChair->CalvesHeatCtrlSw = OFF;
      }
      else
      {
        pMChair->CalvesHeatCtrlOnOffTime = 0;
      }
    }break;

    default:
    {
      pMChair->FuncMA_Heat.Bit.Calves = FMA_HEAT_NONE;
    }break;
  }
  Heat_SetCalvesHeatWorkState((ON == pMChair->CalvesHeatCtrlSw) ? TRUE:FALSE);  

  
  /*--------------------------------------------------------------------------------------------------*/
  if(pMChair->FuncMA_Heat.Bit.Feet != FMA_HEAT_NONE)
  {
    pMChair->ComponentFuncState.Bit.FeetHeat = FUNC_TYPE_MANNUALAUTO; /*����״̬���ֶ��Զ�*/
    Heat_SetFeetHeatWorkState(TRUE);  
  }
  else
  {
    Heat_SetFeetHeatWorkState(FALSE);  
  }

  /*--------------------------------------------------------------------------------------------------*/
//  if(pMChair->FuncMA_Heat.Bit.Calves != FMA_HEAT_NONE)
//  {
//    pMChair->ComponentFuncState.Bit.CalvesHeat = FUNC_TYPE_MANNUALAUTO; /*����״̬���ֶ��Զ�*/

//    Heat_SetCalvesHeatWorkState(TRUE);  
//  }
//  else
//  {
//    Heat_SetCalvesHeatWorkState(FALSE);  
//  }
  
  /*--------------------------------------------------------------------------------------------------*/
  if(pMChair->FuncMA_Heat.Bit.LumbarBack != FMA_HEAT_NONE)
  {
    pMChair->ComponentFuncState.Bit.LumbarBackHeat = FUNC_TYPE_MANNUALAUTO; /*����״̬���ֶ��Զ�*/
    pMChair->LumbarBackHeatCtrlSw = ON;
  }
  else
  {
    pMChair->LumbarBackHeatCtrlSw = OFF;
  }
  Heat_SetLumbarBackHeatWorkState((ON == pMChair->LumbarBackHeatCtrlSw) ? TRUE:FALSE);  
}

