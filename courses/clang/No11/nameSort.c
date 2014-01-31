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
	
	printf ("请输入要排序的人数：\n");
	scanf ("%d", &size);
	
	if (names = _inputName (size)){//判断是否成功分配内存
		_sort (names, size);
		_printName (names, size);
		_free (names, size);
	}
	else
	      printf ("无法获得内存\n");
	      
	system ("pause");
	return 0;
}

char** _inputName (int size)
{
	char** inNames;
	counter i=0;
	
	inNames = (char**) malloc(size*sizeof(char*));
	if (inNames){
		printf ("请输入%d个学生的名字，每输入一个用回车结束:\n", size);
		fflush (stdin);
		for (i=0; i<size; i++){
			*(inNames+i) = (char*) malloc(SIZE*sizeof(char));
			if (*(inNames+i)==NULL){//判断是否成功获得内存
				printf ("无法获得内存");
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

	printf("从小到大，这%d个学生的姓名为：\n", size);
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
