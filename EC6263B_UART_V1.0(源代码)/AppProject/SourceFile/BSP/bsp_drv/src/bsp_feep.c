/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: bsp_feep.c                                                                                                        
**
**    ��������: ʹ��Flashģ��EEPROM                                                                                                        
**
**    ��    ˾:                                                                                                       
**
**    ��Ŀ����:                                                                                                       
**
**    ƽ̨��Ϣ:                                                                                                        
**
**    ��    ��: LZH                                                                                                     
**
**    ����˵��:                                                                                                         
**
**    �޸ļ�¼: --------------------------------------------------------------
**              2016.08    
**              ��� V1.0 �汾
**
========================================================================================================================
========================================================================================================================
*/

/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "bsp_feep.h"          



/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/
#ifndef BSP_CFG_FLASH_PAGE_SIZE
  #error "Please define  BSP_CFG_FLASH_PAGE_SIZE  (in bsp_Cfg.h file)"                    /*�붨��FLASHҳ�Ĵ�С*/
#endif

#ifndef BSP_CFG_FLASH_END_ADDR
  #error "Please define  BSP_CFG_FLASH_END_ADDR  (in bsp_Cfg.h file)"                     /*�붨��FLASH�Ľ�����ַ*/
#endif


#define  FEEP_PAGE_SIZE                 BSP_CFG_FLASH_PAGE_SIZE                           /*ҳ��С*/
#define  FEEP_START_ADDRESS             ((BSP_CFG_FLASH_END_ADDR+1) - (FEEP_PAGE_SIZE*2)) /*FlashģʽEEP����ʼ��ַ�������ҳ����ģ��EEP */


#define  FEEP_PAGE0_START_ADDR          (FEEP_START_ADDRESS + 0)                          /*ģ��EEPҳ0��ʼ��ַ*/ //0x0803EFFF
#define  FEEP_PAGE0_END_ADDR            (FEEP_PAGE0_START_ADDR + (FEEP_PAGE_SIZE - 1))    /*ģ��EEPҳ0������ַ*/
#define  FEEP_PAGE1_START_ADDR          (FEEP_PAGE0_END_ADDR + 1)                         /*ģ��EEPҳ1��ʼ��ַ*/ //0x0803F7FF
#define  FEEP_PAGE1_END_ADDR            (FEEP_PAGE1_START_ADDR + (FEEP_PAGE_SIZE - 1))    /*ģ��EEPҳ1������ַ*/


#define  FEEP_OP_SYNC                   0xA5A5A5A5                                        /*����ͬ����ʶ*/ 


#ifndef  BSP_CFG_FEEP_BLK_SIZE
#define  BSP_CFG_FEEP_BLK_SIZE          128                                               /*Ҫ��������ݿ��С,��λ�ֽ�*/ 
#endif


/*����оƬ��ʵ������������ݿ�Ĵ�С����ҳ���ܹ�֧�ֵ����ݿ�����*/
#if (FEEP_PAGE_SIZE == 512)                            
  #if (BSP_CFG_FEEP_BLK_SIZE <= 64)
    #define  FEEP_BLK_SIZE              64                                                
    #define  FEEP_BLK_SUM               6                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 128)
    #define  FEEP_BLK_SIZE              128                                                
    #define  FEEP_BLK_SUM               3                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 256)
    #define  FEEP_BLK_SIZE              256                                                
    #define  FEEP_BLK_SUM               1                                                 
  #else 
    #define  FEEP_BLK_SIZE              480                                              
    #define  FEEP_BLK_SUM               1                                                 
  #endif

#elif (FEEP_PAGE_SIZE == 1024)                            
  #if (BSP_CFG_FEEP_BLK_SIZE <= 64)
    #define  FEEP_BLK_SIZE              64                                                
    #define  FEEP_BLK_SUM               12                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 128)
    #define  FEEP_BLK_SIZE              128                                                
    #define  FEEP_BLK_SUM               6                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 256)
    #define  FEEP_BLK_SIZE              256                                                
    #define  FEEP_BLK_SUM               3                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 512)
    #define  FEEP_BLK_SIZE              512                                               
    #define  FEEP_BLK_SUM               1                                                 
  #else 
    #define  FEEP_BLK_SIZE              960                                              
    #define  FEEP_BLK_SUM               1                                                 
  #endif
  
