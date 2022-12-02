/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: Server.h                                                                                                         
**
**    功能描述: 振动驱动。
**
**    公    司：蒙发利电子
**
**    项目名称：
**
**    平台信息：
**
**    作    者：LZH
**
**    其他说明:
**
**    修改记录:  --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/
#ifndef  _SERVER_H
#define  _SERVER_H

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp.h"
#include "CDP.h"



/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
#define  UNABLE_REMOTE_UPGRADES                             0                    /*不支持远程升级*/ 
#define  NEED_CACHE_REMOTE_UPGRADES                         1                    /*必须通过通讯模块缓存升级文件*/ 
#define  IMMEDIATE_REMOTE_UPGRADES                          2                    /*直接透传升级*/ 


 

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
typedef struct
{
  uint8_t                      ID;
  uint8_t                      KeyVal;                         /*对应的键值*/
  uint8_t                      (*pVoiceKey)(uint8_t *pData);   /*语音键值附加操作*/

}ServerLogic_t;

/*
************************************************************************************************************************
* 类型定义 :  0x0040 按摩椅电子序列号                                                           
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint8_t             IDCode[20];       /*电子序列号*/

}CDP_DataFormat0x0040_t;

/*
************************************************************************************************************************
* 类型定义 :  0x0042                                                            
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint8_t             CodeVER[30];       /*程序版本号*/

}CDP_DataFormat0x0042_t;

/*
************************************************************************************************************************
* 类型定义 :  0x0043                                                            
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint8_t             UpdataWay;        /*升级方式*/

}CDP_DataFormat0x0043_t;


/*
************************************************************************************************************************
* 类型定义 :  0x004C 按摩椅故障码
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint8_t             FaultCodeBit[10];                   /*故障位*/
  
}CDP_DataFormat0x004C_t;

/*
************************************************************************************************************************
* 类型定义 :  0x004D 按摩椅电机运行时间
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint16_t            SysRunTimeHour;                     /*系统运行时间*/
  uint16_t            XMotorRunTimeHour;                  /*X马达运行时间*/
  uint16_t            YMotorRunTimeHour;                  /*Y马达运行时间*/
  uint16_t            ZMotorRunTimeHour;                  /*Z马达运行时间*/
  uint16_t            TCSMotorRunTimeHour;                /*敲击马达运行时间*/
  uint16_t            BackSpikeMotorRunTimeHour;          /*靠背推杆马达运行时间*/
  uint16_t            FeetSpikeMotorRunTimeHour;          /*小腿推杆马达运行时间*/
  
}CDP_DataFormat0x004D_t;

/*
************************************************************************************************************************
* 类型定义 :  0x0702 按摩椅按键数据
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint8_t             KeyVal;                                      /*键值*/
  uint8_t             AddtionData[1];                              /*键值所附带的数据*/
  
}CDP_DataFormat0x0702_t;

/*
************************************************************************************************************************
* 类型定义 :  0x0912 按摩椅配网数据
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint8_t             IntCfgData[67];
  
}CDP_DataFormat0x0912_t;

/*
************************************************************************************************************************
* 类型定义 :  0x0C60 按摩椅状态
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint8_t             SystemState;
  
}CDP_DataFormat0x0C60_t;

/*
************************************************************************************************************************
* 类型定义 :  0x0D01 按摩椅状态数据1
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t        SysRun                         :1;  /*系统开关机状态*/ 
      uint8_t        Pause                          :1;  /*暂停状态*/    
      uint8_t        MassageTimeOut                 :1;  /*按摩定时到状态*/ 
    }Bit;
  }Byte1; 
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t        CoreXYZKneadInRun              :1;  /*向内揉捏手法 运行中*/ 
      uint8_t        CoreXYZKneadOutRun             :1;  /*向外揉捏手法 运行中*/ 
      uint8_t        CoreTCSLTapRun                 :1;  /*轻敲击手法 运行中*/ 
      uint8_t        CoreTCSTapRun                  :1;  /*敲击手法 运行中*/ 
      uint8_t        CoreTCSClap1Run                :1;  /*拍打1手法 运行中*/ 
      uint8_t        CoreTCSClap2Run                :1;  /*拍打2手法 运行中*/ 
    }Bit;
  }Byte2; 
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t        CoreTCSShia1Run                :1;  /*指压1手法 运行中*/ 
      uint8_t        CoreTCSShia2Run                :1;  /*指压2手法 运行中*/
      uint8_t        CoreXYZRollRun                 :1;  /*推拿(滚动)手法 运行中*/ 
    }Bit;
  }Byte3; 
  
  uint8_t Byte4;
  uint8_t Byte5;
  uint8_t Byte6;
  uint8_t Byte7;
  uint8_t Byte8;
  uint8_t Byte9;
  uint8_t Byte10;
  uint8_t Byte11;
  uint8_t Byte12;
  uint8_t Byte13;
  uint8_t Byte14;
  uint8_t Byte15;
  uint8_t Byte16;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t        KeyAuto                        :6;  /*按键 自动程序*/  
    }Bit;
  }Byte17;

  uint8_t Byte18;
  uint8_t Byte19;
  uint8_t Byte20;
  uint8_t Byte21;
  uint8_t Byte22;
  uint8_t Byte23;
  uint8_t Byte24;
  uint8_t Byte25;
  uint8_t Byte26;
  uint8_t Byte27;
  uint8_t Byte28;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t        MassageTimeMin                 :6;  /*按摩剩余时间*/
    }Bit;
  }Byte29;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t        MassageTimeSec                 :6;  /*按摩剩余时间*/
    }Bit;
  }Byte30;
  
}CDP_DataFormat0x0D01_t;

