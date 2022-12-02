/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    ģ������(Filename):       Glob.h  
    ��Ŀ����(Projectname):       
    �汾��(Version):	      
    ��������(Date):           2008-7-15        
    ����(Author):             FS
    ��������(Description):    ��������
    ����˵��(Others):         
    �޸ļ�¼(History):
****************************************************************/

#ifndef         _GLOB_H
#define		_GLOB_H

#include "Config.h"
#include "Datatype.h"

//-------------��ʱ��ر���-------------
extern Uchar		gTime1MS,vTime10MS,gTime100MS,gTime1S,gTime1MIN;

//-------------��о��ر���-------------

//-------------A/Dת����������ر���-------------

//-------------�¼���ر���-------------
extern Uchar		gWriteEventCount,gReadEventCount,gEventBuffer[EVENT_BUFFER_LENGTH];
//-------------ͨѶ��ر���-------------
extern Uchar	gUART0RxBuffer[40],gRxUART0Data[40],gTxUART0Buffer[40];
extern Uchar	gUART0TxDataCount,gUART0RxDataCount,gUART0SCICheckout;

extern Uchar	gUART1RxBuffer[40],gRxUART1Data[40],gTxUART1Buffer[40];
extern Uchar	gUART1TxDataCount,gUART1RxDataCount,gUART1SCICheckout;

extern Uchar	gUART2RxBuffer[40],gRxUART2Data[40],gTxUART2Buffer[40];
extern Uchar	gUART2TxDataCount,gUART2RxDataCount,gUART2SCICheckout;

extern Uchar	gUART2RxBuffer_1[40],gRxUART2Data_1[40],gTxUART2Buffer_1[40];
extern Uchar	gUART2TxDataCount,gUART2RxDataCount_1,gUART2SCICheckout_1;

extern Uchar	gUART3RxBuffer[40],gRxUART3Data[40],gTxUART3Buffer[40];
extern Uchar	gUART3TxDataCount,gUART3RxDataCount,gUART3SCICheckout;

extern Uchar	gUART4RxBuffer[40],gRxUART4Data[40],gTxUART4Buffer[40];
extern Uchar	gUART4TxDataCount,gUART4RxDataCount,gUART4SCICheckout;

//-------------��־λ��ر���-------------
extern Byte8		gFlagData[FLAG_SECTION_LENGTH];
extern Uchar	gWaitingTimer;

//-------------��������-------------
extern Uchar	gNothingReceiveTimer0,gNothingReceiveTimer1,gNothingReceiveTimer2,gNothingReceiveTimer2_1,gNothingReceiveTimer3,gNothingReceiveTimer4;
extern Byte8	gbErrorState;

#endif
