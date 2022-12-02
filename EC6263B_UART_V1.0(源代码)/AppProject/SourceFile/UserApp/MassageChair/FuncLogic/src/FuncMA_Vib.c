/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣ�FuncMA_Vib.c 
**
**    ��������:���񶯡��ֶ��Զ�
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
static const uint16_t   VibCtrlOnOffTimeTab[][2] = 
{
  {100,  0},    /*����*/

  {180,  60},
  {60,   50},
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
* �������� : MChair_VibFuncReset_Feet                                                                                               
* �������� : MChair_VibFuncReset_Calves                                                                                               
* �������� : MChair_VibFuncReset_Seat                                                                                               
* �������� : MChair_VibFuncReset_LumbarBack                                                                                               
* �������� : ��Ħ�� �񶯹��� ��λ                                                               
* ������� : ��                                                                                
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_VibFuncReset_Feet(void)
{
  pMChair->FeetVibCtrlOnOffTime = 0;
  pMChair->FeetVibCtrlSw = OFF;
  Vib_SetFeetVibWorkState(FALSE);           /*ֹͣ����*/ 
  Vib_FeetVibResetStep();                   /*��λ����*/     
}

void MChair_VibFuncReset_Calves(void)
{
  pMChair->CalvesVibCtrlOnOffTime = 0;
  pMChair->CalvesVibCtrlSw = OFF;
  Vib_SetCalvesVibWorkState(FALSE);         /*ֹͣ����*/  
  Vib_CalvesVibResetStep();                 /*��λ����*/     
}

void MChair_VibFuncReset_Seat(void)
{
  pMChair->SeatVibCtrlOnOffTime = 0;
  pMChair->SeatVibCtrlSw = OFF;
  Vib_SetSeatVibWorkState(FALSE);           /*ֹͣ����*/  
  Vib_SeatVibResetStep();                   /*��λ����*/     
}

void MChair_VibFuncReset_LumbarBack(void)
{
  pMChair->LumbarBackVibCtrlOnOffTime = 0;
  pMChair->LumbarBackVibCtrlSw = OFF;
  Vib_SetLumbarBackVibWorkState(FALSE);     /*ֹͣ����*/
  Vib_LumbarBackVibResetStep();             /*��λ����*/     
}

/*
************************************************************************************************************************
* �������� : MChair_FuncSwitch_VibMA                                                                                               
* �������� : ��Ħ�� �����л� ֮  ���񶯡��ֶ��Զ�                                                                   
* ������� : SwitchMode -- Ҫ�л�ģʽ
*            pFuncLogic -- �����߼�������                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_VibMA(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  VibAction_t VibActionCur;
  VibAction_t VibActionHis;

  VibActionCur.All = *pFuncLogic->pFuncCur;
  VibActionHis.All = *pFuncLogic->pFuncHis;

  if((VibActionCur.Bit.Feet != VibActionHis.Bit.Feet) || (CLOSE == SwitchMode))
  {
    MChair_VibFuncReset_Feet();
  }
  
  if((VibActionCur.Bit.Calves != VibActionHis.Bit.Calves) || (CLOSE == SwitchMode))
  {
    MChair_VibFuncReset_Calves();
  }
  
  if((VibActionCur.Bit.Seat != VibActionHis.Bit.Seat) || (CLOSE == SwitchMode))
  {
    MChair_VibFuncReset_Seat();
  }

  if((VibActionCur.Bit.LumbarBack != VibActionHis.Bit.LumbarBack) || (CLOSE == SwitchMode))
  {
    MChair_VibFuncReset_LumbarBack();
  }
}

/*
************************************************************************************************************************
* �������� : MChair_FuncExe_VibMA                                                                                               
* �������� : ��Ħ�� ����ִ�� ֮  ���񶯡��ֶ��Զ�                                                                   
* ������� : ExePeriod  -- ִ������
*            pFuncLogic -- ָ���������߼���ָ�롣                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_VibMA(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  uint16_t OnTime;
  uint16_t OffTime;

  switch(pMChair->FuncMA_Vib.Bit.Feet)
  {
    case FMA_VIB_NONE:
    {
      pMChair->FeetVibCtrlSw = OFF;
    }break;

    case FMA_FEET_VIB_Mannual:         /*�ֶ����򳣿�*/
    {
      pMChair->ComponentFuncState.Bit.FeetVib = FUNC_TYPE_MANNUALAUTO; /*����״̬���ֶ��Զ�*/

      pMChair->FeetVibCtrlSw = ON;
    }break;

    case FMA_FEET_VIB_ByActionTab:    /*�ɱ���ڵ�ֵ�����ƣ���ActionObjHandle_AccompanyFunc()����*/
    {
      pMChair->ComponentFuncState.Bit.FeetVib = FUNC_TYPE_MANNUALAUTO; /*����״̬���ֶ��Զ�*/
    }break;

    case FMA_FEET_VIB_ByTime_OnAlways:    /*��ʱ�����*/
    case FMA_FEET_VIB_ByTime_On180s_Off60s:
    case FMA_FEET_VIB_ByTime_On60s_Off50s:
    case FMA_FEET_VIB_ByTime_On300s_Off60s:
    {
      pMChair->ComponentFuncState.Bit.FeetVib = FUNC_TYPE_MANNUALAUTO; /*����״̬���ֶ��Զ�*/

      pMChair->FeetVibCtrlOnOffTime += ExePeriod;
      OnTime  = VibCtrlOnOffTimeTab[pMChair->FuncMA_Vib.Bit.Feet - FMA_FEET_VIB_ByTime_OnAlways][0];
      OffTime = OnTime + VibCtrlOnOffTimeTab[pMChair->FuncMA_Vib.Bit.Feet - FMA_FEET_VIB_ByTime_OnAlways][1];
      if(pMChair->FeetVibCtrlOnOffTime/1000 < OnTime) 
      {
        pMChair->FeetVibCtrlSw = ON;
      }
      else if(pMChair->FeetVibCtrlOnOffTime/1000 < OffTime)
      {
        pMChair->FeetVibCtrlSw = OFF;
      }
      else
      {
        pMChair->FeetVibCtrlOnOffTime = 0;
      }

    }break;

    default:
    {
      pMChair->FuncMA_Vib.Bit.Feet = FMA_VIB_NONE;
    }break;
  }
  Vib_SetFeetVibWorkState((ON == pMChair->FeetVibCtrlSw) ? TRUE:FALSE);  

  /*-------------------------------------------------------------------------------------*/

}

