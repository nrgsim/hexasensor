# Hexasensor
This repository contains the arduino code for the hexasensor. It uses the CMake build process utility to generate makefiles, compile and upload to the board. Also, it contains several Adafruit sensor libraries.

#Build

## Dependencies
Hexasensor requires these dependencies in order to build and upload to the arduino.

	cmake
	avr-g++
	avrdude


To build and upload to the arduino, execute these commands
```
./configure
cd build
make
make upload
```

View the output on screen

```
screen \dev\ttyACM0 9600
```
NOTE: the device may differ on your machine. Check for the name in the /dev folder.

#Resources
These github projects are used in the hexasensor:
- [MCP9808](https://github.com/adafruit/Adafruit_MCP9808_Library)
- [HTU21D Library](https://github.com/adafruit/Adafruit_HTU21DF_Library)
- [TSL2561 Library](https://github.com/adafruit/TSL2561-Arduino-Library)
- [ADS1X15 Library](https://github.com/adafruit/Adafruit_ADS1X15)
- [Arduino CMake](https://github.com/queezythegreat/arduino-cmake)
