/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：FuncTab.h 
**
**    功能描述: 按摩功能 表格
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
#ifndef  _FUNCTAB_H
#define  _FUNCTAB_H

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

/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓
【机芯】表格                   【机芯】表格                   【机芯】表格                   【机芯】表格
〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/


/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓
【充气】表格                   【充气】表格                   【充气】表格                   【充气】表格
〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
extern  const GasAutoTabItem_t     GasTab_FullGas[];                /*全身充气*/
extern  const GasAutoTabItem_t     GasTab_RelaxGas[];               /*放松充气*/
extern  const GasAutoTabItem_t     GasTab_QuickGas[];               /*快速充气*/

extern  const GasMannualTabItem_t  GasTab_Shoulder[];               /*肩部手动充气*/
extern  const GasMannualTabItem_t  GasTab_Arms[];                   /*手部手动充气*/
extern  const GasMannualTabItem_t  GasTab_LumbarSeat[];             /*腰座手动充气*/
extern  const GasMannualTabItem_t  GasTab_Calves[];                 /*腿部手动充气*/

extern  const GasAutoTabItem_t     FeetGasRollerTab[];              /*脚滚所伴随的脚部充气*/
extern  const GasAutoTabItem_t     CalvesGasRollerTab[];            /*腿滚所伴随的脚部充气*/


/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓
【推杆】表格                   【推杆】表格                   【推杆】表格                   【推杆】表格
〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
extern  const SpikeAutoTabItem_t  SpikeAutoTab_UserRun[];
extern  const SpikeAutoTabItem_t  SpikeAutoTab_ExeMassage[];
extern  const SpikeAutoTabItem_t  SpikeAutoTab_ZeroGravity1[];
extern  const SpikeAutoTabItem_t  SpikeAutoTab_ZeroGravity2[];
extern  const SpikeAutoTabItem_t  SpikeAutoTab_Home[];

extern  const SpikeAutoTabItem_t  SpikeAutoTab_Rocking[];          /*拉筋  摇摇椅  1m10s*/

/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓
【机芯+充气】表格              【机芯+充气】表格              【机芯+充气】表格              【机芯+充气】表格
〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/


/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓
【机芯+推杆】表格              【机芯+推杆】表格              【机芯+推杆】表格              【机芯+推杆】表格
〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
 

/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓
【充气+推杆】表格              【充气+推杆】表格              【充气+推杆】表格              【充气+推杆】表格
〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/


/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓
【机芯+充气+推杆】表格         【机芯+充气+推杆】表格         【机芯+充气+推杆】表格         【机芯+充气+推杆】表格
〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
extern  const CoreGasSpikeAutoTabItem_t  CoreGasSpikeAutoTab_Shoulder[];             /*拉筋  肩部 1m10s*/
extern  const CoreGasSpikeAutoTabItem_t  CoreGasSpikeAutoTab_ShoulderTCS[];          /*拉筋  肩敲 1m15s*/
extern  const CoreGasSpikeAutoTabItem_t  CoreGasSpikeAutoTab_Lumbar[];               /*拉筋  腰部 1m50s*/
extern  const CoreGasSpikeAutoTabItem_t  CoreGasSpikeAutoTab_BackFeet[];             /*拉筋  腿背上下 1m25ss*/
extern  const CoreGasSpikeAutoTabItem_t  CoreGasSpikeAutoTab_FeetUpDown[];           /*拉筋  腿脚 上下2m40s*/



/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓
【机芯】混合【其他】表格       【机芯】混合【其他】表格       【机芯】混合【其他】表格       【机芯】混合【其他】表格  
〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_Quick[];                  /*快速按摩*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_Relax[];                  /*舒缓放松*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_MoveSleep[];              /*摇动舒眠*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_Stretch[];                /*伸展拉伸*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_Scraping[];               /*刮痧推拿*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_Shiatsu[];                /*深度指压*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_Lady[];                   /*轻柔舒缓（女士专属）*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_Man[];                    /*深度放松（男士专属）*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_ShoulderRelax[];          /*颈肩放松*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_ShoulderRecovery[];       /*颈肩元气（疲劳）恢复*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_ShoulderTuina[];          /*颈肩推拿*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_ShoulderShiatsu[];        /*颈肩深度指压*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_LumbarButtockRelax[];     /*腰臀放松*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_LumbarButtockRecovery[];  /*腰臀元气（疲劳）恢复*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_LumbarButtockPress[];     /*腰臀经络按压*/
extern  const CoreMixOtherTabItem_t  CoreMixOtherTab_LumbarKidneyCare[];       /*腰臀保健*/


/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓
【宫格组合】表格              【宫格组合】表格              【宫格组合】表格              【宫格组合】表格
〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
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
