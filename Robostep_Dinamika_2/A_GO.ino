void go(int S2, int S1) {
  if (S2 > 0)digitalWrite(4, 1); else digitalWrite(4, 0);
  if (S1 > 0)digitalWrite(7, 1); else digitalWrite(7, 0);
  S1 = constrain(S1, -255, 255);
  S2 = constrain(S2, -255, 255);
  analogWrite(5, abs(S1)); analogWrite(6, abs(S2));
}

void start(){
  go(250, 255);
  delay(900);
  go(0, 0);
  delay(T_Break);
  forward();
}

void finish(){
  forward();
  go(250, 255);
  delay(1700);
  go(0, 0);
  while(1){go(0, 0);}
}
//     Таскает 2 банки туда сюда по 4 перекресткам
//     forward();
//     rightB();
//     forward();
//     forward();
//     z();
//     rightB();
//     rightB();
//     forward();
//     forward();
//     rightB();
//     forward();
//     forward();
//     o();
//     rightB();
//     forward();
//     forward();
//     rightB();
//     forward();
//     forward();
//     rightB();
//     forward();
//     z();
//     rightB();
//     rightB();
//     forward();
//     forward();
//     forward();
//     o();
//     rightB();
//     forward();
//     rightB();
//     forward();
//     rightB();
//     rightB();
//     rightB();
//     forward();
//     rightB();
//     forward();
//     forward();
//     z();
//     rightB();
//     rightB();
//     forward();
//     forward();
//     rightB();
//     rightB();
//     rightB();
//     forward();
//     forward();
//     o();
//     rightB();
//     forward();
//     forward();
//     forward();
//     forward();
//     rightB();
//     rightB();
//     rightB();
//     rightB();
//     forward();
//     rightB();
//     forward();
//     z();
//     rightB();
//     rightB();
//     forward();
//     forward();
//     forward();
//     o();
//     rightB();
//     forward();
//     rightB();
//     rightB();
//     rightB();
//     forward();
//     rightB();



//Робостеп без банок
    // start();
    // rightB();
    // forward();
    // forward();
    // forward();
    // forward();
    // rightB();
    // rightB();
    // forward();
    // forward();
    // leftB();
    // forward();
    // rightB();
    // forward();
    // forward();
    // forward();
    // leftB();
    // forward();
    // rightB();
    // forward();
    // rightB();
    // rightB();
    // forward();
    // finish();