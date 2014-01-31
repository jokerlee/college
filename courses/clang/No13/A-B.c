/*
  Name: ����Ĳ 
  Copyright: Free 
  Author: Joker Lee 
  Date: 02-01-2007 18:22 
  Description: �󼯺�A�뼯��B�Ĳ 
*/
#include "stdio.h"
#include "stdlib.h"

typedef struct listnode{//���崢�����ּ��ϵ����� 
      int num;
      struct listnode* nextPtr;
}LISTNODE;

typedef int COUNT;
typedef int FLAG;

void _inputNums (LISTNODE**);//����һ������ 
void _differAB (LISTNODE*, LISTNODE*, LISTNODE**);//Ѱ��AB�Ĳ 
void _printList (LISTNODE*);//��ӡ���� 
int _search (int, LISTNODE*);//������������ĳ��Ԫ�� 

int main (int argc, char** argv)
{
	LISTNODE *listA=NULL, *listB=NULL, *listAB=NULL;
	
	puts ("������A��������ݣ�");
	_inputNums (&listA);
	puts ("������B��������ݣ�");
	_inputNums (&listB);
	
	_differAB (listA, listB, &listAB);

	puts ("A-B������Ϊ��");
	if (listAB == NULL){
            puts ("�ռ�.");}
      else{
            _printList (listAB);}
	
	system ("pause");
	return 0;
}

void _inputNums (LISTNODE** sPtr)
{
      LISTNODE* newPtr=NULL, *crntPtr=*sPtr;
	COUNT i=0;
	char interval=0;

      while (interval != '\n'){//�����ֺ�������س���������� 
		newPtr = (LISTNODE*)malloc(sizeof(LISTNODE));//�½�һ������ 
		scanf ("%d", &newPtr->num);
		newPtr->nextPtr=NULL;

		if (*sPtr == NULL){//��Ϊ��ָ�� 
			*sPtr = newPtr;}
		else{
			crntPtr->nextPtr = newPtr;}
		crntPtr = newPtr;//���µ�ǰָ�� 
		interval = getchar();//�������ַ� 
	}
}

void _differAB (LISTNODE* sPtrA, LISTNODE* sPtrB, LISTNODE** sPtrAB)
{
	LISTNODE* newPtr=NULL, *crntPtrA=sPtrA, *crntPtrAB=NULL;
	
	while (crntPtrA != NULL){//��������A 
            //��B��Ѱ��A����ǰ�����е�������û�ҵ�������������� 
		if (_search (crntPtrA->num, sPtrB)==0){
            	newPtr = (LISTNODE*)malloc(sizeof(LISTNODE));
            	newPtr->num = crntPtrA->num;
			newPtr->nextPtr=NULL;
            	if (*sPtrAB == NULL){
				*sPtrAB = newPtr;}
			else{
				crntPtrAB->nextPtr = newPtr;}
			crntPtrAB = newPtr;
		}
		crntPtrA = crntPtrA->nextPtr;
	}
}

int _search (int data, LISTNODE* sPtr)
{
      LISTNODE* crntPtr=sPtr;

	while (crntPtr != NULL){//����������Ѱĳ����  
		if (crntPtr->num == data){//���ҵ��򷵻أ� 
			return 1;}
		crntPtr = crntPtr->nextPtr;
	}
	return 0;//û�ҵ��򷵻أ� 
}

void _printList (LISTNODE* sPtr)
{
	LISTNODE* crntPtr=sPtr;

	while (crntPtr != NULL){//����ÿһ�����Ტ��ӡ���� 
		printf ("%-6d", crntPtr->num);
		crntPtr = crntPtr->nextPtr;
	}
}
