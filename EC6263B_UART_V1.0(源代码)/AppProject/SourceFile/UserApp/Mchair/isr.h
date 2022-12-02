/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
***************************************************************************//*!
*
* @file isr.h
*
* @author Freescale
*
* @version 0.0.1
*
* @date Jun. 25, 2013
*
* @brief define interrupt service routines referenced by the vector table. 
*
* Note: Only "vectors.c" should include this header file.
*
*******************************************************************************
******************************************************************************/

#ifndef __ISR_H
#define __ISR_H

#include "SysRun.h"
#include  "Glob.h"
#include  "IO_Init.h"
#include  "Flag.h"
#include "bsp_uart.h"
#include <string.h>


Uchar gUART3RxDataStep,gUART3RxDataLength;


#define	UART0ReceiveRestart()	  gUART0RxDataCount = 0;gUART0SCICheckout = 0
#define	UART1ReceiveRestart()	  gUART1RxDataCount = 0;gUART1SCICheckout = 0
#define	UART2ReceiveRestart()	  gUART2RxDataCount = 0;gUART2SCICheckout = 0
#define	UART2ReceiveRestart_1()	  gUART2RxDataCount_1 = 0;gUART2SCICheckout_1 = 0
#define	UART3ReceiveRestart()	  gUART3RxDataCount = 0;gUART3SCICheckout = 0,gUART3RxDataStep = 0
#define	UART4ReceiveRestart()	  gUART4RxDataCount = 0;gUART4SCICheckout = 0

void SysTick_Handler( void )
{
	//static Uchar i;
	gTime1MS++;
	/*if(CoreFlexCountRunFlag)
	{
		if(gFlexCountTime < 0xffff)
		{
			gFlexCountTime++;
		}
	}
	else
	{
		gFlexCountTime = 0;
		gFlexCount1 = 0;
	}
	*/
	if(gTime1MS%25 == 5)
		Ev25MsFlag = 1;
	if(gTime1MS == 20 || gTime1MS == 70)
		Ev50MsFlag = 1;		// 50Ms事件
	if(gTime1MS == 40)
		Ev100MsFlag = 1;		// 100Ms事件
	if(gTime1MS >= 100)
	{
    		gTime1MS = 0;
    		gTime100MS++;
    		if(SysWaitingRunFlag)
		{
			gWaitingTimer++;
			if(gWaitingTimer > 10)
			{
				SysWaitingRunFlag = 0;
				gWaitingTimer = 0;
			}
		}
		
		if(gTime100MS == 2 || gTime100MS == 7)
			Ev500MsFlag = 1;	// 500Ms事件
		if(gTime100MS == 5)
			Ev1SFlag = 1;		// 1S事件
		if(gTime100MS >= 10)
		{
			gTime100MS = 0;
			gTime1S++;
		}
	}
// 1ms变量处理
	if(gNothingReceiveTimer0 < 255)
		gNothingReceiveTimer0++;
	if(gNothingReceiveTimer1 < 255)
		gNothingReceiveTimer1++;
	if(gNothingReceiveTimer2 < 255)
		gNothingReceiveTimer2++;
	if(gNothingReceiveTimer2_1 < 255)
		gNothingReceiveTimer2_1++;
	if(gNothingReceiveTimer3 < 255)
		gNothingReceiveTimer3++;
	if(gNothingReceiveTimer4 < 255)
		gNothingReceiveTimer4++;
	
}


void	CDP_CenMX_ByteRx(uint8_t RxByte)
{

	 if(gNothingReceiveTimer2_1 > 10)//超过10ms没有接收数据
	{
		UART2ReceiveRestart_1();
	}
	gNothingReceiveTimer2_1 = 0;
	
	if(gUART2RxDataCount_1 == 0)
	{
		gUART2RxBuffer_1[0] = RxByte;
		gUART2SCICheckout_1 += RxByte;
		gUART2RxDataCount_1++;
	}
	
	else if(gUART2RxDataCount_1 == 1)
	{
		if(RxByte == (0xFF - gUART2RxBuffer_1[0]))
		{
			gUART2RxBuffer_1[1] = RxByte;
			gUART2SCICheckout_1 += RxByte;
			gUART2RxDataCount_1++;
		}
		else
		{
			UART2ReceiveRestart_1();
		}
	}

	else if(gUART2RxDataCount_1 == 2)
	{
		if(RxByte <= 30)
		{
			gUART2RxBuffer_1[2] = RxByte;
			gUART2SCICheckout_1 += RxByte;
			gUART2RxDataCount_1++;
		}
		else
		{
			UART2ReceiveRestart_1();
		}
	}
	else if((gUART2RxDataCount_1 >= 3) && (gUART2RxDataCount_1 <= (gUART2RxBuffer_1[2] + 4 - 1)))
	{
		if(gUART2RxDataCount_1 == (gUART2RxBuffer_1[2] + 4 - 1))
		{
			if(RxByte == gUART2SCICheckout_1)
			{
				gUART2RxBuffer_1[gUART2RxDataCount_1] = RxByte;
				memcpy((Uchar *)&gRxUART2Data_1,(Uchar *)&gUART2RxBuffer_1,(gUART2RxBuffer_1[2] + 4));
				EvReceiveUART2_1Flag = 1;
			}
			UART2ReceiveRestart_1();
		}else
		{
			gUART2RxBuffer_1[gUART2RxDataCount_1] = RxByte;
			gUART2RxDataCount_1++;
			gUART2SCICheckout_1 += RxByte;
		}
	}
	else
	{
		UART2ReceiveRestart_1();
	}

}

