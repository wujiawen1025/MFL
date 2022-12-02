/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: CDP.h                                                                                                         
**
**    ��������: ͨ�����ݰ���
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
#ifndef  _CDP_H
#define  _CDP_H


/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "GlobalCfg.h"
#include "bsp.h"
#include "ESF.h"          
#include "CDP_CenXxx.h"
#include "CDP_Common.h"
//#include "CDP_CenDebug.h"
#include "CDP_CenServer.h"
#include "CDP_CenApp.h"

/*
========================================================================================================================
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/
#define  CDP_FRAME_MIN_LEN                      9                    /*��С֡����*/ 
#define  CDP_PDU_EXCEPT_DU_LEN                  6                    /*Э�����ݵ�Ԫ�ĳ���(�������ݵ�Ԫ)*/


#define  CDP_FRAME_BOUNDARY                     0x7E                 /*֡�߽�*/            
#define  CDP_FRAME_HEADER                       CDP_FRAME_BOUNDARY   /*֡ͷ*/
#define  CDP_FRAME_FOOTER                       CDP_FRAME_BOUNDARY   /*֡β*/            
#define  CDP_FRAME_ESC                          0x5E                 /*֡ת��*/   


#define  CDP_FRAME_OFFSET_HEADER                0                    /*֡ͷƫ��*/
#define  CDP_FRAME_OFFSET_PDU                   1                    /*Э�����ݵ�Ԫƫ�ƣ���֡ͷ��ʼ��ĵ�һ������*/

#define  CDP_PDU_OFFSET_DES                     0                    /*Э�����ݵ�Ԫ�ڵ� Ŀ�ĵ�ַ ƫ��*/
#define  CDP_PDU_OFFSET_SRC                     1                    /*Э�����ݵ�Ԫ�ڵ� Դ��ַ   ƫ��*/
#define  CDP_PDU_OFFSET_VER                     2                    /*Э�����ݵ�Ԫ�ڵ� �汾��   ƫ��*/
#define  CDP_PDU_OFFSET_CMD                     4                    /*Э�����ݵ�Ԫ�ڵ� ������   ƫ��*/
#define  CDP_PDU_OFFSET_ACK                     5                    /*Э�����ݵ�Ԫ�ڵ� Ӧ��     ƫ��*/
#define  CDP_PDU_OFFSET_DU                      6                    /*Э�����ݵ�Ԫ�ڵ� ���ݵ�Ԫ ƫ��*/

#define  CDP_DU_OFFSET_LEN                      0                    /*���ݵ�Ԫ�ڵ� ���� ƫ��*/            
#define  CDP_DU_OFFSET_ID                       1                    /*���ݵ�Ԫ�ڵ� ID   ƫ��*/  
#define  CDP_DU_OFFSET_DATA                     2                    /*���ݵ�Ԫ�ڵ� ���� ƫ��*/  
#define  CDP_DU_OFFSET_SERVER_ID                2                    /*Զ���������ݵ�Ԫ�ڵ� ID   ƫ��*/
#define  CDP_DU_OFFSET_SERVER_DATA              3                    /*Զ���������ݵ�Ԫ�ڵ� ���� ƫ��*/

