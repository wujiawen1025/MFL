/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: CDP_CenApp.c                                                                                                         
**
**    功能描述: 通信数据包   之   App<--> 中心板。
**
**    公    司：蒙发利电子
**
**    项目名称：
**
**    平台信息：
**
**    作    者：LZH
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
#include "CDP.h"
#include "MChair.h"
#include "CDP_CenApp.h"
#include "Server.h"

/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/
#define  CEN_APP_RX_BUF_SIZE                  (ESF_MEM_BOLCK_BYTE_SIZE - (ESF_MEM_BOLCK_BYTE_SIZE/4)) /*接收缓存大小，最多占内存块的3/4*/
#define  CEN_APP_TX_BUF_SIZE                  (CEN_APP_RX_BUF_SIZE)                                   /*发送缓存大小*/
#define  CEN_APP_UART_PORT                    BSP_UART_Port0                                          /*所用串口*/

#define  CEN_APP_LINK_LOST_TIME_THRESHOLD     4000                                                    /*通信链接丢失时间门限*/

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
static CDP_CenApp_t CDP_CenApp;
CDP_CenApp_t *pCDP_CenApp = &CDP_CenApp;

//static const SysMode_KeyVal_t KeyValMapTab[] = 
//{

//};


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/

/*
************************************************************************************************************************
* 函数名称 : CDP_AppToCen_KeyValHandle                                                                                                         
* 功能描述 : 通信数据包   之   App --> 中心板   按键接收处理                                                       
* 输入参数 :                                                                    
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
void CDP_AppToCen_KeyValHandle()
{
  ESF_Evt_t *pEvt;
  
  pCDP_CenApp->KeyValRx = pCDP_CenApp->RxBuf[APP_CDP_OFFSET_DATA];
//        if((pCDP_CenApp->KeyValRx < TAB_NUM(KeyValMapTab)) && (pCDP_CenApp->KeyValRx != 0))
//        {
//          pCDP_CenApp->KeyValMap = KeyValMapTab[pCDP_CenApp->KeyValRx];
//        }
//        else
//        {
//          pCDP_CenApp->KeyValMap = pCDP_CenApp->KeyValRx;
//          if(0xFF == pCDP_CenApp->KeyValRx)
//          {
//            pCDP_CenApp->CSFlag.Bit.AppKeyLongPress = TRUE;         /*有按键长按*/
//          }
//        }
  pCDP_CenApp->KeyValMap = pCDP_CenApp->KeyValRx;
  
  if((pCDP_CenApp->KeyValMap != 0xff) && (pCDP_CenApp->KeyValMap != 0x00))
  {
    pCDP_CenApp->KeyValAssist = pCDP_CenApp->KeyValMap;         /*记录辅助键值*/
  }

  pEvt = ESF_MemBuf_Get();                                      /*申请事件内存块*/
  if(pEvt != NULL)                                              /*申请成功*/ 
  {
    pEvt->Type = EvtCDPRx;
    pEvt->Arg.CDPRx.CDPType = CDP_TYPE_APP_KEY;          
    pEvt->Arg.CDPRx.pRxBuf = (uint8_t*)pEvt->AppendData;
    memcpy(pEvt->Arg.CDPRx.pRxBuf, &pCDP_CenApp->RxBuf[APP_CDP_OFFSET_DATA], APP_TO_CEN_DATALEN);
    pEvt->Arg.CDPRx.pRxBuf[0] = pCDP_CenApp->KeyValMap;         /*键值修正到映射后的值*/        
    ESF_EvtQuene_Post(pEvt);                                    /*投递事件*/        
  }
  
  pCDP_CenApp->AckBuf[APP_CDP_OFFSET_HEAD] = 0x7B;
  pCDP_CenApp->AckBuf[APP_CDP_OFFSET_FUNC] = 0xB0;
  pCDP_CenApp->AckBuf[APP_CDP_OFFSET_LEN]  = 0x01;
  pCDP_CenApp->AckBuf[APP_CDP_OFFSET_DATA] = pCDP_CenApp->RxBuf[APP_CDP_OFFSET_DATA];
  pCDP_CenApp->CSFlag.Bit.NeedAck = TRUE;
}

void CDP_AppToCen_CfgNetwork()
{
  if(0x01 == (pCDP_CenApp->RxBuf[APP_CDP_OFFSET_DATA]&0x0F))
  {
    Server_SetIntState(FALSE);
    Server_SetIntData(&pCDP_CenApp->RxBuf[APP_CDP_OFFSET_DATA+1], pCDP_CenApp->RxBuf[APP_CDP_OFFSET_LEN]-1, TRUE);
  }
  else
  {
    Server_SetIntData(&pCDP_CenApp->RxBuf[APP_CDP_OFFSET_DATA+1], pCDP_CenApp->RxBuf[APP_CDP_OFFSET_LEN]-1, FALSE);
  }
  
  if( 0xF0 == (pCDP_CenApp->RxBuf[APP_CDP_OFFSET_DATA]&0xF0) )
  {
    Server_SetIntState(TRUE);
    Server_ReReportedData();             /*重新上报配网*/
  }
  
  pCDP_CenApp->AckBuf[APP_CDP_OFFSET_HEAD] = 0x7B;
  pCDP_CenApp->AckBuf[APP_CDP_OFFSET_FUNC] = 0xB0;
  pCDP_CenApp->AckBuf[APP_CDP_OFFSET_LEN]  = 0x01;
  pCDP_CenApp->AckBuf[APP_CDP_OFFSET_DATA] = 0xF0 + (pCDP_CenApp->RxBuf[APP_CDP_OFFSET_DATA]&0x0F);
  pCDP_CenApp->CSFlag.Bit.NeedAck = TRUE;
}

