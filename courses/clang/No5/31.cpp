/*
  Name: 3.�Ҷ��� 
  Copyright: Free 
  Author: Joker Lee 
  Date: 04/11/07 14:04
  Description: ABC��XYZ����,�ҳ��������,����A����X����,C����XZ����(��ٷ�)
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char i,j,k;//i��A�Ķ��֣�j��B�Ķ��֣�k��C�Ķ���	
	int l = 1;//l���ڼ��㱾���ǵڼ�������		
	int flag;//�������Ҫ��������������޸� 
	 
	for(i = 'X';i <= 'Z';i++) { //ΪA�Ҷ��� 
		for(j = 'X';j <= 'Z'; j++){//ΪB�Ҷ��� 
			for(k = 'X';k <= 'Z';k++){ //ΪC�Ҷ���
				if(i!= j && i!=k && j!=k){ //ΪA��B��C���ָ�����ͬʱ����ӡ 
					flag = (i!='X' && k!='X'&& k!='Z');
					if(flag != 0){
						printf("��%d�������:\n",l);
						printf("A��%c����\n",i);
						printf("B��%c����\n",j);
						printf("C��%c����\n",k);
						l++;//����������� 
					}
				}
			}
		} 
	}

	system ("pause");	
	return 0;

}
