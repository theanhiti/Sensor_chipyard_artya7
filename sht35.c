/* SHT35 - Temperature and Humidity sensor */
/* Creator: The-Anh Nguyen SISLAB-ITI 11-2023 */

#include <metal/cpu.h>
#include <metal/io.h>
#include <metal/i2c.h>
#include <metal/uart.h>
#include <metal/machine.h>
#include <time.h>
#include "sht35.h"

void delay_t(){
	for(int i=0; i < 10000000; i++);
}

uint16_t get_sht35_sensor_data(struct metal_i2c *i2c){
	uint8_t 	cmd[LEN2];
	uint8_t 	buf[6];
	
	uint16_t	tmp;
	int16_t		tmp1;
	
	uint16_t 	hum; 
	int16_t		hum1; 

	uint32_t	temp_humi = 0;	
	
	/*set the command for measuring data */
	/*Measure with Repeatability: High, Clock stretching: enable */
	cmd[0] 	= (uint8_t)(SHT35_CMD_CLOCK_STRETCH_M >> 8);
	cmd[1] 	= (uint8_t)(SHT35_CMD_CLOCK_STRETCH_M & 0xFF); 
	

	/* write/read data from I2C address */
	metal_i2c_write(i2c, SHT35_I2C_ADDR, LEN2, cmd, METAL_I2C_STOP_DISABLE);
	delay_t(1000);
//	metal_i2c_write(i2c, SHT35_I2C_ADDR, LEN2, cmd, METAL_I2C_STOP_DISABLE);
//	delay_t();
	metal_i2c_read(i2c, SHT35_I2C_ADDR, 6, buf, METAL_I2C_STOP_ENABLE);

	#ifdef SHT35_DEBUG
	for (uint8_t i=0; i<6; i++){
			printf ("value of buf[%d]: %02x \n", i, buf[i]);
		}		
	#endif

	/*export temperature data */
	tmp		= ((uint16_t)buf[0] <<8) | buf[1];
	tmp1 		= (175*tmp)/65535;
	temp_humi 	= ((uint16_t)tmp1 << 8);
	
	/*export humidity data */
	hum		= ((uint16_t)buf[3] << 8) | buf[4];
	hum1		= (100*hum)/65535;

	temp_humi 	= temp_humi + hum1;

	#ifdef SHT35_DEBUG 
		printf("temperature: %08x %d \n", tmp, tmp1);
	#endif

	return temp_humi; 
}

void reset_sht35_sensor_data(struct metal_i2c *i2c){
	uint8_t cmd[LEN2];
	cmd[0] 	= (uint8_t)(SHT35_CMD_RESET >> 8);
	cmd[1] 	= (uint8_t)(SHT35_CMD_RESET & 0xFF); 
	metal_i2c_write(i2c, SHT35_I2C_ADDR, LEN2, cmd, METAL_I2C_STOP_DISABLE); 
	delay_t(1000);
}




