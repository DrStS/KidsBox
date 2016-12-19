import serial
ser = serial.Serial('/dev/ttyACM0', 9600)
#ser.open()
try:
  while 1
    response=ser.read(12)
    print response
    if response is '4A0019C03FA'
        print 'You are lucky!'
except KeyboardInterrupt:
    ser.close()
