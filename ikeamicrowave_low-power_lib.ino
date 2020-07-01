#include "Tone.h"
#include <FastLED.h>
#include <LowPower.h>

#define LED_PIN 7
#define NUM_LEDS 8
#define SPKR1_PIN 8
#define SPKR2_PIN 6
#define INT_PIN 2
#define FETGATE_PIN 1
//#define FETGATE_PIN 5

CRGB leds[NUM_LEDS];
Tone tone1;
Tone tone2;

const int pippippiplength = 400;
const int pippippippause = 200;
const int microtime = 5000; 

void wakeUp() {
  // Just a handler for the pin interrupt
}

void setLedColor(CRGB color) {
  for (int i = 0; i <= (NUM_LEDS-1); i++) {
      leds[i] = color;
    }
    FastLED.show();
}

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(INT_PIN, INPUT);
  pinMode(FETGATE_PIN, OUTPUT);
  digitalWrite(FETGATE_PIN, LOW);

  //Serial.begin(9600);
  tone1.begin(SPKR1_PIN);
  tone2.begin(SPKR2_PIN);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS); //As soon as I add this line, the first LED turns on.
  //setLedColor(CRGB::Black);
}

// the loop function runs over and over again forever
void loop() {
  attachInterrupt(0, wakeUp, LOW);

  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

  detachInterrupt(0);

  digitalWrite(FETGATE_PIN, HIGH);
  
  tone1.play(NOTE_CS1, microtime);
  tone2.play(NOTE_E6, 200);
  setLedColor(CRGB::White);

  delay(microtime);

  tone2.play(NOTE_E6, pippippiplength);
  setLedColor(CRGB::Green);
  delay(pippippiplength);
  setLedColor(CRGB::Black);
  delay(pippippippause);
  tone2.play(NOTE_E6, pippippiplength);
  setLedColor(CRGB::Green);
  delay(pippippiplength);
  setLedColor(CRGB::Black);
  delay(pippippippause);
  tone2.play(NOTE_E6, pippippiplength);
  setLedColor(CRGB::Green);
  delay(pippippiplength);
  setLedColor(CRGB::Black);
  delay(pippippippause);

  digitalWrite(FETGATE_PIN, LOW);

}
