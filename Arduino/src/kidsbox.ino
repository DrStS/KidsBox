
#define PIN_LED_RED 9
#define PIN_LED_GREEN 18
#define PIN_BUTTON_VOL_PLUS  8
#define PIN_BUTTON_VOL_MINUS 7
#define PIN_BUTTON_PAUSE 5
#define PIN_BUTTON_FORWARD 6
#define PIN_BUTTON_BACKWARD 4


unsigned char pauseByte = 'r';
unsigned char RFIDbuffer[14];       // buffer array for data receive over serial port
int RFIDcount = 0;                  // counter for buffer array
unsigned char RFID[6];       // buffer array for data receive over serial port

void setup()
{
Serial.begin(9600);//Connect to RasPi
Serial1.begin(9600);//Connect to RFID
pinMode(PIN_LED_RED, OUTPUT);
pinMode(PIN_LED_GREEN, OUTPUT);
pinMode(PIN_BUTTON_VOL_PLUS, INPUT_PULLUP); 
pinMode(PIN_BUTTON_VOL_MINUS, INPUT_PULLUP); 
pinMode(PIN_BUTTON_PAUSE, INPUT_PULLUP); 
pinMode(PIN_BUTTON_FORWARD, INPUT_PULLUP); 
pinMode(PIN_BUTTON_BACKWARD, INPUT_PULLUP);


while (Serial.available() == 0){
//Wait for Raspi to be ready
}

if (Serial.read()=='s'){
digitalWrite(PIN_LED_GREEN, HIGH);
}

}

void loop()
{

  if(digitalRead(PIN_BUTTON_VOL_PLUS)==HIGH){
	Serial.write('u');
    digitalWrite(PIN_LED_RED, HIGH);
  }
  
  if(digitalRead(PIN_BUTTON_VOL_MINUS)==HIGH){
	Serial.write('d');
    digitalWrite(PIN_LED_RED, HIGH);
  }

  if(digitalRead(PIN_BUTTON_PAUSE)==HIGH){
   if(pauseByte =='r'){
     pauseByte = 'p';
   }else if(pauseByte =='p'){
     pauseByte = 'r';
   }
    Serial.write(pauseByte);
    digitalWrite(PIN_LED_RED, HIGH);	
  }
  
  if(digitalRead(PIN_BUTTON_FORWARD)==HIGH){
	Serial.write('f');
    digitalWrite(PIN_LED_RED, HIGH);
  }
  
  if(digitalRead(PIN_BUTTON_BACKWARD)==HIGH){
    Serial.write('b');
    digitalWrite(PIN_LED_RED, HIGH);
  }

	while(Serial1.available())    
	{
		RFIDbuffer[RFIDcount++] = Serial1.read();
		if(RFIDcount == 14)break;
	}
	RFID[0]=RFIDbuffer[5];
	RFID[1]=RFIDbuffer[6];
	RFID[2]=RFIDbuffer[7];
	RFID[3]=RFIDbuffer[8];
	RFID[4]=RFIDbuffer[9];
	RFID[5]=RFIDbuffer[10];
	if(RFIDcount>0){
		Serial.write('q');
		Serial.write(RFID, 6); 
	}	
  
// Clean state
clearBufferArray(); 
RFIDcount = 0; 
delay(100);
digitalWrite(PIN_LED_RED, LOW);
}
void clearBufferArray()                 // function to clear buffer array
{
    // clear all index of array with command NULL
    for (int i=0; i<RFIDcount; i++)
    {
        RFIDbuffer[i]=NULL;
    }                  
}