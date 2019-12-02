#ifndef __MYSPI_H__
#define __MYSPI_H__
#include "stm32f10x_gpio.h"
//SPI输入  
#define         BMP280_READ_MISO   GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) //SDO 
// //
#define         BMP280_CE_L      	GPIO_ResetBits(GPIOA, GPIO_Pin_4) //SCB
//
#define         BMP280_CE_H      	GPIO_SetBits(GPIOA, GPIO_Pin_4)   
//SPI输出  
#define         BMP280_MOSI_L  		GPIO_ResetBits(GPIOA , GPIO_Pin_2)  //SDI  SDA
#define         BMP280_MOSI_H 	  GPIO_SetBits(GPIOA , GPIO_Pin_2)     
//SPI时钟  
#define         BMP280_SCK_L  	  GPIO_ResetBits(GPIOA , GPIO_Pin_3)  //SCK SCL
#define         BMP280_SCK_H  	  GPIO_SetBits(GPIOA , GPIO_Pin_3)  


#define    			BMP_SPI_PORT       GPIOA
#define    			BMP_SPI_CLKBUS     RCC_APB2Periph_GPIOA
#define    			BMP_SPI_MOSI       GPIO_Pin_2
#define    			BMP_SPI_CS    		 GPIO_Pin_4
#define    			BMP_SPI_MISO       GPIO_Pin_0
#define    			BMP_SPI_CLK        GPIO_Pin_3
/*
功能：初始化spi接口
*/
void Init_myspi(void)  ;
/*
功能：主、从机交换一个字节
*/
unsigned char spixfer(unsigned char x) ;

#endif
