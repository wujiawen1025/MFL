/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: CDP_CenXxx.c                                                                                                         
**
**    功能描述: 通信数据包   之   手控器 机芯板 小腿板 侧板 <--> 中心板。
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
#include "CDP_CenXxx.h"
#include "CDP.h"
#include "MChair.h"


/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/
#define  CEN_Xxx_RX_BUF_SIZE                  (ESF_MEM_BOLCK_BYTE_SIZE - (ESF_MEM_BOLCK_BYTE_SIZE/4)) /*接收缓存大小，最多占内存块的3/4*/
#define  CEN_Xxx_TX_BUF_SIZE                  (CEN_Xxx_RX_BUF_SIZE)                                  /*发送缓存大小*/
#define  CEN_Xxx_UART_PORT                    BSP_UART_Port1                                          /*所用串口*/

#define  CEN_Xxx_LINK_LOST_TIME_THRESHOLD     4000                                                    /*通信链接丢失时间门限*/

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
static CDP_CenXxx_t CDP_CenXxx;
CDP_CenXxx_t *pCDP_CenXxx = &CDP_CenXxx;

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
* 函数名称 : CDP_CtrlToCen_AnalyzeCtrl                                                                                                         
* 功能描述 : 通信数据包   之   手控器 --> 中心板   控制命令解析                                                          
* 输入参数 : RxByte -- 收到的字节数据                                                                    
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
void CDP_CtrlToCen_AnalyzeCtrl(uint8_t RxByte)
{
  uint8_t i;
  uint8_t sum;
  ESF_Evt_t *pEvt;

  switch(pCDP_CenXxx->ORxState)
  {
    case CTRL_TO_CEN_RX_STATE_SEARCH_HEAD:                            /*搜索起始码*/
    {
      pCDP_CenXxx->ORxLen = 0;
      if(CTRL_TO_CEN_HEAD == RxByte)
      {
        pCDP_CenXxx->ORxBuf[pCDP_CenXxx->ORxLen++] = RxByte;
        pCDP_CenXxx->ORxState = CTRL_TO_CEN_RX_STATE_JUDGE_ADDR;      /*收到起始码，则去判断地址*/
      }
    }break;

    case CTRL_TO_CEN_RX_STATE_JUDGE_ADDR:                             /*判断地址*/
    {
      if(CTRL_TO_CEN_ADDR == RxByte) 
      {
        pCDP_CenXxx->ORxBuf[pCDP_CenXxx->ORxLen++] = RxByte;
        pCDP_CenXxx->ORxState = CTRL_TO_CEN_RX_STATE_JUDGE_FUNC;      /*地址对，去判断功能码*/
      }
      else
      {
       pCDP_CenXxx->ORxState = CTRL_TO_CEN_RX_STATE_SEARCH_HEAD;      /*地址错，重新搜索命令头*/
      }  
    }break;

    case CTRL_TO_CEN_RX_STATE_JUDGE_FUNC:                             /*判断功能码*/
    {
      if(CTRL_TO_CEN_FUNC == RxByte)
      {
        pCDP_CenXxx->ORxBuf[pCDP_CenXxx->ORxLen++] = RxByte;
        pCDP_CenXxx->ORxState = CTRL_TO_CEN_RX_STATE_JUDGE_FRAMELEN;  /*功能码，去判断帧长度*/
      }
      else
      {
       pCDP_CenXxx->ORxState = CTRL_TO_CEN_RX_STATE_SEARCH_HEAD;      /*功能码错，重新搜索命令头*/
      }  
    }break;

    case CTRL_TO_CEN_RX_STATE_JUDGE_FRAMELEN:                         /*判断帧长度*/
    {
      if(CTRL_TO_CEN_FRAMELEN == RxByte)
      {
        pCDP_CenXxx->ORxBuf[pCDP_CenXxx->ORxLen++] = RxByte;
        pCDP_CenXxx->ORxState = CTRL_TO_CEN_RX_STATE_RCV_DATA;        /*长度对，去接收数据*/
        pCDP_CenXxx->ORxDataLen = 0;
      }
      else
      {
       pCDP_CenXxx->ORxState = CTRL_TO_CEN_RX_STATE_SEARCH_HEAD;      /*长度错，重新搜索命令头*/
      }  
    }break;

    case CTRL_TO_CEN_RX_STATE_RCV_DATA:                               /*接收数据*/
    {
      pCDP_CenXxx->ORxBuf[pCDP_CenXxx->ORxLen++] = RxByte;
      pCDP_CenXxx->ORxDataLen++;

      if(pCDP_CenXxx->ORxDataLen >= CTRL_TO_CEN_DATALEN)
      {
        pCDP_CenXxx->ORxState = CTRL_TO_CEN_RX_STATE_JUDGE_SUMCHECK;  /*接收键值完成，去判断累加和*/
      }
    }break;

    case CTRL_TO_CEN_RX_STATE_JUDGE_SUMCHECK:                         /*判断累加和校验*/
    {
      sum = 0;
      for(i=0; i<pCDP_CenXxx->ORxLen; i++)
      {
        sum += pCDP_CenXxx->ORxBuf[i];
      }

      if(sum != RxByte) /*校验错，重新搜索命令头================================*/
      {
        pCDP_CenXxx->ORxState = CTRL_TO_CEN_RX_STATE_SEARCH_HEAD;     
      }
      else /*帧接收成功==========================================================*/
      {
        pCDP_CenXxx->ORxBuf[pCDP_CenXxx->ORxLen++] = RxByte;
        pCDP_CenXxx->CtrlLinkLostTimeMs = 0;                                            /*清链接丢失时间*/ 
        pCDP_CenXxx->CSFlag.Bit.CtrlLinkLostFault = NORMAL;  
 
        pCDP_CenXxx->OKeyValRx = pCDP_CenXxx->ORxBuf[CTRL_TO_CEN_DATA_OFFSET];
//        if((pCDP_CenXxx->KeyValRx < TAB_NUM(KeyValMapTab)) && (pCDP_CenXxx->KeyValRx != 0))
//        {
//          pCDP_CenXxx->KeyValMap = KeyValMapTab[pCDP_CenXxx->KeyValRx];
//        }
//        else
//        {
//          pCDP_CenXxx->KeyValMap = pCDP_CenXxx->KeyValRx;
//          if(0xFF == pCDP_CenXxx->KeyValRx)
//          {
//            pCDP_CenXxx->CSFlag.Bit.CtrlKeyLongPress = TRUE;         /*有按键长按*/
//          }
//        }
        pCDP_CenXxx->OKeyValMap = pCDP_CenXxx->OKeyValRx;
        if((pCDP_CenXxx->OKeyValMap != 0xff) && (pCDP_CenXxx->OKeyValMap != 0x00))
        {
          pCDP_CenXxx->OKeyValAssist = pCDP_CenXxx->OKeyValMap;     /*记录辅助键值*/
        }

        pEvt = ESF_MemBuf_Get();                                      /*申请事件内存块*/
        if(pEvt != NULL)                                              /*申请成功*/ 
        {
          pEvt->Type = EvtCDPRx;
          pEvt->Arg.CDPRx.CDPType = CDP_TYPE_OLD_PROTOCOL;            /*旧协议*/
          pEvt->Arg.CDPRx.pRxBuf = (uint8_t*)pEvt->AppendData;
          memcpy(pEvt->Arg.CDPRx.pRxBuf, &pCDP_CenXxx->ORxBuf[CTRL_TO_CEN_DATA_OFFSET], CTRL_TO_CEN_DATALEN);
          pEvt->Arg.CDPRx.pRxBuf[0] = pCDP_CenXxx->OKeyValMap;        /*键值修正到映射后的值*/   
          pEvt->Arg.CDPRx.RxLen = CTRL_TO_CEN_DATALEN;
          ESF_EvtQuene_Post(pEvt);                                    /*投递事件*/        
        }

        pCDP_CenXxx->ORxState = CTRL_TO_CEN_RX_STATE_SEARCH_HEAD;     /*开始下一帧的接收，重新搜索命令头*/
      }
    }break;

    default:
    {
      pCDP_CenXxx->ORxState = CTRL_TO_CEN_RX_STATE_SEARCH_HEAD;    
    }break;
  }
}

