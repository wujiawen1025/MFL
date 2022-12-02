/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: SaveData.c
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

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "SaveData.h"
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
static SaveData_t  SaveData;
SaveData_t  *pSaveData = &SaveData;

/*程序鉴别信息，一个信息用一行表示，用回车换行分割*/
const uint8_t SoftIdentifyInfo[] =
{ 
"VER: EC8506A-CEN-V0.1\r\n\
MCU: KE04Z128\r\n\
PCB: EC806A-CEN-V1.1\r\n\
EDT: 2018.10.26"
};


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : SaveData_GetSysRunTimeHour                                                                                                         
* 功能描述 : 获取数据                                                                                        
* 输入参数 : 无                                                                                  
* 返回参数 : 要获得的数据                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint16_t SaveData_GetSysRunTimeHour(void)
{
  if(pSaveData->SysRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->SysRunTimeMs100/36000;
  }
} 

/*
************************************************************************************************************************
* 函数名称 : SaveData_GetXMotorRunTimeHour                                                                                                         
* 功能描述 : 获取数据                                                                                        
* 输入参数 : 无                                                                                  
* 返回参数 : 要获得的数据                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint16_t SaveData_GetXMotorRunTimeHour(void)
{
  if(pSaveData->XMotorRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->XMotorRunTimeMs100/36000;
  }
} 

/*
************************************************************************************************************************
* 函数名称 : SaveData_GetYMotorRunTimeHour                                                                                                         
* 功能描述 : 获取数据                                                                                        
* 输入参数 : 无                                                                                 
* 返回参数 : 要获得的数据                                                                   
* 补充说明 : 无                                                                                                    
************************************************************************************************************************
*/
uint16_t SaveData_GetYMotorRunTimeHour(void)
{
  if(pSaveData->YMotorRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->YMotorRunTimeMs100/36000;
  }
} 

/*
************************************************************************************************************************
* 函数名称 : SaveData_GetZMotorRunTimeHour                                                                                                         
* 功能描述 : 获取数据                                                                                        
* 输入参数 : 无                                                                                  
* 返回参数 : 要获得的数据                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint16_t SaveData_GetZMotorRunTimeHour(void)
{
  if(pSaveData->ZMotorRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->ZMotorRunTimeMs100/36000;
  }
} 

/*
************************************************************************************************************************
* 函数名称 : SaveData_GetTCSMotorRunTimeHour                                                                                                         
* 功能描述 : 获取数据                                                                                        
* 输入参数 : 无                                                                                  
* 返回参数 : 要获得的数据                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint16_t SaveData_GetTCSMotorRunTimeHour(void)
{
  if(pSaveData->TCSMotorRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->TCSMotorRunTimeMs100/36000;
  }
} 

/*
************************************************************************************************************************
* 函数名称 : SaveData_GetBackSpikeMotorRunTimeHour                                                                                                         
* 功能描述 : 获取数据                                                                                        
* 输入参数 : 无                                                                                  
* 返回参数 : 要获得的数据                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint16_t SaveData_GetBackSpikeMotorRunTimeHour(void)
{
  if(pSaveData->BackSpikeMotorRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->BackSpikeMotorRunTimeMs100/36000;
  }
} 

/*
************************************************************************************************************************
* 函数名称 : SaveData_GetFeetSpikeMotorRunTimeHour                                                                                                         
* 功能描述 : 获取数据                                                                                        
* 输入参数 : 无                                                                                  
* 返回参数 : 要获得的数据                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint16_t SaveData_GetFeetSpikeMotorRunTimeHour(void)
{
  if(pSaveData->FeetSpikeMotorRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->FeetSpikeMotorRunTimeMs100/36000;
  }
}
 
/*
************************************************************************************************************************
* 函数名称 : SaveData_GetZeroSpikeMotorRunTimeHour                                                                                                         
* 功能描述 : 获取数据                                                                                        
* 输入参数 : 无                                                                                  
* 返回参数 : 要获得的数据                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint16_t SaveData_GetZeroSpikeMotorRunTimeHour(void)
{
  if(pSaveData->ZeroSpikeMotorRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->ZeroSpikeMotorRunTimeMs100/36000;
  }
} 

/*
************************************************************************************************************************
* 函数名称 : SaveData_GetLegFlexMotorRunTimeHour                                                                                                         
* 功能描述 : 获取数据                                                                                        
* 输入参数 : 无                                                                                  
* 返回参数 : 要获得的数据                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint16_t SaveData_GetLegFlexMotorRunTimeHour(void)
{
  if(pSaveData->LegFlexMotorRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->LegFlexMotorRunTimeMs100/36000;
  }
} 

/*
************************************************************************************************************************
* 函数名称 : SaveData_GetIDCodeWriteCount                                                                                                         
* 功能描述 : 获取ID码写入的次数                                                                                        
* 输入参数 : 无                                                                                  
* 返回参数 : ID码写入的次数                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t SaveData_GetIDCodeWriteCount(void)
{
  return pSaveData->IDCodeWriteCount;
} 

/*
************************************************************************************************************************
* 函数名称 : SaveData_GetIDCode                                                                                                         
* 功能描述 : 获取ID码                                                                                        
* 输入参数 : pData -- 保存获得的数据                                                                                  
* 返回参数 : ID码的长度                                                           
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t SaveData_GetIDCode(uint8_t *pData)
{
  if(pSaveData->IDCodeLen > ID_CODE_BUF_SIZE)
  {
    pSaveData->IDCodeLen = ID_CODE_BUF_SIZE;
  }
  memcpy(pData, pSaveData->IDCode, pSaveData->IDCodeLen);
  return pSaveData->IDCodeLen;
} 

/*
************************************************************************************************************************
* 函数名称 : SaveData_SetIDCode                                                                                                         
* 功能描述 : 写入ID码                                                                                        
* 输入参数 : pData -- 指向要写入的数据
*            Len   -- 要写的数据长度                                                                                  
* 返回参数 : 写入的长度                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t SaveData_WriteIDCode(uint8_t *pData, uint8_t Len)
{
  if(Len > ID_CODE_BUF_SIZE)
  {
    Len = ID_CODE_BUF_SIZE;
  }

  if(pSaveData->IDCodeWriteCount < 255)
  {
    pSaveData->IDCodeWriteCount++;
  }
  
  pSaveData->IDCodeLen = Len;
  memcpy(pSaveData->IDCode, pData, pSaveData->IDCodeLen);
  SaveData_Write((uint8_t*)pSaveData, sizeof(SaveData_t));  /*写入EEProm*/
  
  return Len;
}

