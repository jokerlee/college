//10. 念数字0~99 

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
main(){
    int num=0, a=0, b=0, i = 0;//a，b分别用于储存输入数的个位和十位 
    
    printf ("Input data:");
    scanf ("%d", &num);
    
    if (num>99 && num <0){//排除超范围情况
       printf ("input error");
       exit(0);
       }
    
   
    
    for (i=0;i<2;i++){//循环两次打印两位数,第一次打印十位,第二次个位
    a =(int) pow(10,1-i);
        switch (num/a){
               case 0:
                    if (num/10) break;//如果数字大于等于10,跳出,避免出现er shi ling的情况(第一次循环) 
                    else if(i==1){//第二次循环(个位)打印ling,处理输入0的情况
                         printf("LING");
                         system("pause");
                         exit(0);
                         }
                    else break;//避免出现er shi ling的情况(第二次循环)
               case 1:
                    if (i==1) printf("YI ");break;//第一次循环不打印"一",使十位不出现"一",避免出现"一十一"
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
			       printf("SHI ");//处理几"十"几的问题,打印中间的"十"
               
			   num=num%10;//提取个位数,为第二次循环做准备
        }
                    
    system("pause");                      
                    
           
           

}
