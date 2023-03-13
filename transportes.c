#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//Inserção de um meio de transporte
transporte* criarTransporte(transporte * inicio, int id, int tipo, float bat, float aut){
    //if (!existeGestor(inicio, id)){
        transporte * novo = malloc(sizeof(struct transporte));
        if (novo != NULL) {
            novo->id = id;
            novo->tipo = tipo;
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
        fprintf(fp,"%d;%d;%.2f;%.2f\n", aux->id, aux-> tipo, aux->bat, aux->aut);
        fclose(fp);
    }
}

// listar na consola o conteúdo da lista ligada
void listarTransportes(transporte* inicio){
    while (inicio != NULL){
        printf("ID: %d, Tipo: %d, Bateria: %.2f, Autonomia: %.2f\n", inicio->id, inicio->tipo, inicio->bat, inicio->aut);
        inicio = inicio->seguinte;
    }
}