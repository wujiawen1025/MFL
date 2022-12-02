/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    ģ������(Filename):       Glob.c  
    ��Ŀ����(Projectname):       
    �汾��(Version):	      
    ��������(Date):           2008-7-15        
    ����(Author):             FS
    ��������(Description):    �¼�ѹ�롢�¼���������
    ����˵��(Others):         
    �޸ļ�¼(History):
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
