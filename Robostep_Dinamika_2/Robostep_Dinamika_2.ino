//Powered by METEL
//Version 6.3.8
//Date 23.11.24


#include <Servo.h>
#include <arduino_encoder.h>

int sp = 255;
int asd = 0;
int T_Break = 500;
Servo ser;
Encoder enc1;
Encoder enc2;
void setup() {
  for (int i = 4; i <= 7; i++) pinMode(i, OUTPUT);  //Моторы
  pinMode(2, INPUT_PULLUP);                         //Энкодер левый пин 1
  pinMode(3, INPUT_PULLUP);                         //Энкодер левый пин 2
  pinMode(11, INPUT_PULLUP);                        //Энкодер правый пин 1
  pinMode(12, INPUT_PULLUP);                        //Энкодер правый пин 2
  pinMode(10, INPUT_PULLUP);                        //Кнопка
  // pinMode(4, OUTPUT);
  Serial.begin(9600);
  ser.attach(9);
  ser.write(80);
  enc1.setup(2, 3);
  enc2.setup(11, 12);
}
void right(int K, int V, int N) {
  enc1.clear();
  enc2.clear();
  while (1) {
    long int error = abs(enc1.get()) - abs(enc2.get());
    int uprvozd = K * error;
    go(V + uprvozd, -(V + uprvozd));
    if (abs(enc1.get()) >= N || abs(enc2.get()) >= N) {
      go(-150, 150);
      delay(90);
      go(0, 0);
      enc1.clear();
      enc2.clear();
      //      steps++;
      break;
    } else {
    }  //pid(BASE_SPEED,0.3);
  }
}
void left(int K, int V, int N) {
  enc1.clear();
  enc2.clear();
  while (1) {
    long int error = abs(enc1.get()) - abs(enc2.get());
    int uprvozd = K * error;
    go(-(V - uprvozd), V + uprvozd);
    if (abs(enc1.get()) >= N || abs(enc2.get()) >= N) {
      go(150, -150);
      delay(90);
      go(0, 0);
      enc1.clear();
      enc2.clear();
      //      steps++;
      break;
    } else {
    }  //pid(BASE_SPEED,0.3);
  }
}
void encpid(double K, int V, int N) {
  while (1) {
    long int error = enc1.get() - enc2.get();
    int uprvozd = K * error;
    go(V + uprvozd, V - uprvozd);
    if (abs(enc1.get()) >= N || abs(enc2.get()) >= N) {
      go(-100, -100);
      delay(90);
      go(0, 0);
      enc1.clear();
      enc2.clear();
      delay(100);
      break;
    } else {
    }  //pid(BASE_SPEED,0.3);
  }
}
void z() {
  ser.write(170);
}
void o() {
  ser.write(80);
  // delay(600);
  // go(-255, -255);
  // delay(500);
  // go(0, 0);
}
//encpid(0.01259, 250, 2000);
//left(0.01259, 250, 4000);
//right(0.01259, 250, 4000);
void loop() {
  if (!digitalRead(10) == 1) { asd++; }
  if (asd > 0) {
    start();
    














    finish();
    asd = 0;
  }
}
