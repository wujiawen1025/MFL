/****************************************************************
    Copyright? 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    模块名称(Filename):       Config.h  
    项目名称(Projectname):       
    版本号(Version):	      
    创建日期(Date):           2008-7-15        
    作者(Author):             FS
    功能描述(Description):    宏定义及编译条件定义
    其他说明(Others):         包括常量、事件、编译条件定义
    修改记录(History):
****************************************************************/

#ifndef		_CONFIG_H
#define		_CONFIG_H


//可选项目
#define		EC628_CORE_V10					1	// 3D机芯控制板
//编译选项
#define		PROJECT_CONFIG	EC628_CORE_V10



//--------------编译条件定义-------------
//代码版本
#define		CODE_3D_CORE_BOARD_V10			1

//电路板版本
#define		LAYOUT_3D_BACK_V10				1

//MCU型号
#define		MKE02Z64VLD4_64P					1                  //LQFP 64PIN


#if		PROJECT_CONFIG == EC628_CORE_V10     // 3D机芯控制板
#define		CODE_CONFIG			CODE_3D_CORE_BOARD_V10
#define		MCU_CONFIG			MKE02Z64VLD4_64P
#define		LAYOUT_CONFIG			LAYOUT_3D_BACK_V10


#endif

//--------------常量定义--------------

#define		ROLL_COUNT_MIN		0    //底端的记数脉冲值
#define		FLEX_COUNT_MAX		5	//伸缩记数最大值(前端)
#define		FLEX_COUNT_MIN		0	//伸缩记数最小值(后端)

#define		KNEAD_COUNT_MAX				60	//底端的记数脉冲值
#define		KNEAD_COUNT_MIN				0	//底端的记数脉冲值
#define		KNEAD_POINT_COUNT			9	//


//--------------共用常量定义---------------
#define		HEAD_CODE_NORMAL			0x03	//命令头--通常情况
#define		HEAD_CODE_EVENT			0x06	//命令头--有事件发生时
#define		CONTROLLER_ADDR			0x01	//手控器通讯地址
#define		CORE_ADDR					0x02	//机芯控制板通讯地址
#define		SIDE_ADDR					0x08	//侧板控制板通讯地址

#define		RECEIVE_BIT_LENGTH		1	//接收机芯控制板包位数据区长度
#define		RECEIVE_DATA_LENGTH		2	//接收机芯控制板包字节数据区长度

#define		SEND_BIT_LENGTH			1	//发送手控器包位数据区长度
#define		SEND_DATA_LENGTH			4	//发送手控器包字节数据区长度



#define		RX_BUFFER_LENGTH			(RECEIVE_BIT_LENGTH+RECEIVE_DATA_LENGTH+4)  //接收包数据总长度[头+地址+位区+字节区+校验码]
#define		TX_BUFFER_LENGTH			(SEND_BIT_LENGTH+SEND_DATA_LENGTH+4)  //发送包数据总长度[头+地址+位区+字节区+校验码]


#define         EVENT_BUFFER_LENGTH		10	//事件处理堆栈长度
#define		FLAG_SECTION_LENGTH		5	//功能标志位数据区长度
#define		LOSE_LINK_TIME				4	//失去连接时间(秒)


//--------------事件定义--------

#define		evTime50MS					2
#define		evTime100MS				3
#define		evTime200MS				4
#define		evTime500MS				5
#define		evTime1S					6
#define		evTime25MS					7
#define		evReceiveUART0				8
#define		evReceiveUART1				9
#define		evReceiveUART2				10
#define		evReceiveUART3				11
#define		evReceiveUART4				12
#define		evReceiveUART2_1			13

//--------------其他宏定义---------------
//#define	 	TRUE                    1
//#define		FALSE			0
#define		OK			0
//#define		ERROR			-1
//#define		OPEN			1
//#define		CLOSE			0
#define		ENVISION		0x00
#define		DISVISION		0xff

#define		Boolean0		1<<0
#define		Boolean1		1<<1
#define		Boolean2		1<<2
#define		Boolean3		1<<3
#define		Boolean4		1<<4
#define		Boolean5		1<<5
#define		Boolean6		1<<6
#define		Boolean7		1<<7

//typedef		unsigned  char 	Uchar;
//typedef		unsigned  int		Uint;
//typedef		unsigned  long		Ulong;
//typedef		signed 	char		Schar;
//ypedef		signed	int		Sint;
//typedef		signed	long		Slong;

typedef		unsigned char 		Uchar;
typedef		unsigned short	 int	Uint16;
typedef		unsigned int		Uint32;
typedef		unsigned long		Ulong;

typedef		signed char		Schar;
typedef		signed short int	Sint16;
typedef		signed int			Sint32;
typedef		signed long		Slong;


#define         TestBit(var,bit)        ((var) &  (1<<(bit)))
#define         ClrBit(var,bit)	          ((var) &= (~(1<<(bit))))
#define         SetBit(var,bit)          ((var) |= (1<<(bit)))

#endif

