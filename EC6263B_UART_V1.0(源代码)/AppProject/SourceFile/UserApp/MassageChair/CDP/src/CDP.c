/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：CDP.c                                                                                                         
**
**    功能描述：通信数据包。
**
**    公    司：蒙发利电子
**
**    项目名称：
**
**    平台信息：
**
**    作    者：Hzy
**
**    其他说明：
**
**    修改记录：--------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/
/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "CDP.h"
#include "MChair.h"
#include "Server.h"

/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/                                                                
#define  CDP_REPEATER_LTL_MS                   15000              /*转发器活跃时长 LTL(Lively time length)，单位毫秒*/


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
static CDP_t  CDP;
CDP_t  *pCDP = &CDP;

static const SysMode_KeyVal_t SideCtrlKeyValMapTab[] = 
{
  KEYVAL_NoPress,                    // key00:
  KEYVAL_HeatLumbarBack,             // key01:
  KEYVAL_RollerFeet,                 // key02:
  KEYVAL_SpikeFeetDown,              // key03:
  KEYVAL_SpikeFeetUp,                // key04:
  KEYVAL_SpikeBackUpFeetDown,        // key05:
  KEYVAL_SpikeBackDownFeetUp,        // key06:
  KEYVAL_AutoQuick,                  // key07:
  KEYVAL_SpikeZeroGravity,           // key08:
  KEYVAL_Pause,                      // key09:
  KEYVAL_NoPress,                    // key10:
  KEYVAL_CoreMannualFront,           // key11:
  KEYVAL_CoreMannualBack,            // key12:
};


extern uint8_t Server_GetKeyExeState(void);
/*声明数据处理函数（数据处理函数分布在各个对应的相关模块中）*/
extern uint8_t  MChair_KeyValHandle_CDPDataObjRx_0x01(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);

extern uint8_t  MChair_TabTry_CDPDataObjRx_0x1A_To_0x1F(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);

