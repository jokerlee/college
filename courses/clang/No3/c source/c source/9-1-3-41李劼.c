//14.��ӡһ��N�е������γ˷��� 


#include <stdio.h> 
#include <stdlib.h> 

int main() 
{ 
      int i=1, j=1, n=0; //iΪ�кţ�jΪÿ�������� 
    
      printf ("Please input N(N>0):");
      scanf ("%d", &n);
    
      while(i <= n){ //ÿ��ѭ����ӡһ��  
            printf("%d*%d=%d, ", i, j, i*j); //���i*j=? 
            
            if(i == j){//���i=j�ͻ���
                  printf("\n");//���� 
                  ++i; //����+1 
                  j = 0; //���к�j���³�ʼ�� 
            } 
      ++j; //����+1 
      } 
    
      system ("pause");
      return 0;
}
