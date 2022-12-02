/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: RealTimeInspec.c 
**
**    功能描述: 实时检测
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

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "RealTimeInspect.h"
#include "MChair.h"


/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/


/*
========================================================================================================================
*【本地数据类型定义】                              【本地数据类型定义】                              【本地数据类型定义】
========================================================================================================================
*/


/*
========================================================================================================================
*【变量定义 & 各种声明】                          【变量定义 & 各种声明】                          【变量定义 & 各种声明】    
========================================================================================================================
*/


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
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
*                      故障表
* 对故障号 进行统一的分配与管理，方便查看修改。
**************************************************************************************************************/
static const FaultItem_t FaultTab[] = 
{
  /*附加操作：bit0 -- 故障 则 执行关机操作  
              bit1 -- 故障 则 置位发生不允许启动的故障标识*/


  /*故障号    故障报告时长           附加操作         故障检测*/

  /*故障号1~31，以前已经有的-----------------------------------------------*/
//  {1,       FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_01},    /*手控器检测到按键长按超过45S*/
  {2,       FAULT_REPORT_TL_ALWAYS,  B(00000001),    FaultCheck_02},    /*手控器与中心板超过4S未成功通讯*/
  {3,       FAULT_REPORT_TL_ALWAYS,  B(00000001),    FaultCheck_03},    /*机芯控制板与中心板超过4S未成功通讯*/
//  {4,       FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_04},    /*行程计数信号错误*/
  {5,       FAULT_REPORT_TL_ALWAYS,  B(00000001),    FaultCheck_05},    /*侧板按键检测到按键长按超过45S*/
  {6,       FAULT_REPORT_TL_ALWAYS,  B(00000001),    FaultCheck_06},    /*小腿板与中心板超过4S未成功通讯*/
//  {7,       FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_07},    /*两个以上宽度位置检测同时有效*/
//  {8,       FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_08},    /*5S钟未检测到宽位信号*/
//  {9,       FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_09},    /*5S钟未检测到中位信号*/
//  {10,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_10},    /*5S钟未检测到窄位信号*/
//  {11,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_11},    /*10S钟未检测到揉捏换向信号*/
//  {12,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_12},    /*揉捏电机关闭后还检测到宽度信号*/
//  {13,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_13},    /*上下限位传感器同时有效*/
//  {14,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_14},    /*40S钟未检测到上限位传感器信号*/
//  {15,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_15},    /*机芯不揉捏或不敲击*/
//  {16,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_16},    /*上限位传感器检测到信号后2S内又检测到下限位传感器信号*/
//  {17,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_17},    /*40S钟未检测到下限位传感器信号*/
//  {18,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_18},    /*下限位传感器检测到信号后2S内又检测到上限位传感器信号*/
//  {19,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_19},    /*腿部推杆开启2.5S未检测到计数信号(或40S未检测到推杆到位信号)*/
//  {20,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_20},    /**/
//  {21,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_21},    /**/
//  {22,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_22},    /**/
//  {23,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_23},    /**/
//  {24,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_24},    /**/
//  {25,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_25},    /*背部推杆开启2.5S未检测到计数信号(或40S未检测到推杆到位信号)*/
//  {26,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_26},    /*零重力推杆开启2.5S未检测到计数信号*/
//  {27,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_27},    /*伸缩前后限位传感器同时有效(3D机芯)*/
//  {28,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_28},    /*伸缩开启10S钟未检测到伸缩限位传感器信号(3D机芯)*/
//  {29,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_29},    /*机芯伸缩计数信号异常(3D机芯)*/
//  {30,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_30},    /*伸缩限位传感器检测到信号后2S内又检测到另一端伸缩限位传感器信号(3D机芯)*/
//  {31,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_31},    /*小腿伸缩堵转或小腿伸缩计数异常*/
 
  /*故障号32开始的，主要基于松下31/34机芯新扩展的----------------------------------------*/
  {32,      FAULT_REPORT_TL_05S,     B(00000001),    FaultCheck_32},    /*侧板按键与中心板 超过4S未成功通讯*/
//  {33,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_33},    /*按摩椅 无人入座异常*/
//  {34,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_34},    /*预留  酸痛检测通信异常*/
//  {35,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_35},    /*预留  按摩力度检测过负荷异常*/
//  {36,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_36},    /*预留  按摩力度检测无负荷异常*/
//  {37,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_37},    /*预留*/
//  {38,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_38},    /*预留*/
//  {39,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_39},    /*预留*/
  
  {40,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_40},    /*机芯推拿(滚动)马达  位置传感器异常*/
  {41,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_41},    /*机芯推拿(滚动)马达  位置编码异常*/
//  {42,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_42},    /*机芯推拿(滚动)马达  转速(计数)传感器异常*/
//  {43,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_43},    /*机芯推拿(滚动)马达  过电流锁定异常*/
  {44,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_44},    /*机芯揉捏马达  位置传感器异常*/
//  {45,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_45},    /*机芯揉捏马达  位置编码异常*/
  {46,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_46},    /*机芯揉捏马达  转速(计数)传感器异常*/
//  {47,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_47},    /*机芯揉捏马达  过电流锁定异常*/
  {48,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_48},    /*机芯伸缩马达  位置传感器异常*/
  {49,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_49},    /*机芯伸缩马达  位置编码异常*/
  {50,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_50},    /*机芯伸缩马达  转速(计数)传感器异常*/
//  {51,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_51},    /*机芯伸缩马达  过电流锁定异常*/
//  {52,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_52},    /*机芯敲击马达  转速传感器异常*/
//  {53,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_53},    /*机芯敲击马达  过电流锁定异常*/
//  {54,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_54},    /*预留  机芯相关*/
//  {55,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_55},    /*预留  机芯相关*/
  
//  {56,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_56},    /*靠背推杆  位置传感器异常*/
//  {57,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_57},    /*靠背推杆  位置编码异常*/
//  {58,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_58},    /*靠背推杆  过电流锁定异常*/
  {59,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_59},      /*靠背推杆  计数传感器异常*/
//  {60,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_60},    /*小腿推杆  位置传感器异常*/
//  {61,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_61},    /*小腿推杆  位置编码异常*/
//  {62,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_62},    /*小腿推杆  过电流锁定异常*/
  {63,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_63},      /*小腿推杆  计数传感器异常*/
//  {64,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_64},    /*零重力推杆  位置传感器异常*/
//  {65,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_65},    /*零重力推杆  位置编码异常*/
//  {66,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_66},    /*零重力推杆  过电流锁定异常*/
//  {67,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_67},    /*零重力推杆  计数传感器异常*/
  {68,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_68},    /*小腿伸缩  位置(计数)传感器异常*/
  {69,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_69},    /*小腿伸缩  位置编码异常*/
  {70,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_70},    /*小腿伸缩  最短限位传感器故障*/
  {71,      FAULT_REPORT_TL_ALWAYS,  B(00000011),    FaultCheck_71},    /*小腿伸缩  最长限位传感器故障 */

  {72,      FAULT_REPORT_TL_05S,     B(00000000),    FaultCheck_72},    /*背部加热  可控硅短路*/
  {73,      FAULT_REPORT_TL_05S,     B(00000000),    FaultCheck_73},    /*背部加热  热敏电阻短路*/
  {74,      FAULT_REPORT_TL_05S,     B(00000000),    FaultCheck_74},    /*背部加热  热敏电阻开路*/
//  {75,      FAULT_REPORT_TL_ALWAYS,  B(00000000),    FaultCheck_75},    /*预留  背部加热相关*/
//  {76,      FAULT_REPORT_TL_05S,     B(00000000),    FaultCheck_76},    /*脚部加热  晶体管短路*/
//  {77,      FAULT_REPORT_TL_05S,     B(00000000),    FaultCheck_77},    /*脚部加热  热敏电阻短路*/
//  {78,      FAULT_REPORT_TL_05S,     B(00000000),    FaultCheck_78},    /*脚部加热  热敏电阻开路*/
//  {79,      FAULT_REPORT_TL_05S,     B(00000000),    FaultCheck_79},    /*脚部加热  检知线异常*/
//  {80,      FAULT_REPORT_TL_05S,     B(00000000),    FaultCheck_80}     /*机芯振动  转速(计数)传感器异常*/
};

