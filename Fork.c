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
#include "Fork.h"
#include "lista.h"

//Función Fork
void cmd_fork(){
  pid_t pid = fork();
    if (pid == -1) {
        // ERROR.
          perror("Ha fallado la creación del hijo");
    } else if (pid == 0) {
  printf("Proceso hijo:\n");
  //PROCESO HIJO.
    } else {
  //PADRE.
          int status;
          waitpid(pid, &status, 0);
    printf("Finalización hijo. Proceso padre:\n");
    }
}


//Función Exec

void cmd_exec(char * tr[]){
  if (tr[0]==NULL) printf("Nada que ejecutar\n");
    else if (execvp(tr[0],tr)==-1) perror ("No se puede ejecutar"); 
}

//Función Pplano
void cmd_pplano (char * tr[]){
    pid_t pid = fork(); 
    if (pid == -1) {
        // ERROR.
          perror("Ha fallado la creación del proceso");
    } else if (pid == 0) {
  //PROCESO SEGUNDO PLANO.
          ejecutar(tr);
        exit(0);
    } else {
  //PADRE.
    int status;
        waitpid(pid, &status, 0);
    }
} 

//Splano

time_t temp(){
  time_t t;
  time(&t);
  return t;
}

void insertarProceso(char * tr[], pid_t pid, lista l){
    int i;
    data datos;
    datos.pid=pid;
    datos.estado=RUNNING;
    datos.tiempo=temp();
    datos.sig=25; //Por defecto entendemos que un proceso corriendo tiene señal 25, correspondiente a SIGCONT.
    strcpy (datos.ejec,"");
    for (i=0; tr[i]!=NULL;i++)
        strcat(datos.ejec,tr[i]); strcat(datos.ejec," ");
    if (insertarDato(datos, &l, ultimo(l))==-1) 
      printf("FATAL ERROR. Memoria agotada\n");
}

void cmd_splano(char * tr[], lista l, int listaCreada){
  pid_t pid = fork(); 
    if (pid == -1) {
        // ERROR.
          perror("Ha fallado la creación del proceso");
    } else if (pid == 0) {
  //PROCESO SEGUNDO PLANO.
      ejecutar(tr);
        exit(255);
    } else {
  //PADRE SE SIGUE EJECUTANDO.
  if (listaCreada) insertarProceso(tr, pid, l);
    }
}
  // Priority

void cmd_priority (char * tr[],int trozos){
  if (tr==1) printf("La prioridad del shell es : %d\n", 
            /***/getpriority(PRIO_PROCESS,getpid()));
  else if (tr==2) printf("La prioridad del proceso %s es: %d \n",
          /***/tr[0], getpriority(PRIO_PROCESS,atoi(tr[0])));
    else  if (setpriority(PRIO_PROCESS,atoi(tr[0]), 
    /***/atoi(tr[1]))==-1) perror("Error");
      else printf("Prioridad cambiada con exito!! La prioridad es: %s\n",
      /**/ tr[1]);
}
  // JOBS

