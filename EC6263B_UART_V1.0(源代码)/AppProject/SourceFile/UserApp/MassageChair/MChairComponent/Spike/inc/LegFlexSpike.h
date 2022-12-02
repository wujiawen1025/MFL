/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: LegFlexSpike.h                                                                                                         
**
**    ��������:С�����Ƹ�������
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
#ifndef  _LEGFLEXSPIKE_H
#define  _LEGFLEXSPIKE_H

/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "bsp.h"
#include "MotorCommon.h"
#include "CDP.h"


/*
========================================================================================================================
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/
#define  LEGFLEX_UP_EN                                       0
#define  LEGFLEX_DOWN_EN                                     1


#define  LEGFLEXSPIKE_POSITION_MIN                           0            /*�� �Ƹ�λ�ã���С*/
#define  LEGFLEXSPIKE_POSITION_MAX                           6            /*�� �Ƹ�λ�ã����*/
#define  LEGFLEXSPIKE_COUNT_MIN                              0            /*�� �Ƹ�λ�ü�������С*/
#define  LEGFLEXSPIKE_COUNT_MAX                              30           /*�� �Ƹ�λ�ü��������*/
#define  LEGFLEXSPIKE_COUNT_PER_SEGMENT                      (LEGFLEXSPIKE_COUNT_MAX/LEGFLEXSPIKE_POSITION_MAX) /*ÿ��λ�öεļ�����С����*/

#define  ULEGFLEXSPIKE_POSITION_MIN                          0            /*�� �Ƹ�λ�ã���С*/
#define  ULEGFLEXSPIKE_POSITION_MAX                          3            /*�� �Ƹ�λ�ã����*/
#define  ULEGFLEXSPIKE_COUNT_MIN                             0            /*�� �Ƹ�λ�ü�������С*/
#define  ULEGFLEXSPIKE_COUNT_MAX                             15           /*�� �Ƹ�λ�ü��������*/
#define  ULEGFLEXSPIKE_COUNT_PER_SEGMENT                     (ULEGFLEXSPIKE_COUNT_MAX/ULEGFLEXSPIKE_POSITION_MAX) /*�� ÿ��λ�öεļ�����С����*/


#define  LEGFLEXSPIKE_ACTION_STOP                            0            /*�Ƹ˶���ģʽ:ͣ*/
#define  LEGFLEXSPIKE_ACTION_SHORTEN                         1            /*�Ƹ˶���ģʽ:����*/
#define  LEGFLEXSPIKE_ACTION_EXTEND                          2            /*�Ƹ˶���ģʽ:�쳤*/

#define  LEGFLEXSPIKE_DIRECTION_SHORTEN                      0            /*�Ƹ����з���*/
#define  LEGFLEXSPIKE_DIRECTION_EXTEND                       1

#define  LEGFLEXSPIKE_POSITION_CODE_ERR_TIME_THRESHOLD       500          /*λ�ñ������     ����ʱ�䣬��λms*/
#define  LEGFLEXSPIKE_POSITION_SENSOR_LOST_TIME_THRESHOLD    10000        /*λ�ô�����ʧ��   ����ʱ�䣬��λms*/
#define  LEGFLEXSPIKE_COUNT_SENSOR_LOST_TIME_THRESHOLD       5000         /*����������ʧ��   ����ʱ�䣬��λms*/

#define  LEGFLEXSPIKE_DIRECTION_TIME_MS                      (50 * 6)     /*�Ƹ˻���ʱ�䣬����Ϊ50ms*/
#define  LEGFLEXSPIKE_REVERSE_TIME_MS                        (50 * 12)    /*�Ƹ˷�תʱ�䣬����Ϊ50ms*/

