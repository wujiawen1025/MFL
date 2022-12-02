/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣSSysMode.c 
**
**    ��������: ϵͳģʽ����
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
#include "SysMode.h"

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


/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : Default_Key_Power                                                                                                         
* �������� :                                                                                         
* ������� : pData -- ��ֵ����������������                                                                                     
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t Default_Key_Power(uint8_t *pData)
{
//  if(SYS_MODE_STANDBY == pMChair->SysModeCur) 
//  {
//    return SysMode_UserRun_Enter();
//  }
//  else
  {
    return SysMode_Standby_Enter(SYS_MODE_INSPECTAUTO, TRUE);    /*�ػ�����λ�Ƹ˽Ƕ�*/
  }
}


static const SysMode_KeyLogicTabItem_t Default_KeyLogicTab[] = /*Ĭ�ϼ�ֵ��*/
{
  {KEYVAL_Power,                  B(00000000),    Default_Key_Power},

  /*---------------------------------------------------*/
  {KEYVAL_MAX,                    B(00000000),    NULL}
};

#define DEFAULT_KEY_TAB_NUM  TAB_NUM(Default_KeyLogicTab)

static uint16_t Default_GetKeyValID(uint16_t index)
{
  if(index > (DEFAULT_KEY_TAB_NUM-1))
  {
    return INDEX_NO_MATCH;
  }
  return Default_KeyLogicTab[index].KeyValID;
}

/*
************************************************************************************************************************
* �������� : Default_KeyValAdditonOp                                                                                                         
* �������� : ��ִֵ��ǰ��ĸ��Ӳ���                                                                                    
* ������� : Index       -- ��ֵ�ڱ���������
*            BeforeAfter -- BEFORE����ִֵ��ǰִ�и��Ӳ���
*                           AFTER����ִֵ�к�ִ�и��Ӳ���   
*            CurExeState -- ��ǰִ��״̬�� SUCCESS �ɹ�   FAIL ʧ�� 
* ���ز��� : SUCCESS -- ��ִ�к�����ֵ������
*            FAIL    -- ����ִ�к�����ֵ������                                                            
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t Default_KeyValAdditonOp(uint8_t Index, uint8_t BeforeAfter, uint8_t CurExeState)
{
  uint8_t ret;

  
  ret = SUCCESS;                                                 /*�ȼ���ɹ�*/

  /*��ִֵ��ǰ�ĸ��Ӳ���---------------------------------------------------*/
  if(BEFORE == BeforeAfter)                    
  {

  }
  
  /*��ִֵ�к�ĸ��Ӳ���---------------------------------------------------*/
  else 
  {
    if((SUCCESS == CurExeState) &&                               /*��ֵ�ɹ�ִ��*/
       (Default_KeyLogicTab[Index].KeyValID != KEYVAL_NoPress))  /*�а�������*/
    {
      pMChair->PromptToneTLMs = 300;                             /*��ֵ�ɹ�ִ�У�����ʾ��*/
    }
  }

  return ret;  
}

/*
************************************************************************************************************************
* �������� : SysMode_DefaultKeyValHandle                                                                                                         
* �������� : ϵͳģʽĬ�ϵļ�ֵ����                                                                             
* ������� : ��                                                                      
* ���ز��� : ��                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SysMode_DefaultKeyValHandle(void)
{
  pMChair->KeyValHandle.KeyLogicTab    = Default_KeyLogicTab;            /*�����߼���*/
  pMChair->KeyValHandle.KeyLogicTabNum = DEFAULT_KEY_TAB_NUM;            /*�����߼��� ��С*/
  pMChair->KeyValHandle.pGetMatchID    = Default_GetKeyValID;            /*����ָ�룬ָ��ĺ������ã����ر����Ŀ �� ��Ҫ���������� ���ڵ�����*/
  pMChair->KeyValHandle.pAddOp         = Default_KeyValAdditonOp;        /*����ָ�룬ָ��ĺ������ã���ִֵ��ǰ��ĸ��Ӳ��� */
}

 
/*����������������������������������������������������������������������������������������������������������������������*/

