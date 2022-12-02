/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: FuncTabHandle.h 
**
**    功能描述: 按摩功能动作表格的处理
**
**    公    司: 蒙发利电子
**
**    项目名称: 
**
**    平台信息: 
**
**    作    者: Hzy
**
**    其他说明: 
**          (1) 关于【机芯 自动】相关动作表格内的 Repeat 与 Time的说明
**              旧架构中的机芯动作手法，几乎都是单独的手法。可全部用时间来控制步骤的迭代。
**              新架构有许多组合手法，组合手法很难用时间来控制步骤的迭代，应该以动作完成的次数来控制。
**              因此，新架构在动作表格中加入了变量Repeat来控制动作的执行次数。  
**              目前，新架构【机芯】相关自动程序中 只有在 Repeat 次数值为RIGNORE，
**              或CoreXYZAction 动作为 XYZ_ACTION_NONE 时，才用时间来控制步骤的迭代。
**              其他的都用且Repeat来次数来进行步骤的迭代。且Repeat次数不为RIGNORE时，将忽略时间的判断。
**
**          (2) 关于部件的组合 
**              新架构以【机芯】、【充气】、【推杆】这三个主部件作为动作表格的组合元素。
**              可生成 7 种排列组合： 【机芯】、【充气】、【推杆】、【机芯+充气】、
**                                    【机芯+推杆】、【充气+推杆】、【机芯+充气+推杆】
**              其他的功能部件(如滚轮、振动)不再参与动作表格的组合，而是作为附加的伴随功能而存在。
**              附加的伴随功能既可以单独的运行，在主功能开启后，也可单独的对其进行开关操作。
**              这样做可控制排列组合的数量，否则如果所有的部件都像旧架构那样都可以组合。
**              随着组合数量的增多，相关判断逻辑将越来越复杂。
**
**    修改记录:  ------------------------------------------------------------------------------------------------------
**               2016.6.16 ---------------------------------------------------------------------------
**               给 ActionTabAttr_t类型增加两个变量 StartStepNum(表格开始 步骤数) 和 EndStepNum(表格结束 步骤数)。
**               并修改相应的代码，使得动作表格的执行步骤数量限制在  StartStepNum  和 EndStepNum之间。               
**
**               2016.6.20 ---------------------------------------------------------------------------
**               修改 MChair_TabHandle_CoreMixOtherAuto()函数及其相关部分逻辑。
**                 
**               原来  【Other】表格中插入【Other】表格的判断逻辑是：(★在ECP388机型上使用★)
**               当【Core】表格中的 XYZAction = XYZ_ACTION_NONE  且                   
**                                  Time1 = TIGNORE                                 
**               这两个个条件都满足时，【Other】作为插入表格。                      
**               其他情况下，【Other】作为伴随表格。                                
**
**               现在将 【Other】表格中插入【Other】表格的判断逻辑 改为：
**               当【Core】表格中的 Repeat = RIGNORE   且                           
**                                  Time1 = TIGNORE                                 
**               这两个个条件都满足时，【Other】作为插入表格。                      
**               其他情况下，【Other】作为伴随表格。   
**
**               ★★：如果从ECP388程序中拷贝表格过来用时，应注意修改相关表格内容。
**
**               2016.12.1 ---------------------------------------------------------------------------
**               ★ MChair_TabHandle_CoreMixOtherAuto()函数及其相关部分逻辑。                                ★ 
**               ★ 除维护ECP388系列之外。一般尽量不使用，而应使用 FuncAuto_AllCombo.c 文件中的功能作为替代。★ 
**
**               2016.12.5 ---------------------------------------------------------------------------
**               增加表格体验调试功能。
**               通过上位机能够快速编排自动程序表格。
========================================================================================================================
========================================================================================================================
*/

#ifndef  _FUNCTABHANDLE_H
#define  _FUNCTABHANDLE_H


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp.h"
#include "Gas.h"


/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/

