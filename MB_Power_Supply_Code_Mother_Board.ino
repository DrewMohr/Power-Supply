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

#include <Wire.h>;



int i = 0;
int j = 0;
int SECONDARY_BOARD_ON_BOARD = 0;
int button = 8;
int output = 7;

int buttonCurrent;
int buttonPrevious = LOW;

void setup() {
  
  pinMode(3, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
  Serial.begin(9600);

    Serial.println("Mother Board Driver V1");

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
  tone(A1, 1000, 100); // play tone 70 (A#5 = 932 Hz)
  delay(100);
  tone(A1, 1200, 100);
  delay(100);
  tone(A1, 1400, 100);
  delay(100);
  tone(A1, 1600, 100);
  delay(100);
  tone(A1, 1800, 100);
  delay(100);
  delay(500); // Wait for 500 millisecond(s)
  // Start up test begin
  Serial.println("DEBUG-----SEND - - - WAITING FOR CONFIRMATION...");
  digitalWrite(10, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(11, HIGH);
  delay(30); // Wait for 30 millisecond(s)
  digitalWrite(7, HIGH);
  delay(30); // Wait for 30 millisecond(s)
  digitalWrite(7, LOW);
  delay(30); // Wait for 30 millisecond(s)
  digitalWrite(7, HIGH);
    digitalWrite(5, HIGH);
  delay(30); // Wait for 30 millisecond(s)
  digitalWrite(7, LOW);
  delay(30); // Wait for 30 millisecond(s)
  digitalWrite(7, HIGH);
  delay(30); // Wait for 30 millisecond(s)
  digitalWrite(7, LOW);
  delay(70); // Wait for 70 millisecond(s)
  digitalWrite(7, HIGH);
  delay(30); // Wait for 30 millisecond(s)
  digitalWrite(7, LOW);
  delay(30); // Wait for 30 millisecond(s)
  digitalWrite(7, HIGH);
  delay(30); // Wait for 30 millisecond(s)
  digitalWrite(7, LOW);
    digitalWrite(5, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(13, LOW);
  digitalWrite(11, LOW);
  // Start up test end
  delay(500); // Wait for 500 millisecond(s)
  digitalWrite(7, HIGH);
  digitalWrite(13, HIGH);
  delay(500); // Wait for 500 millisecond(s)
  digitalWrite(13, LOW);
  delay(500); // Wait for 500 millisecond(s)
    analogWrite(5, 30);
  digitalWrite(13, HIGH);
  delay(500); // Wait for 500 millisecond(s)
  digitalWrite(13, LOW);
  delay(500); // Wait for 500 millisecond(s)
  digitalWrite(7, LOW);
  tone(A1, 1500, 90);
  delay(100);
  tone(A1, 1500, 90);
  analogWrite(5, 50);
  
  digitalWrite(13, HIGH);
  delay(500); // Wait for 500 millisecond(s)
  digitalWrite(13, LOW);
  delay(500); // Wait for 500 millisecond(s)
  digitalWrite(13, HIGH);
  if (digitalRead(12) != HIGH) {
    Serial.println("DEBUG-----NO DATA PANEL DETECTED");
    Serial.println("DEBUG-----ERROR: 1-300");
    tone(A1, 932, 50); // play tone 70 (A#5 = 932 Hz)
    delay(100); // Wait for 100 millisecond(s)
    tone(A1, 932, 50); // play tone 70 (A#5 = 932 Hz)
    delay(100); // Wait for 100 millisecond(s)
    tone(A1, 932, 50); // play tone 70 (A#5 = 932 Hz)
    delay(100); // Wait for 100 millisecond(s)
    tone(A1, 932, 50); // play tone 70 (A#5 = 932 Hz)
    delay(100); // Wait for 100 millisecond(s)
    tone(A1, 932, 50); // play tone 70 (A#5 = 932 Hz)
    delay(100); // Wait for 100 millisecond(s)
    tone(A1, 932, 50); // play tone 70 (A#5 = 932 Hz)
    delay(100); // Wait for 100 millisecond(s)
  }
  // Setup~~

  output = LOW;
}

void loop()
{
  
  delay(50); // Wait for 80 millisecond(s)
  Serial.println("Check");
  buttonCurrent = digitalRead(button);

  if (buttonCurrent == HIGH && buttonPrevious == LOW){
    if (output == HIGH){
      output = LOW;
      digitalWrite(7, LOW);
      analogWrite(5, 50);
    }
    else {
      output = HIGH;
      digitalWrite(7, HIGH);
      analogWrite(5, 200);
    }
  }
  digitalWrite(7, output);

  buttonPrevious = buttonCurrent;

}
