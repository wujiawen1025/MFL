/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣ�FuncLogic.h 
**
**    ��������: ��Ħ�����߼�����
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
#ifndef  _FUNCLOGIC_H
#define  _FUNCLOGIC_H

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
#define  FUNC_TYPE_NONE                                0       /*�������� ��*/
#define  FUNC_TYPE_MANNUAL                             1       /*�������� �ֶ�*/
#define  FUNC_TYPE_AUTO                                2       /*�������� �Զ�*/
#define  FUNC_TYPE_MANNUALAUTO                         3       /*�������� �ֶ��Զ�*/

#define  FUNC_NONE                                     0x00    /*�޹���*/

/*�����֡��Զ��ֶ�----------------------------------------------------------------*/
#define  FMA_ROLLER_NONE                               FUNC_NONE  

/*���Ź���*/
#define  FMA_FEET_ROLLER_Mannual                       0x01    /*�ֶ�*/  
#define  FMA_FEET_ROLLER_ByActionTab                   0x02    /*�ɱ���ڵ�ֵ������*/  
/*0x3~0x07  ʱ��ο��ƣ� ע������ÿ����λ�Ĺ���ռ��3λ��������ֵΪ0~7�����Ժ궨����������ֵ������7 */
#define  FMA_FEET_ROLLER_ByTime_OnAlways               0x03    /*����*/
#define  FMA_FEET_ROLLER_ByTime_On60s_Off60s           0x04    /*��60s�� ��60s */
#define  FMA_FEET_ROLLER_ByTime_On90s_Off90s           0x05    /*��90s�� ��90s */
#define  FMA_FEET_ROLLER_ByTime_On120s_Off120s         0x06    /*��120s����120s */
#define  FMA_FEET_ROLLER_ByTime_On150s_Off120s         0x07    /*��150s����150s */
  
/*���ȹ���*/
#define  FMA_CALVES_ROLLER_Mannual                     0x01    /*�ֶ�*/  
#define  FMA_CALVES_ROLLER_ByActionTab                 0x02    /*�ɱ���ڵ�ֵ������*/  
/*0x3~0x07  ʱ��ο��ƣ� ע������ÿ����λ�Ĺ���ռ��3λ��������ֵΪ0~7�����Ժ궨����������ֵ������7 */
#define  FMA_CALVES_ROLLER_ByTime_OnAlways             0x03    /*����*/
#define  FMA_CALVES_ROLLER_ByTime_On60s_Off60s         0x04    /*��60s�� ��60s */
#define  FMA_CALVES_ROLLER_ByTime_On90s_Off90s         0x05    /*��90s�� ��90s */
#define  FMA_CALVES_ROLLER_ByTime_On120s_Off120s       0x06    /*��120s����120s */
#define  FMA_CALVES_ROLLER_ByTime_On150s_Off120s       0x07    /*��150s����120s */


/*�����ȡ��Զ��ֶ�----------------------------------------------------------------*/
#define  FMA_HEAT_NONE                                 FUNC_NONE  

/*�����ȡ�*/
#define  FMA_FEET_HEAT_Mannual                         0x01    /*�ֶ�*/  
#define  FMA_FEET_HEAT_ByActionTab                     0x02    /*�ɱ���ڵ�ֵ������*/   
/*0x3~0x07  ʱ��ο��ƣ� ע������ÿ����λ�Ĺ���ռ��3λ��������ֵΪ0~7�����Ժ궨����������ֵ������7 */
#define  FMA_FEET_HEAT_ByTime_OnAlways                 0x03    /*����*/
#define  FMA_FEET_HEAT_ByTime_On180s_Off60s            0x04    /*��180s����60s */
#define  FMA_FEET_HEAT_ByTime_On120s_Off180s           0x05    /*��120s����180s */  
#define  FMA_FEET_HEAT_ByTime_On300s_Off60s            0x06    /*��300s����60s */  

