
#define MAX_ENTRADA 4096

//Funciones para el comando CD
//La funcion MostrarDirActual no se usa porque falla en la ejecucion
void MostrarDirActual(){

char dir[MAX_ENTRADA];

  if (getcwd(dir,MAX_ENTRADA)==NULL)
    perror("Imposible mostrar directorio");
  else
    printf("%s\n",dir);
}

//Hace lo mismo que MostrarDirActual pero pensado de otra manera

char * pwd() { //Indica el directorio actual
    char *auxiliar = "";
    if ((auxiliar = getcwd(NULL, MAX_ENTRADA)) == NULL) {
        perror("pwd");
   
    }
 
}

// Comando CD

void cmd_cd (char *cadena, char *trozos){
	int auxiliar=0;
	if (cadena==NULL) {
		char *cadena = pwd();
		printf ("%s\n", cadena);
	}
	else if (trozos >=2) {
		auxiliar =chdir(cadena);
    printf("Ruta:%s\n",pwd());
		if (auxiliar!=0){
			perror("Error chdir");
		}
	}
	//printf("\n%d\n\n",chdir(cadena)); // saca 0 o -1 segun entre en un if u otro
}