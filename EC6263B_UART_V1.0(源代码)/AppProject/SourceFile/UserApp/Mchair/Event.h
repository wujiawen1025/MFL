/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    模块名称(Filename):       Event.h  
    项目名称(Projectname):       
    版本号(Version):	      
    创建日期(Date):           2008-7-15        
    作者(Author):             FS
    功能描述(Description):    用于外部调用 压入和读出事件 函数
    其他说明(Others):         
    修改记录(History):
****************************************************************/

#ifndef		_EVENT_H
#define		_EVENT_H

#include   "Config.h"

extern   void 	PushEvent(Uchar event);
extern	 Uchar	ReadEvent(void);

#endif