/*�����ȡ�*/
#define  FMA_CALVES_HEAT_Mannual                       0x01    /*�ֶ�*/  
#define  FMA_CALVES_HEAT_ByActionTab                   0x02    /*�ɱ���ڵ�ֵ������*/   
/*0x3~0x07  ʱ��ο��ƣ� ע������ÿ����λ�Ĺ���ռ��3λ��������ֵΪ0~7�����Ժ궨����������ֵ������7 */
#define  FMA_CALVES_HEAT_ByTime_OnAlways               0x03    /*����*/
#define  FMA_CALVES_HEAT_ByTime_On180s_Off60s          0x04    /*��180s����60s */
#define  FMA_CALVES_HEAT_ByTime_On120s_Off180s         0x05    /*��120s����180s */  
#define  FMA_CALVES_HEAT_ByTime_On300s_Off60s          0x06    /*��300s����60s */  

/*�����ȡ�*/
#define  FMA_SEAT_HEAT_Mannual                         0x01    /*�ֶ�*/  
#define  FMA_SEAT_HEAT_ByActionTab                     0x02    /*�ɱ���ڵ�ֵ������*/   
/*0x3~0x07  ʱ��ο��ƣ� ע������ÿ����λ�Ĺ���ռ��3λ��������ֵΪ0~7�����Ժ궨����������ֵ������7 */
#define  FMA_SEAT_HEAT_ByTime_OnAlways                 0x03    /*����*/
#define  FMA_SEAT_HEAT_ByTime_On180s_Off60s            0x04    /*��180s����60s */
#define  FMA_SEAT_HEAT_ByTime_On120s_Off180s           0x05    /*��120s����180s */  
#define  FMA_SEAT_HEAT_ByTime_On300s_Off60s            0x06    /*��300s����60s */  

/*�������ȡ�*/
#define  FMA_LUMBARBACK_HEAT_Mannual                   0x01    /*�ֶ�*/
#define  FMA_LUMBARBACK_HEAT_ByActionTab               0x02    /*�ɱ���ڵ�ֵ������*/  
/*0x3~0x07  ʱ��ο��ƣ� ע������ÿ����λ�Ĺ���ռ��3λ��������ֵΪ0~7�����Ժ궨����������ֵ������7 */
#define  FMA_LUMBARBACK_HEAT_ByTime_OnAlways           0x03    /*����*/
#define  FMA_LUMBARBACK_HEAT_ByTime_On180s_Off60s      0x04    /*��180s����60s */
#define  FMA_LUMBARBACK_HEAT_ByTime_On120s_Off180s     0x05    /*��120s����180s */  
#define  FMA_LUMBARBACK_HEAT_ByTime_On300s_Off60s      0x06    /*��300s����60s */ 


/*���񶯡��Զ��ֶ�----------------------------------------------------------------*/
#define  FMA_VIB_NONE                                  FUNC_NONE  

/*������*/
#define  FMA_FEET_VIB_Mannual                          0x01    /*�ֶ�*/  
#define  FMA_FEET_VIB_ByActionTab                      0x02    /*�ɱ���ڵ�ֵ������*/   
/*0x3~0x07  ʱ��ο��ƣ� ע������ÿ����λ�Ĺ���ռ��3λ��������ֵΪ0~7�����Ժ궨����������ֵ������7 */
#define  FMA_FEET_VIB_ByTime_OnAlways                  0x03    /*����*/
#define  FMA_FEET_VIB_ByTime_On180s_Off60s             0x04    /*��180s����60s */
#define  FMA_FEET_VIB_ByTime_On60s_Off50s              0x05    /*��60s����50s */  
#define  FMA_FEET_VIB_ByTime_On300s_Off60s             0x06    /*��300s����60s */  

/*������*/
#define  FMA_CALVES_VIB_Mannual                        0x01    /*�ֶ�*/  
#define  FMA_CALVES_VIB_ByActionTab                    0x02    /*�ɱ���ڵ�ֵ������*/   
/*0x3~0x07  ʱ��ο��ƣ� ע������ÿ����λ�Ĺ���ռ��3λ��������ֵΪ0~7�����Ժ궨����������ֵ������7 */
#define  FMA_CALVES_VIB_ByTime_OnAlways                0x03    /*����*/
#define  FMA_CALVES_VIB_ByTime_On180s_Off60s           0x04    /*��180s����60s */
#define  FMA_CALVES_VIB_ByTime_On100s_Off50s           0x05    /*��100s����50s */  
#define  FMA_CALVES_VIB_ByTime_On300s_Off60s           0x06    /*��300s����60s */  

