/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: FuncTabHandle.h 
**
**    ��������: ��Ħ���ܶ������Ĵ���
**
**    ��    ˾: �ɷ�������
**
**    ��Ŀ����: 
**
**    ƽ̨��Ϣ: 
**
**    ��    ��: Hzy
**
**    ����˵��: 
**          (1) ���ڡ���о �Զ�����ض�������ڵ� Repeat �� Time��˵��
**              �ɼܹ��еĻ�о�����ַ����������ǵ������ַ�����ȫ����ʱ�������Ʋ���ĵ�����
**              �¼ܹ����������ַ�������ַ�������ʱ�������Ʋ���ĵ�����Ӧ���Զ�����ɵĴ��������ơ�
**              ��ˣ��¼ܹ��ڶ�������м����˱���Repeat�����ƶ�����ִ�д�����  
**              Ŀǰ���¼ܹ�����о������Զ������� ֻ���� Repeat ����ֵΪRIGNORE��
**              ��CoreXYZAction ����Ϊ XYZ_ACTION_NONE ʱ������ʱ�������Ʋ���ĵ�����
**              �����Ķ�����Repeat�����������в���ĵ�������Repeat������ΪRIGNOREʱ��������ʱ����жϡ�
**
**          (2) ���ڲ�������� 
**              �¼ܹ��ԡ���о�����������������Ƹˡ���������������Ϊ�����������Ԫ�ء�
**              ������ 7 ��������ϣ� ����о�����������������Ƹˡ�������о+��������
**                                    ����о+�Ƹˡ���������+�Ƹˡ�������о+����+�Ƹˡ�
**              �����Ĺ��ܲ���(����֡���)���ٲ��붯��������ϣ�������Ϊ���ӵİ��湦�ܶ����ڡ�
**              ���ӵİ��湦�ܼȿ��Ե��������У��������ܿ�����Ҳ�ɵ����Ķ�����п��ز�����
**              �������ɿ���������ϵ�����������������еĲ�������ɼܹ�������������ϡ�
**              ����������������࣬����ж��߼���Խ��Խ���ӡ�
**
**    �޸ļ�¼:  ------------------------------------------------------------------------------------------------------
**               2016.6.16 ---------------------------------------------------------------------------
**               �� ActionTabAttr_t���������������� StartStepNum(���ʼ ������) �� EndStepNum(������ ������)��
**               ���޸���Ӧ�Ĵ��룬ʹ�ö�������ִ�в�������������  StartStepNum  �� EndStepNum֮�䡣               
**
**               2016.6.20 ---------------------------------------------------------------------------
**               �޸� MChair_TabHandle_CoreMixOtherAuto()����������ز����߼���
**                 
**               ԭ��  ��Other������в��롾Other�������ж��߼��ǣ�(����ECP388������ʹ�á�)
**               ����Core������е� XYZAction = XYZ_ACTION_NONE  ��                   
**                                  Time1 = TIGNORE                                 
**               ������������������ʱ����Other����Ϊ������                      
**               ��������£���Other����Ϊ������                                
**
**               ���ڽ� ��Other������в��롾Other�������ж��߼� ��Ϊ��
**               ����Core������е� Repeat = RIGNORE   ��                           
**                                  Time1 = TIGNORE                                 
**               ������������������ʱ����Other����Ϊ������                      
**               ��������£���Other����Ϊ������   
**
**               �������ECP388�����п�����������ʱ��Ӧע���޸���ر�����ݡ�
**
**               2016.12.1 ---------------------------------------------------------------------------
**               �� MChair_TabHandle_CoreMixOtherAuto()����������ز����߼���                                �� 
**               �� ��ά��ECP388ϵ��֮�⡣һ�㾡����ʹ�ã���Ӧʹ�� FuncAuto_AllCombo.c �ļ��еĹ�����Ϊ������� 
**
**               2016.12.5 ---------------------------------------------------------------------------
**               ���ӱ��������Թ��ܡ�
**               ͨ����λ���ܹ����ٱ����Զ�������
========================================================================================================================
========================================================================================================================
*/

#ifndef  _FUNCTABHANDLE_H
#define  _FUNCTABHANDLE_H


/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "bsp.h"
#include "Gas.h"


