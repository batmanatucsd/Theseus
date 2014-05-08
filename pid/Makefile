
run: source.o main.o
	gcc -Wall -pedantic source.o main.o -o run

main.o: main.c
	gcc -Wall -pedantic -c main.c -o main.o

source.o: pid.c pid.h
	gcc -Wall -pedantic -c pid.c -o source.o

clean: 
	rm main.o source.o run
