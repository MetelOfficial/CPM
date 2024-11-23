void pid(int V, float K) {
  int E = analogRead(A2) - analogRead(A0);       //ПО БЕЛОМУ
  int d1 = V + K * E; d1 = constrain(d1, -255, 255);
  int d2 = V - K * E; d2 = constrain(d2, -255, 255);
  go(d1, d2);
}