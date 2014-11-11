#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Entrada.h"
void Saludo()
{
        printf("\n-------------------------------------------------------\n");
        printf("\tBienvenido a la Shell \n");
        puts("\tAutores :Fabian Lema y Orlando Vazquez");
        printf("-------------------------------------------------------\n");
        printf("\n\n");
}

int TrocearCadena(char * cadena, char * trozos[])
{
int i=1;
  if ((trozos[0]=strtok(cadena," \n\t"))==NULL)
   return 0;
  while ((trozos[i]=strtok(NULL," \n\t"))!=NULL)
    i++;
    return i;
}

void cmd_autores() {
    printf("Fabián Lema Pérez, fabian.lema\n");
    printf("Orlando Vázquez López, orlando.vazquez\n");
}

void DecidirComando(char *tr[], int trozos){
 if (!strcmp(tr[0],"fin")) exit(0);
    else if (!strcmp(tr[0],"exit")) exit(0);
    else if (!strcmp(tr[0],"quit")) exit(0);
    else if (!strcmp(tr[0],"autores")) cmd_autores();
    else if (!strcmp(tr[0],"pid")) cmd_pid(tr[1]);
  	else if (!strcmp(tr[0],"cd")) cmd_cd(tr[1],trozos);
    else if (!strcmp(tr[0],"ls")) cmd_ls(tr[1],trozos);
	  // else if (!strcmp(tr[0],"list")) cmd_list1(trozos,tr); Implementando Fabián. No ejecutar peta el pc.
    else if (!strcmp(tr[0],"deltree")) cmd_deltree(tr[1]);
    else if (!strcmp(tr[0],"delete")) cmd_delete(tr[1]);
    else if (!strcmp(tr[0],"fork")) cmd_fork();
    else if (!strcmp(tr[0],"exec")) cmd_exec(tr);
    else if (!strcmp(tr[0],"priority")) cmd_priority(tr+1);
    // else if (!strcmp(tr[0],"time")) cmd_time(); Hace falta esto Orlando¿?
    else if (!strcmp(tr[0],"pplano")) cmd_pplano(tr);
    else if (!strcmp(tr[0],"splano")) cmd_splano(tr);
    else cmd_pplano(tr);
    
}

void ProcesarEntrada(char * entrada){
 char * tr[MAX_ENTRADA/2];
 int trozos;
 if ((trozos=TrocearCadena(entrada, tr))==0)
  return;
 else{
  DecidirComando(tr, trozos);
 }
} 

void Entrada() {
  Saludo();
  while(1){
    printf("\n%s ->",pwd());
    char Entrada [MAX_ENTRADA];
    fgets(Entrada,MAX_ENTRADA, stdin);
    ProcesarEntrada(Entrada);
   }
  printf("EXIT\n");//nunca entra aqui
}