/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: main.c 
**
**    ��������:
**
**    ��    ˾���ɷ�������
**
**    ��Ŀ���ƣ�
**
**    ƽ̨��Ϣ��
**
**    ��    �ߣ�Hzy
**
**    ����˵��:
**
**    �޸ļ�¼:  --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/


/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "System.h"
#include "bsp.h"
#include "Init.h"
#include "SysRun.h"
/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/
#define  WDT_EN               (!SYSTEM_DEBUGING)         /*���Ź�ʹ�ܿ��ơ� 1��ʹ��   0����ʹ��*/

#define  DEBUG_INFO_EN        0                          /*������Ϣ���ơ�   1��ʹ��   0����ʹ��*/

#define  DEBUG_BSP_EN         0                         /*ֱ�ӵ������Կ��Ƶײ�������·�� 1��ʹ��   0����ʹ�� */



/*
========================================================================================================================
*�������������Ͷ��塿                              �������������Ͷ��塿                              �������������Ͷ��塿
========================================================================================================================
*/


/*
************************************************************************************************************************
* ���Ͷ��� :  ֱ�ӵ������Կ��Ƶײ�������·                                                                                                      
************************************************************************************************************************
*/
#if(DEBUG_BSP_EN)
typedef struct
{
	uint8_t BodyTestPowerSupplyIOSW;
	uint8_t 				ReservedIOTestF1Sw;
	uint8_t 				ReservedIOTestA1Sw;
	uint8_t 				ReservedIOTestA0Sw;
	uint8_t 				ReservedIOTestE3Sw;

	uint8_t         HEATSw;
	uint8_t         VIBSw;
	uint8_t         PumpSw;

	uint8_t         SDASw;
	uint8_t         SCLKSw;
	uint8_t         LATCHSw;

	uint8_t         FeetSpikeOnOff;
	uint8_t         FeetSpikeDirection;      /* FEETSPIKE_DIRECTION_UP  FEETSPIKE_DIRECTION_DOWN */
	uint16_t        FeetSpikePWM;
	uint8_t         FeetSpikePosition;

	uint8_t         BackSpikeOnOff;
	uint8_t         BackSpikeDirection;      /* BACKSPIKE_DIRECTION_UP  BACKSPIKE_DIRECTION_DOWN */
	uint16_t        BackSpikePWM;
	uint8_t         BackSpikePosition;

	uint8_t         XOnOff;
	uint8_t         XDirection;              /* XMOTOR_DIRECTION_RIGHT  XMOTOR_DIRECTION_LEFT */
	uint16_t        XPWM;
	uint8_t         XPosition;

	uint8_t         YOnOff;
	uint8_t         YDirection;              /* YMOTOR_DIRECTION_UP  YMOTOR_DIRECTION_DOWN */
	uint16_t        YPWM;
	uint8_t         YPosition;

	uint8_t         RollerOnOff;
	uint8_t         RollerDirection;              /* ZMOTOR_DIRECTION_BACK    ZMOTOR_DIRECTION_FRONT */
	uint16_t        RollerPWM;
	uint8_t         RollerPosition;

	uint8_t         TCSOnOff;
	uint8_t        	TCSDirection;
	uint16_t        TCSPWM;

	uint16_t        LED1PWM;
	uint16_t        LED2PWM;
	uint16_t        LED3PWM;

//    uint8_t         ZeroSpikeOnOff;
//    uint8_t         ZeroSpikeDirection;      /*  */
//    uint16_t        ZeroSpikePWM;
//    uint8_t         ZeroSpikePosition;

	uint8_t         ERPSw;

	union
	{
			uint8_t    All;
			struct
			{
				uint8_t  b0     :1;
				uint8_t  b1     :1;
				uint8_t  b2     :1;
				uint8_t  b3     :1;
				uint8_t  b4     :1;
				uint8_t  b5     :1;
				uint8_t  b6     :1;
				uint8_t  b7     :1;
			}Bit;
	}GasPart1;
	union
	{
			uint8_t    All;
			struct
			{
				uint8_t  b0     :1;
				uint8_t  b1     :1;
				uint8_t  b2     :1;
				uint8_t  b3     :1;
				uint8_t  b4     :1;
				uint8_t  b5     :1;
				uint8_t  b6     :1;
				uint8_t  b7     :1;
			}Bit;
	}GasPart2;

}DebugBsp_t;

#endif   /*���� "if(DEBUG_BSP_EN)" */
   

