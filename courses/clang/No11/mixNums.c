#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 50

typedef int counter;
int _find (char [], int, int [], int, int*, int*);

int main (int argc, char** argv)
{
	int len=0, array[N]={0}, max, min, num;
	char originStr[N];
	counter i=0;
	
	
	printf ("�������ַ�����\n");
	gets (originStr);
	len = strlen (originStr);
	num = _find (originStr, len, array, N, &max, &min);
	
	printf ("�ַ������������ֺϲ���õ��������У�\n");
	for (i=0; i<num; i++){
		printf ("%-5d", array[i]);}

	printf ("\n���������ֵ�ǣ�%d", max);
	printf ("\n��������Сֵ�ǣ�%d\n", min);
	
	system ("pause");
	return 0;
}

int _find (char str[], int eleSize, int array[], int arraySize, int* maxPtr, int* minPtr)
{
	counter i=0, j=0;
	int isContinued = 0;
	
	for (i=0; i<=eleSize; i++){
		if (isdigit(str[i])){
			array[j]=array[j]*10+(str[i]-'0');
			isContinued = 1;
                  if (j==0){
				*maxPtr=array[j];
				*minPtr=array[j];
			}
		}
		else if (!isdigit(str[i]) && (isContinued == 1)){
			isContinued = 0;
			if (array[j]>*maxPtr) *maxPtr = array[j];
			if (array[j]<*minPtr) *minPtr = array[j];
			j++;
		}
	}

	return j;
}
