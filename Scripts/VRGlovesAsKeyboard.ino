/* How to use a flex sensor/resistro - Arduino Tutorial
   Fade an LED with a flex sensor
   More info: http://www.ardumotive.com/how-to-use-a-flex-sensor-en.html
   Dev: Michalis Vasilakis // Date: 9/7/2015 // www.ardumotive.com  */
   
#include <Arduino.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("VR Gloves", "davisgc", 100);
//BleGamepad bleGamepad;

//Constants:
const int flexPin0 = A0;
const int flexPin1 = A3;
const int flexPin2 = A6;
const int flexPin3 = A7;
const int flexPin4 = A4;

//Variables:
int value0;
int value1;
int value2;
int value3;
int value4;

int last0Read = 0;
int last1Read = 0;
int last2Read = 0;
int last3Read = 0;
int last4Read = 0;

char short0 = 'h';
char short1 = 'u';
char short2 = 'i';
char short3 = 'o';
char short4 = 'p';

int mapMax = 100;
int mapMin = 0;
int threshhold = 50;

int isThresh (int val){
  return val >= threshhold;
}

void setup(){
  Serial.begin(115200);       //Begin serial communication
  bleKeyboard.begin();
}

void loop(){
  if (bleKeyboard.isConnected()){
    Serial.println("BLE Keyboard is connected.");
    value0 = analogRead(flexPin0);
    value0 = constrain(map(value0, 2400, 3200, mapMin, mapMax),mapMin,mapMax);
    value1 = analogRead(flexPin1);
    value1 = constrain(map(value1, 2900, 3700, mapMin, mapMax),mapMin,mapMax);
    value2 = analogRead(flexPin2);
    value2 = constrain(map(value2, 1800, 2600, mapMin, mapMax),mapMin,mapMax);
    value3 = analogRead(flexPin3);
    value3 = constrain(map(value3, 2400, 3200, mapMin, mapMax),mapMin,mapMax);
    value4 = analogRead(flexPin4);
    value4 = constrain(map(value4, 2400, 3200, mapMin, mapMax),mapMin,mapMax);

    ///*

    Serial.print("0: ");
    if (isThresh(value0)){
      Serial.print("True, ");
      last0Read = 1;
      bleKeyboard.press(short0);
    }else{
      Serial.print("False, ");
      if (last0Read){
        bleKeyboard.release(short0);
        last0Read = 0;
      }
    }

    Serial.print("1: ");
    if (isThresh(value1)){
      Serial.print("True, ");
      last1Read = 1;
      bleKeyboard.press(short1);
    }else{
      Serial.print("False, ");
      if (last1Read){
        bleKeyboard.release(short1);
        last1Read = 0;
      }
    }

    Serial.print("2: ");
    if (isThresh(value2)){
      Serial.print("True, ");
      last2Read = 1;
      bleKeyboard.press(short2);
    }else{
      Serial.print("False, ");
      if (last2Read){
        bleKeyboard.release(short2);
        last2Read = 0;
      }
    }

    Serial.print("3: ");
    if (isThresh(value3)){
      Serial.print("True, ");
      last3Read = 1;
      bleKeyboard.press(short3);
    }else{
      Serial.print("False, ");
      if (last3Read){
        bleKeyboard.release(short3);
        last3Read = 0;
      }
    }

    Serial.print("4: ");
    if (isThresh(value4)){
      Serial.print("True, ");
      last4Read = 1;
      bleKeyboard.press(short4);
    }else{
      Serial.print("False, ");
      if (last4Read){
        bleKeyboard.release(short4);
        last4Read = 0;
      }
    }
    Serial.println("/");

    //*/
    /*

    Serial.print("0:");
    Serial.print(value0);
    Serial.print(",");
    Serial.print("1:");
    Serial.print(value1);
    Serial.print(",");
    Serial.print("2:");
    Serial.print(value2);
    Serial.print(",");
    Serial.print("3:");
    Serial.print(value3);
    Serial.print(",");
    Serial.print("4:");
    Serial.println(value4);
    */

    delay(500);
  }
}

