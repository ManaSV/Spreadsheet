//se haran cambios dentro de este programa para poder utilizarlo en
//la hoja de calculo con interfaz grafica.
#include <stdio.h>
#include <stdlib.h>
#include "structures.c"
#include "support.c"

//int menu();
//struct nodo* crear_celda();
//void establecer_hoja( struct nodo** cab, int fil, int col, int i, int j, struct nodo* inicio );
//void insertar_celda( char col, int fil, struct nodo** cab, struct nodo* inicio );
//void borrar_celda( char col, int fil, struct nodo** cab, struct nodo* inicio );
//void intercambiar_celdas( struct nodo** cab1, struct nodo** cab2, struct nodo* init );
//void mostrar_hoja( struct nodo** cab, struct nodo* iniciox, struct nodo* inicioy, char cont );

//int main( void ){
//	int flag = 0; int exit = 0;
//	int x, y;
//	struct nodo* hoja1 = malloc( sizeof( struct nodo ) );
//	hoja1->dato = malloc( sizeof( int ) );
//	*((int*)hoja1->dato) = 0;
//	while( !exit ){
//		switch( menu() ){
//			case 0:
//				exit = 1;
//				break;
//			case 1:
//				if( !flag ){
//					printf( "QUE DIMENSIONES DESEA SU HOJA ?(X): " );
//					scanf("%d", &x ); getchar();
//					printf( "(Y): " ); scanf( "%d", &y ); getchar();
//					establecer_hoja( &hoja1, y, x, 0, 0, hoja1 );
//					printf( "\n\n\n" );
//					mostrar_hoja( &hoja1, hoja1, hoja1, 'A' );
//					flag = 1;
//				}else
//					printf("SU HOJA YA ESTA ESTABLECIDA!\n");
//				break;
//			case 2:
//				if( flag )
//					mostrar_hoja( &hoja1, hoja1, hoja1, 'A' );
//				else
//					printf( "TIENE QUE ESTABLECER HOJA ANTES\n" );
//				break;
//			case 3:
//				if( flag ){
//					char col; int fil;
//					do{
//						printf( "EN QUE COLUMNA? : ");
//						scanf( "%c", &col ); getchar();
//						printf( "EN QUE FILA?: " );
//						scanf( "%d", &fil ); getchar();
//					}while( col > x + 64 ||  fil > y - 1 );
//					insertar_celda( col, fil + 1, &hoja1, hoja1 );
//					mostrar_hoja( &hoja1, hoja1, hoja1, 'A' );
//				}else
//					printf( "TIENE QUE ESTABLECER HOJA ANTES\n" );
//				break;
//			case 4:
//				if( flag ){
//					char col; int fil;
//					do{
//						printf( "EN QUE COLUMNA? : " );
//						scanf( "%c", &col ); getchar();
//						printf( "EN QUE FILA?: " );
//						scanf( "%d", &fil ); getchar();
//					}while( col > x + 64 || fil > y - 1 );
//					borrar_celda( col, fil + 1, &hoja1, hoja1 );
//					mostrar_hoja( &hoja1, hoja1, hoja1, 'A' );
//				}else
//					printf( "TIENE QUE ESTABLECER HOJA ANTES\n" );
//				break;
//			case 5:
//				if( flag ){
//					intercambiar_celdas( &hoja1, &hoja1, hoja1 );
//					mostrar_hoja( &hoja1, hoja1, hoja1, 'A' );
//				}else
//					printf( "TIENE QUE ESTABLECER HOJA ANTES\n" );
//				break;
//		}
//	}
//	return 0;
//}

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

struct nodo* crear_celda( char* data_string ){
	struct nodo* nuevo = malloc( sizeof( struct nodo ) );
	nuevo->dato = malloc( MAX );
	nuevo->dato = data_string;
	return nuevo;
}

void establecer_hoja( struct nodo** cab, int fil, int col, int i, int j, struct nodo* inicio ){
	establecer_columna( cab, col, j, inicio );
	establecer_fila( cab, fil, i, inicio );
}

void insertar_celda( char col, int fil, struct nodo** cab, struct nodo* inicio, char* data_string ){
	struct nodo* nuevo = crear_celda( data_string );
	nuevo->columna = col;
	nuevo->fila = fil;
	insertar_fila( fil, &(*cab)->abajo, inicio->abajo, &nuevo );
	insertar_columna( col, &(*cab)->derecha, inicio->derecha, &nuevo );
}

void borrar_celda( char col, int fil, struct nodo** cab, struct nodo* inicio ){
	if( encontrar_celda( col, fil, cab, inicio ) ){
		borrar_fila( col, fil, &(*cab)->abajo, inicio );
		borrar_columna( col, fil, &(*cab)->derecha, inicio );
	}else
		printf( "La celda seleccionada no tiene ningun contenido\n" );
}

void intercambiar_celdas( struct nodo** cab1, struct nodo** cab2, struct nodo* init, int x1, int y1, int x2, int y2 ){
	struct nodo *aux, *aux2;
	if( !encontrar_fila( 'A' + x1, y1 + 1, cab1, *cab1 ) )
		exit(1);
	y1++; //para poder ingresar 0, el programa toma 1 como la fila 0
	//razon de este bug desconocida
	if( !encontrar_fila( 'A' + x1, y2 + 1, cab2, *cab2 ) )
		exit(1);
	y2++;
	if( x1 == x2 && y1 == y2 )
		return;
	aux = retornar_columna( x1, y1, cab1, *cab1 );
	borrar_celda( x1, y1, cab1, init );
	aux->columna = x2 + 'A';
	aux->fila = y2;
	aux2 = retornar_columna( 'A' + x2, y2, cab1, *cab1 );
	borrar_celda( 'A' + x2, y2, cab2, init );
	aux2->columna = x1 + 'A';
	aux2->fila = y1;
	insertar_columna( x2 + 'A', &(*cab1)->derecha, init->derecha, &aux );
	insertar_fila( y2, &(*cab1)->abajo, init->abajo, &aux );
	insertar_columna( x1 + 'A', &(*cab2)->derecha, init->derecha, &aux2 );
	insertar_fila( y1, &(*cab2)->abajo, init->abajo, &aux2 );
}

void mostrar_hoja( struct nodo** cab, struct nodo* iniciox, struct nodo* inicioy, char cont ){
	if( (*cab)->fila == 0 && (*cab)->columna == 0 )
		printf("%5s|", "");
	for( /*empty*/;cont < (*cab)->derecha->columna; cont++ )
		printf( "%7s|","" );
	if( (*cab)->derecha != iniciox ){
		printf( "%7s|", (*cab)->derecha->dato );
		mostrar_hoja( &(*cab)->derecha, iniciox, inicioy, cont + 1 );
	}else if( (*cab)->derecha->abajo != inicioy ){
		printf( "\n ----\n|%3s |", (*cab)->derecha->dato );
		mostrar_hoja( &(*cab)->derecha->abajo, iniciox->abajo, inicioy, 'A' );
	}else{
		printf( "\n\n" );
	}
}
