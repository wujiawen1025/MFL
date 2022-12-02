/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣ�FuncMannual_Gas.c 
**
**    ��������:���������ֶ�
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
  /*���������ֶ� ���Զ���ID*/

  /*0---------------------------------------------------------------*/
  { 
    0,                                                   /*����ID */
    (void*)GasTab_Calves,                                /*�������*/
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

  /*1---------------------------------------------------------------*/
  { 
    0,                                                   /*����ID */
    (void*)GasTab_LumbarSeat,                            /*�������*/
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
  
  /*2---------------------------------------------------------------*/
  { 
    0,                                                   /*����ID */
    (void*)GasTab_Arms,                                  /*�������*/
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
  
  /*3---------------------------------------------------------------*/
  { 
    0,                                                   /*����ID */
    (void*)GasTab_Shoulder,                              /*�������*/
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


/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : MChair_FuncSwitch_GasMannual                                                                                               
* �������� : ��Ħ�� �����л� ֮  ���������ֶ�                                                                              
* ������� : SwitchMode -- Ҫ�л�ģʽ
*            pFuncLogic -- �����߼�������                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_GasMannual(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  GasAction_t  GasHis; 
  GasAction_t  GasCur; 


  GasHis.All = *pFuncLogic->pFuncHis;
  GasCur.All = *pFuncLogic->pFuncCur;

  if(OPEN == SwitchMode)                   /*�򿪲��������˸���*/
  {
    if(GasHis.Bit.Calves != GasCur.Bit.Calves)
    {
      Gas_CalvesCtrlEnOnly();              /*�ȳ�������ʹ�ܣ�������λ���ƹر�*/     
      Gas_SetGasPart(0, 0);
      memset(&GasCalvesStep, 0, sizeof(ActionTabStep_t));
    }

    if(GasHis.Bit.LumbarSeat != GasCur.Bit.LumbarSeat)
    {
      Gas_LumbarSeatCtrlEnOnly();          /*������������ʹ�ܣ�������λ���ƹر�*/       
      Gas_SetGasPart(0, 0);
      memset(&GasLumbarSeatStep, 0, sizeof(ActionTabStep_t));
    }

    if(GasHis.Bit.Arms != GasCur.Bit.Arms)
    {
      Gas_ArmsCtrlEnOnly();                /*�ֱ۳�������ʹ�ܣ�������λ���ƹر�*/        
      Gas_SetGasPart(0, 0);
      memset(&GasArmsStep, 0, sizeof(ActionTabStep_t));
    }

    if(GasHis.Bit.Shoulder != GasCur.Bit.Shoulder)
    {
      Gas_ShoulderCtrlEnOnly();            /*�粿��������ʹ�ܣ�������λ���ƹر�*/      
      Gas_SetGasPart(0, 0);
      memset(&GasShoulderStep, 0, sizeof(ActionTabStep_t));
    }
  }
  else// if(CLOSE == SwitchMode)           /*�رղ�������ȫ����*/
  {
    Gas_SetPumpSw(OFF);
    Gas_AllCtrlEn();                       /*���в�λ��������ʹ��*/ 
    Gas_SetGasPart(0, 0);
    
    if(pMChair->FuncMA_Roller.Bit.Calves != FMA_CALVES_ROLLER_Mannual)   /*�޳��� �� С�ȼ�����ֶ� ��ָ�Ĭ��ǿ��*/
    {
      pMChair->GasIntensity = 3;             /*����ǿ��*/
    }
  }
}

/*
************************************************************************************************************************
* �������� : MChair_FuncExe_GasMannual                                                                                               
* �������� : ��Ħ�� ����ִ�� ֮  ���������ֶ�                                                                              
* ������� : ExePeriod  -- ִ������
*            pFuncLogic -- ָ���������߼���ָ�롣                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_GasMannual(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  GasAction_t  GasCur; 

  pMChair->ComponentFuncState.Bit.Gas = FUNC_TYPE_MANNUAL;   /*��������״̬���ֶ�*/


  if((ON == pMChair->StateBodyScan.Bit.Run)    ||            /*����ɨ�������*/
     (TRUE == pMChair->StateZeroSpike.Bit.Work))             /*������������*/
  {
    Gas_AllCtrlEn();                                         /*���в�λ��������ʹ��*/ 
    Gas_SetGasPart(0, 0);
    return;
  }


  GasCur.All = *pFuncLogic->pFuncCur;

  if(GasCur.Bit.Calves)
  {
    Gas_CalvesCtrlEnOnly();                              /*�Ƚų�������ʹ�ܣ�������λ���ƹر�*/     
    MChair_TabHandle_GasAuto(ExePeriod, (ActionTabAttr_t *)&GasMannualAttrTab[0], &GasCalvesStep);
  }

  if(GasCur.Bit.LumbarSeat)
  {
    Gas_LumbarSeatCtrlEnOnly();                              /*������������ʹ�ܣ�������λ���ƹر�*/       
    MChair_TabHandle_GasAuto(ExePeriod, (ActionTabAttr_t *)&GasMannualAttrTab[1], &GasLumbarSeatStep);
  }

  if(GasCur.Bit.Arms)
  {
    Gas_ArmsCtrlEnOnly();                                    /*�ֱ۳�������ʹ�ܣ�������λ���ƹر�*/       
    MChair_TabHandle_GasAuto(ExePeriod, (ActionTabAttr_t *)&GasMannualAttrTab[2], &GasArmsStep);
  }

  if(GasCur.Bit.Shoulder)
  {
    Gas_ShoulderCtrlEnOnly();                                /*�粿��������ʹ�ܣ�������λ���ƹر�*/        
    MChair_TabHandle_GasAuto(ExePeriod, (ActionTabAttr_t *)&GasMannualAttrTab[3], &GasShoulderStep);
  }
}
