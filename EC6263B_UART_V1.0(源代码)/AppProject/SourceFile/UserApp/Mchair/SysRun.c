/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    模块名称(Filename):       SysRun.c  
    项目名称(Projectname):       
    版本号(Version):	      
    创建日期(Date):           2008-7-15        
    作者(Author):             FS
    功能描述(Description):    系统运行函数
    其他说明(Others):         主要功能都在此函数中实现
    修改记录(History):
****************************************************************/



#include <String.h>
#include <math.h>
#include "Config.h"
#include "IO_Init.h"
#include "Event.h"
#include "Glob.h"
#include "Clib.h"
#include "Flag.h"
#include "Init.h"
#include "Tab.h"
#include "bsp_uart.h"


#define CRC16_INIT							0xFFFF
#define CRC16_POLY							0xA001
Uint16 Data_CRC16(Uchar* mpauc_Data, Uchar mcu_packetLength)
{
	Uchar ucTxByteCnt = 0;
	Uchar ucTxBitShiftCnt = 0;
	Uchar mun_CRC16_TxPacket_Length = 0;
	Uint16  usTxCRC16_Calc_Result = CRC16_INIT;

	mun_CRC16_TxPacket_Length = mcu_packetLength;
    for(ucTxByteCnt = 0 ; ucTxByteCnt< mun_CRC16_TxPacket_Length ; ucTxByteCnt++)
    {
    	usTxCRC16_Calc_Result ^= (*(mpauc_Data + ucTxByteCnt));
        for(ucTxBitShiftCnt =0; ucTxBitShiftCnt< 8 ; ucTxBitShiftCnt++)
        {
        	if(0 != (usTxCRC16_Calc_Result & 0x0001))
            {
            	usTxCRC16_Calc_Result = (usTxCRC16_Calc_Result>>1)^CRC16_POLY; //CRC16_POLY : 0xA001
            }
            else
            {
            	usTxCRC16_Calc_Result = (usTxCRC16_Calc_Result >>1);
            }
        }
    }
	return usTxCRC16_Calc_Result ;
}
void	AcheSendDataToCenter(void)
{             						   //整理发送的数据
	static Uchar TxDataLength;
	TxDataLength = 4+gRxUART3Data[2];
	memcpy((Uchar *)&gTxUART2Buffer,(Uchar *)&gRxUART3Data,TxDataLength);
	BSP_UART_TxData(BSP_UART_Port2,gTxUART2Buffer, TxDataLength);
	
}

void	MXthSendDataToCenter(void)
{             						   //整理发送的数据
	static Uchar TxDataLength;
	TxDataLength = gRxUART4Data[2]+4;
	memcpy((Uchar *)&gTxUART2Buffer,(Uchar *)&gRxUART4Data,TxDataLength);
	BSP_UART_TxData(BSP_UART_Port2,gTxUART2Buffer, TxDataLength);
	
}
void	CenterSendDataToAche(void)
{             						   //整理发送的数据

	memcpy((Uchar *)&gTxUART3Buffer,(Uchar *)&gRxUART2Data,6);
	BSP_UART_TxData(BSP_UART_Port3,gTxUART3Buffer, 6);
	
}
void	CenterSendDataToMX(void)
{             						   //整理发送的数据
	static Uchar TxDataLength;
	TxDataLength = gRxUART2Data_1[2]+4;
	memcpy((Uchar *)&gTxUART4Buffer,(Uchar *)&gRxUART2Data_1,TxDataLength);
	BSP_UART_TxData(BSP_UART_Port4,gTxUART4Buffer,TxDataLength);
}


void    UART0SCI(void)
{

}

void    UART1SCI(void)
{
	
}

void    UART2SCI(void)
{
	CenterSendDataToAche();
}

void    UART2_1SCI(void)
{
	CenterSendDataToMX();
}

void    UART3SCI(void)
{
	AcheSendDataToCenter();
}
void    UART4SCI(void)
{
	MXthSendDataToCenter();
}





void    EventCollect(void) 
{
	if(EvReceiveUART0Flag)                         
	{	
		EvReceiveUART0Flag = 0;
		PushEvent(evReceiveUART0);
	}
	if(EvReceiveUART1Flag)
	{
		EvReceiveUART1Flag = 0;
		PushEvent(evReceiveUART1);
	}
	if(EvReceiveUART2Flag)
	{
		EvReceiveUART2Flag = 0;
		PushEvent(evReceiveUART2);
	}
	if(EvReceiveUART3Flag)
	{
		EvReceiveUART3Flag = 0;
		PushEvent(evReceiveUART3);
	}
	if(EvReceiveUART4Flag)
	{
		EvReceiveUART4Flag = 0;
		PushEvent(evReceiveUART4);
	}
	if(EvReceiveUART2_1Flag)
	{
		EvReceiveUART2_1Flag = 0;
		PushEvent(evReceiveUART2_1);
	}
	if(Ev25MsFlag)
	{
		Ev25MsFlag = 0;
		PushEvent(evTime25MS);
	}
	if(Ev50MsFlag)
	{
		Ev50MsFlag = 0;
		PushEvent(evTime50MS);
	}
	if(Ev100MsFlag)
	{
		Ev100MsFlag = 0;
		PushEvent(evTime100MS);
	}
}
void		VariableProcess100Ms(void)
{

}
void		VariableProcess1Sec(void)
{
	
}
void		Time25MS(void)
{
	
}
void		Time50MS(void)
{

}
void		Time100MS(void)
{
	VariableProcess100Ms();

}

//void AcheLEDCtrlProcess(void)
//{
//	if(AcheLEDDisFlag)
//		AcheLED_IO_ON;
//	else
//		AcheLED_IO_OFF;
//}
void 	SystemRuning(void)
{
	EventCollect();
//	AcheLEDCtrlProcess();
	
	//事件处理
	switch(ReadEvent())
	{
		case evTime25MS:
			Time25MS();			break;
		case evTime50MS:
			Time50MS();			break;
		case evTime100MS:
			Time100MS();		break;
		case evReceiveUART0:
			UART0SCI();                  break;
		case evReceiveUART1:
			UART1SCI();                  break;
		case evReceiveUART2:
			UART2SCI();                  break;
		case evReceiveUART3:
			UART3SCI();                  break;
		case evReceiveUART4:
			UART4SCI();                  break;
		case evReceiveUART2_1:
			UART2_1SCI();                  break;
		default:
			break;
	}
}

