#ifndef LISTA_H
#define LISTA_H

struct tnodo {
	char *variable;
	char *valor;
	struct tnodo *sig;
};

typedef char * String;
typedef struct tnodo nodo;

nodo * crearLista(); // Inicializa a NULL
nodo * insertarLista(nodo * l, const String variable, const String valor);
void actualizarLista(nodo * n, const String valor);
nodo * buscarLista(nodo * l, const String variable); // Se non atopa o elemento, devolve NULL
void vaciarLista(nodo * l); // Libera a memoria
void imprimirLista(nodo * l);

#endif