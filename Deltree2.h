// Esta funcion no esta implementada en la Shell

// Definiciones

int Directorio(char* dir){
  
  struct stat s;
  if(lstat(dir,&s)==-1)
    return 0;
  return ( S_ISDIR(s.st_mode));
}

int BorrarDirectorio (char* dir){
  DIR *p;
  struct dirent *d;
  char aux[MAX_ENTRADA];

  if ((p=opendir(dir))==NULL)
    return -1;

  while ((d=readdir(p))!=NULL){
    if(!strcmp(d->d_name,".")|| !strcmp(d->d_name,".."))
      continue;
    sprintf(aux,"%s/%s",dir,d->d_name);

    if(Directorio(aux)){
      if(BorrarDirectorio(aux)==-1)
       return -1;
    }
    else{ if(unlink(aux)==-1)
      return -1;
    }
  }
}

// Comando Deltree

void cmd_deltree1(char *tr[]){
  
if (tr[0]==NULL)
  printf("Falta argumento\n");
else
  if (BorrarDirectorio(tr[0])==-1)
    perror ("Imposible Borrar directorio");
}

void cmd_deltree2(char *tr[]){
  BorrarDirectorio(tr[0]);
}