/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: Core.h                                                                                                         
**
**    ��������: ��о���������� X Y Z TAP �ĸ���
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
#ifndef  _CORE_H
#define  _CORE_H


/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "CoreXaxisMotor.h"
#include "CoreYaxisMotor.h"
#include "CoreZaxisMotor.h"
#include "CoreTCSMotor.h"
#include "CoreBackScan.h"
#include "CDP.h"


/*
========================================================================================================================
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/
/*���²�ģ�鳣�õĺ궨�壬�Ը��õ�������ʽչ�ָ�ͬ����ϲ�ģ��===========================*/
#define  X_SPEED_MIN                                XMOTOR_SPEEDLEVEL_MIN
#define  X_SPEED_MAX                                XMOTOR_SPEEDLEVEL_MAX
#define  Y_SPEED_MIN                                YMOTOR_SPEEDLEVEL_MIN
#define  Y_SPEED_MAX                                YMOTOR_SPEEDLEVEL_MAX
#define  Z_SPEED_MIN                                ZMOTOR_SPEEDLEVEL_MIN
#define  Z_SPEED_MAX                                ZMOTOR_SPEEDLEVEL_MAX

#define  XYZ_ACTION_SPEED_MIN                       1
#define  XYZ_ACTION_SPEED_MAX                       5

#define  TCS_SPEED_MIN                              TCSMOTOR_SPEEDLEVEL_MIN
#define  TCS_SPEED_MAX                              TCSMOTOR_SPEEDLEVEL_MAX

/*---------------------------------------------------------------------------------------------*/
#define  X_DEFAULT_SPPED                            XMOTOR_SPEEDLEVEL_DEFAULT
#define  X_DEFAULT_FB                               XMOTOR_FB_DEFAULT
#define  Y_DEFAULT_SPPED                            YMOTOR_SPEEDLEVEL_DEFAULT
#define  Y_DEFAULT_FB                               YMOTOR_FB_DEFAULT
#define  Z_DEFAULT_SPPED                            ZMOTOR_SPEEDLEVEL_DEFAULT
#define  Z_DEFAULT_FB                               ZMOTOR_FB_DEFAULT

#define  XYZ_ACTION_DEFAULT_SPPED                   3

#define  TCS_DEFAULT_SPPED                          TCSMOTOR_SPEEDLEVEL_DEFAULT
#define  TCS_DEFAULT_FB                             TCSMOTOR_FB_DEFAULT

/*---------------------------------------------------------------------------------------------*/
#define  CORE_YPOSITION_RESET_TOP                   YMOTOR_POSITION_RESET_AT_TOP   /*��оλ�ø�λ��ʽ: �ϸ�λ*/
#define  CORE_YPOSITION_RESET_BOT                   YMOTOR_POSITION_RESET_AT_BOT   /*��оλ�ø�λ��ʽ: �¸�λ*/


/*��о���߷�Χ�����㡢����================================================================*/
#define  CORE_ROLL_RANGE_NONE                       0        /*����(����)ģʽ: ��*/
#define  CORE_ROLL_RANGE_WHOLE                      1        /*����(����)ģʽ��ȫ��*/
#define  CORE_ROLL_RANGE_SPOT                       2        /*����(����)ģʽ������*/
#define  CORE_ROLL_RANGE_PART                       3        /*����(����)ģʽ������*/

#define  CORE_PART_ROLL_RANGE                       4        /*�������߰뾶��Χ*/

#define  CORE_ROLL_DIRECTION_UP                     0        /*����(����)���� ��*/
#define  CORE_ROLL_DIRECTION_DOWN                   1        /*����(����)���� ��*/

#define  CORE_ROLL_MOVE_NONE                        0        /*û���˶�*/ 
#define  CORE_ROLL_MOVE_UP                          1        /*���������˶�*/
#define  CORE_ROLL_MOVE_DOWN                        2        /*���������˶�*/


/*��о ��������� ���� �˶� ==============================================================*/
#define  CORE_MOVE_ADJUST_NONE                      0
#define  CORE_MOVE_ADJUST_ROLL_UP                   1
#define  CORE_MOVE_ADJUST_ROLL_DOWN                 2
#define  CORE_MOVE_ADJUST_FLEX_FORWARD              1
#define  CORE_MOVE_ADJUST_FLEX_BACKWARD             2


/*��о X Y Z �ռ�λ�� ��غ궨��==========================================================*/
/* PX��PY��PZ    ����о���ϲ��ṩ�ĵ��ò�������������߼�λ�á�
 * PXM��PYM��PZM ������ʵ������(ӳ��)λ�ã���ʵ�ʵ����̵�λ�ü��ṹ������
 *
 * һ��X���Z�ᶼ��һһ��Ӧ������ӳ��ת����Y�������������߲�ͬ����Ҫ�����߼�������ֵ��ӳ�䡣
 * ����Y�Ὺ�׺��������̿�ʶ��88��λ��(PYM00~PYM87)������Ӧ�ϲ������˵ֻ���г̷�31��(PY00~PY30)��
 * �ϲ����ֻ֪��PY00~PY30������������ν�PY00~PY30ӳ�䵽PYM00~PYM87�����ɻ�о�ڲ��㷨ʵ��λ�õ�ӳ�䡣 */