/*
************************************************************************************************************************
* �������� : ERPPower_OnHandle                                                                                                         
* �������� : ERP��Դ �����Ĵ���                                                                                        
* ������� : ExePeriod -- ����ִ������                                                                                       
* ���ز��� : ��                                                                
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void ERPPower_OnHandle(Ticker_t ExePeriod)
{
  pMChair->ERPPowerSw = ON;    
  pMChair->ERPPowerOffWaitTimeMs = 0;
  if((pMChair->ERPPowerOnTimeMs < 10000) && 
     (ON == pMChair->ERPPowerSw)         )
  {
    pMChair->ERPPowerOnTimeMs += ExePeriod;
  }
}

/*
************************************************************************************************************************
* �������� : ERPPower_OffHandle                                                                                                         
* �������� : ERP��Դ �رյĴ���                                                                                        
* ������� : ExePeriod -- ����ִ������                                                                                       
* ���ز��� : ��                                                                
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void ERPPower_OffHandle(Ticker_t ExePeriod)
{
  if((pMChair->ERPPowerOnTimeMs < 10000) && 
     (ON == pMChair->ERPPowerSw)         )
  {
    pMChair->ERPPowerOnTimeMs += ExePeriod;
  }

  if(pMChair->ERPPowerOffWaitTimeMs < 65000)
  {
    pMChair->ERPPowerOffWaitTimeMs += ExePeriod;
  }

  /*�Ƹ˺ͻ�о���ڹ��������ݻ��ر�*/
  if((TRUE == pMChair->StateBackSpike.Bit.Work)     ||  
     (TRUE == pMChair->StateZeroSpike.Bit.Work)     ||
     (TRUE == pMChair->StateFeetSpike.Bit.Work)     ||
     (TRUE == pMChair->StateLegFlexSpike.Bit.Work) ||   
     (TRUE == pMChair->StateXMotor.Bit.Work)        ||
     (TRUE == pMChair->StateYMotor.Bit.Work)        ||
     (TRUE == pMChair->StateZMotor.Bit.Work)        ||
     (TRUE == pMChair->StateCDPCSFlag.Bit.RepeaterWork))/*���İ崦�����ݰ�ת��״̬������ģ����뱣֤������*/ 
  {
    pMChair->ERPPowerSw = ON;               /*��������Դ*/
    pMChair->ERPPowerOffWaitTimeMs = 0;
  }
  /*��о���Ƹ����κζ���������5s���ر�����Դ*/
  else if(pMChair->ERPPowerOffWaitTimeMs > 5000) 
  {
    pMChair->ERPPowerSw = OFF;              /*�ر�����Դ*/
    pMChair->ERPPowerOnTimeMs = 0;
    //BSP_IO_Init();
  }
}

/*
************************************************************************************************************************
* �������� : StandBy_ERPHandle                                                                                                         
* �������� : ERP���Ŀ���                                                                                        
* ������� : ExePeriod -- ����ִ������                                                                                       
* ���ز��� : ��                                                                
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SysMode_ERPPowerHandle(Ticker_t ExePeriod)
{
  switch(pMChair->SysModeCur)
  {
    case SYS_MODE_STANDBY:
    {
      ERPPower_OffHandle(ExePeriod);
    }break;

    case SYS_MODE_USERRUN:
    {
      ERPPower_OnHandle(ExePeriod);
    }break;

    /*���й���ģʽ����ERP��Դ*/
    default: 
    {
      ERPPower_OnHandle(ExePeriod);
    }break;
  }

  BSP_IO_SetOutput_ERPPowerSw(pMChair->ERPPowerSw);
}

