/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: CDP_CenApp.h                                                                                                         
**
**    ��������:	ͨ�����ݰ�   ֮   ����APP <--> ���İ塣
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
#ifndef  _CDP_CEN_APP_H
#define  _CDP_CEN_APP_H


/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "bsp.h"
#include "ESF.h"
#include "CDP_Common.h"
//#include "CDP_CenXxx.h"

/*
========================================================================================================================
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/
#define  APP_CDP_OFFSET_HEAD                     0                    /*Э�����ݵ�Ԫ�ڵ� ��ʼ�� ƫ��*/
#define  APP_CDP_OFFSET_FUNC                     1                    /*Э�����ݵ�Ԫ�ڵ� ������ ƫ��*/
#define  APP_CDP_OFFSET_LEN                      2                    /*Э�����ݵ�Ԫ�ڵ� ���ݳ��� ƫ��*/
#define  APP_CDP_OFFSET_DATA                     3                    /*Э�����ݵ�Ԫ�ڵ� ���� ƫ��*/


/*APP --> ���İ�*/
#define  APP_TO_CEN_HEAD                            0x7B      /*��ʼ��*/
#define  APP_TO_CEN_FUNC                            0xA0      /*������*/
#define  APP_TO_CEN_DATALEN                         0x02      /*���ݳ���*/

/*���İ� --> APP */
#define  CEN_TO_APP_HEAD                            0x7B      /*��ʼ��*/
#define  CEN_TO_APP_FUNC                            0xB0      /*����������  ������*/


/*
************************************************************************************************************************
* ���Ͷ��� :  ͨ�����ݰ� ���ݶ���������                                                                        
************************************************************************************************************************
*/
typedef struct
{
  uint8_t    Cmd;                   /*���ݵ�IDʶ����*/
  void     (*pDataHandle)(void);    /*���ݴ�����*/

}AppDataObjManageTabItem_t;

/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
/*����״̬��*/
#define  APP_TO_CEN_RX_STATE_SEARCH_HEAD            0         /*������ʼ��*/
#define  APP_TO_CEN_RX_STATE_JUDGE_FUNC             1         /*�жϹ�����*/
#define  APP_TO_CEN_RX_STATE_JUDGE_FRAMELEN         2         /*�ж�֡����*/
#define  APP_TO_CEN_RX_STATE_RCV_DATA               3         /*��������*/
#define  APP_TO_CEN_RX_STATE_JUDGE_SUMCHECK         4         /*�ж�У����*/ 

/*
************************************************************************************************************************
* ���Ͷ��� :  �ֿ��� <--> ���İ�   ������״̬��ʶ                                                                              
************************************************************************************************************************
*/
typedef  union 
{
  uint8_t All;
  struct
  {
    uint8_t    LinkLostFault                  :1;    /*ͨ�����Ӷ�ʧ ����*/
    uint8_t    NeedAck                        :1;
//    uint8_t    GetIDCode                      :1;
//    uint8_t    CfgNetwork                     :1;
//    uint8_t    GetSoftVersion                 :1;

  }Bit;

}CDP_CenAppCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/