#define  PXM_MIN                                    XMOTOR_POSITION_MIN
#define  PXM_MAX                                    XMOTOR_POSITION_MAX
#define  PZM_MIN                                    ZMOTOR_POSITION_MIN
#define  PZM_MAX                                    ZMOTOR_POSITION_MAX
#define  PYM_MIN                                    YMOTOR_POSITION_MIN  
#define  PYM_MAX                                    YMOTOR_POSITION_MAX 

#define  PX_MIN                                     PXM_MIN
#define  PX_MAX                                     PXM_MAX
#define  PZ_MIN                                     PZM_MIN
#define  PZ_MAX                                     PZM_MAX
#define  PY_MIN                                     PY00
#define  PY_LUMBAR                                  PY24        /*����λ��(����λ�� ����Ѩ����)����������Ѩ����������λ��(PY_LUMBAR)��24��(PY00 ~ PY24)*/
#define  PY_MAX                                     PY32          

#define  PXM00                                      0
#define  PXM01                                      1
#define  PXM02                                      2
#define  PXM03                                      3
#define  PXM04                                      4
#define  PXMNARROW                                  PXM_MIN
#define  PXMWIDE                                    PXM_MAX

#define  PX00                                       0
#define  PX01                                       1
#define  PX02                                       2
#define  PX03                                       3
#define  PX04                                       4
#define  PXNARROW                                   PX_MIN
#define  PXWIDE                                     PX_MAX

#define  PYM00                                      0
#define  PYM01                                      1
#define  PYM02                                      2
#define  PYM03                                      3
#define  PYM04                                      4
#define  PYM05                                      5
#define  PYM06                                      6
#define  PYM07                                      7
#define  PYM08                                      8
#define  PYM09                                      9
#define  PYM10                                      10
#define  PYM11                                      11
#define  PYM12                                      12
#define  PYM13                                      13
#define  PYM14                                      14
#define  PYM15                                      15
#define  PYM16                                      16
#define  PYM17                                      17
#define  PYM18                                      18
#define  PYM19                                      19
#define  PYM20                                      20
#define  PYM21                                      21
#define  PYM22                                      22
#define  PYM23                                      23
#define  PYM24                                      24
#define  PYM25                                      25
#define  PYM26                                      26
#define  PYM27                                      27
#define  PYM28                                      28
#define  PYM29                                      29
#define  PYM30                                      30
#define  PYM31                                      31
#define  PYM32                                      32
#define  PYM33                                      33
#define  PYM34                                      34
#define  PYM35                                      35
#define  PYM36                                      36
#define  PYM37                                      37
#define  PYM38                                      38
#define  PYM39                                      39
#define  PYM40                                      40
#define  PYM41                                      41
#define  PYM42                                      42
#define  PYM43                                      43
#define  PYM44                                      44
#define  PYM45                                      45
#define  PYM46                                      46
#define  PYM47                                      47
#define  PYM48                                      48
#define  PYM49                                      49
#define  PYM50                                      50
#define  PYM51                                      51
#define  PYM52                                      52
#define  PYM53                                      53
#define  PYM54                                      54
#define  PYM55                                      55
#define  PYM56                                      56
#define  PYM57                                      75
#define  PYM58                                      58
#define  PYM59                                      59
#define  PYM60                                      60
#define  PYM61                                      61
#define  PYM62                                      62
#define  PYM63                                      63
#define  PYM64                                      64
#define  PYM65                                      65
#define  PYM66                                      66
#define  PYM67                                      67
#define  PYM68                                      86
#define  PYM69                                      69
#define  PYM70                                      70
#define  PYM71                                      71
#define  PYM72                                      72
#define  PYM73                                      73
#define  PYM74                                      74
#define  PYM75                                      75
#define  PYM76                                      76
#define  PYM77                                      77
#define  PYM78                                      78
#define  PYM79                                      79
#define  PYM80                                      80
#define  PYM81                                      81
#define  PYM82                                      82
#define  PYM83                                      83
#define  PYM84                                      84
#define  PYM85                                      85
#define  PYM86                                      86
#define  PYM87                                      87
#define  PYM88                                      88
#define  PYM89                                      89
#define  PYM90                                      90
#define  PYM91                                      91
#define  PYM92                                      92
#define  PYM93                                      93
#define  PYM94                                      94
#define  PYM95                                      95
#define  PYM96                                      96
#define  PYM97                                      97
#define  PYM98                                      98
#define  PYM99                                      99
#define  PYMTOP                                     PYM_MIN
#define  PYMBOT                                     PYM_MAX

#define  PY00                                       0
#define  PY01                                       1
#define  PY02                                       2
#define  PY03                                       3
#define  PY04                                       4
#define  PY05                                       5
#define  PY06                                       6
#define  PY07                                       7
#define  PY08                                       8
#define  PY09                                       9
#define  PY10                                       10
#define  PY11                                       11
#define  PY12                                       12
#define  PY13                                       13
#define  PY14                                       14
#define  PY15                                       15
#define  PY16                                       16
#define  PY17                                       17
#define  PY18                                       18
#define  PY19                                       19
#define  PY20                                       20
#define  PY21                                       21
#define  PY22                                       22
#define  PY23                                       23
#define  PY24                                       24
#define  PY25                                       25
#define  PY26                                       26
#define  PY27                                       27
#define  PY28                                       28
#define  PY29                                       29
#define  PY30                                       30
#define  PY31                                       31
#define  PY32                                       32
#define  PY33                                       33
#define  PY34                                       34
#define  PY35                                       35
#define  PY36                                       36
#define  PY37                                       37
#define  PY38                                       38
#define  PY39                                       39
#define  PY40                                       40
#define  PY41                                       41
#define  PY42                                       42
#define  PY43                                       43
#define  PY44                                       44
#define  PY45                                       45
#define  PY46                                       46
#define  PYTOP                                      PY_MIN
#define  PYBOT                                      PY_MAX

