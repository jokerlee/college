//operating of int array

#include <stdio.h>
#include <stdlib.h>
#define SIZE 11


int _bubbleSort(int*, int, int);
int _selectSort(int*, int, int);
int _maxElement(int*, int, int, int);
int _minElement(int*, int, int, int);
int _selectSort(int*, int);
int _orderSearch(int, int*, int, int, int);
int _insertElement(int, int*, int, int);

int main()
{
      int array[SIZE] = {5,6,3,4,1,8,9,2,0,7};
      int validN = 10;
      int i;

      /*_bubbleSort(array, validN, 1);//rise order
      for (i=0; i<validN; i++)
            printf ("%d", array[i]);
            printf ("\n");
      
      _bubbleSort(array, validN, 0);//fall order
      for (i=0; i<validN; i++)
            printf ("%d", array[i]);
            printf ("\n");     */       
      printf ("%d\n", _orderSearch(7 ,array, 0, validN-1, validN));      
      
      //_maxElement(array, validN);
            printf ("max=array[%d]", _maxElement(array, validN, 0, validN-1));
            printf ("\n");
            
      //_minElement(array, validN);
            printf ("min=array[%d]", _minElement(array, validN, 0, validN-1));
            printf ("\n");
      _selectSort(array, validN, 0);
      for (i=0; i<validN; i++)
            printf ("%d", array[i]);
            printf ("\n");
                 
      _selectSort(array, validN, 1);
      for (i=0; i<validN; i++)
            printf ("%d", array[i]);
            printf ("\n");
      
      //_dichoSearch(num ,array, start, end, validN);
      
      _insertElement(111, array, 3, validN);
      for (i=0; i<validN; i++)
            printf ("%d", array[i]);
            printf ("\n");
      //_deletElement(array, loc, validN);

      system ("pause");
      return 0;
}

int _bubbleSort(int *ay, int n, int isRise)
{
      int pass, i;
      
      for (pass=1; pass<n; pass++){
            for (i=0; i<n-1; i++){
                  switch (isRise){
                        case 1:{
                              if (ay[i] > ay[i+1]){
                                    ay[i] = ay[i]+ay[i+1];
                                    ay[i+1] = ay[i]-ay[i+1];
                                    ay[i] = ay[i]-ay[i+1];     
                              }
                              break;
                        }
                        case 0:{
                              if (ay[i] < ay[i+1]){
                                    ay[i] = ay[i]+ay[i+1];
                                    ay[i+1] = ay[i]-ay[i+1];
                                    ay[i] = ay[i]-ay[i+1];     
                              }
                        break;
                        }                       
                        default :return -1;
                  }
                  
            }
      }
}

int _maxElement(int *ay, int n, int start, int end)
{
      int max=start, i;
      
      for (i=start; i<=end && i<n; i++){
            if (ay[i] > ay[max])
                  max = i;NULL;
      }
      return max;
}

int _minElement(int *ay, int n, int start, int end)
{
      int min=start, i;
      
      for (i=start; i<=end && i<n; i++){
            if (ay[i] < ay[min])
                  min = i;NULL;
      }
      return min;
}

int _selectSort(int *ay, int n, int isRise)
{
      int max, min, i, temp;
      switch (isRise){
            case 0:{
                  for (i=0; i<n-1; i++){
                        max = _maxElement(ay, n, i, n-1);
                        temp = ay[i];
                        ay[i] = ay[max];
                        ay[max] = temp;
                  }
                  break;    
            }
            case 1:{
                  for (i=0; i<n-1; i++){
                        min = _minElement(ay, n, i, n-1);
                        temp = ay[i];
                        ay[i] = ay[min];
                        ay[min] = temp;
                  }
                  break;
            }     
            default: return -1;
      }
}
int _orderSearch(int num , int *ay, int start, int end, int n)
{
      int i=start;
      for (i=start; ay[i]!=num && i<=end; i++);
      if (i<=end)
            return i;
      else 
            return -1;
               
}

int _insertElement(int num, int *ay, int loc, int validN)
{
      int i;
      for (i=validN-1; i<=loc; i++){
            ay[i+1] = ay[i];
      }      
	ay[loc]=num; 
}
