/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: SaveData.c
**
**    ��������: ���籣�����ݵĴ���
**
**    ��    ˾���ɷ�������
**
**    ��Ŀ���ƣ�
**
**    ƽ̨��Ϣ��
**
**    ��    �ߣ�Hzy
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
#include "SaveData.h"
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
static SaveData_t  SaveData;
SaveData_t  *pSaveData = &SaveData;

/*���������Ϣ��һ����Ϣ��һ�б�ʾ���ûس����зָ�*/
const uint8_t SoftIdentifyInfo[] =
{ 
"VER: EC8506A-CEN-V0.1\r\n\
MCU: KE04Z128\r\n\
PCB: EC806A-CEN-V1.1\r\n\
EDT: 2018.10.26"
};


/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : SaveData_GetSysRunTimeHour                                                                                                         
* �������� : ��ȡ����                                                                                        
* ������� : ��                                                                                  
* ���ز��� : Ҫ��õ�����                                                                   
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint16_t SaveData_GetSysRunTimeHour(void)
{
  if(pSaveData->SysRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->SysRunTimeMs100/36000;
  }
} 

/*
************************************************************************************************************************
* �������� : SaveData_GetXMotorRunTimeHour                                                                                                         
* �������� : ��ȡ����                                                                                        
* ������� : ��                                                                                  
* ���ز��� : Ҫ��õ�����                                                                   
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint16_t SaveData_GetXMotorRunTimeHour(void)
{
  if(pSaveData->XMotorRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->XMotorRunTimeMs100/36000;
  }
} 

/*
************************************************************************************************************************
* �������� : SaveData_GetYMotorRunTimeHour                                                                                                         
* �������� : ��ȡ����                                                                                        
* ������� : ��                                                                                 
* ���ز��� : Ҫ��õ�����                                                                   
* ����˵�� : ��                                                                                                    
************************************************************************************************************************
*/
uint16_t SaveData_GetYMotorRunTimeHour(void)
{
  if(pSaveData->YMotorRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->YMotorRunTimeMs100/36000;
  }
} 

/*
************************************************************************************************************************
* �������� : SaveData_GetZMotorRunTimeHour                                                                                                         
* �������� : ��ȡ����                                                                                        
* ������� : ��                                                                                  
* ���ز��� : Ҫ��õ�����                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint16_t SaveData_GetZMotorRunTimeHour(void)
{
  if(pSaveData->ZMotorRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->ZMotorRunTimeMs100/36000;
  }
} 

/*
************************************************************************************************************************
* �������� : SaveData_GetTCSMotorRunTimeHour                                                                                                         
* �������� : ��ȡ����                                                                                        
* ������� : ��                                                                                  
* ���ز��� : Ҫ��õ�����                                                                   
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint16_t SaveData_GetTCSMotorRunTimeHour(void)
{
  if(pSaveData->TCSMotorRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->TCSMotorRunTimeMs100/36000;
  }
} 

/*
************************************************************************************************************************
* �������� : SaveData_GetBackSpikeMotorRunTimeHour                                                                                                         
* �������� : ��ȡ����                                                                                        
* ������� : ��                                                                                  
* ���ز��� : Ҫ��õ�����                                                                   
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint16_t SaveData_GetBackSpikeMotorRunTimeHour(void)
{
  if(pSaveData->BackSpikeMotorRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->BackSpikeMotorRunTimeMs100/36000;
  }
} 

/*
************************************************************************************************************************
* �������� : SaveData_GetFeetSpikeMotorRunTimeHour                                                                                                         
* �������� : ��ȡ����                                                                                        
* ������� : ��                                                                                  
* ���ز��� : Ҫ��õ�����                                                                   
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint16_t SaveData_GetFeetSpikeMotorRunTimeHour(void)
{
  if(pSaveData->FeetSpikeMotorRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->FeetSpikeMotorRunTimeMs100/36000;
  }
}
 
/*
************************************************************************************************************************
* �������� : SaveData_GetZeroSpikeMotorRunTimeHour                                                                                                         
* �������� : ��ȡ����                                                                                        
* ������� : ��                                                                                  
* ���ز��� : Ҫ��õ�����                                                                   
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint16_t SaveData_GetZeroSpikeMotorRunTimeHour(void)
{
  if(pSaveData->ZeroSpikeMotorRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->ZeroSpikeMotorRunTimeMs100/36000;
  }
} 

/*
************************************************************************************************************************
* �������� : SaveData_GetLegFlexMotorRunTimeHour                                                                                                         
* �������� : ��ȡ����                                                                                        
* ������� : ��                                                                                  
* ���ز��� : Ҫ��õ�����                                                                   
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint16_t SaveData_GetLegFlexMotorRunTimeHour(void)
{
  if(pSaveData->LegFlexMotorRunTimeMs100 >= 359964000)
  {
    return 9999;
  }
  else
  {
    return pSaveData->LegFlexMotorRunTimeMs100/36000;
  }
} 

/*
************************************************************************************************************************
* �������� : SaveData_GetIDCodeWriteCount                                                                                                         
* �������� : ��ȡID��д��Ĵ���                                                                                        
* ������� : ��                                                                                  
* ���ز��� : ID��д��Ĵ���                                                                   
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t SaveData_GetIDCodeWriteCount(void)
{
  return pSaveData->IDCodeWriteCount;
} 

/*
************************************************************************************************************************
* �������� : SaveData_GetIDCode                                                                                                         
* �������� : ��ȡID��                                                                                        
* ������� : pData -- �����õ�����                                                                                  
* ���ز��� : ID��ĳ���                                                           
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t SaveData_GetIDCode(uint8_t *pData)
{
  if(pSaveData->IDCodeLen > ID_CODE_BUF_SIZE)
  {
    pSaveData->IDCodeLen = ID_CODE_BUF_SIZE;
  }
  memcpy(pData, pSaveData->IDCode, pSaveData->IDCodeLen);
  return pSaveData->IDCodeLen;
} 

/*
************************************************************************************************************************
* �������� : SaveData_SetIDCode                                                                                                         
* �������� : д��ID��                                                                                        
* ������� : pData -- ָ��Ҫд�������
*            Len   -- Ҫд�����ݳ���                                                                                  
* ���ز��� : д��ĳ���                                                                   
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t SaveData_WriteIDCode(uint8_t *pData, uint8_t Len)
{
  if(Len > ID_CODE_BUF_SIZE)
  {
    Len = ID_CODE_BUF_SIZE;
  }

  if(pSaveData->IDCodeWriteCount < 255)
  {
    pSaveData->IDCodeWriteCount++;
  }
  
  pSaveData->IDCodeLen = Len;
  memcpy(pSaveData->IDCode, pData, pSaveData->IDCodeLen);
  SaveData_Write((uint8_t*)pSaveData, sizeof(SaveData_t));  /*д��EEProm*/
  
  return Len;
}

