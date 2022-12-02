/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: FeetSpike.c                                                                                                         
**
**    功能描述: 小腿推杆驱动。
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

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "FeetSpike.h"


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
static void FeetSpike_SetAction(uint8_t Action);


static FeetSpike_t FeetSpike;
FeetSpike_t *pFeetSpike = &FeetSpike;


#if (FEETSPIKE_POSITION_DETECT_MODE == FEETSPIKE_POSITION_DETECT_BY_CODE) /*位置检测使用码盘编码方式*/
/*
* 推杆位置点，码盘编码表
*
* 小腿推杆使用了完全的2位二进制编码 
* 使用位置编码的跳变来确定位置。
* 最底和最顶的位置还应使用编码（最底10  最顶00）来确定。
*
* 码盘编码表(透光 1  遮挡 0)：
* B(10)   //最底 
* B(11)   //
* B(01)   //
* B(00)   //最顶 
*/
static const PositionCodeMap_t FeetSpike_PositionCodeMapTab[] =
{
  {B(10), B(11), FEETSPIKE_POSITION_MIN},  
  {B(11), B(01), 1},
  {B(01), B(00), FEETSPIKE_POSITION_MAX}
};

#define  FEETSPIKE_POSITION_CODE_MAPTAB_NUM   TAB_NUM(FeetSpike_PositionCodeMapTab)

#endif /*结束 #if(FEETSPIKE_POSITION_DETECT_MODE == FEETSPIKE_POSITION_DETECT_BY_CODE)*/




/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/

#if (FEETSPIKE_POSITION_DETECT_MODE == FEETSPIKE_POSITION_DETECT_BY_CODE) /*位置检测使用码盘编码方式*/
/*
************************************************************************************************************************
* 函数名称 : FeetSpike_PositionCodeMap                                                                                                         
* 功能描述 : 推杆位置 编码 映射                                                                                                     
* 输入参数 : CodeCur -- 当前位置编码                                                                                                      
* 返回参数 : 大于 FEETSPIKE_POSITION_MAX       -- 无效的编码，位置存在问题。
*            小于或等于FEETSPIKE_POSITION_MAX  -- 位置编码有效                                                                                                        
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t FeetSpike_PositionCodeMap(uint8_t CodeCur)
{
  uint8_t i;
  uint8_t Position;
  static uint8_t CodeHis = 0xFF;


  Position = pFeetSpike->PositionRealVal;            /*先假设位置没改变，以下代码将根据情况改变Position的赋值*/

  /*最底和最顶的位置， 优先使用位置编码来确定*/
  if(B(10) == CodeCur)
  {
    Position = FEETSPIKE_POSITION_MIN;
    pFeetSpike->CSFlag.Bit.ReachDownLimt = TRUE;
    pFeetSpike->CSFlag.Bit.ReachUpLimt = FALSE; 
  }
  else if(B(00) == CodeCur)
  {
    Position =  FEETSPIKE_POSITION_MAX;
    pFeetSpike->CSFlag.Bit.ReachUpLimt = TRUE; 
    pFeetSpike->CSFlag.Bit.ReachDownLimt = FALSE;
  }

  /*使用编码跳变来确定位置*/
  else if(CodeHis != CodeCur) 
  {
    for(i=0; i<FEETSPIKE_POSITION_CODE_MAPTAB_NUM; i++)
    {
      if((CodeHis == FeetSpike_PositionCodeMapTab[i].HopCode1) && 
         (CodeCur == FeetSpike_PositionCodeMapTab[i].HopCode2) )
      {
        Position = FeetSpike_PositionCodeMapTab[i].Positon;
        break;
      }
      else if((CodeHis == FeetSpike_PositionCodeMapTab[i].HopCode2) && 
              (CodeCur == FeetSpike_PositionCodeMapTab[i].HopCode1) )
      {
        Position = FeetSpike_PositionCodeMapTab[i].Positon;
        break;
      }
    }

    pFeetSpike->CSFlag.Bit.ReachUpLimt   = FALSE;    /*编码不处于极限位置，清除极限标识*/
    pFeetSpike->CSFlag.Bit.ReachDownLimt = FALSE;
  }
  else
  {
    //Position = pFeetSpike->PositionRealVal; /*没发生跳变，则保持原位置*/
    pFeetSpike->CSFlag.Bit.ReachUpLimt   = FALSE;    /*编码不处于极限位置，清除极限标识*/
    pFeetSpike->CSFlag.Bit.ReachDownLimt = FALSE;
  }

  CodeHis = CodeCur;
  return Position; 
}

