/*
  Name: ������ת��ʮ���� 
  Copyright: Free 
  Author: Joker Lee 
  Date: 23/11/07 18:17
  Description: �õݹ��㷨��������ת����ʮ���� 
  �ݹ�˼·:��101101ת����ʮ����,���� 10110ת���ɶ�������*2+1... 
  ���ƹ�ʽ:convert(x)= {convert(x/10)*2+x%10 |x/10!=0; x |x/10=0}
*/
#include <stdio.h>
#include <stdlib.h>

long _convert(int);
int main()
{
	long bin;
	
	printf ("�������������:");
	scanf ("%d", &bin);
	
	printf ("��Ӧ��ʮ��������:%ld\n", _convert(bin)); 
	
	system ("pause");
	return 0;	
}

long _convert(int x)//�ݹ���ж�����ת�� 
{
	if (x/10==0){
		return x;
	}	
	else{
		return _convert(x/10)*2+x%10;
	}
}