//void CDP_AppToCen_GetSoftVersion()
//{
//  pCDP_CenApp->CSFlag.Bit.NeedAck = TRUE;
//}

void CDP_AppToCen_HeartbeatPacket()
{
  pCDP_CenApp->LinkLostTimeMs = 0;                                            /*清链接丢失时间*/ 
  pCDP_CenApp->CSFlag.Bit.LinkLostFault = NORMAL;  
}

/*
************************************************************************************************************************
* 函数名称 : CDP_AppToCen_GetIDCode                                                                                                         
* 功能描述 : 通信数据包   之   App --> 中心板   获取电子序列号                                                   
* 输入参数 :                                                                    
* 返回参数 : 无                                                             
* 补充说明 : 由于蓝牙一包数据只能20Byte，可以数据为16Byte而实际电子序列号有17Byte，故对数量由4位偏移修改为3位                                                                               
************************************************************************************************************************
*/
void CDP_AppToCen_GetIDCode()
{
  int8_t i;
  
  pCDP_CenApp->AckBuf[APP_CDP_OFFSET_HEAD] = 0x7B;
  pCDP_CenApp->AckBuf[APP_CDP_OFFSET_FUNC] = 0xB6;
  pCDP_CenApp->AckBuf[APP_CDP_OFFSET_LEN]  = 16;
  
  SaveData_GetIDCode(&pCDP_CenApp->AckBuf[APP_CDP_OFFSET_DATA]);
  /*数量由4位偏移修改为3位*/
  for(i=0; i<3; i++)
  {
    pCDP_CenApp->AckBuf[APP_CDP_OFFSET_DATA+13+i] = pCDP_CenApp->AckBuf[APP_CDP_OFFSET_DATA+14+i];
  }

  pCDP_CenApp->CSFlag.Bit.NeedAck = TRUE;
}

/*
========================================================================================================================
*    通信数据包功能函数管理表                  通信数据包功能函数管理表                    通信数据包功能函数管理表
========================================================================================================================
*/
static const AppDataObjManageTabItem_t  AppDataObjManageTab[] = 
{
  {0xa0,  CDP_AppToCen_KeyValHandle },          /*App按键处理*/
  {0xa1,  CDP_AppToCen_CfgNetwork },            /*APP配网*/
//  {0xa2,  CDP_AppToCen_GetSoftVersion },        /*APP获取程序版本号*/
  {0xa3,  CDP_AppToCen_HeartbeatPacket },       /*APP心跳包*/
  {0xa6,  CDP_AppToCen_GetIDCode },             /*APP获取电子序列号*/
  
};

#define  APP_DATA_OBJ_MANAGE_TAB_NUM    TAB_NUM(AppDataObjManageTab)

static uint16_t AppDataObjID(uint16_t index)
{
  if(index > (APP_DATA_OBJ_MANAGE_TAB_NUM-1))
  {
    return INDEX_NO_MATCH;
  }
  return AppDataObjManageTab[index].Cmd;
}


/*
************************************************************************************************************************
* 函数名称 : CDP_AppToCen_AnalyzeApp                                                                                                         
* 功能描述 : 通信数据包   之   App --> 中心板   控制命令解析                                                          
* 输入参数 : RxByte -- 收到的字节数据                                                                    
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
void CDP_AppToCen_AnalyzeApp(uint8_t RxByte)
{
  uint8_t i;
  uint8_t sum;
  uint16_t index;
  
  /*防止干扰*/
  if(pCDP_CenApp->FrameRx.ByteRxTimeOutMs >= 4)                     /*波特率19200，则4*1.92=8字节的时间*/                                           
  {
    pCDP_CenApp->RxState = 0;           
  }


  switch(pCDP_CenApp->RxState)
  {
    case APP_TO_CEN_RX_STATE_SEARCH_HEAD:                            /*搜索起始码*/
    {
      pCDP_CenApp->RxLen = 0;
      if(APP_TO_CEN_HEAD == RxByte)
      {
        pCDP_CenApp->RxBuf[pCDP_CenApp->RxLen++] = RxByte;
        pCDP_CenApp->RxState = APP_TO_CEN_RX_STATE_JUDGE_FUNC;       /*收到起始码，则去判断功能码*/
      }
    }break;

    case APP_TO_CEN_RX_STATE_JUDGE_FUNC:                             /*判断功能码*/
    {
      pCDP_CenApp->RxBuf[pCDP_CenApp->RxLen++] = RxByte;
      pCDP_CenApp->RxState = APP_TO_CEN_RX_STATE_JUDGE_FRAMELEN;     /*功能码，去判断帧长度*/
    }break;

    case APP_TO_CEN_RX_STATE_JUDGE_FRAMELEN:                         /*判断帧长度*/
    {
      pCDP_CenApp->RxBuf[pCDP_CenApp->RxLen++] = RxByte;
      pCDP_CenApp->RxDataLen = RxByte;  
      if(pCDP_CenApp->RxDataLen > 0)
      {
        pCDP_CenApp->RxState = APP_TO_CEN_RX_STATE_RCV_DATA;         /*长度对，去接收数据*/
      }
      else
      {
        pCDP_CenApp->RxState = APP_TO_CEN_RX_STATE_JUDGE_SUMCHECK;   /*没有数据，直接判断累加和校验*/
      }
      
    }break;

    case APP_TO_CEN_RX_STATE_RCV_DATA:                               /*接收数据*/
    {
      pCDP_CenApp->RxBuf[pCDP_CenApp->RxLen++] = RxByte;
      pCDP_CenApp->RxDataLen--;

      if(0 == pCDP_CenApp->RxDataLen)
      {
        pCDP_CenApp->RxState = APP_TO_CEN_RX_STATE_JUDGE_SUMCHECK;   /*接收键值完成，去判断累加和*/
      }
    }break;

    case APP_TO_CEN_RX_STATE_JUDGE_SUMCHECK:                         /*判断累加和校验*/
    {
      sum = 0;
      for(i=0; i<pCDP_CenApp->RxLen; i++)
      {
        sum += pCDP_CenApp->RxBuf[i];
      }
      
      
      if(sum != RxByte) /*校验错，重新搜索命令头================================*/
      {
        pCDP_CenApp->RxState = APP_TO_CEN_RX_STATE_SEARCH_HEAD;     
      }
      else /*帧接收成功==========================================================*/
      {
        pCDP_CenApp->RxBuf[pCDP_CenApp->RxLen++] = RxByte;

        pCDP_CenApp->RxState = APP_TO_CEN_RX_STATE_SEARCH_HEAD;      /*开始下一帧的接收，重新搜索命令头*/
        
        index = BinarySearch(pCDP_CenApp->RxBuf[APP_CDP_OFFSET_FUNC], APP_DATA_OBJ_MANAGE_TAB_NUM, AppDataObjID);
        
        if(INDEX_NO_MATCH == index)                                  /*没有匹配的数据对象ID*/    
        {
          return ;                                                   /*数据处理出错，则放弃后续数据的处理*/
        }
        else
        {
          AppDataObjManageTab[index].pDataHandle();
        }
      }
    }break;

    default:
    {
      pCDP_CenApp->RxState = APP_TO_CEN_RX_STATE_SEARCH_HEAD;    
    }break;
  }
}