#define  ACTION_TAB_STEP_SUM_MIN           1                            /*动作表格步骤总数最小值*/
#define  ACTION_TAB_STEP_SUM_MAX           600//255                     /*动作表格步骤总数最大值*/
#define  ACTION_TAB_STEP_NUM_MIN           (ACTION_TAB_STEP_SUM_MIN-1)  /*动作表格步骤号最小值*/
#define  ACTION_TAB_STEP_NUM_MAX           (ACTION_TAB_STEP_SUM_MAX-1)  /*动作表格步骤号最大值*/
#define  ACTION_TAB_STEP_NUM_END           (ACTION_TAB_STEP_NUM_MAX+1)  /*动作表格步骤号结束值*/

#define  ACTION_TAB_STEP_HOP_NONE          0                            /*动作表格步骤跳步：无*/
#define  ACTION_TAB_STEP_HOP_NEXT          1                            /*动作表格步骤跳步：下一步*/
#define  ACTION_TAB_STEP_HOP_LAST          2                            /*动作表格步骤跳步：上一步*/
#define  STEP_HOP_NONE                     ACTION_TAB_STEP_HOP_NONE                      
#define  STEP_HOP_NEXT                     ACTION_TAB_STEP_HOP_NEXT                     
#define  STEP_HOP_LAST                     ACTION_TAB_STEP_HOP_LAST                     


#ifndef  PIGNORE
#define  PIGNORE                           255                          /*位置忽略*/
#endif
#ifndef  PKEEP
#define  PKEEP                             (PIGNORE-1)                  /*位置保持*/
#endif

#define  TIGNORE                           65535                        /*时间忽略*/
#define  RIGNORE                           255                          /*重复次数忽略*/


#define  CORE_AUTO_PZLEVEL_REF             4                            /*机芯自动时的参照Z强度*/
#define  CORE_AUTO_PZLEVEL_MAX             8                            /*机芯自动时的最大Z强度*/


#define  P00                               0
#define  P01                               1
#define  P02                               2
#define  P03                               3
#define  P04                               4
#define  P05                               5
#define  P06                               6
#define  P07                               7
#define  P08                               8
#define  P09                               9
#define  P10                               10
#define  P11                               11
#define  P12                               12
#define  P13                               13
#define  P14                               14
#define  P15                               15
#define  P16                               16
#define  P17                               17
#define  P18                               18
#define  P19                               19
#define  P20                               20
#define  P21                               21
#define  P22                               22
#define  P23                               23
#define  P24                               24
#define  P25                               25
#define  P26                               26
#define  P27                               27
#define  P28                               28
#define  P29                               29
#define  P30                               30
#define  P31                               31
#define  P32                               32
#define  P33                               33
#define  P34                               34
#define  P35                               35
#define  P36                               36
#define  P37                               37
#define  P38                               38
#define  P39                               39
#define  P40                               40
#define  P41                               41
#define  P42                               42
#define  P43                               43
#define  P44                               44
#define  P45                               45
#define  P46                               46
#define  P47                               47
#define  P48                               48
#define  P49                               49
#define  P50                               50
#define  P51                               51
#define  P52                               52
#define  P53                               53
#define  P54                               54
#define  P55                               55
#define  P56                               56
#define  P57                               57
#define  P58                               58
#define  P59                               59
#define  P60                               60
#define  P61                               61
#define  P62                               62
#define  P63                               63
#define  P64                               64
#define  P65                               65
#define  P66                               66
#define  P67                               67
#define  P68                               68
#define  P69                               69
#define  P70                               70
#define  P71                               71
#define  P72                               72
#define  P73                               73
#define  P74                               74
#define  P75                               75
#define  P76                               76
#define  P77                               77
#define  P78                               78
#define  P79                               79
#define  P80                               80
#define  P81                               81
#define  P82                               82
#define  P83                               83
#define  P84                               84
#define  P85                               85
#define  P86                               86
#define  P87                               87
#define  P88                               88
#define  P89                               89
#define  P90                               90
#define  P91                               91
#define  P92                               92
#define  P93                               93
#define  P94                               94
#define  P95                               95
#define  P96                               96
#define  P97                               97
#define  P98                               98
#define  P99                               99


#define  MIX_MODE_NONE                     0                           /*混合模式：无*/
#define  MIX_MODE_INSERT                   1                           /*混合模式：插入方式*/ 
#define  MIX_MODE_ACCOMPANY                2                           /*混合模式：伴随方式*/ 

