/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: CoreXaxisMotor.h                                                                                                         
**
**    ��������: X�����(����(����)���)������
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
#ifndef  _CORE_XAXIS_MOTOR_H
#define  _CORE_XAXIS_MOTOR_H


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
#define  XMOTOR_POSITION_MIN                               0           /*λ����Сֵ*/
#define  XMOTOR_POSITION_MAX                               2           /*λ�����ֵ*/

#define  XMOTOR_ACTION_STOP                                0           /*��ﶯ��ģʽ:ͣ*/
#define  XMOTOR_ACTION_KNEAD_INWARD                        1           /*��ﶯ��ģʽ:����*/
#define  XMOTOR_ACTION_KNEAD_OUTWARD                       2           /*��ﶯ��ģʽ:����*/
#define  XMOTOR_ACTION_LEFT                                3           /*��ﶯ��ģʽ:������*/
#define  XMOTOR_ACTION_RIGHT                               4           /*��ﶯ��ģʽ:������*/

#define  XMOTOR_DIRECTION_LEFT                             BSP_XMOTOR_DIRECTION_LEFT          
#define  XMOTOR_DIRECTION_RIGHT                            BSP_XMOTOR_DIRECTION_RIGHT
#define  XDL                                               XMOTOR_DIRECTION_LEFT     /*X������з��� ��*/
#define  XDR                                               XMOTOR_DIRECTION_RIGHT    /*X������з��� ��*/  

#define  XMOTOR_SPEEDLEVEL_OFF                             0           /*����ٶ� ��*/
#define  XMOTOR_SPEEDLEVEL_MIN                             1           /*����ٶȵȼ�*/
#define  XMOTOR_SPEEDLEVEL_MAX                             5

#define  XMOTOR_SPEEDLEVEL_DEFAULT                         3           /*Ĭ���ٶ�*/
#define  XMOTOR_FB_DEFAULT                                 1           /*Ĭ�Ϸ��� ����*/


#define  XMOTOR_PWM_MIN                                    20          /*��￪ʼת���������СPWM*/
#define  XMOTOR_PWM_MAX                                    255         /*���ȫ��ת�������PWM*/
#define  XMOTOR_PWM_FIXED_STEPING_VAL                      1
#define  XMOTOR_PWMSET_MINI_EXE_PERIODE                    7           /*PWM������Сִ������*/

#define  XMOTOR_RPM_PULSE_NUM                              1           /*���תһȦ��ת�����̾�����������*/
#define  XMOTOR_RPM_MEASURE_CYCLE_TIME                     (60000000/XMOTOR_RPM_PULSE_NUM)  /*����RPMʱ,���ܷ�ʹ�õ�ʱ��(60000000us/������)*/
#define  XMOTOR_RPM_CLEAR_TIME_THRESHOLD                   (1000/XMOTOR_RPM_PULSE_NUM)      /*ת��ֵ���� ����ʱ�䣬��λms*/

#define  XMOTOR_RPM_MAX                                    2700        /*������ת��*/


#define  XMOTOR_POSITION_CODE_ERR_TIME_THRESHOLD           300         /*λ�ñ������     ����ʱ�䣬��λms*/
#define  XMOTOR_POSITION_SENSOR_LOST_TIME_THRESHOLD        8000        /*λ�ô�����ʧ��   ����ʱ�䣬��λms*/
#define  XMOTOR_RPM_SENSOR_LOST_TIME_THRESHOLD             5000        /*ת�ٴ�����ʧ��   ����ʱ�䣬��λms*/
#define  XMOTOR_OVER_CURRENT_TIME_THRESHOLD                3000        /*������������   ����ʱ�䣬��λms*/
#define  XMOTOR_OVER_CURRENT_LEVEL                         0           /*��������������ƽ*/


#define  XMOTOR_DIRECTION_TIME_MS                          4000         /*��ﻻ��ʱ��*/
#define  XMOTOR_REVERSE_TIME_MS                            4100         /*��ﷴתʱ��*/


