#include "hexasensor.h"
#include "Arduino.h"
#include <Wire.h>

//Allocate the Hexasensor Singleton Instance to NULL
Hexasensor* Hexasensor::s_instance = NULL;

void setup() {

  Serial.begin(SERIAL_BAUD);

  int err = Hexasensor::get_singleton()->test_sensors();

  //Check for errors
  if(err != SUCCESS)
  {
     Hexasensor::get_singleton()->print_mesg(err);
    while(1);
  }

}


void loop() {

  Serial.print((Hexasensor::get_singleton())->get_temperature()); Serial.print(", ");
  Serial.print((Hexasensor::get_singleton())->get_humidity()); Serial.print(", ");
  Serial.print((Hexasensor::get_singleton())->get_lux()); Serial.println(", ");

  //delay(DELAY_TIME_MS);
}
