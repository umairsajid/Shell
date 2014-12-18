#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <libgen.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <signal.h>
#include "Fork.h"
#include "lista.h"
#define RUNNING 0
#define TERMSIG 1
#define TERMNORM 2
#define STOP 3
#define MAX_PROCESO 1000000
//Función Fork (Crear proceso hijo)
void cmd_fork(){
  pid_t pid = fork();
  if (pid == -1) {
        // ERROR.
    perror("ERROR creación proceso hijo");
  } else if (pid == 0) {
        //PROCESO HIJO.
    printf("Proceso hijo:\n");
  } else {
  //PADRE.
    int status;
    waitpid(pid, &status, 0);
    printf("Finalizando proceso hijo. Volviendo proceso padre:\n");
  }
}

// Priority

void cmd_priority(char *proceso[]){

 pid_t pid=getpid();
 int valor;
 int change=0;

 if (proceso[0]!=NULL){
  pid=(pid_t) atoi(proceso[0]);
  if (proceso[1]!=NULL){
   valor=atoi(proceso[1]);
   change=1;
 }
}
if (valor < -20){
  printf("La prioridad más alta es -20. Cambiando valor a -20\n");
}
if (valor > 19){
  printf("La prioridad más baja es 19. Cambiando valor a 19\n");
}
if(change){
  if(setpriority(PRIO_PROCESS,pid,valor)==-1){
   perror("ERROR, no se puede cambiar la prioridad");
 }
 printf("Mostrando Prioridad de %d :: %d\n",pid,getpriority(PRIO_PROCESS,pid));
}
else
  printf("Mostrando Prioridad de %d :: %d\n",pid,getpriority(PRIO_PROCESS,pid));
}



//Función Exec

void cmd_exec(char *tr[]) {
  if (tr==NULL){
    //execvp(tr[1],&tr[1]);
    perror("Fallo al intentar ejecutar el proceso.\n");
  }
  else  {
    if (tr[1]==NULL){
      execvp(tr[0],&tr[0]);
    }else{
      execvp(tr[1],&tr[1]);
    }
  }
}

//Función Pplano
void cmd_pplano (char *tr[]) {
  pid_t a;
  if ((a=fork())==0) {
    cmd_exec(tr);
    exit(0);
  }
  else {
    waitpid(a,NULL,0);
  } 
}

//Splano

time_t temp(){
  time_t t;
  time(&t);
  return t;
}

void insertarProceso(char * trozos[], pid_t pid, lista l){
  int i;
  procesos procesos;
  procesos.pid=pid;
  procesos.estado=RUNNING;
  procesos.tiempo=temp();
    procesos.sig=25; //Por defecto entendemos que un proceso corriendo tiene señal 25, correspondiente a SIGCONT.
    strcpy (procesos.ejec,"");
    for (i=0; trozos[i]!=NULL;i++)
      strcat(procesos.ejec,trozos[i]); strcat(procesos.ejec," ");
    if (insertarproceso(procesos, &l, ultimo(l))==-1) 
      printf("FATAL ERROR. Memoria agotada\n");
  }

  void cmd_splano(char *tr[],lista l, int createlist){
   pid_t pid;
   int status;
   switch (pid=fork()) {
    case -1:
    perror("Error creando proceso\n"); 
    break;
    case 0:
    cmd_exec(tr);
    exit(0); 
    default:
    if(createlist)insertarProceso(tr,pid,l);
  }
}


//***************//
//*****JOBS*****//
//*************//

void actualizarEstado(pnodo p, lista *l){
  pid_t rc_pid, child_pid;
  int status;
  child_pid=obtenerproceso(p).pid;
  rc_pid = waitpid(child_pid, &status, WUNTRACED|WNOHANG|WCONTINUED);
  if (rc_pid > 0){
    if (WIFCONTINUED(status)){
      p->proceso.estado=RUNNING; p->proceso.sig=25;
      actualizarproceso(p->proceso,p,l);
    }
    if (WIFEXITED(status)){
      p->proceso.estado=TERMNORM; p->proceso.sig=WEXITSTATUS(status);
      actualizarproceso(p->proceso,p,l);
    }
    if (WIFSIGNALED(status)){
      p->proceso.estado=TERMSIG; p->proceso.sig=WTERMSIG(status);
      actualizarproceso(p->proceso,p,l);
    }
    if (WIFSTOPPED(status)){
      p->proceso.estado=STOP; p->proceso.sig=WSTOPSIG(status);
      actualizarproceso(p->proceso,p,l);
    }       
  }       
}

void escribirEstado(int estado){
    if (estado==RUNNING) printf("%15s","RUNNING");
    else if (estado==TERMNORM) printf("%15s", "TERM NORM");
    else if (estado==TERMSIG) printf("%15s","TERM SIG");
    else if (estado==STOP) printf("%15s","STOPPED");
}

void imprimirTodo(lista l){
  pnodo paux;
  procesos procesosAux;
  paux=primero(l);
  while (paux!=NULL){
    actualizarEstado(paux, &l);
    procesosAux=obtenerproceso(paux);
    printf("%d",procesosAux.pid);
    printf("%8d",getpriority(PRIO_PROCESS,procesosAux.pid));
    escribirEstado(procesosAux.estado);
    printf("%10d",procesosAux.sig);
    printf("%20s",procesosAux.ejec);
    printf("%s %s","        ",ctime(&procesosAux.tiempo));
    paux=paux->siguiente;
  }
}

