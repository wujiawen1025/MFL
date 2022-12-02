/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: bsp_feep.c                                                                                                        
**
**    功能描述: 使用Flash模拟EEPROM                                                                                                        
**
**    公    司:                                                                                                       
**
**    项目名称:                                                                                                       
**
**    平台信息:                                                                                                        
**
**    作    者: LZH                                                                                                     
**
**    其他说明:                                                                                                         
**
**    修改记录: --------------------------------------------------------------
**              2016.08    
**              完成 V1.0 版本
**
========================================================================================================================
========================================================================================================================
*/

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp_feep.h"          



/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/
#ifndef BSP_CFG_FLASH_PAGE_SIZE
  #error "Please define  BSP_CFG_FLASH_PAGE_SIZE  (in bsp_Cfg.h file)"                    /*请定义FLASH页的大小*/
#endif

#ifndef BSP_CFG_FLASH_END_ADDR
  #error "Please define  BSP_CFG_FLASH_END_ADDR  (in bsp_Cfg.h file)"                     /*请定义FLASH的结束地址*/
#endif


#define  FEEP_PAGE_SIZE                 BSP_CFG_FLASH_PAGE_SIZE                           /*页大小*/
#define  FEEP_START_ADDRESS             ((BSP_CFG_FLASH_END_ADDR+1) - (FEEP_PAGE_SIZE*2)) /*Flash模式EEP的起始地址，最后两页用作模拟EEP */


#define  FEEP_PAGE0_START_ADDR          (FEEP_START_ADDRESS + 0)                          /*模拟EEP页0起始地址*/ //0x0803EFFF
#define  FEEP_PAGE0_END_ADDR            (FEEP_PAGE0_START_ADDR + (FEEP_PAGE_SIZE - 1))    /*模拟EEP页0结束地址*/
#define  FEEP_PAGE1_START_ADDR          (FEEP_PAGE0_END_ADDR + 1)                         /*模拟EEP页1起始地址*/ //0x0803F7FF
#define  FEEP_PAGE1_END_ADDR            (FEEP_PAGE1_START_ADDR + (FEEP_PAGE_SIZE - 1))    /*模拟EEP页1结束地址*/


#define  FEEP_OP_SYNC                   0xA5A5A5A5                                        /*操作同步标识*/ 


#ifndef  BSP_CFG_FEEP_BLK_SIZE
#define  BSP_CFG_FEEP_BLK_SIZE          128                                               /*要保存的数据块大小,单位字节*/ 
#endif


/*根据芯片的实际情况调整数据块的大小，和页内能够支持的数据块数量*/
#if (FEEP_PAGE_SIZE == 512)                            
  #if (BSP_CFG_FEEP_BLK_SIZE <= 64)
    #define  FEEP_BLK_SIZE              64                                                
    #define  FEEP_BLK_SUM               6                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 128)
    #define  FEEP_BLK_SIZE              128                                                
    #define  FEEP_BLK_SUM               3                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 256)
    #define  FEEP_BLK_SIZE              256                                                
    #define  FEEP_BLK_SUM               1                                                 
  #else 
    #define  FEEP_BLK_SIZE              480                                              
    #define  FEEP_BLK_SUM               1                                                 
  #endif

#elif (FEEP_PAGE_SIZE == 1024)                            
  #if (BSP_CFG_FEEP_BLK_SIZE <= 64)
    #define  FEEP_BLK_SIZE              64                                                
    #define  FEEP_BLK_SUM               12                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 128)
    #define  FEEP_BLK_SIZE              128                                                
    #define  FEEP_BLK_SUM               6                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 256)
    #define  FEEP_BLK_SIZE              256                                                
    #define  FEEP_BLK_SUM               3                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 512)
    #define  FEEP_BLK_SIZE              512                                               
    #define  FEEP_BLK_SUM               1                                                 
  #else 
    #define  FEEP_BLK_SIZE              960                                              
    #define  FEEP_BLK_SUM               1                                                 
  #endif
  
#elif (FEEP_PAGE_SIZE == 2048)
  #if (BSP_CFG_FEEP_BLK_SIZE <= 64)
    #define  FEEP_BLK_SIZE              64                                                
    #define  FEEP_BLK_SUM               26                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 128)
    #define  FEEP_BLK_SIZE              128                                                
    #define  FEEP_BLK_SUM               14                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 256)
    #define  FEEP_BLK_SIZE              256                                                
    #define  FEEP_BLK_SUM               7                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 512)
    #define  FEEP_BLK_SIZE              512                                               
    #define  FEEP_BLK_SUM               3                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 1024)
    #define  FEEP_BLK_SIZE              1024                                               
    #define  FEEP_BLK_SUM               1                                                 
  #else 
    #define  FEEP_BLK_SIZE              1984                                              
    #define  FEEP_BLK_SUM               1                                                 
  #endif