#define  CDP_ADDR_CEN                           0x01                 /*��ַ�����İ�*/
#define  CDP_ADDR_CTR                           0x10                 /*��ַ�������ֿ��� / ��ƽ�� / �ֻ�APP */
#define  CDP_ADDR_CTR_SIDE                      0x11                 /*��ַ����尴�� */
#define  CDP_ADDR_WIFI                          0x13                 /*��ַ��͸��ͨѶģ�� */
#define  CDP_ADDR_SERVER                        0x14                 /*��ַ����̨������ */
#define  CDP_ADDR_CORE                          0x20                 /*��ַ����о��*/
#define  CDP_ADDR_CORE_X                        0x21                 /*��ַ����оX�����ư�*/
#define  CDP_ADDR_CORE_Y                        0x22                 /*��ַ����оY�����ư�*/
#define  CDP_ADDR_CORE_Z                        0x23                 /*��ַ����оZ�����ư�*/
#define  CDP_ADDR_CORE_TCS                      0x24                 /*��ַ����о�û������ư�*/
#define  CDP_ADDR_SPIKE                         0x30                 /*��ַ���Ƹ˿��ư�*/
#define  CDP_ADDR_SPIKE_BACK                    0x31                 /*��ַ�������Ƹ˿��ư�*/
#define  CDP_ADDR_SPIKE_FEET                    0x32                 /*��ַ��С���Ƹ˿��ư�*/
#define  CDP_ADDR_SPIKE_ZERO                    0x33                 /*��ַ���������Ƹ˿��ư�*/
#define  CDP_ADDR_SPIKE_FEETFLEX                0x34                 /*��ַ��С���������ư�*/
#define  CDP_ADDR_HEAT                          0x40                 /*��ַ�����ȿ��ư�*/
#define  CDP_ADDR_HEAT_HEAD                     0x41                 /*��ַ��ͷ�����ȿ��ư�*/
#define  CDP_ADDR_HEAT_LUMBARBACK               0x42                 /*��ַ���������ȿ��ư�*/
#define  CDP_ADDR_HEAT_SEAT                     0x43                 /*��ַ���������ȿ��ư�*/
#define  CDP_ADDR_HEAT_CALVES                   0x44                 /*��ַ���Ȳ����ȿ��ư�*/
#define  CDP_ADDR_HEAT_FEET                     0x45                 /*��ַ���Ų����ȿ��ư�*/
#define  CDP_ADDR_HEAT_ARMS                     0x46                 /*��ַ���ֲ����ȿ��ư�*/
#define  CDP_ADDR_VIB                           0x48                 /*��ַ���񶯿��ư�*/
#define  CDP_ADDR_VIB_HEAD                      0x49                 /*��ַ��ͷ���񶯿��ư�*/
#define  CDP_ADDR_VIB_LUMBARBACK                0x4A                 /*��ַ�������񶯿��ư�*/
#define  CDP_ADDR_VIB_SEAT                      0x4B                 /*��ַ�������񶯿��ư�*/
#define  CDP_ADDR_VIB_CALVES                    0x4C                 /*��ַ���Ȳ��񶯿��ư�*/
#define  CDP_ADDR_VIB_FEET                      0x4D                 /*��ַ���Ų��񶯿��ư�*/
#define  CDP_ADDR_VIB_ARMS                      0x4E                 /*��ַ���ֲ��񶯿��ư�*/
#define  CDP_ADDR_ROLLER                        0x50                 /*��ַ�����ֿ��ư�*/
#define  CDP_ADDR_ROLLER_FEET                   0x51                 /*��ַ���Ź����ư�*/
#define  CDP_ADDR_ROLLER_CALVES                 0x52                 /*��ַ��С�ȹ����ư�*/
#define  CDP_ADDR_LED                           0x58                 /*��ַ���ƹ���ư�*/
#define  CDP_ADDR_CALVES_FEET                   0x60                 /*��ַ���Ƚſ��ư�*/
/*ע�⣺һ������ģ���п��ܰ�������߼����ܡ�����С��ģ����ܰ�����С��������С�ȳ������Ź��ȡ�
 *      �������ʦ����ϵͳ���������������ַ���ɣ��ɷ���"0x34С���������ư�"��Ҳ�ɷ����"0x51 �Ź����ư�",
 *      Ҳ�ɷ����"0x60�Ƚ��ۺϿ��ư�"������Ȼ��ģ���ַ����ͻ������£������������书���൱�ĵ�ַ���ơ�*/
#define  CDP_ADDR_SELF                          CDP_ADDR_CEN         /*��ַ������*/


