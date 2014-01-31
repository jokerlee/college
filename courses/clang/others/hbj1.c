#include <stdio.h>
#include <stdlib.h>
#define M 5
#define N 5


void inputa(int [][N],int,int);
void exchangeRows(int [][N],int,int,int);
float av(int [],int);
void printa(int[][N],int,int);

main()
{
	int i,j;
	int a[M][N]=
	{6,6,6,6,6,
	 2,2,2,2,2,
	 7,7,7,7,7,
	 9,9,9,9,9,
	 5,5,5,5,5};
	printf("ÇëÊäÈëÕûÊı¾ØÕó£¨5*5£©:\n");
	//inputa(a,M,N);
	for(i=1;i<=M-1;i++){
	    for(j=1;j<=M-1;j++)
	    {
		  if(av(a[j-1],N)>av(a[j],N)){
		     exchangeRows(a,j-1,j,N);
		  }
	    }
      }
	printa(a,M,N);
	system("pause");
	return 0;


}


void inputa(int a[][N],int rows,int cols)
{
	int i,j;
	for(i=0;i<=rows-1;i++)
	    for(j=0;j<=cols-1;j++)
		  scanf("%d",&a[i][j]);


}


void exchangeRows(int a[][N],int Rows1,int Rows2,int cols)
{
	int i,mid;
	for(i=0;i<=cols-1;i++)
	{
		mid=a[Rows1][i];
		a[Rows1][i]=a[Rows2][i];
		a[Rows2][i]=mid;
	}
}

void printa(int a[][N],int rows,int cols )
{
	int i,j;
	for(i=0;i<=rows-1;i++)
	    for(j=0;j<=cols-1;j++)
	    {
		  printf("%-5d",a[i][j]);
		  if(j==cols-1)
		     printf("\n");
          }
}


float av(int a[],int cols)
{
	int i;
	float total=0;
	for(i=0;i<=cols-1;i++)
	    total+=a[i];
	return total/cols;

}















