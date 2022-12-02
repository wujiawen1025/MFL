/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：CDP.c                                                                                                         
**
**    功能描述：通信数据包。
**
**    公    司：蒙发利电子
**
**    项目名称：
**
**    平台信息：
**
**    作    者：Hzy
**
**    其他说明：
**
**    修改记录：--------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "CDP.h"
#include "IAP.h"
//#include "..\..\IAP\src\IAP.c"

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
static CDP_t  CDP;
CDP_t  *pCDP = &CDP;

extern uint8_t IAP_CDPDataObj_0x01(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t IAP_CDPDataObj_0x02(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t IAP_CDPDataObj_0x03(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t IAP_CDPDataObj_0x04(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t IAP_CDPDataObj_0x05(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t IAP_CDPDataObj_0x10(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t IAP_CDPDataObj_0x20(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);


#define   APP_PrgramAddr_Star  0x00002000
uint32_t  APP_PrgramAddr = APP_PrgramAddr_Star;

#define   GInfo_Addr       
#define   APP_Vision   0x

/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/


/*
========================================================================================================================
*【数据对象管理表】                                  【数据对象管理表】                                【数据对象管理表】
========================================================================================================================
*/
static const CDPDataObjManageTabItem_t  IAPDataObjManageTab[] = 
{
  {0x01,  B(00000000),  IAP_CDPDataObj_0x01},            /*通知目标模块进入IAP模式*/
  {0x02,  B(00000000),  IAP_CDPDataObj_0x02},            /*获取目标模块的相关升级配置信息*/
  {0x03,  B(00000000),  IAP_CDPDataObj_0x03},            /*通知目标模块准备好接收文件*/
  {0x04,  B(00000000),  IAP_CDPDataObj_0x04},            /*文件数据块信息*/
  {0x05,  B(00000000),  IAP_CDPDataObj_0x05},            /*文件数据块传输结束*/
  {0x10,  B(00000000),  IAP_CDPDataObj_0x10},            /*取消软件升级*/
  {0x20,  B(00000000),  IAP_CDPDataObj_0x20}             /*获取升级状态*/
};

#define  IAP_DATA_OBJ_MANAGE_TAB_NUM    TAB_NUM(IAPDataObjManageTab)

static uint16_t IAPCDPDataObjID(uint16_t index)
{
  if(index > (IAP_DATA_OBJ_MANAGE_TAB_NUM-1))
  {
    return INDEX_NO_MATCH;
  }
  return IAPDataObjManageTab[index].ID;
}

/*
************************************************************************************************************************
* 函数名称 : CDP_DataObjRxHandle                                                                                      
* 功能描述 : 数据对象处理                                                                                
* 输入参数 : pEvt -- 指向事件的指针，事件内的参数对象包含接收到的数据                                                                                       
* 返回参数 : MEM_IDLE -- 事件内存空闲，可以释放了        
*            MEM_USE  -- 事件内存使用中，还不能释放                                                                   
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t CDP_DataObjRxHandle(ESF_Evt_t	*pEvt)
{
  uint16_t                   index;
  uint8_t                    DataObjLen;                                               /*数据对象长度*/
  int16_t                    DURestLen;                                                /*数据单元剩余长度*/
  uint8_t                    *pRxDU;                                                   /*指向接收的数据单元*/ 
  uint8_t                    *pAckDU;                                                  /*指向应答的数据单元*/
  CDPDataObjManageTabItem_t  *DOManageTab;
  

  pRxDU     = &pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_DU];                              /*指向接收的第一个数据对象*/
  pAckDU    = &pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_DU];                             /*指向应答的第一个数据对象*/
  DURestLen = pEvt->Arg.CDPRx.RxLen - CDP_PDU_EXCEPT_DU_LEN;                           /*所有数据对象长度的总和*/
  while(DURestLen > 0)
  {
    if((pRxDU[CDP_DU_OFFSET_LEN] < 2)        ||                                        /*小于最小长度*/
       (pRxDU[CDP_DU_OFFSET_LEN] > DURestLen))                                         /*大于实际可用剩余长度*/
    {
      return MEM_IDLE;                                                                 /*数据长度错，不再处理*/
    }
    DURestLen -= pRxDU[CDP_DU_OFFSET_LEN];                                             /*数据单元剩余长度*/

    DOManageTab = (CDPDataObjManageTabItem_t*)IAPDataObjManageTab;
    index = BinarySearch(pRxDU[CDP_DU_OFFSET_ID], IAP_DATA_OBJ_MANAGE_TAB_NUM, IAPCDPDataObjID);
    
    if(INDEX_NO_MATCH == index)                                                        /*没有匹配的数据对象ID*/    
    {
      pRxDU  += pRxDU[CDP_DU_OFFSET_LEN];                                              /*指向下一个数据对象*/
      continue;                                                                        /*忽略该数据对象，处理下一个*/
      //return MEM_IDLE;                                                                 /*数据处理出错，则放弃后续数据的处理*/
    }
    else
    {
      DataObjLen = 2;                                                                  /*先默认数据对象长度为2*/
      if(DOManageTab[index].pDataHandle != NULL)
      {
        DataObjLen = DOManageTab[index].pDataHandle(pRxDU, pAckDU, pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_SRC], pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD]);
        if((CDP_DU_HANDLE_ERR == DataObjLen) || (DataObjLen < 2)) 
        {
          return MEM_IDLE;                                                             /*数据处理出错，则放弃后续数据的处理*/
        }
      }
      else
      {
        return MEM_IDLE;                                                               /*无对应的处理函数，则出错，要么补上函数，要么注释掉相应的代码*/
      }
      
      pAckDU[CDP_DU_OFFSET_LEN] = DataObjLen;                                          /*pDataHandle函数返回整个数据对象的长度*/                                           
      pAckDU[CDP_DU_OFFSET_ID]  = pRxDU[CDP_DU_OFFSET_ID];                             /*应答数据对象ID*/
      pEvt->Arg.CDPRx.AckLen   += DataObjLen;                                          /*目前应答长度*/
      pAckDU += pAckDU[CDP_DU_OFFSET_LEN];                                             /*指向下一个数据对象*/
      pRxDU  += pRxDU[CDP_DU_OFFSET_LEN];                                              /*指向下一个数据对象*/
    }    
  }
  
  return MEM_USE;  
}

/*
************************************************************************************************************************
* 函数名称 : CDP_PDURxHandle                                                                                      
* 功能描述 : 接收到的数据处理                                                                                
* 输入参数 : pEvt -- 指向事件的指针，事件内的参数对象包含接收到的数据                                                                                       
* 返回参数 : MEM_IDLE --  事件内存空闲，可以释放了        
*            MEM_USE  --  事件内存使用中，还不能释放                                                                   
* 补充说明 : 
************************************************************************************************************************
*/
uint8_t CDP_PDURxHandle(ESF_Evt_t *pEvt)
{
//  uint8_t  EvtMemState;

//  if(CDP_ADDR_SELF != pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_DES])                           /*不等于自身地址*/
//  {
//    return  MEM_IDLE;                                                                       /*地址错误，不处理*/
//  }

//  if(pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_IAP)                             /*命令：IAP升级操作 */       
//  {
//    return  MEM_IDLE;                                                                       /*不支持的命令码，该内存块可释放了*/
//  }
//  
//  if(pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_ACK] != CDP_ACK_SEND)                            /*应答：数据的主动发起方，填0xFF。*/
//  {
//    return  MEM_IDLE;                                                                        
//  }  
//  
	
//  memcpy(pEvt->Arg.CDPRx.pAckBuf, pEvt->Arg.CDPRx.pRxBuf, CDP_PDU_EXCEPT_DU_LEN);           /*给应答缓存填充部分数据*/
//  pEvt->Arg.CDPRx.AckLen = CDP_PDU_EXCEPT_DU_LEN;                                           /*目前长度*/
//  pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_DES] = pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_SRC]; /*更改相应的地址*/
//  pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_SRC] = pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_DES]; /*更改相应的地址*/
//  pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_ACK] = CDP_ACK_SUCCESS;                            /*应答：先假设成功 */

//  EvtMemState = CDP_DataObjRxHandle(pEvt);                                                  /*处理数据对象*/
//  if(EvtMemState != MEM_IDLE)                                                               /*有数据要应答*/
//  {
//    pEvt->Type = EvtCDPTx;                                                                  /*改为数据包发送事件*/
//    memcpy(pEvt->Arg.CDPTx.pTxBuf, pEvt->Arg.CDPRx.pAckBuf, pEvt->Arg.CDPRx.AckLen);        /*拷贝数据到要发送的缓存*/
//    pEvt->Arg.CDPTx.TxLen  = pEvt->Arg.CDPRx.AckLen;                                        /*要发送的长度*/
//    ESF_EvtQuene_Post(pEvt);                                                                /*投递事件*/
//  }
//  return EvtMemState;    
}

/*
************************************************************************************************************************
* 函数名称 : CDP_PDUTxHandle                                                                                                         
* 功能描述 : 数据包发送                                                                                        
* 输入参数 : pEvt -- 事件                                                                                  
* 返回参数 : MEM_IDLE --  事件内存空闲，可以释放了        
*            MEM_USE  --  事件内存还在使用中，还不能释放                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t CDP_PDUTxHandle(ESF_Evt_t *pEvt)
{
//  uint8_t TxState;
//  
//  TxState = BSP_UART_TxState_Idle;                   /*先假设串口空闲*/

//  if(CDP_ADDR_CTR == pEvt->Arg.CDPTx.pTxBuf[CDP_PDU_OFFSET_DES])            
//  {
//    TxState = CDP_XxxToCtrl_DataTx(pEvt);
//  }

//  if(BSP_UART_TxState_Busy == TxState)
//  {
//    ESF_EvtQuene_Post(pEvt);                         /*串口忙，则重新投递，等待下一次发送*/
//    return MEM_USE;                                  /*内存事件块仍在使用中*/
//  }
//  else
//  {
//    return MEM_IDLE;                                 /*事件所占内存已无用*/
//  }
}