#define  CDP_CMD_UPREPORT                       0x01                 /*����ӻ������ϱ� */
#define  CDP_CMD_QRY                            0x02                 /*���������ѯ�ӻ� */   
#define  CDP_CMD_SET_NACK                       0x03                 /*����������ôӻ����ӻ�����Ӧ�� */    
#define  CDP_CMD_SET_ACK                        0x04                 /*����������ôӻ����ӻ���Ӧ�� */  
#define  CDP_CMD_UPREPORT_SERVER                0x11                 /*��������� �����ϱ�����ҪӦ��*/ 
#define  CDP_CMD_QRY_SERVER                     0x12                 /*��������� ������ѯ�ӻ�*/ 
#define  CDP_CMD_SET_NACK_SERVER                0x13                 /*��������� �������ôӻ����ӻ�����Ӧ��*/ 
#define  CDP_CMD_SET_ACK_SERVER                 0x14                 /*��������� �������ôӻ����ӻ���Ӧ��*/ 
#define  CDP_CMD_TIMEING_UPREPORT_SERVER        0x15                 /*��������� ����������ʱ�ϱ����ӻ��費Ӧ��*/ 
#define  CDP_CMD_IAP                            0xF0                 /*���IAP�������� */   
#define  CDP_CMD_REMOTE_IAP                     0xF1                 /*���Զ��IAP�������� */  


#define  CDP_ACK_SUCCESS                        0x00                 /*Ӧ��ִ�гɹ� */
#define  CDP_ACK_FAIL                           0x01                 /*Ӧ��ִ��ʧ�� */
#define  CDP_ACK_INVALID_CMD                    0x02                 /*Ӧ�𣺲�֧�ֵ������� */
#define  CDP_ACK_INVALID_LEN                    0x03                 /*Ӧ�����ݳ��ȴ� */
#define  CDP_ACK_INVALID_ID                     0x04                 /*Ӧ���������в�֧�ֵ�IDʶ���� */
#define  CDP_ACK_SEND                           0xFF                 /*Ӧ�����ݵ��������𷽣���0xFF */


#define  CDP_DAP_CTRL                           0x01                 /*���ݷ�������˿ڣ��ֿ���*/                                       
#define  CDP_DAP_CEN                            0x02                 /*���ݷ�������˿ڣ���о��*/                                                  
#define  CDP_DAP_CORE                           0x03                 /*���ݷ�������˿ڣ���о��*/                                                  
#define  CDP_DAP_OTHER                          0xFF                 /*���ݷ�������˿ڣ�����*/                                                  

#define  CDP_TYPE_COMMON                        0x00                 /*ͨ�����ݰ����ͣ�ͨ��*/                              
#define  CDP_TYPE_OLD_PROTOCOL                  0x01                 /*ͨ�����ݰ����ͣ���Э��*/                                     
#define  CDP_TYPE_NEW_PROTOCOL                  0x02                 /*ͨ�����ݰ����ͣ���Э��*/                                    
#define  CDP_TYPE_CTRL                          0x10                 /*ͨ�����ݰ����ͣ��ֿ���*/                                    
#define  CDP_TYPE_SIDE_CTRL                     0x11                 /*ͨ�����ݰ����ͣ���������*/                                    
#define  CDP_TYPE_APP_KEY                       0x12                 /*ͨ�����ݰ����ͣ�APP��ֵ*/                                    
#define  CDP_TYPE_APP_CFG                       0x13                 /*ͨ�����ݰ����ͣ�APP����*/                                    

#define  CDP_DU_HANDLE_INVALID_ID               0xFE                 /*���ݵ�Ԫ���� ��֧�ֵ�ID*/                                       
#define  CDP_DU_HANDLE_ERR                      0xFF                 /*���ݵ�Ԫ�������*/                                       


/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/

/*������������������������������������������������������������������������������������������������������������������������������*/
/*
************************************************************************************************************************
* ���Ͷ��� :  0x01 ��ֵ(�ֿ���-->���İ�)                                                                     
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID;
  
  uint8_t             KeyVal;                                      /*��ֵ*/
  uint8_t             AddtionData[1];                              /*��ֵ������������*/

}CDP_DataFormat0x01_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  0x1F �����ԣ���λ�� <-->���İ壩�����ڸ������Ű�Ħ�������                                                              
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         ChannelSw                             :1;    /*�������ͨ������*/
      uint8_t         StepHop                               :2;    /*����ִ�б�ʶ*/
    }Bit;
  }Byte0; 
  
  uint8_t             TabType;                                     /*�������*/

  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         ChannelNoSupport                      :1;    /*ͨ���Ų�֧��*/
      uint8_t         TapTypeNoSupport                      :1;    /*������Ͳ�֧��*/
      uint8_t         ResourceConflict                      :1;    /*�����������Դ��ͻ��ʶ*/
      uint8_t         ConflictChnanelNum                    :3;    /*��ͻ��ͨ����*/
    }Bit;
  }Byte2; 
  
  uint8_t             StepSum;                                     /*�ܲ���*/
  uint8_t             StepNum;                                     /*�·����ݵĲ����*/
  uint8_t             StepData[1];                                 /*��������*/
}CDP_DataFormat0x1A_To_0x1F_t;