extern uint8_t  SaveData_CDPDataObjRx_0x3D(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t  SaveData_CDPDataObjRx_0x3E(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);


extern uint8_t  Core_CDPDataObjRx_0x40(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t* Core_CDPDataObjTx_0x40(void);

extern uint8_t  Heat_CDPDataObjRx_0x41(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t* Heat_CDPDataObjTx_0x41(void);


extern uint8_t Gas_CDPDataObjRx_0x48(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t* Gas_CDPDataObjTx_0x48(void);

extern uint8_t Roller_CDPDataObjRx_0x49(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t* Roller_CDPDataObjTx_0x49(void);

extern uint8_t Vib_CDPDataObjRx_0x4A(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t* Vib_CDPDataObjTx_0x4A(void);

extern uint8_t LegFlexSpike_CDPDataObjRx_0x4B(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
extern uint8_t* LegFlexSpike_CDPDataObjTx_0x4B(void);

uint8_t  SideCtrl_CDPDataObjRx_0x50(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t* SideCtrl_CDPDataObjTx_0x50(Ticker_t ExePeriod);

/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : IAP_CDPDataObj_0x01                                                                                      
* 功能描述 : 通知目标模块进入IAP模式                                                                                 
* 输入参数 : pRxDU  -- 指向接收的数据对象单元
*            pAckDU -- 指向应答的数据对象单元
* 返回参数 : 该数据对象中数据的长度                                                                                                    
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t IAP_CDPDataObj_0x01(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  uint16_t i;
  /*关输出，然后复位，复位后进入BootLoade模式*/
  BSP_IO_SetOutput_CloseAll();
  while(++i < 1000);
  BSP_SystemReset();  
  return 0;
}

/*
========================================================================================================================
*【数据对象管理表】                                  【数据对象管理表】                                【数据对象管理表】
========================================================================================================================
*/
static const CDPDataObjManageTabItem_t  DataObjManageTab[] = 
{
  {0x01,  B(00000000),  MChair_KeyValHandle_CDPDataObjRx_0x01},     /*0x01 键值(手控器-->中心板)*/
  {0x1A,  B(00000000),  MChair_TabTry_CDPDataObjRx_0x1A_To_0x1F},   /*0x1A 表格调试 通道0(上位机<-->中心板)*/
  {0x1B,  B(00000000),  MChair_TabTry_CDPDataObjRx_0x1A_To_0x1F},   /*0x1B 表格调试 通道1(上位机<-->中心板)*/
//  {0x20,  B(00000000),  NULL},                                      /*0x20 状态信息汇总包（中心板-->手控器）*/
  {0x3D,  B(00000000),  SaveData_CDPDataObjRx_0x3D},                /*0x3D 程序鉴别信息*/
  {0x3E,  B(00000000),  SaveData_CDPDataObjRx_0x3E},                /*0x3E 电子序列码*/
//  {0x3F,  B(00000000),  NULL},                                      /*0x3F 系统各部件运行时间*/
  
  {0x40,  B(00000000),  Core_CDPDataObjRx_0x40},                    /*0x40 机芯手法控制(中心板<-->机芯板）*/
  {0x41,  B(00000000),  Heat_CDPDataObjRx_0x41},                    /*0x41 按摩头加热控制(中心板<-->机芯板） */
  {0x48,  B(00000000),  Gas_CDPDataObjRx_0x48},                     /*0x48 腿脚充气控制(中心板<-->腿脚控制板）*/
  {0x49,  B(00000000),  Roller_CDPDataObjRx_0x49},                  /*0x49 腿脚滚轮控制(中心板<-->腿脚控制板）*/
  {0x4A,  B(00000000),  Vib_CDPDataObjRx_0x4A},                      /*0x4A 腿脚振动控制(中心板<-->腿脚控制板）*/
  {0x4B,  B(00000000),  LegFlexSpike_CDPDataObjRx_0x4B},            /*0x4B 腿脚伸缩控制(中心板<-->腿脚控制板）*/
//  {0x4C,  B(00000000),  Heat_CDPDataObjRx_0x4C},                    /*0x4C 腿脚加热控制(中心板<-->腿脚控制板）*/
  {0x50,  B(00000000),  SideCtrl_CDPDataObjRx_0x50}                 /*0x50 侧板控制器(侧板控制器-->中心板) */
};

#define  DATA_OBJ_MANAGE_TAB_NUM    TAB_NUM(DataObjManageTab)

static uint16_t CDPDataObjID(uint16_t index)
{
  if(index > (DATA_OBJ_MANAGE_TAB_NUM-1))
  {
    return INDEX_NO_MATCH;
  }
  return DataObjManageTab[index].ID;
}


static const CDPDataObjManageTabItem_t  IAPDataObjManageTab[] = 
{
  {0x01,  B(00000000),  IAP_CDPDataObj_0x01}            /*通知目标模块进入IAP模式*/
};

#define  IAP_DATA_OBJ_MANAGE_TAB_NUM    TAB_NUM(IAPDataObjManageTab)

static uint16_t IAPCDPDataObjID(uint16_t index)
{
  if(index > (IAP_DATA_OBJ_MANAGE_TAB_NUM-1))
  {
    return INDEX_NO_MATCH;
  }
  return IAPDataObjManageTab[index].ID;
}

static const CDPDataObjManageTabItem_Server_t  ServerDataObjManageTab[] = 
{
  {0x0040,  B(00000000),  Server_CDPDataObjRX_0x0040},            /*接收到设备序列号回传数据*/
//  {0x0041,  B(00000000),  Server_CDPDataObj_0x0041},          /*接收到心跳包回传数据*/
  {0x0042,  B(00000000),  Server_CDPDataObjRX_0x0042},            /*接收到中心板版本号回传数据*/
  {0x0043,  B(00000000),  Server_CDPDataObjRX_0x0043},            /*接收到设备远程升级方式回传数据*/
  {0x0702,  B(00000000),  Server_CDPDataObjRX_0x0702},            /*接收键值*/
  {0x0901,  B(00000000),  Server_CDPDataObjRX_0x0901},            /*获取按摩椅开机状态*/
  {0x0912,  B(00000000),  Server_CDPDataObjRX_0x0912},            /*配网接收*/
  {0x0913,  B(00000000),  Server_CDPDataObjRX_0x0913},            /*获取设备ID*/
  {0x0C60,  B(00000000),  Server_CDPDataObjRX_0x0C60},            /*获取椅子状态*/
  {0x0D01,  B(00000000),  Server_CDPDataObjRX_0x0D01},            /*按摩椅状态数据1 开机*/
  {0x0D02,  B(00000000),  Server_CDPDataObjRX_0x0D02},            /*按摩椅状态数据2 关机*/
};

#define  SERVER_DATA_OBJ_MANAGE_TAB_NUM    TAB_NUM(ServerDataObjManageTab)

static uint16_t ServerCDPDataObjID(uint16_t index)
{
  if(index > (SERVER_DATA_OBJ_MANAGE_TAB_NUM-1))
  {
    return INDEX_NO_MATCH;
  }
  return ServerDataObjManageTab[index].ID;
}

/*
************************************************************************************************************************
* 函数名称 : CDP_DataObjRxHandle                                                                                      
* 功能描述 : 数据对象处理                                                                                
* 输入参数 : pEvt -- 指向事件的指针，事件内的参数对象包含接收到的数据                                                                                       
* 返回参数 : MEM_IDLE -- 事件内存空闲，可以释放了        
*            MEM_USE  -- 事件内存使用中，还不能释放                                                                   
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t CDP_DataObjRxHandle(ESF_Evt_t	*pEvt)
{
  uint16_t                   index;
  uint8_t                    DataObjLen;                                               /*数据对象长度*/
  int16_t                    DURestLen;                                                /*数据单元剩余长度*/
  uint8_t                    *pRxDU;                                                   /*指向接收的数据单元*/ 
  uint8_t                    *pAckDU;                                                  /*指向应答的数据单元*/
  uint16_t                    ServerTemp;
  CDPDataObjManageTabItem_t  *DOManageTab;
  

  pRxDU  = &pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_DU];                                 /*指向接收的第一个数据对象*/
  pAckDU = &pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_DU];                                /*指向应答的第一个数据对象*/
  DURestLen  = pEvt->Arg.CDPRx.RxLen - CDP_PDU_EXCEPT_DU_LEN;                          /*所有数据对象长度的总和*/
  while(DURestLen > 0)
  {
    if((pRxDU[CDP_DU_OFFSET_LEN] < 2)        ||                                        /*小于最小长度*/
       (pRxDU[CDP_DU_OFFSET_LEN] > DURestLen))                                         /*大于实际可用剩余长度*/
    {
      return MEM_IDLE;                                                                 /*数据长度错，不再处理*/
    }
    DURestLen -= pRxDU[CDP_DU_OFFSET_LEN];                                             /*数据单元剩余长度*/

    if( (CDP_CMD_IAP         == pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD]) ||
        (CDP_CMD_REMOTE_IAP  == pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD]) )          /*不同的命令对应不同的数据对象表格*/
    {
      DOManageTab = (CDPDataObjManageTabItem_t*)IAPDataObjManageTab;
      index = 0;//BinarySearch(pRxDU[CDP_DU_OFFSET_ID], IAP_DATA_OBJ_MANAGE_TAB_NUM, IAPCDPDataObjID);
    }
    else if(0x80 == pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_VER])
    {
      DOManageTab = (CDPDataObjManageTabItem_t*)ServerDataObjManageTab;
      ServerTemp = pRxDU[CDP_DU_OFFSET_ID]<<8;
      ServerTemp = ServerTemp | pRxDU[CDP_DU_OFFSET_SERVER_ID];
      index = BinarySearch(ServerTemp, SERVER_DATA_OBJ_MANAGE_TAB_NUM, ServerCDPDataObjID);
    }
    else
    {
      DOManageTab = (CDPDataObjManageTabItem_t*)DataObjManageTab;
      index = BinarySearch(pRxDU[CDP_DU_OFFSET_ID], DATA_OBJ_MANAGE_TAB_NUM, CDPDataObjID);
    }
    
    if(INDEX_NO_MATCH == index)                                                        /*没有匹配的数据对象ID*/    
    {
      pRxDU  += pRxDU[CDP_DU_OFFSET_LEN];                                              /*指向下一个数据对象*/
      continue;                                                                        /*忽略该数据对象，处理下一个*/
      //return MEM_IDLE;                                                                 /*数据处理出错，则放弃后续数据的处理*/
    }
    else
    {
      DataObjLen = 2;                                                                  /*先默认数据对象长度为2*/
      if(DOManageTab[index].pDataHandle != NULL)
      {
        DataObjLen = DOManageTab[index].pDataHandle(pRxDU, pAckDU, pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_SRC], pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD]);
        if((CDP_DU_HANDLE_ERR == DataObjLen) || (DataObjLen < 2)) 
        {
          return MEM_IDLE;                                                             /*数据处理出错，则放弃后续数据的处理*/
        }
      }
      else
      {
        return MEM_IDLE;                                                               /*无对应的处理函数，则出错，要么补上函数，要么注释掉相应的代码*/
      }
      
      pAckDU[CDP_DU_OFFSET_LEN] = DataObjLen;                                          /*pDataHandle函数返回整个数据对象的长度*/                                           
      if( pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_VER] == 0x80 )                         /*服务器数据*/
      {
        pAckDU[CDP_DU_OFFSET_ID]        = pRxDU[CDP_DU_OFFSET_ID];                     /*应答数据对象ID*/
        pAckDU[CDP_DU_OFFSET_SERVER_ID] = pRxDU[CDP_DU_OFFSET_SERVER_ID];              /*应答数据对象ID*/
      }
      else                                                                             /*本地升级*/
      {
        pAckDU[CDP_DU_OFFSET_ID]  = pRxDU[CDP_DU_OFFSET_ID];                           /*应答数据对象ID*/
      }
      pEvt->Arg.CDPRx.AckLen   += DataObjLen;                                          /*目前应答长度*/
      pAckDU += pAckDU[CDP_DU_OFFSET_LEN];                                             /*指向下一个数据对象*/
      pRxDU  += pRxDU[CDP_DU_OFFSET_LEN];                                              /*指向下一个数据对象*/
    }    
  }
  
  return MEM_USE;  
}

