/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: ZeroSpike.c                                                                                                         
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

/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "ZeroSpike.h"


/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/


/*
========================================================================================================================
*�������������Ͷ��塿                              �������������Ͷ��塿                              �������������Ͷ��塿
========================================================================================================================
*/


/*
========================================================================================================================
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
========================================================================================================================
*/
static void ZeroSpike_SetAction(uint8_t Action);


static ZeroSpike_t ZeroSpike;
ZeroSpike_t *pZeroSpike = &ZeroSpike;


#if (ZEROSPIKE_POSITION_DETECT_MODE == ZEROSPIKE_POSITION_DETECT_BY_CODE) /*λ�ü��ʹ�����̱��뷽ʽ*/
/*
* �Ƹ�λ�õ㣬���̱����
*
* �������Ƹ�ʹ������ȫ��2λ�����Ʊ��� 
* ʹ��λ�ñ����������ȷ��λ�á�
* ��׺����λ�û�Ӧʹ�ñ��루���00  �10����ȷ����
*
* ���̱����(͸�� 1  �ڵ� 0)��
*  B(00)   //��� 
*  B(01),  //
*  B(11),  //
*  B(10)   //� 
*/
static const PositionCodeMap_t ZeroSpike_PositionCodeMapTab[] =
{
  {B(00), B(01), ZEROSPIKE_POSITION_MAX},  
  {B(01), B(11), 1},
  {B(11), B(10), ZEROSPIKE_POSITION_MIN}
};

#define  ZEROSPIKE_POSITION_CODE_MAPTAB_NUM   TAB_NUM(ZeroSpike_PositionCodeMapTab)

#endif /*���� #if(ZEROSPIKE_POSITION_DETECT_MODE == ZEROSPIKE_POSITION_DETECT_BY_CODE)*/




/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/

#if (ZEROSPIKE_POSITION_DETECT_MODE == ZEROSPIKE_POSITION_DETECT_BY_CODE) /*λ�ü��ʹ�����̱��뷽ʽ*/
/*
************************************************************************************************************************
* �������� : ZeroSpike_PositionCodeMap                                                                                                         
* �������� : �Ƹ�λ�� ���� ӳ��                                                                                                     
* ������� : CodeCur -- ��ǰλ�ñ���                                                                                                      
* ���ز��� : ���� ZEROSPIKE_POSITION_MAX       -- ��Ч�ı��룬λ�ô������⡣
*            С�ڻ����ZEROSPIKE_POSITION_MAX  -- λ�ñ�����Ч                                                                                                        
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t ZeroSpike_PositionCodeMap(uint8_t CodeCur)
{
  uint8_t i;
  uint8_t Position;
  static uint8_t CodeHis = 0xFF;


  Position = pZeroSpike->PositionRealVal;            /*�ȼ���λ��û�ı䣬���´��뽫��������ı�Position�ĸ�ֵ*/

  /*��׺����λ�ã� ����ʹ��λ�ñ�����ȷ��*/
  if(B(10) == CodeCur)
  {
    Position = ZEROSPIKE_POSITION_MIN;
    pZeroSpike->CSFlag.Bit.ReachDownLimt = TRUE;
    pZeroSpike->CSFlag.Bit.ReachUpLimt = FALSE; 
  }
  else if(B(00) == CodeCur)
  {
    Position =  ZEROSPIKE_POSITION_MAX;
    pZeroSpike->CSFlag.Bit.ReachUpLimt = TRUE; 
    pZeroSpike->CSFlag.Bit.ReachDownLimt = FALSE;
  }

  /*ʹ�ñ���������ȷ��λ��*/
  else if(CodeHis != CodeCur) 
  {
    for(i=0; i<ZEROSPIKE_POSITION_CODE_MAPTAB_NUM; i++)
    {
      if((CodeHis == ZeroSpike_PositionCodeMapTab[i].HopCode1) && 
         (CodeCur == ZeroSpike_PositionCodeMapTab[i].HopCode2) )
      {
        Position = ZeroSpike_PositionCodeMapTab[i].Positon;
        break;
      }
      else if((CodeHis == ZeroSpike_PositionCodeMapTab[i].HopCode2) && 
              (CodeCur == ZeroSpike_PositionCodeMapTab[i].HopCode1) )
      {
        Position = ZeroSpike_PositionCodeMapTab[i].Positon;
        break;
      }
    }

    pZeroSpike->CSFlag.Bit.ReachUpLimt   = FALSE;    /*���벻���ڼ���λ�ã�������ޱ�ʶ*/
    pZeroSpike->CSFlag.Bit.ReachDownLimt = FALSE;
  }
  else
  {
    //Position = pZeroSpike->PositionRealVal; /*û�������䣬�򱣳�ԭλ��*/
    pZeroSpike->CSFlag.Bit.ReachUpLimt   = FALSE;    /*���벻���ڼ���λ�ã�������ޱ�ʶ*/
    pZeroSpike->CSFlag.Bit.ReachDownLimt = FALSE;
  }

  CodeHis = CodeCur;
  return Position; 
}

