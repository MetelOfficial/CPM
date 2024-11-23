void forward() {
  while(analogRead(A2) > 600 || analogRead(A7) > 600){
    pid(110, 0.32367);
  }
  go(-100, 0);
  delay(120);
  go(0, 0);
  delay(1000);
  go(140, 130);
  delay(500);
  go(0, 0);
  delay(50);
}
