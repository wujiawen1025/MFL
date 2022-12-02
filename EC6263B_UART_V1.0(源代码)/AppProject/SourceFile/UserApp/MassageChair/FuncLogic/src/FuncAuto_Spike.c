/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣ�FuncAuto_Spike.c 
**
**    ��������:���Ƹˡ��Զ�
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
static  uint8_t SpikeAutoNeedCloseAngle;    
static uint16_t        SpikeAutoTabIndex;
static ActionTabStep_t SpikeAutoStep;

static const ActionTabAttr_t   SpikeAutoAttrTab[] =
{
  /* �������Ƹ��Զ� �� �������Զ����ܴ���̫һ����
   * �������Ƹ��Զ� û�а��湦�ܣ�����ֻ�ǵ����ĵ����Ƹ˽Ƕȶ���(������)*/

  /*---------------------------------------------------------------*/
  { 
    FA_SPIKE_NONE,                                       /*����ID */
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
  
//  /*---------------------------------------------------------------*/
//  { 
//    FA_SPIKE_UserRun,                                    /*����ID */
//    (void*)SpikeAutoTab_UserRun,                         /*�������*/
//    0,                                                   /*��ʼ����*/
//    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
//    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
//    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
//    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
//    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
//    FMA_ROLLER_NONE,                                     /*�Ź� ����ģʽ*/
//    FMA_ROLLER_NONE,                                     /*�ȹ� ����ģʽ*/
//    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
//    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
//    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
//    FMA_HEAT_NONE,                                       /*������ ����ģʽ*/
//    FMA_LED_NONE                                         /*��   ����ģʽ*/
//  },
//  
//  /*---------------------------------------------------------------*/
//  { 
//    FA_SPIKE_ExeMassage,                                 /*����ID */
//    (void*)SpikeAutoTab_ExeMassage,                      /*�������*/
//    0,                                                   /*��ʼ����*/
//    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
//    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
//    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
//    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
//    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
//    FMA_ROLLER_NONE,                                     /*�Ź� ����ģʽ*/
//    FMA_ROLLER_NONE,                                     /*�ȹ� ����ģʽ*/
//    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
//    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
//    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
//    FMA_HEAT_NONE,                                       /*������ ����ģʽ*/
//    FMA_LED_NONE                                         /*��   ����ģʽ*/
//  },
 
  /*---------------------------------------------------------------*/
  { 
    FA_SPIKE_ZeroGravity1,                               /*����ID */
    (void*)SpikeAutoTab_ZeroGravity1,                    /*�������*/
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
  
  /*---------------------------------------------------------------*/
  { 
    FA_SPIKE_ZeroGravity2,                               /*����ID */
    (void*)SpikeAutoTab_ZeroGravity2,                    /*�������*/
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
  
  /*---------------------------------------------------------------*/
  { 
    FA_SPIKE_Home,                                       /*����ID */
    (void*)SpikeAutoTab_Home,                            /*�������*/
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
  
  /*����������--------����������--------����������--------����������*/
  { 
    FA_SPIKE_TRY,                                        /*����ID */
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

#define SPIKE_AUTO_TAB_NUM    TAB_NUM(SpikeAutoAttrTab)


/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : MChair_SetFuncAutoSpike                                                                                               
* �������� : ��Ħ�� �����Ƹ��Զ��Ĺ���                                                   
* ������� : FuncAutoSpike  --  Ҫ���õĹ���
*            NeedCloseAngle --  �Ƿ���Ҫ�رսǶȡ��ñ���ֻ�� FuncAutoSpike ΪFA_SPIKE_NONEʱ������Ч��
*                               ȡֵ��TRUE  -- ��Ҫ�رսǶȡ�
*                                     FALSE -- ����رսǶ�
* ���ز��� : ��                                                                                              
* ����˵�� : ��
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
  
  if(SpikeAutoNeedCloseAngle == TRUE)  /*��ʱ�������������Ѿ�ִ���꣬����ִ���л������е� ִ�нǶȣ�����ǿ��ִ��һ��*/
  {
    Spike_SetAngle(PBACK_EXE_ANGLE, PFEET_EXE_ANGLE, PZERO_EXE_ANGLE);  /*ִ�нǶ�*/
  }
}


/*
************************************************************************************************************************
* �������� : MChair_FuncSwitch_SpikeAuto                                                                                               
* �������� : ��Ħ�� �����л� ֮  ���Ƹˡ��Զ�                                                              
* ������� : SwitchMode -- Ҫ�л�ģʽ
*            pFuncLogic -- �����߼�������                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� :���Ƹˡ��Զ� һ�㶼���ڵ����������Ƕȵ��ڵȡ����С���о+�Ƹˡ���������+�Ƹˡ�������о+����+�Ƹˡ��ȳ�������ʱ��
*            �ǲ����Ա����Ƹˡ��Զ��л����硣����������������ļ�ֵ��������Ӧ������ص��߼��жϡ�
*            �� FuncLogic.c �ļ��е� FuncLogicTab ����ڶ� MChair.FuncAuto_Spike Ҳ�����˽ϵ͵����ȼ�����ֹ���е���������
************************************************************************************************************************
*/
void MChair_FuncSwitch_SpikeAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  SpikeAutoTabIndex = MChair_FuncSwitch_CloseForNewFunc(pFuncLogic, SpikeAutoAttrTab, SPIKE_AUTO_TAB_NUM, &SpikeAutoStep);

  if(SpikeAutoNeedCloseAngle == TRUE)
  {
    Spike_SetAngle(PBACK_EXE_ANGLE, PFEET_EXE_ANGLE, PZERO_EXE_ANGLE);  /*ִ�нǶ�*/
    SpikeAutoNeedCloseAngle = FALSE;
  }
}


/*
************************************************************************************************************************
* �������� : MChair_FuncExe_SpikeAuto                                                                                               
* �������� : ��Ħ�� ����ִ�� ֮  ���Ƹˡ��Զ�                                                           
* ������� : ExePeriod  -- ִ������
*            pFuncLogic -- ָ���������߼���ָ�롣                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_SpikeAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  if((0x00               == SpikeAutoTabIndex) ||   
     (INDEX_NO_MATCH     == SpikeAutoTabIndex) ||
     (SPIKE_AUTO_TAB_NUM <= SpikeAutoTabIndex) )
  {
    return;                                                  /*���������Ч�����޹���*/
  }
  
  SpikeAutoStep.AdditonOp.Bit.SingleExe = TRUE;              /*���Ƹˡ��Զ�ִֻ��һ�α��*/
  if(0 == SpikeAutoStep.TabRepeat)                           /*���Ƹˡ��Զ�ִֻ��һ�α��*/
  {
    pMChair->ComponentFuncState.Bit.Spike = FUNC_TYPE_AUTO;  /*�Ƹ˹���״̬���Զ�*/

    pMChair->CSFlag.Bit.ZeroGravityAngleRun = TRUE;          /*�������ڽǶ���*/
    pMChair->CSFlag.Bit.BackSpikeMannualMoveDisable = TRUE;  /*�����Ƹ��ֶ���Ч*/
    //pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable = TRUE;  /*�������Ƹ��ֶ���Ч*/
    pMChair->CSFlag.Bit.FeetSpikeMannualMoveDisable = TRUE;  /*С���Ƹ��ֶ���Ч*/
    pMChair->CSFlag.Bit.LegFlexMannualMoveDisable   = TRUE;  /*С�������ֶ���Ч*/

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
    /*�ں���MChair_FuncExe()�У�ִ�и�������ǰ�Ѿ������㣬���ﲻҪ���ˣ�ע�͵���*/
    //pMChair->ComponentFuncState.Bit.Spike = FUNC_TYPE_NONE; /*�Ƹ˹���״̬����*/
  }  
}

