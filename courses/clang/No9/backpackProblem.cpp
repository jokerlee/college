//±³°üÎÊÌâ 

#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int _backpack(const int*, int, int, int);
int main()
{
	int store[SIZE] = {2,1,6,9,8,36,27,25,12,7};
	int s;
	
	scanf ("%d", &s);
	_backpack(store, s, 0, SIZE-1);
	
	system ("pause");
	return 0;
}

int _backpack(const int *st, int maxG, int from, int to)
{
	int sumG=0;
	int i, j, k;
		
	for (i=from; i<=to; i++){
		if (sumG+st[i] < maxG)
			_backpack(st, maxG-st[i], from+1, to);NULL;
			printf ("%d ", st[i]);
		if (sumG+st[i] == maxG)
			printf ("%d ", st[i]);			
			return 0;
		if (i==to &&sumG+st[i] != maxG)
			break;
	}

}
