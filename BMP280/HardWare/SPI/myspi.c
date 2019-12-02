
#include "myspi.h"
/*
���ܣ���ʼ��spi�ӿ�
*/
void Init_myspi(void)  
{   
    GPIO_InitTypeDef GPIO_InitStructure;              
    RCC_APB2PeriphClockCmd(BMP_SPI_CLKBUS,ENABLE);    //ʹ��GPIO ��ʱ��  
    GPIO_InitStructure.GPIO_Pin = BMP_SPI_MOSI|BMP_SPI_CLK|BMP_SPI_CS;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //�������  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(BMP_SPI_PORT, &GPIO_InitStructure);  
  
    BMP280_CE_H;           //��ʼ��ʱ������  
      
    GPIO_InitStructure.GPIO_Pin = BMP_SPI_MISO;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //��������  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(BMP_SPI_PORT, &GPIO_InitStructure);  
    
}
/*
���ܣ������ӻ�����һ���ֽ�
*/
uint8_t spixfer(uint8_t x) 
{ 
  int i;
  uint8_t reply = 0;
  for (i=7; i>=0; i--) {
    reply <<= 1;
    BMP280_SCK_L;
    if(x & (1<<i))
    {
        BMP280_MOSI_H;
    }
    else 
    {
        BMP280_MOSI_L;
    }
    BMP280_SCK_H;//
    if (BMP280_READ_MISO) 
      reply |= 1;
  }
  return reply;
}