/*
************************************************************************************************************************
* 函数名称 : CDP_CenToCtrl_DataTx                                                                                                         
* 功能描述 : 通信数据包   之   中心板 --> 手控器    数据发送                                                                      
* 输入参数 : 无                                                               
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
void CDP_CenStateTmrToCtrl_DataTx(Ticker_t ExePeriod)
{
  uint8_t *rp;
  uint8_t  i;


  memset(&pCDP_CenXxx->TxBuf,       0, CEN_TO_CTRL_DATALEN); /*发送前，先清零所有值*/
  memset(&pCDP_CenXxx->VenderTxBuf, 0, CEN_TO_CTRL_VENDER_DATALEN); /*发送前，先清零所有值*/
  
  /*正常操作下发送的数据帧----------------------------------------------------------*/
//  if((SYS_MODE_STANDBY     == pMChair->SysModeCur) ||  
//     (SYS_MODE_USERRUN     == pMChair->SysModeCur) ||  /*这三个模式差别不大，差别在 SysMode_UserRun_Timer()函数中处理*/ 
//     (SYS_MODE_TESTNOTIMER == pMChair->SysModeCur) || 
//     (SYS_MODE_TESTAGE     == pMChair->SysModeCur) )
  {
    pCDP_CenXxx->TxBuf.Head     = CEN_TO_CTRL_HEAD;
    pCDP_CenXxx->TxBuf.Addr     = CEN_TO_CTRL_ADDR;
    pCDP_CenXxx->TxBuf.FuncCode = CEN_TO_CTRL_FUNC;
    pCDP_CenXxx->TxBuf.DataLen  = CEN_TO_CTRL_DATALEN;

    pCDP_CenXxx->TxBuf.Byte5.SysRun          = pMChair->CSFlag.Bit.SysRun;
    pCDP_CenXxx->TxBuf.Byte5.Pause           = pMChair->CSFlag.Bit.Pause;
    pCDP_CenXxx->TxBuf.Byte5.MassageTimeOut  = pMChair->CSFlag.Bit.UserMassageTimeOut;
    pCDP_CenXxx->TxBuf.Byte5.VenderOpFinish  = pMChair->CSFlag.Bit.VenderOpFinish;
    pCDP_CenXxx->TxBuf.Byte5.BluetoothSwitch = pMChair->CSFlag.Bit.BluetoothSwitch;
    if(pMChair->PromptToneTLMs > ExePeriod)
    {
      pMChair->PromptToneTLMs = 0;
      pCDP_CenXxx->TxBuf.Byte5.PromptToneRun = 1;
    }

    pCDP_CenXxx->TxBuf.Byte6.CoreXYZKneadInRun     = pMChair->StateCoreAction.Bit.XYZ.Bit.KneadInRun;
    pCDP_CenXxx->TxBuf.Byte6.CoreXYZKneadOutRun    = pMChair->StateCoreAction.Bit.XYZ.Bit.KneadOutRun;
    pCDP_CenXxx->TxBuf.Byte6.CoreXYZRollRun        = pMChair->StateCoreAction.Bit.XYZ.Bit.RollRun;
    pCDP_CenXxx->TxBuf.Byte6.CoreXYZKneadRun       = pMChair->StateCoreAction.Bit.XYZ.Bit.KneadRun;
    pCDP_CenXxx->TxBuf.Byte6.CoreXYZKneadStrokeRun = pMChair->StateCoreAction.Bit.XYZ.Bit.KneadStrokeRun;
    pCDP_CenXxx->TxBuf.Byte6.CoreXYZKneadPressRun  = pMChair->StateCoreAction.Bit.XYZ.Bit.KneadPressRun;
    pCDP_CenXxx->TxBuf.Byte6.CoreXYZShiaRun        = pMChair->StateCoreAction.Bit.XYZ.Bit.ShiaRun;
    pCDP_CenXxx->TxBuf.Byte6.CoreXYZStretchRun     = pMChair->StateCoreAction.Bit.XYZ.Bit.StretchRun;
    pCDP_CenXxx->TxBuf.Byte7.CoreTCSClap1Run       = pMChair->StateCoreAction.Bit.TCS.Bit.Clap1Run;
    pCDP_CenXxx->TxBuf.Byte7.CoreTCSClap2Run       = pMChair->StateCoreAction.Bit.TCS.Bit.Clap2Run;
    pCDP_CenXxx->TxBuf.Byte7.CoreTCSShia1Run       = pMChair->StateCoreAction.Bit.TCS.Bit.Shia1Run;
    pCDP_CenXxx->TxBuf.Byte7.CoreTCSShia2Run       = pMChair->StateCoreAction.Bit.TCS.Bit.Shia2Run;
    pCDP_CenXxx->TxBuf.Byte7.CoreTCSLTapRun        = pMChair->StateCoreAction.Bit.TCS.Bit.LTapRun;
    pCDP_CenXxx->TxBuf.Byte7.CoreTCSTapRun         = pMChair->StateCoreAction.Bit.TCS.Bit.TapRun;
		
    if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core)   /*机芯手动*/
		{
			if((pCDP_CenXxx->TxBuf.Byte7.CoreTCSClap1Run) || (pCDP_CenXxx->TxBuf.Byte7.CoreTCSClap2Run)||
			   (pCDP_CenXxx->TxBuf.Byte7.CoreTCSShia1Run) || (pCDP_CenXxx->TxBuf.Byte7.CoreTCSShia2Run)||
			   (pCDP_CenXxx->TxBuf.Byte7.CoreTCSLTapRun)  || (pCDP_CenXxx->TxBuf.Byte7.CoreTCSTapRun))
			{
				pCDP_CenXxx->TxBuf.Byte6.CoreXYZRollRun = 0;
			}
		}
		
    pCDP_CenXxx->TxBuf.Byte8.GasShoulderRun        = pMChair->StateGasPart1.Bit.ShoulderSide;
    pCDP_CenXxx->TxBuf.Byte8.GasArmLeftRun         = pMChair->StateGasPart1.Bit.ArmsLB|pMChair->StateGasPart1.Bit.ArmsLF;
    pCDP_CenXxx->TxBuf.Byte8.GasArmRightRun        = pMChair->StateGasPart1.Bit.ArmsRB|pMChair->StateGasPart1.Bit.ArmsRF;
    pCDP_CenXxx->TxBuf.Byte8.GasSeatRun            = pMChair->StateGasPart1.Bit.SeatSide;
    pCDP_CenXxx->TxBuf.Byte8.GasCalvesRun          = pMChair->StateGasPart2.Bit.CalvesBot | 
                                                     pMChair->StateGasPart2.Bit.CalvesSide;
