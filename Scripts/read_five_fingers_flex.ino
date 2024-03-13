const int flexPin0 = A0;
const int flexPin1 = A3;
const int flexPin2 = A6;
const int flexPin3 = A7;
const int flexPin4 = A4;

int value0;
int value1;
int value2;
int value3;
int value4;


void setup(){
  Serial.begin(115200);

}

void loop(){
  
  value0 = analogRead(flexPin0);
  value0 = map(value0, 2600, 3800, 0, 100);
  value1 = analogRead(flexPin1);
  value1 = map(value1, 2600, 3800, 0, 100);
  value2 = analogRead(flexPin2);
  value2 = map(value2, 2600, 3800, 0, 100);
  value3 = analogRead(flexPin3);
  value3 = map(value3, 2600, 3800, 0, 100);
  value4 = analogRead(flexPin4);
  value4 = map(value4, 2600, 3800, 0, 100);
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
  delay(100);
  
}

