//24.输入n,打印n-1行空心钻石 

/*分析：设总行数为2n-1，当前行为i，到达最大行以前，*前空格为n-i，
*间空格为2(i-1)-1,到达最长行后,*前空格变为i-n,*间空格为2(2(n-1)-1)=
29-2i*/ 


#include <stdio.h> 
#include <stdlib.h> 

int main()
{
      int c=0, i=0, j=0, n=0;//c与j均为控制循环的中间变量 ,j用于处理最长行后的递减 
    
      printf ("input N(total rows will be 2*N-1):");
      scanf ("%d", &n); 
        
      for (i = 1; i < 2*n ;i ++){ //此循环打印每一行 
            j = i;
            if (j > n) //处理最长行后的递减 
                  j = 2*n - j;
        
            for (c = n - j + 1; c > 0; c--)//此循环打印每行第一个*前的空格 
                  printf(" ");
        
            printf ("*");
        
            for (c = 0; c < 2*j - 3; c ++) //此循环打印每行2个*之间的空格 
                  printf(" ");        
        
            if (i != 1 && i != 2*n - 1)//如果是首行或末行，不打印第二个 *
                  printf ("*");     
        
            printf("\n");  
      }     
    
      system ("pause");
      return 0;

} 
