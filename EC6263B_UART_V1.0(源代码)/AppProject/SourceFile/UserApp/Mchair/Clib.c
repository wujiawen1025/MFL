/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    ģ������(Filename):       Clib.c  
    ��Ŀ����(Projectname):       
    �汾��(Version):	      
    ��������(Date):           2015-10-21       
    ����(Author):             zrb
    ��������(Description):    �⺯������ʱ����
    ����˵��(Others):         
                         RamSet(Uchar *, Uchar , Uchar) ���� ���ڴ�ռ丶ֵ
                         Uchar IsZeroTrue(Uchar * , Uchar) ���� �ж������Ƿ����0
                         Uchar IsSameTrue(Uchar * , Uchar , Uchar) ���� �ж������Ƿ����ĳֵ
    �޸ļ�¼(History):
****************************************************************/
#include "Config.h"
#include "IO_Init.h"

void		RamSet(Uchar *buff, Uchar data, Uchar len)
{
	Uint16		i;
	
	for(i = 0; i <= len; i++,buff++)
	{
		*buff = data;
	}
}

Uchar	IsZeroTrue(Uchar *buff,Uchar len)
{
	Uchar i;

	for(i = 0; i < len; i++,buff++)
	{
		if(*buff != 0)
		{
			return (0xff);
		}
	}
	return (0x00);
}

Uchar    IsSameTrue(Uchar *buff, Uchar data , Uchar len)
{
	Uchar i;

	for(i = 0 ; i < len; i++,buff++)
	{
		if(*buff != data)
		{
			return (0xff);
		}
	}
	return (0x00);
}

void	 Delay5us()
{
	Uchar  temp;
	
	for(temp=20; temp; temp--)
	{
		//asm nop;
	}
}

void	Delay50ms()
{
	Uchar	templ;
	Uchar	temph;

	for(temph=125; temph; temph--)
	{	
		for(templ=255; templ; templ--)
		{
			//__RESET_WATCHDOG();
		}	 
	}
}
void	Delay5ms()
{
	Uchar	templ;
	Uchar	temph;
	
	for(temph=12; temph; temph--)
	{	
		for(templ=255; templ; templ--)
		{
		     //__RESET_WATCHDOG();
		}	 
	}
}
void	Delay200ms()
{
    Uchar	templ;
    Uchar	temph;
	
	for(temph = 255; temph; temph--)
	{	
		for(templ=255; templ; templ--) 
		{
			
		}
	}
}

void	Delay500ms()
{
	Uchar  temp;

	for(temp=10; temp; temp--)
	{
		Delay50ms();
	}
}

