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
#include "MChair.h"
#include "Server.h"

/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/                                                                
#define  CDP_REPEATER_LTL_MS                   15000              /*ת������Ծʱ�� LTL(Lively time length)����λ����*/


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

static const SysMode_KeyVal_t SideCtrlKeyValMapTab[] = 
{
  KEYVAL_NoPress,                    // key00:
  KEYVAL_HeatLumbarBack,             // key01:
  KEYVAL_RollerFeet,                 // key02:
  KEYVAL_SpikeFeetDown,              // key03:
  KEYVAL_SpikeFeetUp,                // key04:
  KEYVAL_SpikeBackUpFeetDown,        // key05:
  KEYVAL_SpikeBackDownFeetUp,        // key06:
  KEYVAL_AutoQuick,                  // key07:
  KEYVAL_SpikeZeroGravity,           // key08:
  KEYVAL_Pause,                      // key09:
  KEYVAL_NoPress,                    // key10:
  KEYVAL_CoreMannualFront,           // key11:
  KEYVAL_CoreMannualBack,            // key12:
};


extern uint8_t Server_GetKeyExeState(void);
/*�������ݴ����������ݴ������ֲ��ڸ�����Ӧ�����ģ���У�*/
extern uint8_t  MChair_KeyValHandle_CDPDataObjRx_0x01(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);

extern uint8_t  MChair_TabTry_CDPDataObjRx_0x1A_To_0x1F(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);