#elif (FEEP_PAGE_SIZE == 2048)
  #if (BSP_CFG_FEEP_BLK_SIZE <= 64)
    #define  FEEP_BLK_SIZE              64                                                
    #define  FEEP_BLK_SUM               26                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 128)
    #define  FEEP_BLK_SIZE              128                                                
    #define  FEEP_BLK_SUM               14                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 256)
    #define  FEEP_BLK_SIZE              256                                                
    #define  FEEP_BLK_SUM               7                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 512)
    #define  FEEP_BLK_SIZE              512                                               
    #define  FEEP_BLK_SUM               3                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 1024)
    #define  FEEP_BLK_SIZE              1024                                               
    #define  FEEP_BLK_SUM               1                                                 
  #else 
    #define  FEEP_BLK_SIZE              1984                                              
    #define  FEEP_BLK_SUM               1                                                 
  #endif
#else  //128*1024
  #if (BSP_CFG_FEEP_BLK_SIZE <= 64)
    #define  FEEP_BLK_SIZE              64                                                
    #define  FEEP_BLK_SUM               120                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 128)
    #define  FEEP_BLK_SIZE              128                                                
    #define  FEEP_BLK_SUM               60                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 256)
    #define  FEEP_BLK_SIZE              256                                                
    #define  FEEP_BLK_SUM               30                                                 
  #elif (BSP_CFG_FEEP_BLK_SIZE <= 512)
    #define  FEEP_BLK_SIZE              512                                               
    #define  FEEP_BLK_SUM               10                                                 
  #else 
    #define  FEEP_BLK_SIZE              960                                              
    #define  FEEP_BLK_SUM               10                                                 
  #endif
    
#endif



/*
========================================================================================================================
*�������������Ͷ��塿                              �������������Ͷ��塿                              �������������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� : Flashģ��EEP             
* ע��1��Flash���һ�����ٰ���(2�ֽ�)����˽ṹ���ڳ�������ı�����С����Ϊ2�ֽ����ͣ��Ա�֤����2�ֽڶ��롣
*        Ϊ��֤�Ϻõ�ͨ���ԣ����б���ȫ������Ϊ4�ֽڴ�С�����ͣ��е�оƬ���һ������ȫ��4�ֽڣ����˼������KE����
* ע��2��Flash����Ҫ������ֻ��ҳ������������ɺ��ִ�а��ֻ��ֱ�̲��ݣ�
*        ��ÿ����ַ��Ԫֻ��ִ��һ�Σ���Ҫִ�еڶ��α�̲��ݣ���������²�����
*        ��Flash�Ĳ����������������ϵľ���ͻȻ���磬���²���ʧ�ܡ�
*        ���Ҫ���ڲ��������г��ֵĵ�Դ����Ȼ�������ϵ��¼�������
*        ���Խṹ���������ͬ����ǣ�������ʶ��Ӧ�Ĳ����Ƿ�ɹ���ɡ� 
* ע��3�������е�FlashStatus״̬�ж���ʵû������塣����Flash�ﵽʹ������������ԭ����ϡ�
*        �����Ĵ������߼���Ҫ������˫ҳ��ҳ�ڶ����ݿ������㷨���Flash��ʹ��������
*        ���о���ͬ�����Ӧ�Ե��������ɵ�Flash����ʧ�ܡ�
************************************************************************************************************************
*/
typedef struct  
{
  uint32_t        ActiveCount;                              /*�������32λ�ļ���ֵ����ֵ��Ĵ���ǰ�ҳ */
  uint32_t        EraseSync;                                /*����ͬ����ǣ���ʶ�����Ƿ�ɹ�*/

  uint32_t        WrStartSync[FEEP_BLK_SUM];                /*д������ʼͬ����� */
  uint32_t        WrEndSync[FEEP_BLK_SUM];                  /*д��������ͬ����� */
  uint32_t        Block[FEEP_BLK_SUM][FEEP_BLK_SIZE/4];     /*���ݴ洢�飬��ֵ���Ͷ���Ϊuint32_t��Ȼ���СFEEP_BLK_SIZE/4����֤4�ֽڶ��롣*/
}BSP_FlashEEP_t;