/*
************************************************************************************************************************
* 函数名称 : SaveData_Update                                                                                                         
* 功能描述 : 保存数据的更新                                                                                        
* 输入参数 : ExePeriod 函数执行周期                                                                                  
* 返回参数 : 无                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SaveData_Update(Ticker_t ExePeriod)
{
  static  uint8_t SysMode = SYS_MODE_NONE;


  /*保存数据-------------------------------------------------------------*/
  if(SysMode != pMChair->SysModeCur)
  {
    SysMode = pMChair->SysModeCur;
    if(SYS_MODE_STANDBY == SysMode)                              /*每次进入待机模式，就保存一次数据*/
    {
      SaveData_Write((uint8_t*)pSaveData, sizeof(SaveData_t));   /*写入EEProm*/
    }
  }

  /*数据更新----------------------------------------------------------*/
  if((SYS_MODE_USERRUN == pMChair->SysModeCur)      && 
     (ON == pMChair->CSFlag.Bit.UserMassageTimeRun) )
  {
    pSaveData->SysRunTimeMs100++;
  }

  if(ON == pMChair->StateXMotor.Bit.Work)
  {
    pSaveData->XMotorRunTimeMs100++;
  }

  if(ON == pMChair->StateYMotor.Bit.Work)
  {
    pSaveData->YMotorRunTimeMs100++;
  }

  if(ON == pMChair->StateZMotor.Bit.Work)
  {
    pSaveData->ZMotorRunTimeMs100++;
  }

  if(ON == pMChair->StateTCSMotor.Bit.Work)
  {
    pSaveData->TCSMotorRunTimeMs100++;
  }

  if(ON == pMChair->StateBackSpike.Bit.Run)
  {
    pSaveData->BackSpikeMotorRunTimeMs100++;
  }

  if(ON == pMChair->StateZeroSpike.Bit.Run)
  {
    pSaveData->ZeroSpikeMotorRunTimeMs100++;
  }

  if(ON == pMChair->StateFeetSpike.Bit.Run)
  {
    pSaveData->FeetSpikeMotorRunTimeMs100++;
  }

  if(ON == pMChair->StateLegFlexSpike.Bit.Run)
  {
    pSaveData->LegFlexMotorRunTimeMs100++;
  }
}

/*
========================================================================================================================
*     保存数据功能函数表                           保存数据功能函数表                           保存数据功能函数表
========================================================================================================================
*/
#define  SAVEDATA_TICK_COUNT_BUF_NUM   1
static Ticker_t SaveData_TickCount[SAVEDATA_TICK_COUNT_BUF_NUM];

