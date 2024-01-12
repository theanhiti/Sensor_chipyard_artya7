/*SGP30 - Air Sensirion Gas Platform */
/*Creator: The-Anh Nguyen SISLAB-ITI 11-2023 */

#include <stdio.h>
#include <stdint.h>
#include <metal/i2c.h>
#include <metal/gpio.h>
#include <metal/uart.h>
#include "sgp30.h"

void delay_time(){
	for(int i=0; i<10000000; i++);
}

void init_air_quality(struct metal_i2c *i2c){
	uint8_t cmd[LEN2];

	cmd[0] = (uint8_t)(INIT_AIR_QUALITY >> 8);
	cmd[1] = (uint8_t)(INIT_AIR_QUALITY & 0xFF);

	metal_i2c_write(i2c, SGP30_I2C_ADDR, LEN2, cmd, METAL_I2C_STOP_DISABLE);
	delay_time(1000);
}

uint16_t get_sgp30_sensor_data(struct metal_i2c *i2c){
	uint8_t cmd[LEN2];
	uint8_t buf[3];

	uint8_t tmp; 
	uint16_t CO2_TVOC; 
	
	/*set the command for measuring data */
	cmd[0] = (uint8_t)(MEASURE_AIR_QUALITY >> 8);
	cmd[1] = (uint8_t)(MEASURE_AIR_QUALITY & 0xFF);

	/* write/read data from I2C address */
	metal_i2c_write(i2c, SGP30_I2C_ADDR, LEN2, cmd, METAL_I2C_STOP_DISABLE);
	delay_time(1000);
	metal_i2c_read(i2c, SGP30_I2C_ADDR, 3, buf, METAL_I2C_STOP_ENABLE);
	
	/*export CO2 data */
	CO2_TVOC 	= (CO2_TVOC & 0xFF) | (uint16_t)buf[0] << 8;

	CO2_TVOC 	= (CO2_TVOC & 0xFF00) | buf[1] ;
	
	return CO2_TVOC;
}

uint16_t measure_test(struct metal_i2c *i2c){
	uint8_t cmd[LEN2];
	uint8_t buf[3];
	

	uint16_t test = 0;

	cmd[0] = (uint8_t)(MEASURE_TEST >> 8);
	cmd[1] = (uint8_t)(MEASURE_TEST & 0xFF);
	
	metal_i2c_write(i2c, SGP30_I2C_ADDR, LEN2, cmd, METAL_I2C_STOP_DISABLE);
	delay_time(1500);
	metal_i2c_read(i2c, SGP30_I2C_ADDR, 3, buf, METAL_I2C_STOP_ENABLE);
	
	test = ((uint8_t)buf[0] << 8) + (uint8_t)buf[1];

	return test;
}
