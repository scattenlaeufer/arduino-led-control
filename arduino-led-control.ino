#include <FastLED.h>

#define ws2812b_pin 12
#define n_leds 150

CRGB leds[n_leds];

void setup() {
	//pinMode(ws2812b_pin, OUTPUT);
	FastLED.addLeds<NEOPIXEL, ws2812b_pin>(leds, n_leds);
	pinMode(13, OUTPUT);
}

void loop() {
	for (int i = 0; i < 256; i++){
		for (int k = 0; k < n_leds; k++){
			leds[k].r = 255 - i;
			leds[k].g = i;
		}
		FastLED.show();
	}
	for (int i = 0; i < 256; i++){
		for (int k = 0; k < n_leds; k++){
			leds[k].g = 255 - i;
			leds[k].b = i;
		}
		FastLED.show();
	}
	for (int i = 0; i < 256; i++){
		for (int k = 0; k < n_leds; k++){
			leds[k].b = 255 - i;
			leds[k].r = i;
		}
		FastLED.show();
	}

}