/*
************************************************************************************************************************
* ���Ͷ��� :  �ֿ��� <--> ���İ�  ��ز������ݽṹ                                                                            
************************************************************************************************************************
*/
typedef struct
{
  CDP_CenAppCSFlag_t         CSFlag;
  uint8_t                    *pRxBuf;                  /*���ջ���*/               
  uint16_t                   LinkLostTimeMs;           /*ͨ�����Ӷ�ʧʱ��*/
  
  uint8_t                    CurCDPType;                        /*��ǰ ͨ�����ݰ�����*/

  CDP_FrameRx_t              FrameRx;
  //---------------------------------------------------------------------------
  uint8_t                    RxBuf[20];                        /*���ջ���*/
  uint8_t                    AckBuf[20];
  uint8_t                    RxLen;                            /*���ճ���*/

  uint8_t                    RxDataLen;                         /*���յ������ݳ���*/
  uint8_t                    RxState;                           /*����״̬*/
  uint8_t                    KeyValRx;                          /*���ռ�ֵ*/
  uint8_t                    KeyValMap;                         /*ӳ���ļ�ֵ*/
  uint8_t                    KeyValAssist;                      /*��ֵ����*/

/*���������� �����ֿ���������--------------------------------------*/
  struct
  {
    uint8_t          Head;                               /*��ʼ��*/
    uint8_t          FuncCode;                           /*������*/
    uint8_t          DataLen;                            /*���ݰ�����*/

    struct
    {
      uint8_t        SysRun                         :1;  /*ϵͳ���ػ�״̬*/ 
      uint8_t        Pause                          :1;  /*��ͣ״̬*/    
      uint8_t        MassageTimeOut                 :1;  /*��Ħ��ʱ��״̬*/ 
      uint8_t        PromptToneRun                  :1;  /*������ʾ��*/ 
      uint8_t        VenderOpFinish                 :1;  /*���Ҳ������*/ 

    }Byte5;

    struct
    {
      uint8_t        CoreXYZKneadInRun              :1;  /*���������ַ� ������*/ 
      uint8_t        CoreXYZKneadOutRun             :1;  /*���������ַ� ������*/ 
      uint8_t        CoreXYZRollRun                 :1;  /*����(����)�ַ� ������*/ 
      uint8_t        CoreXYZKneadRun                :1;  /*�����ַ� ������*/ 
      uint8_t        CoreXYZKneadStrokeRun          :1;  /*�ว�ַ� ������*/ 
      uint8_t        CoreXYZKneadPressRun           :1;  /*�ఴ�ַ� ������*/ 
      uint8_t        CoreXYZShiaRun                 :1;  /*ָѹ�ַ� ������*/ 
      uint8_t        CoreXYZStretchRun              :1;  /*��չ�ַ� ������*/ 
    }Byte6;

    struct
    {
      uint8_t        CoreTCSClap1Run                :1;  /*�Ĵ�1�ַ� ������*/ 
      uint8_t        CoreTCSClap2Run                :1;  /*�Ĵ�2�ַ� ������*/ 
      uint8_t        CoreTCSShia1Run                :1;  /*ָѹ1�ַ� ������*/ 
      uint8_t        CoreTCSShia2Run                :1;  /*ָѹ2�ַ� ������*/ 
      uint8_t        CoreTCSLTapRun                 :1;  /*���û��ַ� ������*/ 
      uint8_t        CoreTCSTapRun                  :1;  /*�û��ַ� ������*/ 
    }Byte7;

    struct
    {
      uint8_t        GasShoulderRun                 :1;  /*�粿����IO״̬*/  
      uint8_t        GasArmLeftRun                  :1;  /*�ֱ������IO״̬*/  
      uint8_t        GasArmRightRun                 :1;  /*�ֱ��ҳ���IO״̬*/  
      uint8_t        GasLumbarRun                   :1;  /*��������IO״̬*/  
      uint8_t        GasSeatRun                     :1;  /*��������IO״̬*/  
      uint8_t        GasCalvesRun                   :1;  /*�Ȳ�����IO״̬*/  
    }Byte8;

    struct
    {
      uint8_t        BackHeatRun                    :1;  /*��������IO״̬*/  
      uint8_t                                       :1; 
      uint8_t        CoreSpotState                  :1;  /*��о�ֶ����� ����״̬*/  
      uint8_t        CorePartState                  :1;  /*��о�ֶ����� ����״̬*/  
      uint8_t        CalvesRollerRunState           :1;  /*���� ִ����*/  
      uint8_t        FeetRollerRunState             :1;  /*��� ִ����*/  
      uint8_t        KeyCalvesRoller                :1;  /*���� ����*/  
      uint8_t        KeyFeetRoller                  :1;  /*���� ���*/  
    }Byte9;

    struct
    {
      uint8_t        GasIntensity                   :4;  /*����ǿ��*/  
      uint8_t        MassageIntensity               :4;  /*��Ħǿ��*/  
    }Byte10;

    struct
    {
      uint8_t        TapSpeed                       :4;  /*�û��ٶ�*/  
      uint8_t        XYZSpeed                       :4;  /*XYZ�ַ��ٶ�*/  
    }Byte11;

    struct
    {
      uint8_t        BackScanRun                    :1;  /*��������*/  
      uint8_t        BackScanFinish                 :1;  /*���������*/  
      uint8_t        ShoulderAdjustEn               :1;  /*����粿λ���ֶ�΢��ʹ��*/ 
    }Byte12;

    struct
    {
      uint8_t        KeyBackHeat                    :1;  /*���� ��������*/  
      uint8_t                                       :1; 
      uint8_t        KeyGasShoulder                 :1;  /*���� �粿����*/  
      uint8_t        KeyGasLumbarSeat               :1;  /*���� ��������*/  
      uint8_t        KeyGasArm                      :1;  /*���� �ֲ�����*/  
      uint8_t        KeyGasCalves                   :1;  /*���� �Ȳ�����*/  
      uint8_t        KeyGasFull                     :1;  /*���� ȫ�����*/    
      uint8_t        KeyGasQuick                    :1;  /*���� ���ٳ���*/    
    }Byte13;

    struct
    {
      uint8_t        KeyXYZAction                   :8;  /*���� XYZ�ֶ�����*/  
    }Byte14;

    struct
    {
      uint8_t        KeyTCSAction                   :8;  /*���� TCS�ֶ�����*/  
    }Byte15;

    struct
    {
      uint8_t        KeyAuto                        :8;  /*���� �Զ�����*/  
    }Byte16;

    struct
    {
      uint8_t        keep                           :7;  
      uint8_t        KeyHomeReset                   :1;  /*��λ״̬*/  
    }Byte17;

    struct
    {
      uint8_t        CoreXPosition                  :4;  /*��оX������(0-2)*/  
      uint8_t        CoreZPosition                  :4;  /*��оZ������(0-7)*/  
    }Byte18;

    struct
    {
      uint8_t        KeyBackUpFeetDown              :1;  /*���� ���� ��*/  
      uint8_t        KeyBackDownFeetUp              :1;  /*���� ���� ��*/  
      uint8_t        KeyFeetUp                      :1;  /*���� С�� ��*/  
      uint8_t        KeyFeetDown                    :1;  /*���� С�� ��*/  
      uint8_t        KeyLegExtend                   :1;  /*���� ����*/  
      uint8_t        KeyLegShorten                  :1;  /*���� ����*/  
      uint8_t        KeyZero1                       :1;  /*������1*/  
      uint8_t        KeyZero2                       :1;  /*������2*/ 
    }Byte19;


    struct
    {
      uint8_t        KeyCoreMannualUp               :1;  /*���� ��о ����*/  
      uint8_t        KeyCoreMannualDown             :1;  /*���� ��о ����*/  
      uint8_t        KeyCoreWidthDec                :1;  /*���� ��о ��խ*/  
      uint8_t        KeyCoreWidthAdd                :1;  /*���� ��о ����*/ 
      
      uint8_t        LedLogoRun                     :1;  /*Logo��IO״̬*/  
      uint8_t        LedProjectionRun               :1;  /*ӭ����IO״̬*/  
      uint8_t        KeyLed                         :1;  /*LED�ư���״̬*/  
      
    }Byte20;


    struct
    {
      uint8_t        CoreYPosition                  :8;  /*��оY������(0-36)*/  
    }Byte21;

    int8_t           CoreLeftTemp;                       /*��Ħͷ�¶�*/
    int8_t           CoreRightTemp;                      /*�Ұ�Ħͷ�¶�*/

    uint8_t          MassageTimeSec;                     /*��Ħʣ��ʱ��*/
    uint8_t          MassageTimeMin;                     /*��Ħʣ��ʱ��*/
    uint8_t          PromptToneAddr;                     /*��ʾ����ַ*/ 
    
    struct
    {
      uint8_t                                       :1;  
      uint8_t        WIFINetCfgOK                   :1;  /*WIFI�������*/  
      uint8_t                                       :6;  
    }Byte27;
    
    uint8_t          FaultCodeBit[10];                   /*����λ*/

    uint8_t         SumCode;                             /*У����*/

  }TxBuf; /*���������� �����ֿ���������*/

}CDP_CenApp_t;

/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/

void CDP_CenTmrToApp_DataTx(Ticker_t ExePeriod);
void CDP_CenApp_FaultCheck(Ticker_t ExePeriod);
uint8_t CDP_CenApp_DataTx(ESF_Evt_t *pEvt);
CDP_CenApp_t* CDP_CenApp_Init(void);
CDP_CenAppCSFlag_t CDP_CenApp_GetCSFlag(void);
#endif
