task main()
{
	int m = 1;
	int h = 0;
	while(1){
  displayBigTextLine(1, "%d", m);
  displayBigTextLine(5, "%d", h);
  m+=1;
  wait1Msec(200);


  if(m>=60){
  m-=60;
  h++;
}
}

}
