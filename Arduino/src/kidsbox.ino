//Global variables
int ledPinR = 9;  
int ledPinG = 18;   
int inputWhite=4;
unsigned char buffer[64];//UART buffer
int count = 0; 

void setup() {
Serial.begin(9600);//Connect to RasPi
Serial1.begin(9600);//Connect to RFID
pinMode(ledPinR, OUTPUT);
pinMode(ledPinG, OUTPUT);
pinMode(inputWhite, INPUT_PULLUP); 
}

void loop() {
 // Get data from RFID 
  if (Serial1.available())              
  {
    while(Serial1.available())               // reading data into char array
    {
      buffer[count++] = Serial1.read();      // writing data into array
      if(count == 64)break;
     }
     Serial.write(buffer, count);     // if no data transmission ends, write buffer to hardware serial port
     clearBufferArray();             // call clearBufferArray function to clear the stored data from the array
     count = 0;                      // set counter of while loop to zero
  }
// IO stuff 
  if(digitalRead(inputWhite)==LOW){
    digitalWrite(ledPinG, HIGH);
    digitalWrite(ledPinR, LOW);
  }
  else
  {
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinR, HIGH);
  }
}

void clearBufferArray()                 // function to clear buffer array
{
    // clear all index of array with command NULL
    for (int i=0; i<count; i++)
    {
        buffer[i]=0;
    }                  
}
