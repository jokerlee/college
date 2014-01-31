/*
  Name: 学生信息及寻找最高成绩 
  Copyright: Free 
  Author: Joker Lee 
  Date: 02-01-2007 18:12
  Description: 读入n个学生的学好和成绩，统计出最高成绩的学生，将其信息打出 
*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

typedef struct stuInfo{//储存学生信息的结构 
	float score;
	char no[10];
	struct stuInfo* nextPtr;
}STUINFO;

typedef int COUNT;

void _readInfo (STUINFO**, int);//读入学生信息
void _statHigh (STUINFO*, STUINFO**);//统计最高成绩
void _printLinks (STUINFO*);//打印链表 
void _freeLinks (STUINFO**, STUINFO**);//释放内存 
int main (int argc, char** argv)
{
	int n;
	STUINFO* sAllPtr=NULL;//全部学生信息链表 
	STUINFO* sHighPtr=NULL;//最高成绩学生信息链表 
	
	printf ("请输入学生人数：\nN=");
	scanf ("%d", &n);
	
	_readInfo (&sAllPtr, n);//读入信息 
	_statHigh (sAllPtr, &sHighPtr);//统计 
	
	puts ("最高成绩的学生信息如下：");
	_printLinks (sHighPtr);
	
	_freeLinks (&sAllPtr, &sHighPtr);
	
	system ("pause");
	return 0;
}

void _readInfo (STUINFO** sPtr, int n)
{
      STUINFO* newPtr=NULL, *currentPtr=*sPtr;
	COUNT i=0;

	printf ("请输入这%d个学生的学号成绩：\n", n);
      for (i=0; i<n; i++){//读入n个学生的信息 
		newPtr = (STUINFO*)malloc(sizeof(STUINFO));
		fflush (stdin);
		scanf ("%s", newPtr->no);//读入学号 
		scanf ("%f", &newPtr->score);//读入成绩 
		newPtr->nextPtr=NULL;//初始化指针域 
		
		if (*sPtr == NULL){//若链表为空 
			*sPtr = newPtr;}
		else{
			currentPtr->nextPtr = newPtr;}
		currentPtr = newPtr;
	}
}

void _statHigh (STUINFO* sAPtr, STUINFO** sHPtr)
{
	float max=0;
	STUINFO* crntAPtr=sAPtr, *crntHPtr=*sHPtr, *newPtr=NULL;

	while (crntAPtr != NULL){//遍历原链表，找出最高成绩 
		max = (crntAPtr->score>max)?(crntAPtr->score):max;
		crntAPtr = crntAPtr->nextPtr;
	}

	crntAPtr=sAPtr;
	while (crntAPtr != NULL){//再次遍历原链表， 并与最高成绩比对 
            //若当前链表中的成绩等于最高成绩,将其加入最高成绩链表 
		 if (crntAPtr->score==max){
                  newPtr = (STUINFO*)malloc(sizeof(STUINFO));
                  *newPtr = *crntAPtr;
                  newPtr->nextPtr = NULL;
                  
			if (*sHPtr == NULL){
			      *sHPtr = newPtr;}
			else{
				crntHPtr->nextPtr = newPtr;}
			crntHPtr = newPtr;
		}
      	crntAPtr = crntAPtr->nextPtr;
	}
}

void _printLinks (STUINFO* sPtr)
{
	while (sPtr != NULL){//遍历并打印 
		printf ("学号：%-8s成绩：%-4.1f\n", sPtr->no, sPtr->score);
		sPtr = sPtr->nextPtr;
	}
}

void _freeLinks (STUINFO** sPtr1, STUINFO** sPtr2)
{
      STUINFO* tmpPtr=NULL, *crntPtr=NULL;
      
	crntPtr = *sPtr1;
	while (crntPtr != NULL){//释放全部信息连标 
		tmpPtr = crntPtr;
		free (tmpPtr);
		crntPtr = crntPtr->nextPtr;
	}

	crntPtr = *sPtr2;
	while (crntPtr != NULL){//释放最高成绩链表 
		tmpPtr = crntPtr;
		free (tmpPtr);
		crntPtr = crntPtr->nextPtr;
	}
}
