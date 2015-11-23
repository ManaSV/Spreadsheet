/********************************************************************
 * LIBRERIAS PARA DESGLOSAR MAS EL CONTENIDO DEL PROGRAMA           *
 * FUNCIONES PARA EL ENLACAMIENTO Y RECORRIDO DE LA HOJA DE CALCULO *
 ********************************************************************/

void establecer_fila( struct nodo** cab, int fil, int i, struct nodo* inicio ){
	struct nodo* nuevo = malloc( sizeof( struct nodo ) );
	if( fil ){
		nuevo->dato = malloc( sizeof( int ) );
		*((int*)nuevo->dato) = i + 1;
		nuevo->fila = i + 1;
		nuevo->flag = NUMERO;
		(*cab)->abajo = nuevo;
		(*cab)->abajo->derecha = (*cab)->abajo;
		establecer_fila( &(*cab)->abajo, fil - 1, i + 1, inicio );
	}
	if( !(*cab)->abajo )
		(*cab)->abajo = inicio;
}

void establecer_columna( struct nodo** cab, int col, int j, struct nodo* inicio ){
	struct nodo* nuevo = malloc( sizeof( struct nodo ) );
	if( col ){
		nuevo->dato = malloc( sizeof( char ) );
		*((char*)nuevo->dato) = 'A' + j;
		nuevo->columna = 'A' + j;
		nuevo->flag = LETRA;
		(*cab)->derecha = nuevo;
		(*cab)->derecha->abajo = (*cab)->derecha;
		establecer_columna( &(*cab)->derecha, col - 1, j + 1, inicio );
	}
	if( !(*cab)->derecha )
		(*cab)->derecha = inicio;	
}

void insertar_columna( char col, struct nodo** cab, struct nodo* inicio, struct nodo** nuevo ){
	if( (*cab)->columna < col ){
		insertar_columna( col, &(*cab)->derecha, inicio->derecha, nuevo );
	}else if( (*cab)->abajo != inicio ){
		if( (*nuevo)->fila < (*cab)->abajo->fila ){
			struct nodo* aux = malloc( sizeof( struct nodo ) );
			aux = (*cab)->abajo;
			(*cab)->abajo = *nuevo;
			(*nuevo)->abajo = aux;
		}else
			insertar_columna( col, &(*cab)->abajo, inicio, nuevo );
	}else{
		(*cab)->abajo = *nuevo;
		(*nuevo)->abajo = inicio;
	}
}

void insertar_fila( int fil, struct nodo** cab, struct nodo* inicio, struct nodo** nuevo ){
	if( (*cab)->fila < fil ){
		insertar_fila( fil, &(*cab)->abajo, inicio->abajo, nuevo );
	}else if( (*cab)->derecha != inicio ){
		if( (*nuevo)->columna < (*cab)->derecha->columna ){
			struct nodo* aux = malloc( sizeof( struct nodo ) );
			aux = (*cab)->derecha;
			(*cab)->derecha = *nuevo;
			(*nuevo)->derecha = aux;
		}else{
			insertar_fila( fil, &(*cab)->derecha, inicio, nuevo );
		}
	}else{
		(*cab)->derecha = *nuevo;
		(*nuevo)->derecha = inicio;
	}
}

int encontrar_columna( char col, int fil, struct nodo** cab, struct nodo* inicio ){
	if( (*cab)->columna < col ){
		encontrar_columna( col, fil, &(*cab)->derecha, inicio->derecha  );
	}else{ 
		if( (*cab)->fila < fil ){
			if( (*cab)->abajo == inicio )
				return 0;
			else
				encontrar_columna( col, fil, &(*cab)->abajo, inicio );
		}else
			return 1;
	}
}

void borrar_fila( char col, int fil, struct nodo** cab, struct nodo* inicio ){
	if( (*cab)->fila < fil )
		borrar_fila( col, fil, &(*cab)->abajo, inicio->abajo );
	else if( (*cab)->derecha != inicio ){
		if( (*cab)->derecha->columna < col )
			borrar_fila( col, fil, &(*cab)->derecha, inicio );
		else{
			struct nodo* aux = (*cab)->derecha->derecha;
			(*cab)->derecha->derecha = NULL;
			(*cab)->derecha = aux;
		}
	}else if( (*cab)->derecha->columna == col && (*cab)->derecha->fila == fil ){
		(*cab)->derecha->derecha = NULL;
		(*cab)->derecha = inicio;
	}
}

void borrar_columna( char col, int fil, struct nodo** cab, struct nodo* inicio ){
	if( (*cab)->columna < col )
		borrar_columna( col, fil, &(*cab)->derecha, inicio->derecha );
	else if( (*cab)->abajo != inicio ){
		if( (*cab)->abajo->fila < fil )
			borrar_columna( col, fil, &(*cab)->abajo, inicio );
		else{
			struct nodo* aux = (*cab)->abajo->abajo;
			(*cab)->abajo->abajo = NULL;
			(*cab)->abajo = aux;
		}
	}else if( (*cab)->abajo->columna == col && (*cab)->abajo->fila == fil ){
		(*cab)->abajo->abajo = NULL;
		(*cab)->abajo = inicio;
	}
}

struct nodo* retornar_columna( char col, int fil, struct nodo** cab, struct nodo* inicio ){
	if( (*cab)->columna < col ){
		retornar_columna( col, fil, &(*cab)->derecha, inicio->derecha  );
	}else{ 
		if( (*cab)->fila < fil ){
			if( (*cab)->abajo == inicio )
				return NULL;
			else
				retornar_columna( col, fil, &(*cab)->abajo, inicio );
		}else
			return (*cab);
	}
}

struct nodo* retornar_fila( char col, int fil, struct nodo** cab, struct nodo* inicio ){
	if( (*cab)->fila < fil ){
		retornar_fila( col, fil, &(*cab)->abajo, inicio->abajo  );
	}else{ 
		if( (*cab)->columna < col ){
			if( (*cab)->derecha == inicio )
				return NULL;
			else
				retornar_fila( col, fil, &(*cab)->derecha, inicio );
		}else
			return (*cab);
	}
}