/*
========================================================================================================================
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/

#define  ACTION_TAB_STEP_SUM_MIN           1                            /*���������������Сֵ*/
#define  ACTION_TAB_STEP_SUM_MAX           600//255                     /*����������������ֵ*/
#define  ACTION_TAB_STEP_NUM_MIN           (ACTION_TAB_STEP_SUM_MIN-1)  /*������������Сֵ*/
#define  ACTION_TAB_STEP_NUM_MAX           (ACTION_TAB_STEP_SUM_MAX-1)  /*�������������ֵ*/
#define  ACTION_TAB_STEP_NUM_END           (ACTION_TAB_STEP_NUM_MAX+1)  /*���������Ž���ֵ*/

#define  ACTION_TAB_STEP_HOP_NONE          0                            /*�����������������*/
#define  ACTION_TAB_STEP_HOP_NEXT          1                            /*�����������������һ��*/
#define  ACTION_TAB_STEP_HOP_LAST          2                            /*�����������������һ��*/
#define  STEP_HOP_NONE                     ACTION_TAB_STEP_HOP_NONE                      
#define  STEP_HOP_NEXT                     ACTION_TAB_STEP_HOP_NEXT                     
#define  STEP_HOP_LAST                     ACTION_TAB_STEP_HOP_LAST                     


#ifndef  PIGNORE
#define  PIGNORE                           255                          /*λ�ú���*/
#endif
#ifndef  PKEEP
#define  PKEEP                             (PIGNORE-1)                  /*λ�ñ���*/
#endif

#define  TIGNORE                           65535                        /*ʱ�����*/
#define  RIGNORE                           255                          /*�ظ���������*/


#define  CORE_AUTO_PZLEVEL_REF             4                            /*��о�Զ�ʱ�Ĳ���Zǿ��*/
#define  CORE_AUTO_PZLEVEL_MAX             8                            /*��о�Զ�ʱ�����Zǿ��*/


#define  P00                               0
#define  P01                               1
#define  P02                               2
#define  P03                               3
#define  P04                               4
#define  P05                               5
#define  P06                               6
#define  P07                               7
#define  P08                               8
#define  P09                               9
#define  P10                               10
#define  P11                               11
#define  P12                               12
#define  P13                               13
#define  P14                               14
#define  P15                               15
#define  P16                               16
#define  P17                               17
#define  P18                               18
#define  P19                               19
#define  P20                               20
#define  P21                               21
#define  P22                               22
#define  P23                               23
#define  P24                               24
#define  P25                               25
#define  P26                               26
#define  P27                               27
#define  P28                               28
#define  P29                               29
#define  P30                               30
#define  P31                               31
#define  P32                               32
#define  P33                               33
#define  P34                               34
#define  P35                               35
#define  P36                               36
#define  P37                               37
#define  P38                               38
#define  P39                               39
#define  P40                               40
#define  P41                               41
#define  P42                               42
#define  P43                               43
#define  P44                               44
#define  P45                               45
#define  P46                               46
#define  P47                               47
#define  P48                               48
#define  P49                               49
#define  P50                               50
#define  P51                               51
#define  P52                               52
#define  P53                               53
#define  P54                               54
#define  P55                               55
#define  P56                               56
#define  P57                               57
#define  P58                               58
#define  P59                               59
#define  P60                               60
#define  P61                               61
#define  P62                               62
#define  P63                               63
#define  P64                               64
#define  P65                               65
#define  P66                               66
#define  P67                               67
#define  P68                               68
#define  P69                               69
#define  P70                               70
#define  P71                               71
#define  P72                               72
#define  P73                               73
#define  P74                               74
#define  P75                               75
#define  P76                               76
#define  P77                               77
#define  P78                               78
#define  P79                               79
#define  P80                               80
#define  P81                               81
#define  P82                               82
#define  P83                               83
#define  P84                               84
#define  P85                               85
#define  P86                               86
#define  P87                               87
#define  P88                               88
#define  P89                               89
#define  P90                               90
#define  P91                               91
#define  P92                               92
#define  P93                               93
#define  P94                               94
#define  P95                               95
#define  P96                               96
#define  P97                               97
#define  P98                               98
#define  P99                               99


#define  MIX_MODE_NONE                     0                           /*���ģʽ����*/
#define  MIX_MODE_INSERT                   1                           /*���ģʽ�����뷽ʽ*/ 
#define  MIX_MODE_ACCOMPANY                2                           /*���ģʽ�����淽ʽ*/ 

