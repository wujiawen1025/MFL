

#ifndef	_SideBoard_806_h_
#define	_SideBoard_806_h_


#define CEN_SIDECTRL_UART_PORT        BSP_UART_Port4                                         /*????*/


#define  SIDECTRL_TO_CEN_RXBUF_SIZE             24                   /*接收缓存大小*/ 
#define  CEN_TO_SIDECTRL_TXBUF_SIZE             SIDECTRL_TO_CEN_RXBUF_SIZE                   /*发送缓存大小*/ 

#define  Xxx_CTRL_RX_BUF_SIZE                   SIDECTRL_TO_CEN_RXBUF_SIZE                   /*接收缓存大小*/ 

#define  CDP_SIDECTRL_FRAME_MIN_LEN             12                   /*最小帧长度*/ 


#define  CDP_FRAME_BOUNDARY                     0x7E                 /*帧边界*/            
#define  CDP_FRAME_HEADER                       CDP_FRAME_BOUNDARY   /*帧头*/
#define  CDP_FRAME_FOOTER                       CDP_FRAME_BOUNDARY   /*帧尾*/            
#define  CDP_FRAME_ESC                          0x5E                 /*帧转义*/   

/*--------协议数据单元PDU内偏移-----------------------------*/
#define  CDP_PDU_OFFSET_DES                     0                    /*协议数据单元内的 目的地址 偏移*/
#define  CDP_PDU_OFFSET_SRC                     1                    /*协议数据单元内的 源地址   偏移*/
#define  CDP_PDU_OFFSET_VER                     2                    /*协议数据单元内的 版本号协议ID   偏移*/
#define  CDP_PDU_OFFSET_TAG                     3                    /*协议数据单元内的 数据包标识符   偏移*/
#define  CDP_PDU_OFFSET_CMD                     4                    /*协议数据单元内的 命令码   偏移*/
#define  CDP_PDU_OFFSET_ACK                     5                    /*协议数据单元内的 应答     偏移*/
#define  CDP_PDU_OFFSET_DU                      6                    /*协议数据单元内的 数据单元 偏移*/

/*--------数据单元DU内偏移-----------------------------*/
#define  CDP_DU_OFFSET_LEN                      0                    /*数据单元内的 长度 偏移*/            
#define  CDP_DU_OFFSET_ID                       1                    /*数据单元内的 ID   偏移*/  
#define  CDP_DU_OFFSET_DATA                     2                    /*数据单元内的 数据 偏移*/ 


/*===========通信地址=====================================*/
/*--------每个独立控制模块对应的地址分配-----------------------------*/
#define  CDP_ADDR_CEN                           0x01                 /*地址：中心板*/
#define  CDP_ADDR_SIDE                          0x11                 /*地址：测板按键*/


/*注意：一个物理模块中可能包含多个逻辑模块。比如小腿模块可能包含：小腿伸缩、小腿充气、脚滚等。
 *      因为当前版本协议数据ID标识的分配中，每个ID都代表不同的含义，且都能明确知道归属于于哪个逻辑模块。
 *      因此可只使用一个地址作为物理模块的地址即可，这样也有利于缩减数据包的大小。
 *      当然，如果以后的协议版本中，数据ID标识不能明确区分出数据归属于哪个模块，则应该使用多个逻辑地址以区分数据归属。*/

/*===========命令码=====================================*/

/*===========应答码=====================================*/





/*
************************************************************************************************************************
* 类型定义 :  中心板 <--> 蓝牙  中心板接收数据步骤                                                                             
************************************************************************************************************************
*/
/*
************************************************************************************************************************
* 类型定义 :  中心板 <--> 蓝牙  控制与状态标识                                                                              
************************************************************************************************************************
*/
typedef unsigned char uint8_t;

typedef  union 
{
  uint8_t All;
  struct
  {
    uint8_t    RxWifiDataOKFlag         :1;    /*通信数据接收完成*/
    uint8_t    SendWifiDataFlag         :1;    /*发送数据标志位*/

    uint8_t    Key8PressingFlag         :1;    /*8号键值按键按下标志*/
    uint8_t    Key8LedOnFlag            :1;    /*8号键值按键灯点亮标志*/
   
  }Bit;

}CDP_CenSideCtrlCSFlag_t;  /*Control State Flag  控制与状态标识*/

/*
************************************************************************************************************************
* 类型定义 :  中心板 <--> Wifi  相关操作数据结构                                                                            
************************************************************************************************************************
*/
typedef struct
{
	CDP_CenSideCtrlCSFlag_t CSFlag;
	uint8_t RxLen;									/*接收数据长度*/
	uint8_t RxBuf[SIDECTRL_TO_CEN_RXBUF_SIZE];          /*接收缓存区*/
	
	uint8_t RxNothingTimer;					        /*接收数据长度*/	
    
	
	uint8_t TxBuf[CEN_TO_SIDECTRL_TXBUF_SIZE];          /*发送缓存区*/
	uint8_t TxLen;									/*发送数据长度*/

}CDP_CenSideCtrl_t;	/*通信相关控制变量*/


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



