

#ifndef	_SideBoard_806_h_
#define	_SideBoard_806_h_


#define CEN_SIDECTRL_UART_PORT        BSP_UART_Port4                                         /*????*/


#define  SIDECTRL_TO_CEN_RXBUF_SIZE             24                   /*���ջ����С*/ 
#define  CEN_TO_SIDECTRL_TXBUF_SIZE             SIDECTRL_TO_CEN_RXBUF_SIZE                   /*���ͻ����С*/ 

#define  Xxx_CTRL_RX_BUF_SIZE                   SIDECTRL_TO_CEN_RXBUF_SIZE                   /*���ջ����С*/ 

#define  CDP_SIDECTRL_FRAME_MIN_LEN             12                   /*��С֡����*/ 


#define  CDP_FRAME_BOUNDARY                     0x7E                 /*֡�߽�*/            
#define  CDP_FRAME_HEADER                       CDP_FRAME_BOUNDARY   /*֡ͷ*/
#define  CDP_FRAME_FOOTER                       CDP_FRAME_BOUNDARY   /*֡β*/            
#define  CDP_FRAME_ESC                          0x5E                 /*֡ת��*/   

/*--------Э�����ݵ�ԪPDU��ƫ��-----------------------------*/
#define  CDP_PDU_OFFSET_DES                     0                    /*Э�����ݵ�Ԫ�ڵ� Ŀ�ĵ�ַ ƫ��*/
#define  CDP_PDU_OFFSET_SRC                     1                    /*Э�����ݵ�Ԫ�ڵ� Դ��ַ   ƫ��*/
#define  CDP_PDU_OFFSET_VER                     2                    /*Э�����ݵ�Ԫ�ڵ� �汾��Э��ID   ƫ��*/
#define  CDP_PDU_OFFSET_TAG                     3                    /*Э�����ݵ�Ԫ�ڵ� ���ݰ���ʶ��   ƫ��*/
#define  CDP_PDU_OFFSET_CMD                     4                    /*Э�����ݵ�Ԫ�ڵ� ������   ƫ��*/
#define  CDP_PDU_OFFSET_ACK                     5                    /*Э�����ݵ�Ԫ�ڵ� Ӧ��     ƫ��*/
#define  CDP_PDU_OFFSET_DU                      6                    /*Э�����ݵ�Ԫ�ڵ� ���ݵ�Ԫ ƫ��*/

/*--------���ݵ�ԪDU��ƫ��-----------------------------*/
#define  CDP_DU_OFFSET_LEN                      0                    /*���ݵ�Ԫ�ڵ� ���� ƫ��*/            
#define  CDP_DU_OFFSET_ID                       1                    /*���ݵ�Ԫ�ڵ� ID   ƫ��*/  
#define  CDP_DU_OFFSET_DATA                     2                    /*���ݵ�Ԫ�ڵ� ���� ƫ��*/ 


/*===========ͨ�ŵ�ַ=====================================*/
/*--------ÿ����������ģ���Ӧ�ĵ�ַ����-----------------------------*/
#define  CDP_ADDR_CEN                           0x01                 /*��ַ�����İ�*/
#define  CDP_ADDR_SIDE                          0x11                 /*��ַ����尴��*/


/*ע�⣺һ������ģ���п��ܰ�������߼�ģ�顣����С��ģ����ܰ�����С��������С�ȳ������Ź��ȡ�
 *      ��Ϊ��ǰ�汾Э������ID��ʶ�ķ����У�ÿ��ID������ͬ�ĺ��壬�Ҷ�����ȷ֪�����������ĸ��߼�ģ�顣
 *      ��˿�ֻʹ��һ����ַ��Ϊ����ģ��ĵ�ַ���ɣ�����Ҳ�������������ݰ��Ĵ�С��
 *      ��Ȼ������Ժ��Э��汾�У�����ID��ʶ������ȷ���ֳ����ݹ������ĸ�ģ�飬��Ӧ��ʹ�ö���߼���ַ���������ݹ�����*/

/*===========������=====================================*/

/*===========Ӧ����=====================================*/





/*
************************************************************************************************************************
* ���Ͷ��� :  ���İ� <--> ����  ���İ�������ݲ���                                                                             
************************************************************************************************************************
*/
/*
************************************************************************************************************************
* ���Ͷ��� :  ���İ� <--> ����  ������״̬��ʶ                                                                              
************************************************************************************************************************
*/
typedef unsigned char uint8_t;

typedef  union 
{
  uint8_t All;
  struct
  {
    uint8_t    RxWifiDataOKFlag         :1;    /*ͨ�����ݽ������*/
    uint8_t    SendWifiDataFlag         :1;    /*�������ݱ�־λ*/

    uint8_t    Key8PressingFlag         :1;    /*8�ż�ֵ�������±�־*/
    uint8_t    Key8LedOnFlag            :1;    /*8�ż�ֵ�����Ƶ�����־*/
   
  }Bit;

}CDP_CenSideCtrlCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/

/*
************************************************************************************************************************
* ���Ͷ��� :  ���İ� <--> Wifi  ��ز������ݽṹ                                                                            
************************************************************************************************************************
*/
typedef struct
{
	CDP_CenSideCtrlCSFlag_t CSFlag;
	uint8_t RxLen;									/*�������ݳ���*/
	uint8_t RxBuf[SIDECTRL_TO_CEN_RXBUF_SIZE];          /*���ջ�����*/
	
	uint8_t RxNothingTimer;					        /*�������ݳ���*/	
    
	
	uint8_t TxBuf[CEN_TO_SIDECTRL_TXBUF_SIZE];          /*���ͻ�����*/
	uint8_t TxLen;									/*�������ݳ���*/

}CDP_CenSideCtrl_t;	/*ͨ����ؿ��Ʊ���*/


typedef __packed struct
{
  uint8_t             DataLenth;
  uint8_t             CtrlID;
  uint8_t 			  KeyValue_Byte0;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
			uint8_t    Led1_OnFlag            :1;    /**/
			uint8_t    Led2_OnFlag         		:1;    /**/
			uint8_t    Led3_OnFlag         		:1;    /**/ 
			uint8_t    Led4_OnFlag         		:1;    /**/
			uint8_t    Led5_OnFlag       			:1;    /**/
			uint8_t    Led6_OnFlag      			:1;    /**/
			uint8_t    Led7_OnFlag      			:1;    /**/
			uint8_t    Led8_OnFlag      			:1;    /**/
    }Bit;
  }Byte1; 
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
			uint8_t    Led9_OnFlag      			:1;    /**/
			uint8_t    Led10_OnFlag      			:1;    /**/
			uint8_t          									:5;    /**/
			uint8_t    KeyStuckFlag						:1;    /**/
    }Bit;
  }Byte2; 
  
}CDP_CenSideBoard_t;


/*
typedef   struct
{
	uint8_t DataLenth;
	uint8_t CtrlID;
	uint8_t KeyValue;
	Byte8 SideBoardCSFlag[2];
}CDP_CenSideBoard_t;
*/

void CDP_CenSideBoard_ByteRx(uint8_t RxByte);
void ReceviceDataFromSideBoard(void);
void SendDataToSideBoard100ms(void);
void Variable1msProcess(void);
void SideCtrlInit(void);


#endif