/*������*/
#define  FMA_SEAT_VIB_Mannual                          0x01    /*�ֶ�*/  
#define  FMA_SEAT_VIB_ByActionTab                      0x02    /*�ɱ���ڵ�ֵ������*/   
/*0x3~0x07  ʱ��ο��ƣ� ע������ÿ����λ�Ĺ���ռ��3λ��������ֵΪ0~7�����Ժ궨����������ֵ������7 */
#define  FMA_SEAT_VIB_ByTime_OnAlways                  0x03    /*����*/
#define  FMA_SEAT_VIB_ByTime_On180s_Off60s             0x04    /*��180s����60s */
#define  FMA_SEAT_VIB_ByTime_On100s_Off50s             0x05    /*��100s����50s */  
#define  FMA_SEAT_VIB_ByTime_On300s_Off60s             0x06    /*��300s����60s */  

/*��������*/
#define  FMA_LUMBARBACK_VIB_Mannual                    0x01    /*�ֶ�*/
#define  FMA_LUMBARBACK_VIB_ByActionTab                0x02    /*�ɱ���ڵ�ֵ������*/  
/*0x3~0x07  ʱ��ο��ƣ� ע������ÿ����λ�Ĺ���ռ��3λ��������ֵΪ0~7�����Ժ궨����������ֵ������7 */
#define  FMA_LUMBARBACK_VIB_ByTime_OnAlways            0x03    /*����*/
#define  FMA_LUMBARBACK_VIB_ByTime_On180s_Off60s       0x04    /*��180s����60s */
#define  FMA_LUMBARBACK_VIB_ByTime_On100s_Off50s       0x05    /*��100s����50s */  
#define  FMA_LUMBARBACK_VIB_ByTime_On300s_Off60s       0x06    /*��300s����60s */ 


/*���ƹ⡿�Զ��ֶ�----------------------------------------------------------------*/
#define  FMA_LED_NONE                                  FUNC_NONE  

#define  FMA_LED_Mannual                               0x01    /*�ֶ�*/ 
#define  FMA_LED_ByActionTab                           0x02    /*�ɱ���ڵ�ֵ������*/ 
/*0x3~0x07  ʱ��ο��ƣ� ע������ÿ����λ�Ĺ���ռ��3λ��������ֵΪ0~7�����Ժ궨����������ֵ������7 */
#define  FMA_LED_ByTime_OnAlways                       0x03    /*����*/
#define  FMA_LED_ByTime_On180s_Off60s                  0x04    /*��180s����60s */
#define  FMA_LED_ByTime_On100s_Off50s                  0x05    /*��100s����50s */  
#define  FMA_LED_ByTime_On300s_Off60s                  0x06    /*��300s����60s */  

#define  FMA_LOGO_LED_Mannual                          0x01    /*�ֶ�*/ 

#define  FMA_PROJECTION_LED_Mannual                    0x01    /*�ֶ�*/ 

/*����о���ֶ� -------------------------------------------------------------------*/


/*���Ƹˡ��ֶ� -------------------------------------------------------------------*/


/*���������ֶ� -------------------------------------------------------------------*/
#define  FM_GAS_NONE                                   FUNC_NONE

#define  FM_GAS_HEAD                                   0x01    
#define  FM_GAS_SHOULDER                               0x01    
#define  FM_GAS_ARMS                                   0x01    
#define  FM_GAS_LUMBAR                                 0x01    
#define  FM_GAS_SEAT                                   0x01    
#define  FM_GAS_LUMBARSEAT                             0x01    
#define  FM_GAS_CALVES                                 0x01
#define  FM_GAS_FEET                                   0x01
#define  FM_GAS_CALVESFEET                             0x01


/*�����������--------------------------------------------------------------------*/
#define  FA_TAB_TRY                                    0xFF          /*�������ר��ID*/


/*����о���Զ�--------------------------------------------------------------------*/
#define  FA_CORE_NONE                                  FUNC_NONE  
#define  FA_CORE_TRY                                   FA_TAB_TRY    /*�������ר��ID*/


/*���Ƹˡ��Զ� -------------------------------------------------------------------*/
#define  FA_SPIKE_NONE                                 FUNC_NONE
#define  FA_SPIKE_TRY                                  FA_TAB_TRY    /*�������ר��ID*/

