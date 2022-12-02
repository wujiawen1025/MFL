/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣ�FuncMannual_Core.c 
**
**    ��������:����о���ֶ�����
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
static  CoreXYZMannualArrt_t CoreXYZMannualAttr;      /*�ֶ���������ع�������*/
static  uint8_t  XYZRollForTCS;                       /*��TCS�������������(����)*/

static  uint8_t  VenderTest3DFlex;                    /*���Ҳ���3D����*/
/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : MChair_CoreMannualVenderTest3DSwSet                                                                                               
* �������� : ��Ħ�� �����ֶ����򳧼ҿ���3D����                                                                          
* ������� : Sw -- ��0���ʾ����3D�Զ�����                                                                                    
* ���ز��� : ��                                                                                           
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_CoreMannualVenderTest3DSwSet(uint8_t Sw)
{
  VenderTest3DFlex = Sw; 
}


/*
************************************************************************************************************************
* �������� : MChair_GetCoreMannualWidthMax                                                                                               
* �������� : ��Ħ�� ��û�о�ֶ����� ʱ������ֵ                                                                                
* ������� : ��                                                                                      
* ���ز��� : �ֶ������£��ɵ��ڵ�����ȡ�
*            ����ֵ��PKEEP -- ��Ȳ��ɵ���                                                                                               
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
uint8_t MChair_GetFuncCoreMannualWidthMax(void)
{
  return CoreXYZMannualAttr.XMax; 
}

/*
************************************************************************************************************************
* �������� : MChair_GetCoreMannualFlexLevelMax                                                                                               
* �������� : ��Ħ�� ��û�о�ֶ����� ʱ���������ֵ                                                                                
* ������� : ��                                                                                      
* ���ز��� : �ֶ������£��ɵ��ڵ���������ȡ�
*            ����ֵ��PKEEP -- �����Ȳ��ɵ���                                                                                               
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
uint8_t MChair_GetFuncCoreMannualFlexLevelMax(void)
{
  return CoreXYZMannualAttr.ZMax; 
}

/*
************************************************************************************************************************
* �������� : MChair_GetFuncCoreMannualXYZSpeedMax                                                                                               
* �������� : ��Ħ�� ��û�о�ֶ����� ʱXYZ�ַ��ٶ����ֵ                                                                              
* ������� : ��                                                                                      
* ���ز��� : �ֶ������£��ɵ��ڵ�����ٶȡ�
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
uint8_t MChair_GetFuncCoreMannualXYZSpeedMax(void)
{
  return CoreXYZMannualAttr.SpeedMax; 
}

/*
************************************************************************************************************************
* �������� : MChair_FuncSwitch_CoreMannual                                                                                               
* �������� : ��Ħ�� �����л� ֮  ����о���ֶ�                                                                                
* ������� : SwitchMode -- �л�ģʽ��ȡֵ��OPEN�򿪣� 
*                                          CLOSE�ر� 
*            pFuncLogic -- ָ���������߼���ָ�롣                                                                                      
* ���ز��� : ��                                                                                               
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_CoreMannual(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  CoreAction_t  HisAction;

  if(OPEN == SwitchMode)
  {
    HisAction.All = *pFuncLogic->pFuncHis;

    if(pMChair->FuncMannual_Core.Bit.XYZ.All != HisAction.Bit.XYZ.All )
    {
      if(XYZ_NONE == pMChair->FuncMannual_Core.Bit.XYZ.All) 
      {
        if(pMChair->FuncMannual_Core.Bit.TCS.All > 0)                 /*XYZ�޶�������TCS�ж���*/
        {
          XYZRollForTCS = ROLL;                                       /*��Ҫ ����TCS���������(����)*/
        }
      }
      else
      {
        XYZRollForTCS = XYZ_ACTION_NONE;                              /*XYZ�ж��� �ر�TCS���������(����)*/
        if(ROLL == pMChair->FuncMannual_Core.Bit.XYZ.All)   
        {
          pMChair->FuncMannual_Core.Bit.TCS.All = TCS_ACTION_NONE;    /*XYZ�ֶ�����(����)Ҫ�ر��û�*/
          if(CORE_ROLL_RANGE_SPOT == Core_GetRollRange())             /*����ʱ��Ҫ�رն���*/
          {
            Core_SetRollRange(CORE_ROLL_RANGE_WHOLE);
          }
        }
      }

      pMChair->MannualCoreXYZActionSpeed = 3;                         /*�л�XYZ��������Ĭ���Ƽ��ٶ�*/
      pMChair->MannualCoreWidth = 0;                                  /*�л�XYZ��������Ĭ���Ƽ����*/
    }
    else if(pMChair->FuncMannual_Core.Bit.TCS.All != HisAction.Bit.TCS.All )
    {
      if(pMChair->FuncMannual_Core.Bit.TCS.All > 0)
      {
        if(ROLL == pMChair->FuncMannual_Core.Bit.XYZ.All)       
        {
          pMChair->FuncMannual_Core.Bit.XYZ.All = XYZ_ACTION_NONE;    /*�ֶ��û�Ҫ�ر��ֶ�����(����)*/
        }
        if(XYZ_ACTION_NONE == pMChair->FuncMannual_Core.Bit.XYZ.All) 
        {
          XYZRollForTCS = ROLL;                                       /*�������������(����)*/
        }  
      }
      else
      {
        XYZRollForTCS = XYZ_ACTION_NONE;
      }      
    }

    if(ROLL == XYZRollForTCS)
    {
      Core_GetXYZMannualManageAttr(XYZRollForTCS, &CoreXYZMannualAttr);
    }
    else
    {
      Core_GetXYZMannualManageAttr(pMChair->FuncMannual_Core.Bit.XYZ.All, &CoreXYZMannualAttr);
    }  
    
    /*�����л�ʱ��ͬʱ�����������ļ���ֵ*/
    if(pMChair->MannualCoreWidth > CoreXYZMannualAttr.XMax)
    {
      pMChair->MannualCoreWidth = CoreXYZMannualAttr.XMax; 
    }
    
    if(CoreXYZMannualAttr.ZPrePosition != PKEEP)
    {
      pMChair->MannualCoreFlexLevel = CoreXYZMannualAttr.ZPrePosition; 
    }
    if(pMChair->MannualCoreFlexLevel > CoreXYZMannualAttr.ZMax)
    {
      pMChair->MannualCoreFlexLevel = CoreXYZMannualAttr.ZMax; 
    }
    
    if(pMChair->MannualCoreXYZActionSpeed > CoreXYZMannualAttr.SpeedMax)
    {
      pMChair->MannualCoreXYZActionSpeed = CoreXYZMannualAttr.SpeedMax; 
    }
  }
  else// if(CLOSE == SwitchMode)
  {
    pMChair->MannualCoreWidth          = PXWIDE;     /*�ֶ�������  ��о���*/
    pMChair->MannualCoreFlexLevel      = 2;          /*�ֶ�������  ��о������*/
    pMChair->MannualCoreTCSActionSpeed = 3;          /*�ֶ�������  TCS�����ַ��ٶ�*/
    pMChair->MannualCoreXYZActionSpeed = 3;          /*�ֶ�������  XYZ�����ַ��ٶ�*/
 
    Core_SetXYZPosition(PXWIDE, PYTOP, PZBACK); 
    Core_SetAction(CORE_ACTION_EXE_NONE, XYZ_ACTION_NONE, TCS_ACTION_NONE); 

    /*-----------------------------------------------------------*/
    VenderTest3DFlex = 0;
  }
}

