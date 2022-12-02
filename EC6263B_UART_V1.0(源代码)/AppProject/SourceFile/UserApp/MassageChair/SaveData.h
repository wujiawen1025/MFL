/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: SaveData.h
**
**    功能描述: 掉电保存数据的处理
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
#ifndef  _SAVEDATA_H
#define  _SAVEDATA_H


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp.h"
#include "ESF.h"
#include "memory.h"


/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
#define   SOFT_EDITION          10   /*软件版本号*/

#define   ID_CODE_BUF_SIZE      30


/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  掉电保存数据 相关操作数据结构                                                                                 
************************************************************************************************************************
*/
typedef struct
{
  
  uint16_t        Sync;                           /*同步字*/
  uint16_t        ResetCount;                     /*程序复位次数*/

  uint32_t        SysRunTimeMs100;                /*系统运行时间*/

  uint32_t        XMotorRunTimeMs100;             /*X马达运行时间*/
  uint32_t        YMotorRunTimeMs100;             /*Y马达运行时间*/
  uint32_t        ZMotorRunTimeMs100;             /*Z马达运行时间*/
  uint32_t        TCSMotorRunTimeMs100;           /*敲击马达运行时间*/

  uint32_t        BackSpikeMotorRunTimeMs100;     /*靠背推杆马达运行时间*/
  uint32_t        FeetSpikeMotorRunTimeMs100;     /*小腿推杆马达运行时间*/
  uint32_t        ZeroSpikeMotorRunTimeMs100;     /*零重力推杆马达运行时间*/
  uint32_t        LegFlexMotorRunTimeMs100;      /*小腿伸缩马达运行时间*/

  uint8_t         IDCodeLen;                      /*身份ID编码长度*/
  uint8_t         IDCode[ID_CODE_BUF_SIZE];       /*身份ID编码*/
  uint8_t         IDCodeWriteCount;               /*身份ID编码写入次数*/ 
}SaveData_t;




/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
#define  SaveData_Write(v,l)      BSP_FEEP_Write(v, l)
#define  SaveData_Read(v,l)       BSP_FEEP_Read(v, l)

uint16_t SaveData_GetSysRunTimeHour(void);
uint16_t SaveData_GetXMotorRunTimeHour(void);
uint16_t SaveData_GetYMotorRunTimeHour(void);
uint16_t SaveData_GetZMotorRunTimeHour(void);
uint16_t SaveData_GetTCSMotorRunTimeHour(void);
uint16_t SaveData_GetBackSpikeMotorRunTimeHour(void);
uint16_t SaveData_GetFeetSpikeMotorRunTimeHour(void);
uint16_t SaveData_GetZeroSpikeMotorRunTimeHour(void);
uint16_t SaveData_GetLegFlexMotorRunTimeHour(void);
uint8_t  SaveData_GetIDCodeWriteCount(void);
uint8_t SaveData_GetIDCode(uint8_t *pData);
uint8_t SaveData_WriteIDCode(uint8_t *pData, uint8_t Len);

SaveData_t* SaveData_Load(void);
void SaveData_Handle(void);


#endif
