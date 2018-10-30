#include <Wtv020sd16p.h>

///////////////////////////////// AUDIO //////////////////////////////////////////

int resetPin = 2; 
int clockPin = 3;  
int dataPin = 4;  
int busyPin = 5;

Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin); 

//////////////////////////////// HARTSLAG //////////////////////////////////////


const unsigned char _heartbeat_values[]  = {21,21,21,21,21,21,21,21,21,21,21,21,21,22,23,25,
  28,34,42,54,71,92,117,145,175,203,228,246,255,254,242,220,191,157,121,87,
  58,34,17,6,1,0,2,5,9,13,16,18,19,20,21,21,21,21,21,21,21,21,21,21,21,21,21,21};
const unsigned char _HEARTBEAT_INDEXES = 64; //64

byte ledPin = 9; //Must be PWM capable pin

//int heartbeat_period = 500; //[ms] 60000/120 (120 beats x min, baby) 
//int heartbeat_period = 857; //[ms] 60000/70 (70 beats x min, adult in rest) 
int heartbeat_period = 1000; // slower, feels like soothing


void heartbeat()
{ 
   int index = (millis()%heartbeat_period) * _HEARTBEAT_INDEXES / heartbeat_period;
   analogWrite(ledPin, _heartbeat_values[index]);
}

///////////////////////////////// SENSOR /////////////////////////////////////////

int pressPin = 0;
int pressValue = 0; 

int pressTimer = 0;

int pressTimerSwitch = 0;

boolean finished = false;

///////////////////////////////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600); 
  pinMode(ledPin,OUTPUT); 

  wtv020sd16p.reset();
  heartbeat();
}

void loop()
{
  pressValue = analogRead(pressPin);

  //Serial.println(pressValue);
  //Serial.println(pressTimer);
  //Serial.println(pressTimerSwitch);
  
  if (pressValue > 600)
  {
      pressTimerSwitch = +1; 
  }


  if (pressTimerSwitch == 1)
  {
      wtv020sd16p.asyncPlayVoice(0);
      delay(15);
      while (digitalRead(busyPin) == HIGH and pressTimer < 1920)
      {
          Serial.println(pressTimer);
          pressTimer = pressTimer +1;
          
          heartbeat();
      }
      delay(10); 
      finished = true;
  }

  if (pressTimer == 50)
  {
      pressTimerSwitch = 0;
      pressTimer = 0;
  }

  if (finished == true)
  {
      pressTimerSwitch = 0;
      pressTimer = 0;
  }
 
}
