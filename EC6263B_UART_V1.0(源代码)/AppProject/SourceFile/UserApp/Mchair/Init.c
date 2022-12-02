/****************************************************************
    Copyright(c) 2007-2008,Mengfali Tech.Co,.Ltd
    
    模块名称(Filename):       Init.c  
    项目名称(Projectname):       
    版本号(Version):	      
    创建日期(Date):           2015-10-21        
    作者(Author):             zrb
    功能描述(Description):    初始化函数
    其他说明(Others):         初始化定时器、IO、通讯、存储空间、中断
    修改记录(History):
****************************************************************/


#include "Flag.h"
#include "IO_Init.h"
#include "Isr.h"
#include "clib.h"
void	Init_Serial(void)
{
	BSP_UART_RegRxByteCB(BSP_UART_Port2, UART2_ByteRx); /*注册串口接收处理函数*/
	BSP_UART_RegRxByteCB(BSP_UART_Port3, UART3_ByteRx); /*注册串口接收处理函数*/
	BSP_UART_RegRxByteCB(BSP_UART_Port4, UART4_ByteRx); /*注册串口接收处理函数*/
}

void	Init_Ram(void)
{
	RamSet((Uchar *)0x2000BA00, 0x00, 0xff);
	RamSet((Uchar *)0x2000BB00, 0x00, 0xff);
	RamSet((Uchar *)0x2000BC00, 0x00, 0xff);
	RamSet((Uchar *)0x2000BD00, 0x00, 0xff);
}


void	Init_System(void)
{
	 RamSet((Uchar *)0x2000BE00, 0x00, 0xff);
	 RamSet((Uchar *)0x2000BF00, 0x00, 0xff);
        SystemResetFlag=1;
        SysWaitingRunFlag = 1;
        gWaitingTimer = 0;
       
}

