/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: ZeroSpike.c                                                                                                         
**
**    功能描述:	零重力推杆驱动。
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
#include "ZeroSpike.h"


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
static void ZeroSpike_SetAction(uint8_t Action);


static ZeroSpike_t ZeroSpike;
ZeroSpike_t *pZeroSpike = &ZeroSpike;


#if (ZEROSPIKE_POSITION_DETECT_MODE == ZEROSPIKE_POSITION_DETECT_BY_CODE) /*位置检测使用码盘编码方式*/
/*
* 推杆位置点，码盘编码表
*
* 零重力推杆使用了完全的2位二进制编码 
* 使用位置编码的跳变来确定位置。
* 最底和最顶的位置还应使用编码（最底00  最顶10）来确定。
*
* 码盘编码表(透光 1  遮挡 0)：
*  B(00)   //最底 
*  B(01),  //
*  B(11),  //
*  B(10)   //最顶 
*/
static const PositionCodeMap_t ZeroSpike_PositionCodeMapTab[] =
{
  {B(00), B(01), ZEROSPIKE_POSITION_MAX},  
  {B(01), B(11), 1},
  {B(11), B(10), ZEROSPIKE_POSITION_MIN}
};

#define  ZEROSPIKE_POSITION_CODE_MAPTAB_NUM   TAB_NUM(ZeroSpike_PositionCodeMapTab)

#endif /*结束 #if(ZEROSPIKE_POSITION_DETECT_MODE == ZEROSPIKE_POSITION_DETECT_BY_CODE)*/




/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/

#if (ZEROSPIKE_POSITION_DETECT_MODE == ZEROSPIKE_POSITION_DETECT_BY_CODE) /*位置检测使用码盘编码方式*/
/*
************************************************************************************************************************
* 函数名称 : ZeroSpike_PositionCodeMap                                                                                                         
* 功能描述 : 推杆位置 编码 映射                                                                                                     
* 输入参数 : CodeCur -- 当前位置编码                                                                                                      
* 返回参数 : 大于 ZEROSPIKE_POSITION_MAX       -- 无效的编码，位置存在问题。
*            小于或等于ZEROSPIKE_POSITION_MAX  -- 位置编码有效                                                                                                        
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t ZeroSpike_PositionCodeMap(uint8_t CodeCur)
{
  uint8_t i;
  uint8_t Position;
  static uint8_t CodeHis = 0xFF;


  Position = pZeroSpike->PositionRealVal;            /*先假设位置没改变，以下代码将根据情况改变Position的赋值*/

  /*最底和最顶的位置， 优先使用位置编码来确定*/
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

  /*使用编码跳变来确定位置*/
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

    pZeroSpike->CSFlag.Bit.ReachUpLimt   = FALSE;    /*编码不处于极限位置，清除极限标识*/
    pZeroSpike->CSFlag.Bit.ReachDownLimt = FALSE;
  }
  else
  {
    //Position = pZeroSpike->PositionRealVal; /*没发生跳变，则保持原位置*/
    pZeroSpike->CSFlag.Bit.ReachUpLimt   = FALSE;    /*编码不处于极限位置，清除极限标识*/
    pZeroSpike->CSFlag.Bit.ReachDownLimt = FALSE;
  }

  CodeHis = CodeCur;
  return Position; 
}

