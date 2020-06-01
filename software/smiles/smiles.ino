#include <Adafruit_NeoPixel.h>

const int SENSOR_PIN = A0;
const int LED_PIN = 13;

const int MAX_VAL = 64;
const int N_STEPS = 16;
const int DELTA = MAX_VAL / N_STEPS;

const int NP_PIN = 6;
const int N_LEDS = 27;

const int FADE_IN = 0;
const int FADE_OUT = 1;

const int HAPPY[] = {
    0,  0,  0,  0,  0,
  1,  0,  0,  0,  0,  1,
    1,  0,  0,  0,  1,
  0,  1,  1,  1,  1,  0,
    0,  0,  0,  0,  0,
};

const int BAD[] = {
    0,  0,  1,  0,  0,
  0,  0,  1,  1,  0,  0,
    0,  1,  0,  1,  0,
  0,  1,  0,  0,  1,  0,
    1,  0,  0,  0,  1,
};

const int SURPRISE[] = {
    0,  1,  1,  1,  0,
  0,  1,  0,  0,  1,  0,
    1,  0,  0,  0,  1,
  0,  1,  0,  0,  1,  0,
    0,  1,  1,  1,  0,
};

const int SAD[] = {
    0,  1,  0,  1,  0,
  0,  0,  1,  1,  0,  0,
    0,  0,  1,  0,  0,
  0,  0,  1,  1,  0,  0,
    0,  1,  0,  1,  0,
};

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, NP_PIN, NEO_GRB | NEO_KHZ800);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  fade(0, MAX_VAL, 0, HAPPY, FADE_IN);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = 0;
  sensorValue = analogRead(SENSOR_PIN);
  Serial.println(sensorValue);
  if (sensorValue > 100) {
    digitalWrite(LED_PIN, HIGH);
    fade(0, MAX_VAL, 0, HAPPY, FADE_OUT);
    fade(MAX_VAL, MAX_VAL, 0, BAD, FADE_IN);
    delay(2000);
    fade(MAX_VAL, MAX_VAL, 0, BAD, FADE_OUT);
    // delay(2000);
    fade(0, MAX_VAL, 0, HAPPY, FADE_IN);
    digitalWrite(LED_PIN, LOW); 
  }
}

void clear() {
  for (uint16_t i = 0; i < strip.numPixels(); ++i) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}

void fade(int target_r, int target_g, int target_b, int target_pattern[], int in_or_out) {
  int delta_r = target_r / N_STEPS;
  int delta_g = target_g / N_STEPS;
  int delta_b = target_b / N_STEPS;
  for (int t = 0; t < N_STEPS; ++t) {
    int r, g, b;
    if (in_or_out == FADE_IN) {
      r = delta_r * t;
      g = delta_g * t;
      b = delta_b * t;
    }
    else {
      r = target_r - delta_r * (t + 1);
      g = target_g - delta_g * (t + 1);
      b = target_b - delta_b * (t + 1);
    }
    for (int i = 0; i < N_LEDS; ++i) {
      if (target_pattern[i] == 1) {
        strip.setPixelColor(i, strip.Color(r, g, b));
      }
    }
    strip.show();
    delay(100);
  }
}
