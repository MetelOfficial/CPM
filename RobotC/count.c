
task main()
{
	int c=0;
	bool flag=0;
	clearTimer(T1);
	while(time1[T1]<10000){
		if(getButtonPress(buttonLeft)==1 && flag == 0){
			c+=1;
			flag=1;
		}
		if(getButtonPress(buttonLeft)==0){flag=0;}
		displayTextLine(7, "%d", c);
	}


}
