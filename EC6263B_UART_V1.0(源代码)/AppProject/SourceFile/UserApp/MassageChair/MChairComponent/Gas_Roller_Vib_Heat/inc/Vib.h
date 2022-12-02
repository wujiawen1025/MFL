/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: Vib.h                                                                                                         
**
**    ��������: ��������
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
#ifndef  _VIB_H
#define  _VIB_H

/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "bsp.h"
#include "CDP.h"



/*
========================================================================================================================
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/

#define  VIB_FEET_EN                  1
#define  VIB_CALVES_EN                0
#define  VIB_SEAT_EN                  0
#define  VIB_LUMBARBACK_EN            0

 

/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� :  �񶯶��������                                                                                 
************************************************************************************************************************
*/
typedef struct
{
  uint8_t                SpeedLevel;   /*��ǿ��*/
  uint16_t               OnTime;       /*��ʱ�� ms*/
  uint16_t               OffTime;      /*ͣ��ʱ�� ms*/
  uint8_t                Repeat;       /*�ظ�����*/
}VibTabItem_t;


/*
************************************************************************************************************************
* ���Ͷ��� :  �񶯶���                                                                        
************************************************************************************************************************
*/
typedef union
{
  uint16_t All;
  struct
  {
    uint8_t       Feet            :3;    /*�Ų�*/
    uint8_t       Calves          :3;    /*�Ȳ�*/
    uint8_t       Seat            :3;    /*����*/
    uint8_t       LumbarBack      :3;    /*����*/
    
  }Bit;   
}VibAction_t; 

/*
************************************************************************************************************************
* ���Ͷ��� :  �� ������״̬��ʶ                                                                         
************************************************************************************************************************
*/
typedef  union 
{
  uint32_t All;
  struct
  {
    #if(1==VIB_FEET_EN)
    uint8_t            FeetWork                   :1;    /*������*/
    uint8_t            FeetPause                  :5;    /*��ͣ*/
    uint8_t            FeetRun                    :1;    /*����*/
    #endif
    
    #if(1==VIB_CALVES_EN)
    uint8_t            CalvesWork                 :1;    /*������*/
    uint8_t            CalvesPause                :5;    /*��ͣ*/
    uint8_t            CalvesRun                  :1;    /*����*/
    #endif
    
    #if(1==VIB_SEAT_EN)
    uint8_t            SeatWork                   :1;    /*������*/
    uint8_t            SeatPause                  :5;    /*��ͣ*/
    uint8_t            SeatRun                    :1;    /*����*/
    #endif

    #if(1==VIB_LUMBARBACK_EN)
    uint8_t            LumbarBackWork             :1;    /*������*/
    uint8_t            LumbarBackPause            :5;    /*��ͣ*/
    uint8_t            LumbarBackRun              :1;    /*����*/
    uint8_t            LumbarBackRPMSensorFault   :1;    /*ת��(�����)����������*/
    uint8_t            LumbarBackTestAge          :1;    /*�񶯵���Ŀ�����������*/
    #endif
    
    #if ((0==VIB_FEET_EN) && (0==VIB_CALVES_EN) && (0==VIB_SEAT_EN) && (0==VIB_LUMBARBACK_EN))
    uint8_t            Keep                       :1;    /*�����û�����κι��ܣ�����һ����������ֹ�澯*/
    #endif
  }Bit;
}VibCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/

/*
************************************************************************************************************************
* ���Ͷ��� :  �񶯲���������ݽṹ                                                                             
************************************************************************************************************************
*/
typedef struct
{
  VibCSFlag_t             CSFlag;                      /*������״̬��ʶ*/

  #if(1==VIB_FEET_EN)
  uint8_t                 FeetSetpNum;                 /*������*/  
  uint8_t                 FeetSetpRepeat;              /*�����ظ�����*/ 
  uint16_t                FeetSetpTime;                /*����ʱ��*/ 
  CDP_DataFormat0x4A_t    SetQry0x4A;
  #endif
  
  #if(1==VIB_CALVES_EN)
  uint8_t                 CalvesSetpNum;               /*������*/  
  uint8_t                 CalvesSetpRepeat;            /*�����ظ�����*/ 
  uint16_t                CalvesSetpTime;              /*����ʱ��*/ 
  #endif
  
  #if(1==VIB_SEAT_EN)
  uint8_t                 SeatSetpNum;                 /*������*/  
  uint8_t                 SeatSetpRepeat;              /*�����ظ�����*/ 
  uint16_t                SeatSetpTime;                /*����ʱ��*/ 
  #endif
  
  #if(1==VIB_LUMBARBACK_EN)
  uint8_t                 LumbarBackSetpNum;           /*������*/  
  uint8_t                 LumbarBackSetpRepeat;        /*�����ظ�����*/ 
  uint16_t                LumbarBackSetpTime;          /*����ʱ��*/ 
  #endif

}Vib_t;


/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/
/*��ʼ��--------------------------------------*/
Vib_t*  Vib_Init(void);


/*����ִ��--------------------------------------*/
void Vib_Handle(void);


/* ����Ľӿڣ� �� ����ģ�� �ɶ� ��ģ��ִ�е� ���Ʋ���*/
void Vib_SetLumbarBackVibTestAge(uint8_t OnOff);

void Vib_FeetVibPauseOn(void);
void Vib_FeetVibPauseOff(void);
void Vib_SetFeetVibWorkState(uint8_t  TrueFalse);
void Vib_FeetVibResetStep(void);

void Vib_CalvesVibPauseOn(void);
void Vib_CalvesVibPauseOff(void);
void Vib_SetCalvesVibWorkState(uint8_t  TrueFalse);
void Vib_CalvesVibResetStep(void);

void Vib_SeatVibPauseOn(void);
void Vib_SeatVibPauseOff(void);
void Vib_SetSeatVibWorkState(uint8_t  TrueFalse);
void Vib_SeatVibResetStep(void);

void Vib_LumbarBackVibPauseOn(void);
void Vib_LumbarBackVibPauseOff(void);
void Vib_SetLumbarBackVibWorkState(uint8_t  TrueFalse);
void Vib_LumbarBackVibResetStep(void);

VibCSFlag_t Vib_GetCSFlag(void);

#endif