/*
************************************************************************************************************************
* ���Ͷ��� : 0x20 ״̬��Ϣ���ܰ������İ�-->�ֿ�����                                                                
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         SysRun                                :1;    /*ϵͳ���У����Ǵ���ģʽ*/
      uint8_t         Pause                                 :1;    /*��ͣ*/
      uint8_t         SysModeCur                            :6;    /*ϵͳģʽ ��ǰ*/
    }Bit;
  }Byte0; 

  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         BackLightRun                          :1;    /*��������Ļ����(����Դ) */
      uint8_t         PromptToneRun                         :1;    /*��������ʾ��(������)����*/
      uint8_t         UserMassageTimeOut                    :1;    /*��Ħ��ʱ��״̬*/
      uint8_t         InsepectAutoFinish                    :1;    /*�Զ����ϼ�����*/
      uint8_t         RealTimeInsepectFinish                :1;    /*ʵʱ���ϼ�����*/
    }Bit;
  }Byte1; 

  uint8_t             PromptToneAddr;                              /*��ʾ����ַ*/
  uint8_t             UserMassageTimeMin;                          /*�û���Ħʱ�� ��*/
  uint8_t             UserMassageTimeSec;                          /*�û���Ħʱ�� ��*/
  uint8_t             DefualtSetMassageTime;                       /*Ĭ�����õİ�Ħ��ʱʱ��*/
  
}CDP_DataFormat0x20_t;



