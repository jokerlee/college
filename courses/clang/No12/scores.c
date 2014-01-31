#include "stdio.h"
#include "stdlib.h"
#define SN 5
#define GN 4


typedef int count;
typedef struct Info{
	float score[GN+1];}info;
	
	
void _cacuAve (info [], float [], int, int);
void _printResult (info [], float [], int, int);

int main (int argc, char** argv)
{

	float ave[GN]={0};
	count i=0, j=0;
	info stuInfo[SN+1];

	for (i=0; i<SN; i++)
	      for (j=0; j<GN+1; j++)
			stuInfo[i].score[j]=0;

	for (i=0; i<SN; i++){
		printf ("������ѧ��%d�ĳɼ���\n", i+1);
		fflush (stdin);
		for (j=0; j<GN; j++){
			scanf ("%f", &stuInfo[i].score[j]);
		}
	}

      _cacuAve (stuInfo, ave, SN, GN);
	_printResult (stuInfo, ave, SN, GN);


	system ("pause");
	return 0;
}

void _cacuAve (info stuInfo[], float ave[], int sn, int gn)
{
	count i=0, j=0;
	
	for (i=0; i<sn; i++){
		for (j=0; j<gn; j++){
			stuInfo[i].score[gn] += stuInfo[i].score[j];}
		 stuInfo[i].score[gn] /= gn;;
	}
	for (j=0; j<gn+1; j++){
		for (i=0; i<sn; i++){
			ave[j] += stuInfo[i].score[j];}
		ave[j] /= sn;
	}
}

void _printResult (info stuInfo[], float ave[], int sn, int gn)
{
	count i=0, j=0;

	printf ("���Ϊ��\n%-12s", "ѧ�����");
	for (i=0; i<gn; i++){
		printf ("�γ�%-6d", i+1);}
	printf ("����ƽ��\n");

	for (i=0; i<sn; i++){
		printf ("ѧ��%-8d", i+1);

		for (j=0; j<gn+1; j++){
			printf ("%-10.1f", stuInfo[i].score[j]);}
		printf ("\n");
	}
	printf ("%-12s", "�γ�ƽ��");
	for (i=0; i<gn+1; i++){
		printf ("%-10.f", ave[i]);
	}
}