/*
************************************************************************************************************************
* 函数名称 : ZeroSpike_PositionIOCheck                                                                                                         
* 功能描述 : 位置 IO口的检测                                                                                            
* 输入参数 : ExePeriod -- 函数的执行周期                                                                                                 
* 返回参数 : 无                                                                                             
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void ZeroSpike_PositionIOCheck(Ticker_t ExePeriod)
{
  static uint8_t StableIOCode;                                      /*稳定的编码*/
  static uint8_t StableStat;                                        /*状态稳定统计*/
  static uint8_t IOCode = B(00);                                    /*要复位到顶，先假设初始为最底端*/

  /*有时会有干扰，因此这里做状态稳定的判断------------------------*/
  if(StableIOCode != (BSP_IO_ReadInput_ZeroSpikePosition() & B(11)))
  {
    StableStat = 0;                                                 /*发生变化则表示不稳定*/
    StableIOCode = BSP_IO_ReadInput_ZeroSpikePosition() & B(11);    /*读码盘*/
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
  if(pZeroSpike->PositionMonitor.PositionCode == IOCode)            /*位置没改变*/
  {
    if(ON == pZeroSpike->CSFlag.Bit.Run)                            /*马达在运行时，累加传感器失联时间*/
    {
      if(pZeroSpike->PositionMonitor.SensorLostTimeMs <= ZEROSPIKE_POSITION_SENSOR_LOST_TIME_THRESHOLD) /*未超过失联门限时间*/
      {
        pZeroSpike->PositionMonitor.SensorLostTimeMs += ExePeriod;
      }
      else
      {
        pZeroSpike->CSFlag.Bit.PositionSensorFault = FAULT;         /*位置传感器故障，出现后，程序不会清零，靠复位或重上电才清零*/
      }
    }
    else
    {
      pZeroSpike->PositionMonitor.SensorLostTimeMs = 0;             /*清零传感器失联时间*/
    }
  }
  else  /*位置改变*/
  { 
    pZeroSpike->PositionMonitor.SensorLostTimeMs = 0;	              /*清零传感器失联时间*/
  }


  /*位置相关变量判断与更新--------------------------------------------*/
  pZeroSpike->PositionRealVal = ZeroSpike_PositionCodeMap(IOCode);
  if(ZEROSPIKE_POSITION_MIN == pZeroSpike->PositionRealVal)       /*最顶位置*/
  {
    pZeroSpike->CSFlag.Bit.PositionResetOK = TRUE;                /*位置复位完成*/
  }

  if((ZEROSPIKE_ACTION_UP == pZeroSpike->Action) && (pZeroSpike->CSFlag.Bit.ReachUpLimt))
  {
    ZeroSpike_SetAction(ZEROSPIKE_ACTION_STOP);                     /*达到上限位不能再执行向上运动*/
  }

  if((ZEROSPIKE_ACTION_DOWN == pZeroSpike->Action) && (pZeroSpike->CSFlag.Bit.ReachDownLimt))
  {
    ZeroSpike_SetAction(ZEROSPIKE_ACTION_STOP);                     /*达到下限位不能再执行向下运动*/
  }

  pZeroSpike->PositionMonitor.PositionCode = IOCode;                /*记录新编码*/
}

#endif /*结束 #if(ZEROSPIKE_POSITION_DETECT_MODE == ZEROSPIKE_POSITION_DETECT_BY_CODE)*/



#if (ZEROSPIKE_POSITION_DETECT_MODE == ZEROSPIKE_POSITION_DETECT_BY_COUNT) /*位置检测使用计数方式*/
/*
************************************************************************************************************************
* 函数名称 : ZeroSpike_CountIOCheck_CB                                                                                                         
* 功能描述 : 位置 计数IO口检测  的回调函数                                                                                           
* 输入参数 : 无                                                                                    
* 返回参数 : 无                                                                                             
* 补充说明 : 该函数通过 BSP_IO_InputInterrupt_RegCB_ZeroSpikeCount(ZeroSpike_CountIOCheck_CB);向下注册给BSP层                                                                                                         
************************************************************************************************************************
*/
static void ZeroSpike_CountIOCheck_CB(void)
{
  /*_COUNT_MIN+3：由于误差，经常会推杆停的时候，计数值还大于0，这里加快到0的处理*/
  MotorCountUpdata(&pZeroSpike->PositionMonitor.PositionCountCur, 
                   pZeroSpike->PositionMonitor.CountDirection, 
                   ZEROSPIKE_COUNT_MAX, ZEROSPIKE_COUNT_MIN+3);
}