/*
************************************************************************************************************************
* 函数名称 : CDP_PDUPackTx                                                                                                         
* 功能描述 : 通信数据包 PDU 数据打包和发送                                                                                    
* 输入参数 : DesAddr   -- 目的地址
*            Cmd       -- 命令
*            DUBuf     -- 指针数组，数组内的元素为指针，每个指针指向一个保存DU数据(应该包含数据长度和数据ID) 的内存地址。   
*            DUBufISum -- DUBuf数组的元素个数
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                        
************************************************************************************************************************
*/
void CDP_PDUPackTx(uint8_t DesAddr, uint8_t Cmd, uint8_t *DUBuf[], uint8_t DUBufISum)
{
//  ESF_Evt_t *pEvt = NULL;
//  uint8_t *wp, *rp;
//  uint16_t DULen;
//  uint8_t i;

//  pEvt = ESF_MemBuf_Get();                                                          /*申请内存块*/
//  if(NULL == pEvt)
//  {
//    return;                                                                         /*申请失败则返回*/
//  }
//  
//  pEvt->Type = EvtCDPTx;                                                            /*数据包发送事件*/
//  pEvt->Arg.CDPTx.pTxBuf = (uint8_t*)&pEvt->AppendData[0];                          /*要发送的缓存*/
//  wp = pEvt->Arg.CDPTx.pTxBuf;
//  *wp++ = DesAddr;
//  *wp++ = CDP_ADDR_SELF;
//  *wp++ = 0;
//  *wp++ = 0;
//  *wp++ = Cmd;
//  *wp++ = CDP_ACK_SEND;
//  
//  for(i=0; i<DUBufISum; i++)
//  {
//    rp = DUBuf[i];
//    DULen = rp[CDP_DU_OFFSET_LEN];
//    while(DULen--)
//    {
//      *wp++ = *rp++;
//    }
//  }

//  pEvt->Arg.CDPTx.TxLen = wp - pEvt->Arg.CDPTx.pTxBuf;                              /*要发送的长度*/
//  ESF_EvtQuene_Post(pEvt);                                                          /*投递事件*/
}


