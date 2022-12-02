/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: Core.h                                                                                                         
**
**    功能描述: 机芯驱动。管理 X Y Z TAP 四个马达。
**
**    公    司：蒙发利电子
**
**    项目名称：
**
**    平台信息：
**
**    作    者：Hzy
**
**    其他说明:
**
**    修改记录:  --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/
#ifndef  _CORE_H
#define  _CORE_H


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
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
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
/*将下层模块常用的宏定义，以更好的命名方式展现给同层和上层模块===========================*/
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
#define  CORE_YPOSITION_RESET_TOP                   YMOTOR_POSITION_RESET_AT_TOP   /*机芯位置复位方式: 上复位*/
#define  CORE_YPOSITION_RESET_BOT                   YMOTOR_POSITION_RESET_AT_BOT   /*机芯位置复位方式: 下复位*/


/*机芯行走范围：定点、区间================================================================*/
#define  CORE_ROLL_RANGE_NONE                       0        /*推拿(滚动)模式: 无*/
#define  CORE_ROLL_RANGE_WHOLE                      1        /*推拿(滚动)模式：全程*/
#define  CORE_ROLL_RANGE_SPOT                       2        /*推拿(滚动)模式：定点*/
#define  CORE_ROLL_RANGE_PART                       3        /*推拿(滚动)模式：区间*/

#define  CORE_PART_ROLL_RANGE                       4        /*区间行走半径范围*/

#define  CORE_ROLL_DIRECTION_UP                     0        /*推拿(滚动)方向 上*/
#define  CORE_ROLL_DIRECTION_DOWN                   1        /*推拿(滚动)方向 下*/

#define  CORE_ROLL_MOVE_NONE                        0        /*没在运动*/ 
#define  CORE_ROLL_MOVE_UP                          1        /*正在向上运动*/
#define  CORE_ROLL_MOVE_DOWN                        2        /*正在向下运动*/


/*机芯 各个方向的 调节 运动 ==============================================================*/
#define  CORE_MOVE_ADJUST_NONE                      0
#define  CORE_MOVE_ADJUST_ROLL_UP                   1
#define  CORE_MOVE_ADJUST_ROLL_DOWN                 2
#define  CORE_MOVE_ADJUST_FLEX_FORWARD              1
#define  CORE_MOVE_ADJUST_FLEX_BACKWARD             2


/*机芯 X Y Z 空间位置 相关宏定义==========================================================*/
/* PX、PY、PZ    ：机芯向上层提供的调用参数，属于软件逻辑位置。
 * PXM、PYM、PZM ：马达的实际物理(映射)位置，由实际的码盘等位置检测结构决定。
 *
 * 一般X轴和Z轴都是一一对应，无需映射转换。Y轴随着人体的身高不同，需要进行逻辑和物理值的映射。
 * 比如Y轴开孔后，物理码盘可识别88个位置(PYM00~PYM87)，但对应上层调用来说只把行程分31个(PY00~PY30)。
 * 上层调用只知道PY00~PY30参数，至于如何将PY00~PY30映射到PYM00~PYM87，则由机芯内部算法实现位置的映射。 */
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
#define  PY_LUMBAR                                  PY24        /*腰底位置(大致位于 命门穴附近)，将从哑门穴附近到腰底位置(PY_LUMBAR)分24段(PY00 ~ PY24)*/
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


/*机芯按摩手法相关宏定义===================================================================
 * 动作类型占高4位              ：最多15种类型
 * 某动作类型下的具体手法占低4位：每种类型各自最多15种手法
 *
 *      注意：颈部、肩部、腰部、背部、臀部等类型的手法 不一定只作用在固定的部位。                               
 *           例如 颈部揉捏 可以作用在任何部位。具体的作用部位由程序根据需要进行控制。                    
 *           但一般在该部位执行该手法的按摩效果会比较好。即这种特定部位的手法，比较有针对性。            
 *
 *  手法注解： KNEAD -- 揉捏             KNEADSTROKE -- 揉抚   KNEADPRESS -- 揉按 
 *             ROLL  -- 行走/推拿/滚动   SHIA        -- 指压   STRETCH    -- 伸展
*/
#define  CORE_ACTION_EXE_NONE                       0x00        /*机芯动作执行模式：无，其他使用方式，如人体检测等*/
#define  CORE_ACTION_EXE_MANNNUAL                   0x01        /*机芯动作执行模式：给上层手动程序使用*/
#define  CORE_ACTION_EXE_AUTO                       0x02        /*机芯动作执行模式：给上层自动程序使用*/

