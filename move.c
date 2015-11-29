#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){

	char* string = malloc( 50 );

	int array[4] = {0,0,0,0};

	strcat(string,"(10,20)->(33,44)");
	printf( "%s\n", string );
	
	sscanf(string,"(%d,%d)->(%d,%d)",&array[0],&array[1],&array[2],&array[3]);
	
	printf("Mover de (%d,%d) Hasta (%d,%d)\n",array[0],array[1],array[2],array[3]);
	
	//Lo que cambie más que nada es el malloc de la string, no hice ningun casteo	
	//tambien cambie strcpy por strcat, que concatena la cadena en lugar de copiarla
	free(string);
	return 0;
}