/*
************************************************************************************************************************
* �������� : ZeroSpike_PositionIOCheck                                                                                                         
* �������� : λ�� IO�ڵļ��                                                                                            
* ������� : ExePeriod -- ������ִ������                                                                                                 
* ���ز��� : ��                                                                                             
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void ZeroSpike_PositionIOCheck(Ticker_t ExePeriod)
{
  static uint8_t StableIOCode;                                      /*�ȶ��ı���*/
  static uint8_t StableStat;                                        /*״̬�ȶ�ͳ��*/
  static uint8_t IOCode = B(00);                                    /*Ҫ��λ�������ȼ����ʼΪ��׶�*/

  /*��ʱ���и��ţ����������״̬�ȶ����ж�------------------------*/
  if(StableIOCode != (BSP_IO_ReadInput_ZeroSpikePosition() & B(11)))
  {
    StableStat = 0;                                                 /*�����仯���ʾ���ȶ�*/
    StableIOCode = BSP_IO_ReadInput_ZeroSpikePosition() & B(11);    /*������*/
  }
  else
  {
    if(StableStat < 10)   
    {
      StableStat++;                                                 /*û�����仯�����ȶ�ͳ������*/ 
    }
    else
    {
      IOCode = StableIOCode;                                        /*��ȡ�ȶ���ı���*/
    }
  }


  /* ���ȼ��λ�ñ����Ƿ���ϣ�---------------------------------------------
   * һ��ֻ�����̰�װ���󣬻���û����ʱ��ͣ�����г̣��Ż�������ֹ���
   * ע������ʹ����ȫ�����Ʊ��룬������ λ�ñ������ �ļ�⡣ */


  /*λ�ô��������ϼ�� ------------------------------------------------*/
  if(pZeroSpike->PositionMonitor.PositionCode == IOCode)            /*λ��û�ı�*/
  {
    if(ON == pZeroSpike->CSFlag.Bit.Run)                            /*���������ʱ���ۼӴ�����ʧ��ʱ��*/
    {
      if(pZeroSpike->PositionMonitor.SensorLostTimeMs <= ZEROSPIKE_POSITION_SENSOR_LOST_TIME_THRESHOLD) /*δ����ʧ������ʱ��*/
      {
        pZeroSpike->PositionMonitor.SensorLostTimeMs += ExePeriod;
      }
      else
      {
        pZeroSpike->CSFlag.Bit.PositionSensorFault = FAULT;         /*λ�ô��������ϣ����ֺ󣬳��򲻻����㣬����λ�����ϵ������*/
      }
    }
    else
    {
      pZeroSpike->PositionMonitor.SensorLostTimeMs = 0;             /*���㴫����ʧ��ʱ��*/
    }
  }
  else  /*λ�øı�*/
  { 
    pZeroSpike->PositionMonitor.SensorLostTimeMs = 0;	              /*���㴫����ʧ��ʱ��*/
  }


  /*λ����ر����ж������--------------------------------------------*/
  pZeroSpike->PositionRealVal = ZeroSpike_PositionCodeMap(IOCode);
  if(ZEROSPIKE_POSITION_MIN == pZeroSpike->PositionRealVal)       /*�λ��*/
  {
    pZeroSpike->CSFlag.Bit.PositionResetOK = TRUE;                /*λ�ø�λ���*/
  }

  if((ZEROSPIKE_ACTION_UP == pZeroSpike->Action) && (pZeroSpike->CSFlag.Bit.ReachUpLimt))
  {
    ZeroSpike_SetAction(ZEROSPIKE_ACTION_STOP);                     /*�ﵽ����λ������ִ�������˶�*/
  }

  if((ZEROSPIKE_ACTION_DOWN == pZeroSpike->Action) && (pZeroSpike->CSFlag.Bit.ReachDownLimt))
  {
    ZeroSpike_SetAction(ZEROSPIKE_ACTION_STOP);                     /*�ﵽ����λ������ִ�������˶�*/
  }

  pZeroSpike->PositionMonitor.PositionCode = IOCode;                /*��¼�±���*/
}

