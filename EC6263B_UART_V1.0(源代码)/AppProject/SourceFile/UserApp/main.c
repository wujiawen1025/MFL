/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: main.c 
**
**    功能描述:
**
**    公    司：蒙发利电子
**
**    项目名称：
**
**    平台信息：
**
**    作    者：Hzy
**
**    其他说明:
**
**    修改记录:  --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "System.h"
#include "bsp.h"
#include "Init.h"
#include "SysRun.h"
/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/
#define  WDT_EN               (!SYSTEM_DEBUGING)         /*看门狗使能控制。 1：使能   0：不使能*/

#define  DEBUG_INFO_EN        0                          /*调试信息控制。   1：使能   0：不使能*/

#define  DEBUG_BSP_EN         0                         /*直接单独调试控制底层驱动电路。 1：使能   0：不使能 */



/*
========================================================================================================================
*【本地数据类型定义】                              【本地数据类型定义】                              【本地数据类型定义】
========================================================================================================================
*/


/*
************************************************************************************************************************
* 类型定义 :  直接单独调试控制底层驱动电路                                                                                                      
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

#endif   /*结束 "if(DEBUG_BSP_EN)" */
   

/*
========================================================================================================================
*【变量定义 & 各种声明】                          【变量定义 & 各种声明】                          【变量定义 & 各种声明】    
========================================================================================================================
*/
#if(DEBUG_BSP_EN)
DebugBsp_t DebugBsp;
#endif   /*结束 "if(DEBUG_BSP_EN)" */

/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/


#if(DEBUG_BSP_EN)
/*
************************************************************************************************************************
* 函数名称 : main                                                                                                         
* 功能描述 : 直接单独调试控制底层驱动电路的主函数                                                                                               
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 宏 DEBUG_BSP_EN 不为 0 时有效。                                                                                                         
************************************************************************************************************************
*/ 
int main(void)
{
  System_Init();                                           /* 系统初始化 */ 

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
      BSP_WatchDog_Feed();                                /* 喂狗 */
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

	//ERP继电器驱动输出//////////	
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
		
	//揉捏电机//////////	
		KneadMotorSD_IO_ON; //改成桥式芯片驱动电路，SD使能脚
		if(KneadRunWayFlag)
		{
		    BSP_PWMTmr_SetKneadDuty(DebugBsp.XPWM);       	/* 揉捏 */
		    BSP_PWMTmr_SetKneadDuty2(KNEAD_OFF_PWM);       	/* 揉捏 */
		}
		else
		{
		    BSP_PWMTmr_SetKneadDuty(KNEAD_OFF_PWM);       	/* 揉捏 */
		    BSP_PWMTmr_SetKneadDuty2(DebugBsp.XPWM);       	/* 揉捏 */
		}
		
		if(DebugBsp.XDirection)
		{
			KneadWay_IO_CLOCKWISE;
		}
		else
		{
			KneadWay_IO_ANTICLOCKWISE;
		} 
	
	//敲击电机//////////	
		BSP_PWMTmr_SetTapDuty(DebugBsp.TCSPWM);           	/* 敲击，输入参数值为521的时候0% ，输出为0的时候 100% */

	//行走电机//////////	
//		if(DebugBsp.YOnOff)
//		{
//			RollMotor_IO_ON;
//		}
//		else
//		{
//			RollMotor_IO_OFF;
//		} 
		
		BSP_PWMTmr_SetRollDuty(DebugBsp.YPWM);           	/* 敲击，输入参数值为521的时候0% ，输出为0的时候 100% */

		if(DebugBsp.YDirection)
		{
			RollWay_IO_UP;
		}
		else
		{
			RollWay_IO_DOWN;
		} 
		
	//脚滚电机//////////	
		BSP_PWMTmr_SetFeetRollerDuty(DebugBsp.RollerPWM);           	/* 敲击，输入参数值为521的时候0% ，输出为0的时候 100% */

		if(DebugBsp.RollerDirection)
		{
			FeetRollerWay_IO_FRONT;
		}
		else
		{
			FeetRollerWay_IO_BACK;
		} 

		//三色灯驱动口//////////	
		BSP_PWMTmr_SetLed1PWM(DebugBsp.LED1PWM);           	/* LED1，输入参数值为521的时候0% ，输出为0的时候 100% */
		BSP_PWMTmr_SetLed2PWM(DebugBsp.LED2PWM);           	/* LED1，输入参数值为521的时候0% ，输出为0的时候 100% */
		BSP_PWMTmr_SetLed3PWM(DebugBsp.LED3PWM);           	/* LED1，输入参数值为521的时候0% ，输出为0的时候 100% */
		
		
	//靠背推杆//////////	
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
		
		//小腿推杆//////////	
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

		//加热//////////	
		if(DebugBsp.HEATSw)
		{
			BackHeat_IO1_ON;
		}
		else
		{
			BackHeat_IO1_OFF;
		}

		//振动//////////	
 		if(DebugBsp.VIBSw)
		{
			BackHeat_IO2_ON;
		}
		else
		{
			BackHeat_IO2_OFF;
		}
       

		//气泵气阀驱动//////////	
		if(DebugBsp.PumpSw)
		{
			GasPump_IO_ON;
		}
		else
		{
			GasPump_IO_OFF;
		}
		

		//8804 SDA口//////////		
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
* 函数名称 : main                                                                                                         
* 功能描述 : 应用程序实际的主函数                                                                                               
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
int main(void)
{
   System_Init();                                           /* 系统初始化 */ 
	Init_Ram();
	Init_System();
	Init_Serial();
  
  #if(WDT_EN)
    BSP_WatchDog_Init();
  #endif

//  BSP_IO_SetOutput_4959ResetSw(ON);//4959在ERP上电后，复位脚复位延时后启动

// 	HiLinkAddInit();
// SystemStartReportMassageChairInfo_Wifi();
  while(1)
  {
    #if(WDT_EN)
      BSP_WatchDog_Feed();                                /* 喂狗 */
    #endif
    
    //System_Handle();
		SystemRuning();         //整个系统的运行	

  }
}

#endif   /*结束 "if(DEBUG_BSP_EN)" */
