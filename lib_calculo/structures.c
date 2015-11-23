typedef enum{ NUMERO, LETRA, FLOAT }tipo_dato;

struct nodo{
	void* dato;
	char columna;
	int fila;
	struct nodo* derecha;
	struct nodo* abajo;
	int flag;
};
