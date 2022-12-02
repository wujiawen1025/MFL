/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣ�FuncAuto_GridCombo.c 
**
**    ��������:��������ϡ��Զ���С�Ͷ�ʱ����о���Զ���������ִ�С�
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
static const void*  GridComboActionTab[] = /* ��ɹ���Ķ������Ŀǰ���4*8=32 */
{
  /*����----------------------------------*/
  (void*)GridComboTab_NeckShoulder_1,
  (void*)GridComboTab_NeckShoulder_2,
  (void*)GridComboTab_NeckShoulder_3,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,

  /*����----------------------------------*/
  (void*)GridComboTab_Back_1,
  (void*)GridComboTab_Back_2,
  (void*)GridComboTab_Back_3,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,

  /*����----------------------------------*/
  (void*)GridComboTab_Lumbar_1,
  (void*)GridComboTab_Lumbar_2,
  (void*)GridComboTab_Lumbar_3,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,
  (void*)NULL,

  /*�β�----------------------------------*/
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


static uint8_t    GridComboSelectBit[4];          /*��������ϡ�ѡ��λ*/    
#define  GRIDCOMBO_SELECT_BYTE_NUM    TAB_NUM(GridComboSelectBit)

static uint16_t   GridComboAutoRunTabIndex;       /*��������ϡ����б������*/  

static ActionTabStep_t   GridComboAutoTabStep;

static ActionTabAttr_t   GridAutoDynAttr;          /*��������ϡ���̬����*/


static const ActionTabAttr_t   GridAutoAttrTab[] =
{
  /* ��������ϡ� �� �������Զ����ܴ���̫һ����
   * ��������ϡ� û�а��湦�ܣ����еİ��湦�ܶ��Ƕ������������ӵġ�*/

  /*---------------------------------------------------------------*/
  { 
    FA_GRIDCOMBO_NONE,                                   /*����ID */
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

  /*---------------------------------------------------------------*/
  { 
    FA_GRIDCOMBO_ON,                                     /*����ID */
    (void*)NULL,                                         /*�������*/
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
  }
};

#define GRID_AUTO_TAB_NUM    TAB_NUM(GridAutoAttrTab)


/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : GridComboAuto_UpdateComboSelectBit                                                                                                
* �������� : ���¡�������ϡ������ѡ��λ                                                      
* ������� : pBit -- ָ����λ
* ���ز��� : ��                                                                                              
* ����˵�� : SUCCESS -- ���³ɹ�   
*            FAIL    -- û�����仯������Ҫ����                                                           
************************************************************************************************************************
*/
uint8_t GridComboAuto_UpdateComboSelectBit(uint8_t  *pBit)
{
  uint8_t i;
  uint8_t TBit;
  uint8_t Change;


  /*�ж�ѡ��λ�Ƿ����仯--------------------------------*/
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

  /*ѡ��λ�����仯�Ÿ���----------------------------------*/
  pMChair->FuncAuto_GridCombo = FA_GRIDCOMBO_NONE;            /*�ȼ��� ��������ϡ�������Ч*/
  GridComboAutoRunTabIndex = 0;
  memset(&GridComboAutoTabStep, 0, sizeof(ActionTabStep_t));

  for(i=0; i<GRIDCOMBO_SELECT_BYTE_NUM; i++)
  {
    GridComboSelectBit[i] = pBit[i];

    if((GridComboSelectBit[i] > 0)                           &&  /*����Ӧ�ĳ��򱻿���*/
       (FA_GRIDCOMBO_NONE == pMChair->FuncAuto_GridCombo) )   /*��������ϡ�������δ����*/
    {
      for(TBit=0; TBit<8; TBit++)
      {
        if(GridComboSelectBit[i] & (1<<TBit))
        {
          GridComboAutoRunTabIndex = (i<<3) + TBit;              /*�������һ��������������*/
          break;
        }
      }

      pMChair->FuncAuto_GridCombo = FA_GRIDCOMBO_ON;          /*��������ϡ�������*/
    }
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : GridComboAuto_CalNextRunTabIndex                                                                                           
* �������� : ���㡾������ϡ���һ����Ҫִ�еĶ�����������                                                       
* ������� : ��                                                                                     
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
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
* �������� : GridComboAuto_GetNeckShoulderSelectBit                                                                                            
* �������� : ��ȡ��ǰ��������ϡ������ѡ��λ                                                       
* ������� : ��                                                                             
* ���ز��� : �����ѡ��λ                                                                                                         
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
uint8_t GridComboAuto_GetNeckShoulderSelectBit(void)
{
  return GridComboSelectBit[0];
}

/*
************************************************************************************************************************
* �������� : GridComboAuto_GetBacSelectkBit                                                                                           
* �������� : ��ȡ��ǰ��������ϡ�������ѡ��λ                                                       
* ������� : ��                                                                                
* ���ز��� : ������ѡ��λ                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
uint8_t GridComboAuto_GetBackSelectBit(void)
{
  return GridComboSelectBit[1];
}

/*
************************************************************************************************************************
* �������� : GridComboAuto_GetLumbarSelectBit                                                                                           
* �������� : ��ȡ��ǰ��������ϡ�������ѡ��λ                                                       
* ������� : ��                                                                                 
* ���ز��� : ������ѡ��λ                                                                                               
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
uint8_t GridComboAuto_GetLumbarSelectBit(void)
{
  return GridComboSelectBit[2];
}

/*
************************************************************************************************************************
* �������� : GridComboAuto_GetButtocksSelectBit                                                                                           
* �������� : ��ȡ��ǰ��������ϡ��β���ѡ��λ                                                       
* ������� : ��                                                                                  
* ���ز��� : �β���ѡ��λ                                                                                               
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
uint8_t GridComboAuto_GetButtocksSelectBit(void)
{
  return GridComboSelectBit[3];
}

/*
************************************************************************************************************************
* �������� : GridComboAuto_GetCurRunTabIndex                                                                                           
* �������� : ��ȡ��ǰ��������ϡ����б�������                                                      
* ������� : ��                                                                                  
* ���ز��� :     0 -- ��Ч������������������ϡ�δ������
*            ����0 -- ��ǰ����ִ�еĹ������������±��1��ʼ����                                                                                              
* ����˵�� : ��                                                           
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
    /*EC-P388A Ϊ9��������������9���񷵻�����ֵ*/
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
* �������� : MChair_FuncSwitch_GridComboAuto                                                                                           
* �������� : ��Ħ�� �����л� ֮  ��������ϡ��Զ�                                                       
* ������� : SwitchMode -- Ҫ�л�ģʽ
*            pFuncLogic -- �����߼�������                                                                          
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_GridComboAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  if(CLOSE == SwitchMode)
  {
    pMChair->FuncAuto_GridCombo = FA_GRIDCOMBO_NONE;   /*��������ϡ�������Ч*/
    GridComboAutoRunTabIndex = 0;
    memset(GridComboSelectBit, 0, GRIDCOMBO_SELECT_BYTE_NUM);
  }

  MChair_FuncSwitch_CloseForNewFunc(pFuncLogic, GridAutoAttrTab, GRID_AUTO_TAB_NUM, &GridComboAutoTabStep);
}

/*
************************************************************************************************************************
* �������� : MChair_FuncExe_GridComboAuto                                                                                           
* �������� : ��Ħ�� ����ִ�� ֮  ��������ϡ��Զ�                                                       
* ������� : ExePeriod  -- ִ������
*            pFuncLogic -- ָ���������߼���ָ�롣                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_GridComboAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  if(pMChair->FuncAuto_GridCombo != FA_GRIDCOMBO_ON)  /*�������δ����*/
  {
    return;
  }

  pMChair->ComponentFuncState.Bit.Core = FUNC_TYPE_AUTO;    /*��о����״̬���Զ�*/
  if(FALSE == pMChair->StateBodyScan.Bit.Finish)            /*����ɨ��δ���*/
  {
    return;
  }

  /*��������ϡ� �Ķ���������û����ѡ��ģ���������ö�̬���ԣ���̬�ظ��¶����������*/
  memcpy(&GridAutoDynAttr, (ActionTabAttr_t *)&GridAutoAttrTab[1], sizeof(ActionTabAttr_t));
  GridAutoDynAttr.pActionTab = (void*)GridComboActionTab[GridComboAutoRunTabIndex]; /*��ȡ�������*/
  if(NULL == GridAutoDynAttr.pActionTab) 
  {
    GridComboAuto_CalNextRunTabIndex();                  /*���������Ч���������һ��ִ�б�������*/
    return;
  }

  MChair_TabHandle_CoreMixOtherAuto(ExePeriod, &GridAutoDynAttr, &GridComboAutoTabStep);

  if(GridComboAutoTabStep.TabRepeat > 0) 
  {
    GridComboAuto_CalNextRunTabIndex();                  /*���ִ����һ�飬�������һ��ִ�б�������*/
  }
}

