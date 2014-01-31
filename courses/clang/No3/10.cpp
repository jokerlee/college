#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
int main() 
{ 
	char str[128];
	int i=0;

	printf ("Please input a String:\n");
	scanf ("%s", &str[128]);
	
	while(str[i])
	{
		if ((str[i] >= 97) && (str[i] <= 122))
		    str[i] -=32;
        
        i++;
	}

	printf ("The result is:/n%s", str[128]);

	system("pause");
	return 0;
}
