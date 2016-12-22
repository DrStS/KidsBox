#!/usr/bin/python
import pymplb
import sys
import serial


kidsBoxPlayer = pymplb.MPlayer()
kidsBoxPlayer.loadfile('/home/pi/music/test.mp3')
ser = serial.Serial('/dev/ttyACM0', 9600)
ser.write('s')
print("== KidsBox ready! ==")

try:
	while 1:
		pauseByte=ser.read(1)
		if pauseByte is 'r':
			print("Resume")
			kidsBoxPlayer.set_property('pause','no')
		if pauseByte is 'p':		
			print("Pause")
			kidsBoxPlayer.set_property('pause','yes')
except KeyboardInterrupt:
	ser.close()
