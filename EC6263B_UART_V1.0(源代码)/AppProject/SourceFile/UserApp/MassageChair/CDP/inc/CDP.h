/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: CDP.h                                                                                                         
**
**    功能描述: 通信数据包。
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
#ifndef  _CDP_H
#define  _CDP_H


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
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
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
#define  CDP_FRAME_MIN_LEN                      9                    /*最小帧长度*/ 
#define  CDP_PDU_EXCEPT_DU_LEN                  6                    /*协议数据单元的长度(除掉数据单元)*/


#define  CDP_FRAME_BOUNDARY                     0x7E                 /*帧边界*/            
#define  CDP_FRAME_HEADER                       CDP_FRAME_BOUNDARY   /*帧头*/
#define  CDP_FRAME_FOOTER                       CDP_FRAME_BOUNDARY   /*帧尾*/            
#define  CDP_FRAME_ESC                          0x5E                 /*帧转义*/   


#define  CDP_FRAME_OFFSET_HEADER                0                    /*帧头偏移*/
#define  CDP_FRAME_OFFSET_PDU                   1                    /*协议数据单元偏移，即帧头开始后的第一个数据*/

#define  CDP_PDU_OFFSET_DES                     0                    /*协议数据单元内的 目的地址 偏移*/
#define  CDP_PDU_OFFSET_SRC                     1                    /*协议数据单元内的 源地址   偏移*/
#define  CDP_PDU_OFFSET_VER                     2                    /*协议数据单元内的 版本号   偏移*/
#define  CDP_PDU_OFFSET_CMD                     4                    /*协议数据单元内的 命令码   偏移*/
#define  CDP_PDU_OFFSET_ACK                     5                    /*协议数据单元内的 应答     偏移*/
#define  CDP_PDU_OFFSET_DU                      6                    /*协议数据单元内的 数据单元 偏移*/

#define  CDP_DU_OFFSET_LEN                      0                    /*数据单元内的 长度 偏移*/            
#define  CDP_DU_OFFSET_ID                       1                    /*数据单元内的 ID   偏移*/  
#define  CDP_DU_OFFSET_DATA                     2                    /*数据单元内的 数据 偏移*/  
#define  CDP_DU_OFFSET_SERVER_ID                2                    /*远程升级数据单元内的 ID   偏移*/
#define  CDP_DU_OFFSET_SERVER_DATA              3                    /*远程升级数据单元内的 数据 偏移*/

