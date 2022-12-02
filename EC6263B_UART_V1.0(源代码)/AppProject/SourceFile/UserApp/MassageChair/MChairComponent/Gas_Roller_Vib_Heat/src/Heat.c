/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: Heat.c                                                                                                         
**
**    ��������: ��������
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
#include "Heat.h"
#include "ESF.h"


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
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
========================================================================================================================
*/
static Heat_t   Heat;
Heat_t   *pHeat = &Heat;

/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/


/*
************************************************************************************************************************
* �������� : Heat_GetLumbarBackLeftTemperature                                                                                                         
* �������� : Heat_GetLumbarBackRightTemperature                                                                                                         
* �������� : ��ȡ�¶�                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ��Ħͷ�¶�                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
int8_t Heat_GetLumbarBackLeftTemperature(void)
{
  return pHeat->SetQry0x41.MassageHeadTemp1;
}

int8_t Heat_GetLumbarBackRightTemperature(void)
{
  return pHeat->SetQry0x41.MassageHeadTemp2;
}



/*
************************************************************************************************************************
* �������� : Heat_SetFeetHeatFunc      
* �������� : Heat_SetCalvesHeatFunc      
* �������� : Heat_SetSeatHeatFunc      
* �������� : Heat_SetLumbarBackHeatFunc      
* �������� : ���ü��ȵĹ����벻����                                                                                     
* ������� : TrueFalse -- TRUE  ����
*                         FALSE ������                                                                                      
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Heat_SetFeetHeatWorkState(uint8_t TrueFalse)
{
  #if(1==HEAT_FEET_EN)
  if((TrueFalse != TRUE) && (TrueFalse != FALSE))
  {
    TrueFalse = FALSE;
  }
  pHeat->CSFlag.Bit.FeetWork = TrueFalse;
  #endif
}

void Heat_SetCalvesHeatWorkState(uint8_t TrueFalse)
{
  #if(1==HEAT_CALVES_EN)
  if((TrueFalse != TRUE) && (TrueFalse != FALSE))
  {
    TrueFalse = FALSE;
  }
  pHeat->CSFlag.Bit.CalvesWork = TrueFalse;
  #endif
}

void Heat_SetSeatHeatWorkState(uint8_t TrueFalse)
{
  #if(1==HEAT_SEAT_EN)
  if((TrueFalse != TRUE) && (TrueFalse != FALSE))
  {
    TrueFalse = FALSE;
  }
  pHeat->CSFlag.Bit.SeatWork = TrueFalse;
  #endif
}

void Heat_SetLumbarBackHeatWorkState(uint8_t TrueFalse)
{
  #if(1==HEAT_LUMBARBACK_EN)
  if((TrueFalse != TRUE) && (TrueFalse != FALSE))
  {
    TrueFalse = FALSE;
  }
  pHeat->CSFlag.Bit.LumbarBackWork = TrueFalse;
  #endif
}


/*
************************************************************************************************************************
* �������� : Heat_FeetHeatPauseOn                                                                                                         
* �������� : Heat_CalvesHeatPauseOn                                                                                                         
* �������� : Heat_SeatHeatPauseOn                                                                                                         
* �������� : Heat_LumbarBackHeatPauseOn                                                                                                         
* �������� : ��ͣ���ȹ���                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Heat_FeetHeatPauseOn(void)
{
  #if(1==HEAT_FEET_EN)
  if(pHeat->CSFlag.Bit.FeetPause < 0x1F)
  {
    pHeat->CSFlag.Bit.FeetPause++;
  }
  #endif
}

void Heat_CalvesHeatPauseOn(void)
{
  #if(1==HEAT_CALVES_EN)
  if(pHeat->CSFlag.Bit.CalvesPause < 0x1F)
  {
    pHeat->CSFlag.Bit.CalvesPause++;
  }
  #endif
}

void Heat_SeatHeatPauseOn(void)
{
  #if(1==HEAT_SEAT_EN)
  if(pHeat->CSFlag.Bit.SeatPause < 0x1F)
  {
    pHeat->CSFlag.Bit.SeatPause++;
  }
  #endif
}

void Heat_LumbarBackHeatPauseOn(void)
{
  #if(1==HEAT_LUMBARBACK_EN)
  if(pHeat->CSFlag.Bit.LumbarBackPause < 0x1F)
  {
    pHeat->CSFlag.Bit.LumbarBackPause++;
  }
  #endif
}

/*
************************************************************************************************************************
* �������� : Heat_FeetHeatPauseOff                                                                                                         
* �������� : Heat_CalvesHeatPauseOff                                                                                                         
* �������� : Heat_SeatHeatPauseOff                                                                                                         
* �������� : Heat_LumbarBackHeatPauseOff                                                                                                         
* �������� : �����ͣ���ȹ���                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Heat_FeetHeatPauseOff(void)
{
  #if(1==HEAT_FEET_EN)
  if(pHeat->CSFlag.Bit.FeetPause > 0)
  {
    pHeat->CSFlag.Bit.FeetPause--;
  }
  #endif
}

void Heat_CalvesHeatPauseOff(void)
{
  #if(1==HEAT_CALVES_EN)
  if(pHeat->CSFlag.Bit.CalvesPause > 0)
  {
    pHeat->CSFlag.Bit.CalvesPause--;
  }
  #endif
}

void Heat_SeatHeatPauseOff(void)
{
  #if(1==HEAT_SEAT_EN)
  if(pHeat->CSFlag.Bit.SeatPause > 0)
  {
    pHeat->CSFlag.Bit.SeatPause--;
  }
  #endif
}

void Heat_LumbarBackHeatPauseOff(void)
{
  #if(1==HEAT_LUMBARBACK_EN)
  if(pHeat->CSFlag.Bit.LumbarBackPause > 0)
  {
    pHeat->CSFlag.Bit.LumbarBackPause--;
  }
  #endif
}


/*
************************************************************************************************************************
* �������� : Heat_FeetHeatHandle                                                                                                         
* �������� : Heat_CalvesHeatHandle                                                                                                         
* �������� : Heat_SeatHeatHandle                                                                                                         
* �������� : Heat_LumbarBackHeatHandle                                                                                                         
* �������� : Heat_AllPartsHandle                                                                                                         
* �������� : ����λ���ȼ��ȴ���                                                                                     
* ������� : ExePeriod -- ������ִ������                                                                                    
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Heat_FeetHeatHandle(Ticker_t ExePeriod)
{
  #if(1==HEAT_FEET_EN)
  do
  {
    if(pHeat->CSFlag.Bit.FeetPause > 0)
    {
      pHeat->CSFlag.Bit.FeetRun = OFF;
      break;
    }

    if(TRUE == pHeat->CSFlag.Bit.FeetWork) /*����*/
    {
      pHeat->CSFlag.Bit.FeetRun = ON;
    }
    else  /*��ʹ��*/
    {
      pHeat->CSFlag.Bit.FeetRun = OFF;
    }

  }while(0);

  //BSP_IO_SetOutput_FeetHeatCtrl(pHeat->CSFlag.Bit.FeetRun);
  #endif
}