//    pCDP_CenXxx->TxBuf.Byte8.GasLumbarRun          = pMChair->StateGasPart1.Bit.LumbarSide;
    pCDP_CenXxx->TxBuf.Byte8.GasSeatRun            = pMChair->StateGasPart1.Bit.SeatSide;

    pCDP_CenXxx->TxBuf.Byte9.BackHeatRun       = pMChair->StateHeat.Bit.LumbarBackWork;
    
    if(CORE_ROLL_RANGE_SPOT == pMChair->StateCore.Bit.RollRange)
    {
      pCDP_CenXxx->TxBuf.Byte9.CoreSpotState = 1;
    }
    if(CORE_ROLL_RANGE_PART == pMChair->StateCore.Bit.RollRange)
    {
      pCDP_CenXxx->TxBuf.Byte9.CorePartState = 1;
    }
    pCDP_CenXxx->TxBuf.Byte9.CalvesRollerRunState = pMChair->StateRoller.Bit.CalvesRun;
    pCDP_CenXxx->TxBuf.Byte9.FeetRollerRunState   = pMChair->StateRoller.Bit.FeetRun;
    pCDP_CenXxx->TxBuf.Byte9.KeyCalvesRoller      = pMChair->CalvesRollerCtrlSw;//(pMChair->FuncMA_Roller.Bit.Calves == FMA_CALVES_ROLLER_Mannual) ? 1 : 0;
    pCDP_CenXxx->TxBuf.Byte9.KeyFeetRoller        = pMChair->FeetRollerCtrlSw;//(pMChair->FuncMA_Roller.Bit.Feet == FMA_FEET_ROLLER_Mannual) ? 1 : 0;

    if((pMChair->ComponentFuncState.Bit.Gas != FUNC_TYPE_NONE)         ||
       (pMChair->FuncMA_Roller.Bit.Calves == FMA_CALVES_ROLLER_Mannual))      
    {
      pCDP_CenXxx->TxBuf.Byte10.GasIntensity = pMChair->GasIntensity;
    }

    if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core)   /*机芯手动*/
    {
      pCDP_CenXxx->TxBuf.Byte10.MassageIntensity = pMChair->MannualCoreFlexLevel+1;
    }
    else if(FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Core) /*机芯自动*/
    {
      pCDP_CenXxx->TxBuf.Byte10.MassageIntensity = pMChair->AutoCoreFlexLevelAdjust;
    }

    if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core)   /*机芯手动*/
    {
      if(pMChair->StateCoreAction.Bit.TCS.All > 0)
      {
        pCDP_CenXxx->TxBuf.Byte11.TapSpeed = pMChair->MannualCoreTCSActionSpeed;
      }

      if((TRUE == pMChair->StateCoreAction.Bit.XYZ.Bit.KneadInRun)  || 
         (TRUE == pMChair->StateCoreAction.Bit.XYZ.Bit.KneadOutRun) || 
         (TRUE == pMChair->StateCoreAction.Bit.XYZ.Bit.KneadRun)    )
//      if((pMChair->StateCoreAction.Bit.XYZ.All > 0)                      &&
//         (MChair_GetFuncCoreMannualXYZSpeedMax() > XYZ_ACTION_SPEED_MIN) )
      {
        pCDP_CenXxx->TxBuf.Byte11.XYZSpeed = pMChair->MannualCoreXYZActionSpeed;
      }    
    }

    pCDP_CenXxx->TxBuf.Byte12.BackScanRun      = pMChair->StateBodyScan.Bit.Run;
    pCDP_CenXxx->TxBuf.Byte12.BackScanFinish   = pMChair->StateBodyScan.Bit.Finish;
    pCDP_CenXxx->TxBuf.Byte12.ShoulderAdjustEn = pMChair->StateBodyScan.Bit.ShoulderAdjustEn;

    pCDP_CenXxx->TxBuf.Byte13.KeyBackHeat      = pMChair->LumbarBackHeatCtrlSw;//(FMA_LUMBARBACK_HEAT_Mannual == pMChair->FuncMA_Heat.Bit.LumbarBack) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte13.KeyGasShoulder   = (FM_GAS_SHOULDER   == pMChair->FuncMannual_Gas.Bit.Shoulder) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte13.KeyGasLumbarSeat = (FM_GAS_LUMBARSEAT == pMChair->FuncMannual_Gas.Bit.LumbarSeat) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte13.KeyGasArm        = (FM_GAS_ARMS       == pMChair->FuncMannual_Gas.Bit.Arms) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte13.KeyGasCalves     = (FM_GAS_CALVES     == pMChair->FuncMannual_Gas.Bit.Calves) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte13.KeyGasFull       = (FA_GAS_FullGas    == pMChair->FuncAuto_Gas) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte13.KeyGasQuick      = (FA_GAS_QuickGas    == pMChair->FuncAuto_Gas) ? 1:0;

    pCDP_CenXxx->TxBuf.Byte14.KeyXYZAction     = pMChair->FuncMannual_Core.Bit.XYZ.All;
    pCDP_CenXxx->TxBuf.Byte15.KeyTCSAction     = pMChair->FuncMannual_Core.Bit.TCS.Bit.Action;

    pCDP_CenXxx->TxBuf.Byte16.KeyAuto          = pMChair->FuncAuto_CoreGas;

    pCDP_CenXxx->TxBuf.Byte18.CoreXPosition = Core_GetXPosition();
    pCDP_CenXxx->TxBuf.Byte18.CoreZPosition = Core_GetZPosition();

