/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣ�CDP.c                                                                                                         
**
**    ����������ͨ�����ݰ���
**
**    ��    ˾���ɷ�������
**
**    ��Ŀ���ƣ�
**
**    ƽ̨��Ϣ��
**
**    ��    �ߣ�Hzy
**
**    ����˵����
**
**    �޸ļ�¼��--------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/

/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "CDP.h"
#include "IAP.h"
//#include "..\..\IAP\src\IAP.c"

/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/


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
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/


/*
========================================================================================================================
*�����ݶ�������                                  �����ݶ�������                                �����ݶ�������
========================================================================================================================
*/
static const CDPDataObjManageTabItem_t  IAPDataObjManageTab[] = 
{
  {0x01,  B(00000000),  IAP_CDPDataObj_0x01},            /*֪ͨĿ��ģ�����IAPģʽ*/
  {0x02,  B(00000000),  IAP_CDPDataObj_0x02},            /*��ȡĿ��ģ����������������Ϣ*/
  {0x03,  B(00000000),  IAP_CDPDataObj_0x03},            /*֪ͨĿ��ģ��׼���ý����ļ�*/
  {0x04,  B(00000000),  IAP_CDPDataObj_0x04},            /*�ļ����ݿ���Ϣ*/
  {0x05,  B(00000000),  IAP_CDPDataObj_0x05},            /*�ļ����ݿ鴫�����*/
  {0x10,  B(00000000),  IAP_CDPDataObj_0x10},            /*ȡ���������*/
  {0x20,  B(00000000),  IAP_CDPDataObj_0x20}             /*��ȡ����״̬*/
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
* �������� : CDP_DataObjRxHandle                                                                                      
* �������� : ���ݶ�����                                                                                
* ������� : pEvt -- ָ���¼���ָ�룬�¼��ڵĲ�������������յ�������                                                                                       
* ���ز��� : MEM_IDLE -- �¼��ڴ���У������ͷ���        
*            MEM_USE  -- �¼��ڴ�ʹ���У��������ͷ�                                                                   
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t CDP_DataObjRxHandle(ESF_Evt_t	*pEvt)
{
  uint16_t                   index;
  uint8_t                    DataObjLen;                                               /*���ݶ��󳤶�*/
  int16_t                    DURestLen;                                                /*���ݵ�Ԫʣ�೤��*/
  uint8_t                    *pRxDU;                                                   /*ָ����յ����ݵ�Ԫ*/ 
  uint8_t                    *pAckDU;                                                  /*ָ��Ӧ������ݵ�Ԫ*/
  CDPDataObjManageTabItem_t  *DOManageTab;
  

  pRxDU     = &pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_DU];                              /*ָ����յĵ�һ�����ݶ���*/
  pAckDU    = &pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_DU];                             /*ָ��Ӧ��ĵ�һ�����ݶ���*/
  DURestLen = pEvt->Arg.CDPRx.RxLen - CDP_PDU_EXCEPT_DU_LEN;                           /*�������ݶ��󳤶ȵ��ܺ�*/
  while(DURestLen > 0)
  {
    if((pRxDU[CDP_DU_OFFSET_LEN] < 2)        ||                                        /*С����С����*/
       (pRxDU[CDP_DU_OFFSET_LEN] > DURestLen))                                         /*����ʵ�ʿ���ʣ�೤��*/
    {
      return MEM_IDLE;                                                                 /*���ݳ��ȴ����ٴ���*/
    }
    DURestLen -= pRxDU[CDP_DU_OFFSET_LEN];                                             /*���ݵ�Ԫʣ�೤��*/

    DOManageTab = (CDPDataObjManageTabItem_t*)IAPDataObjManageTab;
    index = BinarySearch(pRxDU[CDP_DU_OFFSET_ID], IAP_DATA_OBJ_MANAGE_TAB_NUM, IAPCDPDataObjID);
    
    if(INDEX_NO_MATCH == index)                                                        /*û��ƥ������ݶ���ID*/    
    {
      pRxDU  += pRxDU[CDP_DU_OFFSET_LEN];                                              /*ָ����һ�����ݶ���*/
      continue;                                                                        /*���Ը����ݶ��󣬴�����һ��*/
      //return MEM_IDLE;                                                                 /*���ݴ������������������ݵĴ���*/
    }
    else
    {
      DataObjLen = 2;                                                                  /*��Ĭ�����ݶ��󳤶�Ϊ2*/
      if(DOManageTab[index].pDataHandle != NULL)
      {
        DataObjLen = DOManageTab[index].pDataHandle(pRxDU, pAckDU, pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_SRC], pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD]);
        if((CDP_DU_HANDLE_ERR == DataObjLen) || (DataObjLen < 2)) 
        {
          return MEM_IDLE;                                                             /*���ݴ������������������ݵĴ���*/
        }
      }
      else
      {
        return MEM_IDLE;                                                               /*�޶�Ӧ�Ĵ������������Ҫô���Ϻ�����Ҫôע�͵���Ӧ�Ĵ���*/
      }
      
      pAckDU[CDP_DU_OFFSET_LEN] = DataObjLen;                                          /*pDataHandle���������������ݶ���ĳ���*/                                           
      pAckDU[CDP_DU_OFFSET_ID]  = pRxDU[CDP_DU_OFFSET_ID];                             /*Ӧ�����ݶ���ID*/
      pEvt->Arg.CDPRx.AckLen   += DataObjLen;                                          /*ĿǰӦ�𳤶�*/
      pAckDU += pAckDU[CDP_DU_OFFSET_LEN];                                             /*ָ����һ�����ݶ���*/
      pRxDU  += pRxDU[CDP_DU_OFFSET_LEN];                                              /*ָ����һ�����ݶ���*/
    }    
  }
  
  return MEM_USE;  
}

