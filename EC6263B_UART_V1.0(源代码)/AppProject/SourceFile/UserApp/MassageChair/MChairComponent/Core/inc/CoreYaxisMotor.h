/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: CoreYaxisMotor.h                                                                                                         
**
**    ��������: Y�����(����(����)���)������
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
#ifndef  _CORE_YAXIS_MOTOR_H
#define  _CORE_YAXIS_MOTOR_H


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
#define  YMOTOR_POSITION_PARA_BY_MACRO                    1            /*λ�ò����ɺ궨�����*/

#define  YMOTOR_TOP_LIMIT_CODE                            B(01)        /*Y���ϼ���λ�ñ���*/
#define  YMOTOR_BOT_LIMIT_CODE                            B(10)        /*Y���¼���λ�ñ���*/

#define  YMOTOR_POSITION_MIN                              0            /*λ����Сֵ*/
#define  YMOTOR_POSITION_MAX                              73//78//75           /*λ�����ֵ*/

#define  YMOTOR_POSITION_RESET_AT_UNKNOW                  0            /*δ֪*/
#define  YMOTOR_POSITION_RESET_AT_MIN                     1            /*���λ�ø�λ������С��*/
#define  YMOTOR_POSITION_RESET_AT_MAX                     2            /*���λ�ø�λ�������*/
#define  YMOTOR_POSITION_RESET_AT_TOP                     YMOTOR_POSITION_RESET_AT_MIN         
#define  YMOTOR_POSITION_RESET_AT_BOT                     YMOTOR_POSITION_RESET_AT_MAX         
#define  YMOTOR_POSITION_RESET_AT                         YMOTOR_POSITION_RESET_AT_TOP   /*���λ�ø�λ��*/    

#define  YMOTOR_COUNT_MIN                                 0            /*λ�ü�������С*/
#define  YMOTOR_COUNT_MAX                                 730//780//740//750          /*λ�ü��������*/
#define  YMOTOR_COUNT_PER_SEGMENT                         (YMOTOR_COUNT_MAX/YMOTOR_POSITION_MAX) /*ÿ��λ�öεļ�����С����*/

#define  YMOTOR_ACTION_STOP                               0            /*��ﶯ��ģʽ*/
#define  YMOTOR_ACTION_UP                                 1      
#define  YMOTOR_ACTION_DOWN                               2

#define  YMOTOR_DIRECTION_UP                              BSP_YMOTOR_DIRECTION_UP
#define  YMOTOR_DIRECTION_DOWN                            BSP_YMOTOR_DIRECTION_DOWN

#define  YMOTOR_MOVE_NONE                                 0            /*û���˶�*/ 
#define  YMOTOR_MOVE_UP                                   1            /*���������˶�*/
#define  YMOTOR_MOVE_DOWN                                 2            /*���������˶�*/

#define  YMOTOR_SPEEDLEVEL_OFF                            0            /*����ٶ� ��*/
#define  YMOTOR_SPEEDLEVEL_MIN                            1            /*����ٶȵȼ�*/
#define  YMOTOR_SPEEDLEVEL_MAX                            7

#define  YMOTOR_SPEEDLEVEL_DEFAULT                        4            /*Ĭ���ٶ�*/
#define  YMOTOR_FB_DEFAULT                                1            /*Ĭ�Ϸ��� ����*/


#define  YMOTOR_PWM_MIN                                   20           /*��￪ʼת���������СPWM*/
#define  YMOTOR_PWM_MAX                                   255          /*���ȫ��ת�������PWM*/
#define  YMOTOR_PWM_FIXED_STEPING_VAL                     1            /*PWM���ӹ̶�����ֵ*/
#define  YMOTOR_PWMSET_MINI_EXE_PERIODE                   7            /*PWM������Сִ������*/

