/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：ESF_Cfg.h 
**
**    功能描述: 对 ESF 进行配置
**
**    项目名称：Easy SoftWare FrameWork (简单 软件框架)
**
**    平台信息：
**
**    作    者：Hzy
**
**    版    本：V1.0
**
**    其他说明:
**
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
#ifndef ESF_CFG_H
#define ESF_CFG_H


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/


/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/

/*==================================================================================================
**
**            配置：处理器位宽定义 
**
===================================================================================================*/
//#define  ESF_CFG_CPU_BIT_WIDTH                8                      /*8位*/
//#define  ESF_CFG_CPU_BIT_WIDTH                16                     /*16位*/
#define  ESF_CFG_CPU_BIT_WIDTH                32                     /*32位*/



/*==================================================================================================
**
**            配置：ESF_Mem 内存块
**        
===================================================================================================*/
#define  ESF_CFG_MEM_BOLCK_NUM                4                     /*内存块数量，注：最小值为2*/
#define  ESF_CFG_MEM_BOLCK_BYTE_SIZE          (512+512)             /*内存块大小，单位字节。*/ 



/*==================================================================================================
**
**            配置：ESF_Evt 
**
**  注：请在 "ESF_Evt.h" 文件里的枚举
**  typedef enum
**  {
**  }ESF_EvtType_t;
**  中添加事件的类型 。
**  根据需要添加 事件参数类型的定义，并补充完善 ESF_Evt_t 结构。
**
===================================================================================================*/
#define  ESF_CFG_EVENT_QUENE_SIZE             4                      /*队列空间，注：最小值为2*/


#endif