/*
************************************************************************************************************************
* 函数名称 : FeetSpike_PositionIOCheck                                                                                                         
* 功能描述 : 位置 IO口的检测                                                                                            
* 输入参数 : ExePeriod -- 函数的执行周期                                                                                                 
* 返回参数 : 无                                                                                             
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void FeetSpike_PositionIOCheck(Ticker_t ExePeriod)
{
  static uint8_t StableIOCode;                                      /*稳定的编码*/
  static uint8_t StableStat;                                        /*状态稳定统计*/
  static uint8_t IOCode = B(00);                                  /*要复位到底，先假设初始为最顶端*/


  /*有时会有干扰，因此这里做状态稳定的判断------------------------*/
  if(StableIOCode != (BSP_IO_ReadInput_FeetSpikePosition() & B(11)))
  {
    StableStat = 0;                                                 /*发生变化则表示不稳定*/
    StableIOCode = BSP_IO_ReadInput_FeetSpikePosition() & B(11);    /*读码盘*/
  }
  else
  {
    if(StableStat < 10)   
    {
      StableStat++;                                                 /*没发生变化，则稳定统计增加*/ 
    }
    else
    {
      IOCode = StableIOCode;                                        /*获取稳定后的编码*/
    }
  }


  /* 优先检测位置编码是否故障，---------------------------------------------
   * 一般只有码盘安装错误，或电机没被及时控停而过行程，才会出现这种故障
   * 注：由于使用完全二进制编码，所以无 位置编码故障 的检测。 */


  /*位置传感器故障检测 ------------------------------------------------*/
  if(pFeetSpike->PositionMonitor.PositionCode == IOCode)            /*位置没改变*/
  {
    if(ON == pFeetSpike->CSFlag.Bit.Run)                            /*马达在运行时，累加传感器失联时间*/
    {
      if(pFeetSpike->PositionMonitor.SensorLostTimeMs <= FEETSPIKE_POSITION_SENSOR_LOST_TIME_THRESHOLD) /*未超过失联门限时间*/
      {
        pFeetSpike->PositionMonitor.SensorLostTimeMs += ExePeriod;
      }
      else
      {
        pFeetSpike->CSFlag.Bit.PositionSensorFault = FAULT;         /*位置传感器故障，出现后，程序不会清零，靠复位或重上电才清零*/
      }
    }
    else
    {
      pFeetSpike->PositionMonitor.SensorLostTimeMs = 0;             /*清零传感器失联时间*/
    }
  }
  else  /*位置改变*/
  { 
    pFeetSpike->PositionMonitor.SensorLostTimeMs = 0;	              /*清零传感器失联时间*/
  }


  /*位置相关变量判断与更新--------------------------------------------*/
  pFeetSpike->PositionRealVal = FeetSpike_PositionCodeMap(IOCode);
  if(FEETSPIKE_POSITION_MIN == pFeetSpike->PositionRealVal)       /*最底位置*/
  {
    pFeetSpike->CSFlag.Bit.PositionResetOK = TRUE;                /*位置复位完成*/
  }

  if((FEETSPIKE_ACTION_UP == pFeetSpike->Action) && (pFeetSpike->CSFlag.Bit.ReachUpLimt))
  {
    FeetSpike_SetAction(FEETSPIKE_ACTION_STOP);                     /*达到上限位不能再执行向上运动*/
  }

  if((FEETSPIKE_ACTION_DOWN == pFeetSpike->Action) && (pFeetSpike->CSFlag.Bit.ReachDownLimt))
  {
    FeetSpike_SetAction(FEETSPIKE_ACTION_STOP);                     /*达到下限位不能再执行向下运动*/
  }

  pFeetSpike->PositionMonitor.PositionCode = IOCode;                /*记录新编码*/
}

