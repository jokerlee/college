#include "elevator.h"
#include "egg.h"
#include "externals.h"

#define INTER 1.75

//=======================================================================

char picname[2][2][15] = { "triangle1.bmp", "triangle3.bmp", "triangle2.bmp", "triangle4.bmp" };
HEGG background, box, outRqLight, in[10], out[10][2], smArrow, tips, flr, dr, sp;

//========================================================================

void splash( void )
{
	sp = LayEgg();
	MovePen( 8,25 );
	DrawBitmap( "splash.bmp" );
	Sleep(2000);
	EatEgg();
}


void initGraph()
{
	EggStart( 30, 30 );
	ShowConsoleWindow( 0 );
	splash();
	background = LayEgg();
	MovePen( 3, 32 );
	DrawBitmap( "whole.bmp" );
	fprintf( oPtr, "Initializing... Please Wait...\n" );
	drawInfo( "Initializing... Please Wait..." );

	box = LayEgg();
	MovePen( 15.18, 12 );
	DrawBitmap( "elevator1.bmp" );

	smArrow=LayEgg();
    MovePen(7,29.3);
	DrawBitmap("smArrow2.bmp");

	in[1] = LayEgg(); MovePen( 4.8,	13.8			);	DrawBitmap( "button1B.bmp" );	ChangeEggLayer( BOTTOM );
	in[2] = LayEgg(); MovePen( 7.4,	14.8			);	DrawBitmap( "button2B.bmp" );	ChangeEggLayer( BOTTOM );
	in[3] = LayEgg(); MovePen( 4.82,	16.3		);	DrawBitmap( "button3B.bmp" );	ChangeEggLayer( BOTTOM );
	in[4] = LayEgg(); MovePen( 7.4,	14.8+2.53		);	DrawBitmap( "button4B.bmp" );	ChangeEggLayer( BOTTOM );
	in[5] = LayEgg(); MovePen( 4.82,	16.3+2.5	);	DrawBitmap( "button5B.bmp" );	ChangeEggLayer( BOTTOM );
	in[6] = LayEgg(); MovePen( 7.4,	14.8+2.53*2		);	DrawBitmap( "button6B.bmp" );	ChangeEggLayer( BOTTOM );
	in[7] = LayEgg(); MovePen( 4.82,	16.3+2.5*2	);	DrawBitmap( "button7B.bmp" );	ChangeEggLayer( BOTTOM );
	in[8] = LayEgg(); MovePen( 7.4,	15+2.53*3		);	DrawBitmap( "button8B.bmp" );	ChangeEggLayer( BOTTOM );
	in[9] = LayEgg(); MovePen( 4.82,	16.3+2.5*3	);	DrawBitmap( "button9B.bmp" );	ChangeEggLayer( BOTTOM );

	out[1][0] = LayEgg();	MovePen(14.26,10);				DrawBitmap( "triangle1.bmp" );	ChangeEggLayer( BOTTOM );
	out[2][0] = LayEgg();	MovePen(14.26,11.88);			DrawBitmap( "triangle1.bmp" );	ChangeEggLayer( BOTTOM );
	out[2][1] = LayEgg();	MovePen(14.26,11.25);			DrawBitmap( "triangle2.bmp" );	ChangeEggLayer( BOTTOM );
	out[3][0] = LayEgg();	MovePen(14.26,11.88+INTER);		DrawBitmap( "triangle1.bmp" );	ChangeEggLayer( BOTTOM );
	out[3][1] = LayEgg();	MovePen(14.26,11.28+INTER);		DrawBitmap( "triangle2.bmp" );	ChangeEggLayer( BOTTOM );
	out[4][0] = LayEgg();	MovePen(14.26,11.88+INTER*2);	DrawBitmap( "triangle1.bmp" );	ChangeEggLayer( BOTTOM );
	out[4][1] = LayEgg();	MovePen(14.26,11.25+INTER*2);	DrawBitmap( "triangle2.bmp" );	ChangeEggLayer( BOTTOM );
	out[5][0] = LayEgg();	MovePen(14.26,11.88+INTER*3);	DrawBitmap( "triangle1.bmp" );	ChangeEggLayer( BOTTOM );
	out[5][1] = LayEgg();	MovePen(14.26,11.25+INTER*3);	DrawBitmap( "triangle2.bmp" );	ChangeEggLayer( BOTTOM );
	out[6][0] = LayEgg();	MovePen(14.26,11.88+INTER*4);	DrawBitmap( "triangle1.bmp" );	ChangeEggLayer( BOTTOM );
	out[6][1] = LayEgg();	MovePen(14.26,11.22+INTER*4);	DrawBitmap( "triangle2.bmp" );	ChangeEggLayer( BOTTOM );
	out[7][0] = LayEgg();	MovePen(14.26,11.88+INTER*5);	DrawBitmap( "triangle1.bmp" );	ChangeEggLayer( BOTTOM );
	out[7][1] = LayEgg();	MovePen(14.26,11.18+INTER*5);	DrawBitmap( "triangle2.bmp" );	ChangeEggLayer( BOTTOM );
	out[8][0] = LayEgg();	MovePen(14.26,11.85+INTER*6);	DrawBitmap( "triangle1.bmp" );	ChangeEggLayer( BOTTOM );
	out[8][1] = LayEgg();	MovePen(14.26,11.18+INTER*6);	DrawBitmap( "triangle2.bmp" );	ChangeEggLayer( BOTTOM );
	out[9][1] = LayEgg();	MovePen(14.26,11.35+INTER*7);	DrawBitmap( "triangle2.bmp" );	ChangeEggLayer( BOTTOM );

	showDir(0);
	showFloor(1);
	fprintf( oPtr, "Initialize Finish.\n" );
	drawInfo( "Initialize Finish." );
}


