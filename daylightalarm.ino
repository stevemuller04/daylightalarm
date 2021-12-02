#include <Adafruit_NeoPixel.h>

#define LEDSTRIP_NUM 24
#define LEDSTRIP_PIN 6
#define LEDSTRIP_MODE NEO_RGB + NEO_KHZ800
#define LIGHTSTEPS_NUM 256
#define LIGHTSTEPS_TOTAL_TIME 1200e3 // 20min in milliseonds

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LEDSTRIP_NUM, LEDSTRIP_PIN, LEDSTRIP_MODE);
unsigned int nextStep = 0;

void setup() {
  pixels.begin();
  pixels.show();
}

void loop() {
  if (nextStep < LIGHTSTEPS_NUM) {
    pixels.fill(getColorByStep(nextStep), 0, LEDSTRIP_NUM);
    pixels.show();
    delay(getDelayByStep(nextStep++));
  }
}

unsigned long getColorByStep(unsigned int step) {
  byte w = (byte)step;
  unsigned long r = w;
  unsigned long g = (unsigned long)(w * 0.4);
  unsigned long b = (unsigned long)(w * 0.2);
  return r << 16 | g << 8 | b;
}

unsigned int getDelayByStep(unsigned int step) {
  return pow(0.99, step) * LIGHTSTEPS_TOTAL_TIME / 92.3685;
}