#define  CORE_ACTION_TYPE_NONE                      0x00        /*机芯动作类型：无*/
#define  CORE_ACTION_TYPE_COMMON1                   0x01        /*机芯动作类型：通用的手法，即不是针对特定部位的手法*/
#define  CORE_ACTION_TYPE_COMMON2                   0x02        /*机芯动作类型：通用的手法，即不是针对特定部位的手法*/
#define  CORE_ACTION_TYPE_COMMON3                   0x03        /*机芯动作类型：通用的手法，即不是针对特定部位的手法*/
#define  CORE_ACTION_TYPE_NEKC                      0x0A        /*机芯动作类型：颈部*/
#define  CORE_ACTION_TYPE_SHOULDER                  0x0B        /*机芯动作类型：肩部*/
#define  CORE_ACTION_TYPE_BACK                      0x0C        /*机芯动作类型：背部*/
#define  CORE_ACTION_TYPE_LUMBAR                    0x0D        /*机芯动作类型：腰部*/
#define  CORE_ACTION_TYPE_BUTTOCK                   0x0E        /*机芯动作类型：臀部*/
#define  CORE_ACTION_TYPE_BODY                      0x0F        /*机芯动作类型：全身*/

#define  CORE_ACTION_NONE                           ((CORE_ACTION_TYPE_NONE<<4) + 0x00)        /*无动作*/  
#define  XYZ_ACTION_NONE                            ((CORE_ACTION_TYPE_NONE<<4) + 0x00)        /*无动作*/  
#define  TCS_ACTION_NONE                            ((CORE_ACTION_TYPE_NONE<<4) + 0x00)        /*无动作*/
#define  XYZ_NONE                                   ((CORE_ACTION_TYPE_NONE<<4) + 0x00)        /*无动作*/  
#define  TCS_NONE                                   ((CORE_ACTION_TYPE_NONE<<4) + 0x00)        /*无动作*/

#define  KNIN                                       ((CORE_ACTION_TYPE_COMMON1<<4) + 0x01)     /*向内揉捏*/        
#define  KNOUT                                      ((CORE_ACTION_TYPE_COMMON1<<4) + 0x02)     /*向外揉捏*/  
#define  KNIN_VARY                                  ((CORE_ACTION_TYPE_COMMON1<<4) + 0x03)     /*向内变速揉捏*/        
#define  KNOUT_VARY                                 ((CORE_ACTION_TYPE_COMMON1<<4) + 0x04)     /*向外变速揉捏*/        
#define  KNIN_PUSH                                  ((CORE_ACTION_TYPE_COMMON1<<4) + 0x05)     /*向内推揉*/        
#define  KNOUT_PUSH                                 ((CORE_ACTION_TYPE_COMMON1<<4) + 0x06)     /*向外推揉*/        
#define  KNIN_LOOP                                  ((CORE_ACTION_TYPE_COMMON1<<4) + 0x07)     /*向内环揉*/        
#define  KNOUT_LOOP                                 ((CORE_ACTION_TYPE_COMMON1<<4) + 0x08)     /*向外环揉*/        
#define  KN_3_6                                     ((CORE_ACTION_TYPE_COMMON1<<4) + 0x09)     /*揉捏 时钟点路径来回*/        
#define  KN_3_6_9                                   ((CORE_ACTION_TYPE_COMMON1<<4) + 0x0A)     /*揉捏 时钟点路径来回*/        
#define  KN_6_9                                     ((CORE_ACTION_TYPE_COMMON1<<4) + 0x0B)     /*揉捏 时钟点路径来回*/        
#define  KN_12_9                                    ((CORE_ACTION_TYPE_COMMON1<<4) + 0x0C)     /*揉捏 时钟点路径来回*/  
#define  KN_12_9_6                                  ((CORE_ACTION_TYPE_COMMON1<<4) + 0x0D)     /*揉捏 时钟点路径来回*/ 
#define  KN_3_12_9                                  ((CORE_ACTION_TYPE_COMMON1<<4) + 0x0E)     /*揉捏 时钟点路径来回*/        

