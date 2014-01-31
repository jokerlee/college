#include <stdio.h>

int main( int argc, char** argv )
{
	char pre = 0, cur = 0;
	int nPre = 0, nCur = 1;

	pre = getchar();
	while ( ( cur = getchar() ) != '#' )
	{
		if ( cur == pre )
		{
			if ( cur == 'a' && pre == 'a' )
				nCur ++;
			else if ( cur == 'b' && pre == 'b' )
				nCur ++;
			else if ( cur == 'c' && pre == 'c' )
				nCur ++;
			else
			{	
				printf( "The string is not acceptable." );
				system( "pause" );			
				return 0;
			}
			pre = cur;
		}
		else
		{
			if ( ( nPre != 0 && nPre != nCur ) || cur != pre + 1 )
			{
				printf( "The string is not acceptable." );
				system( "pause" );			
				return 0;
			}
			nPre = nCur;
			pre = cur;
			nCur = 1;
		}
	}

	if( nPre != nCur || pre != 'c' )
	{
		printf( "The string is not acceptable." );
		system( "pause" );
		return 0;
	}

	printf( "The string is acceptable." );
	system( "pause" );	
	return 0;

}
