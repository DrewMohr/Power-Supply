/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Andrew Mohr 2019-2020
//Version: Beta Build 1.2.1
//Date Started: 1/18/2020 11:07pm
//Last Date Offically Updated: 4/2/2020 12:36am
//--------------------------------------------------
//           CHANGE LOG BELOW
//                Format:
// M/D/Y HH:MMam/pm | v.VERSION x.y.z 
// -- Changes
//--------------------------------------------------
// 01/18/2020 11:07pm | v.Alpha 0.0.1 
// -- Script Created

// ***Log from 1/18/2020 to 1/30/2020 not recorded***

// 01/30/2020 03:01pm | v.Alpha 0.8.5 
// -- Change Log Created

// 02/10/2020 10:22pm | v.Alpha 0.8.7
// -- Added Temperature Monitoring
// -- Debugging
// -- Bug fixes

// 04/02/2020 12:36am | v.Beta 1.2.1
// -- Moved into Beta!
// -- Added support for new users (added a first startup setup)
// -- Got EEPROM/memory systems up and RUNNING
// -- Bug fixes
//    Issues:
//    -- Short circuit light will blink at random on some controllers
//    -- Performance
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <Wire.h> //basics
#include <Adafruit_GFX.h> //GFX
#include <Adafruit_SSD1306.h> //Display Library
#include <Adafruit_Sensor.h> //Temp
#include <DHT.h> //DHT
#include <EEPROM.h>


#define OLED_RESET 13  //keep this before one below!!!
Adafruit_SSD1306 display(OLED_RESET); //Do not move position
#define SCREEN_WIDTH 128
#define SCREEN_HIGHT 64


//variables start

int output;
int fan;
int tempWarn;
int tempWarn_count;
int tempAlarm;
int debug_settings_timer;
int board_state;
  

//EEPROM

    //EEPROM ADDRESSES
      int epaddress_01;
      int epaddress_02;
      int epaddress_03;
      int epaddress_04;


    //EEPROM VAIRABLES
      int ep_addr_01_boardstate;
      int ep_addr_02_backlight;
      int ep_addr_03_invertdisplay;
      int ep_addr_04_startups;


int ThermistorPin = A3;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

String disv = "B1.2.1";
String v = "Alpha Build 1.2.1"; //Release Version-------------------------------UPDATE THIS WHEN UPDATING
String dv = "dev.prebeta-1.2.2r1"; //Development Version----------------------THIS TOO DAMMIT

//variables end



void setup() {
  
//Pinmode start  
  pinMode(A2, OUTPUT);

//Pinmode end

    Serial.println("SERIAL BAUD SET = 9600");
        Serial.begin(9600);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    Serial.println("INITIALIZING DISPLAY >> 0x3c");
  delay(200);
  display.cp437(true);
  display.clearDisplay();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//STORAGE : RAM : EEPROM \/\/\/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//EEPROM [RAM]
  //ie. EEPROM.[function](addr, val/0-255)

    //Address assignment
    /*
        ep_addr_00_boardstate = EEPROM.read(epaddress_00);
        ep_addr_01_backlight = EEPROM.read(epaddress_01);
        ep_addr_02_invertdisplay = EEPROM.read(epaddress_02);
        ep_addr_03_startups = EEPROM.read(epaddress_03);

        EEPROM.write(0, ep_addr_00_boardstate);
        EEPROM.write(1, ep_addr_01_backlight);
        EEPROM.write(2, ep_addr_02_invertdisplay);
        EEPROM.write(3, ep_addr_03_startups);
      */    
          
          
    //Address setup programming
    /*
        if(ep_addr_02_invertdisplay == 1){
          display.invertDisplay(true);
        }
        else{
          display.invertDisplay(false);
        }
       */ 

        if(EEPROM.read(1) == 1){
          board_state = 1;
        }
        else{
          board_state = 0;
          
        }
        



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Begin
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //Serial.println("TEST STATUS LIGHTS");
  analogWrite(5, 250); //green light
  analogWrite(A0, 250); //red light
  analogWrite(11, 250); //yellow light
  digitalWrite(A3, HIGH);
  delay(250);
  analogWrite(5, 0);
  analogWrite(A0, 0);
  analogWrite(11, 0);
  digitalWrite(A3, LOW);
  


  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,8);
  display.print("  WELCOME");
  display.display();
  delay(1000);
 


                //VERSION INFO
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("    VERSION-");
  display.print(              disv);
  display.display();
     
     Serial.print("<<RUNNING VERSION: ");     
     Serial.print(v);
     Serial.println(">>");
     Serial.print("<<DEVELOPMENT BUILD: ");
     Serial.print(dv);
     Serial.println(">>");
     
     
      
      

  delay(1000);




  //PLACE INT AND OTHER STARTUP MATERIAL HERE \/\/\/

  
  
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
    
    delay(100);
  
  delay(100);
  display.clearDisplay();

  
  
