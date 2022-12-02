/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: Spike.h                                                                                                         
**
**    ��������:	�Ƹ����������� ������С�ȡ�С�������������� ���Ƹ�
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
#ifndef  _SPIKE_H
#define  _SPIKE_H


/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "MotorCommon.h"
#include "BackSpike.h"
#include "ZeroSpike.h"
#include "FeetSpike.h"
#include "LegFlexSpike.h"


/*
========================================================================================================================
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/
/*���²�ģ�鳣�õĺ궨�壬�Ը��õ�������ʽչ�ָ�ͬ����ϲ�ģ��===========================*/
#define  PBACK_MIN                                  BACKSPIKE_POSITION_MIN
#define  PBACK_MAX                                  BACKSPIKE_POSITION_MAX
#define  PFEET_MIN                                  FEETSPIKE_POSITION_MIN
#define  PFEET_MAX                                  FEETSPIKE_POSITION_MAX
#define  PZERO_MIN                                  ZEROSPIKE_POSITION_MIN
#define  PZERO_MAX                                  ZEROSPIKE_POSITION_MAX
#define  PLEGFLEX_MIN                               LEGFLEXSPIKE_POSITION_MIN
#define  PLEGFLEX_MAX                               LEGFLEXSPIKE_POSITION_MAX
#define  PULEGFLEX_MIN                              ULEGFLEXSPIKE_POSITION_MIN
#define  PULEGFLEX_MAX                              ULEGFLEXSPIKE_POSITION_MAX


/*�Ƹ� ��������ģʽ ���� �̰�==========================================================*/
#define  SPIKE_KEY_MODE_LONG                        0                      /*�Ƹ�Ϊ����*/
#define  SPIKE_KEY_MODE_SHORT                       1                      /*�Ƹ�Ϊ�̰�*/
#define  SPIKE_KEY_MODE                             SPIKE_KEY_MODE_SHORT


/*�Ƹ� �ռ�λ�� ��غ궨��==========================================================*/
#define  PBACK_HOME_ANGLE                           PBACK00                /*��λ�Ƕ�*/
#define  PFEET_HOME_ANGLE                           PFEET00                /*��λ�Ƕ�*/

#define  PBACK_USER_ANGLE                           PBACK00                /*�����Ƕ�*/
#define  PFEET_USER_ANGLE                           PFEET03                /*�����Ƕ�*/
#define  PZERO_USER_ANGLE                           PZERO04                /*�����Ƕ�*/

#define  PBACK_EXE_ANGLE                            PBACK09                /*ִ�г���Ƕ�*/
#define  PFEET_EXE_ANGLE                            PFEET12                /*ִ�г���Ƕ�*/
#define  PZERO_EXE_ANGLE                            PZERO04                /*ִ�г���Ƕ�*/

#define  PBACK_ZERO1_ANGLE                          PBACK09                /*������1�Ƕ�*/
#define  PFEET_ZERO1_ANGLE                          PFEET12                /*������1�Ƕ�*/
#define  PZERO_ZERO1_ANGLE                          PKEEP                  /*������1�Ƕ�*/

#define  PBACK_ZERO2_ANGLE                          PBACK15                /*������2�Ƕ�*/
#define  PFEET_ZERO2_ANGLE                          PFEET15                /*������2�Ƕ�*/
#define  PZERO_ZERO2_ANGLE                          PKEEP                  /*������2�Ƕ�*/

#define  PBACK_LEG_LEN_DETECT_ANGLE                 PBACK04                /*�����ȳ����ĽǶ�*/
#define  PFEET_LEG_LEN_DETECT_ANGLE                 PFEET04                /*�����ȳ����ĽǶ�*/
#define  PZERO_LEG_LEN_DETECT_ANGLE                 PZERO03                /*�����ȳ����ĽǶ�*/


#define  PBACK15                                    15
#define  PBACK14                                    14
#define  PBACK13                                    13
#define  PBACK12                                    12
#define  PBACK11                                    11
#define  PBACK10                                    10
#define  PBACK09                                    9
#define  PBACK08                                    8
#define  PBACK07                                    7
#define  PBACK06                                    6
#define  PBACK05                                    5
#define  PBACK04                                    4           
#define  PBACK03                                    3
#define  PBACK02                                    2
#define  PBACK01                                    1
#define  PBACK00                                    0

