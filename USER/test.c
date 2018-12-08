#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "time_task.h"
#include "pwm.h"
#include "cap.h"
#include "sdram.h"
#include "lcd.h"
#include "rtc.h"
#include "usmart.h"
//ALIENTEK ������STM32F429������ ʵ��0
//�½�����ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
//LED״̬���ú���
void led_set(u8 sta)
{
	LED1=sta;
} 
//�����������ò��Ժ���
void test_fun(void(*ledset)(u8),u8 sta)
{
	ledset(sta);
}
int main(void)
{ 
	u8 *str = (u8 *)"llj";
	u8 t=0;
	Stm32_Clock_Init(360,25,2,8);	//����ʱ��,180Mhz
	delay_init(180);				//��ʼ����ʱ����
	uart_init(90,115200);			//���ڳ�ʼ��Ϊ115200
	led_lnit();
	time3_init();
	pwm_init();
	cap_init();
	sdram_init();
	sd_task();
	LCD_Init();
	rtc_init();
	usmart_dev.init(90); 		//��ʼ��USMART	
//	LCD_ShowString(10,40,240,32,32,"Apollo STM32"); 	
	LCD_ShowString(100,240,220,132,32,str);
	while(1)
	{
	//	printf("t:%d\r\n",t);
		delay_ms(6);
		t++;
	}
}