/*
************************************************************************************************************************
* 函数名称 : ZeroSpike_PositionIOCheck                                                                                                         
* 功能描述 : 位置 IO口的检测                                                                                   
* 输入参数 : ExePeriod -- 函数的执行周期                                                                                  
* 返回参数 : 无                                                                                             
* 补充说明 : 无                                                                                                       
************************************************************************************************************************
*/
void ZeroSpike_PositionIOCheck(Ticker_t ExePeriod)
{
  static  Ticker_t ReachMinCountMs;

  /*计数传感器故障检测---------------------------------------------*/
  if(pZeroSpike->PositionMonitor.PositionCountHis == pZeroSpike->PositionMonitor.PositionCountCur)  /*计数无变化*/
  {
    if(ON == pZeroSpike->CSFlag.Bit.Run)                                             /*推杆开启*/
    {
      if(pZeroSpike->PositionMonitor.SensorLostTimeMs <= ZEROSPIKE_COUNT_SENSOR_LOST_TIME_THRESHOLD)
      {
        pZeroSpike->PositionMonitor.SensorLostTimeMs += ExePeriod;                   /*马达在运行时，累加计数传感器失联时间*/
      }
      else
      {
        ZeroSpike_SetAction(ZEROSPIKE_ACTION_STOP);                                  /*计数一旦停止，便停止马达运动*/

        if(FALSE == pZeroSpike->CSFlag.Bit.PositionResetOK)                          /*位置还未复位完成，如刚上电要查找初始位置*/
        {
          pZeroSpike->CSFlag.Bit.PositionResetOK = TRUE;                             /*位置复位完成*/
          pZeroSpike->PositionMonitor.PositionCountCur = ZEROSPIKE_COUNT_MIN;        /*极限位置都要修正计数值*/
          pZeroSpike->PositionRealVal = ZEROSPIKE_POSITION_MIN;
        }
        else  //if(TRUE == pZeroSpike->CSFlag.Bit.PositionResetOK)                   /*位置已经复位完成的*/
        {
          if((pZeroSpike->PositionSetVal > ZEROSPIKE_POSITION_MIN) &&                /*要运动到中间的位置点*/
             (pZeroSpike->PositionSetVal < ZEROSPIKE_POSITION_MAX) )
          {
            pZeroSpike->CSFlag.Bit.CountFault = TRUE;                                /*中间位置点出现计数停止的则表示计数传感器故障了*/
          }
          else if(ZEROSPIKE_POSITION_MIN == pZeroSpike->PositionSetVal)              /*要运动到最小位置*/
          {
            if(pZeroSpike->PositionMonitor.PositionCountCur > ZEROSPIKE_COUNT_PER_SEGMENT)
            {
              pZeroSpike->CSFlag.Bit.CountFault = TRUE;                              /*最小位置计数值不够小则表示计数传感器故障了*/
            }
            pZeroSpike->PositionMonitor.PositionCountCur = ZEROSPIKE_COUNT_MIN;      /*极限位置都要修正计数值*/
          }
          else //if(ZEROSPIKE_POSITION_MAX == pZeroSpike->PositionSetVal)            /*要运动到最大位置*/     
          {
            if(pZeroSpike->PositionMonitor.PositionCountCur < (ZEROSPIKE_COUNT_MAX - ZEROSPIKE_COUNT_PER_SEGMENT))
            {
              pZeroSpike->CSFlag.Bit.CountFault = TRUE;                              /*最大位置计数值不够大则表示计数传感器故障了*/
            }
            pZeroSpike->PositionMonitor.PositionCountCur = ZEROSPIKE_COUNT_MAX;      /*极限位置都要修正计数值*/
          }
        }
      }  
      
      pZeroSpike->CSFlag.Bit.CountFault &= pZeroSpike->CSFlag.Bit.CountFaultCheckSw; /*检测开关无效的不告警*/
    }
    else //if(OFF == pZeroSpike->CSFlag.Bit.Run)                                     /*推杆没开*/
    {
      pZeroSpike->PositionMonitor.SensorLostTimeMs = 0;                              /*清零计数传感器失联时间*/
    }
  }
  else //if(pZeroSpike->PositionMonitor.PositionCountHis != pZeroSpike->PositionMonitor.PositionCountCur)   /*计数有变化*/
  {
    pZeroSpike->PositionMonitor.PositionCountHis = pZeroSpike->PositionMonitor.PositionCountCur;
    pZeroSpike->PositionMonitor.SensorLostTimeMs = 0;                                /*清零计数传感器失联时间*/
  }
  
  /*由计数值计算出当前的位置点---------------------------------------------------------------*/
  if(ZEROSPIKE_COUNT_MIN == pZeroSpike->PositionMonitor.PositionCountCur)
  {
    if(ReachMinCountMs < 400)        /*给初始位置多留出400ms的校正时间*/
    {
      ReachMinCountMs += ExePeriod;
    }
    else
    {
      pZeroSpike->PositionRealVal          = ZEROSPIKE_POSITION_MIN;
      pZeroSpike->CSFlag.Bit.ReachDownLimt = TRUE;                                     /*到达极限位置*/
      pZeroSpike->CSFlag.Bit.ReachUpLimt   = FALSE;                               
    }
  }
  else if(ZEROSPIKE_COUNT_MAX == pZeroSpike->PositionMonitor.PositionCountCur)
  {
    ReachMinCountMs = 0;
    pZeroSpike->PositionRealVal          = ZEROSPIKE_POSITION_MAX;
    pZeroSpike->CSFlag.Bit.ReachUpLimt   = TRUE;                                     /*到达极限位置*/
    pZeroSpike->CSFlag.Bit.ReachDownLimt = FALSE;                              
  }
  else
  {
    ReachMinCountMs = 0;
    pZeroSpike->CSFlag.Bit.ReachUpLimt   = FALSE;                                    /*不处于极限位置*/
    pZeroSpike->CSFlag.Bit.ReachDownLimt = FALSE;                                    /*不处于极限位置*/

    if(OFF == pZeroSpike->CSFlag.Bit.Run)
    {
      return;                                                                        /*马达运转时，才更新计算位置值*/
    }


    if(POSITION_COUNT_INC == pZeroSpike->PositionMonitor.CountDirection)             /*计数增加*/
    {
      pZeroSpike->PositionRealVal = pZeroSpike->PositionMonitor.PositionCountCur/ZEROSPIKE_COUNT_PER_SEGMENT;
    }
    else //if(POSITION_COUNT_DEC == pZeroSpike->PositionMonitor.CountDirection)      /*计数减少*/
    {
      pZeroSpike->PositionRealVal = (pZeroSpike->PositionMonitor.PositionCountCur/ZEROSPIKE_COUNT_PER_SEGMENT) + 1;
    }
  }
}