#else  //128*1024
  #if (BSP_CFG_FEEP_BLK_SIZE <= 64)
    #define  FEEP_BLK_SIZE              64                                                
    #define  FEEP_BLK_SUM               120                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 128)
    #define  FEEP_BLK_SIZE              128                                                
    #define  FEEP_BLK_SUM               60                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 256)
    #define  FEEP_BLK_SIZE              256                                                
    #define  FEEP_BLK_SUM               30                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 512)
    #define  FEEP_BLK_SIZE              512                                               
    #define  FEEP_BLK_SUM               10                                                 
  #else 
    #define  FEEP_BLK_SIZE              960                                              
    #define  FEEP_BLK_SUM               10                                                 
  #endif
    
#endif



/*
========================================================================================================================
*【本地数据类型定义】                              【本地数据类型定义】                              【本地数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 : Flash模拟EEP             
* 注意1：Flash编程一次至少半字(2字节)，因此结构体内除数组外的变量最小类型为2字节类型，以保证至少2字节对齐。
*        为保证较好的通用性，所有变量全部定义为4字节大小的类型（有的芯片编程一次至少全字4字节，如飞思卡尔的KE）。
* 注意2：Flash的主要特性是只能页擦除，擦除完成后可执行半字或字编程操纵，
*        但每个地址单元只能执行一次，若要执行第二次编程操纵，则必须重新擦除。
*        对Flash的操作，最可能引起故障的就是突然掉电，导致操作失败。
*        因此要对在操作过程中出现的电源掉电等会引起故障的事件做处理。
*        所以结构体内有许多同步标记，用来标识相应的操作是否成功完成。 
* 注意3：代码中的FlashStatus状态判断其实没多大意义。除非Flash达到使用寿命或其他原因故障。
*        其他的代码与逻辑主要是利用双页与页内多数据块轮替算法提高Flash的使用寿命，
*        还有就是同步标记应对掉电故障造成的Flash操作失败。
************************************************************************************************************************
*/
typedef struct  
{
  uint32_t        ActiveCount;                              /*活动计数，32位的计数值，数值大的代表当前活动页 */
  uint32_t        EraseSync;                                /*擦除同步标记，标识擦除是否成功*/

  uint32_t        WrStartSync[FEEP_BLK_SUM];                /*写操作开始同步标记 */
  uint32_t        WrEndSync[FEEP_BLK_SUM];                  /*写操作结束同步标记 */
  uint32_t        Block[FEEP_BLK_SUM][FEEP_BLK_SIZE/4];     /*数据存储块，数值类型定义为uint32_t，然后大小FEEP_BLK_SIZE/4，保证4字节对齐。*/
}BSP_FlashEEP_t;


/*
========================================================================================================================
*【变量定义 & 各种声明】                          【变量定义 & 各种声明】                          【变量定义 & 各种声明】    
========================================================================================================================
*/
static BSP_FlashEEP_t  *pFEEPPage0 = (BSP_FlashEEP_t*)FEEP_PAGE0_START_ADDR;
static BSP_FlashEEP_t  *pFEEPPage1 = (BSP_FlashEEP_t*)FEEP_PAGE1_START_ADDR;

static BSP_FlashEEP_t  *pFEEPPageActive;    /*当前活动的页*/