#define  ROLL                                       ((CORE_ACTION_TYPE_COMMON2<<4) + 0x01)     /*推拿(滚动)*/      
#define  ROLL_KNIN                                  ((CORE_ACTION_TYPE_COMMON2<<4) + 0x02)     /*推拿(滚动)+向内揉捏*/
#define  ROLL_KNOUT                                 ((CORE_ACTION_TYPE_COMMON2<<4) + 0x03)     /*推拿(滚动)+向外揉捏*/
#define  ROLLUP_PUSH                                ((CORE_ACTION_TYPE_COMMON2<<4) + 0x04)     /*前顶推拿上*/
#define  ROLLDOWN_PUSH                              ((CORE_ACTION_TYPE_COMMON2<<4) + 0x05)     /*前顶推拿下*/
#define  Z3D_SHIA1                                  ((CORE_ACTION_TYPE_COMMON2<<4) + 0x06)     /*Z方向3D 指压1*/        
#define  Z3D_SHIA2                                  ((CORE_ACTION_TYPE_COMMON2<<4) + 0x07)     /*Z方向3D 指压2*/        
#define  SWEDISH1                                   ((CORE_ACTION_TYPE_COMMON2<<4) + 0x08)     /*瑞典1*/        
#define  SWEDISH2                                   ((CORE_ACTION_TYPE_COMMON2<<4) + 0x09)     /*瑞典2*/        

#define  NECK_ROLL1                                 ((CORE_ACTION_TYPE_NEKC<<4) + 0x01)        /*颈部推拿1*/
#define  NECK_KNEAD1                                ((CORE_ACTION_TYPE_NEKC<<4) + 0x02)        /*颈部揉捏1*/
#define  NECK_KNEADSTROKE1                          ((CORE_ACTION_TYPE_NEKC<<4) + 0x03)        /*颈部揉抚1*/
#define  NECK_KNEADPRESS1                           ((CORE_ACTION_TYPE_NEKC<<4) + 0x04)        /*颈部揉按1*/
#define  NECK_SHIA1                                 ((CORE_ACTION_TYPE_NEKC<<4) + 0x05)        /*颈部指压1*/

#define  SHOULDER_ROLL1                             ((CORE_ACTION_TYPE_SHOULDER<<4) + 0x01)    /*肩部推拿(滚动)1*/
#define  SHOULDER_KNEAD1                            ((CORE_ACTION_TYPE_SHOULDER<<4) + 0x02)    /*肩部揉捏1*/
#define  SHOULDER_KNEADSTROKE1                      ((CORE_ACTION_TYPE_SHOULDER<<4) + 0x03)    /*肩部揉抚1*/
#define  SHOULDER_KNEADPRESS1                       ((CORE_ACTION_TYPE_SHOULDER<<4) + 0x04)    /*肩部揉按1*/
#define  SHOULDER_SHIA1                             ((CORE_ACTION_TYPE_SHOULDER<<4) + 0x05)    /*肩部指压1*/

#define  BACK_ROLLUP                                ((CORE_ACTION_TYPE_BACK<<4) + 0x01)        /*背部推拿(滚动)上*/
#define  BACK_ROLLDOWN                              ((CORE_ACTION_TYPE_BACK<<4) + 0x02)        /*背部推拿(滚动)下*/
#define  BACK_KNEAD1                                ((CORE_ACTION_TYPE_BACK<<4) + 0x03)        /*背部揉捏1*/
#define  BACK_KNEAD2                                ((CORE_ACTION_TYPE_BACK<<4) + 0x04)        /*背部揉捏2*/
#define  BACK_KNEADSTROKE1                          ((CORE_ACTION_TYPE_BACK<<4) + 0x05)        /*背部揉抚1*/
#define  BACK_KNEADPRESS1                           ((CORE_ACTION_TYPE_BACK<<4) + 0x06)        /*背部揉按1*/ 
#define  BACK_KNEADPRESS2                           ((CORE_ACTION_TYPE_BACK<<4) + 0x07)        /*背部揉按2*/ 
#define  BACK_SHIA1                                 ((CORE_ACTION_TYPE_BACK<<4) + 0x08)        /*背部指压1*/  

