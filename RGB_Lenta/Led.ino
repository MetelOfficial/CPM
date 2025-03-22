#include "FastLED.h"
#define NUM_LEDS 100 //Кол-во светодиодов в сборке(если лень считать, то просто 100)
#define PIN 6        //Пин ленты
CRGB leds[NUM_LEDS];
byte counter;
void setup() {
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(50);  //Яркость ленты
}
void loop() {
  for (int i = 0; i < NUM_LEDS; i++ ) {        
    leds[i] = CHSV(counter + i * 2, 255, 255);   //Заменить counter + i * 2 на значение от 0 до 255, для изменение статичного цвета
  }
  counter++;    
  FastLED.show();
  delay(5);      
}