#endif /*���� #if(ZEROSPIKE_POSITION_DETECT_MODE == ZEROSPIKE_POSITION_DETECT_BY_CODE)*/



#if (ZEROSPIKE_POSITION_DETECT_MODE == ZEROSPIKE_POSITION_DETECT_BY_COUNT) /*λ�ü��ʹ�ü�����ʽ*/
/*
************************************************************************************************************************
* �������� : ZeroSpike_CountIOCheck_CB                                                                                                         
* �������� : λ�� ����IO�ڼ��  �Ļص�����                                                                                           
* ������� : ��                                                                                    
* ���ز��� : ��                                                                                             
* ����˵�� : �ú���ͨ�� BSP_IO_InputInterrupt_RegCB_ZeroSpikeCount(ZeroSpike_CountIOCheck_CB);����ע���BSP��                                                                                                         
************************************************************************************************************************
*/
static void ZeroSpike_CountIOCheck_CB(void)
{
  /*_COUNT_MIN+3���������������Ƹ�ͣ��ʱ�򣬼���ֵ������0������ӿ쵽0�Ĵ���*/
  MotorCountUpdata(&pZeroSpike->PositionMonitor.PositionCountCur, 
                   pZeroSpike->PositionMonitor.CountDirection, 
                   ZEROSPIKE_COUNT_MAX, ZEROSPIKE_COUNT_MIN+3);
}

