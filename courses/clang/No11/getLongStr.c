#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 100
typedef int counter;

void _getLongStr (char*);

int main (int argc, char** argv)
{
	char string[SIZE];

	printf ("请输入一个英文句子(以句号.作为结束符)");
	gets(string);
	_getLongStr (string);

	system ("pause");
	return 0;
}

void _getLongStr (char* str)
{
	int length=strlen(str), len=0, maxLen=0, firstLtr;
	char** longStrs;
	counter i=0, j=0, k=0;
	
	longStrs = (char**)malloc (SIZE*sizeof(char*));
      for (i=0; i<length; i++){
  		if (!isalpha(str[i])){
			if (len>=maxLen){
				*(longStrs+j) = (char*) malloc (SIZE*sizeof(char));
				for (k=0; k<len; k++){
				      *(*(longStrs+j)+k) = str[firstLtr+k];}
				maxLen = len;
				j++;
			}
			firstLtr=i+1;
			len=0;
		}
		else len++;
}
	for (i=0; i<j; i++){
		printf ("%s\n", (longStrs+i));}

}
