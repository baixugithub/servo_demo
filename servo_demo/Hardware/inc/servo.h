#ifndef _SERVO_H_
#define _SERVO_H_
	
#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"


void transmitdata(u8 str);	 //���ڷ�������
u8 calculate_checkout(void);
void ang_spe_set(u8 id,u16 ang,u16 spe);   //����ID  �Ƕ� �ٶ�
void complete(void);
void change_id(u8 dib);	//u8 dia,
void Attention(void);				//******************************����


#endif