#endif /*结束 #if(FEETSPIKE_POSITION_DETECT_MODE == FEETSPIKE_POSITION_DETECT_BY_CODE)*/



#if (FEETSPIKE_POSITION_DETECT_MODE == FEETSPIKE_POSITION_DETECT_BY_COUNT) /*位置检测使用计数方式*/
/*
************************************************************************************************************************
* 函数名称 : FeetSpike_CountIOCheck_CB                                                                                                         
* 功能描述 : 位置 计数IO口检测  的回调函数                                                                                          
* 输入参数 : 无                                                                                    
* 返回参数 : 无                                                                                             
* 补充说明 : 该函数通过 BSP_IO_InputInterrupt_RegCB_FeetSpikeCount(FeetSpike_CountIOCheck_CB);向下注册给BSP层                                                                                                         
************************************************************************************************************************
*/
static void FeetSpike_CountIOCheck_CB(void)
{
  /*_COUNT_MIN+3：由于误差，经常会推杆停的时候，计数值还大于0，这里加快到0的处理*/
  MotorCountUpdata(&pFeetSpike->PositionMonitor.PositionCountCur, 
                   pFeetSpike->PositionMonitor.CountDirection, 
                   FEETSPIKE_COUNT_MAX, FEETSPIKE_COUNT_MIN+3);
}

