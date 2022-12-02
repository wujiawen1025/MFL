/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣ�FuncTab.h 
**
**    ��������: ��Ħ���� ���
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
#ifndef  _FUNCTAB_H
#define  _FUNCTAB_H

/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "bsp.h"
#include "FuncTabHandle.h"


/*
========================================================================================================================
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/


/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� :                                                                                   
************************************************************************************************************************
*/



/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/

/*����������������������������������������������������������������������������������������������������������������������
����о�����                   ����о�����                   ����о�����                   ����о�����
������������������������������������������������������������������������������������������������������������������������*/


/*����������������������������������������������������������������������������������������������������������������������
�����������                   �����������                   �����������                   �����������
������������������������������������������������������������������������������������������������������������������������*/
extern  const GasAutoTabItem_t     GasTab_FullGas[];                /*ȫ�����*/
extern  const GasAutoTabItem_t     GasTab_RelaxGas[];               /*���ɳ���*/
extern  const GasAutoTabItem_t     GasTab_QuickGas[];               /*���ٳ���*/

extern  const GasMannualTabItem_t  GasTab_Shoulder[];               /*�粿�ֶ�����*/
extern  const GasMannualTabItem_t  GasTab_Arms[];                   /*�ֲ��ֶ�����*/
extern  const GasMannualTabItem_t  GasTab_LumbarSeat[];             /*�����ֶ�����*/
extern  const GasMannualTabItem_t  GasTab_Calves[];                 /*�Ȳ��ֶ�����*/

extern  const GasAutoTabItem_t     FeetGasRollerTab[];              /*�Ź�������ĽŲ�����*/
extern  const GasAutoTabItem_t     CalvesGasRollerTab[];            /*�ȹ�������ĽŲ�����*/


/*����������������������������������������������������������������������������������������������������������������������
���Ƹˡ����                   ���Ƹˡ����                   ���Ƹˡ����                   ���Ƹˡ����
������������������������������������������������������������������������������������������������������������������������*/
extern  const SpikeAutoTabItem_t  SpikeAutoTab_UserRun[];
extern  const SpikeAutoTabItem_t  SpikeAutoTab_ExeMassage[];
extern  const SpikeAutoTabItem_t  SpikeAutoTab_ZeroGravity1[];
extern  const SpikeAutoTabItem_t  SpikeAutoTab_ZeroGravity2[];
extern  const SpikeAutoTabItem_t  SpikeAutoTab_Home[];

extern  const SpikeAutoTabItem_t  SpikeAutoTab_Rocking[];          /*����  ҡҡ��  1m10s*/

/*����������������������������������������������������������������������������������������������������������������������
����о+���������              ����о+���������              ����о+���������              ����о+���������
������������������������������������������������������������������������������������������������������������������������*/


/*����������������������������������������������������������������������������������������������������������������������
����о+�Ƹˡ����              ����о+�Ƹˡ����              ����о+�Ƹˡ����              ����о+�Ƹˡ����
������������������������������������������������������������������������������������������������������������������������*/
 

/*����������������������������������������������������������������������������������������������������������������������
������+�Ƹˡ����              ������+�Ƹˡ����              ������+�Ƹˡ����              ������+�Ƹˡ����
������������������������������������������������������������������������������������������������������������������������*/


/*����������������������������������������������������������������������������������������������������������������������
����о+����+�Ƹˡ����         ����о+����+�Ƹˡ����         ����о+����+�Ƹˡ����         ����о+����+�Ƹˡ����
������������������������������������������������������������������������������������������������������������������������*/
extern  const CoreGasSpikeAutoTabItem_t  CoreGasSpikeAutoTab_Shoulder[];             /*����  �粿 1m10s*/
extern  const CoreGasSpikeAutoTabItem_t  CoreGasSpikeAutoTab_ShoulderTCS[];          /*����  ���� 1m15s*/
extern  const CoreGasSpikeAutoTabItem_t  CoreGasSpikeAutoTab_Lumbar[];               /*����  ���� 1m50s*/
extern  const CoreGasSpikeAutoTabItem_t  CoreGasSpikeAutoTab_BackFeet[];             /*����  �ȱ����� 1m25ss*/
extern  const CoreGasSpikeAutoTabItem_t  CoreGasSpikeAutoTab_FeetUpDown[];           /*����  �Ƚ� ����2m40s*/



/*����������������������������������������������������������������������������������������������������������������������
����о����ϡ����������       ����о����ϡ����������       ����о����ϡ����������       ����о����ϡ����������  
������������������������������������������������������������������������������������������������������������������������*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_Quick[];                  /*���ٰ�Ħ*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_Relax[];                  /*�滺����*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_MoveSleep[];              /*ҡ������*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_Stretch[];                /*��չ����*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_Scraping[];               /*��������*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_Shiatsu[];                /*���ָѹ*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_Lady[];                   /*�����滺��Ůʿר����*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_Man[];                    /*��ȷ��ɣ���ʿר����*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_ShoulderRelax[];          /*�������*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_ShoulderRecovery[];       /*����Ԫ����ƣ�ͣ��ָ�*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_ShoulderTuina[];          /*��������*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_ShoulderShiatsu[];        /*�������ָѹ*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_LumbarButtockRelax[];     /*���η���*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_LumbarButtockRecovery[];  /*����Ԫ����ƣ�ͣ��ָ�*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_LumbarButtockPress[];     /*���ξ��簴ѹ*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_LumbarKidneyCare[];       /*���α���*/


/*����������������������������������������������������������������������������������������������������������������������
��������ϡ����              ��������ϡ����              ��������ϡ����              ��������ϡ����
������������������������������������������������������������������������������������������������������������������������*/
extern  const CoreMixOtherTabItem_t  GridComboTab_NeckShoulder_1[];       
extern  const CoreMixOtherTabItem_t  GridComboTab_NeckShoulder_2[];       
extern  const CoreMixOtherTabItem_t  GridComboTab_NeckShoulder_3[];       
extern  const CoreMixOtherTabItem_t  GridComboTab_NeckShoulder_4[];       
extern  const CoreMixOtherTabItem_t  GridComboTab_Back_1[];       
extern  const CoreMixOtherTabItem_t  GridComboTab_Back_2[];       
extern  const CoreMixOtherTabItem_t  GridComboTab_Back_3[];       
extern  const CoreMixOtherTabItem_t  GridComboTab_Back_4[];       
extern  const CoreMixOtherTabItem_t  GridComboTab_Lumbar_1[];       
extern  const CoreMixOtherTabItem_t  GridComboTab_Lumbar_2[];       
extern  const CoreMixOtherTabItem_t  GridComboTab_Lumbar_3[];       
extern  const CoreMixOtherTabItem_t  GridComboTab_Lumbar_4[];       


#endif
