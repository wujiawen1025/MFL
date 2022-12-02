/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称:                                                                                                         
**
**    功能描述:                                                                                                       
**
**    公    司：                                                                                                        
**
**    项目名称：                                                                                                        
**
**    平台信息：                                                                                                        
**
**    作    者：LZH                                                                                                     
**
**    其他说明:                                                                                                        
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
#include "bsp_uart.h"
#include "gd32f30x_usart.h"

/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/

/*串口使能与掩码*/
#define  BSP_UART_0_EN                      1
#define  BSP_UART_1_EN                      1
#define  BSP_UART_2_EN                      1
#define  BSP_UART_3_EN                      1
#define  BSP_UART_4_EN                      1
#define  BSP_UART_PORT_MASK                 ((BSP_UART_0_EN<<0) | (BSP_UART_1_EN<<1) | (BSP_UART_2_EN<<2) | (BSP_UART_3_EN<<3) | (BSP_UART_4_EN<<4))

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
static UartRxTx_t    UartRxTx[BSP_UART_PORT_MAX];
uint32_t             UsartMap[] = {USART0, USART1, USART2, UART3, UART4}; /*串口号对应的实际串口*/


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : BSP_UART_Init                                                                                                         
* 功能描述 : 串口初始化                                                                                                           
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void BSP_UART_Init(void)
{
  uint8_t             PortNum;
  
  for(PortNum=0; PortNum<BSP_UART_PORT_MAX; PortNum++)
  {
    if(BSP_UART_PORT_MASK & (1<<PortNum))                                       /*该串口使能的才去进行初始化配置*/
    {
      if(USART0 == UsartMap[PortNum])
      {
        rcu_periph_clock_enable(RCU_USART0);                                    /* 使能USART0时钟 */
        nvic_irq_enable(USART0_IRQn, 0, 0);                                     /* 设置USART0优先级 */
      }
      else if(USART1 == UsartMap[PortNum])
      {
        rcu_periph_clock_enable(RCU_USART1);                                    /* 使能USART1时钟 */
        nvic_irq_enable(USART1_IRQn, 0, 0);                                     /* 设置USART1优先级 */
      }
      else if(USART2 == UsartMap[PortNum])
      {
        rcu_periph_clock_enable(RCU_USART2);                                    /* 使能USART2时钟 */
        nvic_irq_enable(USART2_IRQn, 0, 0);                                     /* 设置USART2优先级 */
      }
      else if(UART3 == UsartMap[PortNum])
      {
        rcu_periph_clock_enable(RCU_UART3);                                     /* 使能USART3时钟 */
        nvic_irq_enable(UART3_IRQn, 0, 0);                                      /* 设置USART3优先级 */
      }
      else if(UART4 == UsartMap[PortNum])
      {
        rcu_periph_clock_enable(RCU_UART4);                                     /* 使能USART4时钟 */
        nvic_irq_enable(UART4_IRQn, 0, 0);                                      /* 设置USART4优先级 */
      }
      //UartRxTx[PortNum].WorkMode |= BSP_UART_WORK_MODE_TX;                    /* 发送模式开启 */
      UartRxTx[PortNum].WorkMode |= BSP_UART_WORK_MODE_RX;                      /* 接收模式开启 */
      
      /* USART configure */
      usart_deinit(UsartMap[PortNum]);
//      usart_baudrate_set(UsartMap[PortNum], 19200);
			if(USART0 == UsartMap[PortNum])
			{
				usart_baudrate_set(UsartMap[PortNum], 19200);
			}
			else if(USART1 == UsartMap[PortNum])
			{
				usart_baudrate_set(UsartMap[PortNum], 19200);
			}
			else if(USART2 == UsartMap[PortNum])
			{
				usart_baudrate_set(UsartMap[PortNum], 19200);
			}
			else if(UART3 == UsartMap[PortNum])
			{
				usart_baudrate_set(UsartMap[PortNum], 19200);
			}
			else if(UART4 == UsartMap[PortNum])
			{
				usart_baudrate_set(UsartMap[PortNum], 9600);
			}
			
      usart_receive_config(UsartMap[PortNum], USART_RECEIVE_ENABLE);
      usart_transmit_config(UsartMap[PortNum], USART_TRANSMIT_ENABLE);
      usart_enable(UsartMap[PortNum]);
      
      /* enable USART RX interrupt */  
      usart_interrupt_enable(UsartMap[PortNum], USART_INT_RBNE);
    }           
  }
  
}

