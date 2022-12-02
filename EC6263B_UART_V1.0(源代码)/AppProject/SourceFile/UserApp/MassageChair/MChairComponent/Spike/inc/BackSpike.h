/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: BackSpike.h                                                                                                         
**
**    ��������: �����Ƹ�������
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

#ifndef  _BACKSPIKE_H
#define  _BACKSPIKE_H

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
#define  BACKSPIKE_POSITION_MIN                           0            /*�Ƹ�λ�ã���С*/
#define  BACKSPIKE_POSITION_MAX                           15           /*�Ƹ�λ�ã����*/

#define  BACKSPIKE_COUNT_MIN                              0            /*�Ƹ�λ�ü�������С*/
#define  BACKSPIKE_COUNT_MAX                              970//973     /*�Ƹ�λ�ü��������*/
#define  BACKSPIKE_COUNT_PER_SEGMENT                      (BACKSPIKE_COUNT_MAX/BACKSPIKE_POSITION_MAX) /*ÿ��λ�öεļ�����С����*/

#define  BACKSPIKE_POSITION_DETECT_BY_COUNT               0            /*�Ƹ�λ�ü�ⷽʽ������*/
#define  BACKSPIKE_POSITION_DETECT_BY_CODE                1            /*�Ƹ�λ�ü�ⷽʽ�����̱���*/
#define  BACKSPIKE_POSITION_DETECT_MODE                   BACKSPIKE_POSITION_DETECT_BY_COUNT  

#define  BACKSPIKE_ACTION_STOP                            0            /*�Ƹ˶���ģʽ:ͣ*/
#define  BACKSPIKE_ACTION_UP                              1            /*�Ƹ˶���ģʽ:��*/
#define  BACKSPIKE_ACTION_DOWN                            2            /*�Ƹ˶���ģʽ:��*/

#define  BACKSPIKE_DIRECTION_UP                           BSP_BACKSPIKE_DIRECTION_UP            /*�Ƹ����з���*/
#define  BACKSPIKE_DIRECTION_DOWN                         BSP_BACKSPIKE_DIRECTION_DOWN

#define  BACKSPIKE_PWM_MIN                                0            /*��￪ʼת���������СPWM*/
#define  BACKSPIKE_PWM_MAX                                255          /*���ȫ��ת�������PWM*/
#define  BACKSPIKE_PWM_FIXED_STEPING_VAL                  30

#define  BACKSPIKE_POSITION_CODE_ERR_TIME_THRESHOLD       500          /*λ�ñ������   ����ʱ�䣬��λms*/
#define  BACKSPIKE_POSITION_SENSOR_LOST_TIME_THRESHOLD    30000        /*λ�ô�����ʧ�� ����ʱ�䣬��λms*/
#define  BACKSPIKE_COUNT_SENSOR_LOST_TIME_THRESHOLD       1500         /*����������ʧ�� ����ʱ�䣬��λms*/
#define  BACKSPIKE_OVER_CURRENT_TIME_THRESHOLD            3000         /*�Ƹ˵�������   ����ʱ�䣬��λms*/
#define  BACKSPIKE_OVER_CURRENT_LEVEL                     0            /*�Ƹ˵���������ƽ*/


#define  BACKSPIKE_DIRECTION_TIME_MS                      (50 * 6)     /*�Ƹ˻���ʱ�䣬����Ϊ50ms*/
#define  BACKSPIKE_REVERSE_TIME_MS                        (50 * 12)    /*�Ƹ˷�תʱ�䣬����Ϊ50ms*/



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
}BackSpikeCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/

/*
************************************************************************************************************************
* ���Ͷ��� :  �����Ƹ˲���������ݽṹ                                                                                           
************************************************************************************************************************
*/
typedef struct
{
  BackSpikeCSFlag_t         CSFlag;                  /*������״̬��ʶ*/

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

}BackSpike_t;



/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/
/*��ʼ��--------------------------------------*/
BackSpike_t* BackSpike_Init(void);


/*����ִ��--------------------------------------*/
void BackSpike_PositionIOCheck(Ticker_t ExePeriod);
void BackSpike_OverCurrentIOCheck(Ticker_t ExePeriod);
void BackSpike_PositionHandle(Ticker_t ExePeriod);
void BackSpike_ActionHandle(Ticker_t ExePeriod);


/* ����Ľӿڣ� �� ����ģ�� �ɶ� ��ģ��ִ�е� ���Ʋ���*/
void BackSpike_PauseOn(void);
void BackSpike_PauseOff(void);

uint8_t BackSpike_GetPosition(void);
void BackSpike_SetPosition(uint8_t Position);

BackSpikeCSFlag_t BackSpike_GetCSFlag(void);
void BackSpike_ResetPosition(void);
void BackSpike_SetCountFaultCheckSw(uint8_t Sw);

#endif
