/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：BodyScan.c 
**
**    功能描述: 人体扫描
**
**    公    司：蒙发利电子
**
**    项目名称：
**
**    平台信息：
**
**    作    者：Hzy
**
**    其他说明: 人体检测包含：肩高、背部曲线、酸痛、心率等。一般肩高和背部曲线由机芯部件完成。
**
**    修改记录:  --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "BodyScan.h"
#include "MChair.h"

/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/


/*
========================================================================================================================
*【本地数据类型定义】                              【本地数据类型定义】                              【本地数据类型定义】
========================================================================================================================
*/


/*
========================================================================================================================
*【变量定义 & 各种声明】                          【变量定义 & 各种声明】                          【变量定义 & 各种声明】    
========================================================================================================================
*/
static BodyScan_t BodyScan;
BodyScan_t *pBodyScan = &BodyScan;


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : BodyScan_Init                                                                                                         
* 功能描述 : 人体扫描 初始化                                                                                        
* 输入参数 : 无                                                                                      
* 返回参数 : 返回 可操作扫描功能 的结构体 的指针                                                               
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
BodyScan_t*  BodyScan_Init(void)
{
  memset(pBodyScan, 0, sizeof(BodyScan_t));       /*清零所有数据*/
  Core_BackScanSetReScanCheckSw(ON);
  
  Spike_SetLegLenDetectExtendMax(3);//PLEGFLEX_MAX);
  
  return pBodyScan;
}

/*
************************************************************************************************************************
* 函数名称 : BodyScan_ShoulderReCheck                                                                                                         
* 功能描述 : 人体扫描 重新检测                                                                                   
* 输入参数 : 无                                                                                      
* 返回参数 : SUCCESS -- 执行成功   FAIL -- 执行失败                                                             
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t BodyScan_ShoulderReCheck(void)
{
  BodyScan_Init();                                  /*初始化所有相关数据即可重新扫描检测*/
  pBodyScan->CSFlag.Bit.ShoulderReCheck = TRUE;     /*标识肩部重新检测中*/
  Core_ShoulderAdjustRe();
  return SUCCESS;
}


/*
************************************************************************************************************************
* 函数名称 : BodyScan_PauseOn                                                                                                      
* 功能描述 : 暂停                                                               
* 输入参数 : 无                                                                     
* 返回参数 : 无                                                     
* 补充说明 : 无                                                                                                       
************************************************************************************************************************
*/
void BodyScan_PauseOn(void)
{
  if(pBodyScan->CSFlag.Bit.Pause < 0x1F)
  {
    pBodyScan->CSFlag.Bit.Pause++;
  }
}

/*
************************************************************************************************************************
* 函数名称 : BodyScan_PauseOff                                                                                                      
* 功能描述 : 解除暂停                                                          
* 输入参数 : 无                                                                     
* 返回参数 : 无                                                     
* 补充说明 : 无                                                                                                       
************************************************************************************************************************
*/
void BodyScan_PauseOff(void)
{
  if(pBodyScan->CSFlag.Bit.Pause > 0)
  {
    pBodyScan->CSFlag.Bit.Pause--;
  }
}

