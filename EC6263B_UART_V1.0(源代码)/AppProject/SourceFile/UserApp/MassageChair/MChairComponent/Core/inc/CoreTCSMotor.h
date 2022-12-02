/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: CoreTCSMotor.h                                                                                                         
**
**    ��������: �û����������
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
#ifndef  _CORE_TCS_MOTOR_H
#define  _CORE_TCS_MOTOR_H


/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "MotorCommon.h"



/*
========================================================================================================================
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/
#define  TCSMOTOR_ACTION_STOP                             0            /*��ﶯ��ģʽ*/
#define  TCSMOTOR_ACTION_CLAP1                            1            /*�Ĵ�1*/ 
#define  TCSMOTOR_ACTION_CLAP2                            2            /*�Ĵ�2*/ 
#define  TCSMOTOR_ACTION_SHIA1                            3            /*ָѹ1*/ 
#define  TCSMOTOR_ACTION_SHIA2                            4            /*ָѹ2*/ 
#define  TCSMOTOR_ACTION_LTAP                             5            /*���û�*/ 
#define  TCSMOTOR_ACTION_TAP                              6            /*�û�*/ 
#define  TCSMOTOR_ACTION_NO_FB_LTAP                       7            /*���ٶȷ��������û�*/      
#define  TCSMOTOR_ACTION_NO_FB_TAP                        8            /*���ٶȷ������û�*/      

#define  TCSMOTOR_SPEEDLEVEL_OFF                          0            /*����ٶ� ��*/
#define  TCSMOTOR_SPEEDLEVEL_MIN                          1            /*����ٶȵȼ�*/
#define  TCSMOTOR_SPEEDLEVEL_MAX                          5

#define  TCSMOTOR_SPEEDLEVEL_DEFAULT                      1            /*Ĭ���ٶ�*/
#define  TCSMOTOR_FB_DEFAULT                              1            /*Ĭ�Ϸ��� ����*/


#define  TCSMOTOR_PWM_MIN                                 25           /*��￪ʼת���������СPWM*/
#define  TCSMOTOR_PWM_MAX                                 255          /*���ȫ��ת�������PWM*/
#define  TCSMOTOR_PWM_FIXED_STEPING_VAL                   1
#define  TCSMOTOR_PWMSET_MINI_EXE_PERIODE                 7            /*PWM������Сִ������*/

#define  TCSMOTOR_RPM_PULSE_NUM                           0x04         /*���תһȦ��ת�����̾�����������*/
#define  TCSMOTOR_RPM_MEASURE_CYCLE_TIME                  (60000000/TCSMOTOR_RPM_PULSE_NUM)  /*����RPMʱ,���ܷ�ʹ�õ�ʱ��(60000000us/������)*/
#define  TCSMOTOR_RPM_CLEAR_TIME_THRESHOLD                (1000/TCSMOTOR_RPM_PULSE_NUM-100)  /*ת��ֵ���� ����ʱ�䣬��λms��ʵ������£��û������׿�ͣ�����-100�����̼�⵽��ͣ��ʱ��*/

#define  TCSMOTOR_RPM_MAX                                 3450         /*������ת��*/

#define  TCSMOTOR_RPM_SENSOR_LOST_TIME_THRESHOLD          9000//4500   /*ת�ٴ�����ʧ�� ����ʱ�䣬��λms�� ע�⣺�������ϸ�����4.5s,�������ֶ�����������ǿ������ĳЩλ���±Ƚ����׶£���˽�ʱ���Ϊ9s*/
#define  TCSMOTOR_OVER_CURRENT_TIME_THRESHOLD             3000         /*����������   ����ʱ�䣬��λms*/
#define  TCSMOTOR_OVER_CURRENT_LEVEL                      0            /*������������ƽ*/

#define  TCSMOTOR_DIRECTION_TIME_MS                       100          /*��ﻻ��ʱ��*/


