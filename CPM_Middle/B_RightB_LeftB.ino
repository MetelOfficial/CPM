void leftB() {
  go(-120, 80);
  delay(1000);
  go(0, 0);
  go(-120, 80);
  while (dat(A0) > 700);
  while (dat(A0) < 700);
  go(0, 0);
  go(-110, 80);
  delay(600);
  go(0, 0);
  delay(50);
}


void rightB() {
  go(120, -80);
  delay(1000);
  go(0, 0);
  go(120, -80);
  while (dat(A1) > 700);
  while (dat(A1) < 700);
  go(0, 0);
  go(110, -80);
  delay(600);
  go(0, 0);
  delay(50);
}