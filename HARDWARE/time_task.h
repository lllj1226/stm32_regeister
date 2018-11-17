/*******************************************************************************
 *                      
 *                         Copyright (c) 2013 
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
 
 #ifndef __TIME_TASK_H__
 #define __TIME_TASK_H__

/*******************************************************************************
*                              I n c l u d e s                                 *
*******************************************************************************/
#include "sys.h"
#include "stdio.h"	





/*******************************************************************************
*                            D e f i n i t i o n s                             *
*******************************************************************************/
#define SCHDLR_TASK_CYCL_MAX 10

#define SCHDLR_TASKBIT_10MS       0x00000001
#define SCHDLR_TASKBIT_20MSA      0x00000002
#define SCHDLR_TASKBIT_20MSB      0x00000004
#define SCHDLR_TASKBIT_50MS       0x00000008
#define SCHDLR_TASKBIT_100MS      0x00000010

#define TIME3_FCK   90000000

#define TIM3_CLOCK_BIT     1
#define Time3_clock_enable() (RCC->APB1ENR |= (1<<TIM3_CLOCK_BIT))
#define Time3_clock_disable() (RCC->APB1ENR &= ~(1<<TIM3_CLOCK_BIT))


#define TIMEX_CEN_ENABLE  (1<<0)
#define TIMEX_CEN_DISABLE  ~(1<<0)
#define TIMEX_DIER_TIE     (1<<6)    //ʹ�ܶ�ʱ���ж�
#define TIMEX_DIER_UIE     (1<<0)    //�����ж�ʹ��

#define TIMEX_SR_UIF   (1<<0)

/*******************************************************************************
*                              D a t a   T y p e s                             *
*******************************************************************************/

typedef struct{
	void (* const fp_vd_task)(void);/*����ָ��*/
	u32 taskbit;	/*����ִ�б�ʶ*/
}ST_TASK_SCHDLR;


void time3_init(void);

/*******************************************************************************
* Modification History:
*
* |    name    |    date    |       comment
*      ������		2013-03-05		���Ӽӷ����㺯����
*     
*
********************************************************************************/

#endif
/* End of File: template.h */

