/*
************************************************************************************************************************
* �������� : CDP_PDURxHandle                                                                                      
* �������� : ���յ������ݴ���                                                                                
* ������� : pEvt -- ָ���¼���ָ�룬�¼��ڵĲ�������������յ�������                                                                                       
* ���ز��� : MEM_IDLE --  �¼��ڴ���У������ͷ���        
*            MEM_USE  --  �¼��ڴ�ʹ���У��������ͷ�                                                                   
* ����˵�� : 
************************************************************************************************************************
*/
uint8_t CDP_PDURxHandle(ESF_Evt_t *pEvt)
{
//  uint8_t  EvtMemState;

//  if(CDP_ADDR_SELF != pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_DES])                           /*�����������ַ*/
//  {
//    return  MEM_IDLE;                                                                       /*��ַ���󣬲�����*/
//  }

//  if(pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_IAP)                             /*���IAP�������� */       
//  {
//    return  MEM_IDLE;                                                                       /*��֧�ֵ������룬���ڴ����ͷ���*/
//  }
//  
//  if(pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_ACK] != CDP_ACK_SEND)                            /*Ӧ�����ݵ��������𷽣���0xFF��*/
//  {
//    return  MEM_IDLE;                                                                        
//  }  
//  
	
//  memcpy(pEvt->Arg.CDPRx.pAckBuf, pEvt->Arg.CDPRx.pRxBuf, CDP_PDU_EXCEPT_DU_LEN);           /*��Ӧ�𻺴���䲿������*/
//  pEvt->Arg.CDPRx.AckLen = CDP_PDU_EXCEPT_DU_LEN;                                           /*Ŀǰ����*/
//  pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_DES] = pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_SRC]; /*������Ӧ�ĵ�ַ*/
//  pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_SRC] = pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_DES]; /*������Ӧ�ĵ�ַ*/
//  pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_ACK] = CDP_ACK_SUCCESS;                            /*Ӧ���ȼ���ɹ� */

//  EvtMemState = CDP_DataObjRxHandle(pEvt);                                                  /*�������ݶ���*/
//  if(EvtMemState != MEM_IDLE)                                                               /*������ҪӦ��*/
//  {
//    pEvt->Type = EvtCDPTx;                                                                  /*��Ϊ���ݰ������¼�*/
//    memcpy(pEvt->Arg.CDPTx.pTxBuf, pEvt->Arg.CDPRx.pAckBuf, pEvt->Arg.CDPRx.AckLen);        /*�������ݵ�Ҫ���͵Ļ���*/
//    pEvt->Arg.CDPTx.TxLen  = pEvt->Arg.CDPRx.AckLen;                                        /*Ҫ���͵ĳ���*/
//    ESF_EvtQuene_Post(pEvt);                                                                /*Ͷ���¼�*/
//  }
//  return EvtMemState;    
}

