/*******************************************************************************
 *                      
 *                         Copyright (c) 2013 
 *******************************************************************************/
 /******************************************************************************
 *
 * ģ����   :     Main.h
 *
 * ģ����� : 
 *
 * ��ʷ�޸� :
 *
 *   ��ʷ�޸ļ�¼λ���ļ�β
 *
 ******************************************************************************/
 
 #ifndef __KEY_H__
 #define __KEY_H__

/*******************************************************************************
*                              I n c l u d e s                                 *
*******************************************************************************/
#include "sys.h"	 
#include "stdlib.h"
#include "delay.h"
/*******************************************************************************
*                            D e f i n i t i o n s                             *
*******************************************************************************/

#define KEY_0    0
#define KEY_1    1
#define KEY_2    2
#define KEY_3    3
#define KEY_NO_KEY 0xff


#define KEY0 		PHin(3)   	//PH3
#define KEY1 		PHin(2)		//PH2 
#define KEY2 		PCin(13)	//PC13
#define WK_UP 		PAin(0)		//PA0

void key_init(void);
void key_task(void);
u8 get_gb_key(void);
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
