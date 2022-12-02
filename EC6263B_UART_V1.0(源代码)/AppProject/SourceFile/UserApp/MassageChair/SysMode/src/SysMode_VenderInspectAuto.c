/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: SysMode_VenderInspectAuto.c 
**
**    ��������: ϵͳģʽ ֮  �����Լ�
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
* �������� : SysMode_InspectAuto_Timer                                                                                                         
* �������� : �����Լ� ��ʱ�� ����                                                                                        
* ������� : ExePeriod -- ִ������                                                                                     
* ���ز��� : ��                                                                
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SysMode_InspectAuto_Timer(Ticker_t ExePeriod)
{
  //static uint8_t CoreSpikePauseOnOff = OFF;

  if(pMChair->SysModeCur != SYS_MODE_INSPECTAUTO)
  {
    return;
  }

  /*�� ��&��  ��&��-----------------------------------------------*/
  Heat_SetLumbarBackHeatWorkState(TRUE);
  Roller_SetFeetRollerWorkState(TRUE);
  Roller_SetCalvesRollerWorkState(TRUE);
  Led_SetLogoWorkState(TRUE);  
  Led_SetProjectionWorkState(TRUE);  

  /*���û�--------------------------------------------------------*/
  Core_SetTCSAction(CORE_ACTION_EXE_NONE, TAP);

  /*��о ����-----------------------------------------------*/
  pMChair->VenderInspect.CoreFlexTimeMs += ExePeriod;
  switch(pMChair->VenderInspect.CoreFlexStep)
  {
    case 0:
    {
      Core_SetZPosition(PZ_MAX);
      if(PZ_MAX == Core_GetZPosition())
      {
        pMChair->VenderInspect.CoreFlexStep++;
        pMChair->VenderInspect.CoreFlexTimeMs = 0;
      }
    }break;

    case 1:
    {
      Core_SetZPosition(PZ00);
      if(PZ00 == Core_GetZPosition())
      {
        pMChair->VenderInspect.CoreFlexTimeMs = 0;
        pMChair->VenderInspect.CoreFlexStep = 255;
      }
    }break;

    default: break;
  }

  /*��о ����-----------------------------------------------*/
  pMChair->VenderInspect.CoreKneadTimeMs += ExePeriod;
  switch(pMChair->VenderInspect.CoreKneadStep)
  {
    case 0:
    {
      Core_SetXPosition(PX00);
      if(PX00 == Core_GetXPosition())
      {
        pMChair->VenderInspect.CoreKneadTimeMs = 0;
        pMChair->VenderInspect.CoreKneadStep++;
      }
    }break;

    case 1:
    {
      Core_SetXPosition(PX02);
      if(PX02 == Core_GetXPosition())
      {
        pMChair->VenderInspect.CoreKneadTimeMs = 0;
        pMChair->VenderInspect.CoreKneadStep = 255;
      }
    }break;

    default:break;
  }

  /*��о ����(����)-------------------------------------------------------*/
  pMChair->VenderInspect.CoreRollTimeMs += ExePeriod;
  switch(pMChair->VenderInspect.CoreRollStep)
  {
    case 0:
    {
      Core_SetYPosition(PY_MAX);
      if(PY_MAX == Core_GetYPosition())
      {
        pMChair->VenderInspect.CoreRollTimeMs = 0;
        pMChair->VenderInspect.CoreRollStep++;
      }
    }break;

    case 1:
    {
      Core_SetYPosition(PY00);
      if(PY00 == Core_GetYPosition())
      {
        pMChair->VenderInspect.CoreRollTimeMs = 0;
        pMChair->VenderInspect.CoreRollStep = 255;
      }

    }break;

    default: break;
  }

  /*�����Ƹ�--------------------------------------------------------*/
  pMChair->VenderInspect.BackSpikeTimeMs += ExePeriod;
  switch(pMChair->VenderInspect.BackSpikeStep)
  {
    case 0:
    {
      Spike_SetBackAngle(PBACK_MAX);
      if(PBACK_MAX == Spike_GetBackAngle())
      {
        pMChair->VenderInspect.BackSpikeTimeMs = 0;
        pMChair->VenderInspect.BackSpikeStep++;
      }
    }break;

    case 1:
    {
      Spike_SetBackAngle(PBACK00);
      if(PBACK00 == Spike_GetBackAngle())
      {
        pMChair->VenderInspect.BackSpikeTimeMs = 0;
        pMChair->VenderInspect.BackSpikeStep = 255;
      }
    }break;

    default: break;
  }

  /*С���Ƹ�--------------------------------------------------------*/
  pMChair->VenderInspect.FeetSpikeTimeMs += ExePeriod;
  switch(pMChair->VenderInspect.FeetSpikeStep)
  {
    case 0:
    {
      Spike_SetFeetAngle(PFEET_MAX);
      if(PFEET_MAX == Spike_GetFeetAngle())
      {
        pMChair->VenderInspect.FeetSpikeTimeMs = 0;
        if(0 == BSP_IO_GetVenderTestPin())      /*��װ�����*/
        {
          pMChair->VenderInspect.FeetSpikeStep = 3;
        }
        else 
        {
          pMChair->VenderInspect.FeetSpikeStep++;
        }          
      }
    }break;
    
    case 1:
    {
      Spike_SetLegFlexMove(SPIKE_MOVE_LEG_EXTEND);
      if((TRUE == LegFlexSpike_GetCSFlag().Bit.ReachExtendLimt) || (TRUE == LegFlexSpike_GetCSFlag().Bit.TouchGround))         //ֹͣ����Ҫ���ϴ���
      {
        pMChair->VenderInspect.FeetSpikeTimeMs = 0;
        pMChair->VenderInspect.FeetSpikeStep++;
      }
    }break;
    
    case 2:
    {
      Spike_SetLegFlexMove(SPIKE_MOVE_LEG_SHORT);
      if((TRUE == LegFlexSpike_GetCSFlag().Bit.ReachShortenLimt) || (TRUE == LegFlexSpike_GetCSFlag().Bit.TouchFeet))
      {
        pMChair->VenderInspect.FeetSpikeTimeMs = 0;
        pMChair->VenderInspect.FeetSpikeStep++;
      }
    }break;

    case 3:
    {
      Spike_SetFeetAngle(PFEET00);
      if(PFEET00 == Spike_GetFeetAngle())
      {
        pMChair->VenderInspect.FeetSpikeTimeMs = 0;
        pMChair->VenderInspect.FeetSpikeStep = 255;
      }
    }break;

    default: break;
  }

  /*�������Ƹ�------------------------------------------------------*/


  /*����������-------------------------------------------------------*/
  Gas_SetPumpSw(ON);
  Gas_AllCtrlEn();
  pMChair->CommonTimeSec++;
  switch(pMChair->CommonTimeSec>>1)
  {
    case 0: Gas_SetGasPart(B(11111111), B(11111111)); break; 
    default:
    {
      Gas_SetGasPart(B(00000000), B(00000000));  
      pMChair->CommonTimeSec = 0;
    }break;
  }
//  Gas_SetGasPart(B(11111111), B(11111111));  
//  pMChair->CommonTimeSec++;
//  switch(pMChair->CommonTimeSec>>2)
//  {
//    case 0: Gas_SetGasPart(B(00100000), B(00000000)); break; /*�粿*/
//    case 1: Gas_SetGasPart(B(00010000), B(00000000)); break; /*�ֲ�*/
//    case 2: Gas_SetGasPart(B(00001000), B(00000000)); break; /*����*/
//    case 3: Gas_SetGasPart(B(00000100), B(00000000)); break; /*�ȱ�*/
//    case 4: Gas_SetGasPart(B(00000010), B(00000000)); break; /*������*/
//    case 5: Gas_SetGasPart(B(00000001), B(00000000)); break; /*������*/
//    default:
//    {
//      Gas_SetGasPart(B(00000000), B(00000000));  
//      pMChair->CommonTimeSec = 0;
//    }break;
//  }

  /*=================================================================*/
  if((255 == pMChair->VenderInspect.CoreFlexStep)  &&
     (255 == pMChair->VenderInspect.CoreKneadStep) &&
     (255 == pMChair->VenderInspect.CoreRollStep)  &&
     (255 == pMChair->VenderInspect.BackSpikeStep) &&
     (255 == pMChair->VenderInspect.FeetSpikeStep) )
  {
    Core_SetTCSAction(CORE_ACTION_EXE_NONE, TCS_ACTION_NONE);
    pMChair->CSFlag.Bit.VenderOpFinish = TRUE; /*���Ҳ������*/
  }
}