extern uint8_t  SaveData_CDPDataObjRx_0x3D(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t  SaveData_CDPDataObjRx_0x3E(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);


extern uint8_t  Core_CDPDataObjRx_0x40(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t* Core_CDPDataObjTx_0x40(void);

extern uint8_t  Heat_CDPDataObjRx_0x41(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t* Heat_CDPDataObjTx_0x41(void);


extern uint8_t Gas_CDPDataObjRx_0x48(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t* Gas_CDPDataObjTx_0x48(void);

extern uint8_t Roller_CDPDataObjRx_0x49(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t* Roller_CDPDataObjTx_0x49(void);

extern uint8_t Vib_CDPDataObjRx_0x4A(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t* Vib_CDPDataObjTx_0x4A(void);

extern uint8_t LegFlexSpike_CDPDataObjRx_0x4B(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t* LegFlexSpike_CDPDataObjTx_0x4B(void);

uint8_t  SideCtrl_CDPDataObjRx_0x50(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t* SideCtrl_CDPDataObjTx_0x50(Ticker_t ExePeriod);

/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : IAP_CDPDataObj_0x01                                                                                      
* �������� : ֪ͨĿ��ģ�����IAPģʽ                                                                                 
* ������� : pRxDU  -- ָ����յ����ݶ���Ԫ
*            pAckDU -- ָ��Ӧ������ݶ���Ԫ
* ���ز��� : �����ݶ��������ݵĳ���                                                                                                    
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t IAP_CDPDataObj_0x01(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  uint16_t i;
  /*�������Ȼ��λ����λ�����BootLoadeģʽ*/
  BSP_IO_SetOutput_CloseAll();
  while(++i < 1000);
  BSP_SystemReset();  
  return 0;
}

/*
========================================================================================================================
*�����ݶ�������                                  �����ݶ�������                                �����ݶ�������
========================================================================================================================
*/
static const CDPDataObjManageTabItem_t  DataObjManageTab[] = 
{
  {0x01,  B(00000000),  MChair_KeyValHandle_CDPDataObjRx_0x01},     /*0x01 ��ֵ(�ֿ���-->���İ�)*/
  {0x1A,  B(00000000),  MChair_TabTry_CDPDataObjRx_0x1A_To_0x1F},   /*0x1A ������ ͨ��0(��λ��<-->���İ�)*/
  {0x1B,  B(00000000),  MChair_TabTry_CDPDataObjRx_0x1A_To_0x1F},   /*0x1B ������ ͨ��1(��λ��<-->���İ�)*/
//  {0x20,  B(00000000),  NULL},                                      /*0x20 ״̬��Ϣ���ܰ������İ�-->�ֿ�����*/
  {0x3D,  B(00000000),  SaveData_CDPDataObjRx_0x3D},                /*0x3D ���������Ϣ*/
  {0x3E,  B(00000000),  SaveData_CDPDataObjRx_0x3E},                /*0x3E ����������*/
//  {0x3F,  B(00000000),  NULL},                                      /*0x3F ϵͳ����������ʱ��*/
  
  {0x40,  B(00000000),  Core_CDPDataObjRx_0x40},                    /*0x40 ��о�ַ�����(���İ�<-->��о�壩*/
  {0x41,  B(00000000),  Heat_CDPDataObjRx_0x41},                    /*0x41 ��Ħͷ���ȿ���(���İ�<-->��о�壩 */
  {0x48,  B(00000000),  Gas_CDPDataObjRx_0x48},                     /*0x48 �Ƚų�������(���İ�<-->�Ƚſ��ư壩*/
  {0x49,  B(00000000),  Roller_CDPDataObjRx_0x49},                  /*0x49 �ȽŹ��ֿ���(���İ�<-->�Ƚſ��ư壩*/
  {0x4A,  B(00000000),  Vib_CDPDataObjRx_0x4A},                      /*0x4A �Ƚ��񶯿���(���İ�<-->�Ƚſ��ư壩*/
  {0x4B,  B(00000000),  LegFlexSpike_CDPDataObjRx_0x4B},            /*0x4B �Ƚ���������(���İ�<-->�Ƚſ��ư壩*/
//  {0x4C,  B(00000000),  Heat_CDPDataObjRx_0x4C},                    /*0x4C �Ƚż��ȿ���(���İ�<-->�Ƚſ��ư壩*/
  {0x50,  B(00000000),  SideCtrl_CDPDataObjRx_0x50}                 /*0x50 ��������(��������-->���İ�) */
};

#define  DATA_OBJ_MANAGE_TAB_NUM    TAB_NUM(DataObjManageTab)

static uint16_t CDPDataObjID(uint16_t index)
{
  if(index > (DATA_OBJ_MANAGE_TAB_NUM-1))
  {
    return INDEX_NO_MATCH;
  }
  return DataObjManageTab[index].ID;
}


static const CDPDataObjManageTabItem_t  IAPDataObjManageTab[] = 
{
  {0x01,  B(00000000),  IAP_CDPDataObj_0x01}            /*֪ͨĿ��ģ�����IAPģʽ*/
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

static const CDPDataObjManageTabItem_Server_t  ServerDataObjManageTab[] = 
{
  {0x0040,  B(00000000),  Server_CDPDataObjRX_0x0040},            /*���յ��豸���кŻش�����*/
//  {0x0041,  B(00000000),  Server_CDPDataObj_0x0041},          /*���յ��������ش�����*/
  {0x0042,  B(00000000),  Server_CDPDataObjRX_0x0042},            /*���յ����İ�汾�Żش�����*/
  {0x0043,  B(00000000),  Server_CDPDataObjRX_0x0043},            /*���յ��豸Զ��������ʽ�ش�����*/
  {0x0702,  B(00000000),  Server_CDPDataObjRX_0x0702},            /*���ռ�ֵ*/
  {0x0901,  B(00000000),  Server_CDPDataObjRX_0x0901},            /*��ȡ��Ħ�ο���״̬*/
  {0x0912,  B(00000000),  Server_CDPDataObjRX_0x0912},            /*��������*/
  {0x0913,  B(00000000),  Server_CDPDataObjRX_0x0913},            /*��ȡ�豸ID*/
  {0x0C60,  B(00000000),  Server_CDPDataObjRX_0x0C60},            /*��ȡ����״̬*/
  {0x0D01,  B(00000000),  Server_CDPDataObjRX_0x0D01},            /*��Ħ��״̬����1 ����*/
  {0x0D02,  B(00000000),  Server_CDPDataObjRX_0x0D02},            /*��Ħ��״̬����2 �ػ�*/
};

#define  SERVER_DATA_OBJ_MANAGE_TAB_NUM    TAB_NUM(ServerDataObjManageTab)

static uint16_t ServerCDPDataObjID(uint16_t index)
{
  if(index > (SERVER_DATA_OBJ_MANAGE_TAB_NUM-1))
  {
    return INDEX_NO_MATCH;
  }
  return ServerDataObjManageTab[index].ID;
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
  uint16_t                    ServerTemp;
  CDPDataObjManageTabItem_t  *DOManageTab;
  

  pRxDU  = &pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_DU];                                 /*ָ����յĵ�һ�����ݶ���*/
  pAckDU = &pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_DU];                                /*ָ��Ӧ��ĵ�һ�����ݶ���*/
  DURestLen  = pEvt->Arg.CDPRx.RxLen - CDP_PDU_EXCEPT_DU_LEN;                          /*�������ݶ��󳤶ȵ��ܺ�*/
  while(DURestLen > 0)
  {
    if((pRxDU[CDP_DU_OFFSET_LEN] < 2)        ||                                        /*С����С����*/
       (pRxDU[CDP_DU_OFFSET_LEN] > DURestLen))                                         /*����ʵ�ʿ���ʣ�೤��*/
    {
      return MEM_IDLE;                                                                 /*���ݳ��ȴ����ٴ���*/
    }
    DURestLen -= pRxDU[CDP_DU_OFFSET_LEN];                                             /*���ݵ�Ԫʣ�೤��*/

    if( (CDP_CMD_IAP         == pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD]) ||
        (CDP_CMD_REMOTE_IAP  == pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD]) )          /*��ͬ�������Ӧ��ͬ�����ݶ�����*/
    {
      DOManageTab = (CDPDataObjManageTabItem_t*)IAPDataObjManageTab;
      index = 0;//BinarySearch(pRxDU[CDP_DU_OFFSET_ID], IAP_DATA_OBJ_MANAGE_TAB_NUM, IAPCDPDataObjID);
    }
    else if(0x80 == pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_VER])
    {
      DOManageTab = (CDPDataObjManageTabItem_t*)ServerDataObjManageTab;
      ServerTemp = pRxDU[CDP_DU_OFFSET_ID]<<8;
      ServerTemp = ServerTemp | pRxDU[CDP_DU_OFFSET_SERVER_ID];
      index = BinarySearch(ServerTemp, SERVER_DATA_OBJ_MANAGE_TAB_NUM, ServerCDPDataObjID);
    }
    else
    {
      DOManageTab = (CDPDataObjManageTabItem_t*)DataObjManageTab;
      index = BinarySearch(pRxDU[CDP_DU_OFFSET_ID], DATA_OBJ_MANAGE_TAB_NUM, CDPDataObjID);
    }
    
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
      if( pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_VER] == 0x80 )                         /*����������*/
      {
        pAckDU[CDP_DU_OFFSET_ID]        = pRxDU[CDP_DU_OFFSET_ID];                     /*Ӧ�����ݶ���ID*/
        pAckDU[CDP_DU_OFFSET_SERVER_ID] = pRxDU[CDP_DU_OFFSET_SERVER_ID];              /*Ӧ�����ݶ���ID*/
      }
      else                                                                             /*��������*/
      {
        pAckDU[CDP_DU_OFFSET_ID]  = pRxDU[CDP_DU_OFFSET_ID];                           /*Ӧ�����ݶ���ID*/
      }
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
  uint8_t  EvtMemState;


  /*��ַ�ж�-----------------------------------------------------------------------------------*/
  if(CDP_ADDR_SELF != pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_DES])                             /*�����������ַ*/
  {
    if(CDP_ADDR_SELF == CDP_ADDR_CEN)                                                         /*����Ϊ���İ壬�����İ�Ҫת�����ݸ�����ͨ��ģ��*/
    {
      pCDP->RepeaterLTL = CDP_REPEATER_LTL_MS;                                                /*ÿ�ζ������趨ת�����Ļ�Ծʱ��*/ 
      
      pEvt->Type = EvtCDPTx;                                                                  /*��Ϊ���ݰ������¼�*/
      memcpy(pEvt->Arg.CDPTx.pTxBuf, pEvt->Arg.CDPRx.pRxBuf, pEvt->Arg.CDPRx.RxLen);          /*�������ݵ�Ҫ���͵Ļ���*/
      pEvt->Arg.CDPTx.TxLen  = pEvt->Arg.CDPRx.RxLen;                                         /*Ҫ���͵ĳ���ֱ�ӵ��ڽ��ճ���*/
      ESF_EvtQuene_Post(pEvt);                                                                /*Ͷ���¼�*/
      return  MEM_USE;    
    }
    else //if(CDP_ADDR_SELF != CDP_ADDR_CEN) 
    {
      return  MEM_IDLE;                                                                       /*��ַ���󣬲�����*/
    }
  }

  /*�����ж�-----------------------------------------------------------------------------------*/
  if((pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_SET_ACK)         &&               /*����������ôӻ����ӻ���Ӧ�� */      
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_SET_NACK)        &&               /*����������ôӻ����ӻ�����Ӧ�� */        
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_UPREPORT)        &&               /*����ӻ������ϱ� */        
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_QRY)             &&               /*���������ѯ�ӻ� */       
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_IAP)             &&               /*���IAP�������� */       
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_UPREPORT_SERVER) &&               /*��������� �ӻ������ϱ�*/
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_QRY_SERVER)      &&               /*��������� ������ѯ�ӻ�*/
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_SET_NACK_SERVER) &&               /*��������� �������ôӻ����ӻ�����Ӧ��*/
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_SET_ACK_SERVER)  &&               /*��������� �������ôӻ����ӻ���Ӧ��*/ 
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_REMOTE_IAP) )                     /*���Զ��IAP�������� */
  {
    pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_ACK] = CDP_ACK_INVALID_CMD;                        /*Ӧ�𣺲�֧�ֵ������� */
    return  MEM_IDLE;                                                                         /*��֧�ֵ������룬���ڴ����ͷ���*/
  }
  
  /*��ģ����Ϊ�߼��ӻ�-------------------------------------------------------------------------*/
  if((CDP_ACK_SEND     == pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_ACK]) &&                      /*Ӧ�����ݵ��������𷽣���0xFF��*/
     (CDP_CMD_UPREPORT != pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD]) )                       /*������� �ӻ������ϱ� */                      
  {
    memcpy(pEvt->Arg.CDPRx.pAckBuf, pEvt->Arg.CDPRx.pRxBuf, CDP_PDU_EXCEPT_DU_LEN);           /*��Ӧ�𻺴���䲿������*/
    pEvt->Arg.CDPRx.AckLen = CDP_PDU_EXCEPT_DU_LEN;                                           /*Ŀǰ����*/
    pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_DES] = pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_SRC]; /*������Ӧ�ĵ�ַ*/
    pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_SRC] = pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_DES]; /*������Ӧ�ĵ�ַ*/
    pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_ACK] = CDP_ACK_SUCCESS;                            /*Ӧ���ȼ���ɹ� */
    
    EvtMemState = CDP_DataObjRxHandle(pEvt);                                                  /*�������ݶ���*/

    if((EvtMemState != MEM_IDLE) &&                                                           /*������ҪӦ��*/
       (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_SET_NACK))                      /*��CDP_CMD_SET_NACK ����������ôӻ����ӻ�����Ӧ�� */        
    {
      if(FALSE == Server_GetCSFlag().KeyExeState)
      {
        pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_ACK] = CDP_ACK_FAIL;
        Server_SetKeyExeState(TRUE);
      }
      pEvt->Type = EvtCDPTx;                                                                  /*��Ϊ���ݰ������¼�*/
      memcpy(pEvt->Arg.CDPTx.pTxBuf, pEvt->Arg.CDPRx.pAckBuf, pEvt->Arg.CDPRx.AckLen);        /*�������ݵ�Ҫ���͵Ļ���*/
      pEvt->Arg.CDPTx.TxLen  = pEvt->Arg.CDPRx.AckLen;                                        /*Ҫ���͵ĳ���*/
      ESF_EvtQuene_Post(pEvt);                                                                /*Ͷ���¼�*/
      return  MEM_USE;    
    }
    else
    {
      return MEM_IDLE;    
    }
  }
  
  /*��ģ����Ϊ�߼�����-------------------------------------------------------------------------*/
  else if((CDP_ACK_SUCCESS  == pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_ACK]) ||                 /*Ӧ��ִ�гɹ������յ�����ģ�����Ӧ���ݡ�*/              
          (CDP_CMD_UPREPORT == pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD]) )                  /*����ӻ������ϱ� */                      
  {
    CDP_DataObjRxHandle(pEvt);                                                                /*�������ݶ���*/
    return  MEM_IDLE;                                                                         /*��������Ӧ�󣬸��ڴ����ͷ���*/
  }
  
  /*����---------------------------------------------------------------------------------------*/
  return  MEM_IDLE;                                                                           /*���󣬲�����*/
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
  uint8_t TxState;
  
  TxState = BSP_UART_TxState_Idle;                   /*�ȼ��贮�ڿ���*/

  if(CDP_ADDR_CTR == pEvt->Arg.CDPTx.pTxBuf[CDP_PDU_OFFSET_DES])            
  {
    TxState = CDP_CenApp_DataTx(pEvt);
  }
  else if( (CDP_ADDR_CORE        == pEvt->Arg.CDPTx.pTxBuf[CDP_PDU_OFFSET_DES]) ||
           (CDP_ADDR_CTR_SIDE    == pEvt->Arg.CDPTx.pTxBuf[CDP_PDU_OFFSET_DES]) ||
           (CDP_ADDR_CALVES_FEET == pEvt->Arg.CDPTx.pTxBuf[CDP_PDU_OFFSET_DES]) )
  {
    TxState = CDP_CenXxx_DataTx(pEvt);  
  }
  else if( (CDP_ADDR_WIFI   == pEvt->Arg.CDPTx.pTxBuf[CDP_PDU_OFFSET_DES]) ||
           (CDP_ADDR_SERVER == pEvt->Arg.CDPTx.pTxBuf[CDP_PDU_OFFSET_DES]) )
  {
    TxState = CDP_CenServer_DataTx(pEvt);
  }

  if(BSP_UART_TxState_Busy == TxState)
  {
    ESF_EvtQuene_Post(pEvt);                         /*����æ��������Ͷ�ݣ��ȴ���һ�η���*/
    return MEM_USE;                                  /*�ڴ��¼�������ʹ����*/
  }
  else
  {
    return MEM_IDLE;                                 /*�¼���ռ�ڴ�������*/
  }
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
  ESF_Evt_t *pEvt = NULL;
  uint8_t *wp, *rp;
  uint16_t DULen;
  uint8_t i;

  pEvt = ESF_MemBuf_Get();                                                          /*�����ڴ��*/
  if(NULL == pEvt)
  {
    return;                                                                         /*����ʧ���򷵻�*/
  }
  
  pEvt->Type = EvtCDPTx;                                                            /*���ݰ������¼�*/
  pEvt->Arg.CDPTx.pTxBuf = (uint8_t*)&pEvt->AppendData[0];                          /*Ҫ���͵Ļ���*/
  wp = pEvt->Arg.CDPTx.pTxBuf;
  *wp++ = DesAddr;
  *wp++ = CDP_ADDR_SELF;
  
  if( (CDP_ADDR_WIFI   == DesAddr) ||
      (CDP_ADDR_SERVER == DesAddr) )
  {
    *wp++ = 0x80;
    *wp++ = 0x80;
  }
  else
  {
    *wp++ = 0;
    *wp++ = 0;
  }

  *wp++ = Cmd;
  *wp++ = CDP_ACK_SEND;
  
  for(i=0; i<DUBufISum; i++)
  {
    rp = DUBuf[i];
    DULen = rp[CDP_DU_OFFSET_LEN];
    while(DULen--)
    {
      *wp++ = *rp++;
    }
  }

  pEvt->Arg.CDPTx.TxLen  = wp - pEvt->Arg.CDPTx.pTxBuf;                             /*Ҫ���͵ĳ���*/
  ESF_EvtQuene_Post(pEvt);                                                          /*Ͷ���¼�*/
}

