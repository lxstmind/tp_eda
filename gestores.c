#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// Inserção de um novo registo de um gestor
gestor* criarContaGestor(gestor * inicio, int id, char password[], char nome[]){
    //if (!existeGestor(inicio, id)){
        gestor * novo = malloc(sizeof(struct gestor));
        if (novo != NULL) {
            novo->id = id;
            strcpy(novo->password, password);
            strcpy(novo->nome, nome);
            novo->seguinte = inicio;
            return novo;
        }
    //} else return(inicio);
    return inicio;
}

int verifLoginGestor(gestor* inicio, int id, char password[]) { //comparar o int id com a string da password e ver se der match, verifica devolve 1 se não 0
    while (inicio != NULL) {
        if (inicio->id==id && strcmp(inicio->password, password) == 0) return inicio->id;
        /* printf("%d %d %s\n", inicio->id, id, password);
        fflush(stdin);
        getchar(); */
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

void existeGestor(gestor* inicio, int id){
    while(inicio!=NULL){
        if (inicio->id != id)
            inicio = inicio->seguinte;
    }
}