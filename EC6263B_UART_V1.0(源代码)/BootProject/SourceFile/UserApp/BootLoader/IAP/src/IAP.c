/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: IAP.h                                                                                                        
**
**    ��������:                                                                                                  
**
**    ��    ˾��                                                                                                        
**
**    ��Ŀ���ƣ�                                                                                                        
**
**    ƽ̨��Ϣ��                                                                                                        
**
**    ��    �ߣ�Hzy                                                                                                     
**
**    ����˵��:                                                                                                        
**
**    �޸ļ�¼: --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/

#ifndef  _IAP_C_
#define  _IAP_C_
/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "IAP.h"          
#include "CDP.h"          
#include "bsp_Cfg.h"          


/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/
#ifndef BSP_CFG_FLASH_PAGE_SIZE
  #error "Please define  BSP_CFG_FLASH_PAGE_SIZE  (in bsp_Cfg.h file)"                         /*�붨Flashҳ��С*/
#endif

#ifndef BSP_CFG_BOOTLOADER_START_ADDR
  #error "Please define  BSP_CFG_BOOTLOADER_START_ADDR  (in bsp_Cfg.h file)"                   /*�붨��IAP��ʼ��ַ*/
#endif

#ifndef BSP_CFG_BOOTLOADER_END_ADDR
  #error "Please define  BSP_CFG_BOOTLOADER_END_ADDR  (in bsp_Cfg.h file)"                     /*�붨��IAP������ַ*/
#endif

#ifndef BSP_CFG_UPDATE_OP_INFO_START_ADDR
  #error "Please define  BSP_CFG_UPDATE_OP_INFO_START_ADDR  (in bsp_Cfg.h file)"               /*�붨������������Ϣ��ʼ��ַ*/
#endif

#ifndef BSP_CFG_UPDATE_OP_INFO_END_ADDR
  #error "Please define  BSP_CFG_UPDATE_OP_INFO_END_ADDR  (in bsp_Cfg.h file)"                 /*�붨�����������Ž�����ַ*/
#endif

#ifndef BSP_CFG_APPLICATION_START_ADDR
  #error "Please define  BSP_CFG_APPLICATION_START_ADDR  (in bsp_Cfg.h file)"                  /*�붨��Application��ʼ��ַ*/
#endif

#ifndef BSP_CFG_APPLICATION_END_ADDR
  #error "Please define  BSP_CFG_APPLICATION_END_ADDR  (in bsp_Cfg.h file)"                    /*�붨��Application������ַ*/
#endif

#define  IAP_FLASH_PAGE_SIZE                       BSP_CFG_FLASH_PAGE_SIZE                     /*Flashҳ��С*/

#define  BOOT_START_ADDR                           BSP_CFG_BOOTLOADER_START_ADDR               /*IAP��ʼ��ַ*/
#define  BOOT_END_ADDR                             BSP_CFG_BOOTLOADER_END_ADDR                 /*IAP������ַ*/
#define  UPDATE_OP_INFO_START_ADDR                 BSP_CFG_UPDATE_OP_INFO_START_ADDR           /*����������Ϣ��ʼ��ַ*/
#define  UPDATE_OP_INFO_END_ADDR                   BSP_CFG_UPDATE_OP_INFO_END_ADDR             /*���������Ž�����ַ*/
#define  APP_START_ADDR                            BSP_CFG_APPLICATION_START_ADDR              /*Application��ʼ��ַ*/
#define  APP_END_ADDR                              BSP_CFG_APPLICATION_END_ADDR                /*Application������ַ*/
#define  APP_PAGE_SUM                              ((APP_END_ADDR-APP_START_ADDR+1)/IAP_FLASH_PAGE_SIZE)/*Applicationҳ����*/


