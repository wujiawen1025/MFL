/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: IAP.h                                                                                                        
**
**    功能描述:                                                                                                  
**
**    公    司：                                                                                                        
**
**    项目名称：                                                                                                        
**
**    平台信息：                                                                                                        
**
**    作    者：Hzy                                                                                                     
**
**    其他说明:                                                                                                        
**
**    修改记录: --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/

#ifndef  _IAP_C_
#define  _IAP_C_
/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "IAP.h"          
#include "CDP.h"          
#include "bsp_Cfg.h"          


/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/
#ifndef BSP_CFG_FLASH_PAGE_SIZE
  #error "Please define  BSP_CFG_FLASH_PAGE_SIZE  (in bsp_Cfg.h file)"                         /*请定Flash页大小*/
#endif

#ifndef BSP_CFG_BOOTLOADER_START_ADDR
  #error "Please define  BSP_CFG_BOOTLOADER_START_ADDR  (in bsp_Cfg.h file)"                   /*请定义IAP起始地址*/
#endif

#ifndef BSP_CFG_BOOTLOADER_END_ADDR
  #error "Please define  BSP_CFG_BOOTLOADER_END_ADDR  (in bsp_Cfg.h file)"                     /*请定义IAP结束地址*/
#endif

#ifndef BSP_CFG_UPDATE_OP_INFO_START_ADDR
  #error "Please define  BSP_CFG_UPDATE_OP_INFO_START_ADDR  (in bsp_Cfg.h file)"               /*请定义升级操作信息起始地址*/
#endif

#ifndef BSP_CFG_UPDATE_OP_INFO_END_ADDR
  #error "Please define  BSP_CFG_UPDATE_OP_INFO_END_ADDR  (in bsp_Cfg.h file)"                 /*请定义升级操作信结束地址*/
#endif

#ifndef BSP_CFG_APPLICATION_START_ADDR
  #error "Please define  BSP_CFG_APPLICATION_START_ADDR  (in bsp_Cfg.h file)"                  /*请定义Application起始地址*/
#endif

#ifndef BSP_CFG_APPLICATION_END_ADDR
  #error "Please define  BSP_CFG_APPLICATION_END_ADDR  (in bsp_Cfg.h file)"                    /*请定义Application结束地址*/
#endif

#define  IAP_FLASH_PAGE_SIZE                       BSP_CFG_FLASH_PAGE_SIZE                     /*Flash页大小*/

#define  BOOT_START_ADDR                           BSP_CFG_BOOTLOADER_START_ADDR               /*IAP起始地址*/
#define  BOOT_END_ADDR                             BSP_CFG_BOOTLOADER_END_ADDR                 /*IAP结束地址*/
#define  UPDATE_OP_INFO_START_ADDR                 BSP_CFG_UPDATE_OP_INFO_START_ADDR           /*升级操作信息起始地址*/
#define  UPDATE_OP_INFO_END_ADDR                   BSP_CFG_UPDATE_OP_INFO_END_ADDR             /*升级操作信结束地址*/
#define  APP_START_ADDR                            BSP_CFG_APPLICATION_START_ADDR              /*Application起始地址*/
#define  APP_END_ADDR                              BSP_CFG_APPLICATION_END_ADDR                /*Application结束地址*/
#define  APP_PAGE_SUM                              ((APP_END_ADDR-APP_START_ADDR+1)/IAP_FLASH_PAGE_SIZE)/*Application页总数*/


#define  IAP_DATA_BLK_SUM_PER_CDP                  4                                           /*每个数据包中最多可保含多少个块，根据单片机ram大小和实际通信情况决定*/  
#define  IAP_DATA_BLK_SIZE                         128                                         /*数据块大小，固定为128*/
#define  IAP_DATA_BLK_SUM_PER_PAGE                 (IAP_FLASH_PAGE_SIZE/IAP_DATA_BLK_SIZE)     /*每页内有多少个块*/  
#define  IAP_DATA_BLK_SUM                          (APP_PAGE_SUM*IAP_DATA_BLK_SUM_PER_PAGE)    /*数据块总数*/
#define  IAP_TIME_OUT_LIMIT_MS                     9000                                        /*通信超时时间，单位ms*/

