#=====================================================================#
# Author:  Björn Guth                                                 #
# Date:    13.12.2016                                                 #
#                                                                     #
# Description: Code to control WS2812b chips with an Arduino          #
#                                                                     #
#=====================================================================#


set(CMAKE_TOOLCHAIN_FILE arduino-cmake/cmake/ArduinoToolchain.cmake)

cmake_minimum_required(VERSION 3.6)

project(ArduinoLEDControl C CXX)

set(fast_led_BOARD uno)
set(fast_led_SRCS FastLED/FastLED.cpp)
set(fast_led_HDRS FastLED/FastLED.h)

generate_arduino_library(fast_led)

set(led_control_BOARD uno)
set(led_control_SKETCH arduino-led-control.ino)
set(led_control_PORT /dev/ttyACM0)
set(led_control_LIBS fast_led)

generate_arduino_firmware(led_control)
