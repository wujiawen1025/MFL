/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: Server.c                                                                                                         
**
**    功能描述: 
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

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "Server.h"
#include "ESF.h"
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
static Server_t   Server;
Server_t   *pServer = &Server;

extern uint8_t MChair_KeyValHandle(uint8_t KeyVal, uint8_t *pData);

/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/

/*
************************************************************************************************************************
* 函数名称 : VoiceKey_Default                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_Default(uint8_t *pData)
{
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : VoiceKey_PowerOn                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_PowerOn(uint8_t *pData)
{
  if(SYS_MODE_STANDBY == pMChair->SysModeCur)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : VoiceKey_PowerOff                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_PowerOff(uint8_t *pData)
{
  if(SYS_MODE_USERRUN == pMChair->SysModeCur)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : VoiceKey_PauseOn                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_PauseOn(uint8_t *pData)
{
  if(FALSE == pMChair->CSFlag.Bit.Pause)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : VoiceKey_PauseOff                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_PauseOff(uint8_t *pData)
{
  if(TRUE == pMChair->CSFlag.Bit.Pause)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : VoiceKey_HeatLumbarBackOn                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_HeatLumbarBackOn(uint8_t *pData)
{
  if(OFF == pMChair->LumbarBackHeatCtrlSw)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : VoiceKey_HeatLumbarBackOff                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_HeatLumbarBackOff(uint8_t *pData)
{
  if(ON == pMChair->LumbarBackHeatCtrlSw)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : VoiceKey_AutoQuickOn                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_AutoQuickOn(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Quick)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : VoiceKey_AutoRelaxOn                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_AutoRelaxOn(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Relax)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : VoiceKey_AutoMoveSleepOn                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_AutoMoveSleepOn(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_MoveSleep)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : VoiceKey_AutoStretchOn                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_AutoStretchOn(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Stretch)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : VoiceKey_AutoScrapingOn                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_AutoScrapingOn(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Scraping)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : VoiceKey_AutoShiatsuOn                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_AutoShiatsuOn(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Shiatsu)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : VoiceKey_AutoLadyOn                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_AutoLadyOn(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Lady)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : VoiceKey_AutoManOn                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_AutoManOn(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Man)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}


/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/

static const ServerLogic_t VoiceLogicTab[] = 
{
  /*附加操作：

    键值执行前：bit7 -- 1：关机时，仍可执行    
                        0：关机时，则按键不执行   
    键值执行前：bit6 -- 1：暂停开启，仍可执行
                        0：暂停开启，则不执行。
    键值执行前：bit5 -- 

    键值执行后：                                                   */
  /*  语音指令           对应的按键键值                 语音键值附加操作           */
  {       8,             KEYVAL_Power,                  VoiceKey_PowerOn            },
  {       9,             KEYVAL_Power,                  VoiceKey_PowerOff           },
  {      10,             KEYVAL_Pause,                  VoiceKey_PauseOn            },
  {      11,             KEYVAL_Pause,                  VoiceKey_PauseOff           },

  {      28,             KEYVAL_SpikeZeroGravity1,      VoiceKey_Default            },
  {      31,             KEYVAL_SpikeHomeReset,         VoiceKey_Default            },
  {      40,             KEYVAL_CoreXYZSpeedAdd,        VoiceKey_Default            },
  {      41,             KEYVAL_CoreXYZSpeedDec,        VoiceKey_Default            }, 
  {     103,             KEYVAL_HeatLumbarBack,         VoiceKey_HeatLumbarBackOn   },
  {     107,             KEYVAL_HeatLumbarBack,         VoiceKey_HeatLumbarBackOff  },

  {     120,             KEYVAL_AutoQuick,              VoiceKey_AutoQuickOn        },  
  {     121,             KEYVAL_AutoRelax,              VoiceKey_AutoRelaxOn        }, 
  {     122,             KEYVAL_AutoMoveSleep,          VoiceKey_AutoMoveSleepOn    }, 
  {     123,             KEYVAL_AutoStretch,            VoiceKey_AutoStretchOn      }, 
  {     124,             KEYVAL_AutoScraping,           VoiceKey_AutoScrapingOn     },  
  {     125,             KEYVAL_AutoShiatsu,            VoiceKey_AutoShiatsuOn      }, 
  {     126,             KEYVAL_AutoLady,               VoiceKey_AutoLadyOn         }, 
  {     127,             KEYVAL_AutoMan,                VoiceKey_AutoManOn          }, 
  
};
#define  VOICE_LOGIC_TAB_NUM    TAB_NUM(VoiceLogicTab)