/*
************************************************************************************************************************
* 函数名称 : CDP_CenToApp_DataTx                                                                                                         
* 功能描述 : 通信数据包   之   中心板 --> App    数据发送                                                                      
* 输入参数 : 无                                                               
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
void CDP_CenStateTmrToApp_DataTx(Ticker_t ExePeriod)
{
  uint8_t *rp, *rp1, *wp;
  uint8_t  i;
  static uint8_t Order;
  static uint8_t ToAppFrame[20];
  

  memset(&pCDP_CenApp->TxBuf,       0, CEN_TO_CTRL_DATALEN); /*发送前，先清零所有值*/
  
  /*正常操作下发送的数据帧----------------------------------------------------------*/
//  if((SYS_MODE_STANDBY     == pMChair->SysModeCur) ||  
//     (SYS_MODE_USERRUN     == pMChair->SysModeCur) ||  /*这三个模式差别不大，差别在 SysMode_UserRun_Timer()函数中处理*/ 
//     (SYS_MODE_TESTNOTIMER == pMChair->SysModeCur) || 
//     (SYS_MODE_TESTAGE     == pMChair->SysModeCur) )
  {
    pCDP_CenApp->TxBuf.Head     = 0x7B;
    pCDP_CenApp->TxBuf.DataLen  = CEN_TO_CTRL_DATALEN;

    pCDP_CenApp->TxBuf.Byte5.SysRun          = pMChair->CSFlag.Bit.SysRun;
    pCDP_CenApp->TxBuf.Byte5.Pause           = pMChair->CSFlag.Bit.Pause;
    pCDP_CenApp->TxBuf.Byte5.MassageTimeOut  = pMChair->CSFlag.Bit.UserMassageTimeOut;
    pCDP_CenApp->TxBuf.Byte5.VenderOpFinish  = pMChair->CSFlag.Bit.VenderOpFinish;
//    if(pMChair->PromptToneTLMs > ExePeriod)
//    {
//      pMChair->PromptToneTLMs = 0;
//      pCDP_CenApp->TxBuf.Byte5.PromptToneRun = 1;
//    }

    pCDP_CenApp->TxBuf.Byte6.CoreXYZKneadInRun     = pMChair->StateCoreAction.Bit.XYZ.Bit.KneadInRun;
    pCDP_CenApp->TxBuf.Byte6.CoreXYZKneadOutRun    = pMChair->StateCoreAction.Bit.XYZ.Bit.KneadOutRun;
    pCDP_CenApp->TxBuf.Byte6.CoreXYZRollRun        = pMChair->StateCoreAction.Bit.XYZ.Bit.RollRun;
    pCDP_CenApp->TxBuf.Byte6.CoreXYZKneadRun       = pMChair->StateCoreAction.Bit.XYZ.Bit.KneadRun;
    pCDP_CenApp->TxBuf.Byte6.CoreXYZKneadStrokeRun = pMChair->StateCoreAction.Bit.XYZ.Bit.KneadStrokeRun;
    pCDP_CenApp->TxBuf.Byte6.CoreXYZKneadPressRun  = pMChair->StateCoreAction.Bit.XYZ.Bit.KneadPressRun;
    pCDP_CenApp->TxBuf.Byte6.CoreXYZShiaRun        = pMChair->StateCoreAction.Bit.XYZ.Bit.ShiaRun;
    pCDP_CenApp->TxBuf.Byte6.CoreXYZStretchRun     = pMChair->StateCoreAction.Bit.XYZ.Bit.StretchRun;
    pCDP_CenApp->TxBuf.Byte7.CoreTCSClap1Run       = pMChair->StateCoreAction.Bit.TCS.Bit.Clap1Run;
    pCDP_CenApp->TxBuf.Byte7.CoreTCSClap2Run       = pMChair->StateCoreAction.Bit.TCS.Bit.Clap2Run;
    pCDP_CenApp->TxBuf.Byte7.CoreTCSShia1Run       = pMChair->StateCoreAction.Bit.TCS.Bit.Shia1Run;
    pCDP_CenApp->TxBuf.Byte7.CoreTCSShia2Run       = pMChair->StateCoreAction.Bit.TCS.Bit.Shia2Run;
    pCDP_CenApp->TxBuf.Byte7.CoreTCSLTapRun        = pMChair->StateCoreAction.Bit.TCS.Bit.LTapRun;
    pCDP_CenApp->TxBuf.Byte7.CoreTCSTapRun         = pMChair->StateCoreAction.Bit.TCS.Bit.TapRun;
    
    if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core)   /*机芯手动*/
    {
      if((pCDP_CenApp->TxBuf.Byte7.CoreTCSClap1Run) || (pCDP_CenApp->TxBuf.Byte7.CoreTCSClap2Run)||
         (pCDP_CenApp->TxBuf.Byte7.CoreTCSShia1Run) || (pCDP_CenApp->TxBuf.Byte7.CoreTCSShia2Run)||
         (pCDP_CenApp->TxBuf.Byte7.CoreTCSLTapRun)  || (pCDP_CenApp->TxBuf.Byte7.CoreTCSTapRun))
      {
        pCDP_CenApp->TxBuf.Byte6.CoreXYZRollRun = 0;
      }
    }
    
    pCDP_CenApp->TxBuf.Byte8.GasShoulderRun        = pMChair->StateGasPart1.Bit.ShoulderSide;
    pCDP_CenApp->TxBuf.Byte8.GasArmLeftRun         = pMChair->StateGasPart1.Bit.ArmsLB|pMChair->StateGasPart1.Bit.ArmsLF;
    pCDP_CenApp->TxBuf.Byte8.GasArmRightRun        = pMChair->StateGasPart1.Bit.ArmsRB|pMChair->StateGasPart1.Bit.ArmsRF;
    pCDP_CenApp->TxBuf.Byte8.GasSeatRun            = pMChair->StateGasPart1.Bit.SeatSide;
    pCDP_CenApp->TxBuf.Byte8.GasCalvesRun          = pMChair->StateGasPart2.Bit.CalvesBot | pMChair->StateGasPart2.Bit.CalvesSide;
    pCDP_CenApp->TxBuf.Byte8.GasLumbarRun          = pMChair->StateGasPart1.Bit.LumbarSide;
    pCDP_CenApp->TxBuf.Byte8.GasSeatRun            = pMChair->StateGasPart1.Bit.SeatSide;

    pCDP_CenApp->TxBuf.Byte9.BackHeatRun       = pMChair->StateHeat.Bit.LumbarBackWork;
    
    if(CORE_ROLL_RANGE_SPOT == pMChair->StateCore.Bit.RollRange)
    {
      pCDP_CenApp->TxBuf.Byte9.CoreSpotState = 1;
    }
    if(CORE_ROLL_RANGE_PART == pMChair->StateCore.Bit.RollRange)
    {
      pCDP_CenApp->TxBuf.Byte9.CorePartState = 1;
    }
    pCDP_CenApp->TxBuf.Byte9.CalvesRollerRunState = pMChair->StateRoller.Bit.CalvesRun;
    pCDP_CenApp->TxBuf.Byte9.FeetRollerRunState   = pMChair->StateRoller.Bit.FeetRun;
    pCDP_CenApp->TxBuf.Byte9.KeyCalvesRoller      = pMChair->CalvesRollerCtrlSw;//(pMChair->FuncMA_Roller.Bit.Calves == FMA_CALVES_ROLLER_Mannual) ? 1 : 0;
    pCDP_CenApp->TxBuf.Byte9.KeyFeetRoller        = pMChair->FeetRollerCtrlSw;//(pMChair->FuncMA_Roller.Bit.Feet == FMA_FEET_ROLLER_Mannual) ? 1 : 0;

    if((pMChair->ComponentFuncState.Bit.Gas != FUNC_TYPE_NONE)         ||
       (pMChair->FuncMA_Roller.Bit.Calves == FMA_CALVES_ROLLER_Mannual))      
    {
      pCDP_CenApp->TxBuf.Byte10.GasIntensity = pMChair->GasIntensity;
    }

    if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core)   /*机芯手动*/
    {
      pCDP_CenApp->TxBuf.Byte10.MassageIntensity = pMChair->MannualCoreFlexLevel+1;
    }
    else if(FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Core) /*机芯自动*/
    {
      pCDP_CenApp->TxBuf.Byte10.MassageIntensity = pMChair->AutoCoreFlexLevelAdjust;
    }

    if(pMChair->StateCoreAction.Bit.TCS.All > 0)
    {
      pCDP_CenApp->TxBuf.Byte11.TapSpeed = pMChair->MannualCoreTCSActionSpeed;
    }

    if((TRUE == pMChair->StateCoreAction.Bit.XYZ.Bit.KneadInRun)  || 
       (TRUE == pMChair->StateCoreAction.Bit.XYZ.Bit.KneadOutRun) || 
       (TRUE == pMChair->StateCoreAction.Bit.XYZ.Bit.KneadRun)    )
