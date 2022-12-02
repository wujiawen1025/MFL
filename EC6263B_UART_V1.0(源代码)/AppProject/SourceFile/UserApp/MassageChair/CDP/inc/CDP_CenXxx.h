/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: CDP_CenXxx.h                                                                                                         
**
**    ��������:	ͨ�����ݰ�   ֮   �ֿ��� ��о�� С�Ȱ� ��� <--> ���İ塣
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
#ifndef  _CDP_CEN_CTRL_H
#define  _CDP_CEN_CTRL_H


/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "bsp.h"
#include "ESF.h"
#include "CDP_Common.h"

/*
========================================================================================================================
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/
/*����״̬��*/
#define  CTRL_TO_CEN_RX_STATE_SEARCH_HEAD            0         /*������ʼ��*/
#define  CTRL_TO_CEN_RX_STATE_JUDGE_ADDR             1         /*�жϵ�ַ��*/
#define  CTRL_TO_CEN_RX_STATE_JUDGE_FUNC             2         /*�жϹ�����*/
#define  CTRL_TO_CEN_RX_STATE_JUDGE_FRAMELEN         3         /*�ж�֡����*/
#define  CTRL_TO_CEN_RX_STATE_RCV_DATA               4         /*��������*/
#define  CTRL_TO_CEN_RX_STATE_JUDGE_SUMCHECK         5         /*�ж�У����*/ 


/*�ֿ��� --> ���İ�*/
#define  CTRL_TO_CEN_HEAD                            0xAA      /*��ʼ��*/
#define  CTRL_TO_CEN_ADDR                            0x01      /*��ַ��*/
#define  CTRL_TO_CEN_FUNC                            0xA0      /*������*/
#define  CTRL_TO_CEN_FRAMELEN                        0x0A      /*֡����*/
#define  CTRL_TO_CEN_DATALEN                         0x05      /*���ݳ���*/

#define  CTRL_TO_CEN_ADDR_OFFSET                     1         /*��ַ��֡�е�λ��ƫ����*/
#define  CTRL_TO_CEN_DATA_OFFSET                     4         /*������֡�е�λ��ƫ����*/


/*���İ� --> �ֿ��� */
#define  CEN_TO_CTRL_HEAD                            0xAA      /*��ʼ��*/
#define  CEN_TO_CTRL_ADDR                            0x08      /*��ַ��*/
#define  CEN_TO_CTRL_FUNC                            0xB0      /*����������  ������*/
#define  CEN_TO_CTRL_DATALEN                         40        /*����������  ���ݳ���*/
#define  CEN_TO_CTRL_VENDER_DATALEN                  38        /*���Ҽ��ģʽ��  ���ݳ���*/


#define  CTRL_KEY_BE_STUCK_TIME_THRESHOLD            45000     /*�ֿ����������� ʱ������*/ 
#define  CTRL_LINK_LOST_COUNT_THRESHOLD              8         /*�ֿ������Ӷ�ʧ���� ����*/

#define  CDP_TYPE_NONE                               0x00      /*ͨ�����ݰ����ͣ���*/
//#define  CDP_TYPE_CTRL                               0x01      /*ͨ�����ݰ����ͣ�����*/  



/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
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
    uint8_t    CtrlLinkLostFault          :1;    /*ͨ�����Ӷ�ʧ ����*/
    uint8_t    CoreLinkLostFault          :1;    /*��о��ͨ�����Ӷ�ʧ ����*/
    uint8_t    CalvesFeetLinkLostFault    :1;    /*�ȽŰ�ͨ�����Ӷ�ʧ ����*/
    uint8_t    SideCtrlLinkLostFault      :1;    /*���ͨ�����Ӷ�ʧ   ����*/

  }Bit;

}CDP_CenXxxCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/

