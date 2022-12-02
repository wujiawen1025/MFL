/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: Roller.c                                                                                                         
**
**    ��������: ����������
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
#include "Roller.h"
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
static Roller_t   Roller;
Roller_t   *pRoller = &Roller;


#if((1==ROLLER_FEET_EN) || (1==ROLLER_CALVES_EN))

/**************************************************************************************************
* ��ϵĳ��� ��ͨ������ Roller_GetFeetGas() �ṩ���ϲ���á� �ϲ�����ڽ�����س�����ϵĿ��ơ�
* ���ַ�ʽ����ǿ�ȿ��Ʋ������ã����ǲ�����ѹ���ȷ�ʽ����
*
*    b0   FeetSide       �Ų�
*    b0   Ankle          ����
*    b0   Gas3        
*    b0   Gas4          
*    b0   CalvesSide     �Ȳ�
*    b0   CalvesBot      �ȵ�
*    b0   Gas7          
*    b0   Pump           ����  (Ԥ��)
*/
static const RollerTabItem_t FeetRollerTab[] = 
{
 /* ��ϵĳ���   ǿ��              ����              ��ʼλ��  ����λ��  ����ʱ��  ͣ��ʱ��  �ظ�����*/
  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        0,        0,   5000,    500,      1},
  {B(00000000),  0,    FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,      0,   1000,      1},

  {B(00000000),  100,  FEET_ROLLER_DIRECTION_BACK,   PIGNORE,  PIGNORE,  17000,    500,      1},
  {B(00000000),  90,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   7000,    500,      2},
  {B(00000000),  60,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   7000,    500,      3},

  {B(00000000),  100,  FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,  10000,    500,      1},
  {B(00000000),  60,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   7000,    500,      2},
  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        5,        7,   7000,    500,      3},
  {B(00000000),  90,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   7000,    500,      2},

  {B(00000000),  100,  FEET_ROLLER_DIRECTION_BACK,   PIGNORE,  PIGNORE,  15000,    500,      1},
  {B(00000000),  60,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   7000,    500,      2},
  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        1,        3,   7000,    500,      3},
  {B(00000000),  90,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   7000,    500,      2},
  {B(00000000),  100,  FEET_ROLLER_DIRECTION_BACK,   PIGNORE,  PIGNORE,  15000,    500,      1},

  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        0,        0,   5000,     500,      1},    /*λ�ø�λ*/
  {B(00000000),   0,   FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,   5000,     500,      1},    /*��Ϣ5s*/
  {B(00000000),  60,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      2},
  {B(00000000),  80,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      2},
  {B(00000000), 100,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      3},
  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        0,        0,   5000,     500,      1},    /*λ�ø�λ*/
  {B(00000000),   0,   FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,   5000,     500,      1},    /*��Ϣ5s*/
  {B(00000000), 100,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      3},
  {B(00000000),  80,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      2},
  {B(00000000),  60,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      2},

  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        0,        0,   5000,     500,      1},    /*λ�ø�λ*/
  {B(00000000),   0,   FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,   5000,     500,      1},    /*��Ϣ5s*/
  {B(00000000),  70,   FEET_ROLLER_DIRECTION_BACK,   PIGNORE,  PIGNORE,  15000,     500,      1},
  {B(00000000),  60,   FEET_ROLLER_DIRECTION_FRONT,        5,        7,   7000,     500,      2},
  {B(00000000),  80,   FEET_ROLLER_DIRECTION_FRONT,        5,        7,   7000,     500,      2},
  {B(00000000), 100,   FEET_ROLLER_DIRECTION_FRONT,        5,        7,   7000,     500,      4},

  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        0,        0,   5000,     500,      1},    /*λ�ø�λ*/
  {B(00000000),   0,   FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,   5000,     500,      1},    /*��Ϣ5s*/
  {B(00000000),  70,   FEET_ROLLER_DIRECTION_BACK,   PIGNORE,  PIGNORE,  15000,     500,      1},
  {B(00000000),  60,   FEET_ROLLER_DIRECTION_FRONT,        1,        3,   7000,     500,      2},
  {B(00000000),  80,   FEET_ROLLER_DIRECTION_FRONT,        1,        3,   7000,     500,      2},
  {B(00000000), 100,   FEET_ROLLER_DIRECTION_FRONT,        1,        3,   7000,     500,      4},

  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        0,        0,   5000,     500,      1},    /*λ�ø�λ*/
  {B(00000000),   0,   FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,   5000,     500,      1},    /*��Ϣ5s*/
  {B(00000000),  55,   FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,  15000,     500,      1},
  {B(00000000), 100,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      3},
  {B(00000000),  90,   FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,  10000,     500,      1},
  {B(00000000), 100,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      3},
  {B(00000000),  55,   FEET_ROLLER_DIRECTION_BACK,   PIGNORE,  PIGNORE,  15000,     500,      1},
  {B(00000000), 100,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      3},
  {B(00000000),  90,   FEET_ROLLER_DIRECTION_BACK,   PIGNORE,  PIGNORE,  10000,     500,      1},
  {B(00000000), 100,   FEET_ROLLER_DIRECTION_FRONT,        3,        5,   5000,     500,      3},
  
  {B(00000000),  70,   FEET_ROLLER_DIRECTION_FRONT,        0,        0,   5000,     500,      1},    /*λ�ø�λ*/
  {B(00000000),   0,   FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,   5000,     500,      1},    /*��Ϣ5s*/

  //-------------------------------------------------------------------------------------------------
  {B(00000000),  0,    FEET_ROLLER_DIRECTION_FRONT,  PIGNORE,  PIGNORE,  0,        1000,     1}
};