/*
************************************************************************************************************************
* 函数名称 : FeetSpike_PositionIOCheck                                                                                                         
* 功能描述 : 位置 IO口的检测                                                                                   
* 输入参数 : ExePeriod -- 函数的执行周期                                                                                  
* 返回参数 : 无                                                                                             
* 补充说明 : 无                                                                                                       
************************************************************************************************************************
*/
void FeetSpike_PositionIOCheck(Ticker_t ExePeriod)
{
  static  Ticker_t ReachMinCountMs;

  /*计数传感器故障检测---------------------------------------------*/
  if(pFeetSpike->PositionMonitor.PositionCountHis == pFeetSpike->PositionMonitor.PositionCountCur)  /*计数无变化*/
  {
    if(ON == pFeetSpike->CSFlag.Bit.Run)                                             /*推杆开启*/
    {
      if(pFeetSpike->PositionMonitor.SensorLostTimeMs <= FEETSPIKE_COUNT_SENSOR_LOST_TIME_THRESHOLD)
      {
        pFeetSpike->PositionMonitor.SensorLostTimeMs += ExePeriod;                   /*马达在运行时，累加计数传感器失联时间*/
      }
      else
      {
        FeetSpike_SetAction(FEETSPIKE_ACTION_STOP);                                  /*计数一旦停止，便停止马达运动*/

        if(FALSE == pFeetSpike->CSFlag.Bit.PositionResetOK)                          /*位置还未复位完成，如刚上电要查找初始位置*/
        {
          pFeetSpike->CSFlag.Bit.PositionResetOK = TRUE;                             /*位置复位完成*/
          pFeetSpike->PositionMonitor.PositionCountCur = FEETSPIKE_COUNT_MIN;        /*极限位置都要修正计数值*/
          pFeetSpike->PositionRealVal = FEETSPIKE_POSITION_MIN;
        }
        else  //if(TRUE == pFeetSpike->CSFlag.Bit.PositionResetOK)                   /*位置已经复位完成的*/
        {
          if((pFeetSpike->PositionSetVal > FEETSPIKE_POSITION_MIN) &&                /*要运动到中间的位置点*/
             (pFeetSpike->PositionSetVal < FEETSPIKE_POSITION_MAX) )
          {
            pFeetSpike->CSFlag.Bit.CountFault = TRUE;                                /*中间位置点出现计数停止的则表示计数传感器故障了*/
          }
          else if(FEETSPIKE_POSITION_MIN == pFeetSpike->PositionSetVal)              /*要运动到最小位置*/
          {
            if(pFeetSpike->PositionMonitor.PositionCountCur > FEETSPIKE_COUNT_PER_SEGMENT)
            {
              pFeetSpike->CSFlag.Bit.CountFault = TRUE;                              /*最小位置计数值不够小则表示计数传感器故障了*/
            }
            pFeetSpike->PositionMonitor.PositionCountCur = FEETSPIKE_COUNT_MIN;      /*极限位置都要修正计数值*/
          }
          else //if(FEETSPIKE_POSITION_MAX == pFeetSpike->PositionSetVal)            /*要运动到最大位置*/     
          {
            if(pFeetSpike->PositionMonitor.PositionCountCur < (FEETSPIKE_COUNT_MAX - FEETSPIKE_COUNT_PER_SEGMENT))
            {
              pFeetSpike->CSFlag.Bit.CountFault = TRUE;                              /*最大位置计数值不够大则表示计数传感器故障了*/
            }
            pFeetSpike->PositionMonitor.PositionCountCur = FEETSPIKE_COUNT_MAX;      /*极限位置都要修正计数值*/
          }
        }
      }  
      
      pFeetSpike->CSFlag.Bit.CountFault &= pFeetSpike->CSFlag.Bit.CountFaultCheckSw; /*检测开关无效的不告警*/
    }
    else //if(OFF == pFeetSpike->CSFlag.Bit.Run)                                     /*推杆没开*/
    {
      pFeetSpike->PositionMonitor.SensorLostTimeMs = 0;                              /*清零计数传感器失联时间*/
    }
  }
  else //if(pFeetSpike->PositionMonitor.PositionCountHis != pFeetSpike->PositionMonitor.PositionCountCur)   /*计数有变化*/
  {
    pFeetSpike->PositionMonitor.PositionCountHis = pFeetSpike->PositionMonitor.PositionCountCur;
    pFeetSpike->PositionMonitor.SensorLostTimeMs = 0;                                /*清零计数传感器失联时间*/
  }
  
  /*由计数值计算出当前的位置点---------------------------------------------------------------*/
  if(FEETSPIKE_COUNT_MIN == pFeetSpike->PositionMonitor.PositionCountCur)
  {
    if(ReachMinCountMs < 400)        /*给初始位置多留出400ms的校正时间*/
    {
      ReachMinCountMs += ExePeriod;
    }
    else
    {
      pFeetSpike->PositionRealVal          = FEETSPIKE_POSITION_MIN;
      pFeetSpike->CSFlag.Bit.ReachDownLimt = TRUE;                                     /*到达极限位置*/
      pFeetSpike->CSFlag.Bit.ReachUpLimt   = FALSE;                                
    }
  }
  else if(FEETSPIKE_COUNT_MAX == pFeetSpike->PositionMonitor.PositionCountCur)
  {
    ReachMinCountMs = 0;
    pFeetSpike->PositionRealVal          = FEETSPIKE_POSITION_MAX;
    pFeetSpike->CSFlag.Bit.ReachUpLimt   = TRUE;                                     /*到达极限位置*/
    pFeetSpike->CSFlag.Bit.ReachDownLimt = FALSE;                               
  }
  else
  {
    ReachMinCountMs = 0;
    pFeetSpike->CSFlag.Bit.ReachUpLimt   = FALSE;                                    /*不处于极限位置*/
    pFeetSpike->CSFlag.Bit.ReachDownLimt = FALSE;                                    /*不处于极限位置*/

    if(OFF == pFeetSpike->CSFlag.Bit.Run)
    {
      return;                                                                        /*马达运转时，才更新计算位置值*/
    }
    
    if(POSITION_COUNT_INC == pFeetSpike->PositionMonitor.CountDirection)             /*计数增加*/
    {
      pFeetSpike->PositionRealVal = pFeetSpike->PositionMonitor.PositionCountCur/FEETSPIKE_COUNT_PER_SEGMENT;
    }
    else //if(POSITION_COUNT_DEC == pFeetSpike->PositionMonitor.CountDirection)      /*计数减少*/
    {
      pFeetSpike->PositionRealVal = (pFeetSpike->PositionMonitor.PositionCountCur/FEETSPIKE_COUNT_PER_SEGMENT) + 1;
    }
  }
}

#endif  /* 结束if(FEETSPIKE_POSITION_DETECT_MODE == FEETSPIKE_POSITION_DETECT_BY_COUNT) */


