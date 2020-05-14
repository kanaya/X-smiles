#include <Adafruit_NeoPixel.h>

const int MAX_VAL = 128;
const int N_STEPS = 16;
const int DELTA = MAX_VAL / N_STEPS;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(23, 6, NEO_GRB | NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  clear();
}

void loop() {
  happy();
  delay(2000);
  unhappy();
  sad();
  delay(2000);
  unsad();
}

void clear() {
  for (uint16_t i = 0; i < strip.numPixels(); ++i) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}

void happy() {
  for (int t = 0; t < N_STEPS; ++t) {
    for (int i = 0; i < 14; ++i) {
      int c = DELTA * t;
      strip.setPixelColor(i, strip.Color(0, c, 0));
    }
    strip.show();
    delay(100);
  }
}

void unhappy() {
  for (int t = 0; t < N_STEPS; ++t) {
    for (int i = 0; i < 14; ++i) {
      int c = MAX_VAL - DELTA * (t + 1);
      strip.setPixelColor(i, strip.Color(0, c, 0));
    }
    strip.show();
    delay(100);
  }
} 

void sad() {
  for (int t = 0; t < N_STEPS; ++t) {
    for (int i = 14; i < 23; ++i) {
      int c = DELTA * t;
      strip.setPixelColor(i, strip.Color(c, 0, 0));
    }
    strip.show();
    delay(100);
  }
}

void unsad() {
  for (int t = 0; t < N_STEPS; ++t) {
    for (int i = 14; i < 23; ++i) {
      int c = MAX_VAL - DELTA * (t + 1);
      strip.setPixelColor(i, strip.Color(c, 0, 0));
    }
    strip.show();
    delay(100);
  }
} 
