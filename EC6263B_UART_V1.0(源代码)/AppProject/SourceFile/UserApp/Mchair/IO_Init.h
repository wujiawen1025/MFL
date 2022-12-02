/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    模块名称(Filename):       IO_Init.h  
    项目名称(Projectname):       
    版本号(Version):	      
    创建日期(Date):           2008-5-15        
    作者(Author):             FS
    功能描述(Description):    IO宏定义
    其他说明(Others):         
****************************************************************/

#ifndef         _IO_Init_H
#define		_IO_Init_H
//#include <stdint.h>

#include "Config.h"
#define    	KnobControlRead1_IO()				(GPIO_Read(GPIOA) &GPIO_PTC3_MASK)		
#define    	KnobControlRead2_IO()				(GPIO_Read(GPIOA) &GPIO_PTC2_MASK)		
#define    	KnobControlRead3_IO()				(GPIO_Read(GPIOA) &GPIO_PTC1_MASK)		
#define    	KnobControlRead4_IO()				(GPIO_Read(GPIOA) &GPIO_PTC0_MASK)
#define    	KnobControlRead5_IO()				(GPIO_Read(GPIOA) &GPIO_PTB3_MASK)		
#define    	KnobControlRead6_IO()				(GPIO_Read(GPIOA) &GPIO_PTB2_MASK)		
#define    	KnobControlRead7_IO()				(GPIO_Read(GPIOA) &GPIO_PTA7_MASK)		
#define    	KnobControlRead8_IO()				(GPIO_Read(GPIOA) &GPIO_PTA6_MASK)
#define    	KnobControlRead9_IO()				(GPIO_Read(GPIOA) &GPIO_PTD3_MASK)		
#define    	KnobControlRead10_IO()				(GPIO_Read(GPIOA) &GPIO_PTD2_MASK)		
#define    	KnobControlRead11_IO()				(GPIO_Read(GPIOA) &GPIO_PTA3_MASK)
#define    	KnobControlBSG_IO()					(GPIO_Read(GPIOA) &GPIO_PTA1_MASK)		
#define    	KnobControlASG_IO()					(GPIO_Read(GPIOA) &GPIO_PTA2_MASK)	

#define	 	LED1_ON_IO() 						GPIOA->PCOR |= GPIO_PTD1_MASK	//J17-J23
#define	 	LED1_OFF_IO() 						GPIOA->PSOR |= GPIO_PTD1_MASK	
#define	 	LED2_ON_IO() 						GPIOA->PCOR |= GPIO_PTD0_MASK	
#define	 	LED2_OFF_IO() 						GPIOA->PSOR |= GPIO_PTD0_MASK
#define	 	LED3_ON_IO() 						GPIOA->PCOR |= GPIO_PTB5_MASK	
#define	 	LED3_OFF_IO() 						GPIOA->PSOR |= GPIO_PTB5_MASK	
#define	 	LEDP_ON_IO() 						GPIOA->PCOR |= GPIO_PTC5_MASK	
#define	 	LEDP_OFF_IO() 						GPIOA->PSOR |= GPIO_PTC5_MASK		


#define		AcheLED_IO_ON						GPIOA->PCOR |= GPIO_PTA3_MASK		//输出低
#define		AcheLED_IO_OFF					GPIOA->PSOR |= GPIO_PTA3_MASK
#endif
