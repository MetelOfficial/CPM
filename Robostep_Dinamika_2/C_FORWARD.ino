void forward() {
  while (analogRead(A0) > 550 || analogRead(A2) > 550) {
    pid(255, 0.36);
  }
  go(250, 243);
  delay(650);
  go(0, 0);
  delay(T_Break);
}


void forwardStop() {
  while (analogRead(A0) > 700 || analogRead(A1) > 700) {
    pid(255, 0.32);
  }
  go(-100, -120);
  delay(70);
  go(0, 0);
  delay(50);
}