#define  YMOTOR_RPM_PULSE_NUM                             0x01         /*���תһȦ��ת�����̾�����������*/
#define  YMOTOR_RPM_MEASURE_CYCLE_TIME                    (60000000/YMOTOR_RPM_PULSE_NUM)  /*����RPMʱ,���ܷ�ʹ�õ�ʱ��(60000000us/������)*/
#define  YMOTOR_RPM_CLEAR_TIME_THRESHOLD                  (1000/YMOTOR_RPM_PULSE_NUM)      /*ת��ֵ���� ����ʱ�䣬��λms*/

#define  YMOTOR_RPM_MAX                                   3450         /*������ת��*/

      
#define  YMOTOR_POSITION_CODE_ERR_TIME_THRESHOLD          300          /*λ�ñ������     ����ʱ�䣬��λms*/
#define  YMOTOR_POSITION_SENSOR_LOST_TIME_THRESHOLD       10000        /*λ�ô�����ʧ��   ����ʱ�䣬��λms*/
#define  YMOTOR_RPM_SENSOR_LOST_TIME_THRESHOLD            6000         /*ת�ٴ�����ʧ��   ����ʱ�䣬��λms*/
#define  YMOTOR_OVER_CURRENT_TIME_THRESHOLD               3000         /*������������   ����ʱ�䣬��λms*/
#define  YMOTOR_OVER_CURRENT_LEVEL                        0            /*��������������ƽ*/
/*λ�ü���������ʧ��(��ת�ټ��ʹ��ͬһ������������˹��ϱ���ʱ�������ͬ)   ����ʱ�䣬��λms*/
#define  YMOTOR_COUNT_SENSOR_LOST_TIME_THRESHOLD          YMOTOR_RPM_SENSOR_LOST_TIME_THRESHOLD  


#define  YMOTOR_DIRECTION_TIME_MS                         4000          /*��ﻻ��ʱ��*/
#define  YMOTOR_REVERSE_TIME_MS                           4150          /*��ﷴתʱ��*/


/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� :  Y��� ������״̬��ʶ                                                                                  
************************************************************************************************************************
*/
typedef  union 
{
  uint32_t All;
  struct
  {
    /*Work��ʾ����߼������ڹ���(������Ӧ�Ķ��������Ҳ���Pause�Ƿ���Ч)��
      ��Run��ʾ�����ϵĹ�����Pause��Чʱ����ﲻRun��Pause��Чʱ������Ӧ�Ķ�������Ļ������Run*/
    uint8_t    Work                   :1;    /*������*/
    uint8_t    Pause                  :5;    /*��ͣ*/
    uint8_t    FeedBackEn             :1;    /*��������ʹ��*/
    uint8_t    Run                    :1;    /*����*/
    uint8_t    Direction              :1;    /*����*/
    uint8_t    ReachUpLimt            :1;    /*�Ѵ��Ϸ����޶�*/
    uint8_t    ReachDownLimt          :1;    /*�Ѵ��·����޶�*/

    uint8_t    PositionCodeFault      :1;    /*λ�ñ�����ϣ����ֲ�Ӧ�ô��ڵı���*/
    uint8_t    PositionSensorFault    :1;    /*λ�ô���������*/
    uint8_t    RPMSensorFault         :1;    /*ת�ٴ���������*/
    uint8_t    OverCurrentFault       :1;    /*����������*/
    uint8_t    CountFault             :1;    /*�������ϣ���ⲻ�������仯*/
    uint8_t    Locked                 :1;    /*�����������ٹ���*/

    uint8_t    PositionResetAt        :2;    /*λ�ø�λģʽ���ϸ�λ���¸�λ*/
    uint8_t    PositionResetOK        :1;    /*λ�ø�λ���*/
    uint8_t    CountNocalibrationSw   :1;    /*����λ�ò�У����������*/
  }Bit;

}YMotorCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/

