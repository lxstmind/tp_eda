#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

/**
 * @brief cria um novo vertice no grado
 * 
 * @param g apontador para o grafo 
 * @param novoId id do novo vertice
 * @return retorna um inteiro 1 em caso de sucesso ou 0 em caso de falha
 */
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

/**
 * @brief verifica a existencia de um vertice
 * 
 * @param g apontador para o grafo
 * @param vertice vertice a ser analisado
 * @return retorna um inteiro 1 em caso de sucesso ou 0 em caso de falha
 */
int existeVertice(Grafo g, char vertice[])
{while (g!=NULL)
 {if (strcmp(g->vertice,vertice)==0) return(1);
  else g=g->seguinte;
 }
 return(0);
}

/**
 * @brief cria uma nova aresta para ligar dois pontos já existentes
 * 
 * @param g apontador para o grafo
 * @param vOrigem id do vertice de origem
 * @param vDestino id do vertice de destino
 * @param peso inteiro que representa o peso da aresta
 * @return retorna um inteiro 1 em caso de sucesso ou 0 em caso de falha
 */
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

/**
 * @brief função que remove uma localização do ficheiro de localizações
 * 
 */
void removerLocalizacao() {
    char idRemover[100];
    printf("Informe o ID da localizacao a ser removida: ");
    scanf("%s", idRemover);

    // Abre o ficheiro para leitura
    FILE* fp = fopen("localizacoes.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro de localizacoes!\n");
        return;
    }

    // Abre um ficheiro temporario para escrita
    FILE* fpTemp = fopen("temp.txt", "w");
    if (fpTemp == NULL) {
        printf("Erro ao criar ficheiro temporario!\n");
        fclose(fp);
        return;
    }

    // Percorre o ficheiro de localizacoes linha por linha
    char linha[100];
    int encontrou = 0;
    while (fgets(linha, 100, fp)) {
        // Lê o ID da linha atual
        char id[100];
        sscanf(linha, "%[^;]", id);

        // Se o ID for diferente do ID a ser removido, escreve a linha no ficheiro temporario
        if (strcmp(id, idRemover) != 0) {
            fputs(linha, fpTemp);
        } else {
            encontrou = 1;
        }
    }

    // Fecha os ficheiros
    fclose(fp);
    fclose(fpTemp);

    // Remove o ficheiro antigo
    remove("localizacoes.txt");

    // Renomeia o ficheiro temporario para o nome original
    rename("temp.txt", "localizacoes.txt");

    if (encontrou) {
        printf("Localizacao removida com sucesso!\n");
    } else {
        printf("Localizacao nao encontrada!\n");
    }
}

/**
 * @brief função que remove uma aresta do ficheiro de arestas
 * 
 */
void removerAresta() {
    char pontoRemover[MAX_LOCAL_LENGTH];
    char arestaRemover[MAX_LOCAL_LENGTH];
    
    printf("Informe o ponto a ser removido: ");
    scanf("%s", pontoRemover);
    
    printf("Informe a aresta a ser removida: ");
    scanf("%s", arestaRemover);

    // Abre o ficheiro para leitura
    FILE* fp = fopen("arestas.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro de arestas!\n");
        return;
    }

    // Abre um ficheiro temporario para escrita
    FILE* fpTemp = fopen("temp.txt", "w");
    if (fpTemp == NULL) {
        printf("Erro ao criar ficheiro temporario!\n");
        fclose(fp);
        return;
    }

    // Percorre o ficheiro de arestas linha por linha
    char linha[MAX_LOCAL_LENGTH];
    int encontrou = 0;
    while (fgets(linha, MAX_LOCAL_LENGTH, fp)) {
        // Lê o ponto e a aresta da linha atual
        char pontoAtual[MAX_LOCAL_LENGTH];
        char arestaAtual[MAX_LOCAL_LENGTH];
        sscanf(linha, "%[^;];%[^;]", pontoAtual, arestaAtual);

        // Se o ponto e a aresta forem diferentes dos fornecidos, escreve a linha no ficheiro temporario
        if (strcmp(pontoAtual, pontoRemover) != 0 || strcmp(arestaAtual, arestaRemover) != 0) {
            fputs(linha, fpTemp);
        } else {
            encontrou = 1;
        }
    }

    // Fecha os ficheiros
    fclose(fp);
    fclose(fpTemp);

    // Remove o ficheiro antigo
    remove("arestas.txt");

    // Renomeia o ficheiro temporario para o nome original
    rename("temp.txt", "arestas.txt");

    if (encontrou) {
        printf("Aresta removida com sucesso!\n");
    } else {
        printf("Aresta nao encontrada!\n");
    }
}

/**
 * @brief função que lista os vertices adjacentes de um determinado vertice
 * 
 * @param g grafo para qual vai ser procurado os vertices adjacentes
 * @param vertice vértice para o qual vai listar os vértices adjacentes
 */
void listarAdjacentes(Grafo g, char vertice[]) {
    while (g != NULL && strcmp(g->vertice, vertice) != 0)
        g = g->seguinte;

    if (g != NULL) {
        struct registo2* aux = g->adjacentes;
        while (aux != NULL) {
            printf("Adjacente: %s Peso: %.3f\n", aux->vertice, aux->peso);
            aux = aux->seguinte;
        }
    }
}

/**
 * @brief função que le as arestas de um ficheiro e retorna um grafo
 * 
 * @return Grafo grafo lido a partir do ficheiro arestas.txt
 */
