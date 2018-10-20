#include <Wtv020sd16p.h>
#include <Metro.h>




//////////////////////////////// HARTSLAG //////////////////////////////////////


const unsigned char _heartbeat_values[]  = {21,21,21,21,21,21,21,21,21,21,21,21,21,22,23,25,
  28,34,42,54,71,92,117,145,175,203,228,246,255,254,242,220,191,157,121,87,
  58,34,17,6,1,0,2,5,9,13,16,18,19,20,21,21,21,21,21,21,21,21,21,21,21,21,21,21};
const unsigned char _HEARTBEAT_INDEXES = 64;

byte ledPin = 9; //Must be PWM capable pin

//int heartbeat_period = 500; //[ms] 60000/120 (120 beats x min, baby) 
//int heartbeat_period = 857; //[ms] 60000/70 (70 beats x min, adult in rest) 
int heartbeat_period = 1000; // slower, feels like soothing


void heartbeat()
{
  int index = (millis()%heartbeat_period) * _HEARTBEAT_INDEXES / heartbeat_period;
  analogWrite(ledPin, _heartbeat_values[index]);
}

///////////////////////////////// AUDIO //////////////////////////////////////////

int resetPin = 2; 
int clockPin = 3;  
int dataPin = 4;  
int busyPin = 5;

Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin); 

void playSong()
{
    //wtv020sd16p.asyncPlayVoice(0);
    //wtv020sd16p.pauseVoice();
}

///////////////////////////////// SENSOR /////////////////////////////////////////

int pressPin = 0;
int pressValue = 0; 

int pressTimer = 0;

int pressTimerSwitch = 0;
int pressPlaySwitch = 0;


///////////////////////////// FUNCTIE SWITCH //////////////////////////////////////

int index2 = (millis()%heartbeat_period) * _HEARTBEAT_INDEXES / heartbeat_period;

Metro LampjesMetro = Metro(index2);
Metro HartslagMetro = Metro(index2);


//////////////////////////// DELAY VERVANGING /////////////////////////////////////


unsigned long interval = 1000; // the time we need to wait
unsigned long previousMillis = 0; // millis() returns an unsigned long.

///////////////////////////////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600); 
  pinMode(ledPin,OUTPUT); 

  wtv020sd16p.reset();
}

void loop()
{

  //wtv020sd16p.playVoice(3);

  
  pressValue = analogRead(pressPin);
  unsigned long currentMillis = millis();

  //Serial.println(pressValue);
  Serial.println(pressTimer);
  //Serial.println(pressTimerSwitch);
  
  if (pressValue > 600)
  {
      pressTimerSwitch = +1; 
      pressPlaySwitch = +1;  
  }


  if (pressTimerSwitch == 1)
  {
      pressTimer = pressTimer + 1;
      
      if(LampjesMetro.check())
      {
        heartbeat();
        Serial.println("Lampje");
        Serial.println(" ");
      }
      if(LampjesMetro.check())
      {
        playSong();
        Serial.println("Liedje");
        Serial.println(" ");
        
        //wtv020sd16p.asyncPlayVoice(0);
        //delay(100);
        //wtv020sd16p.pauseVoice();
        
         //if ((unsigned long)(currentMillis - previousMillis) >= interval) 
         //{
          //wtv020sd16p.pauseVoice();
          // save the "current" time
          //previousMillis = millis();
          //}
        //delay(100);
        
      }
      
  }

  if (pressTimerSwitch == 0)
  {
      analogWrite(ledPin,21);
  }

  if (pressTimer == 2000)
  {
      pressTimerSwitch = 0;
      pressPlaySwitch = 0;
      pressTimer = 0;
  }
 
}
