#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1000

void _deletElement(char*, int);
void _insertStr(char*, char*, int);
char* _replaceAll(char*, char*, char*);
int main(int argc, char* argv[])
{
	char string[SIZE], origin[SIZE], replace[SIZE];
	char* opedStr=NULL;
	
	printf ("ÇëÊäÈëÔ´×Ö·û´®£º");
	gets(string);
	printf ("ÇëÊäÈëÒª±»Ìæ»»µÄ×Ö·û´®£º");
	gets(origin);
      printf ("ÇëÊäÈëÌæ»»Ä¿±ê×Ö·û´®£º");
      gets(replace);
      
      opedStr = _replaceAll(string, origin, replace);
      printf ("Ìæ»»ºóµÄ×Ö·û´®£º%s\n", opedStr);
      
      system("pause");
      return 0;
}

char* _replaceAll(char* str1, char* str2, char* str3)
{
	int len=0, loc, i;
	static char newStr[SIZE];
	char* fistltrPtr=NULL;

	len=strlen(str2);
	strcpy(newStr, str1);
      fistltrPtr = strstr(newStr, str2);

 	while (fistltrPtr){
		//loc = fistltrPtr-newStr;
		loc = newStr-fistltrPtr;
		for (i=0; i<len; i++)
		      _deletElement(newStr, loc);NULL;
		_insertStr(str3, newStr, loc);
		fistltrPtr = strstr(newStr, str2);
	}

	return newStr;
}

void _deletElement(char *str, int loc)
{
	int i,len=strlen(str);
	
	for (i=loc; i<=len-2; i++){
		str[i]=str[i+1];
	}
	str[i]=0;
	//debug
	//printf ("É¾³ıºó£º%s\n",str);
}

void _insertStr(char* inStr, char *opStr, int loc)
{
      int i, n, len1=strlen(inStr), len2=strlen(opStr);

	for (i=len2-1; i>=loc; i--){
           	opStr[i+len1] = opStr[i];
	}
	opStr[len2+len1]=0;
	for (i=0; i<len1; i++)
		 opStr[loc+i] = inStr[i]; NULL;

}
