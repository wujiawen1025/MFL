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
* �������� : CDP_CenWifi_ByteRx                                                                                                    
* �������� : ͨ�����ݰ�   ֮   ���İ� <--> ��̨������  ���İ��ֽڽ������ݻص�������                                                                              
* ������� : void                                                                 
* ���ز��� : ��                                                             
* ����˵�� : �����ݸ���֡ͷ֡βΪ����������������ۼӺ��ж���ȷ�󣬸���������                                                                                                
************************************************************************************************************************
*/

void	CDP_CenSideBoard_ByteRx(uint8_t RxByte)
{//�����жϵ��ú���
  static uint8_t NeedESC,ByteRxLen;                                                            /*��ʶ�Ƿ���Ҫת�� */
  static uint8_t PDUReceving = FALSE;                                                /*Э�����ݵ�Ԫ(��ȥ֡ͷ��֡β)������ */
  uint8_t checksum;
  
#if 1 
  if(pCDP_CenSideCtrl->RxNothingTimer > 10)//����10msû�н�������
  {
    PDUReceving = FALSE;                                                            /*�������ݽ���*/
    ByteRxLen = 0;
  }
  pCDP_CenSideCtrl->RxNothingTimer = 0;
#endif

  /*���ݽ���:֡��ȡ��ת�崦���ۼӺ�У��--------------------------------------*/
  if(CDP_FRAME_BOUNDARY == RxByte)                                                   /*�յ�֡�߽�*/ 
  {
    if(TRUE == PDUReceving)                                                          /*���ݽ����У������յ�֡β*/
    {
      if(ByteRxLen >= CDP_SIDECTRL_FRAME_MIN_LEN-2)                                  /*�յ��㹻���ȵ����ݡ�-2:ȥ��֡ͷ֡β*/
      {
        /*�����ۼӺ�У����*/
        checksum = 0;
        checksum = CalculateCheckSum(pCDP_CenSideCtrl->RxBuf, ByteRxLen-1); 

        if(checksum == pCDP_CenSideCtrl->RxBuf[ByteRxLen-1])
        {
          //pCDP_CenSideCtrl->RxBuf[ByteRxLen++] = RxByte;//��У����Ҳ���볤��
          pCDP_CenSideCtrl->RxLen = ByteRxLen-1;
          pCDP_CenSideCtrl->CSFlag.Bit.RxWifiDataOKFlag = TRUE;  //�����ݽ�����ɱ�־   
	   	    //evReceiveSideBoardFlag  = 1;
					ReceviceDataFromSideBoard();					
					
          PDUReceving = FALSE;                                                       /*���ݽ��ս���*/
        }
      }      
    }
    else                                                                             /*���ݻ�û��ʼ���գ������յ�֡ͷ*/
    {
      PDUReceving = TRUE;                                                            /*�������ݽ���*/
    }
    
    NeedESC = FALSE;
    ByteRxLen = 0;
  }
  else if(TRUE == PDUReceving)                                                      /*��y?Y?����??a??2???DD��y?Y��??����?*/
  {
    if(CDP_FRAME_ESC == RxByte)
    {
      NeedESC = TRUE;               //����ת���ַ���������ֱ�Ӵ�����һ��0x7D ���� 0x5D   ,ֱ��+1                                       /*��a��?��?��??����y?Y2?��?��??����??o��?��???������???��???��??����a��?��a��?��|������??1?-3��?-�����?��y?Y*/
    }
    else
    {
      if(TRUE == NeedESC)
      {
        pCDP_CenSideCtrl->RxBuf[ByteRxLen++] = RxByte ^ 0x03;               /*�����λȡ�����൱�ڼ�1����*/
        NeedESC = FALSE;
      }
      else
      {
        pCDP_CenSideCtrl->RxBuf[ByteRxLen++] = RxByte;
      }
      
      if(ByteRxLen >= Xxx_CTRL_RX_BUF_SIZE)                              /*3?1y?o��?3��?����??���䨮����?a��??����?*/   
      {
        NeedESC = FALSE;
        ByteRxLen = 0;
      }
    }
  }
}


