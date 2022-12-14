/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：ESF_Evt.c 
**
**    功能描述: 事件队列 与  事件内存块  的实现
**
**    项目名称：Easy SoftWare FrameWork (简单 软件框架)
**
**    平台信息：
**
**    作    者：Hzy
**
**    版    本：V1.0
**
**    其他说明: ---------------------------------------------------------------
**              事件队列机制：
**              主动方：触发事件，将事件相关信息投递到事件队列中。
**              被动方：不断查阅事件队列，看是否有相关的事件发生。
**
**              ---------------------------------------------------------------
**              关于事件队列机制使用的建议原则：
**              系统的功能一般可分为：
**              （1）、需要不断执行的功能。如 主 While 循环里的一些代码。
**              （2）、依赖时间片，定时执行的代码。
**              （3）、被动（随机）发生事件代码。 如按键，串口接收等。
**
**               对于（1）：不适合使用事件队列机制来不断查询是否发生事件。
**               对于（2）：根据情况可使用，也可不使用事件队列机制。
**               对于（3）：系统不能预估该类事件发生的时刻与次数，最适合使用事件队列机制。
**    修改记录: --------------------------------------------------------------
**              2015.08    
**              完成 V1.0 版本
**              --------------------------------------------------------------
**              2016.06 
**              升级到V1.1版本。主要是为了简化有关事件和内存分配释放的使用。
**              1、去掉事件内存池相关内容。 
**              2、修改 ESF_Evt_t结构体，增加变量AppendData[1]; 
**              3、修改 ESF_Cfg.h文件，使得配置功能更明了简便。
**
========================================================================================================================
========================================================================================================================
*/

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "ESF_Evt.h"



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
static ESF_EvtQuene_t  ESF_EvtQuene;


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : ESF_EvtQuene_Post                                                                                                         
* 功能描述 : 投递事件                                                                        
* 输入参数 : pEvt 指向要投递的事件                                                                                         
* 返回参数 : EFS_ERR_EVT_QUENE_FULL -- 队列满，无法投递
*            EFS_ERR_NONE           -- 投递成功                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t ESF_EvtQuene_Post(ESF_Evt_t *pEvt)
{
  ESF_EnterCritical();

  if(ESF_EvtQuene.used >= ESF_EVENT_QUENE_SIZE)
  {
    ESF_ExitCritical();
    
    ESF_MemBuf_Free(pEvt);            /*投递失败，释放事件所占用的内存空间*/
    
    return EFS_ERR_EVT_QUENE_FULL;
  }
  
  ESF_EvtQuene.FIFO[ESF_EvtQuene.in++] = pEvt;
  if(ESF_EvtQuene.in >= ESF_EVENT_QUENE_SIZE)
  {
    ESF_EvtQuene.in = 0;
  }
  ESF_EvtQuene.used++;

  ESF_ExitCritical();

  return EFS_ERR_NONE;
}

/*
************************************************************************************************************************
* 函数名称 : ESF_EvtQuene_Pend                                                                                                         
* 功能描述 : 查看是否有事件发生                                                                           
* 输入参数 : 无                                                                                      
* 返回参数 : 无事件发生则返回 NULL；
*            有事件发生则返回指向事件的指针。                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
ESF_Evt_t* ESF_EvtQuene_Pend(void)
{  
  uint8_t  Ret;

  ESF_EnterCritical();

  if(0 == ESF_EvtQuene.used)
  {
    ESF_ExitCritical();
    return NULL;
  }

  Ret = ESF_EvtQuene.out;
  ESF_EvtQuene.out++;
  if(ESF_EvtQuene.out >= ESF_EVENT_QUENE_SIZE)
  {
    ESF_EvtQuene.out = 0;
  }
  ESF_EvtQuene.used--;
  
  ESF_ExitCritical();

  return ESF_EvtQuene.FIFO[Ret];  
}

