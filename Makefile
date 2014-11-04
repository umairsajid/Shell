all: 
	clear
	gcc Shell.c -w -lm -o Shell  
	./Shell
clean:
	rm *.o