/*
************************************************************************************************************************
* 函数名称 : CDP_PDURxHandle                                                                                      
* 功能描述 : 接收到的数据处理                                                                                
* 输入参数 : pEvt -- 指向事件的指针，事件内的参数对象包含接收到的数据                                                                                       
* 返回参数 : MEM_IDLE --  事件内存空闲，可以释放了        
*            MEM_USE  --  事件内存使用中，还不能释放                                                                   
* 补充说明 : 
************************************************************************************************************************
*/
uint8_t CDP_PDURxHandle(ESF_Evt_t *pEvt)
{
  uint8_t  EvtMemState;


  /*地址判断-----------------------------------------------------------------------------------*/
  if(CDP_ADDR_SELF != pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_DES])                             /*不等于自身地址*/
  {
    if(CDP_ADDR_SELF == CDP_ADDR_CEN)                                                         /*自身为中心板，则中心板要转发数据给其他通信模块*/
    {
      pCDP->RepeaterLTL = CDP_REPEATER_LTL_MS;                                                /*每次都重新设定转发器的活跃时间*/ 
      
      pEvt->Type = EvtCDPTx;                                                                  /*改为数据包发送事件*/
      memcpy(pEvt->Arg.CDPTx.pTxBuf, pEvt->Arg.CDPRx.pRxBuf, pEvt->Arg.CDPRx.RxLen);          /*拷贝数据到要发送的缓存*/
      pEvt->Arg.CDPTx.TxLen  = pEvt->Arg.CDPRx.RxLen;                                         /*要发送的长度直接等于接收长度*/
      ESF_EvtQuene_Post(pEvt);                                                                /*投递事件*/
      return  MEM_USE;    
    }
    else //if(CDP_ADDR_SELF != CDP_ADDR_CEN) 
    {
      return  MEM_IDLE;                                                                       /*地址错误，不处理*/
    }
  }

  /*命令判断-----------------------------------------------------------------------------------*/
  if((pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_SET_ACK)         &&               /*命令：主机设置从机，从机需应答 */      
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_SET_NACK)        &&               /*命令：主机设置从机，从机无需应答 */        
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_UPREPORT)        &&               /*命令：从机主动上报 */        
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_QRY)             &&               /*命令：主机查询从机 */       
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_IAP)             &&               /*命令：IAP升级操作 */       
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_UPREPORT_SERVER) &&               /*命令：服务器 从机主动上报*/
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_QRY_SERVER)      &&               /*命令：服务器 主机查询从机*/
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_SET_NACK_SERVER) &&               /*命令：服务器 主机设置从机，从机无需应答*/
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_SET_ACK_SERVER)  &&               /*命令：服务器 主机设置从机，从机需应答*/ 
     (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_REMOTE_IAP) )                     /*命令：远程IAP升级操作 */
  {
    pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_ACK] = CDP_ACK_INVALID_CMD;                        /*应答：不支持的命令码 */
    return  MEM_IDLE;                                                                         /*不支持的命令码，该内存块可释放了*/
  }
  
  /*该模块作为逻辑从机-------------------------------------------------------------------------*/
  if((CDP_ACK_SEND     == pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_ACK]) &&                      /*应答：数据的主动发起方，填0xFF。*/
     (CDP_CMD_UPREPORT != pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD]) )                       /*命令：不是 从机主动上报 */                      
  {
    memcpy(pEvt->Arg.CDPRx.pAckBuf, pEvt->Arg.CDPRx.pRxBuf, CDP_PDU_EXCEPT_DU_LEN);           /*给应答缓存填充部分数据*/
    pEvt->Arg.CDPRx.AckLen = CDP_PDU_EXCEPT_DU_LEN;                                           /*目前长度*/
    pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_DES] = pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_SRC]; /*更改相应的地址*/
    pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_SRC] = pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_DES]; /*更改相应的地址*/
    pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_ACK] = CDP_ACK_SUCCESS;                            /*应答：先假设成功 */
    
    EvtMemState = CDP_DataObjRxHandle(pEvt);                                                  /*处理数据对象*/

    if((EvtMemState != MEM_IDLE) &&                                                           /*有数据要应答*/
       (pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD] != CDP_CMD_SET_NACK))                      /*非CDP_CMD_SET_NACK 命令：主机设置从机，从机无需应答 */        
    {
      if(FALSE == Server_GetCSFlag().KeyExeState)
      {
        pEvt->Arg.CDPRx.pAckBuf[CDP_PDU_OFFSET_ACK] = CDP_ACK_FAIL;
        Server_SetKeyExeState(TRUE);
      }
      pEvt->Type = EvtCDPTx;                                                                  /*改为数据包发送事件*/
      memcpy(pEvt->Arg.CDPTx.pTxBuf, pEvt->Arg.CDPRx.pAckBuf, pEvt->Arg.CDPRx.AckLen);        /*拷贝数据到要发送的缓存*/
      pEvt->Arg.CDPTx.TxLen  = pEvt->Arg.CDPRx.AckLen;                                        /*要发送的长度*/
      ESF_EvtQuene_Post(pEvt);                                                                /*投递事件*/
      return  MEM_USE;    
    }
    else
    {
      return MEM_IDLE;    
    }
  }
  
  /*该模块作为逻辑主机-------------------------------------------------------------------------*/
  else if((CDP_ACK_SUCCESS  == pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_ACK]) ||                 /*应答：执行成功。即收到其他模块的响应数据。*/              
          (CDP_CMD_UPREPORT == pEvt->Arg.CDPRx.pRxBuf[CDP_PDU_OFFSET_CMD]) )                  /*命令：从机主动上报 */                      
  {
    CDP_DataObjRxHandle(pEvt);                                                                /*处理数据对象*/
    return  MEM_IDLE;                                                                         /*处理完响应后，该内存块可释放了*/
  }
  
  /*错误---------------------------------------------------------------------------------------*/
  return  MEM_IDLE;                                                                           /*错误，不处理*/
}

