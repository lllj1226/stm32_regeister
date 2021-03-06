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
#include "key_irq_sleep.h"
#include  "key.h"
#include "pcf8574.h"
//ALIENTEK 阿波罗STM32F429开发板 实验0
//新建工程实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
//LED状态设置函数
void led_set(u8 sta)
{
	LED1=sta;
} 
//函数参数调用测试函数
void test_fun(void(*ledset)(u8),u8 sta)
{
	ledset(sta);
}
int main(void)
{ 
	//u8 *str = (u8 *)"llj";
	u8 t=0;
	Stm32_Clock_Init(360,25,2,8);	//设置时钟,180Mhz
	delay_init(180);				//初始化延时函数
	key_init();
	uart_init(90,115200);			//串口初始化为115200
	led_lnit();
	//WKUP_Init();				//待机唤醒初始化
	time3_init();
	pwm_init();
	cap_init();
	sdram_init();
	sd_task();
	LCD_Init();
	rtc_init();
	usmart_dev.init(90); 		//初始化USMART	
//	LCD_ShowString(10,40,240,32,32,"Apollo STM32"); 	
//	LCD_ShowString(100,240,220,132,32,str);
	while(PCF8574_Init())		//检测不到PCF8574
	{
		LCD_ShowString(230,170,200,16,16,(u8 *)"PCF8574 Check Failed!");
		delay_ms(500);
		LCD_ShowString(230,170,200,16,16,(u8 *)"Please Check!        ");
		delay_ms(500);
		
	}
	LCD_ShowString(230,170,200,16,16,(u8 *)"PCF8574 Ready!"); 
	while(1)
	{
	//	printf("t:%d\r\n",t);
		delay_ms(6);
		t++;
	}
}
