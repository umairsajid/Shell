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