/*
************************************************************************************************************************
* ���Ͷ��� :  0x40 ��о�ַ�����(���İ�<-->��о�壩                                                                  
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID;
  
  uint8_t             XPosition;                                   /*xλ��*/
  uint8_t             YPosition;                                   /*yλ��*/
  uint8_t             ZPosition;                                   /*zλ��*/
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         XYZActionSpeed                        :3;    /*xyz�ַ��ٶ�*/
      uint8_t         TCSActionSpeed                        :3;    /*TCS�ַ��ٶ�*/
      uint8_t         ResetXYZActionStep                    :1;    /*XYZ�ַ����踴λ*/
    }Bit;
  }Byte3; 

  uint8_t             XYZAction;                                   /*XYZ�ַ�*/
  uint8_t             TCSAction;                                   /*TCS�ַ�*/
  uint8_t             XYZActionCompleteCount;                      /*XYZ��������ɴ��������������˸ö�������*/  

  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         ActionExeMode                         :2;    /*��о�����ַ�ִ��ģʽ�� ��CORE_ACTION_EXE_NONE   �ֶ�CORE_ACTION_EXE_MANNNUAL   �Զ�CORE_ACTION_EXE_AUTO*/ 
      uint8_t         RollRange                             :2;    /*����(����)��Χ����CORE_ROLL_RANGE_NONE  ȫ��CORE_ROLL_RANGE_WHOLE  ����CORE_ROLL_RANGE_SPOT  ����CORE_ROLL_RANGE_PART*/
      uint8_t         MoveAdjustRoll                        :2;    /*����,���ڻ�о����λ�á��޶���CORE_MOVE_ADJUST_NONE  ��о����CORE_MOVE_ADJUST_ROLL_UP  ��о����CORE_MOVE_ADJUST_ROLL_DOWN*/
      uint8_t         RollMoveState                         :2;    /*��о�����˶�״̬��û���˶�CORE_ROLL_MOVE_NONE    �����˶�CORE_ROLL_MOVE_UP    �����˶�CORE_ROLL_MOVE_DOWN*/
    }Bit;
  }Byte7;  

  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         CorePause                             :1;    /*��о������ͣ ����*/
      uint8_t         CoreZMBackProtectDisableSw            :1;    /*��о�˵����� ʧЧ����*/
      uint8_t                                               :1;    
      uint8_t         CoreBackScanPause                     :1;    /*��о��������ͣ ����*/
      uint8_t         BackScanRun                           :1;    /*��о���������п���*/
      uint8_t         BackScanFinish                        :1;    /*��о��������ɱ�ʶ*/
      uint8_t         BackScanReCheck                       :1;    /*���½��м���ʶ*/
      uint8_t         BackScanNoHumanOnSeat                 :1;    /*��������*/
    }Bit;
  }Byte8; 
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         ShoulderAdjustEn                      :1;    /*�粿λ�õ���ʹ��*/
      uint8_t         ShoulderAdjustOp                      :2;    /*�粿λ�õ��ڲ���*/
      uint8_t         ShoulderLimitState                    :2;    /*�粿λ����������״̬*/
      uint8_t         ShoulderAdjustKeyLS                   :1;    /*�粿λ�õ��ڰ��������̰���ʽ*/
      uint8_t         CurveReceived                         :1;    /*���������ѽ��ձ�ʶ*/
      uint8_t         CurveCheckSw                          :1;    /*�������߼�⿪��*/
    }Bit;
  }Byte9; 

  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         YMTOPLimtCode                         :4;    /*Y���ϼ���λ�ñ���*/
      uint8_t         YMBOTLimtCode                         :4;    /*Y���¼���λ�ñ���*/
    }Bit;
  }Byte10; 
  
  uint8_t             YMPositionMax;                               /*Y��ʵ������λ�����ֵ*/

  __packed union 
  {
    uint16_t All;
    __packed struct
    {
      uint16_t        YMPositionResetAt                     :2;    /*��оYλ�ø�λ���ƣ��ϸ�λCORE_YPOSITION_RESET_TOP  �¸�λCORE_YPOSITION_RESET_BOT*/  
      uint16_t        CountNocalibrationSw                  :1;    /*Y�Ἣ��λ�ò�У����������*/
      uint16_t        YMCountSum                            :13;   /*Y�����г̼���ֵ*/
    }Bit;
  }Byte1213; 
  
  uint8_t             YPositionMax;                                /*Y���߼�λ�����ֵ*/

  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         XMotorPause                           :1;    /*X�����ͣ ����*/
      uint8_t         XMotorWork                            :1;    /*X��﹤�� ״̬*/
      uint8_t         XPositionResetOK                      :1;    /*Xλ�ø�λ ���״̬*/
      uint8_t                                               :1;   
      uint8_t         XPositionSensorFault                  :1;    /*λ�ô���������*/
      uint8_t         XPositionCodeFault                    :1;    /*λ�ñ�����ϣ����ֲ�Ӧ�ô��ڵı���*/
      uint8_t         XRPMSensorFault                       :1;    /*ת��(�����)����������*/
      uint8_t         XOverCurrentFault                     :1;    /*����������*/
    }Bit;
  }Byte15;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         YMotorPause                           :1;    /*Y�����ͣ ����*/
      uint8_t         YMotorWork                            :1;    /*Y��﹤�� ״̬*/
      uint8_t         YPositionResetOK                      :1;    /*Yλ�ø�λ ���״̬*/
      uint8_t                                               :1;   
      uint8_t         YPositionSensorFault                  :1;    /*λ�ô���������*/
      uint8_t         YPositionCodeFault                    :1;    /*λ�ñ�����ϣ����ֲ�Ӧ�ô��ڵı���*/
      uint8_t         YRPMSensorFault                       :1;    /*ת��(�����)����������*/
      uint8_t         YOverCurrentFault                     :1;    /*����������*/
    }Bit;
  }Byte16; 

  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         ZMotorPause                           :1;    /*Z�����ͣ ����*/
      uint8_t         ZMotorWork                            :1;    /*Z��﹤�� ״̬*/
      uint8_t         ZPositionResetOK                      :1;    /*Zλ�ø�λ ���״̬*/
      uint8_t                                               :1;   
      uint8_t         ZPositionSensorFault                  :1;    /*λ�ô���������*/
      uint8_t         ZPositionCodeFault                    :1;    /*λ�ñ�����ϣ����ֲ�Ӧ�ô��ڵı���*/
      uint8_t         ZRPMSensorFault                       :1;    /*ת��(�����)����������*/
      uint8_t         ZOverCurrentFault                     :1;    /*����������*/
    }Bit;
  }Byte17; 

  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         TCSMotorPause                         :1;    /*TCS�����ͣ ����*/
      uint8_t         TCSMotorWork                          :1;    /*TCS��﹤�� ״̬*/
      uint8_t                                               :1;   
      uint8_t                                               :1;   
      uint8_t                                               :1;   
      uint8_t                                               :1;   
      uint8_t         TCSRPMSensorFault                     :1;    /*ת��(�����)����������*/
      uint8_t         TCSOverCurrentFault                   :1;    /*����������*/
    }Bit;
  }Byte18; 
 
}CDP_DataFormat0x40_t;