/*
************************************************************************************************************************
* �������� : ZeroSpike_PositionIOCheck                                                                                                         
* �������� : λ�� IO�ڵļ��                                                                                   
* ������� : ExePeriod -- ������ִ������                                                                                  
* ���ز��� : ��                                                                                             
* ����˵�� : ��                                                                                                       
************************************************************************************************************************
*/
void ZeroSpike_PositionIOCheck(Ticker_t ExePeriod)
{
  static  Ticker_t ReachMinCountMs;

  /*�������������ϼ��---------------------------------------------*/
  if(pZeroSpike->PositionMonitor.PositionCountHis == pZeroSpike->PositionMonitor.PositionCountCur)  /*�����ޱ仯*/
  {
    if(ON == pZeroSpike->CSFlag.Bit.Run)                                             /*�Ƹ˿���*/
    {
      if(pZeroSpike->PositionMonitor.SensorLostTimeMs <= ZEROSPIKE_COUNT_SENSOR_LOST_TIME_THRESHOLD)
      {
        pZeroSpike->PositionMonitor.SensorLostTimeMs += ExePeriod;                   /*���������ʱ���ۼӼ���������ʧ��ʱ��*/
      }
      else
      {
        ZeroSpike_SetAction(ZEROSPIKE_ACTION_STOP);                                  /*����һ��ֹͣ����ֹͣ����˶�*/

        if(FALSE == pZeroSpike->CSFlag.Bit.PositionResetOK)                          /*λ�û�δ��λ��ɣ�����ϵ�Ҫ���ҳ�ʼλ��*/
        {
          pZeroSpike->CSFlag.Bit.PositionResetOK = TRUE;                             /*λ�ø�λ���*/
          pZeroSpike->PositionMonitor.PositionCountCur = ZEROSPIKE_COUNT_MIN;        /*����λ�ö�Ҫ��������ֵ*/
          pZeroSpike->PositionRealVal = ZEROSPIKE_POSITION_MIN;
        }
        else  //if(TRUE == pZeroSpike->CSFlag.Bit.PositionResetOK)                   /*λ���Ѿ���λ��ɵ�*/
        {
          if((pZeroSpike->PositionSetVal > ZEROSPIKE_POSITION_MIN) &&                /*Ҫ�˶����м��λ�õ�*/
             (pZeroSpike->PositionSetVal < ZEROSPIKE_POSITION_MAX) )
          {
            pZeroSpike->CSFlag.Bit.CountFault = TRUE;                                /*�м�λ�õ���ּ���ֹͣ�����ʾ����������������*/
          }
          else if(ZEROSPIKE_POSITION_MIN == pZeroSpike->PositionSetVal)              /*Ҫ�˶�����Сλ��*/
          {
            if(pZeroSpike->PositionMonitor.PositionCountCur > ZEROSPIKE_COUNT_PER_SEGMENT)
            {
              pZeroSpike->CSFlag.Bit.CountFault = TRUE;                              /*��Сλ�ü���ֵ����С���ʾ����������������*/
            }
            pZeroSpike->PositionMonitor.PositionCountCur = ZEROSPIKE_COUNT_MIN;      /*����λ�ö�Ҫ��������ֵ*/
          }
          else //if(ZEROSPIKE_POSITION_MAX == pZeroSpike->PositionSetVal)            /*Ҫ�˶������λ��*/     
          {
            if(pZeroSpike->PositionMonitor.PositionCountCur < (ZEROSPIKE_COUNT_MAX - ZEROSPIKE_COUNT_PER_SEGMENT))
            {
              pZeroSpike->CSFlag.Bit.CountFault = TRUE;                              /*���λ�ü���ֵ���������ʾ����������������*/
            }
            pZeroSpike->PositionMonitor.PositionCountCur = ZEROSPIKE_COUNT_MAX;      /*����λ�ö�Ҫ��������ֵ*/
          }
        }
      }  
      
      pZeroSpike->CSFlag.Bit.CountFault &= pZeroSpike->CSFlag.Bit.CountFaultCheckSw; /*��⿪����Ч�Ĳ��澯*/
    }
    else //if(OFF == pZeroSpike->CSFlag.Bit.Run)                                     /*�Ƹ�û��*/
    {
      pZeroSpike->PositionMonitor.SensorLostTimeMs = 0;                              /*�������������ʧ��ʱ��*/
    }
  }
  else //if(pZeroSpike->PositionMonitor.PositionCountHis != pZeroSpike->PositionMonitor.PositionCountCur)   /*�����б仯*/
  {
    pZeroSpike->PositionMonitor.PositionCountHis = pZeroSpike->PositionMonitor.PositionCountCur;
    pZeroSpike->PositionMonitor.SensorLostTimeMs = 0;                                /*�������������ʧ��ʱ��*/
  }
  
  /*�ɼ���ֵ�������ǰ��λ�õ�---------------------------------------------------------------*/
  if(ZEROSPIKE_COUNT_MIN == pZeroSpike->PositionMonitor.PositionCountCur)
  {
    if(ReachMinCountMs < 400)        /*����ʼλ�ö�����400ms��У��ʱ��*/
    {
      ReachMinCountMs += ExePeriod;
    }
    else
    {
      pZeroSpike->PositionRealVal          = ZEROSPIKE_POSITION_MIN;
      pZeroSpike->CSFlag.Bit.ReachDownLimt = TRUE;                                     /*���Ｋ��λ��*/
      pZeroSpike->CSFlag.Bit.ReachUpLimt   = FALSE;                               
    }
  }
  else if(ZEROSPIKE_COUNT_MAX == pZeroSpike->PositionMonitor.PositionCountCur)
  {
    ReachMinCountMs = 0;
    pZeroSpike->PositionRealVal          = ZEROSPIKE_POSITION_MAX;
    pZeroSpike->CSFlag.Bit.ReachUpLimt   = TRUE;                                     /*���Ｋ��λ��*/
    pZeroSpike->CSFlag.Bit.ReachDownLimt = FALSE;                              
  }
  else
  {
    ReachMinCountMs = 0;
    pZeroSpike->CSFlag.Bit.ReachUpLimt   = FALSE;                                    /*�����ڼ���λ��*/
    pZeroSpike->CSFlag.Bit.ReachDownLimt = FALSE;                                    /*�����ڼ���λ��*/

    if(OFF == pZeroSpike->CSFlag.Bit.Run)
    {
      return;                                                                        /*�����תʱ���Ÿ��¼���λ��ֵ*/
    }


    if(POSITION_COUNT_INC == pZeroSpike->PositionMonitor.CountDirection)             /*��������*/
    {
      pZeroSpike->PositionRealVal = pZeroSpike->PositionMonitor.PositionCountCur/ZEROSPIKE_COUNT_PER_SEGMENT;
    }
    else //if(POSITION_COUNT_DEC == pZeroSpike->PositionMonitor.CountDirection)      /*��������*/
    {
      pZeroSpike->PositionRealVal = (pZeroSpike->PositionMonitor.PositionCountCur/ZEROSPIKE_COUNT_PER_SEGMENT) + 1;
    }
  }
}

