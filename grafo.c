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
 * @brief função que listar arestas de um ponto especifico
 * 
 * @param ponto ponto para ver as suas arestas
 */
void listarArestasPorPonto(const char* ponto) {
    // Abre o ficheiro para leitura
    FILE* fp = fopen("arestas.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro de arestas!\n");
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

        // Verifica se o ponto atual corresponde ao ponto fornecido
        if (strcmp(pontoAtual, ponto) == 0) {
            printf("Ponto: %s, Aresta: %s\n", pontoAtual, arestaAtual);
            encontrou = 1;
        }
    }

    // Fecha o ficheiro
    fclose(fp);

    if (!encontrou) {
        printf("Nao foram encontradas arestas para o ponto '%s'\n", ponto);
    }
}

/**
 * @brief função que emprime na consola a localização correspondente ao seu id
 * 
 * @param id id da localização
 */
void imprimirLocalizacao(const char* id) {
    FILE* arquivo = fopen("localizacoes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de localizacoes.\n");
        return;
    }

    char linha[MAX_LOCAL_LENGTH];
    char* token;

    while (fgets(linha, MAX_LOCAL_LENGTH, arquivo) != NULL) {
        token = strtok(linha, ";");
        if (strcmp(token, id) == 0) {
            token = strtok(NULL, ";");
            printf("Local: %s\n", token);
            fclose(arquivo);
            return;
        }
    }

    fclose(arquivo);
    printf("ID nao encontrado.\n");
}

/**
 * @brief função que lista um tipo de transportes a menos de 1km de um ponto especifico 
 * 
 * @param ponto ponto onde está a cliente
 * @param tipoTransporte inteiro que representa o tipo do transporte
 */
void listarTransportesMaisPerto(const char* ponto, int tipoTransporte) {
    char pontoAtual[MAX_LOCAL_LENGTH];
    char arestaAtual[MAX_LOCAL_LENGTH];
    float peso;
    int idTransporte;
    int tipo;
    char localizacao[MAX_LOCAL_LENGTH];
    float preco;
    float bat;
    float aut;

    // Abre o ficheiro de arestas para leitura
    FILE* fpArestas = fopen("arestas.txt", "r");
    if (fpArestas == NULL) {
        printf("Erro ao abrir o ficheiro de arestas!\n");
        return;
    }

    // Abre o ficheiro de transportes para leitura
    FILE* fpTransportes = fopen("transportes.txt", "r");
    if (fpTransportes == NULL) {
        printf("Erro ao abrir o ficheiro de transportes!\n");
        fclose(fpArestas);
        return;
    }

    // Percorre o ficheiro de arestas linha por linha
    char linhaArestas[MAX_LOCAL_LENGTH];
    int encontrou = 0;
    while (fgets(linhaArestas, MAX_LOCAL_LENGTH, fpArestas)) {
        // Lê o ponto, a aresta e o peso da linha atual do ficheiro de arestas
        sscanf(linhaArestas, "%[^;];%[^;];%f", pontoAtual, arestaAtual, &peso);

        // Verifica se o ponto atual corresponde ao ponto fornecido e se o peso é menor que 1
        if (strcmp(pontoAtual, ponto) == 0 && peso < 1.0) {
            // Procura o transporte na localização correspondente
            char linhaTransportes[MAX_LOCAL_LENGTH];
            while (fgets(linhaTransportes, MAX_LOCAL_LENGTH, fpTransportes)) {
                sscanf(linhaTransportes, "%d;%d;%[^;];%f;%f;%f", &idTransporte, &tipo, localizacao, &preco, &bat, &aut);

                // Verifica se a localização do transporte corresponde à aresta atual
                // Verifica também se o tipo do transporte corresponde ao tipo escolhido pelo cliente
                if (strcmp(localizacao, arestaAtual) == 0 && tipo == tipoTransporte) {
                    printf("ID: %d, Tipo: %d, Preco: %.2f, Bateria: %.2f, Autonomia; %.2f\n", idTransporte, tipo, preco, bat, aut);
                    encontrou = 1;
                }
            }
        }
    }

    // Fecha os ficheiros
    fclose(fpArestas);
    fclose(fpTransportes);

    if (!encontrou) {
        printf("Nao foram encontrados transportes do tipo escolhido a menos de 1km de %s.\n", ponto);
    }
}