void drawMove( int dir )
{
	int i;
	double start, finish;
	SetActiveEgg( box );
	for( i=1; i<=20; i++ )
	{
			//start = clock();
			//while ( ( ( finish = clock() ) - start )/CLOCKS_PER_SEC < 0.1 );
		Sleep(100);
		SetActiveEgg( box );
		OffsetEgg( 0, 0.0875 * (dir>0?1:-1) );
	}
	SetActiveEgg( smArrow );
	OffsetEgg( 0.05 * (dir>0?1:-1)/1.4*175/5, 0 );

}


void drawInfo( char msg[100] )
{
	SetActiveEgg(tips); 
	EatEgg();
	tips = LayEgg();
	MovePen( 5, 30 );
	DrawString( msg );
}

void drawInRqstLight( int m )
{ 
	SetActiveEgg( in[m>0?m:-m] );
	if ( m > 0 )	ChangeEggLayer( TOP );
	else			ChangeEggLayer( BOTTOM );
}

void drawOutRqstLight( int floor, int dir, int flg )
{
	SetActiveEgg( out[floor][dir!=1] );
	if ( flg == 1 )	ChangeEggLayer( TOP );
	if ( flg ==-1 )	ChangeEggLayer( BOTTOM );
	
}

void showDir( int n )
{
	flr = LayEgg();
	SetActiveEgg( flr );
	switch(n)
	{
		case -1:MovePen(10.35,21.56);	DrawBitmap("dnArrow.bmp");	break;
		case 1:	MovePen(10.35,21.56);	DrawBitmap("upArrow.bmp");	break;
		case 0:	MovePen(10.35,21.56);	DrawBitmap("stop.bmp");		break;
	}   
}

void showFloor( int floor )
{
	char picname[10][15] = { "", "1.bmp","2.bmp","3.bmp","4.bmp","5.bmp","6.bmp",
							"7.bmp","8.bmp","9.bmp" };
	dr = LayEgg();
	SetActiveEgg( dr );
	MovePen(11,23.5);
	DrawBitmap( picname[floor] );
}

void drawExit()
{
	sp = LayEgg();
	MovePen( 8,25 );
	DrawBitmap( "exit.bmp" );
	Sleep(2000);
	EatEgg();
}