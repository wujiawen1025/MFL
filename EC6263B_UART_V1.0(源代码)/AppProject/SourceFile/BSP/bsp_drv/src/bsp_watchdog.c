/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称:                                                                                                         
**
**    功能描述:                                                                                                        
**
**    公    司:                                                                                                         
**
**    项目名称:                                                                                                         
**
**    平台信息:                                                                                                       
**
**    作    者: Hzy                                                                                                     
**
**    其他说明:                                                                                                        
**
**    修改记录:  
**
========================================================================================================================
========================================================================================================================
*/

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp_watchdog.h"          



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
************************************************************************************************************************
* 类型定义 :                                                                                                   
************************************************************************************************************************
*/


/*
========================================================================================================================
*【变量定义 & 各种声明】                          【变量定义 & 各种声明】                          【变量定义 & 各种声明】    
========================================================================================================================
*/


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/

void drv_fwdgt_init(uint16_t ms)
{
  float count = ms * 40 / 64;
  /* confiure FWDGT counter clock: 40KHz(IRC40K) / 64 = 0.625 KHz */
  fwdgt_config((uint16_t)count, FWDGT_PSC_DIV64);
  /* enable write access to FWDGT_PSC and FWDGT_RLD */
  fwdgt_write_enable();
  /* After [ms] ms to generate a reset */
  fwdgt_enable();
}


void drv_wwdgt_init(void)
{
  /* enable WWDGT clock */
  rcu_periph_clock_enable(RCU_WWDGT);
  /*
   *  set WWDGT clock = (PCLK1 (60MHz)/4096)/8 = 1831Hz (~546 us)
   *  set counter value to 127
   *  set window value to 80
   *  refresh window is: ~546 * (127-80)= 25.6ms < refresh window < ~546 * (127-63) =34.9ms.
   */
  wwdgt_config(127, 80, WWDGT_CFG_PSC_DIV8);
  wwdgt_enable();
}

/*
************************************************************************************************************************
* 函数名称 : BSP_WatchDog_Init                                                                                                         
* 功能描述 : 看门狗初始化                                                                                                           
* 输入参数 : TimeOutMs -- 看门狗的超时时间，有效值 1ms ~ 4096ms。                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 32KHZ,32分频，计数频率为1KHZ                                                                                                         
************************************************************************************************************************
*/
void BSP_WatchDog_Init(void)
{
  #if (WDGT_TYPE_USING == E_WDGT_TYPE_FWDGT)
    drv_fwdgt_init(1000);
  #elif (WDGT_TYPE_USING == E_WDGT_TYPE_WWDGT)
    drv_wwdgt_init();
  #endif
}

/*
************************************************************************************************************************
* 函数名称 : BSP_WatchDog_Init                                                                                                         
* 功能描述 : 喂狗                                                                                                          
* 输入参数 : 无                                                                                                      
* 返回参数 : 无                                                                                                         
* 补充说明 :                                                                                                       
************************************************************************************************************************
*/
void BSP_WatchDog_Feed(void)
{
  #if (WDGT_TYPE_USING == E_WDGT_TYPE_FWDGT)
    fwdgt_counter_reload();
  #elif (WDGT_TYPE_USING == E_WDGT_TYPE_WWDGT)
    wwdgt_counter_update(127);
  #endif
}
