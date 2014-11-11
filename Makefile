all: 
	clear
	gcc -c CdPid.c -w -lm
	gcc -c Delete.c -w -lm
	gcc -c Fork.c -w -lm
	gcc -c Entrada.c -w -lm
	gcc -c List.c -w -lm
	gcc Shell.c Entrada.o CdPid.o Delete.o Fork.o List.o -o Shell
	./Shell
	rm Shell
	rm *.o	
clean:
	clear
	rm *.o
	rm Shell