/*
************************************************************************************************************************
* �������� : SysMode_OnOffKeyCheck                                                                                                         
* �������� : ���ػ��������                                                                                        
* ������� : ExePeriod -- ����ִ������                                                                                       
* ���ز��� : ��                                                                
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SysMode_OnOffKeyCheck(Ticker_t ExePeriod)
{
  static  uint16_t  ValidTimeMs;


  if(ON_OFF_KEY_VALID_LEVEL == BSP_IO_ReadInput_PowerKeyState())
  { 
    if(ValidTimeMs < 10000)
    ValidTimeMs += ExePeriod;
  }
  else
  {
    ValidTimeMs = 0;                                    /*�����ͷ�*/
  }

  if((ValidTimeMs > 200) && (ValidTimeMs != 0xFFFF))
  {
    if(pMChair->SysModeCur != SYS_MODE_STANDBY) 
    {
      SysMode_Standby_Enter(SYS_MODE_USERRUN, TRUE);    /*�ػ�����λ�Ƹ˽Ƕ�*/  
      ValidTimeMs = 0xFFFF;                             /*��ֹ������δ�ͷţ���һֱ�ظ��л�ϵͳģʽ*/
    }
    else
    {
      if(SUCCESS == SysMode_UserRun_Enter())
      {
        ValidTimeMs = 0xFFFF;                           /*��ֹ������δ�ͷţ���һֱ�ظ��л�ϵͳģʽ*/
      }
    }
  }
}


/*
************************************************************************************************************************
* �������� : SysMode_PauseHandle                                                                                                         
* �������� : ��ͣ����                                                                                        
* ������� : ExePeriod -- ����ִ������                                                                                       
* ���ز��� : ��                                                                
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SysMode_PauseHandle(Ticker_t ExePeriod)
{
  static uint8_t CoreGasSpikePauseOnOff = OFF;
  static uint8_t Other1PauseOnOff = OFF;
  static uint8_t Other2PauseOnOff = OFF;
  
  if(TRUE == pMChair->CSFlag.Bit.Pause)/*��ͣ���в����Ĺ���*/
  {
    PAUSE_ON(&CoreGasSpikePauseOnOff, 0, Core_PauseOn);
    PAUSE_ON(&CoreGasSpikePauseOnOff, 1, Gas_PauseOn);
    PAUSE_ON(&CoreGasSpikePauseOnOff, 2, BackSpike_PauseOn);
    PAUSE_ON(&CoreGasSpikePauseOnOff, 3, ZeroSpike_PauseOn);
    PAUSE_ON(&CoreGasSpikePauseOnOff, 4, FeetSpike_PauseOn);
    if(pMChair->CSFlag.Bit.LegFlexTestSw != TRUE)
    {
      PAUSE_ON(&CoreGasSpikePauseOnOff, 5, LegFlexSpike_PauseOn);
    }
    PAUSE_ON(&CoreGasSpikePauseOnOff, 6, BodyScan_PauseOn);

    PAUSE_ON(&Other1PauseOnOff,       0, Vib_FeetVibPauseOn);
    PAUSE_ON(&Other1PauseOnOff,       1, Vib_CalvesVibPauseOn);
    PAUSE_ON(&Other1PauseOnOff,       2, Vib_SeatVibPauseOn);
    PAUSE_ON(&Other1PauseOnOff,       3, Vib_LumbarBackVibPauseOn);
    PAUSE_ON(&Other1PauseOnOff,       4, Roller_FeetRollerPauseOn);
    PAUSE_ON(&Other1PauseOnOff,       5, Roller_CalvesRollerPauseOn);
    
    PAUSE_ON(&Other2PauseOnOff,       0, Heat_FeetHeatPauseOn);
    PAUSE_ON(&Other2PauseOnOff,       1, Heat_CalvesHeatPauseOn);
    PAUSE_ON(&Other2PauseOnOff,       2, Heat_SeatHeatPauseOn);
    PAUSE_ON(&Other2PauseOnOff,       3, Heat_LumbarBackHeatPauseOn);
    PAUSE_ON(&Other2PauseOnOff,       4, Led_PauseOn);
  }
  else
  {
    PAUSE_OFF(&CoreGasSpikePauseOnOff, 0, Core_PauseOff);
    PAUSE_OFF(&CoreGasSpikePauseOnOff, 1, Gas_PauseOff);
    PAUSE_OFF(&CoreGasSpikePauseOnOff, 2, BackSpike_PauseOff);
    PAUSE_OFF(&CoreGasSpikePauseOnOff, 3, ZeroSpike_PauseOff);
    PAUSE_OFF(&CoreGasSpikePauseOnOff, 4, FeetSpike_PauseOff);
    if(pMChair->CSFlag.Bit.LegFlexTestSw != TRUE)
    {
      PAUSE_OFF(&CoreGasSpikePauseOnOff, 5, LegFlexSpike_PauseOff);
    }
    PAUSE_OFF(&CoreGasSpikePauseOnOff, 6, BodyScan_PauseOff);
    
    PAUSE_OFF(&Other1PauseOnOff,       0, Vib_FeetVibPauseOff);
    PAUSE_OFF(&Other1PauseOnOff,       1, Vib_CalvesVibPauseOff);
    PAUSE_OFF(&Other1PauseOnOff,       2, Vib_SeatVibPauseOff);
    PAUSE_OFF(&Other1PauseOnOff,       3, Vib_LumbarBackVibPauseOff);
    PAUSE_OFF(&Other1PauseOnOff,       4, Roller_FeetRollerPauseOff);
    PAUSE_OFF(&Other1PauseOnOff,       5, Roller_CalvesRollerPauseOff);
    
    PAUSE_OFF(&Other2PauseOnOff,       0, Heat_FeetHeatPauseOff);
    PAUSE_OFF(&Other2PauseOnOff,       1, Heat_CalvesHeatPauseOff);
    PAUSE_OFF(&Other2PauseOnOff,       2, Heat_SeatHeatPauseOff);
    PAUSE_OFF(&Other2PauseOnOff,       3, Heat_LumbarBackHeatPauseOff);
    PAUSE_OFF(&Other2PauseOnOff,       4, Led_PauseOff);
  }
}