/*
************************************************************************************************************************
* �������� : CDP_FrameRxHandle                                                                                                         
* �������� : ͨ�����ݰ�   ֮   ֡���մ���                                                                              
* ������� : pFrameRx -- Ҫ����Ľṹ                                                                   
* ������� : RxByte   -- �յ����ֽ�����     
*            CDPType  -- ���ݰ�����
*            CDPDAP   -- ���ݷ�������˿�
* ���ز��� : 0   -- δ�յ���Ч���ݡ�
*            ��0 -- �յ�ĳ��ģ�������֡���÷�0ֵ��ʾ������Դģ��ĵ�ַ��
* ����˵�� : �ú�������ͨ��BSP_UART_RegRxByteCB()ע���BSP�㣬�Ա��ڴ��ڽ����ֽ��ж��е��á�                                                                                                  
************************************************************************************************************************
*/
uint8_t CDP_FrameRxHandle(CDP_FrameRx_t *pFrameRx, uint8_t RxByte, uint8_t CDPType, uint8_t CDPDAP)
{
  /*������һ���ڴ��������ݽ��յĻ��洦��----------------------------------------*/
  if(NULL == pFrameRx->pEvt) 
  {
    pFrameRx->pEvt = ESF_MemBuf_Get();                                                         /*�����ڴ��*/
    if(NULL == pFrameRx->pEvt)
    {
      return  0;                                                                               /*����ʧ���򷵻أ�����һ��������*/
    }
    pFrameRx->pRxBuf = (uint8_t*)&pFrameRx->pEvt->AppendData[0];                               /*���ݽ��յĴ��λ��*/
  }
  
  /*�ֽڼ���ճ�ʱ�ˣ����������ݽ��ս����������½��������ݡ�
      ���İ�--��о��   (��Э��)
      ���İ�--��ƽ��   (��Э��)
      ���İ�--С�Ȱ�   (��Э��)
    �����������ֶ�����һ�������ϣ���˻���շ������У����ײ������У��Ӵ˳�ʱ�жϡ��������£�  
   �� ����ĳ��ԭ��ò������ݶ��� xx xx xx xx 7E  -->����ƽ�������  -->7E xx xx xx ...... 7E ��
                                             |<------------------------>|
                                             �ⲿ�����ݻ������Э���֡���ճɹ��жϡ�
                                             ��Ȼ�׸��ϲ�󣬻ᱻ���˵�������������ᵼ����Э�����ݾ����ղ�����*/
  if(pFrameRx->ByteRxTimeOutMs >= 4)                     /*������19200����6*1.92=11�ֽڵ�ʱ��*/                                           
  {
    pFrameRx->PDURecing = FALSE;           
  }
  pFrameRx->ByteRxTimeOutMs = 0;

  /*���ݽ��գ�֡��ȡ��ת�崦���ۼӺͼ��--------------------------------------*/
  if(CDP_FRAME_BOUNDARY == RxByte)                                                             /*֡�߽�*/ 
  {
    if(TRUE == pFrameRx->PDURecing)                                                            /*���ݽ����У�������յ�֡β*/
    {
      if(pFrameRx->RxLen >= CDP_FRAME_MIN_LEN-2)                                               /*�յ��㹻���ȵ����ݡ�-2����ȥ֡ͷ��֡β����������ջ���*/
      {
        if(CORRECT == CumulativeSum_Check(pFrameRx->pRxBuf, pFrameRx->RxLen))
        {
          pFrameRx->pEvt->Type              = EvtCDPRx;
          pFrameRx->pEvt->Arg.CDPRx.CDPType = CDPType;
          pFrameRx->pEvt->Arg.CDPRx.DAP     = CDPDAP;                                          /*���ݷ�������˿�*/   
          pFrameRx->pEvt->Arg.CDPRx.pRxBuf  = pFrameRx->pRxBuf;        
          pFrameRx->pEvt->Arg.CDPRx.RxLen   = pFrameRx->RxLen -1;                              /*-1: ��ȥ1�ֽڵ��ۼӺ�У��*/
          pFrameRx->pEvt->Arg.CDPRx.pAckBuf = pFrameRx->pEvt->Arg.CDPRx.pRxBuf + pFrameRx->pEvt->Arg.CDPRx.RxLen;  /*Ӧ�𻺴���ڽ��ջ���֮��*/      
          ESF_EvtQuene_Post(pFrameRx->pEvt);                                                   /*Ͷ���¼�*/ 
          pFrameRx->pEvt = NULL;                                                               /*Ͷ�����ָ�븳�գ��Ա��´������µ��ڴ�黺��*/
          pFrameRx->PDURecing = FALSE;                                                         /*���ݽ��ս���*/
          return pFrameRx->pRxBuf[CDP_PDU_OFFSET_SRC];                                         /*����ģ���ַ*/
        }
      }
    }
    else                                                                                       /*���ݽ��ջ�δ������������յ�֡ͷ*/
    {
      pFrameRx->PDURecing = TRUE;                                                              /*�������ݽ��ս�����*/
    }
    
    pFrameRx->NeedESC = FALSE;
    pFrameRx->RxLen = 0;                                                                       /*ÿ���յ�֡�߽磬�������ճ�������*/
  }
  else if(TRUE == pFrameRx->PDURecing)                                                         /*���ݽ��տ����Ž������ݵĽ���*/
  {
    if(CDP_FRAME_ESC == RxByte)
    {
      pFrameRx->NeedESC = TRUE;                                                                /*ת����ֽ����ݲ�������ջ��棬���ڵ���һ���ֽ�Ҫ��ת�崦����ԭ��ԭ��������*/
    }
    else
    {
      if(TRUE == pFrameRx->NeedESC)
      {
        pFrameRx->pRxBuf[pFrameRx->RxLen++] = RxByte ^ 0x03;                                   /*��ԭ��ԭ��������*/
        pFrameRx->NeedESC = FALSE;
      }
      else
      {
        pFrameRx->pRxBuf[pFrameRx->RxLen++] = RxByte;
      }
      
      if(pFrameRx->RxLen >= pFrameRx->RxLenMax)                                                /*�������泤�ȣ����ͷ��ʼ����*/   
      {
        pFrameRx->NeedESC = FALSE;
        pFrameRx->RxLen = 0;
      }
    }
  }
  
  return 0;
}

