/****************************************************************
    Copyright? 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    ģ������(Filename):       Config.h  
    ��Ŀ����(Projectname):       
    �汾��(Version):	      
    ��������(Date):           2008-7-15        
    ����(Author):             FS
    ��������(Description):    �궨�弰������������
    ����˵��(Others):         �����������¼���������������
    �޸ļ�¼(History):
****************************************************************/

#ifndef		_CONFIG_H
#define		_CONFIG_H


//��ѡ��Ŀ
#define		EC628_CORE_V10					1	// 3D��о���ư�
//����ѡ��
#define		PROJECT_CONFIG	EC628_CORE_V10



//--------------������������-------------
//����汾
#define		CODE_3D_CORE_BOARD_V10			1

//��·��汾
#define		LAYOUT_3D_BACK_V10				1

//MCU�ͺ�
#define		MKE02Z64VLD4_64P					1                  //LQFP 64PIN


#if		PROJECT_CONFIG == EC628_CORE_V10     // 3D��о���ư�
#define		CODE_CONFIG			CODE_3D_CORE_BOARD_V10
#define		MCU_CONFIG			MKE02Z64VLD4_64P
#define		LAYOUT_CONFIG			LAYOUT_3D_BACK_V10


#endif

//--------------��������--------------

#define		ROLL_COUNT_MIN		0    //�׶˵ļ�������ֵ
#define		FLEX_COUNT_MAX		5	//�����������ֵ(ǰ��)
#define		FLEX_COUNT_MIN		0	//����������Сֵ(���)

#define		KNEAD_COUNT_MAX				60	//�׶˵ļ�������ֵ
#define		KNEAD_COUNT_MIN				0	//�׶˵ļ�������ֵ
#define		KNEAD_POINT_COUNT			9	//


//--------------���ó�������---------------
#define		HEAD_CODE_NORMAL			0x03	//����ͷ--ͨ�����
#define		HEAD_CODE_EVENT			0x06	//����ͷ--���¼�����ʱ
#define		CONTROLLER_ADDR			0x01	//�ֿ���ͨѶ��ַ
#define		CORE_ADDR					0x02	//��о���ư�ͨѶ��ַ
#define		SIDE_ADDR					0x08	//�����ư�ͨѶ��ַ

#define		RECEIVE_BIT_LENGTH		1	//���ջ�о���ư��λ����������
#define		RECEIVE_DATA_LENGTH		2	//���ջ�о���ư���ֽ�����������

#define		SEND_BIT_LENGTH			1	//�����ֿ�����λ����������
#define		SEND_DATA_LENGTH			4	//�����ֿ������ֽ�����������



#define		RX_BUFFER_LENGTH			(RECEIVE_BIT_LENGTH+RECEIVE_DATA_LENGTH+4)  //���հ������ܳ���[ͷ+��ַ+λ��+�ֽ���+У����]
#define		TX_BUFFER_LENGTH			(SEND_BIT_LENGTH+SEND_DATA_LENGTH+4)  //���Ͱ������ܳ���[ͷ+��ַ+λ��+�ֽ���+У����]


#define         EVENT_BUFFER_LENGTH		10	//�¼������ջ����
#define		FLAG_SECTION_LENGTH		5	//���ܱ�־λ����������
#define		LOSE_LINK_TIME				4	//ʧȥ����ʱ��(��)


//--------------�¼�����--------

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

//--------------�����궨��---------------
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