#define  PZM00                                      0
#define  PZM01                                      1
#define  PZM02                                      2
#define  PZM03                                      3
#define  PZM04                                      4
#define  PZM05                                      5
#define  PZM06                                      6
#define  PZM07                                      7
#define  PZM08                                      8
#define  PZM09                                      9
#define  PZMBACK                                    PZM_MIN
#define  PZMFRONT                                   PZM_MAX

#define  PZ00                                       0
#define  PZ01                                       1
#define  PZ02                                       2
#define  PZ03                                       3
#define  PZ04                                       4
#define  PZ05                                       5
#define  PZ06                                       6
#define  PZ07                                       7
#define  PZ08                                       8
#define  PZ09                                       9
#define  PZBACK                                     PZ_MIN
#define  PZFRONT                                    PZ_MAX


/*��о��Ħ�ַ���غ궨��===================================================================
 * ��������ռ��4λ              �����15������
 * ĳ���������µľ����ַ�ռ��4λ��ÿ�����͸������15���ַ�
 *
 *      ע�⣺�������粿���������������β������͵��ַ� ��һ��ֻ�����ڹ̶��Ĳ�λ��                               
 *           ���� �������� �����������κβ�λ����������ò�λ�ɳ��������Ҫ���п��ơ�                    
 *           ��һ���ڸò�λִ�и��ַ��İ�ĦЧ����ȽϺá��������ض���λ���ַ����Ƚ�������ԡ�            
 *
 *  �ַ�ע�⣺ KNEAD -- ����             KNEADSTROKE -- �ว   KNEADPRESS -- �ఴ 
 *             ROLL  -- ����/����/����   SHIA        -- ָѹ   STRETCH    -- ��չ
*/
#define  CORE_ACTION_EXE_NONE                       0x00        /*��о����ִ��ģʽ���ޣ�����ʹ�÷�ʽ�����������*/
#define  CORE_ACTION_EXE_MANNNUAL                   0x01        /*��о����ִ��ģʽ�����ϲ��ֶ�����ʹ��*/
#define  CORE_ACTION_EXE_AUTO                       0x02        /*��о����ִ��ģʽ�����ϲ��Զ�����ʹ��*/

#define  CORE_ACTION_TYPE_NONE                      0x00        /*��о�������ͣ���*/
#define  CORE_ACTION_TYPE_COMMON1                   0x01        /*��о�������ͣ�ͨ�õ��ַ�������������ض���λ���ַ�*/
#define  CORE_ACTION_TYPE_COMMON2                   0x02        /*��о�������ͣ�ͨ�õ��ַ�������������ض���λ���ַ�*/
#define  CORE_ACTION_TYPE_COMMON3                   0x03        /*��о�������ͣ�ͨ�õ��ַ�������������ض���λ���ַ�*/
#define  CORE_ACTION_TYPE_NEKC                      0x0A        /*��о�������ͣ�����*/
#define  CORE_ACTION_TYPE_SHOULDER                  0x0B        /*��о�������ͣ��粿*/
#define  CORE_ACTION_TYPE_BACK                      0x0C        /*��о�������ͣ�����*/
#define  CORE_ACTION_TYPE_LUMBAR                    0x0D        /*��о�������ͣ�����*/
#define  CORE_ACTION_TYPE_BUTTOCK                   0x0E        /*��о�������ͣ��β�*/
#define  CORE_ACTION_TYPE_BODY                      0x0F        /*��о�������ͣ�ȫ��*/

#define  CORE_ACTION_NONE                           ((CORE_ACTION_TYPE_NONE<<4) + 0x00)        /*�޶���*/  
#define  XYZ_ACTION_NONE                            ((CORE_ACTION_TYPE_NONE<<4) + 0x00)        /*�޶���*/  
#define  TCS_ACTION_NONE                            ((CORE_ACTION_TYPE_NONE<<4) + 0x00)        /*�޶���*/
#define  XYZ_NONE                                   ((CORE_ACTION_TYPE_NONE<<4) + 0x00)        /*�޶���*/  
#define  TCS_NONE                                   ((CORE_ACTION_TYPE_NONE<<4) + 0x00)        /*�޶���*/