/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 : 表格动作条目 时间                                                                                                   
************************************************************************************************************************
*/
typedef  Ticker_t  TabItemTime_t;                 

/*
************************************************************************************************************************
* 类型定义 : 动作表格步骤                                                                                               
************************************************************************************************************************
*/
typedef struct
{
  uint8_t         Repeat;                        /*步骤重复执行次数*/
  uint8_t         TabRepeat;                     /*表格重复执行次数*/
  uint16_t        Num;                           /*步骤号*/
  TabItemTime_t   RunTimeMs100;                  /*步骤执行时间,单位100ms*/
  TabItemTime_t   RunTimeMs;                     /*步骤执行时间,单位ms，累计ms时间，满100ms后用清零，并递进RunTimeMs100*/
  uint32_t        TabRunTimeMs100;               /*表格执行时间,单位100ms*/

  union
  {
    uint8_t All;
    struct
    {
      uint8_t     StepHop                :2;     /*跳步执行*/
      uint8_t     OccurIterate           :1;     /*标识是否发生迭代*/
      uint8_t     SingleExe              :1;     /*标识是否只执行一次*/
      uint8_t     IsCoreMixOther         :1;     /*标识是否是【机芯】混合【其他】表格*/
      uint8_t     IsWithCore             :1;     /*标识是否带【机芯】*/
    }Bit;
  }AdditonOp;                                    /*附加操作*/

  union
  {
    uint8_t       All;
    struct
    {
      uint8_t     CoreXYZActionRepeat    :1;     /*机芯XYZ动作重复次数*/
      uint8_t     CorePositionOk         :1;     /*机芯位置*/
      uint8_t     SpikeAngleOk           :1;     /*推杆位置*/
      uint8_t     LegFlexOk              :1;     /*小腿伸缩*/
      uint8_t     ULegFlexOk             :1;     /*上 小腿伸缩*/
      uint8_t     TimeOut                :1;     /*超时*/
    }Bit;
  }IncConditionState;                            /*步骤增加条件的状态*/

  union
  {
    uint8_t All;
    struct
    {
      uint8_t     CoreXYZActionRepeat    :1;     /*机芯XYZ动作重复次数*/
      uint8_t     CorePositionOk         :1;     /*机芯位置*/
      uint8_t     SpikeAngleOk           :1;     /*推杆位置*/
      uint8_t     LegFlexOk              :1;     /*小腿伸缩*/
      uint8_t     ULegFlexOk             :1;     /*上 小腿伸缩*/
      uint8_t     TimeOut                :1;     /*超时*/
    }Bit;
  }IncJudgeCondition;                            /*步骤增加需要判断的条件*/

}ActionTabStep_t;


/*
************************************************************************************************************************
* 类型定义 : 动作表格属性                                                                                           
************************************************************************************************************************
*/
typedef struct
{
  uint16_t                   FuncID;                 /*按摩功能ID号，用来标识按摩程序*/    

  /*动作表格 (注：为兼容多种类型的表格，这里使用void(万用)指针，然后根据实际使用，再强制转换类型)*/   
  void                       *pActionTab;   
  uint8_t                    StartStepNum;           /*表格开始 步骤数*/           
  uint16_t                   EndStepNum;             /*表格结束 步骤数*/         
 
  /*根据需要添加相应的伴随模式。*/
  uint8_t                    FeetVibMode;            /*脚振 伴随模式*/ 
  uint8_t                    CalvesVibMode;          /*腿振 伴随模式*/ 
  uint8_t                    SeatVibMode;            /*座振 伴随模式*/ 
  uint8_t                    LumbarBackVibMode;      /*腰背振 伴随模式*/ 
  uint8_t                    FeetRollerMode;         /*脚滚 伴随模式*/ 
  uint8_t                    CalvesRollerMode;       /*腿滚 伴随模式*/ 
  uint8_t                    FeetHeatMode;           /*脚热 伴随模式*/  
  uint8_t                    CalvesHeatMode;         /*腿热 伴随模式*/  
  uint8_t                    SeatHeatMode;           /*座热 伴随模式*/  
  uint8_t                    LumbarBackHeatMode;     /*腰背热 伴随模式*/   
  uint8_t                    LedMode;                /*灯   伴随模式*/  
}ActionTabAttr_t;