/*
************************************************************************************************************************
* �������� : CDP_PDUTxHandle                                                                                                         
* �������� : ���ݰ�����                                                                                        
* ������� : pEvt -- �¼�                                                                                  
* ���ز��� : MEM_IDLE --  �¼��ڴ���У������ͷ���        
*            MEM_USE  --  �¼��ڴ滹��ʹ���У��������ͷ�                                                                   
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t CDP_PDUTxHandle(ESF_Evt_t *pEvt)
{
//  uint8_t TxState;
//  
//  TxState = BSP_UART_TxState_Idle;                   /*�ȼ��贮�ڿ���*/

//  if(CDP_ADDR_CTR == pEvt->Arg.CDPTx.pTxBuf[CDP_PDU_OFFSET_DES])            
//  {
//    TxState = CDP_XxxToCtrl_DataTx(pEvt);
//  }

//  if(BSP_UART_TxState_Busy == TxState)
//  {
//    ESF_EvtQuene_Post(pEvt);                         /*����æ��������Ͷ�ݣ��ȴ���һ�η���*/
//    return MEM_USE;                                  /*�ڴ��¼�������ʹ����*/
//  }
//  else
//  {
//    return MEM_IDLE;                                 /*�¼���ռ�ڴ�������*/
//  }
}

/*
************************************************************************************************************************
* �������� : CDP_PDUPackTx                                                                                                         
* �������� : ͨ�����ݰ� PDU ���ݴ���ͷ���                                                                                    
* ������� : DesAddr   -- Ŀ�ĵ�ַ
*            Cmd       -- ����
*            DUBuf     -- ָ�����飬�����ڵ�Ԫ��Ϊָ�룬ÿ��ָ��ָ��һ������DU����(Ӧ�ð������ݳ��Ⱥ�����ID) ���ڴ��ַ��   
*            DUBufISum -- DUBuf�����Ԫ�ظ���
* ���ز��� : ��                                                             
* ����˵�� : ��                                                                                                        
************************************************************************************************************************
*/
void CDP_PDUPackTx(uint8_t DesAddr, uint8_t Cmd, uint8_t *DUBuf[], uint8_t DUBufISum)
{
//  ESF_Evt_t *pEvt = NULL;
//  uint8_t *wp, *rp;
//  uint16_t DULen;
//  uint8_t i;

//  pEvt = ESF_MemBuf_Get();                                                          /*�����ڴ��*/
//  if(NULL == pEvt)
//  {
//    return;                                                                         /*����ʧ���򷵻�*/
//  }
//  
//  pEvt->Type = EvtCDPTx;                                                            /*���ݰ������¼�*/
//  pEvt->Arg.CDPTx.pTxBuf = (uint8_t*)&pEvt->AppendData[0];                          /*Ҫ���͵Ļ���*/
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

//  pEvt->Arg.CDPTx.TxLen = wp - pEvt->Arg.CDPTx.pTxBuf;                              /*Ҫ���͵ĳ���*/
//  ESF_EvtQuene_Post(pEvt);                                                          /*Ͷ���¼�*/
}


/*
************************************************************************************************************************
* �������� : CDP_DataTxTmrHandle                                                                                                         
* �������� : ͨ�����ݰ�   ֮   ���ݷ��Ͷ�ʱ����                                                                       
* ������� : ��                                                             
* ���ز��� : ��                                                             
* ����˵�� : ��                                                                                                  
************************************************************************************************************************
*/
void CDP_DataTxTmrHandle(Ticker_t ExePeriod)
{

}



