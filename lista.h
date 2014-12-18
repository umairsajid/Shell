#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#ifndef LISTA_PROC
#define LISTA_PROC
#define MAX_ENTRADA 4096

 
typedef struct procesos {
	pid_t pid;
	int estado;
	int sig;
	
	time_t tiempo;
	char ejec[MAX_ENTRADA];
} procesos;
 
struct nodo {
	procesos proceso;
	struct nodo * siguiente;
};
typedef struct nodo *pnodo;
typedef pnodo lista;
 
int crearLista(lista *);
int esListaVacia(lista);
pnodo primero(lista);
pnodo ultimo(lista);
pnodo buscarproceso(int, lista);
procesos obtenerproceso(pnodo);
pnodo anterior(int, lista);
int eliminarproceso(int, lista *);
void vaciarLista (lista *);
int insertarproceso(procesos, lista*, pnodo);
void actualizarproceso (procesos, pnodo, lista *);

#endif

