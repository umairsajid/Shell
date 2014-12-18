CC=gcc -ggdb
all: 
	clear
	$(CC) -c lista.c -w -lm
	$(CC) -c CdPid.c -w -lm
	$(CC) -c Delete.c -w -lm
	$(CC) -c Fork.c -w -lm
	$(CC) -c Entrada.c -w -lm
	$(CC) -c List.c -w -lm
	$(CC) Shell.c Entrada.o CdPid.o Delete.o Fork.o List.o lista.o -o Shell
	./Shell
execute:
	clear
	./Shell
clean:
	clear
	rm *.o
	rm Shell
tar:
	tar czvf p1.tar.gz Makefile *.c *.h