/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� : �������Ŀ ʱ��                                                                                                   
************************************************************************************************************************
*/
typedef  Ticker_t  TabItemTime_t;                 

/*
************************************************************************************************************************
* ���Ͷ��� : ���������                                                                                               
************************************************************************************************************************
*/
typedef struct
{
  uint8_t         Repeat;                        /*�����ظ�ִ�д���*/
  uint8_t         TabRepeat;                     /*����ظ�ִ�д���*/
  uint16_t        Num;                           /*�����*/
  TabItemTime_t   RunTimeMs100;                  /*����ִ��ʱ��,��λ100ms*/
  TabItemTime_t   RunTimeMs;                     /*����ִ��ʱ��,��λms���ۼ�msʱ�䣬��100ms�������㣬���ݽ�RunTimeMs100*/
  uint32_t        TabRunTimeMs100;               /*���ִ��ʱ��,��λ100ms*/

  union
  {
    uint8_t All;
    struct
    {
      uint8_t     StepHop                :2;     /*����ִ��*/
      uint8_t     OccurIterate           :1;     /*��ʶ�Ƿ�������*/
      uint8_t     SingleExe              :1;     /*��ʶ�Ƿ�ִֻ��һ��*/
      uint8_t     IsCoreMixOther         :1;     /*��ʶ�Ƿ��ǡ���о����ϡ����������*/
      uint8_t     IsWithCore             :1;     /*��ʶ�Ƿ������о��*/
    }Bit;
  }AdditonOp;                                    /*���Ӳ���*/

  union
  {
    uint8_t       All;
    struct
    {
      uint8_t     CoreXYZActionRepeat    :1;     /*��оXYZ�����ظ�����*/
      uint8_t     CorePositionOk         :1;     /*��оλ��*/
      uint8_t     SpikeAngleOk           :1;     /*�Ƹ�λ��*/
      uint8_t     LegFlexOk              :1;     /*С������*/
      uint8_t     ULegFlexOk             :1;     /*�� С������*/
      uint8_t     TimeOut                :1;     /*��ʱ*/
    }Bit;
  }IncConditionState;                            /*��������������״̬*/

  union
  {
    uint8_t All;
    struct
    {
      uint8_t     CoreXYZActionRepeat    :1;     /*��оXYZ�����ظ�����*/
      uint8_t     CorePositionOk         :1;     /*��оλ��*/
      uint8_t     SpikeAngleOk           :1;     /*�Ƹ�λ��*/
      uint8_t     LegFlexOk              :1;     /*С������*/
      uint8_t     ULegFlexOk             :1;     /*�� С������*/
      uint8_t     TimeOut                :1;     /*��ʱ*/
    }Bit;
  }IncJudgeCondition;                            /*����������Ҫ�жϵ�����*/

}ActionTabStep_t;


/*
************************************************************************************************************************
* ���Ͷ��� : �����������                                                                                           
************************************************************************************************************************
*/
typedef struct
{
  uint16_t                   FuncID;                 /*��Ħ����ID�ţ�������ʶ��Ħ����*/    

  /*������� (ע��Ϊ���ݶ������͵ı������ʹ��void(����)ָ�룬Ȼ�����ʵ��ʹ�ã���ǿ��ת������)*/   
  void                       *pActionTab;   
  uint8_t                    StartStepNum;           /*���ʼ ������*/           
  uint16_t                   EndStepNum;             /*������ ������*/         
 
  /*������Ҫ�����Ӧ�İ���ģʽ��*/
  uint8_t                    FeetVibMode;            /*���� ����ģʽ*/ 
  uint8_t                    CalvesVibMode;          /*���� ����ģʽ*/ 
  uint8_t                    SeatVibMode;            /*���� ����ģʽ*/ 
  uint8_t                    LumbarBackVibMode;      /*������ ����ģʽ*/ 
  uint8_t                    FeetRollerMode;         /*�Ź� ����ģʽ*/ 
  uint8_t                    CalvesRollerMode;       /*�ȹ� ����ģʽ*/ 
  uint8_t                    FeetHeatMode;           /*���� ����ģʽ*/  
  uint8_t                    CalvesHeatMode;         /*���� ����ģʽ*/  
  uint8_t                    SeatHeatMode;           /*���� ����ģʽ*/  
  uint8_t                    LumbarBackHeatMode;     /*������ ����ģʽ*/   
  uint8_t                    LedMode;                /*��   ����ģʽ*/  
}ActionTabAttr_t;



