//7.��������������λ�������������ɱ�K����

#include<stdlib.h>
#include<stdio.h>

main()
{
      int i, k, sub1, sub2,sub3;//sub���ڴ������� 
      int flag1, flag2;//�����жϱ�� 
      
      printf ("����һ������k��"); 
      scanf ("%d", &k);
      
      for (i = 10000; i <= 30000; i ++){
          sub1 = i/100;
          sub2 = i%10000/10;
          sub3 = i%1000;
                    
          flag1 = (((sub1%k) == 0) && ((sub2%k) == 0) && ((sub3%k) == 0));
          flag2 = ((sub1 != 0) && (sub2 != 0) && (sub3 != 0));
          if (flag1 && flag2)
             printf ("%d\n", i);
          }
              
      system ("pause");
      return 0;
}
