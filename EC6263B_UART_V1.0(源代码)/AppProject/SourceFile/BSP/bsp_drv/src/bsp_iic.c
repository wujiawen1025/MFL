/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: bsp_iic.c
**
**    功能描述: IIC总线操作
**
**    公    司：蒙发利电子
**
**    项目名称：                                                                                                        
**
**    平台信息：                                                                                                        
**
**    作    者：Hzy                                                                                                     
**
**    其他说明: 用IO口模拟IIC来操作。                                                                                                     
**
**    修改记录:  
**
========================================================================================================================
========================================================================================================================
*/

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp_iic.h"          



/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/
#define IIC_SCL_OUTPUT        GPIO_PinInit(GPIOE, GPIO_Pin_1, GPIO_Mode_OUT);
#define IIC_SDA_OUTPUT        GPIO_PinInit(GPIOE, GPIO_Pin_0, GPIO_Mode_OUT);                /* pin75 -- PTE1 -- SCL */				
#define IIC_SDA_INPUT         GPIO_PinInit(GPIOE, GPIO_Pin_0, GPIO_Mode_IN);                 /* pin75 -- PTE1 -- SCL */				

#define   IIC_SCL_H           GPIO_WriteBit(GPIOE, GPIO_Pin_1, Bit_SET)
#define   IIC_SCL_L           GPIO_WriteBit(GPIOE, GPIO_Pin_1, Bit_RESET) 

#define   IIC_SDA_H           GPIO_WriteBit(GPIOE, GPIO_Pin_0, Bit_SET) 
#define   IIC_SDA_L           GPIO_WriteBit(GPIOE, GPIO_Pin_0, Bit_RESET) 

#define   IIC_SDA             GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)


#define  IIC_DEALAY          35

/*
========================================================================================================================
*【本地数据类型定义】                              【本地数据类型定义】                              【本地数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :                                                                                                         
************************************************************************************************************************
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
* 函数名称 : IIC_Delay                                                                                                         
* 功能描述 : IIC 操作延时用函数                                                                                               
* 输入参数 : time --  延时时间                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
__INLINE static void IIC_Delay(uint32_t time)
{  
  while(time--); 
}


/*
************************************************************************************************************************
* 函数名称 : IIC_Start                                                                                                         
* 功能描述 : IIC 开始信号                                                                                        
* 输入参数 : time --  延时时间                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 时钟线保持高电平期间，数据线电平从高到低的跳变，
*            作为IIC 总线的起始信号。                                                                                                       
************************************************************************************************************************
*/
void IIC_Start(void)
{
  IIC_SCL_OUTPUT;
  IIC_SDA_OUTPUT;

  IIC_SCL_H;
  IIC_SDA_H;
  IIC_Delay(IIC_DEALAY);
                   
  IIC_SDA_L;
  IIC_Delay(IIC_DEALAY);

  IIC_SCL_L;		       /*钳住I2C总线，准备发送或接收数据 */
  IIC_Delay(IIC_DEALAY);
}


/*
************************************************************************************************************************
* 函数名称 : IIC_Stop                                                                                                         
* 功能描述 : IIC 停止信号                                                                                         
* 输入参数 : time --  延时时间                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 时钟线保持高电平期间，数据线电平从低到高的跳变，
*            作为IIC 总线的停止信号。                                                                                                         
************************************************************************************************************************
*/
void IIC_Stop(void)
{
  IIC_SCL_OUTPUT;
  IIC_SDA_OUTPUT;

  IIC_SCL_L;
  IIC_SDA_L;
  IIC_Delay(IIC_DEALAY);

  IIC_SCL_H;
  IIC_Delay(IIC_DEALAY);

  IIC_SDA_H;
  IIC_Delay(IIC_DEALAY);
}


/*
************************************************************************************************************************
* 函数名称 : IIC_ByteWrite                                                                                                         
* 功能描述 : IIC 字节写操作                                                                                         
* 输入参数 : Data -- 要写的数据                                                                                                 
* 返回参数 : 0 -- 从器件 应答
*            1 -- 从器件 没应答                                                                                                           
* 补充说明 : IIC 总线数据传送时每成功地传送一个字节数据后，
*            接收器都必须产生一个应答信号。应答的器件在
*            第9个时钟周期时将SDA拉低表示已收到一个8位数据。                                                                                                          
************************************************************************************************************************
*/
uint8_t  IIC_ByteWrite(uint8_t Data)
{
  uint8_t i;
  uint8_t AckState;

  IIC_SDA_OUTPUT;

  for(i=0; i<8; i++)
  {
    if(Data&0x80)
    {
      IIC_SDA_H;
    }
    else
    {
      IIC_SDA_L;
    }
    
    Data <<= 1;
    IIC_Delay(IIC_DEALAY);
    IIC_SCL_H;
    IIC_Delay(IIC_DEALAY);
    IIC_SCL_L;
    IIC_Delay(IIC_DEALAY);
  }

  IIC_SDA_OUTPUT;
  IIC_SDA_H;     
  IIC_Delay(IIC_DEALAY);
  IIC_SCL_H;       
  IIC_Delay(IIC_DEALAY);
  IIC_SDA_INPUT;
  AckState = IIC_SDA;   /*读应答*/
  IIC_SCL_L;  

  return AckState;
}


/*
************************************************************************************************************************
* 函数名称 : IIC_ByteRead                                                                                                         
* 功能描述 : IIC 字节读操作                                                                                            
* 输入参数 :  Ack -- 根据操作情况发送ACK或NACK                                                                                                
* 返回参数 : 读到的数据                                                                                                        
* 补充说明 : IIC 总线数据传送时每成功地传送一个字节数据后，
*            接收器都必须产生一个应答信号。应答的器件在
*            第9个时钟周期时将SDA拉低表示已收到一个8位数据。                                                                                                          
************************************************************************************************************************
*/
uint8_t IIC_ByteRead(uint8_t Ack)   
{
  uint8_t i;
  uint8_t Read;

  IIC_SDA_INPUT;
  for(i=0; i<8; i++)
  {
    IIC_SCL_H;
    IIC_Delay(IIC_DEALAY);
    Read = (Read<<1) | IIC_SDA;
    IIC_SCL_L;
    IIC_Delay(IIC_DEALAY);
  }

  IIC_SDA_OUTPUT;
  
  if(Ack) /*发送 ACK 或 NACK*/
  {
    IIC_SDA_H;
  }
  else
  {
    IIC_SDA_L;
  }
  
  IIC_Delay(IIC_DEALAY);
  IIC_SCL_H;
  IIC_Delay(IIC_DEALAY);
  IIC_SCL_L;
  IIC_Delay(IIC_DEALAY);

  return Read;
}

