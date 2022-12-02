/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: SysMode_UserRun.c 
**
**    ��������: ϵͳģʽ  ֮  �û�����
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
#pragma  diag_suppress 177            /*����mdk�У�����������û�����õĸ澯*/

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
extern uint8_t StandBy_Key_SpikeBackUp(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeBackDown(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeFeetUp(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeFeetDown(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeBackUpFeetDown(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeBackDownFeetUp(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeZeroGravity(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeLegExtend(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeLegShorten(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeULegExtend(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeULegShorten(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeZeroGravity1(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeZeroGravity2(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeHomeReset(uint8_t *pData);

/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/

/*
************************************************************************************************************************
* �������� : UserRun_Key_NoKeyPress                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_NoKeyPress(uint8_t *pData)
{
  /*�����������ͷŴ���---------------------------------------------*/
  Core_SetMoveAdjustRoll(CORE_MOVE_ADJUST_NONE);                /*��о���µ��� �ĳ����ͷ�*/
  
  #if (SHOULDER_ADJUST_KEY_L == SHOULDER_ADJUST_KEY_LSMODE)     /*�粿���ڳ������ͷ�*/
  BodyScan_UserAdjustShoulder(SHOULDER_ADJUST_NONE, SHOULDER_ADJUST_KEY_LSMODE);
  #endif

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)                   /*�Ƹ�Ϊ����*/
  pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;    /*�����Ƹ� �ĳ����ͷ�*/
  pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;    /*С���Ƹ� �ĳ����ͷ�*/
  #endif

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_Power                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_Power(uint8_t *pData)
{
  return SysMode_Standby_Enter(SYS_MODE_USERRUN, TRUE);    /*�ػ�����λ�Ƹ˽Ƕ�*/
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_Pause                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_Pause(uint8_t *pData)
{
//  if(TRUE == pMChair->CSFlag.Bit.UserMassageTimeOut)
//  {
//    return FAIL;  /*��Ħ��ʱ���󣬲���Ӧ��ͣ����*/
//  }
  
  if(FALSE == pMChair->CSFlag.Bit.Pause)
  {
    pMChair->CSFlag.Bit.Pause = TRUE;
  }
  else
  {
    pMChair->CSFlag.Bit.Pause = FALSE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_TimerAdd                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_TimerAdd(uint8_t *pData)
{
  if(TRUE == pMChair->CSFlag.Bit.UserMassageTimeOut)
  {
    return FAIL; /*��ʱ��ʱ�䲻�ɵ�*/
  }

  pMChair->UserMassageTimeDelayOnSec = 0;
  pMChair->UserMassageTimeSec = 0;

  pMChair->UserMassageTimeMin += (5 - (pMChair->UserMassageTimeMin%5));
  if(pMChair->UserMassageTimeMin > 30)
  {
    pMChair->UserMassageTimeMin = 30;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_TimerDec                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_TimerDec(uint8_t *pData)
{
  if(TRUE == pMChair->CSFlag.Bit.UserMassageTimeOut)
  {
    return FAIL; /*��ʱ��ʱ�䲻�ɵ�*/
  }

  if(pMChair->UserMassageTimeMin < 5)
  {
    return FAIL;
  }

  pMChair->UserMassageTimeDelayOnSec = 0;
  pMChair->UserMassageTimeSec = 0;

  if((pMChair->UserMassageTimeMin%5) == 0)
  {
    pMChair->UserMassageTimeMin -= 5;
  }
  else
  {
    pMChair->UserMassageTimeMin -= (pMChair->UserMassageTimeMin%5);
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_Timer                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_Timer(uint8_t *pData)
{
  if((SYS_MODE_TESTAGE == pMChair->SysModeCur)    || 
     (SYS_MODE_TESTNOTIMER == pMChair->SysModeCur))
  {
    MChair_CoreMannualVenderTest3DSwSet(1);       /*���ҿ������Զ�����������һ��Ҫ�ȿ��ֶ����򣬲��ܴ�����*/
    if(pMChair->UserMassageTimeMin == 20)         /*ʱ��Ϊ20��ʱ���²ſ���С�������������Կ���*/
    {
      pMChair->CSFlag.Bit.LegFlexTestSw = TRUE;
    }
  }
  
  /*-------------------------------------------------------------------*/
  if(TRUE == pMChair->CSFlag.Bit.UserMassageTimeOut)
  {
    return FAIL; /*��ʱ��ʱ�䲻�ɵ�*/
  }

  pMChair->UserMassageTimeDelayOnSec = 0;
  pMChair->UserMassageTimeSec = 0;

  if(pMChair->UserMassageTimeMin >= 30)
  {
    pMChair->UserMassageTimeMin = 5;
  }
  else
  {
    pMChair->UserMassageTimeMin += (5 - (pMChair->UserMassageTimeMin%5));
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_BodyCheckOk                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_BodyCheckOk(uint8_t *pData)
{
  return BodyScan_UserAdjustShoulder(SHOULDER_ADJUST_FINISH, SHOULDER_ADJUST_KEY_LSMODE);
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_BodyReCheck                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_BodyReCheck(uint8_t *pData)
{
  return BodyScan_ShoulderReCheck();
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_BluetoothSwitch                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_BluetoothSwitch(uint8_t *pData)
{
  pMChair->CSFlag.Bit.BluetoothSwitch = !pMChair->CSFlag.Bit.BluetoothSwitch;

  BSP_IO_SetOutput_BluetoothSwitch(pMChair->CSFlag.Bit.BluetoothSwitch);
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_SpikeBackUp                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeBackUp      StandBy_Key_SpikeBackUp
//static uint8_t UserRun_Key_SpikeBackUp(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* �������� : UserRun_Key_SpikeBackDown                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeBackDown      StandBy_Key_SpikeBackDown
//static uint8_t UserRun_Key_SpikeBackDown(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* �������� : UserRun_Key_SpikeFeetUp                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeFeetUp      StandBy_Key_SpikeFeetUp
//static uint8_t UserRun_Key_SpikeFeetUp(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* �������� : UserRun_Key_SpikeFeetDown                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeFeetDown      StandBy_Key_SpikeFeetDown
//static uint8_t UserRun_Key_SpikeFeetDown(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* �������� : UserRun_Key_SpikeBackUpFeetDown                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeBackUpFeetDown      StandBy_Key_SpikeBackUpFeetDown
//static uint8_t UserRun_Key_SpikeBackUpFeetDown(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* �������� : UserRun_Key_SpikeBackDownFeetUp                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeBackDownFeetUp      StandBy_Key_SpikeBackDownFeetUp
//static uint8_t UserRun_Key_SpikeBackDownFeetUp(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* �������� : UserRun_Key_SpikeLegExtend                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeLegExtend      StandBy_Key_SpikeLegExtend
//static uint8_t UserRun_Key_SpikeLegExtend(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* �������� : UserRun_Key_SpikeLegShorten                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeLegShorten      StandBy_Key_SpikeLegShorten
//static uint8_t UserRun_Key_SpikeFeetShorten(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* �������� : UserRun_Key_SpikeULegExtend                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeULegExtend      StandBy_Key_SpikeULegExtend
//static uint8_t UserRun_Key_SpikeULegExtend(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* �������� : UserRun_Key_SpikeULegShorten                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeULegShorten      StandBy_Key_SpikeULegShorten
//static uint8_t UserRun_Key_SpikeULegShorten(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* �������� : UserRun_Key_SpikeZeroGravity1                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeZeroGravity1      StandBy_Key_SpikeZeroGravity1
//static uint8_t UserRun_Key_SpikeZeroGravity1(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* �������� : UserRun_Key_SpikeZeroGravity2                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeZeroGravity2      StandBy_Key_SpikeZeroGravity2
//static uint8_t UserRun_Key_SpikeZeroGravity2(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* �������� : UserRun_Key_SpikeZeroGravity                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeZeroGravity      StandBy_Key_SpikeZeroGravity
//static uint8_t UserRun_Key_SpikeZeroGravity(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* �������� : UserRun_Key_SpikeHomeReset                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeHomeReset      StandBy_Key_SpikeHomeReset
//static uint8_t UserRun_Key_SpikeHomeReset(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreXYZSpeedAdd                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreXYZSpeedAdd(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*����ɨ��ʱ���������ٶ�*/
  }

  if((pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL) ||    /*���û�������ֶ�������*/
     (0 == pMChair->StateCoreAction.Bit.XYZ.All))                      /*���û������XYZ������*/
  {
    return FAIL; 
  }
  
  if(ROLL == pMChair->FuncMannual_Core.Bit.XYZ.All)
  {
    return FAIL;      /*���ò��ܵ����ٶ�*/
  }

  if(pMChair->MannualCoreXYZActionSpeed < MChair_GetFuncCoreMannualXYZSpeedMax())
  {
    pMChair->MannualCoreXYZActionSpeed++;   
    return SUCCESS;
  }
  
  return FAIL; 
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreXYZSpeedDec                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreXYZSpeedDec(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*����ɨ��ʱ���������ٶ�*/
  }

  if((pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL) ||    /*���û�������ֶ�������*/
     (0 == pMChair->StateCoreAction.Bit.XYZ.All))                      /*���û������XYZ������*/
  {
    return FAIL; 
  }
  
  if(ROLL == pMChair->FuncMannual_Core.Bit.XYZ.All)
  {
    return FAIL;      /*���ò��ܵ����ٶ�*/
  }

  if(pMChair->MannualCoreXYZActionSpeed > XYZ_ACTION_SPEED_MIN)
  {
    pMChair->MannualCoreXYZActionSpeed--;   
    return SUCCESS;
  }

  return FAIL;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreXYZSpeed                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : �ù��ܽ��������ȣ�����ʱ���ܵ���                                                                                               
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreXYZSpeed(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*����ɨ��ʱ���������ٶ�*/
  }

  if((pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL) ||    /*���û�������ֶ�������*/
     (0 == pMChair->StateCoreAction.Bit.XYZ.All))                      /*���û������XYZ������*/
  {
    return FAIL; 
  }

  
  if(MChair_GetFuncCoreMannualXYZSpeedMax() == XYZ_ACTION_SPEED_MIN)
  {
    return FAIL;      /*ֻ��һ���ٶȣ����ɵ�*/
  }
  
  if(TRUE == pMChair->StateCoreAction.Bit.XYZ.Bit.RollRun)
  {
    return FAIL;      /*���ò��ܵ����ٶ�*/
  }
  pMChair->MannualCoreXYZActionSpeed++;   
  if(pMChair->MannualCoreXYZActionSpeed > MChair_GetFuncCoreMannualXYZSpeedMax())
  {
    pMChair->MannualCoreXYZActionSpeed = XYZ_ACTION_SPEED_MIN;
  }  

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreTCSSpeedAdd                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreTCSSpeedAdd(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*����ɨ��ʱ���������ٶ�*/
  }
  
  if((pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL) ||    /*���û�������ֶ�������*/
     (pMChair->MannualCoreTCSActionSpeed >= TCS_SPEED_MAX))                      
  {
    return FAIL; 
  }
  
  if(0 == pMChair->StateCoreAction.Bit.TCS.All)                    /*���û������TCS������*/
  {
    return FAIL; 
  }
  
  pMChair->MannualCoreTCSActionSpeed++;
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreTCSSpeedDec                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreTCSSpeedDec(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*����ɨ��ʱ���������ٶ�*/
  }

  if((pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL) ||    /*���û�������ֶ�������*/
     (pMChair->MannualCoreTCSActionSpeed <= TCS_SPEED_MIN))                      
  {
    return FAIL; 
  }
  
  if(0 == pMChair->StateCoreAction.Bit.TCS.All)                    /*���û������TCS������*/
  {
    return FAIL; 
  }

  pMChair->MannualCoreTCSActionSpeed--;
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreTCSSpeed                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreTCSSpeed(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*����ɨ��ʱ���������ٶ�*/
  }

  if((pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL) ||    /*���û�������ֶ�������*/
     (0 == pMChair->StateCoreAction.Bit.TCS.All))                      /*���û������TCS������*/
  {
    return FAIL; 
  }

  pMChair->MannualCoreTCSActionSpeed++;   /*��о�ֶ�������ٶ�����*/
  if(pMChair->MannualCoreTCSActionSpeed > TCS_SPEED_MAX)
  {
    pMChair->MannualCoreTCSActionSpeed = TCS_SPEED_MIN;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreWidthAdd                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreWidthAdd(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*����ɨ��ʱ��������*/
  }

  if(pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL)
  {
    return FAIL; /*��о�ֶ����򣬲��ܵ��ڿ��*/
  }
 
  if(PKEEP == MChair_GetFuncCoreMannualWidthMax())
  {
    return FAIL; /*��Ȳ��������*/
  }

  if(pMChair->MannualCoreWidth < MChair_GetFuncCoreMannualWidthMax())
  {
    pMChair->MannualCoreWidth++;
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreWidthDec                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreWidthDec(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*����ɨ��ʱ��������*/
  }

  if(pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL)
  {
    return FAIL; /*��о�ֶ����򣬲��ܵ��ڿ��*/
  }
 
  if(PKEEP == MChair_GetFuncCoreMannualWidthMax())
  {
    return FAIL; /*��Ȳ��������*/
  }

  if(pMChair->MannualCoreWidth > PX_MIN)
  {
    pMChair->MannualCoreWidth--;
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreWidth                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreWidth(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*����ɨ��ʱ��������*/
  }

  if(pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL)
  {
    return FAIL; /*��о�ֶ����򣬲��ܵ��ڿ��*/
  }
 
  if(PKEEP == MChair_GetFuncCoreMannualWidthMax())
  {
    return FAIL; /*��Ȳ��������*/
  }

  pMChair->MannualCoreWidth += 2;
  if(pMChair->MannualCoreWidth > MChair_GetFuncCoreMannualWidthMax())
  {
    pMChair->MannualCoreWidth = PX_MIN;
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreMannualUp                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreMannualUp(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run) /*���ڼ��粿λ��*/ 
  {
    if(TRUE == pMChair->StateBodyScan.Bit.ShoulderAdjustEn)    /*�粿���ʱ���û���λ�õ���*/
    {
      return BodyScan_UserAdjustShoulder(SHOULDER_ADJUST_UP, SHOULDER_ADJUST_KEY_LSMODE);
    }
    else
    {
      return FAIL;
    }
  }
  else
  {
    if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core) /*��о�ֶ�*/
    {
      if(CORE_MOVE_ADJUST_ROLL_UP == Core_GetMoveAdjustRoll())
      {
        return FAIL;
      }
      else
      {
        return Core_SetMoveAdjustRoll(CORE_MOVE_ADJUST_ROLL_UP);
      }
    }
    else if(FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Core) /*��о�Զ�ʱ�����ڼ粿λ��(����)*/
    {
      //return BodyScan_UserAdjustShoulder(SHOULDER_ADJUST_UP);
      return FAIL;
    }
    else
    {
      return FAIL;
    }
  }
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreMannualDown                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreMannualDown(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run) /*���ڼ��粿λ��*/ 
  {
    if(TRUE == pMChair->StateBodyScan.Bit.ShoulderAdjustEn)    /*�粿���ʱ���û���λ�õ���*/
    {
      return BodyScan_UserAdjustShoulder(SHOULDER_ADJUST_DOWN, SHOULDER_ADJUST_KEY_LSMODE);
    }
    else
    {
      return FAIL;
    }
  }
  else
  {
    if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core) /*��о�ֶ�*/
    {
      if(CORE_MOVE_ADJUST_ROLL_DOWN == Core_GetMoveAdjustRoll())
      {
        return FAIL;
      }
      else
      {
        return Core_SetMoveAdjustRoll(CORE_MOVE_ADJUST_ROLL_DOWN);
      }
    }
    else if(FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Core) /*��о�Զ�ʱ�����ڼ粿λ��(����)*/
    {
      //return BodyScan_UserAdjustShoulder(SHOULDER_ADJUST_DOWN);
      return FAIL;
    }
    else
    {
      return FAIL;
    }
  }
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreMannualFront                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreMannualFront(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*����ɨ��ʱ��������*/
  }

  if(TRUE == pMChair->CSFlag.Bit.ZeroGravityAngleRun) 
  {
    return FAIL; /*�������Ƕȵ�����,���������Ч*/
  }

  if(FA_COREGASSPIKE_Thai == pMChair->FuncAuto_CoreGasSpike)
  {
    return FAIL; /*�ó��򲻵���*/
  }
  
  if(FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Core) /*��о�Զ�*/
  {
    if(pMChair->AutoCoreFlexLevelAdjust < 8)
    {
      pMChair->AutoCoreFlexLevelAdjust++;
      return SUCCESS;
    }
    else
    {
      return FAIL;
    }
  }
  else if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core) /*��о�ֶ�*/
  {
    if(PKEEP == MChair_GetFuncCoreMannualFlexLevelMax())
    {
      return FAIL; /*���������*/
    }

    if(pMChair->MannualCoreFlexLevel < MChair_GetFuncCoreMannualFlexLevelMax())
    {
      pMChair->MannualCoreFlexLevel++;
      return SUCCESS;
    }
    else
    {
      return FAIL;
    }
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreMannualBack                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreMannualBack(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*����ɨ��ʱ��������*/
  }

  if(TRUE == pMChair->CSFlag.Bit.ZeroGravityAngleRun) 
  {
    return FAIL; /*�������Ƕȵ�����,���������Ч*/
  }

  if(FA_COREGASSPIKE_Thai == pMChair->FuncAuto_CoreGasSpike)
  {
    return FAIL; /*�ó��򲻵���*/
  }

  if(FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Core) /*��о�Զ�*/
  {
    if(pMChair->AutoCoreFlexLevelAdjust > 1)
    {
      pMChair->AutoCoreFlexLevelAdjust--;
      return SUCCESS;
    }
    else
    {
      return FAIL;
    }
  }
  else if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core) /*��о�ֶ�*/
  {
    if(PKEEP == MChair_GetFuncCoreMannualFlexLevelMax())
    {
      return FAIL; /*���������*/
    }

    if(pMChair->MannualCoreFlexLevel > 0)
    {
      pMChair->MannualCoreFlexLevel--;
      return SUCCESS;
    }
    else
    {
      return FAIL;
    }
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreFlexLevel                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreFlexLevel(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*����ɨ��ʱ��������*/
  }

  if(TRUE == pMChair->CSFlag.Bit.ZeroGravityAngleRun) 
  {
    return FAIL; /*�������Ƕȵ�����,���������Ч*/
  }

  if(FA_COREGASSPIKE_Thai == pMChair->FuncAuto_CoreGasSpike)
  {
    return FAIL; /*�ó��򲻵���*/
  }

  if(FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Core) /*��о�Զ�*/
  {
    if(pMChair->AutoCoreFlexLevelAdjust < 8)
    {
      pMChair->AutoCoreFlexLevelAdjust++;
    }
    else
    {
      pMChair->AutoCoreFlexLevelAdjust = 1;
    }
    return SUCCESS;
  }
  else if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core) /*��о�ֶ�*/
  {
    if(PKEEP == MChair_GetFuncCoreMannualFlexLevelMax())
    {
      return FAIL; /*���������*/
    }

    if(pMChair->MannualCoreFlexLevel < MChair_GetFuncCoreMannualFlexLevelMax())
    {
      pMChair->MannualCoreFlexLevel++;
    }
    else
    {
      pMChair->MannualCoreFlexLevel = 0;
    }
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreSpot                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreSpot(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*����ɨ��ʱ����Ч*/
  }

  if(pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL)
  {
    return FAIL; /*��о�ֶ����򣬲��ܵ���*/
  }

  if(Core_GetRollRange() != CORE_ROLL_RANGE_SPOT)
  {
    return Core_SetRollRange(CORE_ROLL_RANGE_SPOT);
  }
  else 
  {
    if( SUCCESS == Core_SetRollRange(CORE_ROLL_RANGE_WHOLE) )
    {
      return SUCCESS;
    }
    else
    {
      return Core_SetRollRange(CORE_ROLL_RANGE_PART);
    }
  }
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CorePart                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CorePart(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*����ɨ��ʱ����Ч*/
  }

  if(pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL)
  {
    return FAIL; /*��о�ֶ����򣬲��ܵ���*/
  }

  if(Core_GetRollRange() != CORE_ROLL_RANGE_PART)
  {
    return Core_SetRollRange(CORE_ROLL_RANGE_PART);
  }
  else 
  {
    if( SUCCESS == Core_SetRollRange(CORE_ROLL_RANGE_WHOLE) )
    {
      return SUCCESS;
    }
    else
    {
      return Core_SetRollRange(CORE_ROLL_RANGE_SPOT);
    }
  }
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreWhole                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreWhole(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*����ɨ��ʱ����Ч*/
  }

  if(pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL)
  {
    return FAIL; /*��о�ֶ����򣬲��ܵ���*/
  }

  if(Core_GetRollRange() != CORE_ROLL_RANGE_WHOLE)
  {
    return Core_SetRollRange(CORE_ROLL_RANGE_WHOLE);
  }
  return FAIL;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreSpotPartWhole                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreSpotPartWhole(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*����ɨ��ʱ����Ч*/
  }

  if(pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL)
  {
    return FAIL; /*��о�ֶ����򣬲��ܵ���*/
  }

  if(CORE_ROLL_RANGE_WHOLE == Core_GetRollRange())
  {
    if(FAIL == Core_SetRollRange(CORE_ROLL_RANGE_SPOT))
    {
      return Core_SetRollRange(CORE_ROLL_RANGE_PART);
    }
    else
    {
      return SUCCESS;
    }
  }
  else if(CORE_ROLL_RANGE_SPOT == Core_GetRollRange())
  {
    return Core_SetRollRange(CORE_ROLL_RANGE_PART);
  }
  else 
  {
    return Core_SetRollRange(CORE_ROLL_RANGE_WHOLE);
  }
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreRoll                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreRoll(uint8_t *pData)
{
  if(pMChair->FuncMannual_Core.Bit.XYZ.All != ROLL) 
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = ROLL;
  }
  else
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreKnead                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreKnead(uint8_t *pData)
{
  if((pMChair->FuncMannual_Core.Bit.XYZ.All != KNIN)  && 
     (pMChair->FuncMannual_Core.Bit.XYZ.All != KNOUT) ) 
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = KNIN;
  }
  else if(KNIN == pMChair->FuncMannual_Core.Bit.XYZ.All)
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = KNOUT;
  }
  else
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreTap                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreTap(uint8_t *pData)
{
  if((pMChair->FuncMannual_Core.Bit.XYZ.All == SWEDISH1)  || 
     (pMChair->FuncMannual_Core.Bit.XYZ.All == SWEDISH2) )
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }
  
  if((pMChair->FuncMannual_Core.Bit.TCS.All != LTAP) && 
     (pMChair->FuncMannual_Core.Bit.TCS.All != TAP)  ) 
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = LTAP;
  }
  else if(LTAP == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = TAP;
  }
  else
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = CORE_ACTION_NONE;
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreShiatsu                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreShiatsu(uint8_t *pData)
{
  if((pMChair->FuncMannual_Core.Bit.XYZ.All == SWEDISH1)  || 
     (pMChair->FuncMannual_Core.Bit.XYZ.All == SWEDISH2) )
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }
  
  if((pMChair->FuncMannual_Core.Bit.TCS.All != SHIA1)  && 
     (pMChair->FuncMannual_Core.Bit.TCS.All != SHIA2) ) 
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = SHIA1;
  }
  else if(SHIA1 == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = SHIA2;
  }
  else
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = CORE_ACTION_NONE;
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreClap                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreClap(uint8_t *pData)
{
  if((pMChair->FuncMannual_Core.Bit.XYZ.All == SWEDISH1)  || 
     (pMChair->FuncMannual_Core.Bit.XYZ.All == SWEDISH2) )
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }
  
  if((pMChair->FuncMannual_Core.Bit.TCS.All !=CLAP1)  && 
     (pMChair->FuncMannual_Core.Bit.TCS.All != CLAP2) ) 
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = CLAP1;
  }
  else if(CLAP1 == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = CLAP2;
  }
  else
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = CORE_ACTION_NONE;
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreMannualAction                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreMannualAction(uint8_t *pData)
{
  if(CORE_ACTION_NONE == pMChair->FuncMannual_Core.All) 
  {
    pMChair->MannualCoreXYZActionSpeed = 3;   
    pMChair->FuncMannual_Core.Bit.XYZ.All = KNIN;
    pMChair->FuncMannual_Core.Bit.TCS.All = CORE_ACTION_NONE;
  }
  else if((KNOUT == pMChair->FuncMannual_Core.Bit.XYZ.All) ||
          (KNIN  == pMChair->FuncMannual_Core.Bit.XYZ.All) )
  {
    pMChair->MannualCoreTCSActionSpeed = 3;   
    pMChair->FuncMannual_Core.Bit.TCS.All = LTAP;
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }
  else if((TAP  == pMChair->FuncMannual_Core.Bit.TCS.All) ||
          (LTAP == pMChair->FuncMannual_Core.Bit.TCS.All) )
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = SHIA1;
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }
  else if((SHIA2 == pMChair->FuncMannual_Core.Bit.TCS.All) ||
          (SHIA1 == pMChair->FuncMannual_Core.Bit.TCS.All) )
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = CLAP1;
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }
  else if((CLAP1 == pMChair->FuncMannual_Core.Bit.TCS.All) ||
          (CLAP2 == pMChair->FuncMannual_Core.Bit.TCS.All) )
  {
    pMChair->MannualCoreXYZActionSpeed = 3;   
    pMChair->FuncMannual_Core.Bit.XYZ.All = ROLL;
    pMChair->FuncMannual_Core.Bit.TCS.All = CORE_ACTION_NONE;
  }
  else
  {
    pMChair->FuncMannual_Core.All = CORE_ACTION_NONE;
  }    

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreMannualMode                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreMannualMode(uint8_t *pData)
{
  if(KNIN  == pMChair->FuncMannual_Core.Bit.XYZ.All) 
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = KNOUT;
  }
  else if(KNOUT  == pMChair->FuncMannual_Core.Bit.XYZ.All) 
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = KNIN;
  }
  else if(TAP  == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = LTAP;
  }
  else if(LTAP  == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = TAP;
  }
  else if(SHIA1  == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = SHIA2;
  }
  else if(SHIA2  == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = SHIA1;
  }
  else if(CLAP1  == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = CLAP2;
  }
  else if(CLAP2  == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = CLAP1;
  }
  else
  {
    return FAIL;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreMannualSpeed                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreMannualSpeed(uint8_t *pData)
{
  if((KNOUT == pMChair->FuncMannual_Core.Bit.XYZ.All) ||
     (KNIN  == pMChair->FuncMannual_Core.Bit.XYZ.All) )
  {
    return UserRun_Key_CoreXYZSpeed(pData);
  }
  else
  {
    return  UserRun_Key_CoreTCSSpeed(pData);
  }
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreXYZAction                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreXYZAction(uint8_t *pData)
{
  if(pMChair->FuncMannual_Core.Bit.XYZ.All != pData[0]) 
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = pData[0];
  }
  else
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_CoreTCSAction                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreTCSAction(uint8_t *pData)
{
  return FAIL;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_GasIntensityAdd                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_GasIntensityAdd(uint8_t *pData)
{
  if((pMChair->ComponentFuncState.Bit.Gas != FUNC_TYPE_MANNUAL) &&  /*�޳�������*/
     (pMChair->ComponentFuncState.Bit.Gas != FUNC_TYPE_AUTO)    )
  {
    if((FMA_ROLLER_NONE == pMChair->FuncMA_Roller.Bit.Calves)            || /*�޽Ź�*/
       (FMA_FEET_ROLLER_ByActionTab == pMChair->FuncMA_Roller.Bit.Calves))  /*�����ɱ����ƿ��صĽŹ�*/
    {
      return FAIL;
    }
  }

  if(pMChair->GasIntensity >= 5)
  {
    return FAIL;
  }
  
  pMChair->GasIntensity++;
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_GasIntensityDec                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_GasIntensityDec(uint8_t *pData)
{
  if((pMChair->ComponentFuncState.Bit.Gas != FUNC_TYPE_MANNUAL) &&  /*�޳�������*/
     (pMChair->ComponentFuncState.Bit.Gas != FUNC_TYPE_AUTO)    )
  {
    if((FMA_ROLLER_NONE == pMChair->FuncMA_Roller.Bit.Calves)            || /*�޽Ź�*/
       (FMA_FEET_ROLLER_ByActionTab == pMChair->FuncMA_Roller.Bit.Calves))  /*�����ɱ����ƿ��صĽŹ�*/
    {
      return FAIL;
    }
  }

  if(pMChair->GasIntensity <= 1)
  {
    return FAIL;
  }
  
  pMChair->GasIntensity--;
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_GasIntensity                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_GasIntensity(uint8_t *pData)
{
  if((pMChair->ComponentFuncState.Bit.Gas != FUNC_TYPE_MANNUAL) &&  /*�޳�������*/
     (pMChair->ComponentFuncState.Bit.Gas != FUNC_TYPE_AUTO)    )
  {
    if((FMA_ROLLER_NONE == pMChair->FuncMA_Roller.Bit.Calves)            || /*�޽Ź�*/
       (FMA_FEET_ROLLER_ByActionTab == pMChair->FuncMA_Roller.Bit.Calves))  /*�����ɱ����ƿ��صĽŹ�*/
    {
      return FAIL;
    }
  }
  
  pMChair->GasIntensity++;   
  if(pMChair->GasIntensity > 5)
  {
    pMChair->GasIntensity = 1;
  }
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_GasHead                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasHead(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.Head != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.Head = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.Head = FM_GAS_HEAD;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_GasShoulder                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasShoulder(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.Shoulder != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.Shoulder = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.Shoulder = FM_GAS_SHOULDER;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_GasArms                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasArms(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.Arms != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.Arms = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.Arms = FM_GAS_ARMS;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_GasLumbar                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasLumbar(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.Lumbar != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.Lumbar = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.Lumbar = FM_GAS_LUMBAR;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_GasSeat                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasSeat(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.Seat != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.Seat = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.Seat = FM_GAS_SEAT;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_GasLumbarSeat                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasLumbarSeat(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.LumbarSeat != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.LumbarSeat = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.LumbarSeat = FM_GAS_LUMBARSEAT;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_GasCalves                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasCalves(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.Calves != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.Calves = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.Calves = FM_GAS_CALVES;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_GasFeet                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasFeet(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.Feet != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.Feet = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.Feet = FM_GAS_CALVESFEET;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_GasCalvesFeet                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasCalvesFeet(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.CalvesFeet != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.CalvesFeet = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.CalvesFeet = FM_GAS_CALVESFEET;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_GasFullGas                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_GasFullGas(uint8_t *pData)
{
  if(pMChair->FuncAuto_Gas != FA_GAS_FullGas)
  {
    pMChair->FuncAuto_Gas = FA_GAS_FullGas;
  }
  else
  {
    pMChair->FuncAuto_Gas = FA_GAS_NONE;
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_GasQuickGas                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_GasQuickGas(uint8_t *pData)
{
  if(pMChair->FuncAuto_Gas != FA_GAS_QuickGas)
  {
    pMChair->FuncAuto_Gas = FA_GAS_QuickGas;
  }
  else
  {
    pMChair->FuncAuto_Gas = FA_GAS_NONE;
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_GasPartSelcet                                                                                                        
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_GasPartSelcet(uint8_t *pData)
{
  if(FM_GAS_NONE == pMChair->FuncMannual_Gas.All)
  {
    pMChair->FuncMannual_Gas.All = FM_GAS_NONE;
    pMChair->FuncMannual_Gas.Bit.CalvesFeet = FM_GAS_CALVESFEET;
  }
  else if(FM_GAS_CALVESFEET == pMChair->FuncMannual_Gas.Bit.CalvesFeet)
  {
    pMChair->FuncMannual_Gas.All = FM_GAS_NONE;
    pMChair->FuncMannual_Gas.Bit.Seat = FM_GAS_SEAT;
  }
  else if(FM_GAS_SEAT == pMChair->FuncMannual_Gas.Bit.Seat)
  {
    pMChair->FuncMannual_Gas.All = FM_GAS_NONE;
    pMChair->FuncMannual_Gas.Bit.Arms = FM_GAS_ARMS;
  }
  else if(FM_GAS_ARMS == pMChair->FuncMannual_Gas.Bit.Arms)
  {
    pMChair->FuncMannual_Gas.All = FM_GAS_NONE;
    pMChair->FuncMannual_Gas.Bit.Shoulder = FM_GAS_SHOULDER;
  }
  else
  {
    pMChair->FuncMannual_Gas.All = FM_GAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_VibLumbarBack                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_VibLumbarBack(uint8_t *pData)
{
  if(Core_GetYPosition() < PY15)        /*�ϰ����������о��*/
  {
    return FAIL;
  }
  
  /*�񶯴��ڰ���״̬--------------------------------------*/
  if((pMChair->FuncMA_Vib.Bit.LumbarBack != FMA_VIB_NONE) && 
     (pMChair->FuncMA_Vib.Bit.LumbarBack != FMA_LUMBARBACK_VIB_Mannual))
  {
    if(ON == pMChair->LumbarBackVibCtrlSw) /*����״̬�µ�����������*/
    {
      pMChair->FuncMA_Vib.Bit.LumbarBack = FMA_VIB_NONE; /*�ر���*/
    }
    else /*����״̬�µ��񶯴���ֹͣ�׶�*/
    {
      pMChair->FuncMA_Vib.Bit.LumbarBack = FMA_SEAT_VIB_Mannual; /*�񶯳���*/
    }
  }
  /*�񶯱��û���������------------------------------------*/
  else
  {
    if(pMChair->FuncMA_Vib.Bit.LumbarBack != FMA_VIB_NONE)
    {
      pMChair->FuncMA_Vib.Bit.LumbarBack = FMA_VIB_NONE;
    }
    else
    {
      pMChair->FuncMA_Vib.Bit.LumbarBack = FMA_LUMBARBACK_VIB_Mannual;
    }
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_VibSeat                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_VibSeat(uint8_t *pData)
{
  /*�񶯴��ڰ���״̬--------------------------------------*/
  if((pMChair->FuncMA_Vib.Bit.Seat != FMA_VIB_NONE) && 
     (pMChair->FuncMA_Vib.Bit.Seat != FMA_SEAT_VIB_Mannual))
  {
    if(ON == pMChair->SeatVibCtrlSw) /*����״̬�µ�����������*/
    {
      pMChair->FuncMA_Vib.Bit.Seat = FMA_VIB_NONE; /*�ر���*/
    }
    else /*����״̬�µ��񶯴���ֹͣ�׶�*/
    {
      pMChair->FuncMA_Vib.Bit.Seat = FMA_SEAT_VIB_Mannual; /*�񶯳���*/
    }
  }
  /*�񶯱��û���������------------------------------------*/
  else
  {
    if(pMChair->FuncMA_Vib.Bit.Seat != FMA_VIB_NONE)
    {
      pMChair->FuncMA_Vib.Bit.Seat = FMA_VIB_NONE;
    }
    else
    {
      pMChair->FuncMA_Vib.Bit.Seat = FMA_SEAT_VIB_Mannual;
    }
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_VibCalves                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_VibCalves(uint8_t *pData)
{
  /*�񶯴��ڰ���״̬--------------------------------------*/
  if((pMChair->FuncMA_Vib.Bit.Calves != FMA_VIB_NONE) && 
     (pMChair->FuncMA_Vib.Bit.Calves != FMA_CALVES_VIB_Mannual))
  {
    if(ON == pMChair->CalvesVibCtrlSw) /*����״̬�µ�����������*/
    {
      pMChair->FuncMA_Vib.Bit.Calves = FMA_VIB_NONE; /*�ر���*/
    }
    else /*����״̬�µ��񶯴���ֹͣ�׶�*/
    {
      pMChair->FuncMA_Vib.Bit.Calves = FMA_CALVES_VIB_Mannual; /*�񶯳���*/
    }
  }
  /*�񶯱��û���������------------------------------------*/
  else
  {
    if(pMChair->FuncMA_Vib.Bit.Calves != FMA_VIB_NONE)
    {
      pMChair->FuncMA_Vib.Bit.Calves = FMA_VIB_NONE;
    }
    else
    {
      pMChair->FuncMA_Vib.Bit.Calves = FMA_CALVES_VIB_Mannual;
    }
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_VibFeet                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_VibFeet(uint8_t *pData)
{
  /*�񶯴��ڰ���״̬--------------------------------------*/
  if((pMChair->FuncMA_Vib.Bit.Feet != FMA_VIB_NONE) && 
     (pMChair->FuncMA_Vib.Bit.Feet != FMA_FEET_VIB_Mannual))
  {
    if(ON == pMChair->FeetVibCtrlSw) /*����״̬�µ�����������*/
    {
      pMChair->FuncMA_Vib.Bit.Feet = FMA_VIB_NONE; /*�ر���*/
    }
    else /*����״̬�µ��񶯴���ֹͣ�׶�*/
    {
      pMChair->FuncMA_Vib.Bit.Feet = FMA_FEET_VIB_Mannual; /*�񶯳���*/
    }
  }
  /*�񶯱��û���������------------------------------------*/
  else
  {
    if(pMChair->FuncMA_Vib.Bit.Feet != FMA_VIB_NONE)
    {
      pMChair->FuncMA_Vib.Bit.Feet = FMA_VIB_NONE;
    }
    else
    {
      pMChair->FuncMA_Vib.Bit.Feet = FMA_FEET_VIB_Mannual;
    }
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_HeatLumbarBack                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_HeatLumbarBack(uint8_t *pData)
{
  /*���ڰ���״̬--------------------------------------*/
  if((pMChair->FuncMA_Heat.Bit.LumbarBack != FMA_HEAT_NONE) && 
     (pMChair->FuncMA_Heat.Bit.LumbarBack != FMA_LUMBARBACK_HEAT_Mannual))
  {
    if(ON == pMChair->LumbarBackHeatCtrlSw) /*����״̬�µ���������*/
    {
      pMChair->FuncMA_Heat.Bit.LumbarBack = FMA_HEAT_NONE; /*�ر�*/
    }
    else /*����״̬�µĴ���ֹͣ�׶�*/
    {
      pMChair->FuncMA_Heat.Bit.LumbarBack = FMA_LUMBARBACK_HEAT_Mannual; /*����*/
    }
  }
  /*���û���������------------------------------------*/
  else
  {
    if(TRUE == pMChair->CSFlag.Bit.LumbarBackHeatMannualOpDisable)
    {
      return FAIL; /*���������ֶ���Ч*/
    }
    
    if(pMChair->FuncMA_Heat.Bit.LumbarBack != FMA_HEAT_NONE)
    {
      pMChair->FuncMA_Heat.Bit.LumbarBack = FMA_HEAT_NONE;
    }
    else
    {
      pMChair->FuncMA_Heat.Bit.LumbarBack = FMA_LUMBARBACK_HEAT_Mannual;
    }
  }
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_HeatSeat                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_HeatSeat(uint8_t *pData)
{
  /*���ڰ���״̬--------------------------------------*/
  if((pMChair->FuncMA_Heat.Bit.Seat != FMA_HEAT_NONE) && 
     (pMChair->FuncMA_Heat.Bit.Seat != FMA_SEAT_HEAT_Mannual))
  {
    if(ON == pMChair->SeatHeatCtrlSw) /*����״̬�µ���������*/
    {
      pMChair->FuncMA_Heat.Bit.Seat = FMA_HEAT_NONE; /*�ر�*/
    }
    else /*����״̬�µĴ���ֹͣ�׶�*/
    {
      pMChair->FuncMA_Heat.Bit.Seat = FMA_SEAT_HEAT_Mannual; /*����*/
    }
  }
  /*���û���������------------------------------------*/
  else
  {
    if(TRUE == pMChair->CSFlag.Bit.SeatHeatMannualOpDisable)
    {
      return FAIL; /*�����ֶ���Ч*/
    }
    if(pMChair->FuncMA_Heat.Bit.Seat != FMA_HEAT_NONE)
    {
      pMChair->FuncMA_Heat.Bit.Seat = FMA_HEAT_NONE;
    }
    else
    {
      pMChair->FuncMA_Heat.Bit.Seat = FMA_SEAT_HEAT_Mannual;
    }
  }
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_HeatCalves                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_HeatCalves(uint8_t *pData)
{
  /*���ڰ���״̬--------------------------------------*/
  if((pMChair->FuncMA_Heat.Bit.Calves != FMA_HEAT_NONE) && 
     (pMChair->FuncMA_Heat.Bit.Calves != FMA_CALVES_HEAT_Mannual))
  {
    if(ON == pMChair->CalvesHeatCtrlSw) /*����״̬�µ���������*/
    {
      pMChair->FuncMA_Heat.Bit.Calves = FMA_HEAT_NONE; /*�ر�*/
    }
    else /*����״̬�µĴ���ֹͣ�׶�*/
    {
      pMChair->FuncMA_Heat.Bit.Calves = FMA_CALVES_HEAT_Mannual; /*����*/
    }
  }
  /*���û���������------------------------------------*/
  else
  {
    if(TRUE == pMChair->CSFlag.Bit.CalvesHeatMannualOpDisable)
    {
      return FAIL; /*�����ֶ���Ч*/
    }
    if(pMChair->FuncMA_Heat.Bit.Calves != FMA_HEAT_NONE)
    {
      pMChair->FuncMA_Heat.Bit.Calves = FMA_HEAT_NONE;
    }
    else
    {
      pMChair->FuncMA_Heat.Bit.Calves = FMA_CALVES_HEAT_Mannual;
    }
  }
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_HeatFeet                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_HeatFeet(uint8_t *pData)
{
  /*���ڰ���״̬--------------------------------------*/
  if((pMChair->FuncMA_Heat.Bit.Feet != FMA_HEAT_NONE) && 
     (pMChair->FuncMA_Heat.Bit.Feet != FMA_CALVES_HEAT_Mannual))
  {
    if(ON == pMChair->FeetHeatCtrlSw) /*����״̬�µ���������*/
    {
      pMChair->FuncMA_Heat.Bit.Feet = FMA_HEAT_NONE; /*�ر�*/
    }
    else /*����״̬�µĴ���ֹͣ�׶�*/
    {
      pMChair->FuncMA_Heat.Bit.Feet = FMA_CALVES_HEAT_Mannual; /*����*/
    }
  }
  /*���û���������------------------------------------*/
  else
  {
    if(TRUE == pMChair->CSFlag.Bit.FeetHeatMannualOpDisable)
    {
      return FAIL; /*�Ų������ֶ���Ч*/
    }
    if(pMChair->FuncMA_Heat.Bit.Feet != FMA_HEAT_NONE)
    {
      pMChair->FuncMA_Heat.Bit.Feet = FMA_HEAT_NONE;
    }
    else
    {
      pMChair->FuncMA_Heat.Bit.Feet = FMA_CALVES_HEAT_Mannual;
    }
  }
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_RollerCalves                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_RollerCalves(uint8_t *pData)
{
  /*���ڰ���״̬--------------------------------------*/
  if((pMChair->FuncMA_Roller.Bit.Calves != FMA_ROLLER_NONE) && 
     (pMChair->FuncMA_Roller.Bit.Calves != FMA_CALVES_ROLLER_Mannual))
  {
    if(ON == pMChair->CalvesRollerCtrlSw) /*����״̬�µ���������*/
    {
      pMChair->FuncMA_Roller.Bit.Calves = FMA_ROLLER_NONE; /*�ر�*/
    }
    else /*����״̬�µĴ���ֹͣ�׶�*/
    {
      pMChair->FuncMA_Roller.Bit.Calves = FMA_CALVES_ROLLER_Mannual; /*����*/
    }
  }
  /*���û���������------------------------------------*/
  else
  {
    if(pMChair->FuncMA_Roller.Bit.Calves != FMA_ROLLER_NONE)
    {
      pMChair->FuncMA_Roller.Bit.Calves = FMA_ROLLER_NONE;
    }
    else
    {
      pMChair->FuncMA_Roller.Bit.Calves = FMA_CALVES_ROLLER_Mannual;
    }
  }
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_RollerFeet                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_RollerFeet(uint8_t *pData)
{
  /*���ڰ���״̬--------------------------------------*/
  if((pMChair->FuncMA_Roller.Bit.Feet != FMA_ROLLER_NONE) && 
     (pMChair->FuncMA_Roller.Bit.Feet != FMA_FEET_ROLLER_Mannual))
  {
    if(ON == pMChair->FeetRollerCtrlSw) /*����״̬�µ���������*/
    {
      pMChair->FuncMA_Roller.Bit.Feet = FMA_ROLLER_NONE; /*�ر�*/
    }
    else /*����״̬�µĴ���ֹͣ�׶�*/
    {
      pMChair->FuncMA_Roller.Bit.Feet = FMA_FEET_ROLLER_Mannual; /*����*/
    }
  }
  /*���û���������------------------------------------*/
  else
  {
    if(pMChair->FuncMA_Roller.Bit.Feet != FMA_ROLLER_NONE)
    {
      pMChair->FuncMA_Roller.Bit.Feet = FMA_ROLLER_NONE;
    }
    else
    {
      pMChair->FuncMA_Roller.Bit.Feet = FMA_FEET_ROLLER_Mannual;
    }
  }
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_SleepLed                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_SleepLed(uint8_t *pData)
{
  if(pMChair->FuncMA_Led.Bit.Logo != FMA_PROJECTION_LED_Mannual)   /*ͶӰ��*/
  {
    pMChair->FuncMA_Led.Bit.Logo = FMA_PROJECTION_LED_Mannual;
  }
  else
  {
    pMChair->FuncMA_Led.Bit.Logo = FMA_LED_NONE;      
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoQuick                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoQuick(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Quick)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_Quick;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoRelax                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoRelax(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Relax)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_Relax;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
    pMChair->GasIntensity = 2;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoMoveSleep                                                                                                        
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoMoveSleep(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_MoveSleep)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_MoveSleep;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
    pMChair->GasIntensity = 1;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoStretch                                                                                                        
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoStretch(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Stretch)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_Stretch;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoScraping                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoScraping(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Scraping)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_Scraping;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoShiatsu                                                                                                        
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoShiatsu(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Shiatsu)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_Shiatsu;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoLady                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoLady(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Lady)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_Lady;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
    pMChair->GasIntensity = 2;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoMan                                                                                                        
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoMan(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Man)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_Man;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoShoulderRelax                                                                                                       
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoShoulderRelax(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_ShoulderRelax)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_ShoulderRelax;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
    pMChair->GasIntensity = 2;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoShoulderRecovery                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoShoulderRecovery(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_ShoulderRecovery)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_ShoulderRecovery;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoShoulderTuina                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoShoulderTuina(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_ShoulderTuina)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_ShoulderTuina;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoShoulderShiatsu                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoShoulderShiatsu(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_ShoulderShiatsu)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_ShoulderShiatsu;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoLumbarButtockRelax                                                                                                        
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoLumbarButtockRelax(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_LumbarButtockRelax)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_LumbarButtockRelax;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
    pMChair->GasIntensity = 2;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoLumbarButtockRecovery                                                                                                     
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoLumbarButtockRecovery(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_LumbarButtockRecovery)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_LumbarButtockRecovery;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoLumbarButtockPress                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoLumbarButtockPress(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_LumbarButtockPress)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_LumbarButtockPress;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoLumbarKidneyCare                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoLumbarKidneyCare(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_LumbarKidneyCare)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_LumbarKidneyCare;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_AutoGridCombo                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoGridCombo(uint8_t *pData)
{
  uint8_t Result;

//  Result = GridComboAuto_UpdateComboSelectBit(&pData[1]);
//  if(SUCCESS == Result)
//  {
//    if(FA_GRIDCOMBO_ON == pMChair->FuncAuto_GridCombo)
//    {
//      pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*�Զ�������  ��о��Ħǿ��*/
//      pMChair->UserMassageTimeMin = 15;
//      pMChair->UserMassageTimeSec = 0;
//    }
//  }

  return Result;
}


/*
************************************************************************************************************************
* �������� : UserRun_EnterSysModeVender                                                                                                         
* �������� : ���볧��ģ                                                                                    
* ������� : pData         -- ��ֵ���������������� 
*            SysModeVender -- Ҫ����ĳ���ģʽ
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_EnterSysModeVender(uint8_t *pData, uint8_t SysModeVender)
{
  /*ע��������ƽ�忿���İ幩�磬ERP�رպ���ƽ����޷������ˡ�
        ����޷��ڴ���ģʽ�²�����ƽ����볧��ģʽ��ֻ���ڿ����������ƽ����볧��ģʽ��
        ����SysModeVender�����������¼Ҫ����ĳ���ģʽ������״̬�£�������Ӧ�ĳ���ģʽ������
        ���Ƚ������ģʽ��Ȼ�����ģʽ�Ĵ��뽫����SysModeVender������ֵ����ת�뵽��Ӧ�ĳ���ģʽ��*/
  if(pMChair->SysModeCur != SYS_MODE_USERRUN)
  {
    return FAIL;/*ֻ�����û�����ģʽ�£�������ƽ����볧��ģʽ*/
  }

  pMChair->SysModeCur    = SYS_MODE_STANDBY;    /*�Ƚ������ģʽ*/
  pMChair->SysModeVender = SysModeVender;       /*�ٴӴ���ģʽת�뵽����ģʽ*/
  pMChair->SysModeHis    = SYS_MODE_USERRUN;  

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_InspectAuto                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_InspectAuto(uint8_t *pData)
{
  return UserRun_EnterSysModeVender(pData, SYS_MODE_INSPECTAUTO);
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_InspectManual                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_InspectManual(uint8_t *pData)
{
  return UserRun_EnterSysModeVender(pData, SYS_MODE_INSPECTMANUAL);
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_PackingAngle                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_PackingAngle(uint8_t *pData)
{
  return UserRun_EnterSysModeVender(pData, SYS_MODE_PACKING);
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_InspectOther1                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_InspectOther1(uint8_t *pData)
{
  return UserRun_EnterSysModeVender(pData, SYS_MODE_INSPECTOTHER1);
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_InspectOther2                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_InspectOther2(uint8_t *pData)
{
  return UserRun_EnterSysModeVender(pData, SYS_MODE_INSPECTOTHER2);
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_TestNoTimer                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_TestNoTimer(uint8_t *pData)
{
  return UserRun_EnterSysModeVender(pData, SYS_MODE_TESTNOTIMER);
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_TestAge                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_TestAge(uint8_t *pData)
{
  return UserRun_EnterSysModeVender(pData, SYS_MODE_TESTAGE);
}

/*
************************************************************************************************************************
* �������� : UserRun_Key_TestSpike                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_TestSpike(uint8_t *pData)
{
  return UserRun_EnterSysModeVender(pData, SYS_MODE_TESTSPIKE);
}


/*����������������������������������������������������������������������������������������������������������������������*/

static const SysMode_KeyLogicTabItem_t UserRun_KeyLogicTab[] = 
{
  /*���Ӳ�����

    ��ִֵ��ǰ��bit7 -- 1��ERP����Դ�رգ����ִֵ��ǰ��Ҫ���¿�����    
                        0��ERP����Դ�رգ����ִֵ��ǰ������Ҫ���¿�����    
    ��ִֵ��ǰ��bit6 -- 1����ͣ�������Կ�ִ�м�ֵ��  
                        0����ͣ���������ֵ��ִ�С�
    ��ִֵ��ǰ��bit5 -- 1�����ܱ���״̬��ֱ��ִ�м�ֵ
                        0���ֿ����������رգ���Ҫ�ȿ������ұ��μ�ֵ��Ч��

    ��ִֵ�к�                                                   */

  {KEYVAL_NoPress,                  B(01100000),    UserRun_Key_NoKeyPress},

  /* ���ػ�����ͣ����ʱ�� ��--------------------------------------------------------*/
  {KEYVAL_Power,                    B(01100000),    UserRun_Key_Power},
  {KEYVAL_Pause,                    B(01000000),    UserRun_Key_Pause},
//  {KEYVAL_TimerAdd,                 B(00000000),    UserRun_Key_TimerAdd},
//  {KEYVAL_TimerDec,                 B(00000000),    UserRun_Key_TimerDec},
  {KEYVAL_Timer,                    B(00000000),    UserRun_Key_Timer},
  {KEYVAL_BodyCheckOk,              B(00000000),    UserRun_Key_BodyCheckOk},
//  {KEYVAL_BodyReCheck,              B(00000000),    UserRun_Key_BodyReCheck},

  {KEYVAL_BluetoothSwitch,          B(00000000),    UserRun_Key_BluetoothSwitch},
  /*�Ƹ����------------------------------------------------------------------------*/
//  {KEYVAL_SpikeBackUp,              B(10000000),    UserRun_Key_SpikeBackUp},
//  {KEYVAL_SpikeBackDown,            B(10000000),    UserRun_Key_SpikeBackDown},
  {KEYVAL_SpikeFeetUp,              B(10000000),    UserRun_Key_SpikeFeetUp},
  {KEYVAL_SpikeFeetDown,            B(10000000),    UserRun_Key_SpikeFeetDown},
  {KEYVAL_SpikeBackUpFeetDown,      B(10000000),    UserRun_Key_SpikeBackUpFeetDown},
  {KEYVAL_SpikeBackDownFeetUp,      B(10000000),    UserRun_Key_SpikeBackDownFeetUp},
  {KEYVAL_SpikeLegExtend,           B(10000000),    UserRun_Key_SpikeLegExtend},
  {KEYVAL_SpikeLegShorten,          B(10000000),    UserRun_Key_SpikeLegShorten},
  {KEYVAL_SpikeZeroGravity1,        B(10000000),    UserRun_Key_SpikeZeroGravity1},
//  {KEYVAL_SpikeZeroGravity2,        B(10000000),    UserRun_Key_SpikeZeroGravity2},
  {KEYVAL_SpikeZeroGravity,         B(10000000),    UserRun_Key_SpikeZeroGravity},
  {KEYVAL_SpikeHomeReset,           B(10000000),    UserRun_Key_SpikeHomeReset},
//  {KEYVAL_SpikeHomeReset,           B(10000000),    UserRun_Key_SpikeBackUpFeetDown},
//  {KEYVAL_SpikeULegExtend,          B(10000000),    UserRun_Key_SpikeULegExtend},
//  {KEYVAL_SpikeULegShorten,         B(10000000),    UserRun_Key_SpikeULegShorten},
  
  /*��о�ֶ� ���丨������  ���-----------------------------------------------------*/
  {KEYVAL_CoreXYZSpeedAdd,          B(00000000),    UserRun_Key_CoreXYZSpeedAdd},
  {KEYVAL_CoreXYZSpeedDec,          B(00000000),    UserRun_Key_CoreXYZSpeedDec},
  {KEYVAL_CoreXYZSpeed,             B(00000000),    UserRun_Key_CoreXYZSpeed},
  {KEYVAL_CoreTCSSpeedAdd,          B(00000000),    UserRun_Key_CoreTCSSpeedAdd},
  {KEYVAL_CoreTCSSpeedDec,          B(00000000),    UserRun_Key_CoreTCSSpeedDec},
  {KEYVAL_CoreTCSSpeed,             B(00000000),    UserRun_Key_CoreTCSSpeed},
  {KEYVAL_CoreWidthAdd,             B(00000000),    UserRun_Key_CoreWidthAdd},
  {KEYVAL_CoreWidthDec,             B(00000000),    UserRun_Key_CoreWidthDec},
  {KEYVAL_CoreWidth,                B(00000000),    UserRun_Key_CoreWidth},
  {KEYVAL_CoreMannualUp,            B(00000000),    UserRun_Key_CoreMannualUp},
  {KEYVAL_CoreMannualDown,          B(00000000),    UserRun_Key_CoreMannualDown},
  {KEYVAL_CoreMannualFront,         B(00000000),    UserRun_Key_CoreMannualFront},
  {KEYVAL_CoreMannualBack,          B(00000000),    UserRun_Key_CoreMannualBack},
  {KEYVAL_CoreFlexLevel,            B(00000000),    UserRun_Key_CoreFlexLevel},
  {KEYVAL_CoreSpot,                 B(00000000),    UserRun_Key_CoreSpot},
  {KEYVAL_CorePart,                 B(00000000),    UserRun_Key_CorePart},
//  {KEYVAL_CoreWhole,                B(00000000),    UserRun_Key_CoreWhole},
//  {KEYVAL_CoreSpotPartWhole,        B(00000000),    UserRun_Key_CoreSpotPartWhole},
  {KEYVAL_CoreRoll,                 B(00000000),    UserRun_Key_CoreRoll},
  {KEYVAL_CoreKnead,                B(00000000),    UserRun_Key_CoreKnead},
  {KEYVAL_CoreTap,                  B(00000000),    UserRun_Key_CoreTap},
  {KEYVAL_CoreClap,                 B(00000000),    UserRun_Key_CoreClap},
  {KEYVAL_CoreShiatsu,              B(00000000),    UserRun_Key_CoreShiatsu},
//  {KEYVAL_CoreMannualAction,        B(00000000),    UserRun_Key_CoreMannualAction},
//  {KEYVAL_CoreMannualMode,          B(00000000),    UserRun_Key_CoreMannualMode},
//  {KEYVAL_CoreMannualSpeed,         B(00000000),    UserRun_Key_CoreMannualSpeed},
  
  {KEYVAL_XYZAction,                B(00000000),    UserRun_Key_CoreXYZAction},
//  {KEYVAL_TCSAction,                B(00000000),    UserRun_Key_CoreTCSAction},
  
  /*���� �� ��������  ���------------------------------------------------------*/
  {KEYVAL_GasIntensityAdd,          B(00000000),    UserRun_Key_GasIntensityAdd},
  {KEYVAL_GasIntensityDec,          B(00000000),    UserRun_Key_GasIntensityDec},
  {KEYVAL_GasIntensity,             B(00000000),    UserRun_Key_GasIntensity},
//  {KEYVAL_GasHead,                  B(00000000),    UserRun_Key_GasHead},
  {KEYVAL_GasShoulder,              B(00000000),    UserRun_Key_GasShoulder},
  {KEYVAL_GasArms,                  B(00000000),    UserRun_Key_GasArms},
//  {KEYVAL_GasLumbar,                B(00000000),    UserRun_Key_GasLumbar},
//  {KEYVAL_GasSeat,                  B(00000000),    UserRun_Key_GasSeat},
  {KEYVAL_GasLumbarSeat,            B(00000000),    UserRun_Key_GasLumbarSeat},
  {KEYVAL_GasCalves,                B(00000000),    UserRun_Key_GasCalves},
//  {KEYVAL_GasFeet,                  B(00000000),    UserRun_Key_GasFeet},
//  {KEYVAL_GasCalvesFeet,            B(00000000),    UserRun_Key_GasCalvesFeet},
  {KEYVAL_AutoFullGas,              B(00000000),    UserRun_Key_GasFullGas},
  {KEYVAL_GasPartSelcet,            B(00000000),    UserRun_Key_GasPartSelcet},
  {KEYVAL_AutoQuickGas,             B(00000000),    UserRun_Key_GasQuickGas},

  /*���֡����� ���񶯡��� �������������--------------------------------------------*/
//  {KEYVAL_VibLumbarBack,            B(00000000),    UserRun_Key_VibLumbarBack},
//  {KEYVAL_VibSeat,                  B(00000000),    UserRun_Key_VibSeat},
//  {KEYVAL_VibCalves,                B(00000000),    UserRun_Key_VibCalves},
//  {KEYVAL_VibFeet,                  B(00000000),    UserRun_Key_VibFeet},
//  {KEYVAL_HeatLevelAdd,             B(00000000),    NULL},
//  {KEYVAL_HeatLevelDec,             B(00000000),    NULL},
//  {KEYVAL_HeatLevel,                B(00000000),    NULL},
  {KEYVAL_HeatLumbarBack,           B(00000000),    UserRun_Key_HeatLumbarBack},
  {KEYVAL_HeatSeat,                 B(00000000),    UserRun_Key_HeatLumbarBack/*UserRun_Key_HeatSeat*/},
//  {KEYVAL_HeatCalves,               B(00000000),    UserRun_Key_HeatCalves},
//  {KEYVAL_HeatFeet,                 B(00000000),    UserRun_Key_HeatFeet},
  {KEYVAL_RollerCalves,             B(00000000),    UserRun_Key_RollerCalves},
  {KEYVAL_RollerFeet,               B(00000000),    UserRun_Key_RollerFeet},
  {KEYVAL_SleepLed,                 B(00000000),    UserRun_Key_SleepLed},

  /*�Զ�������� -------------------------------------------------------------------*/
  {KEYVAL_AutoQuick,                B(00000000),    UserRun_Key_AutoQuick},
  {KEYVAL_AutoRelax,                B(00000000),    UserRun_Key_AutoRelax},
  {KEYVAL_AutoMoveSleep,            B(00000000),    UserRun_Key_AutoMoveSleep},
  {KEYVAL_AutoStretch,              B(00000000),    UserRun_Key_AutoStretch},
  {KEYVAL_AutoScraping,             B(00000000),    UserRun_Key_AutoScraping},
  {KEYVAL_AutoShiatsu,              B(00000000),    UserRun_Key_AutoShiatsu},
  {KEYVAL_AutoLady,                 B(00000000),    UserRun_Key_AutoLady},
  {KEYVAL_AutoMan,                  B(00000000),    UserRun_Key_AutoMan},
  {KEYVAL_AutoShoulderRelax,        B(00000000),    UserRun_Key_AutoShoulderRelax},
  {KEYVAL_AutoShoulderRecovery,     B(00000000),    UserRun_Key_AutoShoulderRecovery},
  {KEYVAL_AutoShoulderTuina,        B(00000000),    UserRun_Key_AutoShoulderTuina},
  {KEYVAL_AutoShoulderShiatsu,      B(00000000),    UserRun_Key_AutoShoulderShiatsu},
  {KEYVAL_AutoLumbarButtockRelax,   B(00000000),    UserRun_Key_AutoLumbarButtockRelax},
  {KEYVAL_AutoLumbarButtockRecovery,B(00000000),    UserRun_Key_AutoLumbarButtockRecovery},
  {KEYVAL_AutoLumbarButtockPress,   B(00000000),    UserRun_Key_AutoLumbarButtockPress},
  {KEYVAL_AutoLumbarKidneyCare,     B(00000000),    UserRun_Key_AutoLumbarKidneyCare},
  
  {KEYVAL_AutoGridCombo,            B(00000000),    UserRun_Key_AutoGridCombo},

  /*����ģʽ���л�------------------------------------------------------------------*/
  {KEYVAL_InspectAuto,              B(00000000),    UserRun_Key_InspectAuto},           /*ϵͳģʽ�������Լ�*/
  {KEYVAL_InspectManual,            B(00000000),    UserRun_Key_InspectManual},         /*ϵͳģʽ�������ּ�*/
  {KEYVAL_PackingAngle,             B(00000000),    UserRun_Key_PackingAngle},          /*ϵͳģʽ�����Ұ�װ*/
  {KEYVAL_InspectOther1,            B(00000000),    UserRun_Key_InspectOther1},         /*ϵͳģʽ��ϵͳģʽ���������Ҽ�� 1*/
  {KEYVAL_InspectOther2,            B(00000000),    UserRun_Key_InspectOther2},         /*ϵͳģʽ��ϵͳģʽ���������Ҽ�� 2*/
  {KEYVAL_TestNoTimer,              B(00000000),    UserRun_Key_TestNoTimer},           /*ϵͳģʽ�����ҿ��� ֮ �޶�ʱ����ģʽ*/
  {KEYVAL_TestSpike,                B(00000000),    UserRun_Key_TestSpike},             /*ϵͳģʽ�����ҿ��� ֮ �Ƹ�*/
  {KEYVAL_TestAge,                  B(00000000),    UserRun_Key_TestAge},               /*ϵͳģʽ�����ҿ��� ֮ ���� ��һСʱ��ͣ15����*/

  /*--------------------------------------------------------------------------------*/
  {KEYVAL_MAX,                      B(00000000),    NULL}
};


#define USERRUN_KEY_TAB_NUM  TAB_NUM(UserRun_KeyLogicTab)

static uint16_t UserRun_GetKeyValID(uint16_t index)
{
  if(index > (USERRUN_KEY_TAB_NUM-1))
  {
    return INDEX_NO_MATCH;
  }
  return UserRun_KeyLogicTab[index].KeyValID;
}

/*
************************************************************************************************************************
* �������� : UserRun_KeyValAdditonOp                                                                                                         
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
uint8_t UserRun_KeyValAdditonOp(uint8_t Index, uint8_t BeforeAfter, uint8_t CurExeState)
{
  uint8_t ret;


  ret = SUCCESS;                                                /*�ȼ���ɹ�*/
  
  /*��ִֵ��ǰ�ĸ��Ӳ���------------------------------------------------------*/
  if(BEFORE == BeforeAfter) 
  {
    /*��ִֵ��ǰ��bit7 -- 1��ERP����Դ�رգ����ִֵ��ǰ��Ҫ���¿�����    
                          0��ERP����Դ�رգ����ִֵ��ǰ������Ҫ���¿����� */   
    if(UserRun_KeyLogicTab[Index].AdditonOp & B(10000000))
    {
      if(OFF == pMChair->ERPPowerSw)                            /*����Դ���رգ������¿���*/
      {
        pMChair->ERPPowerSw = ON;                               /*��������Դ*/
        pMChair->ERPPowerOnTimeMs = 0;
      }
      pMChair->ERPPowerOffWaitTimeMs = 0;
    }

    /*��ִֵ��ǰ��bit6 -- 1����ͣ�������Կ�ִ�м�ֵ��  
                          0����ͣ���������ֵ��ִ�С�*/
    if(0 == (UserRun_KeyLogicTab[Index].AdditonOp & B(01000000))) 
    {
      if(TRUE == pMChair->CSFlag.Bit.Pause)
      {
        ret = FAIL;                                             /*��ͣ��������ִ�м�ֵ����*/
      }
    }

    /*��ִֵ��ǰ��bit5 -- 1�����ܱ���״̬��ֱ��ִ�м�ֵ
                          0���ֿ����������رգ���Ҫ�ȿ������ұ��μ�ֵ��Ч��*/
    if(0 == (UserRun_KeyLogicTab[Index].AdditonOp & B(00100000))) 
    {
      if(0 == pMChair->LcdBackLightTLMs)                        /*����ʱ���Ѿ�����*/
      {
        ret = FAIL;                                             /*�������رգ���ִ�м�ֵ����*/
        pMChair->LcdBackLightTLMs = 60000;                      /*Ҫ��������´μ�ֵ����Ч*/
      }
    }
  }
  
  /*��ִֵ�к�ĸ��Ӳ���----------------------------------------------------*/
  else
  {
    if((SUCCESS == CurExeState) &&                               /*��ֵ�ɹ�ִ��*/
       (UserRun_KeyLogicTab[Index].KeyValID != KEYVAL_NoPress))  /*�а�������*/
    {
      pMChair->PromptToneTLMs = 300;                             /*��ֵ�ɹ�ִ�У�����ʾ��*/
      pMChair->LcdBackLightTLMs = 60000;                         /*������*/
    }
  }

  return ret;
}


/*����������������������������������������������������������������������������������������������������������������������*/
/*
************************************************************************************************************************
* �������� : SysMode_UserRun_Timer                                                                                                         
* �������� : �û����� ��ض�ʱ����                                                                                    
* ������� : ExePeriod -- ִ������                                                                         
* ���ز��� : ��                                                               
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SysMode_UserRun_Timer(Ticker_t ExePeriod)
{
  if(TRUE == pMChair->CSFlag.Bit.TabTryRun)
  {
    return;  /*�������ʱ����ִ���κζ�ʱ���ܣ�ֱ�ӷ���*/
  }
  
  /*=======================================================================*/
  /*ϵͳģʽ�����ҿ��� ֮ �޶�ʱ����ģʽ, ������������---------------------*/
  if(SYS_MODE_TESTNOTIMER == pMChair->SysModeCur)
  {
    Core_SetZMBackProtectDisableSw(ON);       /*����ʱ���رջ�о��3D�˵���������*/
    return;                                   /*��ִ���κζ�ʱ���ܣ�ֱ�ӷ���*/
  }

  /*=======================================================================*/
  /*ϵͳģʽ�����ҿ��� ֮ ������ ��һСʱ��ͣ15����------------------------*/
  else if(SYS_MODE_TESTAGE == pMChair->SysModeCur)
  {
    Core_SetZMBackProtectDisableSw(ON);       /*����ʱ���رջ�о��3D�˵���������*/
    
    pMChair->CommonTimeSec++;

    if(pMChair->CommonTimeSec > (3600+900)) 
    {
      pMChair->CommonTimeSec = 0;             /*1h+15min �����¼�ʱ*/
      pMChair->CSFlag.Bit.Pause = FALSE;
    }
    else if(pMChair->CommonTimeSec > 3600)
    {
      pMChair->CSFlag.Bit.Pause = TRUE;       /*1h ����ͣ15min*/
    }
    
    if(pMChair->CSFlag.Bit.LegFlexTestSw == TRUE)
    {
      pMChair->CommonTimeSec1++;
      if(pMChair->CommonTimeSec1 <= 60)               
      {
        Spike_SetLegFlexAngle(PLEGFLEX_MAX);          /*�����Ƹ������*/
      }
      else if(pMChair->CommonTimeSec1 <= 120)               
      {
        Spike_SetLegFlexAngle(PLEGFLEX_MIN);          /*�����Ƹ��������*/
      } 
      else
      {
        pMChair->CommonTimeSec1 = 0;
      }      
    }
  }

  /*=======================================================================*/
  /*�û�����ģʽ��  ��Ħ��ʱ-----------------------------------------------*/
  else if(SYS_MODE_USERRUN == pMChair->SysModeCur)
  {
    if((pMChair->ComponentFuncState.Bit.Core           != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.Gas            != FUNC_TYPE_NONE) ||
       //(pMChair->ComponentFuncState.Bit.Spike        != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.FeetVib        != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.CalvesVib      != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.SeatVib        != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.LumbarBackVib  != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.FeetRoller     != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.CalvesRoller   != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.FeetHeat       != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.CalvesHeat     != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.SeatHeat       != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.LumbarBackHeat != FUNC_TYPE_NONE) )
       //(pMChair->ComponentFuncState.Bit.Led            != FUNC_TYPE_NONE) )
    {
      if(TRUE == pMChair->CSFlag.Bit.UserMassageTimeOut)           /*������ʱ��*/
      {
        /* ��ʱ���󣬻����MChair_FuncLogic_ClearAllFunc()�����㰴Ħ���ܣ�
         * 120s�ڰ�Ħ���Դ����û�����ģʽ�£��û��ɲ����������´򿪰�Ħ���ܡ�
         * ��ʱ��Ӧ�����³�ʼ����ʱ��ʱ�䡣���ڿ�����Ĭ��ʱ��Ĺ��ܻ��UserMassageTimeMin�ȸ�ֵ��
         * ��ˣ������ж�UserMassageTimeMinΪ0ʱ�����û��ٴο����˲���Ĭ��ʱ��Ĺ���ʱ���Ŷ�UserMassageTimeMin��ֵ��*/
        if(0 == pMChair->UserMassageTimeMin)
        {
          pMChair->UserMassageTimeMin = MASSAGETIME_MIN_DEFAULT;   /*��Ħʱ�� ��*/
          pMChair->UserMassageTimeSec = 0;                         /*��Ħʱ�� ��*/
        }
        pMChair->UserMassageTimeDelayOnSec = 0;                    /*��Ħ��ʱ����ʱ����������*/
        pMChair->CSFlag.Bit.UserMassageTimeOut = FALSE;            /*��Ħ��ʱ ʱ�䵽 ����*/
      }

      pMChair->UserMassageIdleTimeSec = 0;                         /*�й��ܣ���Ħ����ʱ������*/
      pMChair->CSFlag.Bit.UserMassageTimeRun = ON;                 /*�й��� ��ʼ��Ħ��ʱ*/
    }
    else
    {
//      if(pMChair->UserMassageIdleTimeSec < 180)
//      {
//        pMChair->UserMassageIdleTimeSec++;                         /*�ް�Ħ���ܿ������ۼư�Ħ����ʱ��*/
//      }
//      else
//      {
//        /*180s��û������ذ�Ħ���ܣ����Ե�ǰ���Ƹ˽Ƕȣ��û������ֶ������ˣ����Զ��ػ�*/
//        SysMode_Standby_Enter(SYS_MODE_USERRUN, FALSE);            /*�ػ������ֵ�ǰ�Ƹ˽Ƕ�*/
//      }
    }

    /*����ʱ------------------------------------------------------------------*/
    if(pMChair->UserMassageTimeDelayOnSec < 10)
    {
      pMChair->UserMassageTimeDelayOnSec++;
    }

    if((OFF == pMChair->CSFlag.Bit.UserMassageTimeRun)                 || /*��ʱδ�������а�Ħ��ع���ʱ���ſ���*/
       (pMChair->UserMassageTimeDelayOnSec <= MASSAGETIME_DELAYON_SEC) || /*��ʱ��ʱ����ʱ�� δ��*/
       (TRUE == pMChair->CSFlag.Bit.Pause)                             || /*ϵͳ��ͣʱ������ʱ*/
       (TRUE == pMChair->StateBodyScan.Bit.Run)                        )  /*����ɨ��ʱ������ʱ*/
    {
      return; 
    }

    if(pMChair->UserMassageTimeSec > 0)
    {
      pMChair->UserMassageTimeSec--;
    }
    else
    {
      if(pMChair->UserMassageTimeMin > 0)
      {
        pMChair->UserMassageTimeSec = 59;
        pMChair->UserMassageTimeMin--;
      }
      else
      {
        pMChair->CSFlag.Bit.UserMassageTimeOut = TRUE;     /*���ö�ʱ����ʶ*/
        pMChair->CSFlag.Bit.UserMassageTimeRun = OFF;      /*�ض�ʱ������*/
        MChair_FuncLogic_ClearAllFunc();                   /*�������а�Ħ����*/
        pMChair->UserMassageIdleTimeSec = 60;              /*��ʱ���󣬻���180-60=120s�ĵȴ��û�����������ʱ��*/ 
        //SysMode_Standby_Enter(SYS_MODE_USERRUN, FALSE);  /*��ʱ����ػ������ֵ�ǰ�Ƹ˽Ƕ�*/
        /*��ʱ���󲻹ػ������ֵ�ǰ�Ƹ˽Ƕ�*/
        Spike_SetLegFlexAngle(PLEGFLEX_MIN);               /*�����Ƹ��������*/
        Spike_SetULegFlexAngle(PULEGFLEX_MAX);             /*��С���쵽�*/
        Spike_SetAngle(PKEEP, PKEEP, PKEEP);               /*ֹͣ�Ƹ�*/
      }
    }

    /*ʱ��ʣ1����ʱ����ʾ��10s*/
    if((0== pMChair->UserMassageTimeMin)  &&
       (pMChair->UserMassageTimeSec > 50)  && 
       (pMChair->UserMassageTimeSec <= 59))
    {
      pMChair->PromptToneTLMs = 300;                             
    }

    //    if(pMChair->UserMassageTimeSec < 60)
//    {
//      pMChair->UserMassageTimeSec++;
//    }
//    else
//    {
//      if(pMChair->UserMassageTimeMin > 1)
//      {
//        pMChair->UserMassageTimeSec = 0;
//        pMChair->UserMassageTimeMin--;
//      }
//      else
//      {
//        pMChair->UserMassageTimeMin = 0;                   /*��ʱ����ʱ������*/
//        pMChair->CSFlag.Bit.UserMassageTimeOut = TRUE;     /*���ö�ʱ����ʶ*/
//        pMChair->CSFlag.Bit.UserMassageTimeRun = OFF;      /*�ض�ʱ������*/
//        MChair_FuncLogic_ClearAllFunc();                   /*�������а�Ħ����*/

//        pMChair->UserMassageIdleTimeSec = 60;              /*��ʱ���󣬻���180-60=120s�ĵȴ��û�����������ʱ��*/ 
//        //SysMode_Standby_Enter(SYS_MODE_USERRUN, FALSE);  /*��ʱ����ػ������ֵ�ǰ�Ƹ˽Ƕ�*/
//      }
//    }

//    /*ʱ��ʣ1����ʱ����ʾ��10s*/
//    if((1== pMChair->UserMassageTimeMin)  &&
//       (pMChair->UserMassageTimeSec > 0)  && 
//       (pMChair->UserMassageTimeSec <= 10))
//    {
//      pMChair->PromptToneTLMs = 300;                             
//    }
  }
}

/*
************************************************************************************************************************
* �������� : SysMode_UserRun_Init                                                                                                         
* �������� : ϵͳģʽ ֮ �û����� ��ʼ��                                                                                    
* ������� : ��                                                                                 
* ���ز��� : ��                                                                 
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SysMode_UserRun_Init(void)
{
  uint8_t i;


  /*����ֵ��������Ƿ���ȷ------------------------------*/
  for(i=1; i<USERRUN_KEY_TAB_NUM; i++)
  {
    if(UserRun_KeyLogicTab[i].KeyValID <= UserRun_KeyLogicTab[i-1].KeyValID)
    {
      while(1);  /*�뽫KeyValID ��С�������ظ�����ʹ��*/
    }   
  }
}

/*
************************************************************************************************************************
* �������� : SysMode_UserRun_Handle                                                                                                         
* �������� : ϵͳģʽ ֮ �û����д���                                                                                    
* ������� : ��                                                                            
* ���ز��� : ��                                                             
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SysMode_UserRun_Handle(void)
{
  /*����ģʽ�л�����-----------------------------------------------------*/
  if(pMChair->SysModeHis != pMChair->SysModeCur)
  {
    pMChair->SysModeHis = pMChair->SysModeCur; 
    pMChair->CSFlag.Bit.Pause = FALSE;                          
  }

  /*���ݸ���ģʽ�Ĳ�ͬ���Լ�ֵ������ر�����ֵ---------------------------*/
  pMChair->KeyValHandle.KeyLogicTab    = UserRun_KeyLogicTab;      /*�����߼���*/
  pMChair->KeyValHandle.KeyLogicTabNum = USERRUN_KEY_TAB_NUM;      /*�����߼��� ��С*/
  pMChair->KeyValHandle.pGetMatchID    = UserRun_GetKeyValID;      /*����ָ�룬ָ��ĺ������ã����ر����Ŀ �� ��Ҫ���������� ���ڵ�����*/
  pMChair->KeyValHandle.pAddOp         = UserRun_KeyValAdditonOp;  /*����ָ�룬ָ��ĺ������ã���ִֵ��ǰ��ĸ��Ӳ��� */
}

/*
************************************************************************************************************************
* �������� : SysMode_UserRun_Enter                                                                                                         
* �������� : ϵͳģʽ ֮ �û����� ����                                                                                    
* ������� : ��                                                                            
* ���ز��� : SUCCESS -- ����ɹ�     FAIL -- ����ʧ��                                                               
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t SysMode_UserRun_Enter(void)
{
  if(TRUE == pMChair->CSFlag.Bit.OccurNoStartUpFault)    
  {
    pMChair->ERPPowerSw = ON;                                            /*��������Դ������ƽ�����ʾ������*/
    pMChair->ERPPowerOffWaitTimeMs = 0;
    return FAIL;                                                         /*���������������Ĺ���*/
  }

  if((FALSE == pMChair->StateXMotor.Bit.PositionResetOK) ||
     (FALSE == pMChair->StateYMotor.Bit.PositionResetOK) ||
     (FALSE == pMChair->StateZMotor.Bit.PositionResetOK) )
  {
    return FAIL;                                                         /*��оλ�û�δ��λ*/
  }
  
  if(Core_GetYPosition() != PY_MIN)
  {
    return FAIL;                                                         /*��о�����ڶ���*/
  }

  if((FALSE == pMChair->StateBackSpike.Bit.PositionResetOK)   ||
     //(FALSE == pMChair->StateZeroSpike.Bit.PositionResetOK)    ||
     (FALSE == pMChair->StateFeetSpike.Bit.PositionResetOK)   ||
     (FALSE == pMChair->StateLegFlexSpike.Bit.PositionResetOK)) 
  {
    return FAIL;                                                         /*�Ƹ�λ�û�δ��λ*/
  }

  if(pMChair->SysModeCur != SYS_MODE_STANDBY)                      
  {
    return FAIL;                                                         /*ֻ�ܴӴ���ģʽ�����û�����ģʽ*/
  }

  pMChair->CSFlag.Bit.MChairReported = TRUE;                             /*�����ϱ�*/  
  /*����ʱ�����ܻ����в��ֹ��ܿɿ����������Ƹ˹��ܡ���˿���ǰ �������а�Ħ����*/
  MChair_FuncLogic_ClearAllFunc();  
  
  Spike_SetAngle(PBACK_USER_ANGLE, PFEET_USER_ANGLE, PZERO_USER_ANGLE);  /*�����Ƕ�*/

  pMChair->FuncMA_Led.Bit.Logo = FMA_LOGO_LED_Mannual;                   /*�����ʹ�Logo�ƹ�*/
  pMChair->FuncMA_Led.Bit.Projection = FMA_PROJECTION_LED_Mannual;       /*�����ʹ�ͶӰ�ƹ�*/

  pMChair->SysModeCur    = SYS_MODE_USERRUN;                             /*�����û�����ģʽ*/
  pMChair->SysModeHis    = SYS_MODE_STANDBY;                             /*ֻ�ܴӴ���ģʽ����*/
  pMChair->SysModeVender = SYS_MODE_NONE;                                /*�޳���ģʽ*/

  pMChair->LcdBackLightTLMs = 60000;                                     /*������*/

  return SUCCESS;
}
