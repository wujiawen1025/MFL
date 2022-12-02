/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: CDP.h                                                                                                         
**
**    功能描述: 通信数据包。
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
#ifndef  _CDP_H
#define  _CDP_H


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "GlobalCfg.h"
#include "bsp.h"
#include "ESF.h"          
#include "CDP_Xxx_Ctrl.h"
#include "SideBoard_806.h"

/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
#define  CDP_FRAME_MIN_LEN                      9                    /*最小帧长度*/ 
#define  CDP_PDU_EXCEPT_DU_LEN                  6                    /*协议数据单元的长度(除掉数据单元)*/


#define  CDP_FRAME_BOUNDARY                     0x7E                 /*帧边界*/            
#define  CDP_FRAME_HEADER                       CDP_FRAME_BOUNDARY   /*帧头*/
#define  CDP_FRAME_FOOTER                       CDP_FRAME_BOUNDARY   /*帧尾*/            
#define  CDP_FRAME_ESC                          0x5E                 /*帧转义*/   


#define  CDP_FRAME_OFFSET_HEADER                0                    /*帧头偏移*/
#define  CDP_FRAME_OFFSET_PDU                   1                    /*协议数据单元偏移，即帧头开始后的第一个数据*/

#define  CDP_PDU_OFFSET_DES                     0                    /*协议数据单元内的 目的地址 偏移*/
#define  CDP_PDU_OFFSET_SRC                     1                    /*协议数据单元内的 源地址   偏移*/
#define  CDP_PDU_OFFSET_VER                     2                    /*协议数据单元内的 版本号   偏移*/
#define  CDP_PDU_OFFSET_CMD                     4                    /*协议数据单元内的 命令码   偏移*/
#define  CDP_PDU_OFFSET_ACK                     5                    /*协议数据单元内的 应答     偏移*/
#define  CDP_PDU_OFFSET_DU                      6                    /*协议数据单元内的 数据单元 偏移*/

#define  CDP_DU_OFFSET_LEN                      0                    /*数据单元内的 长度 偏移*/            
#define  CDP_DU_OFFSET_ID                       1                    /*数据单元内的 ID   偏移*/  
#define  CDP_DU_OFFSET_DATA                     2                    /*数据单元内的 数据 偏移*/  


#define  CDP_ADDR_CEN                           0x01                 /*地址：中心板*/
#define  CDP_ADDR_CTR                           0x10                 /*地址：按键手控器 / 类平板 / 手机APP */
#define  CDP_ADDR_CTR_SIDE                      0x11                 /*地址：侧板按键 */
#define  CDP_ADDR_CORE                          0x20                 /*地址：机芯板*/
#define  CDP_ADDR_CORE_X                        0x21                 /*地址：机芯X马达控制板*/
#define  CDP_ADDR_CORE_Y                        0x22                 /*地址：机芯Y马达控制板*/
#define  CDP_ADDR_CORE_Z                        0x23                 /*地址：机芯Z马达控制板*/
#define  CDP_ADDR_CORE_TCS                      0x24                 /*地址：机芯敲击马达控制板*/
#define  CDP_ADDR_SPIKE                         0x30                 /*地址：推杆控制板*/
#define  CDP_ADDR_SPIKE_BACK                    0x31                 /*地址：靠背推杆控制板*/
#define  CDP_ADDR_SPIKE_FEET                    0x32                 /*地址：小腿推杆控制板*/
#define  CDP_ADDR_SPIKE_ZERO                    0x33                 /*地址：零重力推杆控制板*/
#define  CDP_ADDR_SPIKE_FEETFLEX                0x34                 /*地址：小腿伸缩控制板*/
#define  CDP_ADDR_HEAT                          0x40                 /*地址：加热控制板*/
#define  CDP_ADDR_HEAT_HEAD                     0x41                 /*地址：头部加热控制板*/
#define  CDP_ADDR_HEAT_LUMBARBACK               0x42                 /*地址：腰背加热控制板*/
#define  CDP_ADDR_HEAT_SEAT                     0x43                 /*地址：坐部加热控制板*/
#define  CDP_ADDR_HEAT_CALVES                   0x44                 /*地址：腿部加热控制板*/
#define  CDP_ADDR_HEAT_FEET                     0x45                 /*地址：脚部加热控制板*/
#define  CDP_ADDR_HEAT_ARMS                     0x46                 /*地址：手部加热控制板*/
#define  CDP_ADDR_VIB                           0x48                 /*地址：振动控制板*/
#define  CDP_ADDR_VIB_HEAD                      0x49                 /*地址：头部振动控制板*/
#define  CDP_ADDR_VIB_LUMBARBACK                0x4A                 /*地址：腰背振动控制板*/
#define  CDP_ADDR_VIB_SEAT                      0x4B                 /*地址：坐部振动控制板*/
#define  CDP_ADDR_VIB_CALVES                    0x4C                 /*地址：腿部振动控制板*/
#define  CDP_ADDR_VIB_FEET                      0x4D                 /*地址：脚部振动控制板*/
#define  CDP_ADDR_VIB_ARMS                      0x4E                 /*地址：手部振动控制板*/
#define  CDP_ADDR_ROLLER                        0x50                 /*地址：滚轮控制板*/
#define  CDP_ADDR_ROLLER_FEET                   0x51                 /*地址：脚滚控制板*/
#define  CDP_ADDR_ROLLER_CALVES                 0x52                 /*地址：小腿滚控制板*/
#define  CDP_ADDR_LED                           0x58                 /*地址：灯光控制板*/
/*注意：一个物理模块中可能包含多个逻辑模块。比如小腿模块可能包含：小腿伸缩、小腿充气、脚滚等。
 *      因为当前版本协议数据ID标识的分配中，每个ID都代表不同的含义，且都能明确知道归属于于哪个逻辑模块。
 *      因此可只使用一个地址作为物理模块的地址即可，这样也有利于缩减数据包的大小。
 *      当然，如果以后的协议版本中，数据ID标识不能明确区分出数据归属于哪个模块，则应该使用多个逻辑地址以区分数据归属。*/
