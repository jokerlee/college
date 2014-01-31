#include "elevator.h"
#include "egg.h"
#include "externals.h"


void getInput( void )
{
	char key;
	while (1)
	{
		if ( key != '\n')	printf( "«Î ‰»Î«Î«Û£∫" );
		key = getchar();
		switch ( key )
		{
			case 'Q': upRqst[1] = 1; break;
			case 'W': upRqst[2] = 1; break;
			case 'E': upRqst[3] = 1; break;
			case 'R': upRqst[4] = 1; break;
			case 'T': upRqst[5] = 1; break;
			case 'Y': upRqst[6] = 1; break;
			case 'U': upRqst[7] = 1; break;
			case 'I': upRqst[8] = 1; break;

			case 'A': dnRqst[2] = 1; break;
			case 'S': dnRqst[3] = 1; break;
			case 'D': dnRqst[4] = 1; break;
			case 'F': dnRqst[5] = 1; break;
			case 'G': dnRqst[6] = 1; break;
			case 'H': dnRqst[7] = 1; break;
			case 'J': dnRqst[8] = 1; break;
			case 'K': dnRqst[9] = 1; break;

			case '1': eleStat.inRqst[1] = 1; break;
			case '2': eleStat.inRqst[2] = 1; break;
			case '3': eleStat.inRqst[3] = 1; break;
			case '4': eleStat.inRqst[4] = 1; break;
			case '5': eleStat.inRqst[5] = 1; break;
			case '6': eleStat.inRqst[6] = 1; break;
			case '7': eleStat.inRqst[7] = 1; break;
			case '8': eleStat.inRqst[8] = 1; break;
			case '9': eleStat.inRqst[9] = 1; break;
			
			case '#': exit( 0 );
			default : break;
			fflush( stdin );
		}
	}
}