/*
************************************************************************************************************************
* 函数名称 : CDP_PDUTxHandle                                                                                                         
* 功能描述 : 数据包发送                                                                                        
* 输入参数 : pEvt -- 事件                                                                                  
* 返回参数 : MEM_IDLE --  事件内存空闲，可以释放了        
*            MEM_USE  --  事件内存还在使用中，还不能释放                                                                   
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t CDP_PDUTxHandle(ESF_Evt_t *pEvt)
{
  uint8_t TxState;
  
  TxState = BSP_UART_TxState_Idle;                   /*先假设串口空闲*/

  if(CDP_ADDR_CTR == pEvt->Arg.CDPTx.pTxBuf[CDP_PDU_OFFSET_DES])            
  {
    TxState = CDP_CenApp_DataTx(pEvt);
  }
  else if( (CDP_ADDR_CORE        == pEvt->Arg.CDPTx.pTxBuf[CDP_PDU_OFFSET_DES]) ||
           (CDP_ADDR_CTR_SIDE    == pEvt->Arg.CDPTx.pTxBuf[CDP_PDU_OFFSET_DES]) ||
           (CDP_ADDR_CALVES_FEET == pEvt->Arg.CDPTx.pTxBuf[CDP_PDU_OFFSET_DES]) )
  {
    TxState = CDP_CenXxx_DataTx(pEvt);  
  }
  else if( (CDP_ADDR_WIFI   == pEvt->Arg.CDPTx.pTxBuf[CDP_PDU_OFFSET_DES]) ||
           (CDP_ADDR_SERVER == pEvt->Arg.CDPTx.pTxBuf[CDP_PDU_OFFSET_DES]) )
  {
    TxState = CDP_CenServer_DataTx(pEvt);
  }

  if(BSP_UART_TxState_Busy == TxState)
  {
    ESF_EvtQuene_Post(pEvt);                         /*串口忙，则重新投递，等待下一次发送*/
    return MEM_USE;                                  /*内存事件块仍在使用中*/
  }
  else
  {
    return MEM_IDLE;                                 /*事件所占内存已无用*/
  }
}

/*
************************************************************************************************************************
* 函数名称 : CDP_PDUPackTx                                                                                                         
* 功能描述 : 通信数据包 PDU 数据打包和发送                                                                                    
* 输入参数 : DesAddr   -- 目的地址
*            Cmd       -- 命令
*            DUBuf     -- 指针数组，数组内的元素为指针，每个指针指向一个保存DU数据(应该包含数据长度和数据ID) 的内存地址。   
*            DUBufISum -- DUBuf数组的元素个数
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                        
************************************************************************************************************************
*/
void CDP_PDUPackTx(uint8_t DesAddr, uint8_t Cmd, uint8_t *DUBuf[], uint8_t DUBufISum)
{
  ESF_Evt_t *pEvt = NULL;
  uint8_t *wp, *rp;
  uint16_t DULen;
  uint8_t i;

  pEvt = ESF_MemBuf_Get();                                                          /*申请内存块*/
  if(NULL == pEvt)
  {
    return;                                                                         /*申请失败则返回*/
  }
  
  pEvt->Type = EvtCDPTx;                                                            /*数据包发送事件*/
  pEvt->Arg.CDPTx.pTxBuf = (uint8_t*)&pEvt->AppendData[0];                          /*要发送的缓存*/
  wp = pEvt->Arg.CDPTx.pTxBuf;
  *wp++ = DesAddr;
  *wp++ = CDP_ADDR_SELF;
  
  if( (CDP_ADDR_WIFI   == DesAddr) ||
      (CDP_ADDR_SERVER == DesAddr) )
  {
    *wp++ = 0x80;
    *wp++ = 0x80;
  }
  else
  {
    *wp++ = 0;
    *wp++ = 0;
  }

  *wp++ = Cmd;
  *wp++ = CDP_ACK_SEND;
  
  for(i=0; i<DUBufISum; i++)
  {
    rp = DUBuf[i];
    DULen = rp[CDP_DU_OFFSET_LEN];
    while(DULen--)
    {
      *wp++ = *rp++;
    }
  }

  pEvt->Arg.CDPTx.TxLen  = wp - pEvt->Arg.CDPTx.pTxBuf;                             /*要发送的长度*/
  ESF_EvtQuene_Post(pEvt);                                                          /*投递事件*/
}

