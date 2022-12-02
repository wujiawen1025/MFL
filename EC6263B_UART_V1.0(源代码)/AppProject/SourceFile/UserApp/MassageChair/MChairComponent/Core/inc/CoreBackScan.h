/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: CoreBackSacn.h                                                                                                         
**
**    ��������: ��о����ɨ��
**
**    ��    ˾���ɷ�������
**
**    ��Ŀ���ƣ�
**
**    ƽ̨��Ϣ��
**
**    ��    �ߣ�Hzy
**
**    ����˵��: ���屳��λ�õ��߼����֣�
**              ��ߵ�PY00  (����Ѩ����)
**              �粿  PY04
**              ����  PY24  (������Ѩ����)����������Ѩ����������λ�õȷ�24��(PY00 ~ PY24)
**              ʣ�µĸ��ݵ���ĳ��Ȳ�ͬ����ͬ��
**
**    �޸ļ�¼:  --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/
#ifndef  _CORE_BACKSCAN_H
#define  _CORE_BACKSCAN_H


/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "MotorCommon.h"
#include "CoreXaxisMotor.h"
#include "CoreYaxisMotor.h"
#include "CoreZaxisMotor.h"
#include "CoreTCSMotor.h"


/*
========================================================================================================================
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/                                      
#define  SHOULDER_ADJUST_NONE              0                            /*�粿�޵���*/
#define  SHOULDER_ADJUST_DOWN              1                            /*�粿���µ���*/
#define  SHOULDER_ADJUST_UP                2                            /*�粿���ϵ���*/
#define  SHOULDER_ADJUST_FINISH            3                            /*�粿�������*/

#define  SHOULDER_ADJUST_KEY_L             0                            /*�粿���� ���� ����*/
#define  SHOULDER_ADJUST_KEY_S             1                            /*�粿���� ���� �̰�*/
#define  SHOULDER_ADJUST_KEY_LSMODE        SHOULDER_ADJUST_KEY_L        /*�粿���� ���� ���̰�ģʽ*/


#define  SHOULDER_LIMIT_NONE               0                            /*�粿���ڿɵ��ڷ�Χ*/
#define  SHOULDER_LIMIT_UP                 1                            /*�粿�����ϼ��ޣ��������ϵ���*/
#define  SHOULDER_LIMIT_DOWN               2                            /*�粿�����¼��ޣ��������µ���*/


#define  PZCURVE                           0xC0                         /*��������*/
#define  PZDEC1                            (PZCURVE - 1)                /*�����ߵĻ����� ����1��*/
#define  PZDEC2                            (PZCURVE - 2)
#define  PZDEC3                            (PZCURVE - 3)
#define  PZDEC4                            (PZCURVE - 4)
#define  PZDEC5                            (PZCURVE - 5)
#define  PZDEC6                            (PZCURVE - 6)
#define  PZDEC7                            (PZCURVE - 7)
#define  PZDEC8                            (PZCURVE - 8)
#define  PZDEC9                            (PZCURVE - 9)
#define  PZDEC10                           (PZCURVE - 10)
#define  PZDEC11                           (PZCURVE - 11)
#define  PZDEC12                           (PZCURVE - 12)
#define  PZDEC13                           (PZCURVE - 13)
#define  PZDEC14                           (PZCURVE - 14)
#define  PZDEC15                           (PZCURVE - 15)
#define  PZADD1                            (PZCURVE + 1)                /*�����ߵĻ����� ���1��*/
#define  PZADD2                            (PZCURVE + 2)
#define  PZADD3                            (PZCURVE + 3)
#define  PZADD4                            (PZCURVE + 4)
#define  PZADD5                            (PZCURVE + 5)
#define  PZADD6                            (PZCURVE + 6)
#define  PZADD7                            (PZCURVE + 7)
#define  PZADD8                            (PZCURVE + 8)
#define  PZADD9                            (PZCURVE + 9)
#define  PZADD10                           (PZCURVE + 10)
#define  PZADD11                           (PZCURVE + 11)
#define  PZADD12                           (PZCURVE + 12)
#define  PZADD13                           (PZCURVE + 13)
#define  PZADD14                           (PZCURVE + 14)
#define  PZADD15                           (PZCURVE + 15)


#define  CURVE_NUM_MAX                      50