/*
************************************************************************************************************************
* 函数名称 : FeetSpike_OverCurrentIOCheck                                                                                                         
* 功能描述 : 推杆过电流 IO口的检测                                                                               
* 输入参数 : ExePeriod -- 函数的执行周期                                                                                  
* 返回参数 : 无                                                                                             
* 补充说明 : 无                                                                                                       
************************************************************************************************************************
*/
void FeetSpike_OverCurrentIOCheck(Ticker_t ExePeriod)
{
  uint8_t IOCode;

  IOCode = BSP_IO_ReadInput_FeetSpikeOverCurrent(); 
  if(FEETSPIKE_OVER_CURRENT_LEVEL == IOCode)
  {
    if(pFeetSpike->OverCurrentTimeMs <= FEETSPIKE_OVER_CURRENT_TIME_THRESHOLD)
    {
      pFeetSpike->OverCurrentTimeMs += ExePeriod;
    }
    else
    {
      pFeetSpike->CSFlag.Bit.OverCurrentFault = FAULT; 
    }
  }
  else
  {
    pFeetSpike->OverCurrentTimeMs = 0;
  }
}


/*
************************************************************************************************************************
* 函数名称 : FeetSpike_PauseOn                                                                                                         
* 功能描述 : 暂停推杆                                                                            
* 输入参数 : 无                                                                                
* 返回参数 : 无                                                                                             
* 补充说明 : 如果马达正在运转，则会停止马达的运转。
*            只有解除暂停，马达才能重新运转。                                                                                                      
************************************************************************************************************************
*/
void FeetSpike_PauseOn(void)
{
  if(pFeetSpike->CSFlag.Bit.Pause < 0x1F)
  {
    pFeetSpike->CSFlag.Bit.Pause++;
  }
}

/*
************************************************************************************************************************
* 函数名称 : FeetSpike_PauseOff                                                                                                         
* 功能描述 : 解除暂停推杆                                                                        
* 输入参数 : 无                                                                                
* 返回参数 : 无                                                                                             
* 补充说明 : 如果马达正在运转，则会停止马达的运转。
*            只有解除暂停，马达才能重新运转。                                                                                                      
************************************************************************************************************************
*/
void FeetSpike_PauseOff(void)
{
  if(pFeetSpike->CSFlag.Bit.Pause > 0)
  {
    pFeetSpike->CSFlag.Bit.Pause--;
  }
}


/*
************************************************************************************************************************
* 函数名称 : FeetSpike_SetAction                                                                                                         
* 功能描述 : 设置推杆要执行的动作                                                                  
* 输入参数 : Action --> 动作需求，取值：
*                       FEETSPIKE_ACTION_UP
*                       FEETSPIKE_ACTION_DOWN
*                       FEETSPIKE_ACTION_STOP                                                                                
* 返回参数 : 无                                                                                             
* 补充说明 : 无                                                                                               
************************************************************************************************************************
*/
void FeetSpike_SetAction(uint8_t Action)
{
  if((Action != FEETSPIKE_ACTION_UP)   &&
     (Action != FEETSPIKE_ACTION_DOWN) &&
     (Action != FEETSPIKE_ACTION_STOP) )
  {
    Action = FEETSPIKE_ACTION_STOP;       /*动作参数无效，则执行停止动作*/
  }
  
  if((FEETSPIKE_ACTION_UP == Action) && (pFeetSpike->CSFlag.Bit.ReachUpLimt))
  {
    return;                               /*达到上限位不能再执行向上运动*/
  }
  
  if((FEETSPIKE_ACTION_DOWN == Action) && (pFeetSpike->CSFlag.Bit.ReachDownLimt))
  {
    return;                               /*达到下限位不能再执行向下运动*/
  }

  if(TRUE == pFeetSpike->CSFlag.Bit.Locked)  
  {
    return;                               /*马达被锁，不执行任何动作*/
  }

  if(Action != FEETSPIKE_ACTION_STOP) 
  {
    pFeetSpike->CSFlag.Bit.Work = TRUE;   /*动作有效，则开始工作*/
  }
  else
  {
    pFeetSpike->CSFlag.Bit.Work = FALSE;  /*动作无效效，则不工作*/
  }

  pFeetSpike->Action = Action;
}

