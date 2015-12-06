//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

int command_parser( char* string, int* array );

//int main(int argc, char const *argv[]){
//
//	char* string = malloc( 50 );
//
//
//	strcat(string,"10,20:11,34->33,44:21,x");
//	int* array = malloc( sizeof( int ) * 8 );
//	if( command_parser( string, array ) == 4 )
//		printf("Mover de (%d,%d) Hasta (%d,%d)\n",array[0],array[1],array[2],array[3]);
//	else if( command_parser( string, array ) == 8 )
//		printf( "Movimiento en rangos\n" );
//	else
//		printf( "Formato equivocado\n" );
//	
//	//Lo que cambie más que nada es el malloc de la string, no hice ningun casteo	
//	//tambien cambie strcpy por strcat, que concatena la cadena en lugar de copiarla
//	free(string);
//	return 0;
//}

int command_parser( char* string, int* array ){
	if( sscanf( string, "%d,%d:%d,%d->%d,%d:%d,%d", &array[0], &array[1], 
		&array[2] ,&array[3], &array[4], &array[5], &array[6], &array[7] ) == 8 )
		return 8;
	else if( sscanf(string,"%d,%d->%d,%d",&array[0],&array[1],&array[2],&array[3]) == 4)
		return 4;
	else if( sscanf( string, "cp %d,%d %d,%d", &array[0],&array[1],&array[2],&array[3] ) == 4 )
		return 5;
	else if( sscanf( string, "cp %d,%d:%d,%d %d,%d:%d,%d",  &array[0], &array[1], 
		&array[2] ,&array[3], &array[4], &array[5], &array[6], &array[7]) == 8 )
		return 6;
	else if( sscanf( string, "rm %d,%d", &array[0], &array[1] ) == 2 )
		return 2;
	else if( sscanf( string, "sum %d,%d:%d,%d->%d,%d", &array[0], &array[1], &array[2], &array[3], &array[4], &array[5] ) == 6 )
		return 1;
	else if( sscanf( string, "prom %d,%d:%d,%d->%d,%d", &array[0], &array[1], &array[2], &array[3], &array[4], &array[5] ) == 6 )
		return 3;
	return 0;
}
