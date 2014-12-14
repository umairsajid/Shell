#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

int crearLista(lista *l){
	pnodo aux = (pnodo) malloc(sizeof(struct nodo));
	if (aux == NULL) {
		return -1;
	}
	aux->siguiente = NULL;
	*l = aux;
	return 0;
}

int esListaVacia(lista l){
	return (l->siguiente == NULL);
}

pnodo primero(lista l){
	return (l->siguiente);
}

pnodo ultimo(lista l){
	pnodo aux=l;
	while (aux->siguiente != NULL) aux = aux->siguiente;
	return aux;
}

pnodo buscarDato(int n, lista l){
	pnodo aux = l;
	while ((aux != NULL) && (aux->dato.pid != n)) aux = aux->siguiente;
	return aux;
}

data obtenerDato(pnodo p){
	return (p->dato);
}

pnodo anterior(int n, lista l) {
	pnodo pos = l;
	while ((pos->siguiente != NULL) && (pos->siguiente->dato.pid !=n)) 
		pos = pos->siguiente;
	return pos;
}

int eliminarDato(int n, lista *l){
	pnodo aux, aux2 = anterior(n, *l);
	if (aux2 == NULL) {
		return -1;
	}
	aux = aux2->siguiente;
	aux2->siguiente = aux->siguiente;
	free(aux);
	return 0;
}

void vaciarLista (lista *l){
	pnodo aux = primero(*l);
	pnodo aux2;
	while (aux!=NULL) {
		aux2 = aux;
		aux = aux -> siguiente;
		eliminarDato(aux2->dato.pid,l);
	}
}
	
int insertarDato(data n, lista *l, pnodo pos){
	pnodo aux = (pnodo) malloc(sizeof(struct nodo));
	if (aux == NULL) {
		return -1;
	}
	aux->dato = n;
	aux->siguiente = pos->siguiente;
	pos->siguiente=aux;
	return 0;	
}

void actualizarDato (data n, pnodo pos, lista *l){
	pos->dato=n;
}