/*
************************************************************************************************************************
* 类型定义 : 按摩功能 所包含的主部件                                                                                      
************************************************************************************************************************
*/
typedef union 
{
  uint8_t          All;
  struct
  {
    uint8_t        Core            :1;    /*机芯*/
    uint8_t        Gas             :1;    /*充气*/
    uint8_t        Spike           :1;    /*推杆*/

    uint8_t                        :1;
    uint8_t                        :1;
    uint8_t                        :1;
    uint8_t                        :1;
  }Bit;
}FuncMainComponent_t;

/*
************************************************************************************************************************
* 类型定义 : 按摩功能 具有的属性                                                                                    
************************************************************************************************************************
*/
typedef union 
{
  uint8_t          All;
  struct
  {
    /*#define  FUNC_TYPE_NONE                         0     功能类型 无
      #define  FUNC_TYPE_MANNUAL                      1     功能类型 手动
      #define  FUNC_TYPE_AUTO                         2     功能类型 自动
      #define  FUNC_TYPE_MANNUALAUTO                  3     功能类型 手动自动   */
    
    uint8_t        FuncType        :2;   /*0保留   1手动  2自动   3手动与自动*/
    uint8_t        Combo           :1;   /*0分立   1组合 */
    uint8_t                        :3;   /*预留*/
    uint8_t        Priority        :2;   /*优先级  0~3，数值越小，优先级越大 */
  }Bit;
}FuncAttr_t;

/*
************************************************************************************************************************
* 类型定义 : 按摩功能 的 逻辑                                                                                   
************************************************************************************************************************
*/
typedef struct FuncLogic
{
  uint16_t                 *pFuncCur;                                  /*当前功能*/
  uint16_t                 *pFuncHis;                                  /*历史功能*/

  FuncAttr_t               Attr;                                       /*属性*/
  FuncMainComponent_t      MainComponent;                              /*主部件*/

  void (*pFuncSwitch)(uint8_t SwitchMode, struct FuncLogic *pLogic);   /*指向功能切换函数*/                      
  void (*pFuncExe)(Ticker_t ExePeriod, struct FuncLogic *pLogic);      /*指向功能执行函数*/                 
}FuncLogic_t;


/*
************************************************************************************************************************
* 类型定义 : 滚轮 振动  控制位                                                                                  
************************************************************************************************************************
*/
__packed typedef union
{
  uint8_t          All;
  __packed struct
  {
    uint8_t        FeetVib            :1;    /*b0 脚部振动*/
    uint8_t        CalvesVib          :1;    /*b1 腿部振动 */
    uint8_t        SeatVib            :1;    /*b2 坐部振动*/
    uint8_t        LumbarBackVib      :1;    /*b3 腰背振动*/

    uint8_t        FeetRoller         :1;    /*b4 脚滚*/
    uint8_t        CalvesRoller       :1;    /*b5 腿滚*/
    uint8_t                           :1;    /*b6*/
    uint8_t                           :1;    /*b7*/
  }Bit;
}RollerVibCtrl_t;

/*
************************************************************************************************************************
* 类型定义 : 灯光 加热 控制位                                                                              
************************************************************************************************************************
*/
__packed typedef union
{
  uint8_t          All;
  __packed struct
  {
    uint8_t        FeetHeat            :1;    /*b0 脚部加热*/
    uint8_t        CalvesHeat          :1;    /*b1 腿部加热*/
    uint8_t        SeatHeat            :1;    /*b2 座部加热*/
    uint8_t        LumbarBackHeat      :1;    /*b3 腰背加热*/

    uint8_t        SleepLed            :1;    /*b4 呼吸灯*/
    uint8_t                            :1;    /*b5*/
    uint8_t                            :1;    /*b6*/
    uint8_t                            :1;    /*b7*/
  }Bit;
}LedHeatCtrl_t;


/*
************************************************************************************************************************
* 类型定义 : 【机芯】手动表格项                                                                                  
************************************************************************************************************************
*/
typedef struct
{
  uint8_t                  ActionID;                 /*标识要执行的动作*/
  uint8_t                  AdditonOp;                /*附加操作  */
 
  uint8_t                  XMax;                     /*最大 可调宽度*/
  uint8_t                  ZMax;                     /*最大 可调伸缩度*/

  uint8_t                  YPrePosition;             /*动作执行时，预定的Y位置*/ 

}CoreXYZActionMannualTabItem_t;  