#define  FEET_ROLLER_TAB_NUM  TAB_NUM(FeetRollerTab)




#define CalvesRollerTab  FeetRollerTab
#endif



/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : Roller_SetFeetRollerWorkState                                                                                                         
* �������� : Roller_SetCalvesRollerWorkState                                                                                                         
* �������� : ���ù��ֹ��ܵĹ����벻����                                                                                     
* ������� : TureFalse -- TRUE  ����
*                         FALSE ������                                                                                      
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Roller_SetFeetRollerWorkState(uint8_t  TureFalse)
{
  #if(1==ROLLER_FEET_EN)
  if((TureFalse != TRUE) && (TureFalse != FALSE))
  {
    TureFalse = FALSE;
  }

  pRoller->CSFlag.Bit.FeetWork = TureFalse;
  #endif
}

void Roller_SetCalvesRollerWorkState(uint8_t  TureFalse)
{
  #if(1==ROLLER_CALVES_EN)
  if((TureFalse != TRUE) && (TureFalse != FALSE))
  {
    TureFalse = FALSE;
  }

  pRoller->CSFlag.Bit.CalvesWork = TureFalse;
  #endif
}

/*
************************************************************************************************************************
* �������� : Roller_FeetRollerPauseOn                                                                                                         
* �������� : Roller_CalvesRollerPauseOn                                                                                                         
* �������� : ��ͣ���ֹ���                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Roller_FeetRollerPauseOn(void)
{
  #if(1==ROLLER_FEET_EN)
  if(pRoller->CSFlag.Bit.FeetPause < 0x1F)
  {
    pRoller->CSFlag.Bit.FeetPause++;
  }
  #endif
}

void Roller_CalvesRollerPauseOn(void)
{
  #if(1==ROLLER_CALVES_EN)
  if(pRoller->CSFlag.Bit.CalvesPause < 0x1F)
  {
    pRoller->CSFlag.Bit.CalvesPause++;
  }
  #endif
}

/*
************************************************************************************************************************
* �������� : Roller_FeetRollerPauseOff                                                                                                         
* �������� : Roller_CalvesRollerPauseOff                                                                                                         
* �������� : �����ͣ���ֹ���                                                                                    
* ������� : ��                                                                                      
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Roller_FeetRollerPauseOff(void)
{
  #if(1==ROLLER_FEET_EN)
  if(pRoller->CSFlag.Bit.FeetPause > 0)
  {
    pRoller->CSFlag.Bit.FeetPause--;
  }
  #endif
}

void Roller_CalvesRollerPauseOff(void)
{
  #if(1==ROLLER_CALVES_EN)
  if(pRoller->CSFlag.Bit.CalvesPause > 0)
  {
    pRoller->CSFlag.Bit.CalvesPause--;
  }
  #endif
}

/*
************************************************************************************************************************
* �������� : Roller_FeetRollerResetStep                                                                                                         
* �������� : Roller_CalvesRollerResetStep                                                                                                         
* �������� : ��λ����                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Roller_FeetRollerResetStep()
{
  #if(1==ROLLER_FEET_EN)
  pRoller->FeetPositionSetp = 0;      /*���� λ�� ����*/  
  pRoller->FeetSetpNum = 0;           /*���� ������*/  
  pRoller->FeetSetpTime = 0;          /*���� ����ʱ��*/ 
  pRoller->FeetSetpRepeat = 0;        /*���� �����ظ�����*/ 
  #endif
}