#define  IAP_BP_BUF_SUM                            40                                          /*断点缓存总数，最大大小应根据实际配置进行估算*/ 
#define  IAP_BP_SAVE_PER_PAGE                      ((APP_PAGE_SUM/IAP_BP_BUF_SUM)+1)           /*多少个页保存一次断点，Flash只能按页擦除，因此断点最小单位为页的倍数*/ 
#define  IAP_BP_SAVE_PER_BLK                       (IAP_BP_SAVE_PER_PAGE*IAP_DATA_BLK_SUM_PER_PAGE) /*多少个数据块保存一次断点，Flash只能按页擦除，因此断点最小单位为页的倍数*/ 


#define  IAP_FLASH_OP_SYNC                         0xA5A5A5A5                                  /*操作同步标识*/ 

#define  IAP_FLOW_ERR                              CDP_DU_HANDLE_ERR                           /*流程错误*/ 



#define IAP_JUMP_TO_APP_WAIT_TIME                  600                                         /*跳转到应用程序前的等待时间，单位ms*/
#define IAP_RESET_WAIT_TIME                        100                                         /*执行复位操作前的等待时间，单位ms*/

/*
========================================================================================================================
*【本地数据类型定义】                              【本地数据类型定义】                              【本地数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  Flash更新升级操作信息。       
************************************************************************************************************************
*/
typedef struct  
{
  uint32_t        EraseSync;                                /*擦除同步标记，标识擦除是否成功*/

  uint32_t        FileCRC16RecSave;                         /*保存接收的文件CRC16校验码*/

  uint32_t        BreakPointWrStartSync[IAP_BP_BUF_SUM];    /*断点写操作同步标记 */
  uint32_t        BreakPointBuf[IAP_BP_BUF_SUM];            /*断点缓存*/
  uint32_t        BreakPointWrEndSync[IAP_BP_BUF_SUM];      /*断点写操作结束同步标记 */

  uint32_t        UpdateSuccessSync;                        /*更新成功 同步标记*/

}IAP_FlashUpdateOpInfo_t;

/*
************************************************************************************************************************
* 类型定义 :         
************************************************************************************************************************
*/
typedef struct  
{
  uint8_t        FlowStateLast;                             /*流程状态*/

  uint8_t        UpdateState;                               /*升级状态*/

  uint8_t        BlkNumErrCount;                            /*数据块号错误统计*/
  uint16_t       BlkLenRec;                                 /*收到的数据块长度*/
  uint16_t       BlkNumRec;                                 /*收到的数据块号*/
  uint16_t       BlkNumExpect;                              /*期望的数据块号*/

  uint8_t        BreakPointEn;                              /*断点使能*/
  uint16_t       FileCRC16Rec;                              /*接收的文件CRC16*/
  uint16_t       FileCRC16Cal;                              /*计算的文件CRC16*/

  uint32_t       ProgramAddr;                               /*编程地址*/

  uint16_t       LinkTimeOutMs;                             /*通信链接超时时间，单位1ms*/
  
  uint16_t       JumpToAppWaitTimeMs;                       /*跳转到应用程序前的等待时间，单位ms*/
  uint16_t       ResetWaitTimeMs;                           /*执行复位操作前的等待时间，单位ms*/

}IAP_t;

/*
************************************************************************************************************************
* 类型定义 :         
************************************************************************************************************************
*/
typedef  void (*pFunction)(void);


/*
************************************************************************************************************************
* 类型定义 :         
************************************************************************************************************************
*/
__packed typedef  struct
{
  uint8_t        CompanyName[20];                           /*Byte 0~19:  公司名称*/
  uint8_t        FileCRC16[2];                              /*Byte 20~21: 文件CRC16*/
}IAPFileHeaderInfo_t;
  


