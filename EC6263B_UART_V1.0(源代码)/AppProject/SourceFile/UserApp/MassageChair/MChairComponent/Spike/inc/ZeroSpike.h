/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: ZeroSpike.h                                                                                                         
**
**    ��������:	�������Ƹ�������
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

#ifndef  _ZEROSPIKE_H
#define  _ZEROSPIKE_H

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
#define  ZEROSPIKE_POSITION_MIN                           0            /*�Ƹ�λ�ã���С*/
#define  ZEROSPIKE_POSITION_MAX                           2            /*�Ƹ�λ�ã����*/

#define  ZEROSPIKE_COUNT_MIN                              0            /*�Ƹ�λ�ü�������С*/
#define  ZEROSPIKE_COUNT_MAX                              1500         /*�Ƹ�λ�ü��������*/
#define  ZEROSPIKE_COUNT_PER_SEGMENT                      ZEROSPIKE_COUNT_MAX/(ZEROSPIKE_COUNT_MAX) /*ÿ��λ�öεļ�����С����*/

#define  ZEROSPIKE_POSITION_DETECT_BY_COUNT               0            /*�Ƹ�λ�ü�ⷽʽ������*/
#define  ZEROSPIKE_POSITION_DETECT_BY_CODE                1            /*�Ƹ�λ�ü�ⷽʽ�����̱���*/
#define  ZEROSPIKE_POSITION_DETECT_MODE                   ZEROSPIKE_POSITION_DETECT_BY_CODE  

#define  ZEROSPIKE_ACTION_STOP                            0            /*�Ƹ˶���ģʽ:ͣ*/
#define  ZEROSPIKE_ACTION_UP                              1            /*�Ƹ˶���ģʽ:��*/
#define  ZEROSPIKE_ACTION_DOWN                            2            /*�Ƹ˶���ģʽ:��*/

#define  ZEROSPIKE_DIRECTION_UP                           BSP_ZEROSPIKE_DIRECTION_UP            /*�Ƹ����з���*/
#define  ZEROSPIKE_DIRECTION_DOWN                         BSP_ZEROSPIKE_DIRECTION_DOWN


#define  ZEROSPIKE_POSITION_CODE_ERR_TIME_THRESHOLD       500          /*λ�ñ������   ����ʱ�䣬��λms*/
#define  ZEROSPIKE_POSITION_SENSOR_LOST_TIME_THRESHOLD    30000        /*λ�ô�����ʧ�� ����ʱ�䣬��λms*/
#define  ZEROSPIKE_COUNT_SENSOR_LOST_TIME_THRESHOLD       1500         /*����������ʧ�� ����ʱ�䣬��λms*/
#define  ZEROSPIKE_OVER_CURRENT_TIME_THRESHOLD            3000         /*�Ƹ˵�������   ����ʱ�䣬��λms*/
#define  ZEROSPIKE_OVER_CURRENT_LEVEL                     0            /*�Ƹ˵���������ƽ*/


#define  ZEROSPIKE_DIRECTION_TIME_MS                      (50 * 10)    /*�Ƹ˻���ʱ�䣬����Ϊ50ms*/
#define  ZEROSPIKE_REVERSE_TIME_MS                        (50 * 20)    /*�Ƹ˷�תʱ�䣬����Ϊ50ms*/



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
}ZeroSpikeCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/

/*
************************************************************************************************************************
* ���Ͷ��� :  �����Ƹ˲���������ݽṹ                                                                                           
************************************************************************************************************************
*/
typedef struct
{
  ZeroSpikeCSFlag_t         CSFlag;                  /*������״̬��ʶ*/

  uint32_t                  RunTimeMs;               /*�Ƹ�����ʱ�䣬��λ1ms*/
  uint16_t                  UpRunTimeMs;             /*��������ʱ�䣬��λ1ms*/
  uint16_t                  DownRunTimeMs;           /*��������ʱ�䣬��λ1ms*/
  uint16_t                  OverCurrentTimeMs;       /*����������ʱ�䣬��λ1ms*/
  uint16_t                  StateCtrlTimeMs;         /*״̬����ʱ�䣬��λ1ms*/

  uint8_t                   Action;                  /*�Ƹ˶���*/
  uint8_t                   PositionRealVal;         /*λ�� ʵ��ֵ*/
  uint8_t                   PositionSetVal;          /*λ�� ����ֵ*/

  MotorPositionMonitor_t    PositionMonitor;         /*λ�� �����*/

}ZeroSpike_t;



/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/
/*��ʼ��--------------------------------------*/
ZeroSpike_t* ZeroSpike_Init(void);


/*����ִ��--------------------------------------*/
void ZeroSpike_PositionIOCheck(Ticker_t ExePeriod);
void ZeroSpike_OverCurrentIOCheck(Ticker_t ExePeriod);
void ZeroSpike_PositionHandle(Ticker_t ExePeriod);
void ZeroSpike_ActionHandle(Ticker_t ExePeriod);


/* ����Ľӿڣ� �� ����ģ�� �ɶ� ��ģ��ִ�е� ���Ʋ���*/
void ZeroSpike_PauseOn(void);
void ZeroSpike_PauseOff(void);

uint8_t ZeroSpike_GetPosition(void);
void ZeroSpike_SetPosition(uint8_t Position);

ZeroSpikeCSFlag_t ZeroSpike_GetCSFlag(void);
void ZeroSpike_ResetPosition(void);
void ZeroSpike_SetCountFaultCheckSw(uint8_t Sw);

#endif
