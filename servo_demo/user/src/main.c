#include "delay.h"
#include "system.h"
#include "usart.h"
#include "servo.h"
#include "lcd.h"

int main(void)
{
	u8 i = 15;
	u8 j = 25;
	delay_init(72);	     //延时初始化
	uart_init(19200);//串口初始化为9600
	LCD_Init();
	USART_Config(115200);
	POINT_COLOR = RED;
	LCD_ShowString(50, 50, "servo_demo");

	while (i--)
	{
		ang_spe_set(0,612,500);delay_ms(100);
		ang_spe_set(0,300,500);delay_ms(100);
	}
	while(j)
	{	
		change_id(1);
		LCD_ShowString(50, 80, "OK");

		delay_ms(100);
		ang_spe_set(1,200,500);delay_ms(100);
		ang_spe_set(1,350,500);delay_ms(100);  

	}
	while(1)
	{
		LCD_ShowString(50, 70, "OK");
		ang_spe_set(1,365,500);delay_ms(50);
		ang_spe_set(1,650,500);delay_ms(50);  
	
//		Attention();				//******************************立正
	
	}

//		 

}