/*
========================================================================================================================
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
========================================================================================================================
*/
static BSP_FlashEEP_t  *pFEEPPage0 = (BSP_FlashEEP_t*)FEEP_PAGE0_START_ADDR;
static BSP_FlashEEP_t  *pFEEPPage1 = (BSP_FlashEEP_t*)FEEP_PAGE1_START_ADDR;

static BSP_FlashEEP_t  *pFEEPPageActive;    /*��ǰ���ҳ*/

/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : BSP_FEEP_Init                                                                                      
* �������� : Flashģ��EEP��ʼ��                                                                                               
* ������� : ��                                                                                               
* ���ز��� : Flash�Ĳ������                                                                                                         
* ����˵�� : �ú����ڵ��ж��봦���߼���Ҫ���ڶԵ�������Ĺ���ҳ���һ��ʹ��ҳ�����лָ���������������д����س�ʼ���ݣ���                                                                                                        
************************************************************************************************************************
*/
uint16_t BSP_FEEP_Init(void)
{
  uint16_t  FlashStatus;
  
  BSP_DisInttrupt();  

  pFEEPPageActive = (void*)0;
  do
  {
    if(pFEEPPage0->EraseSync != FEEP_OP_SYNC)                                              /*û������Ҫ����*/     
    {
      FlashStatus = BSP_FLASH_Erase(FEEP_PAGE0_START_ADDR);
      if (FlashStatus != SUCCESS)
      {
        break;
      }

      FlashStatus = BSP_FLASH_ProgramWord((uint32_t)&pFEEPPage0->EraseSync, FEEP_OP_SYNC);/*��ʶ�����ɹ�*/
      if (FlashStatus != SUCCESS)
      {
        break;
      }
    }

    if(pFEEPPage1->EraseSync != FEEP_OP_SYNC)                                              /*û������Ҫ����*/            
    {
      FlashStatus = BSP_FLASH_Erase(FEEP_PAGE1_START_ADDR);
      if (FlashStatus != SUCCESS)
      {
        break;
      }
      
      FlashStatus = BSP_FLASH_ProgramWord((uint32_t)&pFEEPPage1->EraseSync, FEEP_OP_SYNC);/*��ʶ�����ɹ�*/
      if (FlashStatus != SUCCESS)
      {
        break;
      }
    }

    if(0xFFFFFFFF == pFEEPPage0->ActiveCount)                                              /*�������Ч*/ 
    {
      FlashStatus = BSP_FLASH_ProgramWord((uint32_t)&pFEEPPage0->ActiveCount, 0);         /*д��ҳĬ�ϵĵ�һ�λ����*/
      if (FlashStatus != SUCCESS)
      {
        break;
      }
    }
    
    if(0xFFFFFFFF == pFEEPPage1->ActiveCount)                                              /*�������Ч*/         
    {
      FlashStatus = BSP_FLASH_ProgramWord((uint32_t)&pFEEPPage1->ActiveCount, 1);         /*д��ҳĬ�ϵĵ�һ�λ����*/
      if (FlashStatus != SUCCESS)
      {
        break;
      }
    }
    
    if(pFEEPPage0->ActiveCount > pFEEPPage1->ActiveCount)                                  /*�����Խ��ģ�����ǰ�ҳ*/
    {
      pFEEPPageActive = pFEEPPage0;  
    }
    else
    {
      pFEEPPageActive = pFEEPPage1;  
    }
  }while(0);
  
  BSP_EnInttrupt();  
  return FlashStatus;
}

