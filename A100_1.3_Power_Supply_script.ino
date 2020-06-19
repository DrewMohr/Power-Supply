/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Power Supply MotherBoard (DESIGNED FOR A100 MODEL)
//Andrew Mohr 2019-2020
//Version: Alpha Build 0.0.4
//Date Project Started: 01/18/2020 11:07pm
//This specific script Started: 04/24/2020 10:10pm
//Last Date Offically Updated: 04/24/2020 10:10pm
//https://github.com/DrewMohr/Power-Supply
//--------------------------------------------------
//           CHANGE LOG BELOW
//                Format:
// M/D/Y HH:MMam/pm | v.VERSION x.y.z 
// -- Changes
//--------------------------------------------------
// 04/24/2020 10:10pm | v.Alpha 0.0.1 
// -- Script Created
//
// 06/13/2020 07:06pm | v.Alpha 0.0.5
// -- Small Changes
//--------------------------------------------------
*/



#include <Wire.h> //basics
#include <Adafruit_GFX.h> //GFX
#include <Adafruit_SSD1306.h> //Display Library
#include <Adafruit_Sensor.h> //Temp
#include <DHT.h> //DHT
#include <EEPROM.h>
#include <Encoder.h> 
#include <Adafruit_INA219.h>
#include <Adafruit_NeoPixel.h>
#include <SparkFun_External_EEPROM.h>


#define OLED_RESET 13  //keep this above one below!!!
Adafruit_SSD1306 display(OLED_RESET); //Do not move position
#define SCREEN_WIDTH 128
#define SCREEN_HIGHT 64

boolean board_state;
byte tempWarn;
byte tempWarn_count;
byte tempAlarm;
byte button_current;
byte up;
byte down;
byte left;
byte right;
byte enter;
byte back;
byte button_trigger;
byte power_button;


int encoder;
int ThermistorPin = A3;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int buttonCurrent;
int buttonPrevious = LOW;
int test;

String disv = "A0.0.1";
String v = "Alpha Build 0.0.2"; //Release Version-------------------------------UPDATE THIS WHEN UPDATING
String dv = "dev.prealpha-0.0.3r1"; //Development Version------------------------THIS TOO DAMMIT


#define boot_BMPWIDTH 32
#define boot_BMPHEIGHT 32
const unsigned char bitmap_boot[] PROGMEM = {

  0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,
  0x00,0x00,0x20,0x00,
  0x00,0x0F,0xB8,0x00,
  0x00,0x1F,0xFC,0x00,
  0x00,0x3F,0xFE,0x00,
  0x00,0x7F,0xFF,0x00,
  0x00,0xFF,0xFF,0x80,
  0x01,0xFF,0xFF,0x80,
  0x03,0xFF,0xFF,0xC0,
  0x03,0xFF,0x1F,0xC0,
  0x07,0xFC,0x07,0xC0,
  0x07,0xF0,0x07,0xC0,
  0x0F,0xE0,0x1F,0x80,
  0x0F,0xE0,0x0F,0x00,
  0x0F,0xE0,0x00,0x00,
  0x0F,0xE0,0x00,0x00,
  0x0F,0xE0,0x00,0x00,
  0x07,0xE0,0x00,0x00,
  0x07,0xF0,0x00,0x20,
  0x03,0xF8,0x00,0x00,
  0x03,0xF8,0x0C,0x40,
  0x01,0xFF,0xFD,0x80,
  0x00,0xFF,0xF7,0x00,
  0x00,0x3F,0xFE,0x00,
  0x00,0x0F,0xF8,0x00,
  0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00

};


void setup() {
  
//Pinmode start  
  //pinMode(4, INPUT);
  
//Pinmode end

  Serial.begin(115200);  
  Wire.begin();
  Wire.setClock(400000);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    Serial.println(F("INITIALIZING 0x3c"));
  delay(200);
  display.cp437(true);
  display.clearDisplay();
  Serial.println("EXIT 00-00");
  display.display();
  digitalWrite(13, LOW);

  button_current = LOW;
 
 
 //START BOOT SEQUENCE

display.clearDisplay();
display.drawBitmap(0, 10, bitmap_boot, 64, 64, WHITE);
display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("BOOTING...");
    display.setCursor(75, 0);
    display.print("STARTING");

    display.setCursor(65, 0);
    display.print("|");
    display.setCursor(65, 5);
    display.print("|");
    display.setCursor(65, 10);
    display.print("|");
    display.setCursor(65, 15);
    display.print("|");
    display.setCursor(65, 20);
    display.print("|");
    display.setCursor(65, 25);
    display.print("|");
    
display.display();
delay(500);

}


void loop() {
/*
display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print(oldPosition);
  display.display();
  

display.clearDisplay();

 buttonCurrent = digitalRead(4);

  if (buttonCurrent == HIGH && buttonPrevious == LOW){
    if (button_current == LOW){
      button_current = HIGH;
      
      digitalWrite(13, HIGH);
      Serial.println("EXIT 06-01");
    }
    else {
      button_current = LOW;
      digitalWrite(13, LOW);

      Serial.println("EXIT 06-00");
    }
  }
*/
display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(75,10);
    display.print("[FAIL]");
    display.display();
digitalWrite(11, HIGH);
digitalWrite(13, HIGH);
delay(100);
digitalWrite(11, LOW);
digitalWrite(13, LOW);
delay(100);
digitalWrite(11, HIGH);
digitalWrite(13, HIGH);
delay(100);
digitalWrite(11, LOW);
digitalWrite(13, LOW);
delay(100);
digitalWrite(11, HIGH);
digitalWrite(13, HIGH);
delay(100);
digitalWrite(11, LOW);
digitalWrite(13, LOW);
delay(100);
digitalWrite(11, HIGH);
digitalWrite(13, HIGH);
delay(100);
digitalWrite(11, LOW);
digitalWrite(13, LOW);
delay(100);
digitalWrite(11, HIGH);
digitalWrite(13, HIGH);
delay(300);
digitalWrite(11, LOW);
digitalWrite(13, LOW);
delay(3000);


}

 
