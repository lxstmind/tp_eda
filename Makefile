all: prog

prog: main.o funcoes.o clientes.o gestores.o transportes.o grafo.o
	gcc -g -o prog main.o funcoes.o clientes.o gestores.o transportes.o grafo.o

main.o: main.c header.h
	gcc -g -o main.o main.c -c

funcoes.o: funcoes.c header.h
	gcc -g -o funcoes.o funcoes.c -c

clientes.o: clientes.c header.h
	gcc -g -o clientes.o clientes.c -c

gestores.o: gestores.c header.h
	gcc -g -o gestores.o gestores.c -c

transportes.o: transportes.c header.h
	gcc -g -o transportes.o transportes.c -c

grafo.o: grafo.c header.h
	gcc -g -o grafo.o grafo.c -c

clean:
	del /Q /S *.o prog

run:
	MinGW32-make clean
	MinGW32-make all
	./prog