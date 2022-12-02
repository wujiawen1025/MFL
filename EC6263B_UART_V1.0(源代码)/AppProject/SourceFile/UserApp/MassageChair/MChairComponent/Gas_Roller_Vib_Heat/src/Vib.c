/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: Vib.c                                                                                                         
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
#include "Vib.h"
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
static Vib_t   Vib;
Vib_t   *pVib = &Vib;


static  const  VibTabItem_t VibTab[] = 
{
  /*ǿ��  ��ʱ��  ͣ��ʱ��  �ظ�����*/
  {20,   0,        500,      1},   /*��ʼ*/
  {25,   6000,     2000,     4},
  {30,   5000,     1000,     3},
  {35,   7000,     3000,     2},
  {30,   5000,     1000,     3},
  {25,   6000,     2000,     4},
  {20,   0,        500,      1}    /*ͣ*/
};
#define  VIB_TAB_NUM  TAB_NUM(VibTab)


/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : Vib_SetFeetVibFunc      
* �������� : Vib_SetCalvesVibFunc      
* �������� : Vib_SetSeatVibFunc      
* �������� : Vib_SetLumbarBackVibFunc      
* �������� : �����񶯵Ĺ����벻����                                                                                     
* ������� : TrueFalse -- TRUE  ����
*                         FALSE ������                                                                                      
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Vib_SetFeetVibWorkState(uint8_t TrueFalse)
{
  #if(1==VIB_FEET_EN)
  if((TrueFalse != TRUE) && (TrueFalse != FALSE))
  {
    TrueFalse = FALSE;
  }
  pVib->CSFlag.Bit.FeetWork = TrueFalse;
  #endif
}

void Vib_SetCalvesVibWorkState(uint8_t TrueFalse)
{
  #if(1==VIB_CALVES_EN)
  if((TrueFalse != TRUE) && (TrueFalse != FALSE))
  {
    TrueFalse = FALSE;
  }
  pVib->CSFlag.Bit.CalvesWork = TrueFalse;
  #endif
}

void Vib_SetSeatVibWorkState(uint8_t TrueFalse)
{
  #if(1==VIB_SEAT_EN)
  if((TrueFalse != TRUE) && (TrueFalse != FALSE))
  {
    TrueFalse = FALSE;
  }
  pVib->CSFlag.Bit.SeatWork = TrueFalse;
  #endif
}

void Vib_SetLumbarBackVibWorkState(uint8_t TrueFalse)
{
  #if(1==VIB_LUMBARBACK_EN)
  if((TrueFalse != TRUE) && (TrueFalse != FALSE))
  {
    TrueFalse = FALSE;
  }
  pVib->CSFlag.Bit.LumbarBackWork = TrueFalse;
  #endif
}


