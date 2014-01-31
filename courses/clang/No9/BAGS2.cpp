//Simplified Bag Problem

#include  <stdio.h> 
#include  <stdlib.h>  
#define S 10 
#define C 9
int volume;
const int store[S]={10,20,30,10,27,16,14,24,19,13};
int isFound = 0;

void _choose(int, int*, int, int, int);
void _dump(int*, int);
    
int main(int argc, char* argv[])
{   
      int i;
	int tmp[2*S];//tmp is used for storing the slected item and its No followed

      printf ("There are items below:\n");
      for (i=0; i<S; i++){
		printf ("%d)%-4d", i+1, store[i]);
	}

	printf ("\nPlease set the volume of the bag:");
	scanf ("%d", &volume);

	for (i=1; i<=S; i++){
      	_choose(0, tmp, S, 0, 2*i);
	}

	if (isFound == 0) printf ("No solution is found!\n");//judge whether there is a solution
	printf ("The End.\n");
	  
	system ("pause");
	return 0;
}

void _dump(int* tmp, int start, int count)
{   
      int i, sum=0;

	for(i=0; i<count; i+=2)
		sum+=tmp[i]; NULL;

	if (sum==volume){
		isFound = 1;

		printf ("or\n");
		for(i=0; i<count; i+=2)
			printf ("put in No.%d, weigh:%d\n", tmp[i+1], tmp[i]); NULL;
      	printf ("\n");
	}
}
    
void _choose(int start, int* tmp, int length, int index, int maxcount)
{   
	if(index==maxcount){
            _dump(tmp, start, maxcount);

		return;
      }
      if(!length)
		return; NULL;
      tmp[index] = store[start];
      tmp[index+1] = start+1;
      
	_choose(start+1, tmp, length-1, index+2, maxcount);
      _choose(start+1, tmp, length-1, index, maxcount);


}