/*
************************************************************************************************************************
 ��������                                                                                                     
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
char OTA_done = 0;	//���յ�EOT��λ������ACK,����+�ɹ���ת��ʧ��getdown
char OTA_retry = 0;
char OTA_Dbuff[134];	//OTA���ݽ��ջ���
unsigned char OTA_Dnum;	//OTA�������ݼ���
unsigned char OTA_Packet = 0;	//��ż�¼
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
* �������� : cellfindstr                                                                                                       
* �������� : �ַ�������                                                                             
* ������� : ��                                                                              
* ���ز��� : ��                                                             
* ����˵�� : ��                                                                                                        
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
* �������� : OTA_frame                                                                                                  
* �������� : ͨ�����ݰ� ����                                                                            
* ������� : ��                                                                              
* ���ز��� : ��                                                             
* ����˵�� : ��                                                                                                        
************************************************************************************************************************
*/
uint32_t flash_bank = 0;
char OTA_frame(char *ss)
{
	unsigned char add = 0;
	unsigned char i;
	uint8_t  OpResult;
	i = ss[1]+ss[2];
	if(i!=0xff) return 2; //���к�У��ʧ��
	if((ss[1] != OTA_Packet) && (ss[1]!=(char)(OTA_Packet+1)))
		return 3;//���кŴ���
	if(ss[1] == OTA_Packet) return 0;//����Ҫ�ظ����
//	if(CRC16_Cal((uint8_t *)ss,131,0)!= (uint16_t )ss[131])
//		return 1;
	//����CRCУ��
	for(i=0; i<131;i++)add+=ss[i];
	if(add!= ss[131])return 1;	//У��ʧ��
	

	if(0 == ((((flash_bank)*128 + 0x08004800)-0x08004800) % 2048))                /*ҳ����ĵ�ַ�����ҳ*/ 
	{
		OpResult = BSP_FLASH_Erase((flash_bank*128 + 0x08004800));                                /*����Ҫ��̵�ҳ*/
		if(OpResult != SUCCESS)
		{
			 return 4;                                              /*����ʧ��*/
		}
	}
	OpResult = BSP_FLASH_ProgramData((flash_bank*128 + 0x08004800),&(ss[3]),128);
	if(OpResult != SUCCESS)
	{
		return 5;                                             /*д��ʧ��*/
	}
	OTA_Packet = ss[1];
//	У��ɹ���д���ݵ�flash
//	д�ɹ�OTA_packet = ss[1];
	flash_bank++;
	return 0;
}
/*
************************************************************************************************************************
* �������� : GOTO_APP                                                                                                         
* �������� : ��ת��appִ��                                                                              
* ������� : ��                                                                              
* ���ز��� : ��                                                             
* ����˵�� : ��                                                                                                        
************************************************************************************************************************
*/
//static const unsigned int ss2 __variables__((0X0000000+512*15)) =0xA5A5a5a5;  //����ͬ����ʶ
//static const uint32_t ss3 __attribute__((at(0X0002000)))=0x200004E0;

void GOTO_APP(void)
{
	uint32_t aaa;
	aaa=0xa5a5a5a5;
	if(*(__IO uint32_t *)(0x08004010) == aaa)
		return;
	
	if (((*(__IO uint32_t*)(0x08004800) & 0x2FFE0000 ) != 0x20000000))	//APP��Ч
	{
			//	BSP_DisInttrupt();
			//   while(++m < 1000);
			//   DelayN500ms(2);
			//   NVIC_SystemReset();
		return;
	}
	/*�ж�Ӧ�ó������Ķ�ջ��ַ�Ƿ�����:0x20000000~0x2001ffff�У��������Ĵ�СΪ128K���������Ƿ��Ѿ�����*/

	IAP_JumpToAppSection();
	
//	���APP��Ч���APP
//	�������getdown
}

