void go(int S2, int S1) {
  if (S1 > 0)digitalWrite(2, 1); else digitalWrite(2, 0);
  if (S2 > 0)digitalWrite(4, 1); else digitalWrite(4, 0);
  analogWrite(3, abs(S1)); analogWrite(5, abs(S2));
} 