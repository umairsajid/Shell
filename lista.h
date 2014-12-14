#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#ifndef LISTA_PROC
#define LISTA_PROC
#define MAX_ENTRADA 4096
#define MAXPATH 500
#define RUNNING 0
#define TERMSIG 1
#define TERMNORM 2
#define STOP 3
 
typedef struct data {
	pid_t pid;
	int estado;
	
	time_t tiempo;
	char ejec[MAXPATH];
} data;
 
struct nodo {
	data dato;
	struct nodo * siguiente;
};
typedef struct nodo *pnodo;
typedef pnodo lista;
 
int crearLista(lista *);
int esListaVacia(lista);
pnodo primero(lista);
pnodo ultimo(lista);
pnodo buscarDato(int, lista);
data obtenerDato(pnodo);
pnodo anterior(int, lista);
int eliminarDato(int, lista *);
void vaciarLista (lista *);
int insertarDato(data, lista*, pnodo);
void actualizarDato (data, pnodo, lista *);

#endif

