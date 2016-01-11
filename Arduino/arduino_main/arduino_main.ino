/*
 Fade

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 This example code is in the public domain.
 */
#include <SoftwareSerial.h>

int leds[] = {9, 10, 11};
int currentLed = 0;
int brightness[] = {255, 255, 255};
int targetBrightness[] = {0, 0, 0};
int fadeAmount[3] = {-25, -25, -25};
SoftwareSerial mySerial(8, 1); // RX, TX

void setLed(int led, int newBrightness) {
  Serial.print(led);
  Serial.print(": ");
  Serial.println(newBrightness);
  brightness[led] = newBrightness;
  analogWrite(leds[led], newBrightness);
}

void setup() {
  // declare pin 9 to be an output:
  pinMode(leds[0], OUTPUT);
  pinMode(leds[1], OUTPUT);
  pinMode(leds[2], OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  if (mySerial.available() > 0) {
    int red = mySerial.parseInt();
    int green = mySerial.parseInt();
    int blue = mySerial.parseInt();
    
    if (mySerial.read() == '\n') {
      // constrain the values to 0 - 255 and invert
      // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
      red = constrain(red, 0, 255);
      green = constrain(green, 0, 255);
      blue = constrain(blue, 0, 255);

      targetBrightness[0] = red;
      targetBrightness[1] = green;
      targetBrightness[2] = blue;
      fadeAmount[0] = (targetBrightness[0]-brightness[0]) / 15;
      fadeAmount[1] = (targetBrightness[1]-brightness[1]) / 15;
      fadeAmount[2] = (targetBrightness[2]-brightness[2]) / 15;
      Serial.println(fadeAmount[0]);
      Serial.println(fadeAmount[1]);
      Serial.println(fadeAmount[2]);
    }
  } else {
    for (int led = 0; led <= 2; led++) {
      if (brightness[led] != targetBrightness[led]) {
        if (abs(targetBrightness[led] - brightness[led]) > abs(fadeAmount[led])) {
          setLed(led, brightness[led] + fadeAmount[led]);
        } else {
          setLed(led, targetBrightness[led]);
        }
      }
    }
    delay(60);
  }
}