#define  IAP_DATA_BLK_SUM_PER_CDP                  4                                           /*ÿ�����ݰ������ɱ������ٸ��飬���ݵ�Ƭ��ram��С��ʵ��ͨ���������*/  
#define  IAP_DATA_BLK_SIZE                         128                                         /*���ݿ��С���̶�Ϊ128*/
#define  IAP_DATA_BLK_SUM_PER_PAGE                 (IAP_FLASH_PAGE_SIZE/IAP_DATA_BLK_SIZE)     /*ÿҳ���ж��ٸ���*/  
#define  IAP_DATA_BLK_SUM                          (APP_PAGE_SUM*IAP_DATA_BLK_SUM_PER_PAGE)    /*���ݿ�����*/
#define  IAP_TIME_OUT_LIMIT_MS                     9000                                        /*ͨ�ų�ʱʱ�䣬��λms*/

#define  IAP_BP_BUF_SUM                            40                                          /*�ϵ㻺������������СӦ����ʵ�����ý��й���*/ 
#define  IAP_BP_SAVE_PER_PAGE                      ((APP_PAGE_SUM/IAP_BP_BUF_SUM)+1)           /*���ٸ�ҳ����һ�ζϵ㣬Flashֻ�ܰ�ҳ��������˶ϵ���С��λΪҳ�ı���*/ 
#define  IAP_BP_SAVE_PER_BLK                       (IAP_BP_SAVE_PER_PAGE*IAP_DATA_BLK_SUM_PER_PAGE) /*���ٸ����ݿ鱣��һ�ζϵ㣬Flashֻ�ܰ�ҳ��������˶ϵ���С��λΪҳ�ı���*/ 


#define  IAP_FLASH_OP_SYNC                         0xA5A5A5A5                                  /*����ͬ����ʶ*/ 

#define  IAP_FLOW_ERR                              CDP_DU_HANDLE_ERR                           /*���̴���*/ 



#define IAP_JUMP_TO_APP_WAIT_TIME                  600                                         /*��ת��Ӧ�ó���ǰ�ĵȴ�ʱ�䣬��λms*/
#define IAP_RESET_WAIT_TIME                        100                                         /*ִ�и�λ����ǰ�ĵȴ�ʱ�䣬��λms*/

/*
========================================================================================================================
*�������������Ͷ��塿                              �������������Ͷ��塿                              �������������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� :  Flash��������������Ϣ��       
************************************************************************************************************************
*/
typedef struct  
{
  uint32_t        EraseSync;                                /*����ͬ����ǣ���ʶ�����Ƿ�ɹ�*/

  uint32_t        FileCRC16RecSave;                         /*������յ��ļ�CRC16У����*/

  uint32_t        BreakPointWrStartSync[IAP_BP_BUF_SUM];    /*�ϵ�д����ͬ����� */
  uint32_t        BreakPointBuf[IAP_BP_BUF_SUM];            /*�ϵ㻺��*/
  uint32_t        BreakPointWrEndSync[IAP_BP_BUF_SUM];      /*�ϵ�д��������ͬ����� */

  uint32_t        UpdateSuccessSync;                        /*���³ɹ� ͬ�����*/

}IAP_FlashUpdateOpInfo_t;

/*
************************************************************************************************************************
* ���Ͷ��� :         
************************************************************************************************************************
*/
typedef struct  
{
  uint8_t        FlowStateLast;                             /*����״̬*/

  uint8_t        UpdateState;                               /*����״̬*/

  uint8_t        BlkNumErrCount;                            /*���ݿ�Ŵ���ͳ��*/
  uint16_t       BlkLenRec;                                 /*�յ������ݿ鳤��*/
  uint16_t       BlkNumRec;                                 /*�յ������ݿ��*/
  uint16_t       BlkNumExpect;                              /*���������ݿ��*/

  uint8_t        BreakPointEn;                              /*�ϵ�ʹ��*/
  uint16_t       FileCRC16Rec;                              /*���յ��ļ�CRC16*/
  uint16_t       FileCRC16Cal;                              /*������ļ�CRC16*/

  uint32_t       ProgramAddr;                               /*��̵�ַ*/

  uint16_t       LinkTimeOutMs;                             /*ͨ�����ӳ�ʱʱ�䣬��λ1ms*/
  
  uint16_t       JumpToAppWaitTimeMs;                       /*��ת��Ӧ�ó���ǰ�ĵȴ�ʱ�䣬��λms*/
  uint16_t       ResetWaitTimeMs;                           /*ִ�и�λ����ǰ�ĵȴ�ʱ�䣬��λms*/

}IAP_t;

