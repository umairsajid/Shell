void Entrada() {
  Saludo();
  while(1){
    printf("\n%s ->",pwd());
    char Entrada [MAX_ENTRADA];
    fgets(Entrada,MAX_ENTRADA, stdin);
    ProcesarEntrada(Entrada);
   }
  printf("EXIT\n");//nunca entra aqui
}