#define  KNIN                                       ((CORE_ACTION_TYPE_COMMON1<<4) + 0x01)     /*��������*/        
#define  KNOUT                                      ((CORE_ACTION_TYPE_COMMON1<<4) + 0x02)     /*��������*/  
#define  KNIN_VARY                                  ((CORE_ACTION_TYPE_COMMON1<<4) + 0x03)     /*���ڱ�������*/        
#define  KNOUT_VARY                                 ((CORE_ACTION_TYPE_COMMON1<<4) + 0x04)     /*�����������*/        
#define  KNIN_PUSH                                  ((CORE_ACTION_TYPE_COMMON1<<4) + 0x05)     /*��������*/        
#define  KNOUT_PUSH                                 ((CORE_ACTION_TYPE_COMMON1<<4) + 0x06)     /*��������*/        
#define  KNIN_LOOP                                  ((CORE_ACTION_TYPE_COMMON1<<4) + 0x07)     /*���ڻ���*/        
#define  KNOUT_LOOP                                 ((CORE_ACTION_TYPE_COMMON1<<4) + 0x08)     /*���⻷��*/        
#define  KN_3_6                                     ((CORE_ACTION_TYPE_COMMON1<<4) + 0x09)     /*���� ʱ�ӵ�·������*/        
#define  KN_3_6_9                                   ((CORE_ACTION_TYPE_COMMON1<<4) + 0x0A)     /*���� ʱ�ӵ�·������*/        
#define  KN_6_9                                     ((CORE_ACTION_TYPE_COMMON1<<4) + 0x0B)     /*���� ʱ�ӵ�·������*/        
#define  KN_12_9                                    ((CORE_ACTION_TYPE_COMMON1<<4) + 0x0C)     /*���� ʱ�ӵ�·������*/  
#define  KN_12_9_6                                  ((CORE_ACTION_TYPE_COMMON1<<4) + 0x0D)     /*���� ʱ�ӵ�·������*/ 
#define  KN_3_12_9                                  ((CORE_ACTION_TYPE_COMMON1<<4) + 0x0E)     /*���� ʱ�ӵ�·������*/        

#define  ROLL                                       ((CORE_ACTION_TYPE_COMMON2<<4) + 0x01)     /*����(����)*/      
#define  ROLL_KNIN                                  ((CORE_ACTION_TYPE_COMMON2<<4) + 0x02)     /*����(����)+��������*/
#define  ROLL_KNOUT                                 ((CORE_ACTION_TYPE_COMMON2<<4) + 0x03)     /*����(����)+��������*/
#define  ROLLUP_PUSH                                ((CORE_ACTION_TYPE_COMMON2<<4) + 0x04)     /*ǰ��������*/
#define  ROLLDOWN_PUSH                              ((CORE_ACTION_TYPE_COMMON2<<4) + 0x05)     /*ǰ��������*/
#define  Z3D_SHIA1                                  ((CORE_ACTION_TYPE_COMMON2<<4) + 0x06)     /*Z����3D ָѹ1*/        
#define  Z3D_SHIA2                                  ((CORE_ACTION_TYPE_COMMON2<<4) + 0x07)     /*Z����3D ָѹ2*/        
#define  SWEDISH1                                   ((CORE_ACTION_TYPE_COMMON2<<4) + 0x08)     /*���1*/        
#define  SWEDISH2                                   ((CORE_ACTION_TYPE_COMMON2<<4) + 0x09)     /*���2*/        

#define  NECK_ROLL1                                 ((CORE_ACTION_TYPE_NEKC<<4) + 0x01)        /*��������1*/
#define  NECK_KNEAD1                                ((CORE_ACTION_TYPE_NEKC<<4) + 0x02)        /*��������1*/
#define  NECK_KNEADSTROKE1                          ((CORE_ACTION_TYPE_NEKC<<4) + 0x03)        /*�����ว1*/
#define  NECK_KNEADPRESS1                           ((CORE_ACTION_TYPE_NEKC<<4) + 0x04)        /*�����ఴ1*/
#define  NECK_SHIA1                                 ((CORE_ACTION_TYPE_NEKC<<4) + 0x05)        /*����ָѹ1*/

#define  SHOULDER_ROLL1                             ((CORE_ACTION_TYPE_SHOULDER<<4) + 0x01)    /*�粿����(����)1*/
#define  SHOULDER_KNEAD1                            ((CORE_ACTION_TYPE_SHOULDER<<4) + 0x02)    /*�粿����1*/
#define  SHOULDER_KNEADSTROKE1                      ((CORE_ACTION_TYPE_SHOULDER<<4) + 0x03)    /*�粿�ว1*/
#define  SHOULDER_KNEADPRESS1                       ((CORE_ACTION_TYPE_SHOULDER<<4) + 0x04)    /*�粿�ఴ1*/
#define  SHOULDER_SHIA1                             ((CORE_ACTION_TYPE_SHOULDER<<4) + 0x05)    /*�粿ָѹ1*/

#define  BACK_ROLLUP                                ((CORE_ACTION_TYPE_BACK<<4) + 0x01)        /*��������(����)��*/
#define  BACK_ROLLDOWN                              ((CORE_ACTION_TYPE_BACK<<4) + 0x02)        /*��������(����)��*/
#define  BACK_KNEAD1                                ((CORE_ACTION_TYPE_BACK<<4) + 0x03)        /*��������1*/
#define  BACK_KNEAD2                                ((CORE_ACTION_TYPE_BACK<<4) + 0x04)        /*��������2*/
#define  BACK_KNEADSTROKE1                          ((CORE_ACTION_TYPE_BACK<<4) + 0x05)        /*�����ว1*/
#define  BACK_KNEADPRESS1                           ((CORE_ACTION_TYPE_BACK<<4) + 0x06)        /*�����ఴ1*/ 
#define  BACK_KNEADPRESS2                           ((CORE_ACTION_TYPE_BACK<<4) + 0x07)        /*�����ఴ2*/ 
#define  BACK_SHIA1                                 ((CORE_ACTION_TYPE_BACK<<4) + 0x08)        /*����ָѹ1*/  

