
#include "myspi.h"
/*
功能：初始化spi接口
*/
void Init_myspi(void)  
{   
    GPIO_InitTypeDef GPIO_InitStructure;              
    RCC_APB2PeriphClockCmd(BMP_SPI_CLKBUS,ENABLE);    //使能GPIO 的时钟  
    GPIO_InitStructure.GPIO_Pin = BMP_SPI_MOSI|BMP_SPI_CLK|BMP_SPI_CS;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //推挽输出  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(BMP_SPI_PORT, &GPIO_InitStructure);  
  
    BMP280_CE_H;           //初始化时先拉高  
      
    GPIO_InitStructure.GPIO_Pin = BMP_SPI_MISO;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //上拉输入  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(BMP_SPI_PORT, &GPIO_InitStructure);  
    
}
/*
功能：主、从机交换一个字节
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

