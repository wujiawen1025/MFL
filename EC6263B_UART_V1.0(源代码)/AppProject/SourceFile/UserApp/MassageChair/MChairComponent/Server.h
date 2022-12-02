/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: Server.h                                                                                                         
**
**    ��������: ��������
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
#ifndef  _SERVER_H
#define  _SERVER_H

/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "bsp.h"
#include "CDP.h"



/*
========================================================================================================================
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/
#define  UNABLE_REMOTE_UPGRADES                             0                    /*��֧��Զ������*/ 
#define  NEED_CACHE_REMOTE_UPGRADES                         1                    /*����ͨ��ͨѶģ�黺�������ļ�*/ 
#define  IMMEDIATE_REMOTE_UPGRADES                          2                    /*ֱ��͸������*/ 


 

/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/

/*
************************************************************************************************************************
* ���Ͷ��� :                                                                         
************************************************************************************************************************
*/
typedef struct
{
  uint8_t                      ID;
  uint8_t                      KeyVal;                         /*��Ӧ�ļ�ֵ*/
  uint8_t                      (*pVoiceKey)(uint8_t *pData);   /*������ֵ���Ӳ���*/

}ServerLogic_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  0x0040 ��Ħ�ε������к�                                                           
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint8_t             IDCode[20];       /*�������к�*/

}CDP_DataFormat0x0040_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  0x0042                                                            
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint8_t             CodeVER[30];       /*����汾��*/

}CDP_DataFormat0x0042_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  0x0043                                                            
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint8_t             UpdataWay;        /*������ʽ*/

}CDP_DataFormat0x0043_t;