#define  LUMBAR_ROLLUP                              ((CORE_ACTION_TYPE_LUMBAR<<4) + 0x01)      /*腰部推拿(滚动)上*/   
#define  LUMBAR_ROLLDOWN                            ((CORE_ACTION_TYPE_LUMBAR<<4) + 0x02)      /*腰部推拿(滚动)下*/   
#define  LUMBAR_KNEAD1                              ((CORE_ACTION_TYPE_LUMBAR<<4) + 0x03)      /*腰部揉捏1*/
#define  LUMBAR_KNEAD2                              ((CORE_ACTION_TYPE_LUMBAR<<4) + 0x04)      /*腰部揉捏2*/  
#define  LUMBAR_KNEADSTROKE1                        ((CORE_ACTION_TYPE_LUMBAR<<4) + 0x05)      /*腰部揉抚1*/
#define  LUMBAR_KNEADPRESS1                         ((CORE_ACTION_TYPE_LUMBAR<<4) + 0x06)      /*腰部揉按1*/
#define  LUMBAR_KNEADPRESS2                         ((CORE_ACTION_TYPE_LUMBAR<<4) + 0x07)      /*腰部揉按2*/
#define  LUMBAR_SHIA1                               ((CORE_ACTION_TYPE_LUMBAR<<4) + 0x08)      /*腰部指压1*/

#define  BUTTOCK_ROLL1                              ((CORE_ACTION_TYPE_BUTTOCK<<4) + 0x01)     /*臀部推拿(滚动)1*/
#define  BUTTOCK_KNEAD1                             ((CORE_ACTION_TYPE_BUTTOCK<<4) + 0x02)     /*臀部揉捏1*/
#define  BUTTOCK_KNEADSTROKE1                       ((CORE_ACTION_TYPE_BUTTOCK<<4) + 0x03)     /*臀部揉抚1*/  
#define  BUTTOCK_KNEADPRESS1                        ((CORE_ACTION_TYPE_BUTTOCK<<4) + 0x04)     /*臀部揉按1*/ 
#define  BUTTOCK_SHIA1                              ((CORE_ACTION_TYPE_BUTTOCK<<4) + 0x05)     /*臀部指压1*/                   

#define  BODY_ROLL1                                 ((CORE_ACTION_TYPE_BODY<<4) + 0x01)        /*全身推拿(滚动)1*/
#define  BODY_KNEAD1                                ((CORE_ACTION_TYPE_BODY<<4) + 0x02)        /*全身揉捏1*/
#define  BODY_KNEADSTROKE1                          ((CORE_ACTION_TYPE_BODY<<4) + 0x03)        /*全身揉抚1*/
#define  BODY_KNEADPRESS1                           ((CORE_ACTION_TYPE_BODY<<4) + 0x04)        /*全身揉按1*/
#define  BODY_SHIA1                                 ((CORE_ACTION_TYPE_BODY<<4) + 0x05)        /*全身指压1*/                    