/*
************************************************************************************************************************
* �������� : Vib_FeetVibPauseOn                                                                                                         
* �������� : Vib_CalvesVibPauseOn                                                                                                         
* �������� : Vib_SeatVibPauseOn                                                                                                         
* �������� : Vib_LumbarBackVibPauseOn                                                                                                         
* �������� : ��ͣ�񶯹���                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Vib_FeetVibPauseOn(void)
{
  #if(1==VIB_FEET_EN)
  if(pVib->CSFlag.Bit.FeetPause < 0x1F)
  {
    pVib->CSFlag.Bit.FeetPause++;
  }
  #endif
}

void Vib_CalvesVibPauseOn(void)
{
  #if(1==VIB_CALVES_EN)
  if(pVib->CSFlag.Bit.CalvesPause < 0x1F)
  {
    pVib->CSFlag.Bit.CalvesPause++;
  }
  #endif
}

void Vib_SeatVibPauseOn(void)
{
  #if(1==VIB_SEAT_EN)
  if(pVib->CSFlag.Bit.SeatPause < 0x1F)
  {
    pVib->CSFlag.Bit.SeatPause++;
  }
  #endif
}

void Vib_LumbarBackVibPauseOn(void)
{
  #if(1==VIB_LUMBARBACK_EN)
  if(pVib->CSFlag.Bit.LumbarBackPause < 0x1F)
  {
    pVib->CSFlag.Bit.LumbarBackPause++;
  }
  #endif
}

/*
************************************************************************************************************************
* �������� : Vib_FeetVibPauseOff                                                                                                         
* �������� : Vib_CalvesVibPauseOff                                                                                                         
* �������� : Vib_SeatVibPauseOff                                                                                                         
* �������� : Vib_LumbarBackVibPauseOff                                                                                                         
* �������� : �����ͣ�񶯹���                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Vib_FeetVibPauseOff(void)
{
  #if(1==VIB_FEET_EN)
  if(pVib->CSFlag.Bit.FeetPause > 0)
  {
    pVib->CSFlag.Bit.FeetPause--;
  }
  #endif
}

void Vib_CalvesVibPauseOff(void)
{
  #if(1==VIB_CALVES_EN)
  if(pVib->CSFlag.Bit.CalvesPause > 0)
  {
    pVib->CSFlag.Bit.CalvesPause--;
  }
  #endif
}

void Vib_SeatVibPauseOff(void)
{
  #if(1==VIB_SEAT_EN)
  if(pVib->CSFlag.Bit.SeatPause > 0)
  {
    pVib->CSFlag.Bit.SeatPause--;
  }
  #endif
}

void Vib_LumbarBackVibPauseOff(void)
{
  #if(1==VIB_LUMBARBACK_EN)
  if(pVib->CSFlag.Bit.LumbarBackPause > 0)
  {
    pVib->CSFlag.Bit.LumbarBackPause--;
  }
  #endif
}

/*
************************************************************************************************************************
* �������� : Vib_FeetVibResetStep                                                                                                         
* �������� : Vib_CalvesVibResetStep                                                                                                         
* �������� : Vib_SeatVibResetStep                                                                                                         
* �������� : Vib_LumbarBackVibResetStep                                                                                                         
* �������� : ��λ����                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Vib_FeetVibResetStep(void)
{
  #if(1==VIB_FEET_EN)
  pVib->FeetSetpNum = 0;           
  pVib->FeetSetpTime = 0;        
  pVib->FeetSetpRepeat = 0;      
  #endif
}

void Vib_CalvesVibResetStep(void)
{
  #if(1==VIB_CALVES_EN)
  pVib->CalvesSetpNum = 0;           
  pVib->CalvesSetpTime = 0;        
  pVib->CalvesSetpRepeat = 0;      
  #endif
}

void Vib_SeatVibResetStep(void)
{
  #if(1==VIB_SEAT_EN)
  pVib->SeatSetpNum = 0;           
  pVib->SeatSetpTime = 0;        
  pVib->SeatSetpRepeat = 0;      
  #endif
}

void Vib_LumbarBackVibResetStep(void)
{
  #if(1==VIB_LUMBARBACK_EN)
  pVib->LumbarBackSetpNum = 0;           
  pVib->LumbarBackSetpTime = 0;        
  pVib->LumbarBackSetpRepeat = 0;      
  #endif
}

/*
************************************************************************************************************************
* �������� : Vib_FeetVibHandle                                                                                                         
* �������� : Vib_CalvesVibHandle                                                                                                         
* �������� : Vib_SeatVibHandle                                                                                                         
* �������� : Vib_LumbarBackVibHandle                                                                                                         
* �������� : Vib_AllPartsHandle                                                                                                         
* �������� : ����λ���񶯴���                                                                                     
* ������� : ExePeriod -- ������ִ������                                                                                    
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Vib_FeetVibHandle(Ticker_t ExePeriod)
{
  #if(1==VIB_FEET_EN)
  do
  {
    if(pVib->CSFlag.Bit.FeetPause > 0)
    {
      pVib->CSFlag.Bit.FeetRun = OFF;
      break;
    }

    if(TRUE == pVib->CSFlag.Bit.FeetWork) /*����*/
    {
      pVib->FeetSetpTime += ExePeriod;
      if(pVib->FeetSetpTime < VibTab[pVib->FeetSetpNum].OnTime)
      {
        pVib->CSFlag.Bit.FeetRun = ON;
      }
      else if(pVib->FeetSetpTime < (VibTab[pVib->FeetSetpNum].OnTime + VibTab[pVib->FeetSetpNum].OffTime))
      {
        pVib->CSFlag.Bit.FeetRun = OFF;
      }
      else
      {
        pVib->FeetSetpTime = 0;
        pVib->FeetSetpRepeat++;
        if(pVib->FeetSetpRepeat >= VibTab[pVib->FeetSetpNum].Repeat)
        {
          pVib->FeetSetpRepeat = 0;
          pVib->FeetSetpNum++;
          if(pVib->FeetSetpNum >= VIB_TAB_NUM)
          {
            pVib->FeetSetpNum = 0;
          }
        }
      } 
    }
    else  /*��ʹ��*/
    {
      Vib_FeetVibResetStep();
      pVib->CSFlag.Bit.FeetRun = OFF;
    }

  }while(0);

  //BSP_IO_SetOutput_FeetVibCtrl(pVib->CSFlag.Bit.FeetRun, 0, VibTab[pVib->FeetSetpNum].PWM);
  pVib->SetQry0x4A.Byte0.Bit.FeetVibSw = pVib->CSFlag.Bit.FeetRun;
  pVib->SetQry0x4A.Byte0.Bit.FeetVibDirection = 1;
  
  #endif
}