/*
========================================================================================================================
*【变量定义 & 各种声明】                          【变量定义 & 各种声明】                          【变量定义 & 各种声明】    
========================================================================================================================
*/
static  IAP_FlashUpdateOpInfo_t  *pFlashUpdateOpInfo = (IAP_FlashUpdateOpInfo_t*)UPDATE_OP_INFO_START_ADDR;
static  IAP_t                    IAP;
static  pFunction                Jump_To_Application;
static  IAPFileHeaderInfo_t      *pFileHeaderInfo;
/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : IAP_SetUpdateState                                                                                      
* 功能描述 : 设置升级状态                                                                                
* 输入参数 : State -- 状态，取值：IAP_UPDATE_STATE_ 开头的宏定义                                                                                             
* 返回参数 : 无                                                                                                    
* 补充说明 : 无
************************************************************************************************************************
*/
//static void IAP_SetUpdateState(uint8_t State)
//{
//  static uint8_t Seted = 0;
//  
//  if(0 == Seted)
//  {
//    IAP.UpdateState = State;
//    Seted = 1;    /*每次复位运行，只允许设置一次*/
//  }
//}


/*
************************************************************************************************************************
* 函数名称 : IAP_LinkTimeOutStart                                                                                      
* 功能描述 : 通信链接超时 启动                                                                            
* 输入参数 : ExePeriod -- 函数的执行周期                                                      
* 返回参数 : 无                                                                                                    
* 补充说明 : 无
************************************************************************************************************************
*/
__inline void IAP_LinkTimeOutStart(void)
{
  IAP.LinkTimeOutMs = 1;     /*超时时间大于0，即代表启动了*/  
}

/*
************************************************************************************************************************
* 函数名称 : IAP_LinkTimeOutCheckRun                                                                                      
* 功能描述 : 通信链接超时 检测                                                                          
* 输入参数 : ExePeriod -- 函数的执行周期                                                      
* 返回参数 : 无                                                                                                    
* 补充说明 : 无
************************************************************************************************************************
*/
void IAP_LinkTimeOutCheck(Ticker_t ExePeriod)
{
//  if(IAP.LinkTimeOutMs)                                    /*超时时间大于0，即代表启动了*/  
//  {
//    if(IAP.LinkTimeOutMs < IAP_TIME_OUT_LIMIT_MS)
//    {
//      IAP.LinkTimeOutMs += ExePeriod;
//    }
//    else
//    {
//      IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_TIMEOUT);   /*升级失败，接收超时*/
//    }
//  }  
}

/*
************************************************************************************************************************
* 函数名称 : IAP_LinkTimeOutResetTime                                                                                      
* 功能描述 : 通信链接超时  复位时间                                                                   
* 输入参数 : 无                                                     
* 返回参数 : 无                                                                                                    
* 补充说明 : 无
************************************************************************************************************************
*/
void IAP_LinkTimeOutResetTime(void)
{
  if(IAP.LinkTimeOutMs > 0) /*超时器已经启动*/
  {
    IAP.LinkTimeOutMs = 1;  /*设置时间到一个合适的最小值*/                            
  }
}


/*
************************************************************************************************************************
* 函数名称 : IAP_CDPDataObj_0x01                                                                                      
* 功能描述 : 通知目标模块进入IAP模式                                                                                 
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t IAP_CDPDataObj_0x01(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
//  IAP.UpdateState = IAP_UPDATE_STATE_NONE;
//  
//  if(IAP.FlowStateLast != 0x00)
//  {
//    IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_OTHER);      /*升级失败，其他原因导致*/
//    return IAP_FLOW_ERR;
//  }
//  
//  IAP_LinkTimeOutStart();
//  IAP.FlowStateLast = 0x01;
//  return 2;
}

/*
************************************************************************************************************************
* 函数名称 : IAP_CDPDataObj_0x02                                                                                      
* 功能描述 : 获取目标模块的相关升级配置信息                                                                                 
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t IAP_CDPDataObj_0x02(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
//  uint8_t *wp;

//  IAP_LinkTimeOutResetTime();
//  
//  if(IAP.FlowStateLast != 0x01)
//  {
//    IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_OTHER);      /*升级失败，其他原因导致*/
//    return IAP_FLOW_ERR;
//  }
//  
//  wp = &pAckDU[CDP_DU_OFFSET_DATA];
//  *wp++ = IAP_DATA_BLK_SUM & 0xFF;                        /*可用数据块数量*/
//  *wp++ = IAP_DATA_BLK_SUM >> 8;
//  *wp++ = IAP_DATA_BLK_SUM_PER_CDP;                       /*每个数据包中最多可包含多少个块*/
//  
//  IAP.FlowStateLast = 0x02;
//  return (wp - &pAckDU[CDP_DU_OFFSET_DATA] + 2);
}

