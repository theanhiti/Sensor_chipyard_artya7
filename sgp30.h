/* SGP30 - Air Sensirion Gas Platform */
/* Creator: The-Anh Nguyen SISLAB-ITI 11-2023 */

#ifndef SGP30
#define SGP30

#include <stdio.h>
#include <stdint.h>
#include <metal/i2c.h>
#include <metal/uart.h>
#include <metal/gpio.h>
#include <time.h>

/*PmodAD2, PmodTmp2 sensor modules are connected to I2C0 bus */
#define SGP30_I2C_ADDR			0x58

/*return values */
#define RET_OK				0
#define RET_NOK				1

/*Buffer length macros */
#define LEN0				0
#define LEN1				1
#define LEN2				2

/* SGP30 command */
#define INIT_AIR_QUALITY		0x2003
#define MEASURE_AIR_QUALITY		0x2008
#define GET_BASELINE			0x2015
#define SET_BASELINE			0x201E
#define SET_HUMIDITY			0x2061
#define MEASURE_TEST			0x2032
#define GET_FEATURE_SET_VERSION		0x202F
#define GET_SERIAL_ID			0x3682
#define MEASURE_RAW_SIGNALs		0x2050

void delay_time();

uint16_t get_sgp30_sensor_data(struct metal_i2c *i2c);

void init_air_quality(struct metal_i2c *i2c);

void measure_air_quality(struct metal_i2c *i2c);

void get_baseline(struct metal_i2c *i2c);

void set_baseline(struct metal_i2c *i2c);

void set_humidity(struct metal_i2c *i2c);

void get_feature_set_version(struct metal_i2c *i2c);

void measure_raw_signals(struct metal_i2c *i2c);

void general_call_reset(struct metal_i2c *i2c);

void get_serial_ID(struct metal_i2c *i2c);

uint16_t measure_test(struct metal_i2c *i2c);

#endif
