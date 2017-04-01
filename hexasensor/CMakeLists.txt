set(ARDUINO_DEFAULT_BOARD diecimila) # Default Board ID, when not specified
set(ARDUINO_DEFAULT_PORT /dev/ttyACM0) # Default Port, when not specified

#Include Adafruit modules to the project
include_directories(${Hexasensor_SOURCE_DIR}/adafruit)
LINK_DIRECTORIES(${Hexasensor_SOURCE_DIR}/adafruit)
link_libraries(adafruit)

generate_arduino_library(filter
    SRCS stat_filter.h
    BOARD uno)

link_libraries(filter)

generate_arduino_firmware(hexasensor
    SRCS main.cpp
    LIBS adafruit filter
    BOARD uno)
