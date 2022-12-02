/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: CoreZaxisMotor.h                                                                                                         
**
**    ��������: Z�����(����(ǿ��)���)������
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
#ifndef  _CORE_ZAXIS_MOTOR_H
#define  _CORE_ZAXIS_MOTOR_H


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
#define  ZMOTOR_BACK_LIMIT_CODE                           B(01)        /*Z�����λ�ñ���*/
#define  ZMOTOR_FRONT_LIMIT_CODE                          B(10)        /*Z��ǰ����λ�ñ���*/

#define  ZMOTOR_POSITION_MIN                              0            /*Z������Сֵ*/
#define  ZMOTOR_POSITION_MAX                              7            /*Z�������ֵ*/

#define  ZMOTOR_COUNT_MIN                                 0            /*λ�ü�������С*/
#define  ZMOTOR_COUNT_MAX                                 91           /*λ�ü��������*/
#define  ZMOTOR_COUNT_PER_SEGMENT                         ((ZMOTOR_COUNT_MAX/ZMOTOR_POSITION_MAX)+1) /*ÿ��λ�öεļ�����С����*/

#define  ZMOTOR_ACTION_STOP                               0            /*��ﶯ��ģʽ*/
#define  ZMOTOR_ACTION_FRONT                              1           
#define  ZMOTOR_ACTION_BACK                               2 

#define  ZMOTOR_DIRECTION_BACK                            BSP_ZMOTOR_DIRECTION_BACK
#define  ZMOTOR_DIRECTION_FRONT                           BSP_ZMOTOR_DIRECTION_FRONT           

#define  ZMOTOR_SPEEDLEVEL_OFF                            0            /*����ٶ� ��*/
#define  ZMOTOR_SPEEDLEVEL_MIN                            1            /*����ٶȵȼ�*/
#define  ZMOTOR_SPEEDLEVEL_MAX                            5

#define  ZMOTOR_SPEEDLEVEL_DEFAULT                        2            /*Ĭ���ٶ�*/
#define  ZMOTOR_FB_DEFAULT                                1            /*Ĭ�Ϸ��� ����*/

#define  ZMOTOR_PWM_MIN                                   20           /*��￪ʼת���������СPWM*/
#define  ZMOTOR_PWM_MAX                                   255          /*���ȫ��ת�������PWM*/
#define  ZMOTOR_PWM_FIXED_STEPING_VAL                     1            /*PWM���ӹ̶�����ֵ*/
#define  ZMOTOR_PWMSET_MINI_EXE_PERIODE                   8            /*PWM������Сִ������*/

#define  ZMOTOR_RPM_PULSE_NUM                             0x01         /*���תһȦ��ת�����̾�����������*/
#define  ZMOTOR_RPM_MEASURE_CYCLE_TIME                    (60000000/ZMOTOR_RPM_PULSE_NUM)  /*����RPMʱ,���ܷ�ʹ�õ�ʱ��(60000000us/������)*/
#define  ZMOTOR_RPM_CLEAR_TIME_THRESHOLD                  (1000/ZMOTOR_RPM_PULSE_NUM)      /*ת��ֵ���� ����ʱ�䣬��λms*/

#define  ZMOTOR_RPM_MAX                                   3450         /*������ת��*/


#define  ZMOTOR_POSITION_CODE_ERR_TIME_THRESHOLD          200          /*λ�ñ������     ����ʱ�䣬��λms*/
#define  ZMOTOR_POSITION_SENSOR_LOST_TIME_THRESHOLD       8000         /*λ�ô�����ʧ��   ����ʱ�䣬��λms��(ע�����¸���������8s�����ڿ���ʱ�������������Զ���������������Ϊ10s)*/
#define  ZMOTOR_RPM_SENSOR_LOST_TIME_THRESHOLD            5000         /*ת�ٴ�����ʧ��   ����ʱ�䣬��λms*/
#define  ZMOTOR_OVER_CURRENT_TIME_THRESHOLD               3000         /*������������   ����ʱ�䣬��λms*/
#define  ZMOTOR_OVER_CURRENT_LEVEL                        0            /*��������������ƽ*/
/*λ�ü���������ʧ��(��ת�ټ��ʹ��ͬһ������������˹��ϱ���ʱ�������ͬ)   ����ʱ�䣬��λms*/
#define  ZMOTOR_COUNT_SENSOR_LOST_TIME_THRESHOLD          ZMOTOR_RPM_SENSOR_LOST_TIME_THRESHOLD  

#define  ZMOTOR_DIRECTION_TIME_MS                         4000     /*��ﻻ��ʱ��*/
#define  ZMOTOR_REVERSE_TIME_MS                           4100     /*��ﷴתʱ��*/