/*
************************************************************************************************************************
* 函数名称 : CDP_FrameRxHandle                                                                                                         
* 功能描述 : 通信数据包   之   帧接收处理                                                                              
* 输入参数 : pFrameRx -- 要处理的结构                                                                   
* 输入参数 : RxByte   -- 收到的字节数据     
*            CDPType  -- 数据包类型
*            CDPDAP   -- 数据访问物理端口
* 返回参数 : 0   -- 未收到有效数据。
*            非0 -- 收到某个模块的数据帧，该非0值表示数据来源模块的地址。
* 补充说明 : 该函数必须通过BSP_UART_RegRxByteCB()注册给BSP层，以便在串口接收字节中断中调用。                                                                                                  
************************************************************************************************************************
*/
uint8_t CDP_FrameRxHandle(CDP_FrameRx_t *pFrameRx, uint8_t RxByte, uint8_t CDPType, uint8_t CDPDAP)
{
  /*先申请一块内存用作数据接收的缓存处理----------------------------------------*/
  if(NULL == pFrameRx->pEvt) 
  {
    pFrameRx->pEvt = ESF_MemBuf_Get();                                                         /*申请内存块*/
    if(NULL == pFrameRx->pEvt)
    {
      return  0;                                                                               /*申请失败则返回，等下一次再申请*/
    }
    pFrameRx->pRxBuf = (uint8_t*)&pFrameRx->pEvt->AppendData[0];                               /*数据接收的存放位置*/
  }
  
  /*字节间接收超时了，则设置数据接收结束，以重新接收新数据。
      中心板--机芯板   (新协议)
      中心板--类平板   (旧协议)
      中心板--小腿板   (旧协议)
    假设上面三种都接在一个串口上，如此混合收发过程中，容易产生误判，加此超时判断。误判如下：  
   【 由于某种原因该部分数据丢了 xx xx xx xx 7E  -->给类平板的数据  -->7E xx xx xx ...... 7E 】
                                             |<------------------------>|
                                             这部分数据会符号新协议的帧接收成功判断。
                                             虽然抛给上层后，会被过滤掉。但此种情况会导致新协议数据经常收不到。*/
  if(pFrameRx->ByteRxTimeOutMs >= 4)                     /*波特率19200，则6*1.92=11字节的时间*/                                           
  {
    pFrameRx->PDURecing = FALSE;           
  }
  pFrameRx->ByteRxTimeOutMs = 0;

  /*数据接收：帧提取、转义处理、累加和检查--------------------------------------*/
  if(CDP_FRAME_BOUNDARY == RxByte)                                                             /*帧边界*/ 
  {
    if(TRUE == pFrameRx->PDURecing)                                                            /*数据接收中，则表明收到帧尾*/
    {
      if(pFrameRx->RxLen >= CDP_FRAME_MIN_LEN-2)                                               /*收到足够长度的数据。-2：减去帧头和帧尾，不放入接收缓存*/
      {
        if(CORRECT == CumulativeSum_Check(pFrameRx->pRxBuf, pFrameRx->RxLen))
        {
          pFrameRx->pEvt->Type              = EvtCDPRx;
          pFrameRx->pEvt->Arg.CDPRx.CDPType = CDPType;
          pFrameRx->pEvt->Arg.CDPRx.DAP     = CDPDAP;                                          /*数据访问物理端口*/   
          pFrameRx->pEvt->Arg.CDPRx.pRxBuf  = pFrameRx->pRxBuf;        
          pFrameRx->pEvt->Arg.CDPRx.RxLen   = pFrameRx->RxLen -1;                              /*-1: 减去1字节的累加和校验*/
          pFrameRx->pEvt->Arg.CDPRx.pAckBuf = pFrameRx->pEvt->Arg.CDPRx.pRxBuf + pFrameRx->pEvt->Arg.CDPRx.RxLen;  /*应答缓存紧邻接收缓存之后*/      
          ESF_EvtQuene_Post(pFrameRx->pEvt);                                                   /*投递事件*/ 
          pFrameRx->pEvt = NULL;                                                               /*投递完后，指针赋空，以便下次申请新的内存块缓存*/
          pFrameRx->PDURecing = FALSE;                                                         /*数据接收结束*/
          return pFrameRx->pRxBuf[CDP_PDU_OFFSET_SRC];                                         /*返回模块地址*/
        }
      }
    }
    else                                                                                       /*数据接收还未开启，则表明收到帧头*/
    {
      pFrameRx->PDURecing = TRUE;                                                              /*开启数据接收进行中*/
    }
    
    pFrameRx->NeedESC = FALSE;
    pFrameRx->RxLen = 0;                                                                       /*每次收到帧边界，都将接收长度清零*/
  }
  else if(TRUE == pFrameRx->PDURecing)                                                         /*数据接收开启才进行数据的接收*/
  {
    if(CDP_FRAME_ESC == RxByte)
    {
      pFrameRx->NeedESC = TRUE;                                                                /*转义的字节数据不放入接收缓存，紧邻的下一个字节要做转义处理，还原成原来的数据*/
    }
    else
    {
      if(TRUE == pFrameRx->NeedESC)
      {
        pFrameRx->pRxBuf[pFrameRx->RxLen++] = RxByte ^ 0x03;                                   /*还原成原来的数据*/
        pFrameRx->NeedESC = FALSE;
      }
      else
      {
        pFrameRx->pRxBuf[pFrameRx->RxLen++] = RxByte;
      }
      
      if(pFrameRx->RxLen >= pFrameRx->RxLenMax)                                                /*超过缓存长度，则从头开始接收*/   
      {
        pFrameRx->NeedESC = FALSE;
        pFrameRx->RxLen = 0;
      }
    }
  }
  
  return 0;
}

