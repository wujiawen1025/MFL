/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    ģ������(Filename):       Flag.h  
    ��Ŀ����(Projectname):       
    �汾��(Version):	      
    ��������(Date):           2008-7-15        
    ����(Author):             FS
    ��������(Description):    ���ֱ�־λ����(���� ͨѶ���ݰ���־��LCD/LED��ʾ��־��������־��������־)
    ����˵��(Others):         
    �޸ļ�¼(History):
****************************************************************/

#ifndef         _FLAG_H
#define		_FLAG_H

#include "Glob.h"

//======����========
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
//======�����ư巢�������İ����ݰ�λ����========
//#define								gTxData.SendBit[0].bits.bit0
//#define								gTxData.SendBit[0].bits.bit1
//#define								gTxData.SendBit[0].bits.bit2
//#define								gTxData.SendBit[0].bits.bit3
//#define								gTxData.SendBit[0].bits.bit4
//#define								gTxData.SendBit[0].bits.bit5

//======�����ư�����İ�������ݰ�λ����=======
#define		LED1RunFlag					gRxData.ReceiveBit[0].bits.bit0// 0=��      1=��
#define		LED2RunFlag					gRxData.ReceiveBit[0].bits.bit1// 1=����   0=����
#define		LED3RunFlag					gRxData.ReceiveBit[0].bits.bit2// 0=ɲ��      1=��
#define		LEDPRunFlag					gRxData.ReceiveBit[0].bits.bit3// 0=���1=��ǰ
//#define								gRxData.ReceiveBit[0].bits.bit4// 0=����1=����
//#define								gRxData.ReceiveBit[0].bits.bit5// 0=��      1=��

//#define								gRxData.ReceiveBit[1].bits.bit0// 1= ERP Mode  0= ����ģʽ
//#define								gRxData.ReceiveBit[1].bits.bit1// 1= ERP Mode  0= ����ģʽ
//#define								gRxData.ReceiveBit[1].bits.bit2
//#define								gRxData.ReceiveBit[1].bits.bit3
#define		SystemRunFlag				gRxData.ReceiveBit[1].bits.bit4

*/
//==============������־λ����==================





#endif
