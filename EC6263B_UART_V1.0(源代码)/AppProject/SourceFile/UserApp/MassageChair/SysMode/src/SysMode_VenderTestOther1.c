/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: SysMode_VenderTestOther.c 
**
**    ��������: ϵͳģʽ ֮  �������� 1
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
* �������� : TestOther1_Key_Power                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t TestOther1_Key_Power(uint8_t *pData)
{
  return SysMode_Standby_Enter(SYS_MODE_INSPECTAUTO, TRUE);
}

/*
************************************************************************************************************************
* �������� : TestOther1_Key_SpikeFeetUp                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                 
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t TestOther1_Key_SpikeFeetUp(uint8_t *pData)
{
  Spike_SetFeetAngle(Spike_GetFeetAngle() + 1);
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : TestOther1_Key_SpikeFeetDown                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                 
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t TestOther1_Key_SpikeFeetDown(uint8_t *pData)
{
  if(Spike_GetFeetAngle() > 0)
  {
    Spike_SetFeetAngle(Spike_GetFeetAngle() - 1);
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : TestOther1_Key_SpikeBackUpFeetDown                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                 
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t TestOther1_Key_SpikeBackUpFeetDown(uint8_t *pData)
{
  if(Spike_GetBackAngle() > 0)
  {
    Spike_SetBackAngle(Spike_GetBackAngle() - 1);
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : TestOther1_Key_SpikeBackDownFeetUp                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                 
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t TestOther1_Key_SpikeBackDownFeetUp(uint8_t *pData)
{
  Spike_SetBackAngle(Spike_GetBackAngle() + 1);
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : TestOther1_Key_CoreWidth                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t TestOther1_Key_CoreWidth(uint8_t *pData)
{
  pMChair->MannualCoreWidth++;
  if(pMChair->MannualCoreWidth > PX_MAX)
  {
    pMChair->MannualCoreWidth = PX_MIN;
  }
  Core_SetXPosition(pMChair->MannualCoreWidth); 
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : TestOther1_Key_CoreMannualUp                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t TestOther1_Key_CoreMannualUp(uint8_t *pData)
{
  if(Core_GetYPosition() > PY_MIN)
  {
    Core_SetYPosition(Core_GetYPosition()-1); 
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : TestOther1_Key_CoreMannualDown                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t TestOther1_Key_CoreMannualDown(uint8_t *pData)
{
  Core_SetYPosition(Core_GetYPosition()+1); 
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : TestOther1_Key_CoreMannualFront                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t TestOther1_Key_CoreMannualFront(uint8_t *pData)
{
  if(pMChair->MannualCoreFlexLevel < PZ_MAX)
  {
    pMChair->MannualCoreFlexLevel++;
  }
  Core_SetZPosition(pMChair->MannualCoreFlexLevel); 
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : TestOther1_Key_CoreMannualBack                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t TestOther1_Key_CoreMannualBack(uint8_t *pData)
{
  if(pMChair->MannualCoreFlexLevel > PZ_MIN)
  {
    pMChair->MannualCoreFlexLevel--;
  }
  Core_SetZPosition(pMChair->MannualCoreFlexLevel); 
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : TestOther1_Key_CoreFlexLevel                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t TestOther1_Key_CoreFlexLevel(uint8_t *pData)
{
  pMChair->MannualCoreFlexLevel++;
  if(pMChair->MannualCoreFlexLevel > PZ_MAX)
  {
    pMChair->MannualCoreFlexLevel = PZ_MIN;
  }
  Core_SetZPosition(pMChair->MannualCoreFlexLevel); 
  return SUCCESS;
}

/*����������������������������������������������������������������������������������������������������������������������*/
static const SysMode_KeyLogicTabItem_t TestOther1_KeyLogicTab[] = /*��ֵ��*/
{
  /*���Ӳ�����

    ��ִֵ��ǰ��bit7 -- 1��ERP����Դ�رգ����ִֵ��ǰ��Ҫ���¿�����    
                        0��ERP����Դ�رգ����ִֵ��ǰ������Ҫ���¿�����    

    ��ִֵ�к�                                                   */

  {KEYVAL_Power,                    B(00000000),    TestOther1_Key_Power},

  {KEYVAL_SpikeFeetUp,              B(10000000),    TestOther1_Key_SpikeFeetUp},
  {KEYVAL_SpikeFeetDown,            B(10000000),    TestOther1_Key_SpikeFeetDown},
  {KEYVAL_SpikeBackUpFeetDown,      B(10000000),    TestOther1_Key_SpikeBackUpFeetDown},
  {KEYVAL_SpikeBackDownFeetUp,      B(10000000),    TestOther1_Key_SpikeBackDownFeetUp},

  {KEYVAL_CoreWidth,                B(00000000),    TestOther1_Key_CoreWidth},
  {KEYVAL_CoreMannualUp,            B(00000000),    TestOther1_Key_CoreMannualUp},
  {KEYVAL_CoreMannualDown,          B(00000000),    TestOther1_Key_CoreMannualDown},
  {KEYVAL_CoreMannualFront,         B(00000000),    TestOther1_Key_CoreMannualFront},
  {KEYVAL_CoreMannualBack,          B(00000000),    TestOther1_Key_CoreMannualBack},
  {KEYVAL_CoreFlexLevel,            B(00000000),    TestOther1_Key_CoreFlexLevel},

  /*---------------------------------------------------*/
  {KEYVAL_MAX,                      B(00000000),    NULL}
};