/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� :  С�������Ƹ� ������״̬��ʶ                                                                                                 
************************************************************************************************************************
*/
typedef  union 
{
  struct
  {
    uint8_t    Work                            :1;    /*������*/
    uint8_t    Pause                           :4;    /*��ͣ*/
    uint8_t    Run                             :1;    /*����*/
    uint8_t    Direction                       :1;    /*����*/
    uint8_t    ReachExtendLimt                 :1;    /*�Ѵ���޶�*/
    uint8_t    ReachShortenLimt                :1;    /*�Ѵ�����޶�*/
    uint8_t    TouchGround                     :1;    /*����*/
    uint8_t    TouchFeet                       :1;    /*����*/
    uint8_t    PositionCodeFault               :1;    /*λ�ñ�����ϣ����ֲ�Ӧ�ô��ڵı���*/
    uint8_t    ExtendPositionSensorFault       :1;    /*���λ����������*/
    uint8_t    ShortPositionSensorFault        :1;    /*�����λ����������*/
    uint8_t    CountFault                      :1;    /*�������ϣ���ⲻ�������仯*/
    uint8_t    Locked                          :1;    /*�����������ٹ���*/
    uint8_t    PositionResetOK                 :1;    /*λ�ø�λ���*/
    
    uint8_t    ULegWork                        :1;    /*������*/
    uint8_t    ULegPause                       :4;    /*��ͣ*/
    uint8_t    ULegRun                         :1;    /*����*/
    uint8_t    ULegDirection                   :1;    /*����*/
    uint8_t    ULegReachExtendLimt             :1;    /*�Ѵ���޶�*/
    uint8_t    ULegReachShortenLimt            :1;    /*�Ѵ�����޶�*/
    uint8_t    ULegPositionCodeFault           :1;    /*λ�ñ�����ϣ����ֲ�Ӧ�ô��ڵı���*/
    uint8_t    ULegExtendPositionSensorFault   :1;    /*���λ����������*/
    uint8_t    ULegShortPositionSensorFault    :1;    /*�����λ����������*/
    uint8_t    ULegCountFault                  :1;    /*�������ϣ���ⲻ�������仯*/
    uint8_t    ULegLocked                      :1;    /*�����������ٹ���*/
    uint8_t    ULegPositionResetOK             :1;    /*λ�ø�λ���*/
  }Bit;

  uint32_t All;
}LegFlexSpikeCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/

/*
************************************************************************************************************************
* ���Ͷ��� :  С�������Ƹ˲���������ݽṹ                                                                                              
************************************************************************************************************************
*/
typedef struct
{
  LegFlexSpikeCSFlag_t      CSFlag;                   /*������״̬��ʶ*/

  uint32_t                  RunTimeMs;                /*�Ƹ�����ʱ�䣬��λ1ms*/
  uint16_t                  StateCtrlTimeMs;          /*״̬����ʱ�䣬��λ1ms*/
  uint8_t                   Action;                   /*�Ƹ˶���*/
  uint8_t                   PositionRealVal;          /*λ�� ʵ��ֵ*/
  uint8_t                   PositionSetVal;           /*λ�� ����ֵ*/
  MotorPositionMonitor_t    PositionMonitor;          /*λ�� �����*/
  
  uint32_t                  ULegRunTimeMs;            /*�Ƹ�����ʱ�䣬��λ1ms*/
  uint16_t                  ULegStateCtrlTimeMs;      /*״̬����ʱ�䣬��λ1ms*/
  uint8_t                   ULegAction;               /*�Ƹ˶���*/
  uint8_t                   ULegPositionRealVal;      /*λ�� ʵ��ֵ*/
  uint8_t                   ULegPositionSetVal;       /*λ�� ����ֵ*/
  MotorPositionMonitor_t    ULegPositionMonitor;      /*λ�� �����*/
  
  CDP_DataFormat0x4B_t    SetQry0x4B;
  
}LegFlexSpike_t;


/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/

/*��ʼ��--------------------------------------*/
LegFlexSpike_t* LegFlexSpike_Init(void);


/*����ִ��--------------------------------------*/
void LegFlexSpike_IOCheck(Ticker_t ExePeriod);
void LegFlexSpike_ActionHandle(Ticker_t ExePeriod);


/* ����Ľӿڣ� �� ����ģ�� �ɶ� ��ģ��ִ�е� ���Ʋ���*/
void LegFlexSpike_PauseOn(void);
void LegFlexSpike_PauseOff(void);

uint8_t LegFlexSpike_GetPosition(void);
void LegFlexSpike_SetPosition(uint8_t Position);

void LegFlexSpike_PositionHandle(Ticker_t ExePeriod);
void LegFlexSpike_SetAction(uint8_t Action);

LegFlexSpikeCSFlag_t LegFlexSpike_GetCSFlag(void);


//==========================================================
void LegFlexSpike_SetULegAction(uint8_t Action);
uint8_t LegFlexSpike_GetULegPosition(void);
void LegFlexSpike_SetULegPosition(uint8_t Position);

#endif