/*
************************************************************************************************************************
* 函数名称 : CDP_CommonDataTx                                                                                                         
* 功能描述 : 通信数据包  之  帧发送发送                                                                      
* 输入参数 : pEvt        -- 要发送的事件数据   
*            pTxFrameBuf -- 发送前的打包帧缓存
*            PortNum     -- 发送的端口
* 返回参数 : BSP_UART_TxState_Busy  -- 发送忙，无法处理发送pTxBuf指向的的数据。
*            其他值                 -- 串口开始发送pTxBuf指向的的数据了。
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
uint8_t CDP_FrameTxHandle(ESF_Evt_t *pEvt, uint8_t *pTxFrameBuf, BSP_UART_PortNum_t PortNum)
{
  uint8_t *wp;
  uint16_t i;
  uint8_t sum;
  
  
  if(BSP_UART_TxState_Busy == BSP_UART_GetTxState(PortNum))
  {
    return BSP_UART_TxState_Busy;    /*发送忙，则返回*/
  }
  
  sum = CumulativeSum_Cal(pEvt->Arg.CDPTx.pTxBuf, pEvt->Arg.CDPTx.TxLen); 
  pEvt->Arg.CDPTx.pTxBuf[pEvt->Arg.CDPTx.TxLen++] = sum;

  wp = pTxFrameBuf;
  *wp++ = CDP_FRAME_HEADER;
  for(i=0; i<pEvt->Arg.CDPTx.TxLen; i++)
  {
    if((CDP_FRAME_BOUNDARY == pEvt->Arg.CDPTx.pTxBuf[i]) || 
       (CDP_FRAME_ESC      == pEvt->Arg.CDPTx.pTxBuf[i]) )
    {
      *wp++ = CDP_FRAME_ESC;
      *wp++ = pEvt->Arg.CDPTx.pTxBuf[i] ^ 0x03;
    }
    else
    {
      *wp++ = pEvt->Arg.CDPTx.pTxBuf[i];
    }
  }
  *wp++ = CDP_FRAME_FOOTER;
  
  return BSP_UART_TxData(PortNum, pTxFrameBuf, (wp - pTxFrameBuf));
}