void UART2_ByteRx(uint8_t temp)
{
	
	 if(gNothingReceiveTimer2 > 10)//超过10ms没有接收数据
	{
		UART2ReceiveRestart();
	}
	gNothingReceiveTimer2 = 0;

	CDP_CenVoice_ByteRx(temp);
	CDP_CenMX_ByteRx(temp);
	//---------------------------------------------------------
	if(gUART2RxDataCount == 0)
	{
		if(temp == 0x10)
		{
			gUART2RxBuffer[0] = temp;
			gUART2RxDataCount++;
			gUART2SCICheckout += temp;
		}else
		{
			UART2ReceiveRestart();
		}
	}
	else if(gUART2RxDataCount <= 4)
	{
		
		gUART2RxBuffer[gUART2RxDataCount] = temp;
		gUART2RxDataCount++;
		gUART2SCICheckout += temp;
	}
	else if(gUART2RxDataCount == 5)
	{
		if(gUART2SCICheckout == temp)
		{
			gUART2RxBuffer[gUART2RxDataCount] = temp;
			memcpy((Uchar *)&gRxUART2Data,(Uchar *)&gUART2RxBuffer,6);
			EvReceiveUART2Flag = 1;
		}
		UART2ReceiveRestart();
	}
	else
	{
		UART2ReceiveRestart();
	}	
}


void UART3_ByteRx(uint8_t temp)
{
	
	if(gNothingReceiveTimer3 > 10)//超过10ms没有接收数据
	{
		UART3ReceiveRestart();
	}
	gNothingReceiveTimer3= 0;
	
	if(gUART3RxDataStep == 0) //帧头
	{
		if(temp == 0x20 ||temp == 0x7E)
		{
			gUART3RxBuffer[gUART3RxDataCount] = temp;
			gUART3RxDataCount++;
			gUART3SCICheckout += temp;
			gUART3RxDataStep = 1;
		}else
		{
			UART3ReceiveRestart();
		}
	}
	else if(gUART3RxDataStep == 1) //命令
	{
		
		gUART3RxBuffer[gUART3RxDataCount] = temp;
		gUART3RxDataCount++;
		gUART3SCICheckout += temp;
		gUART3RxDataStep = 2;
	}
	else if(gUART3RxDataStep == 2) //长度
	{
		gUART3RxBuffer[gUART3RxDataCount] = temp;
		gUART3RxDataCount++;
		gUART3SCICheckout += temp;
		gUART3RxDataLength = 0;
		gUART3RxDataStep = 3;
		if(temp > 6)
		{
			UART3ReceiveRestart();
		}
	}
	else if(gUART3RxDataStep == 3) //数据
	{
		
		gUART3RxBuffer[gUART3RxDataCount] = temp;
		gUART3RxDataCount++;
		gUART3RxDataLength++;
		gUART3SCICheckout += temp;
		
		if(gUART3RxDataLength >= gUART3RxBuffer[2])
		{
			gUART3RxDataStep = 4;
		}
		
	}
	else if(gUART3RxDataStep == 4)
	{
		
		if(gUART3SCICheckout == temp)
		{
			gUART3RxBuffer[gUART3RxDataCount] = temp;
//			if((gBluetoothRxBuffer[1] != 0) ||(gBluetoothRxBuffer[2] != 0)||(gBluetoothRxBuffer[3] != 0))
			{
				memcpy((Uchar *)&gRxUART3Data,(Uchar *)&gUART3RxBuffer,3+1+gUART3RxBuffer[2]);
				EvReceiveUART3Flag = 1;
			}
		}
		UART3ReceiveRestart();
	}
	else
	{
		UART3ReceiveRestart();
	}	 

}

void UART4_ByteRx(uint8_t temp)
{

	 if(gNothingReceiveTimer4 > 10)//超过10ms没有接收数据
	 {
		UART4ReceiveRestart();
	 }
	 gNothingReceiveTimer4 = 0;
	
	if(gUART4RxDataCount == 0)
	{
		gUART4RxBuffer[0] = temp;
		gUART4SCICheckout += temp;
		gUART4RxDataCount++;
	}
	
	else if(gUART4RxDataCount == 1)
	{
		if(temp == (0xFF - gUART4RxBuffer[0]))
		{
			gUART4RxBuffer[1] = temp;
			gUART4SCICheckout += temp;
			gUART4RxDataCount++;
		}
		else
		{
			UART4ReceiveRestart();
		}
	}

	else if(gUART4RxDataCount == 2)
	{
		if(temp <= 16)
		{
			gUART4RxBuffer[2] = temp;
			gUART4SCICheckout += temp;
			gUART4RxDataCount++;
		}
		else
		{
			UART4ReceiveRestart();
		}
	}
	else if((gUART4RxDataCount >= 3) &&(gUART4RxDataCount <= (gUART4RxBuffer[2] + 4 - 1)))
	{
		if(gUART4RxDataCount == (gUART4RxBuffer[2] + 4 - 1))
		{
			if(temp == gUART4SCICheckout)
			{
				gUART4RxBuffer[gUART4RxDataCount] = temp;
				memcpy((Uchar *)&gRxUART4Data,(Uchar *)&gUART4RxBuffer,(gUART4RxBuffer[2] + 4));
				EvReceiveUART4Flag = 1;
			}
			UART4ReceiveRestart();
		}else
		{
			gUART4RxBuffer[gUART4RxDataCount] = temp;
			gUART4RxDataCount++;
			gUART4SCICheckout += temp;
		}
	}
	else
	{
		UART4ReceiveRestart();
	}	
	
}



#endif  //__ISR_H

/* End of "isr.h" */
