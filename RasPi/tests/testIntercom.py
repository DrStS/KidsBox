import serial
ser = serial.Serial('/dev/ttyACM0', 9600)
#ser.open()
try:
  while 1:
    response = ser.readline()
    print response
except KeyboardInterrupt:
    ser.close()
