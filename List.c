#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>  
#include <grp.h>
#include <pwd.h>
#include <getopt.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <errno.h>
#include "lista.h"

char *NombreUsuario(uid_t uid){

  struct passwd *p;
  if ((p=getpwuid(uid))==NULL)
    return("¿?");
  return p->pw_name;
}

char *NombreGrupo(gid_t gid){

  struct group *g;
  if ((g=getgrgid(gid))==NULL)
    return("¿?");
  return g->gr_name;
}

char TipoFichero (mode_t m)
{
switch (m&S_IFMT) 
  { /*and bit a bit con los bits de formato,0170000 */
  case S_IFSOCK: return 's'; /*socket */
  case S_IFLNK: return 'l'; /*symbolic link*/
  case S_IFREG: return '-'; /* fichero normal*/
  case S_IFBLK: return 'b'; /*block device*/
  case S_IFDIR: return 'd'; /*directorio */
  case S_IFCHR: return 'c'; /*char device*/
  case S_IFIFO: return 'p'; /*pipe*/
  default: return '?'; /*desconocido, no deberia aparecer*/
  }
}

char * Permisos (mode_t m)
{
    static char permisos[12];
  strcpy (permisos,"---------- ");
  permisos[0]=TipoFichero(m);
  if (m&S_IRUSR) permisos[1]='r'; /*propietario*/
  if (m&S_IWUSR) permisos[2]='w';
  if (m&S_IXUSR) permisos[3]='x';
  if (m&S_IRGRP) permisos[4]='r'; /*grupo*/
  if (m&S_IWGRP) permisos[5]='w';
  if (m&S_IXGRP) permisos[6]='x';
  if (m&S_IROTH) permisos[7]='r'; /*resto*/
  if (m&S_IWOTH) permisos[8]='w';
  if (m&S_IXOTH) permisos[9]='x';
  if (m&S_ISUID) permisos[3]='s'; /*setuid, setgid y stickybit*/
  if (m&S_ISGID) permisos[6]='s';
  if (m&S_ISVTX) permisos[9]='t';
  return permisos;
}

void DetallesFichero (char *dir, char *f){
  
  static char aux[MAX_ENTRADA];
  struct stat buffer;
  sprintf(aux,"%s/%s",dir,f);
  
  if (lstat(aux,&buffer)==-1){
    sprintf(aux,"Error al acceder a %s:%s",f,strerror);
    return;
  }else{
  printf("%10lu",(unsigned long)buffer.st_ino);
  printf("   %10s",Permisos(buffer.st_mode));
  printf("%10lu",(unsigned long)buffer.st_nlink);
  printf("%10s",NombreUsuario(buffer.st_uid));
  printf("%10s",NombreGrupo(buffer.st_gid));
  printf("    %-20s",f );
  printf("\n");
}

}


int ListarDirectorio (char *dir, int hayS, int hayA){

  DIR *p;
  struct dirent *d;

  if ((p=opendir(dir))==NULL)
    return -1;

  while ((d=readdir(p))!=NULL){
    if (!hayA && d->d_name[0]=='.')
      continue;
    if (hayS){
      printf ("%s\n", d ->d_name);
  }
   else{
      // printf("%s %15s",d->d_name,"" ); 
      DetallesFichero(dir,d->d_name);
      // DetallesFichero(dir,d->d_name);
    }
  }
  return(closedir(p));
}


void cmd_list(char *tr[],int trozos){
  int hayS=0,hayA=0, i;
  char *dir=".";

  for (i=1; tr[i]!=NULL; i++){
    if (!strcmp(tr[i],"-s")){ hayS=1;}
    else{
    	if (!strcmp(tr[i],"-a")){ hayA=1;}
    	else dir=tr[i];
	}
  }

if ((dir,hayS,hayA)==-1)
	dir=".";
	ListarDirectorio(dir,hayS,hayA);
}