/*
************************************************************************************************************************
* �������� : CDP_CommonDataTx                                                                                                         
* �������� : ͨ�����ݰ�  ֮  ֡���ͷ���                                                                      
* ������� : pEvt        -- Ҫ���͵��¼�����   
*            pTxFrameBuf -- ����ǰ�Ĵ��֡����
*            PortNum     -- ���͵Ķ˿�
* ���ز��� : BSP_UART_TxState_Busy  -- ����æ���޷�������pTxBufָ��ĵ����ݡ�
*            ����ֵ                 -- ���ڿ�ʼ����pTxBufָ��ĵ������ˡ�
* ����˵�� : ��                                                                                                  
************************************************************************************************************************
*/
uint8_t CDP_FrameTxHandle(ESF_Evt_t *pEvt, uint8_t *pTxFrameBuf, BSP_UART_PortNum_t PortNum)
{
  uint8_t *wp;
  uint16_t i;
  uint8_t sum;
  
  
  if(BSP_UART_TxState_Busy == BSP_UART_GetTxState(PortNum))
  {
    return BSP_UART_TxState_Busy;    /*����æ���򷵻�*/
  }
  
  sum = CumulativeSum_Cal(pEvt->Arg.CDPTx.pTxBuf, pEvt->Arg.CDPTx.TxLen); 
  pEvt->Arg.CDPTx.pTxBuf[pEvt->Arg.CDPTx.TxLen++] = sum;

  wp = pTxFrameBuf;
  *wp++ = CDP_FRAME_HEADER;
  for(i=0; i<pEvt->Arg.CDPTx.TxLen; i++)
  {
    if((CDP_FRAME_BOUNDARY == pEvt->Arg.CDPTx.pTxBuf[i]) || 
       (CDP_FRAME_ESC      == pEvt->Arg.CDPTx.pTxBuf[i]) )
    {
      *wp++ = CDP_FRAME_ESC;
      *wp++ = pEvt->Arg.CDPTx.pTxBuf[i] ^ 0x03;
    }
    else
    {
      *wp++ = pEvt->Arg.CDPTx.pTxBuf[i];
    }
  }
  *wp++ = CDP_FRAME_FOOTER;
  
  return BSP_UART_TxData(PortNum, pTxFrameBuf, (wp - pTxFrameBuf));
}

