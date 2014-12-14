#ifndef LISTA 
#ifndef MAX_ENTRADA
#define MAX_ENTRADA 4096
#define LISTA
#include <sys/types.h>
#include <sys/wait.h>
 
#define ACT 1
#define TERM 2
#define SIG 4
#define STOP 8
#define ESTADOS |ACT|TERM|SIG|STOP
 
typedef struct procesos {
    pid_t pid;
    int prioridad;
    char comando[100];
    char inicio[20];
    int estado;
    int senial;
} nodoprocesos;
 
struct nodo {
    struct procesos proceso;
    struct nodo *siguiente;
};
 
typedef struct nodo *pnodo;
typedef pnodo lista;
 
pnodo crear_lista();
int lista_vacia(lista l);
pnodo buscar(pid_t pid, lista pnodo);
int ultimo_elemento(pnodo p);
pnodo buscar_anterior(pnodo np, lista l);
pnodo eliminar(pnodo np, lista l);
pnodo insertar_l(nodoprocesos proc, pnodo p);
/* ERRORES: eliminar un elemento que no esta en la lista */
#endif
#endif