//    if(pMChair->StateCoreAction.Bit.XYZ.All > 0)
    {
      pCDP_CenApp->TxBuf.Byte11.XYZSpeed = pMChair->MannualCoreXYZActionSpeed;
    }

    pCDP_CenApp->TxBuf.Byte12.BackScanRun      = pMChair->StateBodyScan.Bit.Run;
    pCDP_CenApp->TxBuf.Byte12.BackScanFinish   = pMChair->StateBodyScan.Bit.Finish;
    pCDP_CenApp->TxBuf.Byte12.ShoulderAdjustEn = pMChair->StateBodyScan.Bit.ShoulderAdjustEn;

    pCDP_CenApp->TxBuf.Byte13.KeyBackHeat      = pMChair->LumbarBackHeatCtrlSw;//(FMA_LUMBARBACK_HEAT_Mannual == pMChair->FuncMA_Heat.Bit.LumbarBack) ? 1:0;
    pCDP_CenApp->TxBuf.Byte13.KeyGasShoulder   = (FM_GAS_SHOULDER   == pMChair->FuncMannual_Gas.Bit.Shoulder) ? 1:0;
    pCDP_CenApp->TxBuf.Byte13.KeyGasLumbarSeat = (FM_GAS_LUMBARSEAT == pMChair->FuncMannual_Gas.Bit.LumbarSeat) ? 1:0;
    pCDP_CenApp->TxBuf.Byte13.KeyGasArm        = (FM_GAS_ARMS       == pMChair->FuncMannual_Gas.Bit.Arms) ? 1:0;
    pCDP_CenApp->TxBuf.Byte13.KeyGasCalves     = (FM_GAS_CALVES     == pMChair->FuncMannual_Gas.Bit.Calves) ? 1:0;
    pCDP_CenApp->TxBuf.Byte13.KeyGasFull       = (FA_GAS_FullGas    == pMChair->FuncAuto_Gas) ? 1:0;
    pCDP_CenApp->TxBuf.Byte13.KeyGasQuick      = (FA_GAS_QuickGas    == pMChair->FuncAuto_Gas) ? 1:0;

    pCDP_CenApp->TxBuf.Byte14.KeyXYZAction     = pMChair->FuncMannual_Core.Bit.XYZ.All;
    pCDP_CenApp->TxBuf.Byte15.KeyTCSAction     = pMChair->FuncMannual_Core.Bit.TCS.Bit.Action;

    pCDP_CenApp->TxBuf.Byte16.KeyAuto          = pMChair->FuncAuto_CoreGas;

    pCDP_CenApp->TxBuf.Byte18.CoreXPosition = Core_GetXPosition();
    pCDP_CenApp->TxBuf.Byte18.CoreZPosition = Core_GetZPosition();

