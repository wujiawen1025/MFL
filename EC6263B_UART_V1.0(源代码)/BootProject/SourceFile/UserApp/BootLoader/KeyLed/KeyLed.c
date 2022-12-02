#include "KeyLed.h"
#include "bsp.h"

unsigned short int gCombinationKeyTime;
int  TxResflag = 0;
extern uint8_t LED_flag;

void	 Delay5us()
{
	unsigned char  temp;
	
	for(temp=20; temp; temp--)
	{
		;//asm nop;
	}
}

void KeyScanVal(void)      //50ms��ʱɨ��
{   	
  if(!KeyPowerTest_IO)
	{ 
	    Key5Write_IO_OFF;
		//Key3Test_IO_OFF;
        Delay5us();
  	/****************ɨ��Wifi��**********************************/
		if(!Key3Test_IO)
		{
			if(gCombinationKeyTime < 60)
				gCombinationKeyTime++;	//50ms����һ��
			if(gCombinationKeyTime >= 40 && gCombinationKeyTime != 200)	  // 2s
			{
				gCombinationKeyTime = 200;//ִֻ��һ��
				TxResflag =1;//	  ���͸�λָ��
			}		
		}
  }
	else 
	{
		gCombinationKeyTime = 0;
	}	
	Key5Write_IO_ON;
}

void LedHandle(void)
{	
	static  unsigned char i=0;
	i++;
	if(i>=30)
	{
	  i=0;
	}
	
	Key4Init_IO_OUTPUT;
	Key5Init_IO_OUTPUT;
	Key6Init_IO_OUTPUT; 
	Key4Write_IO_ON;
	Key5Write_IO_ON;
	Key6Write_IO_ON;
	
	Key1Init_IO_OUTPUT;
	Key2Init_IO_OUTPUT;
	Key3Init_IO_OUTPUT;
	Key1Write_IO_OFF;
	Key2Write_IO_OFF;
	Key3Write_IO_OFF;	
	
	if(LED_flag ==1)
	{
			if(i<=10)
			{
        	Key5Write_IO_ON;
           	Key6Write_IO_OFF;            
        	Key4Write_IO_OFF;

            Key1Write_IO_ON;
        	Key2Write_IO_ON;
        	Key3Write_IO_OFF;
				
			}
			else if( i <= 20)
			{
            Key5Write_IO_OFF;
           	Key6Write_IO_ON;            
        	Key4Write_IO_OFF;

            Key1Write_IO_ON;
        	Key2Write_IO_OFF;
        	Key3Write_IO_ON;

			}
			else if( i <= 30)
			{
        	Key5Write_IO_OFF;
           	Key6Write_IO_OFF;            
        	Key4Write_IO_ON;

            Key1Write_IO_ON;
        	Key2Write_IO_OFF;
        	Key3Write_IO_ON;		
			}
	}
 
}

