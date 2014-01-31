#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000

int* _inputScore(int);
void _sort(int*, int);
int _printScore(int*, int);

int main(int argc, char* argv[])
{
	int* array=NULL;
	int n=0;
	
	puts ("请输入学生人数：");
	scanf ("%d", &n);

	array = _inputScore(n);
	_sort(array, n);
	_printScore(array, n);
	
	free (array);
	system("pause");
	return 0;

}

int* _inputScore(int size)
{
	int i=0;
	int* ay = NULL;
	
	ay = malloc(size*sizeof(int));
	
	printf ("请输入这%d个学生的成绩：\n", size);
	for (i=0; i<size; i++){
		scanf ("%d", ay+i);}

	return ay;
}

void _sort(int* ay, int size)
{
	int i=0, j=0, tmp;
	for (i=1; i<size; i++){
            for (j=0; j<size-1; j++){
                  if (*(ay+j) < *(ay+j+1)){
                        tmp = *(ay+j);
                        *(ay+j) = *(ay+j+1);
                        *(ay+j+1) = tmp;
                  }
		}
	}
}

int _printScore(int* ay, int size)
{
	int i=0;
	
	printf ("从高到低，这%d个学生的成绩为：\n", size);
	for (i=0; i<size; i++){
		printf ("%-4d", *(ay+i));}
}
