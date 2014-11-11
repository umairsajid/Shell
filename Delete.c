#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "Delete.h"

// Comando Delete

void cmd_delete(char *cadena) {
  struct stat valor;
        stat(cadena,&valor); // te dice si es un fichero o directorio

        if (TipoFichero(valor.st_mode)=='d') {
          if (rmdir(cadena)==-1) perror("error"); 
        }
        else if (TipoFichero(valor.st_mode)=='-') {
          if (unlink(cadena)==-1) perror("error");
        }
      } 

// Comando Deltree

int cmd_deltree(const char *tr[])
{
   DIR *d = opendir(tr);
   size_t path_len = strlen(tr);
   int r = -1;

   if (d)
   {
      struct dirent *p;

      r = 0;

      while (!r && (p=readdir(d)))
      {
          int r2 = -1;
          char *buf;
          size_t len;

          /* Skip the names "." and ".." as we don't want to recurse on them. */
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
          {
             continue;
          }

          len = path_len + strlen(p->d_name) + 2; 
          buf = malloc(len);

          if (buf)
          {
             struct stat statbuf;

             snprintf(buf, len, "%s/%s", tr, p->d_name);

             if (!stat(buf, &statbuf))
             {
                if (S_ISDIR(statbuf.st_mode))
                {
                   r2 = cmd_deltree(buf);
                }
                else
                {
                   r2 = unlink(buf);
                }
             }

             free(buf);
          }

          r = r2;
      }

      closedir(d);
   }

   if (!r)
   {
      r = rmdir(tr);
   }

   return r;
}
