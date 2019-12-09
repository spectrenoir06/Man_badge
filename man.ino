#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#define PIN			3
#define NUMPIXELS	5
#define DELAYVAL	5
#define BRIGHTNESS	32
#define MAX_ANIM	2

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint8_t j = 0;
uint8_t mode = 2;

uint32_t Wheel(byte WheelPos) {
	if(WheelPos < 85) {
		return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	} else if(WheelPos < 170) {
		WheelPos -= 85;
		return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	} else {
		WheelPos -= 170;
		return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
}

void setup() {
	mode = EEPROM.read(0);
	if (mode > MAX_ANIM) {
		mode = 0;
	}
	EEPROM.write(0, mode+1);
	pixels.begin();
}

void rainbow() {
	for(int i=0; i<NUMPIXELS; i++)
		pixels.setPixelColor(i, Wheel(j+i*10));
	j++;
	pixels.setBrightness(BRIGHTNESS);
	pixels.show();
	delay(DELAYVAL);
}

void rainbow_cylon() {
	for(uint8_t i=0; i<5; i++) {
		pixels.clear();
		pixels.setPixelColor(i, Wheel(j*10));
		j++;
		pixels.setBrightness(BRIGHTNESS);
		pixels.show();
		delay(75);
	}
	for(uint8_t i=3; i>0; i--) {
		pixels.clear();
		pixels.setPixelColor(i, Wheel(j*10));
		j++;
		pixels.setBrightness(BRIGHTNESS);
		pixels.show();
		delay(75);
	}
}

void heart_beat() {
	uint8_t redo	= 255;
	uint8_t greeno	= 0;
	uint8_t blueo	= 0;

	for(uint8_t i=0;i<5;i++)
		pixels.setPixelColor(i, redo, greeno, blueo);

	pixels.show();
	delay (20);

	int x = 3;
	for (int ii = 1 ; ii <252 ; ii = ii = ii + x){
		pixels.setBrightness(ii);
		pixels.show();
		delay(5);
	}

	x = 3;
	for (int ii = 252 ; ii > 3 ; ii = ii - x){
		pixels.setBrightness(ii);
		pixels.show();
		delay(3);
	}
	delay(10);

	x = 6;
	for (int ii = 1 ; ii <255 ; ii = ii = ii + x){
		pixels.setBrightness(ii);
		pixels.show();
		delay(2);
	}
	x = 6;
	for (int ii = 255 ; ii > 1 ; ii = ii - x){
		pixels.setBrightness(ii);
		pixels.show();
		delay(3);
	}
	delay (50);
}

void loop() {
	switch (mode) {
		case 0:
			rainbow();
			break;
		case 1:
			rainbow_cylon();
			break;
		case 2:
			heart_beat();
			break;
	}
}