#define  CDP_ADDR_SELF                          CDP_ADDR_CEN         /*地址：自身*/


#define  CDP_CMD_UPREPORT                       0x01                 /*命令：从机主动上报 */
#define  CDP_CMD_QRY                            0x02                 /*命令：主机查询从机 */   
#define  CDP_CMD_SET_NACK                       0x03                 /*命令：主机设置从机，从机无需应答 */    
#define  CDP_CMD_SET_ACK                        0x04                 /*命令：主机设置从机，从机需应答 */   
#define  CDP_CMD_IAP                            0xF0                 /*命令：IAP升级操作 */   


#define  CDP_ACK_SUCCESS                        0x00                 /*应答：执行成功 */
#define  CDP_ACK_FAIL                           0x01                 /*应答：执行失败 */
#define  CDP_ACK_INVALID_CMD                    0x02                 /*应答：不支持的命令码 */
#define  CDP_ACK_INVALID_LEN                    0x03                 /*应答：数据长度错 */
#define  CDP_ACK_INVALID_ID                     0x04                 /*应答：数据中有不支持的ID识别码 */
#define  CDP_ACK_RE_COMFIRM                     0x10                 /*应答：命令需要重新确认提示 */
#define  CDP_ACK_SEND                           0xFF                 /*应答：数据的主动发起方，填0xFF */


#define  CDP_DAP_CTRL                           0x01                 /*数据访问物理端口：手控器*/                                       
#define  CDP_DAP_CEN                            0x02                 /*数据访问物理端口：机芯板*/                                                  
#define  CDP_DAP_CORE                           0x03                 /*数据访问物理端口：机芯板*/                                                  
#define  CDP_DAP_OTHER                          0xFF                 /*数据访问物理端口：其他*/                                                  

#define  CDP_TYPE_COMMON                        0x00                                               


#define  CDP_DU_HANDLE_INVALID_ID               0xFE                 /*数据单元处理 不支持的ID*/                                       
#define  CDP_DU_HANDLE_ERR                      0xFF                 /*数据单元处理错误*/                                       

/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  通信数据包 数据对象格式                                                                       
************************************************************************************************************************
*/
typedef struct 
{
  uint8_t     Len;     
  uint8_t     ID;  
  uint8_t     *pData;  

}CDPDataObjFormat_t;

/*
************************************************************************************************************************
* 类型定义 :  通信数据包 数据对象管理表项                                                                        
************************************************************************************************************************
*/
typedef	struct
{
  uint8_t    ID;                   /*数据的ID识别码*/
  uint8_t    AdditonOp;            /*附加操作*/
  uint8_t    (*pDataHandle)(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);    /*数据处理函数*/

}CDPDataObjManageTabItem_t;


/*
************************************************************************************************************************
* 类型定义 :  通信数据包控制与状态标识                                                                                    
************************************************************************************************************************
*/
typedef  union 
{
  struct
  {
    uint8_t        test           :1;   

  }Bit;

  uint8_t All;
}CDPCSFlag_t;  /*Control State Flag  控制与状态标识*/

/*
************************************************************************************************************************
* 类型定义 :  通信数据包 相关操作数据结构                                                                            
************************************************************************************************************************
*/
typedef  uint8_t  (*pDataObjRecHandleCB_t)(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t Cmd);  /*数据处理回调函数*/


/*
************************************************************************************************************************
* 类型定义 :  通信数据包 相关操作数据结构                                                                            
************************************************************************************************************************
*/
typedef struct
{
  CDPCSFlag_t           CSFlag; 

  /*通信数据包部件 主要为调试用，实际编码应尽量使用各部件的接口函数-------*/
  CDP_XxxCtrl_t        *pXxxCtrl;
  
}CDP_t;


/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
uint8_t CDP_PDURxHandle(ESF_Evt_t *pEvt);
uint8_t CDP_PDUTxHandle(ESF_Evt_t *pEvt);
void CDP_PDUPackTx(uint8_t DesAddr, uint8_t Cmd, uint8_t *DUBuf[], uint8_t DUBufISum);
void CDP_Handle(void);
CDP_t* CDP_Init(void);
void GOTO_APP(void);


#endif

