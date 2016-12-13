#=====================================================================#
# Author:  Björn Guth                                                 #
# Date:    13.12.2016                                                 #
#                                                                     #
# Description: Code to control WS2812b chips with an Arduino          #
#                                                                     #
#=====================================================================#


set(CMAKE_TOOLCHAIN_FILE ~/git/arduino-cmake/cmake/ArduinoToolchain.cmake)

cmake_minimum_required(VERSION 3.6)

project(ArduinoLEDControl C CXX)

print_board_list()
print_programmer_list()

set(led_control_BOARD uno)
set(led_control_SKETCH arduino-led-control.ino)
set(led_control_PORT /dev/ttyACM0)

generate_arduino_firmware(led_control)
