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