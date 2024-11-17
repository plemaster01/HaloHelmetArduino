#include <FastLED.h>
#define LED_PIN     3
#define NUM_LEDS    16

int COLOR_PIN = 9;
int MODE_PIN = 6;
int mode = 0;
int btnState = 0;
int lastState = 0;
int btnState2 = 0;
int lastState2 = 0;
int counter = 0;
int spot = 0;

CRGB leds[NUM_LEDS];
int color = 5;
int rgb_color[3] = {255, 0, 0};
int colors[6][3] = {{255,0,0}, {0, 255, 0}, {0, 0, 255}, {128, 0, 128}, {255, 255, 0}, {255, 255, 255}};

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(40); //Number 0-255
  FastLED.clear();
  FastLED.show();
  Serial.begin(9600);
  pinMode(COLOR_PIN, INPUT);
  pinMode(MODE_PIN, INPUT);
  rgb_color[0] = colors[color][0];
  rgb_color[1] = colors[color][1];
  rgb_color[2] = colors[color][2];
  FastLED.show();
  delay(10);
}


void mode_0() {
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB(rgb_color[0],rgb_color[1], rgb_color[2]);
  }
}

void mode_1() {
  for (int i = 0; i < 8; i++){
    leds[i] = CRGB(rgb_color[0],rgb_color[1], rgb_color[2]);
  }
}

void mode_2() {
  for (int i = 0; i < 8; i++){
    leds[i +8] = CRGB(rgb_color[0],rgb_color[1], rgb_color[2]);
  }
}

void mode_3(){
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB(rgb_color[0],rgb_color[1], rgb_color[2]);
  }
  spot = floor(counter/10);
  if (spot < 15) {
    FastLED.setBrightness(45 - (spot*3));
  }
  else {
    FastLED.setBrightness((spot - 15) * 3);
  }
}

void mode_4() {
  spot = floor(counter/19);
  leds[spot] = CRGB(rgb_color[0],rgb_color[1], rgb_color[2]);
  leds[15 - spot] = CRGB(rgb_color[0],rgb_color[1], rgb_color[2]);
}

void mode_5() {
  spot = floor(counter/19);
  leds[spot] = CRGB(rgb_color[0],rgb_color[1], rgb_color[2]);
}

void mode_6(){
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB(rgb_color[0],rgb_color[1], rgb_color[2]);
  }
  spot = floor(counter/10);
  if (spot < 15) {
    FastLED.setBrightness((spot*3));
  }
  else {
    FastLED.setBrightness(45 - ((spot - 15) * 3));
  }
}

void mode_7() {
  FastLED.clear();
  FastLED.setBrightness(40);
}

void loop() {
  counter++;
  FastLED.clear();
  FastLED.setBrightness(40);
  rgb_color[0] = colors[color][0];
  rgb_color[1] = colors[color][1];
  rgb_color[2] = colors[color][2];

  if (mode == 0){mode_0();}
  else if (mode == 1){mode_1();}
  else if (mode == 2){mode_2();}
  else if (mode == 3){mode_3();}
  else if (mode == 4){mode_4();}
  else if (mode == 5){mode_5();}
  else if (mode == 6){mode_6();}
  else {mode_7();}
  FastLED.show();

  btnState = digitalRead(COLOR_PIN);
  if (btnState == 1 && lastState == 0){color++;}
  btnState2 = digitalRead(MODE_PIN);
  if (btnState2 == 1 && lastState2 == 0){mode++;}
  
  lastState = btnState;
  lastState2 = btnState2;
  
  if (mode > 7){mode = 0;}
  if (counter >= 300){
    if (mode == 6){color++;}
    counter = 0;}
  if (color > 5){color = 0;}
  delay(5);
}