/*
************************************************************************************************************************
* ���Ͷ��� :         
************************************************************************************************************************
*/
typedef  void (*pFunction)(void);


/*
************************************************************************************************************************
* ���Ͷ��� :         
************************************************************************************************************************
*/
__packed typedef  struct
{
  uint8_t        CompanyName[20];                           /*Byte 0~19:  ��˾����*/
  uint8_t        FileCRC16[2];                              /*Byte 20~21: �ļ�CRC16*/
}IAPFileHeaderInfo_t;
  


/*
========================================================================================================================
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
========================================================================================================================
*/
static  IAP_FlashUpdateOpInfo_t  *pFlashUpdateOpInfo = (IAP_FlashUpdateOpInfo_t*)UPDATE_OP_INFO_START_ADDR;
static  IAP_t                    IAP;
static  pFunction                Jump_To_Application;
static  IAPFileHeaderInfo_t      *pFileHeaderInfo;
/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : IAP_SetUpdateState                                                                                      
* �������� : ��������״̬                                                                                
* ������� : State -- ״̬��ȡֵ��IAP_UPDATE_STATE_ ��ͷ�ĺ궨��                                                                                             
* ���ز��� : ��                                                                                                    
* ����˵�� : ��
************************************************************************************************************************
*/
//static void IAP_SetUpdateState(uint8_t State)
//{
//  static uint8_t Seted = 0;
//  
//  if(0 == Seted)
//  {
//    IAP.UpdateState = State;
//    Seted = 1;    /*ÿ�θ�λ���У�ֻ��������һ��*/
//  }
//}


/*
************************************************************************************************************************
* �������� : IAP_LinkTimeOutStart                                                                                      
* �������� : ͨ�����ӳ�ʱ ����                                                                            
* ������� : ExePeriod -- ������ִ������                                                      
* ���ز��� : ��                                                                                                    
* ����˵�� : ��
************************************************************************************************************************
*/
__inline void IAP_LinkTimeOutStart(void)
{
  IAP.LinkTimeOutMs = 1;     /*��ʱʱ�����0��������������*/  
}

/*
************************************************************************************************************************
* �������� : IAP_LinkTimeOutCheckRun                                                                                      
* �������� : ͨ�����ӳ�ʱ ���                                                                          
* ������� : ExePeriod -- ������ִ������                                                      
* ���ز��� : ��                                                                                                    
* ����˵�� : ��
************************************************************************************************************************
*/
void IAP_LinkTimeOutCheck(Ticker_t ExePeriod)
{
//  if(IAP.LinkTimeOutMs)                                    /*��ʱʱ�����0��������������*/  
//  {
//    if(IAP.LinkTimeOutMs < IAP_TIME_OUT_LIMIT_MS)
//    {
//      IAP.LinkTimeOutMs += ExePeriod;
//    }
//    else
//    {
//      IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_TIMEOUT);   /*����ʧ�ܣ����ճ�ʱ*/
//    }
//  }  
}

/*
************************************************************************************************************************
* �������� : IAP_LinkTimeOutResetTime                                                                                      
* �������� : ͨ�����ӳ�ʱ  ��λʱ��                                                                   
* ������� : ��                                                     
* ���ز��� : ��                                                                                                    
* ����˵�� : ��
************************************************************************************************************************
*/
void IAP_LinkTimeOutResetTime(void)
{
  if(IAP.LinkTimeOutMs > 0) /*��ʱ���Ѿ�����*/
  {
    IAP.LinkTimeOutMs = 1;  /*����ʱ�䵽һ�����ʵ���Сֵ*/                            
  }
}