/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : BSP_FEEP_Init                                                                                      
* 功能描述 : Flash模拟EEP初始化                                                                                               
* 输入参数 : 无                                                                                               
* 返回参数 : Flash的操作结果                                                                                                         
* 补充说明 : 该函数内的判断与处理逻辑主要用于对掉电引起的故障页或第一次使用页，进行恢复工作（即擦除和写入相关初始数据）。                                                                                                        
************************************************************************************************************************
*/
uint16_t BSP_FEEP_Init(void)
{
  uint16_t  FlashStatus;
  
  BSP_DisInttrupt();  

  pFEEPPageActive = (void*)0;
  do
  {
    if(pFEEPPage0->EraseSync != FEEP_OP_SYNC)                                              /*没擦除的要擦除*/     
    {
      FlashStatus = BSP_FLASH_Erase(FEEP_PAGE0_START_ADDR);
      if (FlashStatus != SUCCESS)
      {
        break;
      }

      FlashStatus = BSP_FLASH_ProgramWord((uint32_t)&pFEEPPage0->EraseSync, FEEP_OP_SYNC);/*标识擦除成功*/
      if (FlashStatus != SUCCESS)
      {
        break;
      }
    }

    if(pFEEPPage1->EraseSync != FEEP_OP_SYNC)                                              /*没擦除的要擦除*/            
    {
      FlashStatus = BSP_FLASH_Erase(FEEP_PAGE1_START_ADDR);
      if (FlashStatus != SUCCESS)
      {
        break;
      }
      
      FlashStatus = BSP_FLASH_ProgramWord((uint32_t)&pFEEPPage1->EraseSync, FEEP_OP_SYNC);/*标识擦除成功*/
      if (FlashStatus != SUCCESS)
      {
        break;
      }
    }

    if(0xFFFFFFFF == pFEEPPage0->ActiveCount)                                              /*活动计数无效*/ 
    {
      FlashStatus = BSP_FLASH_ProgramWord((uint32_t)&pFEEPPage0->ActiveCount, 0);         /*写该页默认的第一次活动计数*/
      if (FlashStatus != SUCCESS)
      {
        break;
      }
    }
    
    if(0xFFFFFFFF == pFEEPPage1->ActiveCount)                                              /*活动计数无效*/         
    {
      FlashStatus = BSP_FLASH_ProgramWord((uint32_t)&pFEEPPage1->ActiveCount, 1);         /*写该页默认的第一次活动计数*/
      if (FlashStatus != SUCCESS)
      {
        break;
      }
    }
    
    if(pFEEPPage0->ActiveCount > pFEEPPage1->ActiveCount)                                  /*活动计数越大的，代表当前活动页*/
    {
      pFEEPPageActive = pFEEPPage0;  
    }
    else
    {
      pFEEPPageActive = pFEEPPage1;  
    }
  }while(0);
  
  BSP_EnInttrupt();  
  return FlashStatus;
}

