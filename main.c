/* Software for sensor*/
/*Creator: The-Anh Nguyen SISLAB-ITI 11-2023 */

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <metal/i2c.h>
#include <metal/io.h>
#include <metal/uart.h>
#include <metal/machine.h>
#include <time.h>
#include "sgp30.h"
#include "sht35.h"

int main() {
	struct 		metal_i2c *i2c; 
	uint32_t 	temp_humi; 
	uint16_t 	CO2_TVOC;
	uint16_t	tmp;

	int16_t		temp;
	uint16_t	humi; 
	
	uint8_t 	CO2;
	uint8_t		TVOC;

	i2c = metal_i2c_get_device(0);
	if (i2c == NULL) {
		printf("I2C's not availble \n");
		return 1; 
	}
	printf("I2C availble \n");
	
	metal_i2c_init(i2c, I2C_BAURATE, METAL_I2C_MASTER);
	
	init_air_quality(i2c);
	delay_t(1000);

	while(1){
		printf("Day: %s \n", __DATE__);
		temp_humi	= get_sht35_sensor_data(i2c);
		temp 		= (temp_humi >> 8) - 45;
	       	humi		= temp_humi & 0x00FF;
		printf("Temperature: %d || Humidity: %d \n", temp, humi);
		reset_sht35_sensor_data(i2c);
			
		CO2_TVOC 	= get_sgp30_sensor_data(i2c);
		CO2 		= (uint8_t)(CO2_TVOC >> 8);
		TVOC		= (uint8_t)(CO2_TVOC & 0xFF);
		printf("CO2: %d         || TVOC: %d     \n", CO2, TVOC);
		delay_t(1000);
	}	

	return 0;
}
