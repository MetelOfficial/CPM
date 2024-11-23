//Powered by Sergey Kushkov
//Version 2.1
//Date 08.02.24


#include <arduino_encoder.h> // Подключаем библиотеку

// Создаем объекты для работы с:
Encoder enc1; // первым энкодером
Encoder enc2; // вторым энкодером

int btn1=13;   // кнопка 1
int btn2=14;   // кнопка 2

char ABC[13] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', '1', '2', '3', '4', '5', ' '}; // массив алфавита
int XY[6] = {12, 12, 12, 12, 12, 12};   // массив координат
int flagBtn1 = 0;
int flagBtn2 = 0;
int Mo = 150;
int N = 0;
int flag = 0;
int Step = 0;
int X;
int d1 = 0;
int d2 = 0;
float Kp = 0.15;

void setup() {
  for (int i = 2; i <= 5; i++) pinMode(i, OUTPUT);
  Serial.begin(9600);
  enc1.setup(6, 7); // Энкодер 1 подключен к пинам D6 и D7 (двунаправленный)
  enc2.setup(8, 9); // Энкодер 2 подключен к пинам D8 и D9 (двунаправленный)
}
//
void go(int L, int R) {
  if (L > 0) digitalWrite(2, 1); else digitalWrite(2, 0);
  if (R > 0) digitalWrite(4, 1); else digitalWrite(4, 0);
  analogWrite(3, abs(L)); analogWrite(5, abs(R));
}
//
void pid(int V, float K) {
  int E = analogRead(A0) - analogRead(A1);
  int M1 = V + E * K; M1 = constrain(M1, -250, 250);
  int M2 = V - E * K; M2 = constrain(M2, -250, 250);
  go(M1, M2);
}
//
void pidEncN(int V, int K, int n) {
  int E = abs(enc1.get()) - abs(enc2.get());
  int M1 = V + E * K; M1 = constrain(M1, -250, 250);
  int M2 = V - E * K; M2 = constrain(M2, -250, 250);
  go(M1, M2);
  if (abs(enc1.get()) > n || abs(enc2.get() > n)) {
    go(0, 0); delay(2000);
    Step++;
    enc1.clear();
    enc2.clear();
  }
}
//
void pidEncBl(int V, int K, int Bl) {
  int E = abs(enc1.get()) - abs(enc2.get());
  int M1 = V + E * K; M1 = constrain(M1, -250, 250);
  int M2 = V - E * K; M2 = constrain(M2, -250, 250);
  go(M1, M2);
  if (analogRead(A0) < Bl || analogRead(A1) < Bl) {
    go(0, 0); delay(2000);
    Step++;
    enc1.clear();
    enc2.clear();
  }
}
//
void encLeftN(int V, int K, int n) {
  int E = abs(enc1.get()) - abs(enc2.get());
  int M1 = V + E * K; M1 = constrain(M1, -250, 250);
  int M2 = V - E * K; M2 = constrain(M2, -250, 250);
  go(-M1, M2);
  if (abs(enc1.get()) > n || abs(enc2.get()) > n) {
    go(0, 0); delay(2000);
    enc1.clear();
    enc2.clear();
  }
}
//
void encRightN(int V, int K, int n) {
  int E = abs(enc1.get()) - abs(enc2.get());
  int M1 = V + E * K; M1 = constrain(M1, -250, 250);
  int M2 = V - E * K; M2 = constrain(M2, -250, 250);
  go(M1, -M2);
  if (abs(enc1.get()) > n || abs(enc2.get()) > n) {
    go(0, 0); delay(2000);
    enc1.clear();
    enc2.clear();
  }
}
//
void indicator() {
  if (Step == 0) {
    if (digitalRead(btn2) == true)
    {
      if (flagBtn2 == 0) {
        flagBtn2 = 1;
        delay(500);
        if (N == 0) {
          delay(1000);
          Step++;
        }
        else
        {
          if (N > 0) {
            N--;
            XY[N] = 12;
          }
        }
      }
    }
    else {
      flagBtn2 = 0;
    }
    if (digitalRead(btn1) == true)
    {
      if (flagBtn1 == 0) {  //delay(500);
        flagBtn1 = 1;
        XY[N] = X;
        delay(500);
        N++;
        if (N > 5) N = 0;
      }
    }
    else
    {
      X = abs(enc1.get()/ 40);
      if (X > 11) X = 11;
      //
      //вот тут нужно выводить данные на экран из массива ABC[X]);
      //
      flagBtn1 = 0;
    }
    //вот тут нужно выводить данные на экран: ABC[XY[0]], ABC[XY[1]]);
    //вот тут нужно выводить данные на экран: ABC[XY[2]], ABC[XY[3]]);
    //вот тут нужно выводить данные на экран: ABC[XY[4]], ABC[XY[5]]);
  }

}
//
void Input() {
  pidEncN(Mo, 5, 500);
  go(0, 0); delay(1000);
  Step++;
}
//
void Cross(int T) {
  if (XY[T] != 0) {
    d1 = analogRead(A0);
    d2 = analogRead(A1);

    if (d1 < 500 && d2 < 500)
    {
      go(Mo,Mo);
      if (flag == 0) {
        N++;
        flag = 1;
      }

      int X = XY[T];
      if (X == N) {
        pidEncN(Mo, 5, 300);
        go(0, 0); delay(500);
        encLeftN(Mo, 5, 1200);
        tone(15, 800); //указать контакт пина пищалки пример - 15
        go(0, 0); delay(2000);
        N = 0;
        Step++;
      }
    }
    else {
      flag = 0;
      pid(Mo, Kp);
    }
  }
  else
  {
    encLeftN(Mo, 5, 1200); //
    go(0, 0); delay(3000);
    N = 0;
    Step++;
  }
}
//
//
void CrossOut(int T) {
  if (XY[T] != 0) {
    d1 = analogRead(A0);
    d2 = analogRead(A1);

    if (d1 < 500 && d2 < 500)
    {
      go(Mo, Mo);
      if (flag == 0) {
        N++;
        flag = 1;
      }
      int X = XY[T];
      if (X == N) {
        pidEncN(Mo, 5, 300);
        go(0, 0); delay(1000);
        N = 0;
        Step++;
        int Y = XY[T + 1] - 6 - 3;
        if (Y == 0) {
          go(0, 0); delay(1000);
          Step++;
        }
        else if (Y > 0)encLeftN(Mo, 5, 1200);
        else encLeftN(Mo, 5, 1200);
      }
    }
    else {
      flag = 0;
      pid(Mo,Kp);
    }
  }
  else
  {
    int Y = XY[T + 1] - 6 - 3;
    if (Y == 0) {
      go(0, 0);
      Step++;
    }
    else if (Y > 0)encLeftN(Mo, 5, 1200);
    else encLeftN(Mo, 5, 1200);
    N = 0;
    Step++;
  }
}

