//input a circlr's radius, then caculates and print its area

#include<stdio.h>
main()
{
      const double Pi = 3.14;
      double radius, area;
      
      printf ("Plese input a radium:");
      scanf ("%f", &radius);
      
      area = Pi * radius * radius;      
      printf ("The area is: %f", area);
      
      //system ("pause");
      return 0;
      
}
      
