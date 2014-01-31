// bags.cpp : Defines the enTRY point for the console application.
//

#include <stdio.h>
#include <malloc.h>

void TRY(int* stuffs,int loc,int len);
static int volume;

int main(int argc, char* argv[])
{

	int size;
	int* stuff;
	int i,init;

	printf("please input the number of the xxx:");
	scanf("%d",&size);

	printf("please input the volume:");
	scanf("%d",&volume);

	stuff=(int*)malloc(size*sizeof(int)*2);

	printf("please input the stuffs");
	for (i=0;i<size*2;i+=2)
	scanf("%d",&stuff[i]);
	
	for (i=0;i<size*2;i+=2){
		for (init=0;init<=i;init+=2) stuff[init+1]=0;
		stuff[i+1]=1;
		TRY(stuff,i,size*2);
	}

	
	return 0;
}

void TRY(int* stuffs,int loc,int len){
	int i;
	int sum=0;
	
	for (i=0;i<=loc;i+=2){
		if (stuffs[i+1]) 
			sum+=stuffs[i];
	}
	
	if (sum==volume){
		printf("keys:");
		for (i=0;i<=loc;i+=2)
			if (stuffs[i+1]) printf("%d ",stuffs[i]);
			printf("\n");
		
		stuffs[loc+1]=0;
		TRY(stuffs,loc+2,len);
		return;
	}else if (sum>volume){
		if (loc<len){
			stuffs[loc+1]=0;
			stuffs[loc+3]=1;
			TRY(stuffs,loc+2,len);
		}
		return;
	}else if (sum<volume){
		if (loc<len){
			stuffs[loc+3]=1;
			TRY(stuffs,loc+2,len);
		}
		return;
	}


}
