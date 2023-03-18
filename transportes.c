#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

transporte* criarTransporte(transporte * inicio, int id, int tipo, char localizacao[], float custo, float bat, float aut){
        transporte * novo = malloc(sizeof(struct transporte));
        if (novo != NULL) {
            novo->id = id;
            novo->tipo = tipo;
            strcpy(novo->localizacao, localizacao);
            novo->custo = custo;
            novo->bat = bat;
            novo->aut = aut;
            novo->seguinte = inicio;
            return novo;
        }
    return inicio;
}

void guardarTransporte(transporte* inicio){
    FILE* fp;
    fp = fopen("transportes.txt","a");
    if (fp!=NULL){
        transporte* aux= inicio;
        fprintf(fp,"%d;%d;%s;%.2f;%.2f;%.2f\n", aux->id, aux-> tipo, aux-> localizacao, aux->custo, aux->bat, aux->aut);
        fclose(fp);
    }
}

transporte* lerTransportes(){
    FILE* fp;
    fp = fopen("transportes.txt","r");
    transporte* aux = NULL;

    if (fp!=NULL){
        int id, tipo;
        char localizacao[MAX_MORADA_LENGTH + 1];
        float custo, bat, aut;

        while (!feof(fp)) { 
            fscanf(fp, "%d;%d;%[^;];%f;%f;%f\n", &id, &tipo, &localizacao, &custo, &bat, &aut);
            aux = criarTransporte(aux, id, tipo, localizacao, custo, bat, aut);
        }

        fclose(fp);
    }

    return aux;
}

void ordenarPorBateria(transporte* inicio) {
    int trocado = 1;
    while (trocado) {
        trocado = 0;
        transporte* anterior = NULL;
        transporte* atual = inicio;
        while (atual->seguinte != NULL) {
            if (atual->bat < atual->seguinte->bat) {
                transporte* proximo = atual->seguinte;
                atual->seguinte = proximo->seguinte;
                proximo->seguinte = atual;
                if (anterior != NULL) {
                    anterior->seguinte = proximo;
                } else {
                    inicio = proximo;
                }
                anterior = proximo;
                trocado = 1;
            } else {
                anterior = atual;
                atual = atual->seguinte;
            }
        }
    }
}

void listarPorBateria(transporte* inicio) {
    if (inicio == NULL) {
        printf("Nenhum transporte registado.\n");
        return;
    }
    ordenarPorBateria(inicio);
    while (inicio != NULL){
        printf("ID: %d, Tipo: %d, Localizacao: %s, Custo: %.2f, Bateria: %.2f, Autonomia: %.2f\n", inicio->id, inicio->tipo, inicio->localizacao, inicio->custo, inicio->bat, inicio->aut);
        inicio = inicio->seguinte;
    }
}

void alterarDadosTransporte(transporte* inicio, int id) {
    transporte* transporteAtual = buscarTransporte(inicio, id);
    if (transporteAtual == NULL) {
        printf("Erro: transporte nao encontrado.\n");
        return;
    }

    int opcao;
    do {
        printf("Escolha o que deseja alterar:\n");
        printf("1 - Tipo: %d\n", transporteAtual->tipo);
        printf("2 - Localizacao: %s\n", transporteAtual->localizacao);
        printf("3 - Custo: %.2f\n", transporteAtual->custo);
        printf("4 - Bateria: %.2f\n", transporteAtual->bat);
        printf("5 - Autonomia: %.2f\n", transporteAtual->aut);
        printf("0 - Confirmar alteracao de dados e sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Qual o novo tipo de transporte?\n");
                scanf("%d", &transporteAtual->tipo);
                break;
            case 2:
                printf("Qual a nova localizacao do transporte?\n");
                scanf("%s", transporteAtual->localizacao);
                break;
            case 3:
                do {
                    printf("Qual o novo custo do transporte?\n");
                    scanf("%f", &transporteAtual->custo);

                    if (transporteAtual->custo < 0) {
                        printf("Erro: o custo deve ser positivo.\n");
                    }
                } while (transporteAtual->custo < 0);
                break;
            case 4:
                do {
                    printf("Qual a nova bateria do transporte?\n");
                    scanf("%f", &transporteAtual->bat);

                    if (transporteAtual->bat < 0) {
                        printf("Erro: a bateria deve ser positiva.\n");
                    }
                } while (transporteAtual->bat < 0);
                break;
            case 5:
                do {
                    printf("Qual a nova autonomia do transporte?\n");
                    scanf("%f", &transporteAtual->aut);

                    if (transporteAtual->aut < 0) {
                        printf("Erro: a autonomia deve ser positiva.\n");
                    }
                } while (transporteAtual->aut < 0);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 0);

    // atualiza os dados do arquivo
    FILE* fp = fopen("transportes.txt", "w+");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // escreve todos os transportes atualizados no arquivo
    while (inicio != NULL) {
        fprintf(fp, "%d;%d;%s;%.2f;%.2f;%.2f\n", inicio->id, inicio->tipo, inicio->localizacao, inicio->custo, inicio->bat, inicio->aut);
        inicio = inicio->seguinte;
    }

    fclose(fp);

    printf("Dados do transporte atualizados com sucesso!\n");
}

transporte* buscarTransporte(transporte* inicio, int id) {
    transporte* aux = inicio;

    while (aux != NULL) {
        if (aux->id == id) {
            return aux;
        }
        aux = aux->seguinte;
    }

    // se chegou aqui, o cliente não foi encontrado
    return NULL;
}

void imprimirTransporte(transporte* c) {
    printf("ID: %d, Tipo: %d, Custo: %.2f, Bateria: %.2f, Autonomia: %.2f", c->id, c->tipo, c->custo, c->bat, c->aut);
}