#define  LUMBAR_ROLLUP                              ((CORE_ACTION_TYPE_LUMBAR<<4) + 0x01)      /*��������(����)��*/   
#define  LUMBAR_ROLLDOWN                            ((CORE_ACTION_TYPE_LUMBAR<<4) + 0x02)      /*��������(����)��*/   
#define  LUMBAR_KNEAD1                              ((CORE_ACTION_TYPE_LUMBAR<<4) + 0x03)      /*��������1*/
#define  LUMBAR_KNEAD2                              ((CORE_ACTION_TYPE_LUMBAR<<4) + 0x04)      /*��������2*/  
#define  LUMBAR_KNEADSTROKE1                        ((CORE_ACTION_TYPE_LUMBAR<<4) + 0x05)      /*�����ว1*/
#define  LUMBAR_KNEADPRESS1                         ((CORE_ACTION_TYPE_LUMBAR<<4) + 0x06)      /*�����ఴ1*/
#define  LUMBAR_KNEADPRESS2                         ((CORE_ACTION_TYPE_LUMBAR<<4) + 0x07)      /*�����ఴ2*/
#define  LUMBAR_SHIA1                               ((CORE_ACTION_TYPE_LUMBAR<<4) + 0x08)      /*����ָѹ1*/

#define  BUTTOCK_ROLL1                              ((CORE_ACTION_TYPE_BUTTOCK<<4) + 0x01)     /*�β�����(����)1*/
#define  BUTTOCK_KNEAD1                             ((CORE_ACTION_TYPE_BUTTOCK<<4) + 0x02)     /*�β�����1*/
#define  BUTTOCK_KNEADSTROKE1                       ((CORE_ACTION_TYPE_BUTTOCK<<4) + 0x03)     /*�β��ว1*/  
#define  BUTTOCK_KNEADPRESS1                        ((CORE_ACTION_TYPE_BUTTOCK<<4) + 0x04)     /*�β��ఴ1*/ 
#define  BUTTOCK_SHIA1                              ((CORE_ACTION_TYPE_BUTTOCK<<4) + 0x05)     /*�β�ָѹ1*/                   

#define  BODY_ROLL1                                 ((CORE_ACTION_TYPE_BODY<<4) + 0x01)        /*ȫ������(����)1*/
#define  BODY_KNEAD1                                ((CORE_ACTION_TYPE_BODY<<4) + 0x02)        /*ȫ������1*/
#define  BODY_KNEADSTROKE1                          ((CORE_ACTION_TYPE_BODY<<4) + 0x03)        /*ȫ���ว1*/
#define  BODY_KNEADPRESS1                           ((CORE_ACTION_TYPE_BODY<<4) + 0x04)        /*ȫ���ఴ1*/
#define  BODY_SHIA1                                 ((CORE_ACTION_TYPE_BODY<<4) + 0x05)        /*ȫ��ָѹ1*/                    

//-------------------------------------------------------------
#define  CLAP1                                      ((CORE_ACTION_TYPE_COMMON1<<4) + TCSMOTOR_ACTION_CLAP1)         /*�Ĵ�1*/ 
#define  CLAP2                                      ((CORE_ACTION_TYPE_COMMON1<<4) + TCSMOTOR_ACTION_CLAP2)         /*�Ĵ�2*/ 
#define  SHIA1                                      ((CORE_ACTION_TYPE_COMMON1<<4) + TCSMOTOR_ACTION_SHIA1)         /*ָѹ1*/ 
#define  SHIA2                                      ((CORE_ACTION_TYPE_COMMON1<<4) + TCSMOTOR_ACTION_SHIA2)         /*ָѹ2*/ 
#define  LTAP                                       ((CORE_ACTION_TYPE_COMMON1<<4) + TCSMOTOR_ACTION_LTAP)          /*���û�*/ 
#define  TAP                                        ((CORE_ACTION_TYPE_COMMON1<<4) + TCSMOTOR_ACTION_TAP)           /*�û�*/ 
#define  NO_FB_LTAP                                 ((CORE_ACTION_TYPE_COMMON1<<4) + TCSMOTOR_ACTION_NO_FB_LTAP)    /*���ٶȷ��������û�*/  
#define  NO_FB_TAP                                  ((CORE_ACTION_TYPE_COMMON1<<4) + TCSMOTOR_ACTION_NO_FB_TAP)     /*���ٶȷ������û�*/  

#define  CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS          CORE_ACTION_TYPE_COMMON2        /*��XYZ�ַ�������ר�Ÿ��ӵ�TCS����*/
#define  XYZ_CLAP1                                  ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + TCSMOTOR_ACTION_CLAP1)         /*�Ĵ�1*/ 
#define  XYZ_CLAP2                                  ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + TCSMOTOR_ACTION_CLAP2)         /*�Ĵ�2*/ 
#define  XYZ_SHIA1                                  ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + TCSMOTOR_ACTION_SHIA1)         /*ָѹ1*/ 
#define  XYZ_SHIA2                                  ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + TCSMOTOR_ACTION_SHIA2)         /*ָѹ2*/ 
#define  XYZ_LTAP                                   ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + TCSMOTOR_ACTION_LTAP)          /*���û�*/ 
#define  XYZ_TAP                                    ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + TCSMOTOR_ACTION_TAP)           /*�û�*/ 
#define  XYZ_NO_FB_LTAP                             ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + TCSMOTOR_ACTION_NO_FB_LTAP)    /*���ٶȷ��������û�*/  
#define  XYZ_NO_FB_TAP                              ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + TCSMOTOR_ACTION_NO_FB_TAP)     /*���ٶȷ������û�*/  
#define  XYZ_D_TCS                                  ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + 0x0F)                          /*��XYZ�ַ�ר�Ÿ��ӵ�Ĭ�ϵ�TCS����*/