/*
************************************************************************************************************************
* 函数名称 : CDP_DataTxTmrHandle                                                                                                         
* 功能描述 : 通信数据包   之   数据发送定时处理                                                                       
* 输入参数 : 无                                                             
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
void CDP_DataTxTmrHandle(Ticker_t ExePeriod)
{

}



/*
************************************************************************************************************************
 变量定义                                                                                                     
************************************************************************************************************************
*/
extern uint16_t RxHandleFlag1;
extern uint16_t RxHandleFlag;
extern char RxData_Wifi[300];
extern uint16_t RxData_Count;
#define  SOH  0x01
#define  STX  0x02
#define  EOT  0x04
#define  ACK  0x06
#define  ACK2  0x66
#define  NAK  0x15
#define  CAN  0x18
#define  R_C  0x08

#define  CTRLZ  0x1A
#define  GETDOWN  0x1B
#define  READY  0x1C


#define  RESTORE  0x1D  


#define Finish_F    (0x00000000 + ((512*15))) 

char OTA_state = GETDOWN;
char OTA_busy = 0;
char OTA_runtime = 0;
char OTA_done = 0;	//接收到EOT置位并发送ACK,检验+成功跳转，失败getdown
char OTA_retry = 0;
char OTA_Dbuff[134];	//OTA数据接收缓存
unsigned char OTA_Dnum;	//OTA接收数据计数
unsigned char OTA_Packet = 0;	//序号记录
char Restortem = 9;
extern uint16_t TxResflag;
char s_soh[3] = {SOH,'\r','\0'};
char s_stx[3] = {STX,'\r','\0'};
char s_eot[3] = {EOT,'\r','\0'};
char s_ack[3] = {ACK,'\r','\0'};
char s_nak[3] = {NAK,'\r','\0'};
char s_can[3] = {CAN,'\r','\0'};

