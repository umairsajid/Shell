void ProcesarEntrada(char * entrada){
 char * tr[MAX_ENTRADA/2];
 int trozos;
 if ((trozos=TrocearCadena(entrada, tr))==0)
  return;
 else{
  DecidirComando(tr, trozos);
 }
} 