/*
************************************************************************************************************************
* ���Ͷ��� : ��Ħ���� ��������������                                                                                      
************************************************************************************************************************
*/
typedef union 
{
  uint8_t          All;
  struct
  {
    uint8_t        Core            :1;    /*��о*/
    uint8_t        Gas             :1;    /*����*/
    uint8_t        Spike           :1;    /*�Ƹ�*/

    uint8_t                        :1;
    uint8_t                        :1;
    uint8_t                        :1;
    uint8_t                        :1;
  }Bit;
}FuncMainComponent_t;

/*
************************************************************************************************************************
* ���Ͷ��� : ��Ħ���� ���е�����                                                                                    
************************************************************************************************************************
*/
typedef union 
{
  uint8_t          All;
  struct
  {
    /*#define  FUNC_TYPE_NONE                         0     �������� ��
      #define  FUNC_TYPE_MANNUAL                      1     �������� �ֶ�
      #define  FUNC_TYPE_AUTO                         2     �������� �Զ�
      #define  FUNC_TYPE_MANNUALAUTO                  3     �������� �ֶ��Զ�   */
    
    uint8_t        FuncType        :2;   /*0����   1�ֶ�  2�Զ�   3�ֶ����Զ�*/
    uint8_t        Combo           :1;   /*0����   1��� */
    uint8_t                        :3;   /*Ԥ��*/
    uint8_t        Priority        :2;   /*���ȼ�  0~3����ֵԽС�����ȼ�Խ�� */
  }Bit;
}FuncAttr_t;

/*
************************************************************************************************************************
* ���Ͷ��� : ��Ħ���� �� �߼�                                                                                   
************************************************************************************************************************
*/
typedef struct FuncLogic
{
  uint16_t                 *pFuncCur;                                  /*��ǰ����*/
  uint16_t                 *pFuncHis;                                  /*��ʷ����*/

  FuncAttr_t               Attr;                                       /*����*/
  FuncMainComponent_t      MainComponent;                              /*������*/

  void (*pFuncSwitch)(uint8_t SwitchMode, struct FuncLogic *pLogic);   /*ָ�����л�����*/                      
  void (*pFuncExe)(Ticker_t ExePeriod, struct FuncLogic *pLogic);      /*ָ����ִ�к���*/                 
}FuncLogic_t;


/*
************************************************************************************************************************
* ���Ͷ��� : ���� ��  ����λ                                                                                  
************************************************************************************************************************
*/
__packed typedef union
{
  uint8_t          All;
  __packed struct
  {
    uint8_t        FeetVib            :1;    /*b0 �Ų���*/
    uint8_t        CalvesVib          :1;    /*b1 �Ȳ��� */
    uint8_t        SeatVib            :1;    /*b2 ������*/
    uint8_t        LumbarBackVib      :1;    /*b3 ������*/

    uint8_t        FeetRoller         :1;    /*b4 �Ź�*/
    uint8_t        CalvesRoller       :1;    /*b5 �ȹ�*/
    uint8_t                           :1;    /*b6*/
    uint8_t                           :1;    /*b7*/
  }Bit;
}RollerVibCtrl_t;

/*
************************************************************************************************************************
* ���Ͷ��� : �ƹ� ���� ����λ                                                                              
************************************************************************************************************************
*/
__packed typedef union
{
  uint8_t          All;
  __packed struct
  {
    uint8_t        FeetHeat            :1;    /*b0 �Ų�����*/
    uint8_t        CalvesHeat          :1;    /*b1 �Ȳ�����*/
    uint8_t        SeatHeat            :1;    /*b2 ��������*/
    uint8_t        LumbarBackHeat      :1;    /*b3 ��������*/

    uint8_t        SleepLed            :1;    /*b4 ������*/
    uint8_t                            :1;    /*b5*/
    uint8_t                            :1;    /*b6*/
    uint8_t                            :1;    /*b7*/
  }Bit;
}LedHeatCtrl_t;