#define  FAULT_TAB_NUM    TAB_NUM(FaultTab)


/*
************************************************************************************************************************
* 函数名称 : RealTimeInspect_FaultCheck                                                                                                         
* 功能描述 : 实时检测之故障检查                                                                                        
* 输入参数 : ExePeriod -- 函数的执行周期                                                                                  
* 返回参数 : 无                                                                   
* 补充说明 : 报警机制：(1) 工程模式下，无论任何故障都一直告警
*                      (2) 其他模式下(待机和用户运行模式),则分两种故障。
*                          一种是一出先便一直告警。
*                          另一种是出现后只告警5s，然后每次用户开机也告警5s。                                                                                                         
************************************************************************************************************************
*/
void RealTimeInspect_FaultCheck(Ticker_t ExePeriod)
{
  static uint8_t  SysModeHis = SYS_MODE_NONE;
  static uint8_t  FaultCheckIndex = 0;
  static uint8_t  DisplayIndex = 0;
  uint8_t  ByteOffSet, BitOffSet;


  /*故障号轮流显示时间处理------------------------------------------------------*/
  if(pMChair->Fault.ReportTLMs > 0) /*上报时间还有剩余*/
  {
    if(DisplayIndex >= FAULT_TAB_NUM)
    {
      DisplayIndex = 0; 
    }  
    ByteOffSet = (FaultTab[DisplayIndex].FaultID-1) >> 3;                             /*计算字节偏移*/
    BitOffSet  = (FaultTab[DisplayIndex].FaultID-1) & 0x07;                           /*计算位偏移*/
    if(pMChair->Fault.ReportFlag.All[ByteOffSet] & (1<<BitOffSet)) 
    {
      pMChair->Fault.DisplayFaultID  = FaultTab[DisplayIndex].FaultID;                /*要显示的故障ID*/
      pMChair->Fault.DisplayTLMsPerFault += ExePeriod;
      if(pMChair->Fault.DisplayTLMsPerFault > 5000)                                   /*显示时间用完*/
      {
        pMChair->Fault.DisplayTLMsPerFault = 0;                                       /*清零故障显示的时间长度*/                               
        pMChair->Fault.DisplayFaultID = 0;                                            /*清空要显示的故障ID*/
        DisplayIndex++;
      }
    }
    else
    {
      pMChair->Fault.DisplayTLMsPerFault = 0;                                         /*清零故障显示的时间长度*/                               
      pMChair->Fault.DisplayFaultID = 0;                                              /*清空要显示的故障ID*/
      DisplayIndex++;
    }  
  }
  else
  {
    pMChair->Fault.DisplayTLMsPerFault = 0;                                         /*清零故障显示的时间长度*/                               
    pMChair->Fault.DisplayFaultID = 0;                                              /*清空要显示的故障ID*/
    DisplayIndex = 0; 
  }

  /*告警时间长度减少----------------------------------------------------------------*/
  if(pMChair->Fault.ReportTLMs > ExePeriod)
  {
    pMChair->Fault.ReportTLMs -= ExePeriod;
  }
  else 
  {
    pMChair->Fault.ReportTLMs = 0;
  }

  /*要上报的故障更新-----------------------------------------------------------*/
  if(FaultTab[FaultCheckIndex].pFaultCheck != NULL)
  {
    ByteOffSet = (FaultTab[FaultCheckIndex].FaultID-1) >> 3;                        /*计算字节偏移*/
    BitOffSet  = (FaultTab[FaultCheckIndex].FaultID-1) & 0x07;                      /*计算位偏移*/

    if(FaultTab[FaultCheckIndex].pFaultCheck() != NORMAL)
    {
     /*附加操作：bit0 -- 故障 则 执行关机操作  
                 bit1 -- 故障 则 置位发生不允许启动的故障标识*/
      if(NORMAL == (pMChair->Fault.ReportFlag.All[ByteOffSet] & (1<<BitOffSet)))    /*刚检测到故障*/
      {
        if(FaultTab[FaultCheckIndex].AdditonOp & B(00000001))
        {
          SysMode_Standby_Enter(SYS_MODE_USERRUN, TRUE);                            /*关机，复位推杆角度*/
        }
      }

      if(FaultTab[FaultCheckIndex].AdditonOp & B(00000010))
      {
        pMChair->CSFlag.Bit.OccurNoStartUpFault = TRUE;                             /*发生不允许启动的故障*/
      }

      /*故障报告时间长度赋值*/
      if(FAULT_REPORT_TL_ALWAYS == FaultTab[FaultCheckIndex].FaultReportTL)
      {
        pMChair->Fault.ReportTLMs = 5000;                                           /*一直报的，每次都赋值*/
      }
      else
      {
        if(NORMAL == (pMChair->Fault.ReportFlag.All[ByteOffSet] & (1<<BitOffSet)))  /*刚检测到故障*/
        {
          pMChair->Fault.ReportTLMs = 5000;                                         /*不是一直报的，刚检测到故障时赋值一次*/
        }
      }

      pMChair->Fault.ReportFlag.All[ByteOffSet] |= (1<<BitOffSet);                  /*有故障*/
    }
    else
    {
      pMChair->Fault.ReportFlag.All[ByteOffSet] &= ~(1<<BitOffSet);                 /*无故障*/
    }
  }

  if((++FaultCheckIndex) >= FAULT_TAB_NUM)
  {
    FaultCheckIndex = 0; /*该函数每次进入只检查一个项目，然后递增到下一个项目，如此循环*/
  }

  /*不同系统模式下，对报警时间长度进行调整------------------------*/
  if(SYS_MODE_STANDBY == pMChair->SysModeCur)
  {
                                           /*关机下，不做任何处理*/
  }
  else if(SYS_MODE_USERRUN == pMChair->SysModeCur)
  {
    if(SysModeHis != SYS_MODE_USERRUN) 
    {
      pMChair->Fault.ReportTLMs = 5000;    /*每次用户开机都赋值一次*/
    }
  }
  else
  {
    pMChair->Fault.ReportTLMs = 5000;      /*工程模式下一直报，每次都赋值*/
  }
  SysModeHis = pMChair->SysModeCur;
}