/*
************************************************************************************************************************
* �������� : CDP_CenWifi_FrameTx                                                                                                         
* �������� : ͨ������֡��� + ����                                                                                   
* ������� : DesAddr   -- Ŀ�ĵ�ַ
*            Cmd       -- ����
*            DUBuf     -- ָ�����飬�����ڵ�Ԫ��Ϊָ�룬ÿ��ָ��ָ��һ������DU����(Ӧ�ð������ݳ��Ⱥ�����ID) ���ڴ��ַ��   
*            DUBufISum -- DUBuf�����Ԫ�ظ���
* ���ز��� : ��                                                             
* ����˵�� :                                                                                                      
************************************************************************************************************************
*/
void CDP_CenWifi_FrameTx(void)
{//����Ҫ���͵����ݽ������  
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
       (CDP_FRAME_ESC      == pCDP_CenSideCtrl->TxBuf[i]) )  /*�ж�5E��7E�����ݣ���������ת��*/
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

//ʵ�ʷ��͵���������ڴ�  
  BSP_UART_TxData(CEN_SIDECTRL_UART_PORT,FrameTxBuf, (wp - FrameTxBuf));	 
}




/*
************************************************************************************************************************
* �������� : ReceviceDataFromWifi                                                                                                    
* �������� : ͨ�����ݰ�   ֮    ���İ� <--> ����  ����PDU���ݴ���                                                                              
* ������� : void                                                                 
* ���ز��� : ��                                                             
* ����˵�� : ʵʱ��ѯ����״̬                                                                                                
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
				gCombinationKeyTime++;	//50ms����һ��
			if(gCombinationKeyTime >= 60 && gCombinationKeyTime != 200)	  // 3s
			{
				gCombinationKeyTime = 200;//ִֻ��һ��
				TxResflag =1;//	  ���͸�λָ��
				pCDP_CenSideCtrl->CSFlag.Bit.Key8LedOnFlag = 1;
			}		
	}
	else
	{
		gCombinationKeyTime= 0;
	}

  
	//if(!CtrlKeyPressFlag)
  //{
  	//gKeyValue = CDP_CenSideBoard.KeyValue_Byte0 ;//�����ֿ�����ֵ
  	//KeyPressEvent();
  //}

}

/*
************************************************************************************************************************
* �������� : SendDataToWifi25ms                                                                                                         
* �������� : ���ݰ�����                                                                                        
* ������� : pEvt -- �¼�                                                                                  
* ���ز��� : MEM_IDLE --  �¼��ڴ���У������ͷ���        
*            MEM_USE  --  �¼��ڴ滹��ʹ���У��������ͷ�                                                                   
* ����˵�� : ��ʱ��ѯ����                                                                                                        
************************************************************************************************************************
*/

void SendDataToSideBoard100ms(void)
{    	
	//Byte2		Ŀ�ĵ�ַ		0x11
	//Byte3		Դ��ַ		0x01
	//Byte4		Э��汾��		0
	//Byte5		Ԥ��		0
	//Byte6		������		0x04
	//Byte7		Ӧ����		0xff

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


	memcpy((&CDP_CenSideCtrl.TxBuf[CDP_PDU_OFFSET_DU]),(uint8_t *)&CDP_CenSideBoard, CDP_CenSideBoard.DataLenth);                /*��Ӧ�𻺴���䲿������*/


	pCDP_CenSideCtrl->TxLen += CDP_CenSideBoard.DataLenth;

	//if( TRUE == pCDP_CenSideCtrl->CSFlag.Bit.SendWifiDataFlag )//������ͱ�־λ��������
	{//�ظ�����
		pCDP_CenSideCtrl->CSFlag.Bit.SendWifiDataFlag = FALSE;
		if( (CDP_ADDR_SIDE   == pCDP_CenSideCtrl->TxBuf[CDP_PDU_OFFSET_DES]))
		{
		  CDP_CenWifi_FrameTx();
		}
	}
}
/*
************************************************************************************************************************
* �������� : Variable1msProcess                                                                                                    
* �������� : ͨ�����ݰ�   ֮   ���İ� <--> ��̨������  �������ݴ���                                                                              
* ������� : void                                                                 
* ���ز��� : ��                                                             
* ����˵�� : �����ݸ���֡ͷ֡βΪ����������������ۼӺ��ж���ȷ�󣬸���������                                                                                                
************************************************************************************************************************
*/
void Variable1msProcess(void)
{
  if( pCDP_CenSideCtrl->RxNothingTimer < 255 )
    pCDP_CenSideCtrl->RxNothingTimer++;
}

/*
************************************************************************************************************************
* �������� : SideCtrlInit                                                                                                    
* �������� :                                                                            
* ������� : void                                                                 
* ���ز��� : ��                                                             
* ����˵�� :                                                                                               
************************************************************************************************************************
*/
void SideCtrlInit(void)
{
  BSP_UART_RegRxByteCB(CEN_SIDECTRL_UART_PORT, CDP_CenSideBoard_ByteRx); /*??????????*/

}




