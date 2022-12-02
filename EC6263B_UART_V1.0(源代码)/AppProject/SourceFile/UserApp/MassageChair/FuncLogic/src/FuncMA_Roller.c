/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣ�FuncMA_Roller.c 
**
**    ��������:�����֡��ֶ��Զ�
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
static const uint16_t   FeetRollerCtrlOnOffTimeTab[][2] = 
{
  {100,  0},    /*����*/
  {60,   60},
  {90,   90},
  {120,  120},
  {150,  150},
  {0,    100}   /*����*/
};


static const uint16_t   CalvesRollerCtrlOnOffTimeTab[][2] = 
{
  {100,  0},    /*����*/
  {60,   60},
  {90,   90},
  {120,  120},
  {150,  150},
  {0,    100}   /*����*/
};

//static ActionTabStep_t GasFeetRollerStep;
static ActionTabStep_t GasCalvesRollerStep;


static const ActionTabAttr_t   GasRollerTab[] =
{
  { 
    0,                                                   /*����ID   ���Զ���ID*/
    (void*)FeetGasRollerTab,                             /*�������*/
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
  
  { 
    0,                                                   /*����ID   ���Զ���ID*/
    (void*)CalvesGasRollerTab,                           /*�������*/
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
* �������� : MChair_HeatFuncReset_Feet                                                                                               
* �������� : MChair_HeatFuncReset_Calves                                                                                               
* �������� : ��Ħ�� ���ֹ��� ��λ                                                               
* ������� : ��                                                                                
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_RollerFuncReset_Feet(void)
{
    pMChair->FeetRollerCtrlOnOffTime = 0;
    pMChair->FeetRollerCtrlSw = OFF;
    Roller_SetFeetRollerWorkState(FALSE);                       /*ֹͣ����*/
    Roller_FeetRollerResetStep();                               /*��λ����*/
}

void MChair_RollerFuncReset_Calves(void)
{
    pMChair->CalvesRollerCtrlOnOffTime = 0;
    pMChair->CalvesRollerCtrlSw = OFF;
    Roller_SetCalvesRollerWorkState(FALSE);                     /*ֹͣ����*/
    Roller_CalvesRollerResetStep();                             /*��λ����*/
}

/*
************************************************************************************************************************
* �������� : Roller_FeetGasCtrl                                                                                               
* �������� : �Ź���������                                                             
* ������� : ��                                                                                
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void Roller_FeetGasCtrl(Ticker_t ExePeriod)
{
//  GasPart2_t   GasPart;
  
  if(TRUE == pMChair->CSFlag.Bit.GasCooperateSpikeRun)             /*��������Ƹ˵Ķ���*/
  {
    return;
  }  
  //Gas_SetPumpSw(ON);
  //Gas_FeetCtrlEnOnly();                                           /*�Ų���������ʹ�ܣ�ִ�нŹ�������ĳ���*/  

  /*��ʽ1���ӽŹ�������ȡ�������ƣ���϶Ƚϸߣ�������ǿ�Ȳ��ɿ���--------------------------*/
//  GasPart2_t   GasPart;
//  GasPart.Bit.Ankle = Roller_GetFeetGas().Bit.Ankle;
//  GasPart.Bit.FeetSide = Roller_GetFeetGas().Bit.FeetSide;
//  Gas_SetGasPart(0, GasPart.All);
  
  /*��ʽ2��ֱ�Ӱ���һ������������϶Ȳ��ߣ�����ǿ�ȿɿ���----------------------------------*/
  //MChair_TabHandle_GasAuto(ExePeriod, (ActionTabAttr_t *)&GasRollerTab[0], &GasFeetRollerStep);
}

/*
************************************************************************************************************************
* �������� : Roller_CalvesGasCtrl                                                                                               
* �������� : �ȹ���������                                                             
* ������� : ��                                                                                
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void Roller_CalvesGasCtrl(Ticker_t ExePeriod)
{
  Gas_SetPumpSw(ON);
  Gas_CalvesCtrlEnOnly();                                     /*�Ų���������ʹ�ܣ�ִ�нŹ�������ĳ���*/  

  /*��ʽ1���ӽŹ�������ȡ�������ƣ���϶Ƚϸߣ�������ǿ�Ȳ��ɿ���--------------------------*/
//  GasPart2_t   GasPart;
//  GasPart.Bit.Ankle = Roller_GetCalvesGas().Bit.Calves;
//  GasPart.Bit.FeetSide = Roller_GetCalvesGas().Bit.CalvesSide;
//  Gas_SetGasPart(0, GasPart.All);
  
  /*��ʽ2��ֱ�Ӱ���һ������������϶Ȳ��ߣ�����ǿ�ȿɿ���----------------------------------*/
  MChair_TabHandle_GasAuto(ExePeriod, (ActionTabAttr_t *)&GasRollerTab[1], &GasCalvesRollerStep);
}
/*
************************************************************************************************************************
* �������� : MChair_FuncSwitch_RollerMA                                                                                               
* �������� : ��Ħ�� �����л� ֮  �����֡��ֶ��Զ�                                                                   
* ������� : SwitchMode -- Ҫ�л�ģʽ
*            pFuncLogic -- �����߼�������                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_RollerMA(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  RollerAction_t RollerActionCur;
  RollerAction_t RollerActionHis;


  RollerActionCur.All = *pFuncLogic->pFuncCur;
  RollerActionHis.All = *pFuncLogic->pFuncHis;
  if(RollerActionCur.Bit.Feet != RollerActionHis.Bit.Feet)      /*�Ź����ܷ����л�*/
  {
    MChair_RollerFuncReset_Feet();
    
    if(FUNC_TYPE_NONE == pMChair->ComponentFuncState.Bit.Gas)   /*���κγ���������ȫ���ر�*/
    {
      Gas_SetPumpSw(OFF);
      Gas_AllCtrlEn();                                          /*���в�λ��������ʹ��*/ 
      Gas_SetGasPart(0, 0);
    }
    else                                                        /*����ֻ�ؽŲ���������������*/
    {
      /*��ͬ�ھɼܹ����¼ܹ��нŹ�����������������������ԽŲ������Ŀ��ơ�
        �رսŹ���������������ԽŲ������Ŀ��ƽ��Զ��ָ���
        ʵ��ԭ����FuncLogicTab[] ���У�&MChair.FuncMA_Roller.All �����ڱ��ĺ��棬
                  ���������ܹ���ǰ��̨˳��ִ�У���˿���ĸ�ֵ���Ź��Գ����ĸ�ֵ��������
                  ��ǰ�ĸ�ֵ��������������ԽŲ������ĸ�ֵ���� */
      Gas_FeetCtrlEnOnly();                                     /*�Ų���������ʹ�ܣ�ִ�нŹ�������ĳ���*/  
      Gas_SetGasPart(0, 0);
    }
  }
  
  if(RollerActionCur.Bit.Calves != RollerActionHis.Bit.Calves)  /*�ȹ����ܷ����л�*/
  {
    MChair_RollerFuncReset_Calves();
    
    if(FUNC_TYPE_NONE == pMChair->ComponentFuncState.Bit.Gas)   /*���κγ���������ȫ���ر�*/
    {
      Gas_SetPumpSw(OFF);
      Gas_AllCtrlEn();                                          /*���в�λ��������ʹ��*/ 
      Gas_SetGasPart(0, 0);
    }
    else                                                        /*����ֻ�ؽŲ���������������*/
    {
      Gas_CalvesCtrlEnOnly();                                  /*�Ȳ���������ʹ�ܣ�ִ���ȹ�������ĳ���*/  
      Gas_SetGasPart(0, 0);
    }
  }  
}