/*
************************************************************************************************************************
* �������� : SaveData_Update                                                                                                         
* �������� : �������ݵĸ���                                                                                        
* ������� : ExePeriod ����ִ������                                                                                  
* ���ز��� : ��                                                                   
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SaveData_Update(Ticker_t ExePeriod)
{
  static  uint8_t SysMode = SYS_MODE_NONE;


  /*��������-------------------------------------------------------------*/
  if(SysMode != pMChair->SysModeCur)
  {
    SysMode = pMChair->SysModeCur;
    if(SYS_MODE_STANDBY == SysMode)                              /*ÿ�ν������ģʽ���ͱ���һ������*/
    {
      SaveData_Write((uint8_t*)pSaveData, sizeof(SaveData_t));   /*д��EEProm*/
    }
  }

  /*���ݸ���----------------------------------------------------------*/
  if((SYS_MODE_USERRUN == pMChair->SysModeCur)      && 
     (ON == pMChair->CSFlag.Bit.UserMassageTimeRun) )
  {
    pSaveData->SysRunTimeMs100++;
  }

  if(ON == pMChair->StateXMotor.Bit.Work)
  {
    pSaveData->XMotorRunTimeMs100++;
  }

  if(ON == pMChair->StateYMotor.Bit.Work)
  {
    pSaveData->YMotorRunTimeMs100++;
  }

  if(ON == pMChair->StateZMotor.Bit.Work)
  {
    pSaveData->ZMotorRunTimeMs100++;
  }

  if(ON == pMChair->StateTCSMotor.Bit.Work)
  {
    pSaveData->TCSMotorRunTimeMs100++;
  }

  if(ON == pMChair->StateBackSpike.Bit.Run)
  {
    pSaveData->BackSpikeMotorRunTimeMs100++;
  }

  if(ON == pMChair->StateZeroSpike.Bit.Run)
  {
    pSaveData->ZeroSpikeMotorRunTimeMs100++;
  }

  if(ON == pMChair->StateFeetSpike.Bit.Run)
  {
    pSaveData->FeetSpikeMotorRunTimeMs100++;
  }

  if(ON == pMChair->StateLegFlexSpike.Bit.Run)
  {
    pSaveData->LegFlexMotorRunTimeMs100++;
  }
}

/*
========================================================================================================================
*     �������ݹ��ܺ�����                           �������ݹ��ܺ�����                           �������ݹ��ܺ�����
========================================================================================================================
*/
#define  SAVEDATA_TICK_COUNT_BUF_NUM   1
static Ticker_t SaveData_TickCount[SAVEDATA_TICK_COUNT_BUF_NUM];

