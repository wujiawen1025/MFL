/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: bsp_pwmtmr.h 
**
**    功能描述:	pwm输出定时器
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
**    修改记录:  
**
========================================================================================================================
========================================================================================================================
*/
#ifndef  _BSP_PWMTMR_H_
#define  _BSP_PWMTMR_H_


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp.h"


/*
========================================================================================================================
*【对外宏定义】                                       【对外宏定义】                                       【对外宏定义】
========================================================================================================================
*/



/*
========================================================================================================================
*【对外数据类型定义】                              【对外数据类型定义】                              【对外数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :                                                                                                          
************************************************************************************************************************
*/
/*
************************************************************************************************************************
* 类型定义 :                                                                                                     
************************************************************************************************************************
*/



/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
void BSP_PWMTmr_Init(void);

void BSP_PWMTmr_SetOutput_LED(uint8_t Duty);


#endif                        /* End of module include.  */