//    if(KEYVAL_SpikeBackDownFeetUp == pCDP_CenXxx->OKeyValAssist)
//    {
//      if((SPIKE_MOVE_BACK_DOWN == pMChair->FuncMannual_Spike.Bit.BackMove) ||
//         (SPIKE_MOVE_FEET_UP   == pMChair->FuncMannual_Spike.Bit.FeetMove) )
//      {
//        pCDP_CenXxx->TxBuf.Byte19.KeyBackDownFeetUp = 1;
//      }
//    }
//    else if(KEYVAL_SpikeBackUpFeetDown == pCDP_CenXxx->OKeyValAssist)
//    {
//      if((SPIKE_MOVE_BACK_UP   == pMChair->FuncMannual_Spike.Bit.BackMove) ||
//         (SPIKE_MOVE_FEET_DOWN == pMChair->FuncMannual_Spike.Bit.FeetMove) )
//      {
//        pCDP_CenXxx->TxBuf.Byte19.KeyBackUpFeetDown = 1;
//      }
//    }
//    else
//    {
//      pCDP_CenXxx->TxBuf.Byte19.KeyFeetUp   = (SPIKE_MOVE_FEET_UP   == pMChair->FuncMannual_Spike.Bit.FeetMove) ? 1:0;
//      pCDP_CenXxx->TxBuf.Byte19.KeyFeetDown = (SPIKE_MOVE_FEET_DOWN == pMChair->FuncMannual_Spike.Bit.FeetMove) ? 1:0;
//    }    
    pCDP_CenXxx->TxBuf.Byte19.KeyBackDownFeetUp = (SPIKE_MOVE_BACK_DOWN    == pMChair->FuncMannual_Spike.Bit.BackMove) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte19.KeyBackUpFeetDown = (SPIKE_MOVE_BACK_UP      == pMChair->FuncMannual_Spike.Bit.BackMove) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte19.KeyFeetUp         = (SPIKE_MOVE_FEET_UP      == pMChair->FuncMannual_Spike.Bit.FeetMove) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte19.KeyFeetDown       = (SPIKE_MOVE_FEET_DOWN    == pMChair->FuncMannual_Spike.Bit.FeetMove) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte19.KeyLegExtend      = (SPIKE_MOVE_LEG_EXTEND   == pMChair->FuncMannual_Spike.Bit.LegFlexMove) ? 1:0;     /*小腿1推杆伸中*/                
    pCDP_CenXxx->TxBuf.Byte19.KeyLegShorten     = (SPIKE_MOVE_LEG_SHORT    == pMChair->FuncMannual_Spike.Bit.LegFlexMove) ? 1:0;     /*小腿1推杆缩中*/       
    pCDP_CenXxx->TxBuf.Byte19.KeyZero2          = (pMChair->FuncAuto_Spike == FA_SPIKE_ZeroGravity2) ? 1 : 0;                        /*零重力1*/  
    pCDP_CenXxx->TxBuf.Byte19.KeyZero1          = (pMChair->FuncAuto_Spike == FA_SPIKE_ZeroGravity1) ? 1 : 0;                        /*零重力2*/  
    if((PBACK_ZERO1_ANGLE == Spike_GetBackAngle()) && (FALSE == pMChair->StateBackSpike.Bit.Work) &&
       (PFEET_ZERO1_ANGLE == Spike_GetFeetAngle()) && (FALSE == pMChair->StateFeetSpike.Bit.Work) )
    {
        pCDP_CenXxx->TxBuf.Byte19.KeyZero1 = 1;                     /*零重力*/  
    }
    if((PBACK_ZERO2_ANGLE == Spike_GetBackAngle()) && (FALSE == pMChair->StateBackSpike.Bit.Work) &&
       (PFEET_ZERO2_ANGLE == Spike_GetFeetAngle()) && (FALSE == pMChair->StateFeetSpike.Bit.Work) )
    {
        pCDP_CenXxx->TxBuf.Byte19.KeyZero2 = 1;                     /*零重力*/  
    }


    /*以下四个键值在类平板的状态显示，特殊处理*/
    if(SUCCESS == pMChair->CSFlag.Bit.KeyValExeResult)
    {
      if(KEYVAL_CoreWidthDec == pCDP_CenXxx->OKeyValMap)
      {
        pCDP_CenXxx->TxBuf.Byte20.KeyCoreWidthDec = 1;
      }
      else if(KEYVAL_CoreWidthAdd == pCDP_CenXxx->OKeyValMap)
      {
        pCDP_CenXxx->TxBuf.Byte20.KeyCoreWidthAdd = 1;
      }
      else if(KEYVAL_CoreMannualUp == pCDP_CenXxx->OKeyValMap)
      {
        pCDP_CenXxx->TxBuf.Byte20.KeyCoreMannualUp = 1;/*保证 点按的显示*/
      }
      else if(KEYVAL_CoreMannualDown == pCDP_CenXxx->OKeyValMap)
      {
        pCDP_CenXxx->TxBuf.Byte20.KeyCoreMannualDown = 1;/*保证 点按的显示*/
      }
    }
    else
    {
      /*保证 长按的显示*/
      pCDP_CenXxx->TxBuf.Byte20.KeyCoreMannualUp   = (CORE_MOVE_ADJUST_ROLL_UP == Core_GetMoveAdjustRoll()) ? 1:0;
      pCDP_CenXxx->TxBuf.Byte20.KeyCoreMannualDown = (CORE_MOVE_ADJUST_ROLL_DOWN == Core_GetMoveAdjustRoll()) ? 1:0;
    }

    pCDP_CenXxx->TxBuf.Byte20.LedLogoRun = (FMA_LOGO_LED_Mannual == pMChair->FuncMA_Led.Bit.Logo) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte20.LedProjectionRun = (FMA_PROJECTION_LED_Mannual == pMChair->FuncMA_Led.Bit.Projection) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte20.KeyLed = (FMA_PROJECTION_LED_Mannual == pMChair->FuncMA_Led.Bit.Logo) ? 1:0;
    
    pCDP_CenXxx->TxBuf.Byte21.CoreYPosition = Core_GetYPosition();

    pCDP_CenXxx->TxBuf.CoreLeftTemp   = Heat_GetLumbarBackLeftTemperature();
    pCDP_CenXxx->TxBuf.CoreRightTemp  = Heat_GetLumbarBackRightTemperature();
    pCDP_CenXxx->TxBuf.MassageTimeSec = pMChair->UserMassageTimeSec; 
    pCDP_CenXxx->TxBuf.MassageTimeMin = pMChair->UserMassageTimeMin; 
    pCDP_CenXxx->TxBuf.PromptToneAddr = pMChair->PromptToneAddr;

    if(pMChair->Fault.ReportTLMs > 0) /*上报时间还有剩余*/
    {
      for(i=0; i<10; i++)
      {
        pCDP_CenXxx->TxBuf.FaultCodeBit[i] = pMChair->Fault.ReportFlag.All[i];
      }
    }
    
    pCDP_CenXxx->TxBuf.Byte37.KeyInspectOneself = (SYS_MODE_INSPECTAUTO      == pMChair->SysModeCur) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte37.KeyInspectManual  = (SYS_MODE_INSPECTMANUAL    == pMChair->SysModeCur) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte37.KeyInspectOther1  = (SYS_MODE_INSPECTOTHER1    == pMChair->SysModeCur) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte37.KeyInspectOther2  = (SYS_MODE_INSPECTOTHER2    == pMChair->SysModeCur) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte37.KeyInspectOther3  = (SYS_MODE_INSPECTOTHER3    == pMChair->SysModeCur) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte37.KeyTestNoTimer    = (SYS_MODE_TESTNOTIMER      == pMChair->SysModeCur) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte37.KeyTestSpike      = (SYS_MODE_TESTSPIKE        == pMChair->SysModeCur) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte37.KeyTestAge        = (SYS_MODE_TESTAGE          == pMChair->SysModeCur) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte38.KeyTestOther1     = (SYS_MODE_TESTOTHER1       == pMChair->SysModeCur) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte38.KeyTestOther2     = (SYS_MODE_TESTOTHER2       == pMChair->SysModeCur) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte38.KeyTestOther3     = (SYS_MODE_TESTOTHER3       == pMChair->SysModeCur) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte38.Packing           = (SYS_MODE_PACKING          == pMChair->SysModeCur) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte38.KeyOther1         = (SYS_MODE_OTHER1           == pMChair->SysModeCur) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte38.KeyOther2         = (SYS_MODE_OTHER2           == pMChair->SysModeCur) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte38.KeyOther3         = (SYS_MODE_OTHER3           == pMChair->SysModeCur) ? 1:0;
    pCDP_CenXxx->TxBuf.Byte38.KeyQueryChairInfo = (SYS_MODE_QUERY_CHAIR_INFO == pMChair->SysModeCur) ? 1:0;

    pCDP_CenXxx->TxBuf.KeyValAck = pCDP_CenXxx->OKeyValRx;

    rp = (uint8_t *)&pCDP_CenXxx->TxBuf;
    for(i=0; i<(CEN_TO_CTRL_DATALEN-1); i++)
    {
      pCDP_CenXxx->TxBuf.SumCode += rp[i];
    }
    BSP_UART_TxData(CEN_Xxx_UART_PORT, (uint8_t *)&pCDP_CenXxx->TxBuf, CEN_TO_CTRL_DATALEN);
  }

  pCDP_CenXxx->CurCDPType = CDP_TYPE_CTRL;  
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
* 函数名称 : CDP_CenXxx_ByteRx                                                                                                         
* 功能描述 : 通信数据包   之    中心板 <--> 手控器   字节接收处理                                                                              
* 输入参数 : RxByte -- 收到的字节数据                                                                    
* 返回参数 : 无                                                             
* 补充说明 : 该函数必须通过BSP_UART_RegRxByteCB()注册给BSP层，以便在串口接收字节中断中调用。                                                                                                  
************************************************************************************************************************
*/
static void CDP_CenXxx_ByteRx(uint8_t RxByte)
{
  uint8_t SrcAddr;

  CDP_CtrlToCen_AnalyzeCtrl(RxByte);
  
  pCDP_CenXxx->FrameRx.RxLenMax = CEN_Xxx_RX_BUF_SIZE;
  SrcAddr = CDP_FrameRxHandle(&pCDP_CenXxx->FrameRx, RxByte, CDP_TYPE_NEW_PROTOCOL, CDP_DAP_CEN);
  
  if(CDP_ADDR_CORE == SrcAddr)                            
  {
    pCDP_CenXxx->CoreLinkLostTimeMs = 0;                                     /*清链接丢失时间*/ 
    pCDP_CenXxx->CSFlag.Bit.CoreLinkLostFault = NORMAL;  
  }
  else if(CDP_ADDR_CALVES_FEET == SrcAddr)
  {
    pCDP_CenXxx->CalvesFeetLinkLostTimeMs = 0;                               /*清链接丢失时间*/ 
    pCDP_CenXxx->CSFlag.Bit.CalvesFeetLinkLostFault = NORMAL;  
  }
  else if(CDP_ADDR_CTR_SIDE == SrcAddr)
  {
    pCDP_CenXxx->SideCtrlLinkLostTimeMs = 0;                                 /*清链接丢失时间*/ 
    pCDP_CenXxx->CSFlag.Bit.SideCtrlLinkLostFault = NORMAL;  
  }
}