#define  CDP_ADDR_CEN                           0x01                 /*地址：中心板*/
#define  CDP_ADDR_CTR                           0x10                 /*地址：按键手控器 / 类平板 / 手机APP */
#define  CDP_ADDR_CTR_SIDE                      0x11                 /*地址：侧板按键 */
#define  CDP_ADDR_WIFI                          0x13                 /*地址：透传通讯模块 */
#define  CDP_ADDR_SERVER                        0x14                 /*地址：后台服务器 */
#define  CDP_ADDR_CORE                          0x20                 /*地址：机芯板*/
#define  CDP_ADDR_CORE_X                        0x21                 /*地址：机芯X马达控制板*/
#define  CDP_ADDR_CORE_Y                        0x22                 /*地址：机芯Y马达控制板*/
#define  CDP_ADDR_CORE_Z                        0x23                 /*地址：机芯Z马达控制板*/
#define  CDP_ADDR_CORE_TCS                      0x24                 /*地址：机芯敲击马达控制板*/
#define  CDP_ADDR_SPIKE                         0x30                 /*地址：推杆控制板*/
#define  CDP_ADDR_SPIKE_BACK                    0x31                 /*地址：靠背推杆控制板*/
#define  CDP_ADDR_SPIKE_FEET                    0x32                 /*地址：小腿推杆控制板*/
#define  CDP_ADDR_SPIKE_ZERO                    0x33                 /*地址：零重力推杆控制板*/
#define  CDP_ADDR_SPIKE_FEETFLEX                0x34                 /*地址：小腿伸缩控制板*/
#define  CDP_ADDR_HEAT                          0x40                 /*地址：加热控制板*/
#define  CDP_ADDR_HEAT_HEAD                     0x41                 /*地址：头部加热控制板*/
#define  CDP_ADDR_HEAT_LUMBARBACK               0x42                 /*地址：腰背加热控制板*/
#define  CDP_ADDR_HEAT_SEAT                     0x43                 /*地址：坐部加热控制板*/
#define  CDP_ADDR_HEAT_CALVES                   0x44                 /*地址：腿部加热控制板*/
#define  CDP_ADDR_HEAT_FEET                     0x45                 /*地址：脚部加热控制板*/
#define  CDP_ADDR_HEAT_ARMS                     0x46                 /*地址：手部加热控制板*/
#define  CDP_ADDR_VIB                           0x48                 /*地址：振动控制板*/
#define  CDP_ADDR_VIB_HEAD                      0x49                 /*地址：头部振动控制板*/
#define  CDP_ADDR_VIB_LUMBARBACK                0x4A                 /*地址：腰背振动控制板*/
#define  CDP_ADDR_VIB_SEAT                      0x4B                 /*地址：坐部振动控制板*/
#define  CDP_ADDR_VIB_CALVES                    0x4C                 /*地址：腿部振动控制板*/
#define  CDP_ADDR_VIB_FEET                      0x4D                 /*地址：脚部振动控制板*/
#define  CDP_ADDR_VIB_ARMS                      0x4E                 /*地址：手部振动控制板*/
#define  CDP_ADDR_ROLLER                        0x50                 /*地址：滚轮控制板*/
#define  CDP_ADDR_ROLLER_FEET                   0x51                 /*地址：脚滚控制板*/
#define  CDP_ADDR_ROLLER_CALVES                 0x52                 /*地址：小腿滚控制板*/
#define  CDP_ADDR_LED                           0x58                 /*地址：灯光控制板*/
#define  CDP_ADDR_CALVES_FEET                   0x60                 /*地址：腿脚控制板*/
/*注意：一个物理模块中可能包含多个逻辑功能。比如小腿模块可能包含：小腿伸缩、小腿充气、脚滚等。
 *      软件工程师根据系统设计需求情况分配地址即可（可分配"0x34小腿伸缩控制板"，也可分配成"0x51 脚滚控制板",
 *      也可分配成"0x60腿脚综合控制板"）。当然在模块地址不冲突的情况下，尽量分配与其功能相当的地址名称。*/
#define  CDP_ADDR_SELF                          CDP_ADDR_CEN         /*地址：自身*/


#define  CDP_CMD_UPREPORT                       0x01                 /*命令：从机主动上报 */
#define  CDP_CMD_QRY                            0x02                 /*命令：主机查询从机 */   
#define  CDP_CMD_SET_NACK                       0x03                 /*命令：主机设置从机，从机无需应答 */    
#define  CDP_CMD_SET_ACK                        0x04                 /*命令：主机设置从机，从机需应答 */  
#define  CDP_CMD_UPREPORT_SERVER                0x11                 /*命令：服务器 主动上报，需要应答*/ 
#define  CDP_CMD_QRY_SERVER                     0x12                 /*命令：服务器 主机查询从机*/ 
#define  CDP_CMD_SET_NACK_SERVER                0x13                 /*命令：服务器 主机设置从机，从机无需应答*/ 
#define  CDP_CMD_SET_ACK_SERVER                 0x14                 /*命令：服务器 主机设置从机，从机需应答*/ 
#define  CDP_CMD_TIMEING_UPREPORT_SERVER        0x15                 /*命令：服务器 主机主动定时上报，从机需不应答*/ 
#define  CDP_CMD_IAP                            0xF0                 /*命令：IAP升级操作 */   
#define  CDP_CMD_REMOTE_IAP                     0xF1                 /*命令：远程IAP升级操作 */  


#define  CDP_ACK_SUCCESS                        0x00                 /*应答：执行成功 */
#define  CDP_ACK_FAIL                           0x01                 /*应答：执行失败 */
#define  CDP_ACK_INVALID_CMD                    0x02                 /*应答：不支持的命令码 */
#define  CDP_ACK_INVALID_LEN                    0x03                 /*应答：数据长度错 */
#define  CDP_ACK_INVALID_ID                     0x04                 /*应答：数据中有不支持的ID识别码 */
#define  CDP_ACK_SEND                           0xFF                 /*应答：数据的主动发起方，填0xFF */