/*
************************************************************************************************************************
* �������� : BSP_FEEP_Write                                                                                      
* �������� : Flashģ��EEPд����                                                                                               
* ������� : pDada -- ָ��Ҫд������                                                                                               
*            Len   -- Ҫд�ĳ���
* ���ز��� : Flash�Ĳ������                                                                                                         
* ����˵�� : ʵ��ԭ������˫ҳ��ҳ�ڶ����ݿ������㷨���Flash��ʹ��������
*                      ��Flash�ֳ����ɷݵȴ��Block����飬Խ�µ����ݱ���λ��Խ����
*                      ��pFEEPPageActive�ҳ�ڵ�Block������þ��󣬻������һ��FEEPPageҳ�������ݱ��浽��һҳ�С�
*                      �����ɹ��󣬽���һҳ����Ϊ��ǰpFEEPPageActive�ҳ��
*            д���̣�(1)д WrStartSync = FEEP_OP_SYNC;�Ա��д������ʼִ�С�
*                       Flash������ֻ��дһ�Σ����ÿ���洢�鶼Ҫ��WrStartSync����Ƿ���ִ�й�д������
*                    (2)д���������ݡ�
*                    (3)д WrEndSync = FEEP_OP_SYNC;�Ա��д������ɡ�
*                       д���ݹ����п��ܷ������磬�������д�벻���������Ҫ��WrEndSync��������Ƿ��������档
*                       ��������ʹ�øñ���жϱ���������Ƿ��������á�
*                    (4)���������ҳ�����������дActiveCount����ֵ���Ա���µĻҳ��
*                       �ⲽ����Ҳ������Ϊ�����ʧ�ܣ����BSP_FEEP_Init()��������������������жϡ�
*                       ��ActiveCount��Ч��ҳ�����ʼ��ΪĬ�ϵ���Сֵ��
*
*            Ӧ�ý�Ӧ�ó�������Ҫ���籣������ݷ�װ��һ���ṹ��ͳһ����pDadaָ��ýṹ������ݣ�����Ҫ��ɢ������  
************************************************************************************************************************
*/
uint16_t BSP_FEEP_Write(void *pDada, uint16_t Len)
{
  uint16_t FlashStatus;
  uint8_t  i;
  uint32_t TmpData;
  uint8_t  *rp, *wp;
  uint32_t WriteAddr;
  uint32_t EndAddr;
  BSP_FlashEEP_t  *pWrFEEPPage;                        /*��¼Ҫִ��д������ҳ*/

  
  for(i=0; i<FEEP_BLK_SUM; i++)
  {
    if(0xFFFFFFFF == pFEEPPageActive->WrStartSync[i])  /*��Block�洢�黹δ��д��*/
    {
      pWrFEEPPage = pFEEPPageActive;                  
      break;
    }
  }
  if(i >= FEEP_BLK_SUM)                                /*��ǰ�ҳ��Block�洢��������*/
  {
    i = 0;                                             /*��ҳ��Block�洢��������ͷ��ʼ*/  
    pWrFEEPPage = (pFEEPPage0 == pFEEPPageActive) ? pFEEPPage1 : pFEEPPage0;
  }
  
  BSP_DisInttrupt();  

  rp = pDada;
  do
  {
    /*������ҳ���������һҳ---------------------------------------------*/
    if(pFEEPPageActive != pWrFEEPPage)  
    {
      WriteAddr = (pFEEPPage0 == pFEEPPageActive) ? FEEP_PAGE1_START_ADDR : FEEP_PAGE0_START_ADDR;
      FlashStatus = BSP_FLASH_Erase(WriteAddr);
      if (FlashStatus != SUCCESS)
      {
        break;
      }
      
      FlashStatus = BSP_FLASH_ProgramWord((uint32_t)&pWrFEEPPage->EraseSync, FEEP_OP_SYNC);    /*��ʶ�����ɹ�*/
      if (FlashStatus != SUCCESS)
      {
        break;
      }
    }
    
    /*д������--------------------------------------------------------*/
    FlashStatus = BSP_FLASH_ProgramWord((uint32_t)&pWrFEEPPage->WrStartSync[i], FEEP_OP_SYNC); /*��ǿ�ʼִ��д����*/  
    if (FlashStatus != SUCCESS)
    {
      break;
    }
    
    WriteAddr = (uint32_t)&pWrFEEPPage->Block[i][0];
    Len = (Len < FEEP_BLK_SIZE) ? Len:FEEP_BLK_SIZE;
    EndAddr   = WriteAddr + Len;
    while(WriteAddr < EndAddr)
    {
      /***************************************************************************************
       * ע�⣺����֮������ô�鷳��ԭ����pDadaָ��ĵ�ַ��һ����4�ֽڶ���ġ�
       * ������ָ������uint8_t�����飬����������׵�ַ����պ���1�ֽڶ���ġ���ʱ���ֱ��ʹ���������µĴ��룺
       *   uint32_t *rp;
       *   rp = pDada;
       *   BSP_FLASH_ProgramWord(WriteAddr, *rp);   
       * �����ڲ���*rpָ��uint32_t���ͣ�Ҫ���ַ4�ֽڶ��룬��ʵ�����ȴ��ָ���4�ֽڶ����ַ��
       * ��ʱ�ô����ִ�н����HardFault_Handler�쳣�������쳣�����ԭ����ʹ�ò�����ķ�ʽ���ڴ���з��ʡ�
       * ����������Ӻü���������ת����������Ӧ�����ֵ�ַ�Ƕ��������
       * ͬ���������*rpָ��uint16_t���ͣ�Ҫ���ַ2�ֽڶ��롣�������Ƶķ���ת����  
       * ��չ��ϵ����ǰʹ��OS���ڴ��ʱ��OS�ڲ�ʹ�õ�Ƭ�������λ��Ϊ���Ͷ������飨32λ�Ͷ���Ϊuint32_t�������飩��
       *           Ȼ���ϲ�Ӧ�ÿ�ʹ���ڴ����������ָ������ǿ��ת����������ɷǶ�������쳣��
       *           ��Ϊ4�ֽڶ���ĵ�ַ�ض�Ҳ��2�ֽڶ���ģ��κε�ַ�ض���1�ֽڶ���ġ������Щ�������໥����ת����
       *           �������OS�ڲ�ʹ��uint8_t��������Ļ�����ָ��ǿ��ת��ʱ���ض����׳��ַǶ�����ʵ��쳣��
       ***************************************************************************************/
      wp = (uint8_t*)&TmpData;
      *wp++ = *rp++;
      *wp++ = *rp++;
      *wp++ = *rp++;
      *wp++ = *rp++;
      FlashStatus = BSP_FLASH_ProgramWord(WriteAddr, TmpData);    
      if (FlashStatus != SUCCESS)
      {
        break;
      }
      WriteAddr += 4;
    }
    
    FlashStatus = BSP_FLASH_ProgramWord((uint32_t)&pWrFEEPPage->WrEndSync[i], FEEP_OP_SYNC);   /*������д����*/      
    if (FlashStatus != SUCCESS)
    {
      break;
    }
    
    /*������ҳ���������ҳ�Ļ������������Ϊ��ǰ�ҳ---------------*/
    if(pFEEPPageActive != pWrFEEPPage) 
    {
      FlashStatus = BSP_FLASH_ProgramWord((uint32_t)&pWrFEEPPage->ActiveCount, (pFEEPPageActive->ActiveCount+1)); /*д��ҳĬ�ϵĵ�һ�λ����*/
      if (FlashStatus != SUCCESS)
      {
        break;
      }
      pFEEPPageActive = pWrFEEPPage;
    }    
  }while(0);
  
  BSP_EnInttrupt();  
  return FlashStatus;
}