/*
************************************************************************************************************************
* ���Ͷ��� :  Y������������ݽṹ                                                                               
************************************************************************************************************************
*/
typedef struct
{

  YMotorCSFlag_t            CSFlag;                  /*������״̬��ʶ*/

  uint8_t                   PositionRealVal;         /*λ�� ʵ��ֵ*/
  uint8_t                   PositionSetVal;          /*λ�� ����ֵ*/

  uint16_t                  DownRunTimeMs;           /*��������ʱ�䣬��λ1ms*/
  uint16_t                  UpRunTimeMs;             /*��������ʱ�䣬��λ1ms*/
  uint32_t                  RunTimeMs;               /*�������ʱ�䣬��λ1ms*/
  uint16_t                  OverCurrentTimeMs;       /*����������ʱ�䣬��λ1ms*/
  uint16_t                  StateCtrlTimeMs;         /*״̬����ʱ�䣬��λ1ms*/

  uint8_t                   Action;                  /*��ﶯ��*/
  uint8_t                   SpeedLevel;              /*�ٶȵȼ�*/
  uint16_t                  RPMSetVal;               /*ת�� ����ֵ*/
  uint16_t                  RPMRealVal;              /*ת�� ʵ��ֵ*/
  uint8_t                   FBWorkState;             /*�����Ĺ���״̬*/
  int16_t                   PWMFinalSetVal;          /*PWM��������ֵ*/
  int16_t                   PWMPreSetVal;            /*PWM Ԥ��ֵ*/
  int16_t                   PWMCompensationVal;      /*PWM ����ֵ*/

  MotorRPMMointor_t         RPMMointor;              /*ת�� �����*/
  MotorPositionMonitor_t    PositionMonitor;         /*λ�� �����*/

  uint8_t                   TOPLimtCode;             /*Y���ϼ���λ�ñ���*/
  uint8_t                   BOTLimtCode;             /*Y���¼���λ�ñ���*/
  uint8_t                   PositionMax;             /*Y����λ�����ֵ*/
  uint8_t                   CountPerSeg;             /*ÿ���ֶΰ�����λ�ü���ֵ*/
  uint16_t                  PositionCountMax;        /*Y�����г̼������ֵ*/
  
}YMotor_t;


/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/
/*��ʼ��--------------------------------------*/
YMotor_t * YMotor_Init(void);


/*����ִ��--------------------------------------*/
void YMotor_PositionIOCheck(Ticker_t ExePeriod);
void YMotor_OverCurrentIOCheck(Ticker_t ExePeriod);
void YMotor_RPMCheckHandle(Ticker_t ExePeriod);
void YMotor_PWMSetValHandle(Ticker_t ExePeriod);
void YMotor_PositionHandle(Ticker_t ExePeriod);
void YMotor_ActionHandle(Ticker_t ExePeriod);


/* ����Ľӿڣ� �� ����ģ�� �ɶ� ��ģ��ִ�е� ���Ʋ���-----------------------------
 * ע�⣺X��Y��Z ������� ֻ�ṩ ���޵ļ����ӿ�API��
 *       X���Ƚ����⣬���Ե������������������ú�����
 */
void YMotor_PauseOn(void);
void YMotor_PauseOff(void);

uint8_t YMotor_GetPosition(void);
void YMotor_SetPosition(uint8_t Position, uint8_t SpeedLevel, uint8_t FBEn); /*����������λ��*/
uint8_t YMotor_GetPWMOutPutVal(void);
YMotorCSFlag_t YMotor_GetCSFlag(void);
uint8_t YMotor_GetMoveState(void);
void YMotor_ResetPosition(void);
void YMotor_SetPositionCtrPara(uint8_t LimtCode, uint8_t PositionMax, uint16_t PositionCountMax, uint8_t ResetAt);
void YMotor_SetCountNocalibrationSw(uint8_t Sw);
uint16_t YMotor_GetPositionCount(void);

uint8_t YMotor_IfRunTooSlow(void);
void YMotor_ReCheckRunTooSlow(void);

#endif