#define  CDP_DAP_CTRL                           0x01                 /*数据访问物理端口：手控器*/                                       
#define  CDP_DAP_CEN                            0x02                 /*数据访问物理端口：机芯板*/                                                  
#define  CDP_DAP_CORE                           0x03                 /*数据访问物理端口：机芯板*/                                                  
#define  CDP_DAP_OTHER                          0xFF                 /*数据访问物理端口：其他*/                                                  

#define  CDP_TYPE_COMMON                        0x00                 /*通信数据包类型：通用*/                              
#define  CDP_TYPE_OLD_PROTOCOL                  0x01                 /*通信数据包类型：旧协议*/                                     
#define  CDP_TYPE_NEW_PROTOCOL                  0x02                 /*通信数据包类型：新协议*/                                    
#define  CDP_TYPE_CTRL                          0x10                 /*通信数据包类型：手控器*/                                    
#define  CDP_TYPE_SIDE_CTRL                     0x11                 /*通信数据包类型：侧板控制器*/                                    
#define  CDP_TYPE_APP_KEY                       0x12                 /*通信数据包类型：APP键值*/                                    
#define  CDP_TYPE_APP_CFG                       0x13                 /*通信数据包类型：APP配置*/                                    

#define  CDP_DU_HANDLE_INVALID_ID               0xFE                 /*数据单元处理 不支持的ID*/                                       
#define  CDP_DU_HANDLE_ERR                      0xFF                 /*数据单元处理错误*/                                       


/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/

/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
/*
************************************************************************************************************************
* 类型定义 :  0x01 键值(手控器-->中心板)                                                                     
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID;
  
  uint8_t             KeyVal;                                      /*键值*/
  uint8_t             AddtionData[1];                              /*键值所附带的数据*/

}CDP_DataFormat0x01_t;

/*
************************************************************************************************************************
* 类型定义 :  0x1F 表格调试（上位机 <-->中心板）：用于辅助编排按摩动作表格                                                              
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
      uint8_t         ChannelSw                             :1;    /*表格数据通道开关*/
      uint8_t         StepHop                               :2;    /*跳步执行标识*/
    }Bit;
  }Byte0; 
  
  uint8_t             TabType;                                     /*表格类型*/

  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         ChannelNoSupport                      :1;    /*通道号不支持*/
      uint8_t         TapTypeNoSupport                      :1;    /*表格类型不支持*/
      uint8_t         ResourceConflict                      :1;    /*表格类型中资源冲突标识*/
      uint8_t         ConflictChnanelNum                    :3;    /*冲突的通道号*/
    }Bit;
  }Byte2; 
  
  uint8_t             StepSum;                                     /*总步数*/
  uint8_t             StepNum;                                     /*下发数据的步骤号*/
  uint8_t             StepData[1];                                 /*步骤数据*/
}CDP_DataFormat0x1A_To_0x1F_t;

/*
************************************************************************************************************************
* 类型定义 : 0x20 状态信息汇总包（中心板-->手控器）                                                                
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
      uint8_t         SysRun                                :1;    /*系统运行，即非待机模式*/
      uint8_t         Pause                                 :1;    /*暂停*/
      uint8_t         SysModeCur                            :6;    /*系统模式 当前*/
    }Bit;
  }Byte0; 

  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         BackLightRun                          :1;    /*控制器屏幕亮灭(背光源) */
      uint8_t         PromptToneRun                         :1;    /*控制器提示音(蜂鸣器)运行*/
      uint8_t         UserMassageTimeOut                    :1;    /*按摩定时到状态*/
      uint8_t         InsepectAutoFinish                    :1;    /*自动故障检测完成*/
      uint8_t         RealTimeInsepectFinish                :1;    /*实时故障检测完成*/
    }Bit;
  }Byte1; 

  uint8_t             PromptToneAddr;                              /*提示音地址*/
  uint8_t             UserMassageTimeMin;                          /*用户按摩时间 分*/
  uint8_t             UserMassageTimeSec;                          /*用户按摩时间 秒*/
  uint8_t             DefualtSetMassageTime;                       /*默认设置的按摩定时时间*/
  
}CDP_DataFormat0x20_t;



