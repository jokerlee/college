//14.打印一个N行的三角形乘法表 


#include <stdio.h> 
#include <stdlib.h> 

int main() 
{ 
      int i=1, j=1, n=0; //i为行号，j为每行项数号 
    
      printf ("Please input N(N>0):");
      scanf ("%d", &n);
    
      while(i <= n){ //每次循环打印一项  
            printf("%d*%d=%d, ", i, j, i*j); //输出i*j=? 
            
            if(i == j){//如果i=j就换行
                  printf("\n");//换行 
                  ++i; //行数+1 
                  j = 0; //换行后j重新初始化 
            } 
      ++j; //项数+1 
      } 
    
      system ("pause");
      return 0;
}
