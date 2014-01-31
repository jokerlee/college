#include "elevator.h"
#include "externals.h"

char snd[10][15]={ "", "floor1.wav", "floor2.wav", "floor3.wav", "floor4.wav", "floor5.wav", 
						"floor6.wav", "floor7.wav", "floor8.wav", "floor9.wav" };

void control( void )
{
	while (1)
	{
	 	if ( isWait() )
			waiting();	
		
		if ( isStop( eleStat.dir, eleStat.floor ) )
			stop( eleStat.dir, eleStat.floor );

		eleStat.dir = newDirection( eleStat.dir, eleStat.floor );

		if ( eleStat.dir != 0 && !isStop( eleStat.dir, eleStat.floor ) )
			move( eleStat.dir, &eleStat.floor );
	}			 
}


//======================================================================

void stop( int dir, int floor )
{
	fprintf( oPtr, "%-4d:Stop at Floor %d\n", Time, floor );

	//�����ɵ�����
	eleStat.inRqst[floor] = 0;

	//��Ӧ��ǰ����
	if ( dir != 0 )
		if ( dir == 1 )			upRqst[floor] = 0;
		else if ( dir == -1 )	dnRqst[floor] = 0;
	else
		if ( upRqst[floor] == 1 )
			upRqst[floor] = 0;
		else if ( dnRqst[floor] == 1 )
			dnRqst[floor] = 0;

	//���µ��������ʾ

	//��������
	PlaySound( "global.wav", NULL, SND_ASYNC|SND_NODEFAULT );   
	Sleep(800);
	PlaySound( snd[floor], NULL, SND_SYNC|SND_NODEFAULT );   
	//ʱ���ƽ�
	putClock( stopTime );
}

//===============================================================

void move( int dir, int* floor )
{
	
	//������һ��
	if ( dir == 1 )	
		fprintf( oPtr, "%-4d:Moving up from %d to Floor %d\n", Time, *floor, *floor+dir );	
	else
		fprintf( oPtr, "%-4d:Moving up from %d to Floor %d\n", Time, *floor, *floor+dir );	

	*floor += dir;

	Time += runTime;
}

//=======================================================================

int isStop( int dir, int floor )
{
	if ( eleStat.inRqst[floor] != 0 )
		return 1;
	if ( dir == 1 && upRqst[floor] == 1 || dir == -1 && dnRqst[floor] == 1 )
		return 1;
	if ( dir == 0 && ( upRqst[floor] == 1 || dnRqst[floor] == 1 ) )
		return 1;
	return 0;
}

//=======================================================================

int newDirection( int dir, int floor )
{
	int i;
	if ( dir == 0 )
		for ( i=1; i<=maxFloor; i++ )
			if ( isStop( dir, i ) )
				return (i-floor)>0?1:-1;
	if ( dir == 0 ) dir = 1;
	//��ͬ����
	for ( i=floor+dir; i<=maxFloor && i>0; i+=dir )
		if ( isStop( dir, i ) )
			return dir;
	//�ѷ�����
	for ( i=floor-dir; i<=maxFloor && i>0; i-=dir )
		if ( isStop( -dir, i ) )
			return -dir;
	
	//������
	return 0;
}

//========================================================================

void waiting( void )
{
	int waitTime = 0;
	eleStat.dir = 0;
	while ( isWait() )
	{
		//��ʱ,�ȴ���ʱ�򷵻ص�һ��
		if ( waitTime > maxWaitTime )
			if ( eleStat.floor != 1 )
			{
				eleStat.inRqst[1] = 1;
				break;
			}

		waitTime ++;
		fprintf( oPtr, "%-4d:Wait at Floor %d\n", Time, eleStat.floor );
		putClock( 1 );
	}
	return;
}


int isWait()
{
	int i;
	for ( i=1; i<=maxFloor; i++ )
		if ( upRqst[i] == 1 || dnRqst[i] == 1 || eleStat.inRqst[i] == 1 )
			return 0;
	return 1;
}

void putClock( int n )
{
	int from, to;
	while ( n-- )
	{
		Time++;
		from = clock();
		do	to = clock();
		while ( (to-from)/(CLOCKS_PER_SEC/2) < 1 );
	}
}