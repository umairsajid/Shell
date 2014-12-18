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

pnodo buscarproceso(int n, lista l){
	pnodo aux = l;
	while ((aux != NULL) && (aux->proceso.pid != n)) aux = aux->siguiente;
	return aux;
}

procesos obtenerproceso(pnodo p){
	return (p->proceso);
}

pnodo anterior(int n, lista l) {
	pnodo pos = l;
	while ((pos->siguiente != NULL) && (pos->siguiente->proceso.pid !=n)) 
		pos = pos->siguiente;
	return pos;
}

int eliminarproceso(int n, lista *l){
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
		eliminarproceso(aux2->proceso.pid,l);
	}
}
	
int insertarproceso(procesos n, lista *l, pnodo pos){
	pnodo aux = (pnodo) malloc(sizeof(struct nodo));
	if (aux == NULL) {
		return -1;
	}
	aux->proceso = n;
	aux->siguiente = pos->siguiente;
	pos->siguiente=aux;
	return 0;	
}

void actualizarproceso (procesos n, pnodo pos, lista *l){
	pos->proceso=n;
}