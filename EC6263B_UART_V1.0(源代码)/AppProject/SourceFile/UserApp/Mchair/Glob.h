/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    模块名称(Filename):       Glob.h  
    项目名称(Projectname):       
    版本号(Version):	      
    创建日期(Date):           2008-7-15        
    作者(Author):             FS
    功能描述(Description):    变量定义
    其他说明(Others):         
    修改记录(History):
****************************************************************/

#ifndef         _GLOB_H
#define		_GLOB_H

#include "Config.h"
#include "Datatype.h"

//-------------定时相关变量-------------
extern Uchar		gTime1MS,vTime10MS,gTime100MS,gTime1S,gTime1MIN;

//-------------机芯相关变量-------------

//-------------A/D转换程序用相关变量-------------

//-------------事件相关变量-------------
extern Uchar		gWriteEventCount,gReadEventCount,gEventBuffer[EVENT_BUFFER_LENGTH];
//-------------通讯相关变量-------------
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

//-------------标志位相关变量-------------
extern Byte8		gFlagData[FLAG_SECTION_LENGTH];
extern Uchar	gWaitingTimer;

//-------------其他变量-------------
extern Uchar	gNothingReceiveTimer0,gNothingReceiveTimer1,gNothingReceiveTimer2,gNothingReceiveTimer2_1,gNothingReceiveTimer3,gNothingReceiveTimer4;
extern Byte8	gbErrorState;

#endif