/*
************************************************************************************************************************
* �������� : MChair_FuncExe_CoreMannual                                                                                               
* �������� : ��Ħ�� ����ִ�� ֮  ����о���ֶ�                                                                                
* ������� : ExePeriod  -- ִ������
*            pFuncLogic -- ָ���������߼���ָ�롣                                                                                      
* ���ز��� : ��                                                                                               
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_CoreMannual(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  static  Ticker_t  Period;

  pMChair->ComponentFuncState.Bit.Core = FUNC_TYPE_MANNUAL;            /*��о����״̬���ֶ�*/

  if((TRUE  == CoreXYZMannualAttr.ExeOp.Bit.PreBackScan) &&            /*��XYZ������Ҫ��ִ�б������*/
     (FALSE == pMChair->StateBodyScan.Bit.Finish)       )              /*����ɨ��δ���*/
  {
    return;
  }

  /*�����û��ĵ���ֵ*/
  Core_SetTCSActionSpeed(pMChair->MannualCoreTCSActionSpeed);
  Core_SetXYZActionSpeed(pMChair->MannualCoreXYZActionSpeed);

  Core_SetXPosition(pMChair->MannualCoreWidth); 
  
  if(VenderTest3DFlex)    /*���һ�о�ֶ����򿽻�ʱ����3D�����Ĵ���*/
  {
    Period += ExePeriod;
    if(Period < 6000)
    {
      pMChair->MannualCoreFlexLevel = 0;
    }
    else if(Period < 12000)
    {
      pMChair->MannualCoreFlexLevel = 5;
    }
    else
    {
      Period = 0;
    }
    
    if(Core_GetYPosition() <= 9)
    {
      pMChair->MannualCoreFlexLevel = (pMChair->MannualCoreFlexLevel>4) ? 4 : pMChair->MannualCoreFlexLevel;
    }
    else if(Core_GetYPosition() <= 22)
    {
      pMChair->MannualCoreFlexLevel = (pMChair->MannualCoreFlexLevel>3) ? 3 : pMChair->MannualCoreFlexLevel;
    }
    else 
    {
      pMChair->MannualCoreFlexLevel = (pMChair->MannualCoreFlexLevel>2) ? 2 : pMChair->MannualCoreFlexLevel;
    }      
  }
  Core_SetZPosition(pMChair->MannualCoreFlexLevel); 

  /*ִ�ж���*/
  if(ROLL == XYZRollForTCS)
  {
    Core_SetAction(CORE_ACTION_EXE_MANNNUAL, XYZRollForTCS, pMChair->FuncMannual_Core.Bit.TCS.All); 
  }
  else
  {
    Core_SetAction(CORE_ACTION_EXE_MANNNUAL, pMChair->FuncMannual_Core.Bit.XYZ.All, pMChair->FuncMannual_Core.Bit.TCS.All); 
  }  
}
