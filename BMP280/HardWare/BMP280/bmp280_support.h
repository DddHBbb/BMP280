#ifndef __BMP280_SUPPORT_H__
#define __BMP280_SUPPORT_H__
#include "delay.h"
#include "stdio.h"
#include "myiic.h"
#include "myspi.h"
#include "bmp280.h"
#include "math.h"
#include "stdbool.h"
//��ѡ��ͬ�ĺ���ʹ�ò�ͬ��ͨ�ŷ�ʽ,ע��Ҫʹ����Ӧ������
//#define __I2C_ROUTINE__
#define __SPI_ROUTINE__

//BMP280��ʼ��
char BMP_280Init(void);
/*BMP280 SPIͨ�ŵĺ���*/
char SPI_READ_WRITE_STRING\
(unsigned char *addr, unsigned char *data, unsigned char cnt);
char SPI_WRITE_STRING(unsigned char *data,unsigned char cnt);

/*BMP280 IICͨ�ŵĺ���*/
char I2C_WRITE_STRING(unsigned char dev_addr, unsigned char *data, unsigned char len);
char I2C_WRITE_READ_STRING(unsigned char dev_addr, unsigned char *reg_addr,unsigned char *buf, unsigned char ack, unsigned char cnt);

#endif