/*
************************************************************************************************************************
* 函数名称 : FeetSpike_GetPosition                                                                                                         
* 功能描述 : 获取推杆位置                                                           
* 输入参数 : 无                                                                               
* 返回参数 : 推杆当前位置                                                                                            
* 补充说明 : 无                                                                                               
************************************************************************************************************************
*/
uint8_t FeetSpike_GetPosition(void)
{
  return pFeetSpike->PositionRealVal;
  //return  pFeetSpike->PositionSetVal; 
}

/*
************************************************************************************************************************
* 函数名称 : FeetSpike_SetPosition                                                                                                         
* 功能描述 : 设置推杆位置                                                         
* 输入参数 : Position --> 推杆 停靠位置
*                         特殊值：PKEEP          -- 保持当前位置不动。
*                                 大于最大坐标值 -- 运动到最大坐标。                                                                                
* 返回参数 : 无                                                                                       
* 补充说明 : 无                                                                                               
************************************************************************************************************************
*/
void FeetSpike_SetPosition(uint8_t Position)
{
  if((Position > FEETSPIKE_POSITION_MAX) &&(Position != PKEEP)) 
  {
    Position = FEETSPIKE_POSITION_MAX;
  }

  pFeetSpike->PositionSetVal = Position; 
}

/*
************************************************************************************************************************
* 函数名称 : FeetSpike_PositionHandle                                                                                                         
* 功能描述 : 推杆停靠位置处理                                                    
* 输入参数 : ExePeriod -- 函数的执行周期                                                                     
* 返回参数 : 无                                                                                      
* 补充说明 : 位置的计算，除非完全采用多位的IO二进制编码检测，
*            否则，只能使用  参考点  结合  当前脉冲计数或二进制编码来计算。
*            因此，在找到参考点以前，无法正确得知当前位置。                                                                                               
************************************************************************************************************************
*/
void FeetSpike_PositionHandle(Ticker_t ExePeriod)
{
  if(FALSE == pFeetSpike->CSFlag.Bit.PositionResetOK)                /*位置还没复位，即还没找到位置计算参考点*/
  {
    FeetSpike_SetAction(FEETSPIKE_ACTION_DOWN);
  }
  else                                                               /*位置已经复位，即位置计算参考点已确认*/
  {
    if(PKEEP == pFeetSpike->PositionSetVal)                          /*位置保持*/
    {
      FeetSpike_SetAction(FEETSPIKE_ACTION_STOP);
    }
    else                                                             /*调节位置*/
    {
      if(FEETSPIKE_POSITION_MIN == pFeetSpike->PositionSetVal)       /*极限位置 单独处理*/
      {
        if(FALSE == pFeetSpike->CSFlag.Bit.ReachDownLimt)
        {
          FeetSpike_SetAction(FEETSPIKE_ACTION_DOWN);
        }
        else
        {
          FeetSpike_SetAction(FEETSPIKE_ACTION_STOP);
        }
      }
      else if(FEETSPIKE_POSITION_MAX == pFeetSpike->PositionSetVal)  /*极限位置 单独处理*/
      {
        if(FALSE == pFeetSpike->CSFlag.Bit.ReachUpLimt)
        {
          FeetSpike_SetAction(FEETSPIKE_ACTION_UP);
        }
        else
        {
          FeetSpike_SetAction(FEETSPIKE_ACTION_STOP);
        }
      }
      else if(pFeetSpike->PositionSetVal == pFeetSpike->PositionRealVal)
      {
        FeetSpike_SetAction(FEETSPIKE_ACTION_STOP);
      }
      else if(pFeetSpike->PositionSetVal > pFeetSpike->PositionRealVal)
      {
        FeetSpike_SetAction(FEETSPIKE_ACTION_UP);
      }
      else //(pFeetSpike->PositionSetVal < pFeetSpike->PositionRealVal)
      {
        FeetSpike_SetAction(FEETSPIKE_ACTION_DOWN);
      }
    }
  }
}