Grafo lerGrafoDoFicheiro() {
    FILE* fp = fopen("arestas.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return NULL;
    }

    char linha[100];
    Grafo primeiro = NULL;
    Grafo atual = NULL;

    while (fgets(linha, sizeof(linha), fp)) {
        char vOrigem[50];
        char vDestino[50];
        float peso;

        if (sscanf(linha, "%[^;];%[^;];%f", vOrigem, vDestino, &peso) == 3) {

            if (!existeVertice(primeiro, vOrigem)) {
                Grafo novo = malloc(sizeof(struct registo1));
                strcpy(novo->vertice, vOrigem);
                novo->adjacentes = NULL;
                novo->seguinte = NULL;

                if (primeiro == NULL) {
                    primeiro = novo;
                    atual = novo;
                } else {
                    atual->seguinte = novo;
                    atual = novo;
                }
            }

            if (!existeVertice(primeiro, vDestino)) {
                Grafo novo = malloc(sizeof(struct registo1));
                strcpy(novo->vertice, vDestino);
                novo->adjacentes = NULL;
                novo->seguinte = NULL;

                if (primeiro == NULL) {
                    primeiro = novo;
                    atual = novo;
                } else {
                    atual->seguinte = novo;
                    atual = novo;
                }
            }

            Grafo origem = primeiro;
            while (strcmp(origem->vertice, vOrigem) != 0)
                origem = origem->seguinte;

            struct registo2* novoAdjacente = malloc(sizeof(struct registo2));
            strcpy(novoAdjacente->vertice, vDestino);
            novoAdjacente->peso = peso;
            novoAdjacente->seguinte = origem->adjacentes;
            origem->adjacentes = novoAdjacente;
        }
    }

    fclose(fp);
    return primeiro;
}

/**
 * @brief função que emprime na consola a localização correspondente ao seu id
 * 
 * @param id id da localização
 */
void imprimirLocalizacao(const char* id) {
    FILE* ficheiro = fopen("localizacoes.txt", "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro de localizacoes.\n");
        return;
    }

    char linha[MAX_LOCAL_LENGTH];
    char* token;

    while (fgets(linha, MAX_LOCAL_LENGTH, ficheiro) != NULL) {
        token = strtok(linha, ";");
        if (strcmp(token, id) == 0) {
            token = strtok(NULL, ";");
            printf("Local: %s\n", token);
            fclose(ficheiro);
            return;
        }
    }

    fclose(ficheiro);
    printf("ID nao encontrado.\n");
}

/**
 * @brief função que lista os transportes de um determinado tipo a 1km de distancia da localizaçã atual
 * 
 * @param localizacaoAtual localização atual do cliente para o qual vão ser listados os vertices adjacentes a 1km
 * @param tipoTransporte intiero que representa tipo de transporte
 */
void listarAdjacentesRaio(const char* localizacaoAtual, int tipoTransporte) {
    char arestaAtual[TAM];
    float peso;
    int idTransporte;
    int tipo;
    char localizacao[TAM];
    float custo;
    float bat;
    float aut;

    Grafo grafo = lerGrafoDoFicheiro();
    if (grafo == NULL) {
        printf("Erro ao ler o grafo do ficheiro!\n");
        return;
    }

    transporte* inicioTransporte = lerTransportes();
    if (inicioTransporte == NULL) {
        printf("Erro ao ler os transportes do ficheiro!\n");
        return;
    }

    int encontrou = 0;

    transporte* transporteAtual = inicioTransporte;
    while (transporteAtual != NULL) {
        if (strcmp(transporteAtual->localizacao, localizacaoAtual) == 0 && transporteAtual->tipo == tipoTransporte) {
            printf("ID: %d, Tipo: %d, Custo: %.2f, Bateria: %.2f, Autonomia: %.2f\n", transporteAtual->id, transporteAtual->tipo, transporteAtual->custo, transporteAtual->bat, transporteAtual->aut);
            encontrou = 1;
        }
        transporteAtual = transporteAtual->seguinte;
    }

    // Percorre o grafo para encontrar a localização atual
    while (grafo != NULL) {
        if (strcmp(grafo->vertice, localizacaoAtual) == 0) {
            // Encontrou a localização atual, percorre os adjacentes
            Adjacente aux = grafo->adjacentes;
            while (aux != NULL) {
                // Verifica o peso da aresta entre a localização atual e a localização adjacente
                if (aux->peso <= 0.5) {
                    // Percorre a lista de transportes para encontrar o transporte na localizacao correspondente
                    transporte* transporteAux = inicioTransporte;
                    while (transporteAux != NULL) {
                        if (strcmp(transporteAux->localizacao, aux->vertice) == 0 && transporteAux->tipo == tipoTransporte) {
                            printf("ID: %d, Tipo: %d, Custo: %.2f, Bateria: %.2f, Autonomia: %.2f\n", transporteAux->id, transporteAux->tipo, transporteAux->custo, transporteAux->bat, transporteAux->aut);
                            encontrou = 1;
                        }
                        transporteAux = transporteAux->seguinte;
                    }
                }
                aux = aux->seguinte;
            }
            break;
        }
        grafo = grafo->seguinte;
    }

    if (!encontrou) {
        printf("Nao foram encontrados transportes do tipo escolhido e na sua localizacao atual.\n");
    }
}