void Heat_CalvesHeatHandle(Ticker_t ExePeriod)
{
  #if(1==HEAT_CALVES_EN)
  do
  {
    if(pHeat->CSFlag.Bit.CalvesPause > 0)
    {
      pHeat->CSFlag.Bit.CalvesRun = OFF;
      break;
    }

    if(TRUE == pHeat->CSFlag.Bit.CalvesWork) /*����*/
    {
      pHeat->CSFlag.Bit.CalvesRun = ON;
    }
    else  /*��ʹ��*/
    {
      pHeat->CSFlag.Bit.CalvesRun = OFF;
    }

  }while(0);

  BSP_IO_SetOutput_CalvesHeat(pHeat->CSFlag.Bit.CalvesRun);
//  pHeat->SetQry0x4E.Byte0.Bit.CalvesWork = pHeat->CSFlag.Bit.LumbarBackWork;
//  pHeat->SetQry0x4E.Byte0.Bit.CalvesPause = (pHeat->CSFlag.Bit.LumbarBackPause > 0) ? 1:0;
  #endif
}

void Heat_SeatHeatHandle(Ticker_t ExePeriod)
{
  #if(1==HEAT_SEAT_EN)
  do
  {
    if(pHeat->CSFlag.Bit.SeatPause > 0)
    {
      pHeat->CSFlag.Bit.SeatRun = OFF;
      break;
    }

    if(TRUE == pHeat->CSFlag.Bit.SeatWork) /*����*/
    {
      pHeat->CSFlag.Bit.SeatRun = ON;
    }
    else  /*��ʹ��*/
    {
      pHeat->CSFlag.Bit.SeatRun = OFF;
    }

  }while(0);

  //BSP_IO_SetOutput_SeatHeatCtrl(pHeat->CSFlag.Bit.SeatRun);

  #endif
}

void Heat_LumbarBackHeatHandle(Ticker_t ExePeriod)
{
  #if(1==HEAT_LUMBARBACK_EN)
  do
  {
    if(pHeat->CSFlag.Bit.LumbarBackPause > 0)
    {
      pHeat->CSFlag.Bit.LumbarBackRun = OFF;
      break;
    }

    if(TRUE == pHeat->CSFlag.Bit.LumbarBackWork) /*����*/
    {
      pHeat->CSFlag.Bit.LumbarBackRun = ON;
    }
    else  /*��ʹ��*/
    {
      pHeat->CSFlag.Bit.LumbarBackRun = OFF;
    }

  }while(0);
  //BSP_IO_SetOutput_LumbarBackHeat(pHeat->CSFlag.Bit.LumbarBackRun);
  pHeat->SetQry0x41.Byte0.Bit.MassageHeadHeatWork = pHeat->CSFlag.Bit.LumbarBackWork;

  #endif
}


