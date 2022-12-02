/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：FuncLogic.h 
**
**    功能描述: 按摩功能逻辑管理
**
**    公    司：蒙发利电子
**
**    项目名称：
**
**    平台信息：
**
**    作    者：Hzy
**
**    其他说明:
**
**    修改记录:  --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/
#ifndef  _FUNCLOGIC_H
#define  _FUNCLOGIC_H

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp.h"
#include "FuncTabHandle.h"

/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
#define  FUNC_TYPE_NONE                                0       /*功能类型 无*/
#define  FUNC_TYPE_MANNUAL                             1       /*功能类型 手动*/
#define  FUNC_TYPE_AUTO                                2       /*功能类型 自动*/
#define  FUNC_TYPE_MANNUALAUTO                         3       /*功能类型 手动自动*/

#define  FUNC_NONE                                     0x00    /*无功能*/

/*【滚轮】自动手动----------------------------------------------------------------*/
#define  FMA_ROLLER_NONE                               FUNC_NONE  

/*【脚滚】*/
#define  FMA_FEET_ROLLER_Mannual                       0x01    /*手动*/  
#define  FMA_FEET_ROLLER_ByActionTab                   0x02    /*由表格内的值来控制*/  
/*0x3~0x07  时间段控制， 注：由于每个部位的功能占用3位，即可用值为0~7，所以宏定义最大可用数值不超过7 */
#define  FMA_FEET_ROLLER_ByTime_OnAlways               0x03    /*常开*/
#define  FMA_FEET_ROLLER_ByTime_On60s_Off60s           0x04    /*开60s， 关60s */
#define  FMA_FEET_ROLLER_ByTime_On90s_Off90s           0x05    /*开90s， 关90s */
#define  FMA_FEET_ROLLER_ByTime_On120s_Off120s         0x06    /*开120s，关120s */
#define  FMA_FEET_ROLLER_ByTime_On150s_Off120s         0x07    /*开150s，关150s */
  
/*【腿滚】*/
#define  FMA_CALVES_ROLLER_Mannual                     0x01    /*手动*/  
#define  FMA_CALVES_ROLLER_ByActionTab                 0x02    /*由表格内的值来控制*/  
/*0x3~0x07  时间段控制， 注：由于每个部位的功能占用3位，即可用值为0~7，所以宏定义最大可用数值不超过7 */
#define  FMA_CALVES_ROLLER_ByTime_OnAlways             0x03    /*常开*/
#define  FMA_CALVES_ROLLER_ByTime_On60s_Off60s         0x04    /*开60s， 关60s */
#define  FMA_CALVES_ROLLER_ByTime_On90s_Off90s         0x05    /*开90s， 关90s */
#define  FMA_CALVES_ROLLER_ByTime_On120s_Off120s       0x06    /*开120s，关120s */
#define  FMA_CALVES_ROLLER_ByTime_On150s_Off120s       0x07    /*开150s，关120s */


/*【加热】自动手动----------------------------------------------------------------*/
#define  FMA_HEAT_NONE                                 FUNC_NONE  

/*【脚热】*/
#define  FMA_FEET_HEAT_Mannual                         0x01    /*手动*/  
#define  FMA_FEET_HEAT_ByActionTab                     0x02    /*由表格内的值来控制*/   
/*0x3~0x07  时间段控制， 注：由于每个部位的功能占用3位，即可用值为0~7，所以宏定义最大可用数值不超过7 */
#define  FMA_FEET_HEAT_ByTime_OnAlways                 0x03    /*常开*/
#define  FMA_FEET_HEAT_ByTime_On180s_Off60s            0x04    /*开180s，关60s */
#define  FMA_FEET_HEAT_ByTime_On120s_Off180s           0x05    /*开120s，关180s */  
#define  FMA_FEET_HEAT_ByTime_On300s_Off60s            0x06    /*开300s，关60s */  

/*【腿热】*/
#define  FMA_CALVES_HEAT_Mannual                       0x01    /*手动*/  
#define  FMA_CALVES_HEAT_ByActionTab                   0x02    /*由表格内的值来控制*/   
/*0x3~0x07  时间段控制， 注：由于每个部位的功能占用3位，即可用值为0~7，所以宏定义最大可用数值不超过7 */
#define  FMA_CALVES_HEAT_ByTime_OnAlways               0x03    /*常开*/
#define  FMA_CALVES_HEAT_ByTime_On180s_Off60s          0x04    /*开180s，关60s */
#define  FMA_CALVES_HEAT_ByTime_On120s_Off180s         0x05    /*开120s，关180s */  
#define  FMA_CALVES_HEAT_ByTime_On300s_Off60s          0x06    /*开300s，关60s */  

/*【座热】*/
#define  FMA_SEAT_HEAT_Mannual                         0x01    /*手动*/  
#define  FMA_SEAT_HEAT_ByActionTab                     0x02    /*由表格内的值来控制*/   
/*0x3~0x07  时间段控制， 注：由于每个部位的功能占用3位，即可用值为0~7，所以宏定义最大可用数值不超过7 */
#define  FMA_SEAT_HEAT_ByTime_OnAlways                 0x03    /*常开*/
#define  FMA_SEAT_HEAT_ByTime_On180s_Off60s            0x04    /*开180s，关60s */
#define  FMA_SEAT_HEAT_ByTime_On120s_Off180s           0x05    /*开120s，关180s */  
#define  FMA_SEAT_HEAT_ByTime_On300s_Off60s            0x06    /*开300s，关60s */  

