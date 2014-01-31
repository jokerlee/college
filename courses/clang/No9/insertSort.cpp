/*
  Name: 29.插入排序 
  Copyright: Free 
  Author: Joker Lee 
  Date: 05-12-00 20:53
  Description: 插入排序法实现升序排序 
*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 512

int _insertSort(int*, int);
int main(int argc, int* argv[])
{
	int origin[SIZE]= {0};
	int i,validN;
	
	printf ("请输入排序前数列，以-1结束：\n");
	
	for (i=0; origin[i-1] != -1; i++){//读入原始数组 
		scanf ("%d", &origin[i]);
	}

	validN = i-1;//有效长度 
	_insertSort(origin, validN);//插入法排序 

	for (i=0; i<validN; i++)//打印 
		printf ("%d ", origin[i]);

	system("pause");
	return 0;
}

int _insertSort(int* nums, int size)
{
	int i, j, tmp;
	
	for (i=1; i<size; i++){//每次循环插入一个数 
		for (j=i; j>0; j--){//对插入的数在区域内进行泡沫排序 
			if (nums[j]<nums[j-1]){
			      tmp = nums[j-1];
			      nums[j-1] = nums[j];
			      nums[j] = tmp;
			}
		}
	}
}
