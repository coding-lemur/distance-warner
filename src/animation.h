#ifndef Animation_h
#define Animation_h

#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 5
#define LED_PIN 5
#define BRIGHTNESS 64
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 200

static uint8_t index = 0;

class Animation
{
  public:
    Animation();

    void setup();
    void start();
    void stop();
    void loop(byte speed);

  private:
    CRGBPalette16 currentPalette;
    CRGB leds[NUM_LEDS];
    bool isRunning;

    CRGBPalette16 getEmptyPalette();
    CRGBPalette16 getAnimationPalette();
    void FillLEDsFromPaletteColors(uint8_t colorIndex);
};
#endif