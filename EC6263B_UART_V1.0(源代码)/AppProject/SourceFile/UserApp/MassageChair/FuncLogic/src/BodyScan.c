/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣ�BodyScan.c 
**
**    ��������: ����ɨ��
**
**    ��    ˾���ɷ�������
**
**    ��Ŀ���ƣ�
**
**    ƽ̨��Ϣ��
**
**    ��    �ߣ�Hzy
**
**    ����˵��: �������������ߡ��������ߡ���ʹ�����ʵȡ�һ���ߺͱ��������ɻ�о������ɡ�
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
#include "BodyScan.h"
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
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
========================================================================================================================
*/
static BodyScan_t BodyScan;
BodyScan_t *pBodyScan = &BodyScan;


/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : BodyScan_Init                                                                                                         
* �������� : ����ɨ�� ��ʼ��                                                                                        
* ������� : ��                                                                                      
* ���ز��� : ���� �ɲ���ɨ�蹦�� �Ľṹ�� ��ָ��                                                               
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
BodyScan_t*  BodyScan_Init(void)
{
  memset(pBodyScan, 0, sizeof(BodyScan_t));       /*������������*/
  Core_BackScanSetReScanCheckSw(ON);
  
  Spike_SetLegLenDetectExtendMax(3);//PLEGFLEX_MAX);
  
  return pBodyScan;
}

/*
************************************************************************************************************************
* �������� : BodyScan_ShoulderReCheck                                                                                                         
* �������� : ����ɨ�� ���¼��                                                                                   
* ������� : ��                                                                                      
* ���ز��� : SUCCESS -- ִ�гɹ�   FAIL -- ִ��ʧ��                                                             
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t BodyScan_ShoulderReCheck(void)
{
  BodyScan_Init();                                  /*��ʼ������������ݼ�������ɨ����*/
  pBodyScan->CSFlag.Bit.ShoulderReCheck = TRUE;     /*��ʶ�粿���¼����*/
  Core_ShoulderAdjustRe();
  return SUCCESS;
}


/*
************************************************************************************************************************
* �������� : BodyScan_PauseOn                                                                                                      
* �������� : ��ͣ                                                               
* ������� : ��                                                                     
* ���ز��� : ��                                                     
* ����˵�� : ��                                                                                                       
************************************************************************************************************************
*/
void BodyScan_PauseOn(void)
{
  if(pBodyScan->CSFlag.Bit.Pause < 0x1F)
  {
    pBodyScan->CSFlag.Bit.Pause++;
  }
}

/*
************************************************************************************************************************
* �������� : BodyScan_PauseOff                                                                                                      
* �������� : �����ͣ                                                          
* ������� : ��                                                                     
* ���ز��� : ��                                                     
* ����˵�� : ��                                                                                                       
************************************************************************************************************************
*/
void BodyScan_PauseOff(void)
{
  if(pBodyScan->CSFlag.Bit.Pause > 0)
  {
    pBodyScan->CSFlag.Bit.Pause--;
  }
}