/*
************************************************************************************************************************
* 函数名称 : CDP_CenCtrl_DataTx                                                                                                         
* 功能描述 : 通信数据包   之  中心板 <--> Ctrl      数据发送                                                                      
* 输入参数 : pTXData -- 要发送的数据   
*            TxLen   -- 发送长度 
* 返回参数 : BSP_UART_TxState_Busy  -- 发送忙，无法处理发送pTxBuf指向的的数据。
*            其他值                 -- 串口开始发送pTxBuf指向的的数据了。
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
uint8_t CDP_CenXxx_DataTx(ESF_Evt_t *pEvt)
{
  static uint8_t FrameTxBuf[CEN_Xxx_TX_BUF_SIZE];

  return CDP_FrameTxHandle(pEvt, FrameTxBuf, CEN_Xxx_UART_PORT);
}


/*
************************************************************************************************************************
* 函数名称 : CDP_CenXxx_FaultCheck                                                                                                         
* 功能描述 : 通信数据包   之   中心板 <--> Ctrl   故障检测                                                                        
* 输入参数 : 无                                                             
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
void CDP_CenXxx_FaultCheck(Ticker_t ExePeriod)
{
  if(OFF == BSP_IO_GetERPPowerSwState())/*ERP电源关闭，Xxx电源也被关闭，就不做故障判断*/
  {
    pCDP_CenXxx->CtrlLinkLostTimeMs = 0;                  
    pCDP_CenXxx->CSFlag.Bit.CtrlLinkLostFault = NORMAL;  
    pCDP_CenXxx->CoreLinkLostTimeMs = 0;                  
    pCDP_CenXxx->CSFlag.Bit.CoreLinkLostFault = NORMAL;  
    pCDP_CenXxx->CalvesFeetLinkLostTimeMs = 0; 
    pCDP_CenXxx->CSFlag.Bit.CalvesFeetLinkLostFault = NORMAL; 
    pCDP_CenXxx->SideCtrlLinkLostTimeMs = 0;                               
    pCDP_CenXxx->CSFlag.Bit.SideCtrlLinkLostFault = NORMAL;  
    return; 
  }
  
  if(pCDP_CenXxx->CtrlLinkLostTimeMs < CEN_Xxx_LINK_LOST_TIME_THRESHOLD)
  {
    pCDP_CenXxx->CtrlLinkLostTimeMs += ExePeriod;             
  }
  else
  {
    pCDP_CenXxx->CSFlag.Bit.CtrlLinkLostFault = FAULT; /*丢失超过门限，则表示链接丢失*/
  }
  if(pCDP_CenXxx->CoreLinkLostTimeMs < CEN_Xxx_LINK_LOST_TIME_THRESHOLD)
  {
    pCDP_CenXxx->CoreLinkLostTimeMs += ExePeriod;             
  }
  else
  {
    pCDP_CenXxx->CSFlag.Bit.CoreLinkLostFault = FAULT; /*丢失超过门限，则表示链接丢失*/
  }

  if(pCDP_CenXxx->CalvesFeetLinkLostTimeMs < CEN_Xxx_LINK_LOST_TIME_THRESHOLD)
  {
    pCDP_CenXxx->CalvesFeetLinkLostTimeMs += ExePeriod;             
  }
  else
  {
    pCDP_CenXxx->CSFlag.Bit.CalvesFeetLinkLostFault = FAULT; /*丢失超过门限，则表示链接丢失*/
  }
  
  if(pCDP_CenXxx->SideCtrlLinkLostTimeMs < CEN_Xxx_LINK_LOST_TIME_THRESHOLD)
  {
    pCDP_CenXxx->SideCtrlLinkLostTimeMs += ExePeriod;             
  }
  else
  {
    pCDP_CenXxx->CSFlag.Bit.SideCtrlLinkLostFault = FAULT; /*丢失超过门限，则表示链接丢失*/
  }
  
  if(pCDP_CenXxx->FrameRx.ByteRxTimeOutMs < 100)
  {
    pCDP_CenXxx->FrameRx.ByteRxTimeOutMs += ExePeriod;
  }
}

/*
************************************************************************************************************************
* 函数名称 : CDP_CenCtrl_Init                                                                                                         
* 功能描述 : 通信数据包   之   手控器 <--> 中心板   初始化                                                                               
* 输入参数 : 无                                                            
* 返回参数 : 返回 可操作的结构体 的指针                                                             
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
CDP_CenXxx_t* CDP_CenXxx_Init(void)
{
  /*初始化相关数据------------------------------------------*/
  memset(pCDP_CenXxx, 0, sizeof(CDP_CenXxx_t));
  BSP_UART_RegRxByteCB(CEN_Xxx_UART_PORT, CDP_CenXxx_ByteRx); /*注册串口接收处理函数*/

  return pCDP_CenXxx;
}

/*
************************************************************************************************************************
* 函数名称 : CDP_CenCtrl_GetCSFlag                                                                                                         
* 功能描述 : 获得 控制 与 状态 标识                                                                
* 输入参数 : 无                                                                   
* 返回参数 : 控制与状态标识 的结构体                                                             
* 补充说明 : 无                                                                                                  
************************************************************************************************************************
*/
CDP_CenXxxCSFlag_t CDP_CenXxx_GetCSFlag(void)
{
  return pCDP_CenXxx->CSFlag;
}