/*
************************************************************************************************************************
* 类型定义 :  0x40 机芯手法控制(中心板<-->机芯板）                                                                  
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID;
  
  uint8_t             XPosition;                                   /*x位置*/
  uint8_t             YPosition;                                   /*y位置*/
  uint8_t             ZPosition;                                   /*z位置*/
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         XYZActionSpeed                        :3;    /*xyz手法速度*/
      uint8_t         TCSActionSpeed                        :3;    /*TCS手法速度*/
      uint8_t         ResetXYZActionStep                    :1;    /*XYZ手法步骤复位*/
    }Bit;
  }Byte3; 

  uint8_t             XYZAction;                                   /*XYZ手法*/
  uint8_t             TCSAction;                                   /*TCS手法*/
  uint8_t             XYZActionCompleteCount;                      /*XYZ动作的完成次数计数，即做了该动作几次*/  

  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         ActionExeMode                         :2;    /*机芯动作手法执行模式。 无CORE_ACTION_EXE_NONE   手动CORE_ACTION_EXE_MANNNUAL   自动CORE_ACTION_EXE_AUTO*/ 
      uint8_t         RollRange                             :2;    /*推拿(滚动)范围，无CORE_ROLL_RANGE_NONE  全程CORE_ROLL_RANGE_WHOLE  定点CORE_ROLL_RANGE_SPOT  区间CORE_ROLL_RANGE_PART*/
      uint8_t         MoveAdjustRoll                        :2;    /*长按,调节机芯上下位置。无动作CORE_MOVE_ADJUST_NONE  机芯向上CORE_MOVE_ADJUST_ROLL_UP  机芯向下CORE_MOVE_ADJUST_ROLL_DOWN*/
      uint8_t         RollMoveState                         :2;    /*机芯上下运动状态，没在运动CORE_ROLL_MOVE_NONE    向上运动CORE_ROLL_MOVE_UP    向下运动CORE_ROLL_MOVE_DOWN*/
    }Bit;
  }Byte7;  

  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         CorePause                             :1;    /*机芯功能暂停 控制*/
      uint8_t         CoreZMBackProtectDisableSw            :1;    /*机芯退档保护 失效开关*/
      uint8_t                                               :1;    
      uint8_t         CoreBackScanPause                     :1;    /*机芯人体检测暂停 控制*/
      uint8_t         BackScanRun                           :1;    /*机芯人体检测运行开关*/
      uint8_t         BackScanFinish                        :1;    /*机芯人体检测完成标识*/
      uint8_t         BackScanReCheck                       :1;    /*重新进行检测标识*/
      uint8_t         BackScanNoHumanOnSeat                 :1;    /*无人入座*/
    }Bit;
  }Byte8; 
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         ShoulderAdjustEn                      :1;    /*肩部位置调节使能*/
      uint8_t         ShoulderAdjustOp                      :2;    /*肩部位置调节操作*/
      uint8_t         ShoulderLimitState                    :2;    /*肩部位置所处极限状态*/
      uint8_t         ShoulderAdjustKeyLS                   :1;    /*肩部位置调节按键长、短按方式*/
      uint8_t         CurveReceived                         :1;    /*人体曲线已接收标识*/
      uint8_t         CurveCheckSw                          :1;    /*人体曲线检测开关*/
    }Bit;
  }Byte9; 

  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         YMTOPLimtCode                         :4;    /*Y轴上极限位置编码*/
      uint8_t         YMBOTLimtCode                         :4;    /*Y轴下极限位置编码*/
    }Bit;
  }Byte10; 
  
  uint8_t             YMPositionMax;                               /*Y轴实际物理位置最大值*/

  __packed union 
  {
    uint16_t All;
    __packed struct
    {
      uint16_t        YMPositionResetAt                     :2;    /*机芯Y位置复位控制：上复位CORE_YPOSITION_RESET_TOP  下复位CORE_YPOSITION_RESET_BOT*/  
      uint16_t        CountNocalibrationSw                  :1;    /*Y轴极限位置不校正计数开关*/
      uint16_t        YMCountSum                            :13;   /*Y轴总行程计数值*/
    }Bit;
  }Byte1213; 
  
  uint8_t             YPositionMax;                                /*Y轴逻辑位置最大值*/

  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         XMotorPause                           :1;    /*X马达暂停 控制*/
      uint8_t         XMotorWork                            :1;    /*X马达工作 状态*/
      uint8_t         XPositionResetOK                      :1;    /*X位置复位 完成状态*/
      uint8_t                                               :1;   
      uint8_t         XPositionSensorFault                  :1;    /*位置传感器故障*/
      uint8_t         XPositionCodeFault                    :1;    /*位置编码故障，出现不应该存在的编码*/
      uint8_t         XRPMSensorFault                       :1;    /*转速(或计数)传感器故障*/
      uint8_t         XOverCurrentFault                     :1;    /*过电流故障*/
    }Bit;
  }Byte15;
  
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         YMotorPause                           :1;    /*Y马达暂停 控制*/
      uint8_t         YMotorWork                            :1;    /*Y马达工作 状态*/
      uint8_t         YPositionResetOK                      :1;    /*Y位置复位 完成状态*/
      uint8_t                                               :1;   
      uint8_t         YPositionSensorFault                  :1;    /*位置传感器故障*/
      uint8_t         YPositionCodeFault                    :1;    /*位置编码故障，出现不应该存在的编码*/
      uint8_t         YRPMSensorFault                       :1;    /*转速(或计数)传感器故障*/
      uint8_t         YOverCurrentFault                     :1;    /*过电流故障*/
    }Bit;
  }Byte16; 

  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         ZMotorPause                           :1;    /*Z马达暂停 控制*/
      uint8_t         ZMotorWork                            :1;    /*Z马达工作 状态*/
      uint8_t         ZPositionResetOK                      :1;    /*Z位置复位 完成状态*/
      uint8_t                                               :1;   
      uint8_t         ZPositionSensorFault                  :1;    /*位置传感器故障*/
      uint8_t         ZPositionCodeFault                    :1;    /*位置编码故障，出现不应该存在的编码*/
      uint8_t         ZRPMSensorFault                       :1;    /*转速(或计数)传感器故障*/
      uint8_t         ZOverCurrentFault                     :1;    /*过电流故障*/
    }Bit;
  }Byte17; 

  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         TCSMotorPause                         :1;    /*TCS马达暂停 控制*/
      uint8_t         TCSMotorWork                          :1;    /*TCS马达工作 状态*/
      uint8_t                                               :1;   
      uint8_t                                               :1;   
      uint8_t                                               :1;   
      uint8_t                                               :1;   
      uint8_t         TCSRPMSensorFault                     :1;    /*转速(或计数)传感器故障*/
      uint8_t         TCSOverCurrentFault                   :1;    /*过电流故障*/
    }Bit;
  }Byte18; 
 
}CDP_DataFormat0x40_t;



