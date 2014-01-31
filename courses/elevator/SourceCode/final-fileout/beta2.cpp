#include "elevator.h"

int Time=0;
status eleStat;
int dnRqst[10] = {0}, upRqst[10]={0};
FILE* oPtr;

//=====================================================================

int main()
{
	eleStat.floor = 1;
	eleStat.dir = 0;
	oPtr = fopen( "result.txt", "a+" );
	DWORD ThreadID1 = 1;
	HANDLE hRead1 = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)control, NULL, 0, &ThreadID1 );
	DWORD ThreadID2 = 2;
	HANDLE hRead2 = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)getInput, NULL, 0, &ThreadID2 );

	while (1) {}
	return 0;
}



