/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����:                                                                                                         
**
**    ��������:                                                                                                       
**
**    ��    ˾��                                                                                                        
**
**    ��Ŀ���ƣ�                                                                                                        
**
**    ƽ̨��Ϣ��                                                                                                        
**
**    ��    �ߣ�LZH                                                                                                     
**
**    ����˵��:                                                                                                        
**
**    �޸ļ�¼:  
**
========================================================================================================================
========================================================================================================================
*/

/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "bsp_uart.h"
#include "gd32f30x_usart.h"

/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/

/*����ʹ��������*/
#define  BSP_UART_0_EN                      1
#define  BSP_UART_1_EN                      1
#define  BSP_UART_2_EN                      1
#define  BSP_UART_3_EN                      1
#define  BSP_UART_4_EN                      1
#define  BSP_UART_PORT_MASK                 ((BSP_UART_0_EN<<0) | (BSP_UART_1_EN<<1) | (BSP_UART_2_EN<<2) | (BSP_UART_3_EN<<3) | (BSP_UART_4_EN<<4))

/*
========================================================================================================================
*�������������Ͷ��塿                              �������������Ͷ��塿                              �������������Ͷ��塿
========================================================================================================================
*/


/*
========================================================================================================================
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
========================================================================================================================
*/
static UartRxTx_t    UartRxTx[BSP_UART_PORT_MAX];
uint32_t             UsartMap[] = {USART0, USART1, USART2, UART3, UART4}; /*���ںŶ�Ӧ��ʵ�ʴ���*/


