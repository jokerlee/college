/*
  Name:15.边插入边排序 
  Copyright: Free 
  Author: Joker Lee 
  Date: 05-12-00 20:50
  Description: 插入一个数找到合适的位置,使数组一直是升序排列 
*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 512
#define N 5

int _findPosition(int*, int, int, int);
int _printArray(int*, int);
int _insertElement(int*, int, int, int, int);

int main(int argc, int* argv[])
{
	int nums[SIZE];
	int i, loc, sizeNow=0;
	
	printf ("请输入%d个整数(空格或回车间隔):", N);
	for (i=0; i<N; i++){
		scanf ("%d", &nums[i]);
		loc = _findPosition(nums, N, i, nums[i]);//调用函数计算插入位置 
		_insertElement(nums, N, sizeNow,loc, nums[i]);//插入当前数字到合适位置 
 		sizeNow ++;//当前数组大小+！ 
	}

      printf ("升序排列结果:");
	_printArray(nums, N);//调用打印函数 
	
	system ("pause");
	return 0;
}

int _findPosition(int* data, int arraySize, int elementSize, int element)
{
	int i;

	if (elementSize==0)
	      return 0;//数组中没有元素，则插入位置为0 
	else if (elementSize < arraySize){//判断数组是否已满 
		for (i=0; i<elementSize; i++){
			if (data[i]<=element){//若待插入元素比第i个元素大 
				if (!(i+1 < elementSize)) return i+1;//若第i个元素是最后一个元素 
				else if (data[i+1]>=element) return i+1;//待插入元素比第i+1个元素小 
	           	}
			else if (i==0 && data[i]>element)
				return 0;//比第一个元素小
		}
	}
}
int _insertElement(int* data, int arraySize, int elementSize, int position, int element)
{
      int i;
	if (!(elementSize<arraySize)) return -2;
	else if (!(position<arraySize)) return -1;
	else{
		for (i=elementSize-1; i>=position; i--)//将插入位置后的元素后移 
	            data[i+1] = data[i]; NULL;
		data[position] = element;//插入元素 
		return 1;
	}
}

int _printArray(int* data, int size)
{
	int i;
	
	for (i=0; i<size; i++){
		printf ("\t%d", data[i]);
	}
      printf ("\n");
}
