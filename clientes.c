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

int verifLoginCliente(cliente* inicio, int id, char password[]) {
    while (inicio != NULL) {
        if (inicio->id == id && strcmp(inicio->password, password) == 0) {
            return inicio->id;
        }
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
        int id, nif;
        char nome[MAX_NAME_LENGTH + 1], password[MAX_PASSWORD_LENGTH + 1], morada[MAX_MORADA_LENGTH + 1];
        float saldo;

        while (!feof(fp)) { 
            fscanf(fp, "%d;%[^;];%[^;];%d;%[^;];%f\n", &id, &nome, &password, &nif, &morada, &saldo);
            aux = criarContaCliente(aux, id, password, nome, nif, morada, saldo);
        }

        fclose(fp);
    }

    return aux;
}

// listar na consola o conteúdo da lista ligada
void listarClientes(cliente* inicio){
    while (inicio != NULL){
        printf("ID: %d, Nome: %s, Password: %s, NIF: %d, Morada: %s, Saldo: %.2f\n", inicio->id, inicio->nome, inicio->password, inicio->nif, inicio->morada, inicio->saldo);
        inicio = inicio->seguinte;
    }
}

void listarApenasCliente(cliente* inicio, int id) {
    cliente* aux = inicio;

    while (aux != NULL) {
        if (aux->id == id) {
            printf("ID: %d, Nome: %s, Password: %s, NIF: %d, Morada: %s, Saldo: %.2f\n", aux->id, aux->nome, aux->password, aux->nif, aux->morada, aux->saldo);
            break;
        }
        aux = aux->seguinte;
    }

    if (aux == NULL) {
        printf("Cliente nao encontrado.\n");
    }
}

void alterarDadosCliente(cliente* inicio, int id) {
    cliente* aux = inicio;
    int opcao;

    while (aux != NULL) {
        if (aux->id == id) {
            printf("Dados atuais:\n");
            printf("ID: %d, Nome: %s, Password: %s, NIF: %d, Morada: %s, Saldo: %.2f\n", aux->id, aux->nome, aux->password, aux->nif, aux->morada, aux->saldo);
            printf("\nDigite o número correspondente à opção que deseja alterar:\n");
            printf("1 - Nome\n2 - Password\n3 - NIF\n4 - Morada\n5 - Saldo\n0 - Sair\n");

            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite o novo nome: ");
                    scanf("%s", aux->nome);
                    printf("Nome alterado com sucesso!\n");
                    break;

                case 2:
                    printf("Digite a nova password: ");
                    scanf("%s", aux->password);
                    printf("Password alterada com sucesso!\n");
                    break;

                case 3:
                    printf("Digite o novo NIF: ");
                    scanf("%d", &aux->nif);
                    printf("NIF alterado com sucesso!\n");
                    break;

                case 4:
                    printf("Digite a nova morada: ");
                    scanf("%s", aux->morada);
                    printf("Morada alterada com sucesso!\n");
                    break;

                case 5:
                    printf("Digite o novo saldo: ");
                    scanf("%f", &aux->saldo);
                    printf("Saldo alterado com sucesso!\n");
                    break;

                case 0:
                    printf("Saindo...\n");
                    return;

                default:
                    printf("Opcaoo invalida.\n");
            }
        break;
        }
        aux = aux->seguinte;
    }

    if (aux == NULL) {
        printf("Cliente nao encontrado.\n");
    }
}

cliente* removerCliente(cliente* inicio, int id) {
    cliente *anterior=inicio, *atual=inicio, *aux;

    if (atual==NULL) return(NULL);
    else if (atual->id == id){ // remoção do 1º registo
    aux = atual->seguinte;
    free(atual);
    return(aux);
    }
    else
    { while ((atual!=NULL)&&(atual->id!=id)) 
    {anterior = atual;
    atual = atual->seguinte;
    }
    if (atual==NULL) return(inicio);
    else
    {anterior->seguinte = atual->seguinte;
    free(atual);
    return(inicio);
    }
    }
}

void existeCliente(cliente* inicio, int id){
    if (inicio == NULL) {
        printf("Nenhum cliente registado.\n");
        return;
    }
    while(inicio!=NULL){
        if (inicio->id != id);
            inicio = inicio->seguinte;
    }
}