/*【腰背热】*/
#define  FMA_LUMBARBACK_HEAT_Mannual                   0x01    /*手动*/
#define  FMA_LUMBARBACK_HEAT_ByActionTab               0x02    /*由表格内的值来控制*/  
/*0x3~0x07  时间段控制， 注：由于每个部位的功能占用3位，即可用值为0~7，所以宏定义最大可用数值不超过7 */
#define  FMA_LUMBARBACK_HEAT_ByTime_OnAlways           0x03    /*常开*/
#define  FMA_LUMBARBACK_HEAT_ByTime_On180s_Off60s      0x04    /*开180s，关60s */
#define  FMA_LUMBARBACK_HEAT_ByTime_On120s_Off180s     0x05    /*开120s，关180s */  
#define  FMA_LUMBARBACK_HEAT_ByTime_On300s_Off60s      0x06    /*开300s，关60s */ 


/*【振动】自动手动----------------------------------------------------------------*/
#define  FMA_VIB_NONE                                  FUNC_NONE  

/*【脚振】*/
#define  FMA_FEET_VIB_Mannual                          0x01    /*手动*/  
#define  FMA_FEET_VIB_ByActionTab                      0x02    /*由表格内的值来控制*/   
/*0x3~0x07  时间段控制， 注：由于每个部位的功能占用3位，即可用值为0~7，所以宏定义最大可用数值不超过7 */
#define  FMA_FEET_VIB_ByTime_OnAlways                  0x03    /*常开*/
#define  FMA_FEET_VIB_ByTime_On180s_Off60s             0x04    /*开180s，关60s */
#define  FMA_FEET_VIB_ByTime_On60s_Off50s              0x05    /*开60s，关50s */  
#define  FMA_FEET_VIB_ByTime_On300s_Off60s             0x06    /*开300s，关60s */  

/*【腿振】*/
#define  FMA_CALVES_VIB_Mannual                        0x01    /*手动*/  
#define  FMA_CALVES_VIB_ByActionTab                    0x02    /*由表格内的值来控制*/   
/*0x3~0x07  时间段控制， 注：由于每个部位的功能占用3位，即可用值为0~7，所以宏定义最大可用数值不超过7 */
#define  FMA_CALVES_VIB_ByTime_OnAlways                0x03    /*常开*/
#define  FMA_CALVES_VIB_ByTime_On180s_Off60s           0x04    /*开180s，关60s */
#define  FMA_CALVES_VIB_ByTime_On100s_Off50s           0x05    /*开100s，关50s */  
#define  FMA_CALVES_VIB_ByTime_On300s_Off60s           0x06    /*开300s，关60s */  

/*【座振】*/
#define  FMA_SEAT_VIB_Mannual                          0x01    /*手动*/  
#define  FMA_SEAT_VIB_ByActionTab                      0x02    /*由表格内的值来控制*/   
/*0x3~0x07  时间段控制， 注：由于每个部位的功能占用3位，即可用值为0~7，所以宏定义最大可用数值不超过7 */
#define  FMA_SEAT_VIB_ByTime_OnAlways                  0x03    /*常开*/
#define  FMA_SEAT_VIB_ByTime_On180s_Off60s             0x04    /*开180s，关60s */
#define  FMA_SEAT_VIB_ByTime_On100s_Off50s             0x05    /*开100s，关50s */  
#define  FMA_SEAT_VIB_ByTime_On300s_Off60s             0x06    /*开300s，关60s */  

/*【腰背振】*/
#define  FMA_LUMBARBACK_VIB_Mannual                    0x01    /*手动*/
#define  FMA_LUMBARBACK_VIB_ByActionTab                0x02    /*由表格内的值来控制*/  
/*0x3~0x07  时间段控制， 注：由于每个部位的功能占用3位，即可用值为0~7，所以宏定义最大可用数值不超过7 */
#define  FMA_LUMBARBACK_VIB_ByTime_OnAlways            0x03    /*常开*/
#define  FMA_LUMBARBACK_VIB_ByTime_On180s_Off60s       0x04    /*开180s，关60s */
#define  FMA_LUMBARBACK_VIB_ByTime_On100s_Off50s       0x05    /*开100s，关50s */  
#define  FMA_LUMBARBACK_VIB_ByTime_On300s_Off60s       0x06    /*开300s，关60s */ 


/*【灯光】自动手动----------------------------------------------------------------*/
#define  FMA_LED_NONE                                  FUNC_NONE  

