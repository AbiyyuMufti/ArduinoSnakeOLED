/*
 Name:		ArduinoSnakeOLED.ino
 Created:	1/4/2021 10:27:51 PM
 Author:	abiyy
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SnakeElement.h"

//#define USE_SERIAL 1
#define USE_BUTTONS 1

long lastTime;
int duration = 50;
int Radius = 2;

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HIGH, &Wire, 4);
SnakeElement mSnake(OLED_WIDTH / 2 + 8 * Radius, OLED_HIGH / 2, Radius);
SnakeDirection Direction = left;
//Circle Food(OLED_WIDTH / 2 + 8 * Radius, OLED_HIGH / 2, Radius / 2);

void setup() {
#ifdef USE_BUTTONS
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);
#endif
    randomSeed(analogRead(0));
    Serial.begin(9600);
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    pinMode(13, OUTPUT);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
        digitalWrite(13, HIGH);
        for (;;); // Don't proceed, loop forever
    }
    else {
        digitalWrite(13, LOW);
    }

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
    delay(1000); // Pause for 1 seconds

    display.clearDisplay();
    mSnake.draw();
    display.display();
    for (int i = 0; i < 4; i++) {
        mSnake.update(left);
        mSnake.elongate();
    }
    display.clearDisplay();
    mSnake.draw();
    //randomFoodPosition();
    //Food.draw();
    display.display();
    Direction = stop;
    lastTime = millis();
}

void loop() {
    checkDirection();
    Serial.println(Direction);
    if ((millis() - lastTime) >= duration) {
        display.clearDisplay();
        /*if (mSnake.eating(Food)) {
          Serial.println("True");
          mSnake.elongate();
          //randomFoodPosition();
        }*/
        mSnake.update(Direction);
        mSnake.draw();
        //Food.draw();
        display.display();
        lastTime = millis();
    }

}

int checkDirection() {
#ifdef USE_SERIAL
    if (Serial.available()) {
        char buffer = Serial.read();
        switch (buffer) {
        case '4':
            Direction = left;
            break;
        case '6':
            Direction = right;
            break;
        case '8':
            Direction = up;
            break;
        case '2':
            Direction = down;
            break;
        case '5':
            Direction = stop;
            break;
        default:
            break;
        }
    }
#endif
#ifdef USE_BUTTONS
    int a = digitalRead(4);
    int b = digitalRead(5);
    int c = digitalRead(6);
    int d = digitalRead(7);
    if (a == 0) {
        Direction = right;
    }
    if (b == 0) {
        Direction = left;
    }
    if (c == 0) {
        Direction = up;
    }
    if (d == 0) {
        Direction = down;
    }
#endif

}

/*void randomFoodPosition() {
  int x = random(OLED_WIDTH);
  int y = random(OLED_HIGH);
  Food.setX(x);
  Food.setY(y);
}*/