/*
************************************************************************************************************************
* ���Ͷ��� : ����о���ֶ������                                                                                  
************************************************************************************************************************
*/
typedef struct
{
  uint8_t                  ActionID;                 /*��ʶҪִ�еĶ���*/
  uint8_t                  AdditonOp;                /*���Ӳ���  */
 
  uint8_t                  XMax;                     /*��� �ɵ����*/
  uint8_t                  ZMax;                     /*��� �ɵ�������*/

  uint8_t                  YPrePosition;             /*����ִ��ʱ��Ԥ����Yλ��*/ 

}CoreXYZActionMannualTabItem_t;  



/*
************************************************************************************************************************
* ���Ͷ��� : ����о���Զ���������                                                                                  
************************************************************************************************************************
*/
__packed typedef struct
{
  uint8_t                  XPosition;                /*��о ���λ��*/  
  uint8_t                  YPosition;                /*��о �߶�λ��*/  
  uint8_t                  ZPosition;                /*��о ������λ��*/  

  uint8_t                  XYZActionSpeed;           /*XYZ�ַ� �ٶ�*/ 
  uint8_t                  TCSActionSpeed;           /*TCS�ַ� �ٶ�*/ 

  uint8_t                  XYZAction;                /*��о XYZ ��ﰴĦ����*/
  uint8_t                  TCSAction;                /*��о TCS ��ﰴĦ����*/ 

}CoreAutoActionObj_t;  /*��о �Զ���Ħ���� ����*/


/*
************************************************************************************************************************
* ���Ͷ��� : ����о���Զ������                                                                            
************************************************************************************************************************
*/
__packed typedef struct
{
  CoreAutoActionObj_t      CoreAutoAction;            /*��о��������*/

  RollerVibCtrl_t          RollerVibBit;              /*���� ���� ��*/
  LedHeatCtrl_t            LedHeatBit;                /*���� ���� �ƹ�*/

  uint8_t                  Repeat;                    /*�����ظ�����*/
  TabItemTime_t            Time1;                     /*����ʱ��*/

}CoreAutoTabItem_t;


/*
************************************************************************************************************************
* ���Ͷ��� : ����������������                                                                                  
************************************************************************************************************************
*/
__packed typedef struct
{
/*           GasPart1  --    b0    SeatSide           ���� 
*                            b1    LumbarSide         ����
*                            b2    ArmsRF             ���ֱ�ǰ
*                            b3    ArmsRB             ���ֱۺ�
*                            b4    ArmsLF             ���ֱ�ǰ
*                            b5    ArmsLB             ���ֱۺ�
*                            b6    ShoulderSide       ���
*
*            GasPart2  --    b0    CalvesBot           �ȵ�  
*                            b1    CalvesSide          �Ȳ�
*                            b2    CalvesSideHold      �Ȳ� ��ѹ
*                            b3    
*                            b4      
*                            b5         
*                            b6     
*                            b7                 */
  GasPart1_t                  GasPart1;   /*������λ*/  
  GasPart2_t                  GasPart2;   /*������λ*/
}GasActionObj_t;


/*
************************************************************************************************************************
* ���Ͷ��� : ���������ֶ������                                                                                
************************************************************************************************************************
*/
__packed typedef struct
{
  GasActionObj_t           GasMannualAction;          /*������������*/

  RollerVibCtrl_t          RollerVibBit;              /*���� ���� ��*/
  LedHeatCtrl_t            LedHeatBit;                /*���� ���� �ƹ�*/

  TabItemTime_t            Time1;                     /*����ʱ��*/
  TabItemTime_t            Time2;                     /*����ʱ��*/
  TabItemTime_t            Time3;                     /*����ʱ��*/
  TabItemTime_t            Time4;                     /*����ʱ��*/
  TabItemTime_t            Time5;                     /*����ʱ��*/

}GasMannualTabItem_t;

/*
************************************************************************************************************************
* ���Ͷ��� : ���������Զ������                                                                          
************************************************************************************************************************
*/
__packed typedef struct
{
  GasActionObj_t           GasAutoAction;             /*������������*/

  RollerVibCtrl_t          RollerVibBit;              /*���� ���� ��*/
  LedHeatCtrl_t            LedHeatBit;                /*���� ���� �ƹ�*/

  TabItemTime_t            Time1;                     /*����ʱ��*/
  TabItemTime_t            Time2;                     /*����ʱ��*/
  TabItemTime_t            Time3;                     /*����ʱ��*/
  TabItemTime_t            Time4;                     /*����ʱ��*/
  TabItemTime_t            Time5;                     /*����ʱ��*/

}GasAutoTabItem_t;