void Roller_CalvesRollerResetStep()
{
  #if(1==ROLLER_CALVES_EN)
  pRoller->CalvesSetpNum = 0;           /*���� ������*/  
  pRoller->CalvesSetpTime = 0;          /*���� ����ʱ��*/ 
  pRoller->CalvesSetpRepeat = 0;        /*���� �����ظ�����*/ 
  #endif
}



/*
************************************************************************************************************************
* �������� : Roller_FeetRollerHandle                                                                                                         
* �������� : Roller_CalvesRollerHandle                                                                                                         
* �������� : ���ִ���                                                                                     
* ������� : ExePeriod -- ������ִ������                                                                                      
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Roller_FeetRollerHandle(Ticker_t ExePeriod)
{
  #if(1==ROLLER_FEET_EN)
  static uint16_t   ProtectTimeMs;                                   
  static uint8_t    DirHis;  
  uint8_t           DirTab;

  do
  {
    /*��ͣ��ֹͣ���-----------------------------------------*/
    if(pRoller->CSFlag.Bit.FeetPause > 0)
    {
      pRoller->CSFlag.Bit.FeetRun = OFF;
      pRoller->FeetPWM = 0;
      break;
    }

    if(TRUE == pRoller->CSFlag.Bit.KeepAtInitPosition)       /*�����ڳ�ʼλ��*/
    {
      if(pRoller->CSFlag.Bit.FeetInitPositionIO != 0)
      {
        pRoller->CSFlag.Bit.FeetRun = ON;
        pRoller->FeetPWM = 70;
      }
      else
      {
        pRoller->CSFlag.Bit.FeetRun = OFF;
        pRoller->FeetPWM = 0;
      }    
      break;
    }
    
    /*�������--------------------------------------------------*/
    if(TRUE == pRoller->CSFlag.Bit.FeetWork) /*����*/
    {
      pRoller->CSFlag.Bit.FeetRun = ON;
      DirTab = FeetRollerTab[pRoller->FeetSetpNum].Direction;
      pRoller->FeetSetpTime += ExePeriod;
      
      if((FeetRollerTab[pRoller->FeetSetpNum].EndPosition   != PIGNORE) &&   /*����λ����Ч������ĳ�������ع�������*/
         (FeetRollerTab[pRoller->FeetSetpNum].StartPosition != PIGNORE) )    /*����λ����Ч������ĳ�������ع�������*/
      {
        pRoller->FeetPWM = FeetRollerTab[pRoller->FeetSetpNum].PWM;

        switch(pRoller->FeetPositionSetp)
        {
          case 0: 
          {
            if((pRoller->FeetPosition == FeetRollerTab[pRoller->FeetSetpNum].EndPosition) ||    /*λ�õ�*/
               (pRoller->FeetSetpTime >= FeetRollerTab[pRoller->FeetSetpNum].OnTime)      )     /*��ʱ*/
            {
              pRoller->FeetPositionSetp++;
            }  
          }break;
          
          case 1: 
          {
            DirTab = !DirTab;                                                                   /*�ع�����*/ 
            if((pRoller->FeetPosition == FeetRollerTab[pRoller->FeetSetpNum].StartPosition) ||  /*λ�õ�*/
               (pRoller->FeetSetpTime >= FeetRollerTab[pRoller->FeetSetpNum].OnTime)        )   /*��ʱ*/
            {
              pRoller->FeetPositionSetp++;
            }  
          }break;
           
          default: 
          { 
            pRoller->FeetPositionSetp = 0; 
            pRoller->FeetSetpTime = 0;
            pRoller->FeetSetpRepeat++;
          }break;
        }
      }
      else  /*����λ����Ч����һֱǰ����һֱ���*/
      {
        if(pRoller->FeetSetpTime < FeetRollerTab[pRoller->FeetSetpNum].OnTime)
        {
          pRoller->FeetPWM = FeetRollerTab[pRoller->FeetSetpNum].PWM;
        }
        else if(pRoller->FeetSetpTime < (FeetRollerTab[pRoller->FeetSetpNum].OnTime + FeetRollerTab[pRoller->FeetSetpNum].OffTime))
        {
          pRoller->FeetPWM = 0;
        }
        else
        {
          pRoller->FeetSetpTime = 0;
          pRoller->FeetSetpRepeat++;
        }       
      }

      if(pRoller->FeetSetpRepeat >= FeetRollerTab[pRoller->FeetSetpNum].Repeat)
      {
        pRoller->FeetSetpRepeat = 0;
        pRoller->FeetSetpNum++;
        if(pRoller->FeetSetpNum >= FEET_ROLLER_TAB_NUM)
        {
          pRoller->FeetSetpNum = 0;
        }
      }
      
      /*���򱣻�*/
      if(DirHis != DirTab)
      {
        DirHis = DirTab;
        ProtectTimeMs = 0;
      }
      if(ProtectTimeMs < 1000)
      {
        ProtectTimeMs += ExePeriod;
      }
      if(ProtectTimeMs < 100)                     
      {
        pRoller->FeetPWM = 0;
      } 
      else if(ProtectTimeMs < 200) 
      {
        pRoller->FeetPWM = 0;
        pRoller->CSFlag.Bit.FeetDirection = DirTab;//FeetRollerTab[pRoller->FeetSetpNum].Direction;
      }      
    }
    else  /*������*/
    {
      Roller_FeetRollerResetStep();
      
      if(pRoller->CSFlag.Bit.FeetInitPositionIO != 0)
      {
        pRoller->CSFlag.Bit.FeetRun = ON;
        pRoller->FeetPWM = 70;
      }
      else
      {
        pRoller->CSFlag.Bit.FeetRun = OFF;
        pRoller->CSFlag.Bit.FeetDirection = FEET_ROLLER_DIRECTION_FRONT; 
        pRoller->FeetPWM = 0;
      }
    }
  }while(0);

  //BSP_IO_SetOutput_FeetRollerCtrl(pRoller->CSFlag.Bit.FeetRun, pRoller->CSFlag.Bit.FeetDirection,  pRoller->FeetPWM);
  pRoller->SetQry0x49.Byte0.Bit.FeetRollerSw = pRoller->CSFlag.Bit.FeetRun;
  pRoller->SetQry0x49.Byte0.Bit.FeetRollerDirection = pRoller->CSFlag.Bit.FeetDirection;
  pRoller->SetQry0x49.FeetRollerPWM = pRoller->FeetPWM;

  #endif
}

