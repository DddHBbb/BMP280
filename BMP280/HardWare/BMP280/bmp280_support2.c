#include "bmp280_support.h"
#ifndef u8 
#define u8 unsigned char
#endif
#ifndef s8 
#define s8 char
#endif
extern s8 I2C_routine(void);
extern s8 SPI_routine(void);
extern struct bmp280_t bmp280;
/****************************************************
* �������ƣ�BMP_280Init
* ����������BMP280��ʼ��
* �����������
* �����������
* ����ֵ������0�ɹ�������-1ʧ��
*****************************************************/
s8 BMP_280Init(void)
{
	#ifdef __I2C_ROUTINE__  
		#ifdef __SPI_ROUTINE__
			#error "������ѡ��������ͨ�ŷ�ʽͬʱ�ã�����ʲô����?"
		#endif
	#endif
    #ifdef __I2C_ROUTINE__
        IIC_Init();
        I2C_routine();
    #else
        #ifdef __SPI_ROUTINE__
            Init_myspi();
            SPI_routine();
        #else
            #error "1540909218:��ѡ���__I2C_ROUTINE__��__SPI_ROUTINE__����"
        #endif
    #endif
    if(bmp280_init(&bmp280))
		return (s8)-1;
    return 0;
}

/****************************************************
* �������ƣ�SPI_READ_WRITE_STRING
* ����������ʵ��BMP280 SPI��ʱ��
* ����������ο��ֲ�
* ����������ο��ֲ�
* ����ֵ�� ����0�ɹ�������-1ʧ��
*****************************************************/
s8 SPI_READ_WRITE_STRING(u8 *addr, u8 *data, u8 cnt)
{
	//����CSB�ź���
	//���ͼĴ�����ַͬʱ���ؼĴ���������
	//��ȡ��ɣ�����CSB�ź���
    int i;
    BMP280_CE_L;
    for(i=0;i<cnt;i++)
    {
         data[i]=spixfer(addr[i]);
    }
    BMP280_CE_H;
    return 0;
}

/****************************************************
* �������ƣ�SPI_WRITE_STRING
* ����������ʵ��BMP280 SPIдʱ��
* ����������ο��ֲ�
* ����������ο��ֲ�
* ����ֵ�� ����0�ɹ�������-1ʧ��
*****************************************************/
s8 SPI_WRITE_STRING(u8 *data,u8 cnt)
{
	//����CSB�ź���
	//���ͼĴ�����ַ�����ͼĴ�������
	//д�����ʱ������CSB�ź���
    int i;
    BMP280_CE_L;
    for(i=0;i<cnt;i++)
    {
       spixfer(data[i]);
    }
    BMP280_CE_H;
    return 0;
}
/****************************************************
* �������ƣ�I2CMULTIPLE_WRITE_READ_PREPARE
* ����������ʵ��BMP280 IIC��дʱ��׼��
* ����������ο��ֲ�
* ����������ο��ֲ�
* ����ֵ�� ����0�ɹ�������-1ʧ��
*****************************************************/
s8 I2CMULTIPLE_WRITE_READ_PREPARE(u8 dev_addr)
{
	//���Ϳ�ʼ�ź�
	//���ʹ��豸��ַ��д����
	//�ȴ�Ӧ��
	IIC_Start();     
	IIC_Send_Byte((dev_addr<<1)|0); 	
	if(IIC_Wait_Ack())
		return (s8)-1;
	return 0;
}
/****************************************************
* �������ƣ�I2C_WRITE_STRING
* ����������ʵ��BMP280 IIC��дʱ��
* ����������ο��ֲ�
* ����������ο��ֲ�
* ����ֵ�� ����0�ɹ�������-1ʧ��
*****************************************************/
s8 I2C_WRITE_STRING(u8 dev_addr, u8 *data, u8 len)
{
	//���Ϳ�ʼ�ź�
	//���ʹ��豸��ַ��д����
	//�ȴ�Ӧ��
	
	//���ͼĴ�����ַ
	//�ȴ�Ӧ��
	//����Ҫд��Ĵ���������
	//�ȴ�Ӧ��
	
    int i=0;
    if(I2CMULTIPLE_WRITE_READ_PREPARE(dev_addr))
		return (s8)-1;
	for(i=1; i<len; i++)
	{
        IIC_Send_Byte(data[0]++); 
        if(IIC_Wait_Ack())
			return (s8)-1;
        IIC_Send_Byte(data[i]);  
		if(IIC_Wait_Ack())
			return (s8)-1;
	}
    IIC_Stop( );	
    return 0;
}
/****************************************************
* �������ƣ�I2C_WRITE_READ_STRING
* ����������ʵ��BMP280 IIC��ʱ��
* ����������ο��ֲ�
* ����������ο��ֲ�
* ����ֵ�� ����0�ɹ�������-1ʧ��
*****************************************************/
s8 I2C_WRITE_READ_STRING\
(u8 dev_addr, u8 *reg_addr, \
u8 *buf, u8 ack, u8 cnt)
{
	//���Ϳ�ʼ�ź�
	//���ʹӵ�ַ��д����
	//�ȴ�Ӧ��
	
	//���ͼĴ�����ַ
	//�ȴ�Ӧ��
	//���Ϳ�ʼ�ź�
	//���ʹ��豸��ַ�Ӷ�����
	//�ȴ�Ӧ��
	//��ȡһ���ֽ����ݺ���Ӧ���źţ������ȡ��ϣ�������Ӧ���źţ�Ȼ����ֹͣ�ź�
	if(I2CMULTIPLE_WRITE_READ_PREPARE(dev_addr))
		return (s8)-1;
	IIC_Send_Byte(*reg_addr);         
	if(IIC_Wait_Ack())
		return (s8)-1;
	IIC_Start();                
	IIC_Send_Byte((dev_addr<<1)|1); 
	if(IIC_Wait_Ack()) 
		return (s8)-1;           
	while(cnt)
	{ 
		if(cnt==1)*buf=IIC_Read_Byte(0);
		else *buf=IIC_Read_Byte(1);		
		cnt--;
		buf++;  
	}
	IIC_Stop();                
	return 0;
}