/*
========================================================================================================================
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� :  ��о��Ħ����                                                                          
************************************************************************************************************************
*/
typedef union
{
  uint16_t All;

  struct
  {
    union
    {
      uint8_t      All;
      struct
      {
        uint8_t    Action       :4;    /*���嶯��*/
        uint8_t    Type         :4;    /*��������*/
      }Bit;   
    }XYZ;   

    union
    {
      uint8_t      All;
      struct
      {
        uint8_t    Action       :4;    /*���嶯��*/
        uint8_t    Type         :4;    /*��������*/
      }Bit;   
    }TCS;   
  }Bit;   
}CoreAction_t; 

/*
************************************************************************************************************************
* ���Ͷ��� :  ��о��Ħ���� ���б�־                                                                          
************************************************************************************************************************
*/
typedef    union
{
  uint8_t      All;
  struct
  {
    uint8_t    KneadInRun                   :1;  /*���������ַ� ������*/ 
    uint8_t    KneadOutRun                  :1;  /*���������ַ� ������*/ 
    uint8_t    RollRun                      :1;  /*����(����)�ַ� ������*/ 
    uint8_t    KneadRun                     :1;  /*�����ַ� ������*/ 
    uint8_t    KneadStrokeRun               :1;  /*�ว�ַ� ������*/ 
    uint8_t    KneadPressRun                :1;  /*�ఴ�ַ� ������*/ 
    uint8_t    ShiaRun                      :1;  /*ָѹ�ַ� ������*/ 
    uint8_t    StretchRun                   :1;  /*��չ�ַ� ������*/ 
  }Bit;   
}CoreXYZActionRunFlag_t;  

typedef    union
{
  uint8_t      All;
  struct
  {
    uint8_t    Clap1Run                     :1;  /*�Ĵ�1�ַ� ������*/ 
    uint8_t    Clap2Run                     :1;  /*�Ĵ�2�ַ� ������*/ 
    uint8_t    Shia1Run                     :1;  /*ָѹ1�ַ� ������*/ 
    uint8_t    Shia2Run                     :1;  /*ָѹ2�ַ� ������*/ 
    uint8_t    LTapRun                      :1;  /*���û��ַ� ������*/ 
    uint8_t    TapRun                       :1;  /*�û��ַ� ������*/ 
  }Bit;   
}CoreTCSActionRunFlag_t;   



typedef union
{
  uint16_t All;
  struct
  {
    CoreXYZActionRunFlag_t  XYZ;
    CoreTCSActionRunFlag_t  TCS;
  }Bit;   
}CoreActionRunFlag_t; 

/*
************************************************************************************************************************
* ���Ͷ��� :  ��о ������״̬��ʶ                                                                          
************************************************************************************************************************
*/
typedef  union 
{
  uint32_t All;
  struct
  {
    uint8_t    Pause                            :5;  /*��ͣ*/
    uint8_t    RollRange                        :2;  /*����(����)��Χ����CORE_ROLL_RANGE_NONE  ȫ��CORE_ROLL_RANGE_WHOLE  ����CORE_ROLL_RANGE_SPOT  ����CORE_ROLL_RANGE_PART*/
    uint8_t    RollDirection                    :1;  /*����(����)������CORE_ROLL_DIRECTION_UP  ��CORE_ROLL_DIRECTION_DOWN*/
    uint8_t    MoveAdjustRoll                   :2;  /*����,���ڻ�о����λ�á��޶���CORE_MOVE_ADJUST_NONE  ��о����CORE_MOVE_ADJUST_ROLL_UP  ��о����CORE_MOVE_ADJUST_ROLL_DOWN*/

    uint8_t    TCSFBEn                          :1;  /*���� �ٶ� ����ʹ��*/ 
    uint8_t    XFBEn                            :1;  /*���� �ٶ� ����ʹ��*/ 
    uint8_t    YFBEn                            :1;  /*����(����) �ٶ� ����ʹ��*/ 
    uint8_t    ZFBEn                            :1;  /*���� �ٶ� ����ʹ��*/ 
    
    uint8_t    ActionExeMode                    :2;  /*����ִ��ģʽ�� ��CORE_ACTION_EXE_NONE   �ֶ�CORE_ACTION_EXE_MANNNUAL   �Զ�CORE_ACTION_EXE_AUTO*/ 
  }Bit;

}CoreCSFlag_t;  /*Control State Flag  ������״̬��ʶ*/

