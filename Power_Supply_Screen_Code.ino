//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Andrew Mohr 2020
//Version: Alpha Build 0.8.7
//Date Started: 1/18/2020 11:07pm
//Last Date Offically Updated: 2/20/2020 04:29pm
//--------------------------------------------------
//           CHANGE LOG BELOW
//                Format:
// M/D/Y HH:MMam/pm | v.VERSION x.y.z 
// -- Changes
//--------------------------------------------------
// 1/18/2020 11:07pm | v.Alpha 0.0.1 
// -- Script Created

// ***Log from 1/18/2020 to 1/30/2020 not recorded***

// 1/30/2020 03:01pm | v.Alpha 0.8.5 
// -- Change Log Created
// 
// 2/10/2020 10:22pm | v.Alpha 0.8.7
// -- Added Temperature Monitoring
// -- Debugging
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <Wire.h> //basics
#include <Adafruit_GFX.h> //GFX
#include <Adafruit_SSD1306.h> //Display Library
#include <Adafruit_Sensor.h> //Temp
#include <DHT.h> //DHT
#include <Servo.h> //Servo

#define OLED_RESET 13  //keep this before one below
Adafruit_SSD1306 display(OLED_RESET);
#define SCREEN_WIDTH 128
#define SCREEN_HIGHT 64

//variables start

int output;
int incomingByte = 0;
int cycle = 0;
int fan;
int fan_count;

int ThermistorPin = A3;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;


//variables end

void setup(){

//Pinmode start  
  pinMode(A2, OUTPUT);

//Pinmode end

    Serial.println("SERIAL BAUD SET = 9600");
        Serial.begin(9600);
  display.clearDisplay();
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    Serial.println("INITIALIZING DISPLAY >> 0x3c");
  delay(200);
  display.cp437(true);

    Serial.println("TEST STATUS LIGHTS");
  analogWrite(5, 250);
  analogWrite(A0, 250);
  analogWrite(11, 250);
  digitalWrite(A3, HIGH);
  delay(250);
  analogWrite(5, 0);
  analogWrite(A0, 0);
  analogWrite(11, 0);
  digitalWrite(A3, LOW);
  delay(10);
      Serial.println("---STARTING---");
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.setCursor(0,0);
  display.print("STARTING UP.");
  display.display();
    Serial.println("STARTING UP.");
  delay(200);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.setCursor(0,0);
  display.print("STARTING UP..");
  display.display();
    Serial.println("STARTING UP..");
  delay(200);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.setCursor(0,0);
  display.print("STARTING UP...");
  display.display();
     Serial.println("STARTING UP...");
   display.clearDisplay();
  delay(200);
    Serial.println("DONE");
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,8);
  display.print("  WELCOME");
  display.display();
    Serial.println("SUCCESS");
  delay(1500);
 
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("    VERSION-A0.8.7");                                     //~~~~~~~~~~~~~~~~~~~~ <<VERSION OF SOFTWARE---CHANGE THIS WHEN UPDATING>>
  display.display();
     Serial.println("<<RUNNING VERSION: ALPHA BUILD 0.8.7>>");        //~~~~~~~~~~~~~~~~~~~~ <<CHANGE THIS AS WELL>>
      //debug serial settings
      //Serial.println("*Debug---ok");
      Serial.println("*Debug---Running Test Build v0.8.7w06_a")
  


  
  delay(2000);


  //PLACE INT AND OTHER STARTUP MATERIAL HERE \/\/\/

  
  display.setTextColor(WHITE);
    display.setTextSize(0);
    display.setCursor(25,25);
    display.print("   LOADING...");
    display.display();
    Serial.println("LOADING");
    delay(1000);
    display.clearDisplay();

  display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0,8);
    display.print("  WELCOME");
    display.display();
  
  

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
    Serial.println("---DONE!---");
    delay(100);
  Serial.println("---STARTING USER INTERFACE---");
  delay(100);

  fan_count = 0;
  //END
  display.clearDisplay();
     

  
  
 }
 
  void loop() {
    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Input Data scripts below|
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

       
    Serial.print("CYCLE ");
     Serial.println(cycle);
    Serial.println("--CHECK--"); //~~~~CHECK

  //display.setTextColor(WHITE);
  //display.setTextSize(0);
  //display.setCursor(45,25);
  //display.print("CYCLE ");
  //display.setTextColor(WHITE);
  //display.setTextSize(0);
  //display.setCursor(83,25);
  //display.print(cycle);
     
    
  display.setTextColor(WHITE);
    display.setTextSize(0);
    display.setCursor(0,0);
    display.print("OUTPUT");
    display.display();
      
  display.setTextColor(WHITE);
    display.setTextSize(0);
    display.setCursor(0,10);
  if (digitalRead(3) == LOW){      //OUTPUT STATUS
    display.print("OFF");
    analogWrite(5, 0);
    display.display();
    display.clearDisplay();
      Serial.println("OUTPUT--OFF");
    
  }
    else {
    display.print("ACTIVE");
    analogWrite(5, 10);
    display.display();
    display.clearDisplay();
      Serial.println("OUTPUT--ACTIVE");
  }



//~~~

    
                                    //READY STATUS
    display.setTextColor(WHITE);
    display.setTextSize(0);
    display.setCursor(95,10);
        if (digitalRead(6) == HIGH) {
      display.print("READY");
        Serial.println("READY");
    
  }
      else {
          Serial.println("--WARNING!--NOT READY--");
        display.setCursor(70,0);
        display.clearDisplay();
        display.print("NOT READY");
        display.display();
        digitalWrite(A0, 255);
        digitalWrite(A2, HIGH);
        delay(50);
        digitalWrite(A0, 0);
        digitalWrite(A2, LOW);
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
                                //SHORT CIRCUIT STATUS
    display.setTextColor(WHITE);
    display.setTextSize(0);
    display.setCursor(56,10);
        if (digitalRead(7) == HIGH) {
      display.print("OK");
        Serial.println("OK");
    
  }
      else {

          Serial.println("SHORT CIRCUIT");
        display.setCursor(50,0);
        display.print("SHORT");
        digitalWrite(A2, HIGH);
        analogWrite(11, 25);
        delay(50);
        digitalWrite(A2, LOW);
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
                                  //BACKLIGHT STATUS
    if (analogRead(A1) >= 480) {

      digitalWrite(A7, LOW);
        display.drawRect(2, 26, 5, 5, WHITE);
        display.drawCircle(4, 23, 4, WHITE);
    }
    else {
      digitalWrite(A7, HIGH);
        display.drawRect(2, 26, 5, 5, WHITE);
        display.fillCircle(4, 23, 4, WHITE);
      }

  //~~~~

            //TMRS -- Temperature Monitoring and Regulatory System     
    Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 

  Serial.print("Temperature: "); 
  Serial.print(T);
  Serial.println(" F");

    if (T >= 85) {
        digitalWrite(8, HIGH);
     fan = HIGH;
      }
    else {
        digitalWrite(8, LOW);
     fan = LOW;
      }

   display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(50,25);
  display.print("TMRS: ");
  
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(85,25);
  display.print(T);
  display.print("F");
  
  //~~~~~


      if (fan_count >= 200) {
          fan = HIGH;

      }

            if (fan_count >= 225) {
              fan_count = 0;
            }





        cycle = cycle + 1; //~~~~~~~~~~~~~~~~~~~KEEP THESE LAST OF VOID LOOP
        fan_count = fan_count + 1;
  
}
