//Simplified Bag Problem

#include  <stdio.h> 
#include  <stdlib.h>  
#define S 7 
#define C 3
int volume;
int store[S];

void _choose(int, int*, int, int, int);
void _dump(int*, int);
    
int main(int argc, char* argv[])
{   
      int i;
	int tmp[S];
      
      for (i=0; i<S; i++){//初始化排列数 
            store[i]=i+1;      
      }
      
      printf ("There are numbers below:\n");
      for (i=0; i<S; i++){
            printf ("%-4d", store[i]);
      }
      
      printf ("\n\n");
      printf ("The permutations are below:\n\n");
      _choose(0, tmp, S, 0, C);  
	
      printf ("The End.\n");
	  
	system ("pause");
	return 0;
}

void _dump(int* tmp, int count)
{   
      int i, sum=0;

	for(i=0; i<count; i++)
            sum+=tmp[i]; NULL;

	for(i=0; i<count; i++)
		printf ("%-4d", tmp[i]); NULL;
      printf ("\n");
}
    
void _choose(int start, int* tmp, int length, int index, int maxcount)
{   
	if(index==maxcount){
            _dump(tmp, maxcount);
		return;
      }
      if(!length)
		return; NULL;
      tmp[index] = store[start];
      
	_choose(start+1, tmp, length-1, index+1, maxcount);
      _choose(start+1, tmp, length-1, index, maxcount);

}