#define  PFEET15                                    15
#define  PFEET14                                    14
#define  PFEET13                                    13
#define  PFEET12                                    12
#define  PFEET11                                    11
#define  PFEET10                                    10
#define  PFEET09                                    9
#define  PFEET08                                    8
#define  PFEET07                                    7
#define  PFEET06                                    6
#define  PFEET05                                    5
#define  PFEET04                                    4           
#define  PFEET03                                    3
#define  PFEET02                                    2
#define  PFEET01                                    1
#define  PFEET00                                    0

#define  PZERO15                                    15
#define  PZERO14                                    14
#define  PZERO13                                    13
#define  PZERO12                                    12
#define  PZERO11                                    11
#define  PZERO10                                    10
#define  PZERO09                                    9
#define  PZERO08                                    8
#define  PZERO07                                    7
#define  PZERO06                                    6
#define  PZERO05                                    5
#define  PZERO04                                    4           
#define  PZERO03                                    3
#define  PZERO02                                    2
#define  PZERO01                                    1
#define  PZERO00                                    0


/*�Ƹ� ��������� ���� �˶� ===================================================================*/
#define  SPIKE_MOVE_NONE                            0
#define  SPIKE_MOVE_BACK_UP                         1
#define  SPIKE_MOVE_BACK_DOWN                       2
#define  SPIKE_MOVE_ZERO_UP                         1
#define  SPIKE_MOVE_ZERO_DOWN                       2
#define  SPIKE_MOVE_FEET_UP                         1
#define  SPIKE_MOVE_FEET_DOWN                       2
#define  SPIKE_MOVE_LEG_SHORT                       1
#define  SPIKE_MOVE_LEG_EXTEND                      2


/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� :  �Ƹ� ������״̬��ʶ                                                                                           
************************************************************************************************************************
*/
typedef  union 
{
  struct
  {
    uint8_t    Pause                          :5;  /*��ͣ*/

    uint8_t    ReachZeroSafetyAngleLimit      :1;  /*�ﵽ��������ȫ�Ƕ�*/

    uint8_t    LegLenDetectPause              :5;  /*��ͣ*/
    uint8_t    LegLenDetectSw                 :1;  /*�ȳ���⿪��*/
    uint8_t    LegLenDetectFinish             :1;  /*�ȳ������ɱ�ʶ*/
    uint8_t    LegLenDetectRun                :1;  /*�ȳ�������б�ʶ*/
    
    uint8_t    LegTouchGroundProtectRun       :1;  /*���ر���*/
  }Bit;
  uint32_t All;
}SpikeCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/


/*
************************************************************************************************************************
* ���Ͷ��� :  �Ƹ˶���                                                                                       
************************************************************************************************************************
*/
typedef union
{
  uint16_t All;
  struct
  {
    uint8_t       BackMove           :2;
    uint8_t       FeetMove           :2;
    uint8_t       ZeroMove           :2;
    uint8_t       LegFlexMove        :2;
    uint8_t       ULegFlexMove       :2;
  }Bit;   
}SpikeAction_t; 

/*
************************************************************************************************************************
* ���Ͷ��� :  �Ƹ˲���������ݽṹ                                                                                      
************************************************************************************************************************
*/
typedef struct
{
  SpikeCSFlag_t            CSFlag;

  SpikeAction_t            ActionCur;
  SpikeAction_t            ActionHis;

  uint8_t                  BackAngleSetVal;                /*�Ƕ� ����ֵ*/
  uint8_t                  FeetAngleSetVal;                /*�Ƕ� ����ֵ*/ 
  uint8_t                  ZeroAngleSetVal;                /*�Ƕ� ����ֵ*/ 
   uint8_t                 LegFlexAngleSetVal;             /*�Ƕ� ����ֵ*/ 
   uint8_t                 ULegFlexAngleSetVal;            /*�Ƕ� ����ֵ*/ 
 //uint8_t                  BackAngleRealVal;               /*�Ƕ� ʵ��ֵ*/
  //uint8_t                  FeetAngleRealVal;               /*�Ƕ� ʵ��ֵ*/
  //uint8_t                  ZeroAngleRealVal;               /*�Ƕ� ʵ��ֵ*/

  uint8_t                  ZeroSafetyAngleLimitBackAngele; /*��������ȫ�Ƕ����� ֮ �����Ƕ�*/  
  uint8_t                  ZeroSafetyAngleLimitZeroAngele; /*��������ȫ�Ƕ����� ֮ �������Ƕ�*/ 

  uint8_t                  LegLenDetectStep;               /*�ȳ���ⲽ��*/
  uint8_t                  LegLenDetectExtendMax;          /*�ȳ����ʱ���쳤�����ֵ*/

  /*�Ƹ˲��� ��ҪΪ�����ã�ʵ�ʱ���Ӧ����ʹ�ø������Ľӿں���-------*/
  BackSpike_t              *pBackSpike;
  FeetSpike_t              *pFeetSpike;
  ZeroSpike_t              *pZeroSpike;
  LegFlexSpike_t           *pLegFlexSpike;

}Spike_t;


