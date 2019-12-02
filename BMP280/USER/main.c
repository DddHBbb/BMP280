#include "stm32f10x.h"
#include "bmp280.h"
#include "delay.h"
#include "usart.h"
#include "bmp280_support.h"

/*��ʾ��ʹ��ģ��IIC��SPI�ķ�ʽ��BMP280ͨ�ţ�ֻ��Ҫ��bmp280_support.hѡ����Ӧ�ĺ꼴��*/
int main(void)  
{   
	s32 v_data_uncomp_tem_s32,compensate_temperature;
	s32 v_data_uncomp_pres_s32,compensate_pressure;
	//���������
	uart_init(256000);
	//bmp280�õ���ʱ����
	delay_init();
	//��������ʼ��
	if(BMP_280Init())
		printf("");
	/*Forced mode��ʽ��ʹ��BMP280��ʾ��*/
	//����ģʽ����
    if(bmp280_set_work_mode(BMP280_ULTRA_LOW_POWER_MODE))
		printf("");
	//���ù�����
	if(bmp280_set_filter(BMP280_FILTER_COEFF_16))
		printf("");
	//�����¶ȹ�����ֵ
	if(bmp280_set_oversamp_temperature(BMP280_OVERSAMP_16X))
		printf("");
	//����ѹǿ������ֵ
	if(bmp280_set_oversamp_pressure(BMP280_OVERSAMP_16X))
		printf("");
	
	while(1)
	{
		delay_ms(500);
		//���õ�Դģʽ
		if(bmp280_set_power_mode(BMP280_FORCED_MODE))
			printf("");
		//��ԭʼ�¶�����
		if(bmp280_read_uncomp_temperature(&v_data_uncomp_tem_s32))
			printf("");
		//��ԭʼѹǿ����
		if(bmp280_read_uncomp_pressure(&v_data_uncomp_pres_s32))
			printf("");
		//������ʵ�¶�����
		compensate_temperature = bmp280_compensate_temperature_int32(v_data_uncomp_tem_s32);
		//������ʵ��ѹǿ����
		compensate_pressure = bmp280_compensate_pressure_int32(v_data_uncomp_pres_s32);
		printf("Current Temperature:%.2f ��C\r\n",compensate_temperature*0.01f);
		printf("Current Pressure   :%.3f kPa\r\n",compensate_pressure*0.01f);
	}	
}


