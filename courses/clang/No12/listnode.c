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

	puts ("������ѧ����Ϣ������,ѧ��,�ɼ�����");
	if (newPtr != NULL)
		printf ("������");
		gets (newPtr->name);
	while (newPtr->name[0] != '#' && newPtr != NULL){
            printf ("ѧ�ţ�");
		scanf ("%d", &newPtr->no);
		printf ("�ɼ���");
		scanf ("%d", &newPtr->score);
		if (*sPtr == NULL){
			*sPtr = newPtr;}
		else{
			lastPtr->nextPtr = newPtr;
			newPtr->nextPtr = NULL;}
		lastPtr = newPtr;
      	newPtr = malloc (sizeof(INFO));
		fflush (stdin);
		printf ("������");
		gets (newPtr->name);
	}
}

void _printAndStat (INFOPTR *sPtr)
{
      INFOPTR currentPtr=*sPtr;
      int freq[10]={0};
      count i=0;

	printf ("\nȫ��ѧ����Ϣ��\n");
	while (currentPtr != NULL){
		printf ("ѧ�ţ�%-4d������%-10s�ɼ���%-4d\n", currentPtr->no, currentPtr->name, currentPtr->score);
		if (currentPtr->score<60)
		      ++freq[9];
		else if (currentPtr->score <= 100 && currentPtr->score >=60)
			++freq[10-(currentPtr->score)/10];
		currentPtr = currentPtr->nextPtr;
	}

 	printf ("\n�ɼ�ͳ�ƣ�\n");
	for (i=0; i<4; i++)
		if (freq[i]!=0)
			printf ("%d0~%d0����%d��\n", 10-i, 11-i,freq[i]);
	if (freq[9]!=0)
		printf ("60��������%d��\n", freq[9]);
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