/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : BSP_UART_Init                                                                                                         
* �������� : ���ڳ�ʼ��                                                                                                           
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void BSP_UART_Init(void)
{
  uint8_t             PortNum;
  
  for(PortNum=0; PortNum<BSP_UART_PORT_MAX; PortNum++)
  {
    if(BSP_UART_PORT_MASK & (1<<PortNum))                                       /*�ô���ʹ�ܵĲ�ȥ���г�ʼ������*/
    {
      if(USART0 == UsartMap[PortNum])
      {
        rcu_periph_clock_enable(RCU_USART0);                                    /* ʹ��USART0ʱ�� */
        nvic_irq_enable(USART0_IRQn, 0, 0);                                     /* ����USART0���ȼ� */
      }
      else if(USART1 == UsartMap[PortNum])
      {
        rcu_periph_clock_enable(RCU_USART1);                                    /* ʹ��USART1ʱ�� */
        nvic_irq_enable(USART1_IRQn, 0, 0);                                     /* ����USART1���ȼ� */
      }
      else if(USART2 == UsartMap[PortNum])
      {
        rcu_periph_clock_enable(RCU_USART2);                                    /* ʹ��USART2ʱ�� */
        nvic_irq_enable(USART2_IRQn, 0, 0);                                     /* ����USART2���ȼ� */
      }
      else if(UART3 == UsartMap[PortNum])
      {
        rcu_periph_clock_enable(RCU_UART3);                                     /* ʹ��USART3ʱ�� */
        nvic_irq_enable(UART3_IRQn, 0, 0);                                      /* ����USART3���ȼ� */
      }
      else if(UART4 == UsartMap[PortNum])
      {
        rcu_periph_clock_enable(RCU_UART4);                                     /* ʹ��USART4ʱ�� */
        nvic_irq_enable(UART4_IRQn, 0, 0);                                      /* ����USART4���ȼ� */
      }
      //UartRxTx[PortNum].WorkMode |= BSP_UART_WORK_MODE_TX;                    /* ����ģʽ���� */
      UartRxTx[PortNum].WorkMode |= BSP_UART_WORK_MODE_RX;                      /* ����ģʽ���� */
      
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
* �������� : BSP_UART_RegRxByteCB                                                                                                         
* �������� : �򴮿�ע���ֽڽ��ջص�����                                                                                                     
* ������� : PortNum   -- ���ں�
*            pRxByteCB -- �����յ�һ���ֽ����ݺ󣬽�Ҫ���õĻص�������                                                                                                          
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
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
* �������� : BSP_UART_GetRxLen                                                                                                         
* �������� : ��ô��ڽ��յ����ֽڳ���                                                                                                     
* ������� : PortNum -- ���ں�
* ���ز��� : ���ڽ��յ����ֽڳ���                                                                                                           
* ����˵�� : ��                                                                                                         
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
* �������� : BSP_UART_GetRxData                                                                                                         
* �������� : ��ô��ڽ��յ�������                                                                                                  
* ������� : PortNum -- ���ں�
*            pGetBuf -- ���ݻ�ú�ı����ַ
*            GetLen  -- Ҫ��õĳ���
* ���ز��� : ʵ�ʻ�õ����ݳ���                                                                                                          
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
//uint16_t BSP_UART_GetRxData(BSP_UART_PortNum_t PortNum, uint8_t *pGetBuf, uint16_t GetLen)
//{
//	
//}

/*
************************************************************************************************************************
* �������� : BSP_UART_TxData                                                                                                         
* �������� : ���� ��������                                                                                                   
* ������� : PortNum   -- ���ں�
*            buf -- ָ��Ҫ���͵�����
*            len -- Ҫ�������ݵĳ���                                                                                                       
* ���ز��� : BSP_UART_TxState_Busy  -- ����æ���޷�������pTxBufָ��ĵ����ݡ�
*            ����ֵ                 -- ���ڿ�ʼ����pTxBufָ��ĵ������ˡ�
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
BSP_UART_TxState_t BSP_UART_TxData(BSP_UART_PortNum_t PortNum, uint8_t *pTxBuf, uint16_t TxLen)
{
  if(PortNum >= BSP_UART_PORT_MAX)
  {
    return BSP_UART_TxState_Idle;                            /*���ںŴ������ͣ����ط�BSP_UART_TxState_Busyֵ����*/
  }

  if(UartRxTx[PortNum].WorkMode & BSP_UART_WORK_MODE_TX)
  {
    return BSP_UART_TxState_Busy;                            /*�������ڷ��ͣ����ط���æ*/
  }
  
  if(TxLen <= 0)
  {
    return BSP_UART_TxState_Idle;                            /*������Ч�������ͣ����ط�BSP_UART_TxState_Busyֵ����*/
  }  

  UartRxTx[PortNum].WorkMode  |= BSP_UART_WORK_MODE_TX;
  UartRxTx[PortNum].TxPoint    = pTxBuf;
  UartRxTx[PortNum].TxLen      = TxLen;
  usart_interrupt_enable(UsartMap[PortNum], USART_INT_TBE);  /*����ʹ��*/

  return BSP_UART_TxState_Idle;                              /*׼����ʼ���ͣ����ط�BSP_UART_TxState_Busyֵ����*/    
}

/*
************************************************************************************************************************
* �������� : BSP_UART_GetTxState                                                                                                         
* �������� : ��ȡ ���� ���� ״̬                                                                                             
* ������� : PortNum   -- ���ں�
* ���ز��� : BSP_UART_TxState_Idle  -- ���Ϳ���
*            BSP_UART_TxState_Busy  -- ����æ
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
BSP_UART_TxState_t BSP_UART_GetTxState(BSP_UART_PortNum_t PortNum)
{
  if(PortNum >= BSP_UART_PORT_MAX)
  {
    return BSP_UART_TxState_Busy;                            /*���ںŴ����ط���æ*/
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
* �������� : USART_IRQHandler                                                                                                         
* �������� : ���� �жϴ�����                                                                                             
* ������� : PortNum  -- ���ں�
* ���ز��� : ��
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static void USART_IRQHandler(BSP_UART_PortNum_t PortNum)
{
  uint8_t RxData;

  if(PortNum >= BSP_UART_PORT_MAX)
  {
    return;                          
  }
  
  /*����ж�-----------------------------------------------------*/
//  if( usart_interrupt_flag_get(UsartMap[PortNum], USART_INT_FLAG_RBNE_ORERR) )
//  {
//    RxData = USART_ReceiveData(UsartMap[PortNum]);    
//    return;
//  }
  
  /*�����ж�-----------------------------------------------------*/
  if( RESET != usart_interrupt_flag_get(UsartMap[PortNum], USART_INT_FLAG_RBNE) )       
  {
    RxData = usart_data_receive(UsartMap[PortNum]);
    if(UartRxTx[PortNum].pRxByteCB != (void *)0)
    {
      UartRxTx[PortNum].pRxByteCB(RxData);                             /*�ֽڽ��ջص�����*/
    }
    
    if(UartRxTx[PortNum].RxFIFOLen < BSP_UART_RX_FIFO_BUF_LEN)         /*���������ζ��е�����*/
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

  /*�����ж�----------------------------------------------------*/
  if( RESET != usart_interrupt_flag_get(UsartMap[PortNum], USART_INT_FLAG_TBE) )
  {
    if(UartRxTx[PortNum].TxLen > 0)                                    /*��������Ҫ����*/
    {
      usart_data_transmit(UsartMap[PortNum], *UartRxTx[PortNum].TxPoint++);
      UartRxTx[PortNum].TxLen--;
    }
    else
    {   
      UartRxTx[PortNum].WorkMode &= ~BSP_UART_WORK_MODE_TX;            /*ȡ������ģʽ*/
      usart_interrupt_disable(UsartMap[PortNum], USART_INT_TBE);
    }
  }
}



/*
************************************************************************************************************************
* �������� : USART0_IRQHandler                                                                                                         
* �������� : ����0 �жϴ�����                                                                                             
* ������� : ��                                                                                                
* ���ز��� : ��
* ����˵�� : ��                                                                                                         
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
* �������� : USART1_IRQHandler                                                                                                         
* �������� : ����1 �жϴ�����                                                                                             
* ������� : ��                                                                                                
* ���ز��� : ��
* ����˵�� : ��                                                                                                         
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
* �������� : USART2_IRQHandler                                                                                                         
* �������� : ����2 �жϴ�����                                                                                             
* ������� : ��                                                                                                
* ���ز��� : ��
* ����˵�� : ��                                                                                                         
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
* �������� : UART3_IRQHandler                                                                                                         
* �������� : ����3 �жϴ�����                                                                                             
* ������� : ��                                                                                                
* ���ز��� : ��
* ����˵�� : ��                                                                                                         
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
* �������� : UART4_IRQHandler                                                                                                         
* �������� : ����4 �жϴ�����                                                                                             
* ������� : ��                                                                                                
* ���ز��� : ��
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void UART4_IRQHandler(void)
{
  #if(BSP_UART_4_EN)
  USART_IRQHandler(BSP_UART_Port4);
  #endif      
}

