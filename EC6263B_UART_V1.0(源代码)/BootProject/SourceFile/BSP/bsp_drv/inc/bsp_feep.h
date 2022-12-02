/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: bsp_feep.h                                                                                                        
**
**    功能描述:	使用Flash模拟EEPROM                                                                                                        
**
**    公    司：                                                                                                        
**
**    项目名称：                                                                                                        
**
**    平台信息：                                                                                                        
**
**    作    者：Hzy                                                                                                     
**
**    其他说明:	                                                                                                        
**
**    修改记录: --------------------------------------------------------------
**              2016.08    
**              完成 V1.0 版本
**
========================================================================================================================
========================================================================================================================
*/
#ifndef  _BSP_FEEP_H_
#define  _BSP_FEEP_H_


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
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
uint16_t BSP_FEEP_Init(void);
uint16_t BSP_FEEP_Write(void *pDada, uint16_t Len);
uint8_t  BSP_FEEP_Read(void *pDada, uint16_t Len);


#endif                        /* End of module include.  */
