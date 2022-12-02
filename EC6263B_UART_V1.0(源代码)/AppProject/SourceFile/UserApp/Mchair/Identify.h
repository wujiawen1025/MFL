/***************************************************************************
    Copyright? 2007-2009, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    模块名称(Filename):	Identify.h  
    项目名称(Projectname):       
    版本号(Version):	      
    创建日期(Date):		2009-10-23      
    作者(Author):			lhl
    功能描述(Description):	程序鉴别信息    
    修改记录(History):
****************************************************************************/
#ifndef		_IDENTIFY_H
#define		_IDENTIFY_H

#include "Config.h"

/*
const unsigned char Identify[] @ 0xFE00 = //程序鉴别信息
{
//必须用"|"起止,"^"号控制换行

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
	
	SCI1C2_TCIE = 0;		//关发送中断
	SCI1C2_TE = 1;		//发送使能
	i = 0;
	while(Identify[i] != '\0' && i<200)
	{
		SCI1D = Identify[i];
		i++;
		while(!SCI1S1_TC);	//采用查询方式,连续发送
		__RESET_WATCHDOG();
	}
	SCI1C2_TCIE = 0;//关发送中断
	SCI1C2_TE = 0;	//关发送使能
	PTEDD_PTEDD0 = 0;//输入口
}
*/
#endif
