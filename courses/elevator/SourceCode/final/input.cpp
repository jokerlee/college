#include "elevator.h"
#include "egg.h"
#include "externals.h"


void getInput( void )
{
	unsigned int key;
	Sleep(2000);
	while (1)
	{
		if ( WaitForEvent() == KEYDOWN )
		{
			key = GetStruckKey();
			switch ( key )
			{
				case 'Q': upRqst[1] = 1; drawOutRqstLight(1,1,1); break;
				case 'W': upRqst[2] = 1; drawOutRqstLight(2,1,1); break;
				case 'E': upRqst[3] = 1; drawOutRqstLight(3,1,1); break;
				case 'R': upRqst[4] = 1; drawOutRqstLight(4,1,1); break;
				case 'T': upRqst[5] = 1; drawOutRqstLight(5,1,1); break;
				case 'Y': upRqst[6] = 1; drawOutRqstLight(6,1,1); break;
				case 'U': upRqst[7] = 1; drawOutRqstLight(7,1,1); break;
				case 'I': upRqst[8] = 1; drawOutRqstLight(8,1,1); break;

				case 'A': dnRqst[2] = 1; drawOutRqstLight(2,-1,1); break;
				case 'S': dnRqst[3] = 1; drawOutRqstLight(3,-1,1); break;
				case 'D': dnRqst[4] = 1; drawOutRqstLight(4,-1,1); break;
				case 'F': dnRqst[5] = 1; drawOutRqstLight(5,-1,1); break;
				case 'G': dnRqst[6] = 1; drawOutRqstLight(6,-1,1); break;
				case 'H': dnRqst[7] = 1; drawOutRqstLight(7,-1,1); break;
				case 'J': dnRqst[8] = 1; drawOutRqstLight(7,-1,1); break;
				case 'K': dnRqst[9] = 1; drawOutRqstLight(8,-1,1); break;

				case '1': eleStat.inRqst[1] = 1; drawInRqstLight(1); break;
				case '2': eleStat.inRqst[2] = 1; drawInRqstLight(2); break;
				case '3': eleStat.inRqst[3] = 1; drawInRqstLight(3); break;
				case '4': eleStat.inRqst[4] = 1; drawInRqstLight(4); break;
				case '5': eleStat.inRqst[5] = 1; drawInRqstLight(5); break;
				case '6': eleStat.inRqst[6] = 1; drawInRqstLight(6); break;
				case '7': eleStat.inRqst[7] = 1; drawInRqstLight(7); break;
				case '8': eleStat.inRqst[8] = 1; drawInRqstLight(8); break;
				case '9': eleStat.inRqst[9] = 1; drawInRqstLight(9); break;
				
				case 0x1B: drawExit(); fclose(oPtr); exit(0); break; //ESCÍË³ö
				default : break;
			}
		}
	}
}