/*
************************************************************************************************************************
* 函数名称 : IAP_CDPDataObj_0x03                                                                                      
* 功能描述 : 通知目标模块准备好接收文件                                                                                 
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t IAP_CDPDataObj_0x03(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
//  uint8_t i;
//  uint8_t *wp;
//  uint8_t OpResult;
//  
//  IAP_LinkTimeOutResetTime();
//  
//  if(IAP.FlowStateLast != 0x02)
//  {
//    IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_OTHER);                       /*升级失败，其他原因导致*/
//    return IAP_FLOW_ERR;
//  }

//  IAP.BlkNumExpect = 0;                                                    /*先假设断点为0*/
//  do
//  {
//    pFileHeaderInfo = (IAPFileHeaderInfo_t*)&pRxDU[CDP_DU_OFFSET_DATA+0];
//    
//    if(memcmp(pFileHeaderInfo->CompanyName, "EASEPAL", 7) != 0 )
//    {
//      IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_COMPANY);                   /*升级失败，文件头信息中的公司名称错误。*/
//      break;
//    }
//    
//    IAP.FileCRC16Rec   = pFileHeaderInfo->FileCRC16[1];  
//    IAP.FileCRC16Rec <<= 8;
//    IAP.FileCRC16Rec  |= pFileHeaderInfo->FileCRC16[0];  
//    IAP.BreakPointEn   = pRxDU[CDP_DU_OFFSET_DATA+128];
//    
//    if((pFlashUpdateOpInfo->EraseSync != IAP_FLASH_OP_SYNC)      ||          /*没擦除的要擦除*/     
//       (pFlashUpdateOpInfo->FileCRC16RecSave != IAP.FileCRC16Rec)||          /*文件CRC不匹配，则擦除所有信息*/
//       (IAP.BreakPointEn != TRUE)                                )           /*不使用断点续传功能，则擦除所有信息*/                           
//    {
//      OpResult = SUCCESS;                                                    /*先假设成功*/
//      OpResult |= BSP_FLASH_Erase(UPDATE_OP_INFO_START_ADDR, 1);
//      OpResult |= BSP_FLASH_ProgramWord((uint32_t)&pFlashUpdateOpInfo->EraseSync, IAP_FLASH_OP_SYNC);        /*标识擦除成功*/
//      OpResult |= BSP_FLASH_ProgramWord((uint32_t)&pFlashUpdateOpInfo->FileCRC16RecSave, IAP.FileCRC16Rec);  /*保存文件CRC*/
//      if(OpResult != SUCCESS)
//      {
//        IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_FLASH);                     /*升级失败，Flash操作异常*/
//        break;
//      }
//    }
//    else /*使用断点续传功能*/
//    {
//      if(IAP_FLASH_OP_SYNC == pFlashUpdateOpInfo->UpdateSuccessSync)         /*该文件已经成功更新了*/
//      {
//        IAP_SetUpdateState(IAP_UPDATE_STATE_SUCCESS);                        /*升级成功*/
//        IAP.FlowStateLast = 0x05;                                            /*不必重复升级了*/
//      }
//      else
//      {
//        for(i=IAP_BP_BUF_SUM; i>0; i--)                                      /*最后保存的断点信息保存位置越靠后，因此从后向前遍历查找*/                      
//        {
//          if(IAP_FLASH_OP_SYNC == pFlashUpdateOpInfo->BreakPointWrEndSync[i-1]) 
//          {
//            IAP.BlkNumExpect = pFlashUpdateOpInfo->BreakPointBuf[i-1];       /*断点有效时，使用断点作为下一个期望接收的数据块序号*/
//            break;
//          }  
//        }
//      }
//    }
//    IAP.ProgramAddr = APP_START_ADDR + (IAP.BlkNumExpect*IAP_DATA_BLK_SIZE); /*根据断点，定位编程地址*/
//    
//  }while(0);
//  
//  
//  wp = &pAckDU[CDP_DU_OFFSET_DATA];
//  *wp++ = IAP.BlkNumExpect & 0xFF;                                        
//  *wp++ = IAP.BlkNumExpect >> 8;
//  
//  IAP.FlowStateLast = 0x03;
//  return (wp - &pAckDU[CDP_DU_OFFSET_DATA] + 2);
}

