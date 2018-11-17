#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "time_task.h"
#include "pwm.h"
#include "cap.h"
//ALIENTEK ������STM32F429������ ʵ��0
//�½�����ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾

int main(void)
{ 
	u8 t=0;
	Stm32_Clock_Init(360,25,2,8);	//����ʱ��,180Mhz
	delay_init(180);				//��ʼ����ʱ����
	uart_init(90,115200);			//���ڳ�ʼ��Ϊ115200
	led_lnit();
	time3_init();
	pwm_init();
	cap_init();
	while(1)
	{
	//	printf("t:%d\r\n",t);
		delay_ms(6);
		t++;
	}
}
