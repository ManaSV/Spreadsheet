#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){

	char *string;

	int array[4] = {0,0,0,0} ,  i;

	string = (char *)malloc(sizeof(char)*60); 

	strcpy(string,"(10,20)->(33,44)");
	
	sscanf(string,"(%d,%d)->(%d,%d)",array[i = 0],array[i+=1],array[i+=1],array[i+=1]);
	
	printf("Mover de (%d,%d) Hasta (%d,%d)\n",array[i = 0],array[i+=1],array[i+=1],array[i+=1]);
	
	
	free(string);
	return 0;
}