//WARNING NOTICE SPLASH
/*
  digitalWrite(A2, HIGH);
  delay(150);
  digitalWrite(A2, LOW);
  delay(150);
  digitalWrite(A2, HIGH);
  delay(150);
  digitalWrite(A2, LOW);
*/ 

    display.setTextColor(WHITE);
      display.setTextSize(0);
      display.setCursor(0,0);
      display.print("      ! WARNING !");
      display.display();

      display.setTextColor(WHITE);
      display.setTextSize(0);
      display.setCursor(0,9);
      display.print("RISK OF SHOCK, PLEASE    USE CAUTION");
      display.display();

      

      digitalWrite(A0, HIGH);
      delay(100);
      digitalWrite(A0, LOW);
      delay(300);
      digitalWrite(A0, HIGH);
      delay(100);
      digitalWrite(A0, LOW);
      delay(300);

      display.clearDisplay();
  
//Automatic board setup

  if(board_state == 0){
      digitalWrite(A0, HIGH);
      delay(300);
      digitalWrite(A0, LOW);
      delay(300);
      digitalWrite(A0, HIGH);
      delay(300);
      digitalWrite(A0, LOW);
      delay(300);

      display.setTextColor(WHITE);
      display.setTextSize(0);
      display.setCursor(0,0);
      display.print("AUTOMATIC SETUP:");
      display.display();
      delay(500);
      display.setTextColor(WHITE);
      display.setTextSize(0);
      display.setCursor(0,25);
      display.print("   Loading...");
      display.display();
    Serial.println("Resetting all EEPROM/memory states to 0");
/*
    epaddress_00 = 0;
    epaddress_01 = 0;
    epaddress_02 = 0;
    epaddress_03 = 0;
*/
    EEPROM.write(1, 0);
    EEPROM.write(2, 0);
    EEPROM.write(3, 0);
    EEPROM.write(4, 0);

    Serial.println("All EEPROM/memory has been succesfully reset to 0");
    delay(1000);
    Serial.println("Finishing up...");
      
      display.clearDisplay();

      display.setTextColor(WHITE);
      display.setTextSize(0);
      display.setCursor(0,0);
      display.print("AUTOMATIC SETUP:");
      display.display();
      delay(300);
      display.setTextColor(WHITE);
      display.setTextSize(0);
      display.setCursor(0,25);
      display.print("  Finishing up...");
      display.display();
        //Setting up for use:
          //ep_addr_00_boardstate = 1;
          EEPROM.write(1, 1);
        //Setting up startup counter:
          //ep_addr_03_startups = 0;
          EEPROM.write(2, 0);
    delay(2500);

    Serial.println("All done!");
    Serial.println("Your unit is now ready to be used.");
    Serial.println("Please Reset to apply");

    display.clearDisplay();

      display.setTextColor(WHITE);
      display.setTextSize(0);
      display.setCursor(0,0);
      display.print("AUTOMATIC SETUP:");
      display.display();
      delay(1000);
      display.setTextColor(WHITE);
      display.setTextSize(0);
      display.setCursor(0,25);
      display.print("PLEASE RESET TO APPLY");
      display.display();
      display.setTextColor(WHITE);
      display.setTextSize(0);
      display.setCursor(0,15);
      display.print("      ALL DONE");
      display.display();
      analogWrite(A0, 255);
      delay(9999999);

  }
  


  ep_addr_04_startups = ep_addr_04_startups + 1;
  tempWarn_count = 0;
  tempWarn = LOW;
  display.clearDisplay();
  //debug:
  //ep_addr_00_boardstate = 0;
  //END
  
    
 }
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




  void loop() {
    

     //incomingbyte = Serial.readString();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//DEBUG/development tools below
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /*  if (incomingbyte == 'DEBUG = ENABLED') {  //TYPE "DEBUG = ENABLED" IN CONSOLE TO ENTER DEBUG
        Serial.print("[DEBUG]-[001]-> ");
        Serial.println("ENTERING DEBUG MODE");
        delay(3000);
        DEBUG == HIGH;
      }

      //if (DEBUG == HIGH) {//ENTER ALL DEBUG RELATED TOOLS HERE \/\/\/
        if (incomingbyte == 'DEBUG > OUTPUT = ON'){
          
          Serial.print("[DEBUG]-[001]-> ");
          Serial.println("OUTPUT - ACTIVE");
          DEBUG_OUTPUT == HIGH;
        }
        if(incomingbyte == 'DEBUG > READY = ON') {
          
          Serial.print("[DEBUG]-[001]-> ");
          Serial.println("READY - READY");
          DEBUG_READY == HIGH;
        }

      */
        
      
        
  

 // }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//STORAGE : RAM : EEPROM   \/\/\/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Input Data scripts below|
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
/*
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.setCursor(45,25);
  display.print("CYCLE ");
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.setCursor(83,25);
  display.print(cycle);
*/ 


if (debug_settings_timer == 5) {
  display.clearDisplay();
  display.setTextColor(WHITE);
    display.setTextSize(0);
    display.setCursor(0,0);
    display.print("SETTINGS");
    display.display();

}
else {
  //debug_settings_timer = debug_settings_timer + 1;
  digitalWrite(A0, LOW);
    display.drawCircle(40, 28, 3, WHITE); 

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
      //Serial.println("OUTPUT--OFF");
    
  }
    else {
    display.print("ACTIVE");
    digitalWrite(5, HIGH);
    display.display();
    display.clearDisplay();
      //Serial.println("OUTPUT--ACTIVE");
  }



/*
  buttonCurrent = digitalRead(button);
  

    
        if (buttonCurrent == HIGH && buttonPrevious == LOW){
            if (output == HIGH){
              output = LOW;
              
            }
          else {
              output = HIGH;
              
              }
            }
              display.clearDisplay();

        if (output == HIGH) {
              display.print("ACTIVE");
              analogWrite(5, 10);
              display.display();
              display.clearDisplay();
              Serial.println("OUTPUT--ACTIVE");
        }
        else {
              display.print("OFF");
              analogWrite(5, 0);
              display.display();
              display.clearDisplay();
              Serial.println("OUTPUT--OFF");
        }
*/

//~~~

    
                                    //READY STATUS
    display.setTextColor(WHITE);
    display.setTextSize(0);
    display.setCursor(95,10);

        if (digitalRead(6) == HIGH) {
      display.print("READY");
        //Serial.println("READY");
    
  }
      else {
          //Serial.println("--WARNING!--NOT READY--");
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
        //Serial.println("OK");
    
  }
      else {

          //Serial.println("SHORT CIRCUIT");
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
        analogWrite(11, 255);
        delay(100);
        analogWrite(11, 0);
        delay(200);

      }
  //~~~~


                                  //PANEL BACKLIGHT STATUS
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





  
            //TMRS -- Temperature Monitoring and Regulatory System   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 
  

  Serial.print("Temperature: "); 
  Serial.print(T);
  Serial.println(" F");

                            //Fan Regulator
    if (T >= 75) {
        digitalWrite(8, HIGH);
     fan = HIGH;
     display.fillCircle(40, 28, 3, WHITE);
      }
    else {
        digitalWrite(8, LOW);
     display.drawCircle(40, 28, 3, WHITE);
     fan = LOW;
      }


                            //tempWarn
        display.setTextColor(WHITE);
        display.setTextSize(1);
        display.setCursor(20,17);

    if (T >= 100)  {
     tempWarn_count = tempWarn_count + 1;
     tempWarn = HIGH;
     display.print("WARNING TEMP HIGH");
     Serial.println("WARNING TEMPERATURE REACHED >100*F");
     
      }
    else {
     tempWarn_count = 0;
     tempWarn = LOW;
      }



     if (T >= 120) {
        digitalWrite(8, HIGH);
     tempAlarm = HIGH;
     digitalWrite(A2, HIGH);
     delay(100);
     digitalWrite(A2, LOW);
     Serial.println("TEMPERATURE HAS REACHED >120*F");
     Serial.println("LM317 MAX TEMP IS 125*F");
      }
    else {
        digitalWrite(8, LOW);
     tempAlarm = LOW;
      }




    if (tempWarn_count == 1) {
        digitalWrite(A0, HIGH);
        digitalWrite(A2, HIGH);
        delay(150);
        digitalWrite(A2, LOW);
        delay(150);
        digitalWrite(A2, HIGH);
        delay(150);
        digitalWrite(A2, LOW);
        delay(150);
        digitalWrite(A2, HIGH);
        delay(150);
        digitalWrite(A2, LOW);
        delay(150);
    }
    if (tempWarn_count == 50) {
      tempWarn_count = 0;
      
    }
    if (tempWarn_count >= 1) {
      digitalWrite(A0, HIGH);
    }
    else {
      digitalWrite(A0, LOW);
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

        //cycle = cycle + 1; //~~~~~KEEP THESE LAST OF VOID LOOP
        //fan_count = fan_count + 1; //THIS TOO
        //buttonCurrent = buttonPrevious;

  }
}
