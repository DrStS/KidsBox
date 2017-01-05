#!/usr/bin/python
import pymplb
import sys
import serial
import alsaaudio

kidsBoxPlayer = pymplb.MPlayer()
kidsBoxPlayer.loadlist('/home/pi/music/playlist')
ser = serial.Serial('/dev/ttyACM0', 9600)
ser.write('s')
kidsBoxMixer = alsaaudio.Mixer()
kidsBoxVolume = 48
kidsBoxMixer.setvolume(kidsBoxVolume)
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
                if pauseByte is 'u':
                        print("Increase volume")
                        kidsBoxVolume = int(kidsBoxVolume + 2)
                        if kidsBoxVolume < 66:
				print(kidsBoxVolume)
				kidsBoxMixer.setvolume(kidsBoxVolume)
			else:
				kidsBoxVolume = 66 
                if pauseByte is 'd':
                        print("Decrease volume")    
                        kidsBoxVolume = int(kidsBoxVolume - 2)
                        if kidsBoxVolume > 0:
                                kidsBoxMixer.setvolume(kidsBoxVolume)
			else:
				kidsBoxVolume = 0
except KeyboardInterrupt:
	ser.close()
