#include "hexasensor.h"

#include "Arduino.h"
#include <Wire.h>

Hexasensor::Hexasensor(): htu(), tsl(TSL2561_ADDR_FLOAT, 12345), mcp()
{

}

Hexasensor* Hexasensor::get_singleton(){
  if(!s_instance)
    s_instance = new Hexasensor();
  return s_instance;
}

int Hexasensor::test_sensors()
{
  int state = SUCCESS;

  if (!mcp.begin())
    state += MCP9808_INIT_ERROR;

  if (!htu.begin())
    state += HTU21DF_INIT_ERROR;

  if (!tsl.begin())
    state += TSL2561_INIT_ERROR;

  //Return is void
  ads.begin();

  return state;
}

void Hexasensor::print_mesg(int error)
{
  if(error & HTU21DF_INIT_ERROR)
    Serial.println("HTU21DF_INIT_ERROR: Could not initialize!");
  if(error & TSL2561_INIT_ERROR)
    Serial.println("TSL2561_INIT_ERROR: Could not initialize!");
  if(error & MCP9808_INIT_ERROR)
    Serial.println("MCP9808_INIT_ERROR: Could not initialize!");
}

float Hexasensor::get_temperature()
{
  //Wake up the MCP9808
  mcp.shutdown_wake(0);

  float c = mcp.readTempC();
  //float f = c * 9.0 / 5.0 + 32; //Use for Farenheit

  delay(DELAY_TIME_MS);

  //Shut down the MCP9808
  mcp.shutdown_wake(1);

  return c;
}

float Hexasensor::get_humidity()
{
  return htu.readHumidity();
}

int Hexasensor::get_lux()
{
  sensors_event_t event;
  tsl.getEvent(&event);

  if(event.light)
    return event.light;
  else
    return 0;
}