/*
************************************************************************************************************************
* �������� : CDP_DataTxTmrHandle                                                                                                         
* �������� : ͨ�����ݰ�   ֮   ���ݷ��Ͷ�ʱ����                                                                       
* ������� : ExePeriod -- ������ִ������                                                                                    
* ���ز��� : ��                                                             
* ����˵�� : ��                                                                                                  
************************************************************************************************************************
*/
void CDP_DataTxTmrHandle(Ticker_t ExePeriod)
{
  static  Ticker_t  AppTicker,SeverTemp;
  static  uint8_t   Order;
  static  Ticker_t  Ticker;
  static  Ticker_t  ServerTicker1,ServerTicker2;
  static  Ticker_t  TickerSec1;
  
  uint8_t *DUBuf[5];    /*ָ�����飬�����ڵ�ָ��ָ�򱣴�DU����(Ӧ�ð������ݳ��Ⱥ�����ID) ���ڴ��ַ��*/
  uint8_t i;  

  if(pCDP->RepeaterLTL >= ExePeriod)
  {
    pCDP->RepeaterLTL -= ExePeriod;
    pCDP->CSFlag.Bit.RepeaterWork = TRUE;      /*ת��������*/
    Ticker = 0;
  }
  else
  {
    pCDP->RepeaterLTL = 0;
    pCDP->CSFlag.Bit.RepeaterWork = FALSE;     /*ת����������*/
   
    /*ת���������ڼ䣬���İ������ģ��Ķ�ʱ���͹�������ͣ��ת����ֹͣ���ٻָ���ʱ���͹���*/  
  
    Ticker += ExePeriod;
    if(35 == Ticker)
    {
      if(0 == Order)
      {
        CDP_CenStateTmrToCtrl_DataTx(35);
      }
    }
    else if(55 == Ticker)
    {
      i = 0;
      Order = !Order;
      if(Order)
      {
        DUBuf[i++] = Gas_CDPDataObjTx_0x48();
        DUBuf[i++] = Roller_CDPDataObjTx_0x49();
//        DUBuf[i++] = Vib_CDPDataObjTx_0x4A();
        DUBuf[i++] = LegFlexSpike_CDPDataObjTx_0x4B();
        CDP_PDUPackTx(CDP_ADDR_CALVES_FEET, CDP_CMD_SET_ACK, DUBuf, i);
      }
      else
      {
        DUBuf[i++] = SideCtrl_CDPDataObjTx_0x50(140);
        CDP_PDUPackTx(CDP_ADDR_CTR_SIDE, CDP_CMD_SET_ACK, DUBuf, i);
      }
    }
    else if(70 == Ticker)
    {
      i = 0;
      DUBuf[i++] = Core_CDPDataObjTx_0x40();
      DUBuf[i++] = Heat_CDPDataObjTx_0x41();
      CDP_PDUPackTx(CDP_ADDR_CORE, CDP_CMD_SET_ACK, DUBuf, i);
      Ticker = 0;
    }
    
    /*���������Ķ�ʱ����*/
    ServerTicker1 += ExePeriod;
    if(ServerTicker1 >= 1000)     /*1S����һ��*/
    {
      if(TRUE == CDP_CenServer_GetCSFlag().Bit.LinkLostFault)
      {
        Server_ReReportedData();
      }
      ServerTicker1 = 0;
      i = 0;
      switch(SeverTemp)
      {
        case 0:
          if( FALSE == Server_GetCSFlag().UpDataSuc_0x0040 )
          {
            DUBuf[i++] = Server_CDPDataObjTx_0x0040();
          }
          SeverTemp++;
          break;
          
        case 1:
          if( FALSE == Server_GetCSFlag().UpDataSuc_0x0042 )
          {
            DUBuf[i++] = Server_CDPDataObjTx_0x0042();
          }
          SeverTemp++;
          break;

        case 2:
          if( FALSE == Server_GetCSFlag().UpDataSuc_0x0043 )
          {
            DUBuf[i++] = Server_CDPDataObjTx_0x0043();
          }
          SeverTemp++;
          break;
          
        default:
          SeverTemp = 0;
          break;
      }
      if(i != 0)
      {
        CDP_PDUPackTx(CDP_ADDR_SERVER, CDP_CMD_UPREPORT_SERVER, DUBuf, i);
      }
      
      /*�������յ� �������к� ��Ž��ж�ʱ�ϱ�״̬*/
      if( TRUE == Server_GetCSFlag().UpDataSuc_0x0040 )
      {
        TickerSec1 ++;
        if(TickerSec1 == 30)
        {
          i = 0;
          DUBuf[i++] = Server_CDPDataObjTx_0x0041();
          CDP_PDUPackTx(CDP_ADDR_SERVER, CDP_CMD_UPREPORT_SERVER, DUBuf, i);
        }
        else if(60 == TickerSec1)
        {
          i = 0;
          DUBuf[i++] = Server_CDPDataObjTx_0x004C();
          CDP_PDUPackTx(CDP_ADDR_SERVER, CDP_CMD_TIMEING_UPREPORT_SERVER, DUBuf, i);
        }
        else if(90 == TickerSec1)
        {
          i = 0;
          DUBuf[i++] = Server_CDPDataObjTx_0x004D();
          CDP_PDUPackTx(CDP_ADDR_SERVER, CDP_CMD_TIMEING_UPREPORT_SERVER, DUBuf, i);
          TickerSec1 = 0;
        }
      }
    }

    ServerTicker2 += ExePeriod;
    if(50 == ServerTicker2)        /*����������״̬���ݣ��仯�ϱ�*/
    {
      if( TRUE == Server_GetCSFlag().UpDataSuc_0x0040 )
      {
        DUBuf[0] = 0;
        
        if(SYS_MODE_STANDBY == pMChair->SysModeCur)
        {
          DUBuf[2] = Server_CDPDataObjTx_0x0D02();
          DUBuf[0] = DUBuf[2];
        }
        else if(SYS_MODE_USERRUN == pMChair->SysModeCur)
        {
          DUBuf[1] = Server_CDPDataObjTx_0x0D01();
          DUBuf[0] = DUBuf[1];
        }
        if(TRUE == pMChair->CSFlag.Bit.MChairReported)
        {
          CDP_PDUPackTx(CDP_ADDR_SERVER, CDP_CMD_UPREPORT_SERVER, DUBuf, 1);
        }
      }
    }
    else if(250 == ServerTicker2)  /*�������ݸ�WIFI��*/
    {
      ServerTicker2 = 0;
      /*���绹δ���ã��������������ݽ��ճɹ����������������������*/
      if( (TRUE  == Server_GetCSFlag().NetDataRx) &&
          (FALSE == Server_GetCSFlag().WIFIIntCfg) )
      {
        DUBuf[0] = Server_CDPDataObjTx_0x0912();
        CDP_PDUPackTx(CDP_ADDR_WIFI, CDP_CMD_SET_ACK_SERVER, DUBuf, 1);
      }
    }
      
    /*���͸�����APP����*/
    AppTicker += ExePeriod;
    if(AppTicker >= 200)
    {
      AppTicker = 0;
      CDP_CenTmrToApp_DataTx(200);
    }
  }
}

