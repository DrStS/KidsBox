DEVICE     = atmega32u4
CLOCK      = 8000000
PROGRAMMER = -c avr109
HEXFILE    = kidsBox.ino.micro.hex
PORT       = /dev/ttyACM0
BITRATE    = 57600

# Tune the lines below only if you know what you are doing:

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE) -P $(PORT) -b ${BITRATE} -D 

flash:
	python reset.py $(PORT)
	sleep 1.5
	$(AVRDUDE) -U flash:w:../hex/$(HEXFILE):i
