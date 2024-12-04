task main()
{
	while(1){
		if(getButtonPress(buttonEnter)){setMotorTarget(MotorA, 0, 100);waitUntilMotorStop(MotorA);delay(200);}
		if(getButtonPress(buttonLeft)){setMotorTarget(MotorA, 100, 100);waitUntilMotorStop(MotorA);delay(200);}
		if(getButtonPress(buttonRight)){setMotorTarget(MotorA, 200, 100);waitUntilMotorStop(MotorA);delay(200);}
	setMotorTarget(MotorA, 50, 100);
	waitUntilMotorStop(MotorA);
	wait1Msec(2000);
	setMotorTarget(MotorA, 0, 100);
	waitUntilMotorStop(MotorA);
	wait1Msec(2000);
}
}
