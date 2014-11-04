void cmd_exec(char *tr) {
  if (tr==NULL){
    //execvp(tr[1],&tr[1]);
    perror("Fallo inesperado. Psicopata de camino\n");
  }
  else  {
    execvp(tr,&tr);
  }
}