/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/
/*��ѯ/�����Ƹ�λ��------------------------------------------------*/
#define  Spike_GetBackAngle()              BackSpike_GetPosition()
#define  Spike_GetZeroAngle()              ZeroSpike_GetPosition()
#define  Spike_GetFeetAngle()              FeetSpike_GetPosition()
#define  Spike_GetLegFlexAngle()           LegFlexSpike_GetPosition()

uint8_t Spike_SetBackAngle(uint8_t BackAngle);
uint8_t Spike_SetZeroAngle(uint8_t ZeroAngle);
uint8_t Spike_SetFeetAngle(uint8_t FeetAngle);
uint8_t Spike_SetLegFlexAngle(uint8_t LegFlexAngle);
uint8_t Spike_SetULegFlexAngle(uint8_t LegFlexAngle);
void Spike_SetAngle(uint8_t BackAngle, uint8_t FeetAngle, uint8_t ZeroAngle);

#define  Spike_ResetBackAngle()            BackSpike_ResetPosition()  /*��λ����ʼλ��*/        
#define  Spike_ResetZeroAngle()            ZeroSpike_ResetPosition()  /*��λ����ʼλ��*/        
#define  Spike_ResetFeetAngle()            FeetSpike_ResetPosition()  /*��λ����ʼλ��*/        

/*��ѯ/�����Ƹ˶���-----------------------------------------------------*/
uint8_t Spike_GetBackMove(void);
uint8_t Spike_GetZeroMove(void);
uint8_t Spike_GetFeetMove(void);
uint8_t Spike_GetLegFlexMove(void);
uint8_t Spike_GetULegFlexMove(void);

void Spike_SetBackMove(uint8_t Move);
void Spike_SetZeroMove(uint8_t Move);
void Spike_SetFeetMove(uint8_t Move);
void Spike_SetLegFlexMove(uint8_t Move);
void Spike_SetULegFlexMove(uint8_t Move);
void Spike_SetMoveAction(uint16_t SpikeMoveAction);

#define  Spike_BackMoveUp()                BackSpike_SetPosition(PBACK_MIN)
#define  Spike_BackMoveDown()              BackSpike_SetPosition(PBACK_MAX)
#define  Spike_BackMoveStop()              BackSpike_SetPosition(PKEEP)

#define  Spike_ZeroMoveUp()                ZeroSpike_SetPosition(PZERO_MAX)
#define  Spike_ZeroMoveDown()              ZeroSpike_SetPosition(PZERO_MIN)
#define  Spike_ZeroMoveStop()              ZeroSpike_SetPosition(PKEEP)

#define  Spike_FeetMoveUp()                FeetSpike_SetPosition(PFEET_MAX)
#define  Spike_FeetMoveDown()              FeetSpike_SetPosition(PFEET_MIN)
#define  Spike_FeetMoveStop()              FeetSpike_SetPosition(PKEEP)

#define  Spike_LegFlexMoveShorten()        LegFlexSpike_SetPosition(PLEGFLEX_MIN)
#define  Spike_LegFlexMoveExtend()         LegFlexSpike_SetPosition(PLEGFLEX_MAX)
#define  Spike_LegFlexMoveStop()           LegFlexSpike_SetPosition(PKEEP)

#define  Spike_ULegFlexMoveShorten()       LegFlexSpike_SetULegPosition(PULEGFLEX_MIN)
#define  Spike_ULegFlexMoveExtend()        LegFlexSpike_SetULegPosition(PULEGFLEX_MAX)
#define  Spike_ULegFlexMoveStop()          LegFlexSpike_SetULegPosition(PKEEP)

/*��������ȫ�޶��Ƕ����--------------------------------------------*/
void Spike_SetZeroSafetyAngleLimitRef(uint8_t RefBack, uint8_t RefZero);

void Spike_SetLegLenDetectSw(uint8_t Sw);
void Spike_LegLenDetectRedo(void);
void Spike_SetLegLenDetectExtendMax(uint8_t MaxLen);
void Spike_LegLenDetectPauseOn(void);
void Spike_LegLenDetectPauseOff(void);


/*�Ƹ� ��ʼ�� �� ������-------------------------------------------*/
Spike_t* Spike_Init(void);
void Spike_Handle(void);

SpikeCSFlag_t Spike_GetCSFlag(void);

#endif
