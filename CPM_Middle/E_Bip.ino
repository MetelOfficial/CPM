void Bip(int a){
  switch(a){
    case 0:digitalWrite(11, 1);
           delay(20);
           digitalWrite(11, 0);
           delay(100);
     break;
    case 1:digitalWrite(11, 1);
           delay(300);
           digitalWrite(11, 0);
           delay(100);
     break;
    case 2:digitalWrite(11, 1);
           delay(150);
           digitalWrite(11, 0);
           delay(100);
           digitalWrite(11, 1);
           delay(150);
           digitalWrite(11, 0);
           delay(100);
     break; 
    case 3:digitalWrite(11, 1);
           delay(1000);
           digitalWrite(11, 0);
           delay(1000);
           digitalWrite(11, 1);
           delay(1000);
           digitalWrite(11, 0);
           delay(1000);
     break; 
  }
}