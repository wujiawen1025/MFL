/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: Server.c                                                                                                         
**
**    ��������: 
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
#include "Server.h"
#include "ESF.h"
#include "MChair.h"

/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/


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
static Server_t   Server;
Server_t   *pServer = &Server;

extern uint8_t MChair_KeyValHandle(uint8_t KeyVal, uint8_t *pData);

/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/

/*
************************************************************************************************************************
* �������� : VoiceKey_Default                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_Default(uint8_t *pData)
{
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : VoiceKey_PowerOn                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_PowerOn(uint8_t *pData)
{
  if(SYS_MODE_STANDBY == pMChair->SysModeCur)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : VoiceKey_PowerOff                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_PowerOff(uint8_t *pData)
{
  if(SYS_MODE_USERRUN == pMChair->SysModeCur)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : VoiceKey_PauseOn                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_PauseOn(uint8_t *pData)
{
  if(FALSE == pMChair->CSFlag.Bit.Pause)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : VoiceKey_PauseOff                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_PauseOff(uint8_t *pData)
{
  if(TRUE == pMChair->CSFlag.Bit.Pause)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : VoiceKey_HeatLumbarBackOn                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_HeatLumbarBackOn(uint8_t *pData)
{
  if(OFF == pMChair->LumbarBackHeatCtrlSw)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : VoiceKey_HeatLumbarBackOff                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_HeatLumbarBackOff(uint8_t *pData)
{
  if(ON == pMChair->LumbarBackHeatCtrlSw)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : VoiceKey_AutoQuickOn                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_AutoQuickOn(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Quick)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : VoiceKey_AutoRelaxOn                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_AutoRelaxOn(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Relax)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : VoiceKey_AutoMoveSleepOn                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_AutoMoveSleepOn(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_MoveSleep)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : VoiceKey_AutoStretchOn                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_AutoStretchOn(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Stretch)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : VoiceKey_AutoScrapingOn                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_AutoScrapingOn(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Scraping)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : VoiceKey_AutoShiatsuOn                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_AutoShiatsuOn(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Shiatsu)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : VoiceKey_AutoLadyOn                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_AutoLadyOn(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Lady)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* �������� : VoiceKey_AutoManOn                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t VoiceKey_AutoManOn(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Man)
  {
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}


/*����������������������������������������������������������������������������������������������������������������������*/

static const ServerLogic_t VoiceLogicTab[] = 
{
  /*���Ӳ�����

    ��ִֵ��ǰ��bit7 -- 1���ػ�ʱ���Կ�ִ��    
                        0���ػ�ʱ���򰴼���ִ��   
    ��ִֵ��ǰ��bit6 -- 1����ͣ�������Կ�ִ��
                        0����ͣ��������ִ�С�
    ��ִֵ��ǰ��bit5 -- 

    ��ִֵ�к�                                                   */
  /*  ����ָ��           ��Ӧ�İ�����ֵ                 ������ֵ���Ӳ���           */
  {       8,             KEYVAL_Power,                  VoiceKey_PowerOn            },
  {       9,             KEYVAL_Power,                  VoiceKey_PowerOff           },
  {      10,             KEYVAL_Pause,                  VoiceKey_PauseOn            },
  {      11,             KEYVAL_Pause,                  VoiceKey_PauseOff           },

  {      28,             KEYVAL_SpikeZeroGravity1,      VoiceKey_Default            },
  {      31,             KEYVAL_SpikeHomeReset,         VoiceKey_Default            },
  {      40,             KEYVAL_CoreXYZSpeedAdd,        VoiceKey_Default            },
  {      41,             KEYVAL_CoreXYZSpeedDec,        VoiceKey_Default            }, 
  {     103,             KEYVAL_HeatLumbarBack,         VoiceKey_HeatLumbarBackOn   },
  {     107,             KEYVAL_HeatLumbarBack,         VoiceKey_HeatLumbarBackOff  },

  {     120,             KEYVAL_AutoQuick,              VoiceKey_AutoQuickOn        },  
  {     121,             KEYVAL_AutoRelax,              VoiceKey_AutoRelaxOn        }, 
  {     122,             KEYVAL_AutoMoveSleep,          VoiceKey_AutoMoveSleepOn    }, 
  {     123,             KEYVAL_AutoStretch,            VoiceKey_AutoStretchOn      }, 
  {     124,             KEYVAL_AutoScraping,           VoiceKey_AutoScrapingOn     },  
  {     125,             KEYVAL_AutoShiatsu,            VoiceKey_AutoShiatsuOn      }, 
  {     126,             KEYVAL_AutoLady,               VoiceKey_AutoLadyOn         }, 
  {     127,             KEYVAL_AutoMan,                VoiceKey_AutoManOn          }, 
  
};
#define  VOICE_LOGIC_TAB_NUM    TAB_NUM(VoiceLogicTab)