/*
************************************************************************************************************************
* 函数名称 : IAP_CDPDataObj_0x04                                                                                      
* 功能描述 : 文件数据块信息                                                                                
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t IAP_CDPDataObj_0x04(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
//  uint8_t OpResult;
//  uint8_t i;
//  uint8_t *wp;

//  IAP_LinkTimeOutResetTime();

//  if((IAP.FlowStateLast != 0x03) && 
//     (IAP.FlowStateLast != 0x04)) 
//  {
//    IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_OTHER);                                 /*升级失败，其他原因导致*/
//    return IAP_FLOW_ERR;
//  }
//  
//  IAP.BlkLenRec   = pRxDU[CDP_DU_OFFSET_LEN] - 4;
//  IAP.BlkNumRec   = pRxDU[CDP_DU_OFFSET_DATA+1];
//  IAP.BlkNumRec <<= 8;
//  IAP.BlkNumRec  |= pRxDU[CDP_DU_OFFSET_DATA+0];

//  if(IAP.BlkNumRec != IAP.BlkNumExpect) 
//  {
//    if(IAP.BlkNumErrCount++ > 5)                                                     /*累计超过一定次数的数据块序号需求错误，则相关设置升级状态*/
//    {
//      IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_BLKNUM);                              /*升级失败，数据块序号错误，防止上位机重复一直发送同一块数据*/
//    }
//  } 
//  else
//  {
//    IAP.BlkNumErrCount = 0;                                                          /*清块号错误统计*/
//    
//    if(0 == ((IAP.ProgramAddr-APP_START_ADDR) % IAP_FLASH_PAGE_SIZE))                /*页对齐的地址则擦除页*/ 
//    {
//      OpResult = BSP_FLASH_Erase(IAP.ProgramAddr, 1);                                /*擦除要编程的页*/
//      if(OpResult != SUCCESS)
//      {
//        IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_FLASH);                             /*升级失败，Flash操作异常*/
//      }
//    }
//    
//    OpResult = BSP_FLASH_ProgramData(IAP.ProgramAddr, &pRxDU[CDP_DU_OFFSET_DATA+2], IAP.BlkLenRec);    /*编程数据块*/
//    if(OpResult != SUCCESS)
//    {
//      IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_FLASH);                               /*升级失败，Flash操作异常*/
//    }
//    else                                                                             /*正确编程完数据*/
//    {
//      IAP.ProgramAddr += IAP.BlkLenRec;
//      IAP.BlkNumExpect++;                                                            /*更新下一个期望接收的数据块序号*/  
//      if((0 == (IAP.BlkNumExpect % IAP_BP_SAVE_PER_BLK)) &&                          /*判断是否可保存断点。*/
//         (IAP_DATA_BLK_SIZE == IAP.BlkLenRec))                                       /*如果不等于固定块长，则表示最后一块数据，后续的断点不必保存了*/
//      {
//        for(i=0; i<IAP_BP_BUF_SUM; i++)
//        {
//          if(0xFFFFFFFF == pFlashUpdateOpInfo->BreakPointWrStartSync[i])             /*该存储空间还未被写入*/
//          {
//            OpResult = SUCCESS;                                                      /*先假设成功*/
//            OpResult |= BSP_FLASH_ProgramWord((uint32_t)&pFlashUpdateOpInfo->BreakPointWrStartSync[i], IAP_FLASH_OP_SYNC); /*标识开始保存断点*/
//            OpResult |= BSP_FLASH_ProgramWord((uint32_t)&pFlashUpdateOpInfo->BreakPointBuf[i], IAP.BlkNumExpect);          /*保存文件断点*/
//            OpResult |= BSP_FLASH_ProgramWord((uint32_t)&pFlashUpdateOpInfo->BreakPointWrEndSync[i], IAP_FLASH_OP_SYNC);   /*标识结束保存断点*/
//            if(OpResult != SUCCESS)
//            {
//              IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_FLASH);                       /*升级失败，Flash操作异常*/
//            } 
//            break;
//          }
//        }
//      }    
//    }
//  }     
//  wp = &pAckDU[CDP_DU_OFFSET_DATA];
//  *wp++ = IAP.BlkNumExpect & 0xFF;    
//  *wp++ = IAP.BlkNumExpect >> 8;
//  
//  IAP.FlowStateLast = 0x04;
//  return (wp - &pAckDU[CDP_DU_OFFSET_DATA] + 2);
}