char *wifi_config[]={		
	"get_down\r",
	"result \"ready\"\r",				
	s_soh,//"1\r",   //SOH
  s_stx,//"2\r",   //STX
	s_eot,//"4\r",   //EOT
	s_ack,//"6\r",   //ACK
	s_nak,//"15\r",   //NAK
	s_can,//
	"c\r",
	"restore\r",
	"reboot\r",
	"mcu_version 0001\r",
	"model 17216.massage.6602a\r",
	"ble_config set 4531 0001\r"
//	{ACK,'\r'},								
//	{NAK,'\r'},				//"result \"ok\"\r",
//	{CAN,'\r'}
};

/*
************************************************************************************************************************
* 函数名称 : cellfindstr                                                                                                       
* 功能描述 : 字符串搜索                                                                             
* 输入参数 : 无                                                                              
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                        
************************************************************************************************************************
*/
char *cellfindstr(const char *str1, const char *str2)
{
    char *cp = (char*)str1;
    char *s1, *s2;
 
    if (!*str2)
        return(NULL);
 
    while (*cp)
    {
        s1 = cp;
        s2 = (char *)str2;
 
        while (*s1 && *s2 && !(*s1 - *s2))
            s1++, s2++;
 
        if (!*s2)
            return(cp);
 
        cp++;
    }
    return(NULL);
}
/*
************************************************************************************************************************
* 函数名称 : OTA_frame                                                                                                  
* 功能描述 : 通信数据包 处理                                                                            
* 输入参数 : 无                                                                              
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                        
************************************************************************************************************************
*/
uint32_t flash_bank = 0;
char OTA_frame(char *ss)
{
	unsigned char add = 0;
	unsigned char i;
	uint8_t  OpResult;
	i = ss[1]+ss[2];
	if(i!=0xff) return 2; //序列号校验失败
	if((ss[1] != OTA_Packet) && (ss[1]!=(char)(OTA_Packet+1)))
		return 3;//序列号错误
	if(ss[1] == OTA_Packet) return 0;//不需要重复变成
//	if(CRC16_Cal((uint8_t *)ss,131,0)!= (uint16_t )ss[131])
//		return 1;
	//改用CRC校验
	for(i=0; i<131;i++)add+=ss[i];
	if(add!= ss[131])return 1;	//校验失败
	

	if(0 == ((((flash_bank)*128 + 0x08004800)-0x08004800) % 2048))                /*页对齐的地址则擦除页*/ 
	{
		OpResult = BSP_FLASH_Erase((flash_bank*128 + 0x08004800));                                /*擦除要编程的页*/
		if(OpResult != SUCCESS)
		{
			 return 4;                                              /*擦出失败*/
		}
	}
	OpResult = BSP_FLASH_ProgramData((flash_bank*128 + 0x08004800),&(ss[3]),128);
	if(OpResult != SUCCESS)
	{
		return 5;                                             /*写入失败*/
	}
	OTA_Packet = ss[1];
//	校验成功－写数据到flash
//	写成功OTA_packet = ss[1];
	flash_bank++;
	return 0;
}
/*
************************************************************************************************************************
* 函数名称 : GOTO_APP                                                                                                         
* 功能描述 : 跳转到app执行                                                                              
* 输入参数 : 无                                                                              
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                        
************************************************************************************************************************
*/
//static const unsigned int ss2 __variables__((0X0000000+512*15)) =0xA5A5a5a5;  //程序同步标识
//static const uint32_t ss3 __attribute__((at(0X0002000)))=0x200004E0;