/*
************************************************************************************************************************
* 函数名称 : BSP_UART_RegRxByteCB                                                                                                         
* 功能描述 : 向串口注册字节接收回调函数                                                                                                     
* 输入参数 : PortNum   -- 串口号
*            pRxByteCB -- 串口收到一个字节数据后，将要调用的回调函数。                                                                                                          
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void BSP_UART_RegRxByteCB(BSP_UART_PortNum_t PortNum,  void (*pRxByteCB)(uint8_t RxByte))
{
  if(PortNum >= BSP_UART_PORT_MAX)
  {
    return;
  }
	
  if(pRxByteCB != (void *)0)
  {
    UartRxTx[PortNum].pRxByteCB = pRxByteCB;
  }
}

/*
************************************************************************************************************************
* 函数名称 : BSP_UART_GetRxLen                                                                                                         
* 功能描述 : 获得串口接收到的字节长度                                                                                                     
* 输入参数 : PortNum -- 串口号
* 返回参数 : 串口接收到的字节长度                                                                                                           
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint16_t BSP_UART_GetRxLen(BSP_UART_PortNum_t PortNum)
{
  uint16_t RxLen;

  if(PortNum >= BSP_UART_PORT_MAX)
  {
    return 0;
  }

  RxLen = UartRxTx[PortNum].RxFIFOLen;   
  return RxLen;
}

/*
************************************************************************************************************************
* 函数名称 : BSP_UART_GetRxData                                                                                                         
* 功能描述 : 获得串口接收到的数据                                                                                                  
* 输入参数 : PortNum -- 串口号
*            pGetBuf -- 数据获得后的保存地址
*            GetLen  -- 要获得的长度
* 返回参数 : 实际获得的数据长度                                                                                                          
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
//uint16_t BSP_UART_GetRxData(BSP_UART_PortNum_t PortNum, uint8_t *pGetBuf, uint16_t GetLen)
//{
//	
//}

/*
************************************************************************************************************************
* 函数名称 : BSP_UART_TxData                                                                                                         
* 功能描述 : 串口 发送数据                                                                                                   
* 输入参数 : PortNum   -- 串口号
*            buf -- 指向要发送的数据
*            len -- 要发送数据的长度                                                                                                       
* 返回参数 : BSP_UART_TxState_Busy  -- 发送忙，无法处理发送pTxBuf指向的的数据。
*            其他值                 -- 串口开始发送pTxBuf指向的的数据了。
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
BSP_UART_TxState_t BSP_UART_TxData(BSP_UART_PortNum_t PortNum, uint8_t *pTxBuf, uint16_t TxLen)
{
  if(PortNum >= BSP_UART_PORT_MAX)
  {
    return BSP_UART_TxState_Idle;                            /*串口号错，不发送，返回非BSP_UART_TxState_Busy值即可*/
  }

  if(UartRxTx[PortNum].WorkMode & BSP_UART_WORK_MODE_TX)
  {
    return BSP_UART_TxState_Busy;                            /*有数据在发送，返回发送忙*/
  }
  
  if(TxLen <= 0)
  {
    return BSP_UART_TxState_Idle;                            /*长度无效，不发送，返回非BSP_UART_TxState_Busy值即可*/
  }  

  UartRxTx[PortNum].WorkMode  |= BSP_UART_WORK_MODE_TX;
  UartRxTx[PortNum].TxPoint    = pTxBuf;
  UartRxTx[PortNum].TxLen      = TxLen;
  usart_interrupt_enable(UsartMap[PortNum], USART_INT_TBE);  /*发送使能*/

  return BSP_UART_TxState_Idle;                              /*准备开始发送，返回非BSP_UART_TxState_Busy值即可*/    
}

/*
************************************************************************************************************************
* 函数名称 : BSP_UART_GetTxState                                                                                                         
* 功能描述 : 获取 串口 发送 状态                                                                                             
* 输入参数 : PortNum   -- 串口号
* 返回参数 : BSP_UART_TxState_Idle  -- 发送空闲
*            BSP_UART_TxState_Busy  -- 发送忙
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
BSP_UART_TxState_t BSP_UART_GetTxState(BSP_UART_PortNum_t PortNum)
{
  if(PortNum >= BSP_UART_PORT_MAX)
  {
    return BSP_UART_TxState_Busy;                            /*串口号错，返回发送忙*/
  }

  if(UartRxTx[PortNum].WorkMode & BSP_UART_WORK_MODE_TX)
  {
    return BSP_UART_TxState_Busy;
  }
  else
  {
    return BSP_UART_TxState_Idle;
  }
}

