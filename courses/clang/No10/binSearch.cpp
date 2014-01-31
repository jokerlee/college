
#include "stdio.h"
#include "stdlib.h"
#define N 5

void _inputArray(int[], int);
void _printArray(const int[], int);
void _selectionSort(int[], int);
int _minElement(const int[], int);
int _binSearch(const int, const int*, int, int);

int main(int argc, char* argv[])
{
	int array[N], x, result;

	printf ("请输入%d个整数：\n", N);
	_inputArray(array, N);

	printf ("升序排列前的数组是：\n");
	_printArray(array, N);

	_selectionSort(array, N);
	printf ("\n升序排列后的数组是：\n");
	_printArray(array, N);

	printf ("\n请输入要查找的整数：\n");
	scanf ("%d$", &x);

	result = _binSearch(x, array, 0, N);
	if (result==-1)
		printf ("%d不在数组中。\n", x);
	else
		printf ("%d所在元素的下标是%d\n", x, result);

	system ("pause");
	return 0;
}

void _inputArray(int inArray[], int inN)
{
	int i;
	for (i=0; i<inN; i++)
		scanf ("%d", &inArray[i]); NULL;
}

void _printArray(const int prtArray[], int prtN)
{
	int i;
	for (i=0; i<prtN; i++)
		printf ("%-4d", prtArray[i]);
}

int _minElement(const int minArray[], int minN)
{
      int i, minE=0;

      for (i=0; i<minN; i++){
            if (minArray[i] < minArray[minE])
                  minE = i;
      }
      return minE;
}

void _selectionSort(int* seArray, int seN)
{
	int min, tmp;

	if (seN>1){
		min = _minElement(seArray, seN);
		if (min != 0){
			tmp = seArray[0];
			seArray[0] = seArray[min];
			seArray[min] = tmp;
		}
	      return _selectionSort(seArray+1, seN-1);
	}
}

int _binSearch(const int binX, const int binArray[], int binFrom, int binTo)
{
	int mid;

	mid = (binFrom+binTo)/2;
	if (binFrom<binTo && binX!=binArray[mid]){
		if (binX < binArray[mid])
			return _binSearch(binX, binArray, binFrom, mid-1);
		else
			return _binSearch(binX, binArray, mid+1, binTo);
	}
	if (binX == binArray[mid])	return mid;
	else return -1;
}