void Vib_CalvesVibHandle(Ticker_t ExePeriod)
{
  #if(1==VIB_CALVES_EN)
  do
  {
    if(pVib->CSFlag.Bit.CalvesPause > 0)
    {
      pVib->CSFlag.Bit.CalvesRun = OFF;
      break;
    }

    if(TRUE == pVib->CSFlag.Bit.CalvesWork) /*����*/
    {
      pVib->CalvesSetpTime += ExePeriod;
      if(pVib->CalvesSetpTime < VibTab[pVib->CalvesSetpNum].OnTime)
      {
        pVib->CSFlag.Bit.CalvesRun = ON;
      }
      else if(pVib->CalvesSetpTime < (VibTab[pVib->CalvesSetpNum].OnTime + VibTab[pVib->CalvesSetpNum].OffTime))
      {
        pVib->CSFlag.Bit.CalvesRun = OFF;
      }
      else
      {
        pVib->CalvesSetpTime = 0;
        pVib->CalvesSetpRepeat++;
        if(pVib->CalvesSetpRepeat >= VibTab[pVib->CalvesSetpNum].Repeat)
        {
          pVib->CalvesSetpRepeat = 0;
          pVib->CalvesSetpNum++;
          if(pVib->CalvesSetpNum >= VIB_TAB_NUM)
          {
            pVib->CalvesSetpNum = 0;
          }
        }
      } 
    }
    else  /*��ʹ��*/
    {
      Vib_CalvesVibResetStep();
      pVib->CSFlag.Bit.CalvesRun = OFF;
    }

  }while(0);

  //BSP_IO_SetOutput_CalvesVibCtrl(pVib->CSFlag.Bit.CalvesRun, 0, VibTab[pVib->CalvesSetpNum].PWM);
  #endif
}

void Vib_SeatVibHandle(Ticker_t ExePeriod)
{
  #if(1==VIB_SEAT_EN)
  do
  {
    if(pVib->CSFlag.Bit.SeatPause > 0)
    {
      pVib->CSFlag.Bit.SeatRun = OFF;
      break;
    }

    if(TRUE == pVib->CSFlag.Bit.SeatWork) /*����*/
    {
      pVib->SeatSetpTime += ExePeriod;
      if(pVib->SeatSetpTime < VibTab[pVib->SeatSetpNum].OnTime)
      {
        pVib->CSFlag.Bit.SeatRun = ON;
      }
      else if(pVib->SeatSetpTime < (VibTab[pVib->SeatSetpNum].OnTime + VibTab[pVib->SeatSetpNum].OffTime))
      {
        pVib->CSFlag.Bit.SeatRun = OFF;
      }
      else
      {
        pVib->SeatSetpTime = 0;
        pVib->SeatSetpRepeat++;
        if(pVib->SeatSetpRepeat >= VibTab[pVib->SeatSetpNum].Repeat)
        {
          pVib->SeatSetpRepeat = 0;
          pVib->SeatSetpNum++;
          if(pVib->SeatSetpNum >= VIB_TAB_NUM)
          {
            pVib->SeatSetpNum = 0;
          }
        }
      } 
    }
    else  /*��ʹ��*/
    {
      Vib_SeatVibResetStep();
      pVib->CSFlag.Bit.SeatRun = OFF;
    }

  }while(0);

  //BSP_IO_SetOutput_SeatVibCtrl(pVib->CSFlag.Bit.SeatRun, 0, VibTab[pVib->SeatSetpNum].PWM);

  #endif
}

