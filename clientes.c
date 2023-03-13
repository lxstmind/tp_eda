#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// Inserção de um novo registo de um cliente
cliente* criarContaCliente(cliente * inicio, int id, char password[], char nome[], int nif, char morada[], float saldo){
    //if (!existeCliente(inicio, id)){
        cliente * novo = malloc(sizeof(struct cliente));
        if (novo != NULL) {
            novo->id = id;
            strcpy(novo->password, password);
            strcpy(novo->nome, nome);
            novo->nif = nif;
            strcpy(novo->morada, morada);
            novo->saldo = saldo;
            novo->seguinte = inicio;
            return(novo);
        }
    //} else return(inicio);
    return(inicio);
}

int verifLoginCliente(cliente* inicio, int id, char password[]) { //comparar o int id com a string da password e ver se dá match, verifica devolve 1 se não 0
    while (inicio != NULL) {
        if (inicio->id==id && strcmp(inicio->password, password) == 0) return inicio->id;

        inicio = inicio->seguinte;
    }

    return 0;
}

void guardarCliente(cliente* inicio){
    FILE* fp;
    fp = fopen("clientes.txt","a");
    if (fp!=NULL){
        cliente* aux= inicio;
        fprintf(fp,"%d;%s;%s;%d;%s;%.2f\n", aux->id, aux->nome, aux->password, aux->nif, aux->morada, aux->saldo);
        fclose(fp);
    }
}

cliente* lerClientes(){
    FILE* fp;
    fp = fopen("clientes.txt","r");
    cliente* aux = NULL;

    if (fp!=NULL){
        int id;
        char nome[MAX_NAME_LENGTH + 1], password[MAX_PASSWORD_LENGTH + 1];

        while (!feof(fp)) { 
            fscanf(fp, "%d;%[^;];%[^\n]\n", &id, &nome, &password);
            //aux = criarContaCliente(aux, id, password, nome);
        }

        fclose(fp);
    }

    return aux;
}

void existeCliente(cliente* inicio, int id){
    while(inicio!=NULL){
        if (inicio->id != id);
            inicio = inicio->seguinte;
    }
}

// listar na consola o conteúdo da lista ligada
void listarClientes(cliente* inicio){
    while (inicio != NULL){
        printf("ID: %d, Nome: %s, Password: %s, NIF: %d, Morada: %s, Saldo: %.2f\n", inicio->id, inicio->nome, inicio->password, inicio->nif, inicio->morada, inicio->saldo);
        inicio = inicio->seguinte;
    }
}