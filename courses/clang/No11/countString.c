#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 1000
void _statistics(char*, int*, int*, int*, int*);
int main(int argc, char* argv[])
{
	char string[SIZE];
	int ltrCount=0, numCount=0, spCount=0, othrCount=0;
	
	printf ("input string:\n");
	gets(string);
	printf ("String: %s\n", string);
	_statistics(string, &ltrCount, &numCount, &spCount, &othrCount);
	
	printf ("Letter£º%d, digit£º%d, space£º%d, others£º%d\n", ltrCount, numCount, spCount, othrCount);
	system("pause");
	return 0;
}

void _statistics(char* str, int* lCount, int* nCount, int* sCount, int* oCount)
{
	int i=0, len;
	len = strlen(str);
	
	for (i=0; i<len; i++){
		if (isdigit(str[i]))
			(*nCount)++;
		else if (isalpha(str[i]))
		      (*lCount)++;
		else if (str[i]==32)
			(*sCount)++;
  		else if (ispunct(str[i]))
  		      (*oCount)++;
	}
}
