void pid(int V, float K) {
  int E = dat(A2) - dat(A7);       
  int d1 = V + K * E; d1 = constrain(d1, -255, 250);
  int d2 = V - K * E; d2 = constrain(d2, -255, 250);
  go(d1, d2);
}