/*
************************************************************************************************************************
* 类型定义 : 【机芯】自动动作对象                                                                                  
************************************************************************************************************************
*/
__packed typedef struct
{
  uint8_t                  XPosition;                /*机芯 宽度位置*/  
  uint8_t                  YPosition;                /*机芯 高度位置*/  
  uint8_t                  ZPosition;                /*机芯 伸缩度位置*/  

  uint8_t                  XYZActionSpeed;           /*XYZ手法 速度*/ 
  uint8_t                  TCSActionSpeed;           /*TCS手法 速度*/ 

  uint8_t                  XYZAction;                /*机芯 XYZ 马达按摩动作*/
  uint8_t                  TCSAction;                /*机芯 TCS 马达按摩动作*/ 

}CoreAutoActionObj_t;  /*机芯 自动按摩动作 对象*/


/*
************************************************************************************************************************
* 类型定义 : 【机芯】自动表格项                                                                            
************************************************************************************************************************
*/
__packed typedef struct
{
  CoreAutoActionObj_t      CoreAutoAction;            /*机芯动作对象*/

  RollerVibCtrl_t          RollerVibBit;              /*伴随 滚轮 振动*/
  LedHeatCtrl_t            LedHeatBit;                /*伴随 加热 灯光*/

  uint8_t                  Repeat;                    /*动作重复次数*/
  TabItemTime_t            Time1;                     /*动作时间*/

}CoreAutoTabItem_t;


/*
************************************************************************************************************************
* 类型定义 : 【充气】动作对象                                                                                  
************************************************************************************************************************
*/
__packed typedef struct
{
/*           GasPart1  --    b0    SeatSide           座侧 
*                            b1    LumbarSide         腰侧
*                            b2    ArmsRF             右手臂前
*                            b3    ArmsRB             右手臂后
*                            b4    ArmsLF             左手臂前
*                            b5    ArmsLB             左手臂后
*                            b6    ShoulderSide       肩侧
*
*            GasPart2  --    b0    CalvesBot           腿底  
*                            b1    CalvesSide          腿侧
*                            b2    CalvesSideHold      腿侧 保压
*                            b3    
*                            b4      
*                            b5         
*                            b6     
*                            b7                 */
  GasPart1_t                  GasPart1;   /*充气部位*/  
  GasPart2_t                  GasPart2;   /*充气部位*/
}GasActionObj_t;


/*
************************************************************************************************************************
* 类型定义 : 【充气】手动表格项                                                                                
************************************************************************************************************************
*/
__packed typedef struct
{
  GasActionObj_t           GasMannualAction;          /*充气动作对象*/

  RollerVibCtrl_t          RollerVibBit;              /*伴随 滚轮 振动*/
  LedHeatCtrl_t            LedHeatBit;                /*伴随 加热 灯光*/

  TabItemTime_t            Time1;                     /*动作时间*/
  TabItemTime_t            Time2;                     /*动作时间*/
  TabItemTime_t            Time3;                     /*动作时间*/
  TabItemTime_t            Time4;                     /*动作时间*/
  TabItemTime_t            Time5;                     /*动作时间*/

}GasMannualTabItem_t;

/*
************************************************************************************************************************
* 类型定义 : 【充气】自动表格项                                                                          
************************************************************************************************************************
*/
__packed typedef struct
{
  GasActionObj_t           GasAutoAction;             /*充气动作对象*/

  RollerVibCtrl_t          RollerVibBit;              /*伴随 滚轮 振动*/
  LedHeatCtrl_t            LedHeatBit;                /*伴随 加热 灯光*/

  TabItemTime_t            Time1;                     /*动作时间*/
  TabItemTime_t            Time2;                     /*动作时间*/
  TabItemTime_t            Time3;                     /*动作时间*/
  TabItemTime_t            Time4;                     /*动作时间*/
  TabItemTime_t            Time5;                     /*动作时间*/

}GasAutoTabItem_t;