#define  FA_SPIKE_ZeroGravity1                         0x01
#define  FA_SPIKE_ZeroGravity2                         0x02
#define  FA_SPIKE_Home                                 0x03

/*���������Զ� -------------------------------------------------------------------*/
#define  FA_GAS_NONE                                   FUNC_NONE
#define  FA_GAS_TRY                                    FA_TAB_TRY    /*�������ר��ID*/

#define  FA_GAS_FullGas                                0x01
#define  FA_GAS_QuickGas                               0x02


/*����о+�������Զ� --------------------------------------------------------------*/
#define  FA_COREGAS_NONE                               FUNC_NONE  
#define  FA_COREGAS_TRY                                FA_TAB_TRY    /*�������ר��ID*/

/*0x01~0x2F   ����о�� ���+ �����������*/
#define  FA_COREGAS_Quick                           0x01          /*���ٰ�Ħ*/
#define  FA_COREGAS_Relax                           0x02          /*�滺����*/
#define  FA_COREGAS_MoveSleep                       0x03          /*ҡ������*/
#define  FA_COREGAS_Stretch                         0x04          /*��չ����*/
#define  FA_COREGAS_Scraping                        0x05          /*��������*/
#define  FA_COREGAS_Shiatsu                         0x06          /*���ָѹ*/
#define  FA_COREGAS_Lady                            0x07          /*Ůʿר��*/
#define  FA_COREGAS_Man                             0x08          /*��ʿר��*/
#define  FA_COREGAS_ShoulderRelax                   0x09          /*�������*/
#define  FA_COREGAS_ShoulderRecovery                0x0A          /*����ƣ�ͻָ�*/
#define  FA_COREGAS_ShoulderTuina                   0x0B          /*��������*/
#define  FA_COREGAS_ShoulderShiatsu                 0x0C          /*�������ָѹ*/
#define  FA_COREGAS_LumbarButtockRelax              0x0D          /*���η���*/
#define  FA_COREGAS_LumbarButtockRecovery           0x0E          /*����ƣ�ͻָ�*/
#define  FA_COREGAS_LumbarButtockPress              0x0F          /*���ξ��簴ѹ*/
#define  FA_COREGAS_LumbarKidneyCare                0x10          /*��������*/

/*0x30~0x05F   ����о+���� �����*/


/*����о+�Ƹˡ��Զ� --------------------------------------------------------------*/
#define  FA_CORESPIKE_NONE                             FUNC_NONE  
#define  FA_CORESPIKE_TRY                              FA_TAB_TRY    /*�������ר��ID*/


/*������+�Ƹˡ��Զ� --------------------------------------------------------------*/
#define  FA_GASSPIKE_NONE                              FUNC_NONE  
#define  FA_GASSPIKE_TRY                               FA_TAB_TRY    /*�������ר��ID*/


/*����о+����+�Ƹˡ��Զ� ---------------------------------------------------------*/
#define  FA_COREGASSPIKE_NONE                          FUNC_NONE  
#define  FA_COREGASSPIKE_TRY                           FA_TAB_TRY    /*�������ר��ID*/

#define  FA_COREGASSPIKE_Thai                          0x01          /*̩ʽ*/


/*��������ϡ��Զ�----------------------------------------------------------------*/
#define  FA_GRIDCOMBO_NONE                             FUNC_NONE  
#define  FA_GRIDCOMBO_ON                               0x01          /*��������ϡ�������*/


/*������ ��ϡ��Զ�----------------------------------------------------------------*/
#define  FA_ALLCOMBO_NONE                              FUNC_NONE  
#define  FA_ALLCOMBO_Demo                              0x01         



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
void MChair_FuncLogic_Switch(void);
void MChair_FuncLogic_ClearAllFunc(void);
uint16_t MChair_FuncSwitch_CloseForNewFunc(FuncLogic_t *pFuncLogic, const ActionTabAttr_t ActionTabAttrTab[], uint8_t ActionTabAttrTabNum, ActionTabStep_t *pTabStep);
void MChair_FuncExe(Ticker_t ExePeriod);

