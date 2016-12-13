//#include<FastLED/FastLED.h>

#define ws2812b_pin 12
#define n_led 30

void setup() {
	pinMode(ws2812b_pin, OUTPUT);
	pinMode(13, OUTPUT);
}

void loop() {
	digitalWrite(13, LOW);
	delay(1000);
	digitalWrite(13, HIGH);
	delay(250);
	digitalWrite(13, LOW);
	delay(250);
	digitalWrite(13, HIGH);
	delay(250);
}
