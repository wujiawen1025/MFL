/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: FeetSpike.h                                                                                                         
**
**    ��������: С���Ƹ�������
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

#ifndef  _FEETSPIKE_H
#define  _FEETSPIKE_H

/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "bsp.h"
#include "MotorCommon.h"


/*
========================================================================================================================
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/
#define  FEETSPIKE_POSITION_MIN                           0            /*�Ƹ�λ�ã���С*/
#define  FEETSPIKE_POSITION_MAX                           15           /*�Ƹ�λ�ã����*/

#define  FEETSPIKE_COUNT_MIN                              0            /*�Ƹ�λ�ü�������С*/
#define  FEETSPIKE_COUNT_MAX                              1890         /*�Ƹ�λ�ü��������*/
#define  FEETSPIKE_COUNT_PER_SEGMENT                      (FEETSPIKE_COUNT_MAX/FEETSPIKE_POSITION_MAX) /*ÿ��λ�öεļ�����С����*/

#define  FEETSPIKE_POSITION_DETECT_BY_COUNT               0            /*�Ƹ�λ�ü�ⷽʽ������*/
#define  FEETSPIKE_POSITION_DETECT_BY_CODE                1            /*�Ƹ�λ�ü�ⷽʽ�����̱���*/
#define  FEETSPIKE_POSITION_DETECT_MODE                   FEETSPIKE_POSITION_DETECT_BY_COUNT  

#define  FEETSPIKE_ACTION_STOP                            0            /*�Ƹ˶���ģʽ:ͣ*/
#define  FEETSPIKE_ACTION_UP                              1            /*�Ƹ˶���ģʽ:��*/
#define  FEETSPIKE_ACTION_DOWN                            2            /*�Ƹ˶���ģʽ:��*/

#define  FEETSPIKE_DIRECTION_UP                           BSP_FEETSPIKE_DIRECTION_UP            /*�Ƹ����з���*/
#define  FEETSPIKE_DIRECTION_DOWN                         BSP_FEETSPIKE_DIRECTION_DOWN

#define  FEETSPIKE_PWM_MIN                                0            /*��￪ʼת���������СPWM*/
#define  FEETSPIKE_PWM_MAX                                255          /*���ȫ��ת�������PWM*/
#define  FEETSPIKE_PWM_FIXED_STEPING_VAL                  30

#define  FEETSPIKE_POSITION_CODE_ERR_TIME_THRESHOLD       500          /*λ�ñ������   ����ʱ�䣬��λms*/
#define  FEETSPIKE_POSITION_SENSOR_LOST_TIME_THRESHOLD    30000        /*λ�ô�����ʧ�� ����ʱ�䣬��λms*/
#define  FEETSPIKE_COUNT_SENSOR_LOST_TIME_THRESHOLD       1500         /*����������ʧ�� ����ʱ�䣬��λms*/
#define  FEETSPIKE_OVER_CURRENT_TIME_THRESHOLD            3000         /*�Ƹ˵�������   ����ʱ�䣬��λms*/
#define  FEETSPIKE_OVER_CURRENT_LEVEL                     0            /*�Ƹ˵���������ƽ*/


#define  FEETSPIKE_DIRECTION_TIME_MS                      (50 * 6)     /*�Ƹ˻���ʱ�䣬����Ϊ50ms*/
#define  FEETSPIKE_REVERSE_TIME_MS                        (50 * 17)    /*�Ƹ˷�תʱ�䣬����Ϊ50ms*/



/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� :  �����Ƹ� ������״̬��ʶ                                                                                                   
************************************************************************************************************************
*/
typedef  union 
{
  struct
  {
    uint8_t    Work                   :1;    /*������*/
    uint8_t    Pause                  :5;    /*��ͣ*/
    uint8_t    Run                    :1;    /*����*/
    uint8_t    Direction              :1;    /*����*/
    uint8_t    ReachUpLimt            :1;    /*�Ѵ��Ϸ����޶�*/
    uint8_t    ReachDownLimt          :1;    /*�Ѵ��·����޶�*/

    uint8_t    PositionCodeFault      :1;    /*λ�ñ�����ϣ����ֲ�Ӧ�ô��ڵı���*/
    uint8_t    PositionSensorFault    :1;    /*λ�ô���������*/
    //uint8_t    RPMSensorFault         :1;    /*ת�ٴ���������*/
    uint8_t    OverCurrentFault       :1;    /*����������*/
    uint8_t    CountFault             :1;    /*�������ϣ���ⲻ�������仯*/
    uint8_t    CountFaultCheckSw      :1;    /*�������ϼ�⿪��*/
    uint8_t    Locked                 :1;    /*�����������ٹ���*/

    uint8_t    PositionResetOK        :1;    /*λ�ø�λ���*/
  }Bit;

  uint32_t All;
}FeetSpikeCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/

/*
************************************************************************************************************************
* ���Ͷ��� :  �����Ƹ˲���������ݽṹ                                                                                           
************************************************************************************************************************
*/
typedef struct
{
  FeetSpikeCSFlag_t         CSFlag;                  /*������״̬��ʶ*/

  uint32_t                  RunTimeMs;               /*�Ƹ�����ʱ�䣬��λ1ms*/
  uint16_t                  UpRunTimeMs;             /*��������ʱ�䣬��λ1ms*/
  uint16_t                  DownRunTimeMs;           /*��������ʱ�䣬��λ1ms*/
  uint16_t                  OverCurrentTimeMs;       /*����������ʱ�䣬��λ1ms*/
  uint16_t                  StateCtrlTimeMs;         /*״̬����ʱ�䣬��λ1ms*/

  uint8_t                   Action;                  /*�Ƹ˶���*/
  uint8_t                   PositionRealVal;         /*λ�� ʵ��ֵ*/
  uint8_t                   PositionSetVal;          /*λ�� ����ֵ*/

  int16_t                   PWMFinalSetVal;          /*PWM��������ֵ*/

  MotorPositionMonitor_t    PositionMonitor;         /*λ�� �����*/

}FeetSpike_t;



/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/
/*��ʼ��--------------------------------------*/
FeetSpike_t* FeetSpike_Init(void);


/*����ִ��--------------------------------------*/
void FeetSpike_PositionIOCheck(Ticker_t ExePeriod);
void FeetSpike_OverCurrentIOCheck(Ticker_t ExePeriod);
void FeetSpike_PositionHandle(Ticker_t ExePeriod);
void FeetSpike_ActionHandle(Ticker_t ExePeriod);


/* ����Ľӿڣ� �� ����ģ�� �ɶ� ��ģ��ִ�е� ���Ʋ���*/
void FeetSpike_PauseOn(void);
void FeetSpike_PauseOff(void);

uint8_t FeetSpike_GetPosition(void);
void FeetSpike_SetPosition(uint8_t Position);

FeetSpikeCSFlag_t FeetSpike_GetCSFlag(void);
void FeetSpike_ResetPosition(void);
void FeetSpike_SetCountFaultCheckSw(uint8_t Sw);

#endif
