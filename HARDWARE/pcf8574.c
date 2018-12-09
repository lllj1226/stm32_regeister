#include "pcf8574.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "myiic.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//PCF8574��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/12/28
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//��ʼ��PCF8574
//����ֵ:0,��ʼ���ɹ�
//      1,��ʼ��ʧ��
u8 PCF8574_Init(void)
{
	u8 temp=0;		  	    																 
	RCC->AHB1ENR|=1<<1;     	//ʹ��PORTBʱ�� 
	GPIO_Set(GPIOB,PIN12,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);	//PB12����Ϊ��������  
	IIC_Init();					//IIC��ʼ�� 	
	//���PCF8574�Ƿ���λ
    IIC_Start();    	 	   
	IIC_Send_Byte(PCF8574_ADDR);//д��ַ			   
	temp=IIC_Wait_Ack();		//�ȴ�Ӧ��,ͨ���ж��Ƿ���ACKӦ��,���ж�PCF8574��״̬
    IIC_Stop();					//����һ��ֹͣ����
    PCF8574_WriteOneByte(0XFF);	//Ĭ�����������IO����ߵ�ƽ
	return temp;
} 

//��ȡPCF8574��8λIOֵ
//����ֵ:����������
u8 PCF8574_ReadOneByte(void)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();    	 	   
	IIC_Send_Byte(PCF8574_ADDR|0X01);   //�������ģʽ			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();							//����һ��ֹͣ����	    
	return temp;
}
//��PCF8574д��8λIOֵ  
//DataToWrite:Ҫд�������
void PCF8574_WriteOneByte(u8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
    IIC_Send_Byte(PCF8574_ADDR|0X00);   //����������ַ0X40,д���� 	 
	IIC_Wait_Ack();	    										  		   
	IIC_Send_Byte(DataToWrite);    	 	//�����ֽ�							   
	IIC_Wait_Ack();      
    IIC_Stop();							//����һ��ֹͣ���� 
	delay_ms(10);	 
}

//����PCF8574ĳ��IO�ĸߵ͵�ƽ
//bit:Ҫ���õ�IO���,0~7
//sta:IO��״̬;0��1
void PCF8574_WriteBit(u8 bit,u8 sta)
{
    u8 data;
    data=PCF8574_ReadOneByte(); //�ȶ���ԭ��������
    if(sta==0)data&=~(1<<bit);     
    else data|=1<<bit;
    PCF8574_WriteOneByte(data); //д���µ�����
}

//��ȡPCF8574��ĳ��IO��ֵ
//bit��Ҫ��ȡ��IO���,0~7
//����ֵ:��IO��ֵ,0��1
u8 PCF8574_ReadBit(u8 bit)
{
    u8 data;
    data=PCF8574_ReadOneByte(); //�ȶ�ȡ���8λIO��ֵ 
    if(data&(1<<bit))return 1;
    else return 0;   
}
   


void pcf8547_task(){
   u8 key_num;
   static u8 beepsta=1;
   key_num = get_gb_key();
	if(key_num==KEY_0)//KEY0����,��ȡ�ַ�������ʾ
	{ 
		beepsta=!beepsta;					//������״̬ȡ��
		PCF8574_WriteBit(BEEP_IO,beepsta);	//���Ʒ�����
	}
	if(PCF8574_INT==0)				//PCF8574���жϵ͵�ƽ��Ч
	{
		key_num=PCF8574_ReadBit(EX_IO);	//��ȡEXIO״̬,ͬʱ���PCF8574���ж����(INT�ָ��ߵ�ƽ)
		if(key_num==0)LED1=!LED1;		//LED1״̬ȡ�� 
	}

}

    
