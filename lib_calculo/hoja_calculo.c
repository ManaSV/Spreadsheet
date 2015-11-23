#include <stdio.h>
#include <stdlib.h>
#include "structures.c"
#include "support.c"

int menu();
struct nodo* crear_celda();
void establecer_hoja( struct nodo** cab, int fil, int col, int i, int j, struct nodo* inicio );
void insertar_celda( char col, int fil, struct nodo** cab, struct nodo* inicio );
void borrar_celda( char col, int fil, struct nodo** cab, struct nodo* inicio );
void intercambiar_celdas( struct nodo** cab1, struct nodo** cab2, struct nodo* init );
void mostrar_hoja( struct nodo** cab, struct nodo* iniciox, struct nodo* inicioy, char cont );

int main( void ){
	int flag = 0; int exit = 0;
	int x, y;
	struct nodo* hoja1 = malloc( sizeof( struct nodo ) );
	hoja1->dato = malloc( sizeof( int ) );
	*((int*)hoja1->dato) = 0;
	while( !exit ){
		switch( menu() ){
			case 0:
				exit = 1;
				break;
			case 1:
				if( !flag ){
					printf( "QUE DIMENSIONES DESEA SU HOJA ?(X): " );
					scanf("%d", &x ); getchar();
					printf( "(Y): " ); scanf( "%d", &y ); getchar();
					establecer_hoja( &hoja1, y, x, 0, 0, hoja1 );
					printf( "\n\n\n" );
					mostrar_hoja( &hoja1, hoja1, hoja1, 'A' );
					flag = 1;
				}else
					printf("SU HOJA YA ESTA ESTABLECIDA!\n");
				break;
			case 2:
				if( flag )
					mostrar_hoja( &hoja1, hoja1, hoja1, 'A' );
				else
					printf( "TIENE QUE ESTABLECER HOJA ANTES\n" );
				break;
			case 3:
				if( flag ){
					char col; int fil;
					do{
						printf( "EN QUE COLUMNA? : ");
						scanf( "%c", &col ); getchar();
						printf( "EN QUE FILA?: " );
						scanf( "%d", &fil ); getchar();
					}while( col > x + 64 ||  fil > y - 1 );
					insertar_celda( col, fil + 1, &hoja1, hoja1 );
					mostrar_hoja( &hoja1, hoja1, hoja1, 'A' );
				}else
					printf( "TIENE QUE ESTABLECER HOJA ANTES\n" );
				break;
			case 4:
				if( flag ){
					char col; int fil;
					do{
						printf( "EN QUE COLUMNA? : " );
						scanf( "%c", &col ); getchar();
						printf( "EN QUE FILA?: " );
						scanf( "%d", &fil ); getchar();
					}while( col > x + 64 || fil > y - 1 );
					borrar_celda( col, fil + 1, &hoja1, hoja1 );
					mostrar_hoja( &hoja1, hoja1, hoja1, 'A' );
				}else
					printf( "TIENE QUE ESTABLECER HOJA ANTES\n" );
				break;
			case 5:
				if( flag ){
					intercambiar_celdas( &hoja1, &hoja1, hoja1 );
					mostrar_hoja( &hoja1, hoja1, hoja1, 'A' );
				}else
					printf( "TIENE QUE ESTABLECER HOJA ANTES\n" );
				break;
		}
	}
	return 0;
}

int menu(){
	int opt;
	printf( "--MENU--\n" );
	do{
		printf( "\t1. ESTABLECER HOJA\n" );
		printf( "\t2. MOSTRAR HOJA\n" );
		printf( "\t3. INSERTAR CELDA\n" );
		printf( "\t4. BORRAR CELDA\n" );
		printf( "\t5. INTERCAMBIAR CELDAS\n" );
		printf( "\t0. SALIR\n" );
		printf( ":" );
		scanf( "%d", &opt );
		getchar();
	}while( opt > 5 || opt < 0 );
	return opt;
}

struct nodo* crear_celda(){
	int flag_01; //Se puede tomar como entero y usar en el switch como enum
	struct nodo* nuevo = malloc( sizeof( struct nodo ) );
	printf( "Que tipo de dato desea ingresar? :" );
	printf( "\n\t0.Numero, 1.Letra, 2.Float\n" );
	scanf( "%d", &flag_01 );
	switch( flag_01 ){
		case NUMERO:
			nuevo->dato = malloc( sizeof(int) );
			printf( "Ingrese su numero: " );
			scanf( "%d", (int*)nuevo->dato );
			nuevo->flag = NUMERO;
			break;
		case LETRA:
			nuevo->dato = malloc( 1 );
			getchar();
			printf( "Ingrese una letra: " );
			scanf( "%c", (char*)nuevo->dato );
			nuevo->flag = LETRA;
			break;
		case FLOAT:
			nuevo->dato = malloc( sizeof( float ) );
			printf( "Ingrese numeros con decimal: " );
			scanf( "%f", (float*)nuevo->dato );
			nuevo->flag = FLOAT;
			break;
		default:
			printf( "Opcion no valida!\n" );
			nuevo = crear_celda();
	}
	return nuevo;
}

