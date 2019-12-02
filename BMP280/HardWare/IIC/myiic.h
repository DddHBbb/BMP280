#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
#include "delay.h" 		   

//IO��������
#define SDA_IN()  {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=8<<4*4;}
#define SDA_OUT() {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=3<<4*4;}

//IO��������	 
#define IIC_SCL    PBout(13)                                                   //SCL
#define IIC_SDA    PBout(12)                                                   //SDA	 
#define READ_SDA   PBin(12) 
																																							//����SDA 

#define    			BMP_IIC_PORT       GPIOB
#define    			BMP_IIC_CLKBUS     RCC_APB2Periph_GPIOB
#define    			BMP_IIC_CLK        GPIO_Pin_13
#define    			BMP_IIC_SDA        GPIO_Pin_12



//IIC���в�������
void IIC_Init(void);                                                           //��ʼ��IIC��IO��				 
void IIC_Start(void);				                                           //����IIC��ʼ�ź�
void IIC_Stop(void);	  			                                           //����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			                                           //IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);                                           //IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				                                           //IIC�ȴ�ACK�ź�
void IIC_Ack(void);					                                           //IIC����ACK�ź�
void IIC_NAck(void);				                                           //IIC������ACK�ź�

#endif