/*
========================================================================================================================
*      ϵͳģʽ ���ܺ��� �����                 ϵͳģʽ ���ܺ��� �����                  ϵͳģʽ ���ܺ��� �����
========================================================================================================================
*/
#define  SYSMODE_TICK_COUNT_BUF_NUM   13
static Ticker_t SysMode_TickCount[SYSMODE_TICK_COUNT_BUF_NUM];

static const ESF_TmrExeFunc_t  SysMode_TmrExeFuncTab[] = 
{
  /*   ִ�к���                  ִ������(ms)  ʱ���������*/

  {SysMode_PauseHandle,                       13,        &SysMode_TickCount[0]},  /*��ͣ����*/
  {SysMode_ERPPowerHandle,                    19,        &SysMode_TickCount[1]},  /*ERP��Դ���Ŀ���*/

  {SysMode_UserRun_Timer,                     1000,      &SysMode_TickCount[2]},  /*��Ħ��ʱ������*/
  {SysMode_InspectAuto_Timer,                 1000,      &SysMode_TickCount[3]},  /*�Լ�*/
  {SysMode_InspectManual_Timer,               1000,      &SysMode_TickCount[4]},  /*�ּ�*/
  {SysMode_TestSpike_Timer,                   1000,      &SysMode_TickCount[5]},  /*�����Ƹ�*/
  {SysMode_InspectOther1_Timer,               1000,      &SysMode_TickCount[6]},  /*�������Ҽ�� 1*/
  {SysMode_InspectOther2_Timer,               1000,      &SysMode_TickCount[7]},  /*�������Ҽ�� 2*/

  {SysMode_OnOffKeyCheck,                     111,       &SysMode_TickCount[10]},  /*���ػ��������*/
  {MChair_FuncExe,                            20,        &SysMode_TickCount[11]},  /*��Ħ���ܵ�ִ��*/
  
  {SysMode_StandBy_EngiModeSelcetTLHandle,    1011,      &SysMode_TickCount[12]}   /*����ģʽѡ��ʱ�䳤�ȴ��� */
}; 

#define  SYSMODE_TMR_EXE_FUNC_TAB_NUM     TAB_NUM(SysMode_TmrExeFuncTab)


