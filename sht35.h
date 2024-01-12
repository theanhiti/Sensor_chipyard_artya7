/*SHT35 - Temperature and Humidity sensor */
/* Creator: The-Anh Nguyen SISLAB-ITI 11-2023*/

#ifndef SHT35
#define SHT35

#include <stdio.h>
#include <stdint.h>
#include <metal/i2c.h>
#include <metal/uart.h>
#include <metal/gpio.h>
#include <time.h>

/* PmodAD2, PmodTmp2 sensor modules are connected to I2C0 bus */
#define SHT35_I2C_ADDR			0x45
#define I2C_BAURATE			30000

/*return values */
#define RET_OK				0
#define RET_NOK				1

/*Buffer length macros */
#define LEN0				0
#define LEN1				1
#define LEN2				2

/*Sensor command */

/*Measurement command for Single shot data acquisition mode */
/*Clock stretching = enabled */
#define SHT35_CMD_CLOCK_STRETCH_H	0x2C06
#define SHT35_CMD_CLOCK_STRETCH_M	0x2C0D
#define SHT35_CMD_CLOCK_STRETCH_L	0x2C10 

/*Clock stretching = disabled */
#define SHT35_CMD_POLLING_H		0x2C00
#define SHT35_CMD_POLLING_M		0x2C0B
#define SHT35_CMD_POLLING_L		0x2C16
/*----------------------------------------------------------*/

/* Measurement command for Periodic data acquisition mode */
/* mps = 0.5 */
#define SHT35_CMD_PERIODIC_HALF_H	0x2032
#define SHT35_CMD_PERIODIC_HALF_M	0x2024
#define SHT35_CMD_PERIODIC_HALF_L	0x202F

/* mps = 1 */
#define SHT35_CMD_PERIODIC_1_H		0x2130
#define SHT35_CMD_PERIODIC_1_M		0x2126
#define SHT35_CMD_PERIODIC_1_L		0x212D

/* mps = 2 */
#define SHT35_CMD_PERIODIC_2_H		0x2236
#define SHT35_CMD_PERIODIC_2_M		0x2220
#define SHT35_CMD_PERIODIC_2_L		0x222B

/* mps = 4 */
#define SHT35_CMD_PERIODIC_4_H		0x2334
#define SHT35_CMD_PERIODIC_4_M		0x2322
#define SHT35_CMD_PERIODIC_4_L		0x2329

/* mps = 10 */
#define SHT35_CMD_PERIODIC_10_H		0x2737
#define SHT35_CMD_PERIODIC_10_M		0x2721
#define SHT35_CMD_PERIODIC_10_L		0x272A

/* ART command */
#define SHT35_CMD_PERIODIC_ART		0x2B32

/* Break command */
#define SHT35_CMD_PERIODIC_BREAK	0x3093

/* Reset command */
#define SHT35_CMD_RESET 0x30A2
/*-------------------------------------------------------*/

/* Measurement function */
void delay_t();

uint16_t get_sht35_sensor_data(struct metal_i2c *i2c);

void reset_sht35_sensor_data(struct metal_i2c *i2c);

#endif
