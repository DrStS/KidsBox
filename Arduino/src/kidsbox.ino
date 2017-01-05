
#define PIN_LED_RED 9
#define PIN_LED_GREEN 18
#define PIN_BUTTON_VOL_PLUS  8
#define PIN_BUTTON_VOL_MINUS 7
#define PIN_BUTTON_PAUSE 5
#define PIN_BUTTON_FORWARD 6
#define PIN_BUTTON_BACKWARD 4

unsigned char pauseByte = 'r';

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



// Clean state
digitalWrite(PIN_LED_RED, LOW);
delay(300);
}
