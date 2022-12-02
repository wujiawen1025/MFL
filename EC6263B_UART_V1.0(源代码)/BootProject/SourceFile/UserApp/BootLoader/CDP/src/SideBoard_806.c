#include <String.h>
#include <math.h>
//#include "Config.h"
//#include "Datatype.h"	
//#include "IO.h"
//#include "Glob.h"
//#include "Clib.h"
//#include "Flag.h"
//#include "Init.h"
//#include "Display.h"
//#include "InspectOneself.h"
//#include "HCS08_EEPROM_API.h"
//#include "KeyScan.h"
//#include "bsp_flash.h" 
//#include "Clib.h" 

//#include "ke0x_common.h"
#include "SideBoard_806.h"
#include "CDP.h"


CDP_CenSideCtrl_t CDP_CenSideCtrl;
CDP_CenSideCtrl_t *pCDP_CenSideCtrl = &CDP_CenSideCtrl;
CDP_CenSideBoard_t CDP_CenSideBoard;
uint16_t  TxResflag = 0;
uint8_t gCombinationKeyTime;

//extern void 	KeyPressEvent(void);

uint16_t	CalculateCheckSum(unsigned char *ptData, uint8_t cntNum)
{
	uint16_t	sum = 0;
	while(cntNum-->0)
	{
		 sum += *ptData++;
	}
	return sum;
}


/*
************************************************************************************************************************
* 函数名称 : CDP_CenWifi_ByteRx                                                                                                    
* 功能描述 : 通信数据包   之   中心板 <--> 后台服务器  中心板字节接收数据回调处理函数                                                                              
* 输入参数 : void                                                                 
* 返回参数 : 无                                                             
* 补充说明 : 将数据根据帧头帧尾为界接收下来，进行累加和判断正确后，给后续处理。                                                                                                
************************************************************************************************************************
*/

void	CDP_CenSideBoard_ByteRx(uint8_t RxByte)
{//串口中断调用函数
  static uint8_t NeedESC,ByteRxLen;                                                            /*标识是否需要转义 */
  static uint8_t PDUReceving = FALSE;                                                /*协议数据单元(除去帧头和帧尾)接收中 */
  uint8_t checksum;
  
#if 1 
  if(pCDP_CenSideCtrl->RxNothingTimer > 10)//超过10ms没有接收数据
  {
    PDUReceving = FALSE;                                                            /*开启数据接收*/
    ByteRxLen = 0;
  }
  pCDP_CenSideCtrl->RxNothingTimer = 0;
#endif

  /*数据接收:帧提取、转义处理、累加和校验--------------------------------------*/
  if(CDP_FRAME_BOUNDARY == RxByte)                                                   /*收到帧边界*/ 
  {
    if(TRUE == PDUReceving)                                                          /*数据接收中，表明收到帧尾*/
    {
      if(ByteRxLen >= CDP_SIDECTRL_FRAME_MIN_LEN-2)                                  /*收到足够长度的数据。-2:去掉帧头帧尾*/
      {
        /*计算累加和校验码*/
        checksum = 0;
        checksum = CalculateCheckSum(pCDP_CenSideCtrl->RxBuf, ByteRxLen-1); 

        if(checksum == pCDP_CenSideCtrl->RxBuf[ByteRxLen-1])
        {
          //pCDP_CenSideCtrl->RxBuf[ByteRxLen++] = RxByte;//将校验码也存入长度
          pCDP_CenSideCtrl->RxLen = ByteRxLen-1;
          pCDP_CenSideCtrl->CSFlag.Bit.RxWifiDataOKFlag = TRUE;  //置数据接收完成标志   
	   	    //evReceiveSideBoardFlag  = 1;
					ReceviceDataFromSideBoard();					
					
          PDUReceving = FALSE;                                                       /*数据接收结束*/
        }
      }      
    }
    else                                                                             /*数据还没开始接收，表明收到帧头*/
    {
      PDUReceving = TRUE;                                                            /*开启数据接收*/
    }
    
    NeedESC = FALSE;
    ByteRxLen = 0;
  }
  else if(TRUE == PDUReceving)                                                      /*êy?Y?óê??a??2???DDêy?Yμ??óê?*/
  {
    if(CDP_FRAME_ESC == RxByte)
    {
      NeedESC = TRUE;               //遇到转义字符不做处理，直接处理下一个0x7D 或者 0x5D   ,直接+1                                       /*×aò?μ?×??úêy?Y2?·?è??óê??o′?￡???áúμ???ò???×??úòa×?×aò?′|àí￡??1?-3é?-à′μ?êy?Y*/
    }
    else
    {
      if(TRUE == NeedESC)
      {
        pCDP_CenSideCtrl->RxBuf[ByteRxLen++] = RxByte ^ 0x03;               /*最后两位取反，相当于加1处理*/
        NeedESC = FALSE;
      }
      else
      {
        pCDP_CenSideCtrl->RxBuf[ByteRxLen++] = RxByte;
      }
      
      if(ByteRxLen >= Xxx_CTRL_RX_BUF_SIZE)                              /*3?1y?o′?3¤?è￡??ò′óí·?aê??óê?*/   
      {
        NeedESC = FALSE;
        ByteRxLen = 0;
      }
    }
  }
}


