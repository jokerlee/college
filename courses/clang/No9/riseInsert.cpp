/*
  Name:15.�߲�������� 
  Copyright: Free 
  Author: Joker Lee 
  Date: 05-12-00 20:50
  Description: ����һ�����ҵ����ʵ�λ��,ʹ����һֱ���������� 
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
	
	printf ("������%d������(�ո��س����):", N);
	for (i=0; i<N; i++){
		scanf ("%d", &nums[i]);
		loc = _findPosition(nums, N, i, nums[i]);//���ú����������λ�� 
		_insertElement(nums, N, sizeNow,loc, nums[i]);//���뵱ǰ���ֵ�����λ�� 
 		sizeNow ++;//��ǰ�����С+�� 
	}

      printf ("�������н��:");
	_printArray(nums, N);//���ô�ӡ���� 
	
	system ("pause");
	return 0;
}

int _findPosition(int* data, int arraySize, int elementSize, int element)
{
	int i;

	if (elementSize==0)
	      return 0;//������û��Ԫ�أ������λ��Ϊ0 
	else if (elementSize < arraySize){//�ж������Ƿ����� 
		for (i=0; i<elementSize; i++){
			if (data[i]<=element){//��������Ԫ�رȵ�i��Ԫ�ش� 
				if (!(i+1 < elementSize)) return i+1;//����i��Ԫ�������һ��Ԫ�� 
				else if (data[i+1]>=element) return i+1;//������Ԫ�رȵ�i+1��Ԫ��С 
	           	}
			else if (i==0 && data[i]>element)
				return 0;//�ȵ�һ��Ԫ��С
		}
	}
}
int _insertElement(int* data, int arraySize, int elementSize, int position, int element)
{
      int i;
	if (!(elementSize<arraySize)) return -2;
	else if (!(position<arraySize)) return -1;
	else{
		for (i=elementSize-1; i>=position; i--)//������λ�ú��Ԫ�غ��� 
	            data[i+1] = data[i]; NULL;
		data[position] = element;//����Ԫ�� 
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