#endif  /* ����if(ZEROSPIKE_POSITION_DETECT_MODE == ZEROSPIKE_POSITION_DETECT_BY_COUNT) */


/*
************************************************************************************************************************
* �������� : ZeroSpike_OverCurrentIOCheck                                                                                                         
* �������� : �Ƹ˹����� IO�ڵļ��                                                                               
* ������� : ExePeriod -- ������ִ������                                                                                  
* ���ز��� : ��                                                                                             
* ����˵�� : ��                                                                                                       
************************************************************************************************************************
*/
void ZeroSpike_OverCurrentIOCheck(Ticker_t ExePeriod)
{
  uint8_t IOCode;

  IOCode = BSP_IO_ReadInput_ZeroSpikeOverCurrent(); 
  if(ZEROSPIKE_OVER_CURRENT_LEVEL == IOCode)
  {
    if(pZeroSpike->OverCurrentTimeMs <= ZEROSPIKE_OVER_CURRENT_TIME_THRESHOLD)
    {
      pZeroSpike->OverCurrentTimeMs += ExePeriod;
    }
    else
    {
      pZeroSpike->CSFlag.Bit.OverCurrentFault = FAULT; 
    }
  }
  else
  {
    pZeroSpike->OverCurrentTimeMs = 0;
  }
}


/*
************************************************************************************************************************
* �������� : ZeroSpike_PauseOn                                                                                                         
* �������� : ��ͣ�Ƹ�                                                                            
* ������� : ��                                                                                
* ���ز��� : ��                                                                                             
* ����˵�� : ������������ת�����ֹͣ������ת��
*            ֻ�н����ͣ��������������ת��                                                                                                      
************************************************************************************************************************
*/
void ZeroSpike_PauseOn(void)
{
  if(pZeroSpike->CSFlag.Bit.Pause < 0x1F)
  {
    pZeroSpike->CSFlag.Bit.Pause++;
  }
}

/*
************************************************************************************************************************
* �������� : ZeroSpike_PauseOff                                                                                                         
* �������� : �����ͣ�Ƹ�                                                                        
* ������� : ��                                                                                
* ���ز��� : ��                                                                                             
* ����˵�� : ������������ת�����ֹͣ������ת��
*            ֻ�н����ͣ��������������ת��                                                                                                      
************************************************************************************************************************
*/
void ZeroSpike_PauseOff(void)
{
  if(pZeroSpike->CSFlag.Bit.Pause > 0)
  {
    pZeroSpike->CSFlag.Bit.Pause--;
  }
}


/*
************************************************************************************************************************
* �������� : ZeroSpike_SetAction                                                                                                         
* �������� : �����Ƹ�Ҫִ�еĶ���                                                                  
* ������� : Action --> ��������ȡֵ��
*                       ZEROSPIKE_ACTION_UP
*                       ZEROSPIKE_ACTION_DOWN
*                       ZEROSPIKE_ACTION_STOP                                                                                
* ���ز��� : ��                                                                                             
* ����˵�� : ��                                                                                               
************************************************************************************************************************
*/
void ZeroSpike_SetAction(uint8_t Action)
{
  if((Action != ZEROSPIKE_ACTION_UP)   &&
     (Action != ZEROSPIKE_ACTION_DOWN) &&
     (Action != ZEROSPIKE_ACTION_STOP) )
  {
    Action = ZEROSPIKE_ACTION_STOP;       /*����������Ч����ִ��ֹͣ����*/
  }
  
  if((ZEROSPIKE_ACTION_UP == Action) && (pZeroSpike->CSFlag.Bit.ReachUpLimt))
  {
    return;                               /*�ﵽ����λ������ִ�������˶�*/
  }
  
  if((ZEROSPIKE_ACTION_DOWN == Action) && (pZeroSpike->CSFlag.Bit.ReachDownLimt))
  {
    return;                               /*�ﵽ����λ������ִ�������˶�*/
  }

  if(TRUE == pZeroSpike->CSFlag.Bit.Locked)  
  {
    return;                               /*��ﱻ������ִ���κζ���*/
  }

  if(Action != ZEROSPIKE_ACTION_STOP) 
  {
    pZeroSpike->CSFlag.Bit.Work = TRUE;   /*������Ч����ʼ����*/
  }
  else
  {
    pZeroSpike->CSFlag.Bit.Work = FALSE;  /*������ЧЧ���򲻹���*/
  }

  pZeroSpike->Action = Action;
}

