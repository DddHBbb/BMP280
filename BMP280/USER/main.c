#include "stm32f10x.h"
#include "bmp280.h"
#include "delay.h"
#include "usart.h"
#include "bmp280_support.h"

/*本示例使用模拟IIC或SPI的方式和BMP280通信，只需要在bmp280_support.h选择相应的宏即可*/
int main(void)  
{   
	s32 v_data_uncomp_tem_s32,compensate_temperature;
	s32 v_data_uncomp_pres_s32,compensate_pressure;
	//调试输出用
	uart_init(256000);
	//bmp280用到延时函数
	delay_init();
	//传感器初始化
	if(BMP_280Init())
		printf("");
	/*Forced mode方式下使用BMP280的示例*/
	//工作模式设置
    if(bmp280_set_work_mode(BMP280_ULTRA_LOW_POWER_MODE))
		printf("");
	//设置过滤器
	if(bmp280_set_filter(BMP280_FILTER_COEFF_16))
		printf("");
	//设置温度过采样值
	if(bmp280_set_oversamp_temperature(BMP280_OVERSAMP_16X))
		printf("");
	//设置压强过采样值
	if(bmp280_set_oversamp_pressure(BMP280_OVERSAMP_16X))
		printf("");
	
	while(1)
	{
		delay_ms(500);
		//设置电源模式
		if(bmp280_set_power_mode(BMP280_FORCED_MODE))
			printf("");
		//读原始温度数据
		if(bmp280_read_uncomp_temperature(&v_data_uncomp_tem_s32))
			printf("");
		//读原始压强数据
		if(bmp280_read_uncomp_pressure(&v_data_uncomp_pres_s32))
			printf("");
		//换算真实温度数据
		compensate_temperature = bmp280_compensate_temperature_int32(v_data_uncomp_tem_s32);
		//换算真实的压强数据
		compensate_pressure = bmp280_compensate_pressure_int32(v_data_uncomp_pres_s32);
		printf("Current Temperature:%.2f °C\r\n",compensate_temperature*0.01f);
		printf("Current Pressure   :%.3f kPa\r\n",compensate_pressure*0.01f);
	}	
}