/*
************************************************************************************************************************
* ���Ͷ��� :  0x004C ��Ħ�ι�����
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint8_t             FaultCodeBit[10];                   /*����λ*/
  
}CDP_DataFormat0x004C_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  0x004D ��Ħ�ε������ʱ��
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint16_t            SysRunTimeHour;                     /*ϵͳ����ʱ��*/
  uint16_t            XMotorRunTimeHour;                  /*X�������ʱ��*/
  uint16_t            YMotorRunTimeHour;                  /*Y�������ʱ��*/
  uint16_t            ZMotorRunTimeHour;                  /*Z�������ʱ��*/
  uint16_t            TCSMotorRunTimeHour;                /*�û��������ʱ��*/
  uint16_t            BackSpikeMotorRunTimeHour;          /*�����Ƹ��������ʱ��*/
  uint16_t            FeetSpikeMotorRunTimeHour;          /*С���Ƹ��������ʱ��*/
  
}CDP_DataFormat0x004D_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  0x0702 ��Ħ�ΰ�������
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint8_t             KeyVal;                                      /*��ֵ*/
  uint8_t             AddtionData[1];                              /*��ֵ������������*/
  
}CDP_DataFormat0x0702_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  0x0912 ��Ħ����������
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint8_t             IntCfgData[67];
  
}CDP_DataFormat0x0912_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  0x0C60 ��Ħ��״̬
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint8_t             SystemState;
  
}CDP_DataFormat0x0C60_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  0x0D01 ��Ħ��״̬����1
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t        SysRun                         :1;  /*ϵͳ���ػ�״̬*/ 
      uint8_t        Pause                          :1;  /*��ͣ״̬*/    
      uint8_t        MassageTimeOut                 :1;  /*��Ħ��ʱ��״̬*/ 
    }Bit;
  }Byte1; 
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t        CoreXYZKneadInRun              :1;  /*���������ַ� ������*/ 
      uint8_t        CoreXYZKneadOutRun             :1;  /*���������ַ� ������*/ 
      uint8_t        CoreTCSLTapRun                 :1;  /*���û��ַ� ������*/ 
      uint8_t        CoreTCSTapRun                  :1;  /*�û��ַ� ������*/ 
      uint8_t        CoreTCSClap1Run                :1;  /*�Ĵ�1�ַ� ������*/ 
      uint8_t        CoreTCSClap2Run                :1;  /*�Ĵ�2�ַ� ������*/ 
    }Bit;
  }Byte2; 
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t        CoreTCSShia1Run                :1;  /*ָѹ1�ַ� ������*/ 
      uint8_t        CoreTCSShia2Run                :1;  /*ָѹ2�ַ� ������*/
      uint8_t        CoreXYZRollRun                 :1;  /*����(����)�ַ� ������*/ 
    }Bit;
  }Byte3; 
  
  uint8_t Byte4;
  uint8_t Byte5;
  uint8_t Byte6;
  uint8_t Byte7;
  uint8_t Byte8;
  uint8_t Byte9;
  uint8_t Byte10;
  uint8_t Byte11;
  uint8_t Byte12;
  uint8_t Byte13;
  uint8_t Byte14;
  uint8_t Byte15;
  uint8_t Byte16;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t        KeyAuto                        :6;  /*���� �Զ�����*/  
    }Bit;
  }Byte17;

  uint8_t Byte18;
  uint8_t Byte19;
  uint8_t Byte20;
  uint8_t Byte21;
  uint8_t Byte22;
  uint8_t Byte23;
  uint8_t Byte24;
  uint8_t Byte25;
  uint8_t Byte26;
  uint8_t Byte27;
  uint8_t Byte28;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t        MassageTimeMin                 :6;  /*��Ħʣ��ʱ��*/
    }Bit;
  }Byte29;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t        MassageTimeSec                 :6;  /*��Ħʣ��ʱ��*/
    }Bit;
  }Byte30;
  
}CDP_DataFormat0x0D01_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  0x0D02 ��Ħ��״̬����2
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID[2];
  
  uint8_t Byte1;
  uint8_t Byte2;
  uint8_t Byte3;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t                                       :1;
      uint8_t          WIFIIntCfg                   :1;
      uint8_t          ResetOK                      :1;
    }Bit;
  }Byte4;
  
  uint8_t Byte5;
  
}CDP_DataFormat0x0D02_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  ���� ������״̬��ʶ                                                                        
************************************************************************************************************************
*/
typedef struct
{
//  uint8_t        GetIDCodeQry                :1;
  uint8_t        KeyExeState                 :1;   /*����ִ�н��״̬*/
  
  uint8_t        WIFIIntCfg                  :1;   /*WIFI������״̬*/
  
  uint8_t        NetDataRx                   :1;   /*�������ݽ���״̬*/
  
  uint8_t        UpDataSuc_0x0040            :1;   /*�ϱ������� �������к� �ɹ�*/
  uint8_t        UpDataSuc_0x0042            :1;   /*�ϱ������� ���İ����汾�� �ɹ�*/
  uint8_t        UpDataSuc_0x0043            :1;   /*�ϱ������� ������ʽ �ɹ�*/
  
}ServerCSFlag_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  ���Ȳ���������ݽṹ                                                                          
************************************************************************************************************************
*/
typedef struct
{
  ServerCSFlag_t            CSFlag;                           /*������״̬��ʶ*/

  uint8_t                   IntDataLen;                       /*�������ݳ���*/
  
  CDP_DataFormat0x0040_t    SetQry0x0040;                     /*��Ħ�ε������к�*/
  CDP_DataFormat0x0042_t    SetQry0x0042;
  CDP_DataFormat0x0043_t    SetQry0x0043;

  CDP_DataFormat0x004C_t    SetQry0x004C;                     /*��Ħ�ι�����*/
  CDP_DataFormat0x004D_t    SetQry0x004D;                     /*��Ħ�ε������ʱ��*/
  CDP_DataFormat0x0912_t    SetQry0x0912;                     /*��������*/
  
  CDP_DataFormat0x0D01_t    SetQry0x0D01;                     /*��Ħ�ο���״̬����1*/
  CDP_DataFormat0x0D02_t    SetQry0x0D02;                     /*��Ħ�ιػ�״̬����2*/
}Server_t;

/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/
/*��ʼ��--------------------------------------*/
Server_t* Server_Init(void);


/*����ִ��--------------------------------------*/


/* ����Ľӿڣ� �� ����ģ�� �ɶ� ��ģ��ִ�е� ���Ʋ���*/
uint8_t* Server_CDPDataObjTx_0x0040(void);
uint8_t* Server_CDPDataObjTx_0x0042(void);
uint8_t* Server_CDPDataObjTx_0x0043(void);
uint8_t* Server_CDPDataObjTx_0x0041(void);
uint8_t* Server_CDPDataObjTx_0x004C(void);
uint8_t* Server_CDPDataObjTx_0x004D(void);
uint8_t* Server_CDPDataObjTx_0x0912(void);
uint8_t* Server_CDPDataObjTx_0x0D01(void);
uint8_t* Server_CDPDataObjTx_0x0D02(void);

uint8_t Server_CDPDataObjRX_0x0040(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0042(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0043(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0702(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0901(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0912(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0913(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0C60(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0D01(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);
uint8_t Server_CDPDataObjRX_0x0D02(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);

void Server_SetKeyExeState(uint8_t TrueFalse);
void Server_SetIntData(uint8_t *data, uint8_t len, uint8_t reconfiguration);
void Server_SetIntState(uint8_t TrueFalse);
void Server_ReReportedData(void);

ServerCSFlag_t Server_GetCSFlag(void);
#endif
