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
void listarAdjacentes(Grafo g, char vertice[])
{Adjacente aux;
 if (existeVertice(g,vertice))
 {while (strcmp(g->vertice,vertice)!=0) g=g->seguinte;
  aux = g->adjacentes;
  while (aux!=NULL) 
  {printf("Adjacente:%s Peso:%.2f\n", aux->vertice, aux->peso);
   aux=aux->seguinte;
  }
 }
}

// Inserir meio de transporte na localização com geocódigo passado por parâmetro
// Devolve 1 em caso de sucesso ou 0 caso contrário
int inserirMeio(Grafo g, char geocodigo[], int codigoMeio)
{
 while ((g!=NULL)&&(strcmp(g->vertice,geocodigo)!=0))
	 g=g->seguinte;
 if (g==NULL) return(0);
 else {Meios novo = malloc(sizeof(struct registo3));
       novo->codigo = codigoMeio;
       novo->seguinte = g->meios;
       g->meios = novo;
       return(1);	 
      }
}

// Listar os códigos dos meios de transporte presente numa determinada localização passada por parâmetro
void listarMeios(Grafo g, char geocodigo[])
{
 while ((g!=NULL)&&(strcmp(g->vertice,geocodigo)!=0))
	 g=g->seguinte;
 if (g!=NULL) 
 {Meios aux=g->meios;
  if (aux==NULL) printf("sem meios de transporte\n");
  else while(aux!=NULL)
  {printf("Codigo meio: %d\n", aux->codigo);
   aux = aux->seguinte;
  }
 }
 else printf("geocodigo inexistente\n");
}

/*
int main()
{Grafo g = NULL;

 criarVertice(&g,"araras.quao.metabolismos");
 criarVertice(&g,"rolico.angico.almeiroes");
 criarVertice(&g,"velhas.cigano.junte");
 criarVertice(&g,"almeiroes.pacoquinhas.valem");
 criarVertice(&g,"bocal.sardas.sorvetes");

 criarAresta(g,"araras.quao.metabolismos","rolico.angico.almeiroes",0.710F);
 criarAresta(g,"araras.quao.metabolismos","velhas.cigano.junte",1.130F);
 criarAresta(g,"araras.quao.metabolismos","almeiroes.pacoquinhas.valem",0.250F);
 criarAresta(g,"araras.quao.metabolismos","bocal.sardas.sorvetes",1.010F);


 inserirMeio(g,"///dimly.nuttier.pitch",100);
 inserirMeio(g,"///dimly.nuttier.pitch",101);
 inserirMeio(g,"///dimly.nuttier.pitch",102);
 inserirMeio(g,"///babbled.trifling.consoled",200);
}
*/

Grafo* lerGrafo(){
    FILE* fp;
    fp = fopen("arestas.txt","r");

    if (fp!=NULL){
        char aresta[50];
        float peso;

        while (!feof(fp)) {
            fscanf(fp, "%[^;];%[^;];%f\n", &aresta, &aresta, &peso);
        }

        fclose(fp);
    }
}