/*
************************************************************************************************************************
* 函数名称 : FeetSpike_ActionHandle                                                                                                         
* 功能描述 : 马达动作处理                                           
* 输入参数 : ExePeriod -- 函数的执行周期                                                                     
* 返回参数 : 无                                                                                      
* 补充说明 : 无                                                                                             
************************************************************************************************************************
*/
void FeetSpike_ActionHandle(Ticker_t ExePeriod)
{
  static uint8_t     ActionHis = 0xFF;                                    /*历史动作状态*/


  /*动作状态的改变判断------------------------------------*/
  if(ActionHis != pFeetSpike->Action)
  {
    pFeetSpike->CSFlag.Bit.Run = OFF;                                     /*动作改变，都先停止电机*/
    if(ActionHis != FEETSPIKE_ACTION_STOP)
    {
      pFeetSpike->StateCtrlTimeMs = 0;                                    /*上<-->下 ， 上/下-->停止，则清零时间*/
    }
    ActionHis = pFeetSpike->Action;
  }

  do
  {
    /*暂停则停止电机-----------------------------------------*/
    if(pFeetSpike->CSFlag.Bit.Pause > 0)
    {
      pFeetSpike->CSFlag.Bit.Run = OFF;
      pFeetSpike->PWMFinalSetVal = FEETSPIKE_PWM_MIN;    /*暂停后的重新启动也需要慢启动*/
     break;
    }

    /* 发生异常，则停止马达-------------------------------------*/
    if((FAULT == pFeetSpike->CSFlag.Bit.PositionCodeFault)   ||           /*位置编码故障*/
       (FAULT == pFeetSpike->CSFlag.Bit.PositionSensorFault) ||           /*位置传感器故障*/
       (FAULT == pFeetSpike->CSFlag.Bit.CountFault)          ||           /*计数故障*/
       (FAULT == pFeetSpike->CSFlag.Bit.OverCurrentFault)    )            /*过电流故障*/
    {
      pFeetSpike->CSFlag.Bit.Locked = TRUE;                               /*异常则上锁马达*/
      pFeetSpike->CSFlag.Bit.Run    = OFF;                                /*异常则停马达*/
      pFeetSpike->CSFlag.Bit.Work   = FALSE;  
      pFeetSpike->StateCtrlTimeMs = 0;
      break;
    }

    /*马达驱动--------------------------------------------------*/
    if(pFeetSpike->Action != FEETSPIKE_ACTION_STOP)
    {
      if(pFeetSpike->StateCtrlTimeMs < 5000)
      {
        pFeetSpike->StateCtrlTimeMs += ExePeriod; 
      }

      if(pFeetSpike->StateCtrlTimeMs <= FEETSPIKE_DIRECTION_TIME_MS)      /*先关电机-----------*/
      {
        pFeetSpike->CSFlag.Bit.Run = OFF;
        pFeetSpike->PWMFinalSetVal = 0;                   /*慢启动*/
      }
      else if(pFeetSpike->StateCtrlTimeMs <= FEETSPIKE_REVERSE_TIME_MS)   /*切换方向------------*/
      {
        if(FEETSPIKE_ACTION_UP == pFeetSpike->Action)
        {
          pFeetSpike->UpRunTimeMs                    = 0; 
          pFeetSpike->CSFlag.Bit.Direction           = FEETSPIKE_DIRECTION_UP;
          pFeetSpike->PositionMonitor.CountDirection = POSITION_COUNT_INC;
        }
        else //if(FEETSPIKE_ACTION_DOWN == pFeetSpike->Action)
        {
          pFeetSpike->DownRunTimeMs                  = 0; 
          pFeetSpike->CSFlag.Bit.Direction           = FEETSPIKE_DIRECTION_DOWN;
          pFeetSpike->PositionMonitor.CountDirection = POSITION_COUNT_DEC;
        }
        pFeetSpike->PWMFinalSetVal = FEETSPIKE_PWM_MIN;     /*慢启动*/
      }
      else /*马达运转---------------------------------------------------------------------------*/
      {
        pFeetSpike->CSFlag.Bit.Run = ON;
        if(pFeetSpike->PWMFinalSetVal < FEETSPIKE_PWM_MAX)  /*慢启动*/
        {
          pFeetSpike->PWMFinalSetVal += FEETSPIKE_PWM_FIXED_STEPING_VAL;
        }
        else
        {
          pFeetSpike->PWMFinalSetVal = FEETSPIKE_PWM_MAX;
        }

        if(FEETSPIKE_ACTION_UP == pFeetSpike->Action)
        {
          if(pFeetSpike->UpRunTimeMs < (0xFFFF-ExePeriod))                /*-ExePeriod :防止加操作溢出*/
          {
            pFeetSpike->UpRunTimeMs += ExePeriod; 
          }
        }
        else //if(FEETSPIKE_ACTION_DOWN == pFeetSpike->Action)
        {
          if(pFeetSpike->DownRunTimeMs < (0xFFFF-ExePeriod))              /*-ExePeriod :防止加操作溢出*/
          {
            pFeetSpike->DownRunTimeMs += ExePeriod; 
          }
        }

        pFeetSpike->RunTimeMs += ExePeriod;                               /*统计马达运转时间*/
      }
    }
    else /*pFeetSpike->Action == FEETSPIKE_ACTION_STOP*/
    {
      pFeetSpike->CSFlag.Bit.Run = OFF;
      if(pFeetSpike->StateCtrlTimeMs < FEETSPIKE_DIRECTION_TIME_MS)       /*停止时，可累计停止时间，要启动时，可加快启动*/
      {
        pFeetSpike->StateCtrlTimeMs += ExePeriod; 
      }
    }
  }while(0);

  BSP_IO_SetOutput_FeetSpikeCtrl(pFeetSpike->CSFlag.Bit.Run, pFeetSpike->CSFlag.Bit.Direction, pFeetSpike->PWMFinalSetVal);
}


