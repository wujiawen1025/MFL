/****************************************************************
    Copyright(c) 2007-2008,Mengfali Tech.Co,.Ltd
    
    ģ������(Filename):       Init.c  
    ��Ŀ����(Projectname):       
    �汾��(Version):	      
    ��������(Date):           2015-10-21        
    ����(Author):             zrb
    ��������(Description):    ��ʼ������
    ����˵��(Others):         ��ʼ����ʱ����IO��ͨѶ���洢�ռ䡢�ж�
    �޸ļ�¼(History):
****************************************************************/


#include "Flag.h"
#include "IO_Init.h"
#include "Isr.h"
#include "clib.h"
void	Init_Serial(void)
{
	BSP_UART_RegRxByteCB(BSP_UART_Port2, UART2_ByteRx); /*ע�ᴮ�ڽ��մ�����*/
	BSP_UART_RegRxByteCB(BSP_UART_Port3, UART3_ByteRx); /*ע�ᴮ�ڽ��մ�����*/
	BSP_UART_RegRxByteCB(BSP_UART_Port4, UART4_ByteRx); /*ע�ᴮ�ڽ��մ�����*/
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