/*
========================================================================================================================
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
========================================================================================================================
*/
#if(DEBUG_BSP_EN)
DebugBsp_t DebugBsp;
#endif   /*���� "if(DEBUG_BSP_EN)" */

/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/


#if(DEBUG_BSP_EN)
/*
************************************************************************************************************************
* �������� : main                                                                                                         
* �������� : ֱ�ӵ������Կ��Ƶײ�������·��������                                                                                               
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : �� DEBUG_BSP_EN ��Ϊ 0 ʱ��Ч��                                                                                                         
************************************************************************************************************************
*/ 
int main(void)
{
  System_Init();                                           /* ϵͳ��ʼ�� */ 

	DebugBsp.BodyTestPowerSupplyIOSW = 0;
	DebugBsp.XOnOff             = 0;
	DebugBsp.XDirection         = 0;             
	DebugBsp.XPWM               = 521;

	DebugBsp.TCSOnOff           = 0;
	DebugBsp.TCSDirection       = 0;
	DebugBsp.TCSPWM             = 521;

	DebugBsp.YOnOff             = 0;
	DebugBsp.YDirection         = 0;             
	DebugBsp.YPWM               = 521;

	DebugBsp.RollerOnOff        = 0;
	DebugBsp.RollerDirection    = 0;             
	DebugBsp.RollerPWM          = 521;

	DebugBsp.LED1PWM          	= 521;
	DebugBsp.LED2PWM          	= 521;
	DebugBsp.LED3PWM          	= 521;
		
	DebugBsp.BackSpikeOnOff     = 0;
	DebugBsp.BackSpikeDirection = 0;     
	DebugBsp.BackSpikePWM       = 0;

	DebugBsp.FeetSpikeOnOff     = 0;
	DebugBsp.FeetSpikeDirection = 0;     
	DebugBsp.FeetSpikePWM       = 0;

//	DebugBsp.ZeroSpikeOnOff     = 0;
//	DebugBsp.ZeroSpikeDirection = 0;     
//	DebugBsp.ZeroSpikePWM       = 0;
	
	DebugBsp.PumpSw             = 0;
	DebugBsp.ERPSw              = 0;
	DebugBsp.SDASw              = 0;
	DebugBsp.SCLKSw             = 0;
	DebugBsp.LATCHSw            = 0;
	DebugBsp.HEATSw 						= 0;
	DebugBsp.VIBSw 							= 0;
	DebugBsp.GasPart1.All = 0;
	DebugBsp.GasPart2.All = 0;
 
  #if(WDT_EN)
    BSP_WatchDog_Init();
  #endif
  
  while(1)
  {
    #if(WDT_EN)
      BSP_WatchDog_Feed();                                /* ι�� */
    #endif
		
		ADOverCTestProcess();

//		if(DebugBsp.BodyTestPowerSupplyIOSW)
//		{
//			BodyTestPowerSupply_IO_ON;
//		}
//		else
//		{
//			BodyTestPowerSupply_IO_OFF;
//		} 

	//ERP�̵����������//////////	
		if(DebugBsp.ERPSw)
		{
			ERPPower_IO_ON;
			ERPPower_IO1_ON;
		}
		else
		{
			ERPPower_IO_OFF;
			ERPPower_IO1_OFF;
		} 
		
	//������//////////	
		KneadMotorSD_IO_ON; //�ĳ���ʽоƬ������·��SDʹ�ܽ�
		if(KneadRunWayFlag)
		{
		    BSP_PWMTmr_SetKneadDuty(DebugBsp.XPWM);       	/* ���� */
		    BSP_PWMTmr_SetKneadDuty2(KNEAD_OFF_PWM);       	/* ���� */
		}
		else
		{
		    BSP_PWMTmr_SetKneadDuty(KNEAD_OFF_PWM);       	/* ���� */
		    BSP_PWMTmr_SetKneadDuty2(DebugBsp.XPWM);       	/* ���� */
		}
		
		if(DebugBsp.XDirection)
		{
			KneadWay_IO_CLOCKWISE;
		}
		else
		{
			KneadWay_IO_ANTICLOCKWISE;
		} 
	
	//�û����//////////	
		BSP_PWMTmr_SetTapDuty(DebugBsp.TCSPWM);           	/* �û����������ֵΪ521��ʱ��0% �����Ϊ0��ʱ�� 100% */

	//���ߵ��//////////	
//		if(DebugBsp.YOnOff)
//		{
//			RollMotor_IO_ON;
//		}
//		else
//		{
//			RollMotor_IO_OFF;
//		} 
		
		BSP_PWMTmr_SetRollDuty(DebugBsp.YPWM);           	/* �û����������ֵΪ521��ʱ��0% �����Ϊ0��ʱ�� 100% */

		if(DebugBsp.YDirection)
		{
			RollWay_IO_UP;
		}
		else
		{
			RollWay_IO_DOWN;
		} 
		
	//�Ź����//////////	
		BSP_PWMTmr_SetFeetRollerDuty(DebugBsp.RollerPWM);           	/* �û����������ֵΪ521��ʱ��0% �����Ϊ0��ʱ�� 100% */

		if(DebugBsp.RollerDirection)
		{
			FeetRollerWay_IO_FRONT;
		}
		else
		{
			FeetRollerWay_IO_BACK;
		} 

		//��ɫ��������//////////	
		BSP_PWMTmr_SetLed1PWM(DebugBsp.LED1PWM);           	/* LED1���������ֵΪ521��ʱ��0% �����Ϊ0��ʱ�� 100% */
		BSP_PWMTmr_SetLed2PWM(DebugBsp.LED2PWM);           	/* LED1���������ֵΪ521��ʱ��0% �����Ϊ0��ʱ�� 100% */
		BSP_PWMTmr_SetLed3PWM(DebugBsp.LED3PWM);           	/* LED1���������ֵΪ521��ʱ��0% �����Ϊ0��ʱ�� 100% */
		
		
	//�����Ƹ�//////////	
		if(DebugBsp.BackSpikeOnOff)
		{
			BackSpikeMotor_IO_ON;
		}
		else
		{
			BackSpikeMotor_IO_OFF;
		} 

		if(DebugBsp.BackSpikeDirection)
		{
			BackSpikeWay_IO_UP;
		}
		else
		{
			BackSpikeWay_IO_DOWN;			
		}
		
		//С���Ƹ�//////////	
		if(DebugBsp.FeetSpikeOnOff)
		{
			FeetSpikeMotor_IO_ON;
		}
		else
		{
			FeetSpikeMotor_IO_OFF;
		} 

		if(DebugBsp.FeetSpikeDirection)
		{
			FeetSpikeWay_IO_UP;
		}
		else
		{
			FeetSpikeWay_IO_DOWN;
		}

		//����//////////	
		if(DebugBsp.HEATSw)
		{
			BackHeat_IO1_ON;
		}
		else
		{
			BackHeat_IO1_OFF;
		}

		//��//////////	
 		if(DebugBsp.VIBSw)
		{
			BackHeat_IO2_ON;
		}
		else
		{
			BackHeat_IO2_OFF;
		}
       

		//������������//////////	
		if(DebugBsp.PumpSw)
		{
			GasPump_IO_ON;
		}
		else
		{
			GasPump_IO_OFF;
		}
		

		//8804 SDA��//////////		
//		if(DebugBsp.SDASw)
//		{
//			Gas_8804SDATIN_IO_ON;
//		}
//		else
//		{
//			Gas_8804SDATIN_IO_OFF;
//		} 

//		if(DebugBsp.SCLKSw)
//		{
//			Gas_8804SCLK_IO_ON;
//		}
//		else
//		{
//			Gas_8804SCLK_IO_OFF;
//		}

//		if(DebugBsp.LATCHSw)
//		{
//			Gas_8804LATCH_IO_ON;
//		}
//		else
//		{
//			Gas_8804LATCH_IO_OFF;
//		} 

		Serial8804Out(DebugBsp.GasPart1.All);		

	}
}


#else

/*
************************************************************************************************************************
* �������� : main                                                                                                         
* �������� : Ӧ�ó���ʵ�ʵ�������                                                                                               
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
int main(void)
{
   System_Init();                                           /* ϵͳ��ʼ�� */ 
	Init_Ram();
	Init_System();
	Init_Serial();
  
  #if(WDT_EN)
    BSP_WatchDog_Init();
  #endif

//  BSP_IO_SetOutput_4959ResetSw(ON);//4959��ERP�ϵ�󣬸�λ�Ÿ�λ��ʱ������

// 	HiLinkAddInit();
// SystemStartReportMassageChairInfo_Wifi();
  while(1)
  {
    #if(WDT_EN)
      BSP_WatchDog_Feed();                                /* ι�� */
    #endif
    
    //System_Handle();
		SystemRuning();         //����ϵͳ������	

  }
}

#endif   /*���� "if(DEBUG_BSP_EN)" */