/*
************************************************************************************************************************
* 函数名称 : FeetSpike_Init                                                                                                         
* 功能描述 : 推杆初始化                                   
* 输入参数 : 无                                                             
* 返回参数 : 无                                                                                      
* 补充说明 : 无                                                                                             
************************************************************************************************************************
*/
FeetSpike_t* FeetSpike_Init(void)
{
  memset(pFeetSpike, 0, sizeof(FeetSpike_t));                                 /*清零所有数据*/
  FeetSpike_ResetPosition();
  #if (FEETSPIKE_POSITION_DETECT_MODE == FEETSPIKE_POSITION_DETECT_BY_COUNT)  /*位置检测使用计数方式*/
    BSP_IO_InputInterrupt_RegCB_FeetSpikeCount(FeetSpike_CountIOCheck_CB);    
  #endif
  
  return pFeetSpike;
}


/*
************************************************************************************************************************
* 函数名称 : FeetSpike_GetCSFlag                                                                                                         
* 功能描述 : 获得 控制 与 状态 标识                                   
* 输入参数 : 无                                                             
* 返回参数 : 无                                                                                      
* 补充说明 : 无                                                                                             
************************************************************************************************************************
*/
FeetSpikeCSFlag_t FeetSpike_GetCSFlag(void)
{
  return pFeetSpike->CSFlag;
}


/*
************************************************************************************************************************
* 函数名称 : FeetSpike_ResetPosition                                                                                                         
* 功能描述 : 复位位置                                   
* 输入参数 : 无                                                             
* 返回参数 : 无                                                                                      
* 补充说明 : 无                                                                                             
************************************************************************************************************************
*/
void FeetSpike_ResetPosition(void)
{
  pFeetSpike->CSFlag.Bit.PositionResetOK = FALSE;
  pFeetSpike->PositionSetVal                   = FEETSPIKE_POSITION_MIN;    /*要使用的参考位置*/
  pFeetSpike->PositionRealVal                  = FEETSPIKE_POSITION_MAX;    /*假设的当前位置*/   
  pFeetSpike->PositionMonitor.PositionCountCur = FEETSPIKE_COUNT_MAX*2;     /*假设的当前位置计数*/ 
}

/*
************************************************************************************************************************
* 函数名称 : FeetSpike_SetCountFaultCheckSw                                                                                                          
* 功能描述 : 设置计数故障检测开关                                  
* 输入参数 : Sw -- ON  开
*                  OFF 关
* 返回参数 : 无                                                                                      
* 补充说明 : 无                                                                                             
************************************************************************************************************************
*/
void FeetSpike_SetCountFaultCheckSw(uint8_t Sw)
{
  if((Sw != ON) && (Sw != OFF))
  {
    Sw = OFF;
  }
  pFeetSpike->CSFlag.Bit.CountFaultCheckSw = Sw;
}

