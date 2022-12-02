/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: CDP_CenApp.c                                                                                                         
**
**    ��������: ͨ�����ݰ�   ֮   App<--> ���İ塣
**
**    ��    ˾���ɷ�������
**
**    ��Ŀ���ƣ�
**
**    ƽ̨��Ϣ��
**
**    ��    �ߣ�LZH
**
**    ����˵��:
**
**    �޸ļ�¼:  --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/

/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "CDP.h"
#include "MChair.h"
#include "CDP_CenApp.h"
#include "Server.h"

/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/
#define  CEN_APP_RX_BUF_SIZE                  (ESF_MEM_BOLCK_BYTE_SIZE - (ESF_MEM_BOLCK_BYTE_SIZE/4)) /*���ջ����С�����ռ�ڴ���3/4*/
#define  CEN_APP_TX_BUF_SIZE                  (CEN_APP_RX_BUF_SIZE)                                   /*���ͻ����С*/
#define  CEN_APP_UART_PORT                    BSP_UART_Port0                                          /*���ô���*/

#define  CEN_APP_LINK_LOST_TIME_THRESHOLD     4000                                                    /*ͨ�����Ӷ�ʧʱ������*/

/*
========================================================================================================================
*�������������Ͷ��塿                              �������������Ͷ��塿                              �������������Ͷ��塿
========================================================================================================================
*/


/*
========================================================================================================================
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
========================================================================================================================
*/
static CDP_CenApp_t CDP_CenApp;
CDP_CenApp_t *pCDP_CenApp = &CDP_CenApp;

//static const SysMode_KeyVal_t KeyValMapTab[] = 
//{

//};


/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/

/*
************************************************************************************************************************
* �������� : CDP_AppToCen_KeyValHandle                                                                                                         
* �������� : ͨ�����ݰ�   ֮   App --> ���İ�   �������մ���                                                       
* ������� :                                                                    
* ���ز��� : ��                                                             
* ����˵�� : ��                                                                                                  
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
//            pCDP_CenApp->CSFlag.Bit.AppKeyLongPress = TRUE;         /*�а�������*/
//          }
//        }
  pCDP_CenApp->KeyValMap = pCDP_CenApp->KeyValRx;
  
  if((pCDP_CenApp->KeyValMap != 0xff) && (pCDP_CenApp->KeyValMap != 0x00))
  {
    pCDP_CenApp->KeyValAssist = pCDP_CenApp->KeyValMap;         /*��¼������ֵ*/
  }

  pEvt = ESF_MemBuf_Get();                                      /*�����¼��ڴ��*/
  if(pEvt != NULL)                                              /*����ɹ�*/ 
  {
    pEvt->Type = EvtCDPRx;
    pEvt->Arg.CDPRx.CDPType = CDP_TYPE_APP_KEY;          
    pEvt->Arg.CDPRx.pRxBuf = (uint8_t*)pEvt->AppendData;
    memcpy(pEvt->Arg.CDPRx.pRxBuf, &pCDP_CenApp->RxBuf[APP_CDP_OFFSET_DATA], APP_TO_CEN_DATALEN);
    pEvt->Arg.CDPRx.pRxBuf[0] = pCDP_CenApp->KeyValMap;         /*��ֵ������ӳ����ֵ*/        
    ESF_EvtQuene_Post(pEvt);                                    /*Ͷ���¼�*/        
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
    Server_ReReportedData();             /*�����ϱ�����*/
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
  pCDP_CenApp->LinkLostTimeMs = 0;                                            /*�����Ӷ�ʧʱ��*/ 
  pCDP_CenApp->CSFlag.Bit.LinkLostFault = NORMAL;  
}

/*
************************************************************************************************************************
* �������� : CDP_AppToCen_GetIDCode                                                                                                         
* �������� : ͨ�����ݰ�   ֮   App --> ���İ�   ��ȡ�������к�                                                   
* ������� :                                                                    
* ���ز��� : ��                                                             
* ����˵�� : ��������һ������ֻ��20Byte����������Ϊ16Byte��ʵ�ʵ������к���17Byte���ʶ�������4λƫ���޸�Ϊ3λ                                                                               
************************************************************************************************************************
*/
void CDP_AppToCen_GetIDCode()
{
  int8_t i;
  
  pCDP_CenApp->AckBuf[APP_CDP_OFFSET_HEAD] = 0x7B;
  pCDP_CenApp->AckBuf[APP_CDP_OFFSET_FUNC] = 0xB6;
  pCDP_CenApp->AckBuf[APP_CDP_OFFSET_LEN]  = 16;
  
  SaveData_GetIDCode(&pCDP_CenApp->AckBuf[APP_CDP_OFFSET_DATA]);
  /*������4λƫ���޸�Ϊ3λ*/
  for(i=0; i<3; i++)
  {
    pCDP_CenApp->AckBuf[APP_CDP_OFFSET_DATA+13+i] = pCDP_CenApp->AckBuf[APP_CDP_OFFSET_DATA+14+i];
  }

  pCDP_CenApp->CSFlag.Bit.NeedAck = TRUE;
}