/*
************************************************************************************************************************
* ���Ͷ��� :  ��о ��ز������ݽṹ                                                                           
************************************************************************************************************************
*/
typedef struct
{
  CoreCSFlag_t             CSFlag;                   /*������״̬��ʶ*/
  XMotorCSFlag_t           XMotorCSFlag;             /*��������״̬��ʶ*/
  YMotorCSFlag_t           YMotorCSFlag;             /*��������״̬��ʶ*/
  ZMotorCSFlag_t           ZMotorCSFlag;             /*��������״̬��ʶ*/
  TCSMotorCSFlag_t         TCSMotorCSFlag;           /*��������״̬��ʶ*/
  CoreActionRunFlag_t      ActionRunFlag;            /*�������б�־*/   
  
  uint16_t                 XYZActionIndex;           /*��оXYZ����ִ������*/
  uint16_t                 TCSActionIndex;           /*��оTCS����ִ������*/
  
  CDP_DataFormat0x40_t     Set;                      /*����о�����������*/
  CDP_DataFormat0x40_t     Qry;                      /*�ӻ�о���ѯ����������*/
  
  CoreBackScanCSFlag_t     BackScanCSFlag;           /*����ɨ�������״̬��ʶ*/
}Core_t;  

/*
************************************************************************************************************************
* ���Ͷ��� :  ��оXYZ�����ֶ�������                                                                    
*
* �����ַ�(�絥��������)��������ִ�ж��㡢���䡢ȫ�̵ȶ����߼���
* �ռ���ϵ��ַ������������ִ�У��������ȫ�̾����������ˡ�  
*                 ������ֻ��ִ�ж������������ʿFUJILIFE������ַ�����ִ�������ȫ�̲�����
* ����ַ�ִ�������ȫ��ʱӦ���������������(1) �򵥵����������˶�
*                                           (2) ���˶��г̻��ֳ����ɸ��㣬ÿһ����ִ�����ɴ��ַ���ѭ�����ء�
************************************************************************************************************************
*/
typedef  struct
{
  uint8_t                  SpeedMax;                       /*�������ɵ��ٶȵ�λ*/
  uint8_t                  XMax;                           /*�ֶ������£���� �ɵ���ȡ�        PKEEP��ʾִ�иö���ʱ���ò������ɵ���*/
  uint8_t                  ZMax;                           /*�ֶ������£���� �ɵ������ȡ�      PKEEP��ʾִ�иö���ʱ���ò������ɵ���*/
  uint8_t                  YPrePosition;                   /*�ֶ������£�����ִ��ǰԤ����Yλ�á�PKEEP��ʾ��Ԥ��λ��*/ 
  uint8_t                  ZPrePosition;                   /*�ֶ������£�����ִ��ǰԤ����Zλ�á�PKEEP��ʾ��Ԥ��λ��*/ 

  union
  {
    struct 
    {
      uint8_t              MoveAdjustRollHandle     :1;    /*�ֶ������£��Ƿ�Ҫ�����ֶ��߶ȵ���*/
      uint8_t              PreBackScan              :1;    /*�ֶ������£�����ִ��ǰ�Ƿ�Ҫ�ȱ������*/
      uint8_t              Spot                     :1;    /*�ֶ��������Ƿ�֧�� ����*/
      uint8_t              Part                     :1;    /*�ֶ��������Ƿ�֧�� ����*/
      uint8_t              Whole                    :1;    /*�ֶ��������Ƿ�֧�� ȫ��*/
      uint8_t              Divide                   :1;    /*�Ƿ��г̻��ֳ����ɸ���*/
      uint8_t              PerRepeat                :4;    /*�����ȫ�̶����ڸ�����λ��ִ�д�����������һֱ�ظ�ִ�У������ȫ�̷ֵ�λִ�У�*/
    }Bit;
    uint16_t All;
  }ExeOp;  /*�ֶ���ִ��ѡ��*/
  
}CoreXYZMannualArrt_t;  


/*
************************************************************************************************************************
* ���Ͷ��� :  ��оXYZ�����������                                                                          
************************************************************************************************************************
*/
typedef struct CoreXYZActionManageTabItem
{
  uint8_t                 ActionID;                       /*��ʶҪִ�еĶ���*/
 
  CoreXYZActionRunFlag_t  ActionRunFlag;                  /*�������б�־*/

  int8_t                  XLeastRange;                    /*X�����ٵ��˶���Χֵ����������ʼ����������ٷ�Χ�� ��������ʼ�����ڵ����ٷ�Χ*/ 
  int8_t                  YLeastRange;                    /*Y�����ٵ��˶���Χֵ����������ʼ�����µ����ٷ�Χ�� ��������ʼ�����ϵ����ٷ�Χ*/ 
  int8_t                  ZLeastRange;                    /*Z�����ٵ��˶���Χֵ����������ʼ����ǰ�����ٷ�Χ�� ��������ʼ���������ٷ�Χ*/ 

  CoreXYZMannualArrt_t    Mannual;

  void  (*pActionExe)(Ticker_t ExePeriod, const struct CoreXYZActionManageTabItem *pItem);   /*����ִ�к���*/
}CoreXYZActionManageTabItem_t;  


/*
************************************************************************************************************************
* ���Ͷ��� :  ��оTCS�����������                                                                           
************************************************************************************************************************
*/
typedef struct
{
  uint8_t                  ActionID;                 /*��ʶҪִ�еĶ���*/
  CoreTCSActionRunFlag_t   ActionRunFlag;            /*�������б�־*/
  uint8_t                  AdditonOp;                /*���Ӳ���  Ԥ��*/
  void  (*pActionExe)(Ticker_t ExePeriod);           /*����ִ�к���*/
}CoreTCSActionManageTabItem_t;  