static const ESF_TmrExeFunc_t  SaveData_TmrExeFuncTab[] = 
{
  /*   ִ�к���              ִ������(ms)         ʱ���������*/
  {SaveData_Update,           100,             &SaveData_TickCount[0]}
};

#define  SAVEDATA_TMR_EXE_FUNC_TAB_NUM     TAB_NUM(SaveData_TmrExeFuncTab)


/*
************************************************************************************************************************
* �������� : SaveData_Load                                                                                                         
* �������� : �������ݵļ���                                                                                        
* ������� : ��                                                                                  
* ���ز��� : ���� �������� �Ľṹ�� ��ָ��                                                                   
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
SaveData_t* SaveData_Load(void)
{
  /*��� SaveData_TmrExeFuncTab ���ܺ����������Ƿ���ȷ------------------------*/
  ESF_TmrExeFuncTabCheck(SaveData_TmrExeFuncTab, SAVEDATA_TMR_EXE_FUNC_TAB_NUM, SAVEDATA_TICK_COUNT_BUF_NUM);

  /*�Ӵ洢�����������-------------------------------------------------------*/
  SaveData_Read((uint8_t*)&pSaveData->Sync, sizeof(pSaveData->Sync));  /*��ͬ����*/
  if (pSaveData->Sync != 0x55AA)                                       /*ͬ����δд�룬���ʾEEPRom Ϊ�µģ���δд������*/	
  {
    memset((uint8_t*)pSaveData, 0, sizeof(SaveData_t)); 
    pSaveData->Sync = 0x55AA;
    SaveData_WriteIDCode((uint8_t*)"TIT86062005290001", 17);           
    SaveData_Write((uint8_t*)pSaveData, sizeof(SaveData_t));           /*��һ�� ��EEPRomд������*/
  }
  else                                                                 /*ͬ�����Ѿ����ڣ���ֱ�Ӷ�������*/
  {
    SaveData_Read((uint8_t*)pSaveData, sizeof(SaveData_t));
  }

  if(pSaveData->ResetCount < 0xFFFF)
  {
    pSaveData->ResetCount++;                                           /*ϵͳ��λ�����ۼ�*/
  }

  return pSaveData;
}

/*
************************************************************************************************************************
* �������� : SaveData_Handle                                                                                                         
* �������� : �������ݵĴ���                                                                                        
* ������� : ��                                                                                  
* ���ز��� : ��                                                                   
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SaveData_Handle(void)
{
  /*���ȹ��ܺ�����------------------------------------------------*/
  ESF_TmrExeFuncScheduling(SaveData_TmrExeFuncTab, SAVEDATA_TMR_EXE_FUNC_TAB_NUM);
}


/*
************************************************************************************************************************
* �������� : SaveData_CDPDataObjRx_0x3D                                                                                      
* �������� : 0x3D ���������Ϣ�� ��λ����ѯ�����Ϣ��
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ��������ݵĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t SaveData_CDPDataObjRx_0x3D(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  memcpy(&pAckDU[CDP_DU_OFFSET_LEN], &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  memcpy(&pAckDU[CDP_DU_OFFSET_DATA], SoftIdentifyInfo, sizeof(SoftIdentifyInfo)-1);       /*�������������Ϣ����*/
  pAckDU[CDP_DU_OFFSET_LEN] = 2 + sizeof(SoftIdentifyInfo)-1;
                                                                                           /*�������ݶ��󳤶�*/
  return pAckDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* �������� : SaveData_CDPDataObjRx_0x3E                                                                                      
* �������� : 0x3E���������룺��λ����ѯ����д�������к���
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ��������ݵĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t SaveData_CDPDataObjRx_0x3E(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  memcpy(&pAckDU[CDP_DU_OFFSET_LEN], &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);

  if(CDP_CMD_QRY == Cmd)
  {
    pAckDU[CDP_DU_OFFSET_DATA+0] = SaveData_GetIDCodeWriteCount();
    pAckDU[CDP_DU_OFFSET_LEN] = SaveData_GetIDCode(&pAckDU[CDP_DU_OFFSET_DATA+1]) + 2 + 1;
  }
  else //if(CDP_CMD_SET_ACK == Cmd)
  {
    pAckDU[CDP_DU_OFFSET_LEN] = SaveData_WriteIDCode(&pRxDU[CDP_DU_OFFSET_DATA+1], pRxDU[CDP_DU_OFFSET_LEN] - 2 - 1);
  }
                                                                                            /*�������ݶ��󳤶�*/
  return pAckDU[CDP_DU_OFFSET_LEN];
}

