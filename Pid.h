void cmd_pid(char * parm) {
 
    if (parm==NULL)
        printf("El pid del shell es: %d",getpid(),"\n");
    else if (!strcmp(parm,"-p")) 
        printf("El pid del padre: %d", getppid(),"\n");
    else printf ("ERROR. Uso: pid [-p]\n\n");
}