void leftB() {
  // go(-70, 70);
  // while (analogRead(A0) > 800);
  // while (analogRead(A0) < 800);
  // while (analogRead(A0) > 800);
  // go(70, -70);
  // delay(50);
  // go(0, 0);
  // delay(1000);
  go(-255, 255);
  delay(700);
  while (analogRead(A0) > 650);
  while (analogRead(A0) < 650);
  go(-200, 200);
  delay(100);
  go(0, 0);
  delay(T_Break);
}


void rightB() {
  // go(70, -70);
  // while (analogRead(A1) < 800);
  // while (analogRead(A1) > 800);
  // while (analogRead(A1) < 800);
  // go(-70, 70);
  // delay(50);
  // go(0, 0);
  // delay(1000);
  go(200, -200);
  delay(950);
  go(200, -200);
  while (analogRead(A0) > 650);
  while (analogRead(A0) < 650);
  go(-200, 200);
  delay(370);
  go(0, 0);
  delay(T_Break);
}