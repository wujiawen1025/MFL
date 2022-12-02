/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    模块名称(Filename):       Flag.h  
    项目名称(Projectname):       
    版本号(Version):	      
    创建日期(Date):           2008-7-15        
    作者(Author):             FS
    功能描述(Description):    各种标志位定义(包括 通讯数据包标志、LCD/LED显示标志、按键标志、动作标志)
    其他说明(Others):         
    修改记录(History):
****************************************************************/

#ifndef         _FLAG_H
#define		_FLAG_H

#include "Glob.h"

//======定义========
#define		SystemRunFlag			gFlagData[0].bits.bit0
#define		SystemResetFlag			gFlagData[0].bits.bit1

#define		Ev50MsFlag			       gFlagData[0].bits.bit3
#define		Ev100MsFlag			       gFlagData[0].bits.bit4
#define		Ev500MsFlag			       gFlagData[0].bits.bit5
#define		Ev1SFlag			       gFlagData[0].bits.bit6

#define		SysWaitingRunFlag		gFlagData[2].bits.bit3

#define		AcheLEDDisFlag		gFlagData[2].bits.bit5

#define		Ev25MsFlag 					gFlagData[3].bits.bit3


#define		EvReceiveUART0Flag 					gFlagData[4].bits.bit0
#define		EvReceiveUART1Flag 					gFlagData[4].bits.bit1
#define		EvReceiveUART2Flag 					gFlagData[4].bits.bit2
#define		EvReceiveUART3Flag 					gFlagData[4].bits.bit3
#define		EvReceiveUART4Flag 					gFlagData[4].bits.bit4
#define		EvReceiveUART2_1Flag 					gFlagData[4].bits.bit5

#define		RollCountErrorFlag		gbErrorState.bits.bit0
#define		FlexCountErrorFlag		gbErrorState.bits.bit1
#define		KneadErrorFlag			gbErrorState.bits.bit2
#define		TapErrorFlag				gbErrorState.bits.bit3
/*
//======侧板控制板发送至中心板数据包位定义========
//#define								gTxData.SendBit[0].bits.bit0
//#define								gTxData.SendBit[0].bits.bit1
//#define								gTxData.SendBit[0].bits.bit2
//#define								gTxData.SendBit[0].bits.bit3
//#define								gTxData.SendBit[0].bits.bit4
//#define								gTxData.SendBit[0].bits.bit5

//======侧板控制板从中心板接收数据包位定义=======
#define		LED1RunFlag					gRxData.ReceiveBit[0].bits.bit0// 0=关      1=开
#define		LED2RunFlag					gRxData.ReceiveBit[0].bits.bit1// 1=向下   0=向上
#define		LED3RunFlag					gRxData.ReceiveBit[0].bits.bit2// 0=刹车      1=开
#define		LEDPRunFlag					gRxData.ReceiveBit[0].bits.bit3// 0=向后1=向前
//#define								gRxData.ReceiveBit[0].bits.bit4// 0=正向1=反向
//#define								gRxData.ReceiveBit[0].bits.bit5// 0=关      1=开

//#define								gRxData.ReceiveBit[1].bits.bit0// 1= ERP Mode  0= 正常模式
//#define								gRxData.ReceiveBit[1].bits.bit1// 1= ERP Mode  0= 正常模式
//#define								gRxData.ReceiveBit[1].bits.bit2
//#define								gRxData.ReceiveBit[1].bits.bit3
#define		SystemRunFlag				gRxData.ReceiveBit[1].bits.bit4

*/
//==============其他标志位定义==================





#endif