//    if(KEYVAL_SpikeBackDownFeetUp == pCDP_CenApp->OKeyValAssist)
//    {
//      if((SPIKE_MOVE_BACK_DOWN == pMChair->FuncMannual_Spike.Bit.BackMove) ||
//         (SPIKE_MOVE_FEET_UP   == pMChair->FuncMannual_Spike.Bit.FeetMove) )
//      {
//        pCDP_CenApp->TxBuf.Byte19.KeyBackDownFeetUp = 1;
//      }
//    }
//    else if(KEYVAL_SpikeBackUpFeetDown == pCDP_CenApp->OKeyValAssist)
//    {
//      if((SPIKE_MOVE_BACK_UP   == pMChair->FuncMannual_Spike.Bit.BackMove) ||
//         (SPIKE_MOVE_FEET_DOWN == pMChair->FuncMannual_Spike.Bit.FeetMove) )
//      {
//        pCDP_CenApp->TxBuf.Byte19.KeyBackUpFeetDown = 1;
//      }
//    }
//    else
//    {
//      pCDP_CenApp->TxBuf.Byte19.KeyFeetUp   = (SPIKE_MOVE_FEET_UP   == pMChair->FuncMannual_Spike.Bit.FeetMove) ? 1:0;
//      pCDP_CenApp->TxBuf.Byte19.KeyFeetDown = (SPIKE_MOVE_FEET_DOWN == pMChair->FuncMannual_Spike.Bit.FeetMove) ? 1:0;
//    }    

    pCDP_CenApp->TxBuf.Byte19.KeyBackDownFeetUp = (SPIKE_MOVE_BACK_DOWN    == pMChair->FuncMannual_Spike.Bit.BackMove) ? 1:0;
    pCDP_CenApp->TxBuf.Byte19.KeyBackUpFeetDown = (SPIKE_MOVE_BACK_UP      == pMChair->FuncMannual_Spike.Bit.BackMove) ? 1:0;
    pCDP_CenApp->TxBuf.Byte19.KeyFeetUp         = (SPIKE_MOVE_FEET_UP      == pMChair->FuncMannual_Spike.Bit.FeetMove) ? 1:0;
    pCDP_CenApp->TxBuf.Byte19.KeyFeetDown       = (SPIKE_MOVE_FEET_DOWN    == pMChair->FuncMannual_Spike.Bit.FeetMove) ? 1:0;
    pCDP_CenApp->TxBuf.Byte19.KeyLegExtend      = /*(LEGFLEXSPIKE_DIRECTION_EXTEND   == pMChair->StateLegFlexSpike.Bit.Direction)&&(pMChair->StateLegFlexSpike.Bit.Run);*/(LEGFLEXSPIKE_ACTION_EXTEND == pMChair->FuncMannual_Spike.Bit.LegFlexMove) ? 1:0;    /*小腿1推杆伸中*/                
    pCDP_CenApp->TxBuf.Byte19.KeyLegShorten     = /*(LEGFLEXSPIKE_DIRECTION_SHORTEN  == pMChair->StateLegFlexSpike.Bit.Direction)&&(pMChair->StateLegFlexSpike.Bit.Run);*/(LEGFLEXSPIKE_ACTION_SHORTEN == pMChair->FuncMannual_Spike.Bit.LegFlexMove) ? 1:0;     /*小腿1推杆缩中*/       
    pCDP_CenApp->TxBuf.Byte19.KeyZero2          = (pMChair->FuncAuto_Spike == FA_SPIKE_ZeroGravity2) ? 1 : 0;                        /*零重力1*/  
    pCDP_CenApp->TxBuf.Byte19.KeyZero1          = (pMChair->FuncAuto_Spike == FA_SPIKE_ZeroGravity1) ? 1 : 0;                        /*零重力2*/ 
    pCDP_CenApp->TxBuf.Byte17.KeyHomeReset      = (pMChair->FuncAuto_Spike == FA_SPIKE_Home) ? 1 : 0;                                /*复位*/ 
    if((PBACK_ZERO1_ANGLE == Spike_GetBackAngle()) && (FALSE == pMChair->StateBackSpike.Bit.Work) &&
       (PFEET_ZERO1_ANGLE == Spike_GetFeetAngle()) && (FALSE == pMChair->StateFeetSpike.Bit.Work) )
    {
      pCDP_CenApp->TxBuf.Byte19.KeyZero1 = 1;                     /*零重力*/  
    }
    if((PBACK_ZERO2_ANGLE == Spike_GetBackAngle()) && (FALSE == pMChair->StateBackSpike.Bit.Work) &&
       (PFEET_ZERO2_ANGLE == Spike_GetFeetAngle()) && (FALSE == pMChair->StateFeetSpike.Bit.Work) )
    {
      pCDP_CenApp->TxBuf.Byte19.KeyZero2 = 1;                     /*零重力*/  
    }
    if((PBACK_HOME_ANGLE == Spike_GetBackAngle()) && (FALSE == pMChair->StateBackSpike.Bit.Work) &&
       (PFEET_HOME_ANGLE == Spike_GetFeetAngle()) && (FALSE == pMChair->StateFeetSpike.Bit.Work) )
    {
      pCDP_CenApp->TxBuf.Byte17.KeyHomeReset = 1;                 /*复位*/
    }

    /*以下四个键值在类平板的状态显示，特殊处理*/
    if(SUCCESS == pMChair->CSFlag.Bit.KeyValExeResult)
    {
      if(KEYVAL_CoreWidthDec == pCDP_CenApp->KeyValMap)
      {
        pCDP_CenApp->TxBuf.Byte20.KeyCoreWidthDec = 1;
      }
      else if(KEYVAL_CoreWidthAdd == pCDP_CenApp->KeyValMap)
      {
        pCDP_CenApp->TxBuf.Byte20.KeyCoreWidthAdd = 1;
      }
      else if(KEYVAL_CoreMannualUp == pCDP_CenApp->KeyValMap)
      {
        pCDP_CenApp->TxBuf.Byte20.KeyCoreMannualUp = 1;/*保证 点按的显示*/
      }
      else if(KEYVAL_CoreMannualDown == pCDP_CenApp->KeyValMap)
      {
        pCDP_CenApp->TxBuf.Byte20.KeyCoreMannualDown = 1;/*保证 点按的显示*/
      }
    }
    else
    {
      /*保证 长按的显示*/
      pCDP_CenApp->TxBuf.Byte20.KeyCoreMannualUp   = (CORE_MOVE_ADJUST_ROLL_UP == Core_GetMoveAdjustRoll()) ? 1:0;
      pCDP_CenApp->TxBuf.Byte20.KeyCoreMannualDown = (CORE_MOVE_ADJUST_ROLL_DOWN == Core_GetMoveAdjustRoll()) ? 1:0;
    }

    pCDP_CenApp->TxBuf.Byte20.LedLogoRun = (FMA_LOGO_LED_Mannual == pMChair->FuncMA_Led.Bit.Logo) ? 1:0;
    pCDP_CenApp->TxBuf.Byte20.LedProjectionRun = (FMA_PROJECTION_LED_Mannual == pMChair->FuncMA_Led.Bit.Projection) ? 1:0;
    pCDP_CenApp->TxBuf.Byte20.KeyLed = (FMA_PROJECTION_LED_Mannual == pMChair->FuncMA_Led.Bit.Projection) ? 1:0;
    
    pCDP_CenApp->TxBuf.Byte21.CoreYPosition = Core_GetYPosition();

    pCDP_CenApp->TxBuf.CoreLeftTemp   = Heat_GetLumbarBackLeftTemperature();
    pCDP_CenApp->TxBuf.CoreRightTemp  = Heat_GetLumbarBackRightTemperature();
    pCDP_CenApp->TxBuf.MassageTimeSec = pMChair->UserMassageTimeSec; 
    pCDP_CenApp->TxBuf.MassageTimeMin = pMChair->UserMassageTimeMin; 
    pCDP_CenApp->TxBuf.PromptToneAddr = pMChair->PromptToneAddr;
    
    pCDP_CenApp->TxBuf.Byte27.WIFINetCfgOK = Server_GetCSFlag().WIFIIntCfg;

    if(pMChair->Fault.ReportTLMs > 0) /*上报时间还有剩余*/
    {
      for(i=0; i<10; i++)
      {
        pCDP_CenApp->TxBuf.FaultCodeBit[i] = pMChair->Fault.ReportFlag.All[i];
      }
    }