/*
************************************************************************************************************************
* 类型定义 :  0x0D02 按摩椅状态数据2
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint8_t Byte1;
  uint8_t Byte2;
  uint8_t Byte3;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t                                       :1;
      uint8_t          WIFIIntCfg                   :1;
      uint8_t          ResetOK                      :1;
    }Bit;
  }Byte4;
  
  uint8_t Byte5;
  
}CDP_DataFormat0x0D02_t;

/*
************************************************************************************************************************
* 类型定义 :  加热 控制与状态标识                                                                        
************************************************************************************************************************
*/
typedef struct
{
//  uint8_t        GetIDCodeQry                :1;
  uint8_t        KeyExeState                 :1;   /*按键执行结果状态*/
  
  uint8_t        WIFIIntCfg                  :1;   /*WIFI板配网状态*/
  
  uint8_t        NetDataRx                   :1;   /*配网数据接收状态*/
  
  uint8_t        UpDataSuc_0x0040            :1;   /*上报服务器 电子序列号 成功*/
  uint8_t        UpDataSuc_0x0042            :1;   /*上报服务器 中心板程序版本号 成功*/
  uint8_t        UpDataSuc_0x0043            :1;   /*上报服务器 升级方式 成功*/
  
}ServerCSFlag_t;

/*
************************************************************************************************************************
* 类型定义 :  加热操作相关数据结构                                                                          
************************************************************************************************************************
*/
typedef struct
{
  ServerCSFlag_t            CSFlag;                           /*控制与状态标识*/

  uint8_t                   IntDataLen;                       /*配网数据长度*/
  
  CDP_DataFormat0x0040_t    SetQry0x0040;                     /*按摩椅电子序列号*/
  CDP_DataFormat0x0042_t    SetQry0x0042;
  CDP_DataFormat0x0043_t    SetQry0x0043;

  CDP_DataFormat0x004C_t    SetQry0x004C;                     /*按摩椅故障码*/
  CDP_DataFormat0x004D_t    SetQry0x004D;                     /*按摩椅电机运行时间*/
  CDP_DataFormat0x0912_t    SetQry0x0912;                     /*配网数据*/
  
  CDP_DataFormat0x0D01_t    SetQry0x0D01;                     /*按摩椅开机状态数据1*/
  CDP_DataFormat0x0D02_t    SetQry0x0D02;                     /*按摩椅关机状态数据2*/
}Server_t;

/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
/*初始化--------------------------------------*/
Server_t* Server_Init(void);


/*周期执行--------------------------------------*/


/* 对外的接口， 即 其他模块 可对 该模块执行的 控制操作*/
uint8_t* Server_CDPDataObjTx_0x0040(void);
uint8_t* Server_CDPDataObjTx_0x0042(void);
uint8_t* Server_CDPDataObjTx_0x0043(void);
uint8_t* Server_CDPDataObjTx_0x0041(void);
uint8_t* Server_CDPDataObjTx_0x004C(void);
uint8_t* Server_CDPDataObjTx_0x004D(void);
uint8_t* Server_CDPDataObjTx_0x0912(void);
uint8_t* Server_CDPDataObjTx_0x0D01(void);
uint8_t* Server_CDPDataObjTx_0x0D02(void);

uint8_t Server_CDPDataObjRX_0x0040(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0042(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0043(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0702(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0901(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0912(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0913(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0C60(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0D01(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0D02(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);

void Server_SetKeyExeState(uint8_t TrueFalse);
void Server_SetIntData(uint8_t *data, uint8_t len, uint8_t reconfiguration);
void Server_SetIntState(uint8_t TrueFalse);
void Server_ReReportedData(void);

ServerCSFlag_t Server_GetCSFlag(void);
#endif
