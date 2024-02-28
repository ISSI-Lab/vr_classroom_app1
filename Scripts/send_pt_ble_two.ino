#include <ESP32Servo.h> 
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//Servo myservo;
BluetoothSerial SerialBT;

//int servoPin = 13;
int potPin = 12;
int potPin2 = 14;
int ADC_Max = 4096;


int val;
int val2;

int valmax = 0;

int mem = 0;
int mem2 = 0;

void setup()
{
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  //myservo.setPeriodHertz(50);
  //myservo.attach(servoPin, 500, 2400);
}

void loop() {
  val = analogRead(potPin);            // read the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, ADC_Max, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  valmax = max(valmax, val);

  val2 = analogRead(potPin2);
  val2 = map(val2, 0, ADC_Max, 0, 180);
  valmax = max(valmax, val2);

  if (val != mem || val2 != mem2){
    Serial.print("potval1: ");
    Serial.print(val);
    Serial.print("potval2: ");
    Serial.print(val2);
    Serial.print(", valmax: ");
    Serial.println(valmax);
    mem = val;
    SerialBT.print(val);
    SerialBT.print(",");
    SerialBT.println(val2);
  }

  delay(200);                          // wait for the servo to get there
}