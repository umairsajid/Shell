#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

nodo * crearLista()
{
        nodo * lista = NULL;
        return lista;
}


static nodo * crearNodo(const String variable, const String valor)
{
	nodo * tmp = (nodo *) malloc(sizeof(nodo));
	if(tmp != NULL)
	{
        tmp->variable = strdup(variable);
        tmp->valor = strdup(valor);
        tmp->sig = NULL;
	}
	return tmp;
}

nodo * insertarLista(nodo * l, const String variable, const String valor)
{
        nodo * nuevo = crearNodo(variable,valor);
        if (nuevo == NULL)
        {
                printf("Memoria agotada \n");
                exit(EXIT_FAILURE);
        }

        if(l == NULL) //Caso de lista vacía
        {
			l = nuevo;
		}
		else //Caso de lista no vacía, inserta al principio
		{
			nuevo->sig = l;
			l = nuevo;
		}
		return l;
}

void actualizarLista(nodo * n, const String valor)
{
		if(strlen(n->valor) < strlen(valor))
		{
			free(n->valor);
			n->valor = malloc(strlen(valor));
		}
		strcpy(n->valor,valor);
}

nodo * buscarLista(nodo * l, const String variable)
{
		//Sigue mientras no llega al final y no encuentra la cadena buscada
        while(l != NULL && strcmp(l->variable,variable))
        {
                l = l->sig;
        }
        return l;
}

void vaciarLista(nodo * l)
{
        nodo * tmp;
        while (l != NULL)
        {
                tmp = l;
                l = l->sig;
                free(tmp->variable);
                free(tmp->valor);
                free(tmp);
        }
}

void imprimirLista(nodo * l)
{
        while(l != NULL)
        {
                printf("Nombre: %s  :: Valor: %s\n",l->variable,l->valor);
                l = l->sig;
        }
}