#endif  /* 结束if(ZEROSPIKE_POSITION_DETECT_MODE == ZEROSPIKE_POSITION_DETECT_BY_COUNT) */


/*
************************************************************************************************************************
* 函数名称 : ZeroSpike_OverCurrentIOCheck                                                                                                         
* 功能描述 : 推杆过电流 IO口的检测                                                                               
* 输入参数 : ExePeriod -- 函数的执行周期                                                                                  
* 返回参数 : 无                                                                                             
* 补充说明 : 无                                                                                                       
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
* 函数名称 : ZeroSpike_PauseOn                                                                                                         
* 功能描述 : 暂停推杆                                                                            
* 输入参数 : 无                                                                                
* 返回参数 : 无                                                                                             
* 补充说明 : 如果马达正在运转，则会停止马达的运转。
*            只有解除暂停，马达才能重新运转。                                                                                                      
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
* 函数名称 : ZeroSpike_PauseOff                                                                                                         
* 功能描述 : 解除暂停推杆                                                                        
* 输入参数 : 无                                                                                
* 返回参数 : 无                                                                                             
* 补充说明 : 如果马达正在运转，则会停止马达的运转。
*            只有解除暂停，马达才能重新运转。                                                                                                      
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
* 函数名称 : ZeroSpike_SetAction                                                                                                         
* 功能描述 : 设置推杆要执行的动作                                                                  
* 输入参数 : Action --> 动作需求，取值：
*                       ZEROSPIKE_ACTION_UP
*                       ZEROSPIKE_ACTION_DOWN
*                       ZEROSPIKE_ACTION_STOP                                                                                
* 返回参数 : 无                                                                                             
* 补充说明 : 无                                                                                               
************************************************************************************************************************
*/
void ZeroSpike_SetAction(uint8_t Action)
{
  if((Action != ZEROSPIKE_ACTION_UP)   &&
     (Action != ZEROSPIKE_ACTION_DOWN) &&
     (Action != ZEROSPIKE_ACTION_STOP) )
  {
    Action = ZEROSPIKE_ACTION_STOP;       /*动作参数无效，则执行停止动作*/
  }
  
  if((ZEROSPIKE_ACTION_UP == Action) && (pZeroSpike->CSFlag.Bit.ReachUpLimt))
  {
    return;                               /*达到上限位不能再执行向上运动*/
  }
  
  if((ZEROSPIKE_ACTION_DOWN == Action) && (pZeroSpike->CSFlag.Bit.ReachDownLimt))
  {
    return;                               /*达到下限位不能再执行向下运动*/
  }

  if(TRUE == pZeroSpike->CSFlag.Bit.Locked)  
  {
    return;                               /*马达被锁，不执行任何动作*/
  }

  if(Action != ZEROSPIKE_ACTION_STOP) 
  {
    pZeroSpike->CSFlag.Bit.Work = TRUE;   /*动作有效，则开始工作*/
  }
  else
  {
    pZeroSpike->CSFlag.Bit.Work = FALSE;  /*动作无效效，则不工作*/
  }

  pZeroSpike->Action = Action;
}