/*
************************************************************************************************************************
* �������� : SysMode_InspectAuto_Init                                                                                                         
* �������� : ϵͳģʽ ֮ �����Լ� ��ʼ��                                                                                        
* ������� : ��                                                                                     
* ���ز��� : ��                                                                
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SysMode_InspectAuto_Init(void)
{

}

/*
************************************************************************************************************************
* �������� : SysMode_InspectAuto_Handle                                                                                                         
* �������� : ϵͳģʽ ֮ �����Լ� ����                                                                                        
* ������� : ��                                                                                     
* ���ز��� : ��                                                                
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SysMode_InspectAuto_Handle(void)
{
  /*����ģʽ�л�����-----------------------------------------------------*/
  if(pMChair->SysModeHis != pMChair->SysModeCur)      
  {
    /*���ģʽ�£������Ƹ˵ļ������ϼ�⿪��*/
    BackSpike_SetCountFaultCheckSw(ON);           
    FeetSpike_SetCountFaultCheckSw(ON);
    ZeroSpike_SetCountFaultCheckSw(ON);
    
    pMChair->SysModeHis = pMChair->SysModeCur; 
  }

  /*���ݸ���ģʽ�Ĳ�ͬ���Լ�ֵ������ر�����ֵ---------------------------*/
  SysMode_DefaultKeyValHandle();
}
