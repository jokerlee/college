//10. ������0~99 

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
main(){
    int num=0, a=0, b=0, i = 0;//a��b�ֱ����ڴ����������ĸ�λ��ʮλ 
    
    printf ("Input data:");
    scanf ("%d", &num);
    
    if (num>99 && num <0){//�ų�����Χ���
       printf ("input error");
       exit(0);
       }
    
   
    
    for (i=0;i<2;i++){//ѭ�����δ�ӡ��λ��,��һ�δ�ӡʮλ,�ڶ��θ�λ
    a =(int) pow(10,1-i);
        switch (num/a){
               case 0:
                    if (num/10) break;//������ִ��ڵ���10,����,�������er shi ling�����(��һ��ѭ��) 
                    else if(i==1){//�ڶ���ѭ��(��λ)��ӡling,��������0�����
                         printf("LING");
                         system("pause");
                         exit(0);
                         }
                    else break;//�������er shi ling�����(�ڶ���ѭ��)
               case 1:
                    if (i==1) printf("YI ");break;//��һ��ѭ������ӡ"һ",ʹʮλ������"һ",�������"һʮһ"
               case 2:
                    printf("ER ");break;
               case 3:
                    printf("SAN ");break;
               case 4:
                    printf("SI ");break;
               case 5:
                    printf("WU ");break;
               case 6:
                    printf("LIU ");break;
               case 7:
                    printf("QI ");break;
               case 8:
                    printf("BA ");break;
               case 9:
                    printf("JIU ");break;
               }
               
			   if (num/10)
			       printf("SHI ");//����"ʮ"��������,��ӡ�м��"ʮ"
               
			   num=num%10;//��ȡ��λ��,Ϊ�ڶ���ѭ����׼��
        }
                    
    system("pause");                      
                    
           
           

}