void Roller_CalvesRollerHandle(Ticker_t ExePeriod)
{
  #if(1==ROLLER_CALVES_EN)
  static uint16_t   ProtectTimeMs;                                   
  static uint8_t    DirHis;  
  uint8_t           DirTab;

  do
  {
    /*��ͣ��ֹͣ���-----------------------------------------*/
    if(pRoller->CSFlag.Bit.CalvesPause > 0)
    {
      pRoller->CSFlag.Bit.CalvesRun = OFF;
      pRoller->CalvesPWM = 0;
      break;
    }

    /*�������--------------------------------------------------*/
    if(TRUE == pRoller->CSFlag.Bit.CalvesWork) /*����*/
    {
      pRoller->CSFlag.Bit.CalvesRun = ON;
      DirTab = CalvesRollerTab[pRoller->CalvesSetpNum].Direction;
      pRoller->CalvesSetpTime += ExePeriod;
      if(pRoller->CalvesSetpTime < CalvesRollerTab[pRoller->CalvesSetpNum].OnTime)
      {
        pRoller->CalvesPWM = CalvesRollerTab[pRoller->CalvesSetpNum].PWM;
      }
      else if(pRoller->CalvesSetpTime < (CalvesRollerTab[pRoller->CalvesSetpNum].OnTime + CalvesRollerTab[pRoller->CalvesSetpNum].OffTime))
      {
        pRoller->CalvesPWM = 0;
      }
      else
      {
        pRoller->CalvesSetpTime = 0;
        pRoller->CalvesSetpRepeat++;
      }       

      if(pRoller->CalvesSetpRepeat >= CalvesRollerTab[pRoller->CalvesSetpNum].Repeat)
      {
        pRoller->CalvesSetpRepeat = 0;
        pRoller->CalvesSetpNum++;
        if(pRoller->CalvesSetpNum >= FEET_ROLLER_TAB_NUM)
        {
          pRoller->CalvesSetpNum = 0;
        }
      }
      
      /*���򱣻�*/
      if(DirHis != DirTab)
      {
        DirHis = DirTab;
        ProtectTimeMs = 0;
      }
      if(ProtectTimeMs < 1000)
      {
        ProtectTimeMs += ExePeriod;
      }
      if(ProtectTimeMs < 200)                     
      {
        pRoller->CSFlag.Bit.CalvesRun = OFF;
      } 
      else if(ProtectTimeMs < 400) 
      {
        pRoller->CSFlag.Bit.CalvesRun = OFF;
        pRoller->CSFlag.Bit.CalvesDirection = CalvesRollerTab[pRoller->CalvesSetpNum].Direction;
      }      
    }
    else  /*������*/
    {
      Roller_CalvesRollerResetStep();
      pRoller->CSFlag.Bit.CalvesRun = OFF;
      pRoller->CalvesPWM = 0;
    }
  }while(0);
  
  pRoller->SetQry0x49.Byte2.Bit.CalvesRollerSw = pRoller->CSFlag.Bit.CalvesRun;
  pRoller->SetQry0x49.Byte2.Bit.CalvesRollerDirection = pRoller->CSFlag.Bit.CalvesDirection;
  
  #endif
}