/*
************************************************************************************************************************
* �������� : SysMode_Init                                                                                                         
* �������� : ϵͳģʽ  ��ʼ��                                                                                        
* ������� : ��                                                                                     
* ���ز��� : ��                                                                
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SysMode_Init(void)
{
  SysMode_Standby_Init();
  SysMode_UserRun_Init();
  SysMode_InspectAuto_Init();
  SysMode_InspectManual_Init();
  SysMode_TestSpike_Init();
  SysMode_InspectOther1_Init();
  SysMode_InspectOther2_Init();
  SysMode_Standby_Enter(SYS_MODE_NONE, TRUE);    /*�ϵ��ʼʱ �������ģʽ*/

  /*��� SysMode_TmrExeFuncTab ���ܺ����������Ƿ���ȷ------------------------*/
  ESF_TmrExeFuncTabCheck(SysMode_TmrExeFuncTab, SYSMODE_TMR_EXE_FUNC_TAB_NUM, SYSMODE_TICK_COUNT_BUF_NUM);
}

/*
************************************************************************************************************************
* �������� : SysMode_Pause_Handle                                                                                                         
* �������� : ϵͳģʽ ����                                                                                        
* ������� : ��                                                                                     
* ���ز��� : ��                                                                
* ����˵�� : �ϵ�Ĭ�Ͻ��� SYS_MODE_STANDBY ����ģʽ���ػ�ģʽ��                                                                                                         
************************************************************************************************************************
*/
static const SysModeHandleItem_t SysModeHandleTab[] = 
{
  {SYS_MODE_STANDBY,            SysMode_Standby_Handle},         /*����*/

  /*��������𲻴󣬹���SysMode_UserRun_Handle������� SysMode_UserRun_Timer()�����д���*/
  {SYS_MODE_USERRUN,            SysMode_UserRun_Handle},         /*�û�����*/
  {SYS_MODE_TESTNOTIMER,        SysMode_UserRun_Handle},         /*���ҿ��� ֮ �޶�ʱ����ģʽ, ������������*/
  {SYS_MODE_TESTAGE,            SysMode_UserRun_Handle},         /*���ҿ��� ֮ ������ ��һСʱ��ͣ15����*/

  {SYS_MODE_INSPECTAUTO,        SysMode_InspectAuto_Handle},     /*�����Լ�*/
  {SYS_MODE_INSPECTMANUAL,      SysMode_InspectManual_Handle},   /*�����ּ�*/
  {SYS_MODE_TESTSPIKE,          SysMode_TestSpike_Handle},       /*���ҿ��� ֮ �Ƹ�*/
  {SYS_MODE_PACKING,            SysMode_Packing_Handle},         /*���Ұ�װ*/
  {SYS_MODE_INSPECTOTHER1,      SysMode_InspectOther1_Handle},   /*�������Ҽ�� 1*/
  {SYS_MODE_INSPECTOTHER2,      SysMode_InspectOther2_Handle}    /*�������Ҽ�� 2*/
};

#define  SYSMODE_HANDLE_TAB_NUM    TAB_NUM(SysModeHandleTab)

void SysMode_Handle(void)
{
  uint8_t i;

  /*ϵͳģʽ����-------------------------------------------------*/
  for(i=0; i<SYSMODE_HANDLE_TAB_NUM; i++)
  {
    if(pMChair->SysModeCur == SysModeHandleTab[i].Mode)
    {
      if(SysModeHandleTab[i].pHandle != NULL)
      {
        SysModeHandleTab[i].pHandle();        /*���뵽���������ģʽ������*/
      }
      break;
    }
  }

  if(i >= SYSMODE_HANDLE_TAB_NUM)             /*SysModeCurֵ����������������ģʽ*/
  {
    pMChair->SysModeCur = SYS_MODE_STANDBY;
  }

  if(SYS_MODE_STANDBY == pMChair->SysModeCur) 
  {
    pMChair->CSFlag.Bit.SysRun = FALSE;       /*����ģʽ*/
  }
  else
  {
    pMChair->CSFlag.Bit.SysRun = TRUE;        /*ϵͳ���У��� ����ģʽ*/
  }

  /*���ȹ��ܺ�����------------------------------------------------*/
  ESF_TmrExeFuncScheduling(SysMode_TmrExeFuncTab, SYSMODE_TMR_EXE_FUNC_TAB_NUM);
}
