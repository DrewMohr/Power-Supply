//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Andrew Mohr 2019-2020
//Version: Beta 2.2.4.7
//Date Started: 12/10/2019 09:24pm
//Last Date Officially Updated: 2/15/2020 04:27pm
//Power Supply Mother Board CPU
//--------------------------------------------------
//           CHANGE LOG BELOW
//                Format:
// M/D/Y HH:MMam/pm | v.VERSION x.y.z -- Changes
//--------------------------------------------------
// 2/15/2020 04:27pm | v.Beta 2.2.4.7 
// -- Changelog created
// -- Motherboard CPU Rebuild
// -- Loop Processing Reconfigured to be more efficient
// -- Trigger Button System Rebuild
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <Wire.h>
#include <DHT.h>
#include <Servo.h>
#include <Adafruit_GFX.h>

  //Variables Start
int i = 0;
int j = 0;
int SECONDARY_BOARD_ON_BOARD = 0;
int button = 8;
int output = 7; //Relay
int fan = 5;
int fan_count;
int buttonCurrent;
int buttonPrevious = LOW;

String v = "Alpha Build 0.8.7"; //Release Version-------------------------------UPDATE THIS WHEN UPDATING
String dv = "dev.prealpha-0.8.8w26"; //Development Version----------------------THIS TOO DAMMIT

  //Variables End

void setup() {
  Serial.begin(9600);
  
  pinMode(A1, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A7, OUTPUT); 
  

  pinMode(3, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(12, INPUT);
  pinMode(8, INPUT);
  pinMode(6, OUTPUT);
  pinMode(button, INPUT);
  pinMode(output, OUTPUT);
  
  // Setup~~
  analogWrite(3, 0);
  tone(A1, 2793.83, 300); // play tone F#7
  delay(300);
  tone(A1, 2217.46, 300); // play tone C#7
  delay(100);
  delay(500); // Wait for 500 millisecond(s)
  // Start up test begin
  Serial.println(v);
  Serial.println(dv);
  Serial.println("DEBUG-----SEND - - - WAITING FOR CONFIRMATION...");
  digitalWrite(10, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(11, HIGH);
  
  delay(30); // Wait for 30 millisecond(s)
  
    digitalWrite(5, HIGH);
  
  delay(150); // Wait for 30 millisecond(s)
 
    digitalWrite(5, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(13, LOW);
  digitalWrite(11, LOW);
  // Start up test end
  delay(500); // Wait for 500 millisecond(s)
  
  digitalWrite(13, HIGH);
  delay(500); // Wait for 500 millisecond(s)
  digitalWrite(13, LOW);
  delay(500); // Wait for 500 millisecond(s)
    analogWrite(5, 30);
  digitalWrite(13, HIGH);
  delay(500); // Wait for 500 millisecond(s)
  digitalWrite(13, LOW);
  delay(500); // Wait for 500 millisecond(s)
  
  delay(100);
  analogWrite(5, 50);
  
  digitalWrite(13, HIGH);
  delay(500); // Wait for 500 millisecond(s)
  digitalWrite(13, LOW);
  delay(500); // Wait for 500 millisecond(s)
  digitalWrite(13, HIGH);


  
  
       fan_count = 0;
  
  // Setup~~
     
  output = LOW;
}

  void loop() {

  
  delay(50); // Wait for 80 millisecond(s)
  Serial.println("Check");
  buttonCurrent = digitalRead(button);

  if (buttonCurrent == HIGH && buttonPrevious == LOW){
    if (output == HIGH){
      output = LOW;
      digitalWrite(7, LOW);
      digitalWrite(A7, LOW);
      analogWrite(5, 50);
    }
    else {
      output = HIGH;
      digitalWrite(7, HIGH);
      digitalWrite(A7, HIGH);
      analogWrite(5, 200);
    }
  }

  
                        //TMRS -- Temperature Monitoring and Regulatory System  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (digitalRead(A7) == HIGH) {
      digitalWrite(5, HIGH);
      fan = HIGH;
    }
    else {
        analogWrite(5, 50);             //Change this for Preferance (When T is at an acceptable level, the fan will still spin - only slowly(50/255))
        //digitalWrite(5, LOW);         //Change this for Preferance (When T is at an acceptable level, the fan will halt)
    }

  

    

        buttonPrevious = buttonCurrent;  //Keep this at end of void loop()
        
}


