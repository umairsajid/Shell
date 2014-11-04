// Comando Delete

void cmd_delete(char *cadena) {
  struct stat valor;
  stat(cadena,&valor); 
  // Devuelve si es fichero o directorio
  
  if (TipoFichero(valor.st_mode)=='d') {
    if (rmdir(cadena)==-1) perror("error"); 
  }
  else if (TipoFichero(valor.st_mode)=='-') {
    if (unlink(cadena)==-1) perror("error");
  }
}