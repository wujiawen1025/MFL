/***************************************************************************
    Copyright? 2007-2009, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    ģ������(Filename):	Identify.h  
    ��Ŀ����(Projectname):       
    �汾��(Version):	      
    ��������(Date):		2009-10-23      
    ����(Author):			lhl
    ��������(Description):	���������Ϣ    
    �޸ļ�¼(History):
****************************************************************************/
#ifndef		_IDENTIFY_H
#define		_IDENTIFY_H

#include "Config.h"

/*
const unsigned char Identify[] @ 0xFE00 = //���������Ϣ
{
//������"|"��ֹ,"^"�ſ��ƻ���

"|\
ProgVer:EC618S-CORE-V1.1^\
PCB:3D-BACK-V1.0^\
MCU:MC9S08AC16^\
EditDate:2015.2.4\
|"

};

*/





















#define		REQUEST	0x55
unsigned char	vReceiveRequestCounter;
/*
void IdentifySend(void)
{
	unsigned char	i;
	
	SCI1C2_TCIE = 0;		//�ط����ж�
	SCI1C2_TE = 1;		//����ʹ��
	i = 0;
	while(Identify[i] != '\0' && i<200)
	{
		SCI1D = Identify[i];
		i++;
		while(!SCI1S1_TC);	//���ò�ѯ��ʽ,��������
		__RESET_WATCHDOG();
	}
	SCI1C2_TCIE = 0;//�ط����ж�
	SCI1C2_TE = 0;	//�ط���ʹ��
	PTEDD_PTEDD0 = 0;//�����
}
*/
#endif
