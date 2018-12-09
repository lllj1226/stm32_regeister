/*******************************************************************************
 *                      
 *                         Copyright (c) 2016 
 *******************************************************************************/
 /******************************************************************************
 *
 * ģ����   : 
 *
 * ģ����� : 
 *
 * ��ʷ�޸� :
 *
 *   ��ʷ�޸ļ�¼λ���ļ�β
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
* ������ : time_init
********************************************************************************
*
* ʵ�ֹ��� :  ����1��100MS��0.1K���ж�
*
* ���� : 
* 		 
* 
* ��� : 
*                
* ע�� :  
		  Tout= ((arr+1)*(psc+1))/Tclk
          APB1=45M�� time3��ʱ��ԴΪAPB1��2��������90M
          CK_CNT������ֵ�� = fCK_PSC / (PSC[15:0] + 1)
*		  �ȵõ�1��10K��Ƶ�ʣ�Ȼ���ü���Ϊ100���Ϳ��Եõ�0.1K���ж�����
********************************************************************************/
void time3_init(){
	/*1��ʱ�ӿ���*/
	Time3_clock_enable();
	/*2:��������*/
	TIM3->PSC = (TIME3_FCK/10000)-1;
	//TIM3->ARR = 10000-1; //1S��ʱ
	TIM3->ARR = 100-1; //10MS��ʱ
    TIM3->CR1 = 0;
	
	/*3:����ʱ���ж�*/
	TIM3->DIER |= TIMEX_DIER_UIE;
	
	/*4:�����ж����ȼ�*/
	MY_NVIC_Init(1,3,TIM3_IRQn,2);
	/*5��������ʱ��*/		
	TIM3->CR1 |= TIMEX_CEN_ENABLE;
	
	
	
}

/*******************************************************************************
* ������ : time3_irq
********************************************************************************
*
* ʵ�ֹ��� :  TIME3�жϴ���
*
* ���� : 
* 		 
* 
* ��� : 
*                
* ע�� :  
*		                  
*		  
********************************************************************************/
void TIM3_IRQHandler(){
	ST_TASK_SCHDLR * st_p_TASK_SCHDLR =  &st_TASK_SCHDLR_list[0];
	/**/
	if((TIM3->SR&TIMEX_SR_UIF) == TRUE){
	    TIM3->SR &= ~TIMEX_SR_UIF;//����жϱ�־λ
		
		u32 schdlr_task_cycl_value = gp_SCHDLR_TASK_CYCL_CFG[schdlr_task_cycl_index];
		/*���½����������(ʱ���Ƭ)*/
		while(st_p_TASK_SCHDLR->fp_vd_task != (void *)NULL){
			
			/*���ݱ�־λ�ж��Ƿ���Ҫִ�и�����*/
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
*һ��ģ��ʵ���������
*
*********************************************************************************/

















/*******************************************************************************
* Modification History:
*
* |    name    |    date    |       comment
*      ������		2013-03-05		���Ӽӷ����㺯����
*     
*
********************************************************************************/

/* End of File: template.c */

























