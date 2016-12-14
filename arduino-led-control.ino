#include <FastLED.h>
#include <LiquidCrystal.h>

#define ws2812b_pin 12
#define n_leds 15

CRGB leds[n_leds];

LiquidCrystal lcd(11, 10, 5,4, 3, 2);

char mode = 2;

const char* mode_list[] = {"None", "colorcicle", "static"};

//int static_color[3] = {255,180,180};
int static_color[3] = {0,0,255};

float brightness = 1;

void setup() {
	//pinMode(ws2812b_pin, OUTPUT);
	FastLED.addLeds<NEOPIXEL, ws2812b_pin>(leds, n_leds);
	for (int i = 0; i < n_leds; i++){
		leds[i] = CRGB::Black;
	}
	FastLED.show();
	pinMode(13, OUTPUT);
	lcd.begin(16, 2);
	lcd.setCursor(0,1);
	lcd.print("R:000G:000B:000");
	lcd.setCursor(0,0);
	lcd.print("Mode:");
	lcd.display();
}

void print_rgb_number(int value, int col, int row){
	lcd.setCursor(col,row);
	if (value < 100){
		if (value < 10){
			lcd.print(0);
		}
		lcd.print(0);
		lcd.print(value);
	}
	else {
		lcd.print(value);
	}
}

void print_rgb(int color[], float brightness=1.){
	print_rgb_number(color[0]*brightness,2,1);
	print_rgb_number(color[1]*brightness,7,1);
	print_rgb_number(color[2]*brightness,12,1);
}

void loop() {
	lcd.setCursor(6,0);
	lcd.print(mode_list[mode]);
	if (mode == 0){
		for (int i = 0; i < 256; i++){
			leds[i] = CRGB::Black;
		}
		FastLED.show();
		delay(500);
	}
	if (mode == 1){
		for (int i = 0; i < 256; i++){
			for (int k = 0; k < n_leds; k++){
				leds[k].r = 255 - i;
				leds[k].g = i;
			}
			FastLED.show();
			print_rgb_number(leds[0].r,2,1);
			print_rgb_number(leds[0].g,7,1);
			delay(30);
		}
		for (int i = 0; i < 256; i++){
			for (int k = 0; k < n_leds; k++){
				leds[k].g = 255 - i;
				leds[k].b = i;
			}
			FastLED.show();
			print_rgb_number(leds[0].b,12,1);
			print_rgb_number(leds[0].g,7,1);
			delay(30);
		}
		for (int i = 0; i < 256; i++){
			for (int k = 0; k < n_leds; k++){
				leds[k].b = 255 - i;
				leds[k].r = i;
			}
			FastLED.show();
			print_rgb_number(leds[0].r,2,1);
			print_rgb_number(leds[0].b,12,1);
			delay(30);
		}
	}
	if (mode == 2){
		for (int i = 0; i < n_leds; i++){
			leds[i].r = static_color[0]*brightness;
			leds[i].g = static_color[1]*brightness;
			leds[i].b = static_color[2]*brightness;
		}
		FastLED.show();
		print_rgb(static_color,brightness);
		delay(500);
	}

}