/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� :  �������û�                                                                                 
************************************************************************************************************************
*/
typedef struct
{
  uint8_t      PWM;      
  uint16_t     Time_ms;   /*ʱ�䣬��λms*/
  uint8_t      Repeat;    /*�ظ�����*/
}TCSMotor_PeriodTap_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  �û���� ������״̬��ʶ                                                                                 
************************************************************************************************************************
*/
typedef  union 
{
  struct
  {
    /*Work��ʾ����߼������ڹ���(������Ӧ�Ķ��������Ҳ���Pause�Ƿ���Ч)��
      ��Run��ʾ�����ϵĹ�����Pause��Чʱ����ﲻRun��Pause��Чʱ������Ӧ�Ķ�������Ļ������Run*/
    uint8_t    Work                   :1;    /*������*/
    uint8_t    Pause                  :5;    /*��ͣ*/
    uint8_t    FeedBackEn             :1;    /*��������ʹ��*/
    uint8_t    Run                    :1;    /*����*/

    uint8_t    RPMSensorFault         :1;    /*ת�ٴ���������*/
    uint8_t    OverCurrentFault       :1;    /*����������*/
    uint8_t    Locked                 :1;    /*�����������ٹ���*/

    uint8_t    PeriodTCSPWMOn         :1;    /*TCS ��PWM ������*/

  }Bit;

  uint32_t All;
}TCSMotorCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/

/*
************************************************************************************************************************
* ���Ͷ��� :  �û�������������ݽṹ                                                                              
************************************************************************************************************************
*/
typedef struct
{
  TCSMotorCSFlag_t          CSFlag;                  /*������״̬��ʶ*/

  uint32_t                  RunTimeMs;               /*�������ʱ�䣬��λ1ms*/
  uint16_t                  OverCurrentTimeMs;       /*����������ʱ�䣬��λ1ms*/
  uint16_t                  StateCtrlTimeMs;         /*״̬����ʱ�䣬��λ1ms*/

  uint8_t                   Action;                  /*��ﶯ��*/
  uint8_t                   ActionStep;              /*���� ����*/
  uint8_t                   ActionStepRepeat;        /*���� �����ظ�����*/
  uint16_t                  ActionStepTime;          /*���� ����ʱ��*/

  uint8_t                   SpeedLevel;              /*�ٶȵȼ�*/
  uint16_t                  RPMSetVal;               /*ת�� ����ֵ*/
  uint16_t                  RPMRealVal;              /*ת�� ʵ��ֵ*/
  uint8_t                   FBWorkState;             /*�����Ĺ���״̬*/
  int16_t                   PWMFinalSetVal;          /*PWM��������ֵ*/
  int16_t                   PWMPreSetVal;            /*PWM Ԥ��ֵ*/
  int16_t                   PWMCompensationVal;      /*PWM ����ֵ*/

  uint8_t                   LightTapRealSpeedLevel;  /*����û���ʵ���ٶȵȼ�*/

  MotorRPMMointor_t         RPMMointor;	             /*ת�� �����*/

}TCSMotor_t;



/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/
/*��ʼ��--------------------------------------*/
TCSMotor_t*  TCSMotor_Init(void);


/*����ִ��--------------------------------------*/
void TCSMotor_OverCurrentIOCheck(Ticker_t ExePeriod);
void TCSMotor_RPMCheckHandle(Ticker_t ExePeriod);
void TCSMotor_PWMSetValHandle(Ticker_t ExePeriod);
void TCSMotor_ActionHandle(Ticker_t ExePeriod);

void TCSMotor_RPMCheckHandle(Ticker_t ExePeriod);


/* ����Ľӿڣ� �� ����ģ�� �ɶ� ��ģ��ִ�е� ���Ʋ���*/
void TCSMotor_PauseOn(void);
void TCSMotor_PauseOff(void);

//void TCSMotor_SetAction(uint8_t Action, uint8_t SpeedLevel, uint8_t FBEn);
void TCSMotor_SetAction(uint8_t Action, uint8_t SpeedLevel);

TCSMotorCSFlag_t TCSMotor_GetCSFlag(void);
uint16_t TCSMotor_GetCurRPM(void);

#endif