#define TESTOTHER1_KEY_TAB_NUM  TAB_NUM(TestOther1_KeyLogicTab)

static uint16_t TestOther1_GetKeyValID(uint16_t index)
{
  if(index > (TESTOTHER1_KEY_TAB_NUM-1))
  {
    return INDEX_NO_MATCH;
  }
  return TestOther1_KeyLogicTab[index].KeyValID;
}


/*
************************************************************************************************************************
* �������� : SysMode_TestOther1_Timer                                                                                                         
* �������� : �������� 1 ��ʱ�� ����                                                                                     
* ������� : ExePeriod -- ִ������                                                                    
* ���ز��� : ��                                                           
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SysMode_TestOther1_Timer(Ticker_t ExePeriod)
{
  static  Ticker_t  SysPeriod;
  static  Ticker_t  Period;
  uint8_t zmax;
  static  uint8_t PauseOnOff = OFF;
  
  Heat_SetLumbarBackHeatWorkState(TRUE);
  
  SysPeriod++;
  if(SysPeriod > (3600+900)) 
  {
    SysPeriod = 0;             /*1h+15min �����¼�ʱ*/
    PAUSE_OFF(&PauseOnOff, 0, Heat_LumbarBackHeatPauseOff);
    PAUSE_OFF(&PauseOnOff, 1, Core_PauseOff);
  }
  else if(SysPeriod > 3600)
  {
    PAUSE_ON(&PauseOnOff, 0, Heat_LumbarBackHeatPauseOn);
    PAUSE_ON(&PauseOnOff, 1, Core_PauseOn);
  }
  
  
  Core_SetAction(CORE_ACTION_EXE_MANNNUAL, KNIN, NO_FB_TAP);  
  Core_SetXYZActionSpeed(7);
  Core_SetTCSActionSpeed(5);

  if(Core_GetYPosition() <= 9)
  {
    zmax  = 4 ;
  }
  else if(Core_GetYPosition() <= 22)
  {
    zmax  = 3 ;
  }
  else 
  {
    zmax  = 2 ;
  }  
  
  Period += ExePeriod;
  if(Period < 5000)
  {
    Core_SetZPosition(0);
  }
  else if(Period < 10000)
  {
    Core_SetZPosition(zmax);
  }
  else
  {
    Period = 0;
  }
}

/*
************************************************************************************************************************
* �������� : SysMode_TestOther1_Init                                                                                                         
* �������� : ϵͳģʽ ֮ �������� 1 ��ʼ��                                                                                     
* ������� : ��                                                                               
* ���ز��� : ��                                                           
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SysMode_TestOther1_Init(void)
{

}


/*
************************************************************************************************************************
* �������� : SysMode_TestOther1_Handle                                                                                                         
* �������� : ϵͳģʽ ֮ �������� 1 ����                                                                                     
* ������� : ��                                                                              
* ���ز��� : ��                                                               
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SysMode_TestOther1_Handle(void)
{
  /*����ģʽ�л�����-----------------------------------------------------*/
  if(pMChair->SysModeHis != pMChair->SysModeCur)      
  {
    pMChair->SysModeHis = pMChair->SysModeCur; 
  }

  /*���ݸ���ģʽ�Ĳ�ͬ���Լ�ֵ������ر�����ֵ---------------------------*/
  pMChair->KeyValHandle.KeyLogicTab    = TestOther1_KeyLogicTab;      /*�����߼���*/
  pMChair->KeyValHandle.KeyLogicTabNum = TESTOTHER1_KEY_TAB_NUM;      /*�����߼��� ��С*/
  pMChair->KeyValHandle.pGetMatchID    = TestOther1_GetKeyValID;      /*����ָ�룬ָ��ĺ������ã����ر����Ŀ �� ��Ҫ���������� ���ڵ�����*/
  pMChair->KeyValHandle.pAddOp         = NULL;                        /*����ָ�룬ָ��ĺ������ã���ִֵ��ǰ��ĸ��Ӳ��� */
}
