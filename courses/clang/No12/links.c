#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#define SIZE 101

#define ISVALID(x) (x>=0&&x<=9)
#define ISEQUAL(x,y) (x.num1 == y.num1 && x. num2 == y.num2)
#define ISRESERVE(x,y) (x.num1 == y.num2 && x. num2 == y.num1)

struct link{
	int num1;
	int num2;
	int isCount;
};
typedef struct link LINK;
typedef int count;

int _inputNums (int [], int);
void _creatLinks (LINK [], int [], int);
void _statistic (LINK [], int);

int main (int argc, char* argv[])
{
	int n=0, originNums[SIZE]={0,1,5,9,8,7,2,2,2,3,2,7,8,7,8,7,9,6,5,9};
	LINK startPtr[SIZE];
	
	printf ("请输入元素个数:\nN=");
	scanf ("%d", &n);
	
	if (_inputNums (originNums, n)==0){
		_creatLinks (startPtr, originNums, n);
		_statistic (startPtr, n);
	}
	
	system ("pause");
	return 0;
}
int _inputNums (int* nums, int n)
{
	count i=0;

	printf ("请输入这%d个元素（0~9）：\n", n);
	fflush (stdin);
	for (i=0; i<n; i++){
		scanf ("%d", &nums[i]);
		if (!ISVALID(nums[i])){
			printf ("输入不合法,请输入合法的数字。\n");
			return -1;
		}
	}
	return 0;
}

void _creatLinks (LINK sPtr[], int nums[], int n)
{
	count i=0;

	for (i=0; i<n-1; i++){
		sPtr[i].num1 = nums[i];
		sPtr[i].num2 = nums[i+1];
		sPtr[i].isCount=0;
	}
}

void _statistic (LINK sPtr[], int n)
{
	count i=0, j=0;
	int n1=0, n2=0;
	
	puts ("链环数字对及其出现的次数为：");
	for (i=0; i<n-1; i++){
            n1=1, n2=0;
		for (j=i+1; j<n-1; j++){
			if (sPtr[j].isCount==0){
				if (ISEQUAL (sPtr[i], sPtr[j]) && sPtr[i].num1!=sPtr[i].num2){
					sPtr[j].isCount = 1;
					n1++;
				}
				else if (ISRESERVE (sPtr[i], sPtr[j])){
                   	     	sPtr[j].isCount = 1;
					n2++;
				}
			}
		}
		if (n1>0 && n2>0){
			if (sPtr[i].num1==sPtr[i].num2){
				printf ("(%d,%d)=%d\n", sPtr[i].num1, sPtr[i].num2, n1+n2);}
			else{
				printf ("(%d,%d)=%d   ", sPtr[i].num1, sPtr[i].num2, n1);
                        printf ("(%d,%d)=%d   \n", sPtr[i].num2, sPtr[i].num1, n2);}
		}
	}
}