/*
************************************************************************************************************************
* �������� : IAP_CDPDataObj_0x01                                                                                      
* �������� : ֪ͨĿ��ģ�����IAPģʽ                                                                                 
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ���ĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t IAP_CDPDataObj_0x01(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
//  IAP.UpdateState = IAP_UPDATE_STATE_NONE;
//  
//  if(IAP.FlowStateLast != 0x00)
//  {
//    IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_OTHER);      /*����ʧ�ܣ�����ԭ����*/
//    return IAP_FLOW_ERR;
//  }
//  
//  IAP_LinkTimeOutStart();
//  IAP.FlowStateLast = 0x01;
//  return 2;
}

/*
************************************************************************************************************************
* �������� : IAP_CDPDataObj_0x02                                                                                      
* �������� : ��ȡĿ��ģ����������������Ϣ                                                                                 
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ���ĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t IAP_CDPDataObj_0x02(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
//  uint8_t *wp;

//  IAP_LinkTimeOutResetTime();
//  
//  if(IAP.FlowStateLast != 0x01)
//  {
//    IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_OTHER);      /*����ʧ�ܣ�����ԭ����*/
//    return IAP_FLOW_ERR;
//  }
//  
//  wp = &pAckDU[CDP_DU_OFFSET_DATA];
//  *wp++ = IAP_DATA_BLK_SUM & 0xFF;                        /*�������ݿ�����*/
//  *wp++ = IAP_DATA_BLK_SUM >> 8;
//  *wp++ = IAP_DATA_BLK_SUM_PER_CDP;                       /*ÿ�����ݰ������ɰ������ٸ���*/
//  
//  IAP.FlowStateLast = 0x02;
//  return (wp - &pAckDU[CDP_DU_OFFSET_DATA] + 2);
}

/*
************************************************************************************************************************
* �������� : IAP_CDPDataObj_0x03                                                                                      
* �������� : ֪ͨĿ��ģ��׼���ý����ļ�                                                                                 
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ���ĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t IAP_CDPDataObj_0x03(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
//  uint8_t i;
//  uint8_t *wp;
//  uint8_t OpResult;
//  
//  IAP_LinkTimeOutResetTime();
//  
//  if(IAP.FlowStateLast != 0x02)
//  {
//    IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_OTHER);                       /*����ʧ�ܣ�����ԭ����*/
//    return IAP_FLOW_ERR;
//  }

