#ifndef HEXASENSOR_H
#define HEXASENSOR_H

/*==============================================================================
hexasensor.h

author: Ethan Lew

The Hexasensor class creates an object of the Hexasensor prototype. It is a
Singleton enforced class and implements procedures on the I2C bus.
==============================================================================*/

#include "Adafruit_MCP9808.h"
#include "Adafruit_TSL2561_U.h"
#include "Adafruit_HTU21DF.h"
#include "Adafruit_ADS1015.h"

#define DELAY_TIME_MS      250
#define SERIAL_BAUD        9600

//HEXASENSOR_STATES
#define SUCCESS            (0)
#define HTU21DF_INIT_ERROR (1<<0)
#define TSL2561_INIT_ERROR (1<<1)
#define MCP9808_INIT_ERROR (1<<2)
#define ADS1115_INIT_ERROR (1<<3)

class Hexasensor
{
public:
  static Hexasensor* get_singleton();
  int test_sensors();
  void print_mesg(int);

  float get_temperature();
  float get_humidity();
  int   get_lux();


private:
  Hexasensor();

  static Hexasensor* s_instance;

  Adafruit_HTU21DF htu;
  Adafruit_TSL2561_Unified tsl;
  Adafruit_MCP9808 mcp;
  Adafruit_ADS1015 ads;
};

#endif
