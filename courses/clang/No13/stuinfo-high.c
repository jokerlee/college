/*
  Name: ѧ����Ϣ��Ѱ����߳ɼ� 
  Copyright: Free 
  Author: Joker Lee 
  Date: 02-01-2007 18:12
  Description: ����n��ѧ����ѧ�úͳɼ���ͳ�Ƴ���߳ɼ���ѧ����������Ϣ��� 
*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

typedef struct stuInfo{//����ѧ����Ϣ�Ľṹ 
	float score;
	char no[10];
	struct stuInfo* nextPtr;
}STUINFO;

typedef int COUNT;

void _readInfo (STUINFO**, int);//����ѧ����Ϣ
void _statHigh (STUINFO*, STUINFO**);//ͳ����߳ɼ�
void _printLinks (STUINFO*);//��ӡ���� 
void _freeLinks (STUINFO**, STUINFO**);//�ͷ��ڴ� 
int main (int argc, char** argv)
{
	int n;
	STUINFO* sAllPtr=NULL;//ȫ��ѧ����Ϣ���� 
	STUINFO* sHighPtr=NULL;//��߳ɼ�ѧ����Ϣ���� 
	
	printf ("������ѧ��������\nN=");
	scanf ("%d", &n);
	
	_readInfo (&sAllPtr, n);//������Ϣ 
	_statHigh (sAllPtr, &sHighPtr);//ͳ�� 
	
	puts ("��߳ɼ���ѧ����Ϣ���£�");
	_printLinks (sHighPtr);
	
	_freeLinks (&sAllPtr, &sHighPtr);
	
	system ("pause");
	return 0;
}

void _readInfo (STUINFO** sPtr, int n)
{
      STUINFO* newPtr=NULL, *currentPtr=*sPtr;
	COUNT i=0;

	printf ("��������%d��ѧ����ѧ�ųɼ���\n", n);
      for (i=0; i<n; i++){//����n��ѧ������Ϣ 
		newPtr = (STUINFO*)malloc(sizeof(STUINFO));
		fflush (stdin);
		scanf ("%s", newPtr->no);//����ѧ�� 
		scanf ("%f", &newPtr->score);//����ɼ� 
		newPtr->nextPtr=NULL;//��ʼ��ָ���� 
		
		if (*sPtr == NULL){//������Ϊ�� 
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

	while (crntAPtr != NULL){//����ԭ�����ҳ���߳ɼ� 
		max = (crntAPtr->score>max)?(crntAPtr->score):max;
		crntAPtr = crntAPtr->nextPtr;
	}

	crntAPtr=sAPtr;
	while (crntAPtr != NULL){//�ٴα���ԭ���� ������߳ɼ��ȶ� 
            //����ǰ�����еĳɼ�������߳ɼ�,���������߳ɼ����� 
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
	while (sPtr != NULL){//��������ӡ 
		printf ("ѧ�ţ�%-8s�ɼ���%-4.1f\n", sPtr->no, sPtr->score);
		sPtr = sPtr->nextPtr;
	}
}

void _freeLinks (STUINFO** sPtr1, STUINFO** sPtr2)
{
      STUINFO* tmpPtr=NULL, *crntPtr=NULL;
      
	crntPtr = *sPtr1;
	while (crntPtr != NULL){//�ͷ�ȫ����Ϣ���� 
		tmpPtr = crntPtr;
		free (tmpPtr);
		crntPtr = crntPtr->nextPtr;
	}

	crntPtr = *sPtr2;
	while (crntPtr != NULL){//�ͷ���߳ɼ����� 
		tmpPtr = crntPtr;
		free (tmpPtr);
		crntPtr = crntPtr->nextPtr;
	}
}