/*
************************************************************************************************************************
* �������� : ZeroSpike_GetPosition                                                                                                         
* �������� : ��ȡ�Ƹ�λ��                                                           
* ������� : ��                                                                               
* ���ز��� : �Ƹ˵�ǰλ��                                                                                            
* ����˵�� : ��                                                                                               
************************************************************************************************************************
*/
uint8_t ZeroSpike_GetPosition(void)
{
  return pZeroSpike->PositionRealVal;
}

/*
************************************************************************************************************************
* �������� : ZeroSpike_SetPosition                                                                                                         
* �������� : �����Ƹ�λ��                                                         
* ������� : Position --> �Ƹ� ͣ��λ��
*                         ����ֵ��PKEEP          -- ���ֵ�ǰλ�ò�����
*                                 �����������ֵ -- �˶���������ꡣ                                                                                
* ���ز��� : ��                                                                                       
* ����˵�� : ��                                                                                               
************************************************************************************************************************
*/
void ZeroSpike_SetPosition(uint8_t Position)
{
  if((Position > ZEROSPIKE_POSITION_MAX) &&(Position != PKEEP)) 
  {
    Position = ZEROSPIKE_POSITION_MAX;
  }

  pZeroSpike->PositionSetVal = Position; 
}

/*
************************************************************************************************************************
* �������� : ZeroSpike_PositionHandle                                                                                                         
* �������� : �Ƹ�ͣ��λ�ô���                                                    
* ������� : ExePeriod -- ������ִ������                                                                     
* ���ز��� : ��                                                                                      
* ����˵�� : λ�õļ��㣬������ȫ���ö�λ��IO�����Ʊ����⣬
*            ����ֻ��ʹ��  �ο���  ���  ��ǰ�������������Ʊ��������㡣
*            ��ˣ����ҵ��ο�����ǰ���޷���ȷ��֪��ǰλ�á�                                                                                               
************************************************************************************************************************
*/
void ZeroSpike_PositionHandle(Ticker_t ExePeriod)
{
  if(FALSE == pZeroSpike->CSFlag.Bit.PositionResetOK)                /*λ�û�û��λ������û�ҵ�λ�ü���ο���*/
  {
    ZeroSpike_SetAction(ZEROSPIKE_ACTION_DOWN);
  }
  else //if(TRUE == pZeroSpike->CSFlag.Bit.PositionResetOK)          /*λ���Ѿ���λ����λ�ü���ο�����ȷ��*/
  {
    if(PKEEP == pZeroSpike->PositionSetVal)                          /*λ�ñ���*/
    {
      ZeroSpike_SetAction(ZEROSPIKE_ACTION_STOP);
    }
    else                                                             /*����λ��*/
    {
      if(ZEROSPIKE_POSITION_MAX == pZeroSpike->PositionSetVal)       /*����λ�� ��������*/
      {
        if(FALSE == pZeroSpike->CSFlag.Bit.ReachDownLimt)
        {
          ZeroSpike_SetAction(ZEROSPIKE_ACTION_DOWN);
        }
        else
        {
          ZeroSpike_SetAction(ZEROSPIKE_ACTION_STOP);
        }
      }
      else if(ZEROSPIKE_POSITION_MIN == pZeroSpike->PositionSetVal)  /*����λ�� ��������*/
      {
        if(FALSE == pZeroSpike->CSFlag.Bit.ReachUpLimt)
        {
          ZeroSpike_SetAction(ZEROSPIKE_ACTION_UP);
        }
        else
        {
          ZeroSpike_SetAction(ZEROSPIKE_ACTION_STOP);
        }
      }
      else if(pZeroSpike->PositionSetVal == pZeroSpike->PositionRealVal)
      {
        ZeroSpike_SetAction(ZEROSPIKE_ACTION_STOP);
      }
      else if(pZeroSpike->PositionSetVal > pZeroSpike->PositionRealVal)
      {
        ZeroSpike_SetAction(ZEROSPIKE_ACTION_DOWN);
      }
      else //(pZeroSpike->PositionSetVal < pZeroSpike->PositionRealVal)
      {
        ZeroSpike_SetAction(ZEROSPIKE_ACTION_UP);
      }
    }
  }
}


