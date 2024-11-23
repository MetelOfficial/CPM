// #include <Wire.h>
// #include "Adafruit_TCS34725.h"
// #include <arduino_encoder.h>
// #include <LiquidCrystal_I2C.h>

// Encoder enc1;
// Encoder enc2;
// Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
// LiquidCrystal_I2C lcd(0x27, 16, 2);
// int asd = 0;
// int col[10];

// void setup() {
//   for (int i = 2; i <= 5; i++) pinMode(i, OUTPUT);
//   for (int i = 6; i <= 9; i++) pinMode(i, INPUT_PULLUP);
//   pinMode(12, INPUT_PULLUP);
//   pinMode(11, OUTPUT);  // Пищалка
//   Serial.begin(9600);
//   tcs.begin();
//   lcd.begin();
//   lcd.backlight();
//   Wire.begin();
//   enc1.setup(6, 7);
//   enc2.setup(8, 9);
//   Bip(1); //Один длинный
//   Bip(0); //Один короткий
//   Bip(2); //Два коротких
//   // Bip(3); //Два длинных
// }
// void go(int S2, int S1) {
//   if (S1 > 0)digitalWrite(2, 1); else digitalWrite(2, 0);
//   if (S2 > 0)digitalWrite(4, 1); else digitalWrite(4, 0);
//   analogWrite(3, abs(S1)); analogWrite(5, abs(S2));
// } 
// void leftB() {
//   go(-120, 80);
//   delay(1000);
//   go(0, 0);
//   go(-120, 80);
//   while (dat(A0) > 700);
//   while (dat(A0) < 700);
//   go(0, 0);
//   go(-110, 80);
//   delay(600);
//   go(0, 0);
//   delay(50);
// }
// void Bip(int a){
//   switch(a){
//     case 0:digitalWrite(11, 1);
//            delay(20);
//            digitalWrite(11, 0);
//            delay(100);
//      break;
//     case 1:digitalWrite(11, 1);
//            delay(300);
//            digitalWrite(11, 0);
//            delay(100);
//      break;
//     case 2:digitalWrite(11, 1);
//            delay(150);
//            digitalWrite(11, 0);
//            delay(100);
//            digitalWrite(11, 1);
//            delay(150);
//            digitalWrite(11, 0);
//            delay(100);
//      break; 
//     case 3:digitalWrite(11, 1);
//            delay(1000);
//            digitalWrite(11, 0);
//            delay(1000);
//            digitalWrite(11, 1);
//            delay(1000);
//            digitalWrite(11, 0);
//            delay(1000);
//      break; 
//   }
// }
// void forward() {
//   while(analogRead(A0) > 670 || analogRead(A1) > 670){
//     pid(100, 0.32367);
//   }
//   go(-100, 0);
//   delay(120);
//   go(0, 0);
//   delay(1000);
//   go(140, 130);
//   delay(500);
//   go(0, 0);
//   delay(50);
// }
// void pid(int V, float K) {
//   int E = analogRead(A0) - analogRead(A1);     
//   int d1 = V + K * E; d1 = constrain(d1, -255, 250);
//   int d2 = V - K * E; d2 = constrain(d2, -255, 250);
//   go(d1, d2);
// }
// void rightB() {
//   go(120, -80);
//   delay(1000);
//   go(0, 0);
//   go(120, -80);
//   while (dat(A1) > 700);
//   while (dat(A1) < 700);
//   go(0, 0);
//   go(110, -80);
//   delay(600);
//   go(0, 0);
//   delay(50);
// }
// void left(int K, int V, int N) {
//   enc1.clear();
//   enc2.clear();
//   while (1) {
//     long int error = abs(enc1.get()) - abs(enc2.get());
//     int uprvozd = K * error;
//     go(-(V - uprvozd), V + uprvozd);
//     if (abs(enc1.get()) >= N || abs(enc2.get()) >= N) {
//       go(0, 0);
//       delay(1000);
//       enc1.clear();
//       enc2.clear();
//       break;
//     } else {
//     }  //pid(BASE_SPEED,0.3);
//   }
// }
// void encpid(double K, int V, int N) {
//   while (1) {
//     long int error = enc2.get() - enc1.get();
//     int uprvozd = K * error;
//     go(V + uprvozd, V - uprvozd);
//     if (abs(enc1.get()) >= N || abs(enc2.get()) >= N) {
//       go(-100, -100);
//       delay(70);
//       go(0, 0);
//       enc1.clear();enc2.clear();
//       delay(100);
//       break;
//     } else {
//     }  //pid(BASE_SPEED,0.3);
//   }
// }
// void loop() {
//   if (!digitalRead(12) == 1) { asd++; }  if (asd > 0) {
//     encpid(1.3, 100, 3000);         //Доезд до первого кубика
//     for (int i = 0; i <= 9; i++) {  //Повторить 10 раз
//       uint16_t clear, red, green, blue;
//       tcs.getRawData(&red, &green, &blue, &clear);
//       if (red > green && red > blue) {
//         col[i] = 1;  // Красный
//       } else if (green > red && green > blue && (red > 150 && blue > 150)) {
//         col[i] = 2;  // Зеленый(желтый  )
//       } else if (blue > red && blue > green) {
//         col[i] = 3;  // Синий
//       } else if (red < 150 && green < 150 && blue < 150) {
//         col[i] = 0;  // Пусто
//       }
//       lcd.setCursor(13, 0);
//       lcd.print(i + 1);
//       Bip(0);
//       lcd.setCursor(i, 1);
//       if (col[i] == 1) {lcd.print("R");}
//       if (col[i] == 2) {lcd.print("G");}
//       if (col[i] == 3) {lcd.print("B");}
//       if (col[i] == 0) {lcd.print("-");}
//       encpid(1.3, 100, 1150);
//     }
//     forward();
//     for (int i = 0; i <= 9; i++) {
//       Bip(0);
//       lcd.setCursor(i, 0);
//       if (col[i] == 1) {lcd.print("T");leftB();leftB();forward();}
//       if (col[i] == 2) {lcd.print("L");leftB();forward();}
//       if (col[i] == 3) {lcd.print("R");rightB();forward();}
//       if (col[i] == 0) {lcd.print("F");forward();}
//     }
//     Bip(3);
//     leftB();
//     leftB();
//     forward();
//     leftB();
//     leftB();
//     forward();
//     leftB();
//     leftB();
//     Bip(2);
//     for (int i = 0; i <= 9; i++) {lcd.setCursor(i, 1);lcd.print(" ");}
//      for (int i = 9; i >= 0; i--) {
//       Bip(0);
//       lcd.setCursor(abs(i-9), 1);
//       if (col[i] == 1) {lcd.print("T");forward();leftB();leftB();}
//       if (col[i] == 2) {lcd.print("R");forward();rightB();}
//       if (col[i] == 3) {lcd.print("L");forward();leftB();}
//       if (col[i] == 0) {lcd.print("F");forward();}
//     }
//     forward();
//     encpid(1.3, 100, 1);  
//     encpid(1.3, 100, 5000);
//     left(1.3, 100, 1500);  
//     encpid(1.3, 100, 1);  
//     while(1);
//   }
// }