void establecer_hoja( struct nodo** cab, int fil, int col, int i, int j, struct nodo* inicio ){
	establecer_columna( cab, col, j, inicio );
	establecer_fila( cab, fil, i, inicio );
}

void insertar_celda( char col, int fil, struct nodo** cab, struct nodo* inicio ){
	struct nodo* nuevo = crear_celda();
	nuevo->columna = col;
	nuevo->fila = fil;
	insertar_fila( fil, &(*cab)->abajo, inicio->abajo, &nuevo );
	insertar_columna( col, &(*cab)->derecha, inicio->derecha, &nuevo );
}

void borrar_celda( char col, int fil, struct nodo** cab, struct nodo* inicio ){
	if( encontrar_columna( col, fil, cab, *cab )  ){
		borrar_fila( col, fil, &(*cab)->abajo, inicio );
		borrar_columna( col, fil, &(*cab)->derecha, inicio );
	}else
		printf( "La celda seleccionada no tiene ningun contenido\n" );
}

void intercambiar_celdas( struct nodo** cab1, struct nodo** cab2, struct nodo* init ){
	char col1, col2;
	int fil1, fil2;
	struct nodo *aux, *aux2;
	do{
		printf("(CELDA 1) EN QUE COLUMNA? : ");
		scanf( "%c", &col1 );
		getchar();
		printf("(CELDA 1) EN QUE FILA? : ");
		scanf( "%d", &fil1 );
		getchar();
	}while( !encontrar_columna( col1, fil1 + 1, cab1, *cab1 ) );
	fil1++; //para poder ingresar 0, el programa toma 1 como la fila 0
	//razon de este bug desconocida
	do{
		printf("(CELDA 2) EN QUE COLUMNA? : ");
		scanf( "%c", &col2 );
		getchar();
		printf("(CELDA 2) EN QUE FILA? : ");
		scanf( "%d", &fil2 );
		getchar();
	}while( !encontrar_columna( col2, fil2 + 1, cab2, *cab2 ) );
	fil2++;
	if( col1 == col2 && fil1 == fil2 )
		return;
	aux = retornar_columna( col1, fil1, cab1, *cab1 );
	borrar_celda( col1, fil1, cab1, init );
	aux->columna = col2;
	aux->fila = fil2;
	aux2 = retornar_columna( col2, fil2, cab1, *cab1 );
	borrar_celda( col2, fil2, cab2, init );
	aux2->columna = col1;
	aux2->fila = fil1;
	insertar_columna( col2, &(*cab1)->derecha, init->derecha, &aux );
	insertar_fila( fil2, &(*cab1)->abajo, init->abajo, &aux );
	insertar_columna( col1, &(*cab2)->derecha, init->derecha, &aux2 );
	insertar_fila( fil1, &(*cab2)->abajo, init->abajo, &aux2 );
}

void mostrar_hoja( struct nodo** cab, struct nodo* iniciox, struct nodo* inicioy, char cont ){
	if( (*cab)->fila== 0 && (*cab)->columna == 0 )
		printf("%5s|", "");
	for( char aux = cont; cont < (*cab)->derecha->columna; cont++ )
		printf( "%5s|","" );
	if( (*cab)->derecha != iniciox ){
		switch( (*cab)->derecha->flag ){
			case NUMERO:
				printf( "%4d |", *((int*)(*cab)->derecha->dato) );
				break;
			case LETRA:
				printf( "%4c |", *((char*)(*cab)->derecha->dato) );
				break;
			case FLOAT:
				printf( "%4.2f |", *((float*)(*cab)->derecha->dato) );
				break;
		}
		mostrar_hoja( &(*cab)->derecha, iniciox, inicioy, cont + 1 );
	}else if( (*cab)->derecha->abajo != inicioy ){
		printf( "\n ----\n|%3d |", *((int*)(*cab)->derecha->dato) );
		mostrar_hoja( &(*cab)->derecha->abajo, iniciox->abajo, inicioy, 'A' );
	}else{
		printf( "\n\n" );
	}
}