/*
************************************************************************************************************************
* ���Ͷ��� :  0x41 ��Ħͷ���ȿ���(���İ�<-->��о�壩
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         MassageHeadHeatWork                   :1;    /*ͷ������ ��������*/
      uint8_t         MassageHeadHeatPause                  :1;    /*��ͣ����*/
      uint8_t         MassageHeadHeatRun                    :1;    /*��������״̬*/
    }Bit;
  }Byte0; 

  int8_t              MassageHeadTemp1;                            /*��Ħͷ�¶�1*/
  int8_t              MassageHeadTemp2;                            /*��Ħͷ�¶�2*/
 
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         MassageHeadThyristorShortFault        :1;    /*�ɿع��· ����*/
      uint8_t         MassageHeadThermistorShortFault       :1;    /*���������· ����*/
      uint8_t         MassageHeadThermistorOpenFault        :1;    /*�������迪· ����*/
    }Bit;
  }Byte3;  
  
}CDP_DataFormat0x41_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  0x48 �Ƚų�������(���İ�<-->�Ƚſ��ư壩
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         GasCalvesBot                          :1;    /*�ȵ�*/
      uint8_t         GasCalvesSide                         :1;    /*�Ȳ�*/
      uint8_t         GasCalvesSideHold                     :1;    /*�Ȳౣѹ*/
    }Bit;
  }Byte0; 
  
  uint8_t             CalvesPressureThreshold;                     /*��ѹ��ͣ����*/
  
}CDP_DataFormat0x48_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  0x49 �ȽŹ��ֿ���(���İ�<-->�Ƚſ��ư壩
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         FeetRollerSw                          :1;    /*�Ź� ����*/
      uint8_t         FeetRollerDirection                   :1;    /*�Ź� ��������*/
      uint8_t         FeetRollerInitPositionIO              :1;    /*�Ź���ʼλ��IO���*/
    }Bit;
  }Byte0; 
  
  uint8_t FeetRollerPWM;
  uint8_t FeetRollerCount;
  
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         CalvesRollerSw                        :1;    /**/
      uint8_t         CalvesRollerDirection                 :1;    /**/
    }Bit;
  }Byte2; 
  
}CDP_DataFormat0x49_t;


/*
************************************************************************************************************************
* ���Ͷ��� :  0x4A �Ƚ��񶯿���(���İ�<-->�Ƚſ��ư壩
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         FeetVibSw                          :1;    /**/
      uint8_t         FeetVibDirection                   :1;    /**/
    }Bit;
  }Byte0; 
  
}CDP_DataFormat0x4A_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  0x4B �Ȳ���������(���İ�<-->�Ƚſ��ư壩
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         LegFlexAction                         :2;    /*С����������*/
      uint8_t         LegReachExtendLimt                    :1;    /*�Ѵ���޶�*/
      uint8_t         LegReachShortenLimt                   :1;    /*�Ѵ�����޶�*/
      uint8_t         LegTouchGround                        :1;    /*����*/
      uint8_t         LegTouchFeet                          :1;    /*����*/
    }Bit;
  }Byte0; 
  uint8_t             LegPositionCount;                            /*С����������ֵ*/

}CDP_DataFormat0x4B_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  0x50 ��������(��������-->���İ�)                                                           
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID;
  
  uint8_t             KeyVal;                                      /*��ֵ*/
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         Led1                                  :1;    /**/
      uint8_t         Led2                                  :1;    /**/
      uint8_t         Led3                                  :1;    /**/
      uint8_t         Led4                                  :1;    /**/
      uint8_t         Led5                                  :1;    /**/
      uint8_t         Led6                                  :1;    /**/
      uint8_t         Led7                                  :1;    /**/
      uint8_t         Led8                                  :1;    /**/
    }Bit;
  }Byte1; 
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         Led9                                  :1;    /**/
      uint8_t         Led10                                 :1;    /**/
      uint8_t                                               :5;    /**/
      uint8_t         KeyStuck                              :1;    /*����������־*/
    }Bit;
  }Byte2;

}CDP_DataFormat0x50_t;