void Vib_LumbarBackVibHandle(Ticker_t ExePeriod)
{
  #if(1==VIB_LUMBARBACK_EN)
  do
  {
    if(pVib->CSFlag.Bit.LumbarBackPause > 0)
    {
      pVib->CSFlag.Bit.LumbarBackRun = OFF;
      break;
    }

    if(TRUE == pVib->CSFlag.Bit.LumbarBackWork) /*����*/
    {
      pVib->LumbarBackSetpTime += ExePeriod;
      if(pVib->LumbarBackSetpTime < VibTab[pVib->LumbarBackSetpNum].OnTime)
      {
        pVib->CSFlag.Bit.LumbarBackRun = ON;
      }
      else if(pVib->LumbarBackSetpTime < (VibTab[pVib->LumbarBackSetpNum].OnTime + VibTab[pVib->LumbarBackSetpNum].OffTime))
      {
        pVib->CSFlag.Bit.LumbarBackRun = OFF;
      }
      else
      {
        pVib->LumbarBackSetpTime = 0;
        pVib->LumbarBackSetpRepeat++;
        if(pVib->LumbarBackSetpRepeat >= VibTab[pVib->LumbarBackSetpNum].Repeat)
        {
          pVib->LumbarBackSetpRepeat = 0;
          pVib->LumbarBackSetpNum++;
          if(pVib->LumbarBackSetpNum >= VIB_TAB_NUM)
          {
            pVib->LumbarBackSetpNum = 0;
          }
        }
      } 
    }
    else  /*��ʹ��*/
    {
      Vib_LumbarBackVibResetStep();
      pVib->CSFlag.Bit.LumbarBackRun = OFF;
    }

  }while(0);

  //BSP_IO_SetOutput_LumbarBackVibCtrl(pVib->CSFlag.Bit.LumbarBackRun, 0, VibTab[pVib->LumbarBackSetpNum].PWM);

  #endif
}


void Vib_AllPartsHandle(Ticker_t ExePeriod)                                                                                                         
{
  Vib_FeetVibHandle(ExePeriod);
  Vib_CalvesVibHandle(ExePeriod);  
  Vib_SeatVibHandle(ExePeriod);
  Vib_LumbarBackVibHandle(ExePeriod);
}


/*
========================================================================================================================
*         �񶯹��ܺ�����                           �񶯹��ܺ�����                           �񶯹��ܺ�����
========================================================================================================================
*/
#define  VIB_TICK_COUNT_BUF_NUM   2
static Ticker_t Vib_TickCount[VIB_TICK_COUNT_BUF_NUM];

static const ESF_TmrExeFunc_t  Vib_TmrExeFuncTab[] = 
{
  /*   ִ�к���             ִ������(ms)        ʱ���������*/
  {Vib_AllPartsHandle,        100,            &Vib_TickCount[0]}

};

#define  VIB_TMR_EXE_FUNC_TAB_NUM     TAB_NUM(Vib_TmrExeFuncTab)


/*
************************************************************************************************************************
* �������� : Vib_Handle                                                                                                         
* �������� : �񶯴���                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Vib_Handle(void)
{
  /*���ȹ��ܺ�����------------------------------------------------*/
  ESF_TmrExeFuncScheduling(Vib_TmrExeFuncTab, VIB_TMR_EXE_FUNC_TAB_NUM);
}

/*
************************************************************************************************************************
* �������� : Vib_Init                                                                                                         
* �������� : �񶯳�ʼ��                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ���� �ɲ����񶯹��� �Ľṹ�� ��ָ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
Vib_t*  Vib_Init(void)
{
  /*��ʼ���������------------------------------------------------------*/
  memset(pVib, 0, sizeof(Vib_t)); /*������������*/

  /*��� Vib_TmrExeFuncTab ���ܺ����������Ƿ���ȷ-----------------------*/
  ESF_TmrExeFuncTabCheck(Vib_TmrExeFuncTab, VIB_TMR_EXE_FUNC_TAB_NUM, VIB_TICK_COUNT_BUF_NUM);

  return pVib;
}

/*
************************************************************************************************************************
* �������� : Vib_GetCSFlag                                                                                                        
* �������� : ��� ���� �� ״̬ ��ʶ                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ������״̬��ʶ �Ľṹ��                                                                
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
VibCSFlag_t Vib_GetCSFlag(void)
{
  return pVib->CSFlag;
}


/*
************************************************************************************************************************
* �������� : Vib_CDPDataObjRx_0x4A                                                                                      
* �������� : 0x4A �Ƚ��񶯿���(���İ�<-->�Ƚſ��ư壩
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ��������ݵĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t Vib_CDPDataObjRx_0x4A(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  /*�������ݵ����İ�-------------------------------------------------------------*/
  memcpy((uint8_t *)&pVib->SetQry0x4A, &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* �������� : Vib_CDPDataObjTx_0x4A                                                                                      
* �������� : 0x4A �Ƚ��񶯿���(���İ�<-->�Ƚſ��ư壩
* ������� : ��
* ���ز��� : �ɹ��򷵻�Ҫ���͵����ݵ��ڴ��׵�ַ��ʧ�ܷ���NULL��ָ��
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t* Vib_CDPDataObjTx_0x4A(void)
{
  pVib->SetQry0x4A.DataLen = sizeof(pVib->SetQry0x4A);  
  pVib->SetQry0x4A.DataID = 0x4A;  

  return (uint8_t *)&pVib->SetQry0x4A;
}

