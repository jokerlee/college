#include "stdio.h"
#include "stdlib.h"
#define SN 5
#define GN 4

typedef struct Info info;
typedef int count;

void _cacuAve (Info [], int, int);
void _printResult (Info [], int, int);

int main (int argc, char** argv)
{
	struct Info{
		float score[GN+1];}
		
	count i=0, j=0;
	Info stuInfo[SN];


	for (i=0; i<SN; i++){
		printf ("������ѧ��%d", i);
		for (j=0; j<GN; j++){
			scanf ("%f", stuInfo[i].score[j]);
		}
	}

      _cacuAve (stuInfo, SN, GN);
	printf ("���Ϊ��\nѧ�����\t");
	for (i=0; i<SN; i++){
		printf ("�γ�%d\t");}
	printf ("����ƽ��\n");

	_printResult (stuInfo, SN, GN);


	system ("pause");
	return 0;
}

void _cacuAve (Info stuInfo[], int sn, int gn)
{
	float sum=0;
	count i=0, j=0;
	
	for (i=0; i<sn; i++){
		for (j=0; j<gn; j++){
			sum += sduInfo[i].score[j];}
		stuInfo[i].score[gn] = sum/gn;
	}
}

void _printResult (Info stuInfo[], int sn, int gn)
{
	count i=0, j=0;
	
	for (i=0; i<sn+1; i++){
		if (i==sn)
			printf ("�γ�ƽ��\n");
		else
		      printf ("ѧ��%d", i);
		printf ("ѧ��%d", i);
		for (j=0; j<gn; j++){
			printf ("%f\t", stuInfo[i].score[j]);}
		printf ("\n");
	}
}