void actualizarEstado(pnodo p, lista *l){
  pid_t rc_pid, child_pid;
  int status;
  child_pid=obtenerDato(p).pid;
  rc_pid = waitpid(child_pid, &status, WUNTRACED|WNOHANG|WCONTINUED);
  if (rc_pid > 0){
    if (WIFCONTINUED(status)){
      p->dato.estado=RUNNING; p->dato.sig=25;
      actualizarDato(p->dato,p,l);
    }
    if (WIFEXITED(status)){
      p->dato.estado=TERMNORM; p->dato.sig=WEXITSTATUS(status);
      actualizarDato(p->dato,p,l);
    }
    if (WIFSIGNALED(status)){
      p->dato.estado=TERMSIG; p->dato.sig=WTERMSIG(status);
      actualizarDato(p->dato,p,l);
    }
    if (WIFSTOPPED(status)){
      p->dato.estado=STOP; p->dato.sig=WSTOPSIG(status);
      actualizarDato(p->dato,p,l);
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
  data datosAux;
  paux=primero(l);
  while (paux!=NULL){
    actualizarEstado(paux, &l);
    datosAux=obtenerDato(paux);
    printf("%d",datosAux.pid);
    printf("%8d",getpriority(PRIO_PROCESS,datosAux.pid));
    escribirEstado(datosAux.estado);
    printf("%10d",datosAux.sig);
    printf("%12s",datosAux.ejec);
    printf("%s %s","        ",ctime(&datosAux.tiempo));
    paux=paux->siguiente;
  }
}

void imprimirTerm(lista l){
  pnodo paux;
  data datosAux;
  paux=primero(l);
  while (paux!=NULL){
    actualizarEstado(paux, &l);
    datosAux=obtenerDato(paux);
    if(datosAux.estado==TERMNORM){
      printf("%d",datosAux.pid);
      printf("%8d",getpriority(PRIO_PROCESS,datosAux.pid));
      escribirEstado(datosAux.estado);
      printf("%10d",datosAux.sig);
      printf("%12s",datosAux.ejec);
      printf("%25s",ctime(&datosAux.tiempo));
    }
  paux=paux->siguiente;
  }
}

void imprimirSig(lista l){
  pnodo paux;
  data datosAux;
  paux=primero(l);
  while (paux!=NULL){
    actualizarEstado(paux, &l);
    datosAux=obtenerDato(paux);
    if(datosAux.estado==TERMSIG){
      printf("%d",datosAux.pid);
      printf("%8d",getpriority(PRIO_PROCESS,datosAux.pid));
      escribirEstado(datosAux.estado);
      printf("%10d",datosAux.sig);
      printf("%12s",datosAux.ejec);
      printf("%25s",ctime(&datosAux.tiempo));
    }
  paux=paux->siguiente;
  }
}

void imprimirStop(lista l){
  pnodo paux;
  data datosAux;
  paux=primero(l);
  while (paux!=NULL){
    actualizarEstado(paux, &l);
    datosAux=obtenerDato(paux);
    if(datosAux.estado==STOP){
      printf("%d",datosAux.pid);
      printf("%8d",getpriority(PRIO_PROCESS,datosAux.pid));
      escribirEstado(datosAux.estado);
      printf("%10d",datosAux.sig);
      printf("%12s",datosAux.ejec);
      printf("%25s",ctime(&datosAux.tiempo));
    }
  paux=paux->siguiente;
  }
}

void imprimirAct(lista l){
  pnodo paux;
  data datosAux;
  paux=primero(l);
  while (paux!=NULL){
    actualizarEstado(paux, &l);
    datosAux=obtenerDato(paux);
    if(datosAux.estado==RUNNING){
      printf("%d",datosAux.pid);
      printf("%8d",getpriority(PRIO_PROCESS,datosAux.pid));
      escribirEstado(datosAux.estado);
      printf("%10d",datosAux.sig);
      printf("%12s",datosAux.ejec);
      printf("%25s",ctime(&datosAux.tiempo));
    }
  paux=paux->siguiente;
  }
}

void jobsPID(lista l, char trozos[]){
  pnodo paux;
  data datosAux;
  paux=buscarDato(atoi(trozos),l);
  if ((paux==NULL)||(obtenerDato(paux).pid==0)) 
  //Si atoi devuelve un pid viable buscarDato siempre devolverá NULL. Ahora, si atoi devuelve 0
  //(esto es, al pasarle caracteres en vez números) es precisa otra comprobación.
    printf("Error: PID inválido\n");
  else{
    actualizarEstado(paux, &l);
    datosAux=obtenerDato(paux);
    printf("%d",datosAux.pid);
    printf("%8d",getpriority(PRIO_PROCESS,datosAux.pid));
    escribirEstado(datosAux.estado);
    printf("%10d",datosAux.sig);
    printf("%12s",datosAux.ejec);
    printf("%25s",ctime(&datosAux.tiempo));
  }
}

void jobs(lista l, char trozos[], int numberTrozos){
  if(!esListaVacia(l)){
     printf("%s %8s %12s %12s %12s %12s\n","PID", "PRIOR", 
        /****/"STATE", "SIG", "COMMAND", "DATE");
     printf("---------------------------------");
     printf("-------------------------------------------------\n");
     if (numberTrozos<2) imprimirTodo(l);
     else if ((strcmp(trozos, "all")==0)) imprimirTodo(l);
     else if ((strcmp(trozos, "term")==0)) imprimirTerm(l);
     else if ((strcmp(trozos, "sig")==0)) imprimirSig(l);
     else if ((strcmp(trozos, "stop")==0)) imprimirStop(l);
     else if ((strcmp(trozos, "act")==0)) imprimirAct(l);
     else jobsPID(l, trozos);
  }
}

void clearjobs(lista *l, int listaCreada){
  pnodo paux, paux2;
  if ((listaCreada) && (!esListaVacia(*l))){
    paux=primero(*l);
    while (paux!=NULL){
      paux2=paux;
      paux=paux->siguiente;
      actualizarEstado(paux2, l);
      if ((obtenerDato(paux2).estado==1) || 
      /*****/(obtenerDato(paux2).estado==2)){
        eliminarDato(obtenerDato(paux2).pid, l);
      }
    }
  } 
}