/*
************************************************************************************************************************
* �������� : BSP_FEEP_Read                                                                                      
* �������� : Flashģ��EEP������                                                                                               
* ������� : pDada -- ��������Ҫ��ŵĵ�ַ     
*            Len   -- Ҫ���ĳ���
* ���ز��� : SUCCESS -- ���ɹ�
*            FAIL    -- ��ʧ��
* ����˵�� : Ӧ�ý�Ӧ�ó�������Ҫ���籣������ݷ�װ��һ���ṹ��ͳһ����pDadaָ��ýṹ������ݣ�����Ҫ��ɢ������  
************************************************************************************************************************
*/
uint8_t  BSP_FEEP_Read(void *pDada, uint16_t Len)
{
  uint8_t i;
  uint8_t *wp;
  uint32_t ReadAddr;
  uint32_t EndAddr;

  wp = pDada;
  for(i=FEEP_BLK_SUM; i>0; i--)                           /*Խ�µ����ݱ���Խ������˴Ӻ���ǰ��������*/
  {
    if(FEEP_OP_SYNC == pFEEPPageActive->WrEndSync[i-1])   /*д��������ͬ�������Ч������������������*/
    {
      ReadAddr = (uint32_t)&pFEEPPageActive->Block[i-1][0];
      Len = (Len < FEEP_BLK_SIZE) ? Len:FEEP_BLK_SIZE;
      EndAddr  = ReadAddr + Len;
      while(ReadAddr < EndAddr)
      {
        *wp++ = *(uint8_t*)ReadAddr;
        ReadAddr++;
      }
      return SUCCESS;
    }
  }  
  
  return FAIL;
}
