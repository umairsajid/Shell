int TrocearCadena(char * cadena, char * trozos[])
{
int i=1;
  if ((trozos[0]=strtok(cadena," \n\t"))==NULL)
   return 0;
  while ((trozos[i]=strtok(NULL," \n\t"))!=NULL)
    i++;
    return i;
}