/*
************************************************************************************************************************
* 函数名称 : IAP_CDPDataObj_0x05                                                                                      
* 功能描述 : 文件数据块传输结束                                                                                
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t IAP_CDPDataObj_0x05(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
//  uint8_t OpResult;
//  uint8_t *rp;
//  uint8_t *wp;
//  
//  IAP_LinkTimeOutResetTime();

//  if(IAP.FlowStateLast != 0x04) 
//  {
//    IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_OTHER);                    /*升级失败，其他原因导致*/
//    return IAP_FLOW_ERR;
//  }

//  rp = (uint8_t *)APP_START_ADDR;
//  IAP.FileCRC16Cal = CRC16_Cal(rp, (IAP.ProgramAddr - APP_START_ADDR), 0x00);
//  if(IAP.FileCRC16Cal != IAP.FileCRC16Rec)
//  {
//    IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_FILECRC);                  /*升级失败，文件CRC不匹配*/
//    BSP_FLASH_Erase(UPDATE_OP_INFO_START_ADDR, 1);                      /*擦除已保存的相关操作信息*/ 
//    BSP_FLASH_ProgramWord((uint32_t)&pFlashUpdateOpInfo->EraseSync, IAP_FLASH_OP_SYNC);  /*标识擦除成功*/
//  }
//  else
//  {
//    OpResult = BSP_FLASH_ProgramWord((uint32_t)&pFlashUpdateOpInfo->UpdateSuccessSync, IAP_FLASH_OP_SYNC); /*标识升级成功*/
//    if(OpResult != SUCCESS)
//    {
//      IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_FLASH);                  /*升级失败，Flash操作异常*/
//    } 
//    else
//    {
//      IAP_SetUpdateState(IAP_UPDATE_STATE_SUCCESS);                     /*升级成功*/
//    }
//  }

//  wp = &pAckDU[CDP_DU_OFFSET_DATA];
//  *wp++ = IAP.FileCRC16Cal & 0xFF;    
//  *wp++ = IAP.FileCRC16Cal >> 8;
//  
//  IAP.FlowStateLast = 0x05;
//  return (wp - &pAckDU[CDP_DU_OFFSET_DATA] + 2);
}

/*
************************************************************************************************************************
* 函数名称 : IAP_CDPDataObj_0x10                                                                                      
* 功能描述 : 取消软件升级                                                                                
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t IAP_CDPDataObj_0x10(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
//  IAP_LinkTimeOutResetTime();
//  IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_CANCEL);                       /*升级失败，上位机取消升级*/
//  return 2;
}

/*
************************************************************************************************************************
* 函数名称 : IAP_CDPDataObj_0x20                                                                                      
* 功能描述 : 获取升级状态                                                                                
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t IAP_CDPDataObj_0x20(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
//  uint8_t *wp;

//  IAP_LinkTimeOutResetTime();

//  wp = &pAckDU[CDP_DU_OFFSET_DATA];
//  *wp++ = IAP.UpdateState;
//  
//  return (wp - &pAckDU[CDP_DU_OFFSET_DATA] + 2);
}


/*
************************************************************************************************************************
* 函数名称 : IAP_JumpToAppSection                                                                                      
* 功能描述 : 跳转到应用程序区域                                                                                
* 输入参数 : 无                                                                                               
* 返回参数 : FAIL -- 跳转失败                                                                                                    
* 补充说明 : 无
************************************************************************************************************************
*/