/*
************************************************************************************************************************
* 函数名称 : CDP_DataTxTmrHandle                                                                                                         
* 功能描述 : 通信数据包   之   数据发送定时处理                                                                       
* 输入参数 : ExePeriod -- 函数的执行周期                                                                                    
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
void CDP_DataTxTmrHandle(Ticker_t ExePeriod)
{
  static  Ticker_t  AppTicker,SeverTemp;
  static  uint8_t   Order;
  static  Ticker_t  Ticker;
  static  Ticker_t  ServerTicker1,ServerTicker2;
  static  Ticker_t  TickerSec1;
  
  uint8_t *DUBuf[5];    /*指针数组，数组内的指针指向保存DU数据(应该包含数据长度和数据ID) 的内存地址。*/
  uint8_t i;  

  if(pCDP->RepeaterLTL >= ExePeriod)
  {
    pCDP->RepeaterLTL -= ExePeriod;
    pCDP->CSFlag.Bit.RepeaterWork = TRUE;      /*转发器工作*/
    Ticker = 0;
  }
  else
  {
    pCDP->RepeaterLTL = 0;
    pCDP->CSFlag.Bit.RepeaterWork = FALSE;     /*转发器不工作*/
   
    /*转发器工作期间，中心板对其他模块的定时发送功能先暂停，转发器停止后，再恢复定时发送功能*/  
  
    Ticker += ExePeriod;
    if(35 == Ticker)
    {
      if(0 == Order)
      {
        CDP_CenStateTmrToCtrl_DataTx(35);
      }
    }
    else if(55 == Ticker)
    {
      i = 0;
      Order = !Order;
      if(Order)
      {
        DUBuf[i++] = Gas_CDPDataObjTx_0x48();
        DUBuf[i++] = Roller_CDPDataObjTx_0x49();
//        DUBuf[i++] = Vib_CDPDataObjTx_0x4A();
        DUBuf[i++] = LegFlexSpike_CDPDataObjTx_0x4B();
        CDP_PDUPackTx(CDP_ADDR_CALVES_FEET, CDP_CMD_SET_ACK, DUBuf, i);
      }
      else
      {
        DUBuf[i++] = SideCtrl_CDPDataObjTx_0x50(140);
        CDP_PDUPackTx(CDP_ADDR_CTR_SIDE, CDP_CMD_SET_ACK, DUBuf, i);
      }
    }
    else if(70 == Ticker)
    {
      i = 0;
      DUBuf[i++] = Core_CDPDataObjTx_0x40();
      DUBuf[i++] = Heat_CDPDataObjTx_0x41();
      CDP_PDUPackTx(CDP_ADDR_CORE, CDP_CMD_SET_ACK, DUBuf, i);
      Ticker = 0;
    }
    
    /*给服务器的定时数据*/
    ServerTicker1 += ExePeriod;
    if(ServerTicker1 >= 1000)     /*1S发送一次*/
    {
      if(TRUE == CDP_CenServer_GetCSFlag().Bit.LinkLostFault)
      {
        Server_ReReportedData();
      }
      ServerTicker1 = 0;
      i = 0;
      switch(SeverTemp)
      {
        case 0:
          if( FALSE == Server_GetCSFlag().UpDataSuc_0x0040 )
          {
            DUBuf[i++] = Server_CDPDataObjTx_0x0040();
          }
          SeverTemp++;
          break;
          
        case 1:
          if( FALSE == Server_GetCSFlag().UpDataSuc_0x0042 )
          {
            DUBuf[i++] = Server_CDPDataObjTx_0x0042();
          }
          SeverTemp++;
          break;

        case 2:
          if( FALSE == Server_GetCSFlag().UpDataSuc_0x0043 )
          {
            DUBuf[i++] = Server_CDPDataObjTx_0x0043();
          }
          SeverTemp++;
          break;
          
        default:
          SeverTemp = 0;
          break;
      }
      if(i != 0)
      {
        CDP_PDUPackTx(CDP_ADDR_SERVER, CDP_CMD_UPREPORT_SERVER, DUBuf, i);
      }
      
      /*服务器收到 电子序列号 后才进行定时上报状态*/
      if( TRUE == Server_GetCSFlag().UpDataSuc_0x0040 )
      {
        TickerSec1 ++;
        if(TickerSec1 == 30)
        {
          i = 0;
          DUBuf[i++] = Server_CDPDataObjTx_0x0041();
          CDP_PDUPackTx(CDP_ADDR_SERVER, CDP_CMD_UPREPORT_SERVER, DUBuf, i);
        }
        else if(60 == TickerSec1)
        {
          i = 0;
          DUBuf[i++] = Server_CDPDataObjTx_0x004C();
          CDP_PDUPackTx(CDP_ADDR_SERVER, CDP_CMD_TIMEING_UPREPORT_SERVER, DUBuf, i);
        }
        else if(90 == TickerSec1)
        {
          i = 0;
          DUBuf[i++] = Server_CDPDataObjTx_0x004D();
          CDP_PDUPackTx(CDP_ADDR_SERVER, CDP_CMD_TIMEING_UPREPORT_SERVER, DUBuf, i);
          TickerSec1 = 0;
        }
      }
    }

    ServerTicker2 += ExePeriod;
    if(50 == ServerTicker2)        /*给服务器的状态数据，变化上报*/
    {
      if( TRUE == Server_GetCSFlag().UpDataSuc_0x0040 )
      {
        DUBuf[0] = 0;
        
        if(SYS_MODE_STANDBY == pMChair->SysModeCur)
        {
          DUBuf[2] = Server_CDPDataObjTx_0x0D02();
          DUBuf[0] = DUBuf[2];
        }
        else if(SYS_MODE_USERRUN == pMChair->SysModeCur)
        {
          DUBuf[1] = Server_CDPDataObjTx_0x0D01();
          DUBuf[0] = DUBuf[1];
        }
        if(TRUE == pMChair->CSFlag.Bit.MChairReported)
        {
          CDP_PDUPackTx(CDP_ADDR_SERVER, CDP_CMD_UPREPORT_SERVER, DUBuf, 1);
        }
      }
    }
    else if(250 == ServerTicker2)  /*发送数据给WIFI板*/
    {
      ServerTicker2 = 0;
      /*网络还未配置，且网络配置数据接收成功，向服务器发送配网数据*/
      if( (TRUE  == Server_GetCSFlag().NetDataRx) &&
          (FALSE == Server_GetCSFlag().WIFIIntCfg) )
      {
        DUBuf[0] = Server_CDPDataObjTx_0x0912();
        CDP_PDUPackTx(CDP_ADDR_WIFI, CDP_CMD_SET_ACK_SERVER, DUBuf, 1);
      }
    }
      
    /*发送给蓝牙APP数据*/
    AppTicker += ExePeriod;
    if(AppTicker >= 200)
    {
      AppTicker = 0;
      CDP_CenTmrToApp_DataTx(200);
    }
  }
}

/*
========================================================================================================================
*    通信数据包功能函数管理表                  通信数据包功能函数管理表                    通信数据包功能函数管理表
========================================================================================================================
*/

#define  CDP_TICK_COUNT_BUF_NUM   4
static Ticker_t CDP_TickCount[CDP_TICK_COUNT_BUF_NUM];

const ESF_TmrExeFunc_t  CDP_TmrExeFuncTab[] = 
{
  /*   执行函数               执行周期(ms)       时间计数变量*/
  {CDP_DataTxTmrHandle,          5,            &CDP_TickCount[0]},
  {CDP_CenXxx_FaultCheck,        2,            &CDP_TickCount[1]},
  {CDP_CenServer_FaultCheck,  1001,            &CDP_TickCount[2]},
  {CDP_CenApp_FaultCheck,        2,            &CDP_TickCount[3]},
};

#define  CDP_TMR_EXE_FUNC_TAB_NUM     TAB_NUM(CDP_TmrExeFuncTab)

/*
************************************************************************************************************************
* 函数名称 : CDP_Handle                                                                                                         
* 功能描述 : 通信数据包 处理                                                                                    
* 输入参数 : 无                                                                              
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                        
************************************************************************************************************************
*/
void CDP_Handle(void)
{
  /*调度功能函数表------------------------------------------------*/
  ESF_TmrExeFuncScheduling(CDP_TmrExeFuncTab, CDP_TMR_EXE_FUNC_TAB_NUM);
}