/*
************************************************************************************************************************
* �������� : ZeroSpike_ActionHandle                                                                                                         
* �������� : ��ﶯ������                                           
* ������� : ExePeriod -- ������ִ������                                                                     
* ���ز��� : ��                                                                                      
* ����˵�� : ��                                                                                             
************************************************************************************************************************
*/
void ZeroSpike_ActionHandle(Ticker_t ExePeriod)
{
  static uint8_t   ActionHis = 0xFF;                                      /*��ʷ����״̬*/


  /*����״̬�ĸı��ж�------------------------------------*/
  if(ActionHis != pZeroSpike->Action)
  {
    pZeroSpike->CSFlag.Bit.Run = OFF;                                     /*�����ı䣬����ֹͣ���*/
    if(ActionHis != ZEROSPIKE_ACTION_STOP)
    {
      pZeroSpike->StateCtrlTimeMs = 0;                                    /*��<-->�� �� ��/��-->ֹͣ��������ʱ��*/
    }
    ActionHis = pZeroSpike->Action;
  }

  do
  {
    /*��ͣ��ֹͣ���-----------------------------------------*/
    if(pZeroSpike->CSFlag.Bit.Pause > 0)
    {
      pZeroSpike->CSFlag.Bit.Run    = OFF;	  
      break;
    }

    /* �����쳣����ֹͣ���-------------------------------------*/
    if((FAULT == pZeroSpike->CSFlag.Bit.PositionCodeFault)   ||           /*λ�ñ������*/
       (FAULT == pZeroSpike->CSFlag.Bit.PositionSensorFault) ||           /*λ�ô���������*/
       (FAULT == pZeroSpike->CSFlag.Bit.CountFault)          ||           /*��������*/
       (FAULT == pZeroSpike->CSFlag.Bit.OverCurrentFault)    )            /*����������*/
    {
      pZeroSpike->CSFlag.Bit.Locked = TRUE;	                              /*�쳣���������*/
      pZeroSpike->CSFlag.Bit.Run    = OFF;	                              /*�쳣��ͣ���*/
      pZeroSpike->CSFlag.Bit.Work   = FALSE;	  
      pZeroSpike->StateCtrlTimeMs = 0;
      break;
    }

    /*�������--------------------------------------------------*/
    if(pZeroSpike->Action != ZEROSPIKE_ACTION_STOP)
    {
      if(pZeroSpike->StateCtrlTimeMs < 5000)
      {
        pZeroSpike->StateCtrlTimeMs += ExePeriod; 
      }

      if(pZeroSpike->StateCtrlTimeMs <= ZEROSPIKE_DIRECTION_TIME_MS)	    /*�ȹص��------------*/
      {
        pZeroSpike->CSFlag.Bit.Run = OFF;
      }
      else if(pZeroSpike->StateCtrlTimeMs <= ZEROSPIKE_REVERSE_TIME_MS)   /*�л�����------------*/
      {
        if(ZEROSPIKE_ACTION_UP == pZeroSpike->Action)
        {
          pZeroSpike->UpRunTimeMs                    = 0; 
          pZeroSpike->CSFlag.Bit.Direction           = ZEROSPIKE_DIRECTION_UP;
          pZeroSpike->PositionMonitor.CountDirection = POSITION_COUNT_INC;
        }
        else //if(ZEROSPIKE_ACTION_DOWN == pZeroSpike->Action)
        {
          pZeroSpike->DownRunTimeMs                  = 0; 
          pZeroSpike->CSFlag.Bit.Direction           = ZEROSPIKE_DIRECTION_DOWN;
          pZeroSpike->PositionMonitor.CountDirection = POSITION_COUNT_DEC;
        }
      }
      else /*�����ת---------------------------------------------------------------------------*/
      {
        pZeroSpike->CSFlag.Bit.Run = ON;

        if(ZEROSPIKE_ACTION_UP == pZeroSpike->Action)
        {
          if(pZeroSpike->UpRunTimeMs < (0xFFFF-ExePeriod))                /*-ExePeriod :��ֹ�Ӳ������*/
          {
            pZeroSpike->UpRunTimeMs += ExePeriod; 
          }
        }
        else //if(ZEROSPIKE_ACTION_DOWN == pZeroSpike->Action)
        {
          if(pZeroSpike->DownRunTimeMs < (0xFFFF-ExePeriod))              /*-ExePeriod :��ֹ�Ӳ������*/
          {
            pZeroSpike->DownRunTimeMs += ExePeriod; 
          }
        }

        pZeroSpike->RunTimeMs += ExePeriod;                               /*ͳ�������תʱ��*/
      }
    }
    else	/*pZeroSpike->Action == ZEROSPIKE_ACTION_STOP*/
    {
      pZeroSpike->CSFlag.Bit.Run = OFF;

      if(pZeroSpike->StateCtrlTimeMs < ZEROSPIKE_DIRECTION_TIME_MS)       /*ֹͣʱ�����ۼ�ֹͣʱ�䣬Ҫ����ʱ���ɼӿ�����*/
      {
        pZeroSpike->StateCtrlTimeMs += ExePeriod; 
      }
    }
  }while(0);

  BSP_IO_SetOutput_ZeroSpikeCtrl(pZeroSpike->CSFlag.Bit.Run, pZeroSpike->CSFlag.Bit.Direction, 0);
}



