void DecidirComando(char *tr[], int trozos){
 if (!strcmp(tr[0],"fin")) exit(0);
    else if (!strcmp(tr[0],"exit")) exit(0);
    else if (!strcmp(tr[0],"quit")) exit(0);
    else if (!strcmp(tr[0],"autores")) cmd_autores();
    else if (!strcmp(tr[0],"pid")) cmd_pid(tr[1]);
  	else if (!strcmp(tr[0],"cd")) cmd_cd(tr[1],trozos);
    else if (!strcmp(tr[0],"ls")) cmd_ls(tr[1],trozos);
     else if (!strcmp(tr[0],"list")) cmd_list(tr);
    else if (!strcmp(tr[0],"deltree")) cmd_deltree(tr[1]);
    else if (!strcmp(tr[0],"delete")) cmd_delete(tr[1]);
    else if (!strcmp(tr[0],"fork")) cmd_fork();
    else if (!strcmp(tr[0],"exec")) cmd_exec(tr[1]);
    else if (!strcmp(tr[0],"priority")) cmd_priority(tr+1);
    else if (!strcmp(tr[0],"time")) cmd_time();
    else if (!strcmp(tr[0],"pplano")) cmd_pplano(tr+1);
    else if (!strcmp(tr[0],"splano")) cmd_splano(tr+1);
    else cmd_pplano(tr);
    
}