//-------------------------------------------------------------
#define  CLAP1                                      ((CORE_ACTION_TYPE_COMMON1<<4) + TCSMOTOR_ACTION_CLAP1)         /*拍打1*/ 
#define  CLAP2                                      ((CORE_ACTION_TYPE_COMMON1<<4) + TCSMOTOR_ACTION_CLAP2)         /*拍打2*/ 
#define  SHIA1                                      ((CORE_ACTION_TYPE_COMMON1<<4) + TCSMOTOR_ACTION_SHIA1)         /*指压1*/ 
#define  SHIA2                                      ((CORE_ACTION_TYPE_COMMON1<<4) + TCSMOTOR_ACTION_SHIA2)         /*指压2*/ 
#define  LTAP                                       ((CORE_ACTION_TYPE_COMMON1<<4) + TCSMOTOR_ACTION_LTAP)          /*轻敲击*/ 
#define  TAP                                        ((CORE_ACTION_TYPE_COMMON1<<4) + TCSMOTOR_ACTION_TAP)           /*敲击*/ 
#define  NO_FB_LTAP                                 ((CORE_ACTION_TYPE_COMMON1<<4) + TCSMOTOR_ACTION_NO_FB_LTAP)    /*无速度反馈的轻敲击*/  
#define  NO_FB_TAP                                  ((CORE_ACTION_TYPE_COMMON1<<4) + TCSMOTOR_ACTION_NO_FB_TAP)     /*无速度反馈的敲击*/  

#define  CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS          CORE_ACTION_TYPE_COMMON2        /*给XYZ手法步骤中专门附加的TCS动作*/
#define  XYZ_CLAP1                                  ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + TCSMOTOR_ACTION_CLAP1)         /*拍打1*/ 
#define  XYZ_CLAP2                                  ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + TCSMOTOR_ACTION_CLAP2)         /*拍打2*/ 
#define  XYZ_SHIA1                                  ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + TCSMOTOR_ACTION_SHIA1)         /*指压1*/ 
#define  XYZ_SHIA2                                  ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + TCSMOTOR_ACTION_SHIA2)         /*指压2*/ 
#define  XYZ_LTAP                                   ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + TCSMOTOR_ACTION_LTAP)          /*轻敲击*/ 
#define  XYZ_TAP                                    ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + TCSMOTOR_ACTION_TAP)           /*敲击*/ 
#define  XYZ_NO_FB_LTAP                             ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + TCSMOTOR_ACTION_NO_FB_LTAP)    /*无速度反馈的轻敲击*/  
#define  XYZ_NO_FB_TAP                              ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + TCSMOTOR_ACTION_NO_FB_TAP)     /*无速度反馈的敲击*/  
#define  XYZ_D_TCS                                  ((CORE_ACTION_TYPE_XYZ_STEP_ADD_TCS<<4) + 0x0F)                          /*给XYZ手法专门附加的默认的TCS动作*/


/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :  机芯按摩动作                                                                          
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
        uint8_t    Action       :4;    /*具体动作*/
        uint8_t    Type         :4;    /*动作类型*/
      }Bit;   
    }XYZ;   

    union
    {
      uint8_t      All;
      struct
      {
        uint8_t    Action       :4;    /*具体动作*/
        uint8_t    Type         :4;    /*动作类型*/
      }Bit;   
    }TCS;   
  }Bit;   
}CoreAction_t; 

/*
************************************************************************************************************************
* 类型定义 :  机芯按摩动作 运行标志                                                                          
************************************************************************************************************************
*/
typedef    union
{
  uint8_t      All;
  struct
  {
    uint8_t    KneadInRun                   :1;  /*向内揉捏手法 运行中*/ 
    uint8_t    KneadOutRun                  :1;  /*向外揉捏手法 运行中*/ 
    uint8_t    RollRun                      :1;  /*推拿(滚动)手法 运行中*/ 
    uint8_t    KneadRun                     :1;  /*揉捏手法 运行中*/ 
    uint8_t    KneadStrokeRun               :1;  /*揉抚手法 运行中*/ 
    uint8_t    KneadPressRun                :1;  /*揉按手法 运行中*/ 
    uint8_t    ShiaRun                      :1;  /*指压手法 运行中*/ 
    uint8_t    StretchRun                   :1;  /*伸展手法 运行中*/ 
  }Bit;   
}CoreXYZActionRunFlag_t;  

