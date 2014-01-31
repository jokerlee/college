#include <stdio.h>
#include <stdlib.h>
#define SIZE 512

int _isLetter(char);
int main(int argc, char* argv[])
{
	int i=0, isLtr, maxLoc=0, firstLtr=0, len=0, maxLen=0;
	char str[SIZE];
	
	printf ("Please input the string('#'to end):\n");

	fflush(stdin);
	gets(str);

	for (i=0; str[i]!='#'; i++){
  		if (!_isLetter(str[i]) && str[i+1]!='#'){
			if (len>maxLen){
				maxLen = len;
				maxLoc = firstLtr;
			}
			firstLtr=i+1;
			len=0;
		}
		else if (str[i+1]=='#' && len+1>maxLen){
			maxLen = len+1;
			maxLoc = firstLtr;
		}
		else len++;
	}

	printf ("The longest word is:");
	for (i=0; i<maxLen; i++)
		printf ("%c", str[maxLoc+i]); NULL;

	system ("pause");
	return 0;
}
int _isLetter(char a)
{
	if ((a>='A'&& a<='Z')||(a>='a' && a<='z'))
	      return 1;
	else
	      return 0;
}
