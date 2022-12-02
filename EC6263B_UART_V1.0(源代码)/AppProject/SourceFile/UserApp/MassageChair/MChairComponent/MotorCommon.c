/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称:                                                                                                      
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
#include "MotorCommon.h"

/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/


/*
========================================================================================================================
*【本地数据类型定义】                              【本地数据类型定义】                              【本地数据类型定义】
========================================================================================================================
*/


/*
========================================================================================================================
*【变量定义 & 各种声明】                          【变量定义 & 各种声明】                          【变量定义 & 各种声明】    
========================================================================================================================
*/


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : MotorCountUpdata                                                                                                         
* 功能描述 : 马达计数更新                                                                                         
* 输入参数 : pCountCur -- 计数变量
*            IncDec    -- 增减标志
*            CountMax  -- 计数最大值   
*            CountMin  -- 计数最小值   
* 返回参数 : 无
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void MotorCountUpdata(uint16_t *pCountCur,  uint8_t IncDec, uint16_t CountMax, uint16_t CountMin)
{
  if(POSITION_COUNT_INC == IncDec)          /*计数增加*/
  {
    if(*pCountCur < CountMax)
    {
      (*pCountCur)++;
    }
  }
  else //if(POSITION_COUNT_DEC == IncDec)   /*计数减少*/
  {
    if(*pCountCur > CountMin)
    {
      (*pCountCur)--;
    }
    else    
    {
      *pCountCur = 0;
    }
  }
}

/*
************************************************************************************************************************
* 函数名称 : MotorCountUpdata                                                                                                         
* 功能描述 : 马达计数更新                                                                                         
* 输入参数 : BSPIOCode     -- BSP采集的IO编码
*            pStableIOCode -- 稳定的编码
*            pStableStat   -- 稳定状态的统计变量
* 返回参数 : 稳定状态的统计次数
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t PositionIOStableStat(uint8_t BSPIOCode,  uint8_t *pStableIOCode, uint8_t *pStableStat)
{
  if(*pStableIOCode != BSPIOCode)
  {
    *pStableStat   = 0;            /*发生变化则表示不稳定*/
    *pStableIOCode = BSPIOCode;    /*读码盘*/
  }
  else
  {
    if(*pStableStat < 255)   
    {
      (*pStableStat)++;                                             /*没发生变化，则稳定统计增加*/ 
    }
  }
  return  (*pStableStat);
}

