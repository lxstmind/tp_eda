CC=gcc
CFLAGS=-Wall -Wextra

all: main

main: main.o funcoes.o clientes.o gestores.o transportes.o grafo.o
	$(CC) $(CFLAGS) -o main main.o funcoes.o clientes.o gestores.o transportes.o grafo.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

funcoes.o: funcoes.c
	$(CC) $(CFLAGS) -c funcoes.c

clientes.o: clientes.c
	$(CC) $(CFLAGS) -c clientes.c

gestores.o: gestores.c
	$(CC) $(CFLAGS) -c gestores.c

transportes.o: transportes.c
	$(CC) $(CFLAGS) -c transportes.c

grafo.o: grafo.c
	$(CC) $(CFLAGS) -c grafo.c

clean:
	rm -f main *.o