/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    模块名称(Filename):       Glob.c  
    项目名称(Projectname):       
    版本号(Version):	      
    创建日期(Date):           2008-7-15        
    作者(Author):             FS
    功能描述(Description):    事件压入、事件读出函数
    其他说明(Others):         
    修改记录(History):
****************************************************************/
#include "Glob.h"


void 	PushEvent(Uchar event)
{	
	Uchar temp;
	
	if(gWriteEventCount >= EVENT_BUFFER_LENGTH)
	{
		gWriteEventCount = 0;
	}
	for(temp = 0; temp <= gWriteEventCount; temp++)
	{
		if(event == gEventBuffer[temp])
		{
			return;
		}
	}
	gEventBuffer[gWriteEventCount] = event;
	gWriteEventCount++;	
}

Uchar	ReadEvent()
{	
	Uchar event;

	if(gReadEventCount >= EVENT_BUFFER_LENGTH)
	{
		gReadEventCount = 0;
		event = gEventBuffer[gReadEventCount];
	}else
	{	
		if(gReadEventCount >= gWriteEventCount)
		{	
			gReadEventCount = 0;
			gWriteEventCount = 0;
			event = 0xff;
		}else
		{
			event = gEventBuffer[gReadEventCount];
			gEventBuffer[gReadEventCount] = 0xff;
			gReadEventCount++;
		}
	}
	return (event);
}