/*
************************************************************************************************************************
* 类型定义 : 小腿伸缩控制                                                                               
************************************************************************************************************************
*/
__packed typedef union
{
  uint8_t          All;               
  __packed struct
  {
    uint8_t        Extend                :1;    /*伸*/
    uint8_t        Shorten               :1;    /*缩*/
    uint8_t        CheckTouchFeet        :1;    /*触脚检测*/
    uint8_t        CheckTouchGround      :1;    /*触地检测*/
    
    uint8_t        UpExtend              :1;    /*上小腿 伸*/
    uint8_t        UpShorten             :1;    /*上小腿 缩*/
  }Bit; 
}LegFlexCtrl_t; 

/*
************************************************************************************************************************
* 类型定义 : 【推杆】自动动作对象                                                                                 
************************************************************************************************************************
*/
__packed typedef struct
{
  LegFlexCtrl_t            LegFlexCtrl;               /*腿脚伸缩执行需求控制*/
  uint8_t                  BackPosition;              /*靠背位置*/  
  uint8_t                  FeetPosition;              /*腿脚位置*/  
  uint8_t                  ZeroPosition;              /*零重力位置*/  

}SpikeAutoActionObj_t; 


/*
************************************************************************************************************************
* 类型定义 : 【推杆】自动表格项
* 注：单纯的推杆自动 没有伴随功能，而且只是单纯的调节推杆角度而已。                                                                                   
************************************************************************************************************************
*/
__packed typedef struct
{
  SpikeAutoActionObj_t     SpikeAutoAction;           /*推杆动作对象*/

  TabItemTime_t            Time1;                     /*动作时间*/

}SpikeAutoTabItem_t;



/*
************************************************************************************************************************
* 类型定义 : 【机芯+充气】自动表格项                                                                                  
************************************************************************************************************************
*/
__packed typedef struct
{
  CoreAutoActionObj_t      CoreAutoAction;            /*机芯动作对象*/

  GasActionObj_t           GasAutoAction;             /*充气动作对象*/

  RollerVibCtrl_t          RollerVibBit;              /*伴随 滚轮 振动*/
  LedHeatCtrl_t            LedHeatBit;                /*伴随 加热 灯光*/

  uint8_t                  Repeat;                    /*动作重复次数*/

  TabItemTime_t            Time1;                     /*动作时间*/
  TabItemTime_t            Time2;                     /*动作时间*/
  TabItemTime_t            Time3;                     /*动作时间*/
  TabItemTime_t            Time4;                     /*动作时间*/
  TabItemTime_t            Time5;                     /*动作时间*/

}CoreGasAutoTabItem_t;


/*
************************************************************************************************************************
* 类型定义 : 【机芯+推杆】自动表格项                                                                                 
************************************************************************************************************************
*/
__packed typedef struct
{
  CoreAutoActionObj_t      CoreAutoAction;            /*机芯动作对象*/

  SpikeAutoActionObj_t     SpikeAutoAction;           /*推杆动作对象*/

  RollerVibCtrl_t          RollerVibBit;              /*伴随 滚轮 振动*/
  LedHeatCtrl_t            LedHeatBit;                /*伴随 加热 灯光*/

  uint8_t                  Repeat;                    /*动作重复次数*/

  TabItemTime_t            Time1;                     /*动作时间*/

}CoreSpikeAutoTabItem_t;


/*
************************************************************************************************************************
* 类型定义 : 【充气+推杆】自动表格项                                                                                
************************************************************************************************************************
*/
__packed typedef struct
{
  GasActionObj_t           GasAutoAction;             /*充气动作对象*/
  SpikeAutoActionObj_t     SpikeAutoAction;           /*推杆动作对象*/

  RollerVibCtrl_t          RollerVibBit;              /*伴随 滚轮 振动*/
  LedHeatCtrl_t            LedHeatBit;                /*伴随 加热 灯光*/

  TabItemTime_t            Time1;                     /*动作时间*/
  TabItemTime_t            Time2;                     /*动作时间*/
  TabItemTime_t            Time3;                     /*动作时间*/
  TabItemTime_t            Time4;                     /*动作时间*/
  TabItemTime_t            Time5;                     /*动作时间*/

}GasSpikeAutoTabItem_t;