/*
========================================================================================================================
*    ͨ�����ݰ����ܺ��������                  ͨ�����ݰ����ܺ��������                    ͨ�����ݰ����ܺ��������
========================================================================================================================
*/

#define  CDP_TICK_COUNT_BUF_NUM   4
static Ticker_t CDP_TickCount[CDP_TICK_COUNT_BUF_NUM];

const ESF_TmrExeFunc_t  CDP_TmrExeFuncTab[] = 
{
  /*   ִ�к���               ִ������(ms)       ʱ���������*/
  {CDP_DataTxTmrHandle,          5,            &CDP_TickCount[0]},
  {CDP_CenXxx_FaultCheck,        2,            &CDP_TickCount[1]},
  {CDP_CenServer_FaultCheck,  1001,            &CDP_TickCount[2]},
  {CDP_CenApp_FaultCheck,        2,            &CDP_TickCount[3]},
};

#define  CDP_TMR_EXE_FUNC_TAB_NUM     TAB_NUM(CDP_TmrExeFuncTab)

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
  /*���ȹ��ܺ�����------------------------------------------------*/
  ESF_TmrExeFuncScheduling(CDP_TmrExeFuncTab, CDP_TMR_EXE_FUNC_TAB_NUM);
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
  memset(pCDP, 0, sizeof(CDP_t)); /*������������*/
  pCDP->pCenXxx  = CDP_CenXxx_Init(); 