/*====================================================================================================================*/
void MChair_CoreMannualVenderTest3DSwSet(uint8_t Sw);
void MChair_FuncSwitch_CoreMannual(uint8_t SwitchMode, FuncLogic_t *pFuncLogic);
void MChair_FuncExe_CoreMannual(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic);
uint8_t MChair_GetFuncCoreMannualWidthMax(void);
uint8_t MChair_GetFuncCoreMannualFlexLevelMax(void);
uint8_t MChair_GetFuncCoreMannualXYZSpeedMax(void);

/*====================================================================================================================*/
void MChair_FuncSwitch_GasMannual(uint8_t SwitchMode, FuncLogic_t *pFuncLogic);
void MChair_FuncExe_GasMannual(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic);

/*====================================================================================================================*/
void MChair_FuncSwitch_SpikeMannual(uint8_t SwitchMode, FuncLogic_t *pFuncLogic);
void MChair_FuncExe_SpikeMannual(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic);

/*====================================================================================================================*/
void MChair_FuncSwitch_CoreAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic);
void MChair_FuncExe_CoreAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic);

/*====================================================================================================================*/
void MChair_FuncSwitch_GasAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic);
void MChair_FuncExe_GasAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic);

/*====================================================================================================================*/
void MChair_FuncSwitch_SpikeAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic);
void MChair_FuncExe_SpikeAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic);

/*====================================================================================================================*/
void MChair_FuncSwitch_CoreGasAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic);
void MChair_FuncExe_CoreGasAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic);

/*====================================================================================================================*/
void MChair_SetFuncAutoSpike(uint16_t FuncAutoSpike, uint8_t NeedCloseAngle);
void MChair_FuncSwitch_CoreSpikeAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic);
void MChair_FuncExe_CoreSpikeAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic);

/*====================================================================================================================*/
void MChair_FuncSwitch_GasSpikeAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic);
void MChair_FuncExe_GasSpikeAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic);

/*====================================================================================================================*/
void MChair_FuncSwitch_CoreGasSpikeAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic);
void MChair_FuncExe_CoreGasSpikeAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic);

/*====================================================================================================================*/
uint8_t GridComboAuto_UpdateComboSelectBit(uint8_t  *pBit);
uint8_t GridComboAuto_GetNeckShoulderSelectBit(void);
uint8_t GridComboAuto_GetBackSelectBit(void);
uint8_t GridComboAuto_GetLumbarSelectBit(void);
uint8_t GridComboAuto_GetButtocksSelectBit(void);
uint8_t GridComboAuto_GetCurRunTabIndex(void);
void MChair_FuncSwitch_GridComboAuto(uint8_t SwitchMode, FuncLogic_t *pFuncLogic);
void MChair_FuncExe_GridComboAuto(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic);

/*====================================================================================================================*/
void MChair_FuncSwitch_AllCombo(void);
void MChair_FuncExe_AllCombo(Ticker_t ExePeriod);

/*====================================================================================================================*/
void MChair_RollerFuncReset_Feet(void);
void MChair_RollerFuncReset_Calves(void);
void MChair_FuncSwitch_RollerMA(uint8_t SwitchMode, FuncLogic_t *pFuncLogic);
void MChair_FuncExe_RollerMA(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic);

/*====================================================================================================================*/
void MChair_VibFuncReset_Feet(void);
void MChair_VibFuncReset_Calves(void);
void MChair_VibFuncReset_Seat(void);
void MChair_VibFuncReset_LumbarBack(void);
void MChair_FuncSwitch_VibMA(uint8_t SwitchMode, FuncLogic_t *pFuncLogic);
void MChair_FuncExe_VibMA(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic);

/*====================================================================================================================*/
void MChair_HeatFuncReset_Feet(void);
void MChair_HeatFuncReset_Calves(void);
void MChair_HeatFuncReset_Seat(void);
void MChair_HeatFuncReset_LumbarBack(void);
void MChair_FuncSwitch_HeatMA(uint8_t SwitchMode, FuncLogic_t *pFuncLogic);
void MChair_FuncExe_HeatMA(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic);

/*====================================================================================================================*/
void MChair_LedFuncReset(void);
void MChair_FuncSwitch_LedMA(uint8_t SwitchMode, FuncLogic_t *pFuncLogic);
void MChair_FuncExe_LedMA(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic);

/*====================================================================================================================*/

#endif
