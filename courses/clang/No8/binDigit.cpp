/*
  Name: ������λ�� 
  Copyright: Free
  Author: Joker Lee 
  Date: 23/11/07 15:57
  Description:�����������ʮ�������Ķ�������ʽ��λ�� ���ݹ飩 
*/
#include <stdio.h>
#include <stdlib.h>

int _getDigit(int);
int main()
{
	int num, i, n;
	printf ("�������������ĸ�����\n");
	scanf ("%d", &n);//����Ҫ����������ĸ��� 
	printf ("������%d����������\n", n);
	
	for (i=0; i<n; i++){//ѭ������i��ʮ�������� 
		scanf ("%d,", &num); 
		if (i==0){//��һ��ѭ����ӡ��ʾ 
			printf ("ת���ɶ�������ʽ��ĳ����ǣ�\n");
		}
		printf ("%d", _getDigit(num));		
		if (i != n-1){//���һλ����ӡ���� 
			printf (",");
		}
		else printf ("\n");//�������һλ���� 
	} 
	system ("pause");
	return 0;
}

int _getDigit(int bit)//�ݹ��������λ�� 
{
	if (bit/2 == 0){
		return 1;
	}	
	else
		return _getDigit(bit/2)+1;
}