/*������������������������������������������������������������������������������������������������������������������������������*/
/*������������������������������������������������������������������������������������������������������������������������������*/

/*
************************************************************************************************************************
* ���Ͷ��� :  ͨ�����ݰ� ���ݶ����ʽ                                                                       
************************************************************************************************************************
*/
typedef struct 
{
  uint8_t     Len;     
  uint8_t     ID;  
  uint8_t     *pData;  

}CDPDataObjFormat_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  ͨ�����ݰ� ���ݶ���������                                                                        
************************************************************************************************************************
*/
typedef struct
{
  uint8_t    ID;                   /*���ݵ�IDʶ����*/
  uint8_t    AdditonOp;            /*���Ӳ���*/
  uint8_t    (*pDataHandle)(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);    /*���ݴ�����*/

}CDPDataObjManageTabItem_t;

typedef	struct
{
  uint16_t   ID;                   /*���ݵ�IDʶ����*/
  uint8_t    AdditonOp;            /*���Ӳ���*/
  uint8_t    (*pDataHandle)(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);    /*���ݴ�����*/

}CDPDataObjManageTabItem_Server_t;

/*
************************************************************************************************************************
* ���Ͷ��� :  ͨ�����ݰ�������״̬��ʶ                                                                                    
************************************************************************************************************************
*/
typedef  union 
{
  struct
  {
    uint8_t        RepeaterWork                      :1;   /*ת��������*/ 
    uint8_t        CenXxx_SideCtrlKeyStuck           :1;   /*������������*/ 

  }Bit;

  uint8_t All;
}CDPCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/

/*
************************************************************************************************************************
* ���Ͷ��� :  ͨ�����ݰ� ��ز������ݽṹ                                                                            
************************************************************************************************************************
*/
typedef  uint8_t  (*pDataObjRecHandleCB_t)(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t Cmd);  /*���ݴ���ص�����*/


/*
************************************************************************************************************************
* ���Ͷ��� :  ͨ�����ݰ� ��ز������ݽṹ                                                                            
************************************************************************************************************************
*/
typedef struct
{
  CDPCSFlag_t           CSFlag;

  /*ͨ�����ݰ����� ��ҪΪ�����ã�ʵ�ʱ���Ӧ����ʹ�ø������Ľӿں���-------*/
  CDP_CenXxx_t          *pCenXxx;
  CDP_CenServer_t       *pCenServer;
  CDP_CenApp_t          *pCenApp;
  
  CDP_DataFormat0x50_t  SetQry0x50;
  
  uint16_t              RepeaterLTL;           /*ת������Ծʱ��  LTL(Lively time length)*/
}CDP_t;


/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/
uint8_t CDP_PDURxHandle(ESF_Evt_t *pEvt);
uint8_t CDP_PDUTxHandle(ESF_Evt_t *pEvt);
void CDP_PDUPackTx(uint8_t DesAddr, uint8_t Cmd, uint8_t *DUBuf[], uint8_t DUBufISum);
uint8_t CDP_FrameRxHandle(CDP_FrameRx_t *pFrameRx, uint8_t RxByte, uint8_t CDPType, uint8_t CDPDAP);
uint8_t CDP_FrameTxHandle(ESF_Evt_t *pEvt, uint8_t *pTxFrameBuf, BSP_UART_PortNum_t PortNum);
void CDP_Handle(void);
CDP_t* CDP_Init(void);
CDPCSFlag_t CDP_GetCSFlag(void);


#endif
