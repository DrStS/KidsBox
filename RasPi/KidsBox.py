#!/usr/bin/python
import pymplb
import sys
import serial
import alsaaudio
import time
import os
from random import randint
#Get my files
myMusicFolder= '/home/pi/music/'
myMusicFiles = filter(lambda x: x.endswith('.mp3'), os.listdir(myMusicFolder))
myNumMusicFiles = len(myMusicFiles)-1

kidsBoxPlayer = pymplb.MPlayer()
kidsBoxPlayer.loadfile(myMusicFolder+myMusicFiles[randint(0,myNumMusicFiles)])
#kidsBoxPlayer.loadlist('http://www.rockantenne.de/webradio/rockantenne.m3u')
ser = serial.Serial('/dev/ttyACM0', 9600)
ser.write('s')
kidsBoxMixer = alsaaudio.Mixer()
kidsBoxVolume = 48
kidsBoxVolumeMax = 62
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
                        if kidsBoxVolume < kidsBoxVolumeMax:
				print(kidsBoxVolume)
				kidsBoxMixer.setvolume(kidsBoxVolume)
			else:
				kidsBoxVolume = kidsBoxVolumeMax
                if pauseByte is 'd':
                        print("Decrease volume")    
                        kidsBoxVolume = int(kidsBoxVolume - 2)
                        if kidsBoxVolume > 0:
                                kidsBoxMixer.setvolume(kidsBoxVolume)
			else:
				kidsBoxVolume = 0
                if pauseByte is 'f':
                        print("Forward")
                        fileNameTmp=myMusicFolder+myMusicFiles[randint(0,myNumMusicFiles)]
                        print(fileNameTmp)
                        kidsBoxPlayer.loadfile(fileNameTmp)
                if pauseByte is 'b':
                        print("Backward")
                        kidsBoxPlayer.loadfile(myMusicFolder+myMusicFiles[randint(0,myNumMusicFiles)])
except KeyboardInterrupt:
	ser.close()
