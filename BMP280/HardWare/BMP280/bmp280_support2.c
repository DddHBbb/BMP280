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
* 函数名称：BMP_280Init
* 功能描述：BMP280初始化
* 输入参数：无
* 输出参数：无
* 返回值：返回0成功，返回-1失败
*****************************************************/
s8 BMP_280Init(void)
{
	#ifdef __I2C_ROUTINE__  
		#ifdef __SPI_ROUTINE__
			#error "大神，你选择了两种通信方式同时用？这是什么操作?"
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
            #error "1540909218:请选择宏__I2C_ROUTINE__或__SPI_ROUTINE__！！"
        #endif
    #endif
    if(bmp280_init(&bmp280))
		return (s8)-1;
    return 0;
}

/****************************************************
* 函数名称：SPI_READ_WRITE_STRING
* 功能描述：实现BMP280 SPI读时序
* 输入参数：参考手册
* 输出参数：参考手册
* 返回值： 返回0成功，返回-1失败
*****************************************************/
s8 SPI_READ_WRITE_STRING(u8 *addr, u8 *data, u8 cnt)
{
	//拉低CSB信号线
	//发送寄存器地址同时读回寄存器的数据
	//读取完成，拉低CSB信号线
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
* 函数名称：SPI_WRITE_STRING
* 功能描述：实现BMP280 SPI写时序
* 输入参数：参考手册
* 输出参数：参考手册
* 返回值： 返回0成功，返回-1失败
*****************************************************/
s8 SPI_WRITE_STRING(u8 *data,u8 cnt)
{
	//拉低CSB信号线
	//发送寄存器地址，发送寄存器数据
	//写入完成时，拉低CSB信号线
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
* 函数名称：I2CMULTIPLE_WRITE_READ_PREPARE
* 功能描述：实现BMP280 IIC读写时序准备
* 输入参数：参考手册
* 输出参数：参考手册
* 返回值： 返回0成功，返回-1失败
*****************************************************/
s8 I2CMULTIPLE_WRITE_READ_PREPARE(u8 dev_addr)
{
	//发送开始信号
	//发送从设备地址加写命令
	//等待应答
	IIC_Start();     
	IIC_Send_Byte((dev_addr<<1)|0); 	
	if(IIC_Wait_Ack())
		return (s8)-1;
	return 0;
}
/****************************************************
* 函数名称：I2C_WRITE_STRING
* 功能描述：实现BMP280 IIC读写时序
* 输入参数：参考手册
* 输出参数：参考手册
* 返回值： 返回0成功，返回-1失败
*****************************************************/
s8 I2C_WRITE_STRING(u8 dev_addr, u8 *data, u8 len)
{
	//发送开始信号
	//发送从设备地址加写命令
	//等待应答
	
	//发送寄存器地址
	//等待应答
	//发送要写入寄存器的数据
	//等待应答
	
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
* 函数名称：I2C_WRITE_READ_STRING
* 功能描述：实现BMP280 IIC读时序
* 输入参数：参考手册
* 输出参数：参考手册
* 返回值： 返回0成功，返回-1失败
*****************************************************/
s8 I2C_WRITE_READ_STRING\
(u8 dev_addr, u8 *reg_addr, \
u8 *buf, u8 ack, u8 cnt)
{
	//发送开始信号
	//发送从地址加写命令
	//等待应答
	
	//发送寄存器地址
	//等待应答
	//发送开始信号
	//发送从设备地址加读命令
	//等待应答
	//读取一个字节数据后发送应答信号，如果读取完毕，不发送应答信号，然后发送停止信号
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