/*
************************************************************************************************************************
* ���Ͷ��� :  �ֿ��� <--> ���İ�  ��ز������ݽṹ                                                                            
************************************************************************************************************************
*/
typedef struct
{
  CDP_CenXxxCSFlag_t         CSFlag;
  CDP_FrameRx_t              FrameRx;
  
  uint16_t                   CtrlLinkLostTimeMs;                /*ͨ�����Ӷ�ʧʱ��*/
  uint16_t                   CoreLinkLostTimeMs;                /*ͨ�����Ӷ�ʧʱ��*/
  uint16_t                   CalvesFeetLinkLostTimeMs;          /*ͨ�����Ӷ�ʧʱ��*/
  uint16_t                   SideCtrlLinkLostTimeMs;            /*ͨ�����Ӷ�ʧʱ��*/
  
  uint8_t                    CurCDPType;                        /*��ǰ ͨ�����ݰ�����*/

  //---------------------------------------------------------------------------
  uint8_t                    ORxBuf[CTRL_TO_CEN_FRAMELEN+2];     /*���ջ���*/
  uint8_t                    ORxLen;                             /*���ճ���*/

  uint8_t                    ORxDataLen;                         /*���յ������ݳ���*/
  uint8_t                    ORxState;                           /*����״̬*/
  uint8_t                    OKeyValRx;                          /*���ռ�ֵ*/
  uint8_t                    OKeyValMap;                         /*ӳ���ļ�ֵ*/
  uint8_t                    OKeyValAssist;                      /*��ֵ����*/

/*���������� �����ֿ���������--------------------------------------*/
  struct
  {
    uint8_t          Head;                               /*��ʼ��*/
    uint8_t          Addr;                               /*��ַ��*/
    uint8_t          FuncCode;                           /*������*/
    uint8_t          DataLen;                            /*���ݰ�����*/

    struct
    {
      uint8_t        SysRun                         :1;  /*ϵͳ���ػ�״̬*/ 
      uint8_t        Pause                          :1;  /*��ͣ״̬*/    
      uint8_t        MassageTimeOut                 :1;  /*��Ħ��ʱ��״̬*/ 
      uint8_t        PromptToneRun                  :1;  /*������ʾ��*/ 
      uint8_t        VenderOpFinish                 :1;  /*���Ҳ������*/ 
      uint8_t        BluetoothSwitch                :1;  /*��������*/

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
      uint8_t        keep                           :8; 
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
    uint8_t          FaultCodeBit[10];                   /*����λ*/

    struct
    {
      uint8_t        KeyInspectOneself              :1;  /*���� �����Զ����*/  
      uint8_t        KeyInspectManual               :1;  /*���� �����ֶ����*/  
      uint8_t        KeyInspectOther1               :1;  /*���� �������Ҽ�� 1*/  
      uint8_t        KeyInspectOther2               :1;  /*���� �������Ҽ�� 2*/  
      uint8_t        KeyInspectOther3               :1;  /*���� �������Ҽ�� 3*/  
      uint8_t        KeyTestNoTimer                 :1;  /*���� �޶�ʱ��������*/  
      uint8_t        KeyTestSpike                   :1;  /*���� �Ƹ˿�������*/  
      uint8_t        KeyTestAge                     :1;  /*���� ������������*/  
    }Byte37;

    struct
    {
      uint8_t        KeyTestOther1                  :1;  /*���� �������� 1*/  
      uint8_t        KeyTestOther2                  :1;  /*���� �������� 2*/  
      uint8_t        KeyTestOther3                  :1;  /*���� �������� 3*/  
      uint8_t        Packing                        :1;  /*���� ��װ����*/ 
      uint8_t        KeyOther1                      :1;  /*���� ����1*/  
      uint8_t        KeyOther2                      :1;  /*���� ����2*/  
      uint8_t        KeyOther3                      :1;  /*���� ����3*/  
      uint8_t        KeyQueryChairInfo              :1;  /*���� ��ѯ��Ħ����Ϣ��������汾�� ����Ϣ��*/  
    }Byte38;

    uint8_t         KeyValAck;                           /*����Ӧ��*/
    uint8_t         SumCode;                             /*У����*/

  }TxBuf; /*���������� �����ֿ���������*/


  /*���Ҽ��ģʽ�� �����ֿ���������-------------------------------*/
  struct
  {
    uint8_t          Head;                               /*��ʼ��*/
    uint8_t          Addr;                               /*��ַ��*/
    uint8_t          FuncCode;                           /*������*/
    uint8_t          DataLen;                            /*���ݰ�����*/

    struct
    {
      uint8_t        SysRun                         :1;  /*ϵͳ���ػ�״̬*/ 
      uint8_t        Pause                          :1;  /*��ͣ״̬*/    
      uint8_t        MassageTimeOut                 :1;  /*��Ħ��ʱ��״̬*/ 
      uint8_t        PromptToneRun                  :1;  /*��ʾ��*/ 
      uint8_t        VenderOpFinish                 :1;  /*���Ҳ������*/ 
   
    }Byte5;

    uint8_t          Edition;                            /*�汾��*/
    uint16_t         SysRunTimeHour;                     /*ϵͳ����ʱ��*/
    uint16_t         XMotorRunTimeHour;                  /*X�������ʱ��*/
    uint16_t         YMotorRunTimeHour;                  /*Y�������ʱ��*/
    uint16_t         ZMotorRunTimeHour;                  /*Z�������ʱ��*/
    uint16_t         TCSMotorRunTimeHour;                /*�û��������ʱ��*/
    uint16_t         BackSpikeMotorRunTimeHour;          /*�����Ƹ��������ʱ��*/
    uint16_t         FeetSpikeMotorRunTimeHour;          /*С���Ƹ��������ʱ��*/
    int8_t           CoreLeftTemp;                       /*��Ħͷ�¶�*/
    int8_t           CoreRightTemp;                      /*�Ұ�Ħͷ�¶�*/
    int8_t           FeetTemp;                           /*�Ų��¶�*/
    uint8_t          PromptToneAddr;                     /*��ʾ����ַ*/ 
    uint8_t          FaultCodeBit[10];                   /*����λ*/

    struct
    {
      uint8_t        KeyInspectOneself              :1;  /*���� �����Զ����*/  
      uint8_t        KeyInspectManual               :1;  /*���� �����ֶ����*/  
      uint8_t        KeyInspectOther1               :1;  /*���� �������Ҽ�� 1*/  
      uint8_t        KeyInspectOther2               :1;  /*���� �������Ҽ�� 2*/  
      uint8_t        KeyInspectOther3               :1;  /*���� �������Ҽ�� 3*/  
      uint8_t        KeyTestNoTimer                 :1;  /*���� �޶�ʱ��������*/  
      uint8_t        KeyTestSpike                   :1;  /*���� �Ƹ˿�������*/  
      uint8_t        KeyTestAge                     :1;  /*���� ������������*/  
    }Byte35;

    struct
    {
      uint8_t        KeyTestOther1                  :1;  /*���� �������� 1*/  
      uint8_t        KeyTestOther2                  :1;  /*���� �������� 2*/  
      uint8_t        KeyTestOther3                  :1;  /*���� �������� 3*/  
      uint8_t        Packing                        :1;  /*���� ��װ����*/ 
      uint8_t        KeyOther1                      :1;  /*���� ����1*/  
      uint8_t        KeyOther2                      :1;  /*���� ����2*/  
      uint8_t        KeyOther3                      :1;  /*���� ����3*/  
      uint8_t        KeyQueryChairInfo              :1;  /*���� ��ѯ��Ħ����Ϣ��������汾�� ����Ϣ��*/  
    }Byte36;

    uint8_t         KeyValAck;                           /*����Ӧ��*/
    uint8_t         SumCode;                             /*У����*/

  }VenderTxBuf; /*���Ҽ��ģʽ�� �����ֿ���������*/

}CDP_CenXxx_t;

/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/
void CDP_CenStateTmrToCtrl_DataTx(Ticker_t ExePeriod);
void CDP_CenXxx_FaultCheck(Ticker_t ExePeriod);
uint8_t CDP_CenXxx_DataTx(ESF_Evt_t *pEvt);
CDP_CenXxx_t* CDP_CenXxx_Init(void);
CDP_CenXxxCSFlag_t CDP_CenXxx_GetCSFlag(void);

#endif
