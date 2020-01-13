#!/usr/bin/python
import sys
import serial
import time
import os
from random import randint
#Get my files
myMusicFolder= '/data/INTERNAL/'
myMusicFiles = list(filter(lambda x: x.endswith('.mp3'), os.listdir(myMusicFolder)))
myNumMusicFiles = len(myMusicFiles)-1
ser = serial.Serial('/dev/ttyACM0', 9600)
ser.write(str.encode('s'))
kidsBoxVolume = 48
kidsBoxVolumeMax = 62
os.system("volumio volume {}".format(kidsBoxVolume))
print("== KidsBox ready! ==")

try:
    while 1:
        pauseByte=ser.read(1)
        if pauseByte is 'r':
            print("Resume")
            os.system("volumio toggle")
        if pauseByte is 'p':		
            print("Pause")
            os.system("volumio toggle")            
        if pauseByte is 'u':
            print("Increase volume")
            kidsBoxVolume = int(kidsBoxVolume + 2)
            if kidsBoxVolume < kidsBoxVolumeMax:
                print(kidsBoxVolume)
                os.system("volumio volume {}".format(kidsBoxVolume))
        if pauseByte is 'd':
            print("Decrease volume")    
            kidsBoxVolume = int(kidsBoxVolume - 2)
            if kidsBoxVolume > 0:
                print(kidsBoxVolume)
                os.system("volumio volume {}".format(kidsBoxVolume))
            else:
                kidsBoxVolume = 0
        if pauseByte is 'f':
            print("Forward")
            os.system("volumio next")
        if pauseByte is 'b':
            print("Backward")
            os.system("volumio previous")
        if pauseByte is 'q':
            print("RFID read")
            RFIDvalue=ser.read(6)
            print(RFIDvalue)
            if str(RFIDvalue) == '193D74':
                print("RFID CARD 1")
                os.system("wget -qO- http://localhost:3000/api/v1/commands/?cmd='playplaylist&name=rockantenne'")
            if str(RFIDvalue) == '1CC9DE':
                print("RFID CARD 2")
                #kidsBoxPlayer.quit()
        time.sleep(0.1)
        pauseByte='N'				
except KeyboardInterrupt:
	ser.close()
