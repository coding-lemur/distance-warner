#ifndef Animation_h
#define Animation_h

#include <FastLED.h>

#define NUM_LEDS 5
#define LED_PIN 5
#define BRIGHTNESS 64
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 200

class Animation
{
  public:
    void setup();
    void start();
    void stop();
    void loop(byte speed);

  private:
    CRGBPalette16 currentPalette = getEmptyPalette();
    CRGB leds[NUM_LEDS];
    bool isRunning = false;
    uint8_t index = 0;

    CRGBPalette16 getEmptyPalette();
    CRGBPalette16 getAnimationPalette();
    void FillLEDsFromPaletteColors(uint8_t colorIndex);
};
#endif