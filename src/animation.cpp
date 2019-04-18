#include <animation.h>

void Animation::setup()
{
    FastLED
        .addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
}

void Animation::start()
{
    if (isRunning)
    {
        return;
    }

    isRunning = true;
    currentPalette = getAnimationPalette();
}

void Animation::stop()
{
    if (!isRunning)
    {
        return;
    }

    isRunning = false;
    currentPalette = getEmptyPalette();
}

CRGBPalette16 Animation::getEmptyPalette()
{
    CRGBPalette16 result;

    fill_solid(result, 16, CRGB::Black);

    return result;
}

CRGBPalette16 Animation::getAnimationPalette()
{
    CRGBPalette16 result;

    // 'black out' all 16 palette entries...
    fill_solid(result, 16, CRGB::Black);

    // and set every fourth one to white.
    result[0] = CRGB::Red;
    result[4] = CRGB::Red;
    result[8] = CRGB::Red;
    result[12] = CRGB::Red;

    return result;
}

void Animation::loop(byte speed)
{
    index += speed; // motion speed

    FillLEDsFromPaletteColors(index);

    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void Animation::FillLEDsFromPaletteColors(uint8_t colorIndex)
{
    uint8_t brightness = 255;

    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness, LINEARBLEND);

        colorIndex += 3;
    }
}