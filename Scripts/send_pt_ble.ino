#include <ESP32Servo.h> 
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

Servo myservo;
BluetoothSerial SerialBT;

int servoPin = 13;
int potPin = 12;
int ADC_Max = 4096;


int val;

int valmax = 0;

int mem = 0;

void setup()
{
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  myservo.setPeriodHertz(50);
  myservo.attach(servoPin, 500, 2400);
}

void loop() {
  val = analogRead(potPin);            // read the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, ADC_Max, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  valmax = max(valmax, val);
  if (val != mem){
    Serial.print("potval: ");
    Serial.print(val);
    Serial.print(", valmax: ");
    Serial.println(valmax);
    mem = val;
    myservo.write(val);                  // set the servo position according to the scaled value
    SerialBT.println(val);
  }
  delay(200);                          // wait for the servo to get there
}