static uint16_t VoiceLogicID(uint16_t index)
{
  if(index > (VOICE_LOGIC_TAB_NUM-1))
  {
    return INDEX_NO_MATCH;
  }
  return VoiceLogicTab[index].ID;
}

/*
************************************************************************************************************************
* �������� : Server_SetKeyExeState                                                                                      
* �������� : 
* ������� : ��
* ���ز��� : 
* ����˵�� : ��
************************************************************************************************************************
*/
void Server_SetKeyExeState(uint8_t TrueFalse)
{
  pServer->CSFlag.KeyExeState = TrueFalse;
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjRX_0x0702                                                                                      
* �������� : ���ռ�ֵ
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ��������ݵĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0702(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  CDP_DataFormat0x0702_t  *pData0x0702;
  uint8_t state;
  uint16_t index;

  pData0x0702 = (CDP_DataFormat0x0702_t *)&pRxDU[CDP_DU_OFFSET_LEN];
  
  index = BinarySearch(pData0x0702->KeyVal, VOICE_LOGIC_TAB_NUM, VoiceLogicID);
  if(index != INDEX_NO_MATCH ) 
  {
    state = VoiceLogicTab[index].pVoiceKey(&pData0x0702->AddtionData[0]);
    if(SUCCESS == state)
    {
      state |= MChair_KeyValHandle(VoiceLogicTab[index].KeyVal, &pData0x0702->AddtionData[0]);
    }
  }
  
  if(SUCCESS == state)
  {
    pServer->CSFlag.KeyExeState = TRUE;
  }
  else// if(FAIL == state) 
  {
    pServer->CSFlag.KeyExeState = FALSE;
  }
  
  /*�������ݸ�������-------------------------------------------------------------*/
  memcpy(&pAckDU[CDP_DU_OFFSET_LEN], &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjTx_0x0040                                                                                      
* �������� : 0x0040 �ϵ緢�͵������к�
* ������� : ��
* ���ز��� : �ɹ��򷵻�Ҫ���͵����ݵ��ڴ��׵�ַ��ʧ�ܷ���NULL��ָ��
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x0040(void)
{
//  pServer->CSFlag.GetIDCodeQry = FALSE;
  
  pServer->SetQry0x0040.DataLen = sizeof(pServer->SetQry0x0040);
  pServer->SetQry0x0040.DataID[0] = 0x00;
  pServer->SetQry0x0040.DataID[1] = 0x40;
  
  SaveData_GetIDCode(pServer->SetQry0x0040.IDCode);

  return (uint8_t *)&pServer->SetQry0x0040;
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjTx_0x0041                                                                                      
* �������� : 0x0041 ������
* ������� : ��
* ���ز��� : �ɹ��򷵻�Ҫ���͵����ݵ��ڴ��׵�ַ��ʧ�ܷ���NULL��ָ��
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x0041(void)
{
  pServer->SetQry0x0040.DataLen = sizeof(pServer->SetQry0x0040);
  pServer->SetQry0x0040.DataID[0] = 0x00;
  pServer->SetQry0x0040.DataID[1] = 0x41;
  
  SaveData_GetIDCode(pServer->SetQry0x0040.IDCode);

  return (uint8_t *)&pServer->SetQry0x0040;
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjTx_0x0042                                                                                      
* �������� : 0x0042 �ϵ緢�ͳ���汾��
* ������� : ��
* ���ز��� : �ɹ��򷵻�Ҫ���͵����ݵ��ڴ��׵�ַ��ʧ�ܷ���NULL��ָ��
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x0042(void)
{
  pServer->SetQry0x0042.DataLen = sizeof(pServer->SetQry0x0040);  
  pServer->SetQry0x0042.DataID[0] = 0x00;  
  pServer->SetQry0x0042.DataID[1] = 0x42; 
  
  memcpy(pServer->SetQry0x0042.CodeVER, "EC8606B_CEN_V1.0", 16);       /*��ȡ����汾��*/

  return (uint8_t *)&pServer->SetQry0x0042;
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjTx_0x0043                                                                                      
* �������� : 0x0048 �ϵ緢��Զ��������ʽ
* ������� : ��
* ���ز��� : �ɹ��򷵻�Ҫ���͵����ݵ��ڴ��׵�ַ��ʧ�ܷ���NULL��ָ��
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x0043(void)
{
  pServer->SetQry0x0043.DataLen = sizeof(pServer->SetQry0x0043);  
  pServer->SetQry0x0043.DataID[0] = 0x00;  
  pServer->SetQry0x0043.DataID[1] = 0x43;

  pServer->SetQry0x0043.UpdataWay = NEED_CACHE_REMOTE_UPGRADES;
  
  return (uint8_t *)&pServer->SetQry0x0043;
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjRX_0x0040                                                                                      
* �������� : �жϷ������Ƿ��յ����İ��ϱ��ĵ������к�                                                                                 
* ������� : pRxDU  -- ָ����յ����ݶ���Ԫ
*            pAckDU -- ָ��Ӧ������ݶ���Ԫ
* ���ز��� : �����ݶ��������ݵĳ���                                                                                                    
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0040(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  pServer->CSFlag.UpDataSuc_0x0040 = TRUE;
  
  if( (TRUE == pServer->CSFlag.UpDataSuc_0x0040) &&
      (TRUE == pServer->CSFlag.UpDataSuc_0x0042) &&
      (TRUE == pServer->CSFlag.UpDataSuc_0x0043)   )
  {
    pServer->CSFlag.WIFIIntCfg = TRUE;
  }
  
  return 0;                              /*����Ҫ�ظ�*/
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjRX_0x0042                                                                                      
* �������� : �жϷ������Ƿ��յ����İ��ϱ������İ����汾��                                                                                 
* ������� : pRxDU  -- ָ����յ����ݶ���Ԫ
*            pAckDU -- ָ��Ӧ������ݶ���Ԫ
* ���ز��� : �����ݶ��������ݵĳ���                                                                                                    
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0042(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  pServer->CSFlag.UpDataSuc_0x0042 = TRUE;
  
  if( (TRUE == pServer->CSFlag.UpDataSuc_0x0040) &&
      (TRUE == pServer->CSFlag.UpDataSuc_0x0042) &&
      (TRUE == pServer->CSFlag.UpDataSuc_0x0043)   )
  {
    pServer->CSFlag.WIFIIntCfg = TRUE;
  }
  
  return 0;                            /*����Ҫ�ظ�*/
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjRX_0x0043                                                                                      
* �������� : �жϷ������Ƿ��յ����İ��ϱ����豸Զ��������ʽ                                                                             
* ������� : pRxDU  -- ָ����յ����ݶ���Ԫ
*            pAckDU -- ָ��Ӧ������ݶ���Ԫ
* ���ز��� : �����ݶ��������ݵĳ���                                                                                                    
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0043(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  pServer->CSFlag.UpDataSuc_0x0043 = TRUE;
  
  if( (TRUE == pServer->CSFlag.UpDataSuc_0x0040) &&
      (TRUE == pServer->CSFlag.UpDataSuc_0x0042) &&
      (TRUE == pServer->CSFlag.UpDataSuc_0x0043)   )
  {
    pServer->CSFlag.WIFIIntCfg = TRUE;
  }
  
  return 0;                               /*����Ҫ�ظ�*/
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjTx_0x0D01                                                                                   
* �������� : ��Ħ��״̬����1
* ������� : ��
* ���ز��� : �ɹ��򷵻�Ҫ���͵����ݵ��ڴ��׵�ַ��ʧ�ܷ���NULL��ָ��
* ����˵�� : ����ʱ�仯�ϱ�
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x0D01(void)
{
  CDP_DataFormat0x0D01_t Set0x0D01;
  
  memset(&Set0x0D01, 0, sizeof(CDP_DataFormat0x0D01_t)); /*������������*/
  
  Set0x0D01.DataLen   = sizeof(pServer->SetQry0x0D01);
  Set0x0D01.DataID[0] = 0x0D;
  Set0x0D01.DataID[1] = 0X01;
  
  Set0x0D01.Byte1.Bit.SysRun             = pMChair->CSFlag.Bit.SysRun;
  Set0x0D01.Byte1.Bit.Pause              = pMChair->CSFlag.Bit.Pause;
  Set0x0D01.Byte1.Bit.MassageTimeOut     = pMChair->CSFlag.Bit.UserMassageTimeOut;

  Set0x0D01.Byte2.Bit.CoreXYZKneadInRun  = pMChair->StateCoreAction.Bit.XYZ.Bit.KneadInRun;
  Set0x0D01.Byte2.Bit.CoreXYZKneadOutRun = pMChair->StateCoreAction.Bit.XYZ.Bit.KneadOutRun;
  Set0x0D01.Byte2.Bit.CoreTCSLTapRun     = pMChair->StateCoreAction.Bit.TCS.Bit.LTapRun;
  Set0x0D01.Byte2.Bit.CoreTCSTapRun      = pMChair->StateCoreAction.Bit.TCS.Bit.TapRun;
  Set0x0D01.Byte2.Bit.CoreTCSClap1Run    = pMChair->StateCoreAction.Bit.TCS.Bit.Clap1Run;
  Set0x0D01.Byte2.Bit.CoreTCSClap2Run    = pMChair->StateCoreAction.Bit.TCS.Bit.Clap2Run;
  Set0x0D01.Byte3.Bit.CoreTCSShia1Run    = pMChair->StateCoreAction.Bit.TCS.Bit.Shia1Run;
  Set0x0D01.Byte3.Bit.CoreTCSShia2Run    = pMChair->StateCoreAction.Bit.TCS.Bit.Shia2Run;
  Set0x0D01.Byte3.Bit.CoreXYZRollRun     = pMChair->StateCoreAction.Bit.XYZ.Bit.RollRun;
  
  Set0x0D01.Byte17.Bit.KeyAuto           = pMChair->FuncAuto_CoreGas + 20;

  Set0x0D01.Byte29.Bit.MassageTimeMin    = pMChair->UserMassageTimeMin;
  Set0x0D01.Byte30.Bit.MassageTimeSec    = pMChair->UserMassageTimeSec;
  
  /*�仯�ϱ�*/
  if( memcmp(&pServer->SetQry0x0D01, &Set0x0D01, sizeof(pServer->SetQry0x0D01)) )
  {
    memcpy(&pServer->SetQry0x0D01, &Set0x0D01, sizeof(pServer->SetQry0x0D01));
    pMChair->CSFlag.Bit.MChairReported = TRUE;
  }

  return (uint8_t *)&pServer->SetQry0x0D01;
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjRX_0x0D01                                                                                      
* �������� :                                                                         
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ���ĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0D01(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  pMChair->CSFlag.Bit.MChairReported = FALSE;
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjTx_0x0D02                                                                                   
* �������� : ��Ħ��״̬����2
* ������� : ��
* ���ز��� : �ɹ��򷵻�Ҫ���͵����ݵ��ڴ��׵�ַ��ʧ�ܷ���NULL��ָ��
* ����˵�� : �ػ�ʱ�仯�ϱ�
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x0D02(void)
{
  CDP_DataFormat0x0D02_t Set0x0D02;

  Set0x0D02.DataLen   = sizeof(pServer->SetQry0x0D02);
  Set0x0D02.DataID[0] = 0x0D;
  Set0x0D02.DataID[1] = 0X02;
  
  Set0x0D02.Byte1 = '8';
  Set0x0D02.Byte2 = '6';
  Set0x0D02.Byte3 = '0';
  Set0x0D02.Byte5 = '6';
  
  Set0x0D02.Byte4.Bit.ResetOK = 1;

  if((FALSE == pMChair->StateXMotor.Bit.PositionResetOK) ||
     (FALSE == pMChair->StateYMotor.Bit.PositionResetOK) ||
     (FALSE == pMChair->StateZMotor.Bit.PositionResetOK) )
  {
    Set0x0D02.Byte4.Bit.ResetOK &= 0;                                                         /*��оλ�û�δ��λ*/
  }
  
  if(Core_GetYPosition() != PY_MIN)
  {
    Set0x0D02.Byte4.Bit.ResetOK &= 0;                                                        /*��о�����ڶ���*/
  }

  if((FALSE == pMChair->StateBackSpike.Bit.PositionResetOK)   ||
     //(FALSE == pMChair->StateZeroSpike.Bit.PositionResetOK)    ||
     (FALSE == pMChair->StateFeetSpike.Bit.PositionResetOK)   ||
     (FALSE == pMChair->StateLegFlexSpike.Bit.PositionResetOK)) 
  {
    Set0x0D02.Byte4.Bit.ResetOK &= 0;                                                        /*�Ƹ�λ�û�δ��λ*/
  }

  Set0x0D02.Byte4.Bit.WIFIIntCfg = pServer->CSFlag.WIFIIntCfg;
  
  /*�仯�ϱ�*/
  if( memcmp(&pServer->SetQry0x0D02, &Set0x0D02, sizeof(pServer->SetQry0x0D02)) )
  {
    memcpy(&pServer->SetQry0x0D02, &Set0x0D02, sizeof(pServer->SetQry0x0D02));
    pMChair->CSFlag.Bit.MChairReported = TRUE;
  }

  return (uint8_t *)&pServer->SetQry0x0D02;
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjRX_0x0D02                                                                                      
* �������� :                                                                         
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ���ĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0D02(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  pMChair->CSFlag.Bit.MChairReported = FALSE;
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* �������� : Server_SetIntData                                                                                   
* �������� : ������������
* ������� : ��
* ���ز��� : �ɹ��򷵻�Ҫ���͵����ݵ��ڴ��׵�ַ��ʧ�ܷ���NULL��ָ��
* ����˵�� : 
************************************************************************************************************************
*/
void Server_SetIntData(uint8_t *data, uint8_t len, uint8_t reconfiguration)
{
  uint8_t i;
  
  if(TRUE == reconfiguration)
  {
    pServer->IntDataLen = 0;
  }
  
  if(pServer->IntDataLen > 67)
  {
    return;
  }
  
  for(i=0; i<len; i++)
  {
    pServer->SetQry0x0912.IntCfgData[pServer->IntDataLen] = *(data+i);
    pServer->IntDataLen ++;
  }
}

void Server_SetIntState(uint8_t TrueFalse)
{
  pServer->CSFlag.NetDataRx = TrueFalse;
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjTx_0x0912                                                                                   
* �������� : �����������ݸ�������
* ������� : ��
* ���ز��� : �ɹ��򷵻�Ҫ���͵����ݵ��ڴ��׵�ַ��ʧ�ܷ���NULL��ָ��
* ����˵�� : 
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x0912(void)
{
  pServer->SetQry0x0912.DataID[0] = 0x09;
  pServer->SetQry0x0912.DataID[1] = 0x12;
  
  pServer->SetQry0x0912.DataLen = pServer->IntDataLen + 3;
  
//  pServer->SetQry0x0912.IntCfgData = 
  return (uint8_t *)&pServer->SetQry0x0912;
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjRX_0x0912                                                                                      
* �������� : ���շ���������ָ��Ӧ������
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ��������ݵĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0912(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  Server_SetIntState(FALSE);           /*���������ɱ�־*/
  
  memcpy(&pAckDU[CDP_DU_OFFSET_LEN], &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjRX_0x0913                                                                                      
* �������� : ��ȡ���ӵ������к�
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ��������ݵĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0913(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  
  pServer->CSFlag.UpDataSuc_0x0040 = FALSE;
  pServer->CSFlag.UpDataSuc_0x0042 = FALSE;
  pServer->CSFlag.UpDataSuc_0x0043 = FALSE;
  
  /*�������ݸ�������-------------------------------------------------------------*/
  memcpy(&pAckDU[CDP_DU_OFFSET_LEN], &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjRX_0x0C60                                                                                      
* �������� : ��ȡ����״̬
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ��������ݵĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0C60(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  CDP_DataFormat0x0C60_t  *pData0x0C60;
  
  pData0x0C60 = (CDP_DataFormat0x0C60_t *)&pRxDU[CDP_DU_OFFSET_LEN];
  
  if(SYS_MODE_USERRUN == pMChair->SysModeCur)
  {
    if(TRUE == pMChair->CSFlag.Bit.Pause)
    {
      pData0x0C60->SystemState = 3;
    }
    else
    {
      pData0x0C60->SystemState = 1;
    }
  }
  else// if(SYS_MODE_STANDBY == pMChair->SysModeCur)
  {
    pData0x0C60->SystemState = 0;
  }
  
  /*�������ݸ�������-------------------------------------------------------------*/
  memcpy(&pAckDU[CDP_DU_OFFSET_LEN], &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjTx_0x004C                                                                                   
* �������� : �������ϱ���������
* ������� : ��
* ���ز��� : �ɹ��򷵻�Ҫ���͵����ݵ��ڴ��׵�ַ��ʧ�ܷ���NULL��ָ��
* ����˵�� : 
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x004C(void)
{
  uint8_t i;
  
  pServer->SetQry0x004C.DataLen = sizeof(pServer->SetQry0x004C);
  pServer->SetQry0x004C.DataID[0] = 0x00;
  pServer->SetQry0x004C.DataID[1] = 0x4C;
  
  for(i=0; i<10; i++)
  {
    pServer->SetQry0x004C.FaultCodeBit[i] = pMChair->Fault.ReportFlag.All[i];
  }

  return (uint8_t *)&pServer->SetQry0x004C;
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjRX_0x0901                                                                                      
* �������� : ��ȡ��Ħ�ε�ǰ״̬                                                                                
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ���ĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t Server_CDPDataObjRX_0x0901(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
//  uint16_t i;

//  /*�������Ȼ��λ����λ�����BootLoadeģʽ*/
//  BSP_IO_SetOutput_CloseAll();
//  while(++i < 1000);
//  BSP_SystemReset();  
//  return 0;
  if( 0 == pRxDU[CDP_DU_OFFSET_SERVER_DATA] )
  {
    pAckDU[CDP_DU_OFFSET_SERVER_DATA] = 0;
    pServer->CSFlag.UpDataSuc_0x0040 = TRUE;
    pServer->CSFlag.UpDataSuc_0x0042 = TRUE;
    pServer->CSFlag.UpDataSuc_0x0043 = TRUE;
    return 4;
  }
  else
  {
    return CDP_DU_HANDLE_ERR;
  }
}

/*
************************************************************************************************************************
* �������� : Server_CDPDataObjTx_0x004D                                                                                   
* �������� : �����Ħʱ���ϱ���������
* ������� : ��
* ���ز��� : �ɹ��򷵻�Ҫ���͵����ݵ��ڴ��׵�ַ��ʧ�ܷ���NULL��ָ��
* ����˵�� : 
************************************************************************************************************************
*/
uint8_t* Server_CDPDataObjTx_0x004D(void)
{
  pServer->SetQry0x004D.DataLen = sizeof(pServer->SetQry0x004D);
  pServer->SetQry0x004D.DataID[0] = 0x00;
  pServer->SetQry0x004D.DataID[1] = 0x4D;
  
  pServer->SetQry0x004D.SysRunTimeHour             = SaveData_GetSysRunTimeHour();
  pServer->SetQry0x004D.XMotorRunTimeHour          = SaveData_GetXMotorRunTimeHour();
  pServer->SetQry0x004D.YMotorRunTimeHour          = SaveData_GetYMotorRunTimeHour();
  pServer->SetQry0x004D.ZMotorRunTimeHour          = SaveData_GetZMotorRunTimeHour();
  pServer->SetQry0x004D.TCSMotorRunTimeHour        = SaveData_GetTCSMotorRunTimeHour();
  pServer->SetQry0x004D.BackSpikeMotorRunTimeHour  = SaveData_GetBackSpikeMotorRunTimeHour();
  pServer->SetQry0x004D.FeetSpikeMotorRunTimeHour  = SaveData_GetFeetSpikeMotorRunTimeHour();

  return (uint8_t *)&pServer->SetQry0x004D;
}

/*
************************************************************************************************************************
* �������� : Server_ReReportedData                                                                                                         
* �������� : �����ϱ�����            
* ������� : ��                                            
* ���ز��� : ���� �ɲٷ��������� �Ľṹ�� ��ָ��                                                                               
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Server_ReReportedData(void)
{
  pServer->CSFlag.UpDataSuc_0x0040 = FALSE;
  pServer->CSFlag.UpDataSuc_0x0042 = FALSE;
  pServer->CSFlag.UpDataSuc_0x0043 = FALSE;
  pServer->CSFlag.WIFIIntCfg       = FALSE;
}

/*
************************************************************************************************************************
* �������� : Server_Init                                                                                                         
* �������� : ������������ ��ʼ��                 
* ������� : ��                                            
* ���ز��� : ���� �ɲٷ��������� �Ľṹ�� ��ָ��                                                                               
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
Server_t* Server_Init(void)
{
  /*��ʼ���������------------------------------------------*/
  memset(pServer, 0, sizeof(Server_t)); /*������������*/
  Server_SetKeyExeState(TRUE);
  
  return pServer;
}

/*
************************************************************************************************************************
* �������� : Server_GetCSFlag                                                                                                         
* �������� : ��� ���� �� ״̬ ��ʶ                        
* ������� : ��                                            
* ���ز��� : ������״̬��ʶ �Ľṹ��                                                                                           
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
ServerCSFlag_t Server_GetCSFlag(void)
{
  return pServer->CSFlag;
}