//  IAP.BlkNumExpect = 0;                                                    /*�ȼ���ϵ�Ϊ0*/
//  do
//  {
//    pFileHeaderInfo = (IAPFileHeaderInfo_t*)&pRxDU[CDP_DU_OFFSET_DATA+0];
//    
//    if(memcmp(pFileHeaderInfo->CompanyName, "EASEPAL", 7) != 0 )
//    {
//      IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_COMPANY);                   /*����ʧ�ܣ��ļ�ͷ��Ϣ�еĹ�˾���ƴ���*/
//      break;
//    }
//    
//    IAP.FileCRC16Rec   = pFileHeaderInfo->FileCRC16[1];  
//    IAP.FileCRC16Rec <<= 8;
//    IAP.FileCRC16Rec  |= pFileHeaderInfo->FileCRC16[0];  
//    IAP.BreakPointEn   = pRxDU[CDP_DU_OFFSET_DATA+128];
//    
//    if((pFlashUpdateOpInfo->EraseSync != IAP_FLASH_OP_SYNC)      ||          /*û������Ҫ����*/     
//       (pFlashUpdateOpInfo->FileCRC16RecSave != IAP.FileCRC16Rec)||          /*�ļ�CRC��ƥ�䣬�����������Ϣ*/
//       (IAP.BreakPointEn != TRUE)                                )           /*��ʹ�öϵ��������ܣ������������Ϣ*/                           
//    {
//      OpResult = SUCCESS;                                                    /*�ȼ���ɹ�*/
//      OpResult |= BSP_FLASH_Erase(UPDATE_OP_INFO_START_ADDR, 1);
//      OpResult |= BSP_FLASH_ProgramWord((uint32_t)&pFlashUpdateOpInfo->EraseSync, IAP_FLASH_OP_SYNC);        /*��ʶ�����ɹ�*/
//      OpResult |= BSP_FLASH_ProgramWord((uint32_t)&pFlashUpdateOpInfo->FileCRC16RecSave, IAP.FileCRC16Rec);  /*�����ļ�CRC*/
//      if(OpResult != SUCCESS)
//      {
//        IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_FLASH);                     /*����ʧ�ܣ�Flash�����쳣*/
//        break;
//      }
//    }
//    else /*ʹ�öϵ���������*/
//    {
//      if(IAP_FLASH_OP_SYNC == pFlashUpdateOpInfo->UpdateSuccessSync)         /*���ļ��Ѿ��ɹ�������*/
//      {
//        IAP_SetUpdateState(IAP_UPDATE_STATE_SUCCESS);                        /*�����ɹ�*/
//        IAP.FlowStateLast = 0x05;                                            /*�����ظ�������*/
//      }
//      else
//      {
//        for(i=IAP_BP_BUF_SUM; i>0; i--)                                      /*��󱣴�Ķϵ���Ϣ����λ��Խ������˴Ӻ���ǰ��������*/                      
//        {
//          if(IAP_FLASH_OP_SYNC == pFlashUpdateOpInfo->BreakPointWrEndSync[i-1]) 
//          {
//            IAP.BlkNumExpect = pFlashUpdateOpInfo->BreakPointBuf[i-1];       /*�ϵ���Чʱ��ʹ�öϵ���Ϊ��һ���������յ����ݿ����*/
//            break;
//          }  
//        }
//      }
//    }
//    IAP.ProgramAddr = APP_START_ADDR + (IAP.BlkNumExpect*IAP_DATA_BLK_SIZE); /*���ݶϵ㣬��λ��̵�ַ*/
//    
//  }while(0);
//  
//  
//  wp = &pAckDU[CDP_DU_OFFSET_DATA];
//  *wp++ = IAP.BlkNumExpect & 0xFF;                                        
//  *wp++ = IAP.BlkNumExpect >> 8;
//  
//  IAP.FlowStateLast = 0x03;
//  return (wp - &pAckDU[CDP_DU_OFFSET_DATA] + 2);
}

/*
************************************************************************************************************************
* �������� : IAP_CDPDataObj_0x04                                                                                      
* �������� : �ļ����ݿ���Ϣ                                                                                
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ���ĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t IAP_CDPDataObj_0x04(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
//  uint8_t OpResult;
//  uint8_t i;
//  uint8_t *wp;

//  IAP_LinkTimeOutResetTime();

//  if((IAP.FlowStateLast != 0x03) && 
//     (IAP.FlowStateLast != 0x04)) 
//  {
//    IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_OTHER);                                 /*����ʧ�ܣ�����ԭ����*/
//    return IAP_FLOW_ERR;
//  }
//  
//  IAP.BlkLenRec   = pRxDU[CDP_DU_OFFSET_LEN] - 4;
//  IAP.BlkNumRec   = pRxDU[CDP_DU_OFFSET_DATA+1];
//  IAP.BlkNumRec <<= 8;
//  IAP.BlkNumRec  |= pRxDU[CDP_DU_OFFSET_DATA+0];

