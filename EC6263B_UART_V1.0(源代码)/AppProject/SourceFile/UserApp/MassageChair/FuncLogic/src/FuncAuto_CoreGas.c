/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣ�FuncAuto_CoreGas.c 
**
**    ��������:����о+�������Զ�
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
static uint16_t  CoreGasAutoTabIndex;
ActionTabStep_t  CoreGasAutoTabStep;

static const ActionTabAttr_t   CoreGasAutoArrtTab[] =
{
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_NONE,                                     /*����ID */
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
  
  /*============================ 0x01~0x2F   ����о�� ��� + �����������=====================================*/
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_Quick,                                    /*����ID */
    (void*)CoreMixOtherTab_Quick,                        /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_FEET_ROLLER_ByTime_On90s_Off90s,                 /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByTime_On90s_Off90s,               /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_Relax,                                    /*����ID */
    (void*)CoreMixOtherTab_Relax,                        /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_FEET_ROLLER_ByTime_On90s_Off90s,                 /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByTime_On90s_Off90s,               /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_MoveSleep,                                /*����ID */
    (void*)CoreMixOtherTab_MoveSleep,                    /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_ROLLER_NONE,                                     /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByTime_On90s_Off90s,               /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_Stretch,                                  /*����ID */
    (void*)CoreMixOtherTab_Stretch,                      /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_FEET_ROLLER_ByActionTab,                         /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByActionTab,                       /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_Scraping,                                 /*����ID */
    (void*)CoreMixOtherTab_Scraping,                     /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_FEET_ROLLER_ByTime_On120s_Off120s,               /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByTime_On120s_Off120s,             /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_Shiatsu,                                  /*����ID */
    (void*)CoreMixOtherTab_Shiatsu,                      /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_FEET_ROLLER_ByTime_On150s_Off120s,               /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByTime_On120s_Off120s,             /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_Lady,                                     /*����ID */
    (void*)CoreMixOtherTab_Lady,                         /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_FEET_ROLLER_ByTime_On90s_Off90s,                 /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByTime_On90s_Off90s,               /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_Man,                                      /*����ID */
    (void*)CoreMixOtherTab_Man,                          /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_FEET_ROLLER_ByTime_On90s_Off90s,                 /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByTime_On90s_Off90s,               /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_ShoulderRelax,                            /*����ID */
    (void*)CoreMixOtherTab_ShoulderRelax,                /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_FEET_ROLLER_ByTime_On90s_Off90s,                 /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByTime_On90s_Off90s,               /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_ShoulderRecovery,                         /*����ID */
    (void*)CoreMixOtherTab_ShoulderRecovery,             /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_FEET_ROLLER_ByTime_On150s_Off120s,               /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByTime_On150s_Off120s,             /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_ShoulderTuina,                            /*����ID */
    (void*)CoreMixOtherTab_ShoulderTuina,                /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_FEET_ROLLER_ByTime_On120s_Off120s,               /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByTime_On150s_Off120s,             /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_ShoulderShiatsu,                          /*����ID */
    (void*)CoreMixOtherTab_ShoulderShiatsu,              /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_FEET_ROLLER_ByTime_On150s_Off120s,               /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByTime_On150s_Off120s,             /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_LumbarButtockRelax,                       /*����ID */
    (void*)CoreMixOtherTab_LumbarButtockRelax,           /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_FEET_ROLLER_ByTime_On90s_Off90s,                 /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByTime_On90s_Off90s,               /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_LumbarButtockRecovery,                    /*����ID */
    (void*)CoreMixOtherTab_LumbarButtockRecovery,        /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_FEET_ROLLER_ByTime_On150s_Off120s,               /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByTime_On150s_Off120s,             /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_LumbarButtockPress,                       /*����ID */
    (void*)CoreMixOtherTab_LumbarButtockPress,           /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_FEET_ROLLER_ByTime_On150s_Off120s,               /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByTime_On150s_Off120s,             /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
  /*----------------------------------------------------------------------------------------------------------*/
  { 
    FA_COREGAS_LumbarKidneyCare,                         /*����ID */
    (void*)CoreMixOtherTab_LumbarKidneyCare,             /*�������*/
    0,                                                   /*��ʼ����*/
    ACTION_TAB_STEP_NUM_MAX,                             /*��������*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*���� ����ģʽ*/
    FMA_VIB_NONE,                                        /*������ ����ģʽ*/
    FMA_FEET_ROLLER_ByTime_On150s_Off120s,               /*�Ź� ����ģʽ*/
    FMA_CALVES_ROLLER_ByTime_On150s_Off120s,             /*�ȹ� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_HEAT_NONE,                                       /*���� ����ģʽ*/
    FMA_LUMBARBACK_HEAT_ByTime_OnAlways,                 /*������ ����ģʽ*/
    FMA_LED_NONE                                         /*��   ����ģʽ*/
  },
  
  /*============================ 0x30~0x05F   ����о+���� ����� =============================================*/

  /*����������--------����������--------����������--------����������*/
  { 
    FA_COREGAS_TRY,                                      /*����ID */
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


#define COREGAS_AUTO_TAB_NUM    TAB_NUM(CoreGasAutoArrtTab)


/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : MChair_FuncSwitch_CoreGasAuto                                                                                                
* �������� : ��Ħ�� �����л� ֮  ����о+�������Զ�                                                      
* ������� : SwitchMode -- Ҫ�л�ģʽ
*            pFuncLogic -- �����߼�������                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_CoreGasAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  CoreGasAutoTabIndex = MChair_FuncSwitch_CloseForNewFunc(pFuncLogic, CoreGasAutoArrtTab, COREGAS_AUTO_TAB_NUM, &CoreGasAutoTabStep);
}

/*
************************************************************************************************************************
* �������� : MChair_FuncExe_CoreGasAuto                                                                                           
* �������� : ��Ħ�� ����ִ�� ֮  ����о+�������Զ�                                                       
* ������� : ExePeriod  -- ִ������
*            pFuncLogic -- ָ���������߼���ָ�롣                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_CoreGasAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  if((0x00                 == CoreGasAutoTabIndex) ||   
     (INDEX_NO_MATCH       == CoreGasAutoTabIndex) ||
     (COREGAS_AUTO_TAB_NUM <= CoreGasAutoTabIndex) )
  {
    return;                                               /*���������Ч�����޹���*/
  }

  pMChair->ComponentFuncState.Bit.Core = FUNC_TYPE_AUTO;  /*��о����״̬���Զ�*/
  pMChair->ComponentFuncState.Bit.Gas = FUNC_TYPE_AUTO;   /*��������״̬���Զ�*/

  if(FALSE == pMChair->StateBodyScan.Bit.Finish)          /*����ɨ��δ���*/
  {
    return;
  }
  
  Gas_AllCtrlEn();                                        /*�������в�λ�ĳ���*/

  if(pMChair->FuncAuto_CoreGas < 0x30)                    /*0x01~0x2F   ����о�� ��� + �����������*/
  {
    MChair_TabHandle_CoreMixOtherAuto(ExePeriod, (ActionTabAttr_t *)&CoreGasAutoArrtTab[CoreGasAutoTabIndex], &CoreGasAutoTabStep);
  }
  else                                                    /*0x30~0x05F   ����о+���� �����*/
  {
    MChair_TabHandle_CoreGasAuto(ExePeriod, (ActionTabAttr_t *)&CoreGasAutoArrtTab[CoreGasAutoTabIndex], &CoreGasAutoTabStep);
  }
}