/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� :  Z��� ������״̬��ʶ                                                                                  
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
    uint8_t    Direction              :1;    /*����*/
    uint8_t    ReachFrontLimt         :1;    /*�Ѵ�ǰ�����޶�*/
    uint8_t    ReachBackLimt          :1;    /*�Ѵ�����޶�*/

    uint8_t    PositionCodeFault      :1;    /*λ�ñ�����ϣ����ֲ�Ӧ�ô��ڵı���*/
    uint8_t    PositionSensorFault    :1;    /*λ�ô���������*/
    uint8_t    RPMSensorFault         :1;    /*ת�ٴ���������*/
    uint8_t    OverCurrentFault       :1;    /*����������*/
    uint8_t    CountFault             :1;    /*�������ϣ���ⲻ�������仯*/
    uint8_t    Locked                 :1;    /*�����������ٹ���*/
    uint8_t    OvershootSpeedLimitCur :1;    /*�����ٶ����Ʊ��� ��ǰ*/
    uint8_t    OvershootSpeedLimitHis :1;    /*�����ٶ����Ʊ��� ��ʷ*/

    uint8_t    PositionResetOK        :1;    /*λ�ø�λ���*/
  }Bit;

  uint32_t All;
}ZMotorCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/

/*
************************************************************************************************************************
* ���Ͷ��� :  Z������������ݽṹ                                                                    
************************************************************************************************************************
*/
typedef struct
{
  ZMotorCSFlag_t            CSFlag;                  /*������״̬��ʶ*/

  uint8_t                   PositionRealVal;         /*λ�� ʵ��ֵ*/
  uint8_t                   PositionSetVal;          /*λ�� ����ֵ*/

  uint16_t                  FrontRunTimeMs;          /*��������ʱ�䣬��λ1ms*/
  uint16_t                  BackRunTimeMs;           /*��������ʱ�䣬��λ1ms*/
  uint32_t                  RunTimeMs;               /*�������ʱ�䣬��λ1ms*/
  uint16_t                  OverCurrentTimeMs;       /*����������ʱ�䣬��λ1ms*/
  uint16_t                  StateCtrlTimeMs;         /*״̬����ʱ�䣬��λ1ms*/
  uint16_t                  RollbackTimeMs;          /*����ʱ�䣬��λ1ms*/

  uint8_t                   Action;                  /*��ﶯ��*/
  uint8_t                   SpeedLevel;              /*�ٶȵȼ�*/
  uint16_t                  RPMSetVal;               /*ת�� ����ֵ*/
  uint16_t                  RPMRealVal;              /*ת�� ʵ��ֵ*/
  uint8_t                   FBWorkState;             /*�����Ĺ���״̬*/
  uint8_t                   NOFBWorkState;           /*�޷����Ĺ���״̬*/
  int16_t                   PWMFinalSetVal;          /*PWM��������ֵ*/
  int16_t                   PWMPreSetVal;            /*PWM Ԥ��ֵ*/
  int16_t                   PWMCompensationVal;      /*PWM ����ֵ*/

  MotorRPMMointor_t         RPMMointor;	             /*ת�� �����*/
  MotorPositionMonitor_t    PositionMonitor;         /*λ�� �����*/

}ZMotor_t;


/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/
/*��ʼ��--------------------------------------*/
ZMotor_t*  ZMotor_Init(void);


/*����ִ��--------------------------------------*/
void ZMotor_PositionIOCheck(Ticker_t ExePeriod);
void ZMotor_OverCurrentIOCheck(Ticker_t ExePeriod);
void ZMotor_RPMCheckHandle(Ticker_t ExePeriod);
void ZMotor_PWMSetValHandle(Ticker_t ExePeriod);
void ZMotor_PositionHandle(Ticker_t ExePeriod);
void ZMotor_ActionHandle(Ticker_t ExePeriod);


/* ����Ľӿڣ� �� ����ģ�� �ɶ� ��ģ��ִ�е� ���Ʋ���-----------------------------
 * ע�⣺X��Y��Z ������� ֻ�ṩ ���޵ļ����ӿ�API��
 *       X���Ƚ����⣬���Ե������������������ú�����
 */
void ZMotor_PauseOn(void);
void ZMotor_PauseOff(void);

uint8_t ZMotor_GetPosition(void);
void ZMotor_SetPosition(uint8_t Position, uint8_t SpeedLevel, uint8_t FBEn);/*����������λ��*/

ZMotorCSFlag_t ZMotor_GetCSFlag(void);
void ZMotor_ResetPosition(void);

#endif

