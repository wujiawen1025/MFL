/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    ģ������(Filename):       Datatype.h  
    ��Ŀ����(Projectname):       
    �汾��(Version):	      
    ��������(Date):           2008-7-15        
    ����(Author):             FS
    ��������(Description):    �ṹ��͹�ͬ�嶨��
    ����˵��(Others):         
    �޸ļ�¼(History):
****************************************************************/

#ifndef		_DATATYPE_H
#define		_DATATYPE_H

#include "Config.h"

typedef  union
{
    struct
    {
	unsigned  char bit0 :	1;
	unsigned  char bit1 :	1;
	unsigned  char bit2 : 	1;
	unsigned  char bit3 :	1;
	unsigned  char bit4 :	1;
	unsigned  char bit5 :	1;
	unsigned  char bit6 :	1;
	unsigned  char bit7 :	1;		
    }bits;
    Uchar	Byte;
}Byte8;

typedef struct
{
    Byte8    Core1Key;
    Byte8    Core2Key;
    Byte8    GasVibKey;
    Byte8    AutoKey;
    Byte8    HandSpikeKey;
    Byte8    AdjustKey;
    Byte8    AboutSystem;
}stKey;


typedef struct
{
    Uchar    SendHead;                //AA
    Uchar    Address;
    Uchar    DataLength;
    Byte8    SendBit[SEND_BIT_LENGTH];
    Uchar    SendData[SEND_DATA_LENGTH];
    Uchar    CheckkSum;
}stSend;



typedef struct
{
    Uchar    ReceiveHead;             //Ac
    Uchar    Address;
    Uchar    DataLength;
    Byte8    ReceiveBit[RECEIVE_BIT_LENGTH];
    Uchar      ReceiveData[RECEIVE_DATA_LENGTH];
    Uchar    CheckkSum;
}stReceive;

typedef struct
{
    	Uchar    GasBit2;
	Uchar    GasBit1;  
	Uchar    GasPosition;
    	Uchar    GasLevel1Time;          //ǿ��1
    	Uchar    GasLevel2Time;		//ǿ��2
    	Uchar    GasLevel3Time;		//ǿ��3
}stGas;

typedef  struct
{
    	Byte8	GasBit2;                
	Byte8	GasBit1;
	Byte8	GasPosition;
	Uchar	Step;
	Uchar	StepTime;
}stGasReturn;

typedef struct
{
	Uchar    	CorePosition;
	Uchar    	CoreFunction;
	Uchar    	CoreWidth;
    	Uchar    	GasBit2;
	Uchar    	GasBit1;  
    	Uchar    	GasLevel1Time;           //ǿ��1
    	Uchar    	GasLevel2Time;		  //ǿ��2
    	Uchar    	GasLevel3Time;		  //ǿ��3
    	Uchar	ESSpikeBit;
    	Uchar    	BackSpikePosition;
	Uchar    	FeetSpikePosition;
	Uchar    	ZeroSpikePosition;
}stStretch;

typedef  struct
{
	Uchar    	CorePosition;
	Uchar    	CoreFunction;
	Uchar    	CoreWidth;
    	Byte8	GasBit2;                
	Byte8	GasBit1;
	Uchar	Step;
	Uchar	StepTime;
	Byte8      ESSpikeBit;
	Uchar    	BackSpikePosition;
	Uchar    	FeetSpikePosition;
	Uchar    	ZeroSpikePosition;
}stStretchReturn;

typedef struct
{
    Uchar    VibMode;
	     //0x00 ͣ
	     //0x01 ����    ��0.5���0.5��
	     //0x02 ����
    Uchar    Time;
    Uchar    PWM;
}stVib;

typedef struct
{
    Uchar    OutFlag;               //��IO��ƽ����ֵ 0xff(1)  0x00(0)
    Uchar    Step;                  //�񶯲��践��ֵ
    Uchar    StepTime;              //�񶯲���ʱ�䷵��ֵ
    Uchar    PointTime;             //�񶯵���ģʽ���ʱ�䷵��ֵ(0--4)
    Uchar    PointFlag;             //�񶯵���ģʽ���񷵻ر�־    1��  0ͣ
    Uchar    PWMTime;               //��ǿ�ȵ���ʱ�䷵��ֵ(0--9)
}stVibReturn;

