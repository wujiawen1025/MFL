/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: Memory.c                                                                                                         
**
**    功能描述:	存储器驱动
**
**    公    司：蒙发利电子
**
**    项目名称：
**
**    平台信息：
**
**    作    者：Hzy
**
**    其他说明:	由于EEPROM的特性，每次写操作都要至少等待5ms的写周期完成，
**              才能进行下一次写操作，且每次最多只能写入一页的数据。
**              因此上层应用应该调用 EEPROM_Write()函数来执行写操作。
**              EEPROM_Write()函数会缓存要写的数据。
**              实际的写操作通过周期性（至少10ms）调用EEPROM_WriteHandle()函数来完成。
**              EPROM_WriteHandle()函数将根据实际情况分次、分页将数据写入EEProm。
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
#include "Memory.h"
#include "ESF.h"


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
static MemoryWrite_t  MemoryWrite;


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : EEPROM_Read                                                                                                         
* 功能描述 : 读操作                                                                                     
* 输入参数 : Addr      -- 读地址
*            pReadData -- 读到的数据要存放的地址
*            ReadLen   -- 读长度                                                                                      
* 返回参数 : FAIL      -- 读失败
*            SUCCESS   -- 读成功                                                                 
* 补充说明 : 以后可能用大容量EEProm，所以这里 Addr 和 ReadLen 用uint16_t。                                                                                                         
************************************************************************************************************************
*/
uint8_t EEPROM_Read(uint16_t Addr, uint8_t *pReadData, uint16_t ReadLen)
{
  uint8_t Ack;
  uint16_t i;

  if(ReadLen <= 0)
  {
    return FAIL;
  }

  if(Addr > EEPROM_MEM_SIZE)
  {
    return FAIL;                                 /*操作地址有误，退出*/
  }

  if((Addr+ReadLen) > EEPROM_MEM_SIZE)
  {
    return FAIL;                                 /*操作过量，退出*/
  }

  /*寻址---------------------------------------*/
  IIC_Start();

  Ack = IIC_ByteWrite(EEPROM_ADDR_WRITE);
  if(IIC_NACK == Ack)
  {
    IIC_Stop();
    return FAIL;
  }

//  Ack = IIC_ByteWrite(Addr >> 8);              /*为大容量预留*/
//  if(IIC_NACK == Ack)
//  {
//    IIC_Stop();
//    return FAIL;
//  }

  Ack = IIC_ByteWrite(Addr & 0xFF);
  if(IIC_NACK == Ack)
  {
    IIC_Stop();
    return FAIL;
  }


  /*读数据---------------------------------------*/
  IIC_Start();

  Ack = IIC_ByteWrite(EEPROM_ADDR_READ);
  if(IIC_NACK == Ack)
  {
    IIC_Stop();
    return FAIL;
  }

  for(i=0; i<(ReadLen-1); i++)
  {
    *pReadData++ = IIC_ByteRead(IIC_ACK);        /*通知 器件 读成功*/
  } 
  *pReadData = IIC_ByteRead(IIC_NACK);           /*通知 器件 停止发送数据，并等待停止信号*/

  IIC_Stop();

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : EEPROM_PageWrite                                                                                                         
* 功能描述 : 页写操作                                                                                     
* 输入参数 : Addr    -- 写地址
*            pData   -- 指向要写的数据
*            DataLen -- 写长度                                                                                      
* 返回参数 : FAIL    -- 写失败
*            SUCCESS -- 写成功                                                                 
* 补充说明 : 1、以后可能用大容量EEProm，所以这里 Addr 和 ReadLen 用uint16_t。 
             2、上层应用不应调用此函数，而应调用 EEPROM_Write 来完成写操作。 
************************************************************************************************************************
*/
static uint8_t EEPROM_PageWrite(uint16_t Addr, uint8_t *pData, uint16_t DataLen)
{
  //uint32_t Twr; /*写周期延时*/
  uint8_t Ack;
  uint8_t i;

  if(DataLen <= 0)
  {
    return FAIL;
  }

  if((Addr+DataLen) > EEPROM_MEM_SIZE)
  {
    return FAIL; /*操作地址有误，退出*/
  }


  IIC_Start();

  Ack = IIC_ByteWrite(EEPROM_ADDR_WRITE);
  if(IIC_NACK == Ack)
  {
    IIC_Stop();
    return FAIL;
  }

//  Ack = IIC_ByteWrite(Addr >> 8); /*为大容量预留*/
//  if(IIC_NACK == Ack)
//  {
//    IIC_Stop();
//    return FAIL;
//  }

  Ack = IIC_ByteWrite(Addr & 0xFF);
  if(IIC_NACK == Ack)
  {
    IIC_Stop();
    return FAIL;
  }

  for(i=0; i<DataLen; i++)
  {
    Ack = IIC_ByteWrite(*pData);
    if(IIC_NACK == Ack)
    {
      IIC_Stop();
      return FAIL;
    }
    pData++;
  }

  IIC_Stop();

  //Twr = 32000;  //延时至少5ms
  //while(--Twr);  /*这里将延时注释掉，使用周期6ms的函数来执行写操作*/

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : EEPROM_Write                                                                                                          
* 功能描述 : 写操作                                                                              
* 输入参数 : Addr    -- 写地址
*            pData   -- 指向要写的数据
*            DataLen -- 写长度                                                                                            
* 返回参数 : MEMORY_WRITE_BUSY   -- 写忙
*            MEMORY_WRITE_RUN    -- 写执行
*            MEMORY_WRITE_OP_ERR -- 写 操作错误                                                                 
* 补充说明 : 以后可能用大容量EEProm，所以这里 Addr 和 ReadLen 用uint16_t。                                                                                                        
************************************************************************************************************************
*/
uint8_t EEPROM_Write(uint16_t Addr, uint8_t *pData, uint16_t DataLen)
{
  if(DataLen <= 0)
  {
    return MEMORY_WRITE_OP_ERR;
  }

  if(Addr > EEPROM_MEM_SIZE)
  {
    return MEMORY_WRITE_OP_ERR;           /*操作地址有误，退出*/
  }

  if((Addr+DataLen) > EEPROM_MEM_SIZE)
  {
    return MEMORY_WRITE_OP_ERR;           /*操作过量，退出*/
  }

  if(MemoryWrite.Len > 0)
  {
    return MEMORY_WRITE_BUSY;
  }

  MemoryWrite.Addr  = Addr;
  MemoryWrite.pData = pData;
  MemoryWrite.Len   = DataLen;

  return MEMORY_WRITE_RUN;
}

/*
************************************************************************************************************************
* 函数名称 : EEPROM_WriteHandle                                                                                                         
* 功能描述 : 写操作处理                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                                 
* 补充说明 : 实际的写操作通过周期性（至少10ms）调用EEPROM_WriteHandle()函数来完成。
**           EPROM_WriteHandle()函数将根据实际情况分次、分页将数据写入EEProm。                                                                                                         
************************************************************************************************************************
*/
void EEPROM_WriteHandle(Ticker_t ExePeriod)
{
  uint8_t size;


  if(MemoryWrite.Len <= 0)
  {
    return;
  }

  /*页写操作不能跨页，否则将会覆盖之前写过的数据。 */

  size = (MemoryWrite.Addr & (0xFF >> (8-EEPROM_PAGE_SIZE_BITS)));
  if(size != 0) /*地址非页对齐*/
  {
    size = EEPROM_PAGE_SIZE - size;                            /*计算对齐到页，需要操作的字节数*/
    size = (size>MemoryWrite.Len) ? MemoryWrite.Len : size;    /*不能大于 要写 的长度*/ 
    EEPROM_PageWrite(MemoryWrite.Addr, MemoryWrite.pData, size);
    MemoryWrite.Len -= size;  
    MemoryWrite.pData += size;
    MemoryWrite.Addr += size;
  }
  else/*地址页对齐*/
  {
    if(MemoryWrite.Len >= EEPROM_PAGE_SIZE)
    {
      size = EEPROM_PAGE_SIZE;
    }
    else
    {
      size = MemoryWrite.Len;
    }

    EEPROM_PageWrite(MemoryWrite.Addr, MemoryWrite.pData, size);
    MemoryWrite.Len -= size;  
    MemoryWrite.pData += size;
    MemoryWrite.Addr += size;
  }
}
