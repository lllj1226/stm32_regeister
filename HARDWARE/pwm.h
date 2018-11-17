/*******************************************************************************
 *                      
 *                         Copyright (c) 2013 
 *******************************************************************************/
 /******************************************************************************
 *
 * ģ����   :     pwm.h
 *
 * ģ����� : 
 *
 * ��ʷ�޸� :
 *
 *   ��ʷ�޸ļ�¼λ���ļ�β
 *
 ******************************************************************************/
 
 #ifndef __PWM_H__
 #define __PWM_H__

/*******************************************************************************
*                              I n c l u d e s                                 *
*******************************************************************************/
#include "sys.h"
#include "stdio.h"

/*******************************************************************************
*                            D e f i n i t i o n s                             *
*******************************************************************************/
#define TIME8_FCK   90000000

#define TIM8_CLOCK_BIT     1
#define Time8_clock_enable() (RCC->APB2ENR |= (1<<TIM8_CLOCK_BIT))

void pwm_init(void);
void pwm_task(void);
/*******************************************************************************
*                              D a t a   T y p e s                             *
*******************************************************************************/


/*******************************************************************************
* Modification History:
*
* |    name    |    date    |       comment
*      ������		2013-03-05		���Ӽӷ����㺯����
*     
*
********************************************************************************/

#endif
/* End of File: Main.h */