typedef  struct
{
	Uchar    Direction;       		
		// 0x00 == STOP
		// 0x01 == UP
		// 0x02 == DOWN
	Uchar    Function1;
	Uchar    Function2;
	Uchar    Position;	          //�г�(0xff���ж�)
	Uchar    Time;		  //ʱ��(0xff���ж�)
	Uchar    Width;       	  //���
		//0x00 == NOCHANGE
		//0x01 == NARROW
		//0X02 == MIDDLE
		//0X04 == WIDE
}stCoreAuto1;

typedef  struct
{
	Uchar    Direction;       		
		// 0x00 == STOP
		// 0x01 == UP
		// 0x02 == DOWN
	Uchar    Function;
		// 0x00 == ROLL
		// 0x01 == KNEAD
		// 0x02 == TAP
		// 0x03 == DUALACTION
	Uchar    Position;	          //�г�(0xff���ж�)
	Uchar    Time;		  //ʱ��(0xff���ж�)
	Uchar    Width;       	  //���
		//0x00 == NOCHANGE
		//0x01 == NARROW
		//0X02 == MIDDLE
		//0X04 == WIDE
	Uchar	Speed;
		//0x01 == SPEED1
		//0x02 == SPEED2
		//0x03 == SPEED3
	Uchar	Strength;
		//0x01 == STRENGTH1
		//0x02 == STRENGTH2
		//0x03 == STRENGTH3
}stCoreAuto2;

typedef	struct
{
	Uint16		PWM_Data1;
	Uint16		PWM_Data2;
	Uint16		PWM_Data3;
	Uint16		PWM_Data4;
	Uint16		PWM_Data5;
	Uint16		PWM_Data6;
	Uint16		PWM_Data7;
	Uint16		PWM_Data8;
	Uint16		PWM_Data9;
	Uint16		PWM_Data10;
}stPWMDate;
typedef	struct
{
	Uint16		M1BackHeightSet;
	Uchar	M1NeckShoulderTimeSet;
	Uchar	M1BackSeatTimeSet;
	Uchar	M1LumbarTimeSet;
	Uchar	M1FeetCalvesTimeSet;
	
	Uint16		M2BackHeightSet;
	Uchar	M2NeckShoulderTimeSet;
	Uchar	M2BackSeatTimeSet;
	Uchar	M2LumbarTimeSet;
	Uchar	M2FeetCalvesTimeSet;
	
	Uint16		M3BackHeightSet;
	Uchar	M3NeckShoulderTimeSet;
	Uchar	M3BackSeatTimeSet;
	Uchar	M3LumbarTimeSet;
	Uchar	M3FeetCalvesTimeSet;
}stStorage;
/*
typedef	struct
{
	Uchar	M1NeckShoulderTimeSet;
//	Uchar	M1NeckShoulderIntensitySet;
	Uchar	M1BackSeatTimeSet;
//	Uchar	M1BackSeatIntensitySet;
	Uchar	M1LumbarTimeSet;
//	Uchar	M1LumbarIntensitySet;
	Uchar	M1FeetCalvesTimeSet;
//	Uchar	M1FeetCalvesIntensitySet;
	
	Uchar	M2NeckShoulderTimeSet;
//	Uchar	M2NeckShoulderIntensitySet;
	Uchar	M2BackSeatTimeSet;
//	Uchar	M2BackSeatIntensitySet;
	Uchar	M2LumbarTimeSet;
//	Uchar	M2LumbarIntensitySet;
	Uchar	M2FeetCalvesTimeSet;
//	Uchar	M2FeetCalvesIntensitySet;

	Uchar	M3NeckShoulderTimeSet;
//	Uchar	M3NeckShoulderIntensitySet;
	Uchar	M3BackSeatTimeSet;
//	Uchar	M3BackSeatIntensitySet;
	Uchar	M3LumbarTimeSet;
//	Uchar	M3LumbarIntensitySet;
	Uchar	M3FeetCalvesTimeSet;
//	Uchar	M3FeetCalvesIntensitySet;
}stStorage;
*/

#endif		
