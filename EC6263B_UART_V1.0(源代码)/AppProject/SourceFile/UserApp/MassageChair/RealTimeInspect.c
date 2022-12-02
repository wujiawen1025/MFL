/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: RealTimeInspec.c 
**
**    ��������: ʵʱ���
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
#include "RealTimeInspect.h"
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


/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/

uint8_t FaultCheck_01(void)
{
  return  NORMAL;
}

uint8_t FaultCheck_02(void)
{
  return pMChair->StateCDPCenXxxCSFlag.Bit.CtrlLinkLostFault;
}

uint8_t FaultCheck_03(void)
{
  return pMChair->StateCDPCenXxxCSFlag.Bit.CoreLinkLostFault;
}

uint8_t FaultCheck_04(void)
{
  return pMChair->StateYMotor.Bit.CountFault; 
}

uint8_t FaultCheck_05(void)
{
  return  pMChair->StateCDPCSFlag.Bit.CenXxx_SideCtrlKeyStuck;
}

uint8_t FaultCheck_06(void)
{
  return  pMChair->StateCDPCenXxxCSFlag.Bit.CalvesFeetLinkLostFault;
}

uint8_t FaultCheck_07(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_08(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_09(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_10(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_11(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_12(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_13(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_14(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_15(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_16(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_17(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_18(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_19(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_20(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_21(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_22(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_23(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_24(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_25(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_26(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_27(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_28(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_29(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_30(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_31(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_32(void)
{
  return  pMChair->StateCDPCenXxxCSFlag.Bit.SideCtrlLinkLostFault;
}

uint8_t FaultCheck_33(void)
{
  if(TRUE == pMChair->StateBodyScan.Bit.NoHumanOnSeat) 
  {
    return FAULT;
  }

  return  NORMAL;
}

uint8_t FaultCheck_34(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_35(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_36(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_37(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_38(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_39(void)
{

  return  NORMAL;
}

uint8_t FaultCheck_40(void)
{
  return (pMChair->StateYMotor.Bit.PositionSensorFault | pMChair->VenderInspect.Result.Bit.YPositionSensorFault);
}

uint8_t FaultCheck_41(void)
{
  return pMChair->StateYMotor.Bit.PositionCodeFault;
}

uint8_t FaultCheck_42(void)
{
  return pMChair->StateYMotor.Bit.RPMSensorFault;
}

uint8_t FaultCheck_43(void)
{
  return pMChair->StateYMotor.Bit.OverCurrentFault;
}

uint8_t FaultCheck_44(void)
{
  return (pMChair->StateXMotor.Bit.PositionSensorFault | pMChair->VenderInspect.Result.Bit.XPositionSensorFault);
}

uint8_t FaultCheck_45(void)
{
  return pMChair->StateXMotor.Bit.PositionCodeFault;
}

uint8_t FaultCheck_46(void)
{
  return pMChair->StateXMotor.Bit.RPMSensorFault;
}

uint8_t FaultCheck_47(void)
{
  return pMChair->StateXMotor.Bit.OverCurrentFault;
}

uint8_t FaultCheck_48(void)
{
  return (pMChair->StateZMotor.Bit.PositionSensorFault | pMChair->VenderInspect.Result.Bit.ZPositionSensorFault);
}

uint8_t FaultCheck_49(void)
{
  return pMChair->StateZMotor.Bit.PositionCodeFault;
}

uint8_t FaultCheck_50(void)
{
  return pMChair->StateZMotor.Bit.RPMSensorFault;
}

uint8_t FaultCheck_51(void)
{
  return pMChair->StateZMotor.Bit.OverCurrentFault;
}

uint8_t FaultCheck_52(void)
{
  return pMChair->StateTCSMotor.Bit.RPMSensorFault;
}

uint8_t FaultCheck_53(void)
{
  return pMChair->StateTCSMotor.Bit.OverCurrentFault;
}

uint8_t FaultCheck_54(void)
{
  return  NORMAL;
}

uint8_t FaultCheck_55(void)
{
  return  NORMAL;
}

uint8_t FaultCheck_56(void)
{
  return (pMChair->StateBackSpike.Bit.PositionSensorFault | pMChair->VenderInspect.Result.Bit.BackPositionSensorFault);
}

uint8_t FaultCheck_57(void)
{
  return pMChair->StateBackSpike.Bit.PositionCodeFault;
}

uint8_t FaultCheck_58(void)
{
  return pMChair->StateBackSpike.Bit.OverCurrentFault;
}

uint8_t FaultCheck_59(void)
{
  return pMChair->StateBackSpike.Bit.CountFault;
}

uint8_t FaultCheck_60(void)
{
  return (pMChair->StateFeetSpike.Bit.PositionSensorFault | pMChair->VenderInspect.Result.Bit.FeetPositionSensorFault);
}

uint8_t FaultCheck_61(void)
{
  return pMChair->StateFeetSpike.Bit.PositionCodeFault;
}

uint8_t FaultCheck_62(void)
{
  return pMChair->StateFeetSpike.Bit.OverCurrentFault;
}

uint8_t FaultCheck_63(void)
{
  return pMChair->StateFeetSpike.Bit.CountFault;
}

uint8_t FaultCheck_64(void)
{
  return  NORMAL;
}

uint8_t FaultCheck_65(void)
{
  return  NORMAL;
}

uint8_t FaultCheck_66(void)
{
  return  NORMAL;
}

uint8_t FaultCheck_67(void)
{
  return  NORMAL;
}

uint8_t FaultCheck_68(void)
{
  return  pMChair->StateLegFlexSpike.Bit.CountFault;
}

uint8_t FaultCheck_69(void)
{
  return  pMChair->StateLegFlexSpike.Bit.PositionCodeFault;
}


uint8_t FaultCheck_70(void)
{
  return  pMChair->StateLegFlexSpike.Bit.ShortPositionSensorFault;
}

uint8_t FaultCheck_71(void)
{
  return  pMChair->StateLegFlexSpike.Bit.ExtendPositionSensorFault;
}

uint8_t FaultCheck_72(void)
{
  return pMChair->StateHeat.Bit.LumbarBackThyristorShortFault;
}

uint8_t FaultCheck_73(void)
{
  return pMChair->StateHeat.Bit.LumbarBackThermistorShortFault;
}

uint8_t FaultCheck_74(void)
{
  return pMChair->StateHeat.Bit.LumbarBackThermistorOpenFault;
}

uint8_t FaultCheck_75(void)
{
  return  NORMAL;
}

uint8_t FaultCheck_76(void)
{
  return  NORMAL;
}

uint8_t FaultCheck_77(void)
{
  return  NORMAL;
}

uint8_t FaultCheck_78(void)
{
  return  NORMAL;
}

uint8_t FaultCheck_79(void)
{
  return  NORMAL;
}

uint8_t FaultCheck_80(void)
{
  return  NORMAL;
}


/*===========================================================================================================*/

/*************************************************************************************************************
*                      ���ϱ�
* �Թ��Ϻ� ����ͳһ�ķ������������鿴�޸ġ�
**************************************************************************************************************/
static const FaultItem_t FaultTab[] = 
{
  /*���Ӳ�����bit0 -- ���� �� ִ�йػ�����  
              bit1 -- ���� �� ��λ���������������Ĺ��ϱ�ʶ*/


  /*���Ϻ�    ���ϱ���ʱ��           ���Ӳ���         ���ϼ��*/

  /*���Ϻ�1~31����ǰ�Ѿ��е�-----------------------------------------------*/
//  {1,       FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_01},    /*�ֿ�����⵽������������45S*/
  {2,       FAULT_REPORT_TL_ALWAYS,  B(00000001),    FaultCheck_02},    /*�ֿ��������İ峬��4Sδ�ɹ�ͨѶ*/
  {3,       FAULT_REPORT_TL_ALWAYS,  B(00000001),    FaultCheck_03},    /*��о���ư������İ峬��4Sδ�ɹ�ͨѶ*/
//  {4,       FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_04},    /*�г̼����źŴ���*/
  {5,       FAULT_REPORT_TL_ALWAYS,  B(00000001),    FaultCheck_05},    /*��尴����⵽������������45S*/
  {6,       FAULT_REPORT_TL_ALWAYS,  B(00000001),    FaultCheck_06},    /*С�Ȱ������İ峬��4Sδ�ɹ�ͨѶ*/
//  {7,       FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_07},    /*�������Ͽ��λ�ü��ͬʱ��Ч*/
//  {8,       FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_08},    /*5S��δ��⵽��λ�ź�*/
//  {9,       FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_09},    /*5S��δ��⵽��λ�ź�*/
//  {10,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_10},    /*5S��δ��⵽խλ�ź�*/
//  {11,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_11},    /*10S��δ��⵽�������ź�*/
//  {12,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_12},    /*�������رպ󻹼�⵽����ź�*/
//  {13,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_13},    /*������λ������ͬʱ��Ч*/
//  {14,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_14},    /*40S��δ��⵽����λ�������ź�*/
//  {15,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_15},    /*��о��������û�*/
//  {16,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_16},    /*����λ��������⵽�źź�2S���ּ�⵽����λ�������ź�*/
//  {17,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_17},    /*40S��δ��⵽����λ�������ź�*/
//  {18,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_18},    /*����λ��������⵽�źź�2S���ּ�⵽����λ�������ź�*/
//  {19,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_19},    /*�Ȳ��Ƹ˿���2.5Sδ��⵽�����ź�(��40Sδ��⵽�Ƹ˵�λ�ź�)*/
//  {20,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_20},    /**/
//  {21,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_21},    /**/
//  {22,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_22},    /**/
//  {23,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_23},    /**/
//  {24,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_24},    /**/
//  {25,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_25},    /*�����Ƹ˿���2.5Sδ��⵽�����ź�(��40Sδ��⵽�Ƹ˵�λ�ź�)*/
//  {26,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_26},    /*�������Ƹ˿���2.5Sδ��⵽�����ź�*/
//  {27,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_27},    /*����ǰ����λ������ͬʱ��Ч(3D��о)*/
//  {28,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_28},    /*��������10S��δ��⵽������λ�������ź�(3D��о)*/
//  {29,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_29},    /*��о���������ź��쳣(3D��о)*/
//  {30,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_30},    /*������λ��������⵽�źź�2S���ּ�⵽��һ��������λ�������ź�(3D��о)*/
//  {31,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_31},    /*С��������ת��С�����������쳣*/
 
  /*���Ϻ�32��ʼ�ģ���Ҫ��������31/34��о����չ��----------------------------------------*/
  {32,      FAULT_REPORT_TL_05S,     B(00000001),    FaultCheck_32},    /*��尴�������İ� ����4Sδ�ɹ�ͨѶ*/
//  {33,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_33},    /*��Ħ�� ���������쳣*/
//  {34,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_34},    /*Ԥ��  ��ʹ���ͨ���쳣*/
//  {35,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_35},    /*Ԥ��  ��Ħ���ȼ��������쳣*/
//  {36,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_36},    /*Ԥ��  ��Ħ���ȼ���޸����쳣*/
//  {37,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_37},    /*Ԥ��*/
//  {38,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_38},    /*Ԥ��*/
//  {39,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_39},    /*Ԥ��*/
  
  {40,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_40},    /*��о����(����)���  λ�ô������쳣*/
  {41,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_41},    /*��о����(����)���  λ�ñ����쳣*/
//  {42,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_42},    /*��о����(����)���  ת��(����)�������쳣*/
//  {43,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_43},    /*��о����(����)���  �����������쳣*/
  {44,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_44},    /*��о�������  λ�ô������쳣*/
//  {45,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_45},    /*��о�������  λ�ñ����쳣*/
  {46,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_46},    /*��о�������  ת��(����)�������쳣*/
//  {47,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_47},    /*��о�������  �����������쳣*/
  {48,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_48},    /*��о�������  λ�ô������쳣*/
  {49,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_49},    /*��о�������  λ�ñ����쳣*/
  {50,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_50},    /*��о�������  ת��(����)�������쳣*/
//  {51,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_51},    /*��о�������  �����������쳣*/
//  {52,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_52},    /*��о�û����  ת�ٴ������쳣*/
//  {53,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_53},    /*��о�û����  �����������쳣*/
//  {54,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_54},    /*Ԥ��  ��о���*/
//  {55,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_55},    /*Ԥ��  ��о���*/
  
//  {56,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_56},    /*�����Ƹ�  λ�ô������쳣*/
//  {57,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_57},    /*�����Ƹ�  λ�ñ����쳣*/
//  {58,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_58},    /*�����Ƹ�  �����������쳣*/
  {59,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_59},      /*�����Ƹ�  �����������쳣*/
//  {60,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_60},    /*С���Ƹ�  λ�ô������쳣*/
//  {61,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_61},    /*С���Ƹ�  λ�ñ����쳣*/
//  {62,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_62},    /*С���Ƹ�  �����������쳣*/
  {63,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_63},      /*С���Ƹ�  �����������쳣*/
//  {64,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_64},    /*�������Ƹ�  λ�ô������쳣*/
//  {65,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_65},    /*�������Ƹ�  λ�ñ����쳣*/
//  {66,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_66},    /*�������Ƹ�  �����������쳣*/
//  {67,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_67},    /*�������Ƹ�  �����������쳣*/
  {68,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_68},    /*С������  λ��(����)�������쳣*/
  {69,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_69},    /*С������  λ�ñ����쳣*/
  {70,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_70},    /*С������  �����λ����������*/
  {71,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_71},    /*С������  ���λ���������� */

  {72,      FAULT_REPORT_TL_05S,     B(00000000),    FaultCheck_72},    /*��������  �ɿع��·*/
  {73,      FAULT_REPORT_TL_05S,     B(00000000),    FaultCheck_73},    /*��������  ���������·*/
  {74,      FAULT_REPORT_TL_05S,     B(00000000),    FaultCheck_74},    /*��������  �������迪·*/
//  {75,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_75},    /*Ԥ��  �����������*/
//  {76,      FAULT_REPORT_TL_05S,     B(00000000),    FaultCheck_76},    /*�Ų�����  ����ܶ�·*/
//  {77,      FAULT_REPORT_TL_05S,     B(00000000),    FaultCheck_77},    /*�Ų�����  ���������·*/
//  {78,      FAULT_REPORT_TL_05S,     B(00000000),    FaultCheck_78},    /*�Ų�����  �������迪·*/
//  {79,      FAULT_REPORT_TL_05S,     B(00000000),    FaultCheck_79},    /*�Ų�����  ��֪���쳣*/
//  {80,      FAULT_REPORT_TL_05S,     B(00000000),    FaultCheck_80}     /*��о��  ת��(����)�������쳣*/
};

#define  FAULT_TAB_NUM    TAB_NUM(FaultTab)


/*
************************************************************************************************************************
* �������� : RealTimeInspect_FaultCheck                                                                                                         
* �������� : ʵʱ���֮���ϼ��                                                                                        
* ������� : ExePeriod -- ������ִ������                                                                                  
* ���ز��� : ��                                                                   
* ����˵�� : �������ƣ�(1) ����ģʽ�£������κι��϶�һֱ�澯
*                      (2) ����ģʽ��(�������û�����ģʽ),������ֹ��ϡ�
*                          һ����һ���ȱ�һֱ�澯��
*                          ��һ���ǳ��ֺ�ֻ�澯5s��Ȼ��ÿ���û�����Ҳ�澯5s��                                                                                                         
************************************************************************************************************************
*/
void RealTimeInspect_FaultCheck(Ticker_t ExePeriod)
{
  static uint8_t  SysModeHis = SYS_MODE_NONE;
  static uint8_t  FaultCheckIndex = 0;
  static uint8_t  DisplayIndex = 0;
  uint8_t  ByteOffSet, BitOffSet;


  /*���Ϻ�������ʾʱ�䴦��------------------------------------------------------*/
  if(pMChair->Fault.ReportTLMs > 0) /*�ϱ�ʱ�仹��ʣ��*/
  {
    if(DisplayIndex >= FAULT_TAB_NUM)
    {
      DisplayIndex = 0; 
    }  
    ByteOffSet = (FaultTab[DisplayIndex].FaultID-1) >> 3;                             /*�����ֽ�ƫ��*/
    BitOffSet  = (FaultTab[DisplayIndex].FaultID-1) & 0x07;                           /*����λƫ��*/
    if(pMChair->Fault.ReportFlag.All[ByteOffSet] & (1<<BitOffSet)) 
    {
      pMChair->Fault.DisplayFaultID  = FaultTab[DisplayIndex].FaultID;                /*Ҫ��ʾ�Ĺ���ID*/
      pMChair->Fault.DisplayTLMsPerFault += ExePeriod;
      if(pMChair->Fault.DisplayTLMsPerFault > 5000)                                   /*��ʾʱ������*/
      {
        pMChair->Fault.DisplayTLMsPerFault = 0;                                       /*���������ʾ��ʱ�䳤��*/                               
        pMChair->Fault.DisplayFaultID = 0;                                            /*���Ҫ��ʾ�Ĺ���ID*/
        DisplayIndex++;
      }
    }
    else
    {
      pMChair->Fault.DisplayTLMsPerFault = 0;                                         /*���������ʾ��ʱ�䳤��*/                               
      pMChair->Fault.DisplayFaultID = 0;                                              /*���Ҫ��ʾ�Ĺ���ID*/
      DisplayIndex++;
    }  
  }
  else
  {
    pMChair->Fault.DisplayTLMsPerFault = 0;                                         /*���������ʾ��ʱ�䳤��*/                               
    pMChair->Fault.DisplayFaultID = 0;                                              /*���Ҫ��ʾ�Ĺ���ID*/
    DisplayIndex = 0; 
  }

  /*�澯ʱ�䳤�ȼ���----------------------------------------------------------------*/
  if(pMChair->Fault.ReportTLMs > ExePeriod)
  {
    pMChair->Fault.ReportTLMs -= ExePeriod;
  }
  else 
  {
    pMChair->Fault.ReportTLMs = 0;
  }

  /*Ҫ�ϱ��Ĺ��ϸ���-----------------------------------------------------------*/
  if(FaultTab[FaultCheckIndex].pFaultCheck != NULL)
  {
    ByteOffSet = (FaultTab[FaultCheckIndex].FaultID-1) >> 3;                        /*�����ֽ�ƫ��*/
    BitOffSet  = (FaultTab[FaultCheckIndex].FaultID-1) & 0x07;                      /*����λƫ��*/

    if(FaultTab[FaultCheckIndex].pFaultCheck() != NORMAL)
    {
     /*���Ӳ�����bit0 -- ���� �� ִ�йػ�����  
                 bit1 -- ���� �� ��λ���������������Ĺ��ϱ�ʶ*/
      if(NORMAL == (pMChair->Fault.ReportFlag.All[ByteOffSet] & (1<<BitOffSet)))    /*�ռ�⵽����*/
      {
        if(FaultTab[FaultCheckIndex].AdditonOp & B(00000001))
        {
          SysMode_Standby_Enter(SYS_MODE_USERRUN, TRUE);                            /*�ػ�����λ�Ƹ˽Ƕ�*/
        }
      }

      if(FaultTab[FaultCheckIndex].AdditonOp & B(00000010))
      {
        pMChair->CSFlag.Bit.OccurNoStartUpFault = TRUE;                             /*���������������Ĺ���*/
      }

      /*���ϱ���ʱ�䳤�ȸ�ֵ*/
      if(FAULT_REPORT_TL_ALWAYS == FaultTab[FaultCheckIndex].FaultReportTL)
      {
        pMChair->Fault.ReportTLMs = 5000;                                           /*һֱ���ģ�ÿ�ζ���ֵ*/
      }
      else
      {
        if(NORMAL == (pMChair->Fault.ReportFlag.All[ByteOffSet] & (1<<BitOffSet)))  /*�ռ�⵽����*/
        {
          pMChair->Fault.ReportTLMs = 5000;                                         /*����һֱ���ģ��ռ�⵽����ʱ��ֵһ��*/
        }
      }

      pMChair->Fault.ReportFlag.All[ByteOffSet] |= (1<<BitOffSet);                  /*�й���*/
    }
    else
    {
      pMChair->Fault.ReportFlag.All[ByteOffSet] &= ~(1<<BitOffSet);                 /*�޹���*/
    }
  }

  if((++FaultCheckIndex) >= FAULT_TAB_NUM)
  {
    FaultCheckIndex = 0; /*�ú���ÿ�ν���ֻ���һ����Ŀ��Ȼ���������һ����Ŀ�����ѭ��*/
  }

  /*��ͬϵͳģʽ�£��Ա���ʱ�䳤�Ƚ��е���------------------------*/
  if(SYS_MODE_STANDBY == pMChair->SysModeCur)
  {
                                           /*�ػ��£������κδ���*/
  }
  else if(SYS_MODE_USERRUN == pMChair->SysModeCur)
  {
    if(SysModeHis != SYS_MODE_USERRUN) 
    {
      pMChair->Fault.ReportTLMs = 5000;    /*ÿ���û���������ֵһ��*/
    }
  }
  else
  {
    pMChair->Fault.ReportTLMs = 5000;      /*����ģʽ��һֱ����ÿ�ζ���ֵ*/
  }
  SysModeHis = pMChair->SysModeCur;
}

/*
========================================================================================================================
*     ʵʱ��⹦�ܺ�����                           ʵʱ��⹦�ܺ�����                           ʵʱ��⹦�ܺ�����
========================================================================================================================
*/
#define  REAL_TIME_INSPECT_TICK_COUNT_BUF_NUM   1
static Ticker_t RealTimeInspect_TickCount[REAL_TIME_INSPECT_TICK_COUNT_BUF_NUM];
static const ESF_TmrExeFunc_t  RealTimeInspect_TmrExeFuncTab[] = 
{
  /*       ִ�к���              ִ������(ms)     ʱ���������*/
  {RealTimeInspect_FaultCheck,     8,          &RealTimeInspect_TickCount[0]} 
};

#define  REAL_TIME_INSPECT_TMR_EXE_FUNC_TAB_NUM     TAB_NUM(RealTimeInspect_TmrExeFuncTab)

/*
************************************************************************************************************************
* �������� : RealTimeInspect_Handle                                                                                                         
* �������� : ʵʱ��� ����                                                                                        
* ������� : ��                                                                                  
* ���ز��� : ��                                                                   
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void RealTimeInspect_Handle(void)
{
  /*���ȹ��ܺ�����------------------------------------------------*/
  ESF_TmrExeFuncScheduling(RealTimeInspect_TmrExeFuncTab, REAL_TIME_INSPECT_TMR_EXE_FUNC_TAB_NUM);
}

/*
************************************************************************************************************************
* �������� : RealTimeInspect_Init                                                                                                         
* �������� : ʵʱ��� ֮ ��ʼ��                                                                                       
* ������� : ��                                                                                  
* ���ز��� : ��                                                                   
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void RealTimeInspect_Init(void)
{
  /*��� RealTimeInspect_TmrExeFuncTab ���ܺ����������Ƿ���ȷ------------------------*/
  ESF_TmrExeFuncTabCheck(RealTimeInspect_TmrExeFuncTab, REAL_TIME_INSPECT_TMR_EXE_FUNC_TAB_NUM, REAL_TIME_INSPECT_TICK_COUNT_BUF_NUM);
}
