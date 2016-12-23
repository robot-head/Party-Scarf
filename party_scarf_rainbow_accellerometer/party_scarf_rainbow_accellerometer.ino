#include <FastLED.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define LED_PIN     6
#define CLOCK_PIN   9
#define COLOR_ORDER GBR
#define CHIPSET     APA102
#define NUM_LEDS    48

#define DEFAULT_BRIGHTNESS  3
#define FRAMES_PER_SECOND 20


CRGB leds[NUM_LEDS];
uint8_t wheelpos = 0;
Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup() {
  //delay(3000); // sanity delay
  mma.begin();
  FastLED.addLeds<CHIPSET, LED_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( DEFAULT_BRIGHTNESS );
}

void loop()
{
  mma.read();
  rainbow(); // run simulation frame

  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

void rainbow() {
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mma.getEvent(&event);
  
  int accel = ((event.acceleration.x + event.acceleration.y + event.acceleration.z)*200);
  FastLED.setBrightness( accel );
  fill_rainbow(leds, NUM_LEDS, wheelpos, 2);
  wheelpos++;
}

