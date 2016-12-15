#include <FastLED.h>
#include <LiquidCrystal.h>

#define ws2812b_pin 12
#define n_leds 15

CRGB leds[n_leds];

LiquidCrystal lcd(11, 10, 5,4, 3, 2);

int mode = 3;

const char* mode_list[] = {"None      ", "static    ", "colorcicle","rainbow   "};

//int static_color[3] = {255,180,180};
//int static_color[3] = {255,100,150};
int static_color[3] = {255,255,255};

float brightness = 1;

void setup() {
	Serial.begin(9600);
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
	lcd.setCursor(0,0);
	lcd.print("Mode: ");
	Serial.write(1);
	delay(500);
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

void print_response(int response){
	lcd.setCursor(6,0);
	lcd.print("          ");
	lcd.print(response);
}

void rainbow(int len, int pos, int start=0){
	for (int i = 0; i < len; i++){
		int k = (i+pos) % len;
		if (i <= len/3){
			float color_step = (255.*3.*i)/len;
			leds[k+start].r = 255-color_step;
			leds[k+start].g = color_step;
			leds[k+start].b = 0;
		}
		else if (i <= 2*len/3){
			float color_step = (255.*3.*(i-len/3.))/len;
			leds[k+start].r = 0;
			leds[k+start].g = 255-color_step;
			leds[k+start].b = color_step;
		}
		else {
			float color_step = (255.*3.*(i-2.*len/3.))/len;
			leds[k+start].r = color_step;
			leds[k+start].g = 0;
			leds[k+start].b = 255-color_step;
		}
	}
	FastLED.show();
}

void loop() {
	if (Serial.available()){
		lcd.setCursor(6,0);
		lcd.print("          ");
		lcd.setCursor(6,0);
		while (Serial.available()){
			mode = Serial.parseInt();;
			print_response(mode);
		}
		if (mode == 1){
			int answer = -2;
			Serial.write("r");
			while (answer == -2){
				answer = Serial.parseInt();
				print_response(answer);
			}
			if (answer != -1){
				static_color[0] = answer;
				answer = -1;
				Serial.write("g");
				while (answer == -1){
					answer = Serial.parseInt();
				}
				static_color[1] = answer;
				answer = -1;
				Serial.write("b");
				while (answer == -1){
					answer = Serial.parseInt();
				}
				static_color[2] = answer;
			}
		}
		//delay(1000);
	}
	lcd.setCursor(6,0);
	if ((mode > -1) && (mode < sizeof(mode_list)/sizeof(mode_list[0]))){
		lcd.print(mode_list[mode]);
	}
	if (mode == 0){
		for (int i = 0; i < n_leds; i++){
			leds[i] = CRGB::Black;
		}
		FastLED.show();
		int black_color[] = {0,0,0};
		print_rgb(black_color);
		delay(500);
	}
	else if (mode == 1){
		for (int i = 0; i < n_leds; i++){
			leds[i].r = static_color[0]*brightness;
			leds[i].g = static_color[1]*brightness;
			leds[i].b = static_color[2]*brightness;
		}
		FastLED.show();
		print_rgb(static_color,brightness);
		delay(500);
	}
	else if (mode == 2){
		/*for (int i = 0; i < n_leds; i++){
			leds[i] = CRGB::Black;
		}*/
		FastLED.show();
		for (int i = 0; i < 256; i++){
			for (int k = 0; k < n_leds; k++){
				leds[k].r = 255 - i;
				leds[k].g = i;
				leds[k].b = 0;
			}
			FastLED.show();
			print_rgb_number(leds[0].r,2,1);
			print_rgb_number(leds[0].g,7,1);
			delay(10);
		}
		for (int i = 0; i < 256; i++){
			for (int k = 0; k < n_leds; k++){
				leds[k].r = 0;
				leds[k].g = 255 - i;
				leds[k].b = i;
			}
			FastLED.show();
			print_rgb_number(leds[0].b,12,1);
			print_rgb_number(leds[0].g,7,1);
			delay(10);
		}
		for (int i = 0; i < 256; i++){
			for (int k = 0; k < n_leds; k++){
				leds[k].r = i;
				leds[k].g = 0;
				leds[k].b = 255 - i;
			}
			FastLED.show();
			print_rgb_number(leds[0].r,2,1);
			print_rgb_number(leds[0].b,12,1);
			delay(10);
		}
	}
	else if (mode == 3){
		int n = 1;
		int len = n_leds/n;
		for (int i = 0; i < len; i++){
			for (int k = 0; k < n; k++){
				rainbow(len,i,len*k);
			}
			int current_color[] = {leds[0].r,leds[0].g,leds[0].b};
			print_rgb(current_color);
			delay(30);
		}
	}
	else {
		mode = 0;
	}
}
