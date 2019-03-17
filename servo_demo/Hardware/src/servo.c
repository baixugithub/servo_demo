#include "servo.h"



u8 Instruction,Checkout,Id;
u8 final[11];
u8 paramenter_ang_spe[4];
u8 moreset[8]; 

u8 calculate_checkout(void)	  //计算校验码
{
	u8 checkout;
	checkout=~(Id+0x07+0x03+0x1e+paramenter_ang_spe[0]+paramenter_ang_spe[1]+paramenter_ang_spe[2]+paramenter_ang_spe[3]);
/*	if(num>255)
	{
		num=num&0x00ff;
	}  
	checkout=~num; */
	return checkout;
}
//

void ang_spe_set(u8 id,u16 ang,u16 spe)   //设置ID  角度 速度
{
	u8 a1,a2,s1,s2;
	Id=id;

	a1=ang/255;	  //双字节十进制分解为单字节十六进制
	a2=ang%255;
	s1=spe/255;
	s2=spe%255;
	paramenter_ang_spe[0]=a2;		
	paramenter_ang_spe[1]=a1;
	paramenter_ang_spe[2]=s2;
	paramenter_ang_spe[3]=s1;	
	complete();
	transmitdata(11);
}
//

void complete(void)	   //确定最终输出数组
{
	 final[0]=0xff;
	 final[1]=0xff;
	 final[2]=Id;
	 final[3]=0x07;
	 final[4]=0x03;	 
	 final[5]=0x1e;
	 final[6]=paramenter_ang_spe[0];
	 final[7]=paramenter_ang_spe[1];	
	 final[8]=paramenter_ang_spe[2];
	 final[9]=paramenter_ang_spe[3];
	 final[10]=calculate_checkout();
	 
}
//
void change_id(u8 dib)
{
	moreset[0]=0xff;
	moreset[1]=0xff;
	moreset[2]=0xfe;  //u8 dia, 
	moreset[3]=0x04;
	moreset[4]=0x03;
	moreset[5]=0x03;
	moreset[6]=dib;
	moreset[7]=~(moreset[2]+moreset[3]+moreset[4]+moreset[5]\
					+moreset[6]);
	/*	if(num>255)
	{
		num=num&0x00ff;
	}  
	checkout=~num; */

	transmitdata(8);
}	
//
	
void transmitdata(u8 str)	 //串口发送数组
{
    u8 index = 0;  
	 for (index=0;index<str;index++)	  
    {
        USART_SendData(USART2,final[index]);
        while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET);

    }
}
//
void Attention(void)				//******************************立正
{		
	ang_spe_set(1,365,500);delay_ms(50);
	ang_spe_set(1,650,500);delay_ms(50);  
}
//