/*
************************************************************************************************************************
* 函数名称 : ZeroSpike_GetPosition                                                                                                         
* 功能描述 : 获取推杆位置                                                           
* 输入参数 : 无                                                                               
* 返回参数 : 推杆当前位置                                                                                            
* 补充说明 : 无                                                                                               
************************************************************************************************************************
*/
uint8_t ZeroSpike_GetPosition(void)
{
  return pZeroSpike->PositionRealVal;
}

/*
************************************************************************************************************************
* 函数名称 : ZeroSpike_SetPosition                                                                                                         
* 功能描述 : 设置推杆位置                                                         
* 输入参数 : Position --> 推杆 停靠位置
*                         特殊值：PKEEP          -- 保持当前位置不动。
*                                 大于最大坐标值 -- 运动到最大坐标。                                                                                
* 返回参数 : 无                                                                                       
* 补充说明 : 无                                                                                               
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
* 函数名称 : ZeroSpike_PositionHandle                                                                                                         
* 功能描述 : 推杆停靠位置处理                                                    
* 输入参数 : ExePeriod -- 函数的执行周期                                                                     
* 返回参数 : 无                                                                                      
* 补充说明 : 位置的计算，除非完全采用多位的IO二进制编码检测，
*            否则，只能使用  参考点  结合  当前脉冲计数或二进制编码来计算。
*            因此，在找到参考点以前，无法正确得知当前位置。                                                                                               
************************************************************************************************************************
*/
void ZeroSpike_PositionHandle(Ticker_t ExePeriod)
{
  if(FALSE == pZeroSpike->CSFlag.Bit.PositionResetOK)                /*位置还没复位，即还没找到位置计算参考点*/
  {
    ZeroSpike_SetAction(ZEROSPIKE_ACTION_DOWN);
  }
  else //if(TRUE == pZeroSpike->CSFlag.Bit.PositionResetOK)          /*位置已经复位，即位置计算参考点已确认*/
  {
    if(PKEEP == pZeroSpike->PositionSetVal)                          /*位置保持*/
    {
      ZeroSpike_SetAction(ZEROSPIKE_ACTION_STOP);
    }
    else                                                             /*调节位置*/
    {
      if(ZEROSPIKE_POSITION_MAX == pZeroSpike->PositionSetVal)       /*极限位置 单独处理*/
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
      else if(ZEROSPIKE_POSITION_MIN == pZeroSpike->PositionSetVal)  /*极限位置 单独处理*/
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
* 函数名称 : ZeroSpike_ActionHandle                                                                                                         
* 功能描述 : 马达动作处理                                           
* 输入参数 : ExePeriod -- 函数的执行周期                                                                     
* 返回参数 : 无                                                                                      
* 补充说明 : 无                                                                                             
************************************************************************************************************************
*/
void ZeroSpike_ActionHandle(Ticker_t ExePeriod)
{
  static uint8_t   ActionHis = 0xFF;                                      /*历史动作状态*/


  /*动作状态的改变判断------------------------------------*/
  if(ActionHis != pZeroSpike->Action)
  {
    pZeroSpike->CSFlag.Bit.Run = OFF;                                     /*动作改变，都先停止电机*/
    if(ActionHis != ZEROSPIKE_ACTION_STOP)
    {
      pZeroSpike->StateCtrlTimeMs = 0;                                    /*上<-->下 ， 上/下-->停止，则清零时间*/
    }
    ActionHis = pZeroSpike->Action;
  }

  do
  {
    /*暂停则停止电机-----------------------------------------*/
    if(pZeroSpike->CSFlag.Bit.Pause > 0)
    {
      pZeroSpike->CSFlag.Bit.Run    = OFF;	  
      break;
    }

    /* 发生异常，则停止马达-------------------------------------*/
    if((FAULT == pZeroSpike->CSFlag.Bit.PositionCodeFault)   ||           /*位置编码故障*/
       (FAULT == pZeroSpike->CSFlag.Bit.PositionSensorFault) ||           /*位置传感器故障*/
       (FAULT == pZeroSpike->CSFlag.Bit.CountFault)          ||           /*计数故障*/
       (FAULT == pZeroSpike->CSFlag.Bit.OverCurrentFault)    )            /*过电流故障*/
    {
      pZeroSpike->CSFlag.Bit.Locked = TRUE;	                              /*异常则上锁马达*/
      pZeroSpike->CSFlag.Bit.Run    = OFF;	                              /*异常则停马达*/
      pZeroSpike->CSFlag.Bit.Work   = FALSE;	  
      pZeroSpike->StateCtrlTimeMs = 0;
      break;
    }

    /*马达驱动--------------------------------------------------*/
    if(pZeroSpike->Action != ZEROSPIKE_ACTION_STOP)
    {
      if(pZeroSpike->StateCtrlTimeMs < 5000)
      {
        pZeroSpike->StateCtrlTimeMs += ExePeriod; 
      }

      if(pZeroSpike->StateCtrlTimeMs <= ZEROSPIKE_DIRECTION_TIME_MS)	    /*先关电机------------*/
      {
        pZeroSpike->CSFlag.Bit.Run = OFF;
      }
      else if(pZeroSpike->StateCtrlTimeMs <= ZEROSPIKE_REVERSE_TIME_MS)   /*切换方向------------*/
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
      else /*马达运转---------------------------------------------------------------------------*/
      {
        pZeroSpike->CSFlag.Bit.Run = ON;

        if(ZEROSPIKE_ACTION_UP == pZeroSpike->Action)
        {
          if(pZeroSpike->UpRunTimeMs < (0xFFFF-ExePeriod))                /*-ExePeriod :防止加操作溢出*/
          {
            pZeroSpike->UpRunTimeMs += ExePeriod; 
          }
        }
        else //if(ZEROSPIKE_ACTION_DOWN == pZeroSpike->Action)
        {
          if(pZeroSpike->DownRunTimeMs < (0xFFFF-ExePeriod))              /*-ExePeriod :防止加操作溢出*/
          {
            pZeroSpike->DownRunTimeMs += ExePeriod; 
          }
        }

        pZeroSpike->RunTimeMs += ExePeriod;                               /*统计马达运转时间*/
      }
    }
    else	/*pZeroSpike->Action == ZEROSPIKE_ACTION_STOP*/
    {
      pZeroSpike->CSFlag.Bit.Run = OFF;

      if(pZeroSpike->StateCtrlTimeMs < ZEROSPIKE_DIRECTION_TIME_MS)       /*停止时，可累计停止时间，要启动时，可加快启动*/
      {
        pZeroSpike->StateCtrlTimeMs += ExePeriod; 
      }
    }
  }while(0);

  BSP_IO_SetOutput_ZeroSpikeCtrl(pZeroSpike->CSFlag.Bit.Run, pZeroSpike->CSFlag.Bit.Direction, 0);
}



/*
************************************************************************************************************************
* 函数名称 : ZeroSpike_Init                                                                                                         
* 功能描述 : 推杆初始化                                   
* 输入参数 : 无                                                             
* 返回参数 : 无                                                                                      
* 补充说明 : 无                                                                                             
************************************************************************************************************************
*/
ZeroSpike_t* ZeroSpike_Init(void)
{
  memset(pZeroSpike, 0, sizeof(ZeroSpike_t));                                 /*清零所有数据*/
  ZeroSpike_ResetPosition();
  #if (ZEROSPIKE_POSITION_DETECT_MODE == ZEROSPIKE_POSITION_DETECT_BY_COUNT)  /*位置检测使用计数方式*/
    BSP_IO_InputInterrupt_RegCB_ZeroSpikeCount(ZeroSpike_CountIOCheck_CB);    
  #endif
  
  return pZeroSpike;
}


/*
************************************************************************************************************************
* 函数名称 : ZeroSpike_GetCSFlag                                                                                                         
* 功能描述 : 获得 控制 与 状态 标识                                   
* 输入参数 : 无                                                             
* 返回参数 : 控制与状态标识 的结构体                                                                                      
* 补充说明 : 无                                                                                             
************************************************************************************************************************
*/
ZeroSpikeCSFlag_t ZeroSpike_GetCSFlag(void)
{
  return pZeroSpike->CSFlag;
}


/*
************************************************************************************************************************
* 函数名称 : ZeroSpike_ResetPosition                                                                                                         
* 功能描述 : 复位位置                                   
* 输入参数 : 无                                                             
* 返回参数 : 无                                                                                      
* 补充说明 : 无                                                                                             
************************************************************************************************************************
*/
void ZeroSpike_ResetPosition(void)
{
  pZeroSpike->CSFlag.Bit.PositionResetOK = FALSE;
  pZeroSpike->PositionSetVal                   = ZEROSPIKE_POSITION_MIN;    /*要使用的参考位置*/
  pZeroSpike->PositionRealVal                  = ZEROSPIKE_POSITION_MAX;    /*假设的当前位置*/ 
  pZeroSpike->PositionMonitor.PositionCountCur = ZEROSPIKE_COUNT_MAX*2;     /*假设的当前位置计数*/ 
}

/*
************************************************************************************************************************
* 函数名称 : ZeroSpike_SetCountFaultCheckSw                                                                                                          
* 功能描述 : 设置计数故障检测开关                                  
* 输入参数 : Sw -- ON  开
*                  OFF 关
* 返回参数 : 无                                                                                      
* 补充说明 : 无                                                                                             
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

