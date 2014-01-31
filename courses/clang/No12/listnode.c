#include "stdio.h"
#include "stdlib.h"
#define SIZE 50

struct stuInfo{
	char name[SIZE];
	int no;
	int score;
	struct stuInfo* nextPtr;
};

typedef struct stuInfo INFO;
typedef struct stuInfo* INFOPTR;
typedef int count;

void _creatLinks (INFOPTR*);
void _printAndStat (INFOPTR*);
void _freeMem (INFOPTR*);
int main (int argc, char* argv[])
{
      INFOPTR startPtr=NULL;

	_creatLinks (&startPtr);
	_printAndStat (&startPtr);
	//_freeMem(&startPtr);

	system ("pause");
	return 0;
}

void _creatLinks (INFOPTR *sPtr)
{
      INFOPTR newPtr=NULL, currentPtr=NULL, lastPtr=NULL;
      newPtr = malloc (sizeof(INFO));

	puts ("请输入学生信息（姓名,学号,成绩）：");
	if (newPtr != NULL)
		printf ("姓名：");
		gets (newPtr->name);
	while (newPtr->name[0] != '#' && newPtr != NULL){
            printf ("学号：");
		scanf ("%d", &newPtr->no);
		printf ("成绩：");
		scanf ("%d", &newPtr->score);
		if (*sPtr == NULL){
			*sPtr = newPtr;}
		else{
			lastPtr->nextPtr = newPtr;
			newPtr->nextPtr = NULL;}
		lastPtr = newPtr;
      	newPtr = malloc (sizeof(INFO));
		fflush (stdin);
		printf ("姓名：");
		gets (newPtr->name);
	}
}

void _printAndStat (INFOPTR *sPtr)
{
      INFOPTR currentPtr=*sPtr;
      int freq[10]={0};
      count i=0;

	printf ("\n全部学生信息：\n");
	while (currentPtr != NULL){
		printf ("学号：%-4d姓名：%-10s成绩：%-4d\n", currentPtr->no, currentPtr->name, currentPtr->score);
		if (currentPtr->score<60)
		      ++freq[9];
		else if (currentPtr->score <= 100 && currentPtr->score >=60)
			++freq[10-(currentPtr->score)/10];
		currentPtr = currentPtr->nextPtr;
	}

 	printf ("\n成绩统计：\n");
	for (i=0; i<4; i++)
		if (freq[i]!=0)
			printf ("%d0~%d0分有%d人\n", 10-i, 11-i,freq[i]);
	if (freq[9]!=0)
		printf ("60分以下有%d人\n", freq[9]);
}

void _freeMem (INFOPTR *sPtr)
{
      INFOPTR currentPtr=*sPtr, tempPtr=NULL;

	while (currentPtr == NULL){
		tempPtr = currentPtr;
		free (tempPtr);
		currentPtr = currentPtr->nextPtr;
	}
}
