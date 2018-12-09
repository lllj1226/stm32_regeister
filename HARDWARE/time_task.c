/*******************************************************************************
 *                      
 *                         Copyright (c) 2016 
 *******************************************************************************/
 /******************************************************************************
 *
 * 模块名   : 
 *
 * 模块介绍 : 
 *
 * 历史修改 :
 *
 *   历史修改记录位于文件尾
 *
 ******************************************************************************/
#include "stdio.h"
#include "delay.h"
#include "time_task.h"
#include "led.h"
#include "pwm.h"
#include "cap.h"
#include "rtc.h"
#include "key.h"
#include "pcf8574.h"
/*******************************************************************************
*                             G l o b a l   D a t a                            *
*******************************************************************************/
 
u8  schdlr_task_cycl_index = 0;
 
const u32  gp_SCHDLR_TASK_CYCL_CFG[SCHDLR_TASK_CYCL_MAX]={
	(SCHDLR_TASKBIT_10MS|SCHDLR_TASKBIT_20MSA|SCHDLR_TASKBIT_50MS|SCHDLR_TASKBIT_100MS),
	(SCHDLR_TASKBIT_10MS|SCHDLR_TASKBIT_20MSB),
	(SCHDLR_TASKBIT_10MS|SCHDLR_TASKBIT_20MSA),
	(SCHDLR_TASKBIT_10MS|SCHDLR_TASKBIT_20MSB),
	(SCHDLR_TASKBIT_10MS|SCHDLR_TASKBIT_20MSA),
	(SCHDLR_TASKBIT_10MS|SCHDLR_TASKBIT_20MSB|SCHDLR_TASKBIT_50MS),
	(SCHDLR_TASKBIT_10MS|SCHDLR_TASKBIT_20MSA),
	(SCHDLR_TASKBIT_10MS|SCHDLR_TASKBIT_20MSB),
	(SCHDLR_TASKBIT_10MS|SCHDLR_TASKBIT_20MSA),
	(SCHDLR_TASKBIT_10MS|SCHDLR_TASKBIT_20MSB)
};


ST_TASK_SCHDLR  st_TASK_SCHDLR_list[]={
	{&led_task , (u32)(SCHDLR_TASKBIT_100MS)},
	{&pwm_task , (u32)(SCHDLR_TASKBIT_20MSB)},
	{&cap_task , (u32)(SCHDLR_TASKBIT_10MS)},
	{&rtc_task , (u32)(SCHDLR_TASKBIT_100MS)},
	{&key_task , (u32)(SCHDLR_TASKBIT_10MS)},
	{&pcf8547_task , (u32)(SCHDLR_TASKBIT_100MS)},
	{NULL  ,(u32)0xffff}
};




/*******************************************************************************
* 函数名 : time_init
********************************************************************************
*
* 实现功能 :  定义1个100MS（0.1K）中断
*
* 输入 : 
* 		 
* 
* 输出 : 
*                
* 注释 :  
		  Tout= ((arr+1)*(psc+1))/Tclk
          APB1=45M， time3的时钟源为APB1的2倍，就是90M
          CK_CNT（计数值） = fCK_PSC / (PSC[15:0] + 1)
*		  先得到1个10K的频率，然后让技术为100，就可以得到0.1K的中断周期
********************************************************************************/
void time3_init(){
	/*1：时钟开启*/
	Time3_clock_enable();
	/*2:配置周期*/
	TIM3->PSC = (TIME3_FCK/10000)-1;
	//TIM3->ARR = 10000-1; //1S定时
	TIM3->ARR = 100-1; //10MS定时
    TIM3->CR1 = 0;
	
	/*3:配置时钟中断*/
	TIM3->DIER |= TIMEX_DIER_UIE;
	
	/*4:设置中断优先级*/
	MY_NVIC_Init(1,3,TIM3_IRQn,2);
	/*5：开启定时器*/		
	TIM3->CR1 |= TIMEX_CEN_ENABLE;
	
	
	
}

/*******************************************************************************
* 函数名 : time3_irq
********************************************************************************
*
* 实现功能 :  TIME3中断处理
*
* 输入 : 
* 		 
* 
* 输出 : 
*                
* 注释 :  
*		                  
*		  
********************************************************************************/
void TIM3_IRQHandler(){
	ST_TASK_SCHDLR * st_p_TASK_SCHDLR =  &st_TASK_SCHDLR_list[0];
	/**/
	if((TIM3->SR&TIMEX_SR_UIF) == TRUE){
	    TIM3->SR &= ~TIMEX_SR_UIF;//清除中断标志位
		
		u32 schdlr_task_cycl_value = gp_SCHDLR_TASK_CYCL_CFG[schdlr_task_cycl_index];
		/*以下进行任务调度(时间分片)*/
		while(st_p_TASK_SCHDLR->fp_vd_task != (void *)NULL){
			
			/*根据标志位判断是否需要执行该任务*/
			if((schdlr_task_cycl_value & st_p_TASK_SCHDLR->taskbit)!= 0){
				(st_p_TASK_SCHDLR->fp_vd_task)();
			}
			st_p_TASK_SCHDLR++;
		
		}
		schdlr_task_cycl_index++;
		if(schdlr_task_cycl_index >= SCHDLR_TASK_CYCL_MAX)
			schdlr_task_cycl_index = 0;
	}
}





/*********************************************************************************
*一下模拟实现任务调度
*
*********************************************************************************/

















/*******************************************************************************
* Modification History:
*
* |    name    |    date    |       comment
*      刘连军		2013-03-05		增加加法运算函数。
*     
*
********************************************************************************/

/* End of File: template.c */

























