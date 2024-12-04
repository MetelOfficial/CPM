
task main()
{
	clearTimer(T1);
	int t=0;
	while(time1[T1] < 5000){
		if(time1[T1]>5500){t=0;}
			t++;
	}
	displayTextLine(1, "%d", t);
	setLEDColor(ledOrange);
	waitForButtonPress();


}
