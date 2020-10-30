#include <Arduino.h>
#include <FastLED.h>
#include "HX711.h"

// How many leds in your strip?
#define NUM_LEDS 50

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 11
long startmillis;
long delaytime=3000;
long currmillis;
int ledreleasedelay=300;
long putbackdelay=3000;

// Define the array of leds
HX711 scaleA;
HX711 scaleB;
CRGB leds[NUM_LEDS];
const int RELAY_PIN1 = 5; //pinkki
const int RELAY_PIN2 = 2; //sininen
const int RELAY_PIN3 = 3; //oranssi
const int RELAY_PIN4 = 6; //vihreä
const int RELAY_PIN5 = 4; //punainen
const int LOADCELL1_DOUT_PIN = 7;
const int LOADCELL1_SCK_PIN = 8;
const int LOADCELL2_DOUT_PIN = 9;
const int LOADCELL2_SCK_PIN = 10;
int randport;
long readingA;
long readingB;
long startreadingA;
long startreadingB;
long score;
boolean gameplay;
// the setup function runs once when you press reset or power the board
void setup() {
   Serial.begin(9600);
scaleA.begin(LOADCELL1_DOUT_PIN, LOADCELL1_SCK_PIN);
scaleB.begin(LOADCELL2_DOUT_PIN, LOADCELL2_SCK_PIN);
   randomSeed(analogRead(A0));  
 
  
   FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  // initialize digital pin 9 as an output.
  pinMode(RELAY_PIN1, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);
  pinMode(RELAY_PIN3, OUTPUT);
  pinMode(RELAY_PIN4, OUTPUT);
  pinMode(RELAY_PIN5, OUTPUT);
  digitalWrite(RELAY_PIN1, LOW); //magneetti 1 releinput 4
  digitalWrite(RELAY_PIN2, LOW);  //magneetti 5 releinput 3
  digitalWrite(RELAY_PIN3, LOW); //magneetti 3 releinput 2
  digitalWrite(RELAY_PIN4, LOW); //magneetti 2 releinput 1
  digitalWrite(RELAY_PIN5, LOW); //magneetti 4 releinput 5
  delay(15000);
   if  (scaleA.is_ready()) {
  startreadingA=scaleA.read();
  Serial.print("HX711 channel A startreading: ");
      Serial.println(startreadingA);
  }
   if  (scaleB.is_ready()) {
  startreadingB=scaleB.read();
  Serial.print("HX711 channel B startreading: ");
      Serial.println(startreadingB);
  }

  gameplay=true;
    startmillis=millis();
}
long scalesensorA()
{
   if (scaleA.wait_ready_retry(10)) {
        readingA = scaleA.read();
       
      Serial.print("HX711 channel A reading: ");
      Serial.println(readingA);
      return readingA;
   }
     else 
       {
       return 0;
       }
}
    long scalesensorB()
    {
    if (scaleB.wait_ready_retry(10)) {
       readingB = scaleB.read();
         Serial.print("HX711 channel B reading: ");
      Serial.println(readingB);
       Serial.println(startreadingB-readingB);
       return readingB;
    }
       else 
       {
       return 0;
       }
      
    }

// the loop function runs over and over again forever
void loop() {

 currmillis=millis();
 if ((currmillis -startmillis <=1000) && (gameplay==true)) {
  randport=random(2,7);
    //randport=3;
     Serial.println ("randport ");
      Serial.println (randport);
     delaytime=delaytime*0.99;
   putbackdelay=putbackdelay*0.95;
  if (randport==RELAY_PIN1) {
  
  FastLED.showColor(CRGB::DeepPink);
  delay(delaytime);
   scalesensorA();
   scalesensorB();
    if ((startreadingA-readingA<=10000)||(startreadingB-readingB<=10000))
  {
  digitalWrite(randport, HIGH);
  delay(ledreleasedelay);
  digitalWrite(randport, LOW);
  delay(putbackdelay);
  score++;
  }
  else gameplay=false;
 }
if (randport==RELAY_PIN2) {
  FastLED.showColor(CRGB::Blue);
  delay(delaytime); 
  scalesensorA();
   scalesensorB();
   if ((startreadingA-readingA<=10000)||(startreadingB-readingB<=10000))
  {
  digitalWrite(randport, HIGH);
  delay(ledreleasedelay);
  digitalWrite(randport, LOW);
  delay(putbackdelay);
  score++;
  }
else gameplay=false;
  }
  if (randport==RELAY_PIN3)  {
  FastLED.showColor(CRGB::OrangeRed);
  delay(delaytime);
  scalesensorA();
   scalesensorB();
    if ((startreadingA-readingA<=10000)||(startreadingB-readingB<=10000))
  {
  digitalWrite(randport, HIGH);
  delay(ledreleasedelay);
  digitalWrite(randport, LOW);
  delay(putbackdelay);
  score++;
  }
  else gameplay=false;
  }
if (randport==RELAY_PIN4)  {
  FastLED.showColor(CRGB::Green);
  delay(delaytime);
    scalesensorA();
   scalesensorB();
 if ((startreadingA-readingA<=10000)||(startreadingB-readingB<=10000))
  {
  digitalWrite(randport, HIGH);
  delay(ledreleasedelay);
  digitalWrite(randport, LOW);
  delay(putbackdelay);
  score++;
  }
  else gameplay=false;
  }
  if (randport==RELAY_PIN5) {
  FastLED.showColor(CRGB::Red);
  delay(delaytime);
   scalesensorA();
   scalesensorB();
 if ((startreadingA-readingA<=10000)||(startreadingB-readingB<=10000))
  {
  digitalWrite(randport, HIGH);
  delay(ledreleasedelay);
  digitalWrite(randport, LOW);
  delay(putbackdelay);
  score++;
  }
  else gameplay=false;

  }
 
 


 }

 startmillis=currmillis;
 if (gameplay==false) 
 {
 FastLED.showColor(CRGB::Black);
   Serial.println("pisteesi");
   Serial.print(score);
  delay(1000);
   FastLED.showColor(CRGB::White);
   delay(1000);
 }
}

