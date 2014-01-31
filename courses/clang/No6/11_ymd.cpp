#include <stdio.h>
#include <stdlib.h>

void whatDay(int, int, int);
int isLeap(int);
int main()
{
	int year, month, day;
	
	printf ("please input the date(YYYY-MM-DD)\n");
	scanf ("%d-%d-%d", &year, &month, &day);
	
	whatDay(year, month, day);
	
	system ("pause");
	return 0;
	
}

void whatDay(int yr, int mth, int dy)
{
	int sum=0, mth2, i;
	
	if (isLeap(yr)==1)
		mth2 = 29;
	else 
		mth2 = 28;
	
	for (i=1; i<mth; i++){
		switch (i){
			case 1:case 3:case 5:case 7:case 8:case 10:case 12:
				sum += 31;break;
			case 2:
				sum += mth2;break;
			case 4:case 6:case 9:case 11:
				sum += 30;break;
		}
	}
	sum += dy;
	printf ("the result is %d", sum);
}


int isLeap(int y)
{
	int isLeap=0;
	if (y%4==0 && y%100!=0 ||y%400==0)
		isLeap = 1;
	
	return isLeap;
}