/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� :  X��� ������״̬��ʶ                                                                                      
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
    uint8_t    ReachLeftLimt          :1;    /*�Ѵ������޶�*/
    uint8_t    ReachRightLimt         :1;    /*�Ѵ��ҷ����޶�*/

    uint8_t    MoveDirectionCtrl      :1;    /*λ���˶��ķ�����ƣ�Ĭ������*/

    uint8_t    PositionCodeFault      :1;    /*λ�ñ�����ϣ����ֲ�Ӧ�ô��ڵı���*/
    uint8_t    PositionSensorFault    :1;    /*λ�ô���������*/
    uint8_t    RPMSensorFault         :1;    /*ת�ٴ���������*/
    uint8_t    OverCurrentFault       :1;    /*����������*/
    uint8_t    Locked                 :1;    /*�����������ٹ���*/

    uint8_t    PositionResetOK        :1;    /*λ�ø�λ���*/

  }Bit;

  uint32_t All;
}XMotorCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/


/*
************************************************************************************************************************
* ���Ͷ��� :  X������������ݽṹ                                                                                   
************************************************************************************************************************
*/
typedef struct
{
  XMotorCSFlag_t            CSFlag;                  /*������״̬��ʶ*/

  uint8_t                   PositionRealVal;         /*λ�� ʵ��ֵ*/
  uint8_t                   PositionSetVal;          /*λ�� ����ֵ*/

  uint16_t                  LeftRunTimeMs;           /*��������ʱ�䣬��λ1ms*/
  uint16_t                  RightRunTimeMs;          /*��������ʱ�䣬��λ1ms*/
  uint32_t                  RunTimeMs;               /*�������ʱ�䣬��λ1ms*/
  uint16_t                  OverCurrentTimeMs;       /*����������ʱ�䣬��λ1ms*/
  uint16_t                  StateCtrlTimeMs;         /*״̬����ʱ�䣬��λ1ms*/

  uint8_t                   Action;                  /*��ﶯ��*/
  uint8_t                   SpeedLevel;              /*�ٶȵȼ�*/
  uint16_t                  RPMSetVal;               /*ת�� ����ֵ*/
  uint8_t                   FBWorkState;             /*�����Ĺ���״̬*/
  int16_t                   PWMFinalSetVal;          /*PWM��������ֵ*/
  int16_t                   PWMPreSetVal;            /*PWM Ԥ��ֵ*/
  int16_t                   PWMCompensationVal;      /*PWM ����ֵ*/

  MotorRPMMointor_t         RPMMointor;              /*ת�� �����*/
  MotorPositionMonitor_t    PositionMonitor;         /*λ�� �����*/

}XMotor_t;



/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/
/*��ʼ��--------------------------------------*/
XMotor_t* XMotor_Init(void);


/*����ִ��--------------------------------------*/
void XMotor_PositionIOCheck(Ticker_t ExePeriod);
void XMotor_OverCurrentIOCheck(Ticker_t ExePeriod);
void XMotor_RPMCheckHandle(Ticker_t ExePeriod);
void XMotor_PWMSetValHandle(Ticker_t ExePeriod);
void XMotor_PositionHandle(Ticker_t ExePeriod);
void XMotor_ActionHandle(Ticker_t ExePeriod);


/* ����Ľӿڣ� �� ����ģ�� �ɶ� ��ģ��ִ�е� ���Ʋ���-----------------------------
 * ע�⣺X��Y��Z ������� ֻ�ṩ ���޵ļ����ӿ�API��
 *       X���Ƚ����⣬���Ե������������������ú�����
 */
void XMotor_PauseOn(void);         /*��ͣ*/
void XMotor_PauseOff(void);        /*�����ͣ*/

uint8_t XMotor_GetPosition(void);  /*��ȡλ��*/
void XMotor_SetPosition(uint8_t Position, uint8_t SpeedLevel, uint8_t FBEn); /*����λ��*/

void XMotor_SetKneadAction(uint8_t Action, uint8_t SpeedLevel, uint8_t FBEn);

void XMotor_SetPositionMoveDirectionCtrl(uint8_t Direction);

XMotorCSFlag_t XMotor_GetCSFlag(void);
void XMotor_ResetPosition(void);

#endif