typedef    union
{
  uint8_t      All;
  struct
  {
    uint8_t    Clap1Run                     :1;  /*拍打1手法 运行中*/ 
    uint8_t    Clap2Run                     :1;  /*拍打2手法 运行中*/ 
    uint8_t    Shia1Run                     :1;  /*指压1手法 运行中*/ 
    uint8_t    Shia2Run                     :1;  /*指压2手法 运行中*/ 
    uint8_t    LTapRun                      :1;  /*轻敲击手法 运行中*/ 
    uint8_t    TapRun                       :1;  /*敲击手法 运行中*/ 
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
* 类型定义 :  机芯 控制与状态标识                                                                          
************************************************************************************************************************
*/
typedef  union 
{
  uint32_t All;
  struct
  {
    uint8_t    Pause                            :5;  /*暂停*/
    uint8_t    RollRange                        :2;  /*推拿(滚动)范围，无CORE_ROLL_RANGE_NONE  全程CORE_ROLL_RANGE_WHOLE  定点CORE_ROLL_RANGE_SPOT  区间CORE_ROLL_RANGE_PART*/
    uint8_t    RollDirection                    :1;  /*推拿(滚动)方向，上CORE_ROLL_DIRECTION_UP  下CORE_ROLL_DIRECTION_DOWN*/
    uint8_t    MoveAdjustRoll                   :2;  /*长按,调节机芯上下位置。无动作CORE_MOVE_ADJUST_NONE  机芯向上CORE_MOVE_ADJUST_ROLL_UP  机芯向下CORE_MOVE_ADJUST_ROLL_DOWN*/

    uint8_t    TCSFBEn                          :1;  /*敲拍 速度 反馈使能*/ 
    uint8_t    XFBEn                            :1;  /*揉捏 速度 反馈使能*/ 
    uint8_t    YFBEn                            :1;  /*推拿(滚动) 速度 反馈使能*/ 
    uint8_t    ZFBEn                            :1;  /*伸缩 速度 反馈使能*/ 
    
    uint8_t    ActionExeMode                    :2;  /*动作执行模式。 无CORE_ACTION_EXE_NONE   手动CORE_ACTION_EXE_MANNNUAL   自动CORE_ACTION_EXE_AUTO*/ 
  }Bit;

}CoreCSFlag_t;  /*Control State Flag  控制与状态标识*/

/*
************************************************************************************************************************
* 类型定义 :  机芯 相关操作数据结构                                                                           
************************************************************************************************************************
*/
typedef struct
{
  CoreCSFlag_t             CSFlag;                   /*控制与状态标识*/
  XMotorCSFlag_t           XMotorCSFlag;             /*马达控制与状态标识*/
  YMotorCSFlag_t           YMotorCSFlag;             /*马达控制与状态标识*/
  ZMotorCSFlag_t           ZMotorCSFlag;             /*马达控制与状态标识*/
  TCSMotorCSFlag_t         TCSMotorCSFlag;           /*马达控制与状态标识*/
  CoreActionRunFlag_t      ActionRunFlag;            /*动作运行标志*/   
  
  uint16_t                 XYZActionIndex;           /*机芯XYZ动作执行索引*/
  uint16_t                 TCSActionIndex;           /*机芯TCS动作执行索引*/
  
  CDP_DataFormat0x40_t     Set;                      /*给机芯板的设置数据*/
  CDP_DataFormat0x40_t     Qry;                      /*从机芯板查询回来的数据*/
  
  CoreBackScanCSFlag_t     BackScanCSFlag;           /*背部扫描控制与状态标识*/
}Core_t;  

/*
************************************************************************************************************************
* 类型定义 :  机芯XYZ动作手动的属性                                                                    
*
* 分立手法(如单独的揉捏)：可随意执行定点、区间、全程等动作逻辑。
* 空间组合的手法：定点可随意执行，但区间和全程就有所讲究了。  
*                 松下是只能执行定点操作，而富士FUJILIFE的许多手法可以执行区间或全程操作。
* 组合手法执行区间或全程时应该是这样的情况：(1) 简单的上下来回运动
*                                           (2) 把运动行程划分成若干个点，每一个点执行若干次手法，循环来回。
************************************************************************************************************************
*/
typedef  struct
{
  uint8_t                  SpeedMax;                       /*动作最大可调速度档位*/
  uint8_t                  XMax;                           /*手动动作下，最大 可调宽度。        PKEEP表示执行该动作时，该参数不可调节*/
  uint8_t                  ZMax;                           /*手动动作下，最大 可调伸缩度。      PKEEP表示执行该动作时，该参数不可调节*/
  uint8_t                  YPrePosition;                   /*手动动作下，动作执行前预定的Y位置。PKEEP表示无预定位置*/ 
  uint8_t                  ZPrePosition;                   /*手动动作下，动作执行前预定的Z位置。PKEEP表示无预定位置*/ 

  union
  {
    struct 
    {
      uint8_t              MoveAdjustRollHandle     :1;    /*手动动作下，是否要处理手动高度调节*/
      uint8_t              PreBackScan              :1;    /*手动动作下，动作执行前是否要先背部检测*/
      uint8_t              Spot                     :1;    /*手动动作下是否支持 定点*/
      uint8_t              Part                     :1;    /*手动动作下是否支持 区间*/
      uint8_t              Whole                    :1;    /*手动动作下是否支持 全程*/
      uint8_t              Divide                   :1;    /*是否将行程划分成若干个点*/
      uint8_t              PerRepeat                :4;    /*区间和全程动作在各个点位的执行次数（定点是一直重复执行，区间和全程分点位执行）*/
    }Bit;
    uint16_t All;
  }ExeOp;  /*手动的执行选项*/
  
}CoreXYZMannualArrt_t;  


/*
************************************************************************************************************************
* 类型定义 :  机芯XYZ动作管理表项                                                                          
************************************************************************************************************************
*/
typedef struct CoreXYZActionManageTabItem
{
  uint8_t                 ActionID;                       /*标识要执行的动作*/
 
  CoreXYZActionRunFlag_t  ActionRunFlag;                  /*动作运行标志*/

  int8_t                  XLeastRange;                    /*X轴最少的运动范围值。正数：起始点向外的最少范围； 负数：起始点向内的最少范围*/ 
  int8_t                  YLeastRange;                    /*Y轴最少的运动范围值。正数：起始点向下的最少范围； 负数：起始点向上的最少范围*/ 
  int8_t                  ZLeastRange;                    /*Z轴最少的运动范围值。正数：起始点向前的最少范围； 负数：起始点向后的最少范围*/ 

  CoreXYZMannualArrt_t    Mannual;

  void  (*pActionExe)(Ticker_t ExePeriod, const struct CoreXYZActionManageTabItem *pItem);   /*动作执行函数*/
}CoreXYZActionManageTabItem_t;  


/*
************************************************************************************************************************
* 类型定义 :  机芯TCS动作管理表项                                                                           
************************************************************************************************************************
*/
typedef struct
{
  uint8_t                  ActionID;                 /*标识要执行的动作*/
  CoreTCSActionRunFlag_t   ActionRunFlag;            /*动作运行标志*/
  uint8_t                  AdditonOp;                /*附加操作  预留*/
  void  (*pActionExe)(Ticker_t ExePeriod);           /*动作执行函数*/
}CoreTCSActionManageTabItem_t;  

/*
************************************************************************************************************************
* 类型定义 :  机芯组合动作项                                                                           
************************************************************************************************************************
*/
typedef struct
{
  int8_t                   XRelative;                /*动作手法的相对位置*/
  int8_t                   YRelative;
  int8_t                   ZRelative;

  uint8_t                  XSpeed;                   /*速度*/ 
  uint8_t                  YSpeed;
  uint8_t                  ZSpeed;

  uint8_t                  XMoveDirecion;            /*x轴使用偏心轮，因此有两个方向的控制*/

  uint8_t                  XYZPauseCtrl;             /*预留：暂停控制，bit2暂停X马达  bit1暂停Y马达   bit0暂停Z马达 */

  int8_t                   XInc;                     /*步骤增加条件：X位置*/
  int8_t                   YInc;                     /*步骤增加条件：Y位置*/
  int8_t                   ZInc;                     /*步骤增加条件：Z位置*/
  uint16_t                 IncMaxTime;               /*步骤增加条件：最大时间*/

}CoreComboActionItem_t;


/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
========================================================================================================================
*/
uint8_t Core_GetXPosition(void);                                                      /*获得X位置*/
uint8_t Core_GetYPosition(void);                                                      /*获得Y位置*/
uint8_t Core_GetZPosition(void);                                                      /*获得Z位置*/
uint8_t Core_SetXPosition(uint8_t Position);                                          /*设置X位置*/
uint8_t Core_SetYPosition(uint8_t Position);                                          /*设置Y位置*/
uint8_t Core_SetZPosition(uint8_t Position);                                          /*设置Z位置*/
void Core_SetXYZPosition(uint8_t XPosition, uint8_t YPosition, uint8_t ZPosition);    /*设置XYZ位置*/

/*设置/查询机芯速度-----------------------------------------------------*/
void Core_SetTCSActionSpeed(uint8_t Speed);                                           /*设置TCS动作手法速度*/
void Core_SetXYZActionSpeed(uint8_t Speed);                                           /*设置XYZ动作手法速度*/


/*设置机芯按摩手法动作---------------------------------------------*/
void  Core_SetTCSAction(uint8_t ExeMode, uint8_t Action);                             /*设置 TCS 动作*/
void  Core_SetXYZAction(uint8_t ExeMode, uint8_t Action);                             /*设置 XYZ 动作*/
void  Core_SetAction(uint8_t ExeMode, uint8_t XYZAction, uint8_t TCSAction);          /*设置 机芯 动作*/

uint8_t Core_GetXYZActionCompleteRepeat(void);                                        /*获取XYZ动作完成次数*/
void Core_ResetXYZActionStep(void);                                                   /*复位 XYZ动作步骤*/

/*设置/查询 机芯控制与状态标识-------------------------------------*/
void Core_SetZMBackProtectDisableSw(uint8_t Sw);                                      /*设置 伸缩回退保护 失效开关*/

uint8_t Core_GetRollMoveState(void);                                                  /*获得当前的推拿(滚动)方向*/
uint8_t Core_GetMoveAdjustRoll(void);                                                 /*获得 手动调节机芯高度方式*/
uint8_t Core_SetMoveAdjustRoll(uint8_t MoveAdjustRoll);                               /*设置 手动调节机芯高度方式*/
uint8_t Core_GetRollRange(void);                                                      /*获得当前的推拿(滚动)范围*/
uint8_t Core_SetRollRange(uint8_t Range);                                             /*设置推拿(滚动)范围*/
CoreCSFlag_t        Core_GetCSFlag(void);                                             /*获得机芯 控制 与 状态 标识 */
CoreActionRunFlag_t Core_GetActionRunFlag(void);                                      /*获得机芯 动作运行 标识 */
XMotorCSFlag_t      Core_GetXMotorState(void);                                        /*获得马达 状态 标识 */
YMotorCSFlag_t      Core_GetYMotorState(void);                                        /*获得马达 状态 标识 */
ZMotorCSFlag_t      Core_GetZMotorState(void);                                        /*获得马达 状态 标识 */
TCSMotorCSFlag_t    Core_GetTCSMotorState(void);                                      /*获得马达 状态 标识 */

void Core_XPauseOn(void);
void Core_YPauseOn(void);
void Core_ZPauseOn(void);
void Core_TCSPauseOn(void);
void Core_XPauseOff(void);
void Core_YPauseOff(void);
void Core_ZPauseOff(void);
void Core_TCSPauseOff(void);
void Core_PauseOn(void);                                                              /*暂停机芯*/
void Core_PauseOff(void);                                                             /*解除暂停机芯 */

void Core_ShoulderAdjustRe(void);                                                     /*重新肩部检测*/

uint8_t Core_GetXYZMannualManageAttr(uint8_t XYZAction, CoreXYZMannualArrt_t *pAttr); /*机芯 获得手动程序下管理的属性 */

/*机芯 初始化 与 处理函数-------------------------------------------*/
Core_t* Core_Init(void);                                                              /*机芯 初始化*/
void Core_Handle(void);                                                               /*机芯 处理*/


#endif
