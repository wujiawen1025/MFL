/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: SysMode_Packing.c 
**
**    功能描述:	系统模式 之  包装
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
#include "SysMode.h"


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
* 函数名称 : SysMode_Packing_Handle                                                                                                         
* 功能描述 : 系统模式 之 包装 处理                                                                                     
* 输入参数 : 无                                                                               
* 返回参数 : 无                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_Packing_Handle(void)
{
  /*发生模式切换操作-----------------------------------------------------*/
  if(pMChair->SysModeHis != pMChair->SysModeCur)      
  {
    pMChair->SysModeHis = pMChair->SysModeCur; 
  }

  /*设置包装角度与机芯位置-----------------------------------------------*/
  Spike_SetLegFlexAngle(PLEGFLEX_MIN);                /*伸缩推杆缩到最短*/
  Spike_SetULegFlexAngle(PULEGFLEX_MAX);              /*上小腿伸到最长*/
  Spike_SetAngle(PBACK_MIN, PFEET_MIN, PZERO_MIN);    /*靠背倒到最底，小腿收起来*/
  Core_SetXYZPosition(PXWIDE, PY30, PZBACK);          /*机芯下复位*/
  if((PFEET_MIN == Spike_GetFeetAngle()) &&
     (PBACK_MIN == Spike_GetBackAngle()) &&
     (PXWIDE    == Core_GetXPosition())  &&
     (PY28      == Core_GetYPosition())  && 
     (PZBACK    == Core_GetZPosition())  &&
     (PLEGFLEX_MIN == Spike_GetLegFlexAngle()) )
  {
    pMChair->CSFlag.Bit.VenderOpFinish = TRUE;      /*厂家操作完成*/
  }

  /*根据各个模式的不同，对键值处理相关变量赋值---------------------------*/
  pMChair->KeyValHandle.KeyLogicTab    = NULL;      /*按键逻辑表*/
  pMChair->KeyValHandle.KeyLogicTabNum = 0;         /*按键逻辑表 大小*/
  pMChair->KeyValHandle.pGetMatchID    = NULL;      /*函数指针，指向的函数作用：返回表格条目 中 的要搜索的数据 所在的索引*/
  pMChair->KeyValHandle.pAddOp         = NULL;      /*函数指针，指向的函数作用：键值执行前后的附加操作 */
}
