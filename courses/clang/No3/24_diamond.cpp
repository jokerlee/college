
#include <stdio.h> 

int main()
{
    	int c=0, i=0, j=0, k=0, l=0, n=0, m=0;
    
	scanf ("%d %d", &n, &m ); 
        
	for (i = 1; i < 2*n ;i ++)
	{    
        	
		j = i;
        
		if (j > n) 
            		j = 2*n - j;
      		for ( l = 0; l < m; l++ )
       		{ 
	        	for (c = n - j + 1; c > 0; c--)
	            		printf(" ");
	        
	        	printf ("*");
	        	
			k++;
	        	
			for (c = 0; c < 2*j - 3; c++)
	            		printf(" ");
	        
	        	if (i != 1 && i != 2*n - 1)
			{
	        		printf ( "*" );
	        		k++;
			}
		        for (c = n - j + 1; c > 0; c--)
	            		printf(" ");
		}
		printf("\n");  
        
    	} 
    
    
    system ("pause");
    return 0;

} 
