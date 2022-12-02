/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    模块名称(Filename):       SysRun.h  
    项目名称(Projectname):       
    版本号(Version):	      
    创建日期(Date):           2008-7-15        
    作者(Author):             FS
    功能描述(Description):    用于外部调用 系统运行 函数
    其他说明(Others):         主要功能都在SystemRuning这个函数中执行
    修改记录(History):
****************************************************************/
#ifndef		_SYSRUN_H
#define		_SYSRUN_H

#include "Config.h"

extern	void 	SystemRuning(void);
extern	void    	SpikeCount(void);
extern	void		MusicSync_Process(void);

Uint16 Data_CRC16(Uchar* mpauc_Data, Uchar mcu_packetLength);


#endif
