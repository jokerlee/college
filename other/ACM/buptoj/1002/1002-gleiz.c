#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

typedef struct score{
   int s[3];
}score,SCORE;
int list[16]={0};
int rank[16384]={0};
score team[16384];
int pos=0;

int comp(const void* a,const void* b);
void gen(int k[],int depth,double sum);
int main(int argc, char *argv[])
{
   int i=0,j=0,k=0;
   int n=0;
   int cases=1;
   int max=0;
   double tmp=0;

   scanf("%d",&n);
   while (n!=0){
       for (i=0;i<n;i++){
           for (j=0;j<3;j++){
               scanf("%lf",&tmp);
               team[i].s[j]=(int)((tmp+0.001)*100);
           }
       }
       for (i=0;i<n;i++){
           scanf("%d",&rank[i]);
       }

       max=10000000;
       for (i=0;i<n;i++){
           if (max==-2) break;
           pos=0;
           gen(team[rank[i]-1].s,0,0);
           qsort(list,pos,sizeof(int),comp);
           if (i==0 || rank[i]>rank[i-1]){
               j=0;
               while (j<pos && list[j]>max) j++;
               if (j==pos){
                   max=-2;
                   break;
               }
               max=list[j];
           }else{
               j=0;
               while (j<pos && list[j]>=max) j++;
               if (j==pos){
                   max=-2;
                   break;
               }
               max=list[j];
           }
       }
       if (max==-2){
           printf("Case %d: No solution\n",cases++);
       }else{
           printf("Case %d: %.2lf\n",cases++,(1.0*max)/100);
       }
       scanf("%d",&n);
   }

   return 0;
}

int comp(const void* a,const void* b){
   return *(int*)b-*(int*)a;
}

void gen(int k[],int depth,double sum){
   if (depth==2){
       list[pos++]=sum+k[2];
       list[pos++]=sum;
       return;
   }else{
       gen(k,depth+1,sum+k[depth]);
       gen(k,depth+1,sum);
   }
}
 