/*
************************************************************************************************************************
* 类型定义 :  0x41 按摩头加热控制(中心板<-->机芯板）
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
      uint8_t         MassageHeadHeatWork                   :1;    /*头部加热 工作控制*/
      uint8_t         MassageHeadHeatPause                  :1;    /*暂停控制*/
      uint8_t         MassageHeadHeatRun                    :1;    /*加热运行状态*/
    }Bit;
  }Byte0; 

  int8_t              MassageHeadTemp1;                            /*按摩头温度1*/
  int8_t              MassageHeadTemp2;                            /*按摩头温度2*/
 
  __packed union 
  {
    uint8_t All;
    __packed struct
    {
      uint8_t         MassageHeadThyristorShortFault        :1;    /*可控硅短路 故障*/
      uint8_t         MassageHeadThermistorShortFault       :1;    /*热敏电阻短路 故障*/
      uint8_t         MassageHeadThermistorOpenFault        :1;    /*热敏电阻开路 故障*/
    }Bit;
  }Byte3;  
  
}CDP_DataFormat0x41_t;

/*
************************************************************************************************************************
* 类型定义 :  0x48 腿脚充气控制(中心板<-->腿脚控制板）
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
      uint8_t         GasCalvesBot                          :1;    /*腿底*/
      uint8_t         GasCalvesSide                         :1;    /*腿侧*/
      uint8_t         GasCalvesSideHold                     :1;    /*腿侧保压*/
    }Bit;
  }Byte0; 
  
  uint8_t             CalvesPressureThreshold;                     /*气压启停门限*/
  
}CDP_DataFormat0x48_t;

