//Powered by METEL
//Version 34.1.6
//Date 23.11.24



#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <arduino_encoder.h>
#include <LiquidCrystal_I2C.h>

Encoder enc1;
Encoder enc2;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
LiquidCrystal_I2C lcd(0x27, 16, 2);
int asd = 0;
int col[10];
int max1=0;
int max2=0;

void setup() {
  for (int i = 2; i <= 5; i++) pinMode(i, OUTPUT);
  for (int i = 6; i <= 9; i++) pinMode(i, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(11, OUTPUT);  // Пищалка
  Serial.begin(9600);
  tcs.begin();
  lcd.begin();
  lcd.backlight();
  Wire.begin();
  enc1.setup(6, 7);
  enc2.setup(8, 9);
  Bip(1); //Один длинный
  Bip(0); //Один короткий
  Bip(2); //Два коротких
  // Bip(3); //Два длинных
}
int dat(int data) {
  return abs(analogRead(data)-1023);
}
void right(int K, int V, int N) {
  enc1.clear();
  enc2.clear();
  while (1) {
    long int error = abs(enc1.get()) - abs(enc2.get());
    int uprvozd = K * error;
    go(V + uprvozd, -(V + uprvozd));
    if (abs(enc1.get()) >= N || abs(enc2.get()) >= N) {
      go(0, 0);
      delay(1000);
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
      go(0, 0);
      delay(1000);
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
    long int error = enc2.get() - enc1.get();
    int uprvozd = K * error;
    go(V + uprvozd, V - uprvozd);
    if (abs(enc1.get()) >= N || abs(enc2.get()) >= N) {
      go(-100, -100);
      delay(70);
      go(0, 0);
      enc1.clear();
      enc2.clear();
      delay(100);
      break;
    } else {
    }  //pid(BASE_SPEED,0.3);
  }
}
void loop() {
  if (!digitalRead(12) == 1) { asd++; }
  if (asd > 0) {
    encpid(1.3, 100, 3000);         //Доезд до первого кубика
    for (int i = 0; i <= 9; i++) {  //Повторить 10 раз
      uint16_t clear, red, green, blue;
      tcs.getRawData(&red, &green, &blue, &clear);
      if (red > green && red > blue) {
        col[i] = 1;  // Красный
      } else if (green > red && green > blue && (red > 150 && blue > 150)) {
        col[i] = 2;  // Зеленый(желтый  )
      } else if (blue > red && blue > green) {
        col[i] = 3;  // Синий
      } else if (red < 150 && green < 150 && blue < 150) {
        col[i] = 0;  // Пусто
      }
      lcd.setCursor(13, 0);
      lcd.print(i + 1);
      Bip(0);
      lcd.setCursor(i, 1);
      if (col[i] == 1) {lcd.print("R");}
      if (col[i] == 2) {lcd.print("G");}
      if (col[i] == 3) {lcd.print("B");}
      if (col[i] == 0) {lcd.print("-");}
      // delay(1000);
      encpid(1.3, 100, 1150);
    }
    forward();
    for (int i = 0; i <= 9; i++) {
      Bip(0);
      lcd.setCursor(i, 0);
      if (col[i] == 1) {lcd.print("T");leftB();leftB();forward();}
      if (col[i] == 2) {lcd.print("L");leftB();forward();}
      if (col[i] == 3) {lcd.print("R");rightB();forward();}
      if (col[i] == 0) {lcd.print("F");forward();}
    }
    Bip(3);
    leftB();
    leftB();
    forward();
    leftB();
    leftB();
    forward();
    leftB();
    leftB();
    Bip(2);
    for (int i = 0; i <= 9; i++) {lcd.setCursor(i, 1);lcd.print(" ");}
     for (int i = 9; i >= 0; i--) {
      Bip(0);
      lcd.setCursor(abs(i-9), 1);
      if (col[i] == 1) {lcd.print("T");forward();leftB();leftB();}
      if (col[i] == 2) {lcd.print("R");forward();rightB();}
      if (col[i] == 3) {lcd.print("L");forward();leftB();}
      if (col[i] == 0) {lcd.print("F");forward();}
    }
    forward();
    encpid(1.3, 100, 1);  
    encpid(1.3, 100, 5000);
    left(1.3, 100, 1500);   
    encpid(1.3, 100, 1);  
    while(1);     
  }
}
