void cmd_deltree (char * dir) {
  DIR *direct=NULL;
  char duplicado[MAX_ENTRADA];
  struct dirent *l;
  struct stat aux;

  if ((direct = opendir(dir)) != NULL) 
  {
    while ((l = readdir(direct)) != NULL) {
    sprintf(duplicado, "%s/%s", dir, l->d_name); //Mete en duplicado el directorio. Sprintf buffer     
      if(strcmp(l->d_name,".")&&(strcmp(l->d_name, "..")))//lista->d_name es el comienzo de la matriz de caracteres con el nombre de la entrada del directorio.
        {    
      lstat(duplicado,&aux);
      // Guarda en aux la informacion del fichero.
      if (S_ISDIR(aux.st_mode)) 
        //S_ISDIR nos devuelve si es un fichero o un directorio para procesarlo en el if.
      {         
        rmdir(duplicado); 
        //Ejecuta la accion para borrar el direcorio. 
      }
      else 
        unlink(duplicado); 
        //Ejecuta la accion para borrar el archivo.
        } 
    }
    rmdir(dir);
    unlink(dir);
    
  } else {
    perror("Error. Directorio no encontrado.");

  }
  
  closedir(direct);
  
  
    
}