/*
************************************************************************************************************************
* �������� : cell_Sizeof                                                                                                         
* �������� : �ַ�������                                                                                
* ������� : ��                                                                              
* ���ز��� : ��                                                             
* ����˵�� : ��                                                                                                        
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
* �������� : OTA_uartget                                                                                                         
* �������� : ͨ�����ݰ� ����  ����                                                                                  
* ������� : ��                                                                              
* ���ز��� : ��                                                             
* ����˵�� : ��                                                                                                        
************************************************************************************************************************
*/
void OTA_uartget(char *ss)     //��ʱɨ��
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
				if(OTAgetCount == 10)   //�յ���10�����ݶ���Ϊupdate_fw������ת��app
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
				else OTA_state = GETDOWN;    //��һ��ʱ��������app
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
				BSP_FLASH_Erase(0x08004000);//������ɣ���������־
				OTA_state = ACK2;  
				OTA_busy = 0;
			}			
			else if(ok==0)//У��ɹ�
			{
				OTA_state = ACK;
				OTA_retry = 0;
			}
			else
			{
				OTA_retry ++;
				if(OTA_retry>=10)
					OTA_state = CAN;	//����ʧ��ȡ������
				else OTA_state = NAK;
			}
		}break;
		case ACK2:
		{
				GOTO_APP();
			  OTA_state = GETDOWN;	//���      
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
* �������� : OTA_uartsend                                                                                                       
* �������� : ͨ�����ݰ� ����  ����                                                                            
* ������� : ��                                                                              
* ���ز��� : ��                                                             
* ����˵�� : ��                                                                                                        
************************************************************************************************************************
*/
uint8_t  LED_flag = 0;
unsigned char t;
void OTA_uartsend()       //��ʱɨ��
{	
	uint8_t temp1;

	if(BSP_UART_GetTxState(BSP_UART_Port2)==BSP_UART_TxState_Busy)
	{
	   return;
	}
	
	temp1 = 0xff;
	if(OTA_busy)	//�жϽ��ճ�ʱ
	{
		OTA_runtime++;
		if(OTA_runtime<10)return;
		if((OTA_state==ACK)||(OTA_state==NAK))
		{
	   	if(OTA_runtime<100)return;
		}			
		else //10�볬ʱ
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
			OTA_Packet= 0;//��һ�ν��յ��İ���Ҫ������1
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
	OTA_Dnum = 0;	//OTA���ո�λ

}
/*
========================================================================================================================
*    ͨ�����ݰ����ܺ��������                  ͨ�����ݰ����ܺ��������                    ͨ�����ݰ����ܺ��������
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : CDP_Handle                                                                                                         
* �������� : ͨ�����ݰ� ����                                                                                    
* ������� : ��                                                                              
* ���ز��� : ��                                                             
* ����˵�� : ��                                                                                                        
************************************************************************************************************************
*/
void CDP_Handle(void)
{
  Ticker_t lag,lagSideCtrl;
  static Ticker_t  TickCount,TickCountSideCtrl;
  	
	if(RxHandleFlag==1)	//���ڽ����¼�--1���չ��ַ�����15msû���ٽ��յ���
		OTA_uartget(RxData_Wifi);//OTA�������ݲ�ѯ    //�������¼��ص�����CDP_CtrlToXxx_ByteRx��(�ж���ʹ)������Ҫ�¼�����
	
  lag = BSP_SysTicker_CalLag(TickCount);     /*����ʱ���*/
  if(lag >= 50)                              /*ʱ���ֵ ���ڵ��� ִ������*/
  {
    TickCount += lag;
//    IAP_RunSectionJudge(100);
//    IAP_LinkTimeOutCheck(100);
//		KeyScanVal();
//		LedHandle();

		OTA_uartsend();//OTA�������ݲ�ѯ		//hooray���ͺ�����������Ҫ���͵����ݲ������ͻ�����жϣ����ж���������з���---����Ҫ�¼�����
  }

/////////////////////////////////////	
	lagSideCtrl = BSP_SysTicker_CalLag(TickCountSideCtrl);     /*����ʱ���*/
  if(lagSideCtrl >= 100)                              /*ʱ���ֵ ���ڵ��� ִ������*/
  {
    TickCountSideCtrl += lagSideCtrl;
		SendDataToSideBoard100ms();
  }
/////////////////////////////////////
}



/*
************************************************************************************************************************
* �������� : CDP_Init                                                                                                         
* �������� : ͨ�����ݰ� ��ʼ��                                                                                 
* ������� : ��                                                                              
* ���ز��� : ���� �ɲ�����о���� �Ľṹ�� ��ָ��                                                             
* ����˵�� : ��                                                                                                        
************************************************************************************************************************
*/

CDP_t* CDP_Init(void)
{
  /*��ʼ���������------------------------------------------*/
  //memset(pCDP, 0, sizeof(CDP_t)); /*������������*/
  
  pCDP->pXxxCtrl = CDP_XxxCtrl_Init();   
	
	SideCtrlInit();
  
	return pCDP;
}
