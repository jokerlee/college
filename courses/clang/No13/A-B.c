/*
  Name: 链表的差集 
  Copyright: Free 
  Author: Joker Lee 
  Date: 02-01-2007 18:22 
  Description: 求集合A与集合B的差集 
*/
#include "stdio.h"
#include "stdlib.h"

typedef struct listnode{//定义储存数字集合的链表 
      int num;
      struct listnode* nextPtr;
}LISTNODE;

typedef int COUNT;
typedef int FLAG;

void _inputNums (LISTNODE**);//读入一个集合 
void _differAB (LISTNODE*, LISTNODE*, LISTNODE**);//寻找AB的差集 
void _printList (LISTNODE*);//打印链表 
int _search (int, LISTNODE*);//在链表中搜索某各元素 

int main (int argc, char** argv)
{
	LISTNODE *listA=NULL, *listB=NULL, *listAB=NULL;
	
	puts ("请输入A链表的数据：");
	_inputNums (&listA);
	puts ("请输入B链表的数据：");
	_inputNums (&listB);
	
	_differAB (listA, listB, &listAB);

	puts ("A-B的数据为：");
	if (listAB == NULL){
            puts ("空集.");}
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

      while (interval != '\n'){//若数字后面紧跟回车，输入结束 
		newPtr = (LISTNODE*)malloc(sizeof(LISTNODE));//新建一个链结 
		scanf ("%d", &newPtr->num);
		newPtr->nextPtr=NULL;

		if (*sPtr == NULL){//若为首指针 
			*sPtr = newPtr;}
		else{
			crntPtr->nextPtr = newPtr;}
		crntPtr = newPtr;//更新当前指针 
		interval = getchar();//读入间隔字符 
	}
}

void _differAB (LISTNODE* sPtrA, LISTNODE* sPtrB, LISTNODE** sPtrAB)
{
	LISTNODE* newPtr=NULL, *crntPtrA=sPtrA, *crntPtrAB=NULL;
	
	while (crntPtrA != NULL){//遍历链表A 
            //在B中寻找A链表当前链结中的数，若没找到则将这个数加入差集中 
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

	while (crntPtr != NULL){//遍历链表搜寻某个数  
		if (crntPtr->num == data){//若找到则返回１ 
			return 1;}
		crntPtr = crntPtr->nextPtr;
	}
	return 0;//没找到则返回０ 
}

void _printList (LISTNODE* sPtr)
{
	LISTNODE* crntPtr=sPtr;

	while (crntPtr != NULL){//遍历每一个链结并打印出来 
		printf ("%-6d", crntPtr->num);
		crntPtr = crntPtr->nextPtr;
	}
}