/*
************************************************************************************************************************
* 函数名称 : BodyScan_Handle                                                                                                         
* 功能描述 : 人体扫描 处理                                                                      
* 输入参数 : ExePeriod -- 函数执行周期                                                                           
* 返回参数 : 无                                          
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void BodyScan_Handle(Ticker_t ExePeriod)
{
  static uint8_t PauseOnOff = OFF;
  
  pBodyScan->CSFlag.Bit.Finish           = Core_BackScanGetCSFlag().Bit.Finish;  
//  pBodyScan->CSFlag.Bit.NoHumanOnSeat    = Core_BackScanGetCSFlag().Bit.NoHumanOnSeat;  
  pBodyScan->CSFlag.Bit.ShoulderAdjustEn = Core_BackScanGetCSFlag().Bit.ShoulderAdjustEn;  
  Core_BackScanSetRunSw(pBodyScan->CSFlag.Bit.Run);
  Core_BackScanSetCurveCheckSw(ON);
  if(FALSE == pBodyScan->CSFlag.Bit.NoHumanOnSeat)                         
  {
    pBodyScan->CSFlag.Bit.NoHumanOnSeat = Core_BackScanGetCSFlag().Bit.NoHumanOnSeat;  
  }
  if(0 == BSP_IO_GetVenderTestPin())      /*工装检测下，强制无人入座无效，不进行人体检测*/
  {
    pBodyScan->CSFlag.Bit.NoHumanOnSeat = FALSE;
    pBodyScan->CSFlag.Bit.Finish = TRUE;
  }
  
  /*执行扫描的 条件判断----------------------------------------------------------*/
  if(pBodyScan->CSFlag.Bit.Pause > 0)                                           /*暂停*/
  {
    PAUSE_ON(&PauseOnOff, 0, Core_BackScanPauseOn);
    return;
  }
  else
  {
    PAUSE_OFF(&PauseOnOff, 0, Core_BackScanPauseOff);
  }

  if((pMChair->SysModeCur != SYS_MODE_USERRUN)     &&                           /*这三个模式差别不大，差别在 SysMode_UserRun_Timer()函数中处理*/ 
     (pMChair->SysModeCur != SYS_MODE_TESTNOTIMER) &&                            
     (pMChair->SysModeCur != SYS_MODE_TESTAGE)     )
  {
    pBodyScan->CSFlag.Bit.Run = OFF;    
    return;
  }


  if(TRUE == pBodyScan->CSFlag.Bit.Finish)                                      /*扫描已经完成*/
  {
    pBodyScan->CSFlag.Bit.Run = OFF;    
    return;
  }

  if((FUNC_TYPE_AUTO    == pMChair->ComponentFuncState.Bit.Core) ||             /*机芯工作在自动 开启扫描*/
     (FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core) )              /*机芯工作在手动 也开启扫描*/ 
  {
    pBodyScan->CSFlag.Bit.Run = ON;                                             
  }
  else
  {
    pBodyScan->CSFlag.Bit.Run = OFF;                                            /*关闭扫描*/
  }
  
  if(OFF == pBodyScan->CSFlag.Bit.Run)
  {
    pBodyScan->ScanStep = 0;      
    pBodyScan->ScanStepTimeMs = 0;
    return;
  }

  /*背部扫描处理-----------------------------------------------------------------*/
  pBodyScan->ScanStepTimeMs += ExePeriod;                                       /*扫描步骤时间*/
  switch(pBodyScan->ScanStep)
  {
    case 0:
    {
      Spike_SetAngle(PBACK05, PFEET07, PZERO_USER_ANGLE); 
      pBodyScan->ScanStep++;
    }break;
    
    case 1:
    {
      if(pBodyScan->ScanStepTimeMs > 1000)
      {
        pBodyScan->ScanStepTimeMs = 0;
        if(TRUE == pBodyScan->CSFlag.Bit.ShoulderAdjustEn)                          /*肩部检测可调时，开提示音*/
        {
          if(Core_BackScanGetYCount() < 50)
          {
            Spike_SetLegLenDetectExtendMax(6);
          }
          else if(Core_BackScanGetYCount() < 100)
          {
            Spike_SetLegLenDetectExtendMax(5);
          }
          else if(Core_BackScanGetYCount() < 160)
          {
            Spike_SetLegLenDetectExtendMax(4);
          }
          else if(Core_BackScanGetYCount() < 220)
          {
            Spike_SetLegLenDetectExtendMax(3);
          }
          else //if(Core_BackScanGetYCount() < 200)
          {
            Spike_SetLegLenDetectExtendMax(2);
          }
          //else
          //{
          //  Spike_SetLegLenDetectExtendMax(1);
          //}
          pMChair->PromptToneTLMs = 300;                             
        }
      }    
    }break;
  
    default:
    {
    }break;
  } 
}

/*
************************************************************************************************************************
* 函数名称 : BodyScan_GetCSFlag                                                                                                         
* 功能描述 : 获得 控制 与 状态 标识                                                             
* 输入参数 : 无                                                                      
* 返回参数 : 控制与状态标识 的结构体                                          
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
BodyScanCSFlag_t BodyScan_GetCSFlag(void)
{
  return pBodyScan->CSFlag;
}
