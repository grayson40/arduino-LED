#include "FastLED.h"
#include "RTClib.h"

#define NUM_LEDS 400
#define DATA_PIN 11
#define FORWARD 0
#define BACKWARD 1
#define SLOW 100
#define MEDIUM 50
#define FAST 5

// RTC object.
RTC_DS3231 rtc;

// LED strip array.
CRGB leds[NUM_LEDS];

boolean direction = FORWARD;

void setup()
{
    // Initialize LED strip.
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(20);

    // Initialize serial.
    Serial.begin(115200);
    Serial.setTimeout(1);

    // Seed random.
    randomSeed(analogRead(0));
}

void loop()
{
    // Get rtc data.
    DateTime now = rtc.now();

    // Lights off from 11PM - 9AM.
    if (now.hour() >= 23 || now.hour() <= 9)
    {
        allColor(CRGB::Black);
    }
    else
    {
        while (!Serial.available())
            ;
        int choice = Serial.readString().toInt();
        switch (choice)
        {
        case 1:
            colorWipe(CRGB::Blue, SLOW, 1);
            break;

        case 2:
            rainbow(1, SLOW);
            break;

        case 3:
            theaterChaseRainbow(1, MEDIUM);
            break;

        case 4:
            stripes(CRGB::Blue, CRGB::Red, 10);
            break;

        case 5:
            cylon(CRGB::Blue, 30, FAST);
            break;

        default:
            break;
        }
    }
}

// Changes all LEDS to given color
void allColor(CRGB c)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = c;
    }
    FastLED.show();
}

void allRandom()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = randomColor();
    }
    FastLED.show();
}

// Random disolve colors
void disolve(int simultaneous, int cycles, int speed)
{
    for (int i = 0; i < cycles; i++)
    {
        for (int j = 0; j < simultaneous; j++)
        {
            int idx = random(NUM_LEDS);
            leds[idx] = CRGB::Black;
        }
        FastLED.show();
        delay(speed);
    }

    allColor(CRGB::Black);
}

// Flashes given color
// If c==NULL, random color flash
void flash(CRGB c, int count, int speed)
{
    for (int i = 0; i < count; i++)
    {
        if (c)
        {
            allColor(c);
        }
        else
        {
            allColor(randomColor());
        }
        delay(speed);
        allColor(CRGB::Black);
        delay(speed);
    }
}

// Wipes color from end to end
void colorWipe(CRGB c, int speed, int direction)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        if (direction == FORWARD)
        {
            leds[i] = c;
        }
        else
        {
            leds[NUM_LEDS - 1 - i] = c;
        }
        FastLED.show();
        delay(speed);
    }
}

// Rainbow colors that slowly cycle across LEDs
void rainbow(int cycles, int speed)
{
    if (cycles == 0)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i] = Wheel(((i * 256 / NUM_LEDS)) & 255);
        }
        FastLED.show();
    }
    else
    {
        for (int j = 0; j < 256 * cycles; j++)
        {
            for (int i = 0; i < NUM_LEDS; i++)
            {
                leds[i] = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
            }
            FastLED.show();
            delay(speed);
        }
    }
}

// Theater-style crawling lights
void theaterChase(CRGB c, int cycles, int speed)
{
    for (int j = 0; j < cycles; j++)
    {
        for (int q = 0; q < 3; q++)
        {
            for (int i = 0; i < NUM_LEDS; i = i + 3)
            {
                int pos = i + q;
                leds[pos] = c; // turn every third pixel on
            }
            FastLED.show();

            delay(speed);

            for (int i = 0; i < NUM_LEDS; i = i + 3)
            {
                leds[i + q] = CRGB::Black; // turn every third pixel off
            }
        }
    }
}

// Theater-style crawling lights with rainbow effect
void theaterChaseRainbow(int cycles, int speed)
{
    for (int j = 0; j < 256 * cycles; j++)
    { // cycle all 256 colors in the wheel
        for (int q = 0; q < 3; q++)
        {
            for (int i = 0; i < NUM_LEDS; i = i + 3)
            {
                int pos = i + q;
                leds[pos] = Wheel((i + j) % 255); // turn every third pixel on
            }
            FastLED.show();

            delay(speed);

            for (int i = 0; i < NUM_LEDS; i = i + 3)
            {
                leds[i + q] = CRGB::Black; // turn every third pixel off
            }
        }
    }
}

// Random flashes of lightning
void lightning(CRGB c, int simultaneous, int cycles, int speed)
{
    int flashes[simultaneous];

    for (int i = 0; i < cycles; i++)
    {
        for (int j = 0; j < simultaneous; j++)
        {
            int idx = random(NUM_LEDS);
            flashes[j] = idx;
            leds[idx] = c ? c : randomColor();
        }
        FastLED.show();
        delay(speed);
        for (int s = 0; s < simultaneous; s++)
        {
            leds[flashes[s]] = CRGB::Black;
        }
        delay(speed);
    }
}

// Sliding bar across LEDs
void cylon(CRGB c, int width, int speed)
{
    // First slide the leds in one direction
    for (int i = 0; i <= NUM_LEDS - width; i++)
    {
        for (int j = 0; j < width; j++)
        {
            leds[i + j] = c;
        }

        FastLED.show();

        // now that we've shown the leds, reset to black for next loop
        for (int j = 0; j < 5; j++)
        {
            leds[i + j] = CRGB::Black;
        }
        delay(speed);
    }

    // Now go in the other direction.
    for (int i = NUM_LEDS - width; i >= 0; i--)
    {
        for (int j = 0; j < width; j++)
        {
            leds[i + j] = c;
        }
        FastLED.show();
        for (int j = 0; j < width; j++)
        {
            leds[i + j] = CRGB::Black;
        }

        delay(speed);
    }
}

// Display alternating stripes
void stripes(CRGB c1, CRGB c2, int width)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        if (i % (width * 2) < width)
        {
            leds[i] = c1;
        }
        else
        {
            leds[i] = c2;
        }
    }
    FastLED.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
CRGB Wheel(byte WheelPos)
{
    if (WheelPos < 85)
    {
        return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
    else if (WheelPos < 170)
    {
        WheelPos -= 85;
        return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    else
    {
        WheelPos -= 170;
        return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}

CRGB randomColor()
{
    return Wheel(random(256));
}
