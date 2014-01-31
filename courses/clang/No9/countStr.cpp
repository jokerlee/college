#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 512

int _countStr(const char*, int, const char*, int);
int main(int argc, int* argv[])
{
	char mainStr[SIZE], subStr[SIZE];
	int i, times;
	
	printf ("Ö÷´®£º");
	gets(mainStr);
	printf ("×Ó´®£º");
	gets(subStr);
	
	times = _countStr(mainStr, strlen(mainStr), subStr, strlen(subStr));
	
	printf ("Times= %d\n", times);
	
	system("pause");
	return 0;
}

int _countStr(const char* mainS, int lenMain, const char* subS, int lenSub)
{
	int i, freq;
	
	for (i=0, freq=0; i<lenMain; i++){
		if (mainS[i]==subS[0] && mainS[i+1]==subS[1]){
			freq ++;
			i++;
		}
	}
	return freq;
}