//  CDP_CenDebug_Init();
  pCDP->pCenApp = CDP_CenApp_Init();
  CDP_CenServer_Init();

  /*��� CDP_TmrExeFuncTab ���ܺ����������Ƿ���ȷ------------------------*/
  ESF_TmrExeFuncTabCheck(CDP_TmrExeFuncTab, CDP_TMR_EXE_FUNC_TAB_NUM, CDP_TICK_COUNT_BUF_NUM);

  return pCDP;
}

/*
************************************************************************************************************************
* �������� : CDP_GetCSFlag                                                                                                         
* �������� : ��� ���� �� ״̬ ��ʶ                                                                
* ������� : ��                                                                   
* ���ز��� : ������״̬��ʶ �Ľṹ��                                                             
* ����˵�� : ��                                                                                                  
************************************************************************************************************************
*/
CDPCSFlag_t CDP_GetCSFlag(void)
{
  return pCDP->CSFlag;
}




/*
************************************************************************************************************************
* �������� : SideCtrl_CDPDataObjRx_0x50                                                                                      
* �������� : 0x50 ��������(��������-->���İ�)
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ��������ݵĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t SideCtrl_CDPDataObjRx_0x50(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  ESF_Evt_t *pEvt;
  
  /*�������ݵ����İ�-------------------------------------------------------------*/
  memcpy((uint8_t *)&pCDP->SetQry0x50, &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  
  pCDP->CSFlag.Bit.CenXxx_SideCtrlKeyStuck = pCDP->SetQry0x50.Byte2.Bit.KeyStuck;

  pEvt = ESF_MemBuf_Get();                                       /*�����¼��ڴ��*/
  if(pEvt != NULL)                                               /*����ɹ�*/ 
  {
    pEvt->Type = EvtCDPRx;
    pEvt->Arg.CDPRx.CDPType = CDP_TYPE_SIDE_CTRL;           
    pEvt->Arg.CDPRx.pRxBuf = (uint8_t*)pEvt->AppendData;
    
    pEvt->Arg.CDPRx.pRxBuf[0] = KEYVAL_NoPress;                  /*��Ĭ���ް�������*/
    if((pCDP->SetQry0x50.KeyVal != 0) && (pCDP->SetQry0x50.KeyVal < TAB_NUM(SideCtrlKeyValMapTab)))
    {
      pEvt->Arg.CDPRx.pRxBuf[0] = SideCtrlKeyValMapTab[pCDP->SetQry0x50.KeyVal]; 
    }
    else if(0xFF == pCDP->SetQry0x50.KeyVal)
    {
      pEvt->Arg.CDPRx.pRxBuf[0] = pCDP->SetQry0x50.KeyVal; 
    }
    pEvt->Arg.CDPRx.RxLen = 1;
    ESF_EvtQuene_Post(pEvt);                                     /*Ͷ���¼�*/        
  }  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* �������� : SideCtrl_CDPDataObjTx_0x50                                                                                      
* �������� : 0x50 ��������(��������-->���İ�)
* ������� : ExePeriod -- ������ִ������                                                                                    
* ���ز��� : �ɹ��򷵻�Ҫ���͵����ݵ��ڴ��׵�ַ��ʧ�ܷ���NULL��ָ��
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t* SideCtrl_CDPDataObjTx_0x50(Ticker_t ExePeriod)
{
  static  Ticker_t       PowerLedFlashTimeMs;         

  pCDP->SetQry0x50.DataLen = sizeof(pCDP->SetQry0x50);  
  pCDP->SetQry0x50.DataID = 0x50;  
  
  
  PowerLedFlashTimeMs += ExePeriod;
  PowerLedFlashTimeMs =  (PowerLedFlashTimeMs > 1500) ? 0 : PowerLedFlashTimeMs;

  /* LED1 : ����������HEAT��ָʾ�� */
  pCDP->SetQry0x50.Byte1.Bit.Led1 = (pMChair->FuncMA_Heat.Bit.LumbarBack == FMA_LUMBARBACK_HEAT_Mannual) ? ON : OFF;

  /* LED2 : ����������FeetRoller��ָʾ�� */
  pCDP->SetQry0x50.Byte1.Bit.Led2 = (pMChair->FuncMA_Roller.Bit.Feet != FMA_ROLLER_NONE) ? ON : OFF;
  
  /* LED5 : ����������POWER��ָʾ�� */
  pCDP->SetQry0x50.Byte1.Bit.Led5 = (TRUE == pMChair->CSFlag.Bit.SysRun) ? ON : ((PowerLedFlashTimeMs < 750) ? ON : OFF);
  
  /* LED8 : ����������ZERO-G��ָʾ�� */
  pCDP->SetQry0x50.Byte1.Bit.Led8 = (pMChair->FuncAuto_Spike == FA_SPIKE_ZeroGravity2) ? ON : OFF;
  if((PBACK_ZERO2_ANGLE == Spike_GetBackAngle()) && (FALSE == pMChair->StateBackSpike.Bit.Work) &&
     (PFEET_ZERO2_ANGLE == Spike_GetFeetAngle()) && (FALSE == pMChair->StateFeetSpike.Bit.Work) )
  {
    pCDP->SetQry0x50.Byte1.Bit.Led8 = ON;
  }
  
  /* LED9 : ����������AUTO��ָʾ�� */
  pCDP->SetQry0x50.Byte2.Bit.Led9 = (pMChair->FuncAuto_CoreGas == FA_COREGAS_Quick) ? ON : OFF;

  /* LED10 : ����������PAUSE��ָʾ�� */
  pCDP->SetQry0x50.Byte2.Bit.Led10 = (TRUE == pMChair->CSFlag.Bit.Pause) ? ((PowerLedFlashTimeMs < 750) ? ON : OFF) : OFF;
  

  return (uint8_t *)&pCDP->SetQry0x50;
}