/*
========================================================================================================================
*     实时检测功能函数表                           实时检测功能函数表                           实时检测功能函数表
========================================================================================================================
*/
#define  REAL_TIME_INSPECT_TICK_COUNT_BUF_NUM   1
static Ticker_t RealTimeInspect_TickCount[REAL_TIME_INSPECT_TICK_COUNT_BUF_NUM];
static const ESF_TmrExeFunc_t  RealTimeInspect_TmrExeFuncTab[] = 
{
  /*       执行函数              执行周期(ms)     时间计数变量*/
  {RealTimeInspect_FaultCheck,     8,          &RealTimeInspect_TickCount[0]} 
};

#define  REAL_TIME_INSPECT_TMR_EXE_FUNC_TAB_NUM     TAB_NUM(RealTimeInspect_TmrExeFuncTab)

/*
************************************************************************************************************************
* 函数名称 : RealTimeInspect_Handle                                                                                                         
* 功能描述 : 实时检测 处理                                                                                        
* 输入参数 : 无                                                                                  
* 返回参数 : 无                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void RealTimeInspect_Handle(void)
{
  /*调度功能函数表------------------------------------------------*/
  ESF_TmrExeFuncScheduling(RealTimeInspect_TmrExeFuncTab, REAL_TIME_INSPECT_TMR_EXE_FUNC_TAB_NUM);
}

/*
************************************************************************************************************************
* 函数名称 : RealTimeInspect_Init                                                                                                         
* 功能描述 : 实时检测 之 初始化                                                                                       
* 输入参数 : 无                                                                                  
* 返回参数 : 无                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void RealTimeInspect_Init(void)
{
  /*检测 RealTimeInspect_TmrExeFuncTab 功能函数表排列是否正确------------------------*/
  ESF_TmrExeFuncTabCheck(RealTimeInspect_TmrExeFuncTab, REAL_TIME_INSPECT_TMR_EXE_FUNC_TAB_NUM, REAL_TIME_INSPECT_TICK_COUNT_BUF_NUM);
}