/*
************************************************************************************************************************
* 类型定义 :  0x49 腿脚滚轮控制(中心板<-->腿脚控制板）
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
      uint8_t         FeetRollerSw                          :1;    /*脚滚 开关*/
      uint8_t         FeetRollerDirection                   :1;    /*脚滚 滚动方向*/
      uint8_t         FeetRollerInitPositionIO              :1;    /*脚滚初始位置IO检测*/
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
* 类型定义 :  0x4A 腿脚振动控制(中心板<-->腿脚控制板）
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
* 类型定义 :  0x4B 腿部伸缩控制(中心板<-->腿脚控制板）
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
      uint8_t         LegFlexAction                         :2;    /*小腿伸缩控制*/
      uint8_t         LegReachExtendLimt                    :1;    /*已达最长限定*/
      uint8_t         LegReachShortenLimt                   :1;    /*已达最短限定*/
      uint8_t         LegTouchGround                        :1;    /*触地*/
      uint8_t         LegTouchFeet                          :1;    /*触脚*/
    }Bit;
  }Byte0; 
  uint8_t             LegPositionCount;                            /*小腿伸缩计数值*/

}CDP_DataFormat0x4B_t;

/*
************************************************************************************************************************
* 类型定义 :  0x50 侧板控制器(侧板控制器-->中心板)                                                           
************************************************************************************************************************
*/
typedef __packed struct
{
  uint8_t             DataLen;
  uint8_t             DataID;
  
  uint8_t             KeyVal;                                      /*键值*/
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
      uint8_t         KeyStuck                              :1;    /*按键卡键标志*/
    }Bit;
  }Byte2;

}CDP_DataFormat0x50_t;


/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/

/*
************************************************************************************************************************
* 类型定义 :  通信数据包 数据对象格式                                                                       
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
* 类型定义 :  通信数据包 数据对象管理表项                                                                        
************************************************************************************************************************
*/
typedef struct
{
  uint8_t    ID;                   /*数据的ID识别码*/
  uint8_t    AdditonOp;            /*附加操作*/
  uint8_t    (*pDataHandle)(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);    /*数据处理函数*/

}CDPDataObjManageTabItem_t;

typedef	struct
{
  uint16_t   ID;                   /*数据的ID识别码*/
  uint8_t    AdditonOp;            /*附加操作*/
  uint8_t    (*pDataHandle)(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd);    /*数据处理函数*/

}CDPDataObjManageTabItem_Server_t;

/*
************************************************************************************************************************
* 类型定义 :  通信数据包控制与状态标识                                                                                    
************************************************************************************************************************
*/
typedef  union 
{
  struct
  {
    uint8_t        RepeaterWork                      :1;   /*转发器工作*/ 
    uint8_t        CenXxx_SideCtrlKeyStuck           :1;   /*侧板控制器卡键*/ 

  }Bit;

  uint8_t All;
}CDPCSFlag_t;  /*Control State Flag  控制与状态标识*/

/*
************************************************************************************************************************
* 类型定义 :  通信数据包 相关操作数据结构                                                                            
************************************************************************************************************************
*/
typedef  uint8_t  (*pDataObjRecHandleCB_t)(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t Cmd);  /*数据处理回调函数*/


/*
************************************************************************************************************************
* 类型定义 :  通信数据包 相关操作数据结构                                                                            
************************************************************************************************************************
*/
typedef struct
{
  CDPCSFlag_t           CSFlag;

  /*通信数据包部件 主要为调试用，实际编码应尽量使用各部件的接口函数-------*/
  CDP_CenXxx_t          *pCenXxx;
  CDP_CenServer_t       *pCenServer;
  CDP_CenApp_t          *pCenApp;
  
  CDP_DataFormat0x50_t  SetQry0x50;
  
  uint16_t              RepeaterLTL;           /*转发器活跃时长  LTL(Lively time length)*/
}CDP_t;


/*
========================================================================================================================
*【对外声明】                                          【对外声明】                                          【对外声明】
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