//    
//    pCDP_CenApp->TxBuf.Byte37.KeyInspectOneself = (SYS_MODE_INSPECTAUTO      == pMChair->SysModeCur) ? 1:0;
//    pCDP_CenApp->TxBuf.Byte37.KeyInspectManual  = (SYS_MODE_INSPECTMANUAL    == pMChair->SysModeCur) ? 1:0;
//    pCDP_CenApp->TxBuf.Byte37.KeyInspectOther1  = (SYS_MODE_INSPECTOTHER1    == pMChair->SysModeCur) ? 1:0;
//    pCDP_CenApp->TxBuf.Byte37.KeyInspectOther2  = (SYS_MODE_INSPECTOTHER2    == pMChair->SysModeCur) ? 1:0;
//    pCDP_CenApp->TxBuf.Byte37.KeyInspectOther3  = (SYS_MODE_INSPECTOTHER3    == pMChair->SysModeCur) ? 1:0;
//    pCDP_CenApp->TxBuf.Byte37.KeyTestNoTimer    = (SYS_MODE_TESTNOTIMER      == pMChair->SysModeCur) ? 1:0;
//    pCDP_CenApp->TxBuf.Byte37.KeyTestSpike      = (SYS_MODE_TESTSPIKE        == pMChair->SysModeCur) ? 1:0;
//    pCDP_CenApp->TxBuf.Byte37.KeyTestAge        = (SYS_MODE_TESTAGE          == pMChair->SysModeCur) ? 1:0;
//    pCDP_CenApp->TxBuf.Byte38.KeyTestOther1     = (SYS_MODE_TESTOTHER1       == pMChair->SysModeCur) ? 1:0;
//    pCDP_CenApp->TxBuf.Byte38.KeyTestOther2     = (SYS_MODE_TESTOTHER2       == pMChair->SysModeCur) ? 1:0;
//    pCDP_CenApp->TxBuf.Byte38.KeyTestOther3     = (SYS_MODE_TESTOTHER3       == pMChair->SysModeCur) ? 1:0;
//    pCDP_CenApp->TxBuf.Byte38.Packing           = (SYS_MODE_PACKING          == pMChair->SysModeCur) ? 1:0;
//    pCDP_CenApp->TxBuf.Byte38.KeyOther1         = (SYS_MODE_OTHER1           == pMChair->SysModeCur) ? 1:0;
//    pCDP_CenApp->TxBuf.Byte38.KeyOther2         = (SYS_MODE_OTHER2           == pMChair->SysModeCur) ? 1:0;
//    pCDP_CenApp->TxBuf.Byte38.KeyOther3         = (SYS_MODE_OTHER3           == pMChair->SysModeCur) ? 1:0;
//    pCDP_CenApp->TxBuf.Byte38.KeyQueryChairInfo = (SYS_MODE_QUERY_CHAIR_INFO == pMChair->SysModeCur) ? 1:0;

