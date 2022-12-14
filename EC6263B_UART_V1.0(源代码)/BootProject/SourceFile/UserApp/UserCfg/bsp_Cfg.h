/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：bsp_Cfg.h 
**
**    功能描述: 板级支持包配置文件
**
**    项目名称：
**
**    平台信息：
**
**    作    者：Hzy
**
**    版    本：
**
**    其他说明:
**
**    修改记录: --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/
#ifndef BSP_CFG_H
#define BSP_CFG_H


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/


/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/

/*==================================================================================================
**
**            配置：系统滴答时钟定时器相关
**
===================================================================================================*/
#define  BSP_CFG_SYS_TICKER_PERIOD          1                          /*系统ticker的周期时间，单位ms*/
//#define  BSP_CFG_SYS_TICKER_MAX             0xFF                       /*系统ticker的的最大计数值，1字节最大0xFF*/
#define  BSP_CFG_SYS_TICKER_MAX             0xFFFF                     /*系统ticker的的最大计数值，2字节最大0xFFFF*/
//#define  BSP_CFG_SYS_TICKER_MAX             0xFFFFFFFF                 /*系统ticker的的最大计数值，4字节最大0xFFFFFFFF*/


/*==================================================================================================
**
**            配置：Flash区域划分  和  Flash模拟EEPROM相关
**            注意：如果使用Flash模拟EEP功能，则应该将最后两个页留给此功能使用。
**                  飞思卡尔Sector Size大小：Kinetis K系列为2048个字节，L系列为1024个字节，而E系列则为512个字节。
**                                           K1x系列为1024个字节
**
**                  1K-0x400     2K-0x800     3K-0xC00     4K-0x1000     5K-0x1400      6K-0x1800      7K-0x1C00          
**                  8K-0x2000    9K-0x2400    10K-0x2800   11K-0x2C00    12K-0x3000     13K-0x3400     14K-0x3800   
**                  15K-0x3C00   16K-0x4000   32K-0x8000   64K-0x10000   128K-0x20000   256K-0x40000   512K-0x80000
**
===================================================================================================*/
#define  BSP_CFG_FEEP_BLK_SIZE                   128                   /*Flash模拟EEP中，要保存的数据块大小,单位字节*/ 

//#define  BSP_CFG_FLASH_PAGE_SIZE               (512)                   /*页大小 512Byte */
//#define  BSP_CFG_FLASH_PAGE_SIZE               (1024)                  /*页大小 2KByte */
#define  BSP_CFG_FLASH_PAGE_SIZE               	(2048)                  /*页大小 2KByte */

/*根据不同的芯片定义其Flash起始和结束地址*/
#define  BSP_CFG_FLASH_START_ADDR                0x08000000            /*FLASH 起始地址*/

#if defined(GD32F30X) 
  #define  BSP_CFG_FLASH_END_ADDR                0x0803FFFF            /*FLASH 结束地址 256K大小 (0x40000)*/
#else
  #error "Please define  GD32F30X"                                   /*请定义相关宏，建议在 "Options for Target"的C/C++页面中定义*/
#endif

#define  BSP_CFG_BOOTLOADER_START_ADDR           BSP_CFG_FLASH_START_ADDR                          /*bootloader起始地址*/
#define  BSP_CFG_BOOTLOADER_END_ADDR             (BSP_CFG_BOOTLOADER_START_ADDR + ((2048*8)-1))    /*bootloader结束地址, 大小16K*/
#define  BSP_CFG_UPDATE_OP_INFO_START_ADDR       (BSP_CFG_BOOTLOADER_END_ADDR+1)                   /*升级操作信息起始地址*/
#define  BSP_CFG_UPDATE_OP_INFO_END_ADDR         (BSP_CFG_UPDATE_OP_INFO_START_ADDR + ((2048)-1))  /*升级操作信结束地址，大小2K*/
#define  BSP_CFG_APPLICATION_START_ADDR          (BSP_CFG_UPDATE_OP_INFO_END_ADDR+1)               /*Application起始地址*/
#define  BSP_CFG_APPLICATION_END_ADDR            (BSP_CFG_FLASH_END_ADDR - (2048*2))               /*Application结束地址，最后两页用作模拟EEP*/

#endif