/*
========================================================================================================================
*    ͨ�����ݰ����ܺ��������                  ͨ�����ݰ����ܺ��������                    ͨ�����ݰ����ܺ��������
========================================================================================================================
*/
static const AppDataObjManageTabItem_t  AppDataObjManageTab[] = 
{
  {0xa0,  CDP_AppToCen_KeyValHandle },          /*App��������*/
  {0xa1,  CDP_AppToCen_CfgNetwork },            /*APP����*/
//  {0xa2,  CDP_AppToCen_GetSoftVersion },        /*APP��ȡ����汾��*/
  {0xa3,  CDP_AppToCen_HeartbeatPacket },       /*APP������*/
  {0xa6,  CDP_AppToCen_GetIDCode },             /*APP��ȡ�������к�*/
  
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
* �������� : CDP_AppToCen_AnalyzeApp                                                                                                         
* �������� : ͨ�����ݰ�   ֮   App --> ���İ�   �����������                                                          
* ������� : RxByte -- �յ����ֽ�����                                                                    
* ���ز��� : ��                                                             
* ����˵�� : ��                                                                                                  
************************************************************************************************************************
*/
void CDP_AppToCen_AnalyzeApp(uint8_t RxByte)
{
  uint8_t i;
  uint8_t sum;
  uint16_t index;
  
  /*��ֹ����*/
  if(pCDP_CenApp->FrameRx.ByteRxTimeOutMs >= 4)                     /*������19200����4*1.92=8�ֽڵ�ʱ��*/                                           
  {
    pCDP_CenApp->RxState = 0;           
  }


  switch(pCDP_CenApp->RxState)
  {
    case APP_TO_CEN_RX_STATE_SEARCH_HEAD:                            /*������ʼ��*/
    {
      pCDP_CenApp->RxLen = 0;
      if(APP_TO_CEN_HEAD == RxByte)
      {
        pCDP_CenApp->RxBuf[pCDP_CenApp->RxLen++] = RxByte;
        pCDP_CenApp->RxState = APP_TO_CEN_RX_STATE_JUDGE_FUNC;       /*�յ���ʼ�룬��ȥ�жϹ�����*/
      }
    }break;

    case APP_TO_CEN_RX_STATE_JUDGE_FUNC:                             /*�жϹ�����*/
    {
      pCDP_CenApp->RxBuf[pCDP_CenApp->RxLen++] = RxByte;
      pCDP_CenApp->RxState = APP_TO_CEN_RX_STATE_JUDGE_FRAMELEN;     /*�����룬ȥ�ж�֡����*/
    }break;

    case APP_TO_CEN_RX_STATE_JUDGE_FRAMELEN:                         /*�ж�֡����*/
    {
      pCDP_CenApp->RxBuf[pCDP_CenApp->RxLen++] = RxByte;
      pCDP_CenApp->RxDataLen = RxByte;  
      if(pCDP_CenApp->RxDataLen > 0)
      {
        pCDP_CenApp->RxState = APP_TO_CEN_RX_STATE_RCV_DATA;         /*���ȶԣ�ȥ��������*/
      }
      else
      {
        pCDP_CenApp->RxState = APP_TO_CEN_RX_STATE_JUDGE_SUMCHECK;   /*û�����ݣ�ֱ���ж��ۼӺ�У��*/
      }
      
    }break;

    case APP_TO_CEN_RX_STATE_RCV_DATA:                               /*��������*/
    {
      pCDP_CenApp->RxBuf[pCDP_CenApp->RxLen++] = RxByte;
      pCDP_CenApp->RxDataLen--;

      if(0 == pCDP_CenApp->RxDataLen)
      {
        pCDP_CenApp->RxState = APP_TO_CEN_RX_STATE_JUDGE_SUMCHECK;   /*���ռ�ֵ��ɣ�ȥ�ж��ۼӺ�*/
      }
    }break;

    case APP_TO_CEN_RX_STATE_JUDGE_SUMCHECK:                         /*�ж��ۼӺ�У��*/
    {
      sum = 0;
      for(i=0; i<pCDP_CenApp->RxLen; i++)
      {
        sum += pCDP_CenApp->RxBuf[i];
      }
      
      
      if(sum != RxByte) /*У���������������ͷ================================*/
      {
        pCDP_CenApp->RxState = APP_TO_CEN_RX_STATE_SEARCH_HEAD;     
      }
      else /*֡���ճɹ�==========================================================*/
      {
        pCDP_CenApp->RxBuf[pCDP_CenApp->RxLen++] = RxByte;

        pCDP_CenApp->RxState = APP_TO_CEN_RX_STATE_SEARCH_HEAD;      /*��ʼ��һ֡�Ľ��գ�������������ͷ*/
        
        index = BinarySearch(pCDP_CenApp->RxBuf[APP_CDP_OFFSET_FUNC], APP_DATA_OBJ_MANAGE_TAB_NUM, AppDataObjID);
        
        if(INDEX_NO_MATCH == index)                                  /*û��ƥ������ݶ���ID*/    
        {
          return ;                                                   /*���ݴ������������������ݵĴ���*/
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
* �������� : CDP_CenToApp_DataTx                                                                                                         
* �������� : ͨ�����ݰ�   ֮   ���İ� --> App    ���ݷ���                                                                      
* ������� : ��                                                               
* ���ز��� : ��                                                             
* ����˵�� : ��                                                                                                  
************************************************************************************************************************
*/
void CDP_CenStateTmrToApp_DataTx(Ticker_t ExePeriod)
{
  uint8_t *rp, *rp1, *wp;
  uint8_t  i;
  static uint8_t Order;
  static uint8_t ToAppFrame[20];
  

  memset(&pCDP_CenApp->TxBuf,       0, CEN_TO_CTRL_DATALEN); /*����ǰ������������ֵ*/
  
  /*���������·��͵�����֡----------------------------------------------------------*/
//  if((SYS_MODE_STANDBY     == pMChair->SysModeCur) ||  
//     (SYS_MODE_USERRUN     == pMChair->SysModeCur) ||  /*������ģʽ��𲻴󣬲���� SysMode_UserRun_Timer()�����д���*/ 
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
    
    if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core)   /*��о�ֶ�*/
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

    if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core)   /*��о�ֶ�*/
    {
      pCDP_CenApp->TxBuf.Byte10.MassageIntensity = pMChair->MannualCoreFlexLevel+1;
    }
    else if(FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Core) /*��о�Զ�*/
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
    pCDP_CenApp->TxBuf.Byte19.KeyLegExtend      = /*(LEGFLEXSPIKE_DIRECTION_EXTEND   == pMChair->StateLegFlexSpike.Bit.Direction)&&(pMChair->StateLegFlexSpike.Bit.Run);*/(LEGFLEXSPIKE_ACTION_EXTEND == pMChair->FuncMannual_Spike.Bit.LegFlexMove) ? 1:0;    /*С��1�Ƹ�����*/                
    pCDP_CenApp->TxBuf.Byte19.KeyLegShorten     = /*(LEGFLEXSPIKE_DIRECTION_SHORTEN  == pMChair->StateLegFlexSpike.Bit.Direction)&&(pMChair->StateLegFlexSpike.Bit.Run);*/(LEGFLEXSPIKE_ACTION_SHORTEN == pMChair->FuncMannual_Spike.Bit.LegFlexMove) ? 1:0;     /*С��1�Ƹ�����*/       
    pCDP_CenApp->TxBuf.Byte19.KeyZero2          = (pMChair->FuncAuto_Spike == FA_SPIKE_ZeroGravity2) ? 1 : 0;                        /*������1*/  
    pCDP_CenApp->TxBuf.Byte19.KeyZero1          = (pMChair->FuncAuto_Spike == FA_SPIKE_ZeroGravity1) ? 1 : 0;                        /*������2*/ 
    pCDP_CenApp->TxBuf.Byte17.KeyHomeReset      = (pMChair->FuncAuto_Spike == FA_SPIKE_Home) ? 1 : 0;                                /*��λ*/ 
    if((PBACK_ZERO1_ANGLE == Spike_GetBackAngle()) && (FALSE == pMChair->StateBackSpike.Bit.Work) &&
       (PFEET_ZERO1_ANGLE == Spike_GetFeetAngle()) && (FALSE == pMChair->StateFeetSpike.Bit.Work) )
    {
      pCDP_CenApp->TxBuf.Byte19.KeyZero1 = 1;                     /*������*/  
    }
    if((PBACK_ZERO2_ANGLE == Spike_GetBackAngle()) && (FALSE == pMChair->StateBackSpike.Bit.Work) &&
       (PFEET_ZERO2_ANGLE == Spike_GetFeetAngle()) && (FALSE == pMChair->StateFeetSpike.Bit.Work) )
    {
      pCDP_CenApp->TxBuf.Byte19.KeyZero2 = 1;                     /*������*/  
    }
    if((PBACK_HOME_ANGLE == Spike_GetBackAngle()) && (FALSE == pMChair->StateBackSpike.Bit.Work) &&
       (PFEET_HOME_ANGLE == Spike_GetFeetAngle()) && (FALSE == pMChair->StateFeetSpike.Bit.Work) )
    {
      pCDP_CenApp->TxBuf.Byte17.KeyHomeReset = 1;                 /*��λ*/
    }

    /*�����ĸ���ֵ����ƽ���״̬��ʾ�����⴦��*/
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
        pCDP_CenApp->TxBuf.Byte20.KeyCoreMannualUp = 1;/*��֤ �㰴����ʾ*/
      }
      else if(KEYVAL_CoreMannualDown == pCDP_CenApp->KeyValMap)
      {
        pCDP_CenApp->TxBuf.Byte20.KeyCoreMannualDown = 1;/*��֤ �㰴����ʾ*/
      }
    }
    else
    {
      /*��֤ ��������ʾ*/
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

    if(pMChair->Fault.ReportTLMs > 0) /*�ϱ�ʱ�仹��ʣ��*/
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
* �������� : CDP_CenTmrToApp_DataTx                                                                                                         
* �������� : ͨ�����ݰ�   ֮   ���İ� --> App    ���ݷ���                                                                      
* ������� : ��                                                               
* ���ز��� : ��                                                             
* ����˵�� : ��                                                                                                  
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
* �������� : CDP_CenApp_ByteRx                                                                                                         
* �������� : ͨ�����ݰ�   ֮    ���İ� <--> App   �ֽڽ��մ���                                                                              
* ������� : RxByte -- �յ����ֽ�����                                                                    
* ���ز��� : ��                                                             
* ����˵�� : �ú�������ͨ��BSP_UART_RegRxByteCB()ע���BSP�㣬�Ա��ڴ��ڽ����ֽ��ж��е��á�                                                                                                  
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
* �������� : CDP_CenApp_DataTx                                                                                                         
* �������� : ͨ�����ݰ�   ֮  ���İ� <--> App      ���ݷ���                                                                      
* ������� : pTXData -- Ҫ���͵�����   
*            TxLen   -- ���ͳ��� 
* ���ز��� : BSP_UART_TxState_Busy  -- ����æ���޷�������pTxBufָ��ĵ����ݡ�
*            ����ֵ                 -- ���ڿ�ʼ����pTxBufָ��ĵ������ˡ�
* ����˵�� : ��                                                                                                  
************************************************************************************************************************
*/
uint8_t CDP_CenApp_DataTx(ESF_Evt_t *pEvt)
{
  static uint8_t FrameTxBuf[CEN_APP_TX_BUF_SIZE];

  return CDP_FrameTxHandle(pEvt, FrameTxBuf, CEN_APP_UART_PORT);
}


/*
************************************************************************************************************************
* �������� : CDP_CenApp_FaultCheck                                                                                                         
* �������� : ͨ�����ݰ�   ֮   ���İ� <--> App   ���ϼ��                                                                        
* ������� : ��                                                             
* ���ز��� : ��                                                             
* ����˵�� : ��                                                                                                  
************************************************************************************************************************
*/
void CDP_CenApp_FaultCheck(Ticker_t ExePeriod)
{
  if(OFF == BSP_IO_GetERPPowerSwState())/*ERP��Դ�رգ�Xxx��ԴҲ���رգ��Ͳ��������ж�*/
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
    pCDP_CenApp->CSFlag.Bit.LinkLostFault = FAULT; /*��ʧ�������ޣ����ʾ���Ӷ�ʧ*/
  }
  
  if(pCDP_CenApp->FrameRx.ByteRxTimeOutMs < 100)
  {
    pCDP_CenApp->FrameRx.ByteRxTimeOutMs += ExePeriod;
  }
}

/*
************************************************************************************************************************
* �������� : CDP_CenApp_Init                                                                                                         
* �������� : ͨ�����ݰ�   ֮   App <--> ���İ�   ��ʼ��                                                                               
* ������� : ��                                                            
* ���ز��� : ���� �ɲ����Ľṹ�� ��ָ��                                                             
* ����˵�� : ��                                                                                                  
************************************************************************************************************************
*/
CDP_CenApp_t* CDP_CenApp_Init(void)
{
  /*��ʼ���������------------------------------------------*/
  memset(pCDP_CenApp, 0, sizeof(CDP_CenApp_t));
  BSP_UART_RegRxByteCB(CEN_APP_UART_PORT, CDP_CenApp_ByteRx); /*ע�ᴮ�ڽ��մ�����*/

  return pCDP_CenApp;
}

/*
************************************************************************************************************************
* �������� : CDP_CenApp_GetCSFlag                                                                                                         
* �������� : ��� ���� �� ״̬ ��ʶ                                                                
* ������� : ��                                                                   
* ���ز��� : ������״̬��ʶ �Ľṹ��                                                             
* ����˵�� : ��                                                                                                  
************************************************************************************************************************
*/
CDP_CenAppCSFlag_t CDP_CenApp_GetCSFlag(void)
{
  return pCDP_CenApp->CSFlag;
}