/*
************************************************************************************************************************
* 函数名称 : CDP_CenWifi_FrameTx                                                                                                         
* 功能描述 : 通信数据帧组包 + 发送                                                                                   
* 输入参数 : DesAddr   -- 目的地址
*            Cmd       -- 命令
*            DUBuf     -- 指针数组，数组内的元素为指针，每个指针指向一个保存DU数据(应该包含数据长度和数据ID) 的内存地址。   
*            DUBufISum -- DUBuf数组的元素个数
* 返回参数 : 无                                                             
* 补充说明 :                                                                                                      
************************************************************************************************************************
*/
void CDP_CenWifi_FrameTx(void)
{//对需要发送的数据进行组包  
  static uint8_t FrameTxBuf[CEN_TO_SIDECTRL_TXBUF_SIZE];
  uint8_t *wp;
  uint16_t i;
  uint8_t sum;
    
  sum = CalculateCheckSum(pCDP_CenSideCtrl->TxBuf, pCDP_CenSideCtrl->TxLen); 
  
  pCDP_CenSideCtrl->TxBuf[pCDP_CenSideCtrl->TxLen++] = sum;

  wp = FrameTxBuf;
  
  *wp++ = CDP_FRAME_HEADER;
  
  for(i=0; i< pCDP_CenSideCtrl->TxLen; i++)
  {
    if((CDP_FRAME_BOUNDARY == pCDP_CenSideCtrl->TxBuf[i]) || 
       (CDP_FRAME_ESC      == pCDP_CenSideCtrl->TxBuf[i]) )  /*判断5E和7E的数据，进行数据转义*/
    {
      *wp++ = CDP_FRAME_ESC;
      *wp++ = pCDP_CenSideCtrl->TxBuf[i] ^ 0x03;
    }
    else
    {
      *wp++ = pCDP_CenSideCtrl->TxBuf[i];
    }
  }
  *wp++ = CDP_FRAME_FOOTER;

//实际发送的组包动作在此  
  BSP_UART_TxData(CEN_SIDECTRL_UART_PORT,FrameTxBuf, (wp - FrameTxBuf));	 
}




/*
************************************************************************************************************************
* 函数名称 : ReceviceDataFromWifi                                                                                                    
* 功能描述 : 通信数据包   之    中心板 <--> 蓝牙  接收PDU数据处理                                                                              
* 输入参数 : void                                                                 
* 返回参数 : 无                                                             
* 补充说明 : 实时查询接收状态                                                                                                
************************************************************************************************************************
*/
void ReceviceDataFromSideBoard(void)
{
  //uint8_t  EvtMemState;

  if( FALSE == pCDP_CenSideCtrl->CSFlag.Bit.RxWifiDataOKFlag )
    return;
  pCDP_CenSideCtrl->CSFlag.Bit.RxWifiDataOKFlag = FALSE;  

  CDP_CenSideBoard.KeyValue_Byte0 = pCDP_CenSideCtrl->RxBuf[CDP_PDU_OFFSET_DU+CDP_DU_OFFSET_DATA];

	if(CDP_CenSideBoard.KeyValue_Byte0 == 0)
	{
		gCombinationKeyTime= 0;
		pCDP_CenSideCtrl->CSFlag.Bit.Key8PressingFlag = 0;
		pCDP_CenSideCtrl->CSFlag.Bit.Key8LedOnFlag = 0;
	}

	if(CDP_CenSideBoard.KeyValue_Byte0 == 8 || pCDP_CenSideCtrl->CSFlag.Bit.Key8PressingFlag == 1)
	{
			pCDP_CenSideCtrl->CSFlag.Bit.Key8PressingFlag = 1;

			if(gCombinationKeyTime < 60)
				gCombinationKeyTime++;	//50ms增加一次
			if(gCombinationKeyTime >= 60 && gCombinationKeyTime != 200)	  // 3s
			{
				gCombinationKeyTime = 200;//只执行一次
				TxResflag =1;//	  发送复位指令
				pCDP_CenSideCtrl->CSFlag.Bit.Key8LedOnFlag = 1;
			}		
	}
	else
	{
		gCombinationKeyTime= 0;
	}

  
	//if(!CtrlKeyPressFlag)
  //{
  	//gKeyValue = CDP_CenSideBoard.KeyValue_Byte0 ;//跳过手控器键值
  	//KeyPressEvent();
  //}

}

