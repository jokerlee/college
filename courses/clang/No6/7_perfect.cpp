#include <stdio.h>
#include <stdlib.h>

int is_perfect(int);
void printPerfect(int);
int main()
{
	int min, max;
	int i, count=0;
	
	printf ("请输入判断范围(from,to)\n");
	scanf ("%d,%d", &min, &max);
	
	for(i=min; i<=max; i++){
		if (is_perfect(i)){
			printPerfect(i);
			printf ("\n");
			count++;
		}	
	}
	
	printf ("共计%d个完全数\n", count);
	system ("pause");
	return 0;	
				
}

int is_perfect(int num)
{
	int isperfect=0, j, geneSum=0;
	
      for (j=1; j<num; j++){//穷举法找出n的所有因子 
            if (num%j == 0)
                  geneSum += j; //若是因子加入总和 
      }
      if (geneSum == num)
		isperfect = 1;
	
	return isperfect;		
}

void printPerfect(int peft)
{
	int gene;
	
	printf ("%d=", peft);
	for(gene=1; gene<=peft; gene++){
		if (peft%gene==0 && gene!=peft)
			printf ("%d+", gene);
			if (gene == peft)
				printf ("\b ");
	}
	
}
