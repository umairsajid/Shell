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
    default: waitpid(pid,&status,0); 
  }
}