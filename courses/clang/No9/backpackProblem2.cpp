#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

static int maxG;

void _stuffing(const int*, int*, int, int);
int main(int argv, char* argc[])
{
	int store[SIZE] = {0,1,1,1,1,1,4,3,2,1};
	int state[SIZE] = {1,0,0,0,0,0,0,0,0,0};
	
	int validN = SIZE;
	
	printf ("Please input the volume:");
	scanf ("%d", &maxG);
	
	_stuffing(store, state, 0, validN);
	
	system ("pause");
	return 0;
}

void _stuffing(const int* store, int* state, int start, int validN)
{
	int i, sumG=0;
	
	for (i=0; i<validN; i++){
		if (state[i]==1) 
			sumG+=store[i];NULL;
	}

	if (sumG == maxG && start < validN){
		printf("Find it!:");
		for (i=0; i<=start; i++){
			if (state[i]==1) 
				printf("%d ", store[i]);NULL;
		}
		printf("\n");
		state[start]=0;
		_stuffing(store, state, start+1, validN);
		return;
	}
	else if (sumG > maxG && start < validN){
		state[start]=0;
		state[start+1]=1;
		_stuffing(store, state, start+1, validN);		
		return;
	}
	else if (sumG < maxG && start < validN){
		state[start+1]=1;
		_stuffing(store, state, start+1, validN);
		return;
	}
	else{
		state[start]=0;return;
	}
}
