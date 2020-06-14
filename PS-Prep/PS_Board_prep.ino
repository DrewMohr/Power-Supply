//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Power Supply Preparation code
//Andrew Mohr 2019-2020
//Date started: 04/05/2020 03:05pm
//Date Last Updated: 04/05/2020 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Instructions:
//You will first upload this to the display driver (arduino 1 ; this is the arduino that runs the screen)
//Then you will upload the actual screen system code that will be on the arduino
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



#include <Wire.h> //basics
#include <Adafruit_GFX.h> //GFX
#include <Adafruit_SSD1306.h> //Display Library
//#include <DHT.h> //DHT
#include <EEPROM.h>


#define OLED_RESET 13  //keep this before one below!!!
Adafruit_SSD1306 display(OLED_RESET); //Do not move position
#define SCREEN_WIDTH 128
#define SCREEN_HIGHT 64


void setup() {

Serial.begin(9600);
    Serial.println("Power supply preparation V1.0");
    Serial.println("Andrew Mohr 2020");
    Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    Serial.println("INITIALIZING DISPLAY >> 0x3c");
    Serial.println("[EXIT 0 - [OK]");
  delay(200);
  display.cp437(true);
  display.clearDisplay();
  delay(500);
  display.invertDisplay(true);
  delay(500);

  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("    preparating");
  Serial.println("preparating for best possible experience");
  display.display();
  Serial.println("EXIT 0 - [OK]");
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,8);
  display.print("    working...");
  Serial.println("working...");
  display.display();
  Serial.println("EXIT 5");
  delay(2000);
  Serial.println("EXIT 0 - [OK]");
    Serial.println("resetting...");
    
    EEPROM.write(1, 0);
    delay(500);
    Serial.println("EXIT 0 - [OK]");

    EEPROM.write(2, 0);
    delay(500);
    Serial.println("EXIT 0 - [OK]");

    EEPROM.write(3, 0);
    delay(500);
    Serial.println("EXIT 0 - [OK]");

    EEPROM.write(4, 0);
    delay(500);
    Serial.println("EXIT 0 - [OK]");

    EEPROM.write(5, 0);
    delay(500);
    Serial.println("EXIT 0 - [OK]");


    display.clearDisplay();
  delay(3000);
    Serial.println("EXIT 0 - [OK]");
    display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,8);
  display.print("Done!");
  Serial.println("Done!");
  display.display();
  Serial.println("EXIT 0 - [OK]");
    
}
void loop() {
  analogWrite(5, 250); //green light
  analogWrite(A0, 250); //red light
  analogWrite(11, 250); //yellow light
  digitalWrite(13, HIGH);
  delay(1000);
  Serial.println("EXIT 0 - [OK]");

  analogWrite(5, 0); //green light
  analogWrite(A0, 0); //red light
  analogWrite(11, 0); //yellow light
  digitalWrite(13, LOW);
  delay(1000);
  Serial.println("EXIT 0 - [OK]");
}