#define  FMA_LED_Mannual                               0x01    /*手动*/ 
#define  FMA_LED_ByActionTab                           0x02    /*由表格内的值来控制*/ 
/*0x3~0x07  时间段控制， 注：由于每个部位的功能占用3位，即可用值为0~7，所以宏定义最大可用数值不超过7 */
#define  FMA_LED_ByTime_OnAlways                       0x03    /*常开*/
#define  FMA_LED_ByTime_On180s_Off60s                  0x04    /*开180s，关60s */
#define  FMA_LED_ByTime_On100s_Off50s                  0x05    /*开100s，关50s */  
#define  FMA_LED_ByTime_On300s_Off60s                  0x06    /*开300s，关60s */  

#define  FMA_LOGO_LED_Mannual                          0x01    /*手动*/ 

#define  FMA_PROJECTION_LED_Mannual                    0x01    /*手动*/ 

/*【机芯】手动 -------------------------------------------------------------------*/


/*【推杆】手动 -------------------------------------------------------------------*/


/*【充气】手动 -------------------------------------------------------------------*/
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


/*动作表格体验--------------------------------------------------------------------*/
#define  FA_TAB_TRY                                    0xFF          /*表格体验专用ID*/


/*【机芯】自动--------------------------------------------------------------------*/
#define  FA_CORE_NONE                                  FUNC_NONE  
#define  FA_CORE_TRY                                   FA_TAB_TRY    /*表格体验专用ID*/


/*【推杆】自动 -------------------------------------------------------------------*/
#define  FA_SPIKE_NONE                                 FUNC_NONE
#define  FA_SPIKE_TRY                                  FA_TAB_TRY    /*表格体验专用ID*/

#define  FA_SPIKE_ZeroGravity1                         0x01
#define  FA_SPIKE_ZeroGravity2                         0x02
#define  FA_SPIKE_Home                                 0x03

/*【充气】自动 -------------------------------------------------------------------*/
#define  FA_GAS_NONE                                   FUNC_NONE
#define  FA_GAS_TRY                                    FA_TAB_TRY    /*表格体验专用ID*/

#define  FA_GAS_FullGas                                0x01
#define  FA_GAS_QuickGas                               0x02


/*【机芯+充气】自动 --------------------------------------------------------------*/
#define  FA_COREGAS_NONE                               FUNC_NONE  
#define  FA_COREGAS_TRY                                FA_TAB_TRY    /*表格体验专用ID*/

/*0x01~0x2F   【机芯】 表格+ 【充气】表格*/
#define  FA_COREGAS_Quick                           0x01          /*快速按摩*/
#define  FA_COREGAS_Relax                           0x02          /*舒缓放松*/
#define  FA_COREGAS_MoveSleep                       0x03          /*摇动舒眠*/
#define  FA_COREGAS_Stretch                         0x04          /*伸展拉伸*/
#define  FA_COREGAS_Scraping                        0x05          /*刮痧推拿*/
#define  FA_COREGAS_Shiatsu                         0x06          /*深度指压*/
#define  FA_COREGAS_Lady                            0x07          /*女士专属*/
#define  FA_COREGAS_Man                             0x08          /*男士专属*/
#define  FA_COREGAS_ShoulderRelax                   0x09          /*颈肩放松*/
#define  FA_COREGAS_ShoulderRecovery                0x0A          /*颈肩疲劳恢复*/
#define  FA_COREGAS_ShoulderTuina                   0x0B          /*颈肩推拿*/
#define  FA_COREGAS_ShoulderShiatsu                 0x0C          /*颈肩深度指压*/
#define  FA_COREGAS_LumbarButtockRelax              0x0D          /*腰臀放松*/
#define  FA_COREGAS_LumbarButtockRecovery           0x0E          /*腰臀疲劳恢复*/
#define  FA_COREGAS_LumbarButtockPress              0x0F          /*腰臀经络按压*/
#define  FA_COREGAS_LumbarKidneyCare                0x10          /*腰肾保健*/

/*0x30~0x05F   【机芯+充气 】表格*/


/*【机芯+推杆】自动 --------------------------------------------------------------*/
#define  FA_CORESPIKE_NONE                             FUNC_NONE  
#define  FA_CORESPIKE_TRY                              FA_TAB_TRY    /*表格体验专用ID*/


/*【充气+推杆】自动 --------------------------------------------------------------*/
#define  FA_GASSPIKE_NONE                              FUNC_NONE  
#define  FA_GASSPIKE_TRY                               FA_TAB_TRY    /*表格体验专用ID*/


/*【机芯+充气+推杆】自动 ---------------------------------------------------------*/
#define  FA_COREGASSPIKE_NONE                          FUNC_NONE  
#define  FA_COREGASSPIKE_TRY                           FA_TAB_TRY    /*表格体验专用ID*/

#define  FA_COREGASSPIKE_Thai                          0x01          /*泰式*/


/*【宫格组合】自动----------------------------------------------------------------*/
#define  FA_GRIDCOMBO_NONE                             FUNC_NONE  
#define  FA_GRIDCOMBO_ON                               0x01          /*【宫格组合】程序开启*/


/*【所有 组合】自动----------------------------------------------------------------*/
#define  FA_ALLCOMBO_NONE                              FUNC_NONE  
#define  FA_ALLCOMBO_Demo                              0x01         



/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :                                                                                 
************************************************************************************************************************
*/



/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
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
