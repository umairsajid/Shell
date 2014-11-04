void cmd_ls(char *cadena, char *trozos) {
  struct dirent * d;
  DIR *direct=NULL; 

  if (trozos=0)
     if ((trozos=opendir(trozos))==NULL)
    printf("Error. No se encontro el directorio");
       else closedir(direct);
    
  chdir(trozos);
  direct = opendir(".");
  d=readdir(direct);
}