#include "FastLED.h"
#include <OneWire.h> 
#include <DallasTemperature.h>

/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/
int led7type1[10][21] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1}
};
int led7type2[10][21] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int temp = 0;
int temp1 = 0;
int temp2 = 0;
int i;

#define LED_FULL_BUS 3
#define NUM_LEDS 50
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<UCS1903, LED_FULL_BUS>(leds, NUM_LEDS);
  //Serial.begin(9600);
}

void writeLed7(int type, int offset, int value){
  for( i = 0 ; i < 21; i++ ){
    if( type == 1 ){
      if( led7type1[value][i] > 0 ){
        leds[offset + i] = CRGB::Blue;
      } else {
        leds[offset + i] = CRGB::Black;
      }
    } else {
      if( led7type2[value][i] > 0 ){
        leds[offset + i] = CRGB::Blue;
      } else {
        leds[offset + i] = CRGB::Black;
      }
    }
  }
}

void writeSpecial(int offset, int len, int value){
  for( i = offset; i < offset + len; i++ ){
    if( value > 0 ){
      leds[i] = CRGB::Blue;
    } else {
      leds[i] = CRGB::Black;
    }
  }
}

void loop() {
//  leds[0] = CRGB::White; FastLED.show(); delay(30);
//  //Example 1: set color from red, green, and blue components individually
//  leds[i].red =    50;
//  leds[i].green = 100;
//  leds[i].blue =  150;
//
//  //Example 2: set color from red, green, and blue components all at once
//  leds[i] = CRGB( 50, 100, 150);

  sensors.requestTemperatures(); // Send the command to get temperature readings
  /********************************************************************/
  temp = (int)sensors.getTempCByIndex(0);
  // Convert
  if(temp > 9){
    temp1 = temp/10;
    temp2 = temp%10;
  } else {
    temp1 = 0;
    temp2 = temp;
  }
//  Serial.print(temp);
//  Serial.print(" ");
//  Serial.print(temp1);
//  Serial.print(" ");
//  Serial.println(temp2);
  // write out
  writeLed7(1, 0,  temp1);
  writeLed7(2, 22, temp2);
  writeSpecial(44, 6, 1);
  FastLED.show();
  // delay 0.5s
  delay(500);
}