/*
************************************************************************************************************************
* 函数名称 : CDP_Init                                                                                                         
* 功能描述 : 通信数据包 初始化                                                                                 
* 输入参数 : 无                                                                              
* 返回参数 : 返回 可操作机芯功能 的结构体 的指针                                                             
* 补充说明 : 无                                                                                                        
************************************************************************************************************************
*/
CDP_t* CDP_Init(void)
{
  /*初始化相关数据------------------------------------------*/
  memset(pCDP, 0, sizeof(CDP_t)); /*清零所有数据*/
  pCDP->pCenXxx  = CDP_CenXxx_Init(); 
//  CDP_CenDebug_Init();
  pCDP->pCenApp = CDP_CenApp_Init();
  CDP_CenServer_Init();

  /*检测 CDP_TmrExeFuncTab 功能函数表排列是否正确------------------------*/
  ESF_TmrExeFuncTabCheck(CDP_TmrExeFuncTab, CDP_TMR_EXE_FUNC_TAB_NUM, CDP_TICK_COUNT_BUF_NUM);

  return pCDP;
}

/*
************************************************************************************************************************
* 函数名称 : CDP_GetCSFlag                                                                                                         
* 功能描述 : 获得 控制 与 状态 标识                                                                
* 输入参数 : 无                                                                   
* 返回参数 : 控制与状态标识 的结构体                                                             
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
CDPCSFlag_t CDP_GetCSFlag(void)
{
  return pCDP->CSFlag;
}




/*
************************************************************************************************************************
* 函数名称 : SideCtrl_CDPDataObjRx_0x50                                                                                      
* 功能描述 : 0x50 侧板控制器(侧板控制器-->中心板)
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象中数据的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t SideCtrl_CDPDataObjRx_0x50(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  ESF_Evt_t *pEvt;
  
  /*更新数据到中心板-------------------------------------------------------------*/
  memcpy((uint8_t *)&pCDP->SetQry0x50, &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  
  pCDP->CSFlag.Bit.CenXxx_SideCtrlKeyStuck = pCDP->SetQry0x50.Byte2.Bit.KeyStuck;

  pEvt = ESF_MemBuf_Get();                                       /*申请事件内存块*/
  if(pEvt != NULL)                                               /*申请成功*/ 
  {
    pEvt->Type = EvtCDPRx;
    pEvt->Arg.CDPRx.CDPType = CDP_TYPE_SIDE_CTRL;           
    pEvt->Arg.CDPRx.pRxBuf = (uint8_t*)pEvt->AppendData;
    
    pEvt->Arg.CDPRx.pRxBuf[0] = KEYVAL_NoPress;                  /*先默认无按键按下*/
    if((pCDP->SetQry0x50.KeyVal != 0) && (pCDP->SetQry0x50.KeyVal < TAB_NUM(SideCtrlKeyValMapTab)))
    {
      pEvt->Arg.CDPRx.pRxBuf[0] = SideCtrlKeyValMapTab[pCDP->SetQry0x50.KeyVal]; 
    }
    else if(0xFF == pCDP->SetQry0x50.KeyVal)
    {
      pEvt->Arg.CDPRx.pRxBuf[0] = pCDP->SetQry0x50.KeyVal; 
    }
    pEvt->Arg.CDPRx.RxLen = 1;
    ESF_EvtQuene_Post(pEvt);                                     /*投递事件*/        
  }  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* 函数名称 : SideCtrl_CDPDataObjTx_0x50                                                                                      
* 功能描述 : 0x50 侧板控制器(侧板控制器-->中心板)
* 输入参数 : ExePeriod -- 函数的执行周期                                                                                    
* 返回参数 : 成功则返回要发送的数据的内存首地址，失败返回NULL空指针
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t* SideCtrl_CDPDataObjTx_0x50(Ticker_t ExePeriod)
{
  static  Ticker_t       PowerLedFlashTimeMs;         

  pCDP->SetQry0x50.DataLen = sizeof(pCDP->SetQry0x50);  
  pCDP->SetQry0x50.DataID = 0x50;  
  
  
  PowerLedFlashTimeMs += ExePeriod;
  PowerLedFlashTimeMs =  (PowerLedFlashTimeMs > 1500) ? 0 : PowerLedFlashTimeMs;

  /* LED1 : 侧板控制器【HEAT】指示灯 */
  pCDP->SetQry0x50.Byte1.Bit.Led1 = (pMChair->FuncMA_Heat.Bit.LumbarBack == FMA_LUMBARBACK_HEAT_Mannual) ? ON : OFF;

  /* LED2 : 侧板控制器【FeetRoller】指示灯 */
  pCDP->SetQry0x50.Byte1.Bit.Led2 = (pMChair->FuncMA_Roller.Bit.Feet != FMA_ROLLER_NONE) ? ON : OFF;
  
  /* LED5 : 侧板控制器【POWER】指示灯 */
  pCDP->SetQry0x50.Byte1.Bit.Led5 = (TRUE == pMChair->CSFlag.Bit.SysRun) ? ON : ((PowerLedFlashTimeMs < 750) ? ON : OFF);
  
  /* LED8 : 侧板控制器【ZERO-G】指示灯 */
  pCDP->SetQry0x50.Byte1.Bit.Led8 = (pMChair->FuncAuto_Spike == FA_SPIKE_ZeroGravity2) ? ON : OFF;
  if((PBACK_ZERO2_ANGLE == Spike_GetBackAngle()) && (FALSE == pMChair->StateBackSpike.Bit.Work) &&
     (PFEET_ZERO2_ANGLE == Spike_GetFeetAngle()) && (FALSE == pMChair->StateFeetSpike.Bit.Work) )
  {
    pCDP->SetQry0x50.Byte1.Bit.Led8 = ON;
  }
  
  /* LED9 : 侧板控制器【AUTO】指示灯 */
  pCDP->SetQry0x50.Byte2.Bit.Led9 = (pMChair->FuncAuto_CoreGas == FA_COREGAS_Quick) ? ON : OFF;

  /* LED10 : 侧板控制器【PAUSE】指示灯 */
  pCDP->SetQry0x50.Byte2.Bit.Led10 = (TRUE == pMChair->CSFlag.Bit.Pause) ? ((PowerLedFlashTimeMs < 750) ? ON : OFF) : OFF;
  

  return (uint8_t *)&pCDP->SetQry0x50;
}