/*
************************************************************************************************************************
* 函数名称 : BSP_FEEP_Write                                                                                      
* 功能描述 : Flash模拟EEP写操作                                                                                               
* 输入参数 : pDada -- 指向要写的数据                                                                                               
*            Len   -- 要写的长度
* 返回参数 : Flash的操作结果                                                                                                         
* 补充说明 : 实现原理：利用双页与页内多数据块轮替算法提高Flash的使用寿命。
*                      将Flash分成若干份等大的Block储存块，越新的数据保存位置越靠后。
*                      当pFEEPPageActive活动页内的Block储存块用尽后，会擦除另一个FEEPPage页，将数据保存到另一页中。
*                      操作成功后，将另一页设置为当前pFEEPPageActive活动页。
*            写过程：(1)写 WrStartSync = FEEP_OP_SYNC;以标记写操作开始执行。
*                       Flash擦除后只可写一次，因此每个存储块都要用WrStartSync标记是否有执行过写操作。
*                    (2)写入具体的数据。
*                    (3)写 WrEndSync = FEEP_OP_SYNC;以标记写操作完成。
*                       写数据过程中可能发生掉电，造成数据写入不完整。因此要用WrEndSync标记数据是否完整保存。
*                       读操作将使用该标记判断保存的数据是否完整可用。
*                    (4)如果发生换页操作，则最后写ActiveCount计数值，以标记新的活动页。
*                       这步操作也可能因为掉电而失败，因此BSP_FEEP_Init()函数将对这种情况进行判断。
*                       对ActiveCount无效的页将其初始化为默认的最小值。
*
*            应该将应用程序所有要掉电保存的数据封装成一个结构体统一管理，pDada指向该结构体的数据，而不要分散开来。  
************************************************************************************************************************
*/
uint16_t BSP_FEEP_Write(void *pDada, uint16_t Len)
{
  uint16_t FlashStatus;
  uint8_t  i;
  uint32_t TmpData;
  uint8_t  *rp, *wp;
  uint32_t WriteAddr;
  uint32_t EndAddr;
  BSP_FlashEEP_t  *pWrFEEPPage;                        /*记录要执行写操作的页*/

  
  for(i=0; i<FEEP_BLK_SUM; i++)
  {
    if(0xFFFFFFFF == pFEEPPageActive->WrStartSync[i])  /*该Block存储块还未被写入*/
    {
      pWrFEEPPage = pFEEPPageActive;                  
      break;
    }
  }
  if(i >= FEEP_BLK_SUM)                                /*当前活动页的Block存储块已用完*/
  {
    i = 0;                                             /*新页的Block存储块索引从头开始*/  
    pWrFEEPPage = (pFEEPPage0 == pFEEPPageActive) ? pFEEPPage1 : pFEEPPage0;
  }
  
  BSP_DisInttrupt();  

  rp = pDada;
  do
  {
    /*发生换页，则擦除另一页---------------------------------------------*/
    if(pFEEPPageActive != pWrFEEPPage)  
    {
      WriteAddr = (pFEEPPage0 == pFEEPPageActive) ? FEEP_PAGE1_START_ADDR : FEEP_PAGE0_START_ADDR;
      FlashStatus = BSP_FLASH_Erase(WriteAddr);
      if (FlashStatus != SUCCESS)
      {
        break;
      }
      
      FlashStatus = BSP_FLASH_ProgramWord((uint32_t)&pWrFEEPPage->EraseSync, FEEP_OP_SYNC);    /*标识擦除成功*/
      if (FlashStatus != SUCCESS)
      {
        break;
      }
    }
    
    /*写入数据--------------------------------------------------------*/
    FlashStatus = BSP_FLASH_ProgramWord((uint32_t)&pWrFEEPPage->WrStartSync[i], FEEP_OP_SYNC); /*标记开始执行写操作*/  
    if (FlashStatus != SUCCESS)
    {
      break;
    }
    
    WriteAddr = (uint32_t)&pWrFEEPPage->Block[i][0];
    Len = (Len < FEEP_BLK_SIZE) ? Len:FEEP_BLK_SIZE;
    EndAddr   = WriteAddr + Len;
    while(WriteAddr < EndAddr)
    {
      /***************************************************************************************
       * 注意：这里之所以这么麻烦，原因是pDada指向的地址不一定是4字节对齐的。
       * 它可能指向类型uint8_t的数组，而该数组的首地址如果刚好是1字节对齐的。此时如果直接使用类似如下的代码：
       *   uint32_t *rp;
       *   rp = pDada;
       *   BSP_FLASH_ProgramWord(WriteAddr, *rp);   
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
      FlashStatus = BSP_FLASH_ProgramWord(WriteAddr, TmpData);    
      if (FlashStatus != SUCCESS)
      {
        break;
      }
      WriteAddr += 4;
    }
    
    FlashStatus = BSP_FLASH_ProgramWord((uint32_t)&pWrFEEPPage->WrEndSync[i], FEEP_OP_SYNC);   /*标记完成写操作*/      
    if (FlashStatus != SUCCESS)
    {
      break;
    }
    
    /*发生换页，则更新新页的活动计数，并设置为当前活动页---------------*/
    if(pFEEPPageActive != pWrFEEPPage) 
    {
      FlashStatus = BSP_FLASH_ProgramWord((uint32_t)&pWrFEEPPage->ActiveCount, (pFEEPPageActive->ActiveCount+1)); /*写该页默认的第一次活动计数*/
      if (FlashStatus != SUCCESS)
      {
        break;
      }
      pFEEPPageActive = pWrFEEPPage;
    }    
  }while(0);
  
  BSP_EnInttrupt();  
  return FlashStatus;
}

/*
************************************************************************************************************************
* 函数名称 : BSP_FEEP_Read                                                                                      
* 功能描述 : Flash模拟EEP读操作                                                                                               
* 输入参数 : pDada -- 读出数据要存放的地址     
*            Len   -- 要读的长度
* 返回参数 : SUCCESS -- 读成功
*            FAIL    -- 读失败
* 补充说明 : 应该将应用程序所有要掉电保存的数据封装成一个结构体统一管理，pDada指向该结构体的数据，而不要分散开来。  
************************************************************************************************************************
*/
uint8_t  BSP_FEEP_Read(void *pDada, uint16_t Len)
{
  uint8_t i;
  uint8_t *wp;
  uint32_t ReadAddr;
  uint32_t EndAddr;

  wp = pDada;
  for(i=FEEP_BLK_SUM; i>0; i--)                           /*越新的数据保存越靠后，因此从后向前遍历查找*/
  {
    if(FEEP_OP_SYNC == pFEEPPageActive->WrEndSync[i-1])   /*写操作结束同步标记有效，即数据有正常保存*/
    {
      ReadAddr = (uint32_t)&pFEEPPageActive->Block[i-1][0];
      Len = (Len < FEEP_BLK_SIZE) ? Len:FEEP_BLK_SIZE;
      EndAddr  = ReadAddr + Len;
      while(ReadAddr < EndAddr)
      {
        *wp++ = *(uint8_t*)ReadAddr;
        ReadAddr++;
      }
      return SUCCESS;
    }
  }  
  
  return FAIL;
}