//  if(IAP.BlkNumRec != IAP.BlkNumExpect) 
//  {
//    if(IAP.BlkNumErrCount++ > 5)                                                     /*�ۼƳ���һ�����������ݿ������������������������״̬*/
//    {
//      IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_BLKNUM);                              /*����ʧ�ܣ����ݿ���Ŵ��󣬷�ֹ��λ���ظ�һֱ����ͬһ������*/
//    }
//  } 
//  else
//  {
//    IAP.BlkNumErrCount = 0;                                                          /*���Ŵ���ͳ��*/
//    
//    if(0 == ((IAP.ProgramAddr-APP_START_ADDR) % IAP_FLASH_PAGE_SIZE))                /*ҳ����ĵ�ַ�����ҳ*/ 
//    {
//      OpResult = BSP_FLASH_Erase(IAP.ProgramAddr, 1);                                /*����Ҫ��̵�ҳ*/
//      if(OpResult != SUCCESS)
//      {
//        IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_FLASH);                             /*����ʧ�ܣ�Flash�����쳣*/
//      }
//    }
//    
//    OpResult = BSP_FLASH_ProgramData(IAP.ProgramAddr, &pRxDU[CDP_DU_OFFSET_DATA+2], IAP.BlkLenRec);    /*������ݿ�*/
//    if(OpResult != SUCCESS)
//    {
//      IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_FLASH);                               /*����ʧ�ܣ�Flash�����쳣*/
//    }
//    else                                                                             /*��ȷ���������*/
//    {
//      IAP.ProgramAddr += IAP.BlkLenRec;
//      IAP.BlkNumExpect++;                                                            /*������һ���������յ����ݿ����*/  
//      if((0 == (IAP.BlkNumExpect % IAP_BP_SAVE_PER_BLK)) &&                          /*�ж��Ƿ�ɱ���ϵ㡣*/
//         (IAP_DATA_BLK_SIZE == IAP.BlkLenRec))                                       /*��������ڹ̶��鳤�����ʾ���һ�����ݣ������Ķϵ㲻�ر�����*/
//      {
//        for(i=0; i<IAP_BP_BUF_SUM; i++)
//        {
//          if(0xFFFFFFFF == pFlashUpdateOpInfo->BreakPointWrStartSync[i])             /*�ô洢�ռ仹δ��д��*/
//          {
//            OpResult = SUCCESS;                                                      /*�ȼ���ɹ�*/
//            OpResult |= BSP_FLASH_ProgramWord((uint32_t)&pFlashUpdateOpInfo->BreakPointWrStartSync[i], IAP_FLASH_OP_SYNC); /*��ʶ��ʼ����ϵ�*/
//            OpResult |= BSP_FLASH_ProgramWord((uint32_t)&pFlashUpdateOpInfo->BreakPointBuf[i], IAP.BlkNumExpect);          /*�����ļ��ϵ�*/
//            OpResult |= BSP_FLASH_ProgramWord((uint32_t)&pFlashUpdateOpInfo->BreakPointWrEndSync[i], IAP_FLASH_OP_SYNC);   /*��ʶ��������ϵ�*/
//            if(OpResult != SUCCESS)
//            {
//              IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_FLASH);                       /*����ʧ�ܣ�Flash�����쳣*/
//            } 
//            break;
//          }
//        }
//      }    
//    }
//  }     
//  wp = &pAckDU[CDP_DU_OFFSET_DATA];
//  *wp++ = IAP.BlkNumExpect & 0xFF;    
//  *wp++ = IAP.BlkNumExpect >> 8;
//  
//  IAP.FlowStateLast = 0x04;
//  return (wp - &pAckDU[CDP_DU_OFFSET_DATA] + 2);
}

