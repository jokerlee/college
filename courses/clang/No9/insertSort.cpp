/*
  Name: 29.�������� 
  Copyright: Free 
  Author: Joker Lee 
  Date: 05-12-00 20:53
  Description: ��������ʵ���������� 
*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 512

int _insertSort(int*, int);
int main(int argc, int* argv[])
{
	int origin[SIZE]= {0};
	int i,validN;
	
	printf ("����������ǰ���У���-1������\n");
	
	for (i=0; origin[i-1] != -1; i++){//����ԭʼ���� 
		scanf ("%d", &origin[i]);
	}

	validN = i-1;//��Ч���� 
	_insertSort(origin, validN);//���뷨���� 

	for (i=0; i<validN; i++)//��ӡ 
		printf ("%d ", origin[i]);

	system("pause");
	return 0;
}

int _insertSort(int* nums, int size)
{
	int i, j, tmp;
	
	for (i=1; i<size; i++){//ÿ��ѭ������һ���� 
		for (j=i; j>0; j--){//�Բ�������������ڽ�����ĭ���� 
			if (nums[j]<nums[j-1]){
			      tmp = nums[j-1];
			      nums[j-1] = nums[j];
			      nums[j] = tmp;
			}
		}
	}
}