/*
************************************************************************************************************************
* 函数名称 : USART_IRQHandler                                                                                                         
* 功能描述 : 串口 中断处理函数                                                                                             
* 输入参数 : PortNum  -- 串口号
* 返回参数 : 无
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static void USART_IRQHandler(BSP_UART_PortNum_t PortNum)
{
  uint8_t RxData;

  if(PortNum >= BSP_UART_PORT_MAX)
  {
    return;                          
  }
  
  /*溢出判断-----------------------------------------------------*/
//  if( usart_interrupt_flag_get(UsartMap[PortNum], USART_INT_FLAG_RBNE_ORERR) )
//  {
//    RxData = USART_ReceiveData(UsartMap[PortNum]);    
//    return;
//  }
  
  /*接收中断-----------------------------------------------------*/
  if( RESET != usart_interrupt_flag_get(UsartMap[PortNum], USART_INT_FLAG_RBNE) )       
  {
    RxData = usart_data_receive(UsartMap[PortNum]);
    if(UartRxTx[PortNum].pRxByteCB != (void *)0)
    {
      UartRxTx[PortNum].pRxByteCB(RxData);                             /*字节接收回调处理*/
    }
    
    if(UartRxTx[PortNum].RxFIFOLen < BSP_UART_RX_FIFO_BUF_LEN)         /*不超过环形队列的容量*/
    {
      UartRxTx[PortNum].RxFIFOBuf[UartRxTx[PortNum].RxFIFOIn++] = RxData;
      if(UartRxTx[PortNum].RxFIFOIn > (BSP_UART_RX_FIFO_BUF_LEN-1))
      {
        UartRxTx[PortNum].RxFIFOIn = 0;
      }
      BSP_DisInttrupt();                                         
      UartRxTx[PortNum].RxFIFOLen++;   
      BSP_EnInttrupt();                                        
    }
  }

  /*发送中断----------------------------------------------------*/
  if( RESET != usart_interrupt_flag_get(UsartMap[PortNum], USART_INT_FLAG_TBE) )
  {
    if(UartRxTx[PortNum].TxLen > 0)                                    /*还有数据要发送*/
    {
      usart_data_transmit(UsartMap[PortNum], *UartRxTx[PortNum].TxPoint++);
      UartRxTx[PortNum].TxLen--;
    }
    else
    {   
      UartRxTx[PortNum].WorkMode &= ~BSP_UART_WORK_MODE_TX;            /*取消发送模式*/
      usart_interrupt_disable(UsartMap[PortNum], USART_INT_TBE);
    }
  }
}



/*
************************************************************************************************************************
* 函数名称 : USART0_IRQHandler                                                                                                         
* 功能描述 : 串口0 中断处理函数                                                                                             
* 输入参数 : 无                                                                                                
* 返回参数 : 无
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void USART0_IRQHandler(void)
{
  #if(BSP_UART_0_EN)
  USART_IRQHandler(BSP_UART_Port0);
  #endif  
}

/*
************************************************************************************************************************
* 函数名称 : USART1_IRQHandler                                                                                                         
* 功能描述 : 串口1 中断处理函数                                                                                             
* 输入参数 : 无                                                                                                
* 返回参数 : 无
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void USART1_IRQHandler(void)
{
  #if(BSP_UART_1_EN)
  USART_IRQHandler(BSP_UART_Port1);
  #endif      
}

/*
************************************************************************************************************************
* 函数名称 : USART2_IRQHandler                                                                                                         
* 功能描述 : 串口2 中断处理函数                                                                                             
* 输入参数 : 无                                                                                                
* 返回参数 : 无
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void USART2_IRQHandler(void)
{
  #if(BSP_UART_2_EN)
  USART_IRQHandler(BSP_UART_Port2);
  #endif      
}

/*
************************************************************************************************************************
* 函数名称 : UART3_IRQHandler                                                                                                         
* 功能描述 : 串口3 中断处理函数                                                                                             
* 输入参数 : 无                                                                                                
* 返回参数 : 无
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void UART3_IRQHandler(void)
{
  #if(BSP_UART_3_EN)
  USART_IRQHandler(BSP_UART_Port3);
  #endif      
}

/*
************************************************************************************************************************
* 函数名称 : UART4_IRQHandler                                                                                                         
* 功能描述 : 串口4 中断处理函数                                                                                             
* 输入参数 : 无                                                                                                
* 返回参数 : 无
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void UART4_IRQHandler(void)
{
  #if(BSP_UART_4_EN)
  USART_IRQHandler(BSP_UART_Port4);
  #endif      
}