//    pCDP_CenApp->TxBuf.KeyValAck = pCDP_CenApp->KeyValRx;

//    rp = (uint8_t *)&pCDP_CenApp->TxBuf;
//    for(i=0; i<(CEN_TO_CTRL_DATALEN-1); i++)
//    {
//      pCDP_CenApp->TxBuf.SumCode += rp[i];
//    }
//    BSP_UART_TxData(CEN_APP_UART_PORT, (uint8_t *)&pCDP_CenApp->TxBuf, CEN_TO_CTRL_DATALEN);
  
  
    if(2 == Order)
    {
      for(i=0; i<10; i++)
      {
        if(pCDP_CenApp->TxBuf.FaultCodeBit[i])
        {
          rp = (uint8_t *)&pCDP_CenApp->TxBuf.FaultCodeBit[0];
          pCDP_CenApp->TxBuf.FuncCode = 0xB8;
          pCDP_CenApp->TxBuf.DataLen  = 10;
          Order++;
          break;
        }
      }
      if(10 == i)
      {
        Order = 0;
      }
    }
    if(0 == Order)
    {
      rp = (uint8_t *)&pCDP_CenApp->TxBuf.Byte5;
      pCDP_CenApp->TxBuf.FuncCode = 0xB1;
      pCDP_CenApp->TxBuf.DataLen  = 15;
      Order++;
    }
    else if(1 == Order) 
    {
      rp = (uint8_t *)&pCDP_CenApp->TxBuf.Byte20;
      pCDP_CenApp->TxBuf.FuncCode = 0xB2;
      pCDP_CenApp->TxBuf.DataLen  = 8;
      Order++;
    }
    
    if(Order > 2)
    {
      Order = 0;
    }

  
    rp1 = (uint8_t *)&pCDP_CenApp->TxBuf;
    wp = ToAppFrame;
    for(i=0; i<3; i++)
    {
      *wp++ = *rp1++;
    }
    
    for(i=0; i<pCDP_CenApp->TxBuf.DataLen; i++)
    {
      *wp++ = *rp++;
    }

    rp = ToAppFrame;
    for(i=0; i<(pCDP_CenApp->TxBuf.DataLen+3); i++)
    {
      pCDP_CenApp->TxBuf.SumCode += ToAppFrame[i];
    }
    *wp++ = pCDP_CenApp->TxBuf.SumCode;
    
    BSP_UART_TxData(CEN_APP_UART_PORT, ToAppFrame, pCDP_CenApp->TxBuf.DataLen+4);
    
  }
  
  pCDP_CenApp->CurCDPType = CDP_TYPE_CTRL;  
}

