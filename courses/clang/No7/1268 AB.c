//1268
#include<stdio.h>

int main()
{
	int max = 0;
	
	while ( scanf( "%d", &max ) != EOF )
	{
		int n = 0;
		int na=0, nb=0;
		for ( n = 1; n <= max; n++ )
		{
			int b = 1;
			int t = n;
			int n1=0, n0=0;
			while( t/2 )
			{
				b *= 2;
				t /= 2;
			}
			t = n;
			while ( b )
			{
				if ( t/b == 1 )
				    n1++;
				else
				    n0++;
				t %= b;
				b /= 2;
			}
			if ( n1 > n0 )
			    na++;
			else
			    nb++;
		}
		printf( "%d %d\n", na, nb );
	}
    
	system( "pause" );
	return 0;
}