/*
************************************************************************************************************************
* 类型定义 : 【机芯+充气+推杆】自动表格项                                                                                
************************************************************************************************************************
*/
__packed typedef struct
{
  CoreAutoActionObj_t      CoreAutoAction;            /*机芯动作对象*/
  GasActionObj_t           GasAutoAction;             /*充气动作对象*/
  SpikeAutoActionObj_t     SpikeAutoAction;           /*推杆动作对象*/

  RollerVibCtrl_t          RollerVibBit;              /*伴随 滚轮 振动*/
  LedHeatCtrl_t            LedHeatBit;                /*伴随 加热 灯光*/

  uint8_t                  Repeat;                    /*动作重复次数*/

  TabItemTime_t            Time1;                     /*动作时间*/
  TabItemTime_t            Time2;                     /*动作时间*/
  TabItemTime_t            Time3;                     /*动作时间*/
  TabItemTime_t            Time4;                     /*动作时间*/
  TabItemTime_t            Time5;                     /*动作时间*/

}CoreGasSpikeAutoTabItem_t;




/*
************************************************************************************************************************
* 类型定义 : 【机芯 混合 其他】自动表格项
* 注1：实现类似松下按摩椅那样，可在不同的【机芯】步骤，伴随（插入）不同的功能表格。
* 注2：也可当做单独的【机芯】自动表格项来使用                                                                                
************************************************************************************************************************
*/
typedef struct
{
  CoreAutoTabItem_t        CoreAutoTabItem;           /*机芯动作 项*/
  void                     *pOtherTab;                /*动作表格。 使用万用指针(void*)，以兼容各种表格*/                
}CoreMixOtherTabItem_t;

/*
************************************************************************************************************************
* 类型定义 : 混合的动作表格的属性                                                                                  
************************************************************************************************************************
*/
typedef struct
{
  void              *pTab;                                 /*混合的表格*/
  
  union
  {
    struct
    {
      uint8_t       Core                          :1;      /*功能部件:机芯*/
      uint8_t       Gas                           :1;      /*功能部件:充气*/
      uint8_t       Spike                         :1;      /*功能部件:推杆*/
    }Bit;
    uint8_t         All;
  }ComponentAttr;    
  
  union
  {
    struct
    {
      uint8_t       Head                       :1;      /*充气部位：头*/
      uint8_t       Shoulder                   :1;      /*充气部位：肩部*/
      uint8_t       Arms                       :1;      /*充气部位：手臂*/
      uint8_t       Lumbar                     :1;      /*充气部位：腰*/
      uint8_t       Seat                       :1;      /*充气部位：坐*/
      uint8_t       Calves                     :1;      /*充气部位：腿*/
      uint8_t       Feet                       :1;      /*充气部位：脚*/
    }Bit;
    uint8_t        All;
  }GasAttr;
  
  union
  {
    struct
    {
      uint8_t       BackMannualDis             :1;      /*推杆靠背手动无效*/
      uint8_t       ZeroMannualDis             :1;      /*推杆零重力手动无效*/
      uint8_t       FeetMannualDis             :1;      /*推杆小腿手动无效*/
      uint8_t       LegFlexMannualDis          :1;      /*推杆小腿伸缩手动无效*/
      uint8_t       ULegFlexMannualDis         :1;      /*推杆上小腿伸缩手动无效*/
    }Bit;
    uint8_t         All;
  }SpikeAttr;
 
}MixOtherActionTabAttr_t;



/*
========================================================================================================================
*【全局声明】                                          【全局声明】                                          【全局声明】
========================================================================================================================
*/
void MChair_TabHandle_CoreAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep);
void MChair_TabHandle_SpikeAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep);
void MChair_TabHandle_GasAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep);
void MChair_TabHandle_CoreGasAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep);
void MChair_TabHandle_CoreSpikeAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep);
void MChair_TabHandle_GasSpikeAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep);
void MChair_TabHandle_CoreGasSpikeAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep);

void MChair_TabHandle_ResetMixOtherTabStep(uint8_t SpikeStop);
void MChair_TabHandle_CoreMixOtherAuto(Ticker_t ExePeriod, ActionTabAttr_t *pActionTabAttr, ActionTabStep_t *pStep);

#endif
