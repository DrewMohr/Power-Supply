//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Andrew Mohr 2020
//Version: Alpha Build 0.6.7
//Last Date Offically Updated: 1/19/20 11:04
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <Wire.h>


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_RESET);
#define SCREEN_WIDTH 128
#define SCREEN_HIGHT 64
int output;
int incomingByte = 0;


void setup(){
  Serial.begin(9600);
  display.clearDisplay();
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(200);
  display.cp437(true);

  analogWrite(5, 250);
  analogWrite(A0, 250);
  analogWrite(11, 250);
  delay(250);
  analogWrite(5, 0);
  analogWrite(A0, 0);
  analogWrite(11, 0);
  delay(10);

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.setCursor(0,0);
  display.print("STARTING UP.");
  display.display();
  delay(200);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.setCursor(0,0);
  display.print("STARTING UP..");
  display.display();
  delay(200);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.setCursor(0,0);
  display.print("STARTING UP...");
  display.display();
  delay(200);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.setCursor(0,0);
  display.print("STARTING UP.");
  display.display();
  delay(200);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.setCursor(0,0);
  display.print("STARTING UP..");
  display.display();
  delay(200);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.setCursor(0,0);
  display.print("STARTING UP...");
  display.display();
  delay(200);
  display.clearDisplay();
  display.display();
  
  delay(1000);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,8);
  display.print("  WELCOME");
  display.display();
  delay(1500);
 
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("    VERSION-A0.6.7");   //~~~~~~~~~~~~~~~~~~~~ VERSION OF SOFTWARE---CHANGE THIS WHEN UPDATING
  display.display();
  delay(2000);

  //PLACE INT AND OTHER STARTUP MATERIAL HERE \/\/\/

  
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.setCursor(25,25);
  display.print("   LOADING...");
  display.display();
  delay(1000);
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,8);
  display.print("  WELCOME");
  display.display();
  
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.setCursor(0,25);
  display.print("      CHECKING...");
  display.display();
  delay(2000);
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,8);
  display.print("  WELCOME");
  display.display();
  
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.setCursor(0,25);
  display.print("        DONE!");
  display.display();
  delay(200);

  
  //END
  display.clearDisplay();

  
  
 }
 
  void loop() {
  
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.setCursor(0,0);
  display.print("OUTPUT");
  display.display();
  
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.setCursor(0,10);
  if (digitalRead(3) == LOW){
    display.print("OFF");
    analogWrite(5, 0);
    display.display();
    
  }
    else {
    display.print("ACTIVE");
    analogWrite(5, 10);
    display.display();
    display.clearDisplay();
  }

//~~~~~~~~~~~~~~~~~~~~~~~~
//Input Data scripts below
//~~~~~~~~~~~~~~~~~~~~~~~~

//~~~
    display.setTextColor(WHITE);
    display.setTextSize(0);
    display.setCursor(95,10);
        if (digitalRead(6) == HIGH) {
      display.print("READY");
    
  }
      else {
        display.setCursor(70,0);
        display.clearDisplay();
        display.print("NOT READY");
        display.display();
        digitalWrite(A0, 255);
        delay(50);
        digitalWrite(A0, 0);
        delay(50);
        digitalWrite(A0, 255);
        delay(50);
        digitalWrite(A0, 0);
        delay(50);
        digitalWrite(A0, 255);
        delay(50);
        digitalWrite(A0, 0);
        delay(50);
        
      }
      
  //~~~~

    display.setTextColor(WHITE);
    display.setTextSize(0);
    display.setCursor(56,10);
        if (digitalRead(7) == HIGH) {
      display.print("OK");
      
    
  }
      else {
        display.setCursor(50,0);
        
        display.print("SHORT");
        analogWrite(11, 25);
        delay(50);
        analogWrite(11, 50);
        delay(50);
        analogWrite(11, 75);
        delay(50);
        analogWrite(11, 100);
        delay(50);
        analogWrite(11, 125);
        delay(50);
        analogWrite(11, 150);
        delay(50);
        analogWrite(11, 175);
        delay(50);
        analogWrite(11, 200);
        delay(50);
        analogWrite(11, 225);
        delay(200);
        analogWrite(11, 255);
        delay(50);
        analogWrite(11, 225);
        delay(50);
        analogWrite(11, 200);
        delay(50);
        analogWrite(11, 175);
        delay(50);
        analogWrite(11, 150);
        delay(50);
        analogWrite(11, 125);
        delay(50);
        analogWrite(11, 100);
        delay(50);
        analogWrite(11, 75);
        delay(50);
        analogWrite(11, 50);
        delay(50);
        analogWrite(11, 25);
        delay(50);
        analogWrite(11, 0);
        delay(200);
  
      }
  //~~~~



  
}