//
void Ulica(int T) {
  d1 = analogRead(A0);
  d2 = analogRead(A1);
  if (d1 < 500 && d2 < 500)
  {
    go(Mo, Mo);
    if (flag == 0) {
      N++;
      flag = 1;
    }
    int Y = XY[T + 1] - 6 - 3;
    if (N == 1) {
      pidEncN(Mo, 5, 300);
      if (Y == 0)go(0, 0);
      else if (Y > 0) encLeftN(Mo, 5, 1200);
      else encLeftN(Mo, 5, 1200);
    }
    if (abs(Y) + 1 == N) {
      pidEncN(Mo, 5, 300);
      if (Y == 0)go(0, 0);
      else if (Y < 0)encLeftN(Mo, 5, 1200);
      else encLeftN(Mo, 5, 1200);
      go(0, 0); delay(1000);
      N = 0;
      Step++;
    }
  }
  else {
    flag = 0;
    pid(Mo, Kp);
  }
}
//
//!!!
void Output() {
  d1 = analogRead(A0);
  d2 = analogRead(A1);

  if (d1 > 500 && d2 > 500)
  {
    go(Mo, Mo);
    flag = 0;
  }
  else if (d1 < 500 && d2 > 500)
  {
    encRightN(Mo, 5, 1200);
  }
  else if (d1 > 500 && d2 < 500)
  {
    encLeftN(Mo, 5, 1200);
  }
  else if (d1 < 500 && d2 < 500)
  {
    go(Mo, Mo);
    if (flag == 0) {
      flag = 1;
      pidEncN(Mo, 5, 1000);
      go(0, 0); delay(500);
      //encLeftN(Mo,5,1200);
      go(0, 0); delay(500);
      Step++;
    }

  }
}
//
void Perehod() {
  pidEncN(Mo, 5, 1000);
  go(0, 0); delay(500);
  encLeftN(Mo, 5, 2200);
  go(0, 0); delay(1000);
  Step++;
}
void UlicaOut(int T) {
  d1 = analogRead(A0);
  d2 = analogRead(A1);

  if (d1 < 500 && d2 < 500)
  {
    go(Mo, Mo);
    if (flag == 0) {
      N++;
      flag = 1;
    }
    int Y = XY[T + 1] - 6 - 3;
    if (abs(Y) == N) {
      pidEncN(Mo, 5, 300);
      if (Y == 0)go(0, 0);
      else if (Y < 0)encLeftN(Mo, 5, 1200);
      else encLeftN(Mo, 5, 1200);
      go(0, 0); delay(500);
      N = 0;
      Step++;
    }
  }
  else {
    flag = 0;
    pid(Mo,Kp);
  }
}

void loop() {
  switch (Step)
  {
    case 0:      indicator();      break;

    case 1:      Input();      break;
    case 2:      Ulica(0);      break;
    case 3:      Cross(0);      break;
    case 4:      CrossOut(0);      break;
    case 5:      UlicaOut(0);      break;
    case 6:      Perehod();      break;

    case 7:      Ulica(2);      break;
    case 8:      Cross(2);      break;
    case 9:      CrossOut(2);      break;
    case 10:      UlicaOut(2);      break;
    case 11:      Perehod();      break;

    case 12:      Ulica(4);      break;
    case 13:      Cross(4);      break;
    case 14:      CrossOut(4);      break;
    case 15:      UlicaOut(4);      break;
    case 16:      Output();      break;
  }
}
