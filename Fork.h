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