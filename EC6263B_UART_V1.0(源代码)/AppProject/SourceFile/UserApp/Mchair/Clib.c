/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    模块名称(Filename):       Clib.c  
    项目名称(Projectname):       
    版本号(Version):	      
    创建日期(Date):           2015-10-21       
    作者(Author):             zrb
    功能描述(Description):    库函数及延时函数
    其他说明(Others):         
                         RamSet(Uchar *, Uchar , Uchar) —— 对内存空间付值
                         Uchar IsZeroTrue(Uchar * , Uchar) —— 判断数据是否等于0
                         Uchar IsSameTrue(Uchar * , Uchar , Uchar) —— 判断数据是否等于某值
    修改记录(History):
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

