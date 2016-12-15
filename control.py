#!/usr/bin/python3

import serial
import time
import sys

ser = serial.Serial('/dev/ttyACM0', 9600)

#ser_in = ser.read()
#print(ser_in)
time.sleep(1)

ser.write(sys.argv[1].encode())

if sys.argv[1] == "1":
	print(ser.read())
	if len(sys.argv) <= 2:
		ser.write('-1'.encode())
	else:
		ser.write(sys.argv[2].encode())
		print(ser.read())
		ser.write(sys.argv[3].encode())
		print(ser.read())
		ser.write(sys.argv[4].encode())

ser.close()
