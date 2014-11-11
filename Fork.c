#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <getopt.h>
#include <sys/resource.h>
#include <unistd.h>
#include "Fork.h"
//Función Fork
void cmd_fork(){
  pid_t pid = fork();
  int estado;
  if (pid == -1){
    perror("Error. Comando no valido");
    exit(0);
  }  
  else if (pid == 0){
    printf("Ejecutando nuevo shell......");
  }
  else{
    waitpid(pid,&estado,0);
  }
}

//Función Exec

void cmd_exec(char *tr[]) {
  if (tr==NULL){
    //execvp(tr[1],&tr[1]);
    perror("Fallo inesperado. Psicopata de camino\n");
  }
  else  {
    execvp(tr[1],&tr[1]);
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

void cmd_splano(char *tr[]) {
   pid_t pid;
   int status;
   

  switch (pid=fork()) {
    case -1:
       perror("Error\n"); 
      break;
    case 0:
       cmd_exec(tr);
       exit(0); 
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