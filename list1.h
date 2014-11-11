/* Función para devolver un error en caso de que ocurra */
void error(const char *s);

/* Calculamos el tamaño del archivo */
long fileSize(char *fname);

/* Sacamos el tipo de archivo haciendo un stat(), es como el stat de la línea de comandos */
unsigned char statFileType(char *fname);

/* Intenta sacar el tipo de archivo del ent */
unsigned char getFileType(char *ruta, struct dirent *ent);

/* Obtiene el nombre del fichero con la ruta completa */
char *getFullName(char *ruta, struct dirent *ent);

/* Genera una cadena de espacios, para dibujar el árbol */
char *generaPosStr(int niv);

/* Función principal, que cuenta archivos */
unsigned cuentaArchivos(char *ruta, int niv);
int imprime (int *num, char *tr[]){ 
 FILE * pFile; 
   pFile = fopen ("/home/fabian/a.txt","w");
   fprintf (pFile, "%s . Total: %u archivos\n", tr[1], num);
   fclose (pFile);
} 
int cmd_list1 (int trozos, char *tr[])
{
  unsigned num;

  if (trozos != 2) 
    {
      error("Uso: ./directorio_2 <ruta>\n");
    }
  printf("Entrando en: %s\n", tr[1]);
  num=cuentaArchivos(tr[1], 1);
  imprime(num, tr);
  //printf("%s . Total: %u archivos\n", tr[1], num);
  /* Empezaremos a leer en el directorio actual */

  return EXIT_SUCCESS;
} 

void error(const char *s)
{
  /* perror() devuelve la cadena S y el error (en cadena de caracteres) que tenga errno */
  perror (s);
  exit(EXIT_FAILURE);
}

char *getFullName(char *ruta, struct dirent *ent)
{
  char *nombrecompleto;
  int tmp;

  tmp=strlen(ruta);
  nombrecompleto=malloc(tmp+strlen(ent->d_name)+2); /* Sumamos 2, por el \0 y la barra de directorios (/) no sabemos si falta */
  if (ruta[tmp-1]=='/')
    sprintf(nombrecompleto,"%s%s", ruta, ent->d_name);
  else
    sprintf(nombrecompleto,"%s/%s", ruta, ent->d_name);
  
  return nombrecompleto;
}

char *generaPosStr(int niv)
{
  int i;
  char *tmp=malloc(niv*2+1);    /* Dos espacios por nivel más terminador */
  for (i=0; i<niv*2; ++i)
    tmp[i]=' ';
  tmp[niv*2]='\0';
  return tmp;
}

unsigned cuentaArchivos(char *ruta, int niv)
{
  /* Con un puntero a DIR abriremos el directorio */
  DIR *dir;
  /* en *ent habrá información sobre el archivo que se está "sacando" a cada momento */
  struct dirent *ent;
  unsigned numfiles=0;          /* Ficheros en el directorio actual */
  unsigned char tipo;       /* Tipo: fichero /directorio/enlace/etc */
  char *nombrecompleto;     /* Nombre completo del fichero */
  char *posstr;         /* Cadena usada para posicionarnos horizontalmente */
  dir = opendir (ruta);

  /* Miramos que no haya error */
  if (dir == NULL) 
    error("No puedo abrir el directorio");
  
  while ((ent = readdir (dir)) != NULL) 
    {
      if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) )
    {
      nombrecompleto=getFullName(ruta, ent);
      tipo=getFileType(nombrecompleto, ent);
      if (tipo==DT_REG)
        {
          ++numfiles;
        }
      else if (tipo==DT_DIR)
        {
          posstr=generaPosStr(niv);
          printf("%sEntrando en: %s\n", posstr, nombrecompleto);          
          printf("%s%s . Total: %u archivos ", posstr, nombrecompleto, cuentaArchivos(nombrecompleto, niv+1));
          /* Podemos poner las líneas que queramos */
          printf("\n");
          free(posstr);
        }
      free(nombrecompleto);
    }
    }
  closedir (dir);
  
  return numfiles;
}

unsigned char getFileType(char *nombre, struct dirent *ent)
{
  unsigned char tipo;

  tipo=ent->d_type;
  if (tipo==DT_UNKNOWN)
    {
      tipo=statFileType(nombre);
    }

  return tipo;
}

/* stat() vale para mucho más, pero sólo queremos el tipo ahora */
unsigned char statFileType(char *fname)
{
  struct stat sdata;

  /* Intentamos el stat() si no funciona, devolvemos tipo desconocido */
  if (stat(fname, &sdata)==-1)
    {
      return DT_UNKNOWN;
    }

  switch (sdata.st_mode & S_IFMT) 
    {
    case S_IFBLK:  return DT_BLK;
    case S_IFCHR:  return DT_CHR;
    case S_IFDIR:  return DT_DIR;
    case S_IFIFO:  return DT_FIFO;
    case S_IFLNK:  return DT_LNK;
    case S_IFREG:  return DT_REG;
    case S_IFSOCK: return DT_SOCK;
    default:       return DT_UNKNOWN;
    }
}


  
  
 int ls() 
 { 
    char *curr_dir = NULL; 
    DIR *dp = NULL; 
    struct dirent *dptr = NULL; 
    unsigned int count = 0; 
  
    // Find the column width of terminal 
    // We will make use of this in part-II  
    // Of this article. 
    struct winsize w; 
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); 
  
    curr_dir = getenv("PWD"); 
    if(NULL == curr_dir) 
    { 
        printf("\n ERROR : Could not get the working directory\n"); 
        return -1; 
    } 
     
    dp = opendir((const char*)curr_dir);    
    if(NULL == dp) 
    { 
        printf("\n ERROR : Could not open the working directory\n"); 
        return -1; 
    } 
   
    for(count = 0; NULL != (dptr = readdir(dp)); count++) 
    { 
        if(dptr->d_name[0] != '.') 
        { 
            // Check if the file is executable 
            if(!access(dptr->d_name,X_OK)) 
            { 
                int fd = -1; 
                struct stat st; 
  
                fd = open(dptr->d_name, O_RDONLY, 0); 
                if(-1 == fd) 
                { 
                    printf("\n Opening file/Directory failed\n"); 
                    return -1; 
                } 
                 
                fstat(fd, &st); 
                // Check if it actaully was a directory with execute 
                // permissions on it. 
                if(S_ISDIR(st.st_mode)) 
                { 
                    // If it was a directory, print it in Blue 
                    printf(MAKE_BLUE"%s     "RESET_COLOR,dptr->d_name); 
                } 
                else 
                {                                   
                    // If it was a normal executable 
                    // Print it in green 
                    printf(MAKE_GREEN"%s     "RESET_COLOR,dptr->d_name); 
                } 
                close(fd); 
            } 
            else 
            { 
                // No executable flag ON 
                // Print it in black(default) 
                printf("%s     ",dptr->d_name); 
            } 
        } 
    } 
    printf("\n"); 
  
    return 0; 
 }