/*
************************************************************************************************************************
* �������� : ZeroSpike_Init                                                                                                         
* �������� : �Ƹ˳�ʼ��                                   
* ������� : ��                                                             
* ���ز��� : ��                                                                                      
* ����˵�� : ��                                                                                             
************************************************************************************************************************
*/
ZeroSpike_t* ZeroSpike_Init(void)
{
  memset(pZeroSpike, 0, sizeof(ZeroSpike_t));                                 /*������������*/
  ZeroSpike_ResetPosition();
  #if (ZEROSPIKE_POSITION_DETECT_MODE == ZEROSPIKE_POSITION_DETECT_BY_COUNT)  /*λ�ü��ʹ�ü�����ʽ*/
    BSP_IO_InputInterrupt_RegCB_ZeroSpikeCount(ZeroSpike_CountIOCheck_CB);    
  #endif
  
  return pZeroSpike;
}


/*
************************************************************************************************************************
* �������� : ZeroSpike_GetCSFlag                                                                                                         
* �������� : ��� ���� �� ״̬ ��ʶ                                   
* ������� : ��                                                             
* ���ز��� : ������״̬��ʶ �Ľṹ��                                                                                      
* ����˵�� : ��                                                                                             
************************************************************************************************************************
*/
ZeroSpikeCSFlag_t ZeroSpike_GetCSFlag(void)
{
  return pZeroSpike->CSFlag;
}


/*
************************************************************************************************************************
* �������� : ZeroSpike_ResetPosition                                                                                                         
* �������� : ��λλ��                                   
* ������� : ��                                                             
* ���ز��� : ��                                                                                      
* ����˵�� : ��                                                                                             
************************************************************************************************************************
*/
void ZeroSpike_ResetPosition(void)
{
  pZeroSpike->CSFlag.Bit.PositionResetOK = FALSE;
  pZeroSpike->PositionSetVal                   = ZEROSPIKE_POSITION_MIN;    /*Ҫʹ�õĲο�λ��*/
  pZeroSpike->PositionRealVal                  = ZEROSPIKE_POSITION_MAX;    /*����ĵ�ǰλ��*/ 
  pZeroSpike->PositionMonitor.PositionCountCur = ZEROSPIKE_COUNT_MAX*2;     /*����ĵ�ǰλ�ü���*/ 
}

/*
************************************************************************************************************************
* �������� : ZeroSpike_SetCountFaultCheckSw                                                                                                          
* �������� : ���ü������ϼ�⿪��                                  
* ������� : Sw -- ON  ��
*                  OFF ��
* ���ز��� : ��                                                                                      
* ����˵�� : ��                                                                                             
************************************************************************************************************************
*/ 
void ZeroSpike_SetCountFaultCheckSw(uint8_t Sw)
{
  if((Sw != ON) && (Sw != OFF))
  {
    Sw = OFF;
  }
  pZeroSpike->CSFlag.Bit.CountFaultCheckSw = Sw;
}