uint8_t tt;
uint8_t IAP_JumpToAppSection(void)
{
  uint32_t JumpAddress;

//  if(IAP_FLASH_OP_SYNC == pFlashUpdateOpInfo->EraseSync)
//  {
//    if(pFlashUpdateOpInfo->UpdateSuccessSync != IAP_FLASH_OP_SYNC)
//    {
//      return FAIL;                                            /*如果有擦除操作，升级却没成功，则返回失败*/
//    }
//  }

  /*判断应用程序区的堆栈地址是否落在:0x0x08000000~0x0803FFFF中，这个区间的大小为256K。即程序是否已经下载*/
  if (((*(__IO uint32_t*)APP_START_ADDR) & 0x2FFE0000 ) == 0x20000000)
  {
    /*跳转前关中断，很重要。否则可能造成跳转时，刚好发生某个中断，跳转时进入的是App程序区的中断向量表，
      而此时App程序区还没开始初始化好，造成错误的数据判断或处理，甚至造中断成死循环*/
    BSP_DisInttrupt();                                        /*跳转前关中断，很重要。*/
    //BSP_UART_DeInit();
    JumpAddress = *(__IO uint32_t*) (APP_START_ADDR + 4);     /*计算跳转地址*/
    Jump_To_Application = (pFunction) JumpAddress;            /*将跳转地址赋给函数指针变量*/
    SCB->VTOR = APP_START_ADDR;                               /*重定位向量表*/
    __set_MSP(*(__IO uint32_t*) APP_START_ADDR);              /*初始化用户程序的堆栈指针*/
    Jump_To_Application();                                    /*跳转到应用程序区执行*/
  }

  return FAIL;
}

/*
************************************************************************************************************************
* 函数名称 : IAP_RunSectionJudge                                                                                                         
* 功能描述 : 运行区判断                                                                                  
* 输入参数 : 无                                                                                  
* 返回参数 : 无                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void IAP_RunSectionJudge(Ticker_t ExePeriod)
{
//  uint8_t  temp[3] = {3, 0x20, IAP_UPDATE_STATE_NO_FIRMWARE};
//  uint8_t *DUBuf[1];    /*指针数组，数组内的指针指向保存DU数据(应该包含数据长度和数据ID) 的内存地址。*/
//  
//  if(IAP.UpdateState != IAP_UPDATE_STATE_NONE)                        /*升级有了结果，即执行了IAP操作*/
//  {
//    if(IAP.ResetWaitTimeMs < IAP_RESET_WAIT_TIME)
//    {
//      IAP.ResetWaitTimeMs += ExePeriod;
//    }
//    else
//    {
//      NVIC_SystemReset();                                             /*有结果后，延迟一小段时间复位系统*/
//    }
//  }
//  else //if(State == IAP_UPDATE_STATE_NONE)                           /*没有执行IAP操作*/
//  {
//    if(IAP.JumpToAppWaitTimeMs < IAP_JUMP_TO_APP_WAIT_TIME)           /*跳转前的等待*/
//    {
//      IAP.JumpToAppWaitTimeMs += ExePeriod;
//    }
//    else
//    {
//      if(FAIL == IAP_JumpToAppSection())                              /*跳转*/
//      {
//        DUBuf[0] = temp;
//        CDP_PDUPackTx(CDP_ADDR_CTR, CDP_CMD_UPREPORT, DUBuf, 1);      /*主动上报 ID为0x20，数据0x10：设备无可运行的固件，请对设备进行升级操作。*/
//      }
//    }
//  }
}


/*
************************************************************************************************************************
* 函数名称 :                                                                                       
* 功能描述 :                                                                                 
* 输入参数 :                                                                                                
* 返回参数 :                                                                                                     
* 补充说明 : 
************************************************************************************************************************
*/
void IAP_Handle(void)
{
//  Ticker_t lag;
//  static Ticker_t  TickCount;
//  
//  lag = BSP_SysTicker_CalLag(TickCount);     /*计算时间差*/
//  if(lag >= 100)                             /*时间差值 大于等于 执行周期*/
//  {
//    TickCount += lag;
//    IAP_RunSectionJudge(100);
//    IAP_LinkTimeOutCheck(100);
//  }
}


#endif
