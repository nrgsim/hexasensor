set(ARDUINO_DEFAULT_BOARD diecimila) # Default Board ID, when not specified
set(ARDUINO_DEFAULT_PORT /dev/ttyACM0) # Default Port, when not specified
set(ARDUINO_CXX_FLAGS "${ARDUINO_C_FLAGS} -fno-exceptions")

#Include Adafruit modules to the project
include_directories(${Hexasensor_SOURCE_DIR}/adafruit)
LINK_DIRECTORIES(${Hexasensor_SOURCE_DIR}/adafruit)
link_libraries(adafruit)

generate_arduino_library(filter
    SRCS stat_filter.h
    BOARD uno)

generate_arduino_library(hexasensor
    SRCS hexasensor.cpp
    LIBS adafruit
    BOARD uno)

link_libraries(filter)
link_libraries(hexasensor)

generate_arduino_firmware(main
    SRCS main.cpp
    LIBS   adafruit hexasensor filter
    BOARD uno)