void CDP_AckTmrToApp_DataTx(Ticker_t ExePeriod)
{
  uint8_t i;
  
  pCDP_CenApp->AckBuf[pCDP_CenApp->AckBuf[APP_CDP_OFFSET_LEN]+3] = 0;
  for(i=0; i<(pCDP_CenApp->AckBuf[APP_CDP_OFFSET_LEN]+3); i++)
  {
    pCDP_CenApp->AckBuf[pCDP_CenApp->AckBuf[APP_CDP_OFFSET_LEN]+3] += pCDP_CenApp->AckBuf[i];
  }
  pCDP_CenApp->CSFlag.Bit.NeedAck = FALSE;
  
  BSP_UART_TxData(CEN_APP_UART_PORT, pCDP_CenApp->AckBuf, pCDP_CenApp->AckBuf[APP_CDP_OFFSET_LEN]+4);
}


/*
************************************************************************************************************************
* 函数名称 : CDP_CenTmrToApp_DataTx                                                                                                         
* 功能描述 : 通信数据包   之   中心板 --> App    数据发送                                                                      
* 输入参数 : 无                                                               
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
void CDP_CenTmrToApp_DataTx(Ticker_t ExePeriod)
{
  if(pCDP_CenApp->CSFlag.Bit.NeedAck)
  {
    CDP_AckTmrToApp_DataTx(ExePeriod);
  }
  else
  {
    CDP_CenStateTmrToApp_DataTx(ExePeriod);
  }
}

//==================================================================================================================
//==================================================================================================================
//==================================================================================================================
//==================================================================================================================
//==================================================================================================================
//==================================================================================================================
//==================================================================================================================
//==================================================================================================================
//==================================================================================================================
//==================================================================================================================
//==================================================================================================================
//==================================================================================================================
//==================================================================================================================






/*
************************************************************************************************************************
* 函数名称 : CDP_CenApp_ByteRx                                                                                                         
* 功能描述 : 通信数据包   之    中心板 <--> App   字节接收处理                                                                              
* 输入参数 : RxByte -- 收到的字节数据                                                                    
* 返回参数 : 无                                                             
* 补充说明 : 该函数必须通过BSP_UART_RegRxByteCB()注册给BSP层，以便在串口接收字节中断中调用。                                                                                                  
************************************************************************************************************************
*/
static void CDP_CenApp_ByteRx(uint8_t RxByte)
{
  uint8_t SrcAddr;
  
  pCDP_CenApp->FrameRx.RxLenMax = CEN_APP_RX_BUF_SIZE;
  
  CDP_AppToCen_AnalyzeApp(RxByte);
  
  SrcAddr = CDP_FrameRxHandle(&pCDP_CenApp->FrameRx, RxByte, CDP_TYPE_NEW_PROTOCOL, CDP_DAP_CEN);
  
}

/*
************************************************************************************************************************
* 函数名称 : CDP_CenApp_DataTx                                                                                                         
* 功能描述 : 通信数据包   之  中心板 <--> App      数据发送                                                                      
* 输入参数 : pTXData -- 要发送的数据   
*            TxLen   -- 发送长度 
* 返回参数 : BSP_UART_TxState_Busy  -- 发送忙，无法处理发送pTxBuf指向的的数据。
*            其他值                 -- 串口开始发送pTxBuf指向的的数据了。
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
uint8_t CDP_CenApp_DataTx(ESF_Evt_t *pEvt)
{
  static uint8_t FrameTxBuf[CEN_APP_TX_BUF_SIZE];

  return CDP_FrameTxHandle(pEvt, FrameTxBuf, CEN_APP_UART_PORT);
}


/*
************************************************************************************************************************
* 函数名称 : CDP_CenApp_FaultCheck                                                                                                         
* 功能描述 : 通信数据包   之   中心板 <--> App   故障检测                                                                        
* 输入参数 : 无                                                             
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
void CDP_CenApp_FaultCheck(Ticker_t ExePeriod)
{
  if(OFF == BSP_IO_GetERPPowerSwState())/*ERP电源关闭，Xxx电源也被关闭，就不做故障判断*/
  {
    pCDP_CenApp->LinkLostTimeMs = 0;                  
    pCDP_CenApp->CSFlag.Bit.LinkLostFault = NORMAL;  
    return; 
  }
  
  if(pCDP_CenApp->LinkLostTimeMs < CEN_APP_LINK_LOST_TIME_THRESHOLD)
  {
    pCDP_CenApp->LinkLostTimeMs += ExePeriod;             
  }
  else
  {
    pCDP_CenApp->CSFlag.Bit.LinkLostFault = FAULT; /*丢失超过门限，则表示链接丢失*/
  }
  
  if(pCDP_CenApp->FrameRx.ByteRxTimeOutMs < 100)
  {
    pCDP_CenApp->FrameRx.ByteRxTimeOutMs += ExePeriod;
  }
}

/*
************************************************************************************************************************
* 函数名称 : CDP_CenApp_Init                                                                                                         
* 功能描述 : 通信数据包   之   App <--> 中心板   初始化                                                                               
* 输入参数 : 无                                                            
* 返回参数 : 返回 可操作的结构体 的指针                                                             
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
CDP_CenApp_t* CDP_CenApp_Init(void)
{
  /*初始化相关数据------------------------------------------*/
  memset(pCDP_CenApp, 0, sizeof(CDP_CenApp_t));
  BSP_UART_RegRxByteCB(CEN_APP_UART_PORT, CDP_CenApp_ByteRx); /*注册串口接收处理函数*/

  return pCDP_CenApp;
}

/*
************************************************************************************************************************
* 函数名称 : CDP_CenApp_GetCSFlag                                                                                                         
* 功能描述 : 获得 控制 与 状态 标识                                                                
* 输入参数 : 无                                                                   
* 返回参数 : 控制与状态标识 的结构体                                                             
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
CDP_CenAppCSFlag_t CDP_CenApp_GetCSFlag(void)
{
  return pCDP_CenApp->CSFlag;
}
