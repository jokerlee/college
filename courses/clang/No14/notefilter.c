#include <stdio.h>
void noteFilter1( FILE *, FILE * );
void noteFilter2( FILE *, FILE * );
int main( int argc, char ** argv )
{
        char oFile[100];
        char rFile[100];
	FILE *sfPtr;
        FILE *cfPtr;
        
        puts( "������Դ�ļ�·����" );
        gets( oFile );
        puts( "�����봦����ļ�·����" );
        gets( rFile );
        
        if ( ( sfPtr = fopen( oFile, "r" ) ) == NULL )
                printf ( "File could not be opened." );
        else
        {
                if ( ( cfPtr = fopen( rFile, "w" ) ) == NULL )
                        printf ( "File could not be opened." );
                else
                {
                        char charr = fgetc(  sfPtr );
                        while ( !feof( sfPtr ) )
                        {
                                if ( charr == '/' )
                                {
                                        charr = fgetc( sfPtr );
                                        if ( charr == '/')
                                                noteFilter1( sfPtr, cfPtr );
                                        else if ( charr == '*' )
                                                noteFilter2( sfPtr, cfPtr );
                                        else
                                        {
                                                charr = fgetc( sfPtr );
                                                //fputc( '/', cfPtr );
                                                continue;
                                        }
                                }
                                else
                                        fputc ( charr, cfPtr );
                                charr = fgetc( sfPtr );
                        }
                }
        }
        printf ( "\nEnd of run.\n" );
        fclose( sfPtr );
        fclose( cfPtr );
        
        system ( "pause" );
        return 0;
        
}

void noteFilter1( FILE * sfPtr, FILE * cfPtr )
{
        char charr = fgetc( sfPtr );
        while ( !feof( sfPtr ) && charr != '\n' )
               charr = fgetc( sfPtr ); 
        fputc( '\n', cfPtr );
        return;
}

void noteFilter2( FILE * sfPtr, FILE * cfPtr )
{
        char charr = fgetc( sfPtr );
        while ( !feof( sfPtr ) )
        {
                if ( charr == '*' || charr == '/')
                {
                        if ( charr == '*' && ( charr = fgetc( sfPtr ) ) == '/' )
                                return;
                        else if ( charr == '/' && ( charr = fgetc( sfPtr ) ) == '*' )
                                noteFilter2( sfPtr, cfPtr ); 
                }     
                charr = fgetc( sfPtr );
        }
}
