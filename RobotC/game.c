
task main()
{
	displayBigTextLine(6, "    Wait...");
	setLEDColor(ledGreen);
	int t = random[10000];
	wait1Msec(t);
	clearTimer(T1);
	eraseDisplay();
	displayBigTextLine(6, "    Press!");
	setLEDColor(ledRed);
	t = time1(T1);
	while(getButtonPress(buttonLeft)!=1&&getButtonPress(buttonRight)!=1){
		t = time1(T1);
		if (getButtonPress(buttonLeft)){setLEDColor(ledRed);eraseDisplay();displayTextLine(7, "Left win in %d", t);}
		if (getButtonPress(buttonRight)){setLEDColor(ledRed);eraseDisplay();displayTextLine(7, "Right win in %d", t);}
	}
	while(1){}


}