static const ESF_TmrExeFunc_t  SaveData_TmrExeFuncTab[] = 
{
  /*   执行函数              执行周期(ms)         时间计数变量*/
  {SaveData_Update,           100,             &SaveData_TickCount[0]}
};

#define  SAVEDATA_TMR_EXE_FUNC_TAB_NUM     TAB_NUM(SaveData_TmrExeFuncTab)


/*
************************************************************************************************************************
* 函数名称 : SaveData_Load                                                                                                         
* 功能描述 : 保存数据的加载                                                                                        
* 输入参数 : 无                                                                                  
* 返回参数 : 返回 保存数据 的结构体 的指针                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
SaveData_t* SaveData_Load(void)
{
  /*检测 SaveData_TmrExeFuncTab 功能函数表排列是否正确------------------------*/
  ESF_TmrExeFuncTabCheck(SaveData_TmrExeFuncTab, SAVEDATA_TMR_EXE_FUNC_TAB_NUM, SAVEDATA_TICK_COUNT_BUF_NUM);

  /*从存储器里加载数据-------------------------------------------------------*/
  SaveData_Read((uint8_t*)&pSaveData->Sync, sizeof(pSaveData->Sync));  /*读同步字*/
  if (pSaveData->Sync != 0x55AA)                                       /*同步字未写入，则表示EEPRom 为新的，尚未写入数据*/	
  {
    memset((uint8_t*)pSaveData, 0, sizeof(SaveData_t)); 
    pSaveData->Sync = 0x55AA;
    SaveData_WriteIDCode((uint8_t*)"TIT86062005290001", 17);           
    SaveData_Write((uint8_t*)pSaveData, sizeof(SaveData_t));           /*第一次 向EEPRom写入数据*/
  }
  else                                                                 /*同步字已经存在，则直接读出数据*/
  {
    SaveData_Read((uint8_t*)pSaveData, sizeof(SaveData_t));
  }

  if(pSaveData->ResetCount < 0xFFFF)
  {
    pSaveData->ResetCount++;                                           /*系统复位次数累计*/
  }

  return pSaveData;
}

/*
************************************************************************************************************************
* 函数名称 : SaveData_Handle                                                                                                         
* 功能描述 : 保存数据的处理                                                                                        
* 输入参数 : 无                                                                                  
* 返回参数 : 无                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SaveData_Handle(void)
{
  /*调度功能函数表------------------------------------------------*/
  ESF_TmrExeFuncScheduling(SaveData_TmrExeFuncTab, SAVEDATA_TMR_EXE_FUNC_TAB_NUM);
}


/*
************************************************************************************************************************
* 函数名称 : SaveData_CDPDataObjRx_0x3D                                                                                      
* 功能描述 : 0x3D 程序鉴别信息： 上位机查询软件信息用
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象中数据的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t SaveData_CDPDataObjRx_0x3D(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  memcpy(&pAckDU[CDP_DU_OFFSET_LEN], &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  memcpy(&pAckDU[CDP_DU_OFFSET_DATA], SoftIdentifyInfo, sizeof(SoftIdentifyInfo)-1);       /*拷贝程序鉴别信息内容*/
  pAckDU[CDP_DU_OFFSET_LEN] = 2 + sizeof(SoftIdentifyInfo)-1;
                                                                                           /*更新数据对象长度*/
  return pAckDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* 函数名称 : SaveData_CDPDataObjRx_0x3E                                                                                      
* 功能描述 : 0x3E电子序列码：上位机查询、烧写电子序列号用
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象中数据的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t SaveData_CDPDataObjRx_0x3E(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  memcpy(&pAckDU[CDP_DU_OFFSET_LEN], &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);

  if(CDP_CMD_QRY == Cmd)
  {
    pAckDU[CDP_DU_OFFSET_DATA+0] = SaveData_GetIDCodeWriteCount();
    pAckDU[CDP_DU_OFFSET_LEN] = SaveData_GetIDCode(&pAckDU[CDP_DU_OFFSET_DATA+1]) + 2 + 1;
  }
  else //if(CDP_CMD_SET_ACK == Cmd)
  {
    pAckDU[CDP_DU_OFFSET_LEN] = SaveData_WriteIDCode(&pRxDU[CDP_DU_OFFSET_DATA+1], pRxDU[CDP_DU_OFFSET_LEN] - 2 - 1);
  }
                                                                                            /*更新数据对象长度*/
  return pAckDU[CDP_DU_OFFSET_LEN];
}