void Roller_AllPartsHandle(Ticker_t ExePeriod)                                                                                                         
{
  Roller_FeetRollerHandle(ExePeriod);
  Roller_CalvesRollerHandle(ExePeriod);  
}


/*
========================================================================================================================
*         ���ֹ��ܺ�����                           ���ֹ��ܺ�����                           ���ֹ��ܺ�����
========================================================================================================================
*/
#define  ROLLER_TICK_COUNT_BUF_NUM   1
static Ticker_t Roller_TickCount[ROLLER_TICK_COUNT_BUF_NUM];

static const ESF_TmrExeFunc_t  Roller_TmrExeFuncTab[] = 
{
  /*   ִ�к���              ִ������(ms)    ʱ���������*/
  {Roller_AllPartsHandle,        101,      &Roller_TickCount[0]}

};

#define  ROLLER_TMR_EXE_FUNC_TAB_NUM     TAB_NUM(Roller_TmrExeFuncTab)


/*
************************************************************************************************************************
* �������� : Roller_Init                                                                                                         
* �������� : ���ֳ�ʼ��                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ���� �ɲ������ֹ��� �Ľṹ�� ��ָ��                                                                
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
Roller_t*  Roller_Init(void)
{
  /*��ʼ���������------------------------------------------*/
  memset(pRoller, 0, sizeof(Roller_t)); /*������������*/

  /*��� Roller_TmrExeFuncTab ���ܺ����������Ƿ���ȷ------------------------*/
  ESF_TmrExeFuncTabCheck(Roller_TmrExeFuncTab, ROLLER_TMR_EXE_FUNC_TAB_NUM, ROLLER_TICK_COUNT_BUF_NUM);

  return pRoller;
}

