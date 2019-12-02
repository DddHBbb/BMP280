#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
#include "delay.h" 		   

//IO方向设置
#define SDA_IN()  {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=8<<4*4;}
#define SDA_OUT() {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=3<<4*4;}

//IO操作函数	 
#define IIC_SCL    PBout(13)                                                   //SCL
#define IIC_SDA    PBout(12)                                                   //SDA	 
#define READ_SDA   PBin(12) 
																																							//输入SDA 

#define    			BMP_IIC_PORT       GPIOB
#define    			BMP_IIC_CLKBUS     RCC_APB2Periph_GPIOB
#define    			BMP_IIC_CLK        GPIO_Pin_13
#define    			BMP_IIC_SDA        GPIO_Pin_12



//IIC所有操作函数
void IIC_Init(void);                                                           //初始化IIC的IO口				 
void IIC_Start(void);				                                           //发送IIC开始信号
void IIC_Stop(void);	  			                                           //发送IIC停止信号
void IIC_Send_Byte(u8 txd);			                                           //IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);                                           //IIC读取一个字节
u8 IIC_Wait_Ack(void); 				                                           //IIC等待ACK信号
void IIC_Ack(void);					                                           //IIC发送ACK信号
void IIC_NAck(void);				                                           //IIC不发送ACK信号

#endif
