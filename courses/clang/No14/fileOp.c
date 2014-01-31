#include <stdio.h>
#include <string.h>
typedef struct information
{
        int index;
        char name[50];
        int quantity;
        float price; 
}INFO;

void showMenu();
void initialize( FILE * );
void showList( FILE * );
void deleteRecord( FILE * );
void updateRecord( FILE * );

int main( int argc, char ** argv )
{
        FILE *cfPtr;
	char cmd;
	
	if ( ( cfPtr = fopen( "commodity.dat", "w+" ) ) == NULL )
		printf( "file could not be opened." );
	else
	{
		initialize( cfPtr );
		showMenu();
		
		printf( "\ncmd: " );
		cmd = getchar(); 
		while ( cmd != '4' )
		{
			switch ( cmd )
			{
				case '1':	
					showList( cfPtr );
					break;
				case '2': 
					updateRecord( cfPtr );
					break;
				case '3':
					deleteRecord( cfPtr );
					break;
				default:
					puts ( "bad command, please input a valid command." );
			}
			printf( "\ncmd: " );
			fflush( stdin );
			cmd = getchar(); 
		}
	}
	
	fclose( cfPtr );
	system( "pause" );
	return 0;
}
void showMenu()
{
	puts( "\t========MENU========" );
	puts( "\t1) show List;" );
	puts( "\t2) update record;" );
	puts( "\t3) delete empty record;" );
	puts( "\t4) exit." );	
	
	return;
}

void initialize( FILE *cfPtr )
{
	INFO info = { 0, 0, 0, 0 };
	int i = 0;

	for ( i=0; i < 100; i ++ )
	{
		fseek( cfPtr, i*sizeof( INFO ), SEEK_SET );
		fwrite( &info, sizeof( INFO ), 1, cfPtr );	
	}	

	info.index = 5; strcpy( info.name, "Lamp" ); info.quantity = 23; info.price = 5.99;
	fseek( cfPtr, (5-1)*sizeof( INFO ), SEEK_SET );
	fwrite( &info, sizeof( INFO ), 1, cfPtr );
	
	info.index = 8; strcpy( info.name, "Screwdriver" ); info.quantity = 9; info.price = 7.99;
	fseek( cfPtr, (8-1)*sizeof( INFO ), SEEK_SET );
	fwrite( &info, sizeof( INFO ), 1, cfPtr );

	info.index = 10; strcpy( info.name, "Hammer" ); info.quantity = 10; info.price = 12.00;
	fseek( cfPtr, (10-1)*sizeof( INFO ), SEEK_SET );
	fwrite( &info, sizeof( INFO ), 1, cfPtr );
	
	info.index = 13; strcpy( info.name, "Bicycle" ); info.quantity = 5; info.price = 100.99;
	fseek( cfPtr, (13-1)*sizeof( INFO ), SEEK_SET );
	fwrite( &info, sizeof( INFO ), 1, cfPtr );
	
	info.index = 16; strcpy( info.name, "Optical mouse" ); info.quantity = 21; info.price = 11.50;
	fseek( cfPtr, (16-1)*sizeof( INFO ), SEEK_SET );
	fwrite( &info, sizeof( INFO ), 1, cfPtr );
	
	info.index = 23; strcpy( info.name, "keyboard" ); info.quantity = 32; info.price = 55.99;
	fseek( cfPtr, (16-1)*sizeof( INFO ), SEEK_SET );
	fwrite( &info, sizeof( INFO ), 1, cfPtr );
	
	return;	
}

void showList( FILE *cfPtr )
{
	int i = 0;
	INFO info;
	
	printf( "%-8s%-16s%-8s%-8s\n", "记录号", "商品名", "数量", "价格" ); 
	for ( i=0; i < 100; i ++ )
	{
		fseek( cfPtr, i*sizeof( INFO ), SEEK_SET );
		fread( &info, sizeof( INFO ), 1, cfPtr);
		if ( info.quantity != 0 )
			printf( "%-8d%-16s%-8d%-8.2f\n",
				 info.index, info.name, info.quantity, info.price );
	}	

	return;
}

void deleteRecord( FILE *cfPtr )
{
	int n = 0;
	INFO info, blankInfo = { 0, 0, 0, 0 };
	
	printf( "Enter the index to delete(1-100):" );
	scanf( "%d", &n );
	if ( n < 1 || n > 100 )
		puts( "The index is out of range." );
	else
	{
		fseek( cfPtr, (n-1)*sizeof( INFO ), SEEK_SET );
		fread( &info, sizeof( INFO ), 1, cfPtr );
		if ( info.quantity != 0 )
			printf( "quantity is not zero, cannot be delete.\n" );
		else
		{
			fseek( cfPtr, (n-1)*sizeof( INFO ), SEEK_SET );
			fwrite( &blankInfo, sizeof( INFO ), 1, cfPtr );
		}
	}		
}

void updateRecord( FILE * cfPtr )
{
	int index = 0;
	INFO info;
	
	printf( "Enter the index to update(1-100):" );	
	scanf( "%d", &index );
	if ( index < 1 || index > 100 )
		puts( "The index is out of range." );
	else
	{
		fseek( cfPtr, (index-1)*sizeof( INFO ), SEEK_SET );
		fread( &info, sizeof( INFO ), 1, cfPtr );
		
		if ( info.index == 0 )
			printf( "Record %d is empty.\n", index );
		else
		{
			printf( "Enter the new quantity:" );
			scanf( "%d", &info.quantity );
			fseek( cfPtr, (index-1)*sizeof( INFO ), SEEK_SET );
			fwrite( &info, sizeof( INFO ), 1, cfPtr );		
		}
	}
	
	return;
}
