/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    ģ������(Filename):       SysRun.h  
    ��Ŀ����(Projectname):       
    �汾��(Version):	      
    ��������(Date):           2008-7-15        
    ����(Author):             FS
    ��������(Description):    �����ⲿ���� ϵͳ���� ����
    ����˵��(Others):         ��Ҫ���ܶ���SystemRuning���������ִ��
    �޸ļ�¼(History):
****************************************************************/
#ifndef		_SYSRUN_H
#define		_SYSRUN_H

#include "Config.h"

extern	void 	SystemRuning(void);
extern	void    	SpikeCount(void);
extern	void		MusicSync_Process(void);

Uint16 Data_CRC16(Uchar* mpauc_Data, Uchar mcu_packetLength);


#endif