/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� :  ����ɨ�������״̬��ʶ                                                             
************************************************************************************************************************
*/
typedef union
{
    uint16_t All;
    struct
    {
      uint8_t    Pause                     :5;          /*��ͣ*/
      uint8_t    Run                       :1;          /*����*/
      uint8_t    Finish                    :1;          /*���*/
      uint8_t    ReScanCheck               :1;          /*��ʶ���¼����*/
      uint8_t    ShoulderAdjustEn          :1;          /*�粿����ʹ��*/
      uint8_t    ShoulderAdjustOp          :2;          /*�粿���ڲ���*/
      uint8_t    ShoulderLimitState        :2;          /*�粿λ����������״̬*/
      uint8_t    UserAdjusting             :1;          /*��ʶ�û��ڵ��ڼ粿λ��*/
      uint8_t    NoHumanOnSeat             :1;          /*��������*/
      uint8_t    CurveReceived             :1;          /*���������ѽ��ձ�ʶ*/
    }Bit;
}CoreBackScanCSFlag_t;                                

/*
************************************************************************************************************************
* ���Ͷ��� :  ����ɨ����ز������ݽṹ                                                                        
************************************************************************************************************************
*/
typedef struct
{
  CoreBackScanCSFlag_t      CSFlag;                     /*������״̬��ʶ*/

  int8_t                    YMFollowZMVal;              /*Y�����Z��ı仯����ֵ*/

  uint16_t                  MTopPositionCount;          /*��Ħ�λ�õ�����(ӳ��)����ֵ*/
  uint16_t                  MShoulderPositionCount;     /*������ʱ��⵽�ļ粿λ�õ�����(ӳ��)����ֵ*/
  uint8_t                   MShoulderPosition;          /*������ʱ��⵽�ļ粿λ�õ�����(ӳ��)*/
  uint8_t                   MShoulderPositionLowest;    /*�������粿λ��*/

  uint8_t                   PositionMax;                /*Y���߼���λ�����ֵ(������λ�ֶ�)*/
  uint8_t                   ShoulderAboveCountPerSeg;   /*������ÿ���߼��ֶΰ�����λ�ü���ֵ*/
  uint8_t                   ShoulderBelowCountPerSeg;   /*������ÿ���߼��ֶΰ�����λ�ü���ֵ*/

  uint8_t                   MPositionMax;               /*Y������(ӳ��)��λ�����ֵ*/
  uint16_t                  MPositionCountMax;          /*Y������(ӳ��)���г̼������ֵ*/
  uint8_t                   MCountPerSeg;               /*Y������(ӳ��)ÿ���ֶΰ�����λ�ü���ֵ*/
  
  uint8_t                   PWMStatCountNoLoad;         /*����ʱ PWMͳ�ƴ��� */
  uint16_t                  PWMSumNoLoad;               /*����ʱ PWM��ֵ */
  uint16_t                  ShoulderPWMThreshold;       /*�粿λ��PWM����ֵ*/
  uint8_t                   ReachShoulderThPWMCount;    /*�ﵽ��λ�õ�PWM�����ֵ����*/

  uint8_t                   ScanStep;                   /*ɨ�貽��*/
  uint16_t                  ShoudlerAdjustValidTime;    /*�粿λ�õ��ڿ���ʱ��*/
  uint32_t                  ScanStepTimeMs;             /*ɨ�貽��ʱ��*/
  
  uint8_t                   CurveTab[CURVE_NUM_MAX];    /*�������߱�*/
  
}CoreBackScan_t;


/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/
void Core_BackScanSetPositionCtrPara(uint16_t MPositionCountMax, uint8_t MPositionMax, uint8_t PositionMax);
void Core_BackScanSetRunSw(uint8_t Sw);
void Core_BackScanSetReScanCheckSw(uint8_t Sw);
uint8_t Core_BackScanSetShoulderAdjustOp(uint8_t Op, uint8_t KeyLS);
void Core_BackScanSetCurveCheckSw(uint8_t Sw);
void Core_BackScanPauseOn(void);
void Core_BackScanPauseOff(void);
CoreBackScanCSFlag_t Core_BackScanGetCSFlag(void);
void Core_BackScanHandle(Ticker_t ExePeriod);
uint8_t Core_BackScanYMDynFollowZM(uint8_t ZPosition);
uint8_t Core_BackScanYMapToYM(uint8_t YPosition);
uint8_t Core_BackScanYMMapToY(uint8_t YMPosition);
uint8_t Core_BackScanZMapToZM(uint8_t ZPosition, uint8_t YPosition);
uint8_t Core_BackScanZMMapToZ(uint8_t ZMPosition);

uint16_t Core_BackScanGetYCount(void);
#endif