void Heat_AllPartsHandle(Ticker_t ExePeriod)                                                                                                         
{
  Heat_FeetHeatHandle(ExePeriod);
  Heat_CalvesHeatHandle(ExePeriod);  
  Heat_SeatHeatHandle(ExePeriod);
  Heat_LumbarBackHeatHandle(ExePeriod);
}


/*
========================================================================================================================
*         ���ȹ��ܺ�����                           ���ȹ��ܺ�����                           ���ȹ��ܺ�����
========================================================================================================================
*/
#define  HEAT_TICK_COUNT_BUF_NUM   1
static Ticker_t Heat_TickCount[HEAT_TICK_COUNT_BUF_NUM];
static const ESF_TmrExeFunc_t  Heat_TmrExeFuncTab[] = 
{
  /*   ִ�к���              ִ������(ms)     ʱ���������*/
  {Heat_AllPartsHandle,         200,          &Heat_TickCount[0]}  
};

#define  HEAT_TMR_EXE_FUNC_TAB_NUM     TAB_NUM(Heat_TmrExeFuncTab)

/*
************************************************************************************************************************
* �������� : Heat_Handle                                                                                                         
* �������� : ���ȴ���                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Heat_Handle(void)
{
  /*���ȹ��ܺ�����------------------------------------------------*/
  ESF_TmrExeFuncScheduling(Heat_TmrExeFuncTab, HEAT_TMR_EXE_FUNC_TAB_NUM);
}

/*
************************************************************************************************************************
* �������� : Heat_Init                                                                                                         
* �������� : ���ȳ�ʼ��                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ���� �ɲ������ȹ��� �Ľṹ�� ��ָ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
Heat_t*  Heat_Init(void)
{
  /*��ʼ���������------------------------------------------*/
  memset(pHeat, 0, sizeof(Heat_t)); /*������������*/

  /*��� Heat_TmrExeFuncTab ���ܺ����������Ƿ���ȷ------------------------*/
  ESF_TmrExeFuncTabCheck(Heat_TmrExeFuncTab, HEAT_TMR_EXE_FUNC_TAB_NUM, HEAT_TICK_COUNT_BUF_NUM);

  return pHeat;
}

/*
************************************************************************************************************************
* �������� : Heat_GetCSFlag                                                                                                         
* �������� : ��� ���� �� ״̬ ��ʶ                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ������״̬��ʶ �Ľṹ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
HeatCSFlag_t Heat_GetCSFlag(void)
{
  return pHeat->CSFlag;
}

/*
************************************************************************************************************************
* �������� : Heat_CDPDataObjRx_0x41                                                                                      
* �������� : 0x41 ��Ħͷ���ȿ���(���İ�<-->��о�壩��Ӧ���� ���İ�ͻ�о�嵥�������ϵͳ���һ�о��ʵ�ֳ�һ���������߼�ģ�顣
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ��������ݵĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t Heat_CDPDataObjRx_0x41(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  /*�������ݵ����İ�-------------------------------------------------------------*/
  memcpy((uint8_t *)&pHeat->SetQry0x41, &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  pHeat->CSFlag.Bit.LumbarBackRun  = pHeat->SetQry0x41.Byte0.Bit.MassageHeadHeatRun;
  pHeat->CSFlag.Bit.LumbarBackThyristorShortFault  = pHeat->SetQry0x41.Byte3.Bit.MassageHeadThyristorShortFault;
  pHeat->CSFlag.Bit.LumbarBackThermistorShortFault  = pHeat->SetQry0x41.Byte3.Bit.MassageHeadThermistorShortFault;
  pHeat->CSFlag.Bit.LumbarBackThermistorOpenFault  = pHeat->SetQry0x41.Byte3.Bit.MassageHeadThermistorOpenFault;
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* �������� : Heat_CDPDataObjTx_0x41                                                                                      
* �������� : 0x41 ��Ħͷ���ȿ���(���İ�<-->��о�壩��Ӧ���� ���İ�ͻ�о�嵥�������ϵͳ���һ�о��ʵ�ֳ�һ���������߼�ģ�顣
* ������� : ��
* ���ز��� : �ɹ��򷵻�Ҫ���͵����ݵ��ڴ��׵�ַ��ʧ�ܷ���NULL��ָ��
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t* Heat_CDPDataObjTx_0x41(void)
{
  pHeat->SetQry0x41.Byte0.Bit.MassageHeadHeatPause = (pHeat->CSFlag.Bit.LumbarBackPause > 0) ? TRUE : FALSE;

  pHeat->SetQry0x41.DataLen = sizeof(pHeat->SetQry0x41);  
  pHeat->SetQry0x41.DataID = 0x41;  

  return (uint8_t *)&pHeat->SetQry0x41;
}
