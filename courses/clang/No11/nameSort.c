#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define SIZE 50

typedef int counter;

char** _inputName (int);
void _sort (char* [], int);
void _printName (char* [], int);
void _free (char* [], int);

int main (int argc, char** argv)
{
	int size=0;
	char** names;
	
	printf ("������Ҫ�����������\n");
	scanf ("%d", &size);
	
	if (names = _inputName (size)){//�ж��Ƿ�ɹ������ڴ�
		_sort (names, size);
		_printName (names, size);
		_free (names, size);
	}
	else
	      printf ("�޷�����ڴ�\n");
	      
	system ("pause");
	return 0;
}

char** _inputName (int size)
{
	char** inNames;
	counter i=0;
	
	inNames = (char**) malloc(size*sizeof(char*));
	if (inNames){
		printf ("������%d��ѧ�������֣�ÿ����һ���ûس�����:\n", size);
		fflush (stdin);
		for (i=0; i<size; i++){
			*(inNames+i) = (char*) malloc(SIZE*sizeof(char));
			if (*(inNames+i)==NULL){//�ж��Ƿ�ɹ�����ڴ�
				printf ("�޷�����ڴ�");
				break;
			}
			gets (*(inNames+i));
		}
	}
	return inNames;
}
void _sort (char* names[], int size)
{
	counter i=0, j=0;
	char* tmpPtr;

	for (i=1; i<size; i++){
		for (j=0; j<size-1; j++){
			if (strncmp(names[j], names[j+1], SIZE)>0){
				tmpPtr = names[j];
				names[j] = names[j+1];
				names[j+1] = tmpPtr;
			}
		}
	}
}

void _printName (char* names[], int size)
{
	counter i=0;

	printf("��С������%d��ѧ��������Ϊ��\n", size);
	for (i=0; i<size; i++){
		printf ("%s\n", names[i]);
	}
}

void _free (char** names, int size)
{
	counter i=0;
	for (i=0; i<size; i++){
		free (names+i);}
	free (names);
}
