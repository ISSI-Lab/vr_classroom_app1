#include <Arduino.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("VR Gloves", "davisgc", 100);
//BleGamepad bleGamepad;

//Constants:
const int flexPin[5] = {A0, A3, A6, A7, A4};

//Variables:
int val[5];

int lastRead[5] = {0, 0, 0, 0, 0};

int sensorMin[5] = {3952, 3575, 3781, 3676, 3957};
int sensorMax[5] = {4095, 4016, 4087, 4011, 4095};

char keyval[5] = {'h', 'u', 'i', 'o', 'p'};

int mapMax = 100;
int mapMin = 0;
int threshhold = 50;

//Functions:
int isThresh (int val){
  return val >= threshhold;
}

void keyPress(int val, int idx){
  Serial.print(idx);
  Serial.print(": ");
  if (isThresh(val)){
    Serial.print("True, ");
    lastRead[idx] = 1;
    bleKeyboard.press(keyval[idx]);
  }else{
    Serial.print("False, ");
    if (lastRead[idx]){
      bleKeyboard.release(keyval[idx]);
      lastRead[idx] = 0;
    }
  }
}

void setup(){
  Serial.begin(115200);
  bleKeyboard.begin();
}

void loop(){
  if (bleKeyboard.isConnected()){
    //Serial.println("BLE Keyboard is connected.");
    for(int i = 0; i < 5; ++i){
      val[i] = analogRead(flexPin[i]);
      /*
      if (val[i] != 0){
        sensorMin[i] = min(val[i], sensorMin[i]);
        sensorMax[i] = max(val[i], sensorMax[i]);
      }
      */
    }

    for(int i = 0; i < 5; ++i){
      val[i] = constrain(map(val[i], sensorMin[i], sensorMax[i], mapMin, mapMax),mapMin,mapMax);
    }

    /*
    for(int i = 0; i < 5; ++i){
      keyPress(val[i], i);
    }
    Serial.println("/");
    */

    ///*

    for(int i = 0; i < 5; ++i){
      Serial.print(i);
      Serial.print(": ");
      Serial.print(val[i]);
      Serial.print(", ");
    }
    Serial.println("/");
    //*/

    delay(500);
  }
}