/*
************************************************************************************************************************
* 函数名称 : SendDataToWifi25ms                                                                                                         
* 功能描述 : 数据包发送                                                                                        
* 输入参数 : pEvt -- 事件                                                                                  
* 返回参数 : MEM_IDLE --  事件内存空闲，可以释放了        
*            MEM_USE  --  事件内存还在使用中，还不能释放                                                                   
* 补充说明 : 定时查询发送                                                                                                        
************************************************************************************************************************
*/

void SendDataToSideBoard100ms(void)
{    	
	//Byte2		目的地址		0x11
	//Byte3		源地址		0x01
	//Byte4		协议版本号		0
	//Byte5		预留		0
	//Byte6		命令码		0x04
	//Byte7		应答码		0xff

	pCDP_CenSideCtrl->TxBuf[0] = CDP_ADDR_SIDE;
	pCDP_CenSideCtrl->TxBuf[1] = 0x01;
	pCDP_CenSideCtrl->TxBuf[2] = 0;
	pCDP_CenSideCtrl->TxBuf[3] = 0;
	pCDP_CenSideCtrl->TxBuf[4] = 0x04;
	pCDP_CenSideCtrl->TxBuf[5] = 0xff;
	pCDP_CenSideCtrl->TxLen = 6;

	CDP_CenSideBoard.DataLenth = 0x05;
	CDP_CenSideBoard.CtrlID = 0x50;

	
	CDP_CenSideBoard.Byte1.Bit.Led1_OnFlag =  0;
	CDP_CenSideBoard.Byte1.Bit.Led2_OnFlag =  0;
	CDP_CenSideBoard.Byte1.Bit.Led3_OnFlag =  0;//NightModeRunFlag;
	CDP_CenSideBoard.Byte1.Bit.Led4_OnFlag =  0;//MiddayModeRunFlag;
	CDP_CenSideBoard.Byte1.Bit.Led5_OnFlag =  0;//SystemRunFlag;
	CDP_CenSideBoard.Byte1.Bit.Led6_OnFlag =  0;//ThaiMassageRunFlag;
	CDP_CenSideBoard.Byte1.Bit.Led7_OnFlag =  0;//MasterSelectionRunFlag;
	CDP_CenSideBoard.Byte1.Bit.Led8_OnFlag =  pCDP_CenSideCtrl->CSFlag.Bit.Key8LedOnFlag;//LumbarHeatRunFlag ||WiFiSmartConfigStartFlag;

	CDP_CenSideBoard.Byte2.Bit.Led9_OnFlag =  0;//RollerRunFlag ||RollerFeetCalvesGasRunFlag;
	CDP_CenSideBoard.Byte2.Bit.Led10_OnFlag = 0;// PauseFlag;


	memcpy((&CDP_CenSideCtrl.TxBuf[CDP_PDU_OFFSET_DU]),(uint8_t *)&CDP_CenSideBoard, CDP_CenSideBoard.DataLenth);                /*给应答缓存填充部分数据*/


	pCDP_CenSideCtrl->TxLen += CDP_CenSideBoard.DataLenth;

	//if( TRUE == pCDP_CenSideCtrl->CSFlag.Bit.SendWifiDataFlag )//如果发送标志位置起，则发送
	{//回复数据
		pCDP_CenSideCtrl->CSFlag.Bit.SendWifiDataFlag = FALSE;
		if( (CDP_ADDR_SIDE   == pCDP_CenSideCtrl->TxBuf[CDP_PDU_OFFSET_DES]))
		{
		  CDP_CenWifi_FrameTx();
		}
	}
}
/*
************************************************************************************************************************
* 函数名称 : Variable1msProcess                                                                                                    
* 功能描述 : 通信数据包   之   中心板 <--> 后台服务器  接收数据处理                                                                              
* 输入参数 : void                                                                 
* 返回参数 : 无                                                             
* 补充说明 : 将数据根据帧头帧尾为界接收下来，进行累加和判断正确后，给后续处理。                                                                                                
************************************************************************************************************************
*/
void Variable1msProcess(void)
{
  if( pCDP_CenSideCtrl->RxNothingTimer < 255 )
    pCDP_CenSideCtrl->RxNothingTimer++;
}

/*
************************************************************************************************************************
* 函数名称 : SideCtrlInit                                                                                                    
* 功能描述 :                                                                            
* 输入参数 : void                                                                 
* 返回参数 : 无                                                             
* 补充说明 :                                                                                               
************************************************************************************************************************
*/
void SideCtrlInit(void)
{
  BSP_UART_RegRxByteCB(CEN_SIDECTRL_UART_PORT, CDP_CenSideBoard_ByteRx); /*??????????*/

}




