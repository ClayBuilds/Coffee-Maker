#include "RTClib.h"
RTC_PCF8523 rtc;

const int gohour = 5;       //hour the coffee maker should turn on
const int gominute = 50;      //minute to turn on. this example starts at 5:50am
const int outpin = 12;      //pin wired to relay
const int inpin = 11;       //pin wired to button
const int res = 1; //reset clock to compile time during setup. Change to 0 and reflash code once RTC time is correct
int toggle = 0;

void setup () 
{
    Serial.begin(9600);
    Serial.flush();

rtc.begin();

  if (res)
  {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));   //reset clock time to compiler PC time
  }

  pinMode(outpin, OUTPUT);
  pinMode(inpin, INPUT_PULLUP);
}

void loop () 
{
    DateTime now = rtc.now();       //get current time
    int Hour = now.hour();
    int Minute = now.minute();
    
    Serial.print(Hour);             //print time to serial monitor
    Serial.print(" : ");
    Serial.println(Minute);

    int button = !digitalRead(inpin);       //check button status

    if((Hour==gohour)&&(Minute==gominute))     //turn on when time reached
    {
        digitalWrite(outpin, HIGH);
        toggle = 1;
    }

    if(button)
    {
      while (button)
      {
        button = !digitalRead(inpin);  //wait until button is released
      }
      if (!toggle)
       {
        digitalWrite(outpin, HIGH);   //turn coffee on if its currently off
        toggle = 1;
       }
      else
      {
        digitalWrite(outpin, LOW);    //turn coffee off if itc currently on
        toggle = 0;
      }
       
    }
}
    