/*
************************************************************************************************************************
* �������� : Roller_Handle                                                                                                         
* �������� : ���ִ���                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Roller_Handle(void)
{
  /*���ȹ��ܺ�����------------------------------------------------*/
  ESF_TmrExeFuncScheduling(Roller_TmrExeFuncTab, ROLLER_TMR_EXE_FUNC_TAB_NUM);
}


/*
************************************************************************************************************************
* �������� : Roller_GetCSFlag                                                                                                          
* �������� : ��� ���� �� ״̬ ��ʶ                                                                                     
* ������� : ��                                                                                      
* ���ز��� : ������״̬��ʶ �Ľṹ��                                                                
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
RollerCSFlag_t Roller_GetCSFlag(void)
{
  return pRoller->CSFlag;
}

/*
************************************************************************************************************************
* �������� : Roller_GetFeetGas                                                                                                         
* �������� : ��� �Ź���ϵĳ���                                                                             
* ������� : ��                                                                                      
* ���ز��� : �Ź���ϵĳ���                                                                   
* ����˵�� : �ṩ���ϲ���ã��ϲ�����ڽ�����س�����ϵĿ���                                                                                                        
************************************************************************************************************************
*/
RollerGasPart_t Roller_GetFeetGas(void)
{
  return FeetRollerTab[pRoller->FeetSetpNum].GasPart;
}

/*
************************************************************************************************************************
* �������� : Roller_SetFeetRollerKeepAtInitPosition                                                                                                          
* �������� : �ýŹ������ڳ�ʼλ��                                                                               
* ������� : ��                                                                                      
* ���ز��� : ��                                                     
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Roller_SetFeetRollerKeepAtInitPosition(void)
{
  pRoller->CSFlag.Bit.KeepAtInitPosition = TRUE;      /*�����ڳ�ʼλ��*/
}

/*
************************************************************************************************************************
* �������� : Roller_ClrFeetRollerKeepAtInitPosition                                                                                                          
* �������� : ����ýŹ������ڳ�ʼλ��                                                                               
* ������� : ��                                                                                      
* ���ز��� : ��                                                     
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Roller_ClrFeetRollerKeepAtInitPosition(void)
{
  pRoller->CSFlag.Bit.KeepAtInitPosition = FALSE;      /*�����ڳ�ʼλ��*/
}

/*
************************************************************************************************************************
* �������� : Roller_CDPDataObjRx_0x49                                                                                      
* �������� : 0x49 �ȽŹ��ֿ���(���İ�<-->�Ƚſ��ư壩
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ��������ݵĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t Roller_CDPDataObjRx_0x49(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  /*�������ݵ����İ�-------------------------------------------------------------*/
  memcpy((uint8_t *)&pRoller->SetQry0x49, &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  pRoller->FeetCount = pRoller->SetQry0x49.FeetRollerCount;

  if(FEET_ROLLER_DIRECTION_FRONT == pRoller->CSFlag.Bit.FeetDirection)
  {
    pRoller->FeetPosition = pRoller->FeetCount/FEET_ROLLER_COUNT_PER_SEGMENT;
  }
  else
  {
    pRoller->FeetPosition = pRoller->FeetCount/FEET_ROLLER_COUNT_PER_SEGMENT + 1;
  }
  
  pRoller->CSFlag.Bit.FeetInitPositionIO = pRoller->SetQry0x49.Byte0.Bit.FeetRollerInitPositionIO;

  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* �������� : Roller_CDPDataObjTx_0x49                                                                                      
* �������� : 0x49 �ȽŹ��ֿ���(���İ�<-->�Ƚſ��ư壩
* ������� : ��
* ���ز��� : �ɹ��򷵻�Ҫ���͵����ݵ��ڴ��׵�ַ��ʧ�ܷ���NULL��ָ��
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t* Roller_CDPDataObjTx_0x49(void)
{
  pRoller->SetQry0x49.DataLen = sizeof(pRoller->SetQry0x49);  
  pRoller->SetQry0x49.DataID = 0x49;  

  return (uint8_t *)&pRoller->SetQry0x49;
}