/*
************************************************************************************************************************
* ���Ͷ��� : С����������                                                                               
************************************************************************************************************************
*/
__packed typedef union
{
  uint8_t          All;               
  __packed struct
  {
    uint8_t        Extend                :1;    /*��*/
    uint8_t        Shorten               :1;    /*��*/
    uint8_t        CheckTouchFeet        :1;    /*���ż��*/
    uint8_t        CheckTouchGround      :1;    /*���ؼ��*/
    
    uint8_t        UpExtend              :1;    /*��С�� ��*/
    uint8_t        UpShorten             :1;    /*��С�� ��*/
  }Bit; 
}LegFlexCtrl_t; 

/*
************************************************************************************************************************
* ���Ͷ��� : ���Ƹˡ��Զ���������                                                                                 
************************************************************************************************************************
*/
__packed typedef struct
{
  LegFlexCtrl_t            LegFlexCtrl;               /*�Ƚ�����ִ���������*/
  uint8_t                  BackPosition;              /*����λ��*/  
  uint8_t                  FeetPosition;              /*�Ƚ�λ��*/  
  uint8_t                  ZeroPosition;              /*������λ��*/  

}SpikeAutoActionObj_t; 


/*
************************************************************************************************************************
* ���Ͷ��� : ���Ƹˡ��Զ������
* ע���������Ƹ��Զ� û�а��湦�ܣ�����ֻ�ǵ����ĵ����Ƹ˽Ƕȶ��ѡ�                                                                                   
************************************************************************************************************************
*/
__packed typedef struct
{
  SpikeAutoActionObj_t     SpikeAutoAction;           /*�Ƹ˶�������*/

  TabItemTime_t            Time1;                     /*����ʱ��*/

}SpikeAutoTabItem_t;



/*
************************************************************************************************************************
* ���Ͷ��� : ����о+�������Զ������                                                                                  
************************************************************************************************************************
*/
__packed typedef struct
{
  CoreAutoActionObj_t      CoreAutoAction;            /*��о��������*/

  GasActionObj_t           GasAutoAction;             /*������������*/

  RollerVibCtrl_t          RollerVibBit;              /*���� ���� ��*/
  LedHeatCtrl_t            LedHeatBit;                /*���� ���� �ƹ�*/

  uint8_t                  Repeat;                    /*�����ظ�����*/

  TabItemTime_t            Time1;                     /*����ʱ��*/
  TabItemTime_t            Time2;                     /*����ʱ��*/
  TabItemTime_t            Time3;                     /*����ʱ��*/
  TabItemTime_t            Time4;                     /*����ʱ��*/
  TabItemTime_t            Time5;                     /*����ʱ��*/

}CoreGasAutoTabItem_t;


/*
************************************************************************************************************************
* ���Ͷ��� : ����о+�Ƹˡ��Զ������                                                                                 
************************************************************************************************************************
*/
__packed typedef struct
{
  CoreAutoActionObj_t      CoreAutoAction;            /*��о��������*/

  SpikeAutoActionObj_t     SpikeAutoAction;           /*�Ƹ˶�������*/

  RollerVibCtrl_t          RollerVibBit;              /*���� ���� ��*/
  LedHeatCtrl_t            LedHeatBit;                /*���� ���� �ƹ�*/

  uint8_t                  Repeat;                    /*�����ظ�����*/

  TabItemTime_t            Time1;                     /*����ʱ��*/

}CoreSpikeAutoTabItem_t;


/*
************************************************************************************************************************
* ���Ͷ��� : ������+�Ƹˡ��Զ������                                                                                
************************************************************************************************************************
*/
__packed typedef struct
{
  GasActionObj_t           GasAutoAction;             /*������������*/
  SpikeAutoActionObj_t     SpikeAutoAction;           /*�Ƹ˶�������*/

  RollerVibCtrl_t          RollerVibBit;              /*���� ���� ��*/
  LedHeatCtrl_t            LedHeatBit;                /*���� ���� �ƹ�*/

  TabItemTime_t            Time1;                     /*����ʱ��*/
  TabItemTime_t            Time2;                     /*����ʱ��*/
  TabItemTime_t            Time3;                     /*����ʱ��*/
  TabItemTime_t            Time4;                     /*����ʱ��*/
  TabItemTime_t            Time5;                     /*����ʱ��*/

}GasSpikeAutoTabItem_t;


