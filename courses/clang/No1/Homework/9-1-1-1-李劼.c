//input sex, age and height, then print then

#include<stdio.h>
main()
{
   int age;
   char sex;
   float height;
   
   printf ("Plese input the sex, age and height as below \n");
   printf ("M,18,1.75 \n");
   scanf ("%c,%d,%f", &sex, &age, &height);
   
   printf  ("The sex is %c \n", sex);
   printf  ("The age is %d \n", age);
   printf  ("The height is %fm \n", height);
   
   system("pause");
   return 0;

}