/*
************************************************************************************************************************
* �������� : IAP_CDPDataObj_0x05                                                                                      
* �������� : �ļ����ݿ鴫�����                                                                                
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ���ĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t IAP_CDPDataObj_0x05(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
//  uint8_t OpResult;
//  uint8_t *rp;
//  uint8_t *wp;
//  
//  IAP_LinkTimeOutResetTime();

//  if(IAP.FlowStateLast != 0x04) 
//  {
//    IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_OTHER);                    /*����ʧ�ܣ�����ԭ����*/
//    return IAP_FLOW_ERR;
//  }

//  rp = (uint8_t *)APP_START_ADDR;
//  IAP.FileCRC16Cal = CRC16_Cal(rp, (IAP.ProgramAddr - APP_START_ADDR), 0x00);
//  if(IAP.FileCRC16Cal != IAP.FileCRC16Rec)
//  {
//    IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_FILECRC);                  /*����ʧ�ܣ��ļ�CRC��ƥ��*/
//    BSP_FLASH_Erase(UPDATE_OP_INFO_START_ADDR, 1);                      /*�����ѱ������ز�����Ϣ*/ 
//    BSP_FLASH_ProgramWord((uint32_t)&pFlashUpdateOpInfo->EraseSync, IAP_FLASH_OP_SYNC);  /*��ʶ�����ɹ�*/
//  }
//  else
//  {
//    OpResult = BSP_FLASH_ProgramWord((uint32_t)&pFlashUpdateOpInfo->UpdateSuccessSync, IAP_FLASH_OP_SYNC); /*��ʶ�����ɹ�*/
//    if(OpResult != SUCCESS)
//    {
//      IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_FLASH);                  /*����ʧ�ܣ�Flash�����쳣*/
//    } 
//    else
//    {
//      IAP_SetUpdateState(IAP_UPDATE_STATE_SUCCESS);                     /*�����ɹ�*/
//    }
//  }

//  wp = &pAckDU[CDP_DU_OFFSET_DATA];
//  *wp++ = IAP.FileCRC16Cal & 0xFF;    
//  *wp++ = IAP.FileCRC16Cal >> 8;
//  
//  IAP.FlowStateLast = 0x05;
//  return (wp - &pAckDU[CDP_DU_OFFSET_DATA] + 2);
}

/*
************************************************************************************************************************
* �������� : IAP_CDPDataObj_0x10                                                                                      
* �������� : ȡ���������                                                                                
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ���ĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t IAP_CDPDataObj_0x10(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
//  IAP_LinkTimeOutResetTime();
//  IAP_SetUpdateState(IAP_UPDATE_STATE_FAIL_CANCEL);                       /*����ʧ�ܣ���λ��ȡ������*/
//  return 2;
}

/*
************************************************************************************************************************
* �������� : IAP_CDPDataObj_0x20                                                                                      
* �������� : ��ȡ����״̬                                                                                
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ���ĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t IAP_CDPDataObj_0x20(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
//  uint8_t *wp;

//  IAP_LinkTimeOutResetTime();

//  wp = &pAckDU[CDP_DU_OFFSET_DATA];
//  *wp++ = IAP.UpdateState;
//  
//  return (wp - &pAckDU[CDP_DU_OFFSET_DATA] + 2);
}


/*
************************************************************************************************************************
* �������� : IAP_JumpToAppSection                                                                                      
* �������� : ��ת��Ӧ�ó�������                                                                                
* ������� : ��                                                                                               
* ���ز��� : FAIL -- ��תʧ��                                                                                                    
* ����˵�� : ��
************************************************************************************************************************
*/