/*
************************************************************************************************************************
* �������� : BodyScan_Handle                                                                                                         
* �������� : ����ɨ�� ����                                                                      
* ������� : ExePeriod -- ����ִ������                                                                           
* ���ز��� : ��                                          
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void BodyScan_Handle(Ticker_t ExePeriod)
{
  static uint8_t PauseOnOff = OFF;
  
  pBodyScan->CSFlag.Bit.Finish           = Core_BackScanGetCSFlag().Bit.Finish;  
//  pBodyScan->CSFlag.Bit.NoHumanOnSeat    = Core_BackScanGetCSFlag().Bit.NoHumanOnSeat;  
  pBodyScan->CSFlag.Bit.ShoulderAdjustEn = Core_BackScanGetCSFlag().Bit.ShoulderAdjustEn;  
  Core_BackScanSetRunSw(pBodyScan->CSFlag.Bit.Run);
  Core_BackScanSetCurveCheckSw(ON);
  if(FALSE == pBodyScan->CSFlag.Bit.NoHumanOnSeat)                         
  {
    pBodyScan->CSFlag.Bit.NoHumanOnSeat = Core_BackScanGetCSFlag().Bit.NoHumanOnSeat;  
  }
  if(0 == BSP_IO_GetVenderTestPin())      /*��װ����£�ǿ������������Ч��������������*/
  {
    pBodyScan->CSFlag.Bit.NoHumanOnSeat = FALSE;
    pBodyScan->CSFlag.Bit.Finish = TRUE;
  }
  
  /*ִ��ɨ��� �����ж�----------------------------------------------------------*/
  if(pBodyScan->CSFlag.Bit.Pause > 0)                                           /*��ͣ*/
  {
    PAUSE_ON(&PauseOnOff, 0, Core_BackScanPauseOn);
    return;
  }
  else
  {
    PAUSE_OFF(&PauseOnOff, 0, Core_BackScanPauseOff);
  }

  if((pMChair->SysModeCur != SYS_MODE_USERRUN)     &&                           /*������ģʽ��𲻴󣬲���� SysMode_UserRun_Timer()�����д���*/ 
     (pMChair->SysModeCur != SYS_MODE_TESTNOTIMER) &&                            
     (pMChair->SysModeCur != SYS_MODE_TESTAGE)     )
  {
    pBodyScan->CSFlag.Bit.Run = OFF;    
    return;
  }


  if(TRUE == pBodyScan->CSFlag.Bit.Finish)                                      /*ɨ���Ѿ����*/
  {
    pBodyScan->CSFlag.Bit.Run = OFF;    
    return;
  }

  if((FUNC_TYPE_AUTO    == pMChair->ComponentFuncState.Bit.Core) ||             /*��о�������Զ� ����ɨ��*/
     (FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core) )              /*��о�������ֶ� Ҳ����ɨ��*/ 
  {
    pBodyScan->CSFlag.Bit.Run = ON;                                             
  }
  else
  {
    pBodyScan->CSFlag.Bit.Run = OFF;                                            /*�ر�ɨ��*/
  }
  
  if(OFF == pBodyScan->CSFlag.Bit.Run)
  {
    pBodyScan->ScanStep = 0;      
    pBodyScan->ScanStepTimeMs = 0;
    return;
  }

  /*����ɨ�账��-----------------------------------------------------------------*/
  pBodyScan->ScanStepTimeMs += ExePeriod;                                       /*ɨ�貽��ʱ��*/
  switch(pBodyScan->ScanStep)
  {
    case 0:
    {
      Spike_SetAngle(PBACK05, PFEET07, PZERO_USER_ANGLE); 
      pBodyScan->ScanStep++;
    }break;
    
    case 1:
    {
      if(pBodyScan->ScanStepTimeMs > 1000)
      {
        pBodyScan->ScanStepTimeMs = 0;
        if(TRUE == pBodyScan->CSFlag.Bit.ShoulderAdjustEn)                          /*�粿���ɵ�ʱ������ʾ��*/
        {
          if(Core_BackScanGetYCount() < 50)
          {
            Spike_SetLegLenDetectExtendMax(6);
          }
          else if(Core_BackScanGetYCount() < 100)
          {
            Spike_SetLegLenDetectExtendMax(5);
          }
          else if(Core_BackScanGetYCount() < 160)
          {
            Spike_SetLegLenDetectExtendMax(4);
          }
          else if(Core_BackScanGetYCount() < 220)
          {
            Spike_SetLegLenDetectExtendMax(3);
          }
          else //if(Core_BackScanGetYCount() < 200)
          {
            Spike_SetLegLenDetectExtendMax(2);
          }
          //else
          //{
          //  Spike_SetLegLenDetectExtendMax(1);
          //}
          pMChair->PromptToneTLMs = 300;                             
        }
      }    
    }break;
  
    default:
    {
    }break;
  } 
}

/*
************************************************************************************************************************
* �������� : BodyScan_GetCSFlag                                                                                                         
* �������� : ��� ���� �� ״̬ ��ʶ                                                             
* ������� : ��                                                                      
* ���ز��� : ������״̬��ʶ �Ľṹ��                                          
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
BodyScanCSFlag_t BodyScan_GetCSFlag(void)
{
  return pBodyScan->CSFlag;
}