void GOTO_APP(void)
{
	uint32_t aaa;
	aaa=0xa5a5a5a5;
	if(*(__IO uint32_t *)(0x08004010) == aaa)
		return;
	
	if (((*(__IO uint32_t*)(0x08004800) & 0x2FFE0000 ) != 0x20000000))	//APP无效
	{
			//	BSP_DisInttrupt();
			//   while(++m < 1000);
			//   DelayN500ms(2);
			//   NVIC_SystemReset();
		return;
	}
	/*判断应用程序区的堆栈地址是否落在:0x20000000~0x2001ffff中，这个区间的大小为128K。即程序是否已经下载*/

	IAP_JumpToAppSection();
	
//	检测APP有效则进APP
//	否则持续getdown
}

/*
************************************************************************************************************************
* 函数名称 : cell_Sizeof                                                                                                         
* 功能描述 : 字符串长度                                                                                
* 输入参数 : 无                                                                              
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                        
************************************************************************************************************************
*/

uint16_t cell_Sizeof(uint8_t * temp)
{
	uint8_t i=0;
	while(*(temp+i))i++;
	return i;

}
/*
************************************************************************************************************************
* 函数名称 : OTA_uartget                                                                                                         
* 功能描述 : 通信数据包 处理  接受                                                                                  
* 输入参数 : 无                                                                              
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                        
************************************************************************************************************************
*/
void OTA_uartget(char *ss)     //定时扫描
{
	static char ok;
	static uint8_t OTAgetCount = 0;
  RxHandleFlag = 0;
	switch(OTA_state)
	{
		case GETDOWN:
		{
			if((cellfindstr(ss,"update_fw")!= NULL))
			{
				OTA_state = READY;
				OTA_done = 0;
			}
			else if((cellfindstr(ss,"down none")!= NULL))
			{
			 if(TxResflag)
			 {
			   OTA_state = RESTORE;  
			 }
			}
			else
			{
			  OTAgetCount++;
				if(OTAgetCount == 10)   //收到的10个数据都不为update_fw，则跳转到app
				{
					OTAgetCount = 0;
				  GOTO_APP();
				} 
			}				
			OTA_busy = 0;
		}break;
		case READY:
		{
				flash_bank = 0;
			if((cellfindstr(ss,"ok")!= NULL) || (cellfindstr(ss,"error")!= NULL))
			{
				if((cellfindstr(ss,"ok")!= NULL))
					OTA_state = NAK;
				else OTA_state = GETDOWN;    //在一段时间后会跳回app
				OTA_busy = 0;
			}
		}break;
		case NAK:
		case ACK:
		{
			if((ss[0]!=EOT) && (RxData_Count < 132))return;
			OTA_busy = 0;
			ok = OTA_frame(ss);
			if(ss[0]==EOT)
      {
				BSP_UART_TxData(BSP_UART_Port2,(uint8_t *)wifi_config[5],cell_Sizeof((uint8_t *)wifi_config[5]));
				BSP_FLASH_Erase(0x08004000);//升级完成，清升级标志
				OTA_state = ACK2;  
				OTA_busy = 0;
			}			
			else if(ok==0)//校验成功
			{
				OTA_state = ACK;
				OTA_retry = 0;
			}
			else
			{
				OTA_retry ++;
				if(OTA_retry>=10)
					OTA_state = CAN;	//重试失败取消传输
				else OTA_state = NAK;
			}
		}break;
		case ACK2:
		{
				GOTO_APP();
			  OTA_state = GETDOWN;	//完成      
		}break;
		case RESTORE:
		{
		  if((cellfindstr(ss,"ok")!= NULL))
			{
			   Restortem ++;
				 OTA_busy = 0;

			}	
      else 
			{
				OTA_busy = 0;
			  OTA_state = GETDOWN;
			}				
		}
	
	}
	RxData_Count = 0;
}
/*
************************************************************************************************************************
* 函数名称 : OTA_uartsend                                                                                                       
* 功能描述 : 通信数据包 处理  发送                                                                            
* 输入参数 : 无                                                                              
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                        
************************************************************************************************************************
*/
uint8_t  LED_flag = 0;
unsigned char t;
void OTA_uartsend()       //定时扫描
{	
	uint8_t temp1;

	if(BSP_UART_GetTxState(BSP_UART_Port2)==BSP_UART_TxState_Busy)
	{
	   return;
	}
	
	temp1 = 0xff;
	if(OTA_busy)	//判断接收超时
	{
		OTA_runtime++;
		if(OTA_runtime<10)return;
		if((OTA_state==ACK)||(OTA_state==NAK))
		{
	   	if(OTA_runtime<100)return;
		}			
		else //10秒超时
		{
			OTA_busy=0;
		}
		if(OTA_retry>=10)
			{
				OTA_state = GETDOWN;
				GOTO_APP();
			}
		else OTA_retry++;
	}
	
//	if(OTA_busy)t=0;
//	else if(t<5)
//	{
//		t++;
//		return;
//	}
	OTA_runtime = 0;
	if(Restortem == 14 && OTA_state == RESTORE)
	{
		Restortem  =9;
		TxResflag = 0;
		OTA_state = GETDOWN;
	}
	switch(OTA_state)
	{
		case GETDOWN:
		{
			LED_flag = 0;
			OTA_busy = 1;
			temp1 = 0;
		}break;
		case READY:
		{
			LED_flag  = 1;
			OTA_busy = 1;
			OTA_Packet= 0;//第一次接收到的包需要必须是1
			temp1 = 1;
		}break;
		case R_C:
			OTA_busy = 1;
			temp1 = 8;
		break;
		case NAK:
			OTA_busy = 1;
			temp1 = 6;
		break;;
		case ACK2:
    {
			LED_flag = 0;
	    GOTO_APP();
    }break;
		case ACK:
		{
			OTA_busy = 1;
			temp1 = 5;
		}break;
		case CAN:
		{
			OTA_state = GETDOWN;
			OTA_busy = 0;
			temp1 = 7;
		}break;
		case RESTORE:
		{
      OTA_busy = 1;
			temp1 = Restortem;      
		}break;
		
	}
	if(temp1 != 0xff)
	{
	  BSP_UART_TxData(BSP_UART_Port2,(uint8_t *)wifi_config[temp1],cell_Sizeof((uint8_t *)wifi_config[temp1]));
	}
	OTA_Dnum = 0;	//OTA接收复位

}
/*
========================================================================================================================
*    通信数据包功能函数管理表                  通信数据包功能函数管理表                    通信数据包功能函数管理表
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : CDP_Handle                                                                                                         
* 功能描述 : 通信数据包 处理                                                                                    
* 输入参数 : 无                                                                              
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                        
************************************************************************************************************************
*/
void CDP_Handle(void)
{
  Ticker_t lag,lagSideCtrl;
  static Ticker_t  TickCount,TickCountSideCtrl;
  	
	if(RxHandleFlag==1)	//串口接收事件--1接收过字符并且15ms没有再接收到。
		OTA_uartget(RxData_Wifi);//OTA接收数据查询    //接收在事件回调函数CDP_CtrlToXxx_ByteRx中(中断驱使)，不需要事件驱动
	
  lag = BSP_SysTicker_CalLag(TickCount);     /*计算时间差*/
  if(lag >= 50)                              /*时间差值 大于等于 执行周期*/
  {
    TickCount += lag;
//    IAP_RunSectionJudge(100);
//    IAP_LinkTimeOutCheck(100);
//		KeyScanVal();
//		LedHandle();

		OTA_uartsend();//OTA发送数据查询		//hooray发送函数会整理需要发送的内容并开发送缓存空中断，在中断中完成所有发送---不需要事件驱动
  }

/////////////////////////////////////	
	lagSideCtrl = BSP_SysTicker_CalLag(TickCountSideCtrl);     /*计算时间差*/
  if(lagSideCtrl >= 100)                              /*时间差值 大于等于 执行周期*/
  {
    TickCountSideCtrl += lagSideCtrl;
		SendDataToSideBoard100ms();
  }
/////////////////////////////////////
}



/*
************************************************************************************************************************
* 函数名称 : CDP_Init                                                                                                         
* 功能描述 : 通信数据包 初始化                                                                                 
* 输入参数 : 无                                                                              
* 返回参数 : 返回 可操作机芯功能 的结构体 的指针                                                             
* 补充说明 : 无                                                                                                        
************************************************************************************************************************
*/

CDP_t* CDP_Init(void)
{
  /*初始化相关数据------------------------------------------*/
  //memset(pCDP, 0, sizeof(CDP_t)); /*清零所有数据*/
  
  pCDP->pXxxCtrl = CDP_XxxCtrl_Init();   
	
	SideCtrlInit();
  
	return pCDP;
}