static uint16_t VoiceLogicID(uint16_t index)
{
  if(index > (VOICE_LOGIC_TAB_NUM-1))
  {
    return INDEX_NO_MATCH;
  }
  return VoiceLogicTab[index].ID;
}

/*
************************************************************************************************************************
* 函数名称 : Server_SetKeyExeState                                                                                      
* 功能描述 : 
* 输入参数 : 无
* 返回参数 : 
* 补充说明 : 无
************************************************************************************************************************
*/
void Server_SetKeyExeState(uint8_t TrueFalse)
{
  pServer->CSFlag.KeyExeState = TrueFalse;
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjRX_0x0702                                                                                      
* 功能描述 : 接收键值
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象中数据的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0702(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  CDP_DataFormat0x0702_t  *pData0x0702;
  uint8_t state;
  uint16_t index;

  pData0x0702 = (CDP_DataFormat0x0702_t *)&pRxDU[CDP_DU_OFFSET_LEN];
  
  index = BinarySearch(pData0x0702->KeyVal, VOICE_LOGIC_TAB_NUM, VoiceLogicID);
  if(index != INDEX_NO_MATCH ) 
  {
    state = VoiceLogicTab[index].pVoiceKey(&pData0x0702->AddtionData[0]);
    if(SUCCESS == state)
    {
      state |= MChair_KeyValHandle(VoiceLogicTab[index].KeyVal, &pData0x0702->AddtionData[0]);
    }
  }
  
  if(SUCCESS == state)
  {
    pServer->CSFlag.KeyExeState = TRUE;
  }
  else// if(FAIL == state) 
  {
    pServer->CSFlag.KeyExeState = FALSE;
  }
  
  /*返回数据给服务器-------------------------------------------------------------*/
  memcpy(&pAckDU[CDP_DU_OFFSET_LEN], &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjTx_0x0040                                                                                      
* 功能描述 : 0x0040 上电发送电子序列号
* 输入参数 : 无
* 返回参数 : 成功则返回要发送的数据的内存首地址，失败返回NULL空指针
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x0040(void)
{
//  pServer->CSFlag.GetIDCodeQry = FALSE;
  
  pServer->SetQry0x0040.DataLen = sizeof(pServer->SetQry0x0040);
  pServer->SetQry0x0040.DataID[0] = 0x00;
  pServer->SetQry0x0040.DataID[1] = 0x40;
  
  SaveData_GetIDCode(pServer->SetQry0x0040.IDCode);

  return (uint8_t *)&pServer->SetQry0x0040;
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjTx_0x0041                                                                                      
* 功能描述 : 0x0041 心跳包
* 输入参数 : 无
* 返回参数 : 成功则返回要发送的数据的内存首地址，失败返回NULL空指针
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x0041(void)
{
  pServer->SetQry0x0040.DataLen = sizeof(pServer->SetQry0x0040);
  pServer->SetQry0x0040.DataID[0] = 0x00;
  pServer->SetQry0x0040.DataID[1] = 0x41;
  
  SaveData_GetIDCode(pServer->SetQry0x0040.IDCode);

  return (uint8_t *)&pServer->SetQry0x0040;
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjTx_0x0042                                                                                      
* 功能描述 : 0x0042 上电发送程序版本号
* 输入参数 : 无
* 返回参数 : 成功则返回要发送的数据的内存首地址，失败返回NULL空指针
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x0042(void)
{
  pServer->SetQry0x0042.DataLen = sizeof(pServer->SetQry0x0040);  
  pServer->SetQry0x0042.DataID[0] = 0x00;  
  pServer->SetQry0x0042.DataID[1] = 0x42; 
  
  memcpy(pServer->SetQry0x0042.CodeVER, "EC8606B_CEN_V1.0", 16);       /*获取程序版本号*/

  return (uint8_t *)&pServer->SetQry0x0042;
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjTx_0x0043                                                                                      
* 功能描述 : 0x0048 上电发送远程升级方式
* 输入参数 : 无
* 返回参数 : 成功则返回要发送的数据的内存首地址，失败返回NULL空指针
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x0043(void)
{
  pServer->SetQry0x0043.DataLen = sizeof(pServer->SetQry0x0043);  
  pServer->SetQry0x0043.DataID[0] = 0x00;  
  pServer->SetQry0x0043.DataID[1] = 0x43;

  pServer->SetQry0x0043.UpdataWay = NEED_CACHE_REMOTE_UPGRADES;
  
  return (uint8_t *)&pServer->SetQry0x0043;
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjRX_0x0040                                                                                      
* 功能描述 : 判断服务器是否收到中心板上报的电子序列号                                                                                 
* 输入参数 : pRxDU  -- 指向接收的数据对象单元
*            pAckDU -- 指向应答的数据对象单元
* 返回参数 : 该数据对象中数据的长度                                                                                                    
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0040(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  pServer->CSFlag.UpDataSuc_0x0040 = TRUE;
  
  if( (TRUE == pServer->CSFlag.UpDataSuc_0x0040) &&
      (TRUE == pServer->CSFlag.UpDataSuc_0x0042) &&
      (TRUE == pServer->CSFlag.UpDataSuc_0x0043)   )
  {
    pServer->CSFlag.WIFIIntCfg = TRUE;
  }
  
  return 0;                              /*不需要回复*/
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjRX_0x0042                                                                                      
* 功能描述 : 判断服务器是否收到中心板上报的中心板程序版本号                                                                                 
* 输入参数 : pRxDU  -- 指向接收的数据对象单元
*            pAckDU -- 指向应答的数据对象单元
* 返回参数 : 该数据对象中数据的长度                                                                                                    
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0042(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  pServer->CSFlag.UpDataSuc_0x0042 = TRUE;
  
  if( (TRUE == pServer->CSFlag.UpDataSuc_0x0040) &&
      (TRUE == pServer->CSFlag.UpDataSuc_0x0042) &&
      (TRUE == pServer->CSFlag.UpDataSuc_0x0043)   )
  {
    pServer->CSFlag.WIFIIntCfg = TRUE;
  }
  
  return 0;                            /*不需要回复*/
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjRX_0x0043                                                                                      
* 功能描述 : 判断服务器是否收到中心板上报的设备远程升级方式                                                                             
* 输入参数 : pRxDU  -- 指向接收的数据对象单元
*            pAckDU -- 指向应答的数据对象单元
* 返回参数 : 该数据对象中数据的长度                                                                                                    
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0043(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  pServer->CSFlag.UpDataSuc_0x0043 = TRUE;
  
  if( (TRUE == pServer->CSFlag.UpDataSuc_0x0040) &&
      (TRUE == pServer->CSFlag.UpDataSuc_0x0042) &&
      (TRUE == pServer->CSFlag.UpDataSuc_0x0043)   )
  {
    pServer->CSFlag.WIFIIntCfg = TRUE;
  }
  
  return 0;                               /*不需要回复*/
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjTx_0x0D01                                                                                   
* 功能描述 : 按摩椅状态数据1
* 输入参数 : 无
* 返回参数 : 成功则返回要发送的数据的内存首地址，失败返回NULL空指针
* 补充说明 : 开机时变化上报
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x0D01(void)
{
  CDP_DataFormat0x0D01_t Set0x0D01;
  
  memset(&Set0x0D01, 0, sizeof(CDP_DataFormat0x0D01_t)); /*清零所有数据*/
  
  Set0x0D01.DataLen   = sizeof(pServer->SetQry0x0D01);
  Set0x0D01.DataID[0] = 0x0D;
  Set0x0D01.DataID[1] = 0X01;
  
  Set0x0D01.Byte1.Bit.SysRun             = pMChair->CSFlag.Bit.SysRun;
  Set0x0D01.Byte1.Bit.Pause              = pMChair->CSFlag.Bit.Pause;
  Set0x0D01.Byte1.Bit.MassageTimeOut     = pMChair->CSFlag.Bit.UserMassageTimeOut;

  Set0x0D01.Byte2.Bit.CoreXYZKneadInRun  = pMChair->StateCoreAction.Bit.XYZ.Bit.KneadInRun;
  Set0x0D01.Byte2.Bit.CoreXYZKneadOutRun = pMChair->StateCoreAction.Bit.XYZ.Bit.KneadOutRun;
  Set0x0D01.Byte2.Bit.CoreTCSLTapRun     = pMChair->StateCoreAction.Bit.TCS.Bit.LTapRun;
  Set0x0D01.Byte2.Bit.CoreTCSTapRun      = pMChair->StateCoreAction.Bit.TCS.Bit.TapRun;
  Set0x0D01.Byte2.Bit.CoreTCSClap1Run    = pMChair->StateCoreAction.Bit.TCS.Bit.Clap1Run;
  Set0x0D01.Byte2.Bit.CoreTCSClap2Run    = pMChair->StateCoreAction.Bit.TCS.Bit.Clap2Run;
  Set0x0D01.Byte3.Bit.CoreTCSShia1Run    = pMChair->StateCoreAction.Bit.TCS.Bit.Shia1Run;
  Set0x0D01.Byte3.Bit.CoreTCSShia2Run    = pMChair->StateCoreAction.Bit.TCS.Bit.Shia2Run;
  Set0x0D01.Byte3.Bit.CoreXYZRollRun     = pMChair->StateCoreAction.Bit.XYZ.Bit.RollRun;
  
  Set0x0D01.Byte17.Bit.KeyAuto           = pMChair->FuncAuto_CoreGas + 20;

  Set0x0D01.Byte29.Bit.MassageTimeMin    = pMChair->UserMassageTimeMin;
  Set0x0D01.Byte30.Bit.MassageTimeSec    = pMChair->UserMassageTimeSec;
  
  /*变化上报*/
  if( memcmp(&pServer->SetQry0x0D01, &Set0x0D01, sizeof(pServer->SetQry0x0D01)) )
  {
    memcpy(&pServer->SetQry0x0D01, &Set0x0D01, sizeof(pServer->SetQry0x0D01));
    pMChair->CSFlag.Bit.MChairReported = TRUE;
  }

  return (uint8_t *)&pServer->SetQry0x0D01;
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjRX_0x0D01                                                                                      
* 功能描述 :                                                                         
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0D01(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  pMChair->CSFlag.Bit.MChairReported = FALSE;
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjTx_0x0D02                                                                                   
* 功能描述 : 按摩椅状态数据2
* 输入参数 : 无
* 返回参数 : 成功则返回要发送的数据的内存首地址，失败返回NULL空指针
* 补充说明 : 关机时变化上报
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x0D02(void)
{
  CDP_DataFormat0x0D02_t Set0x0D02;

  Set0x0D02.DataLen   = sizeof(pServer->SetQry0x0D02);
  Set0x0D02.DataID[0] = 0x0D;
  Set0x0D02.DataID[1] = 0X02;
  
  Set0x0D02.Byte1 = '8';
  Set0x0D02.Byte2 = '6';
  Set0x0D02.Byte3 = '0';
  Set0x0D02.Byte5 = '6';
  
  Set0x0D02.Byte4.Bit.ResetOK = 1;

  if((FALSE == pMChair->StateXMotor.Bit.PositionResetOK) ||
     (FALSE == pMChair->StateYMotor.Bit.PositionResetOK) ||
     (FALSE == pMChair->StateZMotor.Bit.PositionResetOK) )
  {
    Set0x0D02.Byte4.Bit.ResetOK &= 0;                                                         /*机芯位置还未复位*/
  }
  
  if(Core_GetYPosition() != PY_MIN)
  {
    Set0x0D02.Byte4.Bit.ResetOK &= 0;                                                        /*机芯不处于顶端*/
  }

  if((FALSE == pMChair->StateBackSpike.Bit.PositionResetOK)   ||
     //(FALSE == pMChair->StateZeroSpike.Bit.PositionResetOK)    ||
     (FALSE == pMChair->StateFeetSpike.Bit.PositionResetOK)   ||
     (FALSE == pMChair->StateLegFlexSpike.Bit.PositionResetOK)) 
  {
    Set0x0D02.Byte4.Bit.ResetOK &= 0;                                                        /*推杆位置还未复位*/
  }

  Set0x0D02.Byte4.Bit.WIFIIntCfg = pServer->CSFlag.WIFIIntCfg;
  
  /*变化上报*/
  if( memcmp(&pServer->SetQry0x0D02, &Set0x0D02, sizeof(pServer->SetQry0x0D02)) )
  {
    memcpy(&pServer->SetQry0x0D02, &Set0x0D02, sizeof(pServer->SetQry0x0D02));
    pMChair->CSFlag.Bit.MChairReported = TRUE;
  }

  return (uint8_t *)&pServer->SetQry0x0D02;
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjRX_0x0D02                                                                                      
* 功能描述 :                                                                         
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0D02(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  pMChair->CSFlag.Bit.MChairReported = FALSE;
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* 函数名称 : Server_SetIntData                                                                                   
* 功能描述 : 配置网络数据
* 输入参数 : 无
* 返回参数 : 成功则返回要发送的数据的内存首地址，失败返回NULL空指针
* 补充说明 : 
************************************************************************************************************************
*/
void Server_SetIntData(uint8_t *data, uint8_t len, uint8_t reconfiguration)
{
  uint8_t i;
  
  if(TRUE == reconfiguration)
  {
    pServer->IntDataLen = 0;
  }
  
  if(pServer->IntDataLen > 67)
  {
    return;
  }
  
  for(i=0; i<len; i++)
  {
    pServer->SetQry0x0912.IntCfgData[pServer->IntDataLen] = *(data+i);
    pServer->IntDataLen ++;
  }
}

void Server_SetIntState(uint8_t TrueFalse)
{
  pServer->CSFlag.NetDataRx = TrueFalse;
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjTx_0x0912                                                                                   
* 功能描述 : 发送配网数据给服务器
* 输入参数 : 无
* 返回参数 : 成功则返回要发送的数据的内存首地址，失败返回NULL空指针
* 补充说明 : 
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x0912(void)
{
  pServer->SetQry0x0912.DataID[0] = 0x09;
  pServer->SetQry0x0912.DataID[1] = 0x12;
  
  pServer->SetQry0x0912.DataLen = pServer->IntDataLen + 3;
  
//  pServer->SetQry0x0912.IntCfgData = 
  return (uint8_t *)&pServer->SetQry0x0912;
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjRX_0x0912                                                                                      
* 功能描述 : 接收服务器配网指令应答数据
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象中数据的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0912(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  Server_SetIntState(FALSE);           /*清除接收完成标志*/
  
  memcpy(&pAckDU[CDP_DU_OFFSET_LEN], &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjRX_0x0913                                                                                      
* 功能描述 : 获取椅子电子序列号
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象中数据的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0913(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  
  pServer->CSFlag.UpDataSuc_0x0040 = FALSE;
  pServer->CSFlag.UpDataSuc_0x0042 = FALSE;
  pServer->CSFlag.UpDataSuc_0x0043 = FALSE;
  
  /*返回数据给服务器-------------------------------------------------------------*/
  memcpy(&pAckDU[CDP_DU_OFFSET_LEN], &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjRX_0x0C60                                                                                      
* 功能描述 : 获取椅子状态
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象中数据的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0C60(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  CDP_DataFormat0x0C60_t  *pData0x0C60;
  
  pData0x0C60 = (CDP_DataFormat0x0C60_t *)&pRxDU[CDP_DU_OFFSET_LEN];
  
  if(SYS_MODE_USERRUN == pMChair->SysModeCur)
  {
    if(TRUE == pMChair->CSFlag.Bit.Pause)
    {
      pData0x0C60->SystemState = 3;
    }
    else
    {
      pData0x0C60->SystemState = 1;
    }
  }
  else// if(SYS_MODE_STANDBY == pMChair->SysModeCur)
  {
    pData0x0C60->SystemState = 0;
  }
  
  /*返回数据给服务器-------------------------------------------------------------*/
  memcpy(&pAckDU[CDP_DU_OFFSET_LEN], &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjTx_0x004C                                                                                   
* 功能描述 : 故障码上报给服务器
* 输入参数 : 无
* 返回参数 : 成功则返回要发送的数据的内存首地址，失败返回NULL空指针
* 补充说明 : 
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x004C(void)
{
  uint8_t i;
  
  pServer->SetQry0x004C.DataLen = sizeof(pServer->SetQry0x004C);
  pServer->SetQry0x004C.DataID[0] = 0x00;
  pServer->SetQry0x004C.DataID[1] = 0x4C;
  
  for(i=0; i<10; i++)
  {
    pServer->SetQry0x004C.FaultCodeBit[i] = pMChair->Fault.ReportFlag.All[i];
  }

  return (uint8_t *)&pServer->SetQry0x004C;
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjRX_0x0901                                                                                      
* 功能描述 : 获取按摩椅当前状态                                                                                
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0901(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
//  uint16_t i;

//  /*关输出，然后复位，复位后进入BootLoade模式*/
//  BSP_IO_SetOutput_CloseAll();
//  while(++i < 1000);
//  BSP_SystemReset();  
//  return 0;
  if( 0 == pRxDU[CDP_DU_OFFSET_SERVER_DATA] )
  {
    pAckDU[CDP_DU_OFFSET_SERVER_DATA] = 0;
    pServer->CSFlag.UpDataSuc_0x0040 = TRUE;
    pServer->CSFlag.UpDataSuc_0x0042 = TRUE;
    pServer->CSFlag.UpDataSuc_0x0043 = TRUE;
    return 4;
  }
  else
  {
    return CDP_DU_HANDLE_ERR;
  }
}

/*
************************************************************************************************************************
* 函数名称 : Server_CDPDataObjTx_0x004D                                                                                   
* 功能描述 : 电机按摩时间上报给服务器
* 输入参数 : 无
* 返回参数 : 成功则返回要发送的数据的内存首地址，失败返回NULL空指针
* 补充说明 : 
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x004D(void)
{
  pServer->SetQry0x004D.DataLen = sizeof(pServer->SetQry0x004D);
  pServer->SetQry0x004D.DataID[0] = 0x00;
  pServer->SetQry0x004D.DataID[1] = 0x4D;
  
  pServer->SetQry0x004D.SysRunTimeHour             = SaveData_GetSysRunTimeHour();
  pServer->SetQry0x004D.XMotorRunTimeHour          = SaveData_GetXMotorRunTimeHour();
  pServer->SetQry0x004D.YMotorRunTimeHour          = SaveData_GetYMotorRunTimeHour();
  pServer->SetQry0x004D.ZMotorRunTimeHour          = SaveData_GetZMotorRunTimeHour();
  pServer->SetQry0x004D.TCSMotorRunTimeHour        = SaveData_GetTCSMotorRunTimeHour();
  pServer->SetQry0x004D.BackSpikeMotorRunTimeHour  = SaveData_GetBackSpikeMotorRunTimeHour();
  pServer->SetQry0x004D.FeetSpikeMotorRunTimeHour  = SaveData_GetFeetSpikeMotorRunTimeHour();

  return (uint8_t *)&pServer->SetQry0x004D;
}

/*
************************************************************************************************************************
* 函数名称 : Server_ReReportedData                                                                                                         
* 功能描述 : 重新上报数据            
* 输入参数 : 无                                            
* 返回参数 : 返回 可操服务器功能 的结构体 的指针                                                                               
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Server_ReReportedData(void)
{
  pServer->CSFlag.UpDataSuc_0x0040 = FALSE;
  pServer->CSFlag.UpDataSuc_0x0042 = FALSE;
  pServer->CSFlag.UpDataSuc_0x0043 = FALSE;
  pServer->CSFlag.WIFIIntCfg       = FALSE;
}

/*
************************************************************************************************************************
* 函数名称 : Server_Init                                                                                                         
* 功能描述 : 服务器处理函数 初始化                 
* 输入参数 : 无                                            
* 返回参数 : 返回 可操服务器功能 的结构体 的指针                                                                               
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
Server_t* Server_Init(void)
{
  /*初始化相关数据------------------------------------------*/
  memset(pServer, 0, sizeof(Server_t)); /*清零所有数据*/
  Server_SetKeyExeState(TRUE);
  
  return pServer;
}

/*
************************************************************************************************************************
* 函数名称 : Server_GetCSFlag                                                                                                         
* 功能描述 : 获得 控制 与 状态 标识                        
* 输入参数 : 无                                            
* 返回参数 : 控制与状态标识 的结构体                                                                                           
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
ServerCSFlag_t Server_GetCSFlag(void)
{
  return pServer->CSFlag;
}
