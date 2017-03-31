#include "Arduino.h"
#include <Wire.h>

//Include Adafruit Libraries
#include "Adafruit_MCP9808.h"
#include "Adafruit_TSL2561_U.h"
#include "Adafruit_HTU21DF.h"
#include "Adafruit_ADS1015.h"

#define SERIAL_BAUD     9600
#define DELAY_TIME_MS   100

//Initiate Device Contexts
Adafruit_HTU21DF htu = Adafruit_HTU21DF();
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
Adafruit_MCP9808 mcp = Adafruit_MCP9808();
Adafruit_ADS1015 ads;


void setup() {
  //Start Serial at 9600 baud rate
  Serial.begin(SERIAL_BAUD);

  //Verify sensors are present
  if (!mcp.begin()) {
    Serial.println("Couldn't find MCP9808!");
    while (1); }

  if (!htu.begin()) {
    Serial.println("Couldn't find HTU21DF!");
    while (1); }

  if (!tsl.begin()) {
    Serial.println("Couldn't find TSL2561!");
    while (1); }

}

float getTemperature()
{
  //NOTE: Function requires a delay of 250 ms

  //Wake up the MCP9808
  mcp.shutdown_wake(0);

  float c = mcp.readTempC();
  //float f = c * 9.0 / 5.0 + 32; //Use for Farenheit

  delay(250);

  //Shut down the MCP9808
  mcp.shutdown_wake(1);

  return c;
}



void loop() {
  //Apparently, TSL2561 needs an event
  sensors_event_t event;
  tsl.getEvent(&event);

  Serial.print(getTemperature()); Serial.print(", ");
  Serial.print(htu.readHumidity()); Serial.print(", ");
  if(event.light)
  {
	Serial.print(event.light);
  }
  else
  {
	Serial.print("0");
  }
  Serial.println(",");

  //Gather data from the ADS1015
 // int16_t adc3;

  //adc3 = ads.readADC_SingleEnded(3);
  //delay(DELAY_TIME_MS);
  //Serial.print("AIN3: "); Serial.println(adc3);

  delay(DELAY_TIME_MS);
}
