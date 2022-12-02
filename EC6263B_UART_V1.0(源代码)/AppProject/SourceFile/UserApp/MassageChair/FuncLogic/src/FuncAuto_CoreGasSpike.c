/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣ�FuncAuto_CoreGasSpike.c 
**
**    ��������:����о+����+�Ƹˡ��Զ�
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
static uint16_t        CoreGasSpikeAutoTabIndex;
static ActionTabStep_t CoreGasSpikeAutoTabStep;

static const ActionTabAttr_t   CoreGasSpikeAutoAttrTab[] =
{
  /*RollerVibAccompanyBit ��&��������� �� b0 ������  b1 ������   b4 �Ź� */
  /*LedHeatAccompanyBit   ��&�Ȱ������� �� b0 ��������  b1 �Ų����� */

  /*---------------------------------------------------------------*/
  { 
    FA_COREGASSPIKE_NONE,                                /*����ID */
    (void*)0,                                            /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_ROLLER_NONE,                                     /*�Ź� ����ģʽ*/
    FMA_ROLLER_NONE,                                     /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
//  /*----------------------------------------------------------------------------------------------------------*/
//  { 
//    FA_COREGASSPIKE_Thai,                                /*����ID */
//    (void*)CoreGasSpikeAutoTab_Thai,                     /*�������*/
//    0,                                                   /*��ʼ����*/
//    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
//    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
//    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
//    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
//    FMA_LUMBARBACK_VIB_ByActionTab,                      /*������ ����ģʽ*/
//    FMA_FEET_ROLLER_ByTime_On150s_Off120s,               /*�Ź� ����ģʽ*/
//    FMA_CALVES_ROLLER_ByTime_On90s_Off120s,              /*�ȹ� ����ģʽ*/
//    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
//    FMA_CALVES_HEAT_ByTime_On120s_Off180s,               /*���� ����ģʽ*/
//    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
//    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
//    FMA_LED_NONE                                         /*��   ����ģʽ*/
//  },
  
  /*����������--------����������--------����������--------����������*/
  { 
    FA_COREGASSPIKE_TRY,                                 /*����ID */
    (void*)0,                                            /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_FEET_VIB_ByActionTab,                            /*���� ����ģʽ*/
    FMA_CALVES_VIB_ByActionTab,                          /*���� ����ģʽ*/
    FMA_SEAT_VIB_ByActionTab,                            /*���� ����ģʽ*/
    FMA_LUMBARBACK_VIB_ByActionTab,                      /*������ ����ģʽ*/
    FMA_FEET_ROLLER_ByActionTab,                         /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByActionTab,                       /*�ȹ� ����ģʽ*/
    FMA_FEET_HEAT_ByActionTab,                           /*���� ����ģʽ*/
    FMA_CALVES_HEAT_ByActionTab,                         /*���� ����ģʽ*/
    FMA_SEAT_HEAT_ByActionTab,                           /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByActionTab,                     /*������ ����ģʽ*/
    FMA_LED_ByActionTab                                  /*��   ����ģʽ*/
  }
};


#define COREGASSPIKE_AUTO_TAB_NUM    TAB_NUM(CoreGasSpikeAutoAttrTab)


/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : MChair_FuncSwitch_CoreGasSpikeAuto                                                                                                
* �������� : ��Ħ�� �����л� ֮  ����о+����+�Ƹˡ��Զ�                                                      
* ������� : SwitchMode -- Ҫ�л�ģʽ
*            pFuncLogic -- �����߼�������                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_CoreGasSpikeAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  CoreGasSpikeAutoTabIndex = MChair_FuncSwitch_CloseForNewFunc(pFuncLogic, CoreGasSpikeAutoAttrTab, COREGASSPIKE_AUTO_TAB_NUM, &CoreGasSpikeAutoTabStep);
  if(CLOSE == SwitchMode)
  {
    Spike_SetAngle(PBACK_USER_ANGLE, PFEET_USER_ANGLE, PZERO_USER_ANGLE);  /*�����Ƕ�*/
  }
}

/*
************************************************************************************************************************
* �������� : MChair_FuncExe_CoreGasSpikeAuto                                                                                           
* �������� : ��Ħ�� ����ִ�� ֮  ����о+����+�Ƹˡ��Զ�                                                       
* ������� : ExePeriod  -- ִ������
*            pFuncLogic -- ָ���������߼���ָ�롣                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_CoreGasSpikeAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  if((0x00                      == CoreGasSpikeAutoTabIndex) ||   
     (INDEX_NO_MATCH            == CoreGasSpikeAutoTabIndex) ||
     (COREGASSPIKE_AUTO_TAB_NUM <= CoreGasSpikeAutoTabIndex) )
  {
    return;                                                /*���������Ч�����޹���*/
  }

  pMChair->ComponentFuncState.Bit.Core  = FUNC_TYPE_AUTO;  /*��о����״̬���Զ�*/
  pMChair->ComponentFuncState.Bit.Gas   = FUNC_TYPE_AUTO;  /*��������״̬���Զ�*/
  pMChair->ComponentFuncState.Bit.Spike = FUNC_TYPE_AUTO;  /*�Ƹ˹���״̬���Զ�*/

  if(FALSE == pMChair->StateBodyScan.Bit.Finish)           /*����ɨ��δ���*/
  {
    return;
  }

  pMChair->CSFlag.Bit.BackSpikeMannualMoveDisable = TRUE;  /*�����Ƹ��ֶ���Ч*/
  pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable = TRUE;  /*�������Ƹ��ֶ���Ч*/
  pMChair->CSFlag.Bit.FeetSpikeMannualMoveDisable = TRUE;  /*С���Ƹ��ֶ���Ч*/
  pMChair->CSFlag.Bit.LegFlexMannualMoveDisable   = TRUE;  /*С�������ֶ���Ч*/
  pMChair->CSFlag.Bit.GasCooperateSpikeRun        = TRUE;  /*�г�������Ƹ˵Ķ���*/

  Gas_AllCtrlEn();                                         /*�������в�λ�ĳ���*/
  MChair_TabHandle_CoreGasSpikeAuto(ExePeriod, (ActionTabAttr_t *)&CoreGasSpikeAutoAttrTab[CoreGasSpikeAutoTabIndex], &CoreGasSpikeAutoTabStep);
}