uint8_t tt;
uint8_t IAP_JumpToAppSection(void)
{
  uint32_t JumpAddress;

//  if(IAP_FLASH_OP_SYNC == pFlashUpdateOpInfo->EraseSync)
//  {
//    if(pFlashUpdateOpInfo->UpdateSuccessSync != IAP_FLASH_OP_SYNC)
//    {
//      return FAIL;                                            /*����в�������������ȴû�ɹ����򷵻�ʧ��*/
//    }
//  }

  /*�ж�Ӧ�ó������Ķ�ջ��ַ�Ƿ�����:0x0x08000000~0x0803FFFF�У��������Ĵ�СΪ256K���������Ƿ��Ѿ�����*/
  if (((*(__IO uint32_t*)APP_START_ADDR) & 0x2FFE0000 ) == 0x20000000)
  {
    /*��תǰ���жϣ�����Ҫ��������������תʱ���պ÷���ĳ���жϣ���תʱ�������App���������ж�������
      ����ʱApp��������û��ʼ��ʼ���ã���ɴ���������жϻ����������жϳ���ѭ��*/
    BSP_DisInttrupt();                                        /*��תǰ���жϣ�����Ҫ��*/
    //BSP_UART_DeInit();
    JumpAddress = *(__IO uint32_t*) (APP_START_ADDR + 4);     /*������ת��ַ*/
    Jump_To_Application = (pFunction) JumpAddress;            /*����ת��ַ��������ָ�����*/
    SCB->VTOR = APP_START_ADDR;                               /*�ض�λ������*/
    __set_MSP(*(__IO uint32_t*) APP_START_ADDR);              /*��ʼ���û�����Ķ�ջָ��*/
    Jump_To_Application();                                    /*��ת��Ӧ�ó�����ִ��*/
  }

  return FAIL;
}

/*
************************************************************************************************************************
* �������� : IAP_RunSectionJudge                                                                                                         
* �������� : �������ж�                                                                                  
* ������� : ��                                                                                  
* ���ز��� : ��                                                                   
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void IAP_RunSectionJudge(Ticker_t ExePeriod)
{
//  uint8_t  temp[3] = {3, 0x20, IAP_UPDATE_STATE_NO_FIRMWARE};
//  uint8_t *DUBuf[1];    /*ָ�����飬�����ڵ�ָ��ָ�򱣴�DU����(Ӧ�ð������ݳ��Ⱥ�����ID) ���ڴ��ַ��*/
//  
//  if(IAP.UpdateState != IAP_UPDATE_STATE_NONE)                        /*�������˽������ִ����IAP����*/
//  {
//    if(IAP.ResetWaitTimeMs < IAP_RESET_WAIT_TIME)
//    {
//      IAP.ResetWaitTimeMs += ExePeriod;
//    }
//    else
//    {
//      NVIC_SystemReset();                                             /*�н�����ӳ�һС��ʱ�临λϵͳ*/
//    }
//  }
//  else //if(State == IAP_UPDATE_STATE_NONE)                           /*û��ִ��IAP����*/
//  {
//    if(IAP.JumpToAppWaitTimeMs < IAP_JUMP_TO_APP_WAIT_TIME)           /*��תǰ�ĵȴ�*/
//    {
//      IAP.JumpToAppWaitTimeMs += ExePeriod;
//    }
//    else
//    {
//      if(FAIL == IAP_JumpToAppSection())                              /*��ת*/
//      {
//        DUBuf[0] = temp;
//        CDP_PDUPackTx(CDP_ADDR_CTR, CDP_CMD_UPREPORT, DUBuf, 1);      /*�����ϱ� IDΪ0x20������0x10���豸�޿����еĹ̼�������豸��������������*/
//      }
//    }
//  }
}


/*
************************************************************************************************************************
* �������� :                                                                                       
* �������� :                                                                                 
* ������� :                                                                                                
* ���ز��� :                                                                                                     
* ����˵�� : 
************************************************************************************************************************
*/
void IAP_Handle(void)
{
//  Ticker_t lag;
//  static Ticker_t  TickCount;
//  
//  lag = BSP_SysTicker_CalLag(TickCount);     /*����ʱ���*/
//  if(lag >= 100)                             /*ʱ���ֵ ���ڵ��� ִ������*/
//  {
//    TickCount += lag;
//    IAP_RunSectionJudge(100);
//    IAP_LinkTimeOutCheck(100);
//  }
}


#endif
