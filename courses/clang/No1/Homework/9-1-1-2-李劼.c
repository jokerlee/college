//input a circlr's radius, then caculates and print its area

#include<stdio.h>
main()
{
      const Pi = 3.14;
      float radius, area;
      
      printf ("Plese input a radium:");
      scanf ("%f", &radius);
      
      area = Pi * radius * radius;      
      printf ("The area is: %f", area);
      
      system ("pause");
      return 0;
      
}
      
