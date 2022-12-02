/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: bsp_flash.c                                                                                                        
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

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp_flash.h"          


/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/
#ifndef BSP_CFG_FLASH_PAGE_SIZE
  #error "Please define  BSP_CFG_FLASH_PAGE_SIZE  (in bsp_Cfg.h file)"                    /*请定义FLASH页的大小*/
#endif


#define  FLASH_PAGE_SIZE                BSP_CFG_FLASH_PAGE_SIZE                           /*页大小*/


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

/*
************************************************************************************************************************
* 函数名称 : STMFLASH_GetFlashSector                                                                                      
* 功能描述 : 获取某个地址所在的flash扇区                                                                               
* 输入参数 : addr -- flash地址
* 返回参数 : 0~11,即addr所在的扇区
* 补充说明 : 
************************************************************************************************************************
*/
//uint16_t STMFLASH_GetFlashSector(uint32_t addr)
//{
//  if(addr<ADDR_FLASH_SECTOR_1)return FLASH_Sector_0;
//  else if(addr<ADDR_FLASH_SECTOR_2)return FLASH_Sector_1;
//  else if(addr<ADDR_FLASH_SECTOR_3)return FLASH_Sector_2;
//  else if(addr<ADDR_FLASH_SECTOR_4)return FLASH_Sector_3;
//  else if(addr<ADDR_FLASH_SECTOR_5)return FLASH_Sector_4;
//  else if(addr<ADDR_FLASH_SECTOR_6)return FLASH_Sector_5;
//  else if(addr<ADDR_FLASH_SECTOR_7)return FLASH_Sector_6;
//  else if(addr<ADDR_FLASH_SECTOR_8)return FLASH_Sector_7;
//  else if(addr<ADDR_FLASH_SECTOR_9)return FLASH_Sector_8;
//  else if(addr<ADDR_FLASH_SECTOR_10)return FLASH_Sector_9;
//  else if(addr<ADDR_FLASH_SECTOR_11)return FLASH_Sector_10;
//  return FLASH_Sector_11;	  
//};

/*
************************************************************************************************************************
* 函数名称 : BSP_FLASH_Erase                                                                                      
* 功能描述 : Flash擦除操作                                                                                
* 输入参数 : PageAddress -- 擦除的页地址
*            PageSum     -- 要擦除的页数量
* 返回参数 : FAIL    -- 编程失败
*            SUCCESS -- 编程成功
* 补充说明 : 
************************************************************************************************************************
*/
uint16_t BSP_FLASH_Erase(uint32_t PageAddress)
{
//  uint16_t      Page;
//  uint32_t      EraseAddr;
  uint16_t      FlashStatus;
  
  if(PageAddress<BSP_CFG_FLASH_START_ADDR)
  {
    return FAIL;                                               /* 非法地址 */
  }
  
  BSP_DisInttrupt(); 
  fmc_unlock();                                              /* 解锁 */
  
  fmc_flag_clear(FMC_FLAG_BANK0_END | FMC_FLAG_BANK0_WPERR | FMC_FLAG_BANK0_PGERR );
  FlashStatus = fmc_page_erase(PageAddress);
  fmc_flag_clear(FMC_FLAG_BANK0_END | FMC_FLAG_BANK0_WPERR | FMC_FLAG_BANK0_PGERR );

  fmc_lock();                                                /* 上锁 */
  BSP_EnInttrupt();
  
  if(FMC_READY == FlashStatus )
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
* 函数名称 : BSP_FLASH_ProgramWord                                                                                      
* 功能描述 : Flash编程字操作                                                                                
* 输入参数 : ProAddr -- 编程的起始地址
*            Data    -- 要编程的数据
* 返回参数 : FAIL    -- 编程失败
*            SUCCESS -- 编程成功
* 补充说明 : 
************************************************************************************************************************
*/
uint16_t BSP_FLASH_ProgramWord(uint32_t ProAddr, uint32_t Data)
{
  uint16_t  FlashStatus;
  
  BSP_DisInttrupt();  
  fmc_unlock();                                   /* 解锁 */
  
  FlashStatus = fmc_word_program(ProAddr, Data);
  fmc_flag_clear(FMC_FLAG_BANK0_END | FMC_FLAG_BANK0_WPERR | FMC_FLAG_BANK0_PGERR );
  
  fmc_lock();                                     /* 上锁 */
  BSP_EnInttrupt();
  
  if(FMC_READY == FlashStatus )
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
* 函数名称 : BSP_FLASH_ProgramData                                                                                      
* 功能描述 : Flash编程数据操作                                                                                
* 输入参数 : ProAddr -- 编程的起始地址
*            pData   -- 指向要编程的数据
*            DataLen -- 要编程的数据长度
* 返回参数 : FAIL    -- 编程失败
*            SUCCESS -- 编程成功
* 补充说明 : 
************************************************************************************************************************
*/
uint16_t BSP_FLASH_ProgramData(uint32_t ProAddr, void *pData, uint16_t DataLen)
{
  uint32_t WriteAddr;
  uint32_t TmpData;
  uint8_t *rp, *wp;
  uint16_t  FlashStatus;


  BSP_DisInttrupt();  
  fmc_unlock();                                   /* 解锁 */
  
  rp = pData;
  WriteAddr = ProAddr;
  while(WriteAddr < (ProAddr+DataLen))
  {
    /***************************************************************************************
     * 注意：这里之所以这么麻烦，原因是pDada指向的地址不一定是4字节对齐的。
     * 它可能指向类型uint8_t的数组，而该数组的首地址如果刚好是1字节对齐的。此时如果直接使用类似如下的代码：
     *   uint32_t *rp;
     *   rp = pDada;
     *   FLASH_ProgramWord(WriteAddr, *rp);   
     * 则由于参数*rp指向uint32_t类型，要求地址4字节对齐，可实际情况却是指向非4字节对齐地址，
     * 此时该代码的执行将造成HardFault_Handler异常。这种异常现象的原因是使用不对齐的方式对内存进行访问。
     * 因此这里增加好几步的数据转换工作，以应对这种地址非对齐情况。
     * 同理：如果参数*rp指向uint16_t类型，要求地址2字节对齐。可用类似的方法转换。  
     * 扩展联系：以前使用OS的内存块时，OS内部使用单片机的最大位宽为类型定义数组（32位就定义为uint32_t类型数组）。
     *           然后上层应用可使用内存块进行任意的指针类型强制转换，不会造成非对齐访问异常。
     *           因为4字节对齐的地址必定也是2字节对齐的，任何地址必定是1字节对齐的。因此这些类型能相互正常转换。
     *           试想如果OS内部使用uint8_t类型数组的话，在指针强制转换时，必定容易出现非对齐访问的异常。
     ***************************************************************************************/
    wp = (uint8_t*)&TmpData;
    *wp++ = *rp++;
    *wp++ = *rp++;
    *wp++ = *rp++;
    *wp++ = *rp++;
      
    FlashStatus = fmc_word_program(WriteAddr, TmpData);
    fmc_flag_clear(FMC_FLAG_BANK0_END | FMC_FLAG_BANK0_WPERR | FMC_FLAG_BANK0_PGERR );
    if(FlashStatus != FMC_READY)
    {
      fmc_lock();                                  /* 上锁 */
      BSP_EnInttrupt();
      return FAIL;   
    }
    WriteAddr += 4;
  }

  fmc_lock();                                     /* 上锁 */
  BSP_EnInttrupt();
  
  return SUCCESS;
}