void imprimirTerm(lista l){
  pnodo paux;
  procesos procesosAux;
  paux=primero(l);
  while (paux!=NULL){
    actualizarEstado(paux, &l);
    procesosAux=obtenerproceso(paux);
    if(procesosAux.estado==TERMNORM){
      printf("%d",procesosAux.pid);
      printf("%8d",getpriority(PRIO_PROCESS,procesosAux.pid));
      escribirEstado(procesosAux.estado);
      printf("%10d",procesosAux.sig);
      printf("%20s",procesosAux.ejec);
      printf("%s %s","        ",ctime(&procesosAux.tiempo));
    }
  paux=paux->siguiente;
  }
}

void imprimirSig(lista l){
  pnodo paux;
  procesos procesosAux;
  paux=primero(l);
  while (paux!=NULL){
    actualizarEstado(paux, &l);
    procesosAux=obtenerproceso(paux);
    if(procesosAux.estado==TERMSIG){
      printf("%d",procesosAux.pid);
      printf("%8d",getpriority(PRIO_PROCESS,procesosAux.pid));
      escribirEstado(procesosAux.estado);
      printf("%10d",procesosAux.sig);
      printf("%20s",procesosAux.ejec);
      printf("%s %s","        ",ctime(&procesosAux.tiempo));
    }
  paux=paux->siguiente;
  }
}

void imprimirStop(lista l){
  pnodo paux;
  procesos procesosAux;
  paux=primero(l);
  while (paux!=NULL){
    actualizarEstado(paux, &l);
    procesosAux=obtenerproceso(paux);
    if(procesosAux.estado==STOP){
      printf("%d",procesosAux.pid);
      printf("%8d",getpriority(PRIO_PROCESS,procesosAux.pid));
      escribirEstado(procesosAux.estado);
      printf("%10d",procesosAux.sig);
      printf("%20s",procesosAux.ejec);
      printf("%s %s","        ",ctime(&procesosAux.tiempo));
    }
  paux=paux->siguiente;
  }
}

void imprimirAct(lista l){
  pnodo paux;
  procesos procesosAux;
  paux=primero(l);
  while (paux!=NULL){
    actualizarEstado(paux, &l);
    procesosAux=obtenerproceso(paux);
    if(procesosAux.estado==RUNNING){
      printf("%d",procesosAux.pid);
      printf("%8d",getpriority(PRIO_PROCESS,procesosAux.pid));
      escribirEstado(procesosAux.estado);
      printf("%10d",procesosAux.sig);
      printf("%20s",procesosAux.ejec);
      printf("%s %s","        ",ctime(&procesosAux.tiempo));
    }
  paux=paux->siguiente;
  }
}

void jobsPID(lista l, char tr[]){
  pnodo paux;
  procesos procesosAux;
  paux=buscarproceso(atoi(tr),l);
  if ((paux==NULL)||(obtenerproceso(paux).pid==0)) 
  //Si atoi devuelve un pid viable buscarproceso siempre devolverá NULL. Ahora, si atoi devuelve 0
  //(esto es, al pasarle caracteres en vez números) es precisa otra comprobación.
    printf("Error: PID inválido\n");
  else{
    actualizarEstado(paux, &l);
    procesosAux=obtenerproceso(paux);
    printf("%d",procesosAux.pid);
    printf("%8d",getpriority(PRIO_PROCESS,procesosAux.pid));
    escribirEstado(procesosAux.estado);
    printf("%10d",procesosAux.sig);
    printf("%20s",procesosAux.ejec);
    printf("%s %s","        ",ctime(&procesosAux.tiempo));
  }
}

void jobs(lista l, char tr[], int trozos){
  if(!esListaVacia(l)){
     printf("%s %8s %12s %12s %15s %25s\n","PID", "PRIOR", 
        /****/"STATE", "SIG", "COMMAND", "DATE");
     printf("---------------------------------");
     printf("----------------------------------------------------------\n");
     if (trozos<2) imprimirTodo(l);
     else if ((strcmp(tr, "all")==0)) imprimirTodo(l);
     else if ((strcmp(tr, "term")==0)) imprimirTerm(l);
     else if ((strcmp(tr, "sig")==0)) imprimirSig(l);
     else if ((strcmp(tr, "stop")==0)) imprimirStop(l);
     else if ((strcmp(tr, "act")==0)) imprimirAct(l);
     else jobsPID(l, tr);
  }
}

void clearjobs(lista *l, int createlist){
  pnodo paux, paux2;
  if ((createlist) && (!esListaVacia(*l))){
    paux=primero(*l);
    while (paux!=NULL){
      paux2=paux;
      paux=paux->siguiente;
      actualizarEstado(paux2, l);
      if ((obtenerproceso(paux2).estado==1) || 
      /*****/(obtenerproceso(paux2).estado==2)){
        eliminarproceso(obtenerproceso(paux2).pid, l);
      }
    }
  } 
}
void jobs()
char procesos [MAX_PROCESO]