/*
************************************************************************************************************************
* �������� : MChair_FuncExe_RollerMA                                                                                               
* �������� : ��Ħ�� ����ִ�� ֮  �����֡��ֶ��Զ�                                                                   
* ������� : ExePeriod  -- ִ������
*            pFuncLogic -- ָ���������߼���ָ�롣                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_RollerMA(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  uint16_t OnTime;
  uint16_t OffTime;

  switch(pMChair->FuncMA_Roller.Bit.Feet)
  {
    case FMA_ROLLER_NONE:
    {
      pMChair->FeetRollerCtrlSw = OFF;
    }break;

    case FMA_FEET_ROLLER_Mannual:              /*�ֶ�*/
    {
      pMChair->ComponentFuncState.Bit.FeetRoller = FUNC_TYPE_MANNUALAUTO; /*�Ź�����״̬���ֶ��Զ�*/
      Roller_FeetGasCtrl(ExePeriod);           /*�Ź���������*/
      pMChair->FeetRollerCtrlSw = ON;          /*�ֶ��ͳ���*/

    }break;

    case FMA_FEET_ROLLER_ByActionTab:          /*�ɱ���ڵ�ֵ�����ƣ���ActionObjHandle_AccompanyFunc()����*/
    {
      pMChair->ComponentFuncState.Bit.FeetRoller = FUNC_TYPE_MANNUALAUTO; /*�Ź�����״̬���ֶ��Զ�*/
   }break;

    case FMA_FEET_ROLLER_ByTime_OnAlways:      /*��ʱ�����*/
    case FMA_FEET_ROLLER_ByTime_On60s_Off60s:
    case FMA_FEET_ROLLER_ByTime_On90s_Off90s:
    case FMA_FEET_ROLLER_ByTime_On120s_Off120s:
    case FMA_FEET_ROLLER_ByTime_On150s_Off120s:
    {
      pMChair->ComponentFuncState.Bit.FeetRoller = FUNC_TYPE_MANNUALAUTO; /*�Ź�����״̬���ֶ��Զ�*/

      pMChair->FeetRollerCtrlOnOffTime += ExePeriod;
      OnTime = FeetRollerCtrlOnOffTimeTab[pMChair->FuncMA_Roller.Bit.Feet - FMA_FEET_ROLLER_ByTime_OnAlways][0];
      OffTime = OnTime + FeetRollerCtrlOnOffTimeTab[pMChair->FuncMA_Roller.Bit.Feet - FMA_FEET_ROLLER_ByTime_OnAlways][1];
      if(pMChair->FeetRollerCtrlOnOffTime/1000 < OnTime) 
      {
        pMChair->FeetRollerCtrlSw = ON;
        Roller_FeetGasCtrl(ExePeriod);         /*�Ź���������*/
      }
      else if(pMChair->FeetRollerCtrlOnOffTime/1000 == OnTime) 
      {
        Gas_FeetCtrlEnOnly();                  /*�Ų���������ʹ�ܣ�ִ�нŹ�������ĳ���*/  
        Gas_SetGasPart(0, 0);                  /*����ض�֮ǰ���ȹؽŲ�����*/
      }
      else if(pMChair->FeetRollerCtrlOnOffTime/1000 < OffTime)
      {
        pMChair->FeetRollerCtrlSw = OFF;
      }
      else
      {
        pMChair->FeetRollerCtrlOnOffTime = 0;
      }

    }break;

    default:
    {
      pMChair->FuncMA_Roller.Bit.Feet = FMA_ROLLER_NONE;
    }break;
  }
  Roller_SetFeetRollerWorkState((ON == pMChair->FeetRollerCtrlSw)   ? TRUE:FALSE); 


  //------------------------------------------------------------------------------------
  switch(pMChair->FuncMA_Roller.Bit.Calves)
  {
    case FMA_ROLLER_NONE:
    {
      pMChair->CalvesRollerCtrlSw = OFF;
    }break;

    case FMA_CALVES_ROLLER_Mannual:              /*�ֶ�*/
    {
      pMChair->ComponentFuncState.Bit.CalvesRoller = FUNC_TYPE_MANNUALAUTO; /*�Ź�����״̬���ֶ��Զ�*/
      Roller_CalvesGasCtrl(ExePeriod);           /*�Ź���������*/
      pMChair->CalvesRollerCtrlSw = ON;          /*�ֶ��ͳ���*/

    }break;

    case FMA_CALVES_ROLLER_ByActionTab:          /*�ɱ���ڵ�ֵ�����ƣ���ActionObjHandle_AccompanyFunc()����*/
    {
      pMChair->ComponentFuncState.Bit.CalvesRoller = FUNC_TYPE_MANNUALAUTO; /*�Ź�����״̬���ֶ��Զ�*/
   }break;

    case FMA_CALVES_ROLLER_ByTime_OnAlways:      /*��ʱ�����*/
    case FMA_CALVES_ROLLER_ByTime_On60s_Off60s:
    case FMA_CALVES_ROLLER_ByTime_On90s_Off90s:
    case FMA_CALVES_ROLLER_ByTime_On120s_Off120s:
    case FMA_CALVES_ROLLER_ByTime_On150s_Off120s:
    {
//      pMChair->ComponentFuncState.Bit.CalvesRoller = FUNC_TYPE_MANNUALAUTO; /*�Ź�����״̬���ֶ��Զ�*/

//      pMChair->CalvesRollerCtrlOnOffTime += ExePeriod;
//      OnTime = CalvesRollerCtrlOnOffTimeTab[pMChair->FuncMA_Roller.Bit.Calves - FMA_CALVES_ROLLER_ByTime_OnAlways][0];
//      OffTime = OnTime + CalvesRollerCtrlOnOffTimeTab[pMChair->FuncMA_Roller.Bit.Calves - FMA_CALVES_ROLLER_ByTime_OnAlways][1];
//      if(pMChair->CalvesRollerCtrlOnOffTime/1000 < OnTime) 
//      {
//        pMChair->CalvesRollerCtrlSw = ON;
//        Roller_CalvesGasCtrl(ExePeriod);         /*�Ź���������*/
//      }
//      else if(pMChair->CalvesRollerCtrlOnOffTime/1000 == OnTime) 
//      {
//        Gas_CalvesCtrlEnOnly();                  /*�Ų���������ʹ�ܣ�ִ�нŹ�������ĳ���*/  
//        Gas_SetGasPart(0, 0);                  /*����ض�֮ǰ���ȹؽŲ�����*/
//      }
//      else if(pMChair->CalvesRollerCtrlOnOffTime/1000 < OffTime)
//      {
//        pMChair->CalvesRollerCtrlSw = OFF;
//      }
//      else
//      {
//        pMChair->CalvesRollerCtrlOnOffTime = 0;
//      }

      pMChair->ComponentFuncState.Bit.CalvesRoller = FUNC_TYPE_MANNUALAUTO; /*�Ź�����״̬���ֶ��Զ�*/

      pMChair->CalvesRollerCtrlOnOffTime += ExePeriod;
      OnTime = CalvesRollerCtrlOnOffTimeTab[pMChair->FuncMA_Roller.Bit.Calves - FMA_CALVES_ROLLER_ByTime_OnAlways][0];
      OffTime = OnTime + CalvesRollerCtrlOnOffTimeTab[pMChair->FuncMA_Roller.Bit.Calves - FMA_CALVES_ROLLER_ByTime_OnAlways][1];

      if(pMChair->CalvesRollerCtrlOnOffTime/1000 < OnTime)
      {
        pMChair->CalvesRollerCtrlSw = ON;
        Roller_CalvesGasCtrl(ExePeriod);         /*�Ź���������*/
      }
      else if(pMChair->CalvesRollerCtrlOnOffTime/1000 < OffTime) 
      {
        pMChair->CalvesRollerCtrlSw = OFF;
      }
      else
      {
        pMChair->CalvesRollerCtrlOnOffTime = 0;
      }
      
      if(pMChair->CalvesRollerCtrlOnOffTime == 0) 
      {
        Gas_CalvesCtrlEnOnly();                  /*�Ų���������ʹ�ܣ�ִ�нŹ�������ĳ���*/  
        Gas_SetGasPart(0, 0);                    /*����ض�֮ǰ���ȹؽŲ�����*/
      }      
    }break;

    default:
    {
      pMChair->FuncMA_Roller.Bit.Calves = FMA_ROLLER_NONE;
    }break;
  }
  Roller_SetCalvesRollerWorkState((ON == pMChair->CalvesRollerCtrlSw) ? TRUE:FALSE);  
}
