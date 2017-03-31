set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake) # Arduino Toolchain


cmake_minimum_required(VERSION 2.8)

project(Hexasensor C CXX)

print_board_list()
print_programmer_list()

add_subdirectory(adafruit)
add_subdirectory(hexasensor)   #add the example directory into build