/*
************************************************************************************************************************
* ���Ͷ��� : ����о+����+�Ƹˡ��Զ������                                                                                
************************************************************************************************************************
*/
__packed typedef struct
{
  CoreAutoActionObj_t      CoreAutoAction;            /*��о��������*/
  GasActionObj_t           GasAutoAction;             /*������������*/
  SpikeAutoActionObj_t     SpikeAutoAction;           /*�Ƹ˶�������*/

  RollerVibCtrl_t          RollerVibBit;              /*���� ���� ��*/
  LedHeatCtrl_t            LedHeatBit;                /*���� ���� �ƹ�*/

  uint8_t                  Repeat;                    /*�����ظ�����*/

  TabItemTime_t            Time1;                     /*����ʱ��*/
  TabItemTime_t            Time2;                     /*����ʱ��*/
  TabItemTime_t            Time3;                     /*����ʱ��*/
  TabItemTime_t            Time4;                     /*����ʱ��*/
  TabItemTime_t            Time5;                     /*����ʱ��*/

}CoreGasSpikeAutoTabItem_t;




/*
************************************************************************************************************************
* ���Ͷ��� : ����о ��� �������Զ������
* ע1��ʵ���������°�Ħ�����������ڲ�ͬ�ġ���о�����裬���棨���룩��ͬ�Ĺ��ܱ��
* ע2��Ҳ�ɵ��������ġ���о���Զ��������ʹ��                                                                                
************************************************************************************************************************
*/
typedef struct
{
  CoreAutoTabItem_t        CoreAutoTabItem;           /*��о���� ��*/
  void                     *pOtherTab;                /*������� ʹ������ָ��(void*)���Լ��ݸ��ֱ��*/                
}CoreMixOtherTabItem_t;

/*
************************************************************************************************************************
* ���Ͷ��� : ��ϵĶ�����������                                                                                  
************************************************************************************************************************
*/
typedef struct
{
  void              *pTab;                                 /*��ϵı��*/
  
  union
  {
    struct
    {
      uint8_t       Core                          :1;      /*���ܲ���:��о*/
      uint8_t       Gas                           :1;      /*���ܲ���:����*/
      uint8_t       Spike                         :1;      /*���ܲ���:�Ƹ�*/
    }Bit;
    uint8_t         All;
  }ComponentAttr;    
  
  union
  {
    struct
    {
      uint8_t       Head                       :1;      /*������λ��ͷ*/
      uint8_t       Shoulder                   :1;      /*������λ���粿*/
      uint8_t       Arms                       :1;      /*������λ���ֱ�*/
      uint8_t       Lumbar                     :1;      /*������λ����*/
      uint8_t       Seat                       :1;      /*������λ����*/
      uint8_t       Calves                     :1;      /*������λ����*/
      uint8_t       Feet                       :1;      /*������λ����*/
    }Bit;
    uint8_t        All;
  }GasAttr;
  
  union
  {
    struct
    {
      uint8_t       BackMannualDis             :1;      /*�Ƹ˿����ֶ���Ч*/
      uint8_t       ZeroMannualDis             :1;      /*�Ƹ��������ֶ���Ч*/
      uint8_t       FeetMannualDis             :1;      /*�Ƹ�С���ֶ���Ч*/
      uint8_t       LegFlexMannualDis          :1;      /*�Ƹ�С�������ֶ���Ч*/
      uint8_t       ULegFlexMannualDis         :1;      /*�Ƹ���С�������ֶ���Ч*/
    }Bit;
    uint8_t         All;
  }SpikeAttr;
 
}MixOtherActionTabAttr_t;



/*
========================================================================================================================
*��ȫ��������                                          ��ȫ��������                                          ��ȫ��������
========================================================================================================================
*/
void MChair_TabHandle_CoreAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep);
void MChair_TabHandle_SpikeAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep);
void MChair_TabHandle_GasAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep);
void MChair_TabHandle_CoreGasAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep);
void MChair_TabHandle_CoreSpikeAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep);
void MChair_TabHandle_GasSpikeAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep);
void MChair_TabHandle_CoreGasSpikeAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep);

void MChair_TabHandle_ResetMixOtherTabStep(uint8_t SpikeStop);
void MChair_TabHandle_CoreMixOtherAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep);

#endif
