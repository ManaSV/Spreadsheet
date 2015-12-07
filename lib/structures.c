typedef enum{ NUMERO, LETRA, FLOAT }tipo_dato;

struct nodo{
	char* dato;
	char columna;
	int fila;
	struct nodo* derecha;
	struct nodo* abajo;
};