/*
************************************************************************************************************************
* ���Ͷ��� :  ��о��϶�����                                                                           
************************************************************************************************************************
*/
typedef struct
{
  int8_t                   XRelative;                /*�����ַ������λ��*/
  int8_t                   YRelative;
  int8_t                   ZRelative;

  uint8_t                  XSpeed;                   /*�ٶ�*/ 
  uint8_t                  YSpeed;
  uint8_t                  ZSpeed;

  uint8_t                  XMoveDirecion;            /*x��ʹ��ƫ���֣��������������Ŀ���*/

  uint8_t                  XYZPauseCtrl;             /*Ԥ������ͣ���ƣ�bit2��ͣX���  bit1��ͣY���   bit0��ͣZ��� */

  int8_t                   XInc;                     /*��������������Xλ��*/
  int8_t                   YInc;                     /*��������������Yλ��*/
  int8_t                   ZInc;                     /*��������������Zλ��*/
  uint16_t                 IncMaxTime;               /*�����������������ʱ��*/

}CoreComboActionItem_t;


/*
========================================================================================================================
*������������                                          ������������                                          ������������
========================================================================================================================
*/
uint8_t Core_GetXPosition(void);                                                      /*���Xλ��*/
uint8_t Core_GetYPosition(void);                                                      /*���Yλ��*/
uint8_t Core_GetZPosition(void);                                                      /*���Zλ��*/
uint8_t Core_SetXPosition(uint8_t Position);                                          /*����Xλ��*/
uint8_t Core_SetYPosition(uint8_t Position);                                          /*����Yλ��*/
uint8_t Core_SetZPosition(uint8_t Position);                                          /*����Zλ��*/
void Core_SetXYZPosition(uint8_t XPosition, uint8_t YPosition, uint8_t ZPosition);    /*����XYZλ��*/

/*����/��ѯ��о�ٶ�-----------------------------------------------------*/
void Core_SetTCSActionSpeed(uint8_t Speed);                                           /*����TCS�����ַ��ٶ�*/
void Core_SetXYZActionSpeed(uint8_t Speed);                                           /*����XYZ�����ַ��ٶ�*/


/*���û�о��Ħ�ַ�����---------------------------------------------*/
void  Core_SetTCSAction(uint8_t ExeMode, uint8_t Action);                             /*���� TCS ����*/
void  Core_SetXYZAction(uint8_t ExeMode, uint8_t Action);                             /*���� XYZ ����*/
void  Core_SetAction(uint8_t ExeMode, uint8_t XYZAction, uint8_t TCSAction);          /*���� ��о ����*/

uint8_t Core_GetXYZActionCompleteRepeat(void);                                        /*��ȡXYZ������ɴ���*/
void Core_ResetXYZActionStep(void);                                                   /*��λ XYZ��������*/

/*����/��ѯ ��о������״̬��ʶ-------------------------------------*/
void Core_SetZMBackProtectDisableSw(uint8_t Sw);                                      /*���� �������˱��� ʧЧ����*/

uint8_t Core_GetRollMoveState(void);                                                  /*��õ�ǰ������(����)����*/
uint8_t Core_GetMoveAdjustRoll(void);                                                 /*��� �ֶ����ڻ�о�߶ȷ�ʽ*/
uint8_t Core_SetMoveAdjustRoll(uint8_t MoveAdjustRoll);                               /*���� �ֶ����ڻ�о�߶ȷ�ʽ*/
uint8_t Core_GetRollRange(void);                                                      /*��õ�ǰ������(����)��Χ*/
uint8_t Core_SetRollRange(uint8_t Range);                                             /*��������(����)��Χ*/
CoreCSFlag_t        Core_GetCSFlag(void);                                             /*��û�о ���� �� ״̬ ��ʶ */
CoreActionRunFlag_t Core_GetActionRunFlag(void);                                      /*��û�о �������� ��ʶ */
XMotorCSFlag_t      Core_GetXMotorState(void);                                        /*������ ״̬ ��ʶ */
YMotorCSFlag_t      Core_GetYMotorState(void);                                        /*������ ״̬ ��ʶ */
ZMotorCSFlag_t      Core_GetZMotorState(void);                                        /*������ ״̬ ��ʶ */
TCSMotorCSFlag_t    Core_GetTCSMotorState(void);                                      /*������ ״̬ ��ʶ */

void Core_XPauseOn(void);
void Core_YPauseOn(void);
void Core_ZPauseOn(void);
void Core_TCSPauseOn(void);
void Core_XPauseOff(void);
void Core_YPauseOff(void);
void Core_ZPauseOff(void);
void Core_TCSPauseOff(void);
void Core_PauseOn(void);                                                              /*��ͣ��о*/
void Core_PauseOff(void);                                                             /*�����ͣ��о */

void Core_ShoulderAdjustRe(void);                                                     /*���¼粿���*/

uint8_t Core_GetXYZMannualManageAttr(uint8_t XYZAction, CoreXYZMannualArrt_t *pAttr); /*��о ����ֶ������¹�������� */

/*��о ��ʼ�� �� ������-------------------------------------------*/
Core_t* Core_Init(void);                                                              /*��о ��ʼ��*/
void Core_Handle(void);                                                               /*��о ����*/


#endif
