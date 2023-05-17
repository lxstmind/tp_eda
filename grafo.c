#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

// Criar um novo vértice
// Devolve 1 em caso de sucesso ou 0 caso contrário
int criarVertice(Grafo *g, char novoId[])
{Grafo novo = malloc(sizeof(struct registo1));
 if (novo!=NULL)
 {strcpy(novo->vertice,novoId);
  novo->meios = NULL;
  novo->seguinte = *g;
  *g = novo;
  return(1);
 }
 else return(0);
}

// Devolve 1 se o vertice existe no grafo ou 0 caso contrário
int existeVertice(Grafo g, char vertice[])
{while (g!=NULL)
 {if (strcmp(g->vertice,vertice)==0) return(1);
  else g=g->seguinte;
 }
 return(0);
}

// Criar uma nova aresta
// Devolve 1 em caso de sucesso ou 0 caso contrário
int criarAresta(Grafo g, char vOrigem[], char vDestino[], float peso)
{Adjacente novo;
 if (existeVertice(g,vOrigem) && existeVertice(g,vDestino))
 {
  while(strcmp(g->vertice,vOrigem)!=0) g=g->seguinte;
  novo = malloc(sizeof(struct registo1));
  if (novo!=NULL)
	{strcpy(novo->vertice,vDestino);
	 novo->peso = peso;
	 novo->seguinte=g->adjacentes;
	 g->adjacentes=novo;
	 return(1);
	}
  else return(0);
 }
 else return(0);
}

// Listar os vértices adjacentes 
void listarAdjacentes(Grafo g, char vertice[]) {
    while (g != NULL) {
        if (strcmp(g->vertice, vertice) == 0) {
            Adjacente aux = g->adjacentes;
            while (aux != NULL) {
                printf("Adjacente: %s Peso: %.2f\n", aux->vertice, aux->peso);
                aux = aux->seguinte;
            }
            return;
        }
        g = g->seguinte;
    }
    printf("O vertice %s nao foi encontrado.\n", vertice);
}

Grafo* lerGrafo() {
    FILE* fp;
    fp = fopen("arestas.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char origem[MAX_LOCAL_LENGTH];
    char destino[MAX_LOCAL_LENGTH];
    float peso;

    Grafo *grafo = NULL;
    while (fscanf(fp, "%[^;];%[^;];%f\n", origem, destino, &peso) == 3) {
        if (!existeVertice(*grafo, origem)) {
            criarVertice(grafo, origem);
        }
        if (!existeVertice(*grafo, destino)) {
            criarVertice(grafo, destino);
        }
        criarAresta(*grafo, origem, destino, peso);
    }

    fclose(fp);
    return grafo;
}