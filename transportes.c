#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//Inserção de um meio de transporte
transporte* criarTransporte(transporte * inicio, int id, int tipo, char localizacao[], float custo, float bat, float aut){
    //if (!existeGestor(inicio, id)){
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
    //} else return(inicio);
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