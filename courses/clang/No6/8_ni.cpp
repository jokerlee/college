#include <stdio.h>
#include <stdlib.h>

int GetDigit(int);
int GetReverse(int);
int main()
{
	int num;
	
	printf ("please input an integer:\n");
	scanf ("%d", &num);
	
	printf ("It has %d digit.  " ,GetDigit(num));
	printf ("The reverse number is %d", GetReverse(num));
	
	system ("pause");
	return 0;			
}

int GetDigit(int n)
{
	int k;
	for (k=0; n>0; k++){
		n /= 10;
	}
	
	return k;
}

int GetReverse(int n)
{
	int rev=0;
	while (n>0){
		rev = rev*10 + n%10;
		n /= 10;
	}
	
	return rev;
}
