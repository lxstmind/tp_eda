#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// Inserção de um novo registo de um gestor
gestor* criarContaGestor(gestor * inicio, int id, char password[], char nome[]){
        gestor * novo = malloc(sizeof(struct gestor));
        if (novo != NULL) {
            novo->id = id;
            strcpy(novo->password, password);
            strcpy(novo->nome, nome);
            novo->seguinte = inicio;
            return novo;
        }
    return inicio;
}

int verifLoginGestor(gestor* inicio, int id, char password[]) {
    while (inicio != NULL) {
        if (inicio->id == id && strcmp(inicio->password, password) == 0) {
            return inicio->id;
        }
        inicio = inicio->seguinte;
    }
    return 0;
}

void guardarGestor(gestor* inicio){
    FILE* fp;
    fp = fopen("gestores.txt","a");
    if (fp!=NULL){
        gestor* aux = inicio;
        fprintf(fp, "%d;%s;%s\n", aux->id, aux->nome, aux->password);
        fclose(fp);
    }
}

gestor* lerGestores(){
    FILE* fp;
    fp = fopen("gestores.txt","r");
    gestor* aux = NULL;

    if (fp!=NULL){
        int id;
        char nome[MAX_NAME_LENGTH + 1], password[MAX_PASSWORD_LENGTH + 1];

        while (!feof(fp)) { 
            fscanf(fp, "%d;%[^;];%[^\n]\n", &id, &nome, &password);
            aux = criarContaGestor(aux, id, password, nome);
        }

        fclose(fp);
    }

    return aux;
}

void alterarDadosGestor(gestor* inicio, int id) {
    gestor* gestorAtual = buscarGestor(inicio, id);
    if (gestorAtual == NULL) {
        printf("Erro: gestor nao encontrado.\n");
        return;
    }

    int opcao;
    do {
        printf("Escolha o que deseja alterar:\n");
        printf("1 - Nome: %s\n", gestorAtual->nome);
        printf("2 - Senha\n");
        printf("0 - Confirmar alteracao de dados e sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Qual o seu novo nome?\n");
                scanf("%s", gestorAtual->nome);
                break;
            case 2:
                printf("Qual a sua nova senha?\n");
                scanf("%s", gestorAtual->password);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 0);

    // atualiza os dados do arquivo
    FILE* fp = fopen("gestores.txt", "w+");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // escreve todos os gestores atualizados no arquivo
    while (inicio != NULL) {
        fprintf(fp, "%d;%s;%s\n", inicio->id, inicio->nome, inicio->password);
        inicio = inicio->seguinte;
    }

    fclose(fp);

    printf("Dados do gestor atualizados com sucesso!\n");
}

gestor* buscarGestor(gestor* inicio, int id) {
    gestor* aux = inicio;

    while (aux != NULL) {
        if (aux->id == id) {
            return aux;
        }
        aux = aux->seguinte;
    }

    // se chegou aqui, o gestor não foi encontrado
    return NULL;
}

void imprimirGestor(gestor* g) {
    printf("ID: %d, Nome: %s, Password: %s\n", g->id, g->nome, g->password);
}

void removerGestor(){
    int idRemover;
    printf("Informe o ID do gestor a ser removido: ");
    scanf("%d", &idRemover);

    // Abre o arquivo para leitura
    FILE* fp = fopen("gestores.txt", "r");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo de gestores!\n");
        return;
    }

    // Abre um arquivo temporário para escrita
    FILE* fpTemp = fopen("temp.txt", "w");
    if(fpTemp == NULL){
        printf("Erro ao criar arquivo temporário!\n");
        fclose(fp);
        return;
    }

    // Percorre o arquivo de gestores linha por linha
    char linha[200];
    int encontrou = 0;
    while(fgets(linha, 200, fp)){
        // Cria um novo gestor a partir da linha atual
        gestor* gest = malloc(sizeof(gestor));
        sscanf(linha, "%d;%[^;];%[^;]", &gest->id, gest->password, gest->nome);

        // Se o ID for diferente do ID a ser removido, escreve a linha no arquivo temporário
        if(gest->id != idRemover){
            fputs(linha, fpTemp);
        } else {
            encontrou = 1;
            free(gest);
        }
    }

    // Fecha os arquivos
    fclose(fp);
    fclose(fpTemp);

    // Remove o arquivo antigo
    remove("gestores.txt");

    // Renomeia o arquivo temporário para o nome original
    rename("temp.txt", "gestores.txt");

    if(encontrou){
        printf("Gestor removido com sucesso!\